//******************************************************************************************
#include "stdafx.h"
#include "LongRangeAuxiliarySkillTemplate.h"
//******************************************************************************************
namespace MG
{

	enum 
	{
		SKILLTYPEID,
		NOTES,
		SKILLTYPEGROUPID,
		SKILLLEVEL,
		NAME,				
		TEXT,				
		KINDNAME,			
		ARTICONID,
		ACTIONTIME,
		ACTION1,		
		ARTEFFECTID1,	
		AUDIORESID1,	
		ACTION2,		
		ARTEFFECTID2,	
		AUDIORESID2,	
		ACTION3,	
		ARTEFFECTID3,	
		AUDIORESID3,
		ATTACKFRONTTIME,		
		ATTACKBEHINDTIME,	
		PUBLICTIMEPIECEID,	
		PUBLICTIMEPIECEDELAY,
		OWNERTIMEPIECEID,
		OWNERTIMEPIECEDELAY,
		RESETTIMEPIECEID,
		RESETTIMEPIECEGROUPID,
		CHARACTERJUDGEID1,
		CHARACTERJUDGEID2,
		RANGE,				
		MAXRANGE,
		SPENDTYPE,
		FORMULAPARAMETERID2,
		DAMAGETYPE,			
		FORMULAPARAMETERID1,
		RANDOMSTATE,
		STATEID,
		STATENUM,
		HATE,
	};

	LongRangeAuxiliarySkillTemplate::LongRangeAuxiliarySkillTemplate()
	{

	}
	//-------------------------------------------------------------------------------------------
	LongRangeAuxiliarySkillTemplate::~LongRangeAuxiliarySkillTemplate()
	{
		clear();
	}

	//-------------------------------------------------------------------------------------------
	// MG_CN_MODIFY
	Bool LongRangeAuxiliarySkillTemplate::load(Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/)
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
			LongRangeAuxiliarySkillInfo* tempInfo = MG_NEW LongRangeAuxiliarySkillInfo;

			MGStrOp::toU32(csvdata->mData[SKILLTYPEID].c_str(),	tempInfo->skillTypeId);
			MGStrOp::toU32(csvdata->mData[SKILLTYPEGROUPID].c_str(), tempInfo->skillTypeGroupId);
			MGStrOp::toU32(csvdata->mData[SKILLLEVEL].c_str(), tempInfo->skillLevel);
			tempInfo->name = csvdata->mData[NAME];
			tempInfo->text = csvdata->mData[TEXT];
			tempInfo->kindName = csvdata->mData[KINDNAME];
			MGStrOp::toU32(csvdata->mData[ARTICONID].c_str(), tempInfo->artIconId);
			MGStrOp::toFlt(csvdata->mData[ACTIONTIME].c_str(), tempInfo->actionTime);
			tempInfo->actionTime /= 10;

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
			MGStrOp::toU32(csvdata->mData[OWNERTIMEPIECEID].c_str(), tempInfo->ownerTimepieceId);
			MGStrOp::toU32(csvdata->mData[OWNERTIMEPIECEDELAY].c_str(), tempInfo->ownerTimepieceDelay);
			tempInfo->ownerTimepieceDelay *= 100;
			MGStrOp::toU32(csvdata->mData[RESETTIMEPIECEID].c_str(), tempInfo->resetTimepieceId);
			MGStrOp::toU32(csvdata->mData[RESETTIMEPIECEGROUPID].c_str(), tempInfo->resetTimepieceGroupId);
			MGStrOp::toU32(csvdata->mData[CHARACTERJUDGEID1].c_str(), tempInfo->characterJudgeId1);
			MGStrOp::toU32(csvdata->mData[CHARACTERJUDGEID2].c_str(), tempInfo->characterJudgeId2);
			MGStrOp::toFlt(csvdata->mData[RANGE].c_str(), tempInfo->range);
			tempInfo->range /= 10;
			MGStrOp::toFlt(csvdata->mData[MAXRANGE].c_str(), tempInfo->maxRange);
			tempInfo->maxRange /= 10;
			UInt tempDamageType; 
			MGStrOp::toU32(csvdata->mData[DAMAGETYPE].c_str(), tempDamageType);
			tempInfo->damageType = (DamageType)tempDamageType;
			MGStrOp::toU32(csvdata->mData[FORMULAPARAMETERID2].c_str(), tempInfo->formulaParameterId2);
			MGStrOp::toU32(csvdata->mData[FORMULAPARAMETERID1].c_str(), tempInfo->formulaParameterId);
			MGStrOp::toU32(csvdata->mData[RANDOMSTATE].c_str(), tempInfo->randomState);
			MGStrOp::toU32(csvdata->mData[STATEID].c_str(), tempInfo->stateId);
			MGStrOp::toU32(csvdata->mData[STATENUM].c_str(), tempInfo->stateNum);
			MGStrOp::toU32(csvdata->mData[HATE].c_str(), tempInfo->hate);

			if (getLongRangeAuxiliarySkillInfo(tempInfo->skillTypeId))
			{
				DYNAMIC_ASSERT(false);
				MG_SAFE_DELETE(tempInfo);
				continue;
			}

			mLongRangeAuxiliarySkillInfoList[tempInfo->skillTypeId] = tempInfo;
		}

		return true;
	}
	//-------------------------------------------------------------------------------------------
	const LongRangeAuxiliarySkillInfo* LongRangeAuxiliarySkillTemplate::getLongRangeAuxiliarySkillInfo( UInt id )
	{
		std::map<U32, LongRangeAuxiliarySkillInfo*>::iterator it = mLongRangeAuxiliarySkillInfoList.find(id);
		if (it != mLongRangeAuxiliarySkillInfoList.end())
		{
			return it->second;
		}

		return NULL;
	}
	//-------------------------------------------------------------------------------------------
	void LongRangeAuxiliarySkillTemplate::clear()
	{
		std::map<U32, LongRangeAuxiliarySkillInfo*>::iterator it = mLongRangeAuxiliarySkillInfoList.begin();
		for (; it != mLongRangeAuxiliarySkillInfoList.end(); it++)
		{
			MG_SAFE_DELETE(it->second);
		}

		mLongRangeAuxiliarySkillInfoList.clear();
	}
	//-------------------------------------------------------------------------------------------

}