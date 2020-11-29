#include <QCoreApplication>
#include <iostream>
#include "udpthreadcmd.h"
#include "udpthreadpic.h"
#include <string>
#include <QObject>
#include <QThread>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    cout << "Car Cloud has ran successfully" << endl;
    UdpThreadCmd cmdthread;
    UdpThreadPic picthread;
    cmdthread.start();
    picthread.start();
    string cmd;
    while(1){
        cin >> cmd;
        if(cmd == "stop"){
            cmdthread.quit();
            picthread.quit();
        }
    }
    return a.exec();
}
