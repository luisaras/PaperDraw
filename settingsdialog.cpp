#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <qcolordialog.h>
#include <iostream>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
}

int SettingsDialog::exec(MainWindow* mw) {
    for(int i = 0; i < BUTTONS; i++) {
        buttons[i] = mw->buttons[i + 1];
    }
    int result = exec();
    if (result) {
        for(int i = 0; i < BUTTONS; i++) {
            mw->buttons[i + 1] = buttons[i];
        }
    }
    return result;
}

void SettingsDialog::getColor(Button& button) {
    QColor color = QColorDialog::getColor(button.color, this);
    if (color.isValid()) {
        button.color = color;
    }
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_toolBox_currentIndexChanged(int index)
{
    buttons[0].tool = index;
}

void SettingsDialog::on_spinBox_valueChanged(int arg1)
{
    buttons[0].size = arg1;
}

void SettingsDialog::on_setColor_clicked()
{
    getColor(buttons[0]);
}

void SettingsDialog::on_penBox_toggled(bool checked)
{
    buttons[0].usePen = checked;
}

void SettingsDialog::on_keyBox_toggled(bool checked)
{
    buttons[0].useKey = checked;
}

void SettingsDialog::on_mouseBox_toggled(bool checked)
{
    buttons[0].useMouse = checked;
    std::cout << checked << std::endl;
}
