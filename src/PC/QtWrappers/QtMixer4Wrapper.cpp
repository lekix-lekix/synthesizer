#include "QtMixer4Wrapper.hpp"

QtMixer4Wrapper::QtMixer4Wrapper(Mixer_4 *mixer, QObject *parent)
    : mixer_(mixer), QObject{parent}
{}
