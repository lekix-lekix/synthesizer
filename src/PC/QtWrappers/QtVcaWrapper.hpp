#pragma once

#include <QObject>

#include <dsp/dsp.hpp>
#include <QtWrappers.hpp>

class QtVcaWrapper : public QtModuleWrapper
{
    Q_OBJECT
    Q_PROPERTY(float gain READ getGain WRITE setGain NOTIFY gainChanged);

private:
    Vca *vca_;

public:
    explicit    QtVcaWrapper(Vca *vca, QObject *parent = nullptr);

    float       getGain() { return vca_->getGain(); };
    Vca         &setGain(float newVal) { return vca_->setGain(newVal); };

signals:
    void        gainChanged();
};
