//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: GameCameraConfig.h
//        Author: xvyadong
//          Date: 2012-5-26
//          Time: 15:15
// Description: 
//			1.读取摄像机镜头配置
//
// modify History:
//      <author>    <time>        <descript>
//      xvyadong    2012-5-26      add
//////////////////////////////////////////////////////////////
//***********************************************************************************************
#ifndef _H_GAME_CAMERA_CONFIG
#define _H_GAME_CAMERA_CONFIG
//***********************************************************************************************
#include "GameFilePreqs.h"
//***********************************************************************************************
namespace MG
{
	//--------------------------------------------------------------------------
	enum
	{
		GAME_CAMERA_TYPE_NORMAL = 1,
		GAME_CAMERA_TYPE_TRACK,
		GAME_CAMERA_TYPE_MAX
	};
	//--------------------------------------------------------------------------
	enum
	{
		GAME_CAMERA_CONFIG_ID = 0,
		GAME_CAMERA_CONFIG_NOTE,
		GAME_CAMERA_CONFIG_TYPE,

		GAME_CAMERA_MINBOARD_X,
		GAME_CAMERA_MAXBOARD_X,

		GAME_CAMERA_MINBOARD_Z,
		GAME_CAMERA_MAXBOARD_Z,

		GAME_CAMERA_LODHEIGHT_LEVEL1,
		GAME_CAMERA_LODANGLE_LEVEL1,

		GAME_CAMERA_LODHEIGHT_LEVEL2,
		GAME_CAMERA_LODANGLE_LEVEL2,

		GAME_CAMERA_LODHEIGHT_LEVEL3,
		GAME_CAMERA_LODANGLE_LEVEL3,

		GAME_CAMERA_LODHEIGHT_LEVEL4,
		GAME_CAMERA_LODANGLE_LEVEL4,

		GAME_CAMERA_DEF_PITCH,
		GAME_CAMERA_DEF_HEIGHT,
		
		GAME_CAMERA_MIN_PITCH,
		GAME_CAMERA_MAX_PITCH,

		GAME_CAMERA_MOVE_SPEED,
		GAME_CAMERA_ROLL_SPEED,
	};
	//--------------------------------------------------------------------------
	struct GameCameraConfigInfo
	{
		U32					camera_id;

		U32					camera_type;

		Vec3				camera_max_board;		//摄像机运动范围
		Vec3				camera_min_board;

		Flt					camera_default_height;	//默认高度
		Flt					camera_default_pitch;	//摄像机角度

		Flt					camera_max_pitch;		
		Flt					camera_min_pitch;		

		Flt					camera_move_speed;		//摄像机平移速度
		Flt					camera_roll_speed;		//摄像机在鼠标滚动时候移动速度

		std::vector<Flt>	camera_lod_height;
		std::vector<Flt>	camera_lod_angle;
	};
	//--------------------------------------------------------------------------
	class GameCameraConfig
	{
	public:
		GameCameraConfig();
		~GameCameraConfig();
		SINGLETON_INSTANCE(GameCameraConfig);

	public:
		// MG_CN_MODIFY
		Bool                          load(Str16 fileName, IMGExternalPackManager* packManager = NULL);
		const GameCameraConfigInfo*	  getGameCameraConfigInfo(U32 camera_id);

	private:

		void						  clear();

	private:

		std::map<U32, GameCameraConfigInfo*>  mGameCameraConfig;

	};
}
//***********************************************************************************************
#endif
//***********************************************************************************************