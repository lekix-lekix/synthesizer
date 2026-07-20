#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "Synth.hpp"
#include "../rtaudio/RtAudio.h"
#include "QtWrappers.hpp"
#include <ui/InputHandler.hpp>
#include <dsp_library/dsp.hpp>

int audioCallback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
                  double streamTime, RtAudioStreamStatus status, void *userData)
{
    (void)inputBuffer;
    (void)streamTime;
    (void)status;

    // auto start = Time::now();
    double *outBuffer = (double *)outputBuffer;
    Synth *self = static_cast<Synth *>(userData);
    std::weak_ptr<Mixer_4> mixer = self->getMaster();
    for (unsigned int i = 0; i < nBufferFrames; i++) {
       // self->incTotalSamples();
        // self->inRendering.store(true);
        self->render();
        if (!mixer.lock())
            mixer = self->getMaster();
        else
            *outBuffer++ = mixer.lock()->audioOutput;
        // std::cout << *outBuffer << std::endl;
        // self->inRendering.store(false);
    }
    return (0);
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    Synth synth;
    // InputHandler inputHandler(synth);
    QtSynthWrapper synthWrapper(synth, engine);

    InputHandler inputHandler(synth);
    InputHandler::setInstance(&inputHandler);

    engine.addImportPath("qrc:/qt/qml/synth/ui/qml/modules");

    app.installEventFilter(&inputHandler);
    // qmlRegisterSingletonInstance("synth", 1, 0, "InputHandler", &inputHandler);

    engine.rootContext()->setContextProperty("synth", &synthWrapper);

    engine.load(QUrl(QStringLiteral("qrc:/qt/qml/synth/ui/qml/Main.qml")));

    std::vector<std::shared_ptr<AudioModule>> const &modules = synth.getAudioModules();

    RtAudio audio;
    RtAudio::StreamParameters params;

    params.deviceId = audio.getDefaultOutputDevice();
    std::cout << "device id = " << params.deviceId << std::endl;

    auto ids = audio.getDeviceIds();
    std::cout << "Devices: " << ids.size() << std::endl;
    for (auto id : ids)
    {
        auto info = audio.getDeviceInfo(id);
        std::cout << "  [" << id << "] " << info.name << std::endl;
    }

    params.nChannels = 1;
    params.firstChannel = 0;
    unsigned int sampleRate = SAMPLE_RATE;     // freq d'echantillonnage
    unsigned int bufferFrames = BUFFER_FRAMES; // sample frames

    std::cout << bufferFrames << std::endl;
    if (audio.openStream(&params, NULL, RTAUDIO_FLOAT64, sampleRate,
                         &bufferFrames, audioCallback, (void *)&synth))
    {
        std::cerr << '\n'
                  << audio.getErrorText() << '\n'
                  << std::endl;
    }

    if (audio.startStream())
    {
        std::cerr << audio.getErrorText() << std::endl;
        audio.closeStream();
        return -1;
    }

    std::cout << "nb of modules : " << synth.getAudioModules().size() << std::endl;

    // ✅ Le stream tourne en arrière-plan (thread séparé RtAudio)
    // Qt prend la main ici — audioCallback continue de s'exécuter
    int ret = QGuiApplication::exec();

    // Cleanup APRÈS la fermeture de la fenêtre Qt
    if (audio.isStreamRunning())
        audio.stopStream();
    if (audio.isStreamOpen())
        audio.closeStream();

    return ret;
}