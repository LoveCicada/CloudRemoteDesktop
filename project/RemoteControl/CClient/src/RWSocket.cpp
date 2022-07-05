#include "RWSocket.h"

void BlockWriteSocketData(QTcpSocket* socket, uchar* buf, int len)
{
    int fill = 0;
    int w;
    while(true)
    {
        w = socket->write((char*)(buf + fill), len - fill);
        if(w > 0)
        {
            fill += w;
        }
        if(fill == len)
            break;
    }
    socket->flush();
}

void BlockReadSocketData(QTcpSocket* socket, uchar* buf, int len)
{
    int fill = 0;
    int r;
    while(true)
    {
        r = socket->read((char*)(buf + fill), len - fill);
        if(r > 0)
        {
            fill += r;
        }
        if(fill == len)
            break;
    }
}

