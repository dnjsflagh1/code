//******************************************************************************************
#include "stdafx.h"
#include "ShortRangeGeneralAttackSkillTemplate.h"
//******************************************************************************************
namespace MG
{
	enum 
	{
		SKILLTYPEID,
		NOTES,
		SKILLTYPEGROUPID,
		NAME,				
		TEXT,				
		KINDNAME,			
		ARTICONID,
		ACTION1,		
		ARTEFFECTID1,	
		AUDIORESID1,	
		ACTION2,		
		ARTEFFECTID2,	
		AUDIORESID2,	
		ACTION3,	
		ARTEFFECTID3,	
		AUDIORESID3,
		ACTION4,		
		ARTEFFECTID4,	
		AUDIORESID4,		
		ATTACKFRONTTIME,		
		ATTACKBEHINDTIME,	
		PUBLICTIMEPIECEID,	
		PUBLICTIMEPIECEDELAY,
		CHARACTERJUDGEID1,
		CHARACTERJUDGEID2,
		RANGE,				
		MAXRANGE,			
		ATTACKTYPE,			
		FORMULAPARAMETERID,	
		HATE,
	};

	ShortRangeGeneralAttackSkillTemplate::ShortRangeGeneralAttackSkillTemplate()
	{

	}
	//-------------------------------------------------------------------------------------------
	ShortRangeGeneralAttackSkillTemplate::~ShortRangeGeneralAttackSkillTemplate()
	{
		clear();
	}
	//-------------------------------------------------------------------------------------------
	// MG_CN_MODIFY
	Bool ShortRangeGeneralAttackSkillTemplate::load(Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/)
	{
		CsvReader csvreader;
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

			ShortRangeGeneralAttackSkillInfo* tempInfo = MG_NEW ShortRangeGeneralAttackSkillInfo;

			MGStrOp::toU32(csvdata->mData[SKILLTYPEID].c_str(),	tempInfo->skillTypeId);
			MGStrOp::toU32(csvdata->mData[SKILLTYPEGROUPID].c_str(), tempInfo->skillTypeGroupId);
			tempInfo->name = csvdata->mData[NAME];
			tempInfo->text = csvdata->mData[TEXT];
			tempInfo->kindName = csvdata->mData[KINDNAME];
			MGStrOp::toU32(csvdata->mData[ARTICONID].c_str(), tempInfo->artIconId);

			for(UInt i = 0; i < 3; ++i)
			{
				tempInfo->skillExpression[i].action = csvdata->mData[ACTION1 + 3 * i];
				MGStrOp::toU32(csvdata->mData[ACTION1 + 3 * i + 1].c_str(), tempInfo->skillExpression[i].artEffectId);
				MGStrOp::toU32(csvdata->mData[ACTION1 + 3 * i + 2].c_str(), tempInfo->skillExpression[i].audioResId);
			}

			MGStrOp::toFlt(csvdata->mData[ATTACKFRONTTIME].c_str(), tempInfo->attackFrontTime);
			tempInfo->attackFrontTime /= 10;
			MGStrOp::toFlt(csvdata->mData[ATTACKBEHINDTIME].c_str(), tempInfo->attackBehindTime);
			tempInfo->attackBehindTime /= 10;
			MGStrOp::toU32(csvdata->mData[PUBLICTIMEPIECEID].c_str(), tempInfo->publicTimepieceId);
			MGStrOp::toU32(csvdata->mData[PUBLICTIMEPIECEDELAY].c_str(), tempInfo->publicTimepieceDelay);
			tempInfo->publicTimepieceDelay *= 100;
			MGStrOp::toU32(csvdata->mData[CHARACTERJUDGEID1].c_str(), tempInfo->characterJudgeId1);
			MGStrOp::toU32(csvdata->mData[CHARACTERJUDGEID2].c_str(), tempInfo->characterJudgeId2);
			MGStrOp::toFlt(csvdata->mData[RANGE].c_str(), tempInfo->range);
			tempInfo->range /= 10; 
			MGStrOp::toFlt(csvdata->mData[MAXRANGE].c_str(), tempInfo->maxRange);
			tempInfo->maxRange /= 10;
			UInt tempAttackType; 
			MGStrOp::toU32(csvdata->mData[ATTACKTYPE].c_str(), tempAttackType);
			tempInfo->attackType = (AttackType)tempAttackType;
			MGStrOp::toU32(csvdata->mData[FORMULAPARAMETERID].c_str(), tempInfo->formulaParameterId);
			MGStrOp::toU32(csvdata->mData[HATE].c_str(), tempInfo->hate);

			if (getShortRangeGeneralAttackSkillInfo(tempInfo->skillTypeId))
			{
				DYNAMIC_ASSERT(false);
				MG_SAFE_DELETE(tempInfo);
				continue;
			}

			mShortRangeGeneralAttackSkillInfoList[tempInfo->skillTypeId] = tempInfo;
		}

		return true;
	}
	//-------------------------------------------------------------------------------------------
	const ShortRangeGeneralAttackSkillInfo* ShortRangeGeneralAttackSkillTemplate::getShortRangeGeneralAttackSkillInfo( UInt id )
	{
		std::map<U32, ShortRangeGeneralAttackSkillInfo*>::iterator it = mShortRangeGeneralAttackSkillInfoList.find(id);
		if (it != mShortRangeGeneralAttackSkillInfoList.end())
		{
			return it->second;
		}
		return NULL;
	}
	//-------------------------------------------------------------------------------------------
	const ShortRangeGeneralAttackSkillInfo*	ShortRangeGeneralAttackSkillTemplate::getShortRangeGeneralAttackSkillInfoByIndex( UInt index )
	{
		UInt ShortRangeGeneralAttackSkillInfoIndex = 0;

		for(std::map<U32, ShortRangeGeneralAttackSkillInfo*>::iterator it = mShortRangeGeneralAttackSkillInfoList.begin(); it != mShortRangeGeneralAttackSkillInfoList.end(); ++it)
		{
			if(ShortRangeGeneralAttackSkillInfoIndex == index)
			{
				return it->second;
			}

			ShortRangeGeneralAttackSkillInfoIndex++;
		}

		return NULL;
	}
	//-------------------------------------------------------------------------------------------
	UInt ShortRangeGeneralAttackSkillTemplate::getShortRangeGeneralAttackSkillInfoNum()
	{
		return mShortRangeGeneralAttackSkillInfoList.size();
	}
	//-------------------------------------------------------------------------------------------
	void ShortRangeGeneralAttackSkillTemplate::clear()
	{
		std::map<U32, ShortRangeGeneralAttackSkillInfo*>::iterator it = mShortRangeGeneralAttackSkillInfoList.begin();
		for (; it != mShortRangeGeneralAttackSkillInfoList.end(); it++)
		{
			MG_SAFE_DELETE(it->second);
		}
		mShortRangeGeneralAttackSkillInfoList.clear();
	}
	//-------------------------------------------------------------------------------------------

}