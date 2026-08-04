#include "World.hpp"
#include <iostream>

void World::calculateNewPan(QPoint mousePos, QPoint mouseInitPos) {
    QPointF mousePosCoord = pxToCoord(mousePos);
    QPointF mouseInitPosCoord = pxToCoord(mouseInitPos);

    QPointF coordDiff = QPointF(
        (mousePosCoord.x() - mouseInitPosCoord.x()),
        (mousePosCoord.y() - mouseInitPosCoord.y())
    );

    float panX = this->pan.x() + coordDiff.x();
    float panY = this->pan.y() + coordDiff.y();

    this->setPan(QPointF(panX, panY));
    emit panChanged();
}

Q_INVOKABLE QPoint World::coordToPx(QPoint coord) {
    return QPoint((coord.x() + pan.x()) * gridSize * zoom,
                  (coord.y() + pan.y()) * gridSize * zoom);
}

Q_INVOKABLE QPointF World::pxToCoord(QPoint px) {
    return QPointF(px.x() / ((qreal)gridSize * zoom) - pan.x(),
                   px.y() / ((qreal)gridSize * zoom) - pan.y());
}
