
#include <QTcpSocket>
#include "Command.h"
#include "RWSocket.h"
#include "SMsgReader.h"
#include "SMsgHandler.h"


SMsgReader::SMsgReader(QTcpSocket* socket, ServerParmas sp, QObject *parent) :
    m_pCmdSocket(socket), m_ServerParmas(sp), RCThread(parent)
{
    m_cmdMsgOffset = 0;
    m_clientMsgLength = msgProtocolLength;
    memset(m_msgData, 0, m_clientMsgLength);
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
*@brief when tcp socket have receive new data, read socket data
*/
void SMsgReader::readSocketData()
{
    while(true)
    {
        qint64 r = m_pCmdSocket->read((m_msgData + m_cmdMsgOffset), m_clientMsgLength - m_cmdMsgOffset);
        if(r <= 0)
            return;
        m_cmdMsgOffset += r;
        if(m_cmdMsgOffset == m_clientMsgLength)
        {
            readClientMsg();
            m_cmdMsgOffset = 0;
        }
        else
        {
            qDebug() << __FUNCTION__ << " line: " << __LINE__ << " *** readSocketData !=20 ***";
        }
    }

}

void SMsgReader::readClientMsg()
{
    CMDTYPE cmd = static_cast<CMDTYPE>(m_msgData[0]);
    switch(cmd)
    {
        case CMDTYPE::CMD_UNKNOWN:
            qDebug() << __FUNCTION__ << " line: " << __LINE__ << " *** unknown msg ***";
            break;
        case CMDTYPE::CMD_MOUSE_MOVE_TO:
            cmdMouseMoveTo();
            break;
        case CMDTYPE::CMD_MOUSE_LEFT_DOWN:
            cmdMouseLeftDown();
            break;
        case CMDTYPE::CMD_MOUSE_LEFT_UP:
            cmdMouseLeftUp();
            break;
        case CMDTYPE::CMD_MOUSE_RIGHT_DOWN:
            cmdMouseRightDown();
            break;
        case CMDTYPE::CMD_MOUSE_RIGHT_UP:
            cmdMouseRightUp();
            break;
        case CMDTYPE::CMD_MOUSE_WHEEL:
            cmdMouseWheel();
            break;
        case CMDTYPE::CMD_GET_SCREEN_SIZE:
            cmdScreenSize();
            break;
        case CMDTYPE::CMD_MOUSE_DOUBLE_CLICK:
            cmdMouseDoubleClick();
            break;
        case CMDTYPE::CMD_KEY_PRESS:
            cmdKeyPressed();
            break;
        case CMDTYPE::CMD_KEY_RELEASE:
            cmdKeyReleased();
            break;
        case CMDTYPE::CMD_KEY_SP_ALTL_TAB:
            cmdKeySpAltLTab();
            break;
        case CMDTYPE::CMD_KEY_SP_ALTR_TAB:
            cmdKeySpAltRTab();
            break;
        case CMDTYPE::CMD_KEY_SP_WIN_L:
            cmdKeySpWinL();
            break;
        default:
            break;
    }
}

/*
* @brief
*/
void SMsgReader::cmdKeyPressed()
{
    qDebug() << __func__;

    int32_t keyValue = 0;
    int32_t scanCode = 0;
    int32_t virtualKey = 0;
    int32_t modifier = 0;

    CMDData cmdData;
    cmdData.SetData(m_msgData);
    cmdData.GetKeyValue(keyValue);
    cmdData.GetScanCode(scanCode);
    cmdData.GetVirtualKey(virtualKey);
    cmdData.GetModifier(modifier);

    SMsgHandler::keyPressed(keyValue, scanCode, virtualKey, modifier);
}

/*
* @brief
*/
void SMsgReader::cmdKeyReleased()
{
    qDebug() << __func__;

    int32_t keyValue = 0;
    int32_t scanCode = 0;
    int32_t virtualKey = 0;
    int32_t modifier = 0;

    CMDData cmdData;
    cmdData.SetData(m_msgData);
    cmdData.GetKeyValue(keyValue);
    cmdData.GetScanCode(scanCode);
    cmdData.GetVirtualKey(virtualKey);
    cmdData.GetModifier(modifier);

    SMsgHandler::keyReleased(keyValue, scanCode, virtualKey, modifier);

}

/*
 *@brief move to x, y
 */
void SMsgReader::cmdMouseMoveTo()
{
#if 0
    qDebug() << __FUNCTION__;
#endif // 0

    int32_t xPos = 0;
    int32_t yPos = 0;

    CMDData cmdData;
    cmdData.SetData(m_msgData);
    cmdData.GetX(xPos);
    cmdData.GetY(yPos);
    
    SMsgHandler::mouseMoveTo(xPos, yPos);
}

/*
* @brief
*/
void SMsgReader::cmdMouseLeftDown()
{
    qDebug() << __FUNCTION__;

    int32_t xPos = 0;
    int32_t yPos = 0;

    CMDData cmdData;
    cmdData.SetData(m_msgData);
    cmdData.GetX(xPos);
    cmdData.GetY(yPos);

    SMsgHandler::mouseLeftDown(xPos, yPos);
}

/*
* @brief
*/
void SMsgReader::cmdMouseLeftUp()
{
    qDebug() << __FUNCTION__;

    int32_t xPos = 0;
    int32_t yPos = 0;

    CMDData cmdData;
    cmdData.SetData(m_msgData);
    cmdData.GetX(xPos);
    cmdData.GetY(yPos);

    SMsgHandler::mouseLeftUp(xPos, yPos);
}

/*
* @brief
*/
void SMsgReader::cmdMouseRightDown()
{
    qDebug() << __FUNCTION__;

    int32_t xPos = 0;
    int32_t yPos = 0;

    CMDData cmdData;
    cmdData.SetData(m_msgData);
    cmdData.GetX(xPos);
    cmdData.GetY(yPos);

    SMsgHandler::mouseRightDown(xPos, yPos);
}

/*
* @brief
*/
void SMsgReader::cmdMouseRightUp()
{
    qDebug() << __FUNCTION__;

    int32_t xPos = 0;
    int32_t yPos = 0;

    CMDData cmdData;
    cmdData.SetData(m_msgData);
    cmdData.GetX(xPos);
    cmdData.GetY(yPos);

    SMsgHandler::mouseRightUp(xPos, yPos);
}

/*
* @brief
*/
void SMsgReader::cmdMouseDoubleClick()
{
    qDebug() << __FUNCTION__;

    int32_t xPos = 0;
    int32_t yPos = 0;

    CMDData cmdData;
    cmdData.SetData(m_msgData);
    cmdData.GetX(xPos);
    cmdData.GetY(yPos);

    SMsgHandler::mouseLeftDown(xPos, yPos);
    SMsgHandler::mouseLeftUp(xPos, yPos);
    SMsgHandler::mouseLeftDown(xPos, yPos);
    SMsgHandler::mouseLeftUp(xPos, yPos);
}

/*
* @brief
*/
void SMsgReader::cmdMouseWheel()
{
    qDebug() << __FUNCTION__;

    int32_t xPos = 0;
    int32_t yPos = 0;
    int32_t delta = 0;

    CMDData cmdData;
    cmdData.SetData(m_msgData);
    cmdData.GetX(xPos);
    cmdData.GetY(yPos);
    cmdData.GetDelta(delta);

    SMsgHandler::mouseWheel(delta, xPos, yPos);
}

/*
* @brief
*/
void SMsgReader::cmdScreenSize()
{
    qDebug() << __FUNCTION__;

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

/*
* @brief special process alt left+tab
*/
void SMsgReader::cmdKeySpAltLTab()
{
    qDebug() << __FUNCTION__;

    //! alt press + tab press, tab release, alt press release
    //! alt
    const int32_t altKey = 18;
    const int32_t altScanCode = 56;
    const int32_t altVirtualKey = 18;
    const int32_t altModifier = 134217728;

    //! tab
    const int32_t tabKey = 9;
    const int32_t tabScanCode = 15;
    const int32_t tabVirtualKey = 9;
    const int32_t tabModifier = 0;
    
    /*
    @brief  In the current case, use kbValue of CMDData
            storage tab wether release.
    */
    int32_t keyValue = 0;
    CMDData cmdData;
    cmdData.SetData(m_msgData);
    cmdData.GetKeyValue(keyValue);

    //! special process
    CMDTYPE cmdType = CMDTYPE::CMD_UNKNOWN;
    cmdType = static_cast<CMDTYPE>(keyValue);
    if (cmdType == CMDTYPE::CMD_KEY_RELEASE) {
        //! tab release
        SMsgHandler::keyReleased(tabKey, tabScanCode, tabVirtualKey, tabModifier);
    }
    else
    {
        //! alt press + alt press
        SMsgHandler::keyPressed(altKey, altScanCode, altVirtualKey, altModifier);
        SMsgHandler::keyPressed(tabKey, tabScanCode, tabVirtualKey, tabModifier);
    }
}

/*
* @brief special process alt right+tab
*/
void SMsgReader::cmdKeySpAltRTab()
{
    qDebug() << __FUNCTION__;

#if 1

    //! alt press + tab press, tab release, alt press release
    //! alt
    int32_t altKey = 18;
    int32_t altScanCode = 56;
    int32_t altVirtualKey = 18;
    int32_t altModifier = 134217728;

    //! tab
    int32_t tabKey = 9;
    int32_t tabScanCode = 15;
    int32_t tabVirtualKey = 9;
    int32_t tabModifier = 0;

    SMsgHandler::keyPressed(altKey, altScanCode, altVirtualKey, altModifier);
    SMsgHandler::keyPressed(tabKey, tabScanCode, tabVirtualKey, tabModifier);

    SMsgHandler::keyReleased(altKey, altScanCode, altVirtualKey, 0);
    SMsgHandler::keyReleased(tabKey, tabScanCode, tabVirtualKey, tabModifier);

#else

    SMsgHandler::switchWindow();

#endif // 0

}

void SMsgReader::cmdKeySpWinL()
{
    qDebug() << __FUNCTION__;

    SMsgHandler::lockScreen();
}

