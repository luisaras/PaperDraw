#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calibrationdialog.h"
#include "settingsdialog.h"
#include "toolwindow.h"
#include "layerswindow.h"

#include <QPainter>
#include <QRect>
#include <QPen>
#include <QDesktopWidget>

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
    buttons[1].size = 2;
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
    newLayer();
    newLayer();

    toolWindow = new ToolWindow(this);
    toolWindow->show();
    toolWindow->setTool(buttons[0]);

    LayersWindow* lw = new LayersWindow(this);
    lw->show();
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
    toolWindow->setTool(buttons[i]);
    useTool();
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
        std::cout << state << actionStack.size();
    }
    state++;
    QImage* newLayer = new QImage(*file.layers[file.layer]);
    actionStack.push_back(State(file.layer, file.layers[file.layer], newLayer));
    file.layers[file.layer] = newLayer;
}

void MainWindow::undo() {
    if (state > 0) {
        state--;
        State &s = actionStack[state];
        file.layers[s.layer] = s.previous;
        repaint();
        std::cout << "undo" << std::endl;
    }
}

void MainWindow::redo() {
    if (state < actionStack.size()) {
        State &s = actionStack[state];
        file.layers[s.layer] = s.current;
        state++;
        repaint();
        std::cout << "redo" << std::endl;
    }
}

void MainWindow::useTool() {
    QPainter painter(file.layers[file.layer]);
    QPoint pos = mapFromGlobal(QCursor::pos());
    if (cursorX < 0)
        cursorX = pos.x();
    if (cursorY < 0)
        cursorY = pos.y();
    switch (toolWindow->button.tool) {
    case 0:
        usePen(painter, pos);
        break;
    case 1:
        useEraser(painter, pos);
        break;
    case 2:
        useBucket(painter, pos);
    }
    cursorX = pos.x();
    cursorY = pos.y();
    repaint();
}

void MainWindow::usePen(QPainter &painter, QPoint &pos) {
    QBrush brush(toolWindow->button.color);
    painter.setBrush(brush);
    QPen pen(brush, toolWindow->button.size);
    painter.setPen(pen);
    painter.drawLine(cursorX, cursorY, pos.x(), pos.y());
}

void MainWindow::useEraser(QPainter&, QPoint &pos) {
    int size = toolWindow->button.size / 2;
    QColor transparent(255, 255, 255, 0);
    QImage* layer = file.layers[file.layer];
    for(int i = -size; i <= size; i++) {
        for(int j = -size; j <= size; j++) {
            layer->setPixelColor(pos.x() + i, pos.y() + j, transparent);
        }
    }
}

void MainWindow::useBucket(QPainter&, QPoint&) {
}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    if (file.bg) {
        painter.drawImage(0, 0, *file.bg);
    }
    for (uint i = 0; i < file.layers.size(); i++) {
        painter.drawImage(0, 0, *file.layers[i]);
    }
}

void MainWindow::on_actionCalibrate_triggered() {
    CalibrationDialog* dialog = new CalibrationDialog(this);
    dialog->exec();
    delete dialog;
}

void MainWindow::on_actionPreferences_triggered() {
    SettingsDialog* dialog = new SettingsDialog(this);
    dialog->exec(this);
    delete dialog;
}

void MainWindow::on_actionUndo_triggered() { undo(); }
void MainWindow::on_actionUndo_2_triggered() { undo(); }
void MainWindow::on_actionRedo_triggered() { redo(); }
void MainWindow::on_actionRedo_2_triggered() { redo(); }

MainWindow::~MainWindow() { delete ui; }

