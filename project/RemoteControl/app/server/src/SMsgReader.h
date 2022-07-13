#pragma once

/*
@brief SMsgReader - class for reading client command messages on the server side
        (i.e. messages from client to server).
        command msg: mouse, keyboard
*/

#include <QThread>

#include "Common.h"
#include "Command.h"
#include "ServerParams.h"

class QTcpSocket;

class SMsgReader : public RCThread
{
    Q_OBJECT

private:
    QTcpSocket*  m_pCmdSocket;
    ServerParmas m_ServerParmas;

    qint64 m_cmdMsgOffset;
    qint64 m_clientMsgLength;
    //! msg protocol length is 20 byte
    char   m_msgData[msgProtocolLength];             
    
public:
    explicit SMsgReader(QTcpSocket* socket, ServerParmas sp, QObject *parent = 0);
    ~SMsgReader();

    void Extend(void* param = nullptr) override;
signals:
    
public slots:
    void readSocketData();
    void readClientMsg();

    void cmdMouseMoveTo();
    void cmdMouseLeftDown();
    void cmdMouseLeftUp();
    void cmdMouseRightDown();
    void cmdMouseRightUp();
    void cmdMouseWheel();
    void cmdScreenSize();
    void cmdMouseDoubleClick();

    void cmdKeyPressed();
    void cmdKeyReleased();

protected:
    void run();
    
};

