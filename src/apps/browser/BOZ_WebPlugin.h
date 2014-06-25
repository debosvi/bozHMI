/*!
 * Copyright (C) 2013 Renault-Trucks Defense.
 *
 * \file        RTDWebPlugin.h
 * \brief       Web plugin astract class
 * \version     0.1
 * \date        2014/01/30
 * \author      Vincent de RIBOU <vincent.de-ribou@external.renault-trucks.com>
 * \copyright   Renault-Trucks Defense 2013.
 *
 */
    
/*!
 * @ingroup HMI
 * @ingroup RTD_WEBPLUGIN
 * @{
 */
 
#ifndef _RTD_WEBPLUGIN_H_
#define _RTD_WEBPLUGIN_H_

#include <QStringList>
#include <QUrl>
#include <QObject>

class QWidget;

/*!
 * \class QRtdWebPlugin
 * \brief QRtdWebPlugin is a QtWebkit web plugin which allows to include html '<object>' tag.
 * 
 * This class is an abstract class where \ref getWidget method is not defined.
 * Then to have a real webplugin, this class must be sub-classed to define at least \ref getWidget method.
 */
class QRtdWebPlugin : public QObject {
    Q_OBJECT

public:
    //! QRtdWebPlugin constructor.
    /*!
      \sa QRtdWebPlugin()
      \param parent Parent object.
    */
	QRtdWebPlugin(QObject *parent=0);
	
    //! This method is virtual then class is abstract. 
    /*!
      \sa getWidget()
      \return QWidget object.
    */
	virtual QWidget* getWidget() = 0;
};

typedef const char* (*rtdGetClassid)(void);
typedef QObject* (*rtdGetClass)(const QUrl & url, const QStringList & paramNames, const QStringList & paramValues);

/**
 * \fn const char* rtd_get_classid(void)
 * \brief plugin ID recognition
 * \return String plugin nmame.
 *
 * This string allows webplugin engine to match class with html '<object id="name">' id param.
 */
extern "C" const char* rtd_get_classid(void);

/**
 * \fn QRtdWebPlugin* rtd_get_class(const QUrl & url, const QStringList & paramNames, const QStringList & paramValues)
 * \brief plugin object instantiation.
 * \param url URL identifier.
 * \param String plugin nmame.
 * \param paramNames list of parameters names.
 * \param paramValues list of corresponding parameters values.
 * \return String plugin nmame.
 *
 * This is the object returned to web browser.
 */
extern "C" QRtdWebPlugin* rtd_get_class(const QUrl & url, const QStringList & paramNames, const QStringList & paramValues);

#endif

/**
 * @}
 * End of group
 */