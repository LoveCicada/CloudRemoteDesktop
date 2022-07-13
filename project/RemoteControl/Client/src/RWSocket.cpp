

#include <QTcpSocket>
#include "RWSocket.h"

void BlockWriteSocketData(QTcpSocket* socket, char* buf, int len)
{
    int fill = 0;
    int w;
    while(true)
    {
        if (buf[0] == 0) {
            qDebug() << __FUNCTION__ << " msg error";
        }

        w = socket->write((char*)(buf + fill), len - fill);
        if(w > 0)
        {
            fill += w;
        }
        if(fill == len)
            break;
    }
    bool bOk = socket->flush();
    if (!bOk) {
        qDebug() << __func__ << " send data fail";
    }
}

void BlockReadSocketData(QTcpSocket* socket, char* buf, int len)
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

