
#pragma once

/*
@brief interact with the render module
*/

#include <QWindow>

class CRenderHelper
{
public:
	CRenderHelper();
	CRenderHelper(const CRenderHelper& ch);
	~CRenderHelper();

	void Init();
	void Release();

	bool SetWindowHanlde(QWindow*& qw);
	bool GetWindowsHanlde(QWindow*& qw);
	bool SetWndWidth(unsigned int uiW);
	bool GetWndWidth(unsigned int& uiW);
	bool SetWndHeight(unsigned int uiH);
	bool GetWndHeight(unsigned int& uiH);
	bool SetParam(void* param);
	bool GetParam(void* param);
	void Render();
	

private:
	QWindow* m_windowHanlde;
	unsigned int m_wndWidth;
	unsigned int m_wndHeight;
	void* m_pParam;
};