#include "calibrationdialog.h"
#include "ui_calibrationdialog.h"
#include <QPainter>
#include <QKeyEvent>

CalibrationDialog::CalibrationDialog(QWidget *parent, Calibration *c) :
    QDialog(parent),
    ui(new Ui::CalibrationDialog)
{
    calibration = c;
    ui->setupUi(this);
    ui->previousButton->setVisible(false);
    this->setWindowModality(Qt::ApplicationModal);
    setWindowTitle("Calibrate");
}

CalibrationDialog::~CalibrationDialog() {
    delete ui;
}

void CalibrationDialog::on_comboBox_currentIndexChanged(int index) {
    if (calibration->img)
        delete calibration->img;
    if (index == 0)
        calibration->img = new QImage("mobile.jpg");
    else
        calibration->img = new QImage("desktop.jpg");
    int w = calibration->img->width(), h = calibration->img->height();
    calibration->area[0] = QPoint(0, 0);
    calibration->area[1] = QPoint(w - 1, 0);
    calibration->area[2] = QPoint(w - 1,  h - 1);
    calibration->area[3] = QPoint(0, h - 1);
    calibration->area[4] = QPoint(0, 0);
    repaint();
}

void CalibrationDialog::on_nextButton_clicked() {
    if (step == 0) {
        ui->label->setText("Select paper corners.");
        step = 1;

        ui->comboBox->setVisible(false);
        ui->previousButton->setVisible(true);
    } else if (step == 1) {
        ui->label->setText("Put the pen tip over the blue X and press Enter.");
        step = 2;

        ui->nextButton->setEnabled(false);
        x = rand() % calibration->img->width();
        y = rand() % calibration->img->height();
    } else {
        this->setResult(1);
        this->close();
        return;
    }
    repaint();
}

void CalibrationDialog::on_previousButton_clicked() {
    x = -1;
    y = -1;
    if (step == 1) {
        ui->label->setText("Select one of the detected cameras.");
        step = 0;

        ui->comboBox->setVisible(true);
        ui->previousButton->setVisible(false);
    } else if (step < 5) {
        ui->label->setText("Select paper corners.");
        step = 1;

        ui->nextButton->setEnabled(true);
    } else {
        ui->label->setText("Put the pen tip over the blue X and press Enter.");

        ui->nextButton->setText("Next");
        ui->nextButton->setEnabled(false);
        step = 2;
    }
    repaint();
}

void CalibrationDialog::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.translate(geometry().width() / 2 - calibration->img->width() / 2, 50);
    painter.drawImage(0, 0, *calibration->img);
    if (step == 1) {
        QBrush brush = QBrush(QColor(255, 0, 0));
        painter.setPen(QPen(brush, 4));
        painter.drawPolyline(calibration->area, 5);
    } else if (step > 1 && step < 5) {
        QBrush brush = QBrush(QColor(0, 0, 255));
        painter.setPen(QPen(brush, 4));
        painter.drawLine(x - 2, y - 2, x + 2, y + 2);
        painter.drawLine(x + 2, y - 2, x - 2, y + 2);
    }
}

void CalibrationDialog::keyPressEvent(QKeyEvent*) {
    if (step > 1 && step < 5) {
        step ++;
        if (step == 5) {
            ui->nextButton->setEnabled(true);
            ui->nextButton->setText("Finish");
            ui->label->setText("Done.");
        } else {
            x = rand() & calibration->img->width();
            y = rand() & calibration->img->height();
        }
        repaint();
    }
}

void CalibrationDialog::mousePressEvent(QMouseEvent* event) {
    if (step == 1) {
        calibration->area[corner] = event->pos() - QPoint(geometry().width() / 2 - calibration->img->width() / 2, 50);

        corner++;
        if (corner == 4) {
            corner = 0;
        }
        calibration->area[4] = calibration->area[0];
        repaint();
    }
}
