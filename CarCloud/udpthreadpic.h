#ifndef UDPTHREADPIC_H
#define UDPTHREADPIC_H

#include <QObject>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QNetworkDatagram>
#include <iostream>
#include <QThread>

using namespace std;

#define SERVER_PORT_CMD_SEND        9000
#define SERVER_PORT_CMD_RECV        9100
#define SERVER_PORT_PIC_SEND        8000
#define SERVER_PORT_PIC_RECV        8100

class UdpThreadPic : public QThread
{
    Q_OBJECT
public:
    UdpThreadPic();
    QUdpSocket recv;
    QUdpSocket send;
    QHostAddress recveraddr;
    int recverport;
    void run() override;
};

#endif // UDPTHREADCMD_H
