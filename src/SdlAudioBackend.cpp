#include <SDL2/SDL.h>
#include "Synth.hpp"

int device = -1;

void SDLAudiocallback(void *udata, Uint8 *stream, int len) {
    float *out = (float *)stream;
    int num_samples = len / sizeof(float);
    Synth *self = static_cast<Synth *>(udata);
    if (!self)
        std::cout << "No synth found" << std::endl;
    std::weak_ptr<Mixer_4> mixer = self->getMaster();

    for (int i = 0; i < num_samples; i++) {
        self->render();
        if (!mixer.lock())
            out[i] = 0;
            // mixer = self->getMaster();
        else
            out[i] = static_cast<float>(mixer.lock()->audioOutput);
    }
}

bool SDLAudioInit(Synth *synth) {
    SDL_Init(SDL_INIT_AUDIO);

    SDL_AudioSpec wanted;

    /* Set the audio format */
    wanted.freq = SAMPLE_RATE;
    wanted.format = AUDIO_F32SYS;
    wanted.channels = 1;    /* 1 = mono, 2 = stereo */
    wanted.samples = 256;  /* Minimum value handled by SDL */
    wanted.callback = SDLAudiocallback;
    wanted.userdata = (void*)synth;

    /* Open the audio device, forcing the desired format */
    device = SDL_OpenAudio(&wanted, NULL);
    if (device < 0) {
        fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
        return(false);
    }
    SDL_PauseAudio(0);
    return (true);
}

void audioBackendClose() {
    SDL_CloseAudioDevice(device);
    SDL_Quit();
}

bool audioBackendInit(Synth *synth) { return SDLAudioInit(synth); }