#include "CMsgReader.h"
#include "RWSocket.h"


CMsgReader::CMsgReader(QString add, int p, QObject *parent) :
    m_address(add), m_port(p), QThread(parent)
{
    Init();
}

CMsgReader::~CMsgReader()
{
    qDebug() << __FUNCTION__;
    quit();
    wait();
}

void CMsgReader::Init()
{
    InitData();
}

void CMsgReader::InitData()
{
    m_bSocketConnected = false;
    cmdReadLength = 0;
    cmdLength = msgProtocolLength;

    m_msgSocket = make_shared<QTcpSocket>();
    connect(m_msgSocket.get(), SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(connectError(QAbstractSocket::SocketError)));
    connect(m_msgSocket.get(), SIGNAL(connected()), this, SLOT(hostConnected()));
    connect(m_msgSocket.get(), SIGNAL(readyRead()), this, SLOT(readMsgFromServer()));
    m_msgSocket->connectToHost(m_address, m_port);
}

void CMsgReader::run()
{
    QThread::run();
}

void CMsgReader::connectError(QAbstractSocket::SocketError)
{
    qDebug() << __FILE__ << " " << __func__;
    m_msgSocket->abort();
    m_msgSocket->close();
}

void CMsgReader::hostConnected()
{
    qDebug() << "CMsgReader socker connected successful";
    m_bSocketConnected = true;
}

void CMsgReader::readMsgFromServer()
{
    qDebug() << __func__;

    while(true)
    {
        qint64 r = m_msgSocket->read((char*)(cmd_buf + cmdReadLength), cmdLength - cmdReadLength);
        if(r <= 0)
            return;

        cmdReadLength += r;
        if(cmdReadLength == cmdLength)
        {
            cmdReadLength = 0;
            break;
        }
    }

    processMsg();
}

void CMsgReader::processMsg()
{
    CMDData cmdData;
    cmdData.SetData(cmd_buf);
    CMDTYPE cmdType = CMDTYPE::CMD_UNKNOWN;
    cmdData.GetCMD(cmdType);

    switch (cmdType)
    {
    case CMDTYPE::CMD_UNKNOWN:
        break;
    case CMDTYPE::CMD_MOUSE_MOVE_TO:
        break;
    case CMDTYPE::CMD_MOUSE_LEFT_DOWN:
        break;
    case CMDTYPE::CMD_MOUSE_LEFT_UP:
        break;
    case CMDTYPE::CMD_MOUSE_RIGHT_DOWN:
        break;
    case CMDTYPE::CMD_MOUSE_RIGHT_UP:
        break;
    case CMDTYPE::CMD_MOUSE_WHEEL:
        break;
    case CMDTYPE::CMD_MOUSE_DOUBLE_CLICK:
        break;
    case CMDTYPE::CMD_KEY_PRESS:
        break;
    case CMDTYPE::CMD_KEY_RELEASE:
        break;
    case CMDTYPE::CMD_GET_SCREEN_SIZE:
        break;
    case CMDTYPE::CMD_GET_SCREEN_SIZE_RES:
        break;
    case CMDTYPE::CMD_SEND_SERVER_SCREEN_SIZE:
        qDebug() << __FUNCTION__ << "line: " << __LINE__ 
                << " msgType: " <<  static_cast<int>(cmdType);
        readServerParamsMsg(cmdData);
        break;
    default:
        break;
    }

}

void CMsgReader::readServerParamsMsg(CMDData& cmdData)
{
    int32_t iW = 0;
    int32_t iH = 0;
    cmdData.GetW(iW);
    cmdData.GetH(iH);

    m_serverParmas.SetScreenWidth(iW);
    m_serverParmas.SetScreenHeight(iH);

    emit readServerParams(m_serverParmas);

    qDebug() << __func__ << iW;
    qDebug() << __func__ << iH;
}

