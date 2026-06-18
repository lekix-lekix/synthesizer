#pragma once
#include <QObject>
#include <constants.hpp>
#include <Envelope.hpp>
#include <AudioModule.hpp>

class QtEnvWrapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float attack  READ getAttack  WRITE setAttack  NOTIFY onAttackChanged);
    Q_PROPERTY(float decay   READ getDecay   WRITE setDecay   NOTIFY onDecayChanged);
    Q_PROPERTY(float sustain READ getSustain WRITE setSustain NOTIFY onSustainChanged);
    Q_PROPERTY(float release READ getRelease WRITE setRelease NOTIFY onReleaseChanged);

private:
    Envelope *env_;

public:
    explicit        QtEnvWrapper(Envelope *env, QObject *parent = nullptr);

    ADSR            &getADSR() { return env_->getADSR(); };

    float           &getAttack() { return env_->getAttack(); };
    float           &getDecay() { return env_->getDecay(); };
    float           &getSustain() { return env_->getSustain(); };
    float           &getRelease() { return env_->getDecay(); };

    Envelope        &setAttack(float time_ms) { return env_->setAttack(time_ms); };
    Envelope        &setDecay(float time_ms) { return env_->setDecay(time_ms); };
    Envelope        &setSustain(float gain) { return env_->setSustain(gain); };
    Envelope        &setRelease(float time_ms) { return env_->setRelease(time_ms); };

signals:
    void            onAttackChanged();
    void            onDecayChanged();
    void            onSustainChanged();
    void            onReleaseChanged();
};
