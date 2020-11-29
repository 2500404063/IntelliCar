#include "udpthreadpic.h"

UdpThreadPic::UdpThreadPic()
{
    this->recv.bind(QHostAddress::Any,SERVER_PORT_PIC_RECV);
    this->send.bind(QHostAddress::Any,SERVER_PORT_PIC_SEND);
}

void UdpThreadPic::run(){
    while(1){
        if(this->recv.hasPendingDatagrams()){
            auto pack = this->recv.receiveDatagram();
            this->recveraddr = pack.senderAddress();
            this->recverport = pack.senderPort();
            cout << "Handled Receiver" << endl;
        }
        if(this->send.hasPendingDatagrams()){
            QByteArray data;
            auto len = this->send.pendingDatagramSize();
            data.resize(len);
            this->send.readDatagram(data.data(),len);
            this->recv.writeDatagram(data.data(),len,this->recveraddr,this->recverport);
        }
    }
}
