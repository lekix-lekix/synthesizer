#include "QtOscWrapper.hpp"

QtOscWrapper::QtOscWrapper(Osc *osc, QObject *parent)
    : osc_(osc), QObject{parent}
{}

QString QtOscWrapper::getWaveQstr() {
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
