/******************************************************************************/

#include "stdafx.h"
#include "SAtkInstance.h"

/******************************************************************************/

namespace MG
{
	/******************************************************************************/
	SCampListCsv::SCampListCsv(CampIdType campListId)
	{
		InstanceAtkCampListCsvInfo* atkCampListCsvInfo = InstanceAtkCampListCsv::getInstance().getInfoById(campListId);
		DYNAMIC_ASSERT(NULL != atkCampListCsvInfo);
		mAtkCampListCsvInfo = atkCampListCsvInfo;

		for (Int i=0; i<POSITION_MAX; ++i)
		{
			CampIdType campId = atkCampListCsvInfo->camp[i];
			InstanceAtkStrengthListCsvInfo* atkCampListCsvInfo = InstanceAtkStrengthListCsv::getInstance().getInfoById(campId);
			DYNAMIC_ASSERT(NULL != atkCampListCsvInfo);
			mAtkStrengthListCsvList[campId] = atkCampListCsvInfo;
		}
		
		Int sdfe= 0;

		//InstanceAtkStrengthListCsvInfo* atkCampListCsvInfo2 = InstanceAtkStrengthListCsv::getInstance().getInfoById(atkCampListCsvInfo->camp01);
		//DYNAMIC_ASSERT(NULL != atkCampListCsvInfo2);
		//mAtkStrengthListCsvList[atkCampListCsvInfo->camp02] = atkCampListCsvInfo2;

		//InstanceAtkStrengthListCsvInfo* atkCampListCsvInfo3 = InstanceAtkStrengthListCsv::getInstance().getInfoById(atkCampListCsvInfo->camp01);
		//DYNAMIC_ASSERT(NULL != atkCampListCsvInfo3);
		//mAtkStrengthListCsvList[atkCampListCsvInfo->camp03] = atkCampListCsvInfo3;

		//InstanceAtkStrengthListCsvInfo* atkCampListCsvInfo4 = InstanceAtkStrengthListCsv::getInstance().getInfoById(atkCampListCsvInfo->camp01);
		//DYNAMIC_ASSERT(NULL != atkCampListCsvInfo4);
		//mAtkStrengthListCsvList[atkCampListCsvInfo->camp04] = atkCampListCsvInfo4;

		//InstanceAtkStrengthListCsvInfo* atkCampListCsvInfo5 = InstanceAtkStrengthListCsv::getInstance().getInfoById(atkCampListCsvInfo->camp01);
		//DYNAMIC_ASSERT(NULL != atkCampListCsvInfo5);
		//mAtkStrengthListCsvList[atkCampListCsvInfo->camp05] = atkCampListCsvInfo5;

	}

	SCampListCsv::~SCampListCsv()
	{
		mAtkStrengthListCsvList.clear();
	}

	InstanceAtkStrengthListCsvInfo* SCampListCsv::getAtkStrengthInfoByIndex(Int index)
	{
		CampIdType campId = mAtkCampListCsvInfo->camp[index];
		std::map<CampIdType, InstanceAtkStrengthListCsvInfo*>::iterator iter = mAtkStrengthListCsvList.find(campId);
		if (iter != mAtkStrengthListCsvList.end())
		{
			//ÕÒµ½
			return iter->second;
		}
		DYNAMIC_ASSERT(0);
		return NULL;
	}

	/******************************************************************************/
	SAtkInstance::SAtkInstance(InstanceListCsvInfo* instanceListInfo)
		:SInstanceBase(instanceListInfo)
		,mAtkListCsvInfo(NULL)
	{
		InstanceAtkListCsvInfo* atkListCsvInfo = InstanceAtkListCsv::getInstance().getInfoById(instanceListInfo->instanceListId);
		DYNAMIC_ASSERT(NULL != atkListCsvInfo);
		mAtkListCsvInfo = atkListCsvInfo;

		{
			SCampListCsv* campAtkListCsvInfo = MG_NEW SCampListCsv(atkListCsvInfo->campListId1);
			mAtkCampListCsvList.push_back(campAtkListCsvInfo);
		}
		
		{
			SCampListCsv* campDefenseListCsvInfo = MG_NEW SCampListCsv(atkListCsvInfo->campListId3);
			mDefenseCampListCsvList.push_back(campDefenseListCsvInfo);
		}
		
	}
	//--------------------------------------------------------------------------
	SAtkInstance::~SAtkInstance()
	{

	}

	//--------------------------------------------------------------------------
	InstanceAtkListCsvInfo* SAtkInstance::getAtkListCsvInfo()
	{
		return mAtkListCsvInfo;
	}

	SCampListCsv* SAtkInstance::getCampListByForce(FORCE force)
	{
		if (FORCE_ATTACK == force)
		{
			return *(mAtkCampListCsvList.begin());
		}
		else if (FORCE_DEFENSE == force)
		{
			return *(mDefenseCampListCsvList.begin());
		}
		else
		{
			DYNAMIC_ASSERT(0);
			return NULL;
		}

		DYNAMIC_ASSERT(0);
		return NULL;
	}

	//--------------------------------------------------------------------------
}