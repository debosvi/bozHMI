#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "centralclient.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QList<QObject *> list = engine.rootObjects();
    qDebug() << "root objects: " << list;
    
    CentralClient client(QUrl(QStringLiteral("wss://localhost:1234")));
    
    QObject::connect(list.at(0), SIGNAL(message(QString)),
                    &client, SLOT(sendMessage(QString)));

    return app.exec();
}
