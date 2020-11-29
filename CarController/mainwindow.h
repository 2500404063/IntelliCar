#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QHostAddress>

#define SERVER_PORT_CMD_SEND 9000
#define SERVER_PORT_CMD_RECV 9100
#define CMD_FORWARD          0x21
#define CMD_LEFT             0x22
#define CMD_RIGHT            0x23
#define CMD_RUNL             0x24
#define CMD_RUNR             0x25
#define CMD_STOP             0x26

#define SERVER_IP            "192.168.100.6"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool isW = false;
    bool isA = false;
    bool isD = false;
    QUdpSocket sock;

private slots:
    void keyDown(QKeyEvent *e);
    void keyUp(QKeyEvent *e);
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
