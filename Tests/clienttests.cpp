#include "clienttests.h"
#include "QString"

ClientTests::ClientTests():
    testClientOne(),
    testClientThree()
{}

void ClientTests::TestStartClient()
{
    QVERIFY(testClientOne.start(1234, "127.0.0.1"));
    QVERIFY(testClientThree.start(1234, "127.0.0.1"));
}

void ClientTests::TestUserLogin()
{
    QVERIFY(testClientOne.login("user1", "123"));
    QVERIFY(testClientThree.login("user3", "123"));
}


void ClientTests::TestSendMessege()
{
    testClientOne.recvMessegesThr();
    testClientThree.recvMessegesThr();

    QVERIFY(testClientOne.sendMessege("user3", "Hellow user 3"));
    QVERIFY(testClientThree.sendMessege("user1", "Hellow user 1"));
    sleep(1);
}

void ClientTests::TestGetMessege()
{
    QVERIFY(testClientOne.m_lastMesseges.back().text == QString("Hellow user1"));
    QVERIFY(testClientThree.m_lastMesseges.back().text == QString("Hellow user3"));
}
