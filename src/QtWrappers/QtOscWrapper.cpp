#include "QtOscWrapper.hpp"

QtOscWrapper::QtOscWrapper(Osc *osc, QObject *parent)
    : osc_(osc), QObject{parent}
{}
