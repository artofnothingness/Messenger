#include "server.h"

#include <string.h>
#include <string>
#include <QString>
#include <sstream>

std::mutex dbMutex;
std::mutex protocolMutex;

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
    m_serverInfo.sin_family = AF_INET;
    m_serverInfo.sin_port = htons(PORT);
    m_serverInfo.sin_addr.s_addr=inet_addr(ADDR.c_str());

    m_clientTableName = clientTable;
    m_loginRowName = loginRow;
    m_passwordRowName = passwordRow;
    m_interupListening = false;
}

Server::~Server()
{
    close(m_FD);
}

UserLoginBufferIt Server::findUser(UserLoginBufferIt begin, UserLoginBufferIt end, char *value) {
    UserLoginBufferIt it;
    for (it = begin; it != end; ++it) {
        if (!::strcmp(it->second.name, value))
            return it;
    }
    return it;
}


bool Server::openSocket() {
    int status;
    m_FD = socket(AF_INET, SOCK_STREAM, 0);
    if  (m_FD == -1) { return false; }
    status = bind(m_FD, (struct sockaddr *) &m_serverInfo, sizeof(m_serverInfo));
    if (status != 0) { return false; }
    status = listen(m_FD, MAX_USERS);
    if (status != 0) { return false; }
    return true;
}

void Server::startServer()
{
    vector<future<void>> futures;
    while (true && !m_interupListening) {
        int clientFD = accept(m_FD, NULL, NULL);
        futures.push_back(async(std::launch::async, &Server::startListenRequests, this, clientFD));
    }
}

QSqlDatabase Server::openDb()
{
    thread::id _thisThrID = this_thread::get_id();
    stringstream _ss;
    _ss << _thisThrID;
    QString _dbName = QString::fromStdString(_ss.str());

    QSqlDatabase _currClientDBConnection = QSqlDatabase::addDatabase("QMYSQL", _dbName);
    _currClientDBConnection.setHostName(m_hostName);
    _currClientDBConnection.setDatabaseName(m_dataBaseName);
    _currClientDBConnection.setUserName(m_userName);
    _currClientDBConnection.setPassword(m_password);
    return _currClientDBConnection;
}


void Server::startListenRequests(int fd) {
    QSqlDatabase connection = openDb();
    int _status;
    if (!connection.open()) { return; }

    while (true) {
        RequestType _requset;
        _status = recv(fd, &_requset,  sizeof(_requset) , 0);

        if (_status <= 0) {
            m_connectedUsers.erase(fd);
            break;
        }

        if (_requset == Login) {
            int status = loginRequestHandler(fd, connection);
            send(fd, &status, sizeof(bool), 0);
        } else if (_requset == SendMessege) {

        } else if (_requset == GetLastMesseges) {

        }
    }
    close(fd);
}

bool Server::loginRequestHandler(int fd, QSqlDatabase &connection) {
    UserLoginBufferIt _connected = m_connectedUsers.find(fd);
    if (_connected != m_connectedUsers.end())
        return false;

    UserLoginBuffer _user;
    _user.name = new char(m_bufLen);
    _user.password = new char(m_bufLen);
    QString _name = QString::fromUtf8(_user.name);
    QString _password = QString::fromUtf8(_user.password);

    int byte_recv = recv(fd, &_user.name, sizeof(m_bufLen), 0);
    if (byte_recv <= 0)
        return false;

    UserLoginBufferIt _loggined = findUser(m_connectedUsers.begin(),
                                           m_connectedUsers.end(),
                                           _user.name);

    if (_loggined != m_connectedUsers.end())
        return false;

    byte_recv = recv(fd, &_user.password, sizeof(m_bufLen), 0);
    if (byte_recv <= 0)
        return false;

    if (!login(_name, _password, connection))
        return false;

    return true;
}

bool Server::sendMessegeRequestHandler(int fd, QSqlDatabase &connection)
{
        char * _userTo = new char(m_bufLen);
        char *_userFrom = new char(m_bufLen);
        char *_text = new char(m_bufLen);
        QDateTime _date = QDateTime::currentDateTime();

        int bytes_recv = 0;
        int bytes_send = 0;
        bool status = false;

        bytes_send = recv(fd, _userTo, m_bufLen, 0);
        if (bytes_recv <= 0)
            return status;
        bytes_send = recv(fd, _userFrom, m_bufLen, 0);
        if (bytes_recv <= 0)
            return status;
        bytes_send = recv(fd, _text , m_bufLen, 0);
        if (bytes_recv <= 0)
            return status;

        if (findUser(m_connectedUsers.begin(),
                     m_connectedUsers.end(),
                     _userTo) != m_connectedUsers.end()) {
        }

        bytes_send = send(m_serverFD, &_date, sizeof(_date), 0);
        if (bytes_recv <= 0)
            return status;

        bytes_recv = recv(m_serverFD, &status, sizeof(bool), 0);

        return status;
}

bool Server::login(QString login, QString password,
                   QSqlDatabase &currThrDbConnection) {
    dbMutex.lock();
        QString queryString = QString("SELECT * FROM %3 WHERE %4='%1' AND %5='%2'")
                .arg(login)
                .arg(password)
                .arg(m_clientTableName)
                .arg(m_loginRowName)
                .arg(m_passwordRowName);
        QSqlQuery query(queryString, currThrDbConnection); query.next();
     dbMutex.unlock();

    return query.isValid();
}


bool Server::registrate(QString login, QString password, QSqlDatabase &currThrDbConnection) {
    bool status;
    QSqlQuery query(currThrDbConnection);
    query.prepare(QString("INSERT INTO %1 (%2, %3) "
                  "VALUES (:login, :password)").arg(m_clientTableName).arg(m_loginRowName).arg(m_passwordRowName));

    query.bindValue(":login", login);
    query.bindValue(":password", password);

    dbMutex.lock();
        status = query.exec();
    dbMutex.unlock();

    return status;
}
bool Server::drop(QString login, QSqlDatabase &currThrDbConnection) {
    bool status;
    QSqlQuery query(currThrDbConnection);

    query.prepare(QString("DELETE FROM %1 WHERE %2 = '%3'")
                          .arg(m_clientTableName).arg(m_loginRowName).arg(login));
    dbMutex.lock();
        status = query.exec();
    dbMutex.unlock();

    return status;
}

bool Server::insertMessegeDb(QString messege, QString fromUserName, QString toUserName, QSqlDatabase &currThrDbConnection)
{
    bool status;
    QSqlQuery query(currThrDbConnection);

    query.prepare(QString("INSERT INTO %1 (%2, %3, %4 %5) "
                  "VALUES (:text, :data, :fromUser, :toUser)")
                  .arg("Messeges").arg("Text").arg("Data").arg("FromUser").arg("ToUser"));

    query.bindValue(":text", messege);
    query.bindValue(":data", QDateTime::currentDateTime());
    query.bindValue(":fromUser", fromUserName);
    query.bindValue(":toUser", toUserName);

    dbMutex.lock();
        status = query.exec();
    dbMutex.unlock();

    return status;
}

vector<Messege> Server::getLastMessegesDb(
        QString fromUserName, QString toUserName, QSqlDatabase &currThrDbConnection)
{
    vector<Messege> _messeges;
    dbMutex.lock();
        QString queryString = QString("SELECT * FROM %3 WHERE %4='%1' AND %5='%2' ORDER BY Data DESC limit 10")
                .arg(fromUserName).arg(toUserName)
                .arg("Messeges")
                .arg("FromUser")
                .arg("ToUser");
        QSqlQuery query(queryString, currThrDbConnection);
    dbMutex.unlock();

    int fieldText = query.record().indexOf("Text");
    int fieldDate = query.record().indexOf("Data");

    while (query.next()) {
        QString _text = query.value(fieldText).toString();
        QDateTime _date = query.value(fieldDate).toDateTime();
        Messege _currMessege = Messege();
        _currMessege.text = _text;
        _currMessege.date = _date;
        _currMessege.fromUser = fromUserName;
        _currMessege.fromUser = fromUserName;
        _messeges.push_back(_currMessege);
    }

    return _messeges;
}
