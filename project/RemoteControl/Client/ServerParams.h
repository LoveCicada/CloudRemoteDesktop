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


private:

	unsigned short m_screenWidth;
	unsigned short m_screenHeight;
	string m_serverName;
};