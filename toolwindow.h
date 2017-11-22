#ifndef TOOLWINDOW_H
#define TOOLWINDOW_H

#include <QDialog>
#include <QKeyEvent>
#include <QColor>
#include "button.h"

namespace Ui {
class ToolWindow;
}

class ToolWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ToolWindow(QWidget *parent, Button &initial);
    ~ToolWindow();

    Button* button;
    void setTool(Button &button);

private slots:
    void on_setColor_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_toolBox_currentIndexChanged(int index);

private:
    Ui::ToolWindow *ui;

    void setColor(QColor& init);
    void getColor();
};

#endif // TOOLWINDOW_H
