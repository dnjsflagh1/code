/******************************************************************************/

#include "stdafx.h"
#include "RelationWorldMapPlaceCsv.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	RelationWorldMapPlaceCsv::RelationWorldMapPlaceCsv()
	{

	}

	//--------------------------------------------------------------------------
	RelationWorldMapPlaceCsv::~RelationWorldMapPlaceCsv()
	{

	}

	//--------------------------------------------------------------------------
	// MG_CN_MODIFY
	bool RelationWorldMapPlaceCsv::load(const Char16* FileName, IMGExternalPackManager* packManager/* = NULL*/)
	{
		// MG_CN_MODIFY
		return mBase.load(FileName, packManager);
	}

	//--------------------------------------------------------------------------
	RelationInfo* RelationWorldMapPlaceCsv::getRelationInfoByPlaceId(const PlaceIdType placeId)
	{
		return mBase.getRelationInfoByGameDataId(placeId);
	}

	//--------------------------------------------------------------------------
}