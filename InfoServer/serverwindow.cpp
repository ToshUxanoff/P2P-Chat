#include "serverwindow.h"
#include "ui_serverwindow.h"
#include <QMessageBox>
#include <QSqlError>

ServerWindow::ServerWindow(QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::ServerWindow)
    ,tcpServer(new QTcpServer(this))
{
    ui->setupUi(this);
    DataBase = QSqlDatabase::addDatabase("QSQLITE", "UsersList");
    if(!DataBase.open())
    {
       QMessageBox::warning( 0 , "Ошибка!", DataBase.lastError().databaseText());
    }
     QSqlQuery query(DataBase);
     query.exec("CREATE TABLE UsersList (Name VARCHAR(32), Status VARCHAR(5), Addr VARCHAR(32))");
}

ServerWindow::~ServerWindow()
{
    if(ServerOn == true)
    {
        tcpServer->close();
    }
    ServerOn = false;
    DataBase.close();
    delete ui;

}
void ServerWindow::AddNewUser(QString NickName, QString Status, QString Address)
{
    QSqlQuery query(DataBase);
    query.prepare("INSERT INTO UsersList  (Name, Status, Addr) VALUES (:Name, :Status, :Addr)");
    query.bindValue(":Name", NickName);
    query.bindValue(":Status", Status);
    query.bindValue(":Addr", Address);
    query.exec();
}
QString ServerWindow::SearchUser(QString Username)
{
   QSqlQuery query(DataBase);
   QString RetStr;
   query.exec("SELECT Name, Addr FROM UsersList WHERE Status = '!PR!'");
   while(query.next())
   {
       if(query.value(0).toString() == Username)
       {
           RetStr = "!S!" + query.value(1).toString() + ':' + query.value(0).toString() + '|';
           return RetStr;
       }
   }
   RetStr = "!SMESS!Error, User not found";
   return RetStr;
}
void ServerWindow::SendAllUsers(QTcpSocket *ClientSocket)
{
    QDataStream ClientStream(ClientSocket);
    QSqlQuery query(DataBase);
    QString AllUsersData;
    query.exec("SELECT Name, Addr FROM UsersList WHERE Status = '!PUB!'");
    while (query.next())
    {
          AllUsersData += query.value(1).toString() + ':' + query.value(0).toString() + '|';
    }
    ClientStream << "!S!" + AllUsersData;
    ui->Logs->append("sended" + AllUsersData);
}
int ServerWindow::Resolver(QString& Data)
{
    if (Data.startsWith("!0!"))
    {

        return 0; //registration
    }
    else if (Data.startsWith("!1!"))
    {

        return 1; //login
    }
    else if(Data.startsWith("!2!"))
    {

        return 2; //search request
    }
    else if(Data.startsWith("!UPD!"))
    {
        return 3;
    }
    return -1; //wrong data format
}
void ServerWindow::on_Starting_clicked()
{

    connect(tcpServer.get(), SIGNAL(newConnection()), this, SLOT(ConnectClient()));
    if (!tcpServer->listen(QHostAddress(ServerAddress), Port) && ServerOn==false)
    {
         qDebug() <<  QObject::tr("Unable to start the server: %1 ").arg(tcpServer->errorString());
         ui->Logs->append(tcpServer->errorString());
    }
    else if(ServerOn == false)
    {
         ServerOn = true;
         ui->Logs->append("TCPServer listen on " + ServerAddress);
         ui->Logs->append(QString::fromUtf8("Server is running!"));
    }
}
void ServerWindow::ConnectClient()
{
    if(ServerOn==true)
    {
        ui->Logs->append("New connection...");
        QTcpSocket* ClientSocket = tcpServer->nextPendingConnection();
        connect(ClientSocket,SIGNAL(readyRead()),this, SLOT(ListeningClient()));
    }
}

void ServerWindow::ListeningClient()
{
    QTcpSocket* ClientSocket = (QTcpSocket*)sender();
    QDataStream ClientStream(ClientSocket);
    QString Data;
    QString Response;
    ClientStream >> Data;
    if(Resolver(Data) == 0) //registration
    {
        Data = Data.mid(3);
        AddNewUser(Data.split(',')[0], Data.split(',')[2],Data.split(',')[1]);
        ui->Logs->append("New registration request from " + Data);
        ui->RegisteredUsers->append(Data.split(',')[0]);
        SendAllUsers(ClientSocket);
        Users[Data.split(',')[0]] = ClientSocket;

    }
    else if(Resolver(Data) == 1)    //login
    {
        //here request to db
        Data = Data.mid(3);
    }
    else if (Resolver(Data) == 2)
    {
        //here search request to db (search)
        Data = Data.mid(3);
        ui->Logs->append("Search request :" + Data);
        Response = SearchUser(Data);
        ClientStream << Response;
    }
    else if(Resolver(Data)==3)
    {
        SendAllUsers(ClientSocket);
    }
    else
    {
        ui->Logs->append("Error : " + Data);
    }

}
void ServerWindow::on_Stopping_clicked()
{
    if(ServerOn==true)
    {
       tcpServer->close();
       ui->Logs->append(QString::fromUtf8("Server was stopped!"));
       ServerOn = false;
     }
}
