#include "server.h"
#include <QDebug>

using namespace std;
Server::Server(
               int PORT,
               string ADDR,
               int BUFLEN,
               QString clientTable,
               QString loginRow,
               QString passwordRow) :

                                        m_bufLen(BUFLEN)
{
    m_FD = socket(AF_INET, SOCK_STREAM, 0);
    m_serverInfo.sin_family = AF_INET;
    m_serverInfo.sin_port = htons(PORT);
    m_serverInfo.sin_addr.s_addr=inet_addr(ADDR.c_str());

    m_clientTableName = clientTable;
    m_loginRowName = loginRow;
    m_passwordRowName = passwordRow;
}

Server::~Server()
{
    close(m_FD);
}

UserInfoIt Server::findUserByValue(UserInfoIt begin, UserInfoIt end, char *value) {
    UserInfoIt it;
    for (it = begin; it != end; ++it) {
        if (!::strcmp(it->second.buffer, value))
            return it;
    }
    return it;
}


bool Server::establishConnection() {
    int status;
    status = bind(m_FD, (struct sockaddr *) &m_serverInfo, sizeof(m_serverInfo));
    if (status != 0) { return false; }
    status = listen(m_FD, MAX_USERS);
    if (status != 0) { return false; }
    return true;
}

void Server::startListening()
{
    vector<future<void>> futures;
    while (true) {
        int clientFD = accept(m_FD, NULL, NULL);
        futures.push_back(async(std::launch::async, &Server::listenClientThread, this, clientFD));
    }
}


void Server::listenClientThread(int fd) {
    int _bytesRead = 0;
    char *_login = nullptr;
    char *_text = nullptr;
    char *_buffer = nullptr;
    bool _status = false;

    while (true) {
        _bytesRead = 0;
        _login = nullptr;
        _text = nullptr;
        if (_buffer == nullptr) {
            _buffer = new char(m_bufLen);
        }
        _status = false;

        _bytesRead = recv(fd, _buffer,  m_bufLen , 0);
        if (_bytesRead <= 0) {
            printf("Sender on sock %d unreachable\n", fd);
            continue;
        }

        sscanf(_buffer, "%s", _login);
        _text = strchr(_buffer, ' ') + 1;

        UserInfoIt _userIt = m_connectedUsers.find(fd);
        if (_userIt == m_connectedUsers.end()) {
            if (login(_login, _text)) {
                m_connectedUsers[fd] = UserInfo( {QString::fromUtf8(_login), _buffer} );
                _buffer = nullptr;
                _status = true;
                send(fd, (void *)_status, sizeof(bool), 0);
            } else {
                send(fd, (void *)_status, sizeof(bool), 0);
                continue;
            }
        } else {
            UserInfoIt _recvUserIt = findUserByValue(m_connectedUsers.begin(), m_connectedUsers.end(), _login);
            if (_recvUserIt != m_connectedUsers.end()) {
                send(_recvUserIt->first, _text, sizeof(_text) + 1, 0);
            }
        }
    }
    close(fd);
}

bool Server::login(QString login, QString password) {
    QString queryString = QString("SELECT * FROM %3 WHERE %4='%1' AND %5='%2'").arg(login).arg(password)
            .arg(m_clientTableName)
            .arg(m_loginRowName)
            .arg(m_passwordRowName);
    QSqlQuery query(queryString);
    query.next();
    return query.isValid();
}


bool Server::registrate(QString login, QString password) {
        bool status;
        QSqlQuery query;
        query.prepare(QString("INSERT INTO %1 (%2, %3) "
                      "VALUES (:login, :password)").arg(m_clientTableName).arg(m_loginRowName).arg(m_passwordRowName));

        query.bindValue(":login", login);
        query.bindValue(":password", password);
        status = query.exec();
        return status;
}

bool Server::drop(QString login) {
        bool status;
        QSqlQuery query;

        query.prepare(QString("DELETE FROM %1 WHERE %2 = '%3'")
                              .arg(m_clientTableName).arg(m_loginRowName).arg(login));
        status = query.exec();
        return status;
}

vector<QString> Server::getOnlineUsers()
{
    vector<QString> userNames;
    for (auto it = m_connectedUsers.begin(); it != m_connectedUsers.end(); ++it) {
        userNames.push_back(it->second.loginName);
    }
    return userNames;
}

