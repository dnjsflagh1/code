//***************************************************************************************
#include "stdafx.h"
#include "StatusCharacterList.h"
//***************************************************************************************
namespace MG
{
	StatusCharacterList::~StatusCharacterList()
	{
		clear();
	}
	//---------------------------------------------------------------------------------------
	MG::Bool StatusCharacterList::load( Str16 fileName, IMGExternalPackManager* packManager /*= NULL*/ )
	{
		CsvReader csvreader;
		// MG_CN_MODIFY
		if(!csvreader.create(fileName, packManager))
		{
			return false;
		}

		CsvData* csvdata = NULL;
		Int RowCount = csvreader.count();

		DYNAMIC_ASSERT(RowCount != Status_Character_Max);

		for(int i = 0; i < RowCount; ++i)
		{
			csvdata = csvreader.findValue(i);
			if(!csvdata)
			{
				continue;
			}

			StatusCharacterData* tempInfo = new StatusCharacterData;
			
			MGStrOp::toU32(csvdata->mData[Status_Character_StatusCharacterId].c_str(), tempInfo->StatusListId);
			MGStrOp::toU32(csvdata->mData[Status_Character_GroupId		].c_str(), tempInfo->GroupId);
			MGStrOp::toU32(csvdata->mData[Status_Character_GroupLevel		].c_str(), tempInfo->GroupLevel);
			MGStrOp::toU32(csvdata->mData[Status_Character_TargetLevel	].c_str(), tempInfo->TargetLevel);
			tempInfo->Name = csvdata->mData[Status_Character_Name			].c_str();
			tempInfo->Text = csvdata->mData[Status_Character_Text			].c_str();
			tempInfo->KindName = csvdata->mData[Status_Character_KindName		].c_str();
			MGStrOp::toU32(csvdata->mData[Status_Character_ArtIconId		].c_str(), tempInfo->ArtIconId);
			MGStrOp::toU32(csvdata->mData[Status_Character_ShowType		].c_str(), (U32&)tempInfo->ShowType);
			MGStrOp::toU32(csvdata->mData[Status_Character_StyleType		].c_str(), (U32&)tempInfo->StyleType);
			MGStrOp::toU32(csvdata->mData[Status_Character_SlotNum		].c_str(), tempInfo->SlotNum);
			MGStrOp::toU32(csvdata->mData[Status_Character_SlotPriority	].c_str(), tempInfo->SlotPriority);
			MGStrOp::toU32(csvdata->mData[Status_Character_MaxAddNum		].c_str(), tempInfo->MaxAddNum);
			MGStrOp::toU32(csvdata->mData[Status_Character_VisionEventId	].c_str(), tempInfo->VisionEventId);
			MGStrOp::toU32(csvdata->mData[Status_Character_TimeType		].c_str(), (U32&)tempInfo->TimeType);
			MGStrOp::toU32(csvdata->mData[Status_Character_HoldTime		].c_str(), tempInfo->HoldTime);
			tempInfo->HoldTime *= TIME_HUNDRED_MS;
			MGStrOp::toU32(csvdata->mData[Status_Character_DisappearType	].c_str(), tempInfo->DisappearType);
			MGStrOp::toU32(csvdata->mData[Status_Character_AbilityAppendId].c_str(), tempInfo->AbilityAppendId);
			MGStrOp::toU32(csvdata->mData[Status_Character_StatusSysType	].c_str(), (U32&)tempInfo->StatusSysType);
			MGStrOp::toU32(csvdata->mData[Status_Character_VitiateFlag	].c_str(), tempInfo->VitiateFlag);
			MGStrOp::toU32(csvdata->mData[Status_Character_AbsorbType		].c_str(), (U32&)tempInfo->AbsorbType);
			MGStrOp::toU32(csvdata->mData[Status_Character_AbsorbNum		].c_str(), tempInfo->AbsorbNum);
			MGStrOp::toU32(csvdata->mData[Status_Character_ModelResId		].c_str(), tempInfo->ModelResId);
			MGStrOp::toU32(csvdata->mData[Status_Character_CycleNum		].c_str(), tempInfo->CycleNum);
			MGStrOp::toU32(csvdata->mData[Status_Character_CycleType		].c_str(), (U32&)tempInfo->CycleType);
			MGStrOp::toU32(csvdata->mData[Status_Character_CycleParameter1].c_str(), tempInfo->CycleParameter1);
			MGStrOp::toU32(csvdata->mData[Status_Character_CycleParameter2].c_str(), tempInfo->CycleParameter2);
			MGStrOp::toU32(csvdata->mData[Status_Character_CycleParameter3].c_str(), tempInfo->CycleParameter3);
			MGStrOp::toU32(csvdata->mData[Status_Character_CycleParameter4].c_str(), tempInfo->CycleParameter4);
			MGStrOp::toU32(csvdata->mData[Status_Character_EventCondition		].c_str(), (U32&)tempInfo->EventCondition);
			MGStrOp::toU32(csvdata->mData[Status_Character_ConditionParameter1].c_str(), tempInfo->ConditionParameter1);
			MGStrOp::toU32(csvdata->mData[Status_Character_ConditionParameter2].c_str(), tempInfo->ConditionParameter2);
			MGStrOp::toU32(csvdata->mData[Status_Character_ConditionParameter3].c_str(), tempInfo->ConditionParameter3);
			MGStrOp::toU32(csvdata->mData[Status_Character_ConditionParameter4].c_str(), tempInfo->ConditionParameter4);
			MGStrOp::toU32(csvdata->mData[Status_Character_EventResult		].c_str(), (U32&)tempInfo->EventResult);
			MGStrOp::toU32(csvdata->mData[Status_Character_ResultParameter1].c_str(), tempInfo->ResultParameter1);
			MGStrOp::toU32(csvdata->mData[Status_Character_ResultParameter2].c_str(), tempInfo->ResultParameter2);
			MGStrOp::toU32(csvdata->mData[Status_Character_ResultParameter3].c_str(), tempInfo->ResultParameter3);
			MGStrOp::toU32(csvdata->mData[Status_Character_ResultParameter4].c_str(), tempInfo->ResultParameter4);

			mMapStatusCharacterData[tempInfo->StatusListId] = tempInfo;

			setIdLvlMapStatusBaseInfo(tempInfo);
		}

		return true;
	}
	//---------------------------------------------------------------------------------------
	const StatusBaseInfo* StatusCharacterList::getStatusBaseInfo( UInt id )
	{
		std::map<UInt, StatusBaseInfo*>::iterator iter = mMapStatusCharacterData.find(id);
		if ( iter != mMapStatusCharacterData.end() )
			return iter->second;

		return NULL;
	}
	//---------------------------------------------------------------------------------------
	void StatusCharacterList::clear()
	{
		std::map<UInt, StatusBaseInfo*>::iterator frontiter = mMapStatusCharacterData.begin();
		std::map<UInt, StatusBaseInfo*>::iterator backiter = mMapStatusCharacterData.end();
		while (frontiter != backiter)
		{
			MG_DELETE frontiter->second;
			++frontiter;
		}

		mMapStatusCharacterData.clear();
	}
	//---------------------------------------------------------------------------------------
	const StatusBaseInfo* StatusCharacterList::getmStatusBaseInfoByIdLvl( UInt groupId, UInt lvl )
	{
		std::map<UInt, std::map<UInt, StatusBaseInfo*>>::iterator iter1 = mIdLvlMapStatusBaseInfo.find(groupId);
		if ( iter1 != mIdLvlMapStatusBaseInfo.end() )
		{
			std::map<UInt, StatusBaseInfo*> pMapData = iter1->second;
			std::map<UInt, StatusBaseInfo*>::iterator iter2 = pMapData.find(lvl);
			if ( iter2 != pMapData.end() )
			{
				return iter2->second;
			}
		}

		DYNAMIC_ASSERT(0);

		return NULL;
	}
	//---------------------------------------------------------------------------------------
	const StatusBaseInfo* StatusCharacterList::getmStatusBaseInfoByIdLvl( UInt groupId, UInt lvl, UInt objLvl )
	{
		std::map<UInt, std::map<UInt, StatusBaseInfo*>>::iterator iter1 = mIdLvlMapStatusBaseInfo.find(groupId);
		if ( iter1 != mIdLvlMapStatusBaseInfo.end() )
		{
			while (lvl >= 1)
			{
				std::map<UInt, StatusBaseInfo*> pMapData = iter1->second;
				std::map<UInt, StatusBaseInfo*>::iterator iter2 = pMapData.find(lvl);
				if ( iter2 != pMapData.end()  &&  iter2->second->TargetLevel <= objLvl )
				{
					return iter2->second;
				}
				--lvl;
			}
		}

		return NULL;
	}
	//---------------------------------------------------------------------------------------
	void StatusCharacterList::setIdLvlMapStatusBaseInfo( StatusCharacterData* pData )
	{
		std::map<UInt, std::map<UInt, StatusBaseInfo*>>::iterator iter1 = mIdLvlMapStatusBaseInfo.find(pData->GroupId);
		if ( iter1 != mIdLvlMapStatusBaseInfo.end() )
		{
			std::map<UInt, StatusBaseInfo*> pMapData = iter1->second;
			std::map<UInt, StatusBaseInfo*>::iterator iter2 = pMapData.find(pData->GroupLevel);
			if ( iter2 != pMapData.end() )
			{
				DYNAMIC_ASSERT(0);
			}
			else
			{
				pMapData[pData->GroupLevel] = pData;
			}
		}
		else
		{
			std::map<UInt, StatusBaseInfo*> pMapData;
			pMapData[pData->GroupLevel] = pData;
			mIdLvlMapStatusBaseInfo[pData->GroupId] = pMapData;
		}
	}
}