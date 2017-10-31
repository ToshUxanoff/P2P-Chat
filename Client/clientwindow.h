#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include <QAbstractSocket>
#include <QTcpSocket>
#include <QHostAddress>
#include <QTcpServer>
#include <QListWidgetItem>
#include <memory>

namespace Ui {
class ClientWindow;
}

class ClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    ClientWindow(int Port, QString address, QWidget *parent = 0);
    ~ClientWindow();

private slots:
    void on_SearchLine_returnPressed();
    void ConnDetector();

    int Resolver(QString Data);
    void ConnectToPeer(QString IP, int Port, QString UserName);
    void onRead();
    void on_NameInput_returnPressed();
    void SendMessageToPeer(QString PeerName);
    void on_SendMsg_clicked();

    void on_FriendList_itemDoubleClicked(QListWidgetItem *item);

    void on_MsgInput_returnPressed();

private:
    QMap <QString, std::shared_ptr<QTcpSocket>> Peers;
    std::unique_ptr<QTcpSocket> ServerSocket;
    std::unique_ptr<QTcpServer> MyListenSocket;
    QString Destination;
    QString NickName;
    QString ServerIP;
    int ServerPort;
    bool ConnectedToServer = false;
    Ui::ClientWindow *ui;
};

#endif // CLIENTWINDOW_H
