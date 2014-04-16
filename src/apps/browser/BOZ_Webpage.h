/*!
 * Copyright (C) 2013 Renault-Trucks Defense.
 *
 * \file        BOZ_WebPage.h
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
 
#include <QWebPage>

class QWebView;
class QAuthenticator;

/*!
 * \class BOZ_Webpage 
 * \brief Class allowing to view html content and also bridge native Qt class to javascript
 */
class BOZ_Webpage : public QWebPage {
    Q_OBJECT
    
public:
    /*! 
	 * \brief QRtdAbstractVidPlayer constructor.
     * \param url : URI to load
     */
    BOZ_Webpage(QUrl &url);

protected slots:
    /*!
     *  \brief Set specific title to view window
     *  \param title : title to set
     */
    void adjustTitle(QString title);

    void provideAuthentication(QNetworkReply *reply, QAuthenticator *auth);
    
protected:
    /*!
     *  \brief Allows plugin bridge from Qt to/from Javscript
     *  \param classid : class identifier set by HTML object tag
     *  \param url : ??
     *  \param paramNames : HTML object tag parameters names list
     *  \param paramValues : HTML object tag parameters values list
     */
    QObject* createPlugin(const QString& classid, const QUrl& url, const QStringList& paramNames, const QStringList& paramValues);
    
private:
    /*!
     *  \brief Specific viewer
     */
    QWebView *_view;
};

/**
 * @}
 * End of group
 */
