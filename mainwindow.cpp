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
    windowResize();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::windowResize()
{
    int w,h,iw,ih;
    float aspect;

    iw = ui->graphicsView->getImageWidth();
    ih = ui->graphicsView->getImageHeight();

    if(iw>ih){
        aspect = ui->graphicsView->getAspectRatio(true);
        w = width() - 20;
        h = (int)((float)w * aspect);
    }
    else{
        aspect = ui->graphicsView->getAspectRatio(false);
        h = height() - 20;
        w = (int)((float)h * aspect);
    }

    qDebug() << "aspect = " << aspect;

    ui->pushButton->resize(w,ui->pushButton->height());
    ui->titleLabel->resize(w,ui->titleLabel->height());
    ui->graphicsView->resize(w, h);
    //resize(width(),(int)((float)width()*aspect));

    qDebug() << "window_width = " << (w) << " window_height = " << (h);
}

void MainWindow::on_pushButton_clicked()
{
    ui->graphicsView->nextTrack();
    ui->graphicsView->viewport()->update();
    ui->titleLabel->setText(ui->graphicsView->getTitle());
    windowResize();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    event = event;
    qDebug() << __func__ << " called";
    windowResize();
}
