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
private:
    quint16 m_port;


signals:
    void NewSocketConnection_s(QTcpSocket *);


    // QTcpServer interface
protected:
    void incomingConnection(qintptr handle);
};

#endif // TCPSERVER_H
