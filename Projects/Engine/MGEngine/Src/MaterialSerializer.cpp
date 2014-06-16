/******************************************************************************/
#include "stdafx.h"
#include "MGStrOp.h"
#include "MaterialResourceConfig.h"
#include "MaterialSerializer.h"
/******************************************************************************/

namespace MG
{
	Bool MaterialSerializer::parseScript(std::vector<std::wstring> stringVector, MaterialDeclaration* mat_decl)
	{
		if ( !mat_decl )
			return false;

		if ( stringVector.size() != MATERIAL_EFFECT_WATER_ID + 1)
			return false;

		//set default value
		{
			mat_decl->cullingHardWare           = (U8)CULL_NONE;
			mat_decl->cullingSoftWare           = (U8)MANUAL_CULL_NONE;
			mat_decl->isIgnoreBlendType         = 1;
			mat_decl->sceneBlendType            = (U8)SBT_REPLACE;
			mat_decl->sceneBlendFactorSrc       = (U8)SBF_ONE;
			mat_decl->sceneBlendFactorDest      = (U8)SBF_ZERO;
			mat_decl->alphaRejectionCmpFunc     = (U8)CMPF_ALWAYS_PASS;
			mat_decl->alphaRejectionValue       = 0;

		/*	mat_decl->textureScale              = Vec2(1.0f, 1.0f);
			mat_decl->textureRotate             = 0;
			mat_decl->textureRotateAnimation    = 0;
			mat_decl->textureScroll             = Vec2(0.0f, 0.0f);
			mat_decl->textureScrollAnimation    = Vec2(0.0f, 0.0f);

			mat_decl->useGrassEffect			= false;
			mat_decl->velocityGrassSwing.x		= 0.15f;
			mat_decl->velocityGrassSwing.y		= 0.22f;
			mat_decl->factorGrassSwing			= 2.5f;*/
		}

		U32 col_result;

		if ( !stringVector[MATERIAL_CULLING_MODE].empty() )
		{
			MGStrOp::toU32(stringVector[MATERIAL_CULLING_MODE].c_str(), col_result);
			mat_decl->cullingHardWare = (U8)col_result;
		}
		
		if ( !stringVector[MATERIAL_MANUALCULLING_MODE].empty() )
		{
			MGStrOp::toU32(stringVector[MATERIAL_MANUALCULLING_MODE].c_str(), col_result);
			mat_decl->cullingSoftWare = (U8)col_result;
		}

		if ( !stringVector[MATERIAL_SCENE_BLEND_MODE].empty() )
		{
			MGStrOp::toU32(stringVector[MATERIAL_SCENE_BLEND_MODE].c_str(), col_result);
			mat_decl->isIgnoreBlendType = col_result != 0;
		}

		if ( !stringVector[MATERIAL_SCENE_BLEND_TYPE].empty() )
		{
			MGStrOp::toU32(stringVector[MATERIAL_SCENE_BLEND_TYPE].c_str(), col_result);
			mat_decl->sceneBlendType = (U8)col_result;
		}

		if ( !stringVector[MATERIAL_SCENE_BLEND_FACTOR_SRC].empty() )
		{
			MGStrOp::toU32(stringVector[MATERIAL_SCENE_BLEND_FACTOR_SRC].c_str(), col_result);
			mat_decl->sceneBlendFactorSrc = (U8)col_result;
		}

		if ( !stringVector[MATERIAL_SCENE_BLEND_FACTOR_DEST].empty() )
		{
			MGStrOp::toU32(stringVector[MATERIAL_SCENE_BLEND_FACTOR_DEST].c_str(), col_result);
			mat_decl->sceneBlendFactorDest = (U8)col_result;
		}

		if ( !stringVector[MATERIAL_ALPHA_REJECTION_CMP].empty() )
		{
			MGStrOp::toU32(stringVector[MATERIAL_ALPHA_REJECTION_CMP].c_str(), col_result);
			mat_decl->alphaRejectionCmpFunc = (U8)col_result;
		}

		if ( !stringVector[MATERIAL_ALPHA_REJECTION_VALUE].empty() )
		{	
			MGStrOp::toU32(stringVector[MATERIAL_ALPHA_REJECTION_VALUE].c_str(), col_result);
			mat_decl->alphaRejectionValue = (U8)col_result;
		}	

		MGStrOp::toU32(stringVector[MATERIAL_TEMPLATE_ID].c_str(), mat_decl->matDeclID);
		MGStrOp::toString(stringVector[MATERIAL_TEXTURE_PATH].c_str(), mat_decl->texturePath);
		MGStrOp::toString(stringVector[MATERIAL_TEXTURE_DIFFUSE].c_str(), mat_decl->diffuseTextureName);
		MGStrOp::toString(stringVector[MATERIAL_TEXTURE_NORMAL].c_str(), mat_decl->normalTextureName);
		MGStrOp::toString(stringVector[MATERIAL_TEXTURE_AO].c_str(), mat_decl->aoTextureName);
		MGStrOp::toString(stringVector[MATERIAL_TEMPLATE_NAME].c_str(), mat_decl->materialTemplateName);
		
		if ( stringVector.size() > MATERIAL_TEXTURE_AO + 1)
		{
			MGStrOp::toU32(stringVector[MATERIAL_EFFECT_GRASS_ID].c_str(), mat_decl->effectGrassID);
			MGStrOp::toU32(stringVector[MATERIAL_EFFECT_WATER_ID].c_str(), mat_decl->effectWaterID);
		}

		/*CsvParseCullingMode::parse(stringVector[MATERIAL_CULLING_MODE], mat_decl->cullingHardWare, mat_decl->cullingSoftWare);
		CsvParseSceneBlendMode::parse(stringVector[MATERIAL_SCENE_BLEND], mat_decl->isUseBlendType, mat_decl->sceneBlendType, mat_decl->sceneBlendFactorSrc, mat_decl->sceneBlendFactorDest);
		CsvParseAlphaRejection::parse(stringVector[MATERIAL_ALPHA_REJECTION], mat_decl->alphaRejectionCmpFunc, mat_decl->alphaRejectionValue);*/

		return true;
	}
	
}


