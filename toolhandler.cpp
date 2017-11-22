#include "toolhandler.h"
#include <QRect>
#include <QPen>
#include <QDesktopWidget>

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

void ToolHandler::useBucket() {}
