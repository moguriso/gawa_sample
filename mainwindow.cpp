#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    /* add (ここから) */
    m_manager = new QAxScriptManager(this);
    bool isRegistered = m_manager->registerEngine("VBScript", "vbs");
    if(isRegistered){
        qDebug() << "OK to register VBScript";
        m_script = m_manager->load("C:\\msys64\\home\\adachi\\test.vbs", "HelloWorld");
    }
    else
        qDebug() << "NG to register VBScript";
    /* add (ここまで) */

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    /* add (ここから) */
    if(m_script)
        delete m_script;
    if(m_manager)
        delete m_manager;
    /* add (ここまで) */

    delete ui;
}

/* add (ここから) */
QString MainWindow::getArtworkPath()
{
    QString rStr = "";

    if (m_script){
        QVariant var = m_script->call("getArtworkAndPath()");
        qDebug() << var.toString() << "loaded";
        rStr = var.toString();
        qDebug() << "rstr = " << rStr;
    }
    else
        qDebug() << "didn't load";

    return rStr;
}

void MainWindow::nextTrack()
{
    if (m_script){
        m_script->call("nextTrack()");
        qDebug() << "loaded";
    }
    else
        qDebug() << "didn't load";
}
/* add (ここまで) */

void MainWindow::on_pushButton_clicked()
{
    /* add (ここから) */
    QString path = getArtworkPath();

    QImage img(600, 595, QImage::Format_Invalid);
    QImageReader qir(path);
    bool isSuccess = qir.read(&img);
    QRect imgRect = QRect(0, 0, img.width(), img.height());
    if(isSuccess){
        QPainter widgetpainter( ui->graphicsView->viewport() );
        QRect paintRect = QRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());
        widgetpainter.drawImage(paintRect, img, imgRect);
        //widgetpainter.drawImage(0,0,img);
        //ui->graphicsView->viewport()->update();
    }
    else
        qDebug() << qir.errorString();
    /* add (ここまで) */
}
