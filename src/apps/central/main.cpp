#include <QtCore/QCoreApplication>

#include "centralserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    CentralServer server(1234);

    Q_UNUSED(server);

    return a.exec();
}
