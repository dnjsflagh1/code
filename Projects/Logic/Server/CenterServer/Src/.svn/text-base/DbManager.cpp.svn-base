/******************************************************************************/
#include "stdafx.h"
#include "DbManager.h"
#include "AccountDB.h"
#include "ClanDataBase.h"
#include "PlayerCharacterDB.h"
//#include "DistrictDB.h"
#include "PlaceDB.h"
#include "MapDB.h"
//#include "SWorldManager.h"
/******************************************************************************/
namespace MG
{
	//-----------------------------------------------------------------------------
	DbManager::DbManager()
		:mMySqlDriver(NULL),
		mIsCreateTable(false)
	{
		
	}
	//-----------------------------------------------------------------------------
	DbManager::~DbManager()
	{

	}
	//-----------------------------------------------------------------------------
	void DbManager::uninitialize()
	{

	}
	//-----------------------------------------------------------------------------
	Bool DbManager::initialize( DBDriver* driver,SServerSetting* setting )
	{
		DYNAMIC_ASSERT(driver);
		DYNAMIC_ASSERT(setting);
		if (driver)
		{
			mMySqlDriver = driver;
		}
		if (setting)
		{
			mIsCreateTable = setting->getDbConnectInfo()->isCreate;
		}

		//´´½¨±í
		createAllTable();
		return true;
	}

	void DbManager::createAllTable()
	{
		if (mIsCreateTable)
		{
			AccountDBOp::checkOrCreateAccountTable(*mMySqlDriver);
			ClanDataBaseDBOp::checkOrCreateClanDataBaseTable(*mMySqlDriver);
			PlayerCharacterDBOp::checkOrCreatePlayerCharacterTable(*mMySqlDriver);
			//DistrictDBOp::checkOrCreateDistrictTable(*mMySqlDriver);
			//PlaceDBOp::checkOrCreatePlaceTable(*mMySqlDriver);
			//MapDbOp::checkOrCreateMapTable(*mMySqlDriver);
		}
	}

}