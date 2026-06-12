#pragma once
#include <QObject>
#include <constants.hpp>
#include <Envelope.hpp>
#include <AudioModule.hpp>

class QtEnvWrapper : public QObject
{
    Q_OBJECT

private:
    Envelope *env_;

public:
    explicit QtEnvWrapper(Envelope *env, QObject *parent = nullptr);

signals:
};
