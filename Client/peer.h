#ifndef PEER_H
#define PEER_H
#include <memory>
#include <QTcpSocket>
#include <QVector>
//! Класс, предоставляющий интерфейс для хранения данных о каждом "знакомом" пире
class Peer
{
public:
  /*!
   \brief Конструктор по умолчанию
  */
    Peer();
    /*!
     \brief Конструктор, принимающий имя пира и указатель на сокет, инициализированный его адресом
    */
    Peer(QString Name, std::shared_ptr<QTcpSocket> Socket);
    /*!
     \brief Конструктор, принимающий имя пира, указатель на сокет(инициализированный его адресом) и сеансовый ключ для этого пира
    */
    Peer(QString Name, std::shared_ptr<QTcpSocket> Socket, QString Key);
    /*!
     \brief Set-функция для инициализации сеансового ключа этого пира
    */
    void SetSessionKey(QString Key);

    QString PeerName; //!< Имя пира
    std::shared_ptr<QTcpSocket> PeerSocket;//!<Указатель на сокет, инициализированный адресом пира
    QString  SessionKey;  //!< Сеансовый ключ для этого пира
    QVector <QString> MessagesHistory; //!< История сообщений с пиром
};

#endif // PEER_H
