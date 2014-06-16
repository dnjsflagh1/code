/******************************************************************************/
#include "stdafx.h"
#include "LoginServerMain.h"
#include "LoginManager.h"
#include "ClientManager.h"
#include "ServerManager.h"
#include "LoginConfig.h"
#include "ThreadTaskManager.h"
#include "TestNetPacketProcesser.h"
/******************************************************************************/

namespace MG
{
    //-----------------------------------------------------------------------------
    LoginServerMain::LoginServerMain()
    {
        
    }

    //-----------------------------------------------------------------------------
    LoginServerMain::~LoginServerMain()
    {
        
    }

    //-----------------------------------------------------------------------------
    Bool LoginServerMain::initialize(ServerLauncherInterface* launcher)
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

		if ( ClientManager::getInstance().initialize() == false )
		{
			MG::MsgBox::show("客户端管理器初始化失败！");
			return false;
		}

		if ( ServerManager::getInstance().initialize() == false )
		{
			MG::MsgBox::show("服务器管理器初始化失败！");
			return false;
		}
		
		
		LoginConfigInfo* loginConfigInfo = NULL;
		if (LoginConfig::getInstance().loadFile(launcher->getSettingPathName() + L"LoginConfig.txt"))
		{
             loginConfigInfo = LoginConfig::getInstance().getLoginConfigInfo();
		}
		else
		{
			MG::MsgBox::show("服务器登录配置初始化失败！");
			return false;
		}
		//mServerLauncher->writeDBLog("aaaaaaaaaa");
        if ( LoginManager::getInstance().initialize(launcher->getDBDriver(),launcher->getServerSetting(),loginConfigInfo) == false )
		{
			MG::MsgBox::show("登陆管理器初始化失败！");
			return false;
		}
		
		if (ThreadTaskManager::getInstance().initialize() == false)
		{
			MG::MsgBox::show("线程初始化失败！");
			return false;
		}
        return true;
    }

    //-----------------------------------------------------------------------------
    void LoginServerMain::update()
	{
		//FUNDETECTION(__MG_FUNC__);
		ClientManager::getInstance().update();
		ServerManager::getInstance().update();
		LoginManager::getInstance().update();
    }

    //-----------------------------------------------------------------------------
    Bool LoginServerMain::unInitialize()
    {
		//FUNDETECTION(__MG_FUNC__);
        ThreadTaskManager::getInstance().unInitialize();


        LoginManager::getInstance().uninitialize();
		ClientManager::getInstance().uninitialize();
		ServerManager::getInstance().uninitialize();

        return true;
    }

	//-----------------------------------------------------------------------------
	void LoginServerMain::onClientConnected(I32 id,NetAddress*address, INetConnect* connect)
	{
        ClientManager::getInstance().onConnected(id,address);
	}

	//-----------------------------------------------------------------------------
	void LoginServerMain::onClientDisconnect(I32 id, INetConnect* connect)
	{
        ClientManager::getInstance().onDisconnect(id);
		LoginManager::getInstance().removeLogingPlayerByNetId(id);
	}

	//-----------------------------------------------------------------------------
	void LoginServerMain::onClientRecvPacket(I32 id,NetEventRecv* packet, INetConnect* connect)
	{
		if ( TestNetPacketProcesser::getInstance().processClientPacket( id, packet ) == true )
			return;
		//ThreadTaskManager::getInstance().addClientNormalTask(packet,id,id);
		ClientManager::getInstance().processPacket(id, packet);
	}

	//-----------------------------------------------------------------------------
	void LoginServerMain::onServerConnected(I32 id,GameNetType type,U32 serverId, U64 serverUniqueFlag, NetAddress*address)
	{
        ServerManager::getInstance().onConnected(id,type,serverId,serverUniqueFlag,address);
	}

	//-----------------------------------------------------------------------------
	void LoginServerMain::onServerDisconnect(I32 id,NetAddress* address)
	{
		address = NULL;
        ServerManager::getInstance().onDisconnect(id);
	}

	//-----------------------------------------------------------------------------
	void LoginServerMain::onServerRecvPacket(I32 id,NetEventRecv* packet)
	{
		ThreadTaskManager::getInstance().addServerNormalTask(packet,id,id);
		//ServerManager::getInstance().processPacket(id,packet);
	}

	//-----------------------------------------------------------------------------
	void LoginServerMain::freeEvent(INetEvent* netEvent)
	{
		if ( mServerLauncher )
		{
			mServerLauncher->freeEvent( netEvent );
		}
	}
}


