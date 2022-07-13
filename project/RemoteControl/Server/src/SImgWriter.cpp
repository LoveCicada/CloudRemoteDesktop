#include "SImgWriter.h"
#include "SMsgHandler.h"
#include "RWSocket.h"
#include "Command.h"
#include <stdlib.h>

/**
  * send server desktop img to client
  * start a timer
  */
SImgWriter::SImgWriter(QTcpSocket* imgSocket, ServerParmas sp, QObject *parent) :
    RCThread(parent)
{
    m_imgSocket = imgSocket;
    m_serverParmas = sp;

    sent_img_buf  = 0;
    curt_img_buf  = 0;
    send_data_buf = 0;
    cmd_buf_fill = 0;
    interval    = 500;
    started = false;
    memset(cmd_buf, 0, 4);

    connect(m_imgSocket, SIGNAL(readyRead()), this, SLOT(readDataFromClient()));
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(sendFrame()));
    timer->start(interval);
}


void SImgWriter::run()
{
    QThread::run();
}

/*
* when tcp socket have receive new data, read socket data
*/
void SImgWriter::readDataFromClient()
{
    while(true)
    {
        int r = m_imgSocket->read((char*)(cmd_buf + cmd_buf_fill), 4 - cmd_buf_fill);
        if(r <= 0)
            return;
        cmd_buf_fill += r;
        if(cmd_buf_fill == 4)
        {
            readCommand();
            cmd_buf_fill = 0;
        }
    }

}

/**
  *从socket里提取出一条命令时启动
  *目前的命令只有设置目的设备期望图像大小
  */
void SImgWriter::readCommand()
{
    uchar* uc = (uchar*)cmd_buf;
    unsigned short width = uc[0];
    width = width << 8;
    width += uc[1];
    unsigned short height = uc[2];
    height = height << 8;
    height += uc[3];

    dest_width = width;
    dest_height = height;
    if(sent_img_buf != 0)
    {
        delete[] sent_img_buf;
        sent_img_buf = 0;
    }
    sent_img_buf = new uchar[dest_width * dest_height * 3];
    memset(sent_img_buf, 0, dest_width * dest_height * 3);

    if(curt_img_buf != 0)
    {
        delete[] curt_img_buf;
        curt_img_buf = 0;
    }
    curt_img_buf = new uchar[dest_width * dest_height * 3];

    if(send_data_buf != 0)
    {
        delete[] send_data_buf;
        send_data_buf = 0;
    }
    send_data_buf = new uchar[dest_width * dest_height * 3 * 2];

    unsigned short usW = 0;
    unsigned short usH = 0;
    m_serverParmas.GetScreenWidth(usW);
    m_serverParmas.GetScreenHeight(usH);

    double scale_x = (double)dest_width / usW;
    double scale_y = (double)dest_height / usH;

    if(scale_x < scale_y)
        scaleby = SCALE_BY_WIDTH;
    else
        scaleby = SCALE_BY_HEIGHT;

    started = true;
}

/**
  *发送一帧图像
  *前四字节为所发送图像的尺寸，从低字节到高字节依次为width_high, width_low, height_high, height_low
  *后面为图像数据，每个像素3个字节，依次为RGB通道
  */
void SImgWriter::sendFrame()
{
    bool bConnect = checkConnect();
    if (!bConnect) {
        return;
    }

    QImage image = SMsgHandler::grapScreen().toImage();
    QImage img;
    if(scaleby == SCALE_BY_WIDTH)
    {
        img = image.scaledToWidth(dest_width);
    }
    else if(scaleby == SCALE_BY_HEIGHT)
    {
        img = image.scaledToHeight(dest_height);
    }
    int width  = img.width();
    int height = img.height();
    send_width = width;
    send_height = height;

    int bytes = m_imgSocket->bytesToWrite();
    //qDebug()<<"bytes to write"<<bytes;
    if(bytes > ((send_width * send_height * 3 + 4) * 2))
    {
        qDebug()<<"abort writing";
        return;
    }

    for(int i = 0; i < height; i ++)
    {
        uchar* p = curt_img_buf + width * i * 3;
        for(int j = 0; j < width; j ++)
        {
            QRgb rgb   = img.pixel(j, i);
            p[j*3]       = qRed(rgb);
            p[j*3 + 1]   = qGreen(rgb);
            p[j*3 + 2]   = qBlue(rgb);
        }
    }

    int fill = 0;
    send_data_buf[fill] = width  / 0x100;
    send_data_buf[fill+1] = width  % 0x100;
    send_data_buf[fill+2] = height / 0x100;
    send_data_buf[fill+3] = height % 0x100;
    send_data_buf[fill+4] = 0;
    send_data_buf[fill+5] = 0;
    send_data_buf[fill+6] = 0;
    send_data_buf[fill+7] = 1;
    fill += 8;
    int block_width, block_height;
    for(int hi = 0; hi*BLOCK_HEIGHT < height; hi ++)
    {
        for(int wi = 0; wi*BLOCK_WIDTH < width; wi ++)
        {
            block_width = std::min(BLOCK_WIDTH, width - wi*BLOCK_WIDTH);
            block_height = std::min(BLOCK_HEIGHT, height - hi * BLOCK_HEIGHT);
            //block_width = (BLOCK_WIDTH <= (width - wi*BLOCK_WIDTH)) ? BLOCK_WIDTH : (width - wi*BLOCK_WIDTH);
            //block_height = (BLOCK_HEIGHT <= (height - hi * BLOCK_HEIGHT)) ? BLOCK_HEIGHT : (height - hi * BLOCK_HEIGHT);
            int diff = 0;
            uchar* cp = curt_img_buf + hi * BLOCK_HEIGHT * width * 3 + wi * BLOCK_WIDTH * 3;
            uchar* sp = sent_img_buf + hi * BLOCK_HEIGHT * width * 3 + wi * BLOCK_WIDTH * 3;
            for(int i = 0; i < block_height && diff <= DIFF_THN; i ++)
            {
                for(int j = 0; j < block_width && diff <= DIFF_THN; j ++)
                {
                    if(abs(cp[i*width*3+j*3] - sp[i*width*3+j*3]) >= DIFF_PIX)
                        diff ++;
                    else if(abs(cp[i*width*3+j*3 + 1] - sp[i*width*3+j*3 + 1]) >= DIFF_PIX)
                        diff ++;
                    else if(abs(cp[i*width*3+j*3 + 2] - sp[i*width*3+j*3 + 2]) >= DIFF_PIX)
                        diff ++;
                }
            }
            if(diff < DIFF_THN)
                continue;
            int x = wi * BLOCK_WIDTH;
            int y = hi * BLOCK_HEIGHT;
            send_data_buf[fill] = x  / 0x100;
            send_data_buf[fill+1] = x  % 0x100;
            send_data_buf[fill+2] = y / 0x100;
            send_data_buf[fill+3] = y % 0x100;
            send_data_buf[fill+4] = block_width  / 0x100;
            send_data_buf[fill+5] = block_width  % 0x100;
            send_data_buf[fill+6] = block_height / 0x100;
            send_data_buf[fill+7] = block_height % 0x100;
            fill += 8;
            for(int i = 0; i < block_height; i ++)
            {
                memcpy(send_data_buf + fill + i * block_width * 3, cp + i * width * 3, block_width * 3);
            }
            fill += block_width * block_height * 3;
        }
    }

    send_data_buf[fill] = 0;
    send_data_buf[fill+1] = 0;
    send_data_buf[fill+2] = 0;
    send_data_buf[fill+3] = 0;
    send_data_buf[fill+4] = 0;
    send_data_buf[fill+5] = 1;
    send_data_buf[fill+6] = 0;
    send_data_buf[fill+7] = 0;
    fill += 8;

    BlockWriteSocketData(m_imgSocket, (char*)(send_data_buf), fill);
#if 0
    qDebug() << "fill:" << fill;
#endif // 0

    uchar* tp;
    tp = sent_img_buf;
    sent_img_buf = curt_img_buf;
    curt_img_buf  = tp;
}


void SImgWriter::setSendInterval(int i)
{
    timer->setInterval(i);
}

void SImgWriter::sendServerParams()
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
    uc[0] = static_cast<unsigned char>(CMDTYPE::CMD_SEND_SERVER_SCREEN_SIZE);
    uc[1] = usW / 0x100;
    uc[2] = usW % 0x100;
    uc[3] = usH / 0x100;
    uc[4] = usH % 0x100;
    BlockWriteSocketData(m_imgSocket, (char*)uc, 8);
}

bool SImgWriter::checkConnect()
{
    bool bRet = false;
    if (!started)
        return bRet;
    if (m_imgSocket == 0)
    {
        qDebug() << "null socket" << endl;
        return bRet;
    }
    else if (m_imgSocket->isOpen() == false)
    {
        qDebug() << "socket not open" << endl;
        return bRet;
    }
    else if (m_imgSocket->isWritable() == false)
    {
        qDebug() << "socket not writable" << endl;
        return bRet;
    }

    bRet = true;
    return bRet;
}

void SImgWriter::quit()
{
    if(timer)
        timer->stop();
    QThread::quit();
}

SImgWriter::~SImgWriter()
{
    if(timer)
    {
        if(timer->isActive())
        {
            timer->stop();
        }
        delete timer;
        timer = 0;
    }
    if(m_imgSocket)
    {
        if(m_imgSocket->isOpen())
        {
            m_imgSocket->close();
        }
        delete m_imgSocket;
        m_imgSocket = 0;
    }
    if(sent_img_buf != 0)
        delete[] sent_img_buf;
    if(curt_img_buf != 0)
        delete[] curt_img_buf;
    if(send_data_buf != 0)
        delete[] send_data_buf;

    qDebug() << __func__;
}

void SImgWriter::Extend(void* param)
{
    static_cast<void*>(param);
    qDebug() << __func__;
}
