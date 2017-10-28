#include "clientwindow.h"
#include "ui_clientwindow.h"

ClientWindow::ClientWindow(int Port, QString address, QWidget *parent)
    :QMainWindow(parent)
    ,ServerIP(address)
    ,ServerPort(Port)
    ,ui(new Ui::ClientWindow)
{
    ui->setupUi(this);
    MyListenSocket = new QTcpServer(this);
    if(!MyListenSocket->listen())
    {
        ui->DebugWindow->append("ListenSocket unavailable");
    }
    connect(MyListenSocket, SIGNAL(newConnection()), this, SLOT(ConnDetector()));
}

ClientWindow::~ClientWindow()
{
    delete ui;
}
int ClientWindow::Resolver(QString Data)
{
    if(Data.startsWith("!S!"))   //server response (success search)
    {
        return 0;
    }
    else if(Data.startsWith("!C!"))  //new connection request (from peer)
    {
        return 1;
    }
    else if(Data.startsWith("!M!"))  //message
    {
        return 2;
    }
    else if(Data.startsWith("!SMESS!")) //server message
    {
        return 9;
    }
    return -1;
    //add more flags
}
void ClientWindow::SendMessageToPeer(QString PeerName)
{
    QDataStream PeerStream(Peers[PeerName]);
    QString Message = "!M!" + NickName + ':'+ ui->MsgInput->text() ;
    PeerStream << Message;
}
//WORKS
void ClientWindow::ConnDetector()
{
    ui->DebugWindow->append("Someone connected!... ");
    QTcpSocket* LSocket = MyListenSocket->nextPendingConnection();
    connect(LSocket,SIGNAL(readyRead()),this, SLOT(onRead()));
}
//WORKS
void ClientWindow::ConnectToPeer(QString IP, int Port, QString UserName)
{
    QHostAddress addr(IP);
    QTcpSocket* NewSocket = new QTcpSocket();
    NewSocket->connectToHost(addr,Port);
    QDataStream Stream (NewSocket);
    QString ConnectStr("!C!New connection from " +  NickName + " .If you want to chat with this user - search him! ");
    Stream << ConnectStr;
    connect(NewSocket,  SIGNAL(readyRead()), this, SLOT(onRead()));
    ui->DebugWindow->append("ConnectRequest sended");
    Peers[UserName] = NewSocket;
}
//SEARCH
void ClientWindow::on_SearchLine_returnPressed()
{
    QString Request = ui->SearchLine->text();
    Request = "!2!" + Request; //search request
    QDataStream ServStream(ServerSocket);
    ServStream << Request;
}
//REGISTRATION
void ClientWindow::on_NameInput_returnPressed()
{

    QString Name = ui->NameInput->text();
    NickName = Name;
    ServerSocket = new QTcpSocket(this);
    ServerSocket->connectToHost(ServerIP, ServerPort);
    QString RegStr = "!0!" + NickName + ',' + MyListenSocket->serverAddress().toString() +':' + QString::number(MyListenSocket->serverPort()); // +address
    QDataStream ServStream(ServerSocket);
    ServStream << RegStr;
    connect(ServerSocket, SIGNAL(readyRead()), this, SLOT(onRead()));
    ui->NameLabel->setText("You logged as " + NickName);

}

void ClientWindow::onRead()
{
    QTcpSocket* ListenSocket = (QTcpSocket*)sender();
    QDataStream LStream(ListenSocket);
    QString Response;
    LStream >> Response;
    if(Resolver(Response) == 0)
    {
        Response = Response.mid(3);
        ui->DebugWindow->append(ui->SearchLine->text() + " was founded!");
        ConnectToPeer(Response.split(':')[0], Response.split(':')[1].toInt(), ui->SearchLine->text());
        ui->FriendList->addItem(ui->SearchLine->text());

    }
    else if(Resolver(Response) == 1)
    {
        Response = Response.mid(3);
        ui->DebugWindow->append("New connect! " + Response);

    }
    else if(Resolver(Response) == 2)
    {
        Response = Response.mid(3);
        ui->MsgBrowser->append(Response);
    }
    else if(Resolver(Response) == 9)
    {
        Response = Response.mid(7);
        ui->DebugWindow->append("Server : " + Response);
    }
    else if(Resolver(Response) == -1)
    {
        ui->DebugWindow->append("Error! " + Response);
    }
}

void ClientWindow::on_SendMsg_clicked()
{

   QString Message = ui->MsgInput->text();
   ui->MsgBrowser->append ("Me: " + Message);
   SendMessageToPeer(Destination);
}

void ClientWindow::on_FriendList_itemDoubleClicked(QListWidgetItem *item)
{
    Destination = item->text();
}

void ClientWindow::on_MsgInput_returnPressed()
{
    on_SendMsg_clicked();
}
