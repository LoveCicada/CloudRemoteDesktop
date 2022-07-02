#include "SControler.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QHostInfo>
#include <QRect>

SControler::SControler(QObject *parent) :
    QObject(parent)
{
    Init();
}

SControler::~SControler()
{
    qDebug() << __func__;
}

void SControler::Init()
{
    GetServerMachineInfo();
    CretateTcpServer();
}

void SControler::CretateTcpServer()
{
    m_pWriteServerMsgTcpServer = make_shared<QTcpServer>(new QTcpServer);
    m_pWriteServerMsgTcpServer->listen(QHostAddress::Any, MAP_SERVER_MSG_PORT);
    qDebug() << "server msg begin listening" << endl;
    connect(m_pWriteServerMsgTcpServer.get(), SIGNAL(newConnection()), this, SLOT(writeServerMsg()));

    m_pWriteServerImgTcpServer = make_shared<QTcpServer>(new QTcpServer);
    m_pWriteServerImgTcpServer->listen(QHostAddress::Any, MAP_SERVER_IMG_PORT);
    qDebug() << "server img begin listening" << endl;
    connect(m_pWriteServerImgTcpServer.get(), SIGNAL(newConnection()), this, SLOT(writeServerImg()));

    m_pReadClientMsgTcpServer = make_shared<QTcpServer>(new QTcpServer);
    m_pReadClientMsgTcpServer->listen(QHostAddress::Any, CMD_SERVER_PORT);
    qDebug() << "client msg begin listening" << endl;
    connect(m_pReadClientMsgTcpServer.get(), SIGNAL(newConnection()), this, SLOT(readClientMsg()));
}

void SControler::writeServerMsg()
{
    QTcpSocket* pClientMsgSocket = m_pWriteServerMsgTcpServer->nextPendingConnection();
    qDebug() << "new map connection:" << pClientMsgSocket->peerAddress().toString() << endl;

    {
        string str = "new msg connection: " +
            pClientMsgSocket->peerAddress().toString().toStdString();
        WriteCbLog(str);
    }

    SMsgWriter* pMsgThread = new SMsgWriter(pClientMsgSocket, m_serverParmas);
    connect(pClientMsgSocket, SIGNAL(disconnected()), this, SLOT(someSocketDisconnected()));

    SocketAndThreadPtr pSt(new SocketAndThread(pClientMsgSocket, pMsgThread));
    m_STPtrVec.emplace_back(pSt);

    pMsgThread->start();
}

  /*
  * when have a new connect, start a new thread process
  */
void SControler::writeServerImg()
{
    QTcpSocket* pClientImgSocket = m_pWriteServerImgTcpServer->nextPendingConnection();
    qDebug()<<"new map connection:"<< pClientImgSocket->peerAddress().toString()<<endl;

    {
        string str = "new map connection: " +
            pClientImgSocket->peerAddress().toString().toStdString();
        WriteCbLog(str);
    }

    SImgWriter* pImgThread = new SImgWriter(pClientImgSocket, m_serverParmas);
    connect(pClientImgSocket, SIGNAL(disconnected()), this, SLOT(someSocketDisconnected()));

    SocketAndThreadPtr pSt(new SocketAndThread(pClientImgSocket, pImgThread));
    m_STPtrVec.emplace_back(pSt);

    pImgThread->start();
}

void SControler::readClientMsg()
{
    QTcpSocket* pReadClientCmdSocket = m_pReadClientMsgTcpServer->nextPendingConnection();
    qDebug()<<"new cmd connection:"<< pReadClientCmdSocket->peerAddress().toString()<<endl;

    {
        string str = "new cmd connection: " +
            pReadClientCmdSocket->peerAddress().toString().toStdString();
        WriteCbLog(str);
    }

    SMsgReader* pSMsgReader = new SMsgReader(pReadClientCmdSocket);
    connect(pReadClientCmdSocket, SIGNAL(disconnected()), this, SLOT(someSocketDisconnected()));

    SocketAndThreadPtr pSt(new SocketAndThread(pReadClientCmdSocket, pSMsgReader));
    m_STPtrVec.emplace_back(pSt);

    pSMsgReader->start();
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
                QHostAddress qAd = pSocket->peerAddress();
                QString strAd = qAd.toString();
                QString strName = pSocket->peerName();
                qDebug() << "client: " << strAd << " " << strName << " disconnect";

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

void SControler::GetServerMachineInfo()
{
    QDesktopWidget* pDeskWidget = qApp->desktop();
    QRect screenRect = pDeskWidget->screenGeometry();
    unsigned short usW = static_cast<unsigned short>(screenRect.width());
    unsigned short usH = static_cast<unsigned short>(screenRect.height());
    m_serverParmas.SetScreenWidth(usW);
    m_serverParmas.SetScreenHeight(usH);

    QString hostName = QHostInfo::localHostName();
    string strHostName = hostName.toStdString();
    m_serverParmas.SetServerName(strHostName);
}

void SControler::GetServerParams(ServerParmas& sp)
{
    sp = m_serverParmas;
}

void SControler::SetServerParams(const ServerParmas& sp)
{
    m_serverParmas = sp;
}
