
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
class CMDDataBase
{
public:
	
	//! command, like mousemove, mouse left button press
	unsigned char uCMD;

	//! x ==> w
	//! y ==> h

	//! x point hight bit, like int x = 1680,
	//! uXHB = (x & 0XFF00) >> 8 = 0x06 = 6 
	unsigned char uXHB;

	//! x point low bit, like int x = 1680
	//! uXLB = (x & 0X00FF) = 0x90 = 144 
	unsigned char uXLB;
	unsigned char uYHB;
	unsigned char uYLB;

	unsigned char uCmd[8];
	unsigned short ux;
	unsigned short uy;


	CMDDataBase()
	{
		Reset();
	}

	void Reset()
	{
		uCMD = CMD_UNKNOWN;
		uXHB = 0;
		uXLB = 0;
		uYHB = 0;
		uYLB = 0;
		memset(uCmd, 0, 8);
		ux = 0;
		uy = 0;
	}

	CMDDataBase(unsigned char* p)
	{
		SetData(p);
	}

	void SetData(unsigned char* p)
	{
		uCMD = p[0];
		uXHB = p[1];
		uXLB = p[2];
		uYHB = p[3];
		uYLB = p[4];

		uCmd[0] = p[0];
		uCmd[1] = p[1];
		uCmd[2] = p[2];
		uCmd[3] = p[3];
		uCmd[4] = p[4];
		uCmd[5] = p[5];
		uCmd[6] = p[6];
		uCmd[7] = p[7];

		ux = GetUSX();
		uy = GetUSY();
	}

	void GetData(unsigned char* p)
	{
		p[0] = uCmd[0];
		p[1] = uCmd[1];
		p[2] = uCmd[2];
		p[3] = uCmd[3];
		p[4] = uCmd[4];
		p[5] = uCmd[5];
		p[6] = uCmd[6];
		p[7] = uCmd[7];
	}

	CMDTYPE GetCMD()
	{
		return (CMDTYPE)uCMD;
	}

	void SetCMD(unsigned char cmd)
	{
		uCMD = cmd;
		uCmd[0] = cmd;
	}

	unsigned short GetUSX()
	{
		unsigned short us = 0;
		us = uXHB << 8 | uXLB;
		return us;
	}

	unsigned short GetUSY()
	{
		unsigned short us = 0;
		us = uYHB << 8 | uYLB;
		return us;
	}

	int GetX()
	{
		unsigned short us = 0;
		us = GetUSX();
		return (int)us;
	}

	int GetY()
	{
		unsigned short us = 0;
		us = GetUSY();
		return (int)us;
	}

	int GetW()
	{
		unsigned short us = 0;
		us = GetUSX();
		return (int)us;
	}

	int GetH()
	{
		unsigned short us = 0;
		us = GetUSY();
		return (int)us;
	}

	void SetX(int x)
	{
		//! 1680 = 0x0690
		unsigned short us = (unsigned short)x;
		uXHB = (us & 0xFF00) >> 8;
		uXLB = (us & 0x00FF);

		ux = uXHB << 8 | uXLB;

		uCmd[1] = uXHB;
		uCmd[2] = uXLB;
	}

	void SetY(int y)
	{
		unsigned short us = (unsigned short)y;
		uYHB = (us & 0xFF00) >> 8;
		uYLB = (us & 0x00FF);

		uy = uYHB << 8 | uYLB;

		uCmd[3] = uYHB;
		uCmd[4] = uYLB;
	}

};


