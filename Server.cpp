#include "Server.h"
#include "Connection.h"

Server::Server(QObject *parent)
    : QTcpServer(parent)
{

}

bool Server::start(quint16 port)
{
    return listen(QHostAddress::Any, port);
}

void Server::incomingConnection(qintptr handle)
{
    emit logServer("Connected new client");
    auto socket = new Connection(handle, this);
    _connections << socket;

    for (auto socket : _connections) {
        QTextStream stream(socket);
        stream << "Connected new client: " << handle;
        socket->flush();
    }

    connect(socket, &Connection::ReadyRead, this, &Server::readyReadSocket);
    connect(socket, &Connection::StateChanged, this, &Server::changedStateSocket);
}

void Server::readyReadSocket(Connection *socket)
{
    emit logServer("ReadyRead");
    QTextStream out(socket);
    auto text = out.readAll();

    for (auto socket : _connections) {
        QTextStream in(socket);
        in << text;
        socket->flush();
    }
}

void Server::changedStateSocket(Connection *socket, int state)
{
    if (state == QTcpSocket::UnconnectedState) {
        emit logServer("Unconnected one client");
        _connections.removeOne(socket);
        for (auto socket : _connections) {
            QTextStream in(socket);
            in << "Server: Client disconnected...";
            socket->flush();
        }
    }
}
