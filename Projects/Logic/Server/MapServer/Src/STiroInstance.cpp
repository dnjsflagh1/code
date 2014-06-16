/******************************************************************************/

#include "stdafx.h"
#include "STiroInstance.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	STiroInstance::STiroInstance(InstanceListCsvInfo* instanceTiroInfo)
		:SInstanceBase(instanceTiroInfo)
		,mTiroCsv(NULL)
	{
		mTiroCsv = InstanceTiroListCsv::getInstance().getInfoById(instanceTiroInfo->instanceListId);
		DYNAMIC_ASSERT(NULL != mTiroCsv);
	}

	//--------------------------------------------------------------------------
	STiroInstance::~STiroInstance()
	{

	}

	////--------------------------------------------------------------------------
	//InstanceType STiroInstance::getInstanceType()
	//{
	//	return InstanceType_Tiro;
	//}

	//--------------------------------------------------------------------------
	InstanceTiroListCsvInfo* STiroInstance::getTiroCsv()
	{
		return mTiroCsv;
	}

	//--------------------------------------------------------------------------
}