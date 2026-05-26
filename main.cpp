#include "./Osc.hpp"
#include "./Synth.hpp"
#include "./rtaudio/RtAudio.h"
#include "synthesizer.h"
#include <iostream>
#include <unistd.h>

int audioCallback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
        double streamTime, RtAudioStreamStatus status, void *userData) {

    (void) inputBuffer;
    (void) streamTime;
    (void) status;

    double *outBuffer = (double *)outputBuffer;
    Synth *self = static_cast<Synth *>(userData);

    self->render();
    std::array< float, BUFFER_FRAMES > &oscBuff = self->getBuffer();

    for (unsigned int i = 0; i < nBufferFrames; i++) {
        *outBuffer++ = oscBuff[i];
    }
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

    params.deviceId = audio.getDefaultOutputDevice();
    params.nChannels = 1;
    params.firstChannel = 0;
    unsigned int sampleRate = SAMPLE_RATE; // freq d'echantillonnage
    unsigned int bufferFrames = BUFFER_FRAMES; // sample frames

    if (audio.openStream(&params, NULL, RTAUDIO_FLOAT64, sampleRate,
                         &bufferFrames, audioCallback, (void *)&synth));
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
        osc.incFreq();
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