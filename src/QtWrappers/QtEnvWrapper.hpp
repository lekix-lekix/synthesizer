#pragma once
#include <QObject>
#include <constants.hpp>
#include <Envelope.hpp>
#include <AudioModule.hpp>

class QtEnvWrapper : public QObject
{
    Q_OBJECT

private:
    Envelope *env;

public:
    explicit QtEnvWrapper(QObject *parent = nullptr);

signals:
};
