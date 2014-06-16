/******************************************************************************/
#include "stdafx.h"
#include "ResourceManager.h"

// MG_CN_MODIFY
#include "EngineMain.h"
/******************************************************************************/

namespace MG
{
	//---------------------------------------------------------------------------------
	Bool EntityAccessoryResourceConfig::load(CChar* filename)
	{
		MG::ResourceManager::getSingletonPtr()->mEntityAccessoryDeclMap.clear();
		CsvReader csv_reader;

		Str16 wstrfileName;
		MG::MGStrOp::toString(filename, wstrfileName);

		// MG_CN_MODIFY
		IMGExternalPackManager *packManager = EngineMain::getInstance().getPackManager();
		if(!csv_reader.create(wstrfileName, packManager))
		{
			Str8 error_msg = "ResourceManager::load entity accessory resource declaration file ERROR: \n";
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

			U32 parent_id = 0;
			MGStrOp::toU32(csv_data->mData[ENTITY_ACCESSORY_PARENT_ID].c_str(), parent_id);

			ResourceManager::EntityAccessoryDecls& decls = MG::ResourceManager::getSingletonPtr()->mEntityAccessoryDeclMap[parent_id];
			
			{
				EntityAccessoryDeclaration* decl = MG_NEW EntityAccessoryDeclaration;

				MGStrOp::toU32(csv_data->mData[ENTITY_ACCESSORY_ID].c_str(), decl->accessoryID);
				MGStrOp::toU32(csv_data->mData[ENTITY_ACCESSORY_PARENT_ID].c_str(), decl->parentID);
				MGStrOp::toU32(csv_data->mData[ENTITY_ACCESSORY_RESOURCE_ID].c_str(), decl->resourceID);


				MGStrOp::toFlt(csv_data->mData[ENTITY_ACCESSORY_DERIVED_POS_X].c_str(), decl->derivedPos.x);
				MGStrOp::toFlt(csv_data->mData[ENTITY_ACCESSORY_DERIVED_POS_Y].c_str(), decl->derivedPos.y);
				MGStrOp::toFlt(csv_data->mData[ENTITY_ACCESSORY_DERIVED_POS_Z].c_str(), decl->derivedPos.z);

				MGStrOp::toFlt(csv_data->mData[ENTITY_ACCESSORY_DERIVED_QUA_X].c_str(), decl->derivedQuaternion.x);
				MGStrOp::toFlt(csv_data->mData[ENTITY_ACCESSORY_DERIVED_QUA_Y].c_str(), decl->derivedQuaternion.y);
				MGStrOp::toFlt(csv_data->mData[ENTITY_ACCESSORY_DERIVED_QUA_Z].c_str(), decl->derivedQuaternion.z);
				//MGStrOp::toFlt(csv_data->mData[ENTITY_ACCESSORY_DERIVED_QUA_W].c_str(), decl->derivedQuaternion.w);
				decl->derivedQuaternion.w = 1.0f;

				MGStrOp::toString(csv_data->mData[ENTITY_ACCESSORY_BIND_BONE].c_str(), decl->bindBoneName);

				U32 result;
				MGStrOp::toU32(csv_data->mData[ENTITY_ACCESSORY_RESOURCE_TYPE].c_str(), result);
				decl->resourceType = (U8)result;

				MGStrOp::toU32(csv_data->mData[ENTITY_ACCESSORY_DEP_LIFE].c_str(), result);
				decl->isDepositLifeTime = ( result == 0 ? false : true );

				MGStrOp::toU32(csv_data->mData[ENTITY_ACCESSORY_SYNC_ANIM].c_str(), result);
				decl->isSyncAnimation = ( result == 0 ? false : true );

				//把DEGREE值改为四元数
				{
					decl->derivedQuaternion.x = decl->derivedQuaternion.x / 180.0f * MG_PI;
					decl->derivedQuaternion.y = decl->derivedQuaternion.y / 180.0f * MG_PI;
					decl->derivedQuaternion.z = decl->derivedQuaternion.z / 180.0f * MG_PI;

					Qua quaternion;
					quaternion.FromAngleAxis(decl->derivedQuaternion.x, Vec3(0.0f, 1.0f, 0.0f));
					quaternion.FromAngleAxis(decl->derivedQuaternion.y, Vec3(0.0f, 0.0f, 1.0f));
					quaternion.FromAngleAxis(decl->derivedQuaternion.z, Vec3(1.0f, 0.0f, 0.0f));

					decl->derivedQuaternion.w = quaternion.w;
					decl->derivedQuaternion.x = quaternion.x;
					decl->derivedQuaternion.y = quaternion.y;
					decl->derivedQuaternion.z = quaternion.z;
				}
			
				decls.push_back( *decl );

				MG_SAFE_DELETE(decl);
			}
		}

		return true;
	};
	//---------------------------------------------------------------------------------
	void EntityAccessoryResourceConfig::unLoad()
	{
		MG::ResourceManager::getSingletonPtr()->mEntityAccessoryDeclMap.clear();
	};
}


