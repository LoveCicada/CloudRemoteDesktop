#pragma once

/**
 * @file RWSocket.h
 * @author dyf
 * @brief 
 * @version 0.1
 * @date 2022-07-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "ExportMacro.h"

class QTcpSocket;

void RTC_EXPORT BlockWriteSocketData(QTcpSocket* socket, char* buf, int len);
void RTC_EXPORT BlockReadSocketData(QTcpSocket* socket, char* buf, int len);


