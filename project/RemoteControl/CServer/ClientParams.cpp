
#include "ClientParams.h"

ClientParams::ClientParams()
{
	Init();
}

ClientParams::~ClientParams()
{

}

void ClientParams::Init()
{
	m_showWidth = 0;
	m_showHeight = 0;
	m_clientName = "";
}