#include "tests.h"

Tests::Tests() : testServer(1234, "127.0.0.1", 2048, "Clients", "login", "password") {}

void Tests::TestServerSocket()
{
    QVERIFY(testServer.establishConnection());
}

void Tests::TestConnectionDB()
{
    QVERIFY(testServer.connectDB("localhost", "MessangerDB", "root", "123"));
}

void Tests::TestLoginDB()
{
    QVERIFY(testServer.login("user1", "123"));
}

void Tests::TestDropDB()
{
    QVERIFY(testServer.drop("user2"));
}


void Tests::TestRegistrationDB()
{
    QVERIFY(testServer.registrate("user2", "123"));
}

void Tests::TestGetOnlineUsersDB()
{
    QCOMPARE(testServer.getOnlineUsers().size(), testServer.m_connectedUsers.size());
}
