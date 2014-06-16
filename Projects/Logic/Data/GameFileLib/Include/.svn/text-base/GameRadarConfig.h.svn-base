//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: GameRadarConfig.h
//        Author: xvyadong
//          Date: 2012-5-26
//          Time: 15:15
// Description: 
//			1.∂¡»°–°µÿÕº≈‰÷√
//
// modify History:
//      <author>    <time>        <descript>
//      xvyadong    2012-5-26      add
//////////////////////////////////////////////////////////////
//***********************************************************************************************
#ifndef _H_GAME_RADAR_CONFIG
#define _H_GAME_RADAR_CONFIG
//***********************************************************************************************
#include "GameFilePreqs.h"
//***********************************************************************************************
namespace MG
{
	//--------------------------------------------------------------------------
	enum
	{
		GAME_RADAR_ID = 0,
		GAME_RADAR_NOTE,
		GAME_RADAR_NAME,
		GAME_RADAR_PRELOADTYPE,
		GAME_RADAR_RESPACKID,
		GAME_RADAR_FILEPATH,
		GAME_RADAR_FILENAME,
		GAME_RADAR_REPLACEID,

		GAME_RADAR_WORLD_CENTER_X,
		GAME_RADAR_WORLD_CENTER_Y,
		GAME_RADAR_WORLD_SIZE_X,
		GAME_RADAR_WORLD_SIZE_Y,
	};
	//--------------------------------------------------------------------------
	struct GameRadarConfigInfo
	{
		U32             ID;
		
		U8				preloadType;
		U32				resPackID;
		U32				replaceID;

		Vec2			worldCenter;
		Vec2			worldSize;

		Str				filePath;
		Str				fileName;
	};
	//--------------------------------------------------------------------------
	class GameRadarConfig
	{
	public:
		GameRadarConfig();
		~GameRadarConfig();
		SINGLETON_INSTANCE(GameRadarConfig);

	public:
		// MG_CN_MODIFY
		Bool                          load(Str16 fileName, IMGExternalPackManager* packManager = NULL);
		const GameRadarConfigInfo*	  getGameRadarConfigInfo(U32 radar_id);

	private:

		void						  clear();

	private:

		std::map<U32, GameRadarConfigInfo*>  mGameRadarConfig;

	};
}
//***********************************************************************************************
#endif
//***********************************************************************************************