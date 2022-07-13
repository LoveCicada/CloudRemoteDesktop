#include "SMsgWriter.h"
#include "SMsgHandler.h"
#include <stdlib.h>
#include <QTcpSocket>

#include "RWSocket.h"
#include "Command.h"

SMsgWriter::SMsgWriter(QTcpSocket* socket, ServerParmas sp, QObject *parent) :
    m_msgSocket(socket), m_serverParmas(sp), RCThread(parent)
{
    Init();
}

SMsgWriter::~SMsgWriter()
{
    qDebug() << __func__;
}

void SMsgWriter::Extend(void* param)
{
    static_cast<void*>(param);
    qDebug() << __func__;
}

void SMsgWriter::Init()
{
    InitData();
    sendServerParams();
}

void SMsgWriter::InitData()
{
    memset(m_msgData, 0, msgProtocolLength);
    connect(m_msgSocket, SIGNAL(readyRead()), this, SLOT(readMsgFromClient()));
}

void SMsgWriter::run()
{
    QThread::run();
}

bool SMsgWriter::checkConnect()
{
    bool bRet = false;

    if (m_msgSocket == 0)
    {
        qDebug() << "null socket" << endl;
        return bRet;
    }
    else if (m_msgSocket->isOpen() == false)
    {
        qDebug() << "socket not open" << endl;
        return bRet;
    }
    else if (m_msgSocket->isWritable() == false)
    {
        qDebug() << "socket not writable" << endl;
        return bRet;
    }

    bRet = true;
    return bRet;
}

void SMsgWriter::sendServerParams()
{
    bool bConnect = checkConnect();
    if (!bConnect) {
        return;
    }

    unsigned short usW = 0;
    unsigned short usH = 0;
    m_serverParmas.GetScreenWidth(usW);
    m_serverParmas.GetScreenHeight(usH);

    memset(m_msgData, 0, msgProtocolLength);

    CMDData cmdData;
    cmdData.SetCMD(CMDTYPE::CMD_SEND_SERVER_SCREEN_SIZE);
    cmdData.SetX(usW);
    cmdData.SetY(usH);

    CmdSendServerScreenSize csss;
    csss.SetData(cmdData);
    csss.GetData(m_msgData);

    BlockWriteSocketData(m_msgSocket, m_msgData, msgProtocolLength);
}

void SMsgWriter::sendMsgToClient()
{

}

void SMsgWriter::readMsgFromClient()
{

}

void SMsgWriter::quit()
{
    QThread::quit();
}


