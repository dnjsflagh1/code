//******************************************************************************************
#include "stdafx.h"
#include "GoUpAndDownSkillTemplate.h"
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
		//ACTION3,	
		//ARTEFFECTID3,	
		//AUDIORESID3,
		PUBLICTIMEPIECEID,	
		PUBLICTIMEPIECEDELAY,
		CHARACTERJUDGEID1,
		RANGE,				
		MAXRANGE,
	};

	GoUpAndDownSkillTemplate::GoUpAndDownSkillTemplate()
	{

	}
	//-------------------------------------------------------------------------------------------
	GoUpAndDownSkillTemplate::~GoUpAndDownSkillTemplate()
	{
		clear();
	}

	//-------------------------------------------------------------------------------------------
	// MG_CN_MODIFY
	Bool GoUpAndDownSkillTemplate::load(Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/)
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

			GoUpAndDownSkillInfo* tempInfo = MG_NEW GoUpAndDownSkillInfo;

			MGStrOp::toU32(csvdata->mData[SKILLTYPEID].c_str(),	tempInfo->skillTypeId);
			MGStrOp::toU32(csvdata->mData[SKILLTYPEGROUPID].c_str(), tempInfo->skillTypeGroupId);
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

			MGStrOp::toU32(csvdata->mData[PUBLICTIMEPIECEID].c_str(), tempInfo->publicTimepieceId);
			MGStrOp::toU32(csvdata->mData[PUBLICTIMEPIECEDELAY].c_str(), tempInfo->publicTimepieceDelay);
			tempInfo->publicTimepieceDelay *= 100;
			MGStrOp::toU32(csvdata->mData[CHARACTERJUDGEID1].c_str(), tempInfo->characterJudgeId1);

			MGStrOp::toFlt(csvdata->mData[RANGE].c_str(), tempInfo->range);
			tempInfo->range /= 10;

			MGStrOp::toFlt(csvdata->mData[MAXRANGE].c_str(), tempInfo->maxRange);
			tempInfo->maxRange /= 10;

			if (getGoUpAndDownSkillInfo(tempInfo->skillTypeId))
			{
				DYNAMIC_ASSERT(false);
				MG_SAFE_DELETE(tempInfo);
				continue;
			}

			mGoUpAndDownSkillInfoList[tempInfo->skillTypeId] = tempInfo;
		}

		return true;
	}
	//-------------------------------------------------------------------------------------------
	const GoUpAndDownSkillInfo* GoUpAndDownSkillTemplate::getGoUpAndDownSkillInfo( UInt id )
	{
		std::map<U32, GoUpAndDownSkillInfo*>::iterator it = mGoUpAndDownSkillInfoList.find(id);
		if (it != mGoUpAndDownSkillInfoList.end())
		{
			return it->second;
		}
		return NULL;
	}
	//-------------------------------------------------------------------------------------------
	void GoUpAndDownSkillTemplate::clear()
	{
		std::map<U32, GoUpAndDownSkillInfo*>::iterator it = mGoUpAndDownSkillInfoList.begin();
		for (; it != mGoUpAndDownSkillInfoList.end(); it++)
		{
			MG_SAFE_DELETE(it->second);
		}
		mGoUpAndDownSkillInfoList.clear();
	}
	//-------------------------------------------------------------------------------------------

}