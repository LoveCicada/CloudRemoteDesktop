
#pragma once

/*
@brief basic common
*/

#include <QThread>

/*
@brief Extend QThread Class
*/

class RCThread : public QThread
{
	Q_OBJECT

public:
	RCThread(QObject* parent = 0);
	~RCThread();

public:
	virtual void Extend(void* param = nullptr);

};

