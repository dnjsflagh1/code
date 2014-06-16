//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: RelationPlaceMapBuildCsv.h
//        Author: yuanlinhu
//          Date: 2012-3-6
//          Time: 14:26
//   Description: 
//			∂¡»° RelationPlaceMapBuild.Csv ±Ì
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-6      add
//////////////////////////////////////////////////////////////

//*************************************************************************************************//

#ifndef _RELATION_PLACE_MAP_BUILDING_CSV_
#define _RELATION_PLACE_MAP_BUILDING_CSV_

//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "RelationCsvBase.h"

//*************************************************************************************************//

namespace MG
{

	class RelationPlaceMapBuildingCsv
	{
	public:
		RelationPlaceMapBuildingCsv();
		~RelationPlaceMapBuildingCsv();
		SINGLETON_INSTANCE(RelationPlaceMapBuildingCsv);
		// MG_CN_MODIFY
		bool load(const Char16* FileName, IMGExternalPackManager* packManager = NULL);

	private:
		RelationCsvBase			mBase;
	};
}

#endif	//_RELATION_PLACE_MAP_BUILDING_CSV_