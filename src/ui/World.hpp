#pragma once

#include <QPoint>
#include <QWindow>
#include <cmath>

class World {
    public:
        static World &instance() {
            static World sInstance;
            return sInstance;
        }

        World() = default;
        ~World() = default;
        World(const World &other) = delete;
        World(World &&other) = delete;
        const World &operator=(const World &other) = delete;
        World &operator=(World &&other) = delete;

        int     gridSize            = { 128 }; // px per grid unit
        int     worldWidthUnits     = { 300 };
        int     worldHeightUnits    = { 200 };
        float   zoom                = { 1 };
        QPointF pan                 = { 0, 0 };
        QPointF center              = { QPointF(worldWidthUnits / 2, worldHeightUnits / 2) };

        QPoint coordToPx(QPoint coord) {
            return QPoint((coord.x() - pan.x()) * gridSize * zoom,
                          (coord.y() - pan.y()) * gridSize * zoom);
        }

        QPointF pxToCoord(QPoint px) {
            return QPointF(px.x() / ((qreal)gridSize * zoom) + pan.x(),
                           px.y() / ((qreal)gridSize * zoom) + pan.y());
        }

        void calculateNewPan(QPointF mousePos, QPointF mouseInitPos);
};
