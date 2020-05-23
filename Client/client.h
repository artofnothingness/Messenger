#include <algorithm>
#include <cstdio>
#include <thread>
#include <future>

#include <sys/socket.h>
#include <netinet/in.h>
#include <type_traits>
#include <unistd.h>
#include <arpa/inet.h>

#include <string>
#include <utility>
#include <vector>
#include <cstring>
#include <string.h>

#include <QObject>
#include <QString>

using namespace std;


class Client : public QObject {
    Q_OBJECT

public:
    explicit Client(QObject *parent = 0);
    bool startClient(int port, QString address);

    bool userLogin(QString login, QString password);
    // void getActiveUsers();

    bool sendMessageToUser(QString username, QString message);
    QString getMessageFromUser();


private:
    int m_serverFD;
    struct sockaddr_in m_socketInfo;

    char *m_messageBuff;
    char *m_recvBuff;
    int m_bufLen;

    bool m_isLogged;
    QString m_userName;
};






