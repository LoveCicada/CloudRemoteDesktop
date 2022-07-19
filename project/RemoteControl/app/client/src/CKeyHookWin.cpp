
#ifdef _WIN32
#include "Windows.h"
#endif // _WIN32

#include <iostream>
#include "CKeyHookWin.h"
#include "Command.h"
#include "CKeyAssistantWin.h"

using std::cout;
using std::endl;

//************************************
CkeyHookWinAltTab::~CkeyHookWinAltTab()
{

}

//! WPARAM wParam, LPARAM lParam
//! unsigned __int64, __int64
int CkeyHookWinAltTab::Hook(xuint64 wParam, xint64 lParam)
{
	static_cast<xuint64>(wParam);

	PKBDLLHOOKSTRUCT p;
	p = (PKBDLLHOOKSTRUCT)lParam;

	//! <0, down; >0, up
	bool bLAltDown = GetKeyState(VK_LMENU) < 0 ? true : false;
	bool bRAltDown = GetKeyState(VK_RMENU) < 0 ? true : false;

	CMDData cmdData;
	if (bLAltDown) {
		cmdData.SetCMD(CMDTYPE::CMD_KEY_SP_ALTL_TAB);
	}
	else if (bRAltDown) {
		cmdData.SetCMD(CMDTYPE::CMD_KEY_SP_ALTR_TAB);
	}

	//!VK_TAB
#if 0

	bool bTabUp = GetKeyState(VK_TAB) >0 ? true : false;
	if (bTabUp) {
		//! tab release
		cmdData.SetKeyValue(static_cast<int32_t>(CMDTYPE::CMD_KEY_RELEASE));
	}

#else

	if (WM_SYSKEYUP == wParam) {
		//! tab release
		cmdData.SetKeyValue(static_cast<int32_t>(CMDTYPE::CMD_KEY_RELEASE));
	}

#endif // 0

	cout << __FUNCTION__ << " catch alt+tab" << " wParam: " << wParam << endl;
	CKeyAssistantWin::Notify(cmdData);
	return 1;
}

//************************************
CkeyHookWinWinL::~CkeyHookWinWinL()
{

}

int CkeyHookWinWinL::Hook(xuint64 wParam, xint64 lParam)
{
	static_cast<xuint64>(wParam);

	PKBDLLHOOKSTRUCT p;
	p = (PKBDLLHOOKSTRUCT)lParam;

	//! <0, down; >0, up
	bool bLWinDown = GetKeyState(VK_LWIN) < 0 ? true : false;
	bool bRWinDown = GetKeyState(VK_RWIN) < 0 ? true : false;

	CMDData cmdData;
	if (bLWinDown) {
		cmdData.SetCMD(CMDTYPE::CMD_KEY_SP_WIN_L);
	}
	else if (bRWinDown) {
		cmdData.SetCMD(CMDTYPE::CMD_KEY_SP_WIN_L);
	}

	cout << __func__ << " catch win+L" << endl;
	CKeyAssistantWin::Notify(cmdData);
	return 1;
}
