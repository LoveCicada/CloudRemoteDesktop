#include "Command.h"
#include "RCBuffer.h"

CMDData::CMDData()
{
	Reset();
}

void CMDData::Reset()
{
	memset(c, 0, msgProtocolLength);
	cmdType	 = CMDTYPE::CMD_UNKNOWN;
	cSysType = sSysType = SYSTYPE::UNKNOWN;
	cExtend	 = 0;

	xPos	 = 0;
	yPos	 = 0;
	delta	 = 0;
	kbValue  = 0;

	nativeScanCode	 = 0;
	nativeVirtualKey = 0;
	nativeModifiers  = 0;
}

void CMDData::SetData(CMDData cmdData)
{
	RCBuffer stream(c, msgProtocolLength);

	//! common header
	cmdType = cmdData.cmdType;
	stream.write_1bytes(static_cast<int8_t>(cmdData.cmdType));

	cSysType = cmdData.cSysType;
	stream.write_1bytes(static_cast<int8_t>(cmdData.cSysType));

	sSysType = cmdData.sSysType;
	stream.write_1bytes(static_cast<int8_t>(cmdData.sSysType));

	cExtend = cmdData.cExtend;
	stream.write_1bytes(static_cast<int8_t>(cmdData.cExtend));

	//!
	int32_t xValid = cmdData.xPos ? cmdData.xPos : cmdData.kbValue;
	kbValue = xPos = xValid;
	stream.write_4bytes(xValid);

	//!
	int32_t yValid = cmdData.yPos ? cmdData.yPos : cmdData.nativeScanCode;
	nativeScanCode = yPos = cmdData.nativeScanCode;
	stream.write_4bytes(yValid);

	//!
	int32_t deltaValid = cmdData.delta ? cmdData.delta : cmdData.nativeVirtualKey;
	nativeVirtualKey = delta = cmdData.nativeVirtualKey;
	stream.write_4bytes(deltaValid);

	//!  
	nativeModifiers = cmdData.nativeModifiers;
	stream.write_4bytes(cmdData.nativeModifiers);
}

void CMDData::GetData(CMDData& cmdData)
{
	memcpy(cmdData.c, c, msgProtocolLength);
	cmdData.cmdType		= cmdType;
	cmdData.cSysType	= cSysType;
	cmdData.sSysType	= sSysType;
	cmdData.cExtend		= cExtend;

	//!
	int32_t xValid	= cmdData.xPos ? cmdData.xPos : cmdData.kbValue;
	cmdData.xPos	= cmdData.kbValue = xValid;

	int32_t yValid	= cmdData.yPos ? cmdData.yPos : cmdData.nativeScanCode;
	cmdData.yPos	= cmdData.nativeScanCode = yValid;

	int32_t deltaValid	= cmdData.delta ? cmdData.delta : cmdData.nativeVirtualKey;
	cmdData.delta		= cmdData.nativeVirtualKey = deltaValid;

	cmdData.nativeModifiers = nativeModifiers;
}

void CMDData::SetData(char* p)
{
	static_cast<void*>(p);
	memcpy(c, p, msgProtocolLength);

	RCBuffer stream(c, msgProtocolLength);

	//! common header
	cmdType = static_cast<CMDTYPE>(stream.read_1bytes());

	cSysType = static_cast<SYSTYPE>(stream.read_1bytes());

	sSysType = static_cast<SYSTYPE>(stream.read_1bytes());

	cExtend = static_cast<char>(stream.read_1bytes());

	//! mouse msg or keyboard msg
	kbValue = xPos = stream.read_4bytes();

	//!
	nativeScanCode = yPos = stream.read_4bytes();

	//!
	nativeVirtualKey = delta = stream.read_4bytes();

	//!  
	nativeModifiers = stream.read_4bytes();
}

void CMDData::GetData(char* p)
{
	memcpy(p, c, msgProtocolLength);
}

void CMDData::GetCMD(CMDTYPE& type)
{
	type = static_cast<CMDTYPE>(cmdType);
}

void CMDData::SetCMD(CMDTYPE cmd)
{
	cmdType = cmd;
}

void CMDData::GetX(int32_t& x)
{
	x = xPos;
}

void CMDData::GetY(int32_t& y)
{
	y = yPos;
}

void CMDData::SetX(int32_t x)
{
	xPos = x;
}

void CMDData::SetY(int32_t y)
{
	yPos = y;
}

void CMDData::GetW(int32_t& w)
{
	w = xPos;
}

void CMDData::GetH(int32_t& h)
{
	h = yPos;
}

void CMDData::GetDelta(int32_t& deltaValue)
{
	deltaValue = this->delta;
}

void CMDData::SetDelta(int32_t deltaValue)
{
	this->delta = deltaValue;
}

void CMDData::GetKeyValue(int32_t& keyValue)
{
	keyValue = kbValue;
}

void CMDData::SetKeyValue(int32_t keyValue)
{
	kbValue = keyValue;
}

void CMDData::GetScanCode(int32_t& scanCode)
{
	scanCode = nativeScanCode;
}

void CMDData::SetScanCode(int32_t scanCode)
{
	nativeScanCode = scanCode;
}

void CMDData::GetVirtualKey(int32_t& virtualKey)
{
	virtualKey = nativeVirtualKey;
}

void CMDData::SetVirtualKey(int32_t virtualKey)
{
	nativeVirtualKey = virtualKey;
}

void CMDData::GetModifier(int32_t& modifier)
{
	modifier = nativeModifiers;
}

void CMDData::SetModifier(int32_t modifier)
{
	nativeModifiers = modifier;
}


//***************************
CmdHanldeBase::CmdHanldeBase()
{

}

CmdHanldeBase::CmdHanldeBase(char* p)
{
	m_cmdData.SetData(p);
}

CmdHanldeBase::CmdHanldeBase(const CMDData& data)
{
	m_cmdData = data;
	m_cmdData.SetData(data);
}

CmdHanldeBase::~CmdHanldeBase()
{
}

void CmdHanldeBase::SetData(const CMDData& data)
{
	m_cmdData.SetData(data);
}

void CmdHanldeBase::GetData(CMDData& data)
{
	data = m_cmdData;
	m_cmdData.GetData(data);
}

void CmdHanldeBase::GetData(char* p)
{
	m_cmdData.GetData(p);
}

void CmdHanldeBase::SetCMD(CMDTYPE cmd)
{
	m_cmdData.SetCMD(cmd);
}

void CmdHanldeBase::GetCMD(CMDTYPE& type)
{
	m_cmdData.GetCMD(type);
}

void CmdHanldeBase::GetX(int32_t& x)
{
	m_cmdData.GetX(x);
}

void CmdHanldeBase::GetY(int32_t& y)
{
	m_cmdData.GetY(y);
}

void CmdHanldeBase::SetX(int32_t x)
{
	m_cmdData.SetX(x);
}

void CmdHanldeBase::SetY(int32_t y)
{
	m_cmdData.SetY(y);
}

void CmdHanldeBase::GetW(int32_t& w)
{
	m_cmdData.GetW(w);
}

void CmdHanldeBase::GetH(int32_t& h)
{
	m_cmdData.GetH(h);
}


//***************************
CmdMouseMove::CmdMouseMove()
{
	SetCMD(CMDTYPE::CMD_MOUSE_MOVE_TO);
}

CmdMouseMove::CmdMouseMove(char* p) : CmdHanldeBase(p)
{
	SetCMD(CMDTYPE::CMD_MOUSE_MOVE_TO);
}

CmdMouseMove::CmdMouseMove(const CMDData& data) : CmdHanldeBase(data)
{

}

CmdMouseMove::~CmdMouseMove()
{

}


//***************************
CmdMouseLeftDown::CmdMouseLeftDown()
{
	SetCMD(CMDTYPE::CMD_MOUSE_LEFT_DOWN);
}

CmdMouseLeftDown::CmdMouseLeftDown(char* p) : CmdHanldeBase(p)
{
	SetCMD(CMDTYPE::CMD_MOUSE_LEFT_DOWN);
}

CmdMouseLeftDown::CmdMouseLeftDown(const CMDData& data) : CmdHanldeBase(data)
{

}

CmdMouseLeftDown::~CmdMouseLeftDown()
{

}


//***************************
CmdMouseLeftUp::CmdMouseLeftUp()
{
	SetCMD(CMDTYPE::CMD_MOUSE_LEFT_UP);
}

CmdMouseLeftUp::CmdMouseLeftUp(char* p) : CmdHanldeBase(p)
{
	SetCMD(CMDTYPE::CMD_MOUSE_LEFT_UP);
}

CmdMouseLeftUp::CmdMouseLeftUp(const CMDData& data) : CmdHanldeBase(data)
{

}

CmdMouseLeftUp::~CmdMouseLeftUp()
{

}

//***************************
CmdMouseRightDown::CmdMouseRightDown()
{
	SetCMD(CMDTYPE::CMD_MOUSE_RIGHT_DOWN);
}

CmdMouseRightDown::CmdMouseRightDown(char* p) : CmdHanldeBase(p)
{
	SetCMD(CMDTYPE::CMD_MOUSE_RIGHT_DOWN);
}

CmdMouseRightDown::CmdMouseRightDown(const CMDData& data) : CmdHanldeBase(data)
{

}

CmdMouseRightDown::~CmdMouseRightDown()
{

}

//***************************
CmdMouseRightUp::CmdMouseRightUp()
{
	SetCMD(CMDTYPE::CMD_MOUSE_RIGHT_UP);
}

CmdMouseRightUp::CmdMouseRightUp(char* p) : CmdHanldeBase(p)
{
	SetCMD(CMDTYPE::CMD_MOUSE_RIGHT_UP);
}

CmdMouseRightUp::CmdMouseRightUp(const CMDData& data) : CmdHanldeBase(data)
{

}

CmdMouseRightUp::~CmdMouseRightUp()
{

}

//***************************
CmdMouseWheel::CmdMouseWheel()
{
	SetCMD(CMDTYPE::CMD_MOUSE_WHEEL);
}

CmdMouseWheel::CmdMouseWheel(char* p) : CmdHanldeBase(p)
{
	SetCMD(CMDTYPE::CMD_MOUSE_WHEEL);
}

CmdMouseWheel::CmdMouseWheel(const CMDData& data) : CmdHanldeBase(data)
{
}

CmdMouseWheel::~CmdMouseWheel()
{

}

//***************************
CmdMouseDbClick::CmdMouseDbClick()
{
	SetCMD(CMDTYPE::CMD_MOUSE_DOUBLE_CLICK);
}

CmdMouseDbClick::CmdMouseDbClick(char* p) : CmdHanldeBase(p)
{
	SetCMD(CMDTYPE::CMD_MOUSE_DOUBLE_CLICK);
}

CmdMouseDbClick::CmdMouseDbClick(const CMDData& data) : CmdHanldeBase(data)
{

}

CmdMouseDbClick::~CmdMouseDbClick()
{

}

//***************************
CmdKeyPress::CmdKeyPress()
{
	SetCMD(CMDTYPE::CMD_KEY_PRESS);
}

CmdKeyPress::CmdKeyPress(char* p) : CmdHanldeBase(p)
{
	SetCMD(CMDTYPE::CMD_KEY_PRESS);
}

CmdKeyPress::CmdKeyPress(const CMDData& data) : CmdHanldeBase(data)
{

}

CmdKeyPress::~CmdKeyPress()
{

}

//***************************
CmdKeyRelease::CmdKeyRelease()
{
	SetCMD(CMDTYPE::CMD_KEY_RELEASE);
}

CmdKeyRelease::CmdKeyRelease(char* p) : CmdHanldeBase(p)
{
	SetCMD(CMDTYPE::CMD_KEY_RELEASE);
}

CmdKeyRelease::CmdKeyRelease(const CMDData& data) : CmdHanldeBase(data)
{

}

CmdKeyRelease::~CmdKeyRelease()
{

}

//***************************
CmdGetScreenSize::CmdGetScreenSize()
{
	SetCMD(CMDTYPE::CMD_GET_SCREEN_SIZE);
}

CmdGetScreenSize::CmdGetScreenSize(char* p) : CmdHanldeBase(p)
{
	SetCMD(CMDTYPE::CMD_GET_SCREEN_SIZE);
}

CmdGetScreenSize::CmdGetScreenSize(const CMDData& data) : CmdHanldeBase(data)
{

}

CmdGetScreenSize::~CmdGetScreenSize()
{

}

//***************************
CmdGetScreenSizeRes::CmdGetScreenSizeRes()
{
	SetCMD(CMDTYPE::CMD_GET_SCREEN_SIZE_RES);
}

CmdGetScreenSizeRes::CmdGetScreenSizeRes(char* p) : CmdHanldeBase(p)
{
	SetCMD(CMDTYPE::CMD_GET_SCREEN_SIZE_RES);
}

CmdGetScreenSizeRes::CmdGetScreenSizeRes(const CMDData& data) : CmdHanldeBase(data)
{

}

CmdGetScreenSizeRes::~CmdGetScreenSizeRes()
{

}


//***************************
CmdSendServerScreenSize::CmdSendServerScreenSize()
{
	SetCMD(CMDTYPE::CMD_SEND_SERVER_SCREEN_SIZE);
}

CmdSendServerScreenSize::CmdSendServerScreenSize(char* p) : CmdHanldeBase(p)
{
	SetCMD(CMDTYPE::CMD_SEND_SERVER_SCREEN_SIZE);
}

CmdSendServerScreenSize::CmdSendServerScreenSize(const CMDData& data) : CmdHanldeBase(data)
{

}

CmdSendServerScreenSize::~CmdSendServerScreenSize()
{

}

//***************************
CmdKeySpAltLTab::CmdKeySpAltLTab()
{
	SetCMD(CMDTYPE::CMD_KEY_SP_ALTL_TAB);
}

CmdKeySpAltLTab::CmdKeySpAltLTab(char* p) : CmdHanldeBase(p)
{
	SetCMD(CMDTYPE::CMD_KEY_SP_ALTL_TAB);
}

CmdKeySpAltLTab::CmdKeySpAltLTab(const CMDData& data) : CmdHanldeBase(data)
{

}

CmdKeySpAltLTab::~CmdKeySpAltLTab()
{

}