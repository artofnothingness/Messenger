#ifndef SERVER_H
#define SERVER_H

#include <future>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <utility>

#include <string>
#include <vector>
#include <map>
#include <cstring>
#include <algorithm>

#include <QVariant>
#include <QObject>
#include <QDateTime>

#include "dbconnection.h"
#include "DataStructures.h"

using namespace std;


class Server : public DBConnection  {
public:
    explicit Server(
           int PORT, string ADDR, int BUFLEN,
           QString clientTable, QString loginRow, QString passwordRow);
    ~Server();

    bool openSocket(); // OK
    void startServer(); // OK
    void startListenRequests(int fd); // NOT DONE

    // REQUESTS
    bool loginRequestHandler(int fd , QSqlDatabase &connection); // TESTING LOGIN
    bool sendMessegeRequestHandler(int fd, QSqlDatabase &connection); // NOT DONE


    // DATABASE
    QSqlDatabase    openDb(); // OK
    vector<Messege> getLastMessegesDb(QString fromUserName, QString toUserName,
                                      QSqlDatabase &connection); // TESTING
    bool            insertMessegeDb(QString messege, QString fromUserName,
                                    QString toUserName, QSqlDatabase &connection); // OK CAN BE MOD
    bool            login(QString login, QString password, QSqlDatabase &connection); //OK
    bool            registrate(QString login, QString password, QSqlDatabase &connection); //OK
    bool            drop(QString login, QSqlDatabase &connection); //OK

    static UserLoginBufferIt findUser(UserLoginBufferIt begin, UserLoginBufferIt end, char *value); //OK

    int                 m_FD;
    int                 m_bufLen;
    bool                m_interupListening;
    map <int, UserLoginBuffer> m_connectedUsers;
    struct sockaddr_in  m_serverInfo;
    QString             m_clientTableName;
    QString             m_loginRowName;
    QString             m_passwordRowName;
};

#endif // SERVER_H
