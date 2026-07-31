#pragma once

#include <QObject>

#include <dsp_library/dsp.hpp>
#include <QtWrappers.hpp>
#include <cmath>

class QtVcoWrapper : public QtModuleWrapper
{
    Q_OBJECT
    Q_PROPERTY(float freq READ getFreq WRITE setFreq NOTIFY freqChanged);
    Q_PROPERTY(float freqCVInAmount READ getFreqCVInAmount WRITE setFreqCVInAmount NOTIFY freqCVInAmountChanged);
    Q_PROPERTY(QString wave READ getWaveQstr NOTIFY waveChanged);

private:
    Vco *vco_;

public:
    explicit            QtVcoWrapper(Vco *vco, QObject *parent = nullptr);

    float               getFreq() { return vco_->getFreq(); };
    float               getFreqCVInAmount() { return vco_->getFreqCVInAmount(); };

    QtVcoWrapper        &setFreq(float newFreq);
    QtVcoWrapper        &setFreqCVInAmount(float newAmount) { vco_->setFreqCVInAmount(newAmount); return *this; };

    e_wave              &getWave() { return vco_->getWavetype(); };
    QString             getWaveQstr();
    Q_INVOKABLE void    toggleWave() { vco_->toggleWave(); emit waveChanged(); };

signals:
    void                freqChanged();
    void                freqCVInAmountChanged();
    void                waveChanged();
};
