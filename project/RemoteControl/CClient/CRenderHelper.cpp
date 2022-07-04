
#include "CRenderHelper.h"

CRenderHelper::CRenderHelper()
{
	Init();
}

CRenderHelper::CRenderHelper(const CRenderHelper& ch)
{
	m_windowHanlde = ch.m_windowHanlde;
	m_wndWidth = ch.m_wndWidth;
	m_wndHeight = ch.m_wndHeight;
	m_pParam = ch.m_pParam;
}

CRenderHelper::~CRenderHelper()
{
	Release();
}

void CRenderHelper::Init()
{
	m_windowHanlde = nullptr;
	m_pParam = nullptr;
	m_wndWidth = 0;
	m_wndHeight = 0;
}

void CRenderHelper::Release()
{
	m_windowHanlde = nullptr;
	m_pParam = nullptr;
	m_wndWidth = 0;
	m_wndHeight = 0;
}

bool CRenderHelper::SetWindowHanlde(QWindow*& qw)
{
	bool bRet = true;

	m_windowHanlde = qw;

	return bRet;
}

bool CRenderHelper::GetWindowsHanlde(QWindow*& qw)
{
	bool bRet = true;

	qw = m_windowHanlde;

	return bRet;
}

bool CRenderHelper::SetWndWidth(unsigned int uiW)
{
	bool bRet = true;

	m_wndWidth = uiW;

	return bRet;
}

bool CRenderHelper::GetWndWidth(unsigned int& uiW)
{
	bool bRet = true;

	uiW = m_wndWidth;

	return bRet;
}

bool CRenderHelper::SetWndHeight(unsigned int uiH)
{
	bool bRet = true;

	m_wndHeight = uiH;

	return bRet;
}

bool CRenderHelper::GetWndHeight(unsigned int& uiH)
{
	bool bRet = true;

	uiH = m_wndWidth;

	return bRet;
}

bool CRenderHelper::SetParam(void* param)
{
	bool bRet = true;

	m_pParam = param;

	return bRet;
}

bool CRenderHelper::GetParam(void* param)
{
	bool bRet = true;

	param = m_pParam;

	return bRet;
}

void CRenderHelper::Render()
{

}
