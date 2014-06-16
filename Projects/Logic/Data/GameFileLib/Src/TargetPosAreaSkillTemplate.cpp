//******************************************************************************************
#include "stdafx.h"
#include "TargetPosAreaSkillTemplate.h"
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
		//ACTIONTIME,
		//ACTION1,		
		//ARTEFFECTID1,	
		//AUDIORESID1,	
		ACTION2,		
		ARTEFFECTID2,	
		AUDIORESID2,	
		ACTION3,	
		ARTEFFECTID3,	
		AUDIORESID3,
		POINTEFFECTID,
		POINTSKILLEFFECTID,
		POINTAUDIOID,
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
		SKILLRADIUO,
		ATTACKNUM,
		SHARETYPE,
		SKILLCASTNUM,
		SKILLCASTINTERVAL,
		SPENDTYPE,
		FORMULAPARAMETERID2,	
		ATTACKTYPE,	
		FORMULAPARAMETERID1,
		DAMAGETYPE,
		RANDOMSTATE,
		STATEID,
		STATENUM,
		HATE,
	};

	TargetPosAreaSkillTemplate::TargetPosAreaSkillTemplate()
	{

	}
	//-------------------------------------------------------------------------------------------
	TargetPosAreaSkillTemplate::~TargetPosAreaSkillTemplate()
	{
		clear();
	}

	//-------------------------------------------------------------------------------------------
	// MG_CN_MODIFY
	Bool TargetPosAreaSkillTemplate::load(Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/)
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

			TargetPosAreaSkillInfo* tempInfo = MG_NEW TargetPosAreaSkillInfo;

			MGStrOp::toU32(csvdata->mData[SKILLTYPEID].c_str(),	tempInfo->skillTypeId);
			MGStrOp::toU32(csvdata->mData[SKILLTYPEGROUPID].c_str(), tempInfo->skillTypeGroupId);
			MGStrOp::toU32(csvdata->mData[SKILLLEVEL].c_str(), tempInfo->skillLevel);
			tempInfo->name = csvdata->mData[NAME];
			tempInfo->text = csvdata->mData[TEXT];
			tempInfo->kindName = csvdata->mData[KINDNAME];
			MGStrOp::toU32(csvdata->mData[ARTICONID].c_str(), tempInfo->artIconId);
			//MGStrOp::toU32(csvdata->mData[ACTIONTIME].c_str(), tempInfo->actionTime);

			for(UInt i = 0; i < 2; ++i)
			{
				tempInfo->skillExpression[i+1].action = csvdata->mData[ACTION2 + 3 * i];
				MGStrOp::toU32(csvdata->mData[ACTION2 + 3 * i + 1].c_str(), tempInfo->skillExpression[i+1].artEffectId);
				MGStrOp::toU32(csvdata->mData[ACTION2 + 3 * i + 2].c_str(), tempInfo->skillExpression[i+1].audioResId);
			}

			MGStrOp::toU32(csvdata->mData[POINTEFFECTID].c_str(), tempInfo->pointEffectId);
			MGStrOp::toU32(csvdata->mData[POINTSKILLEFFECTID].c_str(), tempInfo->pointSkillEffectId);
			MGStrOp::toU32(csvdata->mData[POINTAUDIOID].c_str(), tempInfo->pointAudioId);
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
			MGStrOp::toFlt(csvdata->mData[SKILLRADIUO].c_str(), tempInfo->skillRadius);
			tempInfo->skillRadius /= 10;
			MGStrOp::toU32(csvdata->mData[ATTACKNUM].c_str(), tempInfo->attackNum);
			UInt tempShareType; 
			MGStrOp::toU32(csvdata->mData[SHARETYPE].c_str(), tempShareType);
			tempInfo->shareType = (ShareType)tempShareType;
			UInt tempSpendType; 
			MGStrOp::toU32(csvdata->mData[SKILLCASTNUM].c_str(), tempInfo->skillCastNum);
			Flt skillCastInterval = 0;
			MGStrOp::toFlt(csvdata->mData[SKILLCASTINTERVAL].c_str(), skillCastInterval);
			tempInfo->skillCastInterval = skillCastInterval / 10;
			MGStrOp::toU32(csvdata->mData[SPENDTYPE].c_str(), tempSpendType);
			tempInfo->spendType = (SpendType)tempSpendType;
			MGStrOp::toU32(csvdata->mData[FORMULAPARAMETERID2].c_str(), tempInfo->formulaParameterId2);
			UInt tempAttackType; 
			MGStrOp::toU32(csvdata->mData[ATTACKTYPE].c_str(), tempAttackType);
			tempInfo->attackType = (AttackType)tempAttackType;
			MGStrOp::toU32(csvdata->mData[FORMULAPARAMETERID1].c_str(), tempInfo->formulaParameterId);
			UInt tempDamageType; 
			MGStrOp::toU32(csvdata->mData[DAMAGETYPE].c_str(), tempDamageType);
			tempInfo->damageType = (DamageType)tempDamageType;
			MGStrOp::toU32(csvdata->mData[RANDOMSTATE].c_str(), tempInfo->randomState);
			MGStrOp::toU32(csvdata->mData[STATEID].c_str(), tempInfo->stateId);
			MGStrOp::toU32(csvdata->mData[STATENUM].c_str(), tempInfo->stateNum);
			MGStrOp::toU32(csvdata->mData[HATE].c_str(), tempInfo->hate);

			if (getTargetPosAreaSkillInfo(tempInfo->skillTypeId))
			{
				DYNAMIC_ASSERT(false);
				MG_SAFE_DELETE(tempInfo);
				continue;
			}

			mTargetPosAreaSkillInfoList[tempInfo->skillTypeId] = tempInfo;
		}

		return true;
	}
	//-------------------------------------------------------------------------------------------
	const TargetPosAreaSkillInfo* TargetPosAreaSkillTemplate::getTargetPosAreaSkillInfo( UInt id )
	{
		std::map<U32, TargetPosAreaSkillInfo*>::iterator it = mTargetPosAreaSkillInfoList.find(id);
		if (it != mTargetPosAreaSkillInfoList.end())
		{
			return it->second;
		}
		return NULL;
	}
	//-------------------------------------------------------------------------------------------
	void TargetPosAreaSkillTemplate::clear()
	{
		std::map<U32, TargetPosAreaSkillInfo*>::iterator it = mTargetPosAreaSkillInfoList.begin();
		for (; it != mTargetPosAreaSkillInfoList.end(); it++)
		{
			MG_SAFE_DELETE(it->second);
		}
		mTargetPosAreaSkillInfoList.clear();
	}
	//-------------------------------------------------------------------------------------------

}