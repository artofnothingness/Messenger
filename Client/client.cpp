#include "client.h"
#include <QString>
#include <QDebug>
#include <thread>

    Client::Client(QObject *parent) :
        QObject(parent) {}

    Client::~Client() {
        close(m_serverFD); }

    void Client::recvMessegesThr() {
        m_listenerThread = std::thread(&Client::recvMesseges, this);
    }

    void Client::recvMesseges() {
        while(true) {
            protocolMutex.lock();
            int bytes_read = recv(m_serverFD, m_recvBuff, m_bufLen, 0);
            protocolMutex.unlock();

            if (bytes_read < 0) {
                break;
            }
            m_lastMesseges.push_back(m_recvBuff, strlen( (char*) m_recvBuff)));
        }
    }

    bool Client::sendMessege(QString username, QString text) {
        QByteArray _userTo = username.toLatin1();
        QByteArray _userFrom = m_userName.toLatin1();
        QByteArray _text = text.toLatin1();
        QDateTime _date = QDateTime::currentDateTime();

        int bytes_send = 0;
        int bytes_recv = 0;
        bool status = false;

        protocolMutex.lock();
        bytes_send = send(m_serverFD, _userTo.data(), _userTo.size() + 1 , 0);
        if (bytes_send <= 0)
            return status;
        bytes_send = send(m_serverFD, _userFrom.data(), _userFrom.size() + 1 , 0);
        if (bytes_send <= 0)
            return status;
        bytes_send = send(m_serverFD, _text.data(), _text.size() + 1 , 0);
        if (bytes_send <= 0)
            return status;
        bytes_send = send(m_serverFD, &_date, sizeof(_date), 0);
        if (bytes_send <= 0)
            return status;

        bytes_recv = recv(m_serverFD, &status, sizeof(bool), 0);
        protocolMutex.unlock();

        return status;
    }

    bool Client::sendRequest(RequestType request)
    {
        RequestType _request = request;
        int bytes_send = send(m_serverFD, &_request, sizeof(_request), 0);

        if (bytes_send <= 0) {
            return false;
        }

        bool status = false;
        int bytes_recv = recv(m_serverFD, &status, sizeof(bool), 0);

        if (bytes_recv <= 0) {
            return false;
        }

        return status;
    }


    bool Client::start(int port, QString address) {
        QByteArray _addressData = address.toLatin1();
        char *_address = _addressData.data();

        m_socketInfo.sin_family = AF_INET;
        m_serverFD = socket(AF_INET, SOCK_STREAM, 0);
        m_socketInfo.sin_port = htons(port);
        m_socketInfo.sin_addr.s_addr = inet_addr(_address);

        int status = ::connect(m_serverFD, (struct sockaddr *)&m_socketInfo, sizeof(m_socketInfo));
        m_bufLen = 2048;

        struct timeval tv;

        tv.tv_sec = 0;
        tv.tv_usec = 400 * 50;
        setsockopt(m_serverFD, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

        m_recvBuff =  (void *) malloc(m_bufLen);
        m_messageBuff = new char(m_bufLen);




        return (status == 0);
    }

    bool Client::recvMessegesLast(QString username) {
//        int _vecSize = 0;
//        int _bytes_recv = recv(m_serverFD, &_vecSize, sizeof(int), 0);
//        if (_bytes_recv <= 0) { return false; }

//        vector<Messege> _lastMesseges(_vecSize);
//        if (_vecSize > 0) {
//            int _bytes_recv = recv(m_serverFD, &m_lastMesseges, sizeof(vector<Messege>(_vecSize)), 0);
//        }

//        if (_bytes_recv <=0 ) {
//            return false;
//        }
        return true;
    }

    bool Client::login(QString login, QString password)
    {

        bool isConnected = false;
        QByteArray _login = login.toLatin1();
        QByteArray _password = password.toLatin1();

        int bytes_send = send(m_serverFD, _login.data(), _login.size() + 1, 0);
        if (bytes_send <= 0)
            { return false; }
        else {
            int bytes_send = send(m_serverFD, _password.data(), _password.size() + 1, 0);
            int bytes_recv = recv(m_serverFD, &isConnected, sizeof(bool), 0);
            if ( (bytes_send <= 0) || (bytes_recv <= 0) || (isConnected == false) )
                { return false; }
        }
        return isConnected;
    }



