#ifndef CALIBRATION_H
#define CALIBRATION_H

static QImage* mobileCamera = new QImage("mobile.jpg");

struct Calibration {
    QImage* img = 0;
    QPoint area[5];
};

#endif // CALIBRATION_H
