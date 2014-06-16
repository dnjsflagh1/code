
/******************************************************************************/

#include "stdafx.h"
#include "RelationCsvBase.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	RelationCsvBase::RelationCsvBase()
	{

	}

	//--------------------------------------------------------------------------
	RelationCsvBase::~RelationCsvBase()
	{

	}

	//--------------------------------------------------------------------------
	// MG_CN_MODIFY
	Bool RelationCsvBase::load(const Char16* FileName, IMGExternalPackManager* packManager/* = NULL*/)
	{
		CsvReader csvreader;
		// MG_CN_MODIFY
		if(!csvreader.create(FileName, packManager))
		{
			return false;
		}

		CsvData* csvdata = NULL;
		Int RowCount = csvreader.count();

		for(Int i = 0; i < RowCount; ++i)
		{
			csvdata = csvreader.findValue(i);
			if(!csvdata)
			{
				continue;
			}

			RelationIdType relationId;
			MGStrOp::toI32(csvdata->mData[RCB_RelationId].c_str(), relationId);
			if (true == mRelationList.hasData(relationId))
			{
				DYNAMIC_ASSERT(0);
				continue;
			}

			MapIdType mapId;
			MGStrOp::toU32(csvdata->mData[RCB_MapId].c_str(), mapId);

			GameObjectIdType gameDataId;
			MGStrOp::toU64(csvdata->mData[RCB_GameDataId].c_str(), gameDataId);

			RelationInfo* newRelationInfo = mRelationList.createOrRetrieve(relationId, false);
			newRelationInfo->relationId	= relationId;
			newRelationInfo->mapId		= mapId;
			newRelationInfo->artName	= csvdata->mData[RCB_ArtName];
			newRelationInfo->gameDataId	= gameDataId;

			//mArtMapResList[id] = newArtMapRes;
		}

		return true;
	}

	//--------------------------------------------------------------------------
	RelationInfo* RelationCsvBase::getRelationInfoByGameDataId(const GameObjectIdType gameObjectId)
	{
		RelationInfo* retrunInfo = NULL;
		std::map<RelationIdType, RelationInfo*>* relationList = mRelationList.getDataSet();

		std::map<RelationIdType, RelationInfo*>::iterator iter = relationList->begin();
		for (iter = relationList->begin(); iter != relationList->end(); ++iter)
		{
			RelationInfo* info = iter->second;
			if (NULL != info && gameObjectId == info->gameDataId)
			{
				retrunInfo = info;
				break;
			}
		}

		return retrunInfo;
	}
	//--------------------------------------------------------------------------

}
