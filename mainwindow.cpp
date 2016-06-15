#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

#if 0
    Qt::WindowFlags flags = windowFlags();
    flags |= Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::FramelessWindowHint;
    setWindowFlags(flags);
#endif

    QString path = ui->graphicsView->getArtworkPath();
    ui->graphicsView->loadImage(path);
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
    ui->graphicsView->resize(w, h);
    //resize(width(),(int)((float)width()*aspect));

    qDebug() << "window_width = " << (w) << " window_height = " << (h);
}

void MainWindow::on_pushButton_clicked()
{
    ui->graphicsView->nextTrack();
    ui->graphicsView->viewport()->update();
    windowResize();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    qDebug() << __func__ << " called";
    windowResize();
}
