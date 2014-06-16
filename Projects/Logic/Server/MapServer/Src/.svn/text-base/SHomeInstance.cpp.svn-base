/******************************************************************************/

#include "stdafx.h"
#include "SHomeInstance.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	SHomeInstance::SHomeInstance(InstanceListCsvInfo* instanceListInfo)
		:SInstanceBase(instanceListInfo)
		,mHomeListCsv(NULL)
	{
		InstanceHomeListCsvInfo* homeInstance = InstanceHomeListCsv::getInstance().getInfoById(instanceListInfo->instanceListId);
		DYNAMIC_ASSERT(NULL != homeInstance);
		mHomeListCsv = homeInstance;
	}

	//--------------------------------------------------------------------------
	SHomeInstance::~SHomeInstance()
	{

	}

	//--------------------------------------------------------------------------
	InstanceHomeListCsvInfo* SHomeInstance::getHomeCsv()
	{
		return mHomeListCsv;
	}
	//--------------------------------------------------------------------------
}