/******************************************************************************/
#include "stdafx.h"
#include "ClanDataBase.h"
#include "MySqlDriver.h"
#include "DBQueryResult.h"
#include "DBDriver.h"
#include "CommonGameDBOp.h"
#include "ClanQuestObject.h"
#include "QuestList.h"
#include "PlayerItem.h"
/******************************************************************************/

namespace MG
{
    Bool ClanDataBaseDBOp::checkOrCreateClanDataBaseTable( DBDriver& driver )
    {
        static Colume clandatabaseColumn[] = 
        {
            {"clandb_account_id",       "BIGINT",               "0"},                                 //帐号ID
            {"clandb_maingenreal_id",   "BIGINT",               "0"},                                 //主武将
            {"clandb_map_id",           "INT",                  "0"},                                 //regionID
            {"clandb_map_type",         "TINYINT",              "0"},                                 //regionType
            {"clandb_status",           "TINYINT",              "0"},                                 //状态
            {"clandb_ancestry",         "TINYINT",              "0"},                                 //血统
            {"clandb_homeland_name",    "VARCHAR(1000)",        "0"},                                 //郡望
            {"clandb_name",             "VARCHAR(1000)",        "0"},                                 //名
            {"clandb_blem",             "TINYINT",              "0"},                                 //旗徽
            {"clandb_blem_color",       "TINYINT",              "0"},                                 //颜色
            {"clandb_bg",               "TINYINT",              "0"},                                 //背景
            {"clandb_bg_color",         "TINYINT",              "0"},                                 //背景颜色
            {"clandb_login_num",        "INT",                  "0"},                                 //登录次数
            {"clandb_clanbag_size",     "INT",                  "0"},                                 //氏族背包的大小
            {"clandb_quest_doing",     "VARCHAR(1000)",         "0"},                                 //氏族进行中任务记录
			{"clandb_quest_finished",   "VARCHAR(1000)",         "0"},                                 //氏族已完成任务记录
			{"clandb_bag_item",         "VARCHAR(10000)",        "0"},                                 //氏族背包物品

			{"clandb_money",			"INT",                  "0"}                                 //氏族游戏币
            /*{"clandb_create_time",      "DATETIME",           "0"},
            {"clandb_online_time",      "DATETIME",             "0"},
            {"clandb_delete_time",      "DATETIME",             "0"},
            {"clandb_login_time",       "DATETIME",             "0"},
            {"clandb_logout_time",      "DATETIME",             "0"}*/
        };

        DBQueryResultEx resEx = driver.query("CREATE TABLE IF NOT EXISTS clandatabase_info (clandb_id BIGINT NOT NULL AUTO_INCREMENT,PRIMARY KEY(clandb_id))");
        DBQueryResult* res1 = *resEx;
        if ( !res1 || res1->getResultType() == DBQuery_Result_INVALID  )
        {
            return false;
        }

        Bool  res2 = driver.addColume( CLANDATABASE_TABLE_NAME, clandatabaseColumn, sizeof(clandatabaseColumn)/sizeof(Colume) );
        if ( !res2 )
        {
            return false;
        }
        //玩家的accountid,一个玩家可拥有多个氏族，即非唯一
        if ( !( *( driver.query("CREATE INDEX accountid ON clandatabase_info (clandb_account_id)") ) ) )
        {
            return false;
        }                                    
        //武将的id是唯一的，武将被氏族拥有，故在这一列中只能出现一次。
        if ( !( *( driver.query("CREATE INDEX maingenrealid ON clandatabase_info (clandb_maingenreal_id)") ) ) )
        {
            return false;
        }

        return true;
    }
    //------------------------------------------------------------------------------------
	Bool ClanDataBaseDBOp::getClanDataBase( DBDriver& driver, const U64& accountId, std::vector<ClanData>& nameList,std::vector<dbDoingClanQuestObject>& doingQuestData,
		std::vector<FinishedClanQuestObject>& finishedQuestData,std::vector<ItemRecord>& recordList )
    {
        ClanData data;

        Char8 sql[128] = {0};
        MGStrOp::sprintf(sql,128,"select * from "CLANDATABASE_TABLE_NAME" where clandb_account_id = %I64d",accountId);

        DBQueryResultEx resEx = driver.query(sql);
        DBQueryResult* res = *resEx;
        if ( res  &&  res->getResultType() != DBQuery_Result_INVALID  &&  res->getRowCount() > 0 )
        {
            Str16 wName;
			Str16 questDoingRecordString;
			Str16 questFinishedRecordString;
            Str   tempStr;
            
			//clanItemDB
			Str8 dbClanItemRecordString;
            //U8 nY,nM,nD,nH,nMi,nS;
            I32 nRow = res->getRowCount();
            for ( I32 i=0; i<nRow; i++ )
            {
                memset(&data, 0, sizeof(data));
                U32 nCol = 0;

                data.clanId             = res->getFieldData( i, nCol++ )->ulonglongData;
                data.accountId          = res->getFieldData( i, nCol++ )->ulonglongData;
                data.mainGenrealId      = res->getFieldData( i, nCol++ )->ulonglongData;
                data.regionID           = res->getFieldData( i, nCol++ )->ulonglongData;
                data.regionType         = (REGION_OBJ_TYPE)res->getFieldData( i, nCol++ )->ubyteData;
                data.status             = (CLAN_STATUS_TYPE)res->getFieldData( i, nCol++ )->ubyteData;
                data.ConstellationId    = res->getFieldData( i, nCol++ )->ubyteData;
             
                res->getFieldData(i, nCol++, tempStr);
                MGStrOp::toString(tempStr.c_str(), wName);
                data.clanHomeLandName   = wName;
                res->getFieldData(i, nCol++, tempStr);
                MGStrOp::toString(tempStr.c_str(), wName);
                data.clanName           = wName;
                data.armyemblem         = res->getFieldData( i, nCol++ )->ubyteData;
                data.armyemblemcolor    = res->getFieldData( i, nCol++ )->ubyteData;
                data.bg                 = res->getFieldData( i, nCol++ )->ubyteData;
                data.bgcolor            = res->getFieldData( i, nCol++ )->ubyteData;
                data.loginnum           = res->getFieldData( i, nCol++ )->uintData;
                data.clanbagSize        = res->getFieldData( i, nCol++ )->uintData;
				res->getFieldData(i, nCol++, tempStr);
                MGStrOp::toString(tempStr.c_str(), questDoingRecordString);
				res->getFieldData(i, nCol++, tempStr);
                MGStrOp::toString(tempStr.c_str(), questFinishedRecordString);
                
				res->getFieldData(i, nCol++, dbClanItemRecordString);
				//data.clanGameMoney = res->getFieldData(i, nCol++)->uintData;
                /*res->getFieldData(i, nCol++, tempStr);
                sscanf_s(tempStr.c_str(),"%d-%d-%d %d:%d:%d",&nY,&nM,&nD,&nH,&nMi,&nS);
                data.createtime  = MGTimeOp::createtimestamp(nY,nM,nD,nH,nMi,nS);
                res->getFieldData(i, nCol++, tempStr);
                sscanf_s(tempStr.c_str(),"%d-%d-%d %d:%d:%d",&nY,&nM,&nD,&nH,&nMi,&nS);
                data.onlinetime  = MGTimeOp::createtimestamp(nY,nM,nD,nH,nMi,nS);
                res->getFieldData(i, nCol++, tempStr);
                sscanf_s(tempStr.c_str(),"%d-%d-%d %d:%d:%d",&nY,&nM,&nD,&nH,&nMi,&nS);
                data.deletetime  = MGTimeOp::createtimestamp(nY,nM,nD,nH,nMi,nS);
                res->getFieldData(i, nCol++, tempStr);
                sscanf_s(tempStr.c_str(),"%d-%d-%d %d:%d:%d",&nY,&nM,&nD,&nH,&nMi,&nS);
                data.logintime  = MGTimeOp::createtimestamp(nY,nM,nD,nH,nMi,nS);
                res->getFieldData(i, nCol++, tempStr);
                sscanf_s(tempStr.c_str(),"%d-%d-%d %d:%d:%d",&nY,&nM,&nD,&nH,&nMi,&nS);
                data.logouttime  = MGTimeOp::createtimestamp(nY,nM,nD,nH,nMi,nS);*/
                nameList.push_back(data);

				//现在一个玩家只有一个氏族,对应唯一条任务记录,有多个需求需要修改
				if ( nRow >= 2 )
				{
					DYNAMIC_ASSERT(0);
				}
          		
				//加载任务信息
                loadQuest(questDoingRecordString,questFinishedRecordString,doingQuestData,finishedQuestData);
				
				//加载氏族背包物品信息
                loadClanItem(dbClanItemRecordString,recordList);
				
            }
            return true;
        }

        return false;
    }
    //------------------------------------------------------------------------------------
    Bool ClanDataBaseDBOp::insertClanDataBase( DBDriver& driver, U64& clandatabaseid )
    {
        //插入
        Char8 sql[1024] = {0};
        MGStrOp::sprintf(
                            sql,
                            1024, 
                            "insert into clandatabase_info () values()" 
                         );
                    
        Bool result = false; 
        driver.queryLock();
        {

            DBQueryResultEx resEx = driver.query( sql, false );
            DBQueryResult* dbRes = *resEx;
            if ( dbRes  &&  dbRes->getResultType() != DBQuery_Result_INVALID )
            {  
                result = true;
                clandatabaseid = CommonGameDBOp::getLastInsertID( driver, false );
            }
        }
        driver.queryUnLock();
        return result;
    }
    //------------------------------------------------------------------------------------
    MG::Bool ClanDataBaseDBOp::updateClanDataBase( DBDriver& driver, const ClanData* cbDBdata, const U64& clandatabaseid )
    {
        //插入
        Char8 sql[1024] = {0};
        Str8 templandname, tempname;
        MGStrOp::toString( cbDBdata->clanHomeLandName.c_str(), templandname );
        MGStrOp::toString( cbDBdata->clanName.c_str(), tempname );
        MGStrOp::sprintf(
            sql,
            1024, 
            "update clandatabase_info set\
            clandb_account_id = %I64d, clandb_maingenreal_id = %I64d, clandb_map_id = %d, clandb_map_type = %d, clandb_status = %d, \
            clandb_ancestry = %d, clandb_homeland_name = '%s', clandb_name = '%s', clandb_blem = %d, clandb_blem_color = %d, \
            clandb_bg = %d, clandb_bg_color = %d, clandb_login_num = %d, clandb_clanbag_size = %d, clandb_quest_doing = '', \
			clandb_quest_finished = '',clandb_bag_item='', clandb_money = %I32d \
            where clandb_id = %I64d" 
            ,cbDBdata->accountId, cbDBdata->mainGenrealId, cbDBdata->regionID, cbDBdata->regionType, cbDBdata->status 
            ,cbDBdata->ConstellationId, templandname.c_str(), tempname.c_str(), cbDBdata->armyemblem, cbDBdata->armyemblemcolor
            ,cbDBdata->bg, cbDBdata->bgcolor, cbDBdata->loginnum, cbDBdata->clanbagSize, 0, cbDBdata->clanId
            );
		MG_LOG(out_game_logic,"updateClanDataBase accountid = %I64d\n",cbDBdata->accountId);
        DBQueryResultEx resEx = driver.query( sql, false );
        DBQueryResult* dbRes = *resEx;
        if ( dbRes  &&  dbRes->getResultType() != DBQuery_Result_INVALID )
        {  
            return true;
        }
        return false;
    }
    //------------------------------------------------------------------------------------
    Bool ClanDataBaseDBOp::updateClanDataBaseStatus( DBDriver& driver, const U64& clandatabaseid, const U8& status )
    {
        return false;
    }
    //------------------------------------------------------------------------------------
    Bool ClanDataBaseDBOp::deleteClanDataBase( DBDriver& driver, const U64& clandatabaseid )
    {
		Char8 sql[128] = {0};
		MGStrOp::sprintf(
			                sql,
							128,
							"delete from clandatabase_info where clandb_id = %I64d",
                            clandatabaseid
			            );
	    DBQueryResultEx resEx = driver.query( sql, false );
		DBQueryResult* dbRes = *resEx;
		if ( dbRes  &&  dbRes->getResultType() != DBQuery_Result_INVALID )
		{  
			return true;
		}
        return false;
    }
    //------------------------------------------------------------------------------------
    Bool ClanDataBaseDBOp::updateClanDataBaseMainGenreal( DBDriver& driver, const U64& clandatabaseid, const U64& mainGenrealId )
    {
        Char8 sql[128] = {0};
        MGStrOp::sprintf(
                            sql,
                            128, 
                            "update clandatabase_info set clandb_maingenreal_id = %I64d where clandb_id = %I64d",
                            mainGenrealId,
                            clandatabaseid
                        );
        DBQueryResultEx resEx = driver.query( sql, false );
        DBQueryResult* dbRes = *resEx;
        if ( dbRes  &&  dbRes->getResultType() != DBQuery_Result_INVALID )
        {  
            return true;
        }
        return false;
    }
	//------------------------------------------------------------------------------------
	MG::Bool ClanDataBaseDBOp::updateClanDataBaseMoney( DBDriver& driver, const U64& clandatabaseid, const UInt& money )
	{
		Char8 sql[128] = {0};
		MGStrOp::sprintf(
			sql,
			128, 
			"update clandatabase_info set clandb_money = %d where clandb_id = %I64d",
			money,
			clandatabaseid
			);
		DBQueryResultEx resEx = driver.query( sql, false );
		DBQueryResult* dbRes = *resEx;
		if ( dbRes  &&  dbRes->getResultType() != DBQuery_Result_INVALID )
		{  
			return true;
		}
		return false;
	}
	//------------------------------------------------------------------------------------
	void ClanDataBaseDBOp::loadQuest(const Str16& dbQuestDoingRecordString,const Str16& dbQuestFinishedRecordString,std::vector<dbDoingClanQuestObject>& doingQuestData,
		                 std::vector<FinishedClanQuestObject>& finishedQuestData  )
	{
		
		//doingrecorddoing格式
		//questID.completestate.begintime.endtime.value1.value2.value3.value4,
		//uestID.completestate.begintime.endtime.value1.value2.value3.value4,...
		//
        
		//doing quest data
		std::vector<std::vector<Str16>> questDoingRecords;
		std::vector<Str16>              tempDoingRecords;  
		std::vector<Str16>              tempFinishedRecords;
		MGStrOp::split<Str16>(dbQuestDoingRecordString,DB_RECORDS_SEPARATOR,tempDoingRecords);
		if (tempDoingRecords.size() >0 && 
			dbQuestDoingRecordString.length() > 0 && dbQuestDoingRecordString[0] != L'\0')
		{   
			//对应记录中字段
			I32 questId =0;
			I32 completeState = 0;
			U64 beginTime = 0;
			U64 endTime = 0;
			I32 value1 = 0;
			I32 value2 = 0;
			I32 value3 = 0;
			I32 value4 = 0;
			dbDoingClanQuestObject questObj;

			std::vector<Str16>::iterator front = tempDoingRecords.begin();
			for (; front != tempDoingRecords.end();front++)
			{
				 std::vector<Str16> FieldsInRecord;
                 MGStrOp::split<Str16>((*front),DB_FIELDS_SEPARATOR,FieldsInRecord);
				 MGStrOp::toI32(FieldsInRecord[0].c_str(),questId);
				 questObj.questInfoId = questId;
				 MGStrOp::toI32(FieldsInRecord[1].c_str(),completeState);
				 questObj.mRecord.state = (QUEST_COMPLETE_STATE)completeState;
				 MGStrOp::toU64(FieldsInRecord[2].c_str(),beginTime);
				 questObj.mRecord.beginTime = beginTime;
				 MGStrOp::toU64(FieldsInRecord[3].c_str(),endTime);
				 questObj.mRecord.endTime = endTime;
				 MGStrOp::toI32(FieldsInRecord[4].c_str(),value1);
				 questObj.mRecord.value[0] = value1;
				 MGStrOp::toI32(FieldsInRecord[5].c_str(),value2);
				 questObj.mRecord.value[1] = value2;
				 MGStrOp::toI32(FieldsInRecord[6].c_str(),value3);
				 questObj.mRecord.value[2] = value3;
				 MGStrOp::toI32(FieldsInRecord[7].c_str(),value4);
				 questObj.mRecord.value[3] = value4; 
 
				 //
				 doingQuestData.push_back(questObj);

			}

		}
        
        //finished quest data
        MGStrOp::split<Str16>(dbQuestFinishedRecordString,DB_RECORDS_SEPARATOR,tempFinishedRecords);
		if (tempFinishedRecords.size() >0 
			&& dbQuestFinishedRecordString.length() >0
			&& dbQuestFinishedRecordString[0] != L'\0')
		{
			//对应记录中字段
			I32 questId = 0;
            U32 endTime = 0;
			FinishedClanQuestObject questObj;
			std::vector<Str16>::iterator front = tempFinishedRecords.begin();
			for (; front != tempFinishedRecords.end();front++)
			{
				std::vector<Str16> FieldsInRecord;
				MGStrOp::split<Str16>((*front),DB_FIELDS_SEPARATOR,FieldsInRecord);
				MGStrOp::toI32(FieldsInRecord[0].c_str(),questId);
				questObj.questInfoId = questId;
				MGStrOp::toU32(FieldsInRecord[1].c_str(),endTime);
				questObj.endTime = endTime;
				
				//
				finishedQuestData.push_back(questObj);

			}
		}

	}

	//------------------------------------------------------------------------------------
	MG::Bool ClanDataBaseDBOp::updateQuest( DBDriver& driver,const U64 clandatabaseid,std::map< U32 , ClanQuestObject*>* doingQuestData,
		std::map<U32,FinishedClanQuestObject*>* finishedQuestData)
	{
          Str8 dbQuestDoingRecordString;
		  Str8 dbQuestFinishedRecordString;
		  Str16 tempFinishedRecords;
		  Str16 tempDoingRecords;

          if (doingQuestData->size() >0 )
          {
				  //对应记录中字段
				  Str16 questId;
				  Str16 completeState;
				  Str16 beginTime;
				  Str16 endTime;
				  Str16 value1;
				  Str16 value2;
				  Str16 value3;
				  Str16 value4;
				  //
                 Str16 tempFields;
                 U32  countFlag = 0;
				 std::map< U32 , ClanQuestObject*>::iterator  doingQuestIt = doingQuestData->begin();
				 while(doingQuestIt != doingQuestData->end())
				 {
					 countFlag++;
					 MGStrOp::toString((doingQuestIt->second)->mInfo->id,questId);
					 MGStrOp::toString(I32(doingQuestIt->second->mRecord.state),completeState);
					 MGStrOp::toString(doingQuestIt->second->mRecord.beginTime,beginTime);
					 MGStrOp::toString(doingQuestIt->second->mRecord.endTime,endTime);
					 MGStrOp::toString(doingQuestIt->second->mRecord.value[0],value1);
					 MGStrOp::toString(doingQuestIt->second->mRecord.value[1],value2);
					 MGStrOp::toString(doingQuestIt->second->mRecord.value[2],value3);
					 MGStrOp::toString(doingQuestIt->second->mRecord.value[3],value4);
                     tempFields = questId + L"."+completeState + L"."+beginTime + L"."+endTime + L"."+value1 + L"."+value2 + L"."+value3 + L"."+value4;
                     if(countFlag == doingQuestData->size())
					 {
						 tempDoingRecords += tempFields;
					 }
					 else
					 { 
                       tempDoingRecords += tempFields + L",";
					 }

					 doingQuestIt++;
					 
				 }

          }

		  //finished quest
          if (finishedQuestData->size() >0 )
          {
                 Str16 questInfoId;
				 Str16 endTime;
				 Str16 tempFields;
				 U32   countFlag = 0;
				 std::map<U32,FinishedClanQuestObject*>::iterator  finishedQuestIt = finishedQuestData->begin();
				 while (finishedQuestIt != finishedQuestData->end())
				 {
					 countFlag++;
                     MGStrOp::toString(finishedQuestIt->second->questInfoId,questInfoId);
					 MGStrOp::toString(finishedQuestIt->second->endTime,endTime);
					 tempFields = questInfoId + L"." + endTime;
					 if (countFlag == finishedQuestData->size())
					 {
							tempFinishedRecords += tempFields;
					 }
					 else
					 {
						 tempFinishedRecords += tempFields + L"," ;
					 }
					finishedQuestIt++;

				 }
          }

		  MGStrOp::toString(tempDoingRecords.c_str(),dbQuestDoingRecordString);
          MGStrOp::toString(tempFinishedRecords.c_str(),dbQuestFinishedRecordString);
          //
		  Char8 sql[1024] = {0};
		  MGStrOp::sprintf(
			  sql,
			  1024, 
			  "update clandatabase_info set \
			  clandb_quest_doing = '%s', clandb_quest_finished = '%s' \
			  where clandb_id = %I64d" 
			  ,dbQuestDoingRecordString.c_str(),dbQuestFinishedRecordString.c_str(),clandatabaseid
			  );

		  DBQueryResultEx resEx = driver.query( sql, false );
		  DBQueryResult* dbRes = *resEx;
		  if ( dbRes  &&  dbRes->getResultType() != DBQuery_Result_INVALID )
		  {  
			  return true;
		  }
		  return false;


	}
	//------------------------------------------------------------------------------------
	void ClanDataBaseDBOp::loadClanItem( const Str8 dbClanItemRecordString,std::vector<ItemRecord>& recordList )
	{
        //
        std::vector<Str8> tempClanItemRecords;
        MGStrOp::split<Str8>(dbClanItemRecordString,DB_RECORDS_SEPARATOR,tempClanItemRecords);
		if (tempClanItemRecords.size() >0 && 
			dbClanItemRecordString.length() > 0 && dbClanItemRecordString[0] != L'\0')
		{
             //对应数据库中的字段
			IdType              itemDBID            = 0;
			U32                 itemTempID          = 0;
			/*ITEM_BELONG_TYPE*/I32    itemBelongType      = 0;
			IdType              itemBelongID        = 0;  //物品绑定角色或氏族的
			/*ITEM_SITE_TYPE*/I32      belongPos           = 0;      //物品当前所在格位
			/*ITEM_BIND_TYPE*/I32      bindType            = 0;
			U32                 slotIndex               = 0;
			Char16              fatherName[MAX_CHARACTER_NAME_LEN] = {0};
			U32                 curNum              = 0;
			U32                 curDurable          = 0;
			U32                 curRepairNum        = 0;
			U32                 curStrengthenLv     = 0;
			U32                 randAppendID        = 0;
			U32                 strengthenAppendID  = 0;
			U64                 dueTime             = 0;
			U64                 bornTime            = 0;
			U64                 delTime             = 0;
			U64                 updateTime          = 0;
			//
			
			ItemRecord  itemRecordObject;
			std::vector<Str8>::iterator front = tempClanItemRecords.begin();
			std::vector<Str8>::iterator back = tempClanItemRecords.end();
			while(front != back)
			{
                 std::vector<Str8> FieldsInRecord;
				  MGStrOp::split<Str8>((*front),DB_FIELDS_SEPARATOR,FieldsInRecord);
				  MGStrOp::toU64(FieldsInRecord[0].c_str(),itemDBID);
				  itemRecordObject.itemDBID = itemDBID;
				  MGStrOp::toU32(FieldsInRecord[1].c_str(),itemTempID);
                  itemRecordObject.itemTempID = itemTempID;
				  MGStrOp::toI32(FieldsInRecord[2].c_str(),itemBelongType);
				  itemRecordObject.itemBelongType = (ITEM_BELONG_TYPE)itemBelongType;
				  MGStrOp::toU64(FieldsInRecord[3].c_str(),itemBelongID);
				  itemRecordObject.itemBelongID = itemBelongID;
				  MGStrOp::toI32(FieldsInRecord[4].c_str(),belongPos);
				  itemRecordObject.belongPos = (ITEM_SITE_TYPE)belongPos;
				  MGStrOp::toI32(FieldsInRecord[5].c_str(),bindType);
				  itemRecordObject.bindType = (ITEM_BIND_TYPE)bindType;
				  MGStrOp::toU32(FieldsInRecord[6].c_str(),slotIndex);
				  itemRecordObject.slotIndex = slotIndex;
				  //
				  Str16 tempName;
				  MGStrOp::toString(FieldsInRecord[7].c_str(),tempName);
				  memcpy(itemRecordObject.fatherName,tempName.c_str(), sizeof(MAX_CHARACTER_NAME_LEN));
				  MGStrOp::toU32(FieldsInRecord[8].c_str(),curNum);
				  itemRecordObject.curNum = curNum;
				  MGStrOp::toU32(FieldsInRecord[9].c_str(),curDurable);
				  itemRecordObject.curDurable = curDurable;
				  MGStrOp::toU32(FieldsInRecord[10].c_str(),curRepairNum);
				  itemRecordObject.curRepairNum = curRepairNum;
				  MGStrOp::toU32(FieldsInRecord[11].c_str(),curStrengthenLv);
				  itemRecordObject.curStrengthenLv = curStrengthenLv;
				  MGStrOp::toU32(FieldsInRecord[12].c_str(),randAppendID);
				  itemRecordObject.randAppendID = randAppendID;
				  MGStrOp::toU32(FieldsInRecord[13].c_str(),strengthenAppendID);
				  itemRecordObject.strengthenAppendID = strengthenAppendID;
				  MGStrOp::toU64(FieldsInRecord[14].c_str(),dueTime);
				  itemRecordObject.delTime = dueTime;
				  MGStrOp::toU64(FieldsInRecord[15].c_str(),bornTime);
				  itemRecordObject.bornTime = bornTime;
				  MGStrOp::toU64(FieldsInRecord[16].c_str(),delTime);
				  itemRecordObject.delTime = delTime;
				  MGStrOp::toU64(FieldsInRecord[17].c_str(),updateTime);
				  itemRecordObject.updateTime = updateTime;

				  recordList.push_back(itemRecordObject);
                  front++;
			}

		}

	}
	//------------------------------------------------------------------------------------
	MG::Bool ClanDataBaseDBOp::updateClanItem( DBDriver& driver,const U64 clandatabaseid,std::vector<PlayerItem*>* clanItemList )
	{
          Str8 dbClanItemRecordString;
          if (clanItemList->size() > 0)
          {
			  //对应数据库中的字段
			  Str8                 itemDBID;
			  Str8                 itemTempID;
			  /*ITEM_BELONG_TYPE*/Str8    itemBelongType;
			  Str8              itemBelongID;  //物品绑定角色或氏族的
			  /*ITEM_SITE_TYPE*/Str8      belongPos;      //物品当前所在格位
			  /*ITEM_BIND_TYPE*/Str8      bindType;
			  Str8                 slotIndex;
			  Str8              fatherName;
			  Str8                 curNum;
			  Str8                 curDurable;
			  Str8                 curRepairNum;
			  Str8                 curStrengthenLv;
			  Str8                 randAppendID;
			  Str8                 strengthenAppendID;
			  Str8                 dueTime;
			  Str8                 bornTime;
			  Str8                 delTime;
			  Str8                 updateTime;
			
			  //
			  Str8 tempFields;
			  U32  countFlag = 0;
			  std::vector<PlayerItem*>::iterator front = clanItemList->begin();
			  std::vector<PlayerItem*>::iterator back = clanItemList->end();
			  while ( front!= back)
			  {
				  countFlag++;
				  MGStrOp::toString((*front)->getItemRecord()->itemDBID,itemDBID);
				  MGStrOp::toString((*front)->getItemRecord()->itemTempID,itemTempID);
				  MGStrOp::toString((I32)(*front)->getItemRecord()->itemBelongType,itemBelongType);
				  MGStrOp::toString((*front)->getItemRecord()->itemBelongID,itemBelongID);
				  MGStrOp::toString((I32)(*front)->getItemRecord()->belongPos,belongPos);
				  MGStrOp::toString((I32)(*front)->getItemRecord()->bindType,bindType);
				  MGStrOp::toString((*front)->getItemRecord()->slotIndex,slotIndex);
				  MGStrOp::toString(((Str16)(*front)->getItemRecord()->fatherName).c_str(),fatherName);
				  MGStrOp::toString((*front)->getItemRecord()->curNum,curNum);
				  MGStrOp::toString((*front)->getItemRecord()->curDurable,curDurable);
				  MGStrOp::toString((*front)->getItemRecord()->curRepairNum,curRepairNum);
				  MGStrOp::toString((*front)->getItemRecord()->curStrengthenLv,curStrengthenLv);
				  MGStrOp::toString((*front)->getItemRecord()->randAppendID,randAppendID);
				  MGStrOp::toString((*front)->getItemRecord()->dueTime,dueTime);
				  MGStrOp::toString((*front)->getItemRecord()->bornTime,bornTime);
				  MGStrOp::toString((*front)->getItemRecord()->delTime,delTime);
				  MGStrOp::toString((*front)->getItemRecord()->updateTime,updateTime);
                  tempFields = itemDBID + "." + itemTempID + "." + itemBelongType + "." + itemBelongID + "." + belongPos + "." + bindType + "." + slotIndex + "." 
					     + fatherName + "." + curNum + "." + curDurable + "." + curRepairNum + "." + curStrengthenLv + "." + randAppendID + "." + strengthenAppendID 
						 + "." + dueTime + "." + bornTime + "." + delTime + "." + updateTime;
				  if (countFlag == clanItemList->size())
				  {
                         dbClanItemRecordString += tempFields;
				  }
				  else
				  {
						dbClanItemRecordString += tempFields + ",";
				  }

				  front++;
			  }
          }
		  //
		  Char8 sql[2048] = {0};
		  MGStrOp::sprintf(
			  sql,
			  2048, 
			  "update clandatabase_info set \
			  clandb_bag_item = '%s' where clandb_id = %I64d" 
			  ,dbClanItemRecordString.c_str(),clandatabaseid
			  );
		  DBQueryResultEx resEx = driver.query( sql, false );
		  DBQueryResult* dbRes = *resEx;
		  if ( dbRes  &&  dbRes->getResultType() != DBQuery_Result_INVALID )
		  {  
			  return true;
		  }
		  return false;
	}
}