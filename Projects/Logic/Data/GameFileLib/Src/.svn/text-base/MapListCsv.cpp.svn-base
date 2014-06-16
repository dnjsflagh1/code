/******************************************************************************/

#include "stdafx.h"
#include "MapListCsv.h"
#include "ArtMapResCsv.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	MapListCsv::MapListCsv()
	{

	}

	//--------------------------------------------------------------------------
	MapListCsv::~MapListCsv()
	{

	}

	//--------------------------------------------------------------------------
	MapListCsvInfo* MapListCsv::getInfoByMapId(MapIdType id)
	{
		return mMapList.getData(id);
	}

	//--------------------------------------------------------------------------
	std::map<MapIdType, MapListCsvInfo*>* MapListCsv::getList()
	{
		return mMapList.getDataSet();
	}

	//--------------------------------------------------------------------------
	// MG_CN_MODIFY
	Bool MapListCsv::load(const Char16* FileName, IMGExternalPackManager* packManager/* = NULL*/)
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

			MapIdType mapListId = -1;
			MGStrOp::toU32(csvdata->mData[MLC_MapId].c_str(), mapListId);
			if (true == mMapList.hasData(mapListId))
			{
				DYNAMIC_ASSERT(0);
				continue;
			}

			Str mapGroupName = "";
			MGStrOp::toString(csvdata->mData[MLC_MapGroupName].c_str(), mapGroupName);

			Int mapOpenType = -1;
			MGStrOp::toI32(csvdata->mData[MLC_OpenType].c_str(), mapOpenType);

			Int mapType = -1;
			MGStrOp::toI32(csvdata->mData[MLC_MapType].c_str(), mapType);

			ArtMapResIdType artMapResId = -1;
			MGStrOp::toI32(csvdata->mData[MLC_ArtMapResId].c_str(), artMapResId);

			U32 audioResID = -1;
			MGStrOp::toU32(csvdata->mData[MLC_AudioResId].c_str(), audioResID);


			ArtPointResId rpgJumpPointId = 0;
			MGStrOp::toI32(csvdata->mData[MLC_RpgJumpPointId].c_str(), rpgJumpPointId);
			
			ArtPointResId rpgAlivePointId = 0;
			MGStrOp::toI32(csvdata->mData[MLC_RpgAlivePointId].c_str(), rpgAlivePointId);
			
			ArtPointResId slgAttackJumpPointId = 0;
			MGStrOp::toI32(csvdata->mData[MLC_SlgAttackJumpPointId].c_str(), slgAttackJumpPointId);
			
			ArtPointResId slgAttackAlivePointId = 0;
			MGStrOp::toI32(csvdata->mData[MLC_SlgAttackAlivePointId].c_str(), slgAttackAlivePointId);
			
			ArtPointResId slgDefenseJumpPointId = 0;
			MGStrOp::toI32(csvdata->mData[MLC_SlgDefenseJumpPointId].c_str(), slgDefenseJumpPointId);
			
			ArtPointResId slgDefenseAlivePointId = 0;
			MGStrOp::toI32(csvdata->mData[MLC_SlgDefenseAlivePointId].c_str(), slgDefenseAlivePointId);


			MapListCsvInfo* newMapInfo = mMapList.createOrRetrieve(mapListId, false);
			newMapInfo->mapListId		= mapListId;
			newMapInfo->mapGroupName	= csvdata->mData[MLC_MapGroupName];
			newMapInfo->mapName			= csvdata->mData[MLC_MapName];
			newMapInfo->mapText			= csvdata->mData[MLC_MapText];
			newMapInfo->mapOpenType		= (MapOpenType)mapOpenType;
			newMapInfo->mapType			= (MapType)mapType;
			newMapInfo->artMapResId		= artMapResId;
			newMapInfo->fileName		= csvdata->mData[MLC_MapFileName];
			newMapInfo->filePath		= csvdata->mData[MLC_MapFilePath];
			newMapInfo->audioResID		= audioResID;
			
			newMapInfo->rpgJumpPointId			= rpgJumpPointId;
			newMapInfo->rpgAlivePointId			= rpgAlivePointId;
			newMapInfo->slgAttackJumpPointId	= slgAttackJumpPointId;
			newMapInfo->slgAttackAlivePointId	= slgAttackAlivePointId;
			newMapInfo->slgDefenseJumpPointId	= slgDefenseJumpPointId;
			newMapInfo->slgDefenseAlivePointId	= slgDefenseAlivePointId;
		}

		return true;
	}
}