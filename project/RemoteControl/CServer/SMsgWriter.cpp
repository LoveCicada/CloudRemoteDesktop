#include "SMsgWriter.h"
#include "SMsgHandler.h"
#include "RWSocket.h"
#include "Command.h"
#include <stdlib.h>

/**
  *图像传输线程
  *建立一个双通道的tcp socket
  *启动一个定时器
  */
SMsgWriter::SMsgWriter(QTcpSocket* socket, ServerParmas sp, QObject *parent) :
    QThread(parent)
{
    m_msgSocket = socket;
    m_serverParmas = sp;

    sent_img_buf  = 0;
    curt_img_buf  = 0;
    send_data_buf = 0;
    cmd_buf_fill = 0;
    started = false;
    memset(cmd_buf, 0, 4);
    connect(m_msgSocket, SIGNAL(readyRead()), this, SLOT(readMsgFromClient()));
}

void SMsgWriter::run()
{
    QThread::run();
}

bool SMsgWriter::checkConnect()
{
    bool bRet = false;
    if (!started)
        return bRet;
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

    unsigned char uc[8] = { 0 };
    uc[0] = CMDTYPE::CMD_SEND_SERVER_SCREEN_SIZE;
    uc[1] = usW / 0x100;
    uc[2] = usW % 0x100;
    uc[3] = usH / 0x100;
    uc[4] = usH % 0x100;
    BlockWriteSocketData(m_msgSocket, uc, 8);
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

SMsgWriter::~SMsgWriter()
{
    if(sent_img_buf != 0)
        delete[] sent_img_buf;
    if(curt_img_buf != 0)
        delete[] curt_img_buf;
    if(send_data_buf != 0)
        delete[] send_data_buf;
    qDebug() << __func__;
}
