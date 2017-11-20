#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include <QPainter>
#include <QPixmap>
#include "toolwindow.h"
#define TBUTTONS 3
#define INITW 300
#define INITH 200

namespace Ui {
    struct File;
    class MainWindow;
}

struct File {
    QPixmap* bg;
    std::vector<QPixmap*> layers;
    uint width = INITW;
    uint height = INITH;
    int layer = 0;
    QString path = "";
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void useTool();
    void newLayer();

    File file;
    Button buttons[TBUTTONS];

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void on_actionCalibrate_triggered();

    void on_actionPreferences_triggered();

private:
    Ui::MainWindow *ui;
    ToolWindow* toolWindow;
    double cursorX = -1;
    double cursorY = -1;
    std::vector<QPainter*> painters;

};

#endif // MAINWINDOW_H
