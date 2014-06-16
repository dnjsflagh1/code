/******************************************************************************/
#include "stdafx.h"
#include "ChatServerMain.h"
//#include "LoginManager.h"
//#include "ClientManager.h"
#include "ServerManager.h"
/******************************************************************************/

namespace MG
{
    //-----------------------------------------------------------------------------
    ChatServerMain::ChatServerMain()
    {
        
    }

    //-----------------------------------------------------------------------------
    ChatServerMain::~ChatServerMain()
    {
        
    }

    //-----------------------------------------------------------------------------
    Bool ChatServerMain::initialize(ServerLauncherInterface* launcher)
    {
		//FUNDETECTION(__MG_FUNC__);

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
		MG::LogSystem::getInstance().setPartName("ChatServer");
		LogSystem::getInstance().setEnableConsole(launcher->getServerSetting()->getCoreInfo()->isOpenConsole);
		LogSystem::getInstance().setLogLevel(launcher->getServerSetting()->getCoreInfo()->logLevel);


		/*if ( ClientManager::getInstance().initialize() == false )
		{
			MG::MsgBox::show("客户端管理器初始化失败！");
			return false;
		}

		if ( ServerManager::getInstance().initialize() == false )
		{
			MG::MsgBox::show("服务器管理器初始化失败！");
			return false;
		}*/
		//	
		////mServerLauncher->writeDBLog("aaaaaaaaaa");
		//if ( LoginManager::getInstance().initialize(launcher->getDBDriver(),launcher->getServerSetting()) == false )
		//{
		//	MG::MsgBox::show("登陆管理器初始化失败！");
		//	return false;
		//}
        return true;
    }

    //-----------------------------------------------------------------------------
    void ChatServerMain::update()
	{
		//FUNDETECTION(__MG_FUNC__);
		/*ClientManager::getInstance().update();
		ServerManager::getInstance().update();
		LoginManager::getInstance().update();*/
    }

    //-----------------------------------------------------------------------------
    Bool ChatServerMain::unInitialize()
    {
		//FUNDETECTION(__MG_FUNC__);
       /* LoginManager::getInstance().uninitialize();
		ClientManager::getInstance().uninitialize();
		ServerManager::getInstance().uninitialize();*/
        return true;
    }

	//-----------------------------------------------------------------------------
	void ChatServerMain::onClientConnected(I32 id,NetAddress*address, INetConnect* connect)
	{
       // ClientManager::getInstance().onConnected(id,address);
	}

	//-----------------------------------------------------------------------------
	void ChatServerMain::onClientDisconnect(I32 id, INetConnect* connect)
	{
       // ClientManager::getInstance().onDisconnect(id);
	}

	//-----------------------------------------------------------------------------
	void ChatServerMain::onClientRecvPacket(I32 id,NetEventRecv* packet, INetConnect* connect)
	{
		//ClientManager::getInstance().processPacket(id, packet);
	}

	//-----------------------------------------------------------------------------
	void ChatServerMain::onServerConnected(I32 id,GameNetType type, U32 serverId, U64 serverUniqueFlag, NetAddress*address)
	{
        ServerManager::getInstance().onConnected(id,type,serverId,serverUniqueFlag,address);
	}

	//-----------------------------------------------------------------------------
	void ChatServerMain::onServerDisconnect(I32 id,NetAddress* address)
	{
		address = NULL;
        //ServerManager::getInstance().onDisconnect(id);
	}

	//-----------------------------------------------------------------------------
	void ChatServerMain::onServerRecvPacket(I32 id,NetEventRecv* packet)
	{
		ServerManager::getInstance().processPacket(id,packet);
	}

}


