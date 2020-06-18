#ifndef TCPCOMPORTBRIDGE_H
#define TCPCOMPORTBRIDGE_H

#include <QObject>
#include <tcpserver.h>
#include <QTcpSocket>
#include <QDebug>
#include <QSerialPort>


class TcpComportBridge : public QObject
{
    Q_OBJECT
public:
    TcpComportBridge(QString Comport, quint16 tcpPort, quint32 Baudrate,bool verbose=false);
    bool connectToComport();
    bool startTcpServer();
    void ConnectToServer(QString Address, quint32 port);

private slots:
    void onNewSocket(QTcpSocket *socket);
    void onTcpReadyRead();
    void onComportReadRead();
    void onSocketDisconnect();
private:
    QList<QTcpSocket *> socketList;
    TcpServer *Server;
    QSerialPort *comport;
    bool m_verbose;
};

#endif // TCPCOMPORTBRIDGE_H
