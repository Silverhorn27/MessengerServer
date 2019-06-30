#include "MessengerServer.h"
#include "ui_MessengerServer.h"
#include <QDateTime>

MessengerServer::MessengerServer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MessengerServer)
{
    ui->setupUi(this);
    ui->logEdit->setReadOnly(true);
    ui->startButton->setDefault(true);
    setWindowTitle("Server");
    _tcpServer = new Server(this);
    connect(ui->startButton, &QPushButton::clicked, this, &MessengerServer::startButton);
    connect(ui->stopButton, &QPushButton::clicked, this, &MessengerServer::stopButton);
    connect(_tcpServer, &Server::logServer, this, &MessengerServer::log);
}

MessengerServer::~MessengerServer()
{
    delete ui;
}

void MessengerServer::start()
{
    if (!_tcpServer->start(_port)) {
        log("Error! The server did not start. " + _tcpServer->errorString());
        _tcpServer->close();
    }
    log("Server started");
}

void MessengerServer::log(const QString &message)
{
    QString logMessage = QDateTime::currentDateTime().toString("hh:mm:ss  ") + message;
    ui->logEdit->append(logMessage);
}

void MessengerServer::startButton()
{
    if (ui->portSpinBox->value() < 1000) {
        QMessageBox::critical(nullptr, "Server Error", "Port are incorrect!");
        log("Error! The server did not start");
        return;
    }

    _port = static_cast<quint16>(ui->portSpinBox->value());
    MessengerServer::start();
}

void MessengerServer::stopButton()
{
    _tcpServer->close();
    log("Server stopped");
}
