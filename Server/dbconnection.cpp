#include "dbconnection.h"

bool DBConnection::connectDB(QString hostName,
                                        QString DBName,
                                        QString userName,
                                        QString password
                                        )
{
    m_hostName     = hostName ;
    m_dataBaseName = DBName;
    m_userName     = userName;
    m_password     = password;

    QSqlDatabase m_DB = QSqlDatabase::addDatabase("QMYSQL");
    m_DB.setHostName(m_hostName);
    m_DB.setDatabaseName(m_dataBaseName);
    m_DB.setUserName(m_userName);
    m_DB.setPassword(m_password);

    return m_DB.open() ? 1 : 0;
}

