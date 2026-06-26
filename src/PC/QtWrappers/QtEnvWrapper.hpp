#pragma once

#include <QObject>
#include <dsp/dsp.hpp>

class QtEnvWrapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float attack  READ getAttack  WRITE setAttack  NOTIFY onAttackChanged);
    Q_PROPERTY(float decay   READ getDecay   WRITE setDecay   NOTIFY onDecayChanged);
    Q_PROPERTY(float sustain READ getSustain WRITE setSustain NOTIFY onSustainChanged);
    Q_PROPERTY(float release READ getRelease WRITE setRelease NOTIFY onReleaseChanged);

private:
    Env *env_;

public:
    explicit        QtEnvWrapper(Env *env, QObject *parent = nullptr);

    const ADSR      &getADSR() { return env_->getADSR(); };

    const float     &getAttack() { return env_->getAttack(); };
    const float     &getDecay() { return env_->getDecay(); };
    const float     &getSustain() { return env_->getSustain(); };
    const float     &getRelease() { return env_->getDecay(); };

    Env             &setAttack(float time_ms) { return env_->setAttack(time_ms); };
    Env             &setDecay(float time_ms) { return env_->setDecay(time_ms); };
    Env             &setSustain(float gain) { return env_->setSustain(gain); };
    Env             &setRelease(float time_ms) { return env_->setRelease(time_ms); };

signals:
    void            onAttackChanged();
    void            onDecayChanged();
    void            onSustainChanged();
    void            onReleaseChanged();
};
