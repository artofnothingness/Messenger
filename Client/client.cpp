#include <client.h>

    Client::Client(QObject *parent) :
        QObject(parent) {
    }


    // TO DO
    QString Client::getMessageFromUser() {
        recv(m_serverFD, m_recvBuff, m_bufLen, 0);
        QString retMess = QString::fromUtf8(m_recvBuff);
        return retMess;
    }


    bool Client::sendMessageToUser(QString username, QString text) {
        char *_textPtr = text.toLatin1().data();
        char *_userNamePtr = username.toLatin1().data();

        size_t _usernameSize = username.size();
        size_t _messageSize = text.size();

        size_t _shift;
        ::strncpy(m_messageBuff, _userNamePtr, _usernameSize);
         _shift = _usernameSize;
        m_messageBuff[_shift] = ' ';
        _shift += 1;
        ::strncpy(m_messageBuff + _shift, _textPtr, _messageSize);
        _shift += _messageSize;
        m_messageBuff[_shift] = '\0';

        int bytes_send = send(m_serverFD, m_messageBuff, strlen(m_messageBuff) + 1, 0);
        return (bytes_send <= 0);
    }


    bool Client::startClient(int port, QString address) {
        m_socketInfo.sin_family = AF_INET;
        m_serverFD = socket(AF_INET, SOCK_STREAM, 0);
        m_socketInfo.sin_port = htons(port);
        m_socketInfo.sin_addr.s_addr = inet_addr(address.toLatin1().data());

        int status = ::connect(m_serverFD, (struct sockaddr *)&m_socketInfo, sizeof(m_socketInfo));

        m_recvBuff = new char(m_bufLen);
        m_messageBuff = new char(m_bufLen);

        m_bufLen = 2048;

        return (status == 0);
    }

    bool Client::userLogin(QString login, QString password)
    {
        char *_loginPtr = login.toLatin1().data();
        char *_passwordPtr = password.toLatin1().data();

        size_t _loginSize = login.size();
        size_t _passwordSize = password.size();

        size_t _shift;
        ::strncpy(m_messageBuff, _loginPtr, _loginSize);
         _shift = _loginSize;
        m_messageBuff[_shift] = ' ';
        _shift += 1;
        ::strncpy(m_messageBuff + _shift, _passwordPtr, _passwordSize);
        _shift += _passwordSize;
        m_messageBuff[_shift] = '\0';

        int bytes_send = send(m_serverFD, m_messageBuff, strlen(m_messageBuff) + 1, 0);
        if (bytes_send <= 0) {
            return false;
        } else {
            int bytes_recv = recv(m_serverFD, m_recvBuff, m_bufLen, 0);
            if (bytes_recv <= 0)
            {
                return false;
            } else {
                bool isConnected = static_cast<bool>(m_recvBuff);
                if (isConnected) {
                     m_isLogged = true;
                     m_login = login;
                     return true;
                } else {
                    return false;
                }
            }
        }
    }



