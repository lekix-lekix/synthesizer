#include "QtVcoWrapper.hpp"

QtVcoWrapper::QtVcoWrapper(Vco *vco, QObject *parent)
    : QtModuleWrapper(parent), vco_(vco)
{
    ports_.emplace("audioOutput", std::ref(vco_->audioOutput));
    ports_.emplace("freqCVIn", std::ref(vco_->freqCVIn));
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
