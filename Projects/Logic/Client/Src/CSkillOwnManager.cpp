/******************************************************************************/
#include "stdafx.h"
#include "CSkillOwnManager.h"
#include "CCharacter.h"
#include "SkillInfoList.h"
#include "CSkillObject.h"
#include "AttributeAppend.h"
#include "CharacterList.h"
/******************************************************************************/

namespace MG
{

	//-----------------------------------------------------------------------
	CSkillOwnManager::CSkillOwnManager( CCharacter* character )
		: SkillOwnManager(character)
		,mDefaultSkill(0)
	{

	}

	//-----------------------------------------------------------------------
	CSkillOwnManager::~CSkillOwnManager()
	{

	}

	//-----------------------------------------------------------------------
	void CSkillOwnManager::addOwnerSkill( IdType skillId )
	{
		SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(skillId);
		if(mDefaultSkill == 0 && skillInfo && (skillInfo->skillType == SKT_SHORTRANGEGENERAL || skillInfo->skillType == SKT_LONGRANGEGENERAL))
		{
			mDefaultSkill = skillId;
		}

		//计算属性
		calAttr(skillId);

		SkillOwnManager::addOwnerSkill(skillId);
	}

	//-----------------------------------------------------------------------
	UInt CSkillOwnManager::getDefaultSkill()
	{
		return mDefaultSkill;
	}
	//-----------------------------------------------------------------------
	void CSkillOwnManager::calAttrAll()
	{
		for(UInt i = 0; i < mSkillList.size(); ++i)
		{
			calAttr(mSkillList[i]);
		}
	}
	//-----------------------------------------------------------------------
	void CSkillOwnManager::calAttrAllBase()
	{
		std::map<U32, Flt> tempAttrMap;
		CCharacter* character = (CCharacter*)mOwner;

		for(UInt i = 0; i < mSkillList.size(); ++i)
		{
			getAttrMap(&tempAttrMap, mSkillList[i]);
		}

		std::map<U32, Flt>::iterator front = tempAttrMap.begin();
		std::map<U32, Flt>::iterator back = tempAttrMap.end();
		while (front != back)
		{
			character->getAttributeSystem()->addValue(
				front->first, front->second
				);

			++front;
		}
	}
	//-----------------------------------------------------------------------
	void CSkillOwnManager::calAttr( IdType skillId )
	{
		std::map<U32, Flt> tempAttrMap;
		CCharacter* character = (CCharacter*)mOwner;

		for(UInt i = 0; i < mSkillList.size(); ++i)
		{
			getAttrMap(&tempAttrMap, mSkillList[i]);
		}

		std::map<U32, Flt>::iterator front = tempAttrMap.begin();
		std::map<U32, Flt>::iterator back = tempAttrMap.end();
		while (front != back)
		{
			character->getAttributeSystem()->calRelateAttr(
				front->first, front->second, 
				character->getCharacterTempInfo()->getCharacterFormulaType(),
				character->getCharacterData()
				);

			++front;
		}
	}
	//-----------------------------------------------------------------------
	void CSkillOwnManager::getAttrMap( std::map<U32, Flt>* pAttrMap, U32 skillId )
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