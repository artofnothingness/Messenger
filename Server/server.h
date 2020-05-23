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

#include "dbconnection.h"

using namespace std;

#define MAX_USERS 1000

struct UserInfo {
    QString loginName;
    char *buffer;
};

typedef std::map<int, UserInfo>::iterator UserInfoIt;


class Server : public DBConnection  {

public:
    explicit Server( int PORT, string ADDR, int BUFLEN,
           QString clientTable, QString loginRow, QString passwordRow);

    ~Server();
    bool establishConnection();
    void startListening();

    void listenClientThread(int fd);
    static UserInfoIt findUserByValue(UserInfoIt begin, UserInfoIt end, char *value);

    //Query based
    bool login(QString login, QString password);
    bool registrate(QString login, QString password);
    bool drop(QString login);
    vector<QString> getOnlineUsers();

    map <int, UserInfo> m_connectedUsers;
private:
    struct sockaddr_in m_serverInfo;
    int m_FD;
    uint32_t m_bufLen;
    QString m_clientTableName;
    QString m_loginRowName;
    QString m_passwordRowName;
};

#endif // SERVER_H
