
#pragma once

/**
 * @file ServerParams.h
 * @author dyf
 * @brief manager server
 * export server
 * create, init, stop, close
 * @version 0.1
 * @date 2022-07-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifdef _MSC_VER
#ifdef _RD_SERVER_Export
#define _RD_SERVER_Lib __declspec(dllexport)
#else
#define _RD_SERVER_Lib __declspec(dllimport)
#endif
#else
#define _RD_SERVER_Lib __attribute((visibility("default")))
#endif


class /*_RD_SERVER_Lib*/ ServerHelper
{
public:
	ServerHelper();
	~ServerHelper();

public:
	bool CreateServer();
	bool InitServer();
	bool StopServer();
	bool CloseServer();

private:
	void* m_pServer;
};