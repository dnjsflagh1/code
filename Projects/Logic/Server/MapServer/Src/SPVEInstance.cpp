/******************************************************************************/

#include "stdafx.h"
#include "SPVEInstance.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	SPVEInstance::SPVEInstance(InstanceListCsvInfo* instanceListInfo)
		:SInstanceBase(instanceListInfo)
		,mPVECsv(NULL)
	{
		InstancePVEListCsvInfo* pveInstance = InstancePVEListCsv::getInstance().getInfoById(instanceListInfo->instanceListId);
		DYNAMIC_ASSERT(NULL != pveInstance);
		mPVECsv = pveInstance;
	}

	//--------------------------------------------------------------------------
	SPVEInstance::~SPVEInstance()
	{

	}

	////--------------------------------------------------------------------------
	//InstanceType SPVEInstance::getInstanceType()
	//{
	//	return InstanceType_PVE;
	//}

	//--------------------------------------------------------------------------
	InstancePVEListCsvInfo* SPVEInstance::getPVECsv()
	{
		return mPVECsv;
	}

	//--------------------------------------------------------------------------
	Int SPVEInstance::getFinishCharacter() const
	{
		return mPVECsv->finishCharacter;
	}

	//--------------------------------------------------------------------------
}