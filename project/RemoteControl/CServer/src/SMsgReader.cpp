#include "SMsgReader.h"
#include "SMsgHandler.h"
#include "Command.h"
#include "RWSocket.h"
#include <QTcpSocket>


SMsgReader::SMsgReader(QTcpSocket* socket, ServerParmas sp, QObject *parent) :
    m_pCmdSocket(socket), m_ServerParmas(sp), RCThread(parent)
{
    cmdMsgOffset = 0;
    clientMsgLength = msgProtocolLength;
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
        qint64 r = m_pCmdSocket->read((clientMsgData + cmdMsgOffset), clientMsgLength - cmdMsgOffset);
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
            qDebug() << "*** readSocketData !=20 ***";
        }
    }

}

void SMsgReader::readClientMsg()
{
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
    qDebug() << __func__;

    int32_t keyValue = 0;
    int32_t scanCode = 0;
    int32_t virtualKey = 0;
    int32_t modifier = 0;

    CMDData cmdData;
    cmdData.SetData(clientMsgData);
    cmdData.GetKeyValue(keyValue);
    cmdData.GetScanCode(scanCode);
    cmdData.GetVirtualKey(virtualKey);
    cmdData.GetModifier(modifier);

    SMsgHandler::keyPressed(keyValue);
}

//buf[1] -> key code
void SMsgReader::cmdKeyReleased()
{
    qDebug() << __func__;

    int32_t keyValue = 0;
    int32_t scanCode = 0;
    int32_t virtualKey = 0;
    int32_t modifier = 0;

    CMDData cmdData;
    cmdData.SetData(clientMsgData);
    cmdData.GetKeyValue(keyValue);
    cmdData.GetScanCode(scanCode);
    cmdData.GetVirtualKey(virtualKey);
    cmdData.GetModifier(modifier);

    SMsgHandler::keyReleased(keyValue);

}

/*
 *@brief move to x, y
 */
void SMsgReader::cmdMouseMoveTo()
{
    qDebug() << __func__;

    int32_t xPos = 0;
    int32_t yPos = 0;

    CMDData cmdData;
    cmdData.SetData(clientMsgData);
    cmdData.GetX(xPos);
    cmdData.GetY(yPos);
    
    SMsgHandler::mouseMoveTo(xPos, yPos);
}

void SMsgReader::cmdMouseLeftDown()
{
    qDebug() << __func__;

    int32_t xPos = 0;
    int32_t yPos = 0;

    CMDData cmdData;
    cmdData.SetData(clientMsgData);
    cmdData.GetX(xPos);
    cmdData.GetY(yPos);

    SMsgHandler::mouseLeftDown(xPos, yPos);
}
void SMsgReader::cmdMouseLeftUp()
{
    qDebug() << __func__;

    int32_t xPos = 0;
    int32_t yPos = 0;

    CMDData cmdData;
    cmdData.SetData(clientMsgData);
    cmdData.GetX(xPos);
    cmdData.GetY(yPos);

    SMsgHandler::mouseLeftUp(xPos, yPos);
}

void SMsgReader::cmdMouseRightDown()
{
    qDebug() << __func__;

    int32_t xPos = 0;
    int32_t yPos = 0;

    CMDData cmdData;
    cmdData.SetData(clientMsgData);
    cmdData.GetX(xPos);
    cmdData.GetY(yPos);

    SMsgHandler::mouseRightDown(xPos, yPos);
}

void SMsgReader::cmdMouseRightUp()
{
    qDebug() << __func__;

    int32_t xPos = 0;
    int32_t yPos = 0;

    CMDData cmdData;
    cmdData.SetData(clientMsgData);
    cmdData.GetX(xPos);
    cmdData.GetY(yPos);

    SMsgHandler::mouseRightUp(xPos, yPos);
}

void SMsgReader::cmdMouseDoubleClick()
{
    qDebug() << __func__;

    int32_t xPos = 0;
    int32_t yPos = 0;

    CMDData cmdData;
    cmdData.SetData(clientMsgData);
    cmdData.GetX(xPos);
    cmdData.GetY(yPos);

    SMsgHandler::mouseLeftDown(xPos, yPos);
    SMsgHandler::mouseLeftUp(xPos, yPos);
    SMsgHandler::mouseLeftDown(xPos, yPos);
    SMsgHandler::mouseLeftUp(xPos, yPos);
}

void SMsgReader::cmdMouseWheel()
{
    qDebug() << __func__;

    int32_t xPos = 0;
    int32_t yPos = 0;
    int32_t delta = 0;

    CMDData cmdData;
    cmdData.SetData(clientMsgData);
    cmdData.GetX(xPos);
    cmdData.GetY(yPos);
    cmdData.GetDelta(delta);

    SMsgHandler::mouseWheel(delta, xPos, yPos);
}

void SMsgReader::cmdScreenSize()
{
    qDebug() << __func__;

    unsigned short usW = 0;
    unsigned short usH = 0;
    m_ServerParmas.GetScreenWidth(usW);
    m_ServerParmas.GetScreenHeight(usH);

    char c[msgProtocolLength];
    CMDData cmdData;
    cmdData.SetCMD(CMDTYPE::CMD_SEND_SERVER_SCREEN_SIZE);
    cmdData.SetX(usW);
    cmdData.SetY(usH);

    CmdGetScreenSizeRes cssr;
    cssr.SetData(cmdData);
    cssr.GetData(c);

    BlockWriteSocketData(m_pCmdSocket, c, 8);
}
