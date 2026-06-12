#include "../rtaudio/RtAudio.h"
#include <iostream>
#include <chrono>
#include <cassert>
#include <unistd.h>
#include "Synth.hpp"
#include <termios.h>
#include <fcntl.h>

using us = std::chrono::nanoseconds;
using Time = std::chrono::steady_clock;

// AUDIO TESTS
// auto stop1 = Time::now();
// auto stop2 = Time::now();
// std::cout << "read time = " << std::chrono::duration_cast<us>(stop2 - stop1).count() << std::endl;
// assert(!std::isnan(frame));
// assert(!std::isinf(frame));
// assert(std::abs(frame) <= 1.0f); // clipping check

// Détecter les sauts brutaux
// if (i > 2) {
//     float delta = std::abs(frame - prev);
//     assert(delta < 0.5f); // seuil à ajuster
// }
// std::cout << "frame = " << frame << std::endl;
// prev = frame;
// auto end = Time::now();
// auto time_elapsed = std::chrono::duration_cast<us>(end - start).count();
// std::cout << "time_elapsed = " << time_elapsed << std::endl;
// (void) time_elapsed;
// std::cout << "AudioCallback : " << time_elapsed << std::endl;
// assert(time_elapsed < DEADLINE_US);

void setRawMode(bool enable) {
    static termios oldt;
    if (enable) {
        termios newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        // rend stdin non-bloquant
        fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, 0); // restaure mode bloquant
    }
}

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

void checkInputs(std::shared_ptr<Envelope> env) {
    setRawMode(true);

    bool spaceHeld = false;
    bool running = true;
    auto lastSpace = std::chrono::steady_clock::now();

    while (running) {
        char c;
        if (read(STDIN_FILENO, &c, 1) > 0) { // une touche est pressée
            if (c == 'q') running = false;
            if (c == ' ') {
                std::cout << spaceHeld << std::endl;
                if (!spaceHeld) {
                    spaceHeld = true;
                    env->setGate(true);
                }
                lastSpace = std::chrono::steady_clock::now(); // reset timer
            }
        }

        // si aucun ' ' reçu depuis 50ms → relâché
        if (spaceHeld) {
            auto now = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastSpace).count();
            if (elapsed > 50) {
                spaceHeld = false;
                env->setGate(false);
            }
        }

        usleep(5000); // poll toutes les 5ms
    }

}

int main()
{
    RtAudio audio;

    auto ids = audio.getDeviceIds();
    std::cout << "Devices: " << ids.size() << std::endl;
    for (auto id : ids)
    {
        auto info = audio.getDeviceInfo(id);
        std::cout << "  [" << id << "] " << info.name << std::endl;
    }

    RtAudio::StreamParameters params;

    Synth synth;

    synth.addAudioModule(OSC);
    synth.addAudioModule(VCA);
    synth.addAudioModule(MIXER_4);

    std::vector<std::shared_ptr<AudioModule>> const &modules = synth.getAudioModules();
    // for (unsigned int i = 0; i < modules.size(); i++) {
        // if (i != modules.size() - 1)
            // modules[i]->connect(modules[i], modules[i + 1]);
    // }

    std::shared_ptr<Envelope> env = std::dynamic_pointer_cast<Envelope>(synth.addModulator(ENV, modules[1]));

    modules[0]->audioConnect(modules[0], modules[1]);
    modules[1]->audioConnect(modules[1], modules[2]);

    // synth.getModule<Osc>(1)->setFreq(261.626f);
    // synth.getModule<Osc>(2)->setFreq(311.127f);


    // synth.getOsc(1)->setFreq(311.127f); // C minor

    // synth.getOsc(0)->setWave(SAW);
    // synth.getOsc(1)->setWave(SAW);
    // synth.getOsc(2)->setWave(SAW);
    //

    // synth.getOsc(2)->setFreq(391.995f);
    std::cout << synth.getModulators().size() << std::endl;

    params.deviceId = audio.getDefaultOutputDevice();
    params.nChannels = 1;
    params.firstChannel = 0;
    unsigned int sampleRate = SAMPLE_RATE;     // freq d'echantillonnage
    unsigned int bufferFrames = BUFFER_FRAMES; // sample frames

    if (audio.openStream(&params, NULL, RTAUDIO_FLOAT64, sampleRate,
                         &bufferFrames, audioCallback, (void *)&synth))
    {
        std::cerr << '\n'
                  << audio.getErrorText() << '\n'
                  << std::endl;
    }

    // Stream is open ... now start it.
    if (audio.startStream())
    {
        std::cout << audio.getErrorText() << std::endl;
        goto cleanup;
    }
    
    checkInputs(env);

    setRawMode(false);
    audio.stopStream();

    // Block released ... stop the stream
    if (audio.isStreamRunning())
        audio.stopStream(); // or could call audio.abortStream();

cleanup:
    if (audio.isStreamOpen())
        audio.closeStream();

    // DSP.join();
    return 0;
}