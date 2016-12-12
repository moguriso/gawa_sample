#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QWidget>
#include <QMutex>

#include "artwork.h"
#include "tw.h"

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

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    Artwork* mArtwork;
    Tw* mTw;
    void windowResize();
    void paintEvent(QPaintEvent *);
};

#endif // MAINWINDOW_H
