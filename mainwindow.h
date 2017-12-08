#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include <QImage>
#include "toolwindow.h"
#include "calibration.h"
#define TBUTTONS 3
#define INITW 300
#define INITH 200

namespace Ui {
    struct File;
    struct State;
    class MainWindow;
}

struct State {
    uint layer;
    QImage* current;
    QImage* previous;
    State() {}
    State(uint l, QImage *p, QImage* c) {
        layer = l; previous = p; current = c;
    }
};

struct File {
    std::vector<QImage*> layers;
    uint width = INITW;
    uint height = INITH;
    uint layer = 0;
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
    void newState();
    void undo();
    void redo();

    void usePen(QPainter &painter, QPoint &pos);
    void useEraser(QPainter &painter, QPoint &pos);
    void useBucket(QPainter &painter, QPoint &pos);

    File file;
    Calibration calibration;
    Button buttons[TBUTTONS];

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void on_actionCalibrate_triggered();

    void on_actionPreferences_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionShow_hide_camera_image_triggered();

    void on_actionZoom_in_triggered();

    void on_actionZoom_out_triggered();

    void on_actionRotate_clockwise_triggered();

    void on_actionRotate_counter_clockwise_triggered();

    void on_actionInvert_horizontally_triggered();

private:
    Ui::MainWindow *ui;
    ToolWindow* toolWindow;
    double cursorX = -1;
    double cursorY = -1;
    std::vector<State> actionStack;
    uint state = 0;
    int usedButton = -1;

    bool showCamera = true;
    int invert = 1;
    int rotation = 0;
    double zoom = 1;
    QTransform xform;
    QTransform ixform;

    int getButton(int key);
    void recalcMatrix();
};

#endif // MAINWINDOW_H
