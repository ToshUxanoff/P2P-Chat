#include "clientwindow.h"
#include "ui_clientwindow.h"
#include <math.h>

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
    QString Message = NickName + ':' + ui->MsgInput->text();
    Message = Encrypt(Message, "addkeyhere");
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
        Response = Decrypt(Response, "addkeyhere");
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

std::string hex_to_string(const std::string& in)
{
    std::string output;
    if ((in.length() % 2) != 0) {
        throw std::runtime_error("String is not valid length ...");
    }
    size_t cnt = in.length() / 2;
    for (size_t i = 0; cnt > i; ++i) {
        uint32_t s = 0;
        std::stringstream ss;
        ss << std::hex << in.substr(i * 2, 2);
        ss >> s;
        output.push_back(static_cast<unsigned char>(s));
    }
    return output;
}
std::string string_to_hex(const std::string& in)
{
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (size_t i = 0; in.length() > i; ++i)
    {
        ss << std::setw(2) << static_cast<unsigned int>(static_cast<unsigned char>(in[i]));
    }
    return ss.str();
}
void BlockAddition(std::string &Message)
{
   while(Message.length()%32 != 0)
   {
       Message += '00';
   }
}

QString ClientWindow::Encrypt(QString &Message, QString Key)
{
    const ByteBlock key = hex_to_bytes("8899aabbccddeeff0011223344556677fedcba98765432100123456789abcdef");
        std::string HexString (string_to_hex(Message.toStdString()));
        if(HexString.length()%32 != 0) //==16 bytes
        {
            BlockAddition(HexString);
        }
        ByteBlock ByteMessage = hex_to_bytes(HexString);
        Kuznyechik Encryptor(key);
        std::vector<ByteBlock> Vect16BytesBlocks = split_blocks(ByteMessage, 16);
        HexString.clear();
        for(size_t i = 0; i < Vect16BytesBlocks.size(); ++i)
        {
            Encryptor.encrypt(Vect16BytesBlocks[i], Vect16BytesBlocks[i]);
            HexString += hex_representation(Vect16BytesBlocks[i]);
        }

    Message = QString::fromStdString(HexString);
    return Message;
}
QString ClientWindow::Decrypt(QString &Message, QString Key)
{
    const ByteBlock TESTKEY = hex_to_bytes("8899aabbccddeeff0011223344556677fedcba98765432100123456789abcdef");
    std::string BufString = (Message.toStdString());
    ByteBlock ByteMessage = hex_to_bytes(BufString);
    Kuznyechik decryptor(TESTKEY);
    std::vector<ByteBlock> Vect16BytesMessages = split_blocks(ByteMessage, 16); //16-bytes blocks
    BufString.clear(); //using for write encrypted data in hex
    for(size_t i = 0; i < Vect16BytesMessages.size(); ++i)
    {
        decryptor.decrypt(Vect16BytesMessages[i], Vect16BytesMessages[i]);
        BufString += hex_representation(Vect16BytesMessages[i]);
    }
    Message = QString::fromStdString(hex_to_string(BufString));
    return Message;
}
void ClientWindow::on_checkBox_toggled(bool checked)
{
    Private = checked;
}
