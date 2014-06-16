/******************************************************************************/

#include "stdafx.h"
#include "RelationPlaceMapBuildingCsv.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	RelationPlaceMapBuildingCsv::RelationPlaceMapBuildingCsv()
	{

	}

	//--------------------------------------------------------------------------
	RelationPlaceMapBuildingCsv::~RelationPlaceMapBuildingCsv()
	{

	}

	//--------------------------------------------------------------------------
	// MG_CN_MODIFY
	bool RelationPlaceMapBuildingCsv::load(const Char16* FileName, IMGExternalPackManager* packManager/* = NULL*/)
	{
		// MG_CN_MODIFY
		return mBase.load(FileName, packManager);
	}
}