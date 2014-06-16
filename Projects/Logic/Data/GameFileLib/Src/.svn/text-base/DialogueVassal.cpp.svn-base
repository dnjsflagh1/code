//******************************************************************************************
#include "stdafx.h"
#include "DialogueVassal.h"
//******************************************************************************************

namespace MG
{
           
	//-------------------------------------------------------------------------------------------      
	DialogueVassal::DialogueVassal()
	{
		
	}
	//-------------------------------------------------------------------------------------------
	DialogueVassal::~DialogueVassal()
	{
         clear();
	}
	//-------------------------------------------------------------------------------------------
	MG::Bool DialogueVassal::load( Str16 fileName, IMGExternalPackManager* packManager /*= NULL*/ )
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
			DialogueVassalInfo* tempInfo = MG_NEW DialogueVassalInfo;
			MGStrOp::toU32(csvdata->mData[dialogueVassalId].c_str(), tempInfo->id);
			MGStrOp::toU32(csvdata->mData[dialogueType].c_str(), tempInfo->diaType);
			MGStrOp::toU32(csvdata->mData[dialogueObjectId].c_str(), tempInfo->diaObjectId);


			MGStrOp::toU32(csvdata->mData[fuctionListId1].c_str(), tempInfo->fuctionId[0]);
			MGStrOp::toU32(csvdata->mData[fuctionListId2].c_str(), tempInfo->fuctionId[1]);
			MGStrOp::toU32(csvdata->mData[fuctionListId3].c_str(), tempInfo->fuctionId[2]);
			MGStrOp::toU32(csvdata->mData[fuctionListId4].c_str(), tempInfo->fuctionId[3]);
			MGStrOp::toU32(csvdata->mData[fuctionListId5].c_str(), tempInfo->fuctionId[4]);
			MGStrOp::toU32(csvdata->mData[fuctionListId6].c_str(), tempInfo->fuctionId[5]);
			MGStrOp::toU32(csvdata->mData[fuctionListId7].c_str(), tempInfo->fuctionId[6]);
			MGStrOp::toU32(csvdata->mData[fuctionListId8].c_str(), tempInfo->fuctionId[7]);

			if (getDialogueVassalInfo(tempInfo->id))
			{
				DYNAMIC_ASSERT(false);
				MG_SAFE_DELETE(tempInfo);
				continue;
			}
			mDialogueVassalInfoMap[tempInfo->id] = tempInfo;
		}
		return true;

	}
	//-------------------------------------------------------------------------------------------
	DialogueVassalInfo* DialogueVassal::getDialogueVassalInfo( U32 id )
	{
		std::map<U32, DialogueVassalInfo*>::iterator it = mDialogueVassalInfoMap.find(id);
		if (it != mDialogueVassalInfoMap.end())
		{
			return it->second;
		}
		return NULL;
	}
	//-------------------------------------------------------------------------------------------
	DialogueVassalInfo* DialogueVassal::getDialogueVassalInfobyObjectId( U32 id )
	{
		std::map<U32, DialogueVassalInfo*>::iterator it = mDialogueVassalInfoMap.begin();
		for (; it != mDialogueVassalInfoMap.end(); it++)
		{
			if (it->second && it->second->diaObjectId == id)
			{
				return it->second;
			}
		}
		return NULL;
	}
	//-------------------------------------------------------------------------------------------
	void DialogueVassal::clear()
	{
		std::map<U32, DialogueVassalInfo*>::iterator it = mDialogueVassalInfoMap.begin();
		for (; it != mDialogueVassalInfoMap.end(); it++)
		{
			MG_SAFE_DELETE(it->second);
		}
		mDialogueVassalInfoMap.clear();
	}

}