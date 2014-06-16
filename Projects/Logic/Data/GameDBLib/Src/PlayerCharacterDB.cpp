/******************************************************************************/
#include "stdafx.h"
#include "PlayerCharacterDB.h"
#include "MySqlDriver.h"
#include "DBQueryResult.h"
#include "DBDriver.h"
#include "CommonGameDBOp.h"
#include "PlayerItem.h"
/******************************************************************************/

namespace MG
{
	Bool PlayerCharacterDBOp::checkOrCreatePlayerCharacterTable( DBDriver& driver )
	{
		static Colume characterColumn[] = 
		{      		
            {"char_clan_id",			    "BIGINT",			"0"},				//氏族ID
            {"char_name",				    "VARCHAR(50)",		"0"},				//角色名
            {"char_surname",			    "VARCHAR(50)",		"0"},				//角色姓
            //{"char_ziname",				    "VARCHAR(50)",		"0"},				//角色字
            {"char_template_id",		    "INT",			    "0"},				//角色模板ID
            {"char_cur_age",			    "INT",			    "0"},				//角色当前年龄
            {"char_life_span",			    "INT",			    "0"},				//角色基础寿命
            {"char_add_life_span",		    "INT",			    "0"},				//角色增加的寿命
            {"char_cur_lvl",			    "INT",			    "0"},				//角色当前等级
            {"char_cur_exp1",			    "INT",			    "0"},				//角色当前经验
            {"char_cur_exp2",			    "INT",			    "0"},				//角色当前名望
            {"char_cur_exp3",			    "INT",			    "0"},				//角色当前功绩
            {"char_cur_hp",			        "INT",			    "0"},				//角色当前血值
            {"char_cur_mp",			        "INT",			    "0"},				//角色当前魔值
            {"char_lineage_num",		    "INT",			    "0"},               //角色血脉觉醒次数
            {"char_art_mash_id_1",		    "INT",				"0"},				//角色的基础人模
            {"char_art_mash_id_2",		    "INT",				"0"},				//角色的服装模型
            {"char_icon_id",			    "INT",			    "0"},				//角色的2d头像
            {"char_infuence_id",		    "INT",			    "0"},				//角色归属的势力
            {"char_skill_point_all",		"INT",			    "0"},               //角色通过升级总共获得的技能点历史总计
            {"char_no_assign_skill_point",	"INT",			    "0"},               //角色当前的未分配的技能点数
            {"char_state",				    "TINYINT",			"0"},				//角色状态
            {"char_life_state",			    "TINYINT",			"0"},				//角色的生存状态
            {"char_region_type",            "TINYINT",          "0"},               //角色所在区域类型
            {"char_region_id",              "INT",              "0"},               //角色所在区域id
            {"char_pos_x",                  "FLOAT",            "0"},               //角色所在位置x
            {"char_pos_y",                  "FLOAT",            "0"},               //角色所在位置y
            {"char_pos_z",                  "FLOAT",            "0"},               //角色所在位置z	
            {"char_dir_x",                  "FLOAT",            "0"},               //角色所在方位x
            {"char_dir_y",                  "FLOAT",            "0"},               //角色所在方位y
            {"char_dir_z",                  "FLOAT",            "0"},               //角色所在方位z
			{"char_attr_Id",				"INT",				"0"},               //角色属性附加随机ID
			{"char_attr_add_Id",			"INT",				"0"},               //角色属性等级附加随机ID
            {"char_attr_rand1",             "FLOAT",            "0"},               //角色属性随机值力量
            {"char_attr_rand2",             "FLOAT",            "0"},               //角色属性随机值敏捷
            {"char_attr_rand3",             "FLOAT",            "0"},               //角色属性随机值智力	
            {"char_attr_rand4",             "FLOAT",            "0"},               //角色属性随机值体质
            {"char_attr_rand5",             "FLOAT",            "0"},               //角色属性随机值精神
            {"char_attr_rand6",             "FLOAT",            "0"},               //角色属性随机值斗志
            {"char_attr_add_rand1",         "FLOAT",            "0"},               //角色属性随机值力量 升级附加值
            {"char_attr_add_rand2",         "FLOAT",            "0"},               //角色属性随机值敏捷 升级附加值
            {"char_attr_add_rand3",         "FLOAT",            "0"},               //角色属性随机值智力 升级附加值	
            {"char_attr_add_rand4",         "FLOAT",            "0"},               //角色属性随机值体质 升级附加值
            {"char_attr_add_rand5",         "FLOAT",            "0"},               //角色属性随机值精神 升级附加值
            {"char_attr_add_rand6",         "FLOAT",            "0"},               //角色属性随机值斗志 升级附加值
			{"char_item",                   "VARCHAR(10000)",   "0"},               //角色物品
			{"char_buff",                   "VARCHAR(10000)",   "0"},               //角色状态
			
		};

        DBQueryResultEx resEx = driver.query("CREATE TABLE IF NOT EXISTS player_character_info (char_uin BIGINT NOT NULL AUTO_INCREMENT,PRIMARY KEY(char_uin))");
        DBQueryResult* res1 = * resEx;
		if (!res1 ||(res1 && res1->getResultType() == DBQuery_Result_INVALID))
		{
			return false;
		}

		Bool res2 = driver.addColume(CHAR_TABLE_NAME,characterColumn,sizeof(characterColumn)/sizeof(Colume));
		if (!res2)
		{
			return false;
		}
                                   
        if ( !( *( driver.query("ALTER TABLE player_character_info ADD INDEX clanid (char_clan_id)") ) ) )
        {
            return false;
        }

		return true;
	}
    //--------------------------------------------------------------------------------------------------
    Bool PlayerCharacterDBOp::createPlayerCharacter( DBDriver& driver, const PlayerCharacterData* characterDB, U64& uid)
	{
        //插入
        Char8 sql[2048] = {0};
        Str8  tempname;
        Str8  tempsurname;
        Str8  tempziname;
        MGStrOp::toString(characterDB->mName.c_str(), tempname);
        MGStrOp::toString(characterDB->charSurName.c_str(), tempsurname);
       // MGStrOp::toString(characterDB->charZiName.c_str(), tempziname);

        MGStrOp::sprintf(
            sql,
            2048, 
            "insert into player_character_info\
            (char_name, char_surname, char_clan_id, char_template_id, \
            char_cur_age, char_life_span, char_add_life_span, char_cur_lvl, char_cur_exp1, \
            char_cur_exp2, char_cur_exp3, char_cur_hp, char_cur_mp, char_lineage_num, \
            char_art_mash_id_1, char_art_mash_id_2, char_icon_id,  \
            char_infuence_id, char_skill_point_all, char_no_assign_skill_point, char_state, char_life_state, \
            char_region_type, char_region_id, char_pos_x, char_pos_y, char_pos_z, \
			char_dir_x, char_dir_y, char_dir_z, char_attr_Id, char_attr_add_Id,   \
            char_attr_rand1, char_attr_rand2, char_attr_rand3, char_attr_rand4, char_attr_rand5,   \
            char_attr_rand6, char_attr_add_rand1, char_attr_add_rand2, char_attr_add_rand3, char_attr_add_rand4, \
			char_attr_add_rand5, char_attr_add_rand6, char_item, char_buff ) \
             values('%s', '%s', '%I64d', '%d', '%d', '%d', '%d', '%d', '%d', \
            '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d',  \
            '%d', '%d', '%d', '%d', '%d', '%d', '%d', \
            '%f', '%f', '%f', '%f', '%f', '%f', '%d', '%d', '%f', '%f', \
            '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '', '' ) ",
            tempname.c_str(), tempsurname.c_str(), characterDB->charClanId, characterDB->mCharacterTemplateID,
            characterDB->charCurAge, characterDB->charLifeSpan, characterDB->charAddLifeSpan, characterDB->mLevel, characterDB->charExp1,
            characterDB->charExp2, characterDB->charExp3, characterDB->mHp, characterDB->mMp, characterDB->mLineageNum,  
            characterDB->charArtMashID1, characterDB->charArtMashID2, characterDB->charArtIcon,  
            characterDB->charInfluenceID,  characterDB->charSkillPointAll, characterDB->charNoAssignSkillPoint, characterDB->charState, characterDB->charLifeState,  
            characterDB->mRegionType, characterDB->mRegionID, characterDB->mPos.x, characterDB->mPos.y, characterDB->mPos.z,
            characterDB->mDir.x, characterDB->mDir.y, characterDB->mDir.z, characterDB->charAttrAppendId, characterDB->charAttrAppendLvlAddId, 
            characterDB->charAttrRand[0], characterDB->charAttrRand[1], characterDB->charAttrRand[2], characterDB->charAttrRand[3], characterDB->charAttrRand[4],  
            characterDB->charAttrRand[5], characterDB->charAttrRandAdd[0], characterDB->charAttrRandAdd[1], characterDB->charAttrRandAdd[2], characterDB->charAttrRandAdd[3],
			characterDB->charAttrRandAdd[4], characterDB->charAttrRandAdd[5] );

        Bool result = false;
        driver.queryLock();
        { 
            DBQueryResultEx resEx = driver.query( sql, false );
            DBQueryResult* dbRes = *resEx;
            if ( dbRes  &&  dbRes->getResultType() != DBQuery_Result_INVALID )
            {  
                result = true;
                uid = CommonGameDBOp::getLastInsertID( driver, false );
            }
        }
        driver.queryUnLock();
        return result;
	}
    //-------------------------------------------------------------------------------------------------
    Bool PlayerCharacterDBOp::getPlayerCharactersNameMap( DBDriver& driver, U64 clanId, PlayerCharacterIdType charId,
		std::vector<PlayerCharacterData>& nameList,
		std::vector<ItemRecord>& itemRecordList, 
		std::map<IdType, std::map<UInt, BuffData>>& mapPlayerCharBuff )
	{
		Char8 sql[128] = {0};
		PlayerCharacterData data;

		if (charId > 0)
		{
			MGStrOp::sprintf(sql, 128, "select * from player_character_info where char_clan_id = %I64d and char_uin = %I64i", 
							clanId, charId);
		}
		else if(charId == 0)
		{
			MGStrOp::sprintf(sql, 128, "select * from player_character_info where char_clan_id = %I64d", clanId);

		}
		else
		{
			DYNAMIC_ASSERT(0);
		}

		DBQueryResultEx resEx = driver.query(sql);
        DBQueryResult* res = *resEx;
		Str16 wName;
		Str   tempStr;
        
		Str   dbItemRecordString;
		Str	  dbBuffDataString;
        //数据库错误
        if ( !res )
        {
            return false;
        }

		I32 nRow = res->getRowCount();
        
		if (res  &&  nRow > 0 )
		{
			for(Int i = 0; i < nRow; i++)
			{
				memset(&data, 0, sizeof(data));
                I32 nCol = 0;

				data.mId                     = res->getFieldData(i,nCol++)->ulonglongData;
                data.charClanId                 = res->getFieldData(i,nCol++)->ulonglongData;

				res->getFieldData(i,nCol++,tempStr);
				MGStrOp::toString(tempStr.c_str(),wName);
                data.mName                   = wName;

                res->getFieldData(i,nCol++,tempStr);
                MGStrOp::toString(tempStr.c_str(),wName);
                data.charSurName                = wName;

                //res->getFieldData(i,nCol++,tempStr);
                //MGStrOp::toString(tempStr.c_str(),wName);
                //data.charZiName                 = wName;
				
                data.mCharacterTemplateID        = res->getFieldData(i,nCol++)->uintData;
                data.charCurAge                 = res->getFieldData(i,nCol++)->uintData;
                data.charLifeSpan               = res->getFieldData(i,nCol++)->uintData;
                data.charAddLifeSpan            = res->getFieldData(i,nCol++)->uintData;
                data.mLevel                    = res->getFieldData(i,nCol++)->uintData;
                data.charExp1                   = res->getFieldData(i,nCol++)->uintData;
                data.charExp2                   = res->getFieldData(i,nCol++)->uintData;
                data.charExp3                   = res->getFieldData(i,nCol++)->uintData;
                data.mHp                     = res->getFieldData(i,nCol++)->uintData;
                data.mMp                     = res->getFieldData(i,nCol++)->uintData;
                data.mLineageNum             = res->getFieldData(i,nCol++)->uintData;
                data.charArtMashID1             = res->getFieldData(i,nCol++)->uintData;
                data.charArtMashID2             = res->getFieldData(i,nCol++)->uintData;
                data.charArtIcon                = res->getFieldData(i,nCol++)->uintData;
                data.charInfluenceID            = res->getFieldData(i,nCol++)->uintData;
                data.charSkillPointAll          = res->getFieldData(i,nCol++)->uintData;
                data.charNoAssignSkillPoint     = res->getFieldData(i,nCol++)->uintData;
                data.charState                  = (CHAR_STATE)res->getFieldData(i,nCol++)->ubyteData;
                data.charLifeState              = (CHAR_LIFE_STATE)res->getFieldData(i,nCol++)->ubyteData;
 	
                data.mRegionType             = (REGION_OBJ_TYPE)res->getFieldData(i,nCol++)->ubyteData;
                data.mRegionID               = res->getFieldData(i,nCol++)->uintData;
                data.mPos.x                  = res->getFieldData(i, nCol++)->FltData;
                data.mPos.y                  = res->getFieldData(i, nCol++)->FltData;
                data.mPos.z                  = res->getFieldData(i, nCol++)->FltData;
                data.mDir.x                  = res->getFieldData(i, nCol++)->FltData;
                data.mDir.y                  = res->getFieldData(i, nCol++)->FltData;
                data.mDir.z                  = res->getFieldData(i, nCol++)->FltData;

				data.charAttrAppendId		 = res->getFieldData(i, nCol++)->uintData;
				data.charAttrAppendLvlAddId	 = res->getFieldData(i, nCol++)->uintData;

                for (Int j=0; j<6; j++)
                {
                    data.charAttrRand[j]        = res->getFieldData(i, nCol++)->FltData;
                }

                for (Int j=0; j<6; j++)
                {
                    data.charAttrRandAdd[j]     = res->getFieldData(i, nCol++)->FltData;
                }
                
				//道具
				res->getFieldData(i,nCol++,dbItemRecordString);
				nameList.push_back(data);
				//加载角色物品数据
				loadPlayerCharacterItem(dbItemRecordString,itemRecordList);

				//buff
				res->getFieldData(i, nCol++, dbBuffDataString);
				//加载角色状态list
				//std::map<UInt, BuffData> mapBuffData;
				//loadPlayerCharacterBuff(dbBuffDataString, mapBuffData);
				//mapPlayerCharBuff[data.mId] = mapBuffData;
			}
			return true;
		}

		return true;
	}
    //-------------------------------------------------------------------------------------------------
    Bool PlayerCharacterDBOp::updatePlayerCharacterHP( DBDriver& driver, U64 charId, UInt hp )
    {
        Char8 sql[128] = {0};
        MGStrOp::sprintf(
            sql,
            128, 
            "update "CHAR_TABLE_NAME" set char_cur_hp = %d where char_uin = %I64d",
            hp,
            charId
            );
        DBQueryResultEx resEx = driver.query( sql, false );
        DBQueryResult* dbRes = *resEx;
        if ( dbRes  &&  dbRes->getResultType() != DBQuery_Result_INVALID )
        {  
            return true;
        }
        return false;
		//return true;
    }
    //-------------------------------------------------------------------------------------------------
    Bool PlayerCharacterDBOp::updatePlayerCharacterMP( DBDriver& driver, U64 charId, UInt mp )
    {
        Char8 sql[128] = {0};
        MGStrOp::sprintf(
            sql,
            128, 
            "update "CHAR_TABLE_NAME" set char_cur_mp = %d where char_uin = %I64d",
            mp,
            charId
            );
        DBQueryResultEx resEx = driver.query( sql, false );
        DBQueryResult* dbRes = *resEx;
        if ( dbRes  &&  dbRes->getResultType() != DBQuery_Result_INVALID )
        {  
            return true;
        }
        return false;
    }
    //-------------------------------------------------------------------------------------------------
    Bool PlayerCharacterDBOp::updatePlayerCharacterInfo( DBDriver& driver, const PlayerCharacterData* characterDB )
    {
        Char8 sql[1024] = {0};

        MGStrOp::sprintf(
            sql,
            1024, 
            "update "CHAR_TABLE_NAME" \
            set char_template_id = %d, char_cur_age = %d, char_life_span = %d, char_add_life_span = %d, \
            char_cur_lvl = %d, char_cur_hp = %d, char_cur_mp = %d, \
             char_icon_id = %d, \
            char_region_type = %d, char_region_id = %d, char_pos_x = %f, char_pos_y = %f, char_pos_z = %f, \
            char_dir_x = %f, char_dir_y = %f, char_dir_z = %f, char_attr_Id = %d, char_attr_add_Id = %d, \
            char_attr_rand1 = %f, char_attr_rand2 = %f, char_attr_rand3 = %f, char_attr_rand4 = %f, char_attr_rand5 = %f,  \
            char_attr_rand6 = %f, char_attr_add_rand1 = %f, char_attr_add_rand2 = %f, char_attr_add_rand3 = %f, char_attr_add_rand4 = %f, char_attr_add_rand5 = %f,\
			char_attr_add_rand6 = %f  where char_uin = %I64d",
            characterDB->mCharacterTemplateID,
            characterDB->charCurAge, characterDB->charLifeSpan, characterDB->charAddLifeSpan, characterDB->mLevel, 
            characterDB->mHp, characterDB->mMp, characterDB->charArtIcon,   
            characterDB->mRegionType, characterDB->mRegionID,
            characterDB->mPos.x, characterDB->mPos.y, characterDB->mPos.z,
            characterDB->mDir.x, characterDB->mDir.y, characterDB->mDir.z,
			characterDB->charAttrAppendId, characterDB->charAttrAppendLvlAddId,
            characterDB->charAttrRand[0], characterDB->charAttrRand[1], characterDB->charAttrRand[2], 
            characterDB->charAttrRand[3], characterDB->charAttrRand[4], characterDB->charAttrRand[5], 
            characterDB->charAttrRandAdd[0], characterDB->charAttrRandAdd[1], characterDB->charAttrRandAdd[2], 
            characterDB->charAttrRandAdd[3], characterDB->charAttrRandAdd[4], characterDB->charAttrRandAdd[5], 
            characterDB->mId
            );

        DBQueryResultEx resEx = driver.query( sql, false );
        DBQueryResult* dbRes = *resEx;
        if ( dbRes  &&  dbRes->getResultType() != DBQuery_Result_INVALID )
        {  
            return true;
        }
        return false;
    }
	//-------------------------------------------------------------------------------------------------
	MG::Bool PlayerCharacterDBOp::deletePlayerCharacter( DBDriver& driver,U64 clanID )
	{
		Char8 sql[128] = {0};
		MGStrOp::sprintf(
			sql,
			128,
			"delete from player_character_info where char_clan_id = %I64d",
			clanID
			);
			DBQueryResultEx resEx = driver.query( sql, false );
		DBQueryResult* dbRes = *resEx;
		if ( dbRes  &&  dbRes->getResultType() != DBQuery_Result_INVALID )
		{  
			return true;
		}
		return false;
	}
	//-------------------------------------------------------------------------------------------------
	MG::Bool PlayerCharacterDBOp::updatePlayerCharacterLevel( DBDriver& driver, U64 charId, UInt level )
	{
		Char8 sql[128] = {0};
		MGStrOp::sprintf(
			sql,
			128, 
			"update "CHAR_TABLE_NAME" set char_cur_lvl = %d where char_uin = %I64d",
			level,
			charId
			);
		DBQueryResultEx resEx = driver.query( sql, false );
		DBQueryResult* dbRes = *resEx;
		if ( dbRes  &&  dbRes->getResultType() != DBQuery_Result_INVALID )
		{  
			return true;
		}
		return false;
	}
	//-------------------------------------------------------------------------------------------------
	MG::Bool PlayerCharacterDBOp::updatePlayerCharacterExp( DBDriver& driver, U64 charId, UInt exp )
	{
		Char8 sql[128] = {0};
		MGStrOp::sprintf(
			sql,
			128, 
			"update "CHAR_TABLE_NAME" set char_cur_exp1 = %d where char_uin = %I64d",
			exp,
			charId
			);
		DBQueryResultEx resEx = driver.query( sql, false );
		DBQueryResult* dbRes = *resEx;
		if ( dbRes  &&  dbRes->getResultType() != DBQuery_Result_INVALID )
		{  
			return true;
		}
		return false;
	}
	//-------------------------------------------------------------------------------------------------
	void PlayerCharacterDBOp::loadPlayerCharacterItem( Str8 dbCharacterRecordString,std::vector<ItemRecord>& recordList )
	{
		std::vector<Str8> tempCharacterItemRecords;
		MGStrOp::split<Str8>(dbCharacterRecordString,DB_RECORDS_SEPARATOR,tempCharacterItemRecords);
		if (tempCharacterItemRecords.size() >0 && 
			dbCharacterRecordString.length() > 0 && dbCharacterRecordString[0] != L'\0')
		{
			//对应数据库中的字段
			IdType              itemDBID            = 0;
			PlayerCharacterIdType characterId       = 0;
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
			std::vector<Str8>::iterator front = tempCharacterItemRecords.begin();
			std::vector<Str8>::iterator back = tempCharacterItemRecords.end();
			while(front != back)
			{
				std::vector<Str8> FieldsInRecord;
				MGStrOp::split<Str8>((*front),DB_FIELDS_SEPARATOR,FieldsInRecord);
				MGStrOp::toU64(FieldsInRecord[0].c_str(),itemDBID);
				itemRecordObject.itemDBID = itemDBID;
				MGStrOp::toU64(FieldsInRecord[1].c_str(),characterId);
				itemRecordObject.characterId = characterId;
				MGStrOp::toU32(FieldsInRecord[2].c_str(),itemTempID);
				itemRecordObject.itemTempID = itemTempID;
				MGStrOp::toI32(FieldsInRecord[3].c_str(),itemBelongType);
				itemRecordObject.itemBelongType = (ITEM_BELONG_TYPE)itemBelongType;
				MGStrOp::toU64(FieldsInRecord[4].c_str(),itemBelongID);
				itemRecordObject.itemBelongID = itemBelongID;
				MGStrOp::toI32(FieldsInRecord[5].c_str(),belongPos);
				itemRecordObject.belongPos = (ITEM_SITE_TYPE)belongPos;
				MGStrOp::toI32(FieldsInRecord[6].c_str(),bindType);
				itemRecordObject.bindType = (ITEM_BIND_TYPE)bindType;
				MGStrOp::toU32(FieldsInRecord[7].c_str(),slotIndex);
				itemRecordObject.slotIndex = slotIndex;
				//
				Str16 tempName;
				MGStrOp::toString(FieldsInRecord[8].c_str(),tempName);
				memcpy(itemRecordObject.fatherName,tempName.c_str(), sizeof(MAX_CHARACTER_NAME_LEN));
				MGStrOp::toU32(FieldsInRecord[9].c_str(),curNum);
				itemRecordObject.curNum = curNum;
				MGStrOp::toU32(FieldsInRecord[10].c_str(),curDurable);
				itemRecordObject.curDurable = curDurable;
				MGStrOp::toU32(FieldsInRecord[11].c_str(),curRepairNum);
				itemRecordObject.curRepairNum = curRepairNum;
				MGStrOp::toU32(FieldsInRecord[12].c_str(),curStrengthenLv);
				itemRecordObject.curStrengthenLv = curStrengthenLv;
				MGStrOp::toU32(FieldsInRecord[13].c_str(),randAppendID);
				itemRecordObject.randAppendID = randAppendID;
				MGStrOp::toU32(FieldsInRecord[14].c_str(),strengthenAppendID);
				itemRecordObject.strengthenAppendID = strengthenAppendID;
				MGStrOp::toU64(FieldsInRecord[15].c_str(),dueTime);
				itemRecordObject.delTime = dueTime;
				MGStrOp::toU64(FieldsInRecord[16].c_str(),bornTime);
				itemRecordObject.bornTime = bornTime;
				MGStrOp::toU64(FieldsInRecord[17].c_str(),delTime);
				itemRecordObject.delTime = delTime;
				MGStrOp::toU64(FieldsInRecord[18].c_str(),updateTime);
				itemRecordObject.updateTime = updateTime;
				
				recordList.push_back(itemRecordObject);
				front++;
			}

		}
	}
	//-------------------------------------------------------------------------------------------------
	bool PlayerCharacterDBOp::updatePlayerCharacterItem( DBDriver& driver, U64 charId,std::vector<PlayerItem*>* characterItemList )
	{
		Str8 dbCharacterItemRecordString;
		if (characterItemList->size() > 0)
		{
			//对应数据库中的字段
			Str8                 itemDBID;
			Str8 characterId;
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
			std::vector<PlayerItem*>::iterator front = characterItemList->begin();
			std::vector<PlayerItem*>::iterator back = characterItemList->end();
			while ( front!= back)
			{
				countFlag++;
				MGStrOp::toString((*front)->getItemRecord()->itemDBID,itemDBID);
				MGStrOp::toString((*front)->getItemRecord()->characterId,characterId);
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
				tempFields = itemDBID + "." + characterId + "." + itemTempID + "." + itemBelongType + "." + itemBelongID + "." + belongPos + "." 
					+ bindType + "." + slotIndex + "." 
					+ fatherName + "." + curNum + "." + curDurable + "." + curRepairNum + "." + curStrengthenLv + "." + randAppendID + "." + strengthenAppendID + "." 
					+ dueTime + "." + bornTime + "." + delTime + "." + updateTime;
				if (countFlag == characterItemList->size())
				{
					dbCharacterItemRecordString += tempFields;
				}
				else
				{
					dbCharacterItemRecordString += tempFields + ",";
				}

				front++;
			}
		}
		//
		Char8 sql[2048] = {0};
		MGStrOp::sprintf(
			sql,
			2048, 
			"update "CHAR_TABLE_NAME" set char_item = '%s' where char_uin = %I64d",
			dbCharacterItemRecordString.c_str(),
			charId
			);
		DBQueryResultEx resEx = driver.query( sql, false );
		DBQueryResult* dbRes = *resEx;
		if ( dbRes  &&  dbRes->getResultType() != DBQuery_Result_INVALID )
		{  
			return true;
		}
		return false;
	}
	//-------------------------------------------------------------------------------------------------
	bool PlayerCharacterDBOp::updatePlayerCharacterBuff( DBDriver& driver, U64 charId, std::map<UInt, BuffData>* buffDataList )
	{
		Str8 dbCharacterItemRecordString;
		if (buffDataList->size() > 0)
		{
			//对应数据库中的字段
			Str8					buffId;
			Str8					curAddNum;
			Str8					timeUse;
			Str8					timeStart;
			//将buff转化为字符串。
			Str8 tempFields;
			U32  countFlag = 0;
			std::map<UInt, BuffData>::iterator front = buffDataList->begin();
			std::map<UInt, BuffData>::iterator back = buffDataList->end();
			while ( front!= back)
			{
				countFlag++;

				MGStrOp::toString((*front).second.mBuffId,			buffId);
				MGStrOp::toString((*front).second.mCurAddNum,		curAddNum);
				MGStrOp::toString((*front).second.mTimeUse,			timeUse);
				MGStrOp::toString((*front).second.mTimeStart,		timeStart);
				
				tempFields = buffId + "." + curAddNum + "." + timeUse + "." + timeStart;
				if (countFlag == buffDataList->size())
				{
					dbCharacterItemRecordString += tempFields;
				}
				else
				{
					dbCharacterItemRecordString += tempFields + ",";
				}

				front++;
			}
		}
		//转化的字符串存到CHAR_TABLE_NAME表中。
		/*Char8 sql[2048] = {0};
		MGStrOp::sprintf(
			sql,
			128, 
			"update "CHAR_TABLE_NAME" set char_bufflist = '%s' where char_uin = %I64d",
			dbCharacterItemRecordString.c_str(),
			charId
			);
		DBQueryResultEx resEx = driver.query( sql, false );
		DBQueryResult* dbRes = *resEx;
		if ( dbRes  &&  dbRes->getResultType() != DBQuery_Result_INVALID )
		{  
			return true;
		}*/
		return false;
	}
	//-------------------------------------------------------------------------------------------------
	void PlayerCharacterDBOp::loadPlayerCharacterBuff( Str8 dbCharacterRecordString,std::map<UInt, BuffData>& recordList )
	{
		std::vector<Str8> tempCharacterItemRecords;
		MGStrOp::split<Str8>(dbCharacterRecordString,DB_RECORDS_SEPARATOR,tempCharacterItemRecords);
		if (tempCharacterItemRecords.size() >0 && 
			dbCharacterRecordString.length() > 0 && dbCharacterRecordString[0] != L'\0')
		{
			//buff对象
			BuffData tempBuffData;

			ItemRecord  itemRecordObject;
			std::vector<Str8>::iterator front = tempCharacterItemRecords.begin();
			std::vector<Str8>::iterator back = tempCharacterItemRecords.end();
			while(front != back)
			{
				std::vector<Str8> FieldsInRecord;
				MGStrOp::split<Str8>((*front),DB_FIELDS_SEPARATOR,FieldsInRecord);

				//对应数据库中的字段
				MGStrOp::toI32(FieldsInRecord[0].c_str(),tempBuffData.mBuffId);
				MGStrOp::toI32(FieldsInRecord[1].c_str(),tempBuffData.mCurAddNum);
				MGStrOp::toI32(FieldsInRecord[2].c_str(),(I32&)(tempBuffData.mTimeUse));
				MGStrOp::toU32(FieldsInRecord[4].c_str(),tempBuffData.mTimeStart);

				recordList[tempBuffData.mBuffId] = tempBuffData;

				front++;
			}

		}
	}
	//-------------------------------------------------------------------------------------------------
}