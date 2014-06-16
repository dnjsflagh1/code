//******************************************************************************************
#include "stdafx.h"
#include "SkillLearn.h"
//******************************************************************************************
namespace MG
{

	SkillLearn::SkillLearn()
	{

	}
	//-------------------------------------------------------------------------------------------
	SkillLearn::~SkillLearn()
	{
		clear();
	}

	//-------------------------------------------------------------------------------------------
	// MG_CN_MODIFY
	Bool SkillLearn::load(Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/)
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
			SkillLearnInfo* tempInfo = MG_NEW SkillLearnInfo;

			MGStrOp::toU32(csvdata->mData[SKILLLEARNID].c_str(), tempInfo->skillLearnId);			
			MGStrOp::toU32(csvdata->mData[CLANJUDGEID].c_str(), tempInfo->clanJudgeid);
			MGStrOp::toU32(csvdata->mData[CHARACTERJUDGEID].c_str(), tempInfo->characterJudgeid);
			MGStrOp::toU32(csvdata->mData[SKILLFRONTID].c_str(), tempInfo->skillFrontId);	
			MGStrOp::toU32(csvdata->mData[ITEMID].c_str(),	tempInfo->itemId);	
			MGStrOp::toU32(csvdata->mData[ITEMNUM].c_str(),	tempInfo->itemNum);	
			MGStrOp::toU32(csvdata->mData[DELITEMID].c_str(), tempInfo->delItemId);
			tempInfo->artAction = csvdata->mData[ARTACTION].c_str();
			MGStrOp::toU32(csvdata->mData[ARTEFFECTRESID].c_str(),	tempInfo->artEffectResId);	
			MGStrOp::toU32(csvdata->mData[AUDIORESID].c_str(),	tempInfo->audioResId);	


			if (getSkillLearnInfo(tempInfo->skillLearnId))
			{
				DYNAMIC_ASSERT(false);
				MG_SAFE_DELETE(tempInfo);
				continue;
			}

			mSkillLearnInfoList[tempInfo->skillLearnId] = tempInfo;
		}

		return true;
	}
	//-------------------------------------------------------------------------------------------
	const SkillLearnInfo* SkillLearn::getSkillLearnInfo( UInt id )
	{
		std::map<U32, SkillLearnInfo*>::iterator it = mSkillLearnInfoList.find(id);
		if (it != mSkillLearnInfoList.end())
		{
			return it->second;
		}

		return NULL;
	}
	//-------------------------------------------------------------------------------------------
	void SkillLearn::clear()
	{
		std::map<U32, SkillLearnInfo*>::iterator it = mSkillLearnInfoList.begin();
		for (; it != mSkillLearnInfoList.end(); it++)
		{
			MG_SAFE_DELETE(it->second);
		}

		mSkillLearnInfoList.clear();
	}
	//-------------------------------------------------------------------------------------------

}