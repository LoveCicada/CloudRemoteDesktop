#ifndef MAPTHREAD_H
#define MAPTHREAD_H

/*
@brief SMsgWriter - class for server send messages on the server side.
        (i.e. messages send client from server).
        server --> client
        command msg: mouse, keyboard
*/

#include <QThread>
#include <QTimer>
#include <QColor>
#include <QImage>
#include <QPixmap>

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
    SMsgWriter(QTcpSocket* socket, ServerParmas sp, QObject *parent = 0);
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
    void quit();

protected:
    void run();
    
};

#endif // MAPTHREAD_H
