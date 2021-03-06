
#pragma once

/*
@brief
*/

typedef void (*pfnCb)(void* user, void* param);

typedef struct CallBack
{
    pfnCb cb;
    void* user;
    void* param;

    CallBack()
    {
        cb      = nullptr;
        user    = nullptr;
        param   = 0;
    }

}CallBack;

class CKeyAssistant {

public:
	virtual ~CKeyAssistant() {

	}

public:
	CKeyAssistant();
	void Init();

	//! set callback
	void SetCallBack(CallBack cb);

public:
	virtual void Process() = 0;

protected:
    CallBack m_pCb;
};

