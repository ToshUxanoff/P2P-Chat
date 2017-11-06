#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QTcpSocket>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlDriver>
#include <memory>
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
    void AddNewUser(QString NickName, QString Status, QString Address);
    void SendAllUsers(QTcpSocket* ClientSocket);
    QString SearchUser(QString Username);
    //server address and port
    QString ServerAddress = "127.0.0.1";
    int Port = 9090;
    bool ServerOn = false;
    Ui::ServerWindow *ui;
    std::unique_ptr<QTcpServer> tcpServer;
    QSqlDatabase DataBase;
    QMap<QString, QTcpSocket*> Users; //for send info about new peers
};

#endif // SERVERWINDOW_H
