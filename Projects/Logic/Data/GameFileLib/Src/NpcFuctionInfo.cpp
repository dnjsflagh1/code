//******************************************************************************************
#include "stdafx.h"
#include "NpcFuctionInfo.h"
//******************************************************************************************
namespace MG
{

	//-------------------------------------------------------------------------------------------
	// MG_CN_MODIFY
	MG::Bool NpcFunctionInfos::load(Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/)
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
			NpcFunctionInfo* tempInfo = MG_NEW NpcFunctionInfo;

			MGStrOp::toU32(csvdata->mData[npcfunctioninfoid].c_str(),			tempInfo->id);

			MGStrOp::toU32(csvdata->mData[npcfunctioninfoartiocnres].c_str(),	tempInfo->artIocnResId);
			

			if (csvdata->mData[npcfunctioninfodesc].size() > NPC_FUCTION_INFO_DESC_MAX_LEN)
			{
				DYNAMIC_ASSERT(false);
				Char temp[256] = {0};
				MGStrOp::sprintf(temp,256,"DialogueFunctionList.csv中ID为%d的功能文字长度超过64",tempInfo->id);
				MsgBox::show(temp);
				MG_SAFE_DELETE(tempInfo);
				return false;
			}
			tempInfo->desc = csvdata->mData[npcfunctioninfodesc];

			Int tempType = 0;
			MGStrOp::toI32(csvdata->mData[npcfunctioninfotype].c_str(),			tempType);
			tempInfo->type = (NPC_FUCTION_TYPE)tempType;

			MGStrOp::toI32(csvdata->mData[npcfunctioninfoparam1].c_str(),		tempInfo->param1);

			MGStrOp::toI32(csvdata->mData[npcfunctioninfoparam2].c_str(),		tempInfo->param2);

			MGStrOp::toI32(csvdata->mData[npcfunctioninfoparam3].c_str(),		tempInfo->param3);

			if (csvdata->mData[npcfunctioninfoparam4].size() > NPC_FUCTION_INFO_PARAM4_MAX_LEN)
			{
				DYNAMIC_ASSERT(false);
				Char temp[256] = {0};
				MGStrOp::sprintf(temp,256,"DialogueFunctionList.csv中ID为%d的第四个参数文字长度超过64",tempInfo->id);
				MsgBox::show(temp);
				MG_SAFE_DELETE(tempInfo);
				return false;
			}
			tempInfo->param4 = csvdata->mData[npcfunctioninfoparam4];

			if (getNpcFuctionInfo(tempInfo->id))
			{
				DYNAMIC_ASSERT(false);
				MG_SAFE_DELETE(tempInfo);
				continue;
			}
			mNpcFuctionInfoMap[tempInfo->id] = tempInfo;
		}
		return true;
	}
	//-------------------------------------------------------------------------------------------
	NpcFunctionInfo* NpcFunctionInfos::getNpcFuctionInfo( U32 id )
	{
		std::map<U32, NpcFunctionInfo*>::iterator it = mNpcFuctionInfoMap.find(id);
		if (it != mNpcFuctionInfoMap.end())
		{
			return it->second;
		}
		return NULL;
	}
	//-------------------------------------------------------------------------------------------
	void NpcFunctionInfos::clear()
	{
		std::map<U32, NpcFunctionInfo*>::iterator it = mNpcFuctionInfoMap.begin();
		for (; it != mNpcFuctionInfoMap.end(); it++)
		{
			MG_SAFE_DELETE(it->second);
		}
		mNpcFuctionInfoMap.clear();
	}
	//-------------------------------------------------------------------------------------------
	NpcFunctionInfos::NpcFunctionInfos()
	{

	}
	//-------------------------------------------------------------------------------------------
	NpcFunctionInfos::~NpcFunctionInfos()
	{

	}

}
//******************************************************************************************