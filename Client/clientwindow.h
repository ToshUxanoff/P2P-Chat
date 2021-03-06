#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include <QAbstractSocket>
#include <QHostAddress>
#include <QTcpServer>
#include <QListWidgetItem>
#include <QCloseEvent>
#include <QTimer>
#include <QEventLoop>
#include <QNetworkProxyQuery>
#include <QNetworkProxyFactory>
#include "Kuznyechik.hpp"
#include <iomanip>
#include <sstream>
#include <dh.h>
#include <dh2.h>
#include <nbtheory.h>
#include <iostream>
#include <osrng.h>
#include <peer.h>
#include <issuecreator.h>

namespace Ui {
class ClientWindow;
}
//! Класс, предоставляющий интерфейc пользователя
class ClientWindow : public QMainWindow
{
    Q_OBJECT

public:
  /*!
      \brief Конструктор, принимающий на вход порт и адрес информационного сервера

      \param[in] Port Порт
      \param[in] address IPv4 адрес
  */
    ClientWindow(int Port, QString address, QWidget *parent = 0);
    /*!
      \brief Деструктор
    */
    ~ClientWindow();
public slots:
    /*!
      \brief Слот, отвечающий за отправку поискового запроса на сервер по нажатию кнопки Return
    */
    void on_SearchLine_returnPressed();
    /*!
      \brief Слот, отвечающий за получение входящих данных

         Передает данные в Resolver, который вернет информацию о формате пришедших данных. После определения формата (сообщение, ответ от сервера, запрос на обмен ключами и т.п.) - функция передает данные на обработку
     */
    void onRead();
    /*!
      \brief Слот, отвечающий за сохранение и отправку на сервер имени пользователя
    */
    void on_NameInput_returnPressed();

    /*!
      \brief Слот, определяющий имя пира, который был выбран пользователем (используется для отправки сообщений выбранному пользователю)
    */
    void on_FriendList_itemDoubleClicked(QListWidgetItem *item);
    /*!
      \brief Слот, служащий для cчитывания текста из поля ввода по нажатию клавиши return, добавляющий сообщение в историю и вызывающий функцию отправки сообщения этому пиру
    */
    void on_MsgInput_returnPressed();
    /*!
      \brief Слот для обнаружения входящих соединений
    */
    void ConnDetector();
    /*!
     \brief Слот, отвечающий за запрос серверу на получение списка всех пиров в сети. Активируется по нажатию кнопки Update
    */
    void on_UpdateListButton_clicked();
    /*!
      \brief  Слот, информирующий о нажатии галочки "Private" при входе в сеть. Устанавливает соответствующий статус(Private, Public)текущему пользователю
    */
    void on_checkBox_toggled(bool checked);
    /*!
    \brief Слот для открытия Issue Creator по нажатию соответствующей кнопки
    */
    void on_pushButton_clicked();
    /*!
    \brief Слот для отправки запроса о поиске пира на сервер
    */
    void on_SearchButton_clicked();
    /*!
    \brief Слот, аналогичный on_NameInput_returnPressed()
    */
    void on_LoginButton_clicked();
    /*!
    \brief Слот, перехватывающий закрытие окна приложения и отправляющий запрос на сервер о выходе из сети перед закрытием
    */
    void closeEvent(QCloseEvent* e);

private:
    //<=methods=>
    /*!
      \brief Функция, предназначенная для распознавания типа данных, переданных в неё

      Функция определяет приписанный к началу данных флаг, который указывает на тип данных (сообщение, ответ от сервера, различные запросы от других пиров).
      \param[in] Data  Данные, тип которых необходимо определить
      \return Число - код, соответствующий типу пришедших данных.
    */
    int Resolver(const QString &Data);
    /*!
    \brief Функция для отправки сообщения пиру

      Функция ищет нужного пира в списке пиров и отправляет ему введенное в окне ввода сообщение
      \param[in] PeerName Имя адресата
      \return Ничего не возвращает
    */
    void SendMessageToPeer(const QString &PeerName, QString Message);
    /*!
      \brief Функция для отправки запроса на соединение другому пиру

      Функция инициализирует новый сокет переданными данными (IP, Port), создается новый объект класса Peer, использующийся для хранения данных о пользователе, заносит объект в структуру для хранения списка "знакомых" пиров, после чего этому пиру автоматически отправляется запрос на соединение. Получив такой запрос, пир автоматически сохранит пользователя отправившего этот запрос в своей структуре и сможет отправлять ему сообщения. Таким образом пиры будут "знать" друг друга без помощи информационного сервера
      \param[in] IP IPv4 адрес пира, которому будет отправляться запрос.
      \param[in] Port Порт
      \param[in] UserName Имя пира
      \return Ничего не возвращает
    */

    void ConnectToPeer(const QString &IP, int Port, const QString &UserName);
    /*!
      \brief Функция для отправки запроса на соединение другому пиру если статус текущего пользователя - приватный.

      Запрос на соединение не должен отправляться от приватного пира без необходимости, чтобы не раскрывать его. Если такая необходимость появляется - запрос отправляется, тогда адресат будет знать приватного пользователя.
      \param[in] UserName Имя пира (необходимо для поиска его в своей структуре, так как приватный пир имеет информацию обо всех публичных, соответственно они есть в его структуре, остается их только найти)
      \return Ничего не возвращает
    */
    void SendConnectRequest(const QString &PeerName);
    /*!
      \brief Парсер списка пользователей, полученного от сервера

      Выполняет парсинг полученной на вход строки, после чего заносит каждого пользователя в структуру. Вызывается при входе в сеть, либо при обновлении всего списка
      \params[in] Response Строка, содержащая информацию обо всех пользователях в сети
      \return Ничего не возвращает
    */
    void ParseAllUsersData(QString Response);
    /*!
        \brief Функция зашифровки сообщения с заданным ключом
        Функция шифрует сообщение  по алгоритму "Кузнечик" (ГОСТ Р 34.12-2015) с заданным ключом. Подробнее ознакомиться с реализацией можно перейдя по ссылке в источниках.

        \param[in] Message Сообщение, которое необходимо зашифровать.
        \param[in] Key Ключ для зашифровки
        \return Возвращает строку - зашифрованное сообщение
    */
    QString Encrypt(QString &Message, QString Key);
    /*!
        \brief Функция расшифровки сообщения с заданным ключом
        Функция дешифрует сообщение  по алгоритму "Кузнечик" (ГОСТ Р 34.12-2015) с заданным ключом. Подробнее ознакомиться с реализацией можно перейдя по ссылке в источниках.

        \param[in] Message Сообщение, которое необходимо дешифровать.
        \param[in] Key Ключ для дешифровки
        /return Возвращает строку - расшифрованное сообщение
    */
    QString Decrypt(QString &Message, QString Key);
    /*!
      \brief Функция для генерации параметров ключей (Prime, Generator, PrivNumb, PublicNumb) и самой пары ключей.

      Подробнее о параметрах можно прочесть в описании алгоритма Диффи-Хеллмана.
      \return Ничего не возвращает
    */
    void GenKeyParams();
    /*!
      \brief Функция для генерации параметров и выработки сеансового ключа с пиром, приславшим свои публичные данные для обмена ключами.

      Вызывается при получении запроса от пира на обмен ключами. Все необходимые данные он предоставляет в запросе. Подробнее о необходимых параметрах можно прочесть в описании алгоритма Диффи-Хеллмана.
      После генерации ключ заносится в структуру этого пира для последующей шифровки и дешифровки сообщений.
      \param[in] Username  Имя пира
      \param[in] prime  Prime параметр
      \param[in] generator Generator параметр
      \param[in] publicNumb Публичный ключ, полученный пиром, приславшим запрос, при выработке ключа.
      \return Возвращает сеансовый ключ для данного пира
    */
    CryptoPP::SecByteBlock IncomingSessionKeyGen(const QString &Username, CryptoPP::Integer prime, CryptoPP::Integer generator, CryptoPP::SecByteBlock publicNumb);
    /*!
        \brief Функция для согласования общего сеансового ключа

        С помощью полученного от пира его публичного ключа, сеансовый ключ согласуется и заносится в структру этого пира для последующей шифровки и дешифровки сообщений.
      \param[in] Username  Имя пира
      \param[in] publicNumb Публичный ключ, полученный пиром, приславшим запрос, при выработке сеансового ключа.
      \return Ничего не возвращает
    */
    void GettingAgreement(const QString &Username, CryptoPP::SecByteBlock publicNumb);
    /*!
      \brief Функция отправки публичного ключа заданному пиру

      \param[in] UserName  Имя пира
      \param[in] publicKey Публичный ключ для отправки
      \return Ничего не возвращает
    */
    void SendGeneratedPublicKey(const QString &UserName, CryptoPP::SecByteBlock publicKey);
    /*!
     \brief Функция поиска пира в структуре по имени.

     \param[in] Name Имя искомого пира
     \return Возвращает указатель на объект пира
    */
    Peer* SearchPeerByName(const QString &Name);
    /*!
     \brief Функция возврата индекса пира в структуре по имени.

     \param[in] Name Имя искомого пира
     \return Возвращает индекс пира
    */
    int IndexPeerByName(const QString &Name);
    //<=fields=>
        //crypto
    CryptoPP::DH dh;   //!< Объект класса DH, необходимый для реализации алгоритма Диффи-Хеллмана. Подробнее можно узнать в официальной документации библиотеки CryptoPP
    CryptoPP::Integer Prime;  //!< Параметр необходимый для генерации пары ключей. Подробнее можно узнать в официальной документации библиотеки CryptoPP
    CryptoPP::Integer Generator;//!< Параметр необходимый для генерации пары ключей. Подробнее можно узнать в официальной документации библиотеки CryptoPP
    CryptoPP::SecByteBlock PrivNumb;//!< Публичное сгенерированное с помощью вышеуказанных параметров число. Подробнее можно узнать в официальной документации библиотеки CryptoPP
    CryptoPP::SecByteBlock PublicNumb;  //!< Приватное сгенерированное с помощью вышеуказанных параметров число. Подробнее можно узнать в официальной документации библиотеки CryptoPP
    CryptoPP::SecByteBlock MySecretKey; //!< Приватный ключ. Подробнее можно узнать в официальной документации библиотеки CryptoPP
        //sockets
    QVector<Peer> Peers;    //!< Структура для хранения списка известных пиров
    std::unique_ptr<QTcpSocket> ServerSocket;  //!< Указатель на сокет инициализированный адресом и портом информационного сервера
    std::unique_ptr<QTcpServer> ThisListenSocket;  //!< Указатель на слушающий сокет текущего пользователя
       //vars
    QString Destination;    //!< Имя адресата
    QString NickName;       //!< Имя текущего пользователя
    QString ServerIP;       //!< IPv4 адрес сервера
    int ServerPort;         //!< Порт информационного сервера
    bool ConnectedToServer = false;   //!< Флаг, сигнализирующий о успешном присоединении к серверу. Если соединения нет - поиск недоступен.
    bool Private = false;     //!< Флаг, сигнализирующий о статусе пользователя.
    Ui::ClientWindow *ui;
};

#endif // CLIENTWINDOW_H
