
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

	void Init();


private:

	unsigned short m_showWidth;
	unsigned short m_showHeight;
	string m_clientName;
};