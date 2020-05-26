#ifndef TESTS_H
#define TESTS_H

#include <QtTest/QtTest>
#include <QObject>

#include "../Server/server.h"

class ServerTests : public QObject
{
    Q_OBJECT
public:
    ServerTests();

private slots:
    void TestSocket();
    void TestConnectionDB();

    void TestRegistrationUserDB();
    void TestLoginUserDB();
    void TestDropUserDB();

    void TestGetMesseges();

public:
    Server testServer;
};
#endif // TESTS_H
