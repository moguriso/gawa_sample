#include "artwork.h"

#include <QtWebEngineWidgets/QWebEngineView>

Artwork::Artwork(QWidget *parent) : QGraphicsView(parent)
{
    mImg = NULL;
    mImgReader = NULL;

    mParent = parent;
    m_manager = new QAxScriptManager(this);
    bool isRegistered = m_manager->registerEngine("VBScript", "vbs");
    if(isRegistered){
        qDebug() << "OK to register VBScript";
        m_script = m_manager->load("://test.vbs", "HelloWorld");
        //m_script = m_manager->load("qrc://test.vbs", "HelloWorld");
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

bool Artwork::loadImage(QString path)
{
    bool r_inf = false;

    QImage* pImg = new QImage();
    QImageReader* pReader = new QImageReader(path);

    bool isSuccess = pReader->read(pImg);
    if(isSuccess){
        if(path.indexOf("png") != -1)
            setAlpha(pImg, 128);

        if(!mImg)
            delete mImg;
        if(!mImgReader)
            delete mImgReader;

        mImg = pImg;
        mImgReader = pReader;
        r_inf = true;
    }
    else
        qDebug() << pReader->errorString();

    return r_inf;
}

void Artwork::updateImage(QPaintEvent *event, QString path)
{
    bool isSuccess = loadImage(path);
    if(isSuccess){
        if(path.indexOf("png") != -1)
            setAlpha(mImg, 128);
        QRect imgRect = QRect(0, 0, mImg->width(), mImg->height());
        //resize(mImg->width(), mImg->height());
        qDebug() << "view_width = " << mImg->width() << " view_height = " << mImg->height();

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

    qDebug() << __FUNCTION__ << " called";

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

    return w;
}

int Artwork::getImageHeight()
{
    int h;

    h= (mImg) ? mImg->height() : 0;
    qDebug() << "height = " << h;

    return h;
}

float Artwork::getAspectRatio(bool is)
{
    float fRet;

    if(is)
    {
        fRet = (float)getImageHeight() / (float)getImageWidth();
    }
    else{
        fRet = (float)getImageWidth() / (float)getImageHeight();
    }

    return fRet;
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

QString Artwork::getTitle()
{
    QString rStr = "";
    if (m_script){
        QVariant var = m_script->call("getTitle()");
        rStr = var.toString();
    }
    else
        qDebug() << "didn't load";

    return rStr;
}

void Artwork::enterScript()
{
    qDebug() << __FUNCTION__ << " called";
    mMutex.lock();
}

void Artwork::finScript()
{
    qDebug() << __FUNCTION__ << " called";
    mMutex.unlock();
}

void Artwork::mouseReleaseEvent(QMouseEvent *event)
{
    QWebEngineView* WebView = new QWebEngineView();
    QUrl url = "https://www.google.co.jp";
    WebView->load(url);
    WebView->show();
}
