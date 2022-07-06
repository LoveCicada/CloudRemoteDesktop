#ifndef MAPTHREAD_H
#define MAPTHREAD_H

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
#include "Command.h"
#include "ServerParams.h"

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
    bool socketConnected;

    int request_width;
    int request_height;

    int    frame_buf_fill;
    int    frame_bytes;
    unsigned char  cmd_buf[8];
    qint64 cmdReadLength;
    qint64 cmdLength;

    bool frame_size_setted;

    int subX;
    int subY;
    int subWidth;
    int subHeight;
    int subSize;
    int subFill;

public:
    int received_frame_width;
    int received_frame_height;
    QImage* image;
    ServerParmas m_serverParmas;
public:

    CMsgReader(QString add, int p, int w, int h, QObject *parent = 0);
    ~CMsgReader();

    void Init();
    void InitData();
    void processMsg();
    void readServerParamsMsg(CMDData& cmdData);
    
signals:
    void readServerParams(const ServerParmas& sp);
    void frameGot(QImage*);
    void frameSizeChanged(int, int);
    
public slots:
    void connectError(QAbstractSocket::SocketError);
    void readMsgFromServer();
    void hostConnected();

protected:
    void run();
    
};

#endif // MAPTHREAD_H
