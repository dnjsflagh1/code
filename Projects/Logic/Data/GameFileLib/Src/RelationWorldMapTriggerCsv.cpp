/******************************************************************************/

#include "stdafx.h"
#include "RelationWorldMapTriggerCsv.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	RelationWorldMapTriggerCsv::RelationWorldMapTriggerCsv()
	{

	}

	//--------------------------------------------------------------------------
	RelationWorldMapTriggerCsv::~RelationWorldMapTriggerCsv()
	{

	}

	//--------------------------------------------------------------------------
	// MG_CN_MODIFY
	bool RelationWorldMapTriggerCsv::load(const Char16* FileName, IMGExternalPackManager* packManager/* = NULL*/)
	{
		// MG_CN_MODIFY
		return mBase.load(FileName, packManager);
	}

	//--------------------------------------------------------------------------
}