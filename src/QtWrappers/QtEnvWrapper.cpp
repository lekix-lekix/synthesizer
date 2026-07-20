#include "QtEnvWrapper.hpp"

QtEnvWrapper::QtEnvWrapper(Env *env, QObject *parent)
    : env_(env), QtModuleWrapper(parent)
{
    ports_.emplace("cvOut", &env_->cvOut);
    // add gate in / trigger
}
