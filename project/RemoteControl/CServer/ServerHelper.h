
#pragma once

/**
 * @brief manager server
 * export server
 * create, init, stop, close
 * 
 */


#ifdef _MSC_VER
#ifdef _RD_SERVER_Export
#define _RD_SERVER_Lib __declspec(dllexport)
#else
#define _RD_SERVER_Lib __declspec(dllimport)
#endif
#else
#define _RD_SERVER_Lib
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