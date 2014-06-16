/******************************************************************************/
#include "stdafx.h"
#include "CenterServerMain.h"
#include "ServerManager.h"
//#include "SWorldManager.h"
#include "DbManager.h"
#include "CenterGameTimeSystem.h"
#include "CalendarInfo.h"
#include "SWorldManager.h"
#include "SCampaignManager.h"
#include "BattleConfig.h"
#include "PrintDialog.h"
#include "PrintWindowsCfg.h"

#include "PlaceListCsv.h"
#include "InstanceListCsv.h"
#include "InstanceTimeListCsv.h"
#include "InstanceAtkListCsv.h"
/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------------
	CenterServerMain::CenterServerMain()
	{

	}

	//-----------------------------------------------------------------------------
	CenterServerMain::~CenterServerMain()
	{

	}

	//-----------------------------------------------------------------------------
	Bool CenterServerMain::initialize(ServerLauncherInterface* launcher)
	{
		Str16 str16KeyName = launcher->getConfigKeyName();
		str16KeyName = L"..\\Log\\" + str16KeyName;
		Str8 str8KeyName;
		MGStrOp::toString(str16KeyName.c_str(),str8KeyName);

		MG::LogSystem::getInstance().setSysLogPath(str8KeyName.c_str());
		MG::LogSystem::getInstance().setGameLogicLogPath(str8KeyName.c_str());
		MG::LogSystem::getInstance().setPartName("CenterServer");
		LogSystem::getInstance().setEnableConsole(launcher->getServerSetting()->getCoreInfo()->isOpenConsole);
		LogSystem::getInstance().setLogLevel(launcher->getServerSetting()->getCoreInfo()->logLevel);
		LogSystem::getInstance().setSaveToFile(true);

		if ( launcher == NULL )
			return false;

		mServerLauncher = launcher;

		DYNAMIC_ASSERT(mServerLauncher);

		if ( LoadFile() == false )        //加载公共资源。
			return false;

		if ( ServerManager::getInstance().initialize(launcher->getServerSetting()) == false )
			return false;

		
		//if (DbManager::getInstance().initialize(launcher->getDBDriver(),launcher->getServerSetting()) == false)
		//	return false;

		//if (SWorldManager::getInstance().initialize(launcher)== false)
		//	return false;

		if ( SWorldManager::getInstance().initialize(launcher) == false )
			return false;

		//if(CenterGameTimeSystem::getInstance().initialize() == false)
		//	return false;


		PrintDialog::getInstance().createMainDialog();

		return true;
	}

	//-----------------------------------------------------------------------------
	void CenterServerMain::update()
	{
		SCampaignManager::getInstance().update();
	}

	//-----------------------------------------------------------------------------
	Bool CenterServerMain::unInitialize()
	{
        DbManager::getInstance().uninitialize();
        SWorldManager::getInstance().unInitialize();
        CenterGameTimeSystem::getInstance().unInitialize();
        ServerManager::getInstance().uninitialize();

		return true;
	}

	//-----------------------------------------------------------------------------
	void CenterServerMain::onClientConnected(I32 id,NetAddress*address, INetConnect* connect)
	{

	}

	//-----------------------------------------------------------------------------
	void CenterServerMain::onClientDisconnect(I32 id, INetConnect* connect)
	{

	}

	//-----------------------------------------------------------------------------
	void CenterServerMain::onClientRecvPacket(I32 id,NetEventRecv* packet, INetConnect* connect)
	{


	}

	//-----------------------------------------------------------------------------
	void CenterServerMain::onServerConnected(I32 id,GameNetType type, U32 serverId,U64 serverUniqueFlag, NetAddress*address)
	{
		ServerManager::getInstance().onConnected( id, type,serverId, serverUniqueFlag, address );
	}

	//-----------------------------------------------------------------------------
	void CenterServerMain::onServerDisconnect(I32 id,NetAddress*address)
	{
		ServerManager::getInstance().onDisconnect( id );
	}

	//-----------------------------------------------------------------------------
	void CenterServerMain::onServerRecvPacket(I32 id,NetEventRecv* packet)
	{
		ServerManager::getInstance().processPacket( id,  packet );
	}
	//-----------------------------------------------------------------------------

	MG::Bool CenterServerMain::LoadFile()
	{
		if(PlaceListCsv::getInstance().load(L"Config\\Game\\World\\PlaceList.csv") == false)
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		//副本
		if ( InstanceListCsv::getInstance().load(L"Config\\Game\\World\\InstanceList.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		//副本中用到的时间
		if ( InstanceTimeListCsv::getInstance().load(L"Config\\Game\\World\\InstanceTimeList.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}


		//Atk 副本
		if ( InstanceAtkListCsv::getInstance().load(L"Config\\Game\\World\\InstanceAtkList.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}


		if ( CalendarInfos::getInstance().load(L"Config\\Game\\Text\\Calendar.csv") == false )
			return false;

		//战斗相关配置
		if ( BattleConfig::getInstance().loadFile(getSettingFilePath()+ L"BattleConfig.ini") == false )
			return false;

		//打印相关配置
		if ( PrintWindowsCfg::getInstance().loadFile(getSettingFilePath() + L"PrintWindowsCfg.ini") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		return true;
	}

	//-----------------------------------------------------------------------------
	MG::Str16 CenterServerMain::getSettingFilePath()
	{
       return mServerLauncher->getSettingPathName();
	}
}


