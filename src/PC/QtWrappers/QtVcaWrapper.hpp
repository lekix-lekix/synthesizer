#pragma once

#include <QObject>

#include <dsp/dsp.hpp>

class QtVcaWrapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float gain READ getGain WRITE setGain NOTIFY gainChanged);

private:
    Vca *vca_;

public:
    explicit QtVcaWrapper(Vca *vca, QObject *parent = nullptr);

    float   getGain() { return vca_->gain; };
    void    setGain(float newVal) { vca_->gain = newVal; };

signals:
    void    gainChanged();
};
