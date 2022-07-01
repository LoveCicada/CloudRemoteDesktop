#include "SControler.h"

SControler::SControler(QObject *parent) :
    QObject(parent)
{
    m_pMapServer = make_shared<QTcpServer>(new QTcpServer);
    m_pMapServer->listen(QHostAddress::Any, MAP_SERVER_PORT);
    qDebug()<<"map server listening"<<endl;
    connect(m_pMapServer.get(), SIGNAL(newConnection()), this, SLOT(newMapClient()));

    m_pCmdServer = make_shared<QTcpServer>(new QTcpServer);
    m_pCmdServer->listen(QHostAddress::Any, CMD_SERVER_PORT);
    qDebug()<<"cmd server listening"<<endl;
    connect(m_pCmdServer.get(), SIGNAL(newConnection()), this, SLOT(newCmdClient()));

}

SControler::~SControler()
{
    qDebug() << __func__;
}

  /*
  * when have a new connect, start a new thread process
  */
void SControler::newMapClient()
{
    QTcpSocket* pClientMapSocket = m_pMapServer->nextPendingConnection();
    qDebug()<<"new map connection:"<<pClientMapSocket->peerAddress().toString()<<endl;

    {
        string str = "new map connection: " +
            pClientMapSocket->peerAddress().toString().toStdString();
        WriteCbLog(str);
    }

    SMsgWriter* pMapThread = new SMsgWriter(pClientMapSocket);
    connect(pClientMapSocket, SIGNAL(disconnected()), this, SLOT(someSocketDisconnected()));

    SocketAndThreadPtr pSt(new SocketAndThread(pClientMapSocket, pMapThread));
    m_STPtrVec.emplace_back(pSt);

    pMapThread->start();
}

void SControler::newCmdClient()
{
    QTcpSocket* pClientCmdSocket = m_pCmdServer->nextPendingConnection();
    qDebug()<<"new cmd connection:"<< pClientCmdSocket->peerAddress().toString()<<endl;

    {
        string str = "new cmd connection: " +
            pClientCmdSocket->peerAddress().toString().toStdString();
        WriteCbLog(str);
    }

    SMsgReader* pCmdThread = new SMsgReader(pClientCmdSocket);
    connect(pClientCmdSocket, SIGNAL(disconnected()), this, SLOT(someSocketDisconnected()));

    SocketAndThreadPtr pSt(new SocketAndThread(pClientCmdSocket, pCmdThread));
    m_STPtrVec.emplace_back(pSt);

    pCmdThread->start();
}

void SControler::someSocketDisconnected()
{
    auto itor = m_STPtrVec.begin();
    for (; itor != m_STPtrVec.end(); )
    {
        auto pSocket = itor->get()->socket;
        auto state = pSocket->state();
        if (QAbstractSocket::UnconnectedState == state)
        {
            if (pSocket->isOpen())
            {
                pSocket->close();
            }

            auto pThread = itor->get()->thread;
            pThread->quit();
            connect(pThread, SIGNAL(finished()), pThread, SLOT(deleteLater()));

            //! erase return next itor, update itor
            itor = m_STPtrVec.erase(itor);
        }
        else
        {
            itor++;
        }
    }
}

void SControler::SetLogCb(pfnLog logCb, void* pUser, int logLevel)
{
    m_pCallBackLog.logCb    = logCb;
    m_pCallBackLog.pUser    = pUser;
    m_pCallBackLog.logLevel = logLevel;
}

void SControler::WriteCbLog(const string& str)
{
    if (m_pCallBackLog.logCb)
    {
        m_pCallBackLog.logCb(m_pCallBackLog.pUser, str, 0);
    }
}