#pragma once

#include <QObject>
#include <dsp/dsp.hpp>
#include <QtModuleWrapper.hpp>

class QtEnvWrapper : public QtModuleWrapper
{
    Q_OBJECT
    Q_PROPERTY(float attack  READ getAttack  WRITE setAttack  NOTIFY onAttackChanged);
    Q_PROPERTY(float decay   READ getDecay   WRITE setDecay   NOTIFY onDecayChanged);
    Q_PROPERTY(float sustain READ getSustain WRITE setSustain NOTIFY onSustainChanged);
    Q_PROPERTY(float release READ getRelease WRITE setRelease NOTIFY onReleaseChanged);

private:
    Env *env_;

public:
    explicit            QtEnvWrapper(Env *env, QObject *parent = nullptr);

    const ADSR          &getADSR() { return env_->getADSR(); };

    Q_INVOKABLE const float         getAttack() { return env_->getAttack(); };
    Q_INVOKABLE const float         getDecay() { return env_->getDecay(); };
    Q_INVOKABLE const float         getSustain() { return env_->getSustain(); };
    Q_INVOKABLE const float         getRelease() { return env_->getDecay(); };

    Q_INVOKABLE Env     &setAttack(float time_ms) { return env_->setAttack(time_ms); };
    Q_INVOKABLE Env     &setDecay(float time_ms) { return env_->setDecay(time_ms); };
    Q_INVOKABLE Env     &setSustain(float gain) { return env_->setSustain(gain); };
    Q_INVOKABLE Env     &setRelease(float time_ms) { return env_->setRelease(time_ms); };

signals:
    void                onAttackChanged();
    void                onDecayChanged();
    void                onSustainChanged();
    void                onReleaseChanged();
};
