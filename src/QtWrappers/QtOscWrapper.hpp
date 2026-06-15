#pragma once

#include <QObject>

#include <Osc.hpp>

class QtOscWrapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float freq READ getFreq WRITE setFreq NOTIFY freqChanged);
    Q_PROPERTY(e_wave wave READ getWave);

private:
    Osc *osc_;

public:
    explicit            QtOscWrapper(Osc *osc, QObject *parent = nullptr);

    float               getFreq() { return osc_->getFreq(); };
    Osc                 &setFreq(float newFreq) { return osc_->setFreq(newFreq); };
    Q_INVOKABLE Osc     &toggleWave() { return osc_->toggleWave(); };
    e_wave              &getWave() { return osc_->getWave(); };

signals:
    void    freqChanged();
};
