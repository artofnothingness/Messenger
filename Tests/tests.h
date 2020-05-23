#ifndef TESTS_H
#define TESTS_H

#include <QtTest/QtTest>
#include <QObject>

#include "../Server/server.h"

class Tests : public QObject
{
    Q_OBJECT
public:
    Tests();

private slots:
    void TestServerSocket();
    void TestConnectionDB();
    void TestLoginDB();
    void TestRegistrationDB();
    void TestDropDB();
    void TestGetOnlineUsersDB();

private:
    Server testServer;

};
#endif // TESTS_H
