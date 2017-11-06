#include "clientwindow.h"
#include <QApplication>

int ServerPort = 9090;
QString ServerIP ("127.0.0.1");

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientWindow w(ServerPort, ServerIP);
    w.show();
    return a.exec();
}
