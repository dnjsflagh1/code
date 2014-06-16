/******************************************************************************/
#include "stdafx.h"
#include "DbManager.h"
#include "LogAccountDB.h"
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
    //-----------------------------------------------------------------------------
	void DbManager::createAllTable()
	{
		if (mIsCreateTable)
		{
            LogAccountDBOp::checkOrCreateLogAccountDBTable(mMySqlDriver);
		}
	}

}