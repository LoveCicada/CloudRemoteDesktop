#pragma once

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

struct ConfigData
{
	string serverIp;
	int serverMapPort;
	int serverCmdPort;

	ConfigData()
	{
		Init();
	}

	~ConfigData()
	{
		
	}

	void Init()
	{
		serverIp = "127.0.0.1";
		serverMapPort = 5648;
		serverCmdPort = 5649;
	}

	ConfigData(const ConfigData& data)
	{
		serverIp = data.serverIp;
		serverMapPort = data.serverMapPort;
		serverCmdPort = data.serverCmdPort;
	}
};

/*
template<typename T>
class Singleton
{
	friend T;   //T can visit Singleton private member and function
public:
	static T* GetInstance() {
		static T instance;
		return &instance;
	}

private:
	Singleton() {
		cout << __func__ << endl;
	}
	~Singleton() {
		cout << __func__ << endl;
	}
	Singleton(const Singleton&) {}
	Singleton& operator=(const Singleton&) {
		return *this;
	}

};

*/

class Config
{

public:
	static Config* GetInstance() {
		static Config instance;
		return &instance;
	}

	ConfigData GetConfigData()
	{
		return m_configData;
	}

	void SetConfigData(ConfigData data)
	{
		m_configData = data;
		bool bRet = Write();
		if (bRet) {
			cout << __func__ << " fail*** " << endl;
		}
	}

private:
	Config() {
		bool bRet =  Read();
		if (bRet) {
			cout << __func__ << " fail*** " << endl;
		}
		cout << __func__ << endl;
	}
	~Config() {
		cout << __func__ << endl;
	}
	Config(const Config&) {}
	Config& operator=(const Config&) {
		return *this;
	}

	/*
	@brief read from config file
	*/
	bool Read()
	{
		bool bRet = true;


		return bRet;
	}

	/*
	@brief write to config file
	*/
	bool Write()
	{
		bool bRet = true;


		return bRet;
	}

private:
	ConfigData m_configData;

};