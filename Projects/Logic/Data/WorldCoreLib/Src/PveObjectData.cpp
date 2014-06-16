/******************************************************************************/

#include "stdafx.h"
#include "PveObjectData.h"
#include "InstanceListCsv.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------------------
	PveObjectData::PveObjectData(InstanceListCsvInfo* instanceInfo)
		:mListCsvInfo(instanceInfo)
		,mPveCsvInfo(NULL)
	{
		DYNAMIC_ASSERT(NULL != instanceInfo);
		mPveCsvInfo = InstancePVEListCsv::getInstance().getInfoById(instanceInfo->instanceListId);
		DYNAMIC_ASSERT(NULL != mPveCsvInfo);
		setMapListCsvInfoByMapId(mPveCsvInfo->mapListId);
	}

	//--------------------------------------------------------------------------------------
	PveObjectData::~PveObjectData()
	{
	}

	InstanceIdType PveObjectData::getInstanceId()
	{
		return getListCsvInfo()->instanceId;
	}

	InstanceListCsvInfo* PveObjectData::getListCsvInfo()
	{
		return mListCsvInfo;
	}

	InstancePVEListCsvInfo* PveObjectData::getPveCsvInfo()
	{
		return mPveCsvInfo;
	}

}