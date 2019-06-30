#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTcpSocket>

class Connection : public QTcpSocket
{
    Q_OBJECT
public:
    Connection(qintptr handle, QObject *parent = nullptr);

signals:
    void ReadyRead(Connection *);
    void StateChanged(Connection *, int);
};

#endif // CONNECTION_H
