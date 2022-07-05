
#include "Common.h"

RCThread::RCThread(QObject* parent) : QThread(parent)
{

}

RCThread::~RCThread()
{

}

void RCThread::Extend(void* param)
{
	static_cast<void*>(param);
}

