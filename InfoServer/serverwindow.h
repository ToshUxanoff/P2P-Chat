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
//! Класс, предоставляющий интерфейc сервера
class ServerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServerWindow(QWidget *parent = 0);
    ~ServerWindow();
    /*!
      \brief Функция, предназначенная для распознавания типа данных, переданных в неё

      Функция определяет приписанный к началу данных флаг, который указывает на тип данных (сообщение, ответ от сервера, различные запросы от других пиров).
      \param[in] Data  Данные, тип которых необходимо определить
      \return Число - код, соответствующий типу пришедших данных.
    */
    int Resolver(const QString &Data);

private slots:
    /*!
    \brief Слот, включающий сервер при нажатии кнопки Start
    */
    void on_Starting_clicked();
    /*!
    \brief Слот, выключающий сервер при нажатии кнопки Stop
    */
    void on_Stopping_clicked();
    /*!
    \brief Слот, отвечающий за обработку входящих соединения и передачу их в слот ListeningClient()
    */
    void ConnectClient();
    /*!
    \brief Слот, "слушающий" приходящие данные от пользователя
    */
    void ListeningClient();

private:
    //server address and port
    QString ServerAddress = "0.0.0.0";
    int Port = 9090;
    //<=database funcs=>
    /*!
    \brief Функция для удаления из базы данных вышедшего из сети пользователя
    */
    void DeleteOfflineUser(const QString &Name);
    /*!
    \brief Функция для обновления списка пользователей в экране
    */
    void UpdateUsersList();
    /*!
      \brief Функция, предназначенная для добавления пользователя в базу данных

      \param[in] NickName  Имя пользователя
      \param[in] Status  Статус (приватный или публичный)
      \param[in] Address IP-адрес
    */
    void AddNewUser(const QString& NickName, const QString& Status, const QString& Address);
    /*!
      \brief Функция, предназначенная для отправки списка всех пиров пользователю

      \param[in] ClientSocket  Сокет, инициализированный адресом пользователя
    */
    void SendAllUsers(QTcpSocket* ClientSocket);
    /*!
      \brief Функция, предназначенная для поиска пользователя в базе данных

      \param[in] UserName  Имя пользователя
    */
    QString SearchUser(const QString& Username);
    /*!
      \brief Функция, предназначенная для проверки имени пользователя на уникальность

      \param[in] UserName  Имя пользователя
    */
    bool IsUniqueUser(const QString & Username);
    //<=vars=>
    bool ServerOn = false;  //! Переменная, отвечающая за состояние сервера (включен или выключен)
    Ui::ServerWindow *ui;
    std::unique_ptr<QTcpServer> tcpServer; //! Указатель на слушающий сокет сервера
    QSqlDatabase DataBase;  //! Объект базы данных
    QMap<QString, QTcpSocket*> Users; //for send info about new peers
};

#endif // SERVERWINDOW_H
