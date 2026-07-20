#pragma once

#include <QObject>
#include <unordered_map>
#include <iostream>

class QtModuleWrapper : public QObject
{
    Q_OBJECT

protected:
    std::unordered_map<std::string, float *> ports_;

public:
    explicit QtModuleWrapper(QObject *parent = nullptr);

    std::unordered_map<std::string, float *> &getPorts() { return ports_; };

    float *getPort(QString port) {
        std::string portStr = port.toStdString();
        return ports_.find(portStr)->second;
    }

    Q_INVOKABLE void connectionRequest(QObject *fromObj, QString fromPort, QObject *toObj, QString toPort) {
        QtModuleWrapper *from = qobject_cast<QtModuleWrapper *>(fromObj);
        QtModuleWrapper *to = qobject_cast<QtModuleWrapper *>(toObj);

        std::cout << "connected " << fromPort.toStdString() << " to " << toPort.toStdString();

        emit connectionRequestSignal(from->getPort(fromPort), to->getPort(toPort));
    }

    Q_INVOKABLE void disconnectionRequest(QObject *fromObj, QString fromPort, QObject *toObj, QString toPort) {
        QtModuleWrapper *from = qobject_cast<QtModuleWrapper *>(fromObj);
        QtModuleWrapper *to = qobject_cast<QtModuleWrapper *>(toObj);

        std::cout << "disconnected " << fromPort.toStdString() << " from " << toPort.toStdString();

        emit disconnectionRequestSignal(from->getPort(fromPort), to->getPort(toPort));
    }

signals:
    void                connectionRequestSignal(float *from, float *to);
    void                disconnectionRequestSignal(float *from, float *to);
};
