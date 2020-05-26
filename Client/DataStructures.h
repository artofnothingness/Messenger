#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H
#include <QString>
#include <QDateTime>
#include <map>

#define MAX_USERS 1000
#define BUF_LEN 2048

struct Messege {
    QString fromUser;
    QString toUser;
    QString text;
    QDateTime date;
};

struct User {
    QString login;
    QString password;
};


enum RequestType{
    Login,
    GetLastMesseges,
    SendMessege
};


struct UserInfo {
    QString loginName;
    char *buffer;
};

typedef std::map<int, UserInfo>::iterator UserInfoIt;
#endif // DATASTRUCTURES_H
