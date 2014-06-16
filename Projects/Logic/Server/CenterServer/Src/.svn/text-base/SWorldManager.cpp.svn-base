
/******************************************************************************/

#include "stdafx.h"
#include "SWorldManager.h"

/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------
	SWorldManager::SWorldManager( )
		:mDBDriver(NULL)
	{

	}

	//--------------------------------------------------------------------------
	SWorldManager::~SWorldManager( )
	{

	}

	//--------------------------------------------------------------------------
	Bool SWorldManager::initialize(ServerLauncherInterface* launcher)
	{
		setDBDriver( launcher->getDBDriver() );

		//if (false == mRegionObjectManager.loadCsvAndCreateRegion())
		//{
		//	DYNAMIC_ASSERT(0);
		//	return false;
		//}

		//创建地图数据记录根据内存信息
		//createRegionDbRecordInfoByMemory();
		return true;
	}

	//--------------------------------------------------------------------------
	Bool SWorldManager::unInitialize()
	{
		return true;
	}

    //--------------------------------------------------------------------------
	void SWorldManager::setDBDriver(DBDriver* driver)
	{
		mDBDriver = driver;
	}

#if 0
	//-----------------------------------------------------------------------------
	I32 SWorldManager::getActiveMapsId( std::vector<IdType>& mapsId,I32 divideIndex,I32 activeMapServerCount )
	{
		//计算出被激活的map区间  暂时根据读取map的顺序
		//TODO:
		I32 startIndex = 0;
		I32 endIndex = 0;
		std::map<RegionIdType, SRegionObject*>* allMapList = mRegionObjectManager.getAllObjcetList();
		I32 allMapListCount = allMapList->size();
		I32 activeMapCount = allMapListCount / activeMapServerCount;
		I32 remainder = allMapListCount % activeMapServerCount;
		if (divideIndex < remainder  )
		{
			startIndex = (activeMapCount + 1) * divideIndex;
			endIndex	= (activeMapCount + 1) * (divideIndex + 1);

		}
		else
		{
			startIndex = activeMapCount * divideIndex + remainder;
			endIndex = activeMapCount  * (divideIndex + 1) + remainder; 
		}

		std::map<RegionIdType, SRegionObject*>::iterator mapDataIt = allMapList->begin();
		for(Int count = 0; mapDataIt != allMapList->end(); mapDataIt++,count++)
		{
			if (count >= startIndex &&  count < endIndex)
			{
				if (mapDataIt->second)
				{
					mapsId.push_back(mapDataIt->first);	
				}
				else
				{
					DYNAMIC_ASSERT(false);
				}
			}

		}
		return mapsId.size();
	}

#endif
	//--------------------------------------------------------------------------
}
