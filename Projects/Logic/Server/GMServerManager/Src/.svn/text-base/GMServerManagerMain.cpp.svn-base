/******************************************************************************/
#include "stdafx.h"
#include "GMServerManagerMain.h"
#include "GMAccountDB.h"
#include "GMClientManager.h"
#include "ServerManager.h"
/******************************************************************************/

namespace MG
{
    //-----------------------------------------------------------------------------
    GMServerManagerMain::GMServerManagerMain()
    {
        
    }

    //-----------------------------------------------------------------------------
    GMServerManagerMain::~GMServerManagerMain()
    {
        
    }

    //-----------------------------------------------------------------------------
    Bool GMServerManagerMain::initialize(ServerLauncherInterface* launcher)
    {
		mServerLauncher = launcher;
		DYNAMIC_ASSERT(mServerLauncher);
		if ( launcher == NULL )
			return false;

		Str16 str16KeyName = launcher->getConfigKeyName();
		str16KeyName = L"..\\Log\\" + str16KeyName;
		Str8 str8KeyName;
		MGStrOp::toString(str16KeyName.c_str(),str8KeyName);

		LogSystem::getInstance().setSysLogPath(str8KeyName.c_str());
		LogSystem::getInstance().setGameLogicLogPath(str8KeyName.c_str());
		LogSystem::getInstance().setPartName("LoginServer");
		LogSystem::getInstance().setEnableConsole(launcher->getServerSetting()->getCoreInfo()->isOpenConsole);
		LogSystem::getInstance().setLogLevel(launcher->getServerSetting()->getCoreInfo()->logLevel);
		LogSystem::getInstance().setSaveToFile(true);

		if (launcher->getServerSetting()->getDbConnectInfo()->isCreate)
		{
			GMAccountDBOp::checkOrCreateGMAccountTable(*(launcher->getDBDriver()));
		}
		if (!GMClientManager::getInstance().initialize())
		{
			return false;
		}
		if (!ServerManager::getInstance().initialize(launcher->getServerSetting()))
		{
			return false;
		}
        return true;
    }

    //-----------------------------------------------------------------------------
    void GMServerManagerMain::update()
	{
		//FUNDETECTION(__MG_FUNC__);
		
    }

    //-----------------------------------------------------------------------------
    Bool GMServerManagerMain::unInitialize()
    {
		//FUNDETECTION(__MG_FUNC__);
		GMClientManager::getInstance().uninitialize();
		ServerManager::getInstance().uninitialize();
		return true;
    }

	//-----------------------------------------------------------------------------
	void GMServerManagerMain::onClientConnected(I32 id,NetAddress*address)
	{
        
	}

	//-----------------------------------------------------------------------------
	void GMServerManagerMain::onClientDisconnect(I32 id)
	{
        //ClientManager::getInstance().onDisconnect(id);
	}

	//-----------------------------------------------------------------------------
	void GMServerManagerMain::onClientRecvPacket(I32 id,NetEventRecv* packet)
	{
		GMClientManager::getInstance().processPacket(id, packet);
	}

	//-----------------------------------------------------------------------------
	void GMServerManagerMain::onServerConnected(I32 id,GameNetType type,U32 serverId, U64 serverUniqueFlag, NetAddress*address)
	{
        //ServerManager::getInstance().onConnected(id,type,serverId,serverUniqueFlag,address);
	}

	//-----------------------------------------------------------------------------
	void GMServerManagerMain::onServerDisconnect(I32 id,NetAddress* address)
	{
		address = NULL;
       // ServerManager::getInstance().onDisconnect(id);
	}

	//-----------------------------------------------------------------------------
	void GMServerManagerMain::onServerRecvPacket(I32 id,NetEventRecv* packet)
	{
		//ServerManager::getInstance().processPacket(id,packet);
	}

	//-----------------------------------------------------------------------------
	void GMServerManagerMain::freeEvent(INetEvent* netEvent)
	{
		if ( mServerLauncher )
		{
			mServerLauncher->freeEvent( netEvent );
		}
	}
}


