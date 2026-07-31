#include "World.hpp"
#include <iostream>

void World::calculateNewPan(QPointF mousePos, QPointF mouseInitPos) {
    float diffX = mouseInitPos.x() - mousePos.x();
    float diffY = mouseInitPos.y() - mousePos.y();

    QPointF coord = pxToCoord(QPoint(mousePos.x(), mousePos.y()));
    std::cout << "coord : " << coord.x() << " " << coord.y() << std::endl;

    // QPointF mouseDiff = this->coordToPx(QPoint(diffX, diffY));
    std::cout << "Init pos : " << mouseInitPos.x() << " " << mouseInitPos.y() << std::endl;
    std::cout << "New pos : " << mousePos.x() << " " << mousePos.y() << std::endl;
    std::cout << "diff : " << diffX << " " << diffY << std::endl;
    // std::cout << mouseDiff.x() << " " << mouseDiff.y() << std::endl;
    this->pan.setX((this->pan.x() + diffX) * 0.01);
    this->pan.setY((this->pan.y() + diffY) * 0.01);
    // this->pan.setX(this->pan.x() + 0.1);
}