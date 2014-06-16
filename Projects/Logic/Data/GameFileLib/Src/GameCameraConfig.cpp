
/******************************************************************************/

#include "stdafx.h"
#include "GameCameraConfig.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	GameCameraConfig::GameCameraConfig()
	{
		
	}

	//--------------------------------------------------------------------------
	GameCameraConfig::~GameCameraConfig()
	{

	}

	//--------------------------------------------------------------------------
	// MG_CN_MODIFY
	Bool GameCameraConfig::load(Str16 FileName, IMGExternalPackManager* packManager/* = NULL*/)
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

			U32 camera_id;
			MGStrOp::toU32(csvdata->mData[GAME_CAMERA_CONFIG_ID].c_str(), camera_id);
			
			std::map<U32, GameCameraConfigInfo*>::iterator iter = mGameCameraConfig.find( camera_id );
			if ( iter != mGameCameraConfig.end() )
			{
				DEBUG_ASSERT_LOG(false,"has duplicate game camera setting in CameraSetList.csv\n");
				continue;
			}

			GameCameraConfigInfo* camera_config_info = MG_NEW GameCameraConfigInfo;
			camera_config_info->camera_id = camera_id;

			MGStrOp::toU32(csvdata->mData[GAME_CAMERA_CONFIG_TYPE].c_str(), camera_config_info->camera_type);

			MGStrOp::toFlt(csvdata->mData[GAME_CAMERA_DEF_PITCH].c_str(), camera_config_info->camera_default_pitch);
			MGStrOp::toFlt(csvdata->mData[GAME_CAMERA_DEF_HEIGHT].c_str(), camera_config_info->camera_default_height);

			MGStrOp::toFlt(csvdata->mData[GAME_CAMERA_MAX_PITCH].c_str(), camera_config_info->camera_max_pitch);
			MGStrOp::toFlt(csvdata->mData[GAME_CAMERA_MIN_PITCH].c_str(), camera_config_info->camera_min_pitch);

			MGStrOp::toFlt(csvdata->mData[GAME_CAMERA_MINBOARD_X].c_str(), camera_config_info->camera_min_board.x);
			camera_config_info->camera_min_board.y = 0;
			//MGStrOp::toFlt(csvdata->mData[GAME_CAMERA_MINBOARD_Y].c_str(), camera_config_info->camera_min_board.y);
			MGStrOp::toFlt(csvdata->mData[GAME_CAMERA_MINBOARD_Z].c_str(), camera_config_info->camera_min_board.z);

			MGStrOp::toFlt(csvdata->mData[GAME_CAMERA_MAXBOARD_X].c_str(), camera_config_info->camera_max_board.x);
			//MGStrOp::toFlt(csvdata->mData[GAME_CAMERA_MAXBOARD_Y].c_str(), camera_config_info->camera_max_board.y);
			camera_config_info->camera_max_board.y = 0;
			MGStrOp::toFlt(csvdata->mData[GAME_CAMERA_MAXBOARD_Z].c_str(), camera_config_info->camera_max_board.z);

			MGStrOp::toFlt(csvdata->mData[GAME_CAMERA_MOVE_SPEED].c_str(), camera_config_info->camera_move_speed);
			MGStrOp::toFlt(csvdata->mData[GAME_CAMERA_ROLL_SPEED].c_str(), camera_config_info->camera_roll_speed);

			Flt lod_height = 0.0f;
			Flt lod_angle = 0.0f;

			MGStrOp::toFlt(csvdata->mData[GAME_CAMERA_LODHEIGHT_LEVEL1].c_str(), lod_height);
			MGStrOp::toFlt(csvdata->mData[GAME_CAMERA_LODANGLE_LEVEL1].c_str(), lod_angle);

			camera_config_info->camera_lod_height.push_back( lod_height );
			camera_config_info->camera_lod_angle.push_back( lod_angle );

			MGStrOp::toFlt(csvdata->mData[GAME_CAMERA_LODHEIGHT_LEVEL2].c_str(), lod_height);
			MGStrOp::toFlt(csvdata->mData[GAME_CAMERA_LODANGLE_LEVEL2].c_str(), lod_angle);

			camera_config_info->camera_lod_height.push_back( lod_height );
			camera_config_info->camera_lod_angle.push_back( lod_angle );

			MGStrOp::toFlt(csvdata->mData[GAME_CAMERA_LODHEIGHT_LEVEL3].c_str(), lod_height);
			MGStrOp::toFlt(csvdata->mData[GAME_CAMERA_LODANGLE_LEVEL3].c_str(), lod_angle);

			camera_config_info->camera_lod_height.push_back( lod_height );
			camera_config_info->camera_lod_angle.push_back( lod_angle );

			MGStrOp::toFlt(csvdata->mData[GAME_CAMERA_LODHEIGHT_LEVEL4].c_str(), lod_height);
			MGStrOp::toFlt(csvdata->mData[GAME_CAMERA_LODANGLE_LEVEL4].c_str(), lod_angle);

			camera_config_info->camera_lod_height.push_back( lod_height );
			camera_config_info->camera_lod_angle.push_back( lod_angle );

			// 将所有的距离信息改为分米单位
			{
				for ( int i = 0; i < camera_config_info->camera_lod_height.size(); i++ )
				{
					camera_config_info->camera_lod_height[i] *= 0.1f;
				}

				camera_config_info->camera_default_height *= 0.1f;

				camera_config_info->camera_max_board *= 0.1f;
				camera_config_info->camera_min_board *= 0.1f;

				camera_config_info->camera_move_speed *= 0.1f;
			}

			mGameCameraConfig[ camera_id ] = camera_config_info;
		}
		return true;
	}

	//--------------------------------------------------------------------------
	const GameCameraConfigInfo* GameCameraConfig::getGameCameraConfigInfo(U32 camera_id)
	{
		std::map<U32, GameCameraConfigInfo*>::iterator iter = mGameCameraConfig.find( camera_id );
		if ( iter != mGameCameraConfig.end() )
			return iter->second;
		return NULL;
	}

	//--------------------------------------------------------------------------
	void GameCameraConfig::clear()
	{
		for ( std::map<U32, GameCameraConfigInfo*>::iterator iter = mGameCameraConfig.begin(); iter != mGameCameraConfig.end(); iter++ )
		{
			MG_DELETE(iter->second);
		}
		mGameCameraConfig.clear();
	}

}