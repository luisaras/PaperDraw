#ifndef CALIBRATIONDIALOG_H
#define CALIBRATIONDIALOG_H

#include <QDialog>
#include "calibration.h"

namespace Ui {
class CalibrationDialog;
}

class CalibrationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CalibrationDialog(QWidget *parent, Calibration* c);
    ~CalibrationDialog();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent * event) override;

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_nextButton_clicked();

    void on_previousButton_clicked();

private:
    Ui::CalibrationDialog *ui;
    Calibration* calibration;
    int step = 0;
    int corner = 0;

    double x, y;
};

#endif // CALIBRATIONDIALOG_H
