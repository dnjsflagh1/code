/******************************************************************************/

#include "stdafx.h"
#include "RelationWorldMapCharacterCsv.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	RelationWorldMapCharacterCsv::RelationWorldMapCharacterCsv()
	{

	}

	//--------------------------------------------------------------------------
	RelationWorldMapCharacterCsv::~RelationWorldMapCharacterCsv()
	{

	}

	//--------------------------------------------------------------------------
	// MG_CN_MODIFY
	bool RelationWorldMapCharacterCsv::load(const Char16* FileName, IMGExternalPackManager* packManager/* = NULL*/)
	{
		// MG_CN_MODIFY
		return mBase.load(FileName, packManager);
	}

	//--------------------------------------------------------------------------
}