
#pragma once

/*
@brief interact with the render module
*/

#include <QOpenGLWidget>

class CRenderHelper
{
public:
	CRenderHelper();
	CRenderHelper(const CRenderHelper& ch);
	~CRenderHelper();

	void Init();
	void Release();

	bool SetWindowHanlde(QOpenGLWidget* qw);
	bool GetWindowsHanlde(QOpenGLWidget* qw);
	bool SetWndWidth(unsigned int uiW);
	bool GetWndWidth(unsigned int& uiW);
	bool SetWndHeight(unsigned int uiH);
	bool GetWndHeight(unsigned int& uiH);
	bool SetParam(void* param);
	bool GetParam(void* param);
	void Render();
	

private:
	QOpenGLWidget* m_pOpenGLWidget;
	unsigned int m_wndWidth;
	unsigned int m_wndHeight;
	void* m_pParam;
};