#ifndef CONTROLER_H
#define CONTROLER_H

/*
@brief server process SMsgReader and SMsgWriter
        read msg from client
        write frame to client
*/

#include "SMsgHandler.h"
#include "SMsgWriter.h"
#include "SMsgReader.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QHostAddress>
#include <QObject>
#include <QVector>
#include <vector>
#include <memory>
#include <string>

using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::string;

typedef struct CallBackLog
{
    pfnLog logCb;
    void* pUser;
    int logLevel;

    CallBackLog()
    {
        logCb = nullptr;
        pUser = nullptr;
        logLevel = 0;
    }

}CallBackLog;

typedef struct SocketAndThread
{
    QTcpSocket* socket;
    QThread*  thread;

    SocketAndThread(QTcpSocket* st, QThread* th)
    {
        socket = st;
        thread = th;
    }

} SocketAndThread;

class SControler : public QObject
{
    Q_OBJECT

private:
    typedef shared_ptr<SocketAndThread> SocketAndThreadPtr;
    typedef vector<SocketAndThreadPtr> SocketAndThreadPtrVec;
    typedef shared_ptr<QTcpServer> QTcpServerPtr;

private:
    QTcpServerPtr m_pCmdServer;
    QTcpServerPtr m_pMapServer;
    SocketAndThreadPtrVec m_STPtrVec;

    //! callback log
    CallBackLog m_pCallBackLog;

public:
    const static int DATA_HEARER_MAP = 1;    //图像数据
    const static int DATA_HEADER_CMD = 2;    //命令数据
    const static int DATA_HEARER_RES = 3;    //命令结果数据

    const static int MAP_SERVER_PORT = 5648;
    const static int CMD_SERVER_PORT = 5649;

    explicit SControler(QObject *parent = 0);
    ~SControler();

public:
    //! log callback
    void SetLogCb(pfnLog logCb, void* pUser, int logLevel);
    void WriteCbLog(const string& str);
public slots:
    void newMapClient();
    void newCmdClient();
    void someSocketDisconnected();
};

#endif // CONTROLER_H
