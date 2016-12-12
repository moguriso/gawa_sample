#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString path = ui->graphicsView->getArtworkPath();
    ui->graphicsView->loadImage(path);
    ui->titleLabel->setText(ui->graphicsView->getTitle());

    mTw = new Tw();
}

MainWindow::~MainWindow()
{
    delete mTw;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->graphicsView->nextTrack();
    ui->graphicsView->viewport()->update();
    ui->titleLabel->setText(ui->graphicsView->getTitle());
}

void MainWindow::on_pushButton_2_clicked()
{
    mTw->init();
    mTw->postTweet(ui->graphicsView->getTitle());
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    event = event;
    qDebug() << __FUNCTION__ << " called";
    ui->graphicsView->viewport()->update();
}

