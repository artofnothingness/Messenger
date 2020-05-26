#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>

class DBConnection
{
public:
    DBConnection() = default;
    bool connectDB(QString hostName,
                         QString DBName,
                         QString userName,
                         QString password);

public:
QSqlDatabase m_DB;
QString m_hostName;
QString m_dataBaseName;
QString m_userName;
QString m_password;

};

#endif // DBCONNECTION_H
