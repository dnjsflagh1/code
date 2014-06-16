//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: RelationWorldMapAreaCsv.h
//        Author: yuanlinhu
//          Date: 2012-3-6
//          Time: 14:28
//   Description: 
//			∂¡»° RelationWorldMapArea.Csv ±Ì
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-6      add
//////////////////////////////////////////////////////////////

//*************************************************************************************************//

#ifndef _RELATION_WORLD_MAP_AREA_CSV_
#define _RELATION_WORLD_MAP_AREA_CSV_

//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "RelationCsvBase.h"

//*************************************************************************************************//

namespace MG
{
	class RelationWorldMapAreaCsv
	{
	public:
		RelationWorldMapAreaCsv();
		~RelationWorldMapAreaCsv();
		SINGLETON_INSTANCE(RelationWorldMapAreaCsv);
		// MG_CN_MODIFY
		bool		load(const Char16* FileName, IMGExternalPackManager* packManager = NULL);

		RelationInfo*	getRelationInfoByAreaId(const AreaIdType areaId);

	private:
		RelationCsvBase			mBase;
	};
}

#endif	//_RELATION_WORLD_MAP_AREA_CSV_