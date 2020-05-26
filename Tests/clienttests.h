#ifndef CLIENTTESTS_H
#define CLIENTTESTS_H

#include <QtTest/QtTest>
#include <QObject>

#include "../Client/client.h"

class ClientTests : public QObject
{
    Q_OBJECT
public:
    ClientTests();

private slots:
    void TestStartClient();
    void TestUserLogin();

    void TestSendMessege();
    void TestGetMessege();

    // todo();
    void TestGetLastMesseges();

public:
    Client testClientOne;
    Client testClientThree;
};

#endif // CLIENTTESTS_H
