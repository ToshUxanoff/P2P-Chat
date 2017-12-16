#include "clientwindow.h"
#include "mycrypto.hpp"
#include <QApplication>

QString ReadServerParams()
{
    QFile configFile("ServConfig.txt");
    QString Addr;
    if(configFile.open(QIODevice::ReadOnly))
    {
        Addr = configFile.readAll();
        configFile.close();
    }
    return Addr;
}

using namespace CryptoPP;

int main(int argc, char* argv[])
{
    QString Address = ReadServerParams();
    int ServerPort = Address.split(':')[1].toInt();
    QString ServerIP ( Address.split(':')[0]);
    QApplication a(argc, argv);
    ClientWindow w(ServerPort, ServerIP);
    w.show();
    return a.exec();
}
