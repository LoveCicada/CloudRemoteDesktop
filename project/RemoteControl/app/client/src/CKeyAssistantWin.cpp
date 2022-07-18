
#include "CKeyAssistantWin.h"
#include "Command.h"
#include "Windows.h"
#include <iostream>
using std::cout;
using std::endl;

HHOOK g_hKeyBoard;
int nativeVirtualKeyBefore = 0;

//! bottom keyboard system caller, filter alt+tab
static LRESULT CALLBACK KeyBoardProc(int code, WPARAM wParam, LPARAM lParam)
{

	if (code == HC_ACTION)
	{
		PKBDLLHOOKSTRUCT p;

		switch (wParam)
		{
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYUP:
			p = (PKBDLLHOOKSTRUCT)lParam;

			{
				//! log
				p->flags;
				p->vkCode;
				p->scanCode;
				p->dwExtraInfo;
				cout << "flags: " << p->flags << " vkCode: " << p->vkCode
					<< "scanCode: " << p->scanCode << " dwExtraInfo: " << p->dwExtraInfo << endl;
				cout << endl;
			}

			//! alt + tab
			if ((p->vkCode == VK_TAB) && ((p->flags & LLKHF_ALTDOWN) != 0))
			{
				nativeVirtualKeyBefore = 0;
				cout << __func__ << " catch alt+tab" << endl;
				CMDTYPE cmdType = CMDTYPE::CMD_KEY_SP_ALTL_TAB;
				CKeyAssistantWin::Notify(static_cast<int>(cmdType));
				return 1;
			}
#if 0
			//! win + l, L key value = 0x4C
			else if ((p->vkCode == VK_LWIN) && ((p->flags & 0x4C) != 0))
			{
				cout << __func__ << " catch win+L" << endl;
				CMDTYPE cmdType = CMDTYPE::CMD_KEY_SP_WIN_L;
				CKeyAssistantWin::Notify(static_cast<int>(cmdType));
				return 1;

			}
#endif // 0
			//! left win + l, L key value = 0x4C
			else if ((p->vkCode == 0x4C) && (nativeVirtualKeyBefore == VK_LWIN))
			{
				nativeVirtualKeyBefore = 0;
				cout << __func__ << " catch win+L" << endl;
				CMDTYPE cmdType = CMDTYPE::CMD_KEY_SP_WIN_L;
				CKeyAssistantWin::Notify(static_cast<int>(cmdType));
				return 1;

			}
			//! right win + l, L key value = 0x4C
			else if ((p->vkCode == 0x4C) && (nativeVirtualKeyBefore == VK_RWIN))
			{
				nativeVirtualKeyBefore = 0;
				cout << __func__ << " catch win+L" << endl;
				CMDTYPE cmdType = CMDTYPE::CMD_KEY_SP_WIN_L;
				CKeyAssistantWin::Notify(static_cast<int>(cmdType));
				return 1;

			}

			nativeVirtualKeyBefore = static_cast<int>(p->vkCode);

			break;
		}
	}

	return ::CallNextHookEx(g_hKeyBoard, code, wParam, lParam);
}

//! register global hook
static void SetHookEx()
{
	HMODULE hModule = GetModuleHandle("Hook");
	HMODULE hModuleUser = LoadLibrary("user32.dll");
	static_cast<HMODULE>(hModule);
	static_cast<HMODULE>(hModuleUser);
	g_hKeyBoard = SetWindowsHookEx(WH_KEYBOARD_LL, KeyBoardProc, hModuleUser, 0);
	DWORD err = GetLastError();
	cout << __func__ << " err: " << err << endl;
}

//! unregister global hook
static void UnSetHookEx()
{
	if (g_hKeyBoard) {
		UnhookWindowsHookEx(g_hKeyBoard);
		DWORD err = GetLastError();
		cout << __func__ << " err: " << err << endl;
	}

	g_hKeyBoard = NULL;
}

CKeyAssistantWin* CKeyAssistantWin::m_pOwner = nullptr;

CKeyAssistantWin::CKeyAssistantWin()
{
	InitHanlde();
	SetHook();
}

CKeyAssistantWin::~CKeyAssistantWin()
{
	UnSetHook();
	m_pOwner = nullptr;
}

void CKeyAssistantWin::InitHanlde()
{
	m_pOwner = this;
}

void CKeyAssistantWin::Process()
{
	
}

void CKeyAssistantWin::SetHook()
{
	SetHookEx();
}

void CKeyAssistantWin::UnSetHook()
{
	UnSetHookEx();
}

void CKeyAssistantWin::SendKeyMsg(int cmdType)
{
	static_cast<CMDTYPE>(cmdType);
	if (m_pCb.cb && m_pCb.user) {
		m_pCb.param = static_cast<int>(cmdType);
		m_pCb.cb(m_pCb.user, m_pCb.param);
	}
}

void CKeyAssistantWin::Notify(int cmdType)
{
	cout << __func__ << endl;
	if (m_pOwner) {
		m_pOwner->SendKeyMsg(cmdType);
	}

}
