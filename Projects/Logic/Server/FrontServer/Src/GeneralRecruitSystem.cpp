/******************************************************************************/
#include "stdafx.h"
#include "GeneralRecruitSystem.h"
#include "AttributeInit.h"
#include "CharacterList.h"
#include "GeneralRandomCsv.h"
#include "GeneralRecruitCsv.h"
#include "CharacterRandNameCsv.h"
#include "CalendarInfo.h"
#include "AttributeFormula.h"
/******************************************************************************/

/******************************************************************************/
namespace MG
{
	//-----------------------------------------------------------------------------
	GeneralRecruitSystem::GeneralRecruitSystem()
		:mLastGeneralRecruitId(0)
	{
		for (Int i=0; i<RECRUIT_POSITION_MAX; ++i)
		{
			CharAttrInfo* newInfo = MG_NEW CharAttrInfo();
			RECRUIT_POSITION index = (RECRUIT_POSITION)i;
			mCharAttrList[index] = newInfo;
		}
		
	}

	GeneralRecruitSystem::~GeneralRecruitSystem()
	{
		for (Int i=0; i<RECRUIT_POSITION_MAX; ++i)
		{
			RECRUIT_POSITION index = (RECRUIT_POSITION)i;
			CharAttrInfo* newInfo = mCharAttrList[index];
			MG_SAFE_DELETE(newInfo);
		}

		mCharAttrList.clear();
	}

	void GeneralRecruitSystem::reFresh(U32 GeneralRecruitId)
	{
		GeneralRecruitCsvInfo* generalRecruitCsvInfo = GeneralRecruitCsv::getInstance().getInfoById(GeneralRecruitId);
		if (NULL == generalRecruitCsvInfo)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		//保存上次刷新的id
		setLastGeneralRecruitId(GeneralRecruitId);

		for (Int i=0; i<RECRUIT_POSITION_MAX; ++i)
		{
			//开始随机武将
			U32 GeneralGroupId = generalRecruitCsvInfo->GeneralGroupID[i];
			RECRUIT_POSITION index = (RECRUIT_POSITION)i;
			setRandomGeneral(index, GeneralGroupId);
		}
			
		int kk = 0;
	}

	void GeneralRecruitSystem::setRandomGeneral(RECRUIT_POSITION index, U32 GeneralGroupId)
	{
		U32 randNum = MGRandom::getInstance().rand_ab_One(0, 100000);

		const GeneralRandomCsvInfo* result = NULL;
		std::vector<const GeneralRandomCsvInfo*>* randomList = GeneralRandomCsv::getInstance().getRandomListByGeneralGroupId(GeneralGroupId);
		for (std::vector<const GeneralRandomCsvInfo*>::iterator iter = randomList->begin(); iter != randomList->end(); ++iter)
		{
			const GeneralRandomCsvInfo* temp = *iter;
			if (temp->GeneralRandomNum >= randNum)
			{
				if (NULL == result)
				{
					result = *iter;
				}

				if (NULL != result && result->GeneralRandomNum > temp->GeneralRandomNum)
				{
					result = *iter;
				}
			}
		}

		//肯定能找到某个随机武将
		DYNAMIC_ASSERT(NULL != result);
		setRandomAttr(index, result);
	}

	void GeneralRecruitSystem::setRandomAttr(RECRUIT_POSITION index, const GeneralRandomCsvInfo* generalRandomInfo)
	{
		DYNAMIC_ASSERT(generalRandomInfo->LifeSpanRandom >= 0);
		DYNAMIC_ASSERT(index >= 0 && index < RECRUIT_POSITION_MAX);

		const CharacterTempInfo* characterInfo = CharacterTemplate::getInstance().getCharacterTempInfo(generalRandomInfo->CharacterTemplateId);
		DYNAMIC_ASSERT(NULL != characterInfo);

		const AttributeInitInfo* attribute1 = AttributeInit::getInstance().getAttributeInitInfo(generalRandomInfo->AbilityInit1);
		const AttributeInitInfo* attribute2 = AttributeInit::getInstance().getAttributeInitInfo(generalRandomInfo->AbilityInit2);
		DYNAMIC_ASSERT(NULL != attribute1 && NULL != attribute2);

		CharAttrInfo* attrInfo = NULL;
		std::map<RECRUIT_POSITION, CharAttrInfo*>::iterator iter = mCharAttrList.find(index);
		if (iter != mCharAttrList.end())
		{
			attrInfo = iter->second;
		}
		else
		{
			DYNAMIC_ASSERT(0);
		}

		CharacterTempInfo* charTempInfo = CharacterTemplate::getInstance().getCharacterTempInfo(generalRandomInfo->CharacterTemplateId);
		DYNAMIC_ASSERT(NULL != charTempInfo);

		Str16 randMing			= CharacterRandNameCsv::getInstance().getRandMingBySexual(charTempInfo->getGenrealGenderType());
		Str16 randCommonXing	= CharacterRandNameCsv::getInstance().getRandCommonXing();
		DYNAMIC_ASSERT(randMing.empty() == false && randCommonXing.empty() == false);

		//填充模版ID,等
		Int LifeSpanRandom = 0;
		if (generalRandomInfo->LifeSpanRandom > 0)
		{
			LifeSpanRandom = MGRandom::getInstance().rand_ab_One(0, generalRandomInfo->LifeSpanRandom);
		}

		DYNAMIC_ASSERT(generalRandomInfo->CharacterTemplateId == characterInfo->getCharacterTempId());
		attrInfo->charTemplateId			= 	generalRandomInfo->CharacterTemplateId;
		attrInfo->charTempInfo				= 	charTempInfo;
		attrInfo->charAttrAppendId			=	generalRandomInfo->AbilityInit1;
		attrInfo->charAttrAppendLvlAddId	=	generalRandomInfo->AbilityInit2;

		const CalendarInfo* pCalendarInfo = CalendarInfos::getInstance().getCalendarInfo(1);
		attrInfo->age						=	setGenrealAge( pCalendarInfo, characterInfo->getGenrealAge() );
		attrInfo->lifeSpanBase				=	setGenrealAge( pCalendarInfo, characterInfo->getGenrealMinLifeSpan() + LifeSpanRandom );
		
		//获取随机名字 【随机名字系统】
		attrInfo->name_xing			= randCommonXing;
		attrInfo->name_ming			= randMing;
		attrInfo->name				= randCommonXing + randMing;

		//填充随机属性1
		for (Int i=0; i<DB_RECORD_ATTR_NUM; ++i)
		{
			U32 val = (U32)attribute1->AppendAttrList[i].value;
			if (val == 0)
			{
				continue;
			}

			DYNAMIC_ASSERT(val >= 1);
			attrInfo->charAttrRand[i] = MGRandom::getInstance().rand_ab_One(1, val);
		}

		//填充随机属性2
		for (Int i=0; i<DB_RECORD_ATTR_NUM; ++i)
		{
			U32 val = (U32)attribute2->AppendAttrList[i].value;
			if (val == 0)
			{
				continue;
			}

			DYNAMIC_ASSERT(val >= 1);
			attrInfo->charAttrRandAdd[i] = MGRandom::getInstance().rand_ab_One(1, val);
		}
		int kk = 0;
	}

	U32 GeneralRecruitSystem::getLastGeneralRecruitId() const
	{
		return mLastGeneralRecruitId;
	}

	void GeneralRecruitSystem::setLastGeneralRecruitId(U32 id)
	{
		mLastGeneralRecruitId = id;
	}

	std::map<RECRUIT_POSITION, CharAttrInfo*>* GeneralRecruitSystem::getCharAttrList()
	{
		return &mCharAttrList;
	}

	CharAttrInfo* GeneralRecruitSystem::getCharAttrInfoByIndex(RECRUIT_POSITION index)
	{
		std::map<RECRUIT_POSITION, CharAttrInfo*>::iterator iter = mCharAttrList.find(index);
		if (iter != mCharAttrList.end())
		{
			return iter->second;
		}

		return NULL;
	}

	U32 GeneralRecruitSystem::setGenrealAge( const CalendarInfo* pCalendarInfo, U32 age )
	{
		return AttributeFormula::getInstance().calValueCharacterAge(
				age,
				pCalendarInfo->year,
				pCalendarInfo->day
			);
	}
}