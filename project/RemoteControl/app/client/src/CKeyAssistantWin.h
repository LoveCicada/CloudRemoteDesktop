
#pragma once

#include "CKeyAssistant.h"


/*
@brief
*/

class CMDData;

class CKeyAssistantWin final : public CKeyAssistant
{
public:
	CKeyAssistantWin();
	~CKeyAssistantWin();
	void InitHanlde();

public:
	virtual void Process() override;

public:
	static void Notify(CMDData& cmdData);

protected:
	void SetHook();
	void UnSetHook();
	void SendKeyMsg(CMDData& cmdData);

private:
	static CKeyAssistantWin* m_pOwner;
};

