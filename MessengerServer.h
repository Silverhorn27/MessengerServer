#ifndef MESSENGERSERVER_H
#define MESSENGERSERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include "Server.h"

namespace Ui {
class MessengerServer;
}

class MessengerSocket;

class MessengerServer : public QWidget
{
    Q_OBJECT

public:
    explicit MessengerServer(QWidget *parent = nullptr);
    ~MessengerServer();
    void start();

private slots:
    void startButton();
    void stopButton();
    void log(const QString &message);

private:
    Ui::MessengerServer *ui;
    Server *_tcpServer;
    quint16 _port;
};

#endif // MESSENGERSERVER_H
