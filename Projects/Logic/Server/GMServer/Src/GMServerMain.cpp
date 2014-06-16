/******************************************************************************/
#include "stdafx.h"
#include "GMServerMain.h"
//#include "ClientManager.h"
//#include "ServerManager.h"
/******************************************************************************/

namespace MG
{
    //-----------------------------------------------------------------------------
    GMServerMain::GMServerMain()
    {
        
    }

    //-----------------------------------------------------------------------------
    GMServerMain::~GMServerMain()
    {
        
    }

    //-----------------------------------------------------------------------------
    Bool GMServerMain::initialize(ServerLauncherInterface* launcher)
    {
		mServerLauncher = launcher;
		DYNAMIC_ASSERT(mServerLauncher);
		if ( launcher == NULL )
			return false;

		Str16 str16KeyName = launcher->getConfigKeyName();
		str16KeyName = L"..\\Log\\" + str16KeyName;
		Str8 str8KeyName;
		MGStrOp::toString(str16KeyName.c_str(),str8KeyName);

		MG::LogSystem::getInstance().setSysLogPath(str8KeyName.c_str());
		MG::LogSystem::getInstance().setGameLogicLogPath(str8KeyName.c_str());
		MG::LogSystem::getInstance().setPartName("LoginServer");
		LogSystem::getInstance().setEnableConsole(launcher->getServerSetting()->getCoreInfo()->isOpenConsole);
		LogSystem::getInstance().setLogLevel(launcher->getServerSetting()->getCoreInfo()->logLevel);
		LogSystem::getInstance().setSaveToFile(true);

		
        return true;
    }

    //-----------------------------------------------------------------------------
    void GMServerMain::update()
	{
		//FUNDETECTION(__MG_FUNC__);
		
    }

    //-----------------------------------------------------------------------------
    Bool GMServerMain::unInitialize()
    {
		//FUNDETECTION(__MG_FUNC__);

        return true;
    }

	//-----------------------------------------------------------------------------
	void GMServerMain::onClientConnected(I32 id,NetAddress*address)
	{
        
	}

	//-----------------------------------------------------------------------------
	void GMServerMain::onClientDisconnect(I32 id)
	{
        //ClientManager::getInstance().onDisconnect(id);
	}

	//-----------------------------------------------------------------------------
	void GMServerMain::onClientRecvPacket(I32 id,NetEventRecv* packet)
	{
		//ClientManager::getInstance().processPacket(id, packet);
	}

	//-----------------------------------------------------------------------------
	void GMServerMain::onServerConnected(I32 id,GameNetType type,U32 serverId, U64 serverUniqueFlag, NetAddress*address)
	{
        //ServerManager::getInstance().onConnected(id,type,serverId,serverUniqueFlag,address);
	}

	//-----------------------------------------------------------------------------
	void GMServerMain::onServerDisconnect(I32 id,NetAddress* address)
	{
		address = NULL;
       // ServerManager::getInstance().onDisconnect(id);
	}

	//-----------------------------------------------------------------------------
	void GMServerMain::onServerRecvPacket(I32 id,NetEventRecv* packet)
	{
		//ServerManager::getInstance().processPacket(id,packet);
	}

	//-----------------------------------------------------------------------------
	void GMServerMain::freeEvent(INetEvent* netEvent)
	{
		if ( mServerLauncher )
		{
			mServerLauncher->freeEvent( netEvent );
		}
	}
}


