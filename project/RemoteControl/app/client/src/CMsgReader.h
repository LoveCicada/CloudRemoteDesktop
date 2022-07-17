
#pragma once

/*
@brief CMsgReader - class for client read messages on the client side.
        (i.e. read messages from server to client).
        server params, and other.
*/

#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include <QImage>
#include <memory>

#include "../../../utils/include/Command.h"
#include "../../../utils/include/ServerParams.h"

using std::shared_ptr;
using std::make_shared;

class CMsgReader : public QThread
{
    Q_OBJECT

private:
    typedef shared_ptr<QTcpSocket> QTcpSocketPtr;
private:
    QTcpSocketPtr m_msgSocket;
    QString     m_address;
    int         m_port;
    bool        m_bSocketConnected;

    char  cmd_buf[msgProtocolLength];
    qint64 cmdReadLength;
    qint64 cmdLength;

public:
    ServerParmas m_serverParmas;
public:

    CMsgReader(QString add, int p, QObject *parent = 0);
    ~CMsgReader();

    void Init();
    void InitData();
    void processMsg();
    void readServerParamsMsg(CMDData& cmdData);
    
signals:
    void readServerParams(const ServerParmas& sp);
    
public slots:
    void connectError(QAbstractSocket::SocketError);
    void readMsgFromServer();
    void hostConnected();

protected:
    void run();
    
};

