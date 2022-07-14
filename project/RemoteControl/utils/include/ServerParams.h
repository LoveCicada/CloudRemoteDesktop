#pragma once

/**
 * @file ServerParams.h
 * @author dyf
 * @brief ServerParams - structure describing the current state of the remote server
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
 * @brief use pimpl wrap
 *		  ClientParamsPrivate is imp.
 *
 */

class ServerParamsPrivate;

class RTC_EXPORT ServerParmas
{
public:
	ServerParmas();
	~ServerParmas();

	ServerParmas(const ServerParmas& sp);
	ServerParmas& operator=(const ServerParmas& sp);

	void Init();
	void Release();
	ServerParamsPrivate* GetPrivateImp();

	void SetScreenWidth(unsigned short usW);
	void SetScreenHeight(unsigned short usH);
	void SetServerName(string serverName);

	void GetScreenWidth(unsigned short& usW);
	void GetScreenHeight(unsigned short& usH);
	void GetServerName(string& serverName);
private:

	ServerParamsPrivate* m_pImp;
};