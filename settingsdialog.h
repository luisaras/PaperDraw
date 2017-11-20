#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include "mainwindow.h"
#define BUTTONS 3

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

    int exec(MainWindow* mw);
    int exec() { return QDialog::exec(); }

private slots:

    void on_setColor_clicked();

    void on_setColor_2_clicked();

    void on_setColor_3_clicked();

private:
    QColor colors[BUTTONS];
    Ui::SettingsDialog *ui;

    QComboBox* toolCombos[BUTTONS];
    QSpinBox* sizes[BUTTONS];
    QLabel* colorPreviews[BUTTONS];
    QPushButton* colorButtons[BUTTONS];
    QCheckBox* penBoxes[BUTTONS];
    QCheckBox* keyBoxes[BUTTONS];
    QCheckBox* mouseBoxes[BUTTONS];
    QComboBox* penCombos[BUTTONS];
    QLineEdit* keyLines[BUTTONS];
    QComboBox* mouseCombos[BUTTONS];

    void setButton(Button &b, int i);
    void updateButton(Button &b, int i);

    void setColor(QColor &init, int i);
    void getColor(int i);
};

#endif // SETTINGSDIALOG_H
