#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
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

    void on_toolBox_currentIndexChanged(int index);

    void on_spinBox_valueChanged(int arg1);

    void on_setColor_clicked();

    void on_penBox_toggled(bool checked);

    void on_keyBox_toggled(bool checked);

    void on_mouseBox_toggled(bool checked);

private:
    Button buttons[BUTTONS];
    Ui::SettingsDialog *ui;
    void getColor(Button& button);
};

#endif // SETTINGSDIALOG_H
