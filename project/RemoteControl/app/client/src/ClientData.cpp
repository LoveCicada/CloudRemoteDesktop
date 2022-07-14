
#include "ClientData.h"

ClientData::ClientData()
{
    Init();
}

ClientData::~ClientData()
{

}

void ClientData::Init()
{
    width = 0;
    height = 0;
    port = 0;
    ip = "";
}