#include "servertests.h"

ServerTests::ServerTests() :
    testServer(1234, "127.0.0.1", 2048, "Clients", "login", "password") {
}

void ServerTests::TestConnectionDB()
{
    QVERIFY(testServer.connectDB("localhost", "MessangerDB", "root", "123"));
}

void ServerTests::TestSocket()
{
    QVERIFY(testServer.openSocket());
}

void ServerTests::TestLoginUserDB()
{
    QVERIFY(testServer.login("user2", "123", testServer.m_DB));
}

void ServerTests::TestDropUserDB()
{
    QVERIFY(testServer.drop("user2", testServer.m_DB));
}

void ServerTests::TestGetMesseges()
{
    QVERIFY(testServer.getLastMessegesDb("user1", "user3", testServer.m_DB).back().fromUser == "user1");
    QVERIFY(testServer.getLastMessegesDb("user3", "user1", testServer.m_DB).back().toUser == "user1");

    QVERIFY(testServer.getLastMessegesDb("user3", "user1", testServer.m_DB).back().fromUser == "user3");
    QVERIFY(testServer.getLastMessegesDb("user1", "user3", testServer.m_DB).back().toUser == "user3");
}

void ServerTests::TestRegistrationUserDB()
{
    QVERIFY(testServer.registrate("user2", "123", testServer.m_DB));
}



