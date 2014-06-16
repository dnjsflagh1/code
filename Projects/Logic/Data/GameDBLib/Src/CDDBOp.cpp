//**********************************************************************************************************
#include "stdafx.h"
#include "CDDBOp.h"
//**********************************************************************************************************
namespace MG
{
    MG::Bool CDDBOp::checkOrCreateCDDBTable( DBDriver& driver )
    {
        static Colume CDDBColumn[] = 
        {
            {"cddb_master_id",              "BIGINT",               "0"},                                 //CD影响的id
            {"cddb_type",                   "TINYINT",              "0"},                                 //CD影响的类型
            {"cddb_cd_id",                  "TINYINT",              "0"},                                 //CD的ID
            {"cddb_last_time",              "INT",                  "0"},                                 //Cd的剩余使用时间（如果是真实时间，就是到期时间）
            {"cddb_save_time",              "BIGINT",               "0"}                                  //CD的保存时间。（上次推出的时间）
        };
        DBQueryResultEx resEx = driver.query("CREATE TABLE IF NOT EXISTS cddb_info (cddb_id BIGINT NOT NULL AUTO_INCREMENT,PRIMARY KEY(cddb_id))");
        DBQueryResult* res1 =  *resEx;
        if ( !res1 || res1->getResultType() == DBQuery_Result_INVALID  )
        {
            return false;
        }

        Bool  res2 = driver.addColume( CDDB_TABLE_NAME, CDDBColumn, sizeof(CDDBColumn)/sizeof(Colume) );
        if ( !res2 )
        {
            return false;
        }

        //查询自己的CD的索引
        if ( !( *( driver.query("CREATE INDEX cdmasteridtype ON cddb_info (cddb_master_id, cddb_type)") ) ) )
        {
            return false;
        } 

        //唯一
        if ( !( *( driver.query("CREATE INDEX cdmasteridtypecdid ON cddb_info (cddb_master_id, cddb_type, cddb_cd_id)") ) ) )
        {
            return false;
        }

        return true;
    }
    //----------------------------------------------------------------------------------------------
    MG::Bool CDDBOp::getCDDBList( DBDriver& driver, const IdType& masterID, const CD_MASTER_TYPE& masterType, std::vector<CDDBData>& CDList )
    {
        CDDBData data;
        Char8 sql[128] = {0};
        MGStrOp::sprintf(sql,128,"select * from cddb_info where cddb_master_id = %I64d and cddb_type = %d",masterID, masterType);

        DBQueryResultEx resEx = driver.query(sql);
        DBQueryResult* res = *resEx;
        if ( res  &&  res->getResultType() != DBQuery_Result_INVALID  &&  res->getRowCount() > 0 )
        {
            I32 nRow = res->getRowCount();
            for ( I32 i=0; i<nRow; i++ )
            {
                memset(&data, 0, sizeof(data));
                U32 nCol = 2;

                data.cdTempId                   = res->getFieldData( i, nCol++ )->uintData;
                data.lastTime                   = res->getFieldData( i, nCol++ )->uintData;
                data.saveTime                   = res->getFieldData( i, nCol++ )->ulonglongData;

                CDList.push_back(data);
            }
            return true;
        }

        return false;
    }
    //----------------------------------------------------------------------------------------------
    MG::Bool CDDBOp::insertCDDB( DBDriver& driver, IdType masterID, CD_MASTER_TYPE masterType, U32 CDtempID, U32 lastTime )
    {
        Char8 sql[256] = {0};
        MGStrOp::sprintf(sql,256,"insert into cddb_info \
            (cddb_master_id, cddb_type, cddb_cd_id, cddb_last_time, cddb_save_time) \
            values('%I64d', '%d', '%d', '%d', '%I64d')",
            masterID, masterType, CDtempID, lastTime
            ,MGTimeOp::getCurrTimestamp() 
       );

        DBQueryResultEx resEx = driver.query(sql);
        DBQueryResult* res = *resEx;
        if ( res  &&  res->getResultType() != DBQuery_Result_INVALID )
        {
            return true;
        }

        return false;
    }
    //----------------------------------------------------------------------------------------------
    MG::Bool CDDBOp::checkCDDBExist( DBDriver& driver, const IdType& masterID, const CD_MASTER_TYPE& masterType, U32 CDtempID )
    {
        Char8 sql[128] = {0};
        MGStrOp::sprintf(sql,128,
            "select * from cddb_info where cddb_master_id = %I64d and cddb_type = %d and cddb_cd_id = %d",
            masterID, masterType, CDtempID);

        DBQueryResultEx resEx = driver.query(sql);
        DBQueryResult* res = *resEx;
        if ( res  &&  res->getResultType() != DBQuery_Result_INVALID  &&  res->getRowCount() > 0 )
        {
            return true;
        }

        return false;
    }
    //----------------------------------------------------------------------------------------------
    MG::Bool CDDBOp::updateCDDB( DBDriver& driver, IdType masterID, CD_MASTER_TYPE masterType, U32 CDtempID, U32 lastTime )
    {
        if ( checkCDDBExist(driver, masterID, masterType, CDtempID) )
        {
            Char8 sql[256] = {0};
            MGStrOp::sprintf(sql,256,
                "update cddb_info set cddb_last_time = '%d', cddb_save_time = '%I64d'\
                where cddb_master_id = %I64d and cddb_type = %d and cddb_cd_id = %d",
                lastTime, MGTimeOp::getCurrTimestamp(),
                masterID, masterType, CDtempID);

            DBQueryResultEx resEx = driver.query(sql);
            DBQueryResult* res = *resEx;
            if ( res  &&  res->getResultType() != DBQuery_Result_INVALID )
            {
                return true;
            }

            return false;
        }
        else
        {
            return insertCDDB( driver, masterID, masterType, CDtempID, lastTime );
        }
    }
}