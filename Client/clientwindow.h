#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include <QAbstractSocket>
#include <QTcpSocket>
#include <QHostAddress>
#include <QTcpServer>
#include <QListWidgetItem>
#include <memory>
#include "grasshopper.h"
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

    void onRead();
    void on_NameInput_returnPressed();   
    void on_SendMsg_clicked();
    void on_FriendList_itemDoubleClicked(QListWidgetItem *item);
    void on_MsgInput_returnPressed();
    void ConnDetector();
    void on_UpdateListButton_clicked();
    void on_checkBox_toggled(bool checked);

private:
    //<=methods=>
    int Resolver(QString Data);
    void SendMessageToPeer(QString PeerName);
    void ConnectToPeer(QString IP, int Port, QString UserName);
    void ParseAllUsersData(QString Response);
    void MyKeyGen();
    QString Encrypt(QString Message);
    QString Decrypt(QString Message);
    //<=fields=>
    uint8_t InthashArray[32];//for test
    kuz_key_t Key;
    w128_t Bytes;
    QMap <QString, std::shared_ptr<QTcpSocket>> Peers;
    std::unique_ptr<QTcpSocket> ServerSocket;
    std::unique_ptr<QTcpServer> ThisListenSocket;
    QString Destination;
    QString NickName;
    QString ServerIP;
    int ServerPort;
    bool ConnectedToServer = false;
    bool Private = false;
    Ui::ClientWindow *ui;
};

#endif // CLIENTWINDOW_H
