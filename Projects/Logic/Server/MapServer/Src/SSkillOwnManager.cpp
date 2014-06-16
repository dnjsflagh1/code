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
#include "CharacterLvlTemplate.h"
#include "SkillInfoList.h"
#include "SkillBaseInfo.h"
#include "SAttributeSystem.h"
#include "AttributeAppend.h"
/******************************************************************************/
namespace MG
{

	//-----------------------------------------------------------------------
	SSkillOwnManager::SSkillOwnManager( SCharacter* character )
		: SkillOwnManager(character)
		,mMinSkillAttackDis(0)
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
		if ( ((SCharacter*)mOwner)->getCharacterTempInfo()  ==  NULL )
			return;
		if ( ((SCharacter*)mOwner)->getCharacterTempInfo()->getCharacterCharacterSkillId(0) == 0 )
			return;

		const CharSkillInfo* charSkillInfo = CharacterSkillTemplate::getInstance().getCharSkillInfo(((SCharacter*)mOwner)->getCharacterTempInfo()->getCharacterCharacterSkillId(0));
		if(charSkillInfo)
		{
			for(UInt i = 0; i < CHAR_SKILL_NUM; ++i)
			{
				if(charSkillInfo->CharSkillList[i] == 0)
				{
					continue;
				}

				SkillOwnManager::addOwnerSkill(charSkillInfo->CharSkillList[i]);
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
			//SkillDBOp::getSkillsDataMap(*FrontServerMain::getInstance().getDBDriver(), mOwner->getID(), tempVSkillData);
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
		 SkillObject* skillObject = NULL;

		 for(UInt i = 0; i < skillList.size(); ++i)
		 {
			 SkillOwnManager::addOwnerSkill(skillList[i]);
		 }
	}
	//-----------------------------------------------------------------------
	void SSkillOwnManager::calAttr( IdType skillId )
	{
		std::map<U32, Flt> tempAttrMap;
		SCharacter* character = (SCharacter*)mOwner;

		SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(skillId);
		if ( skillInfo->skillType != SkillType::SKT_PASSIVENESS )
		{
			InitiativeSkillBasicInfo* initiativeSkillInfo = (InitiativeSkillBasicInfo*)(skillInfo->skillInfo);
			if(mMinSkillAttackDis > initiativeSkillInfo->range || mMinSkillAttackDis == 0)
			{
				mMinSkillAttackDis = initiativeSkillInfo->range;
			}

			return;
		}

		PassivenessSkillBasicInfo* tempskillInfo = (PassivenessSkillBasicInfo*)(skillInfo->skillInfo);
		if ( tempskillInfo->abilityAppendId == 0)
		{
			return;
		}

		//先找到基本属性。
		const AttributeAppendInfo* tempAppendAttr = AttributeAppend::getInstance().getAttributeAppendInfo( tempskillInfo->abilityAppendId );
		if ( tempAppendAttr )
		{
			for (Int i=0; i<APPENDATTR_NUM; i++)
			{
				if ( tempAppendAttr->AppendAttrList[i].id )
				{  
					if ( tempAppendAttr->AppendType == APPEND_TYPE_REAL )
						tempAttrMap[tempAppendAttr->AppendAttrList[i].id] += tempAppendAttr->AppendAttrList[i].value;
					else
						tempAttrMap[tempAppendAttr->AppendAttrList[i].id] += 
						tempAppendAttr->AppendAttrList[i].value*skillInfo->skillInfo->skillLevel*PERMILLAGE_VALUE;
				}
				else
					continue;
			}
		}

		std::map<U32, Flt>::iterator front = tempAttrMap.begin();
		std::map<U32, Flt>::iterator back = tempAttrMap.end();
		while (front != back)
		{
			character->getSAttributeSystem()->calRelateAttr(
				front->first, front->second, 
				character->getCharacterTempInfo()->getCharacterFormulaType(),
				character->getCharacterData()
				);

			++front;
		}
	}
	//-----------------------------------------------------------------------
	void SSkillOwnManager::calAttrAll()
	{
		for(UInt i = 0; i < mSkillList.size(); ++i)
		{
			calAttr(mSkillList[i]);
		}
	}
	//-----------------------------------------------------------------------

	void SSkillOwnManager::addOwnerSkill( IdType skillId )
	{
		SkillOwnManager::addOwnerSkill(skillId);
		calAttr(skillId);
	}

	//-----------------------------------------------------------------------
	Flt SSkillOwnManager::getMinSkillAttackDis()
	{
		return mMinSkillAttackDis;
	}
	//-----------------------------------------------------------------------
	void SSkillOwnManager::calAttrAllBase()
	{
		std::map<U32, Flt> tempAttrMap;
		SCharacter* character = (SCharacter*)mOwner;

		for(UInt i = 0; i < mSkillList.size(); ++i)
		{
			getAttrMap(&tempAttrMap, mSkillList[i]);
		}

		std::map<U32, Flt>::iterator front = tempAttrMap.begin();
		std::map<U32, Flt>::iterator back = tempAttrMap.end();
		while (front != back)
		{
			character->getSAttributeSystem()->addValue(
				front->first, front->second
				);

			++front;
		}
	}
	//-----------------------------------------------------------------------
	void SSkillOwnManager::getAttrMap( std::map<U32, Flt>* pAttrMap, U32 skillId )
	{
		SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(skillId);
		if ( skillInfo->skillType != SkillType::SKT_PASSIVENESS )
		{
			return;
		}

		PassivenessSkillBasicInfo* tempskillInfo = (PassivenessSkillBasicInfo*)(skillInfo->skillInfo);
		if ( tempskillInfo->abilityAppendId == 0)
		{
			return;
		}

		//先找到基本属性。
		const AttributeAppendInfo* tempAppendAttr = AttributeAppend::getInstance().getAttributeAppendInfo( tempskillInfo->abilityAppendId );
		if ( tempAppendAttr )
		{
			for (Int i=0; i<APPENDATTR_NUM; i++)
			{
				if ( tempAppendAttr->AppendAttrList[i].id )
				{  
					if ( tempAppendAttr->AppendType == APPEND_TYPE_REAL )
						(*pAttrMap)[tempAppendAttr->AppendAttrList[i].id] += tempAppendAttr->AppendAttrList[i].value;
					else
						(*pAttrMap)[tempAppendAttr->AppendAttrList[i].id] += 
						tempAppendAttr->AppendAttrList[i].value*skillInfo->skillInfo->skillLevel*PERMILLAGE_VALUE;
				}
				else
					continue;
			}
		}
	}
}