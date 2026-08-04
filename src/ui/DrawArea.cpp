#include "DrawArea.hpp"
// #include <qjsengine.h>
#include <iostream>

DrawArea::DrawArea(QQuickItem *parent) : QQuickPaintedItem(parent) {
    // GPU-resident FBO instead of CPU QImage -> avoids the upload memcpy
    setRenderTarget(QQuickPaintedItem::FramebufferObject);
    setSmooth(true);
    setAntialiasing(true);
}

void DrawArea::paintGrid(QPainter *painter) {
    QWindowList windows = QGuiApplication::allWindows();
    QWindow *window = windows.first();
    int winWidth = window->width();
    int winHeight = window->height();

    QPen pen;

    pen.setColor(QColor(Qt::black));
    pen.setWidth(2);
    painter->setPen(pen);

    QVector<QPoint> lines;
    for (int x = 0; ; x++) {
        QPoint beginLinePx;
        QPoint endLinePx;
        // std::cout << World::instance() << std::endl;
        beginLinePx = World::instance().coordToPx(QPoint(x, 0));
        endLinePx = World::instance().coordToPx(QPoint(x, winHeight));
        if (beginLinePx.x() > winWidth || endLinePx.x() > winWidth)
            break ;
        lines.push_back(beginLinePx);
        lines.push_back(endLinePx);
    }
    for (int y = 0; ; y++) {
        QPoint beginLinePx;
        QPoint endLinePx;
        beginLinePx = World::instance().coordToPx(QPoint(0, y));
        endLinePx = World::instance().coordToPx(QPoint(winWidth, y));
        if (beginLinePx.y() > winHeight || endLinePx.y() > winHeight)
            break ;
        lines.push_back(beginLinePx);
        lines.push_back(endLinePx);
    }
    painter->drawLines(lines);
}

void DrawArea::paint(QPainter *painter) {
    painter->setRenderHint(QPainter::Antialiasing);

    if (gridBool_ == true) {
        paintGrid(painter);
        update();
        return ;
    }

    QPen pen;
    for (auto &c: cables_) {
        QVariantMap cableMap = c.toMap();
        QVariantList pointsVList = cableMap["points"].toList();
        std::vector<QPointF> points = getPointsFromVList(pointsVList);

        pen.setCapStyle(Qt::RoundCap);
        pen.setJoinStyle(Qt::RoundJoin);

        pen.setColor(QColor(0, 0, 0, 64)); // shadow
        pen.setWidth(14); // 7
        passthrough(points, 5.0f, painter, &pen);

        pen.setColor(QColor(cableMap["color"].toString()));
        pen.setWidth(10); // 8
        passthrough(points, 0, painter, &pen);

        pen.setColor(QColor(255, 255, 255, 87));
        pen.setWidth(2);
        passthrough(points, -3.0f, painter, &pen); // 1.6

        // if (i == points.size() - 1)
        //     i = 0;

        // pen.setColor(Qt::white);
        // QPainterPath path;
        // int x = points[i].x();
        // int y = points[i].y();
        // path.moveTo(x, y);
        // path.arcTo(QRectF(x, y, 10, 10), 0, 360);
        // painter->strokePath(path, pen);
        // i++;
    }
    update();
}

std::vector<QPointF> DrawArea::getPointsFromVList(const QVariantList &points) {
    std::vector<QPointF> res;
    for (auto &p : points) {
        QVariantMap pointMap = p.toMap();
        int x = pointMap["x"].toInt();
        int y = pointMap["y"].toInt();
        res.push_back(QPointF(x, y));
    }
    return res;
}

void DrawArea::passthrough(std::vector<QPointF> &pts, float yOffset, QPainter *painter, QPen *pen) {
    QPainterPath path;

    path.moveTo(pts[0].x(), pts[0].y() + yOffset);
    size_t len = pts.size();
    for (size_t i = 1; i < len - 1; i++) {
        float xc = (pts[i].x() + pts[i + 1].x()) / 2;
        float xy = (pts[i].y() + pts[i + 1].y()) / 2 + yOffset;
        path.quadTo(pts[i].x(), pts[i].y() + yOffset, xc, xy);
    }
    path.lineTo(pts[len - 1].x(), pts[len - 1].y() + yOffset);

    painter->setPen(*pen);
    painter->strokePath(path, *pen);
}




