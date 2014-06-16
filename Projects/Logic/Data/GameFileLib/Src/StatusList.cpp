//***************************************************************************************
#include "stdafx.h"
#include "StatusList.h"
#include "StatusCharacterList.h"
//***************************************************************************************
namespace MG
{
	StatusList::~StatusList()
	{
		clear();
	}
	//-------------------------------------------------------------------------------
	MG::Bool StatusList::load( Str16 fileName, IMGExternalPackManager* packManager /*= NULL*/ )
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

			StatusData* tempInfo = new StatusData;
			UInt nCol = 0;

			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->StatusId);
			nCol++;
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), (U32&)tempInfo->StatusType);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->StatusListId);


			setStatusBaseInfo(tempInfo);
			setStatusData(tempInfo);

			mMapStatusData[tempInfo->StatusId] = tempInfo;
		}

		return true;
	}
	//-------------------------------------------------------------------------------
	const StatusData* StatusList::getStatusData( UInt id )
	{
		std::map<UInt, StatusData*>::iterator iter = mMapStatusData.find(id);
		if (iter != mMapStatusData.end())
		{
			return iter->second;
		}

		DYNAMIC_ASSERT(0);
		return NULL;
	}
	//-------------------------------------------------------------------------------
	const StatusData* StatusList::getStatusData( UInt id, UInt objLvl )
	{
		const StatusData* pStatusData = getStatusData(id);
		switch (pStatusData->StatusType)
		{
		case STATUS_TYPE_CHARACTER:
			{
				const StatusBaseInfo* pStatusBaseInfo = 
					StatusCharacterList::getInstance().getmStatusBaseInfoByIdLvl(
						pStatusData->mpStatusBaseInfo->GroupId, 
						pStatusData->mpStatusBaseInfo->GroupLevel,
						objLvl
					);
				if ( pStatusBaseInfo )
					return getStatusDataByTypeListId(pStatusData->StatusType, pStatusBaseInfo->StatusListId);
			}
			break;
		case STATUS_TYPE_CLAN:
			break;
		case STATUS_TYPE_PLACE:
			break;
		case STATUS_TYPE_FORCE:
			break;
		}

		DYNAMIC_ASSERT(0);
		return NULL;
	}
	//-------------------------------------------------------------------------------
	void StatusList::clear()
	{
		std::map<UInt, StatusData*>::iterator frontIter = mMapStatusData.begin();
		std::map<UInt, StatusData*>::iterator backIter = mMapStatusData.end();
		while (frontIter != backIter)
		{
			MG_DELETE frontIter->second;
			++frontIter;
		}

		mMapStatusData.clear();
	}
	//-------------------------------------------------------------------------------
	void StatusList::setStatusBaseInfo( StatusData* pStatusData )
	{
		switch (pStatusData->StatusType)
		{
		case STATUS_TYPE_CHARACTER:
			pStatusData->mpStatusBaseInfo = StatusCharacterList::getInstance().getStatusBaseInfo(pStatusData->StatusListId);
			break;
		case STATUS_TYPE_CLAN:
			break;
		case STATUS_TYPE_PLACE:
			break;
		case STATUS_TYPE_FORCE:
			break;
		default:
			DYNAMIC_ASSERT(0);
			break;
		}
	}
	//-------------------------------------------------------------------------------
	void StatusList::setStatusData( StatusData* pStatusData )
	{
		std::map<UInt, StatusData*>* pMapStatusData = NULL;

		std::map<STATUS_TYPE, std::map<UInt, StatusData*>*>::iterator iter1 = mMapStatusTypeStatusData.find(pStatusData->StatusType);
		if (iter1 != mMapStatusTypeStatusData.end())
		{
			pMapStatusData = iter1->second;
			std::map<UInt, StatusData*>::iterator iter2 = pMapStatusData->find(pStatusData->StatusListId);
			if ( iter2 != pMapStatusData->end() )
			{
				DYNAMIC_ASSERT(0);
			}
			else
			{
				(*pMapStatusData)[pStatusData->StatusListId] = pStatusData;
			}
		}
		else
		{
			pMapStatusData =  new std::map<UInt, StatusData*>;
			(*pMapStatusData)[pStatusData->StatusListId] = pStatusData;
			mMapStatusTypeStatusData[pStatusData->StatusType] = pMapStatusData;
		}
	}
	//-------------------------------------------------------------------------------
	const StatusData* StatusList::getStatusDataByTypeListId( STATUS_TYPE type, UInt listId )
	{
		std::map<STATUS_TYPE, std::map<UInt, StatusData*>*>::iterator iter1 = mMapStatusTypeStatusData.find(type);
		if (iter1 != mMapStatusTypeStatusData.end())
		{
			std::map<UInt, StatusData*>* pMapStatusData = iter1->second;
			std::map<UInt, StatusData*>::iterator iter2 = pMapStatusData->find(listId);
			if ( iter2 != pMapStatusData->end() )
			{
				return iter2->second;
			}
		}
		DYNAMIC_ASSERT(0);

		return NULL;
	}
}