
#include "ServerHelper.h"
#include "SControler.h"
#include <iostream>
using std::cout;
using std::endl;

ServerHelper::ServerHelper()
{
    m_pServer = nullptr;
}

ServerHelper::~ServerHelper()
{
    if (m_pServer)
    {
        SControler* pServer = static_cast<SControler*>(m_pServer);
        delete pServer;
        m_pServer = nullptr;
    }
}

bool ServerHelper::CreateServer()
{
    bool bRet = true;
    
    SControler* pServer = new SControler();
    if (!pServer) {
        cout << __func__ << " create server fail***" << endl;
        return false;
    }

    cout << __func__ << " create server success---" << endl;

    m_pServer = static_cast<SControler*>(pServer);

    return bRet;
}

bool ServerHelper::InitServer()
{
    bool bRet = true;


    return bRet;
}

bool ServerHelper::StopServer()
{
    bool bRet = true;


    return bRet;
}

bool ServerHelper::CloseServer()
{
    bool bRet = true;

    if (m_pServer)
    {
        SControler* pServer = static_cast<SControler*>(m_pServer);
        delete pServer;
        m_pServer = nullptr;
    }

    return bRet;
}
