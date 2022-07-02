#ifndef ALGO_H
#define ALGO_H

#include <QTcpSocket>

void BlockWriteSocketData(QTcpSocket* socket, uchar* buf, int len);
void BlockReadSocketData(QTcpSocket* socket, uchar* buf, int len);

#endif // ALGO_H
