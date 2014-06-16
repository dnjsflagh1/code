/******************************************************************************/
#include "stdafx.h"
#include "SkillDB.h"
#include "MySqlDriver.h"
#include "DBQueryResult.h"
#include "DBDriver.h"
#include "CommonGameDBOp.h"
/******************************************************************************/
namespace MG
{
	Bool SkillDBOp::checkOrCreateSkillTable( DBDriver& driver )
	{
		static Colume skillColumn[] = 
		{      		
			{"skill_master_id",			"BIGINT",			"0"},				//根据以上主人类型，记录的Id( 或regionID或clanID )
			{"skill_data",				"VARCHAR(240)",		"0"},				//skill数据	         
		};

        DBQueryResultEx resEx = driver.query("CREATE TABLE IF NOT EXISTS "SKILL_TABLE_NAME" (skill_uin BIGINT NOT NULL AUTO_INCREMENT,PRIMARY KEY(skill_uin))");
        DBQueryResult* pRes = *resEx;
        if (!pRes ||(pRes && pRes->getResultType() == DBQuery_Result_INVALID))
        {
            return false;
        }

		Bool res1 = driver.addColume(SKILL_TABLE_NAME,skillColumn,sizeof(skillColumn)/sizeof(Colume));
		if (!res1)
		{
			return false;
		}
		//加索引
		if ( !( *( driver.query("CREATE UNIQUE INDEX charmasterid ON skill_info (skill_master_id)") ) ) )
		{
			return false;
		}

		return true;
	}
	//----------------------------------------------------------------------------------------
	Bool SkillDBOp::createSkill( DBDriver& driver, U64 characterId, std::vector<IdType> skillList )
	{
		//插入
		Char8 sql[512] = {0};
        //转换为字符串
		Str8 skillString = composeSkillString(skillList);
        //打印
		MGStrOp::sprintf(
			sql,
			512, 		
			"insert into "SKILL_TABLE_NAME"\
										  (skill_master_id, skill_data) values('%I64d', '%s')" ,
										  characterId, skillString.c_str()
										  );
        //存储DB
		Bool result = false; 
        DBQueryResultEx resEx = driver.query( sql );
        DBQueryResult* dbRes = *resEx;
		if ( !dbRes )
		{  
			return false;
		}

		return true;
	}

	//----------------------------------------------------------------------------------------
	Bool SkillDBOp::updateSkill( DBDriver& driver, U64 characterId, IdType skillData )
	{

		return false;
	}

	//----------------------------------------------------------------------------------------
	Bool SkillDBOp::getSkillsDataMap(DBDriver& driver, U64 characterId, std::vector<IdType>& skillList)
	{
		Str skillString;

		Char8 sql[128] = {0};
		MGStrOp::sprintf(sql,128,"select * from "SKILL_TABLE_NAME" where skill_master_id = %I64d ", characterId);

        DBQueryResultEx resEx = driver.query( sql );
        DBQueryResult* res = *resEx;
		if ( res  &&  res->getResultType() != DBQuery_Result_INVALID  &&  res->getRowCount() > 0 )
		{
			assert( res->getRowCount() < 2 );
			res->getFieldData( 0, 2, skillString);
			analysisSkillData(skillString, skillList);

			return true;
		}

		return false;
	}

	//----------------------------------------------------------------------------------------
	void SkillDBOp::analysisSkillData(Str skillStr, std::vector<IdType>& skillList)
	{
		Str tempStr;
		IdType skillId;
		Int index = 0;

		while(1)
		{
			index = skillStr.find(';');

			if(index == -1)
			{
				return;
			}

			tempStr = skillStr.substr(0, index);
			skillStr = skillStr.substr(index + 1, skillStr.length());

			index = tempStr.find(',');
			Str tempSkillId = tempStr.substr(0, index);
			MGStrOp::toU64(tempSkillId.c_str(), skillId);
			//Str tempSkillLevel = tempStr.substr(index + 1, tempStr.length());
			//MGStrOp::toU32(tempSkillLevel.c_str(), skillData.skillLevel);

			skillList.push_back(skillId);
		}
	}

	//----------------------------------------------------------------------------------------
	Str8 SkillDBOp::composeSkillString( std::vector<IdType>& skillList )
	{
		Str8 skillString;
		Str8 tempString;

		for(UInt i = 0; i < skillList.size(); ++i)
		{
			MGStrOp::toString(skillList[i], tempString);
			skillString += tempString + ";";
			//MGStrOp::toString(skillList[i].skillLevel, tempString);
			//skillString += tempString + ";";
		}

		return skillString;
	}

	//----------------------------------------------------------------------------------------
	void SkillDBOp::insertSkillData( std::vector<IdType>& skillList, IdType skillId )
	{
		for(UInt i = 0; i < skillList.size(); ++i)
		{
			if(skillList[i] == skillId)
			{
				 return;
			}
		}

		skillList.push_back(skillId);
	}

}