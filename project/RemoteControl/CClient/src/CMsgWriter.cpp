#include "CMsgWriter.h"

CMsgWriter::CMsgWriter(QString add, int p, QObject* parent) : QObject(parent)
{
    m_address = add;
    m_port = p;
    socketConnected = false;
    cmd_buf_fill = 0;
}

void CMsgWriter::run()
{
    qRegisterMetaType<QAbstractSocket::SocketError>("SocketError");
    m_msgSocket = make_shared<QTcpSocket>();

    connect(m_msgSocket.get(), SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(connectError(QAbstractSocket::SocketError)));
    connect(m_msgSocket.get(), SIGNAL(connected()), this, SLOT(connectSucceed()));
    connect(m_msgSocket.get(), SIGNAL(readyRead()), this, SLOT(readDataFromServer()));

    connectToServer();
    bool bConnected = m_msgSocket->waitForConnected();
    if (!bConnected) {
        qDebug() << "connect timed out";
        return;
    }
    cmdScreenSize();
}

void CMsgWriter::readDataFromServer()
{
    while(true)
    {
        int r = m_msgSocket->read((char*)(cmd_buf + cmd_buf_fill), 8 - cmd_buf_fill);
        if(r <= 0)
            return;
        cmd_buf_fill += r;
        if(cmd_buf_fill == 8)
        {
            m_cmdData.SetData(cmd_buf);
            readServerMsg();
            cmd_buf_fill = 0;
        }
    }
}

void CMsgWriter::readServerMsg()
{
    CMDTYPE cmdType = CMDTYPE::CMD_UNKNOWN;
    m_cmdData.GetCMD(cmdType);
    if (cmdType == CMDTYPE::CMD_GET_SCREEN_SIZE_RES)
    {
        int w = 0;
        int h = 0;
        m_cmdData.GetW(w);
        m_cmdData.GetH(h);
        m_cmdData.GetW(w);
        m_cmdData.GetH(h);

        emit setServerScreenSize(w, h);
        qDebug() << "get server screen size:" << w << " " << h;
    }
}

void CMsgWriter::connectToServer()
{
    qDebug()<<"try to connect";
    m_msgSocket->connectToHost(m_address, m_port);
}

void CMsgWriter::connectError(QAbstractSocket::SocketError)
{
    qDebug() << __FILE__ << " " << __func__;
    m_msgSocket->abort();
    m_msgSocket->close();
}

void CMsgWriter::connectSucceed()
{
    qDebug()<<"connect succeed";
    socketConnected = true;
}

void CMsgWriter::cmdMouseMoveTo(int x, int y)
{
    //qDebug()<<"mouse move to";
    if(socketConnected == false)
        return;
    uchar uc[8] = {0};

    CMDData tmpCMDData;
    tmpCMDData.SetCMD(CMD_MOUSE_MOVE_TO);
    tmpCMDData.SetX(x);
    tmpCMDData.SetY(y);
    tmpCMDData.GetData(uc);

    BlockWriteSocketData(m_msgSocket.get(), uc, 8);
}

void CMsgWriter::cmdMouseDoubleClick(int x, int y)
{
    uchar uc[8] = {0};

    CMDData tmpCMDData;
    tmpCMDData.SetCMD(CMD_MOUSE_DOUBLE_CLICK);
    tmpCMDData.SetX(x);
    tmpCMDData.SetY(y);
    tmpCMDData.GetData(uc);

    BlockWriteSocketData(m_msgSocket.get(), uc, 8);
}

void CMsgWriter::cmdMouseLeftDown(int x, int y)
{
    uchar uc[8] = {0};

    CMDData tmpCMDData;
    tmpCMDData.SetCMD(CMD_MOUSE_LEFT_DOWN);
    tmpCMDData.SetX(x);
    tmpCMDData.SetY(y);
    tmpCMDData.GetData(uc);

    BlockWriteSocketData(m_msgSocket.get(), uc, 8);
}

void CMsgWriter::cmdMouseLeftUp(int x, int y)
{
    uchar uc[8] = {0};

    CMDData tmpCMDData;
    tmpCMDData.SetCMD(CMD_MOUSE_LEFT_UP);
    tmpCMDData.SetX(x);
    tmpCMDData.SetY(y);
    tmpCMDData.GetData(uc);

    BlockWriteSocketData(m_msgSocket.get(), uc, 8);
}

void CMsgWriter::cmdMouseRightDown(int x, int y)
{
    uchar uc[8] = {0};

    CMDData tmpCMDData;
    tmpCMDData.SetCMD(CMD_MOUSE_RIGHT_DOWN);
    tmpCMDData.SetX(x);
    tmpCMDData.SetY(y);
    tmpCMDData.GetData(uc);

    BlockWriteSocketData(m_msgSocket.get(), uc, 8);
}

void CMsgWriter::cmdMouseRightUp(int x, int y)
{
    uchar uc[8] = {0};

    CMDData tmpCMDData;
    tmpCMDData.SetCMD(CMD_MOUSE_RIGHT_UP);
    tmpCMDData.SetX(x);
    tmpCMDData.SetY(y);
    tmpCMDData.GetData(uc);

    BlockWriteSocketData(m_msgSocket.get(), uc, 8);
}

void CMsgWriter::cmdMouseWheel(int delta, int x, int y)
{
    uchar uc[8] = {0};

    CmdMouseWheel cmdMouseWheel;
    cmdMouseWheel.SetX(x);
    cmdMouseWheel.SetY(y);
    cmdMouseWheel.SetDelta(delta);
    cmdMouseWheel.GetData(uc);

    BlockWriteSocketData(m_msgSocket.get(), uc, 8);
}

void CMsgWriter::cmdScreenSize()
{
    uchar uc[8] = {0};

    CMDData tmpCMDData;
    tmpCMDData.SetCMD(CMD_GET_SCREEN_SIZE);
    tmpCMDData.GetData(uc);

    BlockWriteSocketData(m_msgSocket.get(), uc, 8);
}

void CMsgWriter::cmdKeyPress(int key)
{
    uchar uc[8] = {0};
#if 1

    /*
    @brief use 4 byte storage key value
        uc[1], uc[2], uc[3], uc[4]
        eg: Key_Escape = 0x01000000,
        01      00      00      00
        uc[1]   uc[2]   uc[3]   uc[4]
    */

    /*uc[0] = CMD_KEY_PRESS;
    uc[1] = (key & 0xFF000000) >> 24;
    uc[2] = (key & 0x00FF0000) >> 16;
    uc[3] = (key & 0x0000FF00) >> 8;
    uc[4] = (key & 0x000000FF);*/

    uc[0] = CMD_KEY_PRESS;
    uc[1] = key;

#else

    ClientCMDData tmpClientCMDData;
    tmpClientCMDData.SetCMD(CMD_KEY_PRESS);
    tmpClientCMDData.GetData(uc);

#endif // 0
    BlockWriteSocketData(m_msgSocket.get(), uc, 8);
}

void CMsgWriter::cmdKeyRelease(uchar key)
{
    uchar uc[8] = {0};
#if 1

    /*
    @brief use 4 byte storage key value
        uc[1], uc[2], uc[3], uc[4]
        eg: Key_Escape = 0x01000000,
        01      00      00      00
        uc[1]   uc[2]   uc[3]   uc[4]
    */

    /*uc[0] = CMD_KEY_RELEASE;
    uc[1] = (key & 0xFF000000) >> 24;
    uc[2] = (key & 0x00FF0000) >> 16;
    uc[3] = (key & 0x0000FF00) >> 8;
    uc[4] = (key & 0x000000FF);*/

    uc[0] = CMD_KEY_RELEASE;
    uc[1] = key;

#else

    ClientCMDData tmpClientCMDData;
    tmpClientCMDData.SetCMD(CMD_KEY_RELEASE);
    tmpClientCMDData.GetData(uc);

#endif // 0

    BlockWriteSocketData(m_msgSocket.get(), uc, 8);
}
