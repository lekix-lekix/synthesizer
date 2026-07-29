#include "RtAudio.h"
#include "AudioBackend.hpp"
#include "Synth.hpp"
#include <dsp_library/dsp.hpp>

static RtAudio audio;

int RTAudioCallback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
                    double streamTime, RtAudioStreamStatus status, void *userData)
{
    (void)inputBuffer;
    (void)streamTime;
    (void)status;

    // auto start = Time::now();
    double *outBuffer = (double *)outputBuffer;
    Synth *self = static_cast<Synth *>(userData);
    if (!self)
        std::cout << "No synth found" << std::endl;
    std::weak_ptr<Mixer_4> mixer = self->getMaster();
    for (unsigned int i = 0; i < nBufferFrames; i++)
    {
        self->render();
        if (!mixer.lock())
            mixer = self->getMaster();
        else
            *outBuffer++ = mixer.lock()->audioOutput;
    }
    return (0);
}

bool RTAudioInit(Synth *synth) {
    RtAudio::StreamParameters params;

    unsigned int sampleRate = SAMPLE_RATE;     // freq d'echantillonnage
    unsigned int bufferFrames = BUFFER_FRAMES; // sample frames

    params.deviceId = audio.getDefaultOutputDevice();
    params.nChannels = 1;
    params.firstChannel = 0;

    if (audio.openStream(&params, NULL, RTAUDIO_FLOAT64, sampleRate,
                        &bufferFrames, RTAudioCallback, (void *)synth)) {
        std::cerr << '\n'
                  << audio.getErrorText() << '\n'
                  << std::endl;
        return false;
    }
    if (audio.startStream()) {
        std::cerr << audio.getErrorText() << std::endl;
        audio.closeStream();
        return false;
    }
    return true;
}

void audioBackendClose() {
    if (audio.isStreamRunning()) audio.stopStream();
    if (audio.isStreamOpen()) audio.stopStream();
}

bool audioBackendInit(Synth *synth) { bool err = RTAudioInit(synth); return err; };