# 🎛️ Cutee Synth - A Modular Digital Synthesizer

![Cutee Synth screenshot](./Cutee%20Synth.png?raw=true "Cutee Synth")

### Overview

Cutee is a C++ modular synthesizer built on top of my [homemade DSP/synthesis library](https://github.com/lekix-lekix/dsp_library), using the Qt Framework for the UI and the RtAudio library.
The project aims to digitally replicate the behavior of classic analog modular synthesizer modules, with a focus on real-time audio processing and object-oriented
programming.

### Architecture

As every realtime audio project, Cutee runs on a multithreaded architecture : one lock-free realtime audio thread that handles the audio loop (that must go fast and render under ~2.90ms to avoid audio glitches), and one UI thread that handles memory allocations, modulations, UI, etc.

A main Synth class handles the memory allocation, the connections and to render every module :

```cpp
class Synth
{
    private:
        std::vector<std::shared_ptr<AudioModule>>                                 audioModules_;
        std::atomic<std::vector<std::unique_ptr<Patch>>*>                         connections_;

        std::shared_ptr<AudioModule>                makeAudioModule(e_audioModules type);
        std::unique_ptr<Patch>                      makePatch(float *from, float *to);

    public:
        [...]

        std::shared_ptr<AudioModule>                addAudioModule(e_audioModules type);
        std::unique_ptr<Patch>                      connect(float *from, float *to);
        void                                        render();
}
```

Call synth->render on every frame and it will render each audio module it contains, and propagate values from one audio module to another.


The project is designed around C++ QtWrappers classes around the DSP modules, that look like this :

```cpp
class QtVcoWrapper : public QtModuleWrapper
{
    Q_OBJECT
    Q_PROPERTY(float freq READ getFreq WRITE setFreq NOTIFY freqChanged);
    Q_PROPERTY(float freqCVInAmount READ getFreqCVInAmount WRITE setFreqCVInAmount NOTIFY freqCVInAmountChanged);
    Q_PROPERTY(QString wave READ getWaveQstr NOTIFY waveChanged);

private:
    Vco *vco_;
    [...]
}
```

All theses classes are used as interface between the DSP modules and the UI. A knob gets turned in the front-end, the Qt wrapper class gets a notification and send it to the C++ backend.

### DSP Library

All modules share a base class (AudioModule), that share a few attributes : the totalSamplesElapsed, with is used to calculate what should happen relatively to the audio frame rate (44000 samples / second), a name, and a render function.

## Modules

🔊 OSC — Digital Oscillator
Generates an digital audio signal : Sine, square and saw waves.

🔊 VCA — Voltage Controlled Amplifier

Controls the amplitude of an audio signal using a CV input (0–10V standard).

```cpp
audioOutput = audioInput * (gain * (CV_in / 10.0f));
```

- `CV_in` ranges from 0V to 10V
- Divided by 10 to obtain a normalized gain (0.0 → 1.0)
- Multiplied by a manual `gain` parameter (default: 1.0)

📈 Envelope — ADSR
Generates a control voltage envelope following the classic Attack / Decay / Sustain / Release shape.
All envelope outputs are in the 0V → 10V range to match the CV standard.

📈 CV Standard
The project follows the 0–10V CV standard, common in Eurorack modular synthesis

## Usage

Include the dsp library :

```cpp
    #include <dsp/dsp.hpp>
```

Instantiate a module of your choice :

```cpp
Vco vco;
```

Then on every audio frame, call its render function :

```cpp
vco.render()
```

And the module will output its current value for this sample (e.g., vco.audioOutput\_). Send that sample to your buffer (soundcard for PC, DAC for embedded), and you will be on your way to hear something.
Since the library is built to be cross-platform, you either need to patch and connect the modules outputs and inputs together using either software or physical cables.

### PC Implementation (work in progress)

The implementation runs on a multithreaded architecture:

- An audio thread run by RtAudio that renders real-time audio
- An UI thread that handles input parameters and memory allocation

The UI is made with Qt Framework and is currently in progress. Here's a preview of what it looks right now :
![synthesizer-preview](./Synthesizer.png)

## Usage

It is made around a Synth class that contains all AudioModules.

Instantiate a Synth class :

```cpp
    Synth synth;
```

Then, some audio modules :

```cpp
    synth.addAudioModule(OSC);
    synth.addAudioModule(VCA);
    synth.addAudioModule(MIXER_4);
```

Get their outputs in some ways (its still in progress) and connect them :

```cpp
    synth.connect(vcoptr->audioOutput, vcaptr->audioInput);
    synth.connect(vco2ptr->audioOutput, vcaptr->audioInput);
    synth.connect(vcaptr->audioOutput, mixerptr->audioInputs[0]);
    synth.connect(envptr->cvOut, vcaptr->CV_in);
```

## Roadmap

Qt graphical interface and PC Build
VCF — Voltage Controlled Filter
Conception and implementation of physical embedded mdules

Author
lekix-lekix — github.com/lekix-lekix

```

```
