//******************************************************************************************
#include "stdafx.h"
#include "NpcFucionDialogInfo.h"
//******************************************************************************************
namespace MG
{
	//-------------------------------------------------------------------------------------------
	// MG_CN_MODIFY
	MG::Bool NpcFuncionDialogInfos::load(Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/)
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
			NpcFuncionDialogInfo* tempInfo = MG_NEW NpcFuncionDialogInfo;
			MGStrOp::toU32(csvdata->mData[npcfuctiondialoginfoid].c_str(), tempInfo->id);
			MGStrOp::toU32(csvdata->mData[npcfuctiondialoginfocharacterid].c_str(), tempInfo->characterTempId);
			
			MGStrOp::toU32(csvdata->mData[npcfuctiondialoginfofuction1].c_str(), tempInfo->npcFuctionId[0]);
			MGStrOp::toU32(csvdata->mData[npcfuctiondialoginfofuction2].c_str(), tempInfo->npcFuctionId[1]);
			MGStrOp::toU32(csvdata->mData[npcfuctiondialoginfofuction3].c_str(), tempInfo->npcFuctionId[2]);
			MGStrOp::toU32(csvdata->mData[npcfuctiondialoginfofuction4].c_str(), tempInfo->npcFuctionId[3]);
			MGStrOp::toU32(csvdata->mData[npcfuctiondialoginfofuction5].c_str(), tempInfo->npcFuctionId[4]);
			MGStrOp::toU32(csvdata->mData[npcfuctiondialoginfofuction6].c_str(), tempInfo->npcFuctionId[5]);
			MGStrOp::toU32(csvdata->mData[npcfuctiondialoginfofuction7].c_str(), tempInfo->npcFuctionId[6]);
			MGStrOp::toU32(csvdata->mData[npcfuctiondialoginfofuction8].c_str(), tempInfo->npcFuctionId[7]);
			
			if (getNpcFucionDialogInfo(tempInfo->id))
			{
				DYNAMIC_ASSERT(false);
				MG_SAFE_DELETE(tempInfo);
				continue;
			}
			mNpcFuctionDialogInfoMap[tempInfo->id] = tempInfo;
		}
		return true;
	}
	//-------------------------------------------------------------------------------------------
	NpcFuncionDialogInfo* NpcFuncionDialogInfos::getNpcFucionDialogInfo( U32 id )
	{
		std::map<U32, NpcFuncionDialogInfo*>::iterator it = mNpcFuctionDialogInfoMap.find(id);
		if (it != mNpcFuctionDialogInfoMap.end())
		{
			return it->second;
		}
		return NULL;
	}
	//-------------------------------------------------------------------------------------------
	void NpcFuncionDialogInfos::clear()
	{
		std::map<U32, NpcFuncionDialogInfo*>::iterator it = mNpcFuctionDialogInfoMap.begin();
		for (; it != mNpcFuctionDialogInfoMap.end(); it++)
		{
			MG_SAFE_DELETE(it->second);
		}
		mNpcFuctionDialogInfoMap.clear();
	}
	//-------------------------------------------------------------------------------------------
	NpcFuncionDialogInfos::NpcFuncionDialogInfos()
	{

	}
	//-------------------------------------------------------------------------------------------
	NpcFuncionDialogInfos::~NpcFuncionDialogInfos()
	{

	}

	NpcFuncionDialogInfo* NpcFuncionDialogInfos::getNpcFucionDialogInfobyCharacterTempId( U32 id )
	{
		std::map<U32, NpcFuncionDialogInfo*>::iterator it = mNpcFuctionDialogInfoMap.begin();
		for (; it != mNpcFuctionDialogInfoMap.end(); it++)
		{
			if (it->second && it->second->characterTempId == id)
			{
				return it->second;
			}
		}
		return NULL;
	}

}
//******************************************************************************************