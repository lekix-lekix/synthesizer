#include "./rtaudio/RtAudio.h"
#include "synthesizer.hpp"
#include <iostream>
#include <chrono>
#include <cassert>
#include <unistd.h>

using unit_t = std::chrono::milliseconds;

int audioCallback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
        double streamTime, RtAudioStreamStatus status, void *userData) {

    (void) inputBuffer;
    (void) streamTime;
    (void) status;
    
    // auto start = std::chrono::steady_clock::now();
    double *outBuffer = (double *)outputBuffer;
    Synth *self = static_cast<Synth *>(userData);

    self->render();
    std::array< float, BUFFER_FRAMES > &oscBuff = self->getBuffer();

    for (unsigned int i = 0; i < nBufferFrames; i++) {
        assert(!std::isnan(oscBuff[i]));
        assert(!std::isinf(oscBuff[i]));
        assert(std::abs(oscBuff[i]) <= 1.0f); // clipping check
        
        // Détecter les sauts brutaux
        // if (i > 100) {
            // float delta = std::abs(oscBuff[i] - oscBuff[i-1]);
            // assert(delta < 0.5f); // seuil à ajuster
        // }
        *outBuffer++ = oscBuff[i];
    }
    // auto end = std::chrono::steady_clock::now();
    // std::cout << std::chrono::duration_cast<unit_t>(end - start).count() << " ms\n"; 
    return (0);
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

    synth.addOsc(std::make_unique<Osc>());
    synth.addOsc(std::make_unique<Osc>());
    synth.addOsc(std::make_unique<Osc>());

    synth.getOsc(0)->setWave(SAW); 
    synth.getOsc(1)->setWave(SAW); 
    synth.getOsc(2)->setWave(SAW); 
    
    synth.getOsc(0)->setFreq(261.626f);
    synth.getOsc(1)->setFreq(311.127f); // C minor
    synth.getOsc(2)->setFreq(391.995f);

    params.deviceId = audio.getDefaultOutputDevice();
    params.nChannels = 1;
    params.firstChannel = 0;
    unsigned int sampleRate = SAMPLE_RATE; // freq d'echantillonnage
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
    for (int i = 0; i < 200; i++) {
        usleep(10000);
        synth.getOsc(0)->incFreq();
    }
    for (int j = 0; j < 200; j++) {
        usleep(10000);
        synth.getOsc(0)->decFreq();
    }

    
    std::cin.get(input);

    // Block released ... stop the stream
    if (audio.isStreamRunning())
        audio.stopStream(); // or could call audio.abortStream();

cleanup:
    if (audio.isStreamOpen())
        audio.closeStream();

    return 0;
}