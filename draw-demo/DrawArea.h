#pragma once
#include <QQuickPaintedItem>
#include <QPainterPath>
#include <QPainter>
#include <QVector>
#include <QPointF>

class DrawArea : public QQuickPaintedItem {
    Q_OBJECT
public:
    explicit DrawArea(QQuickItem *parent = nullptr);

    void paint(QPainter *painter) override;

    Q_INVOKABLE void addPoint(qreal x, qreal y);
    Q_INVOKABLE void startStroke(qreal x, qreal y);
    Q_INVOKABLE void clear();

private:
    QVector<QVector<QPointF>> m_strokes; // one vector of points per stroke
};