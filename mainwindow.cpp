#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calibrationdialog.h"
#include "settingsdialog.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
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
    dialog->exec();
    delete dialog;
}
