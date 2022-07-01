#pragma once

#include <QTcpSocket>

void writeAndBlock(QTcpSocket* socket, uchar* buf, int len);
void readAndBlock(QTcpSocket* socket, uchar* buf, int len);

int getMin(int, int);

