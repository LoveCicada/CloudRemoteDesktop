
#pragma once

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
    QTcpSocketPtr   m_msgSocket;
    QString         m_address;
    int             m_port;
    bool            m_bSocketConnected;

    char            m_msgData[msgProtocolLength];
    CMDData         m_cmdData;

    int   m_msgOffsetLength;
public:
    CMsgWriter(QString add, int p, QObject* parent = 0);
    ~CMsgWriter();

    void connectToServer();
    void reconnectToServer();
    void start();

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

public:
    //! filter special keyboard event
    void filterSpMsg(CMDTYPE cmdType);

    //! alt left + tab
    void cmdKeySpAltLTab();
    //! alt left + tab
    void cmdKeySpAltRTab();
    //! win + L/l
    void cmdKeySpWinL();

};
