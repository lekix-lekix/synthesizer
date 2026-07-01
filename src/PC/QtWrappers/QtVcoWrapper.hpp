#pragma once

#include <QObject>

#include <dsp/dsp.hpp>
#include <QtWrappers.hpp>

class QtVcoWrapper : public QtModuleWrapper
{
    Q_OBJECT
    Q_PROPERTY(float freq READ getFreq WRITE setFreq NOTIFY freqChanged);
    Q_PROPERTY(QString wave READ getWaveQstr NOTIFY waveChanged);

private:
    Vco *vco_;

public:
    explicit            QtVcoWrapper(Vco *vco, QObject *parent = nullptr);

    float               getFreq() { return vco_->freq; };
    void                setFreq(float newFreq) { vco_->freq = newFreq; };

    e_wave              &getWave() { return vco_->getWavetype(); };
    QString             getWaveQstr();
    Q_INVOKABLE void    toggleWave() { vco_->toggleWave(); emit waveChanged(); };

signals:
    void                freqChanged();
    void                waveChanged();
};
