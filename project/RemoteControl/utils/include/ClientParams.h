
#pragma once


/**
 * @file ClientParams.h
 * @author dyf
 * @brief ClientParams - structure describing the current state of the remote server.
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

class ClientParamsPrivate;

class RTC_EXPORT ClientParams
{
public:
	ClientParams();
	~ClientParams();

	ClientParams(const ClientParams& sp);
	ClientParams& operator=(const ClientParams& sp);

	void Init();
	void Release();
	ClientParamsPrivate* GetPrivateImp();

	void SetScreenWidth(unsigned short usW);
	void SetScreenHeight(unsigned short usH);
	void SetServerName(string clientName);

	void GetScreenWidth(unsigned short& usW);
	void GetScreenHeight(unsigned short& usH);
	void GetServerName(string& clientName);

private:
	
	ClientParamsPrivate* m_pImp;
};