
#pragma once


/*
@brief
*/

#include <string>

using std::string;

class ClientParams
{
public:
	ClientParams();
	~ClientParams();

	ClientParams(const ClientParams& sp);
	ClientParams& operator=(const ClientParams& sp);

	void Init();

	void SetScreenWidth(unsigned short usW);
	void SetScreenHeight(unsigned short usH);
	void SetServerName(string clientName);

	void GetScreenWidth(unsigned short& usW);
	void GetScreenHeight(unsigned short& usH);
	void GetServerName(string& clientName);

private:

	unsigned short m_screenWidth;
	unsigned short m_screenHeight;
	string m_clientName;
};