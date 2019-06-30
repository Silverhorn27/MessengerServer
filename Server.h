#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>

class Connection;

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server(QObject *parent = nullptr);
    bool start(quint16 port);

protected:
    void incomingConnection(qintptr handle) override;

private slots:
    void readyReadSocket(Connection *socket);
    void changedStateSocket(Connection *socket, int state);

signals:
    void logServer(QString);

private:
    QList<Connection *> _connections;
};

#endif // SERVER_H
