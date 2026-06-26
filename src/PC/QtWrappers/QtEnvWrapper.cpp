#include "QtEnvWrapper.hpp"

QtEnvWrapper::QtEnvWrapper(Env *env, QObject *parent)
    : env_(env), QObject{parent}
{}
