//******************************************************************************************
#include "stdafx.h"
#include "QuestNormalList.h"
#include "QuestText.h"
#include "QuestValueChange.h"
//******************************************************************************************
namespace MG
{
	// MG_CN_MODIFY
	MG::Bool QuestNormalInfos::load(Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/)
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
			QuestNormalInfo* tempInfo = MG_NEW QuestNormalInfo();

			MGStrOp::toU32(csvdata->mData[questnormalinfoid].c_str(),				tempInfo->id);
			
			I32 tempType;
			MGStrOp::toI32(csvdata->mData[questnormalinfocycletype].c_str(),		tempType);
			tempInfo->cycleType = (CYCLE_TYPE)tempType; 
			MGStrOp::toU32(csvdata->mData[questnormalinfotextid].c_str(),			tempInfo->textId);
			MGStrOp::toU32(csvdata->mData[questnormalinfoacceptnpcid].c_str(),		tempInfo->acceptNpcId);
			MGStrOp::toU32(csvdata->mData[questnormalinfosubmitnpcid].c_str(),		tempInfo->submitNpcId);
			MGStrOp::toU32(csvdata->mData[questnormalinfoclanjudgeid].c_str(),		tempInfo->clanJudgeId);
			MGStrOp::toU32(csvdata->mData[questnormalinfocharacterjudgeid].c_str(),		tempInfo->characterJudgeId);
			MGStrOp::toU32(csvdata->mData[questnormalinfovaluechangegroupid].c_str(),tempInfo->valueChangeGroupId);
			MGStrOp::toI32(csvdata->mData[questnormalinfovaluesuccess1].c_str(),	tempInfo->valueSuccess[0]);
			MGStrOp::toI32(csvdata->mData[questnormalinfovaluesuccess2].c_str(),	tempInfo->valueSuccess[1]);
			MGStrOp::toI32(csvdata->mData[questnormalinfovaluesuccess3].c_str(),	tempInfo->valueSuccess[2]);
			MGStrOp::toI32(csvdata->mData[questnormalinfovaluesuccess4].c_str(),	tempInfo->valueSuccess[3]);
			MGStrOp::toI32(csvdata->mData[questnormalinfovaluefail1].c_str(),		tempInfo->valueFail[0]);
			MGStrOp::toI32(csvdata->mData[questnormalinfovaluefail2].c_str(),		tempInfo->valueFail[1]);
			MGStrOp::toI32(csvdata->mData[questnormalinfovaluefail3].c_str(),		tempInfo->valueFail[2]);
			MGStrOp::toI32(csvdata->mData[questnormalinfovaluefail4].c_str(),		tempInfo->valueFail[3]);
			MGStrOp::toU32(csvdata->mData[questnormalinfogivestateid].c_str(),		tempInfo->giveStateId);
			MGStrOp::toU32(csvdata->mData[questnormalinfogivestatenum].c_str(),		tempInfo->giveStateNum);
			MGStrOp::toU32(csvdata->mData[questnormalinfogiveitemid].c_str(),		tempInfo->giveItemId);
			MGStrOp::toString(csvdata->mData[questnormalinfogivescript].c_str(),	tempInfo->giveScript);
			MGStrOp::toU32(csvdata->mData[questnormalinfodelstateid].c_str(),		tempInfo->delStateId);
			MGStrOp::toU32(csvdata->mData[questnormalinfodelitemgroupid].c_str(),	tempInfo->delItemGroupId);
			MGStrOp::toString(csvdata->mData[questnormalinfodelscript].c_str(),		tempInfo->delScript);
			MGStrOp::toU32(csvdata->mData[questnormalinfoitemgroupid].c_str(),		tempInfo->itemGroupId);
			

			if (getQuestNormalInfo(tempInfo->id))
			{
				DYNAMIC_ASSERT(false);
				MG_SAFE_DELETE(tempInfo);
				continue;
			}
			mQuestNormalInfoMap[tempInfo->id] = tempInfo;
		}
		return true;
	}
	//-------------------------------------------------------------------------------------------
	QuestNormalInfo* QuestNormalInfos::getQuestNormalInfo( U32 id )
	{
		std::map<U32, QuestNormalInfo*>::iterator it = mQuestNormalInfoMap.find(id);
		if (it != mQuestNormalInfoMap.end())
		{
			return it->second;
		}
		return NULL;
	}
	//-------------------------------------------------------------------------------------------
	void QuestNormalInfos::clear()
	{
		std::map<U32, QuestNormalInfo*>::iterator it = mQuestNormalInfoMap.begin();
		for (; it != mQuestNormalInfoMap.end(); it++)
		{
			MG_SAFE_DELETE(it->second);
		}
		mQuestNormalInfoMap.clear();
	}
	//-------------------------------------------------------------------------------------------
	QuestNormalInfos::QuestNormalInfos()
	{

	}
	//-------------------------------------------------------------------------------------------
	QuestNormalInfos::~QuestNormalInfos()
	{

	}
	//-------------------------------------------------------------------------------------------
	// 任务数据
	//-------------------------------------------------------------------------------------------
	QuestTextInfo* QuestNormalInfo::getTextInfo()
	{
		return QuestTextInfos::getInstance().getQuestTextInfo(textId);
	}
	//---------------------------------------------------------------------
	Str8& QuestNormalInfo::getAcceptScript()
	{
		return giveScript;
	}
	//---------------------------------------------------------------------
	Str8& QuestNormalInfo::getSubmitScript()
	{
		return delScript;
	}
	//---------------------------------------------------------------------
	CYCLE_TYPE QuestNormalInfo::getQuestCycleType()
	{
		return cycleType;
	}
	//---------------------------------------------------------------------
	MG::Int QuestNormalInfo::getValue( Bool success,Int index )
	{
		if (index > 3 && index < 0)
		{
			return 0;
		}
		if (success)
		{
			return valueSuccess[index];
		}
		else
		{
			return valueFail[index];
		}
	}
	//---------------------------------------------------------------------
	MG::Int QuestNormalInfo::getValueChangeGroupInfo( std::vector<QuestValueChangeInfo*>& changeValues )
	{
		return QuestValueChangeInfos::getInstance().getQuestValueChangeInfoByGroupId(valueChangeGroupId,changeValues);
	}
	//---------------------------------------------------------------------
	MG::U32 QuestNormalInfo::getItemGroupId()
	{
		return itemGroupId;
	}
	//---------------------------------------------------------------------
	MG::U32 QuestNormalInfo::getItemDelGroupId()
	{
             return delItemGroupId;
	}
	//---------------------------------------------------------------------
	MG::U32 QuestNormalInfo::getclanJudgeId()
	{
            return clanJudgeId;
	}
	//---------------------------------------------------------------------
	MG::U32 QuestNormalInfo::getcharacterJudgeId()
	{
          return characterJudgeId;
	}
}