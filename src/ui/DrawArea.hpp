#pragma once

#include <QQuickPaintedItem>
#include <QWindow>
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
    explicit                DrawArea(QQuickItem *parent = nullptr);

    void                    paint(QPainter *painter) override;
    void                    passthrough(std::vector<QPointF> &points, float yOffset, QPainter *painter, QPen *pen);

    void                    paintGrid(QPainter *painter);

    Q_INVOKABLE const DrawArea &setCables(const QVariantList &cables)   { cables_ = cables; return *this; };
    Q_INVOKABLE const DrawArea &setGridBool(bool gridBool)              { gridBool_ = gridBool; return *this; };

    Q_INVOKABLE void    setPan(QPoint mousePos, QPoint mouseInitPos) {
        World::instance().calculateNewPan(mousePos, mouseInitPos);
    }

    // Q_INVOKABLE void zoomIn()  { World::instance().zoom *= 1.1; };
    // Q_INVOKABLE void zoomOut() { World::instance().zoom *= 0.9; };
};
