

#include "ClientParams.h"

/********************* imp ********************/
class ClientParamsPrivate
{
public:
	ClientParamsPrivate()
	{
		Init();
	}

	~ClientParamsPrivate() = default;

	void Init()
	{
		m_screenWidth = 0;
		m_screenHeight = 0;
		m_clientName = "";
	}

	ClientParamsPrivate(const ClientParamsPrivate& cp)
	{
		m_screenWidth	= cp.m_screenWidth;
		m_screenHeight	= cp.m_screenHeight;
		m_clientName	= cp.m_clientName;
	}

	ClientParamsPrivate& operator=(const ClientParamsPrivate& sp)
	{
		if (this != &sp) {
			m_screenWidth	= sp.m_screenWidth;
			m_screenHeight	= sp.m_screenHeight;
			m_clientName	= sp.m_clientName;
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
ClientParams::ClientParams()
{
	Init();
}

ClientParams::~ClientParams()
{
	Release();
}

ClientParams::ClientParams(const ClientParams& sp)
{
	m_pImp = sp.m_pImp;	
}

ClientParams& ClientParams::operator=(const ClientParams& sp)
{
	if (this != &sp) {
		this->m_pImp = sp.m_pImp;
	}
	return *this;
}

void ClientParams::Init()
{
	m_pImp = new ClientParamsPrivate();
}

void ClientParams::Release()
{
	if (m_pImp) {
		delete m_pImp;
	}
	m_pImp = nullptr;
}

ClientParamsPrivate* ClientParams::GetPrivateImp()
{
	if (m_pImp) {
		return m_pImp;
	}

	return nullptr;
}

void ClientParams::SetScreenWidth(unsigned short usW)
{
	m_pImp->SetScreenWidth(usW);
}

void ClientParams::SetScreenHeight(unsigned short usH)
{
	m_pImp->SetScreenHeight(usH);
}

void ClientParams::SetServerName(string clientName)
{
	m_pImp->SetServerName(clientName);
}

void ClientParams::GetScreenWidth(unsigned short& usW)
{
	m_pImp->GetScreenWidth(usW);
}

void ClientParams::GetScreenHeight(unsigned short& usH)
{
	m_pImp->GetScreenHeight(usH);
}

void ClientParams::GetServerName(string& clientName)
{
	m_pImp->GetServerName(clientName);
}
