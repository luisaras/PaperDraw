#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calibrationdialog.h"
#include "settingsdialog.h"
#include "toolwindow.h"
#include "layerswindow.h"
#include "toolhandler.h"

#include <QPainter>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 1-size black pen
    buttons[0].tool = 0;
    buttons[0].size = 1;
    buttons[0].color = QColor(0, 0, 0);
    buttons[0].useKey = true;
    buttons[0].key = Qt::Key_1;
    buttons[0].useMouse = true;
    buttons[0].mouse = 0;

    // 2-size eraser
    buttons[1].tool = 1;
    buttons[1].size = 8;
    buttons[1].useKey = true;
    buttons[1].key = Qt::Key_2;
    buttons[1].useMouse = true;
    buttons[1].mouse = 2;

    // Red bucket
    buttons[2].tool = 2;
    buttons[2].color = QColor(255, 0, 0);
    buttons[2].useKey = true;
    buttons[2].key = Qt::Key_3;

    // Test file
    calibration = Calibration();
    calibration.img = new QImage("mobile.jpg");
    int w = calibration.img->width(), h = calibration.img->height();
    calibration.area[0] = QPoint(0, 0);
    calibration.area[1] = QPoint(w - 1, 0);
    calibration.area[2] = QPoint(w - 1,  h - 1);
    calibration.area[3] = QPoint(0, h - 1);
    calibration.area[4] = QPoint(0, 0);
    file.width = w;
    file.height = h;
    newLayer();
    newLayer();

    toolWindow = new ToolWindow(this, buttons[0]);
    toolWindow->show();

    LayersWindow* lw = new LayersWindow(this);
    lw->show();

    recalcMatrix();
}

void MainWindow::paintEvent(QPaintEvent *) {
    if (!calibration.img)
        return;
    QPainter painter(this);
    painter.setTransform(xform);
    // Background
    if (calibration.img && showCamera) {
        painter.drawImage(0, 0, *calibration.img);
    }
    // Layers
    painter.drawPolyline(calibration.area, 5);
    for (uint i = 0; i < file.layers.size(); i++) {
        painter.drawImage(0, 0, *file.layers[i]);
    }
    // Cursor
    /*
    painter.setTransform(QTransform());
    QPoint pos = mapFromGlobal(QCursor::pos());
    painter.drawLine(pos.x() - 2, pos.y() - 2, pos.x() + 2, pos.y() + 2);
    painter.drawLine(pos.x() + 2, pos.y() - 2, pos.x() - 2, pos.y() + 2);*/
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    QWidget::keyPressEvent(event);
    int i = getButton(event->key());
    if (usedButton != -1) {
        if (usedButton != i)
            return;
    } else {
        if (i != -1)
            usedButton = i;
        else return;
    }
    if (!event->isAutoRepeat())
        newState();

    QPoint pos = mapFromGlobal(QCursor::pos());
    pos = ixform.map(pos);

    if (cursorX < 0)
        cursorX = pos.x();
    if (cursorY < 0)
        cursorY = pos.y();
    QPoint lastPos(cursorX, cursorY);
    toolWindow->setTool(buttons[i]);
    ToolHandler handler(file.layers[file.layer], buttons[i], pos, lastPos);
    handler.useTool();
    cursorX = pos.x();
    cursorY = pos.y();
    repaint();
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if (!event->isAutoRepeat() && usedButton != -1) {
        int i = getButton(event->key());
        if (i == usedButton) {
            cursorX = -1;
            cursorY = -1;
            usedButton = -1;
        }
    }
}

int MainWindow::getButton(int key) {
    for (int i = 0; i < TBUTTONS; i++)
        if (buttons[i].useKey && buttons[i].key == key)
            return i;
    return -1;
}

void MainWindow::newLayer() {
    QImage* layer = new QImage(file.width, file.height, QImage::Format_ARGB32);
    layer->fill(QColor(255, 255, 255, 0));
    file.layers.push_back(layer);
    file.layers[file.layer] = new QImage(*file.layers[file.layer]);
}

void MainWindow::newState() {
    if (state < actionStack.size()) {
        actionStack.resize(state);
    }
    state++;
    QImage* newLayer = new QImage(*file.layers[file.layer]);
    actionStack.push_back(State(file.layer, file.layers[file.layer], newLayer));
    file.layers[file.layer] = newLayer;
}

void MainWindow::on_actionCalibrate_triggered() {
    CalibrationDialog* dialog = new CalibrationDialog(this, &calibration);
    dialog->exec();
    repaint();
    delete dialog;
}

void MainWindow::on_actionPreferences_triggered() {
    SettingsDialog* dialog = new SettingsDialog(this);
    dialog->exec(this);
    delete dialog;
}

void MainWindow::on_actionUndo_triggered() {
    if (state > 0) {
        state--;
        State &s = actionStack[state];
        file.layers[s.layer] = s.previous;
        repaint();
    }
}

void MainWindow::on_actionRedo_triggered() {
    if (state < actionStack.size()) {
        State &s = actionStack[state];
        file.layers[s.layer] = s.current;
        state++;
        repaint();
    }
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::recalcMatrix() {
    QRect r = geometry();
    QTransform t;
    t.translate(r.width() / 2, r.height() / 2);
    t.rotate(rotation);
    t.scale(invert * zoom, zoom);
    t.translate(-calibration.img->width() / 2, -calibration.img->height() / 2);
    xform = t;
    ixform = t.inverted();
    repaint();
}

void MainWindow::on_actionShow_hide_camera_image_triggered() {
    showCamera = !showCamera;
    repaint();
}

void MainWindow::on_actionZoom_in_triggered() {
    if (zoom < 8) {
        zoom *= 2;
        recalcMatrix();
    }
}

void MainWindow::on_actionZoom_out_triggered() {
    if (zoom > 1 / 8) {
        zoom /= 2;
        recalcMatrix();
    }
}

void MainWindow::on_actionRotate_clockwise_triggered() {
    rotation = (rotation + 15) % 360;
    recalcMatrix();
}

void MainWindow::on_actionRotate_counter_clockwise_triggered() {
    rotation = (rotation + 345) % 360;
    recalcMatrix();
}

void MainWindow::on_actionInvert_horizontally_triggered() {
    invert *= -1;
    recalcMatrix();
}
