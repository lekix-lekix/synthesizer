#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Synth.hpp"
#include "../rtaudio/RtAudio.h"
#include "QtSynthWrapper.hpp"
#include "constants.hpp"

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
        self->incTotalSamples();
        self->render();
        // std::cout << mixer.lock()->getOutput() << std::endl;
        *outBuffer++ = mixer.lock()->getOutput();
        // std::cout << "=======\n";
        // std::cout << *(outBuffer - 1) << std::endl;
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
    engine.loadFromModule("synth", "Main");

    Synth synth;
    QtSynthWrapper synthWrapper(synth);
    app.installEventFilter(&synthWrapper);

    synth.addAudioModule(OSC);
    synth.addAudioModule(VCA);
    synth.addAudioModule(MIXER_4);

    std::vector<std::shared_ptr<AudioModule>> const &modules = synth.getAudioModules();

    std::cout << modules.size() << std::endl;

    modules[0]->audioConnect(modules[0], modules[1]);
    modules[1]->audioConnect(modules[1], modules[2]);

    std::shared_ptr<Envelope> env = std::dynamic_pointer_cast<Envelope>(synth.addModulator(ENV, modules[1]));

    // env->setGate(true);

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