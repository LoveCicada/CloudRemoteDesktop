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
        int r = m_msgSocket->read((char*)(cmd_buf + cmd_buf_fill), msgProtocolLength - cmd_buf_fill);
        if(r <= 0)
            return;
        cmd_buf_fill += r;
        if(cmd_buf_fill == msgProtocolLength)
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
    if(socketConnected == false)
        return;
    char c[msgProtocolLength] = {0};

    CMDData tmpCMDData;
    tmpCMDData.SetCMD(CMD_MOUSE_MOVE_TO);
    tmpCMDData.SetX(x);
    tmpCMDData.SetY(y);
    
    CmdMouseMove cmdMouseMove;
    cmdMouseMove.SetData(tmpCMDData);
    cmdMouseMove.GetData(c);

    BlockWriteSocketData(m_msgSocket.get(), c, msgProtocolLength);
}

void CMsgWriter::cmdMouseDoubleClick(int x, int y)
{
    char c[msgProtocolLength] = {0};

    CMDData tmpCMDData;
    tmpCMDData.SetCMD(CMD_MOUSE_DOUBLE_CLICK);
    tmpCMDData.SetX(x);
    tmpCMDData.SetY(y);
   
    CmdMouseDbClick cmdc;
    cmdc.SetData(tmpCMDData);

    BlockWriteSocketData(m_msgSocket.get(), c, msgProtocolLength);
}

void CMsgWriter::cmdMouseLeftDown(int x, int y)
{
    char c[msgProtocolLength] = {0};

    CMDData tmpCMDData;
    tmpCMDData.SetCMD(CMD_MOUSE_LEFT_DOWN);
    tmpCMDData.SetX(x);
    tmpCMDData.SetY(y);
    

    CmdMouseLeftDown cmld;
    cmld.SetData(tmpCMDData);
    cmld.GetData(c);

    BlockWriteSocketData(m_msgSocket.get(), c, msgProtocolLength);
}

void CMsgWriter::cmdMouseLeftUp(int x, int y)
{
    char c[msgProtocolLength] = {0};

    CMDData tmpCMDData;
    tmpCMDData.SetCMD(CMD_MOUSE_LEFT_UP);
    tmpCMDData.SetX(x);
    tmpCMDData.SetY(y);

    CmdMouseLeftDown cmld;
    cmld.SetData(tmpCMDData);
    cmld.GetData(c);

    BlockWriteSocketData(m_msgSocket.get(), c, msgProtocolLength);
}

void CMsgWriter::cmdMouseRightDown(int x, int y)
{
    char c[msgProtocolLength] = {0};

    CMDData tmpCMDData;
    tmpCMDData.SetCMD(CMD_MOUSE_RIGHT_DOWN);
    tmpCMDData.SetX(x);
    tmpCMDData.SetY(y);

    CmdMouseRightDown cmdrd;
    cmdrd.SetData(tmpCMDData);
    cmdrd.GetData(c);

    BlockWriteSocketData(m_msgSocket.get(), c, msgProtocolLength);
}

void CMsgWriter::cmdMouseRightUp(int x, int y)
{
    char c[msgProtocolLength] = {0};

    CMDData tmpCMDData;
    tmpCMDData.SetCMD(CMD_MOUSE_RIGHT_UP);
    tmpCMDData.SetX(x);
    tmpCMDData.SetY(y);
    
    CmdMouseRightUp cmru;
    cmru.SetData(tmpCMDData);
    cmru.GetData(c);

    BlockWriteSocketData(m_msgSocket.get(), c, msgProtocolLength);
}

void CMsgWriter::cmdMouseWheel(int delta, int x, int y)
{
    char c[msgProtocolLength] = {0};

    CMDData tmpCMDData;
    tmpCMDData.SetCMD(CMD_MOUSE_WHEEL);
    tmpCMDData.SetX(x);
    tmpCMDData.SetY(y);
    tmpCMDData.SetDelta(delta);
    
    CmdMouseWheel cmw;
    cmw.SetData(tmpCMDData);
    cmw.GetData(c);

    BlockWriteSocketData(m_msgSocket.get(), c, msgProtocolLength);
}

void CMsgWriter::cmdScreenSize()
{
    char c[msgProtocolLength] = {0};

    CMDData cmdData;
    cmdData.SetCMD(CMDTYPE::CMD_GET_SCREEN_SIZE);
    CmdGetScreenSize css;
    css.SetData(cmdData);
    css.GetData(c);

    BlockWriteSocketData(m_msgSocket.get(), c, msgProtocolLength);
}

void CMsgWriter::cmdKeyPress(int32_t key)
{
    char c[msgProtocolLength] = {0};

    CMDData tmpCMDData;
    tmpCMDData.SetCMD(CMD_KEY_PRESS);
    tmpCMDData.SetKeyValue(key);

    CmdKeyPress ckp;
    ckp.SetData(tmpCMDData);
    ckp.GetData(c);

    BlockWriteSocketData(m_msgSocket.get(), c, msgProtocolLength);
}

void CMsgWriter::cmdKeyRelease(int32_t key)
{
    char c[msgProtocolLength] = {0};

    CMDData tmpCMDData;
    tmpCMDData.SetCMD(CMD_KEY_RELEASE);
    tmpCMDData.SetKeyValue(key);

    CmdKeyRelease ckr;
    ckr.SetData(tmpCMDData);
    ckr.GetData(c);

    BlockWriteSocketData(m_msgSocket.get(), c, msgProtocolLength);
}
