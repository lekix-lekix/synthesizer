# 🎛️ Cutee Synth - A Modular Digital Synthesizer - Work in progress

![Cutee Synth screenshot](./Cutee%20Synth.png?raw=true "Cutee Synth")

### Overview

Cutee is a C++23 modular synthesizer built on top of my [homemade DSP/synthesis library](https://github.com/lekix-lekix/dsp_library), using the Qt Framework for the UI (with QtQuick : QML and Javascript) and the RtAudio library.
The project aims to digitally replicate the behavior of classic analog modular synthesizer modules, with a focus on real-time audio processing and object-oriented
programming.

### Architecture

As every realtime audio project, Cutee runs on a multithreaded architecture : one lock-free realtime audio thread that handles the audio loop (that must go fast and render under ~2.90ms to avoid audio glitches), and one UI thread that handles memory allocations, modulations, UI, etc.

A main Synth class handles the memory allocation, the connections and the renders of every module :

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

All theses classes are used as interface between the DSP modules and the UI. A knob gets turned in the front-end, the Qt wrapper class gets a notification and send it to the C++ backend. In the same way, it gets informations from the backend, and gives it to the QML that will print it.

## Build from source

### Prerequisites

- CMake >= 3.16
- A C++23-capable compiler (GCC, Clang, or MSVC)
- Qt 6 (Core, Gui, Widgets, Quick, Qml modules)
- Ninja (optional, but recommended)
- Linux only (for now)

On Ubuntu:
```bash
sudo apt install build-essential cmake ninja-build \
    qt6-base-dev qt6-declarative-dev \
    qml6-module-qtquick qml6-module-qtquick-controls \
    qml6-module-qtquick-layouts qml6-module-qtquick-window
```

### Build

```bash
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release 
cmake --build build --parallel
```

If Qt isn't found automatically, point CMake to your Qt install:
```bash
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_PREFIX_PATH=/path/to/Qt/6.x.x/gcc_64 (mine is -DCMAKE_PREFIX_PATH:PATH=/opt/Qt/6.11.1/gcc_64)
```

### Run

```bash
./build/src/synth_pcbuild
```

The building process is kind of chaotic at the moment and will probably fail on your machine. I would not recommend building it and am currently working on a web hosted version.

This project is a work in progress.

Author
lekix-lekix — github.com/lekix-lekix

```

```
