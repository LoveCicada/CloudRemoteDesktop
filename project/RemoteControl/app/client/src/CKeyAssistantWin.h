
#pragma once

#include "CKeyAssistant.h"


/*
@brief
*/



class CKeyAssistantWin final : public CKeyAssistant
{
public:
	CKeyAssistantWin();
	~CKeyAssistantWin();
	void InitHanlde();

public:
	virtual void Process() override;

public:
	static void Notify(int cmdType);

protected:
	void SetHook();
	void UnSetHook();
	void SendKeyMsg(int cmdType);

private:
	static CKeyAssistantWin* m_pOwner;
};

