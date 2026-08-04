#include "Module.hpp"
#include <iostream>

Module::Module(QObject *parent)
    : QObject{parent}
{}

Q_INVOKABLE void Module::snapToGrid(double x, double y) {
    std::cout << x << y << std::endl;
}