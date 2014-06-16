//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Common\Game\WorldCoreLib\Include\RegionDevide.h
//        Author: yuanlinhu
//          Date: 2012-3-30
//          Time: 16:46
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-30      add
//////////////////////////////////////////////////////////////

/******************************************************************************/
#ifndef _REGION_DEVIDE_ALGORITHM_H_
#define _REGION_DEVIDE_ALGORITHM_H_
/******************************************************************************/

#include "WorldCorePreqs.h"

/******************************************************************************/
namespace MG
{
	class RegionDevideAlgorithm
	{
	public:
		RegionDevideAlgorithm();
		~RegionDevideAlgorithm();
		SINGLETON_INSTANCE(RegionDevideAlgorithm);

		I32 getActiveRegionIdVec( std::vector<RegionIdType>& regionIdVec,I32 divideIndex,I32 activeMapServerCount, std::vector<RegionIdType>* allRegionList);
	};
}

#endif	//_REGION_DEVIDE_ALGORITHM_H_