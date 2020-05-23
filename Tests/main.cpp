#include <QCoreApplication>
#include "tests.h"


int main(int argc, char *argv[])
{
    Tests test;
    QCoreApplication a(argc, argv);
    QTest::qExec(&test);
    return a.exec();
}
