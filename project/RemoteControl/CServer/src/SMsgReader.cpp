#include "SMsgReader.h"
#include "SMsgHandler.h"
#include "Command.h"
#include "RWSocket.h"

SMsgReader::SMsgReader(QTcpSocket* socket, ServerParmas sp, QObject *parent) :
    m_pCmdSocket(socket), m_ServerParmas(sp), RCThread(parent)
{
    cmdMsgOffset = 0;
    clientMsgLength = 8;
    memset(clientMsgData, 0, clientMsgLength);
    connect(m_pCmdSocket, SIGNAL(readyRead()), this, SLOT(readSocketData()));
}

SMsgReader::~SMsgReader()
{
    qDebug() << __func__;
}

void SMsgReader::Extend(void* param)
{
    static_cast<void*>(param);
    qDebug() << __func__;
}

void SMsgReader::run()
{
    QThread::run();
}

/*
* when tcp socket have receive new data, read socket data
*/
void SMsgReader::readSocketData()
{
    while(true)
    {
        qint64 r = m_pCmdSocket->read((char*)(clientMsgData + cmdMsgOffset), clientMsgLength - cmdMsgOffset);
        if(r <= 0)
            return;
        cmdMsgOffset += r;
        if(cmdMsgOffset == clientMsgLength)
        {
            readClientMsg();
            cmdMsgOffset = 0;
        }
        else
        {
            qDebug() << "*** readSocketData !=8 ***";
        }
    }

}

void SMsgReader::readClientMsg()
{
    //qDebug()<<"new command";
    int cmd = clientMsgData[0];
    switch(cmd)
    {
        case CMD_MOUSE_MOVE_TO:
            cmdMouseMoveTo();
            break;
        case CMD_MOUSE_LEFT_DOWN:
            cmdMouseLeftDown();
            break;
        case CMD_MOUSE_LEFT_UP:
            cmdMouseLeftUp();
            break;
        case CMD_MOUSE_RIGHT_DOWN:
            cmdMouseRightDown();
            break;
        case CMD_MOUSE_RIGHT_UP:
            cmdMouseRightUp();
            break;
        case CMD_MOUSE_WHEEL:
            cmdMouseWheel();
            break;
        case CMD_GET_SCREEN_SIZE:
            cmdScreenSize();
            break;
        case CMD_MOUSE_DOUBLE_CLICK:
            cmdMouseDoubleClick();
            break;
        case CMD_KEY_PRESS:
            cmdKeyPressed();
            break;
        case CMD_KEY_RELEASE:
            cmdKeyReleased();
            break;
    }
}

//buf[1] -> key code
void SMsgReader::cmdKeyPressed()
{
    uchar c = clientMsgData[1];
    SMsgHandler::keyPressed(c);
}

//buf[1] -> key code
void SMsgReader::cmdKeyReleased()
{
    uchar c = clientMsgData[1];
    SMsgHandler::keyReleased(c);
}

/**
  *移动鼠标到点x, y
  * 1 xh, 2 xl, 3 yh, 4yl
  */
void SMsgReader::cmdMouseMoveTo()
{
    int x = clientMsgData[1];
    x = x << 8;
    x += clientMsgData[2];
    int y = clientMsgData[3];
    y = y << 8;
    y += clientMsgData[4];
    //qDebug()<<"mouse move to:"<<x<<" "<<y;
    SMsgHandler::mouseMoveTo(x, y);
}

void SMsgReader::cmdMouseLeftDown()
{
    qDebug()<<"left down";
    int x = clientMsgData[1];
    x = x << 8;
    x += clientMsgData[2];
    int y = clientMsgData[3];
    y = y << 8;
    y += clientMsgData[4];
    SMsgHandler::mouseLeftDown(x, y);
}
void SMsgReader::cmdMouseLeftUp()
{
    qDebug()<<"left up";
    int x = clientMsgData[1];
    x = x << 8;
    x += clientMsgData[2];
    int y = clientMsgData[3];
    y = y << 8;
    y += clientMsgData[4];
    SMsgHandler::mouseLeftUp(x, y);
}

void SMsgReader::cmdMouseRightDown()
{
    qDebug()<<"right down";
    int x = clientMsgData[1];
    x = x << 8;
    x += clientMsgData[2];
    int y = clientMsgData[3];
    y = y << 8;
    y += clientMsgData[4];
    SMsgHandler::mouseRightDown(x, y);
}

void SMsgReader::cmdMouseRightUp()
{
    qDebug()<<"right up";
    int x = clientMsgData[1];
    x = x << 8;
    x += clientMsgData[2];
    int y = clientMsgData[3];
    y = y << 8;
    y += clientMsgData[4];
    SMsgHandler::mouseRightUp(x, y);
}

void SMsgReader::cmdMouseDoubleClick()
{
    qDebug()<<"double click";
    int x = clientMsgData[1];
    x = x << 8;
    x += clientMsgData[2];
    int y = clientMsgData[3];
    y = y << 8;
    y += clientMsgData[4];
    SMsgHandler::mouseLeftDown(x, y);
    SMsgHandler::mouseLeftUp(x, y);
    SMsgHandler::mouseLeftDown(x, y);
    SMsgHandler::mouseLeftUp(x, y);
}

void SMsgReader::cmdMouseWheel()
{
#if 0

    int delta = clientMsgData[1];
    delta = delta << 8;
    delta += clientMsgData[2];
    int x = clientMsgData[3];
    x = x << 8;
    x += clientMsgData[4];
    int y = clientMsgData[5];
    y = y << 8;
    y += clientMsgData[6];

#else

    int x = clientMsgData[1];
    x = x << 8;
    x += clientMsgData[2];
    int y = clientMsgData[3];
    y = y << 8;
    y += clientMsgData[4];

    int delta = clientMsgData[5];
    delta = delta << 8;
    delta += clientMsgData[6];

#endif // 0

    SMsgHandler::mouseWheel(delta, x, y);
}

void SMsgReader::cmdScreenSize()
{
    unsigned short usW = 0;
    unsigned short usH = 0;
    m_ServerParmas.GetScreenWidth(usW);
    m_ServerParmas.GetScreenHeight(usH);

    uchar uc[8];
    uc[0] = CMD_GET_SCREEN_SIZE_RES;
    uc[1] = usW / 0x100;
    uc[2] = usW % 0x100;
    uc[3] = usH / 0x100;
    uc[4] = usH % 0x100;
    BlockWriteSocketData(m_pCmdSocket, uc, 8);
}
