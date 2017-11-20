#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <qcolordialog.h>
#include <iostream>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    toolCombos[0] = ui->toolBox;
    toolCombos[1] = ui->toolBox_2;
    toolCombos[2] = ui->toolBox_3;
    sizes[0] = ui->spinBox;
    sizes[1] = ui->spinBox_2;
    sizes[2] = ui->spinBox_3;
    colorPreviews[0] = ui->colorPreview;
    colorPreviews[1] = ui->colorPreview_2;
    colorPreviews[2] = ui->colorPreview_3;
    colorButtons[0] = ui->setColor;
    colorButtons[1] = ui->setColor_2;
    colorButtons[2] = ui->setColor_3;
    penBoxes[0] = ui->penBox;
    penBoxes[1] = ui->penBox_2;
    penBoxes[2] = ui->penBox_3;
    keyBoxes[0] = ui->keyBox;
    keyBoxes[1] = ui->keyBox_2;
    keyBoxes[2] = ui->keyBox_3;
    mouseBoxes[0] = ui->mouseBox;
    mouseBoxes[1] = ui->mouseBox_2;
    mouseBoxes[2] = ui->mouseBox_3;

    penCombos[0] = ui->penCombo;
    penCombos[1] = ui->penCombo_2;
    penCombos[2] = ui->penCombo_3;
    keyLines[0] = ui->keyLine;
    keyLines[1] = ui->keyLine_2;
    keyLines[2] = ui->keyLine_3;
    mouseCombos[0] = ui->mouseCombo;
    mouseCombos[1] = ui->mouseCombo_2;
    mouseCombos[2] = ui->mouseCombo_3;

    for(int i = 0; i < BUTTONS; i++) {
        colorPreviews[i]->setAutoFillBackground(true);
    }
}

int SettingsDialog::exec(MainWindow* mw) {
    for(int i = 0; i < BUTTONS; i++) {
        setButton(mw->buttons[i + 1], i);
    }
    int result = exec();
    if (result) {
        for(int i = 0; i < BUTTONS; i++) {
            updateButton(mw->buttons[i + 1], i);
        }
    }
    return result;
}

void SettingsDialog::setButton(Button &b, int i) {
    toolCombos[i]->setCurrentIndex(b.tool);
    sizes[i]->setValue(b.size);
    penBoxes[i]->setChecked(b.usePen);
    keyBoxes[i]->setChecked(b.useKey);
    mouseBoxes[i]->setChecked(b.useMouse);
    penCombos[i]->setCurrentIndex(b.pen);
    QString txt(b.key);
    keyLines[i]->setText(txt);
    mouseCombos[i]->setCurrentIndex(b.mouse);
    setColor(b.color, i);
}

void SettingsDialog::updateButton(Button &b, int i) {
    b.tool = toolCombos[i]->currentIndex();
    b.size = sizes[i]->value();
    b.usePen = penBoxes[i]->isChecked();
    b.useKey = keyBoxes[i]->isChecked();
    b.useMouse = mouseBoxes[i]->isChecked();
    b.pen = penCombos[i]->currentIndex();
    b.mouse = mouseCombos[i]->currentIndex();
    b.color = colors[i];
    QKeySequence seq = QKeySequence(keyLines[i]->text());
    if (seq.count() == 1) {
        b.key = seq[0];
        std::cout << b.key << std::endl;
    }
}

void SettingsDialog::setColor(QColor& init, int i) {
    int rgb[3];
    init.getRgb(rgb, rgb + 1, rgb + 2);
    QString color = "(" + QString::number(rgb[0]);
    color += "," + QString::number(rgb[1]);
    color += "," + QString::number(rgb[2]);
    color += ")";

    QString style = "background-color: rgb" + color + ";";
    colorPreviews[i]->setStyleSheet(style);
    colors[i] = init;
}

void SettingsDialog::getColor(int i) {
    QColor color = QColorDialog::getColor(colors[i], this);
    if (color.isValid()) {
        setColor(color, i);
    }
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_setColor_clicked()
{
    getColor(0);
}

void SettingsDialog::on_setColor_2_clicked()
{
    getColor(1);
}

void SettingsDialog::on_setColor_3_clicked()
{
    getColor(2);
}
