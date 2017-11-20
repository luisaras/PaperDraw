#ifndef LAYERSWINDOW_H
#define LAYERSWINDOW_H

#include "mainwindow.h"
#include <QWidget>

namespace Ui {
class LayersWindow;
}

class LayersWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LayersWindow(MainWindow *parent = 0);
    ~LayersWindow();

private slots:
    void on_listWidget_clicked(const QModelIndex &index);

private:
    MainWindow* mainWindow;
    Ui::LayersWindow *ui;
};

#endif // LAYERSWINDOW_H
