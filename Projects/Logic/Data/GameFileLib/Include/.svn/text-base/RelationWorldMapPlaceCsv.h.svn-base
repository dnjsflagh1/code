//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: RelationWorldMapPlaceCsv.h
//        Author: yuanlinhu
//          Date: 2012-3-9
//          Time: 14:17
//   Description: 
//			∂¡»° RelationWorldMapPlace.csv±Ì 
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-9      add
//////////////////////////////////////////////////////////////

//*************************************************************************************************//

#ifndef _RELATION_WORLD_MAP_PLACE_CSV_
#define _RELATION_WORLD_MAP_PLACE_CSV_

//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "RelationCsvBase.h"

//*************************************************************************************************//

namespace MG
{
	class RelationWorldMapPlaceCsv
	{
	public:
		RelationWorldMapPlaceCsv();
		~RelationWorldMapPlaceCsv();
		SINGLETON_INSTANCE(RelationWorldMapPlaceCsv);
		// MG_CN_MODIFY
		bool load(const Char16* FileName, IMGExternalPackManager* packManager = NULL);

		RelationInfo*	getRelationInfoByPlaceId(const PlaceIdType placeId);

	private:
		RelationCsvBase			mBase;
	};
}

#endif	//_RELATION_WORLD_MAP_PLACE_CSV_