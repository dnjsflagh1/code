//***********************************************************************************************
#include "stdafx.h"
#include "GameSettingConfig.h"
//***********************************************************************************************
namespace MG
{
	//-----------------------------------------------------------------------------------
	GameSettingConfig::GameSettingConfig()
	{
		initPropertyWordMap();
	}
	//-----------------------------------------------------------------------------------
	GameSettingConfig::~GameSettingConfig()
	{
		mIni.destroy();
	}
	//-----------------------------------------------------------------------------------
	// MG_CN_MODIFY
	Bool GameSettingConfig::load( const Str16& fileName, IMGExternalPackManager* packManager/* = NULL*/)
	{
		if ( fileName.empty() )
			return false;

		if ( !mIni.create( fileName, packManager ) )
		{
			mIni.save( fileName );
		}

		mFileName = fileName;

		return true;
	}
	//-----------------------------------------------------------------------------------
	void GameSettingConfig::initPropertyWordMap()
	{
		mPropertyWordMap[GAME_SETTING_SECTION_DISPLAY] = L"Display";

		mPropertyWordMap[DISPLAY_SETTING_FULLSCREEN] = L"FullScreen";
		mPropertyWordMap[DISPLAY_SETTING_RESOLUTION] = L"Resolution";
		mPropertyWordMap[DISPLAY_SETTING_FSAA] = L"FSAA";
		mPropertyWordMap[DISPLAY_SETTING_VSYNC] = L"isVsync";
		mPropertyWordMap[DISPLAY_SETTING_SHADOW_LEVEL] = L"ShadowLevel";
		mPropertyWordMap[DISPLAY_SETTING_FOG_TYPE] = L"FogType";
		mPropertyWordMap[DISPLAY_SETTING_POST_FX_LEVEL] = L"PostFXLevel";
		mPropertyWordMap[DISPLAY_SETTING_MATERIAL_LEVEL] = L"MaterialLevel";
		mPropertyWordMap[DISPLAY_SETTING_PARTICLE_LEVEL] = L"ParticleLevel";
		mPropertyWordMap[DISPLAY_SETTING_ENABLE_WATER_REFLECTION] = L"EnableWaterReflection";
		mPropertyWordMap[DISPLAY_SETTING_ENABLE_HIGH_LEVEL_MODEL] = L"EnableHighLevelModel";
		mPropertyWordMap[DISPLAY_SETTING_ENABLE_HIGH_LEVEL_TEXTURE] = L"EnableHighLevelTexture";
		mPropertyWordMap[DISPLAY_SETTING_ENABLE_DETAIL_TERRAIN_OBJECT] = L"EnableDetailTerrainObject";

		mPropertyWordMap[GAME_SETTING_SECTION_SOUND] = L"Sound";
		mPropertyWordMap[SOUND_SETTING_ENABLE_SOUND] = L"EnableSound";
		mPropertyWordMap[SOUND_SETTING_ENABLE_BGM] = L"EnableBGM";

		//zit
		mPropertyWordMap[GAME_SETTING_SECTION_FONT] = L"Font";
		mPropertyWordMap[FONT_SETTING_FONTNAME] = L"curFontName";


        //debug
        mPropertyWordMap[GAME_SETTING_DEBUG] = L"Debug";
        mPropertyWordMap[DEBUG_NO_TERRAIN] = L"DebugNoTerrain";
        mPropertyWordMap[DEBUG_NO_TERRAIN] = L"DebugNoTerrain";
        mPropertyWordMap[DEBUG_NO_WATER] = L"DebugNoWater";
        mPropertyWordMap[DEBUG_NO_SKY] = L"DebugNoSky";
        mPropertyWordMap[DEBUG_NO_SPEEDTREE] = L"DebugNoSpeedTree";
        mPropertyWordMap[DEBUG_NO_SPEEDGRASS] = L"DebugNoGrass";
        mPropertyWordMap[DEBUG_NO_STATIC_ENTITY] = L"DebugNoStaticEntity";
        mPropertyWordMap[DEBUG_NO_STATIC_EFFECT] = L"DebugNoStaticEffect";
        mPropertyWordMap[DEBUG_NO_ENTITY] = L"DebugNoEntity";
        mPropertyWordMap[DEBUG_NO_BUILDING] = L"DebugNoBuilding";
        mPropertyWordMap[DEBUG_NO_NPC] = L"DebugNoNpc";
        mPropertyWordMap[DEBUG_NO_ITEM] = L"DebugNoItem";
        mPropertyWordMap[DEBUG_SHOW_BLOCK] = L"DebugShowBlock";

	}
	//-----------------------------------------------------------------------------------
	Bool GameSettingConfig::save( const Str16& fileName )
	{
		bool res = false;

		if ( !fileName.empty() || ( fileName.empty() && !mFileName.empty() ) )
		{
			res = mIni.save( mFileName );
		}

		return res;
	}
	//-----------------------------------------------------------------------------------
	Str16 GameSettingConfig::getSettingProperty(Int section_id, Int property_id )
	{
		if ( !mFileName.empty() )
		{
			Str16 section_key = mPropertyWordMap[section_id];
			Str16 property_key = mPropertyWordMap[property_id];

			mIni.setGroup( section_key );
			return mIni.getValue( property_key, L"" );
		}

		return L"";
	}
	//-----------------------------------------------------------------------------------
	void GameSettingConfig::setSettingProperty(Int section_id, Int property_id, Str16& val)
	{
		if ( !mFileName.empty() )
		{
			Str16 section_key = mPropertyWordMap[section_id];
			Str16 property_key = mPropertyWordMap[property_id];

			mIni.setGroupKeyValue(section_key, property_key, val);
		}
	}
	//-----------------------------------------------------------------------------------
	void GameSettingConfig::clear()
	{
		if ( !mFileName.empty() )
		{
			mIni.clear();
		}
	}
}