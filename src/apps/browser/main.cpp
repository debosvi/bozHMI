#include <QApplication>
#include <QWebFrame>

#include "BOZ_Webpage.h"

int main(int ac, char **av) {
    QApplication a(ac, av);
    QUrl url;
    if (ac > 1)
        url = QUrl::fromUserInput(av[1]);
    else
        url = QUrl("http://localhost:8080/empty.html");
    
    BOZ_Webpage wp(url);
    
    return a.exec();
}
