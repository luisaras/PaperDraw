#include "layerswindow.h"
#include "ui_layerswindow.h"

LayersWindow::LayersWindow(MainWindow *parent) :
    QWidget(parent, Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint),
    ui(new Ui::LayersWindow)
{
    ui->setupUi(this);
    setWindowTitle("Layers");
    setWindowModality(Qt::NonModal);
    mainWindow = parent;
}

LayersWindow::~LayersWindow()
{
    delete ui;
}

void LayersWindow::on_listWidget_clicked(const QModelIndex &index)
{
    mainWindow->file.layer = index.row();
}
