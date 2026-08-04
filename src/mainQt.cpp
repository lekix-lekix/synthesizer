#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "Synth.hpp"
#include "../rtaudio/RtAudio.h"
#include "QtWrappers.hpp"
#include <qdiriterator.h>
#include <ui/InputHandler.hpp>
#include <dsp_library/dsp.hpp>
#include <DrawArea.hpp>
#include "AudioBackend.hpp"
#include "World.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    World world;
    World::s_instance = &world;
    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []()
        { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    // qmlRegisterSingletonInstance<World>("synth", 1, 0, "World", &world);

    Synth synth;
    InputHandler inputHandler(synth);
    QtSynthWrapper synthWrapper(synth, engine);

    InputHandler::setInstance(&inputHandler);

    engine.addImportPath("qrc:/qt/qml/synth/ui/qml/modules");

    app.installEventFilter(&inputHandler);

    engine.rootContext()->setContextProperty("synth", &synthWrapper);
    engine.load(QUrl(QStringLiteral("qrc:/qt/qml/synth/ui/qml/Main.qml")));

    std::vector<std::shared_ptr<AudioModule>> const &modules = synth.getAudioModules();

    if (audioBackendInit(&synth) == false) return -1;
    int ret = QGuiApplication::exec();
    audioBackendClose();

    return ret;
}