#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QTcpSocket>
namespace Ui {
class ServerWindow;
}

class ServerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServerWindow(QWidget *parent = 0);
    ~ServerWindow();
    int Resolver(QString& Data);
private slots:
    void on_Starting_clicked();
    void on_Stopping_clicked();
    void ConnectClient();
    void ListeningClient();

private:
    //server address and port
    QString ServerAddress = "127.0.0.1";
    int Port = 9090;
    Ui::ServerWindow *ui;
    QTcpServer *tcpServer;
    int Status;
    QMap<QString, QString> Users;
};

#endif // SERVERWINDOW_H
