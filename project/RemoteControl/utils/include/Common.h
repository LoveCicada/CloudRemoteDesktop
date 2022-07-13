
#pragma once

/**
 * @file Common.h
 * @author duanyafeng
 * @brief basic common
 * @version 0.1
 * @date 2022-07-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "ExportMacro.h"
#include <QThread>

/*
@brief Extend QThread Class
*/

class RTC_EXPORT RCThread : public QThread
{
	Q_OBJECT

public:
	RCThread(QObject* parent = 0);
	~RCThread();

public:
	virtual void Extend(void* param = nullptr);

};

