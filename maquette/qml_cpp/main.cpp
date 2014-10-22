#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "message.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    Message msg;
    engine.rootContext()->setContextProperty("msg", &msg);
    engine.load(QUrl(QStringLiteral("qrc:/message.qml")));

    return app.exec();
}
