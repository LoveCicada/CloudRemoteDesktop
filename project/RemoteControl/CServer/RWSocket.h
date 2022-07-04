#pragma once

#include <QTcpSocket>

void BlockWriteSocketData(QTcpSocket* socket, uchar* buf, int len);
void BlockReadSocketData(QTcpSocket* socket, uchar* buf, int len);

int getMin(int, int);

