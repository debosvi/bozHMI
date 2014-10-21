#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "centralclient.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    CentralClient client(QUrl(QStringLiteral("wss://localhost:1234")));

    Q_UNUSED(client);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
