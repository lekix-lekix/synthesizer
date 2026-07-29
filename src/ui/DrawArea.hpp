#pragma once

#include <QQuickPaintedItem>
#include <QPainterPath>
#include <QPainter>
#include <QVector>
#include <QPointF>

class DrawArea : public QQuickPaintedItem {
    Q_OBJECT
    QML_ELEMENT

private:
    QVariantList cables_;
    std::vector<QPointF> getPointsFromVList(const QVariantList &points);

public:
    explicit DrawArea(QQuickItem *parent = nullptr);

    void paint(QPainter *painter) override;
    void passthrough(std::vector<QPointF> &points, float yOffset, QPainter *painter, QPen *pen);

    Q_INVOKABLE DrawArea &setCables(const QVariantList &cables) { cables_ = cables; return *this; };
};
