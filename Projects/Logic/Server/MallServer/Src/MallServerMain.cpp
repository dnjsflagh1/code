/******************************************************************************/
#include "stdafx.h"
#include "MallServerMain.h"
#include "ServerManager.h"
#include "DbManager.h"
/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------------
	MallServerMain::MallServerMain()
	{

	}

	//-----------------------------------------------------------------------------
	MallServerMain::~MallServerMain()
	{

	}

	//-----------------------------------------------------------------------------
	Bool MallServerMain::initialize(ServerLauncherInterface* launcher)
	{
		if ( launcher == NULL )
			return false;

		mServerLauncher = launcher;

		MG::LogSystem::getInstance().setSysLogPath("log");
		MG::LogSystem::getInstance().setGameLogicLogPath("log");
		MG::LogSystem::getInstance().setPartName("MallServer");
		LogSystem::getInstance().setEnableConsole(launcher->getServerSetting()->getCoreInfo()->isOpenConsole);
		LogSystem::getInstance().setLogLevel(launcher->getServerSetting()->getCoreInfo()->logLevel);
		DYNAMIC_ASSERT(mServerLauncher);


		if ( ServerManager::getInstance().initialize(launcher->getServerSetting()) == false )
			return false;
		
		if (DbManager::getInstance().initialize(launcher->getDBDriver(),launcher->getServerSetting()) == false)
			return false;

		return true;
	}

	//-----------------------------------------------------------------------------
	void MallServerMain::update()
	{
	}

	//-----------------------------------------------------------------------------
	Bool MallServerMain::unInitialize()
	{
		return true;
	}

	//-----------------------------------------------------------------------------
	void MallServerMain::onClientConnected(I32 id,NetAddress*address, INetConnect* connect)
	{

	}

	//-----------------------------------------------------------------------------
	void MallServerMain::onClientDisconnect(I32 id, INetConnect* connect)
	{

	}

	//-----------------------------------------------------------------------------
	void MallServerMain::onClientRecvPacket(I32 id,NetEventRecv* packet, INetConnect* connect)
	{


	}

	//-----------------------------------------------------------------------------
	void MallServerMain::onServerConnected(I32 id,GameNetType type,U32 serverId, U64 serverUniqueFlag, NetAddress*address)
	{
		ServerManager::getInstance().onConnected( id, type, serverId, serverUniqueFlag, address );
	}

	//-----------------------------------------------------------------------------
	void MallServerMain::onServerDisconnect(I32 id,NetAddress*address)
	{
		ServerManager::getInstance().onDisconnect( id );
	}

	//-----------------------------------------------------------------------------
	void MallServerMain::onServerRecvPacket(I32 id,NetEventRecv* packet)
	{
		ServerManager::getInstance().processPacket( id,  packet );
	}

}


