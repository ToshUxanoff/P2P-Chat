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
    int Resolver(const QString &Data);

private slots:
    void on_Starting_clicked();
    void on_Stopping_clicked();
    void ConnectClient();
    void ListeningClient();
    void UpdateUsersList();
    void DeleteOfflineUser(const QString &Name);
private:
    //server address and port
    QString ServerAddress = "127.0.0.1";
    int Port = 9090;
    //<=database funcs=>

    void AddNewUser(const QString& NickName, const QString& Status,const QString& Address);
    void SendAllUsers(QTcpSocket* ClientSocket);
    QString SearchUser(const QString& Username);
    bool IsUniqueUser(const QString & Username);
    //<=vars=>
    bool ServerOn = false;
    Ui::ServerWindow *ui;
    std::unique_ptr<QTcpServer> tcpServer;
    QSqlDatabase DataBase;
    QMap<QString, QTcpSocket*> Users; //for send info about new peers
};

#endif // SERVERWINDOW_H
