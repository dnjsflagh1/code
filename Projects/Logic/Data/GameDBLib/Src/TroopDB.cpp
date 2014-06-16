/******************************************************************************/
#include "stdafx.h"
#include "TroopDB.h"
#include "MySqlDriver.h"
#include "DBQueryResult.h"
#include "DBDriver.h"
#include "CommonGameDBOp.h"
/******************************************************************************/
#if 0
namespace MG
{
    Bool TroopDBOp::checkOrCreateTroopTable( DBDriver& driver )
    {
        static Colume troopColumn[] = 
        {      		
            {"troop_master_id",			"BIGINT",			"0"},				//根据以上主人类型，记录的Id( 或regionID或clanID )
            {"troop_template_id",		"INT",		        "0"},				//军队模板id	
            {"troop_master_type",	    "INT",		        "0"},				//"军队主人的类型，   
            {"troop_life_type",			"INT",		        "0"},				//军队存活类型，
            {"troop_lvl",               "INT",              "0"},               //军队等级
            {"troop_exp",			    "INT",			    "0"},				//军队当前经验度，最大为1000
            {"troop_num",		        "INT",			    "0"},				//军队当前兵数		
            {"troop_loyal",		        "INT",			    "0"},				//军队当前忠诚度，最大为1000
            {"troop_weapon",			"INT",			    "0"},				//军队当前武装度，最大为1000           
            {"troop_wound",			    "INT",			    "0"},				//军队当前伤兵率，最大为1000            
        };

        DBQueryResultEx resEx = driver.query("CREATE TABLE IF NOT EXISTS "TROOP_TABLE_NAME" (troop_id BIGINT NOT NULL AUTO_INCREMENT,PRIMARY KEY(troop_id))");
        DBQueryResult* pRes = *resEx;
        if (!pRes ||(pRes && pRes->getResultType() == DBQuery_Result_INVALID))
        {
            return false;
        }

        Bool res1 = driver.addColume(TROOP_TABLE_NAME,troopColumn,sizeof(troopColumn)/sizeof(Colume));
        if (!res1)
        {
            return false;
        }
        //加索引
        if ( !( *( driver.query("ALTER TABLE "TROOP_TABLE_NAME" ADD INDEX  troopmaster (troop_master_id, troop_master_type)") ) ) )
        {
            return false;
        }

        return true;
    }
    //----------------------------------------------------------------------------------------
    Bool TroopDBOp::createTroop( DBDriver& driver, const TroopData* troopDB, U64& uid )
    {
		return true;
        ////插入
        //Char8 sql[512] = {0};

        //MGStrOp::sprintf(
        //    sql,
        //    1028, 		
        //    "insert into "TROOP_TABLE_NAME"\
        //    (troop_master_id, troop_template_id, troop_master_type, troop_life_type, troop_lvl, \
        //    troop_exp, troop_num, troop_loyal, troop_weapon, troop_wound) \
        //    values('%I64d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d')" ,
        //    troopDB->MasterId, troopDB->ArmyTemplateId, troopDB->MasterType, troopDB->ArmyLiveType, troopDB->ArmyLevel,
        //    troopDB->ArmyExp, troopDB->ArmyNum, troopDB->ArmyLoyal, troopDB->ArmyWeapon, troopDB->ArmyWound
        //    );

        //Bool result = false; 
        //DBQueryResult* dbRes = NULL;
        //driver.queryLock();
        //{
        //    DBQueryResultEx resEx = driver.query( sql, false );
        //    dbRes =  *resEx;
        //    if ( dbRes  &&  dbRes->getResultType() != DBQuery_Result_INVALID )
        //    {  
        //        result = true;
        //        uid = CommonGameDBOp::getLastInsertID( driver, false );
        //    }
        //}
        //driver.queryUnLock();
        //return result;
    }
    //----------------------------------------------------------------------------------------
    Bool TroopDBOp::getTroop( DBDriver& driver, U64 ArmyDataBaseId, TroopData& troopDB )
    {
 /*       Char8 sql[128] = {0};
        MGStrOp::sprintf(sql,128,"select * from "TROOP_TABLE_NAME" where troop_id = %I64d", ArmyDataBaseId);

        DBQueryResultEx resEx = driver.query(sql);
        DBQueryResult* res = *resEx;

        
        if ( res  &&  res->getResultType() != DBQuery_Result_INVALID  &&  res->getRowCount() > 0 )
        {
            assert( res->getRowCount() < 2 );
            
            memset(&troopDB, 0, sizeof(troopDB));
            U32 nCol = 0;

            troopDB.ArmyDataBaseId         = res->getFieldData( 0, nCol++ )->ulonglongData;
            troopDB.MasterId               = res->getFieldData( 0, nCol++ )->ulonglongData;
            troopDB.ArmyTemplateId         = res->getFieldData( 0, nCol++ )->uintData;
            troopDB.MasterType             = (TROOP_MASTER_TYPE)res->getFieldData( 0, nCol++ )->uintData;
            troopDB.ArmyLiveType           = (TROOP_LIFE_TYPE)res->getFieldData( 0, nCol++ )->uintData;
            troopDB.ArmyLevel              = res->getFieldData( 0, nCol++ )->uintData;
            troopDB.ArmyExp                = res->getFieldData( 0, nCol++ )->uintData;
            troopDB.ArmyNum                = res->getFieldData( 0, nCol++ )->uintData;
            troopDB.ArmyLoyal              = res->getFieldData( 0, nCol++ )->uintData;
            troopDB.ArmyWeapon             = res->getFieldData( 0, nCol++ )->uintData;           
            troopDB.ArmyWound              = res->getFieldData( 0, nCol++ )->uintData;

            return true;
        }*/

        return false;
    }
    //----------------------------------------------------------------------------------------
    Bool TroopDBOp::getTroopsDataMap( DBDriver& driver, TROOP_MASTER_TYPE MasterType, U64 MasterId, std::map<U64,TroopData>& dataList )
    {
        //TroopData data;

        //Char8 sql[128] = {0};
        //MGStrOp::sprintf(sql,128,"select * from "TROOP_TABLE_NAME" where troop_master_id = %I64d and troop_master_type = %d", MasterId, MasterType);

        //DBQueryResultEx resEx = driver.query(sql);
        //DBQueryResult* res = *resEx;
        //if ( res  &&  res->getResultType() != DBQuery_Result_INVALID  &&  res->getRowCount() > 0 )
        //{
        //    I32 nRow = res->getRowCount();
        //    for ( I32 i=0; i<nRow; i++ )
        //    {
        //        memset(&data, 0, sizeof(data));
        //        U32 nCol = 0;

        //        data.ArmyDataBaseId         = res->getFieldData( 0, nCol++ )->ulonglongData;
        //        data.MasterId               = res->getFieldData( 0, nCol++ )->ulonglongData;
        //        data.ArmyTemplateId         = res->getFieldData( 0, nCol++ )->uintData;
        //        data.MasterType             = (TROOP_MASTER_TYPE)res->getFieldData( 0, nCol++ )->uintData;
        //        data.ArmyLiveType           = (TROOP_LIFE_TYPE)res->getFieldData( 0, nCol++ )->uintData;
        //        data.ArmyLevel              = res->getFieldData( 0, nCol++ )->uintData;
        //        data.ArmyExp                = res->getFieldData( 0, nCol++ )->uintData;
        //        data.ArmyNum                = res->getFieldData( 0, nCol++ )->uintData;
        //        data.ArmyLoyal              = res->getFieldData( 0, nCol++ )->uintData;
        //        data.ArmyWeapon             = res->getFieldData( 0, nCol++ )->uintData;           
        //        data.ArmyWound              = res->getFieldData( 0, nCol++ )->uintData;

        //        dataList[data.ArmyDataBaseId] = data;
        //    }
        //    return true;
        //}

        return false;
    }
}
#endif