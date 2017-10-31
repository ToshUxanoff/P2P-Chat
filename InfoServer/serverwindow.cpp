#include "serverwindow.h"
#include "ui_serverwindow.h"

ServerWindow::ServerWindow(QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::ServerWindow)
    ,tcpServer(new QTcpServer(this))
{
    ui->setupUi(this);
}

ServerWindow::~ServerWindow()
{
    if(Status == 1)
    {
        tcpServer->close();
    }
    delete ui;
    Status = 0;
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
    return -1; //wrong data format
}
void ServerWindow::on_Starting_clicked()
{

    connect(tcpServer.get(), SIGNAL(newConnection()), this, SLOT(ConnectClient()));
    if (!tcpServer->listen(QHostAddress(ServerAddress), Port) && Status==0)
    {
         qDebug() <<  QObject::tr("Unable to start the server: %1 ").arg(tcpServer->errorString());
         ui->Logs->append(tcpServer->errorString());
    }
    else if(Status == 0)
    {
         Status=1;
         ui->Logs->append("TCPServer listen on " + ServerAddress);
         ui->Logs->append(QString::fromUtf8("Server is running!"));
    }
}
void ServerWindow::ConnectClient()
{
    if(Status==1)
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
        // here add user to db
        Data = Data.mid(3);
        Users[Data.split(',')[0]] = Data.split(',')[1];
        ui->Logs->append("New registration request from " + Data);
        Response = "!SMESS! Succesfully registered";
        ClientStream << Response;
        ui->RegisteredUsers->append(Data.split(',')[0]);
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
        auto it = Users.find(Data);
        if (it != Users.end())
        {
            Response = "!S!" + it.value();
        }
        else
        {
            Response = "!SMESS!Can't find this user!";
        }
        ClientStream << Response;
    }
    else
    {
        ui->Logs->append("Error : " + Data);
    }

}
void ServerWindow::on_Stopping_clicked()
{
    if(Status==1)
    {
       tcpServer->close();
       ui->Logs->append(QString::fromUtf8("Server was stopped!"));
       Status=0;
     }
}
