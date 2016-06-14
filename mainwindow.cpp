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
    QString path;

    nextTrack();
    path = getArtworkPath();

    qDebug() << path;
    /* add (ここまで) */
}
