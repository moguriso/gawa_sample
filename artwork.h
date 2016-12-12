#ifndef ARTWORK_H
#define ARTWORK_H

#include <QDebug>
#include <QWidget>
#include <QAxScriptEngine>
#include <QAxScript>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QImageReader>
#include <QMutex>
#include <QPushButton>

class Artwork : public QGraphicsView
{
public:
    Artwork(QWidget *parent);
    ~Artwork();
    QString getArtworkPath();
    void nextTrack();


    int getImageWidth();
    int getImageHeight();
    bool loadImage(QString);
    float getAspectRatio(bool);
    QString getTitle();

protected:
    void paintEvent(QPaintEvent *);

private:
    QImage *mImg;
    QImageReader *mImgReader;
    QMutex mMutex;

    void setAlpha(QImage *qImg, int alpha);
    QAxScriptManager *m_manager;
    QAxScript *m_script;
    void enterScript();
    void finScript();
    void updateImage(QPaintEvent *, QString);
    void setNoImage(QPaintEvent *, QString);
    QWidget *mParent;
};

#endif // ARTWORK_H
