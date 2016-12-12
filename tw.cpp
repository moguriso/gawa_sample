#include "tw.h"

Tw::Tw()
{

}

bool Tw::init()
{
    bool r_inf = false;

    // FIXME: it's so tentative implementaion...
    this->oauth.setConsumerKey(consumer_key);
    this->oauth.setConsumerSecret(consumer_secret);
    this->oauth.setToken(token);
    this->oauth.setTokenSecret(token_secret);
    this->oauth.user_id(user_id);
    this->oauth.screen_name(screen_name);
    //this->status.statusesUpdate();

    if(oauth.state() == 0) {
        QString pin = "";
        oauth.request_token(pin);
        oauth.access_token(pin);
    }

    if(oauth.state() == 2) {
        oauth.authorize();
    }

    if(oauth.state() == 5){
        qDebug() << "success token authorize";
        r_inf = true;
    }

    return r_inf;
}

bool Tw::postTweet(QString title)
{
    bool r_inf = false;
    QVariantMap map;
    QString sTweet = "#NowPlaying " + title;
    map.insert("status", sTweet);

    if(oauth.state() == 5)
    {
        status.statusesUpdate(map);
        r_inf = true;
    }
    return r_inf;
}
