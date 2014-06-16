//***************************************************************************************
#include "stdafx.h"
#include "LogAccountDB.h"
#include "MySqlDriver.h"
#include "DBQueryResult.h"
#include "DBDriver.h"
#include "CommonGameDBOp.h"
//***************************************************************************************
namespace MG
{
    MG::Bool LogAccountDBOp::checkOrCreateLogAccountDBTable( DBDriver* driver )
    {
        static Colume logaccountDBColume[] = 
        {
            {"logaccdb_account_id",                  "BIGINT",               "0"},                                 //模板ID
            {"logaccdb_type",                       "TINYINT",               "0"},                                 //归属氏族ID
            {"logaccdb_name",                    "VARCHAR(50)",              "0"},                                 //目前格位
            {"logaccdb_time",                       "BIGINT",                "0"}
        };

        DBQueryResultEx resEx = driver->query("CREATE TABLE IF NOT EXISTS "LOGACCOUNT_TABLE_NAME" (logaccdb_id BIGINT NOT NULL AUTO_INCREMENT,PRIMARY KEY(logaccdb_id))");
        DBQueryResult* res1 =  *resEx;
        if ( !res1 || res1->getResultType() == DBQuery_Result_INVALID  )
        {
            return false;
        }

        Bool  res2 = driver->addColume( LOGACCOUNT_TABLE_NAME, logaccountDBColume, sizeof(logaccountDBColume)/sizeof(Colume) );
        if ( !res2 )
        {
            return false;
        }

        //查询自己的物品的索引
        if ( !( *( driver->query("CREATE INDEX logacc_accid ON "LOGACCOUNT_TABLE_NAME" (logaccdb_account_id)") ) ) )
        {
            return false;
        } 

        //自己的物品的clanid+index为唯一
        if ( !( *( driver->query("CREATE INDEX logacc_accname ON "LOGACCOUNT_TABLE_NAME" (logaccdb_name)") ) ) )
        {
            return false;
        }

        //自己的物品的clanid+index为唯一
        if ( !( *( driver->query("CREATE INDEX logacc_typettime ON "LOGACCOUNT_TABLE_NAME" (logaccdb_type, logaccdb_time)") ) ) )
        {
            return false;
        }

        return true;
    }
    //------------------------------------------------------------------------------------
    MG::Bool LogAccountDBOp::insertLogAccountDB( DBDriver* driver, PT_SYSLOG_ACCOUNT_OPERATE_DATA* data )
    {
        //插入
        Char8 sql[256] = {0};     

        //转换名字
        Str8 tempName;
        MGStrOp::toString(data->name, tempName);

        MGStrOp::sprintf(
            sql,
            256, 
            "insert into logaccountdb_info (logaccdb_account_id, logaccdb_type, logaccdb_name, logaccdb_time) \
            values('%I64d', '%d', '%s', '%I64d')",
            data->accountID, data->type, tempName.c_str(), data->time 
            );

        DBQueryResultEx resEx = driver->query(sql);
        DBQueryResult* dbRes = *resEx;
        if ( dbRes  &&  dbRes->getResultType() != DBQuery_Result_INVALID )
        {  
            return true;
        }

        return false;
    }
    //------------------------------------------------------------------------------------
    MG::Bool LogAccountDBOp::getLogAccountDB( DBDriver* driver, std::vector<PT_SYSLOG_ACCOUNT_OPERATE_DATA>* data, U64 accountID )
    {
        //查询
        Char8 sql[256] = {0};
        MGStrOp::sprintf(sql, 256, "select * from logaccountdb_info where logaccdb_account_id = '%I64d'", accountID);

        //填充
        DBQueryResultEx resEx = driver->query(sql);
        DBQueryResult* dbRes = *resEx;
        if ( dbRes  &&  dbRes->getResultType() != DBQuery_Result_INVALID )
        {  
            PT_SYSLOG_ACCOUNT_OPERATE_DATA tempData;
            U32 nCol = 1;
            I32 nRow = dbRes->getRowCount();
            Str8 tempStr;
            Str16 tempWStr;

            for ( I32 i=0; i<nRow; i++ )
            {
                memset(&tempData, 0, sizeof(PT_SYSLOG_ACCOUNT_OPERATE_DATA));
                nCol = 1;

                tempData.accountID  = dbRes->getFieldData( i, nCol++ )->ulonglongData;
                tempData.type       = (ACCOUNT_OPERATE_TYPE)( dbRes->getFieldData( i, nCol++ )->ubyteData );

                dbRes->getFieldData(i, nCol++, tempStr);
                MGStrOp::toString(tempStr.c_str(), tempWStr);
                wcscpy_s(tempData.name, MAX_ACCOUNT_LONGIN_NAME_LEN, tempWStr.c_str());

                tempData.time       = dbRes->getFieldData( i, nCol++ )->ulonglongData;

                data->push_back(tempData);
            }

            return true;
        }

        return false;
    }
    //------------------------------------------------------------------------------------
    MG::Bool LogAccountDBOp::getLogAccountDB( DBDriver* driver, std::vector<PT_SYSLOG_ACCOUNT_OPERATE_DATA>* data, Str16 accountName )
    {
        //查询
        Char8 sql[256] = {0};
		Str8 str8AccountName;
		MGStrOp::toString(accountName.c_str(),str8AccountName);

        MGStrOp::sprintf(sql, 256, "select * from logaccountdb_info where logaccdb_name = '%s'", str8AccountName.c_str());

        //填充
        DBQueryResultEx resEx = driver->query(sql);
        DBQueryResult* dbRes = *resEx;
        if ( dbRes  &&  dbRes->getResultType() != DBQuery_Result_INVALID )
        {  
            PT_SYSLOG_ACCOUNT_OPERATE_DATA tempData;
            U32 nCol = 1;
            I32 nRow = dbRes->getRowCount();
            Str8 tempStr;

            for ( I32 i=0; i<nRow; i++ )
            {
                memset(&tempData, 0, sizeof(PT_SYSLOG_ACCOUNT_OPERATE_DATA));
                nCol = 1;

                tempData.accountID  = dbRes->getFieldData( i, nCol++ )->ulonglongData;
                tempData.type       = (ACCOUNT_OPERATE_TYPE)( dbRes->getFieldData( i, nCol++ )->ubyteData );

                nCol++;
                wcscpy_s(tempData.name, MAX_ACCOUNT_LONGIN_NAME_LEN, accountName.c_str());

                tempData.time       = dbRes->getFieldData( i, nCol++ )->ulonglongData;

                data->push_back(tempData);
            }

            return true;
        }

        return false;
    }
	//------------------------------------------------------------------------------------
	MG::Bool LogAccountDBOp::getLogAccountDB(DBDriver *driver, std::vector<PT_SYSLOG_ACCOUNT_OPERATE_DATA> *data, U64 startTime, U64 endTime)
	{
        //查询
		Char8 sql[256] = {0};
		 

		MGStrOp::sprintf(sql,256,"select * from logaccountdb_info where logaccdb_time >= %I64d  and logaccdb_time <= %I64d",startTime,endTime);
        
		//填充
		DBQueryResultEx resEx = driver->query(sql);
		DBQueryResult* dbRes = *resEx;
		if ( dbRes  &&  dbRes->getResultType() != DBQuery_Result_INVALID )
		{  
			PT_SYSLOG_ACCOUNT_OPERATE_DATA tempData;
			U32 nCol = 1;
			I32 nRow = dbRes->getRowCount();
			Str8 tempStr;
			Str16 tempWStr;


			for ( I32 i=0; i<nRow; i++ )
			{
				memset(&tempData, 0, sizeof(PT_SYSLOG_ACCOUNT_OPERATE_DATA));
				nCol = 1;

				tempData.accountID  = dbRes->getFieldData( i, nCol++ )->ulonglongData;
				tempData.type       = (ACCOUNT_OPERATE_TYPE)( dbRes->getFieldData( i, nCol++ )->ubyteData );

				dbRes->getFieldData(i, nCol++, tempStr);
				MGStrOp::toString(tempStr.c_str(), tempWStr);
				wcscpy_s(tempData.name, MAX_ACCOUNT_LONGIN_NAME_LEN, tempWStr.c_str());

				tempData.time       = dbRes->getFieldData( i, nCol++ )->ulonglongData;

				data->push_back(tempData);
			}

			return true;
		}

		return false;
	}

	//------------------------------------------------------------------------------------
	MG::Bool LogAccountDBOp::getLogAccountDB(DBDriver *driver, std::vector<PT_SYSLOG_ACCOUNT_OPERATE_DATA> *data, Str16 accountName, U64 startTime, U64 endTime)
	{
		//查询
		Char8 sql[256] = {0};
		Str8 str8AccountName;
		MGStrOp::toString(accountName.c_str(),str8AccountName);
        MGStrOp::sprintf(sql, 256, "select * from logaccountdb_info where logaccdb_name = '%s' and (logaccdb_time between %I64d and %I64d) ", str8AccountName.c_str(),startTime,endTime);
		
		//填充
		DBQueryResultEx resEx = driver->query(sql);
		DBQueryResult* dbRes = *resEx;
		if ( dbRes  &&  dbRes->getResultType() != DBQuery_Result_INVALID )
		{  
			PT_SYSLOG_ACCOUNT_OPERATE_DATA tempData;
			U32 nCol = 1;
			I32 nRow = dbRes->getRowCount();
			Str8 tempStr;

			for ( I32 i=0; i<nRow; i++ )
			{
				memset(&tempData, 0, sizeof(PT_SYSLOG_ACCOUNT_OPERATE_DATA));
				nCol = 1;

				tempData.accountID  = dbRes->getFieldData( i, nCol++ )->ulonglongData;
				tempData.type       = (ACCOUNT_OPERATE_TYPE)( dbRes->getFieldData( i, nCol++ )->ubyteData );

				nCol++;
				wcscpy_s(tempData.name, MAX_ACCOUNT_LONGIN_NAME_LEN, accountName.c_str());

				tempData.time       = dbRes->getFieldData( i, nCol++ )->ulonglongData;

				data->push_back(tempData);
			}

			return true;
		}

		return false;
	}
}