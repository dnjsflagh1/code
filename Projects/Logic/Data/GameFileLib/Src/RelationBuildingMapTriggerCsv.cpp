/******************************************************************************/

#include "stdafx.h"
#include "RelationBuildingMapTriggerCsv.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	RelationBuildingMapTriggerCsv::RelationBuildingMapTriggerCsv()
	{

	}

	//--------------------------------------------------------------------------
	RelationBuildingMapTriggerCsv::~RelationBuildingMapTriggerCsv()
	{

	}

	//--------------------------------------------------------------------------
	// MG_CN_MODIFY
	bool RelationBuildingMapTriggerCsv::load(const Char16* FileName, IMGExternalPackManager* packManager/* = NULL*/)
	{
		// MG_CN_MODIFY
		return mBase.load(FileName, packManager);
	}
}