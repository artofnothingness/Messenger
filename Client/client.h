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
#include <string.h>
#include <utility>
#include <vector>
#include <cstring>

#include <QObject>
#include <QString>
#include <QDateTime>
#include "DataStructures.h"

std::mutex protocolMutex;

using namespace std;

class Client : public QObject {
    Q_OBJECT

public:
    explicit Client(QObject *parent = 0);
    ~Client();
    bool start(int port, QString address); // OK
    bool login(QString login, QString password); // NOT DONE

    void recvMesseges(); //  NOT DONE
    void recvMessegesThr(); // OK
    bool recvMessegesLast(QString fromUserName); // NOT DONE
    bool sendMessege(QString username, QString message); //TESTING

    bool sendRequest(RequestType request);

private:
    int                 m_serverFD;
    int                 m_clientFD;
    struct sockaddr_in  m_socketInfo;

    char               *m_messageBuff;
    void               *m_recvBuff;
    int                 m_bufLen;

    bool                m_isLogged;
    QString             m_userName;

public:
    std::thread         m_listenerThread;
    vector<Messege>     m_lastMesseges;
};






