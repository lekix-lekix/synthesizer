#include "QtEnvWrapper.hpp"

QtEnvWrapper::QtEnvWrapper(Envelope *env, QObject *parent)
    : env_(env), QObject{parent}
{}
