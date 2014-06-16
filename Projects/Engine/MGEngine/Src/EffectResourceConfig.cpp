/******************************************************************************/
#include "stdafx.h"
#include "ResourceManager.h"

// MG_CN_MODIFY
#include "EngineMain.h"
/******************************************************************************/

namespace MG
{
	//---------------------------------------------------------------------------------
	Bool EffectResourceConfig::load(CChar* commonEffectFile, CChar* waterEffectFile, CChar* grassEffectFile, CChar* effectComponentfile)
	{		
		unLoad();

		Str16 wszfileName;


        if ( commonEffectFile )
        {
            MG::MGStrOp::toString(commonEffectFile, wszfileName);
            loadCommonEffect(wszfileName.c_str());
        }

		if ( waterEffectFile )
		{
			MG::MGStrOp::toString(waterEffectFile, wszfileName);
			loadWaterEffect(wszfileName.c_str());
		}

		if ( grassEffectFile )
		{
			MG::MGStrOp::toString(grassEffectFile, wszfileName);
			loadGrassEffect(wszfileName.c_str());
		}

		if ( effectComponentfile )
		{
			MG::MGStrOp::toString(effectComponentfile, wszfileName);
			loadEffectComponent(wszfileName.c_str());
		}

		return true;
	}
	//---------------------------------------------------------------------------------
	Bool EffectResourceConfig::loadCommonEffect(CChar16* filename)
	{
		CsvReader csv_reader;

		// MG_CN_MODIFY
		IMGExternalPackManager *packManager = EngineMain::getInstance().getPackManager();
		if(!csv_reader.create(filename, packManager))
		{
			Str16 error_msg = L"ResourceManager::load effect resource file ERROR: \n";
			error_msg += filename;

			MG_MESSAGE(error_msg.c_str());
			DYNAMIC_ASSERT(false);
			return false;
		}

		Int row_count = csv_reader.count();

		for ( int i = 0; i < row_count; i++ )
		{
			CsvData* csv_data = csv_reader.findValue(i);

			if ( !csv_data )
				continue;

			U32 res_id = 0;
			MGStrOp::toU32(csv_data->mData[EFFECT_RESOURCE_ID].c_str(), res_id);

			EffectResourceDeclaration& effectElementResDecl = MG::ResourceManager::getSingletonPtr()->mEffectElementResDecls[res_id];

			effectElementResDecl.ResID = res_id;

			MGStrOp::toString(csv_data->mData[EFFECT_RESOURCE_NAME].c_str(), effectElementResDecl.name);
			MGStrOp::toString(csv_data->mData[EFFECT_RESOURCE_FILEPATH].c_str(), effectElementResDecl.filePath);
			MGStrOp::toString(csv_data->mData[EFFECT_RESOURCE_FILENAME].c_str(), effectElementResDecl.fileName);
			MGStrOp::toString(csv_data->mData[EFFECT_RESOURCE_BINDBONE].c_str(), effectElementResDecl.bindBoneName);

			MGStrOp::toU32(csv_data->mData[EFFECT_RESOURCE_RESPACKID].c_str(), effectElementResDecl.respackID);
			MGStrOp::toU32(csv_data->mData[EFFECT_RESOURCE_REPLACERRESID].c_str(), effectElementResDecl.replaceResID);
			MGStrOp::toU32(csv_data->mData[EFFECT_RESOURCE_BINDBOX].c_str(), effectElementResDecl.bindBoxHeightRate);

			U32 result = 0;
			MGStrOp::toU32(csv_data->mData[EFFECT_RESOURCE_PRELOADTYPE].c_str(), result);
			effectElementResDecl.preloadType = result;

			MGStrOp::toU32(csv_data->mData[EFFECT_RESOURCE_LOOPTYPE].c_str(), result);
			effectElementResDecl.loopType = result;

			MGStrOp::toU32(csv_data->mData[EFFECT_RESOURCE_USAGE].c_str(), result);
			effectElementResDecl.useage = result;
		}

		return true;
	};
	//---------------------------------------------------------------------------------
	MG::Bool EffectResourceConfig::loadEffectComponent( CChar16* effectComponentfile )
	{
		CsvReader csv_reader;

		// MG_CN_MODIFY
		IMGExternalPackManager *packManager = EngineMain::getInstance().getPackManager();
		if(!csv_reader.create(effectComponentfile, packManager))
		{
			Str16 error_msg = L"ResourceManager::load effect resource file ERROR: \n";
			error_msg += effectComponentfile;

			MG_MESSAGE(error_msg.c_str());
			DYNAMIC_ASSERT(false);
			return false;
		}

		Int row_count = csv_reader.count();

		for ( int i = 0; i < row_count; i++ )
		{
			CsvData* csv_data = csv_reader.findValue(i);

			if ( !csv_data )
				continue;

			U32 res_id = 0;
			MGStrOp::toU32(csv_data->mData[EFFECT_COMPONENT_RESOURCE_ID].c_str(), res_id);

			EffectComponentResourceDeclaration& effectComponentElementResDecl = MG::ResourceManager::getSingletonPtr()->mEffectComponentElementResDecls[res_id];

			effectComponentElementResDecl.ResID = res_id;

			MGStrOp::toString(csv_data->mData[EFFECT_COMPONENT_RESOURCE_NAME].c_str(), effectComponentElementResDecl.name);
			MGStrOp::toString(csv_data->mData[EFFECT_COMPONENT_RESOURCE_FILEPATH].c_str(), effectComponentElementResDecl.filePath);
			MGStrOp::toString(csv_data->mData[EFFECT_COMPONENT_RESOURCE_FILENAME].c_str(), effectComponentElementResDecl.fileName);

			MGStrOp::toU32(csv_data->mData[EFFECT_COMPONENT_RESOURCE_RESPACKID].c_str(), effectComponentElementResDecl.respackID);
			MGStrOp::toU32(csv_data->mData[EFFECT_COMPONENT_RESOURCE_REPLACERRESID].c_str(), effectComponentElementResDecl.replaceResID);

			U32 result = 0;
			MGStrOp::toU32(csv_data->mData[EFFECT_COMPONENT_RESOURCE_PRELOADTYPE].c_str(), result);
			effectComponentElementResDecl.preloadType = result;

			MGStrOp::toU32(csv_data->mData[EFFECT_COMPONENT_RESOURCE_USAGE].c_str(), result);
			effectComponentElementResDecl.useage = result;
		}

		return true;
	}
	//---------------------------------------------------------------------------------
	Bool EffectResourceConfig::loadGrassEffect(CChar16* filename)
	{
		CsvReader csv_reader;

		// MG_CN_MODIFY
		IMGExternalPackManager *packManager = EngineMain::getInstance().getPackManager();
		if(!csv_reader.create(filename, packManager))
		{
			Str16 error_msg = L"ResourceManager::load grass effect resource file ERROR: \n";
			error_msg += filename;

			MG_MESSAGE(error_msg.c_str());
			DYNAMIC_ASSERT(false);
			return false;
		}

		Int row_count = csv_reader.count();

		for ( int i = 0; i < row_count; i++ )
		{
			CsvData* csv_data = csv_reader.findValue(i);

			if ( !csv_data )
				continue;

			GrassEffectResourceDeclaration effectResDecl;

			////set default value
			//{
			//	effectResDecl.grassEffectID = 0;
			//	effectResDecl.grassSwingFactor = 2.5f;
			//	effectResDecl.grassSwingVelocity = Vec2( 0.15f, 0.22f );
			//}
			
			MGStrOp::toU32(csv_data->mData[GRASS_EFFECT_ID].c_str(), effectResDecl.grassEffectID);
			MGStrOp::toFlt(csv_data->mData[GRASS_EFFECT_SWING_VELOCITY_X].c_str(), effectResDecl.grassSwingVelocity.x);
			MGStrOp::toFlt(csv_data->mData[GRASS_EFFECT_SWING_VELOCITY_Z].c_str(), effectResDecl.grassSwingVelocity.y);
			MGStrOp::toFlt(csv_data->mData[GRASS_EFFECT_SWING_FACTOR].c_str(), effectResDecl.grassSwingFactor);

			MG::ResourceManager::getSingletonPtr()->mGrassEffectResDecls[effectResDecl.grassEffectID] = effectResDecl;
		}

		return true;
	}

    //---------------------------------------------------------------------------------
    Bool EffectResourceConfig::loadWaterEffect(CChar16* filename)
    {
        // MG_CN_MODIFY
        IMGExternalPackManager *packManager = EngineMain::getInstance().getPackManager();
        if(!mWaterEffectResourceFile.create(filename, packManager))
        {
            Str16 error_msg = L"ResourceManager::load water effect resource file ERROR: \n";
            error_msg += filename;

            MG_MESSAGE(error_msg.c_str());
            DYNAMIC_ASSERT(false);
            return false;
        }

        //////////////////////////////////////////////////////////////////////////
        mWaterEffectResourceFileName = filename;
        //////////////////////////////////////////////////////////////////////////

        reloadWaterEffect();
        
        return true;
    }

	//---------------------------------------------------------------------------------
	void EffectResourceConfig::unLoad()
	{
		MG::ResourceManager::getSingletonPtr()->mEffectElementResDecls.clear();
		MG::ResourceManager::getSingletonPtr()->mWaterEffectResDecls.clear();
		MG::ResourceManager::getSingletonPtr()->mGrassEffectResDecls.clear();

		mWaterEffectResourceFile.destroy();
	};

	//---------------------------------------------------------------------------------
	bool EffectResourceConfig::reloadWaterEffect()
	{
		MG::ResourceManager::getSingletonPtr()->mWaterEffectResDecls.clear();

        Int row_count = mWaterEffectResourceFile.count();

        for ( int i = 0; i < row_count; i++ )
        {
            CsvData* csv_data = mWaterEffectResourceFile.findValue(i);

            if ( !csv_data )
                continue;

            WaterEffectResourceDeclaration effectResDecl;

            MGStrOp::toU32(csv_data->mData[WATER_EFFECT_ID].c_str(), effectResDecl.waterEffectID);
            MGStrOp::toU32(csv_data->mData[WATER_EFFECT_USAGE].c_str(), effectResDecl.waterEffectUsage);
            MGStrOp::toString(csv_data->mData[WATER_EFFECT_DESC].c_str(), effectResDecl.waterEffectDesc);

            MGStrOp::toFlt(csv_data->mData[WATER_EFFECT_DEEP_COLOR_X].c_str(), effectResDecl.waterDeepColor.x);
            MGStrOp::toFlt(csv_data->mData[WATER_EFFECT_DEEP_COLOR_Y].c_str(), effectResDecl.waterDeepColor.y);
            MGStrOp::toFlt(csv_data->mData[WATER_EFFECT_DEEP_COLOR_Z].c_str(), effectResDecl.waterDeepColor.z);

            MGStrOp::toFlt(csv_data->mData[WATER_EFFECT_REFLECT_COLOR_X].c_str(), effectResDecl.waterReflectColor.x);
            MGStrOp::toFlt(csv_data->mData[WATER_EFFECT_REFLECT_COLOR_Y].c_str(), effectResDecl.waterReflectColor.y);
            MGStrOp::toFlt(csv_data->mData[WATER_EFFECT_REFLECT_COLOR_Z].c_str(), effectResDecl.waterReflectColor.z);
            MGStrOp::toFlt(csv_data->mData[WATER_EFFECT_REFLECT_COLOR_W].c_str(), effectResDecl.waterReflectColor.w);

            MGStrOp::toFlt(csv_data->mData[WATER_EFFECT_REFLECT_SCALSES_X].c_str(), effectResDecl.waterReflectScalses.x);
            MGStrOp::toFlt(csv_data->mData[WATER_EFFECT_REFLECT_SCALSES_Y].c_str(), effectResDecl.waterReflectScalses.y);
            MGStrOp::toFlt(csv_data->mData[WATER_EFFECT_REFLECT_SCALSES_Z].c_str(), effectResDecl.waterReflectScalses.z);
            MGStrOp::toFlt(csv_data->mData[WATER_EFFECT_REFLECT_SCALSES_W].c_str(), effectResDecl.waterReflectScalses.w);

            MGStrOp::toFlt(csv_data->mData[WATER_EFFECT_SPECULAR_COLOR_X].c_str(), effectResDecl.waterSpecularColor.x);
            MGStrOp::toFlt(csv_data->mData[WATER_EFFECT_SPECULAR_COLOR_Y].c_str(), effectResDecl.waterSpecularColor.y);
            MGStrOp::toFlt(csv_data->mData[WATER_EFFECT_SPECULAR_COLOR_Z].c_str(), effectResDecl.waterSpecularColor.z);

            MGStrOp::toFlt(csv_data->mData[WATER_EFFECT_SPECULAR_SCALSES_X].c_str(), effectResDecl.waterSpecularScalses.x);
            MGStrOp::toFlt(csv_data->mData[WATER_EFFECT_SPECULAR_SCALSES_Y].c_str(), effectResDecl.waterSpecularScalses.y);
            MGStrOp::toFlt(csv_data->mData[WATER_EFFECT_SPECULAR_SCALSES_Z].c_str(), effectResDecl.waterSpecularScalses.z);
            MGStrOp::toFlt(csv_data->mData[WATER_EFFECT_SPECULAR_SCALSES_W].c_str(), effectResDecl.waterSpecularScalses.w);

            MGStrOp::toFlt(csv_data->mData[WATER_EFFECT_REFRACT_SCALSES_X].c_str(), effectResDecl.waterRefractScalses.x);
            MGStrOp::toFlt(csv_data->mData[WATER_EFFECT_REFRACT_SCALSES_Y].c_str(), effectResDecl.waterRefractScalses.y);
            MGStrOp::toFlt(csv_data->mData[WATER_EFFECT_REFRACT_SCALSES_Z].c_str(), effectResDecl.waterRefractScalses.z);
            MGStrOp::toFlt(csv_data->mData[WATER_EFFECT_REFRACT_SCALSES_W].c_str(), effectResDecl.waterRefractScalses.w);

            MGStrOp::toFlt(csv_data->mData[WATER_EFFECT_BUMP_TEX_PARAMS_X].c_str(), effectResDecl.waterBumpTexParams.x);
            MGStrOp::toFlt(csv_data->mData[WATER_EFFECT_BUMP_TEX_PARAMS_Y].c_str(), effectResDecl.waterBumpTexParams.y);
            MGStrOp::toFlt(csv_data->mData[WATER_EFFECT_BUMP_TEX_PARAMS_Z].c_str(), effectResDecl.waterBumpTexParams.z);
            MGStrOp::toFlt(csv_data->mData[WATER_EFFECT_BUMP_TEX_PARAMS_W].c_str(), effectResDecl.waterBumpTexParams.w);

            MGStrOp::toString(csv_data->mData[WATER_EFFECT_SKY_CUBE_TEX_NAME].c_str(), effectResDecl.waterSkyCubeTexName);
            MGStrOp::toU32(csv_data->mData[WATER_EFFECT_BUMP_TEX_TYPE].c_str(), effectResDecl.waterBumpTexType);
            MGStrOp::toString(csv_data->mData[WATER_EFFECT_BUMP_TEX_NAME1].c_str(), effectResDecl.waterBumpTexName1);
            MGStrOp::toString(csv_data->mData[WATER_EFFECT_BUMP_TEX_NAME2].c_str(), effectResDecl.waterBumpTexName2);
            MGStrOp::toString(csv_data->mData[WATER_EFFECT_BUMP_TEX_NAME3].c_str(), effectResDecl.waterBumpTexName3);

            MGStrOp::toFlt(csv_data->mData[WATER_EFFECT_BUMP_TEX_ANIMATION_X].c_str(), effectResDecl.waterBumpTexAnim.x);
            MGStrOp::toFlt(csv_data->mData[WATER_EFFECT_BUMP_TEX_ANIMATION_Y].c_str(), effectResDecl.waterBumpTexAnim.y);
            MGStrOp::toFlt(csv_data->mData[WATER_EFFECT_BUMP_TEX_ANIMATION_Z].c_str(), effectResDecl.waterBumpTexAnim.z);
            MGStrOp::toFlt(csv_data->mData[WATER_EFFECT_BUMP_TEX_ANIMATION_W].c_str(), effectResDecl.waterBumpTexAnim.w);
            
            //save
            MG::ResourceManager::getSingletonPtr()->mWaterEffectResDecls[effectResDecl.waterEffectID] = effectResDecl;
        }

		return true;
	}

	//---------------------------------------------------------------------------------
	void EffectResourceConfig::modifyWaterEffect(U32 EffectID)
	{
		WaterEffectResourceDeclaration* effectResDecl = MG::ResourceManager::getSingletonPtr()->getWaterEffectResourceDeclaration(EffectID);
		if ( !effectResDecl )
			return;

		Str16 key;
		MGStrOp::toString(EffectID, key);
		CsvData* csv_data = mWaterEffectResourceFile.findValue(key);
		if ( !csv_data )
			return;

        MGStrOp::toString(effectResDecl->waterEffectUsage, csv_data->mData[WATER_EFFECT_USAGE]);

        MGStrOp::toString(effectResDecl->waterDeepColor.x, csv_data->mData[WATER_EFFECT_DEEP_COLOR_X]);
        MGStrOp::toString(effectResDecl->waterDeepColor.y, csv_data->mData[WATER_EFFECT_DEEP_COLOR_Y]);
        MGStrOp::toString(effectResDecl->waterDeepColor.z, csv_data->mData[WATER_EFFECT_DEEP_COLOR_Z]);

        MGStrOp::toString(effectResDecl->waterReflectColor.x, csv_data->mData[WATER_EFFECT_REFLECT_COLOR_X]);
        MGStrOp::toString(effectResDecl->waterReflectColor.y, csv_data->mData[WATER_EFFECT_REFLECT_COLOR_Y]);
        MGStrOp::toString(effectResDecl->waterReflectColor.z, csv_data->mData[WATER_EFFECT_REFLECT_COLOR_Z]);
        MGStrOp::toString(effectResDecl->waterReflectColor.w, csv_data->mData[WATER_EFFECT_REFLECT_COLOR_W]);

        MGStrOp::toString(effectResDecl->waterReflectScalses.x, csv_data->mData[WATER_EFFECT_REFLECT_SCALSES_X]);
        MGStrOp::toString(effectResDecl->waterReflectScalses.y, csv_data->mData[WATER_EFFECT_REFLECT_SCALSES_Y]);
        MGStrOp::toString(effectResDecl->waterReflectScalses.z, csv_data->mData[WATER_EFFECT_REFLECT_SCALSES_Z]);
        MGStrOp::toString(effectResDecl->waterReflectScalses.w, csv_data->mData[WATER_EFFECT_REFLECT_SCALSES_W]);

        MGStrOp::toString(effectResDecl->waterSpecularColor.x, csv_data->mData[WATER_EFFECT_SPECULAR_COLOR_X]);
        MGStrOp::toString(effectResDecl->waterSpecularColor.y, csv_data->mData[WATER_EFFECT_SPECULAR_COLOR_Y]);
        MGStrOp::toString(effectResDecl->waterSpecularColor.z, csv_data->mData[WATER_EFFECT_SPECULAR_COLOR_Z]);

        MGStrOp::toString(effectResDecl->waterSpecularScalses.x, csv_data->mData[WATER_EFFECT_SPECULAR_SCALSES_X]);
        MGStrOp::toString(effectResDecl->waterSpecularScalses.y, csv_data->mData[WATER_EFFECT_SPECULAR_SCALSES_Y]);
        MGStrOp::toString(effectResDecl->waterSpecularScalses.z, csv_data->mData[WATER_EFFECT_SPECULAR_SCALSES_Z]);
        MGStrOp::toString(effectResDecl->waterSpecularScalses.w, csv_data->mData[WATER_EFFECT_SPECULAR_SCALSES_W]);

        MGStrOp::toString(effectResDecl->waterRefractScalses.x, csv_data->mData[WATER_EFFECT_REFRACT_SCALSES_X]);
        MGStrOp::toString(effectResDecl->waterRefractScalses.y, csv_data->mData[WATER_EFFECT_REFRACT_SCALSES_Y]);
        MGStrOp::toString(effectResDecl->waterRefractScalses.z, csv_data->mData[WATER_EFFECT_REFRACT_SCALSES_Z]);
        MGStrOp::toString(effectResDecl->waterRefractScalses.w, csv_data->mData[WATER_EFFECT_REFRACT_SCALSES_W]);

        MGStrOp::toString(effectResDecl->waterBumpTexParams.x, csv_data->mData[WATER_EFFECT_BUMP_TEX_PARAMS_X]);
        MGStrOp::toString(effectResDecl->waterBumpTexParams.y, csv_data->mData[WATER_EFFECT_BUMP_TEX_PARAMS_Y]);
        MGStrOp::toString(effectResDecl->waterBumpTexParams.z, csv_data->mData[WATER_EFFECT_BUMP_TEX_PARAMS_Z]);
        MGStrOp::toString(effectResDecl->waterBumpTexParams.w, csv_data->mData[WATER_EFFECT_BUMP_TEX_PARAMS_W]);

        MGStrOp::toString(effectResDecl->waterSkyCubeTexName.c_str(), csv_data->mData[WATER_EFFECT_SKY_CUBE_TEX_NAME]);
        MGStrOp::toString(effectResDecl->waterBumpTexType, csv_data->mData[WATER_EFFECT_BUMP_TEX_TYPE]);
        MGStrOp::toString(effectResDecl->waterBumpTexName1.c_str(), csv_data->mData[WATER_EFFECT_BUMP_TEX_NAME1]);
        MGStrOp::toString(effectResDecl->waterBumpTexName2.c_str(), csv_data->mData[WATER_EFFECT_BUMP_TEX_NAME2]);
        MGStrOp::toString(effectResDecl->waterBumpTexName3.c_str(), csv_data->mData[WATER_EFFECT_BUMP_TEX_NAME3]);

        MGStrOp::toString(effectResDecl->waterBumpTexAnim.x, csv_data->mData[WATER_EFFECT_BUMP_TEX_ANIMATION_X]);
        MGStrOp::toString(effectResDecl->waterBumpTexAnim.y, csv_data->mData[WATER_EFFECT_BUMP_TEX_ANIMATION_Y]);
        MGStrOp::toString(effectResDecl->waterBumpTexAnim.z, csv_data->mData[WATER_EFFECT_BUMP_TEX_ANIMATION_Z]);
        MGStrOp::toString(effectResDecl->waterBumpTexAnim.w, csv_data->mData[WATER_EFFECT_BUMP_TEX_ANIMATION_W]);
	}
	//---------------------------------------------------------------------------------
	void EffectResourceConfig::saveWaterEffect()
	{
		if ( mWaterEffectResourceFileName.empty() )
			return;

		mWaterEffectResourceFile.saveToFile(mWaterEffectResourceFileName);
	}

}


