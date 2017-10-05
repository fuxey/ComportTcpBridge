#include "tcpcomportbridge.h"


TcpComportBridge::TcpComportBridge(QString Comport, quint16 tcpPort,quint32 Baudrate)
{
    this->Server = new TcpServer(tcpPort);
    this->comport = new QextSerialPort(Comport);

    switch(Baudrate){
        case 9600: this->comport->setBaudRate(BAUD9600); break;
        case 38400: this->comport->setBaudRate(BAUD38400); break;
        case 115200: this->comport->setBaudRate(BAUD115200); break;
        default: qDebug() << "Baudrate is undefined set to 115200";
        this->comport->setBaudRate(BAUD115200);
    }
    connect(this->Server,SIGNAL(NewSocketConnection_s(QTcpSocket*)),this,SLOT(onNewSocket(QTcpSocket*)));
}


bool TcpComportBridge::connectToComport()
{
    connect(this->comport,SIGNAL(readyRead()),this,SLOT(onComportReadRead()));
   return this->comport->open(QIODevice::ReadWrite);
}


bool TcpComportBridge::startTcpServer()
{
    return this->Server->StartServer();
}


void TcpComportBridge::ConnectToServer(QString Address,quint32 port){
    QTcpSocket *sock;
    sock = new QTcpSocket;
    sock->connectToHost(Address,port);
    if(sock->open(QTcpSocket::ReadWrite)){
        this->onNewSocket(sock);
    }else {
        sock->deleteLater();
    }
}


void TcpComportBridge::onNewSocket(QTcpSocket *socket){

    connect(socket,SIGNAL(readyRead()),this,SLOT(onTcpReadyRead()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(onSocketDisconnect()));

    socketList.append(socket);
}


void TcpComportBridge::onTcpReadyRead(){

    for(int i = 0; i < socketList.size(); i++){
        QTcpSocket *tempSock = socketList.at(i);
        if(tempSock->bytesAvailable()> 0){
            QByteArray data = tempSock->readAll();
            comport->write(data);
            qDebug() << "----------------------------------------------------------------------------------------";
            qDebug() << "Write data from socket to Comport" << tempSock->localAddress() << "data" << data.toHex();

        }
    }
}


void TcpComportBridge::onComportReadRead(){

    if(comport->bytesAvailable()>0){
        qDebug() << "----------------------------------------------------------------------------------------";
        qDebug() << "Write Data from Comport to:";
        QByteArray data = comport->readAll();
        for(int i = 0; i < socketList.size(); i++){
            QTcpSocket *tempsock = socketList.at(i);
            tempsock->write(data);
            qDebug() << tempsock->peerAddress();
        }
        qDebug() << data.toHex();
    }
}


void TcpComportBridge::onSocketDisconnect(){
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    socket->disconnectFromHost();

    socketList.removeOne(socket);
    socket->deleteLater();

    qDebug() << "Socket Disconnected!";
    for(int i = 0; i < socketList.size(); i++){
        qDebug() << socketList.at(i)->peerAddress();
    }

}
