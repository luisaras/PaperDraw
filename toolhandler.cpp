#include "toolhandler.h"
#include <QRect>
#include <QPen>
#include <QDesktopWidget>
#include <queue>
#include <iostream>

ToolHandler::ToolHandler(QImage *_layer, Button &_button, QPoint &_pos, QPoint &_lastPos) :
    layer(_layer), button(_button), pos(_pos), lastPos(_lastPos) {}

void ToolHandler::useTool() {
    QPainter painter(layer);
    switch (button.tool) {
    case 0:
        usePen(painter);
        break;
    case 1:
        useEraser();
        break;
    case 2:
        useBucket();
    }
}

void ToolHandler::usePen(QPainter &painter) {
    QBrush brush(button.color);
    painter.setBrush(brush);
    QPen pen(brush, button.size);
    painter.setPen(pen);
    painter.drawLine(lastPos.x(), lastPos.y(), pos.x(), pos.y());
}

void ToolHandler::useEraser() {
    int size = button.size / 2;
    QColor transparent(255, 255, 255, 0);
    for(int i = -size; i <= size; i++) {
        for(int j = -size; j <= size; j++) {
            layer->setPixelColor(pos.x() + i, pos.y() + j, transparent);
        }
    }
}

void ToolHandler::useBucket() {
    if (pos.x() < 0 || pos.x() >= layer->width())
        return;
    if (pos.y() < 0 || pos.y() >= layer->height())
        return;
    std::queue<QPoint> points;
    QColor initColor = layer->pixelColor(pos);
    if (initColor == button.color)
        return;
    points.push(pos);
    while(!points.empty()) {
        QPoint &p = points.back();
        points.pop();
        layer->setPixelColor(p, button.color);
        if (p.x() < layer->width() - 1) {
            QPoint p2(p.x() + 1, p.y());
            QColor c = layer->pixelColor(p2);
            if (c == initColor && c != button.color) {
                points.push(p2);
            }
        }
        if (p.x() > 0) {
            QPoint p2(p.x() - 1, p.y());
            QColor c = layer->pixelColor(p2);
            if (c == initColor && c != button.color)
                points.push(p2);
        }
        if (p.y() < layer->height() - 1) {
            QPoint p2(p.x(), p.y() + 1);
            QColor c = layer->pixelColor(p2);
            if (c == initColor && c != button.color)
                points.push(p2);
        }
        if (p.y() > 0) {
            QPoint p2(p.x(), p.y() - 1);
            QColor c = layer->pixelColor(p2);
            if (c == initColor && c != button.color)
                points.push(p2);
        }
    }
}
