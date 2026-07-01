#include "QtEnvWrapper.hpp"

QtEnvWrapper::QtEnvWrapper(Env *env, QObject *parent)
    : QtModuleWrapper(parent), env_(env)
{
    ports_.emplace("cvOut", env_->cvOut);
    // add gate in / trigger
}
