

#include "ClientParams.h"

ClientParams::ClientParams()
{
	Init();
}

ClientParams::~ClientParams()
{

}

ClientParams::ClientParams(const ClientParams& sp)
{
	m_screenWidth = sp.m_screenWidth;
	m_screenHeight = sp.m_screenHeight;
	//m_clientName = sp.m_clientName;
}

ClientParams& ClientParams::operator=(const ClientParams& sp)
{
	if (this != &sp) {
		m_screenWidth = sp.m_screenWidth;
		m_screenHeight = sp.m_screenHeight;
		//m_clientName = sp.m_clientName;
	}

	return *this;
}

void ClientParams::Init()
{
	m_screenWidth = 0;
	m_screenHeight = 0;
	//m_clientName = "";
}

void ClientParams::SetScreenWidth(unsigned short usW)
{
	m_screenWidth = usW;
}

void ClientParams::SetScreenHeight(unsigned short usH)
{
	m_screenHeight = usH;
}

void ClientParams::SetServerName(string clientName)
{
	static_cast<void>(clientName);
	//m_clientName = clientName;
}

void ClientParams::GetScreenWidth(unsigned short& usW)
{
	usW = m_screenWidth;
}

void ClientParams::GetScreenHeight(unsigned short& usH)
{
	usH = m_screenHeight;
}

void ClientParams::GetServerName(string& clientName)
{
	//clientName = m_clientName;
	static_cast<void>(clientName);
}
