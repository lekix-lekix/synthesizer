#pragma once

#include <QQuickPaintedItem>
#include <QPainterPath>
#include <QPainter>
#include <QVector>
#include <QPointF>

#include "World.hpp"

class DrawArea : public QQuickPaintedItem {
    Q_OBJECT
    QML_ELEMENT

private:
    bool                    gridBool_ = { false };

    QVariantList            cables_;
    bool                    initGrid_ = { false };
    int                     gridSize_ = { 128 };

    std::vector<QPointF>    getPointsFromVList(const QVariantList &points);
    QPoint                  coordToPx(QPoint coord);


public:
    World       *world;

    explicit    DrawArea(QQuickItem *parent = nullptr);

    void        paint(QPainter *painter) override;
    void        passthrough(std::vector<QPointF> &points, float yOffset, QPainter *painter, QPen *pen);

    Q_INVOKABLE DrawArea &setCables(const QVariantList &cables) { cables_ = cables; return *this; };

    Q_INVOKABLE World    &setPan(QVariantMap mousePos, QVariantMap mouseInitPos) {
        World::instance().calculateNewPan(
            QPointF(mousePos.value("x").toFloat(), mousePos.value("y").toFloat()),
            QPointF(mouseInitPos.value("x").toFloat(), mouseInitPos.value("y").toFloat())
        );
        return *this->world;
    }

    void paintGrid(QPainter *painter);

    Q_INVOKABLE const DrawArea &setGridBool(bool gridBool) { gridBool_ = gridBool; return *this; };

    Q_INVOKABLE void    zoomIn() { World::instance().zoom *= 1.1; };
    Q_INVOKABLE void    zoomOut() { World::instance().zoom *= 0.9; };
};
