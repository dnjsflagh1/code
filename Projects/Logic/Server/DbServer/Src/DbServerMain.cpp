/******************************************************************************/
#include "stdafx.h"
#include "DbServerMain.h"
#include "ServerDllInterface.h"
//#include "ServerManager.h"


/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------------
	DbServerMain::DbServerMain()
        :mLuaMgr(NULL)
	{
        //调用这个函数来检测：
        _CrtDumpMemoryLeaks();
       // mLuaMgr = MG_NEW LuaManager;
	}

	//-----------------------------------------------------------------------------
	DbServerMain::~DbServerMain()
	{
        unInitialize();
        MG_SAFE_DELETE(mLuaMgr);
	}

	//-----------------------------------------------------------------------------
	Bool DbServerMain::initialize(ServerLauncherInterface* launcher)
	{
		//FUNDETECTION(__MG_FUNC__);
		MG::LogSystem::getInstance().setSysLogPath("log");
		MG::LogSystem::getInstance().setGameLogicLogPath("log");
		MG::LogSystem::getInstance().setPartName("DbServer");
		DYNAMIC_ASSERT(launcher);
		if ( launcher == NULL )
			return false;
		mServerLauncher = launcher;
		
		LogSystem::getInstance().setLogLevel( out_max );
		
        if ( LoadFile() == false )        //加载公共资源。
            return false;

        if ( CreateTable() == false )
            return false;


		return true;
	}

	//-----------------------------------------------------------------------------
	void DbServerMain::update()
	{
		//FUNDETECTION(__MG_FUNC__);
		//FringeGameTimeSystem::getInstance().update();
		//NetPacketPackManager::getInstance().update();
		//SWorldManager::getInstance().update();
	}

	//-----------------------------------------------------------------------------
	Bool DbServerMain::unInitialize()
	{
		//FUNDETECTION(__MG_FUNC__);
		//mLuaMgr->unInitialize();
		return true;
	}

	//-----------------------------------------------------------------------------
	void DbServerMain::onClientConnected(I32 id,NetAddress*address)
	{

	}

	//-----------------------------------------------------------------------------
	void DbServerMain::onClientDisconnect(I32 id)
	{

	}

	//-----------------------------------------------------------------------------
	void DbServerMain::onClientRecvPacket(I32 id,NetEventRecv* packet)
	{
		//FUNDETECTION(__MG_FUNC__);

	}

	//-----------------------------------------------------------------------------
	void DbServerMain::onServerConnected(I32 id,GameNetType type, U32 serverId, U64 serverUniqueFlag,NetAddress*address)
	{
	
	}

	//-----------------------------------------------------------------------------
	void DbServerMain::onServerDisconnect(I32 id,NetAddress*address)
	{

	}

	//-----------------------------------------------------------------------------
	void DbServerMain::onServerRecvPacket(I32 id,NetEventRecv* packet)
	{
		//FUNDETECTION(__MG_FUNC__);

	}
    //-----------------------------------------------------------------------------
    DBDriver* DbServerMain::getDBDriver()
    {
        return mServerLauncher->getDBDriver();
    }

    //-----------------------------------------------------------------------------
    Bool DbServerMain::LoadFile()
    {
		//FUNDETECTION(__MG_FUNC__);
        return true;
    }
    //-----------------------------------------------------------------------------
    MG::Bool DbServerMain::CreateTable()
    {
        if (mServerLauncher->getServerSetting()->getDbConnectInfo()->isCreate)
        {
            //PlayerCharacterDBOp::checkOrCreatePlayerCharacterTable( *( mServerLauncher->getDBDriver() ) );
            ////创建表 ClanDataBase_info
            //ClanDataBaseDBOp::checkOrCreateClanDataBaseTable( *( mServerLauncher->getDBDriver() ) );

            //SkillDBOp::checkOrCreateSkillTable( *( mServerLauncher->getDBDriver() ) );

            //ItemDBOp::checkOrCreateItemDBTable( *( mServerLauncher->getDBDriver() ) );

            return true;
        }

        return false;
    }
}


