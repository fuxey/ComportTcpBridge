#include "tcpserver.h"

TcpServer::TcpServer(quint16 port)
{
    this->m_port = port;

}


bool TcpServer::StartServer()
{
    if(!this->listen(QHostAddress::Any,this->m_port)){
        qDebug() << "Could not start server";
        return false;
    }else {
        qDebug() << "Listening... to port " << this->m_port;
        return true;
    }
}


void TcpServer::incomingConnection(int socketDescriptor)
{
    qDebug() << socketDescriptor << " Connecting...";

    QTcpSocket *socket = new QTcpSocket();
    if(!socket->setSocketDescriptor(socketDescriptor)){
       // emit socket->error();
    }

    emit NewSocketConnection_s(socket);
}
