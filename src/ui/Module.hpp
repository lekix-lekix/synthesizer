#pragma once

#include <QObject>
#include <QtQuick>

#include "World.hpp"

class Module : public QObject {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Module(QObject *parent = nullptr);

    Q_INVOKABLE void snapToGrid(double x, double y);

signals:
};
