# 🎛️ Modular Digital Synthesizer

## Cross-platform modular digital synthesizer — PC & Embedded (Work in progress)


### Overview
A C++ modular synthesizer engine designed to run both on desktop (PC) and embedded hardware (Daisy Seed / STM32). The project aims to digitally replicate the behavior of classic analog modular synthesizer modules, with a focus on real-time audio processing.

### Architecture
The engine runs on a multithreaded architecture:
 - One audio thread run by RtAudio that renders real-time audio 
 - One UI thread that handles input parameters, memory allocations, and more to come.
   
It is built in modern C++, following RAII guidelines and object oriented design : audio modules share a base class (AudioModule); modulators share another one (Modulator).

### Usage :
Instantiate a Synth class : 
```
      Synth synth;
```
Then, some audio modules : 
```
    synth.addAudioModule(OSC);
    synth.addAudioModule(VCA);
    synth.addAudioModule(MIXER_4);
```
Connect them together : 
```
    std::vector<std::shared_ptr<AudioModule>> const &modules = synth.getAudioModules();
    modules[0]->audioConnect(modules[0], modules[1]);
    modules[1]->audioConnect(modules[1], modules[2]);
```
Compile using ```make``` and launch ! You should hear a 440hz sinewave.

### Modules
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

## Roadmap

 VCA module
 ADSR Envelope with exponential curves
 VCO — Voltage Controlled Oscillator
 VCF — Voltage Controlled Filter
 Qt graphical interface (PC)
 Port to Daisy Seed (STM32 / FreeRTOS) using a homemade audio embedded library
 
Author
lekix-lekix — github.com/lekix-lekix
