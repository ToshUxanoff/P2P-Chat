#ifndef PEER_H
#define PEER_H
#include <memory>
#include <QTcpSocket>

class Peer
{
public:
    Peer();
    Peer(QString Name, std::shared_ptr<QTcpSocket> Socket);
    Peer(QString Name, std::shared_ptr<QTcpSocket> Socket, QString Key);
    void SetSessionKey(QString Key);
    QString PeerName;
    std::shared_ptr<QTcpSocket> PeerSocket;
    QString  SessionKey;
};

#endif // PEER_H
