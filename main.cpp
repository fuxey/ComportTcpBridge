#include <QCoreApplication>
#include <QSerialPortInfo>
#include <QDebug>
#include "tcpcomportbridge.h"
#include "cxxopts.hpp"
#include <csignal>



static void signalHandler(int signum) {
  qInfo() << "Signal caught, shutdown program: " << signum;
  qApp->exit(1);

}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    bool verbose = false;


    cxxopts::Options options("XDock test serial echo");
    options.add_options()(
        "c,serport", "Serialport used, full path e.g.: '/dev/ttyUSB0', or 'COM3' ",
        cxxopts::value<std::string>()->default_value("/dev/ttyUSB0"))(
        "b,baudrate", "baudrate for serial",cxxopts::value<int>()->default_value("115200"))(
        "p,port", "tcp port where telnet can connect to", cxxopts::value<int>()->default_value("8080"))(
        "l,listports", "list all available comports")(
        "v,verbosity", "print all received messages")(
        "h,help", "Print helptext");

    auto result = options.parse(argc, argv);

    if(result.count("verbosity")) {
        verbose = true;
    }


    if (result.count("help")) {
      std::cout << options.help() << std::endl;
      return 0;
    }
#ifndef Q_OS_WINDOWS
    std::signal(SIGKILL, signalHandler);
#endif
    std::signal(SIGTERM, signalHandler);
    std::signal(SIGINT, signalHandler);


    if(result.count("listports")){
        QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
        for(int i = 0; i < ports.size();i++){
            qInfo() << "available port:" << i << ports.at(i).portName() << ports.at(i).vendorIdentifier();
        }
        if(ports.size() == 0){
            qInfo() << "No Comports Available";
        }
    }


    if(result.count("serport") && result.count("baudrate") && result.count("port")) {

        TcpComportBridge *bridge;
        bridge = new TcpComportBridge(QString::fromStdString(result["serport"].as<std::string>()),
                result["port"].as<int>(),result["baudrate"].as<int>(),verbose);


        if(!bridge->startTcpServer()) {
            qWarning() << "Cannot Start TcpServer!";
            return 1;
        }

        if(!bridge->connectToComport()) {
            qWarning() << "Cannot Open Comport!";
            return 2;
        }


        qInfo() << "Start Bridge on Comport"<< QString::fromStdString(result["serport"].as<std::string>())
                << "Baudrate" << result["baudrate"].as<int>()
                << "port" << result["port"].as<int>();

    } else {
       std::cout << options.help() << std::endl;
       return 0;
    }
    return a.exec();
}
