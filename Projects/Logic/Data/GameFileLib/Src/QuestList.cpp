//******************************************************************************************
#include "stdafx.h"
#include "QuestList.h"
#include "QuestNormalList.h"
//******************************************************************************************
namespace MG
{
	// MG_CN_MODIFY
	MG::Bool ClanQuestInfos::load(Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/)
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
			ClanQuestInfo* tempInfo = MG_NEW ClanQuestInfo;

			MGStrOp::toU32(csvdata->mData[QuestInfoid].c_str(),			tempInfo->id);

			I32 tempType;
			MGStrOp::toI32(csvdata->mData[QuestInfotype].c_str(),		tempType);
			tempInfo->type = (QUEST_TYPE)tempType; 

			MGStrOp::toU32(csvdata->mData[QuestListInfoid].c_str(),		tempInfo->questId);

			if (getQuestInfo(tempInfo->id))
			{
				DYNAMIC_ASSERT(false);
				MG_SAFE_DELETE(tempInfo);
				continue;
			}
			mQuestInfoMap[tempInfo->id] = tempInfo;
		}
		return true;
	}
	//-------------------------------------------------------------------------------------------
	ClanQuestInfo* ClanQuestInfos::getQuestInfo( U32 id )
	{
		std::map<U32, ClanQuestInfo*>::iterator it = mQuestInfoMap.find(id);
		if (it != mQuestInfoMap.end())
		{
			return it->second;
		}
		return NULL;
	}
	//-------------------------------------------------------------------------------------------
	void ClanQuestInfos::clear()
	{
		std::map<U32, ClanQuestInfo*>::iterator it = mQuestInfoMap.begin();
		for (; it != mQuestInfoMap.end(); it++)
		{
			MG_SAFE_DELETE(it->second);
		}
		mQuestInfoMap.clear();
	}
	//-------------------------------------------------------------------------------------------
	ClanQuestInfos::ClanQuestInfos()
	{

	}
	//-------------------------------------------------------------------------------------------
	ClanQuestInfos::~ClanQuestInfos()
	{

	}
	//-------------------------------------------------------------------------------------------
	MG::Bool ClanQuestInfos::setQuestInfoData()
	{
		std::map<U32, ClanQuestInfo*>::iterator it = mQuestInfoMap.begin();
		for (; it != mQuestInfoMap.end(); it++)
		{
			if (!it->second)
			{
				return false;
			}
			switch(it->second->type)
			{
			case QUEST_TYPE_NORMAL:
				{
					it->second->questInfo = QuestNormalInfos::getInstance().getQuestNormalInfo(it->second->questId);
				}
				break;
			case QUEST_TYPE_RANDOM:
				{
					//it->second->questInfo = QuestNormalInfos::getInstance().getQuestNormalInfo(it->second->questId);
				}
				break;
			default:
				{
					DYNAMIC_ASSERT(false);
				}
			}
			if (!it->second->questInfo)
			{
				return false;
			}
		}
		return true;
	}
}