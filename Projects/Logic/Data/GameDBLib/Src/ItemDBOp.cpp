//**********************************************************************************************************
#include "stdafx.h"
#include "ItemDBOp.h"
#include "MySqlDriver.h"
#include "DBQueryResult.h"
#include "DBDriver.h"
#include "CommonGameDBOp.h"
//**********************************************************************************************************
namespace MG
{
    MG::Bool ItemDBOp::checkOrCreateItemDBTable( DBDriver& driver )
    {
        static Colume itemDBColumn[] = 
        {
            {"itemdb_character_id",             "BIGINT",               "0"},                                 //��ɫID�������ɫ����ʹ�ã�
            {"itemdb_temp_id",                  "INT",                  "0"},                                 //ģ��ID
            {"itemdb_belong_id",                "BIGINT",               "0"},                                 //�������͵�ID
            {"itemdb_belong_type",              "TINYINT",              "0"},                                 //��������
            {"itemdb_belong_pos",               "TINYINT",              "0"},                                 //���õĽ���
            {"itemdb_index",                    "INT",                  "0"},                                 //�ŵڼ���
            {"itemdb_father_name",              "VARCHAR(50)",          "0"},                                 //������
            {"itemdb_bind_type",                "TINYINT",              "0"},                                 //������
            {"itemdb_curnum",                   "INT",                  "0"},                                 //�ص���
            {"itemdb_curdurable",               "INT",                  "0"},                                 //��ǰ�;ö�
            {"itemdb_currepairnum",             "INT",                  "0"},                                 //��ǰ�������
            {"itemdb_curstrengthenlv",          "INT",                  "0"},                                 //ǿ���ȼ�
            {"itemdb_rand_appendid",            "INT",                  "0"},                                 //�����������ID
            {"itemdb_strengthen_appendid",      "INT",                  "0"},                                 //ǿ������ID
            {"itemdb_due_time",                 "BIGINT",               "0"},                                 //����ʱ�䣨ʱ��Σ�
            {"itemdb_born_time",                "DATETIME",             "0"},                                 //����ʱ��
            {"itemdb_del_time",                 "DATETIME",             "0"},                                 //ɾ��ʱ��
            {"itemdb_update_time",              "DATETIME",             "0"}                                  //���ʱ��
        };

        DBQueryResultEx resEx = driver.query("CREATE TABLE IF NOT EXISTS itemdb_info (item_id BIGINT NOT NULL AUTO_INCREMENT,PRIMARY KEY(item_id))");
        DBQueryResult* res1 =  *resEx;
        if ( !res1 || res1->getResultType() == DBQuery_Result_INVALID  )
        {
            return false;
        }

        Bool  res2 = driver.addColume( ITEMDB_TABLE_NAME, itemDBColumn, sizeof(itemDBColumn)/sizeof(Colume) );
        if ( !res2 )
        {
            return false;
        }

        //�Լ�����Ʒ��clanid+indexΪΨһ
        if ( !( *( driver.query("CREATE INDEX itemdbbelongidtype ON itemdb_info (itemdb_belong_id, itemdb_belong_type)") ) ) )
        {
            return false;
        }

        return true;
    }
    //-------------------------------------------------------------------------------------------
    MG::Bool ItemDBOp::getItemDB( DBDriver& driver, const U64& clanID, const ITEM_BELONG_TYPE& type, std::vector<ItemRecord>& recordList )
    {
        ItemRecord data;

        Char8 sql[128] = {0};
        MGStrOp::sprintf(sql,128,"select * from "ITEMDB_TABLE_NAME" where itemdb_belong_id = %I64d and itemdb_belong_type = %d",clanID, type);

        DBQueryResultEx resEx = driver.query(sql);
        DBQueryResult* res = *resEx;
        if ( res  &&  res->getResultType() != DBQuery_Result_INVALID  &&  res->getRowCount() > 0 )
        {
            Str16 wName;
            Str   tempStr;

            I32 nRow = res->getRowCount();
            for ( I32 i=0; i<nRow; i++ )
            {
                memset(&data, 0, sizeof(data));
                U32 nCol = 0;
                
                
               // data.itemDBID                    = res->getFieldData( i, nCol++ )->ulonglongData;
                data.characterId                 = res->getFieldData( i, nCol++ )->ulonglongData;
                data.itemTempID                  = res->getFieldData( i, nCol++ )->uintData;
                data.itemBelongID                = res->getFieldData( i, nCol++ )->ulonglongData;
                data.itemBelongType              = (ITEM_BELONG_TYPE)( res->getFieldData( i, nCol++ )->ubyteData );
                data.belongPos                   = (ITEM_SITE_TYPE)( res->getFieldData( i, nCol++ )->ubyteData );
                data.slotIndex                       = res->getFieldData( i, nCol++ )->uintData;
                res->getFieldData(i, nCol++, tempStr);
                MGStrOp::toString(tempStr.c_str(), wName);
                memcpy(data.fatherName, wName.c_str(), sizeof(MAX_CHARACTER_NAME_LEN));
                data.bindType                    = (ITEM_BIND_TYPE)( res->getFieldData( i, nCol++ )->ubyteData );
                data.curNum                      = res->getFieldData( i, nCol++ )->uintData;
                data.curDurable                  = res->getFieldData( i, nCol++ )->uintData;
                data.curRepairNum                = res->getFieldData( i, nCol++ )->uintData;
                data.curStrengthenLv             = res->getFieldData( i, nCol++ )->uintData;
                data.randAppendID                = res->getFieldData( i, nCol++ )->uintData;
                data.strengthenAppendID          = res->getFieldData( i, nCol++ )->uintData;
                //ʱ��
                /*data.dueTime                     = res->getFieldData( i, nCol++ )->ulonglongData;
                data.bornTime                    = res->getFieldData( i, nCol++ )->ulonglongData;
                data.delTime                     = res->getFieldData( i, nCol++ )->ulonglongData;
                data.updateTime                  = res->getFieldData( i, nCol++ )->ulonglongData;*/
                

                recordList.push_back(data);
            }
            return true;
        }

        return false;
    }
    //-------------------------------------------------------------------------------------------
    MG::Bool ItemDBOp::insertItemDB( DBDriver& driver, U64& itemDBID )
    {
        //����
        Char8 sql[128] = {0};     

        MGStrOp::sprintf(
                        sql,
                        128, 
                        "insert into itemdb_info ()  values()" 
        );

        Bool result = false; 
        driver.queryLock();
        {
            DBQueryResultEx resEx = driver.query(sql);
            DBQueryResult* dbRes = *resEx;
            if ( dbRes  &&  dbRes->getResultType() != DBQuery_Result_INVALID )
            {  
                result = true;
                itemDBID = CommonGameDBOp::getLastInsertID( driver, false );
            }
        }
        driver.queryUnLock();
        return result;
    }
    //-------------------------------------------------------------------------------------------
    MG::Bool ItemDBOp::updateItemDBPos( DBDriver& driver, const U64& itemDBID, const U8 belongPos )
    {
        Char8 sql[128] = {0};
        MGStrOp::sprintf(
            sql,
            128, 
            "update itemdb_info set itemdb_belong_pos = %d where item_id = %I64d",
            belongPos,
            itemDBID
            );

        DBQueryResultEx resEx = driver.query( sql, false );
        DBQueryResult* dbRes = *resEx;
        if ( dbRes  &&  dbRes->getResultType() != DBQuery_Result_INVALID )
        {  
            return true;
        }
        return false;
    }
    //-------------------------------------------------------------------------------------------
    MG::Bool ItemDBOp::updateItemDBNum( DBDriver& driver, const U64& itemDBID, const U8 num )
    {
        Char8 sql[128] = {0};
        MGStrOp::sprintf(
            sql,
            128, 
            "update itemdb_info set itemdb_curnum = %d where item_id = %I64d",
            num,
            itemDBID
            );

        DBQueryResultEx resEx = driver.query( sql, false );
        DBQueryResult* dbRes = *resEx;
        if ( dbRes  &&  dbRes->getResultType() != DBQuery_Result_INVALID )
        {  
            return true;
        }
        return false;
    }
    //-------------------------------------------------------------------------------------------
    MG::Bool ItemDBOp::updateItemDBInfo( DBDriver& driver, const U64& itemDBID, const ItemRecord* itemDBdata )
    {
        Char8 sql[1028] = {0};
        Str8 tempfathername;
        MGStrOp::toString( itemDBdata->fatherName, tempfathername ); 

        MGStrOp::sprintf(
            sql,
            1028, 
            "update itemdb_info set \
            itemdb_belong_id = %I64d, itemdb_belong_type = %d, itemdb_belong_pos = %d, itemdb_index = %d \
            , itemdb_father_name = '%s', itemdb_bind_type = %d, itemdb_curnum = %d, itemdb_curdurable = %d, itemdb_currepairnum = %d \
            , itemdb_curstrengthenlv = %d, itemdb_rand_appendid = %d, itemdb_strengthen_appendid = %d, itemdb_due_time = %I64d \
            , itemdb_character_id = %I64d   where item_id = %I64d",
            itemDBdata->itemBelongID, itemDBdata->itemBelongType, itemDBdata->belongPos, itemDBdata->slotIndex
            , tempfathername.c_str(), itemDBdata->bindType, itemDBdata->curNum, itemDBdata->curDurable, itemDBdata->curRepairNum
            , itemDBdata->curStrengthenLv, itemDBdata->randAppendID, itemDBdata->strengthenAppendID, itemDBdata->dueTime 
            , itemDBdata->characterId
            , itemDBID
            );

        DBQueryResultEx resEx = driver.query( sql, false );
        DBQueryResult* dbRes = *resEx;
        if ( dbRes  &&  dbRes->getResultType() != DBQuery_Result_INVALID )
        {  
            return true;
        }
        return false;
    }
    //-------------------------------------------------------------------------------------------
    MG::Bool ItemDBOp::updateItemDBIndex(DBDriver& driver, const U64& itemDBID, const U32& Index, const U8& belongPos)
    {
        Char8 sql[128] = {0};
        MGStrOp::sprintf(
            sql,
            128, 
            "update itemdb_info set itemdb_index = %d, itemdb_belong_pos = %d where item_id = %I64d",
            Index,
            belongPos,
            itemDBID
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