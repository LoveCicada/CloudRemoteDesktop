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
    m_msgSocket = make_shared<QTcpSocket>(new QTcpSocket);

    connect(m_msgSocket.get(), SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(connectError(QAbstractSocket::SocketError)));
    connect(m_msgSocket.get(), SIGNAL(connected()), this, SLOT(connectSucceed()));
    connect(m_msgSocket.get(), SIGNAL(readyRead()), this, SLOT(readDataFromServer()));

    connectToServer();
    m_msgSocket->waitForConnected();
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
            m_clientCMDData.SetData(cmd_buf);
            readServerMsg();
            cmd_buf_fill = 0;
        }
    }
}

void CMsgWriter::readServerMsg()
{
#if 0

    int c = cmd_buf[0];
    if(c == CMD_GET_SCREEN_SIZE_RES)
    {
        int w = cmd_buf[1];
        w = w << 8;
        w += cmd_buf[2];
        int h = cmd_buf[3];
        h = h << 8;
        h += cmd_buf[4];
        emit setServerScreenSize(w, h);
        qDebug()<<"get server screen size:"<<w<<" "<<h;
    }

#else

    CMDTYPE cmdType = m_clientCMDData.GetCMD();
    if (cmdType == CMDTYPE::CMD_GET_SCREEN_SIZE_RES)
    {
        int w = m_clientCMDData.GetW();
        int h = m_clientCMDData.GetH();

        emit setServerScreenSize(w, h);
        qDebug() << "get server screen size:" << w << " " << h;
    }

#endif // 0

}

void CMsgWriter::connectToServer()
{
    qDebug()<<"try to connect";
    m_msgSocket->connectToHost(m_address, m_port);
}

void CMsgWriter::connectError(QAbstractSocket::SocketError)
{
    qDebug()<<"connect error, reconnect";
    //QThread::msleep(200);
    m_msgSocket->abort();
    m_msgSocket->close();
    connectToServer();
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

#if 0

    uc[0] = CMD_MOUSE_MOVE_TO;
    uc[1] = x / 0x100;
    uc[2] = x % 0x100;
    uc[3] = y / 0x100;
    uc[4] = y % 0x100;

#else

    //qDebug()<<"mouse move to"<<x<<" "<<y;

    ClientCMDData tmpClientCMDData;
    tmpClientCMDData.SetCMD(CMD_MOUSE_MOVE_TO);
    tmpClientCMDData.SetX(x);
    tmpClientCMDData.SetY(y);
    tmpClientCMDData.GetData(uc);

#endif // 0

    BlockWriteSocketData(m_msgSocket.get(), uc, 8);
}

void CMsgWriter::cmdMouseDoubleClick(int x, int y)
{
    uchar uc[8] = {0};

#if 0

    uc[0] = CMD_MOUSE_DOUBLE_CLICK;
    uc[1] = x / 0x100;
    uc[2] = x % 0x100;
    uc[3] = y / 0x100;
    uc[4] = y % 0x100;

#else

    ClientCMDData tmpClientCMDData;
    tmpClientCMDData.SetCMD(CMD_MOUSE_DOUBLE_CLICK);
    tmpClientCMDData.SetX(x);
    tmpClientCMDData.SetY(y);
    tmpClientCMDData.GetData(uc);

#endif // 0

    BlockWriteSocketData(m_msgSocket.get(), uc, 8);
}

void CMsgWriter::cmdMouseLeftDown(int x, int y)
{
    uchar uc[8] = {0};

#if 0

    uc[0] = CMD_MOUSE_LEFT_DOWN;
    uc[1] = x / 0x100;
    uc[2] = x % 0x100;
    uc[3] = y / 0x100;
    uc[4] = y % 0x100;

#else

    ClientCMDData tmpClientCMDData;
    tmpClientCMDData.SetCMD(CMD_MOUSE_LEFT_DOWN);
    tmpClientCMDData.SetX(x);
    tmpClientCMDData.SetY(y);
    tmpClientCMDData.GetData(uc);

#endif // 0

    BlockWriteSocketData(m_msgSocket.get(), uc, 8);
}

void CMsgWriter::cmdMouseLeftUp(int x, int y)
{
    uchar uc[8] = {0};

#if 0

    uc[0] = CMD_MOUSE_LEFT_UP;
    uc[1] = x / 0x100;
    uc[2] = x % 0x100;
    uc[3] = y / 0x100;
    uc[4] = y % 0x100;

#else

    ClientCMDData tmpClientCMDData;
    tmpClientCMDData.SetCMD(CMD_MOUSE_LEFT_UP);
    tmpClientCMDData.SetX(x);
    tmpClientCMDData.SetY(y);
    tmpClientCMDData.GetData(uc);

#endif // 0

    BlockWriteSocketData(m_msgSocket.get(), uc, 8);
}

void CMsgWriter::cmdMouseRightDown(int x, int y)
{
    uchar uc[8] = {0};

#if 0

    uc[0] = CMD_MOUSE_RIGHT_DOWN;
    uc[1] = x / 0x100;
    uc[2] = x % 0x100;
    uc[3] = y / 0x100;
    uc[4] = y % 0x100;

#else

    ClientCMDData tmpClientCMDData;
    tmpClientCMDData.SetCMD(CMD_MOUSE_RIGHT_DOWN);
    tmpClientCMDData.SetX(x);
    tmpClientCMDData.SetY(y);
    tmpClientCMDData.GetData(uc);

#endif // 0

    BlockWriteSocketData(m_msgSocket.get(), uc, 8);
}

void CMsgWriter::cmdMouseRightUp(int x, int y)
{
    uchar uc[8] = {0};

#if 0

    uc[0] = CMD_MOUSE_RIGHT_UP;
    uc[1] = x / 0x100;
    uc[2] = x % 0x100;
    uc[3] = y / 0x100;
    uc[4] = y % 0x100;

#else

    ClientCMDData tmpClientCMDData;
    tmpClientCMDData.SetCMD(CMD_MOUSE_RIGHT_UP);
    tmpClientCMDData.SetX(x);
    tmpClientCMDData.SetY(y);
    tmpClientCMDData.GetData(uc);

#endif // 0

    BlockWriteSocketData(m_msgSocket.get(), uc, 8);
}

void CMsgWriter::cmdMouseWheel(int delta, int x, int y)
{
    uchar uc[8] = {0};

#if 1

    uc[0] = CMD_MOUSE_WHEEL;
    uc[1] = delta / 0x100;
    uc[2] = delta % 0x100;
    uc[3] = x / 0x100;
    uc[4] = x % 0x100;
    uc[5] = y / 0x100;
    uc[6] = y % 0x100;

#else

    ClientCMDData tmpClientCMDData;
    tmpClientCMDData.SetCMD(CMD_MOUSE_WHEEL);
    tmpClientCMDData.SetX(x);
    tmpClientCMDData.SetY(y);
    tmpClientCMDData.GetData(uc);

#endif // 0

    BlockWriteSocketData(m_msgSocket.get(), uc, 8);
}

void CMsgWriter::cmdScreenSize()
{
    uchar uc[8] = {0};

#if 0

    uc[0] = CMD_GET_SCREEN_SIZE;

#else

    ClientCMDData tmpClientCMDData;
    tmpClientCMDData.SetCMD(CMD_GET_SCREEN_SIZE);
    tmpClientCMDData.GetData(uc);

#endif // 0

    BlockWriteSocketData(m_msgSocket.get(), uc, 8);
}

void CMsgWriter::cmdKeyPress(uchar key)
{
    uchar uc[8] = {0};
#if 1

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

    uc[0] = CMD_KEY_RELEASE;
    uc[1] = key;

#else

    ClientCMDData tmpClientCMDData;
    tmpClientCMDData.SetCMD(CMD_KEY_RELEASE);
    tmpClientCMDData.GetData(uc);

#endif // 0

    BlockWriteSocketData(m_msgSocket.get(), uc, 8);
}
