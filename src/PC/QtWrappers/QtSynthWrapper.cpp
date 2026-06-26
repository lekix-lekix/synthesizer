#include "QtSynthWrapper.hpp"

QtSynthWrapper::QtSynthWrapper(Synth &synth, QObject *parent)
    : synth_(synth), QObject{parent} {
    synth.onAudioModuleCreated = [this](AudioModule *newModule, e_audioModules type) {
        this->onAudioModuleCreated(newModule, type);
    };
}

QtSynthWrapper &QtSynthWrapper::setGate(bool state) { // TO CHANGE
    std::vector<std::shared_ptr<AudioModule>> &modules = synth_.getAudioModules();
    std::shared_ptr<Env> env = nullptr;
    for (auto &module : modules) {
        env = std::dynamic_pointer_cast<Env>(module);
        if (env)
            break;
    }
    if (env)
        env->gateIn = state;
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

void QtSynthWrapper::onAudioModuleCreated(AudioModule *newModule, e_audioModules type) { // BIG TROUBLE
    QObject *moduleWrapper;

    switch (type) {
        case VCO: {
            Vco *newVco = dynamic_cast<Vco*>(newModule);
            if (!newVco)
                return ;
            qtAudioModules_.append(QVariant::fromValue(new QtVcoWrapper(newVco, this)));
            break;
        }
        default:
            break;
        }
    std::cout << "Audio Module created" << std::endl;
}