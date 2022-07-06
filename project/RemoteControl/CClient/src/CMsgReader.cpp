#include "CMsgReader.h"
#include "RWSocket.h"


CMsgReader::CMsgReader(QString add, int p, int w, int h, QObject *parent) :
    m_address(add), m_port(p), request_width(w), request_height(h), QThread(parent)
{
    Init();
}

CMsgReader::~CMsgReader()
{
    qDebug() << __func__;
}

void CMsgReader::Init()
{
    InitData();
}

void CMsgReader::InitData()
{
    socketConnected = false;
    frame_buf_fill = 0;
    cmdReadLength = 0;
    cmdLength = 8;
    image = 0;

    frame_size_setted = false;
    received_frame_width = -1;
    received_frame_height = -1;

    subX = 0;
    subY = 0;
    subWidth = 0;
    subHeight = 0;
    subSize = 0;
    subFill = 0;

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
    socketConnected = true;
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
    ClientCMDData cmdData;
    cmdData.SetData(cmd_buf);
    CMDTYPE cmdType = cmdData.GetCMD();

    switch (cmdType)
    {
    case CMD_UNKNOWN:
        break;
    case CMD_MOUSE_MOVE_TO:
        break;
    case CMD_MOUSE_LEFT_DOWN:
        break;
    case CMD_MOUSE_LEFT_UP:
        break;
    case CMD_MOUSE_RIGHT_DOWN:
        break;
    case CMD_MOUSE_RIGHT_UP:
        break;
    case CMD_MOUSE_WHEEL:
        break;
    case CMD_MOUSE_DOUBLE_CLICK:
        break;
    case CMD_KEY_PRESS:
        break;
    case CMD_KEY_RELEASE:
        break;
    case CMD_GET_SCREEN_SIZE:
        break;
    case CMD_GET_SCREEN_SIZE_RES:
        break;
    case CMD_SEND_SERVER_SCREEN_SIZE:
        qDebug() << "CMsgReader " << __func__ << cmdType;
        readServerParamsMsg(cmdData);
        break;
    default:
        break;
    }

}

void CMsgReader::readServerParamsMsg(ClientCMDData& cmdData)
{
    unsigned short usW = 0;
    unsigned short usH = 0;
    usW = cmdData.GetW();
    usH = cmdData.GetH();

    m_serverParmas.SetScreenWidth(usW);
    m_serverParmas.SetScreenHeight(usH);

    emit readServerParams(m_serverParmas);

    qDebug() << __func__ <<usW;
    qDebug() << __func__ << usH;
}

