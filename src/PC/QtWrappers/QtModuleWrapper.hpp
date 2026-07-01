#pragma once

#include <QObject>
#include <unordered_map>
#include <iostream>

class QtModuleWrapper : public QObject
{
    Q_OBJECT

protected:
    std::unordered_map<std::string, std::reference_wrapper<float>> ports_;

public:
    explicit QtModuleWrapper(QObject *parent = nullptr);

    std::unordered_map<std::string, std::reference_wrapper<float>> &getPorts() { return ports_; };

    float &getPort(QString port) {
        std::string portStr = port.toStdString();
        return ports_.find(portStr)->second.get();
    }

    Q_INVOKABLE void connectionRequest(QObject *fromObj, QString fromPort, QObject *toObj, QString toPort) {
        std::cout << "coucou request !" << std::endl;
        QtModuleWrapper *from = qobject_cast<QtModuleWrapper *>(fromObj);
        QtModuleWrapper *to = qobject_cast<QtModuleWrapper *>(toObj);

        emit connectionRequestSignal(from->getPort(fromPort), to->getPort(toPort));
    }

signals:
    void                connectionRequestSignal(float &from, float &to);
};
