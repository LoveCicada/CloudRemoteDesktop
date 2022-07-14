
#include "ServerParams.h"


/********************* imp ********************/
class ServerParamsPrivate
{
public:
	ServerParamsPrivate()
	{
		Init();
	}

	~ServerParamsPrivate() = default;

	void Init()
	{
		m_screenWidth = 0;
		m_screenHeight = 0;
		m_clientName = "";
	}

	ServerParamsPrivate(const ServerParamsPrivate& cp)
	{
		m_screenWidth = cp.m_screenWidth;
		m_screenHeight = cp.m_screenHeight;
		m_clientName = cp.m_clientName;
	}

	ServerParamsPrivate& operator=(const ServerParamsPrivate& sp)
	{
		if (this != &sp) {
			m_screenWidth = sp.m_screenWidth;
			m_screenHeight = sp.m_screenHeight;
			m_clientName = sp.m_clientName;
		}

		return *this;
	}

	void SetScreenWidth(unsigned short usW)
	{
		m_screenWidth = usW;
	}

	void SetScreenHeight(unsigned short usH)
	{
		m_screenHeight = usH;
	}

	void SetServerName(string clientName)
	{
		m_clientName = clientName;
	}

	void GetScreenWidth(unsigned short& usW)
	{
		usW = m_screenWidth;
	}

	void GetScreenHeight(unsigned short& usH)
	{
		usH = m_screenHeight;
	}

	void GetServerName(string& clientName)
	{
		clientName = m_clientName;
	}


public:
	unsigned short m_screenWidth;
	unsigned short m_screenHeight;
	string m_clientName;
};


/********************* wrap ********************/
ServerParmas::ServerParmas()
{
	Init();
}

ServerParmas::~ServerParmas()
{
	Release();
}

ServerParmas::ServerParmas(const ServerParmas& sp)
{
	m_pImp = sp.m_pImp;
}

ServerParmas& ServerParmas::operator=(const ServerParmas& sp)
{
	if (this != &sp) {
		this->m_pImp = sp.m_pImp;
	}

	return *this;
}

void ServerParmas::Init()
{
	m_pImp = new ServerParamsPrivate();
}

void ServerParmas::Release()
{
}

ServerParamsPrivate* ServerParmas::GetPrivateImp()
{
	return nullptr;
}

void ServerParmas::SetScreenWidth(unsigned short usW)
{
	m_pImp->SetScreenWidth(usW);
}

void ServerParmas::SetScreenHeight(unsigned short usH)
{
	m_pImp->SetScreenHeight(usH);
}

void ServerParmas::SetServerName(string serverName)
{
	m_pImp->SetServerName(serverName);
}

void ServerParmas::GetScreenWidth(unsigned short& usW)
{
	m_pImp->GetScreenWidth(usW);
}

void ServerParmas::GetScreenHeight(unsigned short& usH)
{
	m_pImp->GetScreenHeight(usH);
}

void ServerParmas::GetServerName(string& serverName)
{
	m_pImp->GetServerName(serverName);
}
