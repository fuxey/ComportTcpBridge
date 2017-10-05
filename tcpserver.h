#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
class TcpServer :public QTcpServer
{
    Q_OBJECT
public:
    TcpServer(quint16 port);
    bool StartServer();
protected:
    void incomingConnection(int socketDescriptor);
private:
    quint16 m_port;


signals:
    void NewSocketConnection_s(QTcpSocket *);

};

#endif // TCPSERVER_H
