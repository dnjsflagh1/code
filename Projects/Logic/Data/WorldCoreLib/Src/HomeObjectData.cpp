/******************************************************************************/
#include "stdafx.h"
#include "HomeObjectData.h"
/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------------------
	HomeObjectData::HomeObjectData(InstanceListCsvInfo* instanceInfo)
		:mListCsvInfo(instanceInfo)
		,mHomeCsvInfo(NULL)
	{
		DYNAMIC_ASSERT(NULL != instanceInfo);
		mHomeCsvInfo = InstanceHomeListCsv::getInstance().getInfoById(instanceInfo->instanceListId);
		DYNAMIC_ASSERT(NULL != mHomeCsvInfo);
		setMapListCsvInfoByMapId(mHomeCsvInfo->mapListId);
	}

	//--------------------------------------------------------------------------------------
	HomeObjectData::~HomeObjectData()
	{
	}

	InstanceIdType HomeObjectData::getInstanceId()
	{
		return getListCsvInfo()->instanceId;
	}

	InstanceListCsvInfo* HomeObjectData::getListCsvInfo()
	{
		return mListCsvInfo;
	}

	InstanceHomeListCsvInfo* HomeObjectData::getHomeCsvInfo()
	{
		return mHomeCsvInfo;
	}

}