/******************************************************************************/
#include "stdafx.h"
#include "SSkillUseManager.h"
#include "SPlayer.h"
#include "SLuaSkillSystem.h"
#include "CharacterSkillTempLate.h"
#include "SCharacter.h"
#include "SkillDB.h"
#include "CharacterList.h"
#include "FrontServerMain.h"
#include "SkillInfoList.h"
#include "SkillBaseInfo.h"
#include "ShortRangeGeneralAttackSkillTemplate.h"
#include "LongRangeGeneralAttackSkillTemplate.h"
#include "SingleTargetSkillTemplate.h"
/******************************************************************************/
namespace MG
{

    //-----------------------------------------------------------------------
    SSkillUseManager::SSkillUseManager( SCharacter* character )
        :SkillUseManager(character)
    {
    }

    //-----------------------------------------------------------------------
    SSkillUseManager::~SSkillUseManager()
    {
        
    }

    //-----------------------------------------------------------------------
    SkillObject* SSkillUseManager::createSkillObject(IdType id)
    {
		SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(id);
		if(!skillInfo)
		{
			return NULL;
		}

		SCharacter* character = getSCharacter();
		if(skillInfo && character)
		{
			mCurrUseSkill= MG_POOL_NEW(mSkillObjectPool, SSkillObject, (character)); 
			mCurrUseSkill->setSkillInfo(skillInfo);
			return mCurrUseSkill;
		}

		return NULL;
    }

	 //-----------------------------------------------------------------------
	Bool SSkillUseManager::isCanUseSkill(IdType id)
	{
		return true;
	}

	//-----------------------------------------------------------------------
	void SSkillUseManager::destroySkillObject(SkillObject*& skillObject)
	{
		SSkillObject*& tempskillObject = (SSkillObject*&)skillObject;
		MG_POOL_DELETE(mSkillObjectPool, tempskillObject);
		skillObject = NULL;
	}
    //-----------------------------------------------------------------------
   // void SSkillUseManager::getDefultSkill()
   // {
   //     const CharacterTempInfo* tempInfo = getSCharacter()->getCharacterTempInfo();
   //     if ( tempInfo )
   //     {
   //         vector<SkillData> tempVSkillData;
   //         getTempSkill(tempVSkillData, tempInfo);
   //         //存储DB
   //         if ( getCharacter()->getType() == GOT_PLAYERCHARACTER )
   //             SkillDBOp::createSkill( (*FrontServerMain::getInstance().getDBDriver()), getCharacter()->getID(), tempVSkillData );

   //         //加入内存
   //         addSkill(tempVSkillData);
   //     }
   // }
   // //-----------------------------------------------------------------------
   // void SSkillUseManager::getDBSkill()
   // {
   //     vector<SkillData> tempVSkillData;
   //     //获取技能
   //     if ( getCharacter()->getType() == GOT_PLAYERCHARACTER )
   //     {
   //         SkillDBOp::getSkillsDataMap(*FrontServerMain::getInstance().getDBDriver(), getCharacter()->getID(), tempVSkillData);
   //         //如果没有技能，在重新读一遍
   //         if ( tempVSkillData.size() < 1 )
   //         {
   //             getDefultSkill();
   //             return;
   //         }
   //     }
   //     else
   //     {
   //         const CharacterTempInfo* tempInfo = getSCharacter()->getCharacterTempInfo();
   //         if ( tempInfo )
   //         {
   //             getTempSkill(tempVSkillData, tempInfo);
   //         }
			////SkillData skillData;
			////skillData.skillId = 9;
			////skillData.skillLevel = 1;
			////tempVSkillData.push_back(skillData);
   //     }
   //     //加入内存
   //     
   //     addSkill(tempVSkillData);
   // }
   // //-----------------------------------------------------------------------
   // void SSkillUseManager::getTempSkill( vector<SkillData>& tempVSkillData, const CharacterTempInfo* pTempInfo )
   // {
   //     const CharSkillInfo* tempVSkillInfo[CHAR_SKILL_ID_NUM];
   //     SkillData tempData;
   //     //获得技能模板信息
   //     if ( CHAR_ATTRRAND_TYPE_YES == pTempInfo->AbilityRandomType )
   //     {
   //         for (Int i=0; i<CHAR_SKILL_ID_NUM; i++)
   //         {
   //             tempVSkillInfo[i] = CharacterSkillTemplate::getInstance().getRandCharSkillInfo(pTempInfo->CharacterSkillId[i]);
   //         }

   //     }
   //     else
   //     {
   //         for (Int i=0; i<CHAR_SKILL_ID_NUM; i++)
   //         {
   //             tempVSkillInfo[i] = CharacterSkillTemplate::getInstance().getCharSkillInfo(pTempInfo->CharacterSkillId[i]);
   //         }
   //     }
   //     //提取技能信息
   //     for (Int i=0; i<CHAR_SKILL_ID_NUM; i++)
   //     {
   //         if (tempVSkillInfo[i] == NULL)
   //             continue;
   //         for (Int j=0; j<CHAR_SKILL_NUM; j++)
   //         {
   //             if ( tempVSkillInfo[i]->CharSkillList[j].id )
   //             {   
   //                 tempData.skillId = tempVSkillInfo[i]->CharSkillList[j].id;
   //                 tempData.skillLevel = tempVSkillInfo[i]->CharSkillList[j].lv;
   //                 tempVSkillData.push_back(tempData);
   //             }
   //         }
   //     }
   // }
    //-----------------------------------------------------------------------
    //void SSkillUseManager::addSkill(std::vector<SkillData> skillList)
    //{
    //    SkillObject* skillObject = NULL;

    //    for(UInt i = 0; i < skillList.size(); ++i)
    //    {
    //        skillObject = addOrGetSkill(skillList[i].skillId);
    //        if(skillObject)
    //        {
    //            skillObject->setSkillLevel(skillList[i].skillLevel);
    //        }
    //    }
    //}
    //-----------------------------------------------------------------------
    SCharacter* SSkillUseManager::getSCharacter()
    {
        return dynamic_cast<SCharacter*>( SkillUseManager::getCharacter() );
    }

	//-----------------------------------------------------------------------
}