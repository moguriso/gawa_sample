#include "artwork.h"

Artwork::Artwork(QWidget *parent) : QGraphicsView(parent)
{
    mImg = NULL;
    mImgReader = NULL;
    m_manager = new QAxScriptManager(this);
    bool isRegistered = m_manager->registerEngine("VBScript", "vbs");
    if(isRegistered){
        qDebug() << "OK to register VBScript";
        m_script = m_manager->load("://test.vbs", "HelloWorld");
    }
    else
        qDebug() << "NG to register VBScript";

    connect(m_script, static_cast<void(QAxScript::*)()>(&QAxScript::entered),
        [=](){ enterScript(); });
    connect(m_script, static_cast<void(QAxScript::*)()>(&QAxScript::finished),
        [=](){ finScript(); });
}

Artwork::~Artwork()
{
#if 0
    QObject::disconnect(m_script, SIGNAL( finished() ),
            this, SLOT(finScript);
#endif

    if(m_script)
        delete m_script;
    if(m_manager)
        delete m_manager;
}

void Artwork::setAlpha(QImage *qImg, int alpha)
{
  for (int x = 0, width = qImg->width(); x < width; ++x)
    for (int y = 0, height = qImg->height(); y < height; ++y) {
      QColor color(qImg->pixel(x, y));
      color.setAlpha(alpha);
      qImg->setPixel(x, y, color.rgba());
    }
}

void Artwork::updateImage(QPaintEvent *event, QString path)
{
    mImg = new QImage();
    mImgReader = new QImageReader(path);

    bool isSuccess = mImgReader->read(mImg);
    QRect imgRect = QRect(0, 0, mImg->width(), mImg->height());
    if(isSuccess){
        if(path.indexOf("png") != -1)
            setAlpha(mImg, 128);

        resize(mImg->width(), mImg->height());

        QPainter widgetpainter( viewport() );
        QRect paintRect = QRect(0, 0, width(), height());
        widgetpainter.drawImage(paintRect, *mImg, imgRect);
        QGraphicsView::paintEvent(event);
    }
    else
        qDebug() << mImgReader->errorString();
}

void Artwork::setNoImage(QPaintEvent *event, QString str)
{
    QPainter widgetpainter( viewport() );
    QRect paintRect = QRect(0, 0, width() -20, widgetpainter.font().pointSize());
    widgetpainter.drawText(paintRect, str, QTextOption(Qt::AlignTop | Qt::AlignRight));
    QGraphicsView::paintEvent(event);
}

void Artwork::paintEvent(QPaintEvent *event)
{
    QString path;

    path = getArtworkPath();
    path = path.replace("\\\\", "\\");

    if(path != "")
        updateImage(event, path);
    else
        setNoImage(event, "No Image.");
}

QString Artwork::getArtworkPath()
{
    QString rStr = "";

    if (m_script){
        QVariant var = m_script->call("getArtworkAndPath()");
        //qDebug() << var.toString() << "loaded";
        rStr = var.toString();
        //qDebug() << "rstr = " << rStr;
    }
    else
        qDebug() << "didn't load";

    return rStr;
}

int Artwork::getImageWidth()
{
    int w;

    w = (mImg) ? mImg->width() : 0;
    qDebug() << "width = " << w;

    if((w<300) || (1000<w))
        w=300;

    qDebug() << "width = " << w;

    return w;
}

int Artwork::getImageHeight()
{
    int h;

    h= (mImg) ? mImg->height() : 0;
    qDebug() << "height = " << h;

    if((h<300) || (1000<h))
        h=300;

    qDebug() << "height = " << h;
    return h;
}

void Artwork::nextTrack()
{
    if (m_script){
        m_script->call("nextTrack()");
        //qDebug() << "loaded";
    }
    else
        qDebug() << "didn't load";
}

void Artwork::enterScript()
{
    qDebug() << __func__ << " called";
    mMutex.lock();
}

void Artwork::finScript()
{
    qDebug() << __func__ << " called";
    mMutex.unlock();
}
