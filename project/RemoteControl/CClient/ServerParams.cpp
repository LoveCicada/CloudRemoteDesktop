
#include "ServerParams.h"

ServerParmas::ServerParmas()
{
	Init();
}

ServerParmas::~ServerParmas()
{

}

void ServerParmas::Init()
{
	m_screenWidth	= 0;
	m_screenHeight	= 0;
	m_serverName	= "";
}

void ServerParmas::SetScreenWidth(unsigned short usW)
{
	m_screenWidth = usW;
}

void ServerParmas::SetScreenHeight(unsigned short usH)
{
	m_screenHeight = usH;
}

void ServerParmas::SetServerName(string serverName)
{
	m_serverName = serverName;
}

void ServerParmas::GetScreenWidth(unsigned short& usW)
{
	usW = m_screenWidth;
}

void ServerParmas::GetScreenHeight(unsigned short& usH)
{
	usH = m_screenHeight;
}

void ServerParmas::GetServerName(string& serverName)
{
	serverName = m_serverName;
}
