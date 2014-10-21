#ifndef _CENTRAL_CLIENT_H_
#define _CENTRAL_CLIENT_H_

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QtNetwork/QSslError>
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QUrl>

QT_FORWARD_DECLARE_CLASS(QWebSocket)

class CentralClient : public QObject
{
    Q_OBJECT
public:
    explicit CentralClient(const QUrl &url, QObject *parent = Q_NULLPTR);

private Q_SLOTS:
    void onConnected();
    void sendMessage(QString msg);
    void onTextMessageReceived(QString message);
    void onSslErrors(const QList<QSslError> &errors);

private:
    QWebSocket m_webSocket;
};

#endif // _CENTRAL_CLIENT_H_
