#include "clientwindow.h"
#include <QApplication>
//#include "registration.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientWindow w(9090, "127.0.0.1");
    w.show();

    return a.exec();
}
