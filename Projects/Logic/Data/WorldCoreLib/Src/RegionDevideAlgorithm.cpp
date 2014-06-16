
/******************************************************************************/

#include "stdafx.h"

#include "RegionDevideAlgorithm.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------------------
	RegionDevideAlgorithm::RegionDevideAlgorithm()
	{

	}

	//--------------------------------------------------------------------------------------
	RegionDevideAlgorithm::~RegionDevideAlgorithm()
	{

	}

	//-----------------------------------------------------------------------------
	I32 RegionDevideAlgorithm::getActiveRegionIdVec( std::vector<RegionIdType>& regionIdVec,I32 divideIndex,I32 activeMapServerCount, 
												std::vector<RegionIdType>* allRegionList)
	{
		//计算出被激活的map区间  暂时根据读取map的顺序
		//TODO:
		I32 startIndex = 0;
		I32 endIndex = 0;
		//std::map<RegionIdType, MapInfo*>*	allMapList = mRegionObjectManager.getAllObjcetList();
		I32 allMapListCount = allRegionList->size();
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

		std::vector<RegionIdType>::iterator mapDataIt = allRegionList->begin();
		for(Int count = 0; mapDataIt != allRegionList->end(); mapDataIt++,count++)
		{
			if (count >= startIndex &&  count < endIndex)
			{
				if (*mapDataIt > 0)
				{
					regionIdVec.push_back(*mapDataIt);	
				}
				else
				{
					DYNAMIC_ASSERT(false);
				}
			}

		}
		return regionIdVec.size();
	}
}
