/******************************************************************************/
#ifndef _MATERIAL_RESOURCE_CONFIG_H_
#define _MATERIAL_RESOURCE_CONFIG_H_
/******************************************************************************/
#include "EnginePreqs.h"
#include "IResourceManager.h"
/******************************************************************************/

namespace MG
{
	enum
	{
		MATERIAL_TEMPLATE_ID = 0,
		MATERIAL_TEMPLATE_NAME,
		
		MATERIAL_CULLING_MODE,
		MATERIAL_MANUALCULLING_MODE,

		MATERIAL_SCENE_BLEND_MODE,
		MATERIAL_SCENE_BLEND_TYPE,
		MATERIAL_SCENE_BLEND_FACTOR_SRC,
		MATERIAL_SCENE_BLEND_FACTOR_DEST,

		MATERIAL_ALPHA_REJECTION_CMP,
		MATERIAL_ALPHA_REJECTION_VALUE,

		MATERIAL_TEXTURE_PATH,
		MATERIAL_TEXTURE_DIFFUSE,
		MATERIAL_TEXTURE_NORMAL,
		MATERIAL_TEXTURE_AO,

		MATERIAL_EFFECT_GRASS_ID,
		MATERIAL_EFFECT_WATER_ID,

	/*	MATERIAL_EFFECT_GRASS_AVALIABLE,
		MATERIAL_EFFECT_GRASS_VELOCITY_X,
		MATERIAL_EFFECT_GRASS_VELOCITY_Z,
		MATERIAL_EFFECT_GRASS_FACTOR,

		MATERIAL_EFFECT_LAKE_AVALIABLE,
		MATERIAL_EFFECT_LAKE_PARAM,
		MATERIAL_EFFECT_LAKE_VELOCITY_Z,
		MATERIAL_EFFECT_LAKE_FACTOR,

		MATERIAL_TEXTURE_SCALE_X,
		MATERIAL_TEXTURE_SCALE_Y,
		
		MATERIAL_TEXTURE_ROTATE,
		MATERIAL_TEXTURE_ROTATE_ANIMATION,

		MATERIAL_TEXTURE_SCROLL_X,
		MATERIAL_TEXTURE_SCROLL_Y,
		MATERIAL_TEXTURE_SCROLL_X_ANIMATION,
		MATERIAL_TEXTURE_SCROLL_Y_ANIMATION,*/
	};

	enum
	{
		MATERIAL_PARAM_ID = 0,
		MATERIAL_PARAM_AMBIENT,
		MATERIAL_PARAM_DIFFUSE,
		MATERIAL_PARAM_SPECULAR,
	};

	/******************************************************************************/
	//This is a interface class for reading CSV table of material resource .
	/******************************************************************************/
	class MaterialResourceConfig
	{
	public:
		MaterialResourceConfig(){};
		~MaterialResourceConfig(){};
		SINGLETON_INSTANCE(MaterialResourceConfig);

	public:

		//Load file for initializing material declaration maps of resource manager;
		Bool							loadMaterialResource(ModelDeclaration* decls);
		//Load file for initializing material param declaration maps of resource manager;
		Bool							loadMaterialParam(ModelDeclaration* decls);
		//UnLoad model declaration maps;
		void							unLoad();
	};
}

#endif