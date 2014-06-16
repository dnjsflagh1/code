//******************************************************************************************
#include "stdafx.h"
#include "QuestText.h"
//******************************************************************************************
namespace MG
{
	// MG_CN_MODIFY
	MG::Bool QuestTextInfos::load(Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/)
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
			QuestTextInfo* tempInfo = MG_NEW QuestTextInfo;

			MGStrOp::toU32(csvdata->mData[questtextinfoid].c_str(),	tempInfo->id);
			tempInfo->name = csvdata->mData[questtextinfoname];
			tempInfo->nameAdd = csvdata->mData[questtextinfonameadd];
			tempInfo->desc = csvdata->mData[questtextinfodesc];
			tempInfo->acceptText = csvdata->mData[questtextinfoaccepttext];
			tempInfo->submitText = csvdata->mData[questtextinfosubmittext];
			tempInfo->submitTextUnFinish = csvdata->mData[questtextinfosubmittextunfinish];
			tempInfo->submitTextFail = csvdata->mData[questtextinfosubmittextfail];
			tempInfo->destNpcText = csvdata->mData[questtextinfodestnpctext];
			tempInfo->valueText1 = csvdata->mData[questtextinfovaluetext1];
			tempInfo->valueText2 = csvdata->mData[questtextinfovaluetext2];
			tempInfo->valueText3 = csvdata->mData[questtextinfovaluetext3];
			tempInfo->valueText4 = csvdata->mData[questtextinfovaluetext4];
		

			if (getQuestTextInfo(tempInfo->id))
			{
				DYNAMIC_ASSERT(false);
				MG_SAFE_DELETE(tempInfo);
				continue;
			}
			mQuestTextInfoMap[tempInfo->id] = tempInfo;
		}
		return true;
	}
	//-------------------------------------------------------------------------------------------
	QuestTextInfo* QuestTextInfos::getQuestTextInfo( U32 id )
	{
		std::map<U32, QuestTextInfo*>::iterator it = mQuestTextInfoMap.find(id);
		if (it != mQuestTextInfoMap.end())
		{
			return it->second;
		}
		return NULL;
	}
	//-------------------------------------------------------------------------------------------
	void QuestTextInfos::clear()
	{
		std::map<U32, QuestTextInfo*>::iterator it = mQuestTextInfoMap.begin();
		for (; it != mQuestTextInfoMap.end(); it++)
		{
			MG_SAFE_DELETE(it->second);
		}
		mQuestTextInfoMap.clear();
	}
	//-------------------------------------------------------------------------------------------
	QuestTextInfos::QuestTextInfos()
	{

	}
	//-------------------------------------------------------------------------------------------
	QuestTextInfos::~QuestTextInfos()
	{

	}
}