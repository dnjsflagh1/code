//******************************************************************************************
#include "stdafx.h"
#include "PassivenessSkillTemplate.h"
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
		ARTEFFECTID,	
		ABILITYAPPENDID,	
	};

	PassivenessSkillTemplate::PassivenessSkillTemplate()
	{

	}
	//-------------------------------------------------------------------------------------------
	PassivenessSkillTemplate::~PassivenessSkillTemplate()
	{
		clear();
	}
	//-------------------------------------------------------------------------------------------
	// MG_CN_MODIFY
	Bool PassivenessSkillTemplate::load(Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/)
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

			PassivenessSkillInfo* tempInfo = MG_NEW PassivenessSkillInfo;

			MGStrOp::toU32(csvdata->mData[SKILLTYPEID].c_str(),	tempInfo->skillTypeId);
			MGStrOp::toU32(csvdata->mData[SKILLTYPEGROUPID].c_str(), tempInfo->skillTypeGroupId);
			MGStrOp::toU32(csvdata->mData[SKILLLEVEL].c_str(), tempInfo->skillLevel);
			tempInfo->name = csvdata->mData[NAME];
			tempInfo->text = csvdata->mData[TEXT];
			tempInfo->kindName = csvdata->mData[KINDNAME];
			MGStrOp::toU32(csvdata->mData[ARTICONID].c_str(), tempInfo->artIconId);
			MGStrOp::toU32(csvdata->mData[ARTEFFECTID].c_str(), tempInfo->artEffectId);
			MGStrOp::toU32(csvdata->mData[ABILITYAPPENDID].c_str(), tempInfo->abilityAppendId);

			if (getPassivenessSkillInfo(tempInfo->skillTypeId))
			{
				DYNAMIC_ASSERT(false);
				MG_SAFE_DELETE(tempInfo);
				continue;
			}

			mPassivenessSkillInfoList[tempInfo->skillTypeId] = tempInfo;
		}

		return true;
	}
	//-------------------------------------------------------------------------------------------
	const PassivenessSkillInfo* PassivenessSkillTemplate::getPassivenessSkillInfo( UInt id )
	{
		std::map<U32, PassivenessSkillInfo*>::iterator it = mPassivenessSkillInfoList.find(id);
		if (it != mPassivenessSkillInfoList.end())
		{
			return it->second;
		}
		return NULL;
	}
	//-------------------------------------------------------------------------------------------
	void PassivenessSkillTemplate::clear()
	{
		std::map<U32, PassivenessSkillInfo*>::iterator it = mPassivenessSkillInfoList.begin();
		for (; it != mPassivenessSkillInfoList.end(); it++)
		{
			MG_SAFE_DELETE(it->second);
		}
		mPassivenessSkillInfoList.clear();
	}
	//-------------------------------------------------------------------------------------------

}