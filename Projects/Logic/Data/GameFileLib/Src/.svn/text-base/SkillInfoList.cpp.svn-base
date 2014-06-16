//******************************************************************************************
#include "stdafx.h"
#include "SkillInfoList.h"
#include "ShortRangeGeneralAttackSkillTemplate.h"
#include "LongRangeGeneralAttackSkillTemplate.h"
#include "PassivenessSkillTemplate.h"
#include "SingleTargetSkillTemplate.h"
#include "SingleEmitterSkillTemplate.h"
#include "SelfAreaSkillTemplate.h"
#include "TargetPosAreaSkillTemplate.h"
#include "ParabolaAreaSkillTemplate.h"
#include "GoUpAndDownSkillTemplate.h"
#include "LongRangeAuxiliarySkillTemplate.h"
#include "SkillBaseInfo.h"
//******************************************************************************************
namespace MG
{

	SkillInfoList::SkillInfoList()
	{

	}
	//-------------------------------------------------------------------------------------------
	SkillInfoList::~SkillInfoList()
	{
		clear();
	}

	//-------------------------------------------------------------------------------------------
	// MG_CN_MODIFY
	Bool SkillInfoList::load(Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/)
	{
		CsvReader csvreader;
		SkillBaseInfo* skillInfo = NULL;
		// MG_CN_MODIFY
		if(!csvreader.create(fileName, packManager))
		{
			return false;
		}

		CsvData* csvdata = NULL;
		Int rowCount = csvreader.count();
		for(Int i = 0; i < rowCount; ++i)
		{
			csvdata = csvreader.findValue(i);
			if(!csvdata)
			{
				continue;
			}
			SkillInfo* tempInfo = MG_NEW SkillInfo;

			MGStrOp::toU64(csvdata->mData[SKILLID].c_str(),	tempInfo->skillId);			
			UInt tempSkillType; 
			MGStrOp::toU32(csvdata->mData[SKILLTYPE].c_str(), tempSkillType);
			tempInfo->skillType = (SkillType)tempSkillType;
			MGStrOp::toU32(csvdata->mData[SKILLLISTID].c_str(), tempInfo->skillListId);
			MGStrOp::toU32(csvdata->mData[SKILLSHOWTYPE].c_str(), (U32&)tempInfo->skillShowType);


			if (getSkillInfo(tempInfo->skillId))
			{
				DYNAMIC_ASSERT(false);
				MG_SAFE_DELETE(tempInfo);
				continue;
			}
			
			switch(tempSkillType)
			{
			case SKT_SHORTRANGEGENERAL:
				skillInfo = (InitiativeSkillBasicInfo*)ShortRangeGeneralAttackSkillTemplate::getInstance().getShortRangeGeneralAttackSkillInfo(tempInfo->skillListId);
				break;
			case SKT_LONGRANGEGENERAL:
				skillInfo= (LongRangeGeneralAttackSkillInfo*)LongRangeGeneralAttackSkillTemplate::getInstance().getLongRangeGeneralAttackSkillInfo(tempInfo->skillListId);
				break;
			case SKT_SINGLETARGET:
				skillInfo = (SingleTargetSkillInfo*)SingleTargetSkillTemplate::getInstance().getSingleTargetSkillInfo(tempInfo->skillListId);
				break;
			case SKT_PASSIVENESS:
				skillInfo =  (PassivenessSkillInfo*)PassivenessSkillTemplate::getInstance().getPassivenessSkillInfo(tempInfo->skillListId);
				break;
			case SKT_SINGLEEMITTER:
				skillInfo = (SingleEmitterSkillInfo*)SingleEmitterSkillTemplate::getInstance().getSingleEmitterSkillInfo(tempInfo->skillListId);
				break;
			case SKT_SELFAREA:
				skillInfo =  (SelfAreaSkillInfo*)SelfAreaSkillTemplate::getInstance().getSelfAreaSkillInfo(tempInfo->skillListId);
				break;
			case SKT_TARGETPOSAREA:
				skillInfo =  (TargetPosAreaSkillInfo*)TargetPosAreaSkillTemplate::getInstance().getTargetPosAreaSkillInfo(tempInfo->skillListId);
				break;
			case SKT_PARABOLAAREA:
				skillInfo =  (ParabolaAreaSkillInfo*)ParabolaAreaSkillTemplate::getInstance().getParabolaAreaSkillInfo(tempInfo->skillListId);
				break;
			case SKT_GOUPANDDOWN:
				skillInfo =  (GoUpAndDownSkillInfo*)GoUpAndDownSkillTemplate::getInstance().getGoUpAndDownSkillInfo(tempInfo->skillListId);
				break;
			case SKT_LONGRANGEAUXILIARY:
				skillInfo =  (LongRangeAuxiliarySkillInfo*)LongRangeAuxiliarySkillTemplate::getInstance().getLongRangeAuxiliarySkillInfo(tempInfo->skillListId);
				break;
			}

			tempInfo->skillInfo = skillInfo;
			mSkillInfoList[tempInfo->skillId] = tempInfo;
		}

		return true;
	}
	//-------------------------------------------------------------------------------------------
	const SkillInfo* SkillInfoList::getSkillInfo( IdType id )
	{
		std::map<IdType, SkillInfo*>::iterator it = mSkillInfoList.find(id);
		if (it != mSkillInfoList.end())
		{
			return it->second;
		}

		return NULL;
	}

	//-------------------------------------------------------------------------------------------
	const SkillInfo* SkillInfoList::getSkillInfoByIndex( UInt index )
	{
		UInt skillInfoIndex = 0;
		for(std::map<IdType, SkillInfo*>::iterator it = mSkillInfoList.begin(); it != mSkillInfoList.end(); ++it)
		{
			if(index == skillInfoIndex)
			{
				return it->second;
			}
		
			skillInfoIndex++;
		}

		return NULL;
	}
	
	//-------------------------------------------------------------------------------------------
	UInt SkillInfoList::getSkillInfoNum()
	{
		return mSkillInfoList.size();
	}
	//-------------------------------------------------------------------------------------------
	void SkillInfoList::clear()
	{
		std::map<IdType, SkillInfo*>::iterator it = mSkillInfoList.begin();
		for (; it != mSkillInfoList.end(); it++)
		{
			MG_SAFE_DELETE(it->second);
		}

		mSkillInfoList.clear();
	}
	//-------------------------------------------------------------------------------------------

}