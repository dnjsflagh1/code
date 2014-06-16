//******************************************************************************************
#include "stdafx.h"
#include "QuestValueChange.h"
//******************************************************************************************
namespace MG
{
	// MG_CN_MODIFY
	MG::Bool QuestValueChangeInfos::load(Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/)
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
			QuestValueChangeInfo* tempInfo = MG_NEW QuestValueChangeInfo;

			MGStrOp::toU32(csvdata->mData[questvaluechangeinfoid].c_str(),					tempInfo->id);
			MGStrOp::toU32(csvdata->mData[questvaluechangeinfogroupid].c_str(),				tempInfo->groupId);
			I32 tempType;
			MGStrOp::toI32(csvdata->mData[questvaluechangeinfotype].c_str(),				tempType);
			tempInfo->type = (CHANGE_TYPE)tempType; 
			MGStrOp::toU32(csvdata->mData[questvaluechangeinfoparam1].c_str(),				tempInfo->param1);
			MGStrOp::toU32(csvdata->mData[questvaluechangeinfoparam2].c_str(),				tempInfo->param2);
			MGStrOp::toU32(csvdata->mData[questvaluechangeinfoparam3].c_str(),				tempInfo->param3);
			MGStrOp::toU32(csvdata->mData[questvaluechangeinfoparam4].c_str(),				tempInfo->param4);

			MGStrOp::toI32(csvdata->mData[questvaluechangeinfovaluechangetype].c_str(),		tempType);       
			tempInfo->valueChangeType = (VALUECHANGE_TYPE)(tempType-1);                   //填表从1开始
			MGStrOp::toI32(csvdata->mData[questvaluechangeinfovaluechangenum].c_str(),		tempInfo->valueChangeNum);
			if (getQuestValueChangeInfo(tempInfo->id))
			{
				DYNAMIC_ASSERT(false);
				MG_SAFE_DELETE(tempInfo);
				continue;
			}
			mQuestValueChangeInfoMap[tempInfo->id] = tempInfo;
		}
		return true;
	}
	//-------------------------------------------------------------------------------------------
	QuestValueChangeInfo* QuestValueChangeInfos::getQuestValueChangeInfo( U32 id )
	{
		std::map<U32, QuestValueChangeInfo*>::iterator it = mQuestValueChangeInfoMap.find(id);
		if (it != mQuestValueChangeInfoMap.end())
		{
			return it->second;
		}
		return NULL;
	}
	//-------------------------------------------------------------------------------------------
	void QuestValueChangeInfos::clear()
	{
		std::map<U32, QuestValueChangeInfo*>::iterator it = mQuestValueChangeInfoMap.begin();
		for (; it != mQuestValueChangeInfoMap.end(); it++)
		{
			MG_SAFE_DELETE(it->second);
		}
		mQuestValueChangeInfoMap.clear();
	}
	//-------------------------------------------------------------------------------------------
	QuestValueChangeInfos::QuestValueChangeInfos()
	{

	}
	//-------------------------------------------------------------------------------------------
	QuestValueChangeInfos::~QuestValueChangeInfos()
	{

	}

	MG::Int QuestValueChangeInfos::getQuestValueChangeInfoByGroupId( U32 groupId,std::vector<QuestValueChangeInfo*>& changeValues )
	{
		std::map<U32, QuestValueChangeInfo*>::iterator it = mQuestValueChangeInfoMap.begin();
		for (; it != mQuestValueChangeInfoMap.end(); it++)
		{
			if (it->second->groupId == groupId)
			{
				changeValues.push_back(it->second);
			}	 
		}
		return changeValues.size();
	}
}