
#pragma once

#include "CKeyHook.h"

class CKeyHookWin : public CKeyHook
{
public:
	virtual ~CKeyHookWin() {

	}

public:
	virtual int Hook(xuint64 wParam, xint64 lParam) = 0;

};

/*
@brief alt + tab
*/
class CkeyHookWinAltTab
{
public:
	~CkeyHookWinAltTab();

public:
	int Hook(xuint64 wParam, xint64 lParam);
};


/*
@brief win + l/L
*/
class CkeyHookWinWinL
{
public:
	~CkeyHookWinWinL();

public:
	int Hook(xuint64 wParam, xint64 lParam);
};
