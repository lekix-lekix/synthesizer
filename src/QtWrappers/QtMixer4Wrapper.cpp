#include "QtMixer4Wrapper.hpp"

QtMixer4Wrapper::QtMixer4Wrapper(Mixer_4 *mixer, QObject *parent)
    :  mixer_(mixer), QtModuleWrapper(parent)
{
    ports_.emplace("audioInput0", &mixer_->audioInputs[0]);
    ports_.emplace("audioInput1", &mixer_->audioInputs[1]);
    ports_.emplace("audioInput2", &mixer_->audioInputs[2]);
    ports_.emplace("audioInput3", &mixer_->audioInputs[3]);
    ports_.emplace("audioOutput", &mixer->audioOutput);
}
