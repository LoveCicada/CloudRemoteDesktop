#pragma once

class QTcpSocket;

void BlockWriteSocketData(QTcpSocket* socket, char* buf, int len);
void BlockReadSocketData(QTcpSocket* socket, char* buf, int len);


