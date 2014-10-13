#ifndef BOZCENTRALCLIENT_H
#define BOZCENTRALCLIENT_H

#include <QWebSocket>

class bozCentralClient : public QWebSocket
{
    Q_OBJECT
public:
    explicit bozCentralClient(QObject *parent = 0);

signals:

public slots:

};

#endif // BOZCENTRALCLIENT_H
