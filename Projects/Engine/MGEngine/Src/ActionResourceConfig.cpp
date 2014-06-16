/******************************************************************************/
#include "stdafx.h"
#include "ResourceManager.h"

// MG_CN_MODIFY
#include "EngineMain.h"
/******************************************************************************/

namespace MG
{
	//---------------------------------------------------------------------------------
	Bool ActionResourceConfig::load(ModelDeclaration* modelDecl)
	{
		if ( !modelDecl )
			return false;

		if ( modelDecl->actionFileName.empty() )
		{
			if ( modelDecl->modelUsage == MODEL_USEAGE_CHAR )
			{
				Str8 error_msg = "ResourceManager::load action csv file ERROR: " + modelDecl->name;
				error_msg += '\n';
				errorList += (error_msg);
			}

			return false;
		}
			
		// return false if not found action file;
		size_t i = modelDecl->actionFileName.find_last_of(".");
		if ( i == Str8::npos )
		{
			Str8 error_msg = "ResourceManager::load action csv file ERROR: " + modelDecl->name;
			error_msg += '\n';
			errorList += (error_msg);

			return false;
		}

		// return false if action file is not csv file;
		Str8 strExtend = modelDecl->actionFileName.substr(i + 1);
		if ( strcmp(strExtend.c_str(), "csv" ) != 0 &&
			strcmp(strExtend.c_str(), "action") != 0 )
		{
			Str8 error_msg = "ResourceManager::load action declaration file ERROR: " + modelDecl->name;
			error_msg += '\n';
			errorList += (error_msg);

			return false;
		}

		Str final_path = modelDecl->path + "\\" + modelDecl->actionFileName;
		Str16 wstr_final_path;
		MG::MGStrOp::toString(final_path.c_str(), wstr_final_path);

		CsvReader csv_reader;
		// MG_CN_MODIFY
		IMGExternalPackManager *packManager = EngineMain::getInstance().getPackManager();
		if(!csv_reader.create(wstr_final_path, packManager))
		{
			/*此处暂时先注掉*/
			/*Str8 error_msg = "ResourceManager::load action declaration file ERROR: " + final_path;
			MG_MESSAGE(error_msg.c_str());
			DYNAMIC_ASSERT(false);*/
			Str8 error_msg = "ResourceManager::load action declaration file ERROR: " + modelDecl->name;
			error_msg += '\n';
			errorList += (error_msg);

			return false;
		}

		Int row_count = csv_reader.count();

		if ( row_count <= 0 )
			return false;

		MG::ResourceManager::ActionDeclsInfo& declInfos = MG::ResourceManager::getSingletonPtr()->mActionDeclInfos[modelDecl->id];

		for ( int i = 0; i < row_count; i++ )
		{
			CsvData* csv_data = csv_reader.findValue(i);

			if ( !csv_data )
				continue;

			// Splicing actual action name
			Str action_name;
			Str action_weapon_group;
			Str action_ride_group;

			MGStrOp::toString(csv_data->mData[ACTION_NAME].c_str(), action_name);
			MGStrOp::toString(csv_data->mData[ACTION_WEAPON_GROUP].c_str(), action_weapon_group);
			MGStrOp::toString(csv_data->mData[ACTION_RIDE_GROUP].c_str(), action_ride_group);

			if ( !action_weapon_group.empty() )
			{
				action_weapon_group += '_';
			}

			if ( !action_ride_group.empty() )
			{
				action_ride_group += '_';
			}

			action_name = action_weapon_group + action_ride_group + action_name;

			// insert action declaration into map
			{
				ActionDeclaration* decl = MG_NEW ActionDeclaration;

				decl->name = action_name;

				MGStrOp::toString(csv_data->mData[ACTION_RESNAME].c_str(), decl->resource);
				MGStrOp::toString(csv_data->mData[ACTION_RESPATH].c_str(), decl->resourcePath);

				MGStrOp::toFlt(csv_data->mData[ACTION_TIME].c_str(), decl->time);
				MGStrOp::toFlt(csv_data->mData[ACTION_SPEED].c_str(), decl->speed);

				U32 result = 0;
				MGStrOp::toU32(csv_data->mData[ACTION_LOOP].c_str(), result);
				decl->isLoop = (result == 2);

				if ( csv_data->mData.size() > ACTION_LOOP + 1 )
				{
					MGStrOp::toU32(csv_data->mData[ACTION_REVERSE].c_str(), result);
					decl->isReverse = (result == 2);

					MGStrOp::toU32(csv_data->mData[ACTION_FREEZE].c_str(), result);
					decl->isStopLastFrame = (result == 2);
				}

				MG::ResourceManager::ActionDecls::iterator iter = declInfos.decls.find( decl->name );
				if ( iter != declInfos.decls.end() )
					MG_DELETE( iter->second );

				declInfos.decls[ action_name ] = decl;
			}
		}

		return true;
	}
	//------------------------------------------------------------------------------------------------
	void ActionResourceConfig::unLoad()
	{
		MG::ResourceManager::getSingletonPtr()->unLoadActionDecls();
	}
	//------------------------------------------------------------------------------------------------

	void ActionResourceConfig::showErrorList()
	{
		if ( !errorList.empty() )
		{
			MG_MESSAGE(errorList.c_str());
			errorList.clear();
		}
	}
}
