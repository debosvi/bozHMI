
#include <QtCore/QDebug>
#include <QtWebSockets/QWebSocket>
#include <QCoreApplication>

#include "centralclient.h"

QT_USE_NAMESPACE

CentralClient::CentralClient(const QUrl &url, QObject *parent) :
    QObject(parent),
    m_webSocket()
{
    connect(&m_webSocket, &QWebSocket::connected, this, &CentralClient::onConnected);
    typedef void (QWebSocket:: *sslErrorsSignal)(const QList<QSslError> &);
    connect(&m_webSocket, static_cast<sslErrorsSignal>(&QWebSocket::sslErrors),
            this, &CentralClient::onSslErrors);
    m_webSocket.open(QUrl(url));
}

void CentralClient::onConnected()
{
    qDebug() << "WebSocket connected";
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &CentralClient::onTextMessageReceived);
    m_webSocket.sendTextMessage(QStringLiteral("Hello, world!"));
}

void CentralClient::onTextMessageReceived(QString message)
{
    qDebug() << "Message received:" << message;
    qApp->quit();
}

void CentralClient::onSslErrors(const QList<QSslError> &errors)
{
    Q_UNUSED(errors);

    // WARNING: Never ignore SSL errors in production code.
    // The proper way to handle self-signed certificates is to add a custom root
    // to the CA store.

    m_webSocket.ignoreSslErrors();
}
