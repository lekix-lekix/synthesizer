#pragma once

#include <QObject>
#include <unordered_map>

#include <dsp/dsp.hpp>

class QtVcoWrapper : public QObject
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

    std::unordered_map<std::string, float *> ports = {
        {"audioOutput", &vco_->audioOutput},
        {"freqCVIn", &vco_->freqCVIn}
    };

    // float               &getPort(std::string port) { return ports[port].second; };
    void                connectionRequest(float &from, float &to) { emit connectionRequestSignal(from, to); };

signals:
    void                freqChanged();
    void                waveChanged();
    void                connectionRequestSignal(float &from, float &to);
};
