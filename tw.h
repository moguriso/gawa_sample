#ifndef TW_H
#define TW_H

#include <QMutex>
#include <QtCore/QDebug>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QInputDialog>
#include <QtTwitterAPI/oauth.h>
#include <QtTwitterAPI/status.h>

class Tw
{
public:
    Tw();
    bool init();
    bool postTweet(QString);


protected:
    const QString consumer_key      = "";
    const QString consumer_secret   = "";
    const QString token             = "";
    const QString token_secret      = "";
    const QString user_id           = "";
    const QString screen_name       = "";

private:
    OAuth oauth;
    Status status;
};

#endif // TW_H
