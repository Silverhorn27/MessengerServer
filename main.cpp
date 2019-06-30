#include "MessengerServer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MessengerServer server;
    server.show();

    return app.exec();
}
