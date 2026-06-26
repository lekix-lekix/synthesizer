#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "Synth.hpp"
#include "../rtaudio/RtAudio.h"
// #include "QtSynthWrapper.hpp"
// #include "QtVcoWrapper.hpp"
// #include "QtVcaWrapper.hpp"
// #include "QtEnvWrapper.hpp"
// #include "QtMixer4Wrapper.hpp"
#include "QtWrappers.hpp"
#include <dsp/dsp.hpp>

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
        self->render();
        // std::cout << mixer.lock()->getOutput() << std::endl;
        *outBuffer++ = mixer.lock()->audioOutput;
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
    // engine.loadFromModule("synth", "Main");

    Synth synth;
    QtSynthWrapper synthWrapper(synth, engine);
    app.installEventFilter(&synthWrapper);

    engine.load(QUrl(QStringLiteral("qrc:/qt/qml/synth/ui/Main.qml")));

    std::shared_ptr<AudioModule> osc = synth.addAudioModule(VCO);
    std::shared_ptr<AudioModule> osc2 = synth.addAudioModule(VCO);
    std::shared_ptr<AudioModule> vca = synth.addAudioModule(VCA);
    std::shared_ptr<AudioModule> mixer = synth.addAudioModule(MIXER_4);
    std::shared_ptr<AudioModule> env = synth.addAudioModule(ENV);

    Vco *vcoptr = dynamic_cast<Vco*>(osc.get());
    Vco *vco2ptr = dynamic_cast<Vco*>(osc2.get());
    Vca *vcaptr = dynamic_cast<Vca*>(vca.get());
    Mixer_4 *mixerptr = dynamic_cast<Mixer_4 *>(mixer.get());
    Env* envptr = dynamic_cast<Env *>(env.get());

    synth.connect(vcoptr->audioOutput, vcaptr->audioInput);
    synth.connect(vco2ptr->audioOutput, vcaptr->audioInput);
    synth.connect(vcaptr->audioOutput, mixerptr->audioInputs[0]);
    synth.connect(envptr->cvOut, vcaptr->CV_in);

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

    // QtVcoWrapper oscWrapper(dynamic_cast<Vco *>(osc.get())); // /!\ -> twice, as there is already one created in QSynthWrapper
    // QtVcoWrapper oscWrapper2(dynamic_cast<Vco *>(osc2.get()));
    // QtVcaWrapper vcaWrapper(dynamic_cast<Vca *>(vca.get())); // same
    // QtEnvWrapper envWrapper(dynamic_cast<Env *>(env.get()));
    // QtMixer4Wrapper mixerWrapper(dynamic_cast<Mixer_4 *>(mixer.get()));

    // engine.rootContext()->setContextProperty("osc", &oscWrapper);
    // engine.rootContext()->setContextProperty("osc2", &oscWrapper2);
    // engine.rootContext()->setContextProperty("vca", &vcaWrapper);
    // engine.rootContext()->setContextProperty("env", &envWrapper);
    // engine.rootContext()->setContextProperty("mixer", &mixerWrapper);

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