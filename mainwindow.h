#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include <QKeyEvent>
#define TBUTTONS 4

namespace Ui {
    struct Button;
    class MainWindow;
}

struct Button {
    bool useMouse = true;
    bool useKey = false;
    bool usePen = false;
    int mouse = 0;
    int pen = 0;
    int key = Qt::Key_1;

    int tool = 0;
    QColor color;
    int size = 1;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Button buttons[TBUTTONS];

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_actionCalibrate_triggered();

    void on_actionPreferences_triggered();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
