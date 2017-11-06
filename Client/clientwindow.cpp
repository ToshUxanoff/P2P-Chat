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
    kuz_init();
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
    QString Message = NickName + ':' + ui->MsgInput->text();
    Message = Encrypt(Message);
    if(Private == true)
    {
        Message = "!M! (private user)" + Message;
    }
    else
    {
        Message = "!M!" + Message;
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
    //hiding controls
    ui->NameInput->hide();
    ui->checkBox->hide();
    //connecting to server
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
    //generating key
    MyKeyGen();
}
void ClientWindow::onRead()
{
    QTcpSocket* ListenSocket((QTcpSocket*)sender());
    QDataStream LStream(ListenSocket);
    QString Response;
    LStream >> Response;
    if(Resolver(Response) == 0) //data from server
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
        Response = Decrypt(Response);
        ui->MsgBrowser->append(Response);
    }
    else if(Resolver(Response) == 9) //server messages
    {
        Response = Response.mid(7);
        ui->DebugWindow->append("Server : " + Response);
    }
    else if(Resolver(Response) == -1) //errors
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

void ClientWindow::on_UpdateListButton_clicked()
{
    QString UpdReq = "!UPD!";
    ui->FriendList->clear();
    Peers.clear();
    QDataStream ServStream(ServerSocket.get());
    ServStream << UpdReq;

}
void ClientWindow::MyKeyGen()
{

    QByteArray ByteHash(QCryptographicHash::hash(NickName.toUtf8(), QCryptographicHash::Sha256).toHex());
    for(int i = 0; i < 32; ++i)
    {
        InthashArray[i] = ByteHash[i];
    }
    kuz_set_encrypt_key(&Key, InthashArray);

}
QString ClientWindow::Encrypt(QString Message)
{
    QByteArray BuffByteMess = Message.toUtf8();
    uint8_t IntHashText[512];
    for(int i = 0; i < BuffByteMess.size(); ++i)
    {
       IntHashText[i] = BuffByteMess[i];
       Bytes.b[i] = IntHashText[i];
    }
    kuz_encrypt_block(&Key, &Bytes);
    QString ReturnMessage;
    for(int i = 0; i < BuffByteMess.size(); ++i)
    {
        ReturnMessage[i] = Bytes.b[i];
    }
    return ReturnMessage;
}
QString ClientWindow::Decrypt(QString Message)
{
    //test  version, need to add keys.
    //key = sha256(TEST) u vsex
    QByteArray BuffByteMess = Message.toUtf8();
    uint8_t IntHashText[512];
    for(int i = 0; i < BuffByteMess.size(); ++i)
    {
       IntHashText[i] = BuffByteMess[i];
       Bytes.b[i] = IntHashText[i];
    }
    kuz_set_decrypt_key(&Key, InthashArray);
    kuz_decrypt_block(&Key, &Bytes);
    QString ReturnMessage;
    for(int i = 0; i < BuffByteMess.size(); ++i)
    {
        ReturnMessage[i] = Bytes.b[i];
    }
    return ReturnMessage;
}

void ClientWindow::on_checkBox_toggled(bool checked)
{
    Private = checked;
}
