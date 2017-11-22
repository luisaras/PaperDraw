#include "toolwindow.h"
#include "ui_toolwindow.h"
#include <qcolordialog.h>
#include <iostream>

ToolWindow::ToolWindow(QWidget *parent, Button& initial) :
    QWidget(parent, Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint),
    ui(new Ui::ToolWindow)
{
    ui->setupUi(this);
    setWindowTitle("Tool");
    setWindowModality(Qt::NonModal);
    setTool(initial);
}

void ToolWindow::setTool(Button &b) {
    button = &b;
    ui->toolBox->setCurrentIndex(b.tool);
    ui->spinBox->setValue(b.size);
    setColor(b.color);
}

void ToolWindow::setColor(QColor& init) {
    int rgb[3];
    init.getRgb(rgb, rgb + 1, rgb + 2);
    QString color = "(" + QString::number(rgb[0]);
    color += "," + QString::number(rgb[1]);
    color += "," + QString::number(rgb[2]);
    color += ")";

    QString style = "background-color: rgb" + color + ";";
    ui->colorPreview->setStyleSheet(style);
}

void ToolWindow::getColor() {
    QColor color = QColorDialog::getColor(button->color, this);
    if (color.isValid()) {
        setColor(color);
        button->color = color;
    }
}

void ToolWindow::on_setColor_clicked() {
    getColor();
}

void ToolWindow::on_spinBox_valueChanged(int arg1) {
    button->size = arg1;
}

void ToolWindow::on_toolBox_currentIndexChanged(int index) {
    button->tool = index;
}

ToolWindow::~ToolWindow() { delete ui; }
