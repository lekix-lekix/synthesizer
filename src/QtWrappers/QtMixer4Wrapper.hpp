#pragma once

#include <QObject>

#include <Mixer_4.hpp>

class QtMixer4Wrapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float gain0 READ getGain0 WRITE setGain0 NOTIFY onGain0Changed)
    Q_PROPERTY(float gain1 READ getGain1 WRITE setGain1 NOTIFY onGain1Changed)
    Q_PROPERTY(float gain2 READ getGain2 WRITE setGain2 NOTIFY onGain2Changed)
    Q_PROPERTY(float gain3 READ getGain3 WRITE setGain3 NOTIFY onGain3Changed)

    private:
        Mixer_4 *mixer_;

    public:
        explicit            QtMixer4Wrapper(Mixer_4 *mixer, QObject *parent = nullptr);

        float               getGain0() { return mixer_->getGain(0); }
        float               getGain1() { return mixer_->getGain(1); }
        float               getGain2() { return mixer_->getGain(2); }
        float               getGain3() { return mixer_->getGain(3); }

        Mixer_4             &setGain0(float newVal) { return mixer_->setGain(0, newVal); }
        Mixer_4             &setGain1(float newVal) { return mixer_->setGain(1, newVal); }
        Mixer_4             &setGain2(float newVal) { return mixer_->setGain(2, newVal); }
        Mixer_4             &setGain3(float newVal) { return mixer_->setGain(3, newVal); }

    signals:
        void                onGain0Changed();
        void                onGain1Changed();
        void                onGain2Changed();
        void                onGain3Changed();
};

