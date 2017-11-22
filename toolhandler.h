#ifndef TOOLHANDLER_H
#define TOOLHANDLER_H

#include "button.h"
#include <QPainter>
#include <QImage>
#include <QPoint>

class ToolHandler
{
public:
    ToolHandler(QImage* layer, Button& button, QPoint& pos, QPoint& lastPos);

    void useTool();

private:

    QImage* layer;
    Button &button;
    QPoint &pos;
    QPoint &lastPos;

    void usePen(QPainter &painter);
    void useEraser();
    void useBucket();
};

#endif // TOOLHANDLER_H
