
/******************************************************************************/

#include "stdafx.h"
#include "GameRadarConfig.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	GameRadarConfig::GameRadarConfig()
	{
		
	}

	//--------------------------------------------------------------------------
	GameRadarConfig::~GameRadarConfig()
	{

	}

	//--------------------------------------------------------------------------
	// MG_CN_MODIFY
	Bool GameRadarConfig::load(Str16 FileName, IMGExternalPackManager* packManager/* = NULL*/)
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

			U32 radar_id;
			MGStrOp::toU32(csvdata->mData[GAME_RADAR_ID].c_str(), radar_id);
			
			std::map<U32, GameRadarConfigInfo*>::iterator iter = mGameRadarConfig.find( radar_id );
			if ( iter != mGameRadarConfig.end() )
			{
				DEBUG_ASSERT_LOG(false,"has duplicate game camera setting in RadarSettngList.csv\n");
				continue;
			}

			GameRadarConfigInfo* radar_info = MG_NEW GameRadarConfigInfo;
			radar_info->ID = radar_id;

			U32 result = 0;
			MGStrOp::toU32(csvdata->mData[GAME_RADAR_PRELOADTYPE].c_str(), result);
			radar_info->preloadType = (U8)result;

			MGStrOp::toU32(csvdata->mData[GAME_RADAR_REPLACEID].c_str(), radar_info->replaceID);
			MGStrOp::toU32(csvdata->mData[GAME_RADAR_RESPACKID].c_str(), radar_info->resPackID);

			MGStrOp::toFlt(csvdata->mData[GAME_RADAR_WORLD_CENTER_X].c_str(), radar_info->worldCenter.x);
			MGStrOp::toFlt(csvdata->mData[GAME_RADAR_WORLD_CENTER_Y].c_str(), radar_info->worldCenter.y);
			MGStrOp::toFlt(csvdata->mData[GAME_RADAR_WORLD_SIZE_X].c_str(), radar_info->worldSize.x);
			MGStrOp::toFlt(csvdata->mData[GAME_RADAR_WORLD_SIZE_Y].c_str(), radar_info->worldSize.y);

			MGStrOp::toString(csvdata->mData[GAME_RADAR_FILEPATH].c_str(), radar_info->filePath );
			MGStrOp::toString(csvdata->mData[GAME_RADAR_FILENAME].c_str(), radar_info->fileName );

			radar_info->worldCenter.x /= 10.0f;
			radar_info->worldCenter.y /= 10.0f;

			radar_info->worldSize.x /= 10.0f;
			radar_info->worldSize.y /= 10.0f;

			mGameRadarConfig[ radar_id ] = radar_info;			
		}
		return true;
	}

	//--------------------------------------------------------------------------
	const GameRadarConfigInfo* GameRadarConfig::getGameRadarConfigInfo(U32 radar_id)
	{
		std::map<U32, GameRadarConfigInfo*>::iterator iter = mGameRadarConfig.find( radar_id );
		if ( iter != mGameRadarConfig.end() )
			return iter->second;
		return NULL;
	}

	//--------------------------------------------------------------------------
	void GameRadarConfig::clear()
	{
		for ( std::map<U32, GameRadarConfigInfo*>::iterator iter = mGameRadarConfig.begin(); iter != mGameRadarConfig.end(); iter++ )
		{
			MG_DELETE(iter->second);
		}
		mGameRadarConfig.clear();
	}

}