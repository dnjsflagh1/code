/******************************************************************************/
#include "stdafx.h"
#include "SysLogServerMain.h"
#include "ServerManager.h"
#include "DbManager.h"
/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------------
	SysLogServerMain::SysLogServerMain()
	{

	}

	//-----------------------------------------------------------------------------
	SysLogServerMain::~SysLogServerMain()
	{

	}

	//-----------------------------------------------------------------------------
	Bool SysLogServerMain::initialize(ServerLauncherInterface* launcher)
	{
		if ( launcher == NULL )
			return false;

		LogSystem::getInstance().setSysLogPath("log");
		LogSystem::getInstance().setGameLogicLogPath("log");
		LogSystem::getInstance().setPartName("SysLogServer");
		LogSystem::getInstance().setEnableConsole(launcher->getServerSetting()->getCoreInfo()->isOpenConsole);
		LogSystem::getInstance().setLogLevel(launcher->getServerSetting()->getCoreInfo()->logLevel);
		mServerLauncher = launcher;

		DYNAMIC_ASSERT(mServerLauncher);


		if ( ServerManager::getInstance().initialize(launcher->getServerSetting()) == false )
			return false;
		
		if (DbManager::getInstance().initialize(launcher->getDBDriver(),launcher->getServerSetting()) == false)
			return false;

		return true;
	}

	//-----------------------------------------------------------------------------
	void SysLogServerMain::update()
	{
	}

	//-----------------------------------------------------------------------------
	Bool SysLogServerMain::unInitialize()
	{
		return true;
	}

	//-----------------------------------------------------------------------------
	void SysLogServerMain::onClientConnected(I32 id,NetAddress*address,INetConnect* connect)
	{

	}

	//-----------------------------------------------------------------------------
	void SysLogServerMain::onClientDisconnect(I32 id,INetConnect* connect)
	{

	}

	//-----------------------------------------------------------------------------
	void SysLogServerMain::onClientRecvPacket(I32 id,NetEventRecv* packet,INetConnect* connect)
	{

	}

	//-----------------------------------------------------------------------------
	void SysLogServerMain::onServerConnected(I32 id,GameNetType type,U32 serverId, U64 serverUniqueFlag, NetAddress*address)
	{
		ServerManager::getInstance().onConnected( id, type, serverId, serverUniqueFlag, address );
	}

	//-----------------------------------------------------------------------------
	void SysLogServerMain::onServerDisconnect(I32 id,NetAddress*address)
	{
		ServerManager::getInstance().onDisconnect( id );
	}

	//-----------------------------------------------------------------------------
	void SysLogServerMain::onServerRecvPacket(I32 id,NetEventRecv* packet)
	{
		ServerManager::getInstance().processPacket( id,  packet );
	}

}


