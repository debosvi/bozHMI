/*!
 * Copyright (C) 2013 Renault-Trucks Defense.
 *
 * \file        BOZ_WebPage.cpp
 * \brief       BOZ_ Web browser class
 * \version     0.1
 * \date        2014/01/30
 * \author      Vincent de RIBOU <vincent.de-ribou@external.renault-trucks.com>
 * \copyright   Renault-Trucks Defense 2013.
 *
 */

/**
 * @ingroup HMI
 * @ingroup BOZ__WEBPLUGIN
 * @{
 */
 
#include <QDir>
#include <QLibrary>

#include <QNetworkProxyFactory>
#include <QWebView>
#include <QWebFrame>
//#include <QNetworkAccessManager>
#include <QAuthenticator>

#include "BOZ_Webpage.h"

#include "BOZ_WebPlugin.h"

BOZ_Webpage::BOZ_Webpage(QUrl &url) : _view(0) {
    /* use of http_proxy & https_proxy */
    QNetworkProxyFactory::setUseSystemConfiguration(true);

    _view = new QWebView();
    _view->setPage(this);
    _view->page()->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
    _view->page()->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
    _view->page()->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    _view->page()->settings()->enablePersistentStorage("/tmp");

    // allows to catch touch events inside JavaScript instead of native Qt app
    _view->setAttribute(Qt::WA_AcceptTouchEvents, false);
    
    _view->load(url);
    //! allows to change window title on content title change
    connect(_view, SIGNAL(titleChanged(QString)), SLOT(adjustTitle(QString)));  
    connect(_view->page()->networkAccessManager(), SIGNAL(authenticationRequired(QNetworkReply*, QAuthenticator*)), SLOT(provideAuthentication(QNetworkReply*,QAuthenticator*)));
    
    _view->page()->mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);
    _view->page()->mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);

    _view->resize(1024,768);
    _view->show();
}

void BOZ_Webpage::provideAuthentication(QNetworkReply *reply, QAuthenticator *auth) {
    Q_UNUSED(reply);
    qDebug("%s", __PRETTY_FUNCTION__);
    auth->setUser("admin");
    auth->setPassword("Admin");
}

QObject* BOZ_Webpage::createPlugin(const QString & classid, const QUrl & url, const QStringList & paramNames, const QStringList & paramValues) {
    int idx=paramNames.indexOf(QString("id"));
    QString idstr = paramValues[idx];
    QWebView *_view = (QWebView*)view();
    Q_UNUSED(url)

#if 1
    QDir plugindir(WEBPLUGIN_DIR);
    QStringList filters;
    filters << "*.so";
    plugindir.setNameFilters(filters);
    QStringList entries = plugindir.entryList();
   
    qDebug("entry nb: %d", entries.size());
    QStringList::ConstIterator entry;
    for( entry=entries.constBegin(); entry!=entries.constEnd(); ++entry ) {
        QString libname(WEBPLUGIN_DIR);
        libname.append("/");
        libname.append(*entry);
        qDebug("entry: %s", libname.toLatin1().data());
        QLibrary loadlib(libname);
        bool loaded=loadlib.load();
        if(!loaded) {
            qDebug("\tnot loadable, error(%s)", loadlib.errorString().toLatin1().data());
            continue;
        }
        rtdGetClassid getid = (rtdGetClassid)loadlib.resolve("rtd_get_classid");
        if(getid) {
            qDebug("\tmatch rtd webplugin");
            const char* id=(*getid)();
            if(!classid.compare(QString(id))) {
                qDebug("\tmatch classid");
                rtdGetClass getclass = (rtdGetClass)loadlib.resolve("rtd_get_class");
                if(getclass) {
                    qDebug("\tstart create new instance");
                    QRtdWebPlugin* pw=(QRtdWebPlugin*)(*getclass)(url, paramNames, paramValues);
                    _view->page()->mainFrame()->addToJavaScriptWindowObject(idstr, pw);
                    return pw->getWidget();           
                }
                else {
                    qDebug("\tcan't start create new instance");
                }
            }
            else {
                qDebug("\tdon't match classid (%s/%s)", classid.toLatin1().data(), id);
            }
        }
        else {
            qDebug("\tdon't match rtd webplugin");
        }
        loadlib.unload();
    }    qDebug("create class %s", classid.toLatin1().data());


#else

    if(classid == "rtd_vplayer") {
        qDebug("URL to play: %s", url.url().toLatin1().data());
        BOZ_::QRtdQtAVVidPlayer *pw=new BOZ_::QRtdQtAVVidPlayer();
        QString uri=url.url();
        pw->setURI(uri);
        //! allows to access from javascript to HTML id set
        _view->page()->mainFrame()->addToJavaScriptWindowObject(idstr, pw);
        QWidget *wid = pw->getWidget();

        qDebug("player widget(%p)", wid);
        return wid;
    }
#endif

    qWarning("classid not matched %s", classid.toLatin1().data());
    return NULL;
}

void BOZ_Webpage::adjustTitle(QString title ) {
    qDebug("%s: title (%s)", __PRETTY_FUNCTION__, title.toLatin1().data());
    _view->setWindowTitle(_view->title() + " : " + title);
}

/**
 * @}
 * End of group
 */
