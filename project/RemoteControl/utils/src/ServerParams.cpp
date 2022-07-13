
#include "ServerParams.h"

ServerParmas::ServerParmas()
{
	Init();
}

ServerParmas::~ServerParmas()
{

}

ServerParmas::ServerParmas(const ServerParmas& sp)
{
	m_screenWidth = sp.m_screenWidth;
	m_screenHeight = sp.m_screenHeight;
	//m_serverName = sp.m_serverName;
}

ServerParmas& ServerParmas::operator=(const ServerParmas& sp)
{
	if (this != &sp) {
		m_screenWidth = sp.m_screenWidth;
		m_screenHeight = sp.m_screenHeight;
		//m_serverName = sp.m_serverName;
	}

	return *this;
}

void ServerParmas::Init()
{
	m_screenWidth	= 0;
	m_screenHeight	= 0;
	//m_serverName	= "";
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
	static_cast<void>(serverName);
	//m_serverName = serverName;
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
	static_cast<void>(serverName);
	//serverName = m_serverName;
}
