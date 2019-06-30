#include "Connection.h"

Connection::Connection(qintptr handle, QObject *parent)
    : QTcpSocket(parent)
{
    setSocketDescriptor(handle);

    connect(this, &Connection::readyRead, [&]() {
        emit ReadyRead(this);
    });

    connect(this, &Connection::stateChanged, [&](int state) {
        emit StateChanged(this, state);
    });
}
