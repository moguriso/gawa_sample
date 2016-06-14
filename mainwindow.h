#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAxScriptEngine>
#include <QAxScript>
#include <QDebug>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QImageReader>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    QString getArtworkPath();     //add
    void nextTrack();             //add
    QAxScriptManager *m_manager;  //add
    QAxScript *m_script;          //add
};

#endif // MAINWINDOW_H
