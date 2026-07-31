#include "QtVcoWrapper.hpp"

constexpr float OCTAVES_SPAN = 4.0f;
constexpr float DEFAULT_FREQ = 440.0f;

QtVcoWrapper::QtVcoWrapper(Vco *vco, QObject *parent)
    : QtModuleWrapper(parent), vco_(vco)
{
    ports_.emplace("audioOutput", &vco_->audioOutput);
    ports_.emplace("freqCVIn", &vco_->freqCVIn);
}

QtVcoWrapper &QtVcoWrapper::setFreq(float newFreq) {
    const float minFreq = DEFAULT_FREQ / std::pow(2, OCTAVES_SPAN);
    const float maxFreq = DEFAULT_FREQ * std::pow(2, OCTAVES_SPAN);
    const float freq = minFreq * std::pow(maxFreq / minFreq, newFreq);
    vco_->setFreq(freq);
    return *this;
}

QString QtVcoWrapper::getWaveQstr() {
    e_wave &waveType = getWave();
    switch (waveType) {
        case SINE:
            return "sine";
            break;
        case SQUARE:
            return "square";
            break;
        case SAW:
            return "saw";
            break;
        case TRIANGLE:
            return "triangle";
            break;
        }
    return "";
}
