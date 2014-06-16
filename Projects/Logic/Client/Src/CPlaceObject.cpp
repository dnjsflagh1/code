
//*********************************************************************************************

//*********************************************************************************************

#include "stdafx.h"

#include "CPlaceObject.h"
#include "PlaceObjectData.h"
#include "CRegionManager.h"

//*********************************************************************************************
namespace MG
{
	//--------------------------------------------------------------------------------------
	CPlaceObject::CPlaceObject(PlaceListCsvInfo* placeInfo, DistrictIdType districtId)
		:CRegionObject(MG_NEW PlaceObjectData(placeInfo, districtId))
	{
	}

	//--------------------------------------------------------------------------------------
	CPlaceObject::~CPlaceObject()
	{
	}

	RegionIdType CPlaceObject::getRegionId()
	{
		return getPlaceData()->getPlaceId();
	}

	REGION_OBJ_TYPE CPlaceObject::getRegionType() const
	{
		return ROT_PLACE;
	}

	DistrictIdType CPlaceObject::getDistrictId()
	{
		return getPlaceData()->getDistrictListCsvInfo()->getDistrictId();
	}

	DistrictRankType CPlaceObject::getDistrictRankType()
	{
		DistrictListCsvInfo* districtListCsvInfo = getPlaceData()->getDistrictListCsvInfo();
		DYNAMIC_ASSERT(DRT_ZHOU == districtListCsvInfo->getRank() || 
			DRT_JUN == districtListCsvInfo->getRank() ||
			DRT_XIAN == districtListCsvInfo->getRank());
		return districtListCsvInfo->getRank();
	}

	//--------------------------------------------------------------------------------------
	PlaceObjectData* CPlaceObject::getPlaceData()
	{
		return (PlaceObjectData*)getData();
	}

	PlaceListCsvInfo* CPlaceObject::getPlaceListCsvInfo()
	{
		return getPlaceData()->getPlaceListCsvInfo();
	}

	//--------------------------------------------------------------------------------------
	CMapDistribution* CPlaceObject::getRootMapDistributionObj()
	{
		DistrictListCsvInfo* zhouDistrictInfo = NULL;
		DistrictListCsvInfo* districtListCsvInfo = getPlaceData()->getDistrictListCsvInfo();

		while(1)
		{
			if (DRT_ZHOU == districtListCsvInfo->getRank())
			{
				//找到 州
				zhouDistrictInfo = districtListCsvInfo;
				break;
			}
			else if(DRT_JUN == districtListCsvInfo->getRank() ||
				DRT_XIAN == districtListCsvInfo->getRank())
			{
				//继续找它的父亲
				districtListCsvInfo = districtListCsvInfo->getMaster();
			}
			else
			{
				DYNAMIC_ASSERT(0);
			}
		}
		
		DYNAMIC_ASSERT(NULL != zhouDistrictInfo);


		CMapDistribution* resultMapDistribution = NULL;
		std::map<MapDistributionIdType, CMapDistribution*>* mapDistributionObjList = CRegionManager::getInstance().getMapDistributionObjList();
		for(std::map<MapDistributionIdType, CMapDistribution*>::iterator iter = mapDistributionObjList->begin();
																		 iter != mapDistributionObjList->end();
																		 ++iter)
		{
			CMapDistribution* mapDistribution = iter->second;
			if (mapDistribution->getDistrictId() == zhouDistrictInfo->getDistrictId())
			{
				resultMapDistribution = mapDistribution;
				break;
			}
		}

		DYNAMIC_ASSERT(NULL != resultMapDistribution);
		return resultMapDistribution;
	}
	//--------------------------------------------------------------------------------------
}