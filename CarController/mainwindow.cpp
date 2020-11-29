#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->view,
            static_cast<void(PicView::*)(QKeyEvent*)>(&PicView::keyPress),
            this,
            static_cast<void(MainWindow::*)(QKeyEvent*)>(&MainWindow::keyDown)
            );
    connect(ui->view,
            static_cast<void(PicView::*)(QKeyEvent*)>(&PicView::keyRelease),
            this,
            static_cast<void(MainWindow::*)(QKeyEvent*)>(&MainWindow::keyUp)
            );
    ui->view->setFocus();

}

void MainWindow::resizeEvent(QResizeEvent *event){
    //qDebug() << ui->view->width();
    QPixmap pic;
    //pic.load("D:/test.jpg");
    pic.loadFromData(Buf);
    QPalette palette = ui->view->palette();
    palette.setBrush(ui->view->backgroundRole(),
    QBrush(pic.scaled(ui->view->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    ui->view->setPalette(palette);
    ui->view->setAutoFillBackground(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyDown(QKeyEvent *e){ //按键按下处理槽函数
    char cmd = 0;   //指令临时变量
    if (e->key() == Qt::Key::Key_W){  //判断当W按下后
        if(!this->isW){
            this->isW = true;  //标记W是否按下过
            cmd = CMD_FORWARD; //设置指令（含义请看宏定义）
            this->sock.writeDatagram(&cmd,1,QHostAddress(QString(SERVER_IP)),SERVER_PORT_CMD_SEND);
            //发送数据
        }
    } //之后的代码与上类似
    else if (e->key() == Qt::Key::Key_A){
        if(!this->isA){
            this->isA = true;
            if(!isW) cmd = CMD_LEFT;
            else cmd = CMD_RUNL;
            this->sock.writeDatagram(&cmd,1,QHostAddress(QString(SERVER_IP)),SERVER_PORT_CMD_SEND);
        }
    }
    else if (e->key() == Qt::Key::Key_D){
        if(!this->isD){
            this->isD = true;
            if(!isW) cmd = CMD_RIGHT;
            else cmd = CMD_RUNR;
            this->sock.writeDatagram(&cmd,1,QHostAddress(QString(SERVER_IP)),SERVER_PORT_CMD_SEND);
        }
    }
    else if (e->key() == Qt::Key::Key_S && !e->isAutoRepeat()){
        cmd = CMD_STOP;
        this->sock.writeDatagram(&cmd,1,QHostAddress(QString(SERVER_IP)),SERVER_PORT_CMD_SEND);
    }
}

void MainWindow::keyUp(QKeyEvent *e){
    qDebug() << "2";
    char cmd;
    if (e->key() == Qt::Key::Key_W){
        if(this->isW){
            this->isW = false;
            cmd = CMD_STOP;
            this->sock.writeDatagram(&cmd,1,QHostAddress(QString(SERVER_IP)),SERVER_PORT_CMD_SEND);
        }
    }
    else if (e->key() == Qt::Key::Key_A){
        this->isA = false;
        if(isW) cmd = CMD_FORWARD;
        else cmd = CMD_STOP;
        this->sock.writeDatagram(&cmd,1,QHostAddress(QString(SERVER_IP)),SERVER_PORT_CMD_SEND);
    }
    else if (e->key() == Qt::Key::Key_D && !e->isAutoRepeat()){
        this->isD = false;
        if(isW) cmd = CMD_FORWARD;
        else cmd = CMD_STOP;
        this->sock.writeDatagram(&cmd,1,QHostAddress(QString(SERVER_IP)),SERVER_PORT_CMD_SEND);
    }
    else if (e->key() == Qt::Key::Key_S && !e->isAutoRepeat()){
        cmd = CMD_STOP;
        this->sock.writeDatagram(&cmd,1,QHostAddress(QString(SERVER_IP)),SERVER_PORT_CMD_SEND);
    }
}

