#include "QtVcaWrapper.hpp"

QtVcaWrapper::QtVcaWrapper(Vca *vca, QObject *parent)
    : QtModuleWrapper(parent), vca_(vca)
{
    ports_.emplace("audioInput", &vca_->audioInput);
    ports_.emplace("audioOutput", &vca_->audioOutput);
    ports_.emplace("gainCVIn", &vca_->gainCVIn);
}
