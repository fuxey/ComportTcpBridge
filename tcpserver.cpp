#include "tcpserver.h"

TcpServer::TcpServer(quint16 port)
{
    this->m_port = port;

}


bool TcpServer::StartServer()
{
    if(!this->listen(QHostAddress::Any,this->m_port)){
        qWarning() << "Could not start server";
        return false;
    }else {
        qInfo() << "Listening... to port " << this->m_port;
        return true;
    }
}


void TcpServer::incomingConnection(qintptr handle)
{
    qInfo() << handle << " Connecting...";

    QTcpSocket *socket = new QTcpSocket();
    if(!socket->setSocketDescriptor(handle)){
       // emit socket->error();
    }

    emit NewSocketConnection_s(socket);
}
