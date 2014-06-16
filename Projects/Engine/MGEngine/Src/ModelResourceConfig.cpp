/******************************************************************************/
#include "stdafx.h"
#include "ResourceManager.h"

// MG_CN_MODIFY
#include "EngineMain.h"
/******************************************************************************/

namespace MG
{
	//---------------------------------------------------------------------------------
	Bool ModelResourceConfig::load(CChar* fileName)
	{
		MG::ResourceManager::getSingletonPtr()->mModelDecls.clear();
		CsvReader csv_reader;
		
		Str16 wstrfileName;
		MG::MGStrOp::toString(fileName, wstrfileName);

		// MG_CN_MODIFY
		IMGExternalPackManager *packManager = EngineMain::getInstance().getPackManager();
		if(!csv_reader.create(wstrfileName, packManager))
		{
			MG_MESSAGE("ResourceManager::loadDeclarations ERROR");
			DYNAMIC_ASSERT(false);
			return false;
		}

		Int row_count = csv_reader.count();

		for ( int i = 0; i < row_count; i++ )
		{
			CsvData* csv_data = csv_reader.findValue(i);

			if ( !csv_data )
				continue;

			U32 model_id = 0;
			MGStrOp::toU32(csv_data->mData[MODEL_ID].c_str(), model_id);

			ModelDeclaration& decl = MG::ResourceManager::getSingletonPtr()->mModelDecls[model_id];

			decl.id = model_id;

			MGStrOp::toString(csv_data->mData[MODEL_NAME].c_str(), decl.name);
			MGStrOp::toString(csv_data->mData[MODEL_PATH].c_str(), decl.path);
			MGStrOp::toString(csv_data->mData[MODEL_MESH_FILE].c_str(), decl.meshFileName);
			MGStrOp::toString(csv_data->mData[MODEL_MESH_FILE_HIGH_LEVEL].c_str(), decl.meshHighLevelFileName);
			MGStrOp::toString(csv_data->mData[MODEL_ALLSIDE_BLOCK_MESH_FILE].c_str(), decl.blockAllSideMeshFileName);
			MGStrOp::toString(csv_data->mData[MODEL_INSIDE_BLOCK_MESH_FILE].c_str(), decl.blockInSideMeshFileName);
			MGStrOp::toString(csv_data->mData[MODEL_OUTSIDE_BLOCK_MESH_FILE].c_str(), decl.blockOutSideMeshFileName);
			MGStrOp::toString(csv_data->mData[MODEL_ROAD_MESH_FILE].c_str(), decl.RoadMeshFileName);
			MGStrOp::toString(csv_data->mData[MODEL_PASSAGE_MESH_FILE].c_str(), decl.PassageMeshFileName);
			MGStrOp::toString(csv_data->mData[MODEL_SKELETON_FILE].c_str(), decl.skeletonFileName);
			MGStrOp::toString(csv_data->mData[MODEL_ACTION_FILE].c_str(), decl.actionFileName);
			MGStrOp::toString(csv_data->mData[MODEL_MATERIAL_FILE].c_str(), decl.materialFileName);
			MGStrOp::toString(csv_data->mData[MODEL_GROUP_NAME].c_str(), decl.group);

			MGStrOp::toU32(csv_data->mData[MODEL_PRELOAD_TYPE].c_str(), (U32&)decl.preloadType);
			MGStrOp::toU32(csv_data->mData[MODEL_USEAGE].c_str(), (U32&)decl.modelUsage);
			MGStrOp::toU32(csv_data->mData[MODEL_RESOURCE_PACK_ID].c_str(), decl.resPackID);
			MGStrOp::toU32(csv_data->mData[MODEL_REPLACE_ID].c_str(), decl.replaceId);

			//---------------------------------------------------------------------------------
			//模型缩放信息
			U32 zoonX,zoonY,zoonZ; //策划填的模型x,yz缩放(1000代表原始大小，0也表示不缩放)
			MGStrOp::toU32(csv_data->mData[MODEL_ZOONX].c_str(), zoonX);
			MGStrOp::toU32(csv_data->mData[MODEL_ZOONX].c_str(), zoonY);
			MGStrOp::toU32(csv_data->mData[MODEL_ZOONX].c_str(), zoonZ);
			if (zoonX == 0)
				zoonX = 1000;
			if (zoonY == 0)
				zoonY = 1000;
			if (zoonZ == 0)
				zoonZ = 1000;
			decl.zoonX = (Flt)zoonX/1000.0f;
			decl.zoonY = (Flt)zoonY/1000.0f;
			decl.zoonZ = (Flt)zoonZ/1000.0f;

			I32 offsetX; //策划填的模型悬空(单位分米),游戏中单位为1 meter
			MGStrOp::toI32(csv_data->mData[MODEL_OFFSETY].c_str(), offsetX);
			decl.offsetY = (Flt)offsetX/10.0f;

			MGStrOp::toFlt(csv_data->mData[MODEL_PATHER_RADIUS].c_str(), decl.patherRadius);
			decl.patherRadius /= 10;
			
			//read material declaration file
			MaterialResourceConfig::getInstance().loadMaterialResource(&decl);
			//read action declaration file
			ActionResourceConfig::getInstance().load(&decl);
		}

		ActionResourceConfig::getInstance().showErrorList();

		return true;
	}
	//------------------------------------------------------------------------------------------------
	void ModelResourceConfig::unLoad()
	{
		MG::ResourceManager::getSingletonPtr()->mModelDecls.clear();
	}
}
