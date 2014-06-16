#include "stdafx.h"
#include "PlaceDB.h"
//#include "WorldManager.h"

#if 0
namespace MG
{

	//-----------------------------------------------------------------------
	Bool PlaceDBOp::checkOrCreatePlaceTable(DBDriver& driver)
	{
		static Colume placeColumn[] = 
		{      		
			{"place_id",			"BIGINT",			"0"},				//氏族ID
		};

        DBQueryResultEx resEx = driver.query("CREATE TABLE IF NOT EXISTS place_info (place_uin BIGINT NOT NULL AUTO_INCREMENT,PRIMARY KEY(place_uin))");
		DBQueryResult* res1 = *resEx;
		if (!res1 ||(res1 && res1->getResultType() == DBQuery_Result_INVALID))
		{
			return false;
		}

		Bool res2 = driver.addColume(PLACE_TABLE_NAME,placeColumn,sizeof(placeColumn)/sizeof(Colume));
		if (!res2)
		{
			return false;
		}

		if ( !( *( driver.query("ALTER TABLE place_info ADD UNIQUE placeid (place_id)") ) ) )
		{
			return false;
		}
		return true;
	}

	//-----------------------------------------------------------------------
	Bool PlaceDBOp::checkPlace(DBDriver& driver, Char8* sql)
	{

		return true;
	}

	//-----------------------------------------------------------------------
	Bool PlaceDBOp::createOrUpdatePlaceDB(DBDriver& driver, PlaceObject_OldVersion& placeDB)
	{

		return true;
	}

	//-----------------------------------------------------------------------
	Bool PlaceDBOp::loadPlaceFromDB(DBDriver& driver, PlaceObject_OldVersion& placeDB)
	{

		return true;
	}

	//-----------------------------------------------------------------------
	Bool PlaceDBOp::loadAllPlaceFromDB(DBDriver& driver, WorldManager_OldVersion* worldMgr)
	{
		Char8 sql[1028] = {0};
		MGStrOp::sprintf(
			sql,
			1028,
			"%s",
			"select * from place_info");
		Bool result = false; 
		DBQueryResult* dbRes = NULL;
        DBQueryResultEx resEx( dbRes );
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
				PlaceObject_OldVersion* placeObj = worldMgr->retrievePlaceObject(dbRes->getFieldData(i,nCol)->ulonglongData);
				if (placeObj)
				{
					//载入相关数据
					nCol++;
				}

			}
		}
		return result;
	}

	Bool PlaceDBOp::createDbRecordByMemory( DBDriver& driver, PlaceObject_OldVersion& placeDB )
	{
		 Char8 sql[1028] = {0};
		 MGStrOp::sprintf(
			 sql,
			 1028, 
			 "insert into place_info (place_id) values (%d)",
			 placeDB.getID());

		 Bool result = false; 
         DBQueryResult* dbRes = NULL;
         DBQueryResultEx resEx( dbRes );
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