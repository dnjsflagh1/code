//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: ClientSettingConfig.h
//        Author: xvyadong
//          Date: 2012-5-9
//          Time: 15:15
// Description: 
//			1.读取客户端配置
//
// modify History:
//      <author>    <time>        <descript>
//      xvyadong    2012-5-9      add
//////////////////////////////////////////////////////////////
//***********************************************************************************************
#ifndef _H_GAME_SETTING_CONFIG
#define _H_GAME_SETTING_CONFIG
//***********************************************************************************************
#include "GameFilePreqs.h"
//***********************************************************************************************
namespace MG
{
	enum
	{
		GAME_SETTING_SECTION_DISPLAY = 0,

		DISPLAY_SETTING_RESOLUTION,
		DISPLAY_SETTING_FULLSCREEN,
		DISPLAY_SETTING_VSYNC,
		DISPLAY_SETTING_FSAA,
		DISPLAY_SETTING_POST_FX_LEVEL,
		DISPLAY_SETTING_SHADOW_LEVEL,
		DISPLAY_SETTING_MATERIAL_LEVEL,
		DISPLAY_SETTING_PARTICLE_LEVEL,
		DISPLAY_SETTING_FOG_TYPE,

		DISPLAY_SETTING_ENABLE_WATER_REFLECTION,
		DISPLAY_SETTING_ENABLE_HIGH_LEVEL_MODEL,
		DISPLAY_SETTING_ENABLE_HIGH_LEVEL_TEXTURE,
		DISPLAY_SETTING_ENABLE_DETAIL_TERRAIN_OBJECT,

		GAME_SETTING_SECTION_SOUND,
		SOUND_SETTING_ENABLE_SOUND,
		SOUND_SETTING_ENABLE_BGM,

		GAME_SETTING_SECTION_FONT,
		FONT_SETTING_FONTNAME,

        //DEBUG
        GAME_SETTING_DEBUG,
        DEBUG_NO_TERRAIN,
        DEBUG_NO_WATER,
        DEBUG_NO_SKY,
        DEBUG_NO_SPEEDTREE,
		DEBUG_NO_SPEEDGRASS,
        DEBUG_NO_STATIC_ENTITY,
        DEBUG_NO_STATIC_EFFECT,
        DEBUG_NO_ENTITY,
        DEBUG_NO_BUILDING,
        DEBUG_NO_NPC,
        DEBUG_NO_ITEM,
        DEBUG_SHOW_BLOCK,
	};

	class GameSettingConfig
	{
	public:
		GameSettingConfig();
		~GameSettingConfig();
		SINGLETON_INSTANCE(GameSettingConfig);

	public:

		//读取
		Bool							load(const Str16& fileName, IMGExternalPackManager* packManager = NULL);

		Bool							save(const Str16& fileName = L"");

		void							clear();

		Str16							getSettingProperty(Int section_id, Int property_id );

		void							setSettingProperty(Int section_id, Int property_id, Str16& val );

	protected:

		void							initPropertyWordMap();

	protected:

		Str16							mFileName;
	
		UINI							mIni;

		std::map<U32, Str16>			mPropertyWordMap;

	};
}
//***********************************************************************************************
#endif
//***********************************************************************************************