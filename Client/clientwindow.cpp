#include "clientwindow.h"
#include "ui_clientwindow.h"

ClientWindow::ClientWindow(int Port, QString address, QWidget *parent)
    :QMainWindow(parent)
    ,ServerSocket (new QTcpSocket(this))
    ,ThisListenSocket(new QTcpServer(this))
    ,ServerIP(address)
    ,ServerPort(Port)
    ,ui(new Ui::ClientWindow)
{
    ui->setupUi(this);
    if(!ThisListenSocket.get()->listen())
    {
        ui->DebugWindow->append("ListenSocket unavailable");
    }
    connect(ThisListenSocket.get(), SIGNAL(newConnection()), this, SLOT(ConnDetector()));
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
    QDataStream PeerStream(Peers[PeerName].get());
    QString Message;
    if(Private == true)
    {
        Message = "!M!"  + NickName + "(private user)" + ':'+ ui->MsgInput->text();
    }
    else
    {
        Message = "!M!" + NickName + ':' + ui->MsgInput->text();
    }
    PeerStream << Message;
}
void ClientWindow::ConnDetector()
{
    QTcpSocket* LSocket(ThisListenSocket.get()->nextPendingConnection());
    connect(LSocket, SIGNAL(readyRead()), this, SLOT(onRead()));
}
void ClientWindow::ConnectToPeer(QString IP, int Port, QString UserName)
{
    if(!Peers.contains(UserName))
    {
        QHostAddress addr(IP);
        std::shared_ptr<QTcpSocket>NewSocket(new QTcpSocket());
        NewSocket.get()->connectToHost(addr,Port);
        QDataStream Stream (NewSocket.get());
        QString ConnectReq("!C!"  + ThisListenSocket.get()->serverAddress().toString() +':' + QString::number(ThisListenSocket.get()->serverPort()) + ':' + NickName);
        Stream << ConnectReq;
        connect(NewSocket.get(),  SIGNAL(readyRead()), this, SLOT(onRead()));
        Peers[UserName] = NewSocket;
    }
}
void ClientWindow::ParseAllUsersData(QString Response)
{
   int PeersNumber = Response.count('|');
   QVector<QString> Users;
   for(int i = 0; i < PeersNumber; ++i)
   {
       Users.push_back(Response.split('|')[i]);
       if(Users[i].split(':')[2]!= NickName)
       {
            QString IP(Users[i].split(':')[0]);
            int Port = Users[i].split(':')[1].toInt();
            QString Name(Users[i].split(':')[2]);
            ui->FriendList->addItem(Name);
            if(Private == false) {
                ConnectToPeer(IP, Port, Name);
            }
            else{
                std::shared_ptr<QTcpSocket>NewSocket(new QTcpSocket());
                NewSocket.get()->connectToHost(IP,Port);
                Peers[Name] = NewSocket;
            }
       }
    }
}
void ClientWindow::on_SearchLine_returnPressed()
{
    if(ConnectedToServer)
    {
        QString Request = ui->SearchLine->text();
        auto it = Peers.find(Request);
        if(Request != NickName && it == Peers.end())
        {
            Request = "!2!" + Request; //search request
            QDataStream ServStream(ServerSocket.get());
            ServStream << Request;
        }
    }
    else
    {
        ui->DebugWindow->append("Can't connect to server!");
    }
}
void ClientWindow::on_NameInput_returnPressed()
{
    NickName = ui->NameInput->text();
    ui->NameInput->hide();
    ui->checkBox->hide();
    ServerSocket.get()->connectToHost(ServerIP, ServerPort);
    QString Status("!PUB!");
    if(Private == true)
    {
        Status = "!PR!";
    }
    QString RegStr = "!0!" + NickName + ',' + ThisListenSocket.get()->serverAddress().toString() +':' + QString::number(ThisListenSocket.get()->serverPort()) + ',' + Status; // +address
    QDataStream ServStream(ServerSocket.get());
    ServStream << RegStr;
    connect(ServerSocket.get(), SIGNAL(readyRead()), this, SLOT(onRead()));
    ui->NameLabel->setText("Logged as " + NickName);
    ConnectedToServer = true;
}
void ClientWindow::onRead()
{
    QTcpSocket* ListenSocket((QTcpSocket*)sender());
    QDataStream LStream(ListenSocket);
    QString Response;
    LStream >> Response;
    if(Resolver(Response) == 0) //get data from server
    {
        Response = Response.mid(3);
        ParseAllUsersData(Response);
    }
    else if(Resolver(Response) == 1) //new connect
    {      
        if((Response.split(':')[2] != NickName) && (!Peers.contains(Response.split(':')[2])))
        {
            Response = Response.mid(3);
            ui->DebugWindow->append("New peer connected! " + Response.split(':')[2]);
            ui->FriendList->addItem(Response.split(':')[2]);
            QHostAddress addr(Response.split(':')[0]);
            int Port =  Response.split(':')[1].toInt();
            std::shared_ptr<QTcpSocket>NewSocket(new QTcpSocket());
            NewSocket.get()->connectToHost(addr,Port);
            Peers[Response.split(':')[2]] = NewSocket;
        }
    }
    else if(Resolver(Response) == 2) //message
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
   ui->MsgInput->clear();
}
void ClientWindow::on_FriendList_itemDoubleClicked(QListWidgetItem *item)
{
    Destination = item->text();
}
void ClientWindow::on_MsgInput_returnPressed()
{
    on_SendMsg_clicked();
}
void ClientWindow::on_checkBox_clicked()
{
    Private = true;
}
void ClientWindow::on_UpdateListButton_clicked()
{
    QString UpdReq = "!UPD!";
    ui->FriendList->clear();
    Peers.clear();
    QDataStream ServStream(ServerSocket.get());
    ServStream << UpdReq;

}
