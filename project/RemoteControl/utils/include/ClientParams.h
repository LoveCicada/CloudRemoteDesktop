
#pragma once


/**
 * @file ClientParams.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "ExportMacro.h"
#include <string>
using std::string;

/**
 * @brief 
 * 
 */
class RTC_EXPORT ClientParams
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
	//string m_clientName;
};