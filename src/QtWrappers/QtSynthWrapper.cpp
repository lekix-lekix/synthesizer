#include "QtSynthWrapper.hpp"

QtSynthWrapper::QtSynthWrapper(Synth &synth, QQmlApplicationEngine &appEngine, QObject *parent)
    : synth_(synth), appEngine_(appEngine), QObject{parent} {
    synth.onAudioModuleCreated = [this](AudioModule *newModule, e_audioModules type) {
        this->onAudioModuleCreated(newModule, type);
    };
    appEngine_.rootContext()->setContextProperty("synth", this);
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

void QtSynthWrapper::onAudioModuleCreated(AudioModule *newModule, e_audioModules type) {
    QObject *moduleWrapper = nullptr;
    QString moduleUrl("qrc:/qt/qml/synth/ui/qml/modules/");

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
    qtAudioModules_.append(QVariant::fromValue(moduleWrapper));
    this->insertQmlModule(moduleUrl, moduleWrapper);
}

void QtSynthWrapper::insertQmlModule(QString moduleUrl, QObject *moduleWrapper) {
    QQmlComponent component(&appEngine_, QUrl(moduleUrl));
    QVariantMap initialProps;
    std::cerr << "moduleWrapper ptr: " << moduleWrapper << std::endl;
    initialProps["engine"] = QVariant::fromValue(moduleWrapper);

    std::cout << "COUCOU" << std::endl;
    QObject *obj = component.createWithInitialProperties(initialProps, appEngine_.rootContext());
    if (!obj) {
        std::cerr << "Error while creating QtComponent: " << component.errorString().toStdString() << std::endl;
        return;
    }
    std::cout << "END COUCOU" << std::endl;

    QList<QObject*> rootObjs = appEngine_.rootObjects();
    std::cerr << "rootObjects count count: " << rootObjs.size() << std::endl;
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
    std::cout << "main container " << mainContainer << std::endl;
    item->setParentItem(mainContainer);
    auto *mw = qobject_cast<QtModuleWrapper *>(moduleWrapper);
    if (mw) {
        std::cout << "init connect" << std::endl;
        QObject::connect(mw, &QtModuleWrapper::connectionRequestSignal, this, &QtSynthWrapper::onConnectionRequest);
        QObject::connect(mw, &QtModuleWrapper::disconnectionRequestSignal, this, &QtSynthWrapper::onDisconnectionRequest);
    }
}