#include "CMsgReader.h"
#include "RWSocket.h"
#include "consts.h"

CMsgReader::CMsgReader(QString add, int p, int w, int h, QObject *parent) :
    QThread(parent)
{
    mapSocket = new QTcpSocket;
    address   = add;
    port      = p;
    socketConnected = false;

    request_width  = w;
    request_height = h;
    connect(mapSocket, SIGNAL(connected()), this, SLOT(hostConnected()));
    connect(mapSocket, SIGNAL(readyRead()), this, SLOT(newData()));

    recv_buf  = new uchar[BLOCK_WIDTH * BLOCK_HEIGHT * 3];
    frame_buf = new uchar[20000000];
    frame_buf_fill = 0;
    cmd_buf_fill = 0;
    image = 0;

    cmd_got = false;
    frame_size_setted = false;
    received_frame_width = -1;
    received_frame_height = -1;

    cmd_parsed = false;
    subX = 0;
    subY = 0;
    subWidth  = 0;
    subHeight = 0;
    subSize   = 0;
    subFill   = 0;

    mapSocket->connectToHost(address, port);
}

void CMsgReader::run()
{
    QThread::run();
}

void CMsgReader::hostConnected()
{
    qDebug() << "CMsgReader socker connected successful";
    socketConnected = true;
    sendRequestSize(request_width, request_height);
}

void CMsgReader::sendRequestSize(int width, int height)
{
    request_width = width;
    request_height = height;
    uchar uc[4];
    uc[0] = width / 0x100;
    uc[1] = width % 0x100;
    uc[2] = height / 0x100;
    uc[3] = height % 0x100;
    writeAndBlock(mapSocket, uc, 4);
}

void CMsgReader::newData()
{
    //qDebug()<<"new data";
    if(cmd_got == false)
    {
        while(true)
        {
            int r = mapSocket->read((char*)(cmd_buf + cmd_buf_fill), 8 - cmd_buf_fill);
            if(r <= 0)
                return;

            cmd_buf_fill += r;
            if(cmd_buf_fill == 8)
            {
                cmd_buf_fill = 0;
                cmd_got = true;
                break;
            }
        }
    }
    parseCommand();
}

void CMsgReader::parseCommand()
{
    if(cmd_parsed == false)
    {
        uchar* uc = (uchar*)cmd_buf;
        uint x = uc[0];
        x = x << 8;
        x += uc[1];
        uint y = uc[2];
        y = y << 8;
        y += uc[3];
        uint width = uc[4];
        width = width << 8;
        width += uc[5];
        uint height = uc[6];
        height = height << 8;
        height += uc[7];
        //qDebug()<<x <<" "<<y<<" "<<width<<" "<<height;
        if(width == 0 || height == 0)
        {
            if(height == 0)
            {
                updateFrame();
            }
            else
            {
                received_frame_width = x;
                received_frame_height = y;
                if(frame_size_setted == false)
                {
                    emit frameSizeChanged(received_frame_width, received_frame_height);
                    frame_size_setted = true;
                }
            }
            cmd_got = false;
            cmd_buf_fill = 0;
            return;
        }
        subX = x;
        subY = y;
        subWidth  = width;
        subHeight = height;
        subSize   = width * height * 3;
        subFill   = 0;
        cmd_parsed = true;
    }
    getSubWindow();
}

void CMsgReader::getSubWindow()
{
    while(true)
    {
        int r = mapSocket->read((char*)(recv_buf + subFill),subSize - subFill);
        if(r <= 0)
        {
            return;
        }
        subFill += r;
        if(subFill == subSize)
        {
            uchar* fp = frame_buf + subY * received_frame_width * 3 + subX * 3;
            for(int i = 0; i < subHeight; i ++)
            {
                //memcpy(fp + i * received_frame_width * 3, recv_buf + i * BLOCK_WIDTH * 3, BLOCK_WIDTH * 3);
                memcpy(fp + i * received_frame_width * 3, recv_buf + i * subWidth * 3, subWidth * 3);
            }
            cmd_got = false;
            cmd_buf_fill = 0;
            cmd_parsed = false;
            return;
        }
    }
    newData();
}

void CMsgReader::updateFrame()
{
    if(image != 0)
        delete image;
    image = new QImage(frame_buf, received_frame_width, received_frame_height, QImage::Format_RGB888);

    emit frameGot(image);

    cmd_got = false;
    frame_size_setted = false;
}
