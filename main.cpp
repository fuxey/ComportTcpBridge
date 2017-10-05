#include <QCoreApplication>
#include "argumentparser.h"
#include "qextserialenumerator.h"
#include <QDebug>
#include "tcpcomportbridge.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);



    Argument *ListComports = new Argument(QStringList() << "c","Enter c to see all available Comports");
    Argument *Comport = new Argument(QStringList() << "p", "Enter p <comport> to connect to it!");
    Argument *Port = new Argument(QStringList() << "t", "Enter t <port> for where to connect via tcp to it! Default is 9800");
    Argument *Baud = new Argument(QStringList() << "b", "Enter b < Baudrate> for the Baudrate of the Comport! Default is 115200");
    Argument *TcpClient = new Argument(QStringList() << "t", "Enter t <ipaddress> for the tcp server you want to connect with");
    ArgumentParser pars;
    pars.setArgs(ListComports);
    pars.setArgs(Comport);
    pars.setArgs(Port);
    pars.setArgs(Baud);
    pars.setArgs(TcpClient);

    pars.ParseArguments(a.arguments());
    pars.PrintArgumentDescription();


    quint16 tcpPort = 0;
    QString comportString;
    quint32 baudrate;
    QString clientAddr;

    if(ListComports->set){
        QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
        for(int i = 0; i < ports.size();i++){
            qDebug() << "available port:" << i << ports.at(i).portName << ports.at(i).enumName << ports.at(i).vendorID;
        }
        if(ports.size() == 0){
            qDebug() << "No Comports Available";
        }
    }

    if(TcpClient->set){

    } else{

    }


    if(Port->set){
        tcpPort = Port->Value;
    } else {
        qDebug() << "No correct TcpPort is entered use DefaultPort 9800";
        tcpPort = 9800;
    }

    if(Comport->set){
        comportString = Comport->payload;
        qDebug()<< "Use Comport "<<comportString;
    } else {
        qDebug() << "No correct Comport is set!";
        return 3;
    }


    if(Baud->set){
        baudrate = Baud->Value;
        qDebug() << "Set Baudrate to" << baudrate;
    } else {
        baudrate =115200;
        qDebug() << "No Baudrate was entered start with default Value 115200";
    }

    TcpComportBridge *bridge;
    bridge = new TcpComportBridge(comportString,tcpPort,baudrate);

    if(TcpClient->set){
        clientAddr = TcpClient->payload;
        bridge->ConnectToServer(clientAddr,tcpPort);
    } else {
        qDebug() << "No TcpHost was selected, try to start tcp Server!";
            if(!bridge->startTcpServer()){
            qDebug() << "Cannot Start TcpServer";
            return 1;
        }
    }

    if(!bridge->connectToComport()){
        qDebug() << "Cannot Open Comport!";
        return 2;
    }


    qDebug() << "Start Bridge on Comport"<< comportString <<"Baudrate" << baudrate << "port" << tcpPort;

    return a.exec();
}
