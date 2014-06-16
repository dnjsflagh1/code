/******************************************************************************/
#include "stdafx.h"
#include "MapType2RegionObject.h"
#include "InstanceListCsv.h"

/******************************************************************************/
namespace MG
{
	//-----------------------------------------------------------------------
	void MapType2RegionObject::MapTypeChangeRegionObject(const MapType mapType, const RegionIdType mapId, REGION_OBJ_TYPE& regionType, RegionIdType& regionId)
	{
		DYNAMIC_ASSERT(mapType > MT_Null && mapType < MT_Max);
		DYNAMIC_ASSERT(mapId > 0);

		REGION_OBJ_TYPE toRegionType = ROT_UNKNOWN;
		RegionIdType	toRegionId = mapId;

		switch (mapType)
		{
		case MT_Distribution:
			{
				toRegionType = ROT_MAP_DISTRIBUTION;
			}
			break;
		case MT_Place:
			{
				toRegionType = ROT_PLACE;
			}
			break;
		case MT_Building:
			{
				DEBUG_ASSERT_LOG(0, "副本类型[MT_Building]错误\n");
				DYNAMIC_ASSERT(0);
			}
			break;
		case MT_Direction:
			{
				DEBUG_ASSERT_LOG(0, "副本类型[MT_Direction]错误\n");
				DYNAMIC_ASSERT(0);
			}
			break;
		case MT_Instance:
			{
				InstanceListCsvInfo* instanceListInfo = InstanceListCsv::getInstance().getInfoById(mapId);

				DYNAMIC_ASSERT(NULL != instanceListInfo);
				if (instanceListInfo->instanceType <= InstanceType_Null || instanceListInfo->instanceType >= InstanceType_Max)
				{
					DEBUG_ASSERT_LOG(0, "副本类型[mapType]错误\n");
				}

				switch(instanceListInfo->instanceType)
				{
				case InstanceType_HomeLand:
					{
						toRegionType = ROT_HOME;
					}
					break;
				case InstanceType_Tiro:
					{
						toRegionType = ROT_TIRO;
					}
					break;
				case InstanceType_PVP:
					{
						toRegionType = ROT_PVP;
					}
					break;
				case InstanceType_PVE:
					{
						toRegionType = ROT_PVE;
					}
					break;
				case InstanceType_Growup:
					{
						toRegionType = ROT_GROWUP;
					}
					break;
				case InstanceType_Atk:
					{
						DYNAMIC_ASSERT(0);
						toRegionType = ROT_PLACE;
					}
					break;
				case InstanceType_History:
					{
						toRegionType = ROT_HISTORY;
					}
					break;
				case InstanceType_Sport:
					{
						toRegionType = ROT_SPORT;
					}
					break;
				case InstanceType_Fight:
					{
						toRegionType = ROT_FIGHT;
					}
					break;
				case InstanceType_Train:
					{
						toRegionType = ROT_TRAIN;
					}
					break;
				default:
					{
						DEBUG_ASSERT_LOG(0, "副本类型[instanceListInfo->instanceType]错误\n");
						DYNAMIC_ASSERT(0);
					}
					break;
				}

				toRegionId = mapId;
			}
			break;
		default:
			{
				DEBUG_ASSERT_LOG(0, "跳转类型错误");
			}
			break;
		}

		regionType	= toRegionType;
		regionId	= toRegionId;
	}

}