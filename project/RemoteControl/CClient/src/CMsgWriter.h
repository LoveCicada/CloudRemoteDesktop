#ifndef CMDTHREAD_H
#define CMDTHREAD_H

/*
@brief CMsgWriter - class for send client command messages on the client side
        (i.e. writer messages from client to server).
        client params
        command msg: mouse, keyboard
*/

#include <QThread>
#include <QTcpSocket>
#include <QMetaType>
#include <memory>
#include "RWSocket.h"
#include "Command.h"

using std::shared_ptr;
using std::make_shared;

class CMsgWriter : public QObject
{
    Q_OBJECT

private:
    typedef shared_ptr<QTcpSocket> QTcpSocketPtr;
private:
    QTcpSocketPtr m_msgSocket;
    QString     m_address;
    int         m_port;
    bool socketConnected;

    char cmd_buf[msgProtocolLength];
    CMDData m_cmdData;

    int   cmd_buf_fill;
public:
    CMsgWriter(QString add, int p, QObject* parent = 0);
    void connectToServer();
    void reconnectToServer();


signals:
    void setServerScreenSize(int, int);
    
public slots:
    void connectError(QAbstractSocket::SocketError);
    void connectSucceed();
    void readDataFromServer();
    void readServerMsg();
    void cmdMouseMoveTo(int x, int y);
    void cmdMouseLeftDown(int x, int y);
    void cmdMouseLeftUp(int x, int y);
    void cmdMouseRightDown(int x, int y);
    void cmdMouseRightUp(int x, int y);
    void cmdMouseWheel(int delta, int x, int y);
    void cmdScreenSize();
    void cmdMouseDoubleClick(int x, int y);

    void cmdKeyPress(int32_t key, int32_t scanCode, int32_t virtualKey, int32_t modifier);
    void cmdKeyRelease(int32_t key, int32_t scanCode, int32_t virtualKey, int32_t modifier);


    void run();
    
};


#endif // CMDTHREAD_H
