#include "DrawArea.h"

DrawArea::DrawArea(QQuickItem *parent) : QQuickPaintedItem(parent) {
    // GPU-resident FBO instead of CPU QImage -> avoids the upload memcpy
    setRenderTarget(QQuickPaintedItem::FramebufferObject);
    setAntialiasing(true);
}

void DrawArea::paint(QPainter *painter) {
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(Qt::black, 2));

    for (const auto &stroke : m_strokes) {
        if (stroke.size() < 2) continue;
        QPainterPath path;
        path.moveTo(stroke[0]);
        for (int i = 1; i < stroke.size(); ++i)
            path.lineTo(stroke[i]); // swap for quadTo/cubicTo if you smooth later
        painter->drawPath(path);
    }
}

void DrawArea::startStroke(qreal x, qreal y) {
    m_strokes.append(QVector<QPointF>{QPointF(x, y)});
    update();
}

void DrawArea::addPoint(qreal x, qreal y) {
    if (m_strokes.isEmpty()) {
        startStroke(x, y);
        return;
    }
    m_strokes.last().append(QPointF(x, y));
    update();
}

void DrawArea::clear() {
    m_strokes.clear();
    update();
}