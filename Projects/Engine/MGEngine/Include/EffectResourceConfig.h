#ifndef _EFFECT_RESOURCE_CONFIG_H_
#define _EFFECT_RESOURCE_CONFIG_H_
/******************************************************************************/
#include "EnginePreqs.h"
#include "IResourceManager.h"
/******************************************************************************/

namespace MG
{
	/******************************************************************************/
	//This class be used to reading CSV table 
	//"EffectComponentResourceConfig.csv"
	/******************************************************************************/
	enum
	{
		EFFECT_COMPONENT_RESOURCE_ID = 0,
		EFFECT_COMPONENT_RESOURCE_NOTES,
		EFFECT_COMPONENT_RESOURCE_NAME,
		EFFECT_COMPONENT_RESOURCE_PRELOADTYPE,
		EFFECT_COMPONENT_RESOURCE_USAGE,
		EFFECT_COMPONENT_RESOURCE_RESPACKID,
		EFFECT_COMPONENT_RESOURCE_FILEPATH,
		EFFECT_COMPONENT_RESOURCE_FILENAME,
		EFFECT_COMPONENT_RESOURCE_REPLACERRESID,
	};
	/******************************************************************************/
	//This class be used to reading CSV table 
	//"EffectResourceConfig.csv"
	/******************************************************************************/
	enum
	{
		EFFECT_RESOURCE_ID = 0,
		EFFECT_RESOURCE_NOTES,
		EFFECT_RESOURCE_NAME,
		EFFECT_RESOURCE_PRELOADTYPE,
		EFFECT_RESOURCE_USAGE,
		EFFECT_RESOURCE_LOOPTYPE,
		EFFECT_RESOURCE_RESPACKID,
		EFFECT_RESOURCE_FILEPATH,
		EFFECT_RESOURCE_FILENAME,
		EFFECT_RESOURCE_REPLACERRESID,
		EFFECT_RESOURCE_BINDBOX,
		EFFECT_RESOURCE_BINDBONE,
	};

	////////////////////////////////////////////////////
	//material effect grass
	////////////////////////////////////////////////////
	enum
	{
		GRASS_EFFECT_ID = 0,
		GRASS_EFFECT_DESC,
		GRASS_EFFECT_SWING_FACTOR,
		GRASS_EFFECT_SWING_VELOCITY_X,
		GRASS_EFFECT_SWING_VELOCITY_Z,
	};
	
	////////////////////////////////////////////////////
	//material effect water USAGE
	////////////////////////////////////////////////////
	enum
	{
		WATER_EFFECT_USAGE_NULL = 0,
		WATER_EFFECT_USAGE_LAKE,
        WATER_EFFECT_USAGE_RIVER,
		WATER_EFFECT_USAGE_WATER,
		WATER_EFFECT_USAGE_SEA,
	};

	enum
	{
		WATER_EFFECT_ID = 0,
		WATER_EFFECT_DESC,
		WATER_EFFECT_USAGE,

		WATER_EFFECT_DEEP_COLOR_X,
		WATER_EFFECT_DEEP_COLOR_Y,
        WATER_EFFECT_DEEP_COLOR_Z,

		WATER_EFFECT_REFLECT_COLOR_X,
		WATER_EFFECT_REFLECT_COLOR_Y,
		WATER_EFFECT_REFLECT_COLOR_Z,
		WATER_EFFECT_REFLECT_COLOR_W,

        WATER_EFFECT_REFLECT_SCALSES_X,
        WATER_EFFECT_REFLECT_SCALSES_Y,
        WATER_EFFECT_REFLECT_SCALSES_Z,
        WATER_EFFECT_REFLECT_SCALSES_W,

		WATER_EFFECT_SPECULAR_COLOR_X,
		WATER_EFFECT_SPECULAR_COLOR_Y,
		WATER_EFFECT_SPECULAR_COLOR_Z,

		WATER_EFFECT_SPECULAR_SCALSES_X,
        WATER_EFFECT_SPECULAR_SCALSES_Y,
        WATER_EFFECT_SPECULAR_SCALSES_Z,
        WATER_EFFECT_SPECULAR_SCALSES_W,

        WATER_EFFECT_REFRACT_SCALSES_X,
        WATER_EFFECT_REFRACT_SCALSES_Y,
        WATER_EFFECT_REFRACT_SCALSES_Z,
        WATER_EFFECT_REFRACT_SCALSES_W,

        WATER_EFFECT_BUMP_TEX_PARAMS_X,
        WATER_EFFECT_BUMP_TEX_PARAMS_Y,
        WATER_EFFECT_BUMP_TEX_PARAMS_Z,
        WATER_EFFECT_BUMP_TEX_PARAMS_W,

        WATER_EFFECT_SKY_CUBE_TEX_NAME,
        WATER_EFFECT_BUMP_TEX_TYPE,
        WATER_EFFECT_BUMP_TEX_NAME1,
        WATER_EFFECT_BUMP_TEX_NAME2,
        WATER_EFFECT_BUMP_TEX_NAME3,

        WATER_EFFECT_BUMP_TEX_ANIMATION_X,
        WATER_EFFECT_BUMP_TEX_ANIMATION_Y,
        WATER_EFFECT_BUMP_TEX_ANIMATION_Z,
        WATER_EFFECT_BUMP_TEX_ANIMATION_W,
	};
	
	class EffectResourceConfig
	{
	public:

		EffectResourceConfig(){};
		~EffectResourceConfig(){};
		SINGLETON_INSTANCE(EffectResourceConfig);

	public:

		Bool							load(CChar* commonEffectFile, CChar* waterEffectFile, CChar* grassEffectFile, CChar* effectComponentfile);
		//Load file for initializing common effect ( like particle ) resource declaration maps of resource manager;
		Bool							loadCommonEffect(CChar16* filename);
		//Load file for initializing water effect resource declaration maps of resource manager;
		Bool							loadWaterEffect(CChar16* filename);
		//Load file for initializing grass effect resource declaration maps of resource manager;
		Bool							loadGrassEffect(CChar16* filename);
		// 加载新的特效组件声明文件
		Bool							loadEffectComponent(CChar16* effectComponentfile);
		//UnLoad effect element resource declaration maps;
		void							unLoad();

	public:

        //for reload all effect
        bool							reloadWaterEffect();
		//for saving water effect csv file
		void							saveWaterEffect();
		//for saving single effect;
		void							modifyWaterEffect(U32 EffectID);

	private:

		//for load and save;
		CsvReader						mWaterEffectResourceFile;
		//file name to load
		Str16							mWaterEffectResourceFileName;								
	};
}

#endif

/******************************************************************************/