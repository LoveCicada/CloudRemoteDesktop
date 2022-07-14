#pragma once

/*
@brief SMsgWriter - class for server send messages on the server side.
        (i.e. messages send client from server).
        server --> client
        command msg: mouse, keyboard
*/

#include <QThread>
#include "Common.h"
#include "Command.h"
#include "ServerParams.h"

class QTcpSocket;

class SMsgWriter : public RCThread
{
    Q_OBJECT

private:

    ServerParmas m_serverParmas;
    char m_msgData[msgProtocolLength];
    
    //! send server msg to client, like server parmas.
    QTcpSocket* m_msgSocket;

public:
    explicit SMsgWriter(QTcpSocket* socket, ServerParmas sp, QObject *parent = 0);
    ~SMsgWriter();
    void Extend(void* param = nullptr) override;

    void Init();
    void InitData();
public:
    bool checkConnect();
    void sendServerParams();
    void sendMsgToClient();
    
signals:
    
public slots:
    void readMsgFromClient();

protected:
    void run() override;
    void quit();
};

