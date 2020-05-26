#include <QCoreApplication>
#include "server.h"

int main(int argc, char *argv[])
{

    Server sv = Server(1234, "127.0.0.1", 2048, "Clients", "login", "password");

    sv.connectDB("localhost", "MessangerDB", "root", "123");
    sv.openSocket();
    sv.startServer();

    QCoreApplication a(argc, argv);
    return a.exec();
}
