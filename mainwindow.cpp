#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calibrationdialog.h"
#include "settingsdialog.h"
#include "toolwindow.h"
#include "layerswindow.h"

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

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    QWidget::keyPressEvent(event);
    std::cout << "lalal" << std::endl;
    for (int i = 0; i < TBUTTONS; i++) {
        if (buttons[i].useKey && buttons[i].key == event->key()) {
            toolWindow->setTool(buttons[i]);
            useTool();
        }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if (!event->isAutoRepeat()) {
        cursorX = -1;
        cursorY = -1;
    }
}

void MainWindow::newLayer() {
    QPixmap* layer = new QPixmap(file.width, file.height);
    layer->fill(QColor(255, 255, 255, 0));
    file.layers.push_back(layer);
    painters.push_back(new QPainter(layer));
}

void MainWindow::useTool() {
    QPainter* painter = painters[file.layer];

    QBrush brush(toolWindow->button.color);
    painter->setBrush(brush);
    QPen pen(brush, toolWindow->button.size);
    painter->setPen(pen);

    QPoint pos = mapFromGlobal(QCursor::pos());
    if (cursorX < 0)
        cursorX = pos.x();
    if (cursorY < 0)
        cursorY = pos.y();
    painter->drawLine(cursorX, cursorY, pos.x(), pos.y());
    cursorX = pos.x();
    cursorY = pos.y();
    this->repaint();
}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    if (file.bg) {
        painter.drawPixmap(0, 0, *file.bg);
    }
    for (uint i = 0; i < file.layers.size(); i++) {
        painter.drawPixmap(0, 0, *file.layers[i]);
    }
}

void MainWindow::on_actionCalibrate_triggered()
{
    CalibrationDialog* dialog = new CalibrationDialog(this);
    dialog->exec();
    delete dialog;
}

void MainWindow::on_actionPreferences_triggered()
{
    SettingsDialog* dialog = new SettingsDialog(this);
    dialog->exec(this);
    delete dialog;
}
