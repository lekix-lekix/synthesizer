#pragma once

#include <QObject>

#include <Osc.hpp>

class QtOscWrapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float freq READ getFreq WRITE setFreq NOTIFY freqChanged);
    Q_PROPERTY(QString wave READ getWaveQstr NOTIFY waveChanged);

private:
    Osc *osc_;

public:
    explicit            QtOscWrapper(Osc *osc, QObject *parent = nullptr);

    float               getFreq() { return osc_->getFreq(); };
    Osc                 &setFreq(float newFreq) { return osc_->setFreq(newFreq); };

    e_wave              &getWave() { return osc_->getWave(); };
    QString             getWaveQstr();
    Q_INVOKABLE void    toggleWave() { osc_->toggleWave(); emit waveChanged(); };

signals:
    void                freqChanged();
    void                waveChanged();
};
