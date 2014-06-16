/******************************************************************************/

#include "stdafx.h"
#include "TiroObjectData.h"
#include "InstanceTiroListCsv.h"
#include "InstanceListCsv.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------------------
	TiroObjectData::TiroObjectData(InstanceListCsvInfo* instanceInfo)
		:mListCsvInfo(instanceInfo)
		,mTiroCsvInfo(NULL)
	{
		DYNAMIC_ASSERT(NULL != instanceInfo);
		mTiroCsvInfo = InstanceTiroListCsv::getInstance().getInfoById(instanceInfo->instanceListId);
		DYNAMIC_ASSERT(NULL != mTiroCsvInfo);
		setMapListCsvInfoByMapId(mTiroCsvInfo->mapListId);
	}

	//--------------------------------------------------------------------------------------
	TiroObjectData::~TiroObjectData()
	{
	}

	InstanceIdType TiroObjectData::getInstanceId()
	{
		//�޷��� InstanceList.csv ���ҵ���Ӧ�ļ�¼
		return getListCsvInfo()->instanceId;
	}

	InstanceListCsvInfo* TiroObjectData::getListCsvInfo()
	{
		return mListCsvInfo;
	}

	InstanceTiroListCsvInfo* TiroObjectData::getTiroCsvInfo()
	{
		return mTiroCsvInfo;
	}

}