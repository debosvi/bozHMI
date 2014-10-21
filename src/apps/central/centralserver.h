#ifndef _CENTRAL_SERVER_H_
#define _CENTRAL_SERVER_H_

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>
#include <QtNetwork/QSslError>

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

class CentralServer : public QObject
{
    Q_OBJECT
public:
    explicit CentralServer(quint16 port, QObject *parent = Q_NULLPTR);
    virtual ~CentralServer();

Q_SIGNALS:

private Q_SLOTS:
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();
    void onSslErrors(const QList<QSslError> &errors);

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
};

#endif // _CENTRAL_SERVER_H_
