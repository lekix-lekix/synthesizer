#include "QtVcoWrapper.hpp"

QtVcoWrapper::QtVcoWrapper(Vco *vco, QObject *parent)
    : vco_(vco), QObject{parent}
{}

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
