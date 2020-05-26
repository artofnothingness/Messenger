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


enum RequestType{
    Login,
    GetLastMesseges,
    SendMessege
};


struct UserLoginBuffer {
    char *name;
    char *password;
};

typedef std::map<int, UserLoginBuffer>::iterator UserLoginBufferIt;

#endif // DATASTRUCTURES_H
