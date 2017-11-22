#ifndef BUTTON_H
#define BUTTON_H

#include <QColor>

struct Button {
    bool useMouse = false;
    bool useKey = false;
    bool usePen = false;
    int mouse = 0;
    int pen = 0;
    int key = Qt::Key_1;

    int tool = 0;
    int size = 1;
    QColor color;
};

#endif // BUTTON_H
