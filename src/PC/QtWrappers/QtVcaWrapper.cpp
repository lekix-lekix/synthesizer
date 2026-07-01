#include "QtVcaWrapper.hpp"

QtVcaWrapper::QtVcaWrapper(Vca *vca, QObject *parent)
    : QtModuleWrapper(parent), vca_(vca)
{
    ports_.emplace("audioInput", std::ref(vca_->audioInput));
    ports_.emplace("audioOutput", std::ref(vca_->audioOutput));
    ports_.emplace("gainCVIn", std::ref(vca_->gainCVIn));
}
