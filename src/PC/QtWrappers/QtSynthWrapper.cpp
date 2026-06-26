#include "QtSynthWrapper.hpp"

QtSynthWrapper::QtSynthWrapper(Synth &synth, QQmlApplicationEngine &appEngine, QObject *parent)
    : synth_(synth), appEngine_(appEngine), QObject{parent} {
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
    QObject *moduleWrapper = nullptr;
    QString moduleUrl("qrc:/qt/qml/synth/ui/");

    switch (type) {
        case VCO: {
            Vco *newVco = dynamic_cast<Vco*>(newModule);
            if (!newVco)
                return ;
            moduleWrapper = new QtVcoWrapper(newVco, this);
            moduleUrl.append("Vco.qml");
            break;
        }
        case VCA: {
            Vca *newVca = dynamic_cast<Vca*>(newModule);
            if (!newVca)
                return ;
            moduleWrapper = new QtVcaWrapper(newVca);
            moduleUrl.append("Vca.qml");
            break;
        }
        case ENV: {
            Env *newEnv = dynamic_cast<Env*>(newModule);
            if (!newEnv)
                return ;
            moduleWrapper = new QtEnvWrapper(newEnv);
            moduleUrl.append("Env.qml");
            break;
        }
        case MIXER_4: {
            Mixer_4 *newMixer4 = dynamic_cast<Mixer_4*>(newModule);
            if (!newMixer4)
                return ;
            moduleUrl.append("Mixer4.qml");
            moduleWrapper = new QtMixer4Wrapper(newMixer4);
            break;
        }
    }
    if (!moduleWrapper){
        std::cerr << "Error while creating AudioModule" << std::endl;
        return ;
    }
    QQmlComponent component(&appEngine_, QUrl(moduleUrl));
    QObject *obj = component.create();
    if (!obj) {
        std::cerr << "Error while creating QtComponent: " << component.errorString().toStdString() << std::endl;
        return;
    }

    obj->setProperty("engine", QVariant::fromValue(moduleWrapper));
    qtAudioModules_.append(QVariant::fromValue(moduleWrapper));

    QList<QObject*> rootObjs = appEngine_.rootObjects();
    std::cerr << "rootObjects count: " << rootObjs.size() << std::endl;
    if (rootObjs.isEmpty()) {
        std::cerr << "appEngine_ has no loaded QML! Wrong engine instance?" << std::endl;
        return;
    }
    QQuickItem *mainContainer = rootObjs.first()->findChild<QQuickItem*>("mainContainer");
    if (!mainContainer) {
        std::cerr << "mainContainer not found in QML tree" << std::endl;
        return;
    }

    QQuickItem *item = qobject_cast<QQuickItem*>(obj);
    if (!item) {
        std::cerr << moduleUrl.toStdString() << " root object is not a QQuickItem" << std::endl;
        return;
    }

    item->setParentItem(mainContainer);

    // QQuickItem *item = qobject_cast<QQuickItem *>(obj);
    // QList<QObject*> rootObjs = appEngine_.rootObjects();
    // QObject *root = rootObjs.first();
    // QQuickWindow *windowRoot = qobject_cast<QQuickWindow*>(root);
    // if (!windowRoot) {
        // std::cerr << "root is not a QQuickWindow" << std::endl;
        // return;
    // }

    // QQuickItem *container = windowRoot->contentItem();  // <-- le vrai item racine utilisable comme parent
    // item->setParentItem(container);

}