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

class Artwork : public QGraphicsView
{
public:
    Artwork(QWidget *parent);
    ~Artwork();
    QString getArtworkPath();     //add
    void nextTrack();             //add
    void paintEvent(QPaintEvent *);

    int getImageWidth();
    int getImageHeight();
    bool loadImage(QString);
    float getAspectRatio(bool);
    QString getTitle();

private:
    QImage *mImg;
    QImageReader *mImgReader;
    QMutex mMutex;

    void setAlpha(QImage *qImg, int alpha);
    QAxScriptManager *m_manager;  //add
    QAxScript *m_script;          //add
    void enterScript();
    void finScript();
    void updateImage(QPaintEvent *, QString);
    void setNoImage(QPaintEvent *, QString);
    QWidget *mParent;
};

#endif // ARTWORK_H
