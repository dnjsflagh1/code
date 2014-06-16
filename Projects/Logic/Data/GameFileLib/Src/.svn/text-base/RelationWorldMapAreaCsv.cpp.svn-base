/******************************************************************************/

#include "stdafx.h"
#include "RelationWorldMapAreaCsv.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	RelationWorldMapAreaCsv::RelationWorldMapAreaCsv()
	{

	}

	//--------------------------------------------------------------------------
	RelationWorldMapAreaCsv::~RelationWorldMapAreaCsv()
	{

	}

	//--------------------------------------------------------------------------
	// MG_CN_MODIFY
	bool RelationWorldMapAreaCsv::load(const Char16* FileName, IMGExternalPackManager* packManager/* = NULL*/)
	{
		// MG_CN_MODIFY
		return mBase.load(FileName, packManager);
	}

	//--------------------------------------------------------------------------
	RelationInfo* RelationWorldMapAreaCsv::getRelationInfoByAreaId(const AreaIdType areaId)
	{
		return mBase.getRelationInfoByGameDataId(areaId);
	}

	//--------------------------------------------------------------------------
}