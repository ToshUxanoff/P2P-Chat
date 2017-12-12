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
void ServerWindow::AddNewUser(const QString &NickName, const QString &Status, const QString &Address)
{
    QSqlQuery query(DataBase);
    query.prepare("INSERT INTO UsersList  (Name, Status, Addr) VALUES (:Name, :Status, :Addr)");
    query.bindValue(":Name", NickName);
    query.bindValue(":Status", Status);
    query.bindValue(":Addr", Address);
    query.exec();
}
bool ServerWindow::IsUniqueUser(const QString &Username)
{
    QSqlQuery query(DataBase);
    query.exec("SELECT Name FROM UsersList");
    QString Name;
    while(query.next())
    {
        Name = query.value(0).toString();
        if(Name == Username)
        {
            return false;
        }
    }
    return true;
}
QString ServerWindow::SearchUser(const QString& Username)
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
}
void ServerWindow::UpdateUsersList()
{
    ui->RegisteredUsers->clear();
    QSqlQuery query(DataBase);
    QString Name;
    query.exec("SELECT Name FROM UsersList");
    while(query.next())
    {
        ui->RegisteredUsers->append(query.value(0).toString());
    }
}
int ServerWindow::Resolver(const QString& Data)
{
    if (Data.startsWith("!0!"))
    {
        return 0; //registration
    }
    else if(Data.startsWith("!S!"))
    {
        return 1; //search request
    }
    else if(Data.startsWith("!UPD!"))
    {
        return 2;
    }
    else if(Data.startsWith("!OFF!"))
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
void ServerWindow::DeleteOfflineUser(const QString& Name)
{
    QSqlQuery query(DataBase);
    query.prepare("DELETE FROM UsersList WHERE Name=:name");
    query.bindValue(":name", Name);
    query.exec();
    UpdateUsersList();
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
        if(IsUniqueUser(Data.split(',')[0])) //new user
        {
            AddNewUser(Data.split(',')[0], Data.split(',')[2], Data.split(',')[1]);
            ui->Logs->append("Registration request from " + Data);
            ui->RegisteredUsers->append(Data.split(',')[0]);
            Response ="!CNCTD!";
            ClientStream << Response;
            Users[Data.split(',')[0]] = ClientSocket;
        }
        else
        {
            Response = "!SMESS! Error!Such user already exists!";
            ClientStream << Response;
        }
    }
    else if (Resolver(Data) == 1)
    {
        Data = Data.mid(3);
        ui->Logs->append("Search request :" + Data);
        Response = SearchUser(Data);
        ClientStream << Response;
    }
    else if(Resolver(Data) == 2)
    {
        SendAllUsers(ClientSocket);
    }
    else if(Resolver(Data) == 3)
    {
        Data = Data.mid(5);
        ui->Logs->append(Data + " is offline now");
        DeleteOfflineUser(Data);
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
