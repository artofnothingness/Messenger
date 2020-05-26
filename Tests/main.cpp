#include <QCoreApplication>
#include "servertests.h"
 #include "clienttests.h"

int main(int argc, char *argv[])
{
    ServerTests serverTests;
    ClientTests clientTests;

    QCoreApplication a(argc, argv);

    QTest::qExec(&serverTests);

    future<void> testListening = async(std::launch::async, &Server::startSocket, &serverTests.testServer);

    QTest::qExec(&clientTests);

    QTest::qCleanup();
    return a.exec();
}
