#include "stdafx.h"
#include "MapDB.h"
//#include "WorldManager.h"


#if 0
namespace MG
{

	//-----------------------------------------------------------------------
	Bool MapDbOp::checkOrCreateMapTable(DBDriver& driver)
	{
		static Colume mapColumn[] = 
		{      		
			{"map_id",			"BIGINT",			"0"},				//氏族ID
		};

		DBQueryResultEx resEx = driver.query("CREATE TABLE IF NOT EXISTS map_info (map_uin BIGINT NOT NULL AUTO_INCREMENT,PRIMARY KEY(map_uin))");
        DBQueryResult* res1 = *resEx;
		if (!res1 ||(res1 && res1->getResultType() == DBQuery_Result_INVALID))
		{
			return false;
		}

		Bool res2 = driver.addColume(MAP_TABLE_NAME,mapColumn,sizeof(mapColumn)/sizeof(Colume));
		if (!res2)
		{
			return false;
		}

		if ( !( *( driver.query("ALTER TABLE map_info ADD UNIQUE mapid (map_id)") ) ) )
		{
			return false;
		}
		return true;
	}

	//-----------------------------------------------------------------------
	Bool MapDbOp::checkMap(DBDriver& driver, Char8* sql)
	{

		return true;
	}

	//-----------------------------------------------------------------------
	Bool MapDbOp::createOrUpdateMapDB(DBDriver& driver, MapObject_OldVersion& mapDB)
	{

		return true;
	}

	//-----------------------------------------------------------------------
	Bool MapDbOp::loadMapFromDB(DBDriver& driver, MapObject_OldVersion& mapDB)
	{

		return true;
	}

	//-----------------------------------------------------------------------
	Bool MapDbOp::loadAllMapFromDB(DBDriver& driver, WorldManager_OldVersion* worldMgr)
	{
		Char8 sql[1028] = {0};
		MGStrOp::sprintf(
			sql,
			1028,
			"%s",
			"select * from map_info");
		Bool result = false; 
		DBQueryResult* dbRes = NULL;
        DBQueryResultEx resEx(dbRes);
		driver.queryLock();
		{ 
			resEx = driver.query( sql, false );
            dbRes = *resEx;
			if ( dbRes  &&  dbRes->getResultType() != DBQuery_Result_INVALID )
			{  
				result = true;
			}
		}
		driver.queryUnLock();
		
		if (result)
		{
			I32 nRow = dbRes->getRowCount();
			
			for(Int i = 0; i < nRow; i++)
			{
				I32 nCol = 1;
				MapObject_OldVersion* mapObj = worldMgr->retrieveMapObject(dbRes->getFieldData(i,nCol)->ulonglongData);
				if (mapObj)
				{
					//载入相关数据
					nCol++;
				}

			}
		}
		return result;
	}

	Bool MapDbOp::createDbRecordByMemory( DBDriver& driver, MapObject_OldVersion& mapDB )
	{

		Char8 sql[1028] = {0};
		MGStrOp::sprintf(
			sql,
			1028, 
			"insert into map_info (map_id) values (%d)",
			mapDB.getID());

		Bool result = false; 
        DBQueryResult* dbRes = NULL;
        DBQueryResultEx resEx(dbRes);
		driver.queryLock();
		{ 
			resEx = driver.query( sql, false );
            dbRes = *resEx;
			if ( dbRes  &&  dbRes->getResultType() != DBQuery_Result_INVALID )
			{  
				result = true;
			}
		}
		driver.queryUnLock();
		return result;
	}

}

#endif