#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->graphicsView->getArtworkPath();
    ui->graphicsView->viewport()->update();
    windowResize();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::windowResize()
{
     int w,h,p_h;
     p_h = ui->pushButton->height();
     w = ui->graphicsView->getImageWidth();
     h = ui->graphicsView->getImageHeight();
     ui->pushButton->resize(w,p_h);
     this->resize(w+20,h+20);
}

void MainWindow::on_pushButton_clicked()
{
    ui->graphicsView->nextTrack();
    windowResize();
    ui->graphicsView->viewport()->update();
}
