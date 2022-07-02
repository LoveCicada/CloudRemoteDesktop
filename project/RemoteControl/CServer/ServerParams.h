#pragma once

/*
@brief ServerParams - structure describing the current state of the remote server
*/

#include <string>

using std::string;

class ServerParmas
{
public:
	ServerParmas();
	~ServerParmas();

	void Init();

	void SetScreenWidth(unsigned short usW);
	void SetScreenHeight(unsigned short usH);
	void SetServerName(string serverName);

	void GetScreenWidth(unsigned short& usW);
	void GetScreenHeight(unsigned short& usH);
	void GetServerName(string& serverName);

private:

	unsigned short m_screenWidth;
	unsigned short m_screenHeight;
	string m_serverName;
};