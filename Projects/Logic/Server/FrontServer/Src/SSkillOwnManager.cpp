/******************************************************************************/
#include "stdafx.h"
#include "SSkillObject.h"
#include "SSkillOwnManager.h"
#include "SPlayer.h"
#include "SLuaSkillSystem.h"
#include "CharacterSkillTempLate.h"
#include "SCharacter.h"
#include "SkillDB.h"
#include "CharacterList.h"
#include "FrontServerMain.h"
#include "CharacterLvlTemplate.h"
/******************************************************************************/
namespace MG
{

	//-----------------------------------------------------------------------
	SSkillOwnManager::SSkillOwnManager( SCharacter* character )
		: SkillOwnManager(character)
	{

	}

	//-----------------------------------------------------------------------
	SSkillOwnManager::~SSkillOwnManager()
	{

	}


	//-----------------------------------------------------------------------
	void SSkillOwnManager::getDefultSkill()
	{
		 //const CharacterTempInfo* tempInfo = ((SCharacter*)mOwner)->getCharacterTempInfo();
		 //if ( tempInfo )
		 //{
			// vector<SkillData> tempVSkillData;
			// getTempSkill(tempVSkillData, tempInfo);
			// //存储DB
			// if ( mOwner->getType() == GOT_PLAYERCHARACTER )
			//	 SkillDBOp::createSkill( (*FrontServerMain::getInstance().getDBDriver()), mOwner->getID(), tempVSkillData );

			// //加入内存
			// addSkillData(tempVSkillData);
		 //}

		const CharSkillInfo* charSkillInfo = CharacterSkillTemplate::getInstance().getCharSkillInfo(((SCharacter*)mOwner)->getCharacterTempInfo()->getCharacterCharacterSkillId(0));
		if(charSkillInfo)
		{
			for(UInt i = 0; i < CHAR_SKILL_NUM; ++i)
			{
				if(charSkillInfo->CharSkillList[i] == 0)
				{
					continue;
				}

				SkillOwnManager::addOwnerSkill( charSkillInfo->CharSkillList[i] );
			}
		}
	}
	//-----------------------------------------------------------------------
	void SSkillOwnManager::getDBSkill()
	{
		vector<IdType> tempVSkillData;
		//获取技能
		if ( mOwner->getType() == GOT_PLAYERCHARACTER )
		{
			SkillDBOp::getSkillsDataMap(*FrontServerMain::getInstance().getDBDriver(), mOwner->getID(), tempVSkillData);
			//如果没有技能，在重新读一遍
			if ( tempVSkillData.size() < 1 )
			{
				getDefultSkill();
				return;
			}
		}
		else
		{
			const CharacterTempInfo* tempInfo = ((SCharacter*)mOwner)->getCharacterTempInfo();
			if ( tempInfo )
			{
				getTempSkill(tempVSkillData, tempInfo);
			}
				//SkillData skillData;
				//skillData.skillId = 9;
				//skillData.skillLevel = 1;
				//tempVSkillData.push_back(skillData);
		}
		 //加入内存
	     
		addOwnerSkill(tempVSkillData);
	}
	//-----------------------------------------------------------------------
	void SSkillOwnManager::getTempSkill( vector<IdType>& tempVSkillData, const CharacterTempInfo* pTempInfo )
	{
		const CharSkillInfo* tempVSkillInfo[CHAR_SKILL_ID_NUM];
		IdType tempSkillId;
		//获得技能模板信息
		/*if ( CHAR_ATTRRAND_TYPE_YES == pTempInfo->getCharacterAbilityRandomType() )
		{
			for (Int i=0; i<CHAR_SKILL_ID_NUM; i++)
			{
				tempVSkillInfo[i] = CharacterSkillTemplate::getInstance().getRandCharSkillInfo(pTempInfo->getCharacterCharacterSkillId(i));
			}

		}
		else*/
		{
			for (Int i=0; i<CHAR_SKILL_ID_NUM; i++)
			{
				tempVSkillInfo[i] = CharacterSkillTemplate::getInstance().getCharSkillInfo(pTempInfo->getCharacterCharacterSkillId(i));
			}
		}
		 //提取技能信息
		for (Int i=0; i<CHAR_SKILL_ID_NUM; i++)
		{
			if (tempVSkillInfo[i] == NULL)
				continue;
			for (Int j=0; j<CHAR_SKILL_NUM; j++)
			{
				if ( tempVSkillInfo[i]->CharSkillList[j] )
				{   
					tempSkillId = tempVSkillInfo[i]->CharSkillList[j];
					tempVSkillData.push_back(tempSkillId);
				}
			}
		}
	}

	//-----------------------------------------------------------------------
	void SSkillOwnManager::addOwnerSkill(std::vector<IdType> skillList)
	{
		 for(UInt i = 0; i < skillList.size(); ++i)
		 {
			 SkillOwnManager::addOwnerSkill(skillList[i]);
		 }
	}

	//-----------------------------------------------------------------------
}