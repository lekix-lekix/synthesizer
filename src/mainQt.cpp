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

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []()
        { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    Synth synth;
    // qmlRegisterType<DrawArea>("synth", 1, 0, "DrawArea");
    // DrawArea drawArea;
    InputHandler inputHandler(synth);
    QtSynthWrapper synthWrapper(synth, engine);

    // InputHandler inputHandler(synth);
    InputHandler::setInstance(&inputHandler);

    engine.addImportPath("qrc:/qt/qml/synth/ui/qml/modules");

    app.installEventFilter(&inputHandler);

    engine.rootContext()->setContextProperty("synth", &synthWrapper);
    // engine.load(QUrl(QStringLiteral("qrc:/synth/ui/qml/Main.qml")));
    engine.load(QUrl(QStringLiteral("qrc:/qt/qml/synth/ui/qml/Main.qml")));
    // engine.loadFromModule("synth", "Main");

    std::vector<std::shared_ptr<AudioModule>> const &modules = synth.getAudioModules();

    // params.nChannels = 1;
    // params.firstChannel = 0;
    // unsigned int sampleRate = SAMPLE_RATE;     // freq d'echantillonnage
    // unsigned int bufferFrames = BUFFER_FRAMES; // sample frames

    // std::cout << bufferFrames << std::endl;
    // if (audio.openStream(&params, NULL, RTAUDIO_FLOAT64, sampleRate,
    //                      &bufferFrames, audioCallback, (void *)&synth))
    // {
    //     std::cerr << '\n'
    //               << audio.getErrorText() << '\n'
    //               << std::endl;
    // }

    // if (audio.startStream())
    // {
    //     std::cerr << audio.getErrorText() << std::endl;
    //     audio.closeStream();
    //     return -1;
    // }

    // std::cout << "nb of modules : " << synth.getAudioModules().size() << std::endl;

    // // ✅ Le stream tourne en arrière-plan (thread séparé RtAudio)
    // // Qt prend la main ici — audioCallback continue de s'exécuter
    // // Cleanup APRÈS la fermeture de la fenêtre Qt
    // if (audio.isStreamRunning())
    //     audio.stopStream();
    // if (audio.isStreamOpen())
    //     audio.closeStream();

    if (audioBackendInit(&synth) == false) return -1;
    int ret = QGuiApplication::exec();
    audioBackendClose();

    return ret;
}