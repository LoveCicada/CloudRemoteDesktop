#include "Command2.h"


CMDData::CMDData()
{
	Reset();
}

void CMDData::Reset()
{
	uCMD = CMD_UNKNOWN;
	uXHB = 0;
	uXLB = 0;
	uYHB = 0;
	uYLB = 0;
	uDeltaHB = 0;
	uDeltaLB = 0;
	memset(uCmd, 0, 8);
	ux = 0;
	uy = 0;
	udelta = 0;
}

CMDData::CMDData(unsigned char* p)
{
	SetData(p);
}

void CMDData::SetData(unsigned char* p)
{
	uCMD = p[0];
	uXHB = p[1];
	uXLB = p[2];
	uYHB = p[3];
	uYLB = p[4];

	uDeltaHB = p[5];
	uDeltaLB = p[6];

	uCmd[0] = p[0];
	uCmd[1] = p[1];
	uCmd[2] = p[2];
	uCmd[3] = p[3];
	uCmd[4] = p[4];
	uCmd[5] = p[5];
	uCmd[6] = p[6];
	uCmd[7] = p[7];

	GetUSX(ux);
	GetUSY(uy);
	GetDelta(udelta);
}

void CMDData::GetData(unsigned char* p)
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

void CMDData::GetCMD(CMDTYPE& type)
{
	type = static_cast<CMDTYPE>(uCMD);
}

void CMDData::SetCMD(unsigned char cmd)
{
	uCMD = cmd;
	uCmd[0] = cmd;
}

void CMDData::GetUSX(unsigned short& us)
{
	us = uXHB << 8 | uXLB;
}

void CMDData::GetUSY(unsigned short& us)
{
	us = uYHB << 8 | uYLB;
}

void CMDData::GetX(int& x)
{
	unsigned short us = 0;
	GetUSX(us);
	x = (int)us;
}

void CMDData::GetY(int& y)
{
	unsigned short us = 0;
	GetUSY(us);
	y = (int)us;
}

void CMDData::SetX(int x)
{
	//! 1680 = 0x0690
	unsigned short us = (unsigned short)x;
	uXHB = (us & 0xFF00) >> 8;
	uXLB = (us & 0x00FF);

	ux = uXHB << 8 | uXLB;

	uCmd[1] = uXHB;
	uCmd[2] = uXLB;
}

void CMDData::SetY(int y)
{
	unsigned short us = (unsigned short)y;
	uYHB = (us & 0xFF00) >> 8;
	uYLB = (us & 0x00FF);

	uy = uYHB << 8 | uYLB;

	uCmd[3] = uYHB;
	uCmd[4] = uYLB;
}

void CMDData::GetW(int& w)
{
	unsigned short us = 0;
	GetUSX(us);
	w = (int)us;
}

void CMDData::GetH(int& h)
{
	unsigned short us = 0;
	GetUSY(us);
	h = (int)us;
}

void CMDData::GetDelta(int& delta)
{
	unsigned short us = (unsigned short)delta;
	GetDelta(us);
	delta = (int)us;
}

void CMDData::SetDelta(int delta)
{
	unsigned short us = (unsigned short)delta;
	SetDelta(us);
}

void CMDData::GetDelta(unsigned short& delta)
{
	udelta = uDeltaHB << 8 | uDeltaLB;
	delta = udelta;
}

void CMDData::SetDelta(unsigned short delta)
{
	udelta = delta;

	unsigned short us = delta;
	uDeltaHB = (us & 0xFF00) >> 8;
	uDeltaLB = (us & 0x00FF);

	udelta = uDeltaHB << 8 | uDeltaLB;

	uCmd[5] = uDeltaHB;
	uCmd[6] = uDeltaLB;
}


//***************************
CmdHanldeBase::CmdHanldeBase()
{

}

CmdHanldeBase::CmdHanldeBase(unsigned char* p)
{
	m_cmdData.SetData(p);
}

CmdHanldeBase::CmdHanldeBase(const CMDData& data)
{
	m_cmdData = data;
}

CmdHanldeBase::~CmdHanldeBase()
{
}

void CmdHanldeBase::SetData(const CMDData& data)
{
	m_cmdData = data;
}

void CmdHanldeBase::GetData(CMDData& data)
{
	data = m_cmdData;
}

void CmdHanldeBase::SetCMD(unsigned char cmd)
{
	m_cmdData.SetCMD(cmd);
}

void CmdHanldeBase::GetCMD(CMDTYPE& type)
{
	m_cmdData.GetCMD(type);
}

void CmdHanldeBase::GetUSX(unsigned short& usX)
{
	m_cmdData.GetUSX(usX);
}

void CmdHanldeBase::GetUSY(unsigned short& usY)
{
	m_cmdData.GetUSY(usY);
}

void CmdHanldeBase::GetX(int& x)
{
	m_cmdData.GetX(x);
}

void CmdHanldeBase::GetY(int& y)
{
	m_cmdData.GetY(y);
}

void CmdHanldeBase::SetX(int x)
{
	m_cmdData.SetX(x);
}

void CmdHanldeBase::SetY(int y)
{
	m_cmdData.SetY(y);
}

void CmdHanldeBase::GetW(int& w)
{
	m_cmdData.GetW(w);
}

void CmdHanldeBase::GetH(int& h)
{
	m_cmdData.GetH(h);
}


//***************************
CmdMouseMove::CmdMouseMove()
{
	SetCMD(CMDTYPE::CMD_MOUSE_MOVE_TO);
	m_usDelta = 0;
}

CmdMouseMove::CmdMouseMove(unsigned char* p) : CmdHanldeBase(p)
{
	SetCMD(CMDTYPE::CMD_MOUSE_MOVE_TO);
	GetDelta(m_usDelta);
}

CmdMouseMove::CmdMouseMove(const CMDData& data) : CmdHanldeBase(data)
{
	GetDelta(m_usDelta);
}

CmdMouseMove::~CmdMouseMove()
{

}

void CmdMouseMove::SetDelta(const int& delta)
{
	unsigned short usDelta = (unsigned short)(delta);
	SetDelta(usDelta);
}

void CmdMouseMove::SetDelta(const unsigned short& usDelta)
{
	m_cmdData.SetDelta(usDelta);
	m_cmdData.GetDelta(m_usDelta);
}

void CmdMouseMove::GetDelta(int& delta)
{
	unsigned short usDelta = (unsigned short)(delta);
	GetDelta(usDelta);
	delta = usDelta;
}

void CmdMouseMove::GetDelta(unsigned short& usDelta)
{
	m_cmdData.GetDelta(m_usDelta);
	usDelta = m_usDelta;
}


//***************************