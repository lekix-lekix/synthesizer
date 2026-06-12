#include "QtSynthWrapper.hpp"

QtSynthWrapper::QtSynthWrapper(Synth &synth, QObject *parent)
    : synth_(synth), QObject{parent} {
    synth.onAudioModuleCreated = [this](AudioModule *newModule, e_audioModules type) {
        this->onAudioModuleCreated(newModule, type);
    };
    synth.onModulatorCreated = [this](Modulator *newModule, e_modulators type) {
        this->onModulatorCreated(newModule, type);
    };
}

QtSynthWrapper &QtSynthWrapper::setGate(bool state) {
    std::vector<std::shared_ptr<Modulator>> &modules = synth_.getModulators();
    std::shared_ptr<Envelope> env = std::dynamic_pointer_cast<Envelope>(modules[0]);

    env->setGate(state);
    return *this;
}

bool QtSynthWrapper::eventFilter(QObject *obj, QEvent *event) { // to move into a keyboard module
    if (event->type() == QEvent::KeyPress) {
        // std::cout << "keypress detected\n";
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

        if (keyEvent->isAutoRepeat()) // ignorer la répétition clavier
            return false;

        switch (keyEvent->key())
        {
            case Qt::Key_A: this->setGate(true);  return true;

        }
    }
    else if (event->type() == QEvent::KeyRelease){
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

        if (keyEvent->isAutoRepeat())
            return false;

        switch (keyEvent->key()) {
            case Qt::Key_A: this->setGate(false); return true;
        }
    }

    return QObject::eventFilter(obj, event); // ← important : passer les autres événements
}

void QtSynthWrapper::onModulatorCreated(Modulator *newModule, e_modulators type) {
    QObject *moduleWrapper;

    switch (type) {
    case ENV: {
        Envelope *newEnv = dynamic_cast<Envelope*>(newModule);
        if (!newEnv)
            return ;
        qtModulators_.append(QVariant::fromValue(new QtEnvWrapper(newEnv, this)));
        break;
    }
        default:
            break;
    }
    std::cout << "Modulator created" << std::endl;
}

void QtSynthWrapper::onAudioModuleCreated(AudioModule *newModule, e_audioModules type) {
    QObject *moduleWrapper;

    switch (type) {
    case OSC: {
        Osc *newOsc = dynamic_cast<Osc*>(newModule);
        if (!newOsc)
            return ;
        qtAudioModules_.append(QVariant::fromValue(new QtOscWrapper(newOsc, this)));
        break;
    }
    default:
        break;
    }
    std::cout << "Audio Module created" << std::endl;
}