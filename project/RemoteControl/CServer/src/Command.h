
#pragma once

#include <string.h>

/*
@brief client/server operation cmd define
*/
typedef enum CMDTYPE
{
	CMD_UNKNOWN				= 0,
	CMD_MOUSE_MOVE_TO		= 1,
	CMD_MOUSE_LEFT_DOWN		= 2,
	CMD_MOUSE_LEFT_UP		= 3,
	CMD_MOUSE_RIGHT_DOWN	= 4,
	CMD_MOUSE_RIGHT_UP		= 5,
	CMD_MOUSE_WHEEL			= 6,
	CMD_MOUSE_DOUBLE_CLICK	= 7,
	CMD_KEY_PRESS			= 8,
	CMD_KEY_RELEASE			= 9,
	CMD_GET_SCREEN_SIZE		= 11,
	CMD_GET_SCREEN_SIZE_RES = 12,
	CMD_SEND_SERVER_SCREEN_SIZE = 13,
}CMDTYPE;

const int BLOCK_WIDTH = 50;
const int BLOCK_HEIGHT = 50;
const int DIFF_PIX = 5;
const int DIFF_THN = 10;

//! server <--> client msg
const static int MAP_SERVER_MSG_PORT = 5647;

//! server <--> client img
const static int MAP_SERVER_IMG_PORT = 5648;

const static int CMD_SERVER_PORT = 5649;


/*
@brief client/server command data define
*/
class CMDData
{
public:
	
	//! command, like mousemove, mouse left button press
	unsigned char uCMD;

	/*
	@brief uXHB = p[1];	uXHB = p[2];
		   uLHB = p[3];	uLHB = p[4];
		   x <==> w
		   y <==> h

		   x point hight bit, like int x = 1680,
		   uXHB = (x & 0XFF00) >> 8 = 0x06 = 6

		   x point low bit, like int x = 1680
		   uXLB = (x & 0X00FF) = 0x90 = 144
	*/

	unsigned char uXHB;
	unsigned char uXLB;
	unsigned char uYHB;
	unsigned char uYLB;

	/*
	@brief	uDeltaHB = p[5];	uDeltaLB = p[6];
	*/
	unsigned char uDeltaHB;
	unsigned char uDeltaLB;

	unsigned char uCmd[8];
	unsigned short ux;
	unsigned short uy;
	unsigned short udelta;

public:
	CMDData();

	void Reset();

	CMDData(unsigned char* p);

	void SetData(unsigned char* p);

	void GetData(unsigned char* p);

	void GetCMD(CMDTYPE& type);

	void SetCMD(unsigned char cmd);

	void GetUSX(unsigned short& us);

	void GetUSY(unsigned short& us);

	void GetX(int& x);

	void GetY(int& y);

	void SetX(int x);

	void SetY(int y);

	void GetW(int& w);

	void GetH(int& h);

	void GetW(unsigned short& w);

	void GetH(unsigned short& h);

	void GetDelta(int& delta);

	void SetDelta(int delta);

	void GetDelta(unsigned short& delta);

	void SetDelta(unsigned short delta);
};

/*
@brief Wrap process cmd msg data storage and analyze.
	   Each of msg process at derived class.	
*/
class CmdHanldeBase
{
public:
	CmdHanldeBase();
	CmdHanldeBase(unsigned char* p);
	CmdHanldeBase(const CMDData& data);
	virtual ~CmdHanldeBase();

public:
	void SetData(const CMDData& data);
	void GetData(CMDData& data);
	void GetData(unsigned char* p);

public:
	//!
	void SetCMD(unsigned char cmd);
	void GetCMD(CMDTYPE& type);
	void GetUSX(unsigned short& usX);
	void GetUSY(unsigned short& usY);
	void GetX(int& x);
	void GetY(int &y);
	void SetX(int x);
	void SetY(int y);
	void GetW(int& w);
	void GetH(int& h);

public:
	CMDData m_cmdData;

};

/*
@brief	process mouse move
		CMD_MOUSE_MOVE_TO
*/
class CmdMouseMove : public CmdHanldeBase
{
public:
	CmdMouseMove();
	CmdMouseMove(unsigned char* p);
	CmdMouseMove(const CMDData& data);
	~CmdMouseMove();

public:
	//! extend

private:

};

/*
@brief	process mouse press
		CMD_MOUSE_LEFT_DOWN
*/
class CmdMouseLeftDown : public CmdHanldeBase
{
public:
	CmdMouseLeftDown();
	CmdMouseLeftDown(unsigned char* p);
	CmdMouseLeftDown(const CMDData& data);
	~CmdMouseLeftDown();

public:
	//! extend

private:
	
};

/*
@brief	process mouse press
		CMD_MOUSE_LEFT_UP
*/
class CmdMouseLeftUp : public CmdHanldeBase
{
public:
	CmdMouseLeftUp();
	CmdMouseLeftUp(unsigned char* p);
	CmdMouseLeftUp(const CMDData& data);
	~CmdMouseLeftUp();

public:
	//! extend

private:

};

/*
@brief	process mouse press
		CMD_MOUSE_RIGHT_DOWN
*/
class CmdMouseRightDown : public CmdHanldeBase
{
public:
	CmdMouseRightDown();
	CmdMouseRightDown(unsigned char* p);
	CmdMouseRightDown(const CMDData& data);
	~CmdMouseRightDown();

public:
	//! extend

private:

};

/*
@brief	process mouse press
		CMD_MOUSE_RIGHT_UP
*/
class CmdMouseRightUp : public CmdHanldeBase
{
public:
	CmdMouseRightUp();
	CmdMouseRightUp(unsigned char* p);
	CmdMouseRightUp(const CMDData& data);
	~CmdMouseRightUp();

public:
	//! extend

private:

};

/*
@brief	process mouse press
		CMD_MOUSE_WHEEL
*/
class CmdMouseWheel : public CmdHanldeBase
{
public:
	CmdMouseWheel();
	CmdMouseWheel(unsigned char* p);
	CmdMouseWheel(const CMDData& data);
	~CmdMouseWheel();

public:
	//! extend
	void SetDelta(const int& delta);
	void SetDelta(const unsigned short& usDelta);
	void GetDelta(int& delta);
	void GetDelta(unsigned short& usDelta);

private:
	//! mouse wheel step
	unsigned short m_usDelta;
};


/*
@brief	process mouse press
		CMD_MOUSE_DOUBLE_CLICK
*/
class CmdMouseDbClick : public CmdHanldeBase
{
public:
	CmdMouseDbClick();
	CmdMouseDbClick(unsigned char* p);
	CmdMouseDbClick(const CMDData& data);
	~CmdMouseDbClick();

public:
	//! extend

private:

};

/*
@brief	process keyboard press
		CMD_KEY_PRESS
*/
class CmdKeyPress : public CmdHanldeBase
{
public:
	CmdKeyPress();
	CmdKeyPress(unsigned char* p);
	CmdKeyPress(const CMDData& data);
	~CmdKeyPress();

public:
	//! extend

private:

};

/*
@brief	process keyboard release
		CMD_KEY_RELEASE
*/
class CmdKeyRelease : public CmdHanldeBase
{
public:
	CmdKeyRelease();
	CmdKeyRelease(unsigned char* p);
	CmdKeyRelease(const CMDData& data);
	~CmdKeyRelease();

public:
	//! extend

private:

};

/*
@brief	process keyboard release
		CMD_GET_SCREEN_SIZE
*/
class CmdGetScreenSize : public CmdHanldeBase
{
public:
	CmdGetScreenSize();
	CmdGetScreenSize(unsigned char* p);
	CmdGetScreenSize(const CMDData& data);
	~CmdGetScreenSize();

public:
	//! extend

private:

};

/*
@brief	process keyboard release
		CMD_GET_SCREEN_SIZE_RES
*/
class CmdGetScreenSizeRes : public CmdHanldeBase
{
public:
	CmdGetScreenSizeRes();
	CmdGetScreenSizeRes(unsigned char* p);
	CmdGetScreenSizeRes(const CMDData& data);
	~CmdGetScreenSizeRes();

public:
	//! extend

private:

};

/*
@brief	process keyboard release
		CMD_SEND_SERVER_SCREEN_SIZE
*/
class CmdSendServerScreenSize : public CmdHanldeBase
{
public:
	CmdSendServerScreenSize();
	CmdSendServerScreenSize(unsigned char* p);
	CmdSendServerScreenSize(const CMDData& data);
	~CmdSendServerScreenSize();

public:
	//! extend

private:

};