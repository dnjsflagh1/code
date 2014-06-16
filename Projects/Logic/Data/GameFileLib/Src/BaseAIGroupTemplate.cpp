//*****************************************************************************************************************
#include "stdafx.h"
#include "BaseAIGroupTemplate.h"
//*****************************************************************************************************************
namespace MG
{
	enum
	{	
		AIBASEGROUPID,
		NOTES,
		AIBASEID1,
		AIBASEID2,
		AIBASEID3,
		AIBASEID4,
		AIBASEID5,
		AIBASEID6,
		AIBASEID7,
		AIBASEID8,
		AIBASEID9,
		AIBASEID10,
		AIBASEID11,
		AIBASEID12,
		AIBASEID13,
		AIBASEID14,
		AIBASEID15,
		AIBASEID16,
	};

	BaseAIGroupTemplate::BaseAIGroupTemplate()
	{

	}
	//-------------------------------------------------------------------------------------------------

	BaseAIGroupTemplate::~BaseAIGroupTemplate()
	{
		clear();
	}

	//-------------------------------------------------------------------------------------------------
	// MG_CN_MODIFY
	Bool BaseAIGroupTemplate::load( Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/ )
	{
		CsvReader csvreader;
		// MG_CN_MODIFY
		if(!csvreader.create(fileName, packManager))
		{
			return false;
		}

		CsvData* csvdata = NULL;
		Int RowCount = csvreader.count();

		for(int i = 0; i < RowCount; ++i)
		{
			csvdata = csvreader.findValue(i);
			if(!csvdata)
			{
				continue;
			}

			BaseAIGroup* tempGroup = new BaseAIGroup;

			MGStrOp::toU32(csvdata->mData[AIBASEGROUPID].c_str(), tempGroup->aiBaseGroupId);

			UInt aiId = 0;
			BaseAIInfo* baseAIInfo = NULL;

			for(UInt i = AIBASEID1; i < AIBASEID16 + 1; ++i)
			{
				MGStrOp::toU32(csvdata->mData[i].c_str(), aiId);
				if(aiId == 0)
				{
					continue;
				}

				baseAIInfo = (BaseAIInfo*)BaseAITemplate::getInstance().getBaseAIInfo(aiId);
				if(!baseAIInfo)
				{
					continue;
				}

				switch(baseAIInfo->aiBaseType)
				{
				case BAT_REBIRTH:
				case BAT_DISAPPEAR:
				case BAT_EFFECT:
					tempGroup->aiBaseAIInfoList[BAH_ANY][baseAIInfo->aiBaseType] = baseAIInfo;
					break;

				case BAT_RANDOMMOVE:
				case BAT_GUARD:
					tempGroup->aiBaseAIInfoList[BAH_PEACE][baseAIInfo->aiBaseType] = baseAIInfo;
					break;

				case BAT_SEEKHELP:
				case BAT_ESCAPE:
					tempGroup->aiBaseAIInfoList[BAH_STARTFIGHT][baseAIInfo->aiBaseType] = baseAIInfo;
					break;

				case BAT_HATEDETECT:
				case BAT_PURSUE:
				case BAT_KEEPDISTANCE:
				case BAT_SELECTSKILL:
					tempGroup->aiBaseAIInfoList[BAH_FIGHT][baseAIInfo->aiBaseType] = baseAIInfo;
					break;

				case BAT_RETURN:
					tempGroup->aiBaseAIInfoList[BAH_ENDFIGHT][baseAIInfo->aiBaseType] = baseAIInfo;
					break;

				}
			}


			mBaseAIGroupList[tempGroup->aiBaseGroupId] = tempGroup;
		}

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	void BaseAIGroupTemplate::clear()
	{
		for(std::map<UInt, BaseAIGroup*>::iterator it = mBaseAIGroupList.begin(); it != mBaseAIGroupList.end(); ++it)
		{
			MG_SAFE_DELETE(it->second);
		}

		mBaseAIGroupList.clear();
	}

	//-------------------------------------------------------------------------------------------------
	const BaseAIGroup* BaseAIGroupTemplate::getBaseAIGroup( UInt groupId )
	{
		std::map<UInt, BaseAIGroup*>::iterator it = mBaseAIGroupList.find(groupId);
		if(it == mBaseAIGroupList.end())
		{
			return NULL;
		}

		return it->second;
	}


	//*********************************************************************************************************

}