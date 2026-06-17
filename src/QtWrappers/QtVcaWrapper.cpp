#include "QtVcaWrapper.hpp"

QtVcaWrapper::QtVcaWrapper(Vca *vca, QObject *parent)
    : vca_(vca), QObject{parent}
{}
