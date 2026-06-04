#include "../rtaudio/RtAudio.h"
#include "../includes/synthesizer.hpp"
#include <iostream>
#include <chrono>
#include <cassert>
#include <unistd.h>

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

int audioCallback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
                  double streamTime, RtAudioStreamStatus status, void *userData)
{
    (void)inputBuffer;
    (void)streamTime;
    (void)status;

    // auto start = Time::now();
    double *outBuffer = (double *)outputBuffer;
    Synth *self = static_cast<Synth *>(userData);
    for (unsigned int i = 0; i < nBufferFrames; i++) {
        self->incTotalSamples();
        *outBuffer++ = self->render();
    }

    return (0);
}

int main()
{
    RtAudio audio;

    std::cout << "deadline = " << DEADLINE_US << std::endl;

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
    synth.addAudioModule(OSC);
    synth.addAudioModule(OSC);
    synth.addAudioModule(VCA);

    synth.getModule<Osc>(1)->setFreq(261.626f);
    synth.getModule<Osc>(2)->setFreq(311.127f);


    // synth.getOsc(1)->setFreq(311.127f); // C minor

    // synth.getOsc(0)->setWave(SAW);
    // synth.getOsc(1)->setWave(SAW);
    // synth.getOsc(2)->setWave(SAW);
    //

    // synth.getOsc(2)->setFreq(391.995f);

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

    char input;
    std::cout << "\nPlaying ... press <enter> to quit.\n";
    // for (int i = 0; i < 200; i++) {
    //     usleep(10000);
    //     synth.getOsc(0)->incFreq();
    // }
    // for (int j = 0; j < 200; j++) {
    //     usleep(10000);
    //     synth.getOsc(0)->decFreq();
    // }

    std::cin.get(input);

    // Block released ... stop the stream
    if (audio.isStreamRunning())
        audio.stopStream(); // or could call audio.abortStream();

cleanup:
    if (audio.isStreamOpen())
        audio.closeStream();

    // DSP.join();
    return 0;
}