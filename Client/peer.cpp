#include "peer.h"

Peer::Peer()
{

}
Peer::Peer(QString Name, std::shared_ptr<QTcpSocket> Socket)
    :PeerName(Name)
    ,PeerSocket(Socket)
{}
void Peer::SetSessionKey(QString Key)
{
    SessionKey = Key;
}

Peer::Peer(QString Name, std::shared_ptr<QTcpSocket> Socket, QString Key)
    :PeerName(Name)
    ,PeerSocket(Socket)
    ,SessionKey(Key)
{}
