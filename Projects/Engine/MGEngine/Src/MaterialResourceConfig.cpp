/******************************************************************************/
#include "stdafx.h"
#include "ResourceManager.h"
#include "MaterialManager.h"

// MG_CN_MODIFY
#include "EngineMain.h"
/******************************************************************************/

namespace MG
{
	//---------------------------------------------------------------------------------
	Bool MaterialResourceConfig::loadMaterialResource(ModelDeclaration* decl_ptr)
	{
		if ( !decl_ptr )
			return false;

		if ( decl_ptr->materialFileName.empty() )
			return false;

		// if not csv file, return false;
		size_t i = decl_ptr->materialFileName.find_last_of(".");
		if ( i == Str8::npos )
		{
			return false;
		}
		Str8 strExtend = decl_ptr->materialFileName.substr(i + 1);
		if ( strcmp(strExtend.c_str(), "csv" ) != 0 )
		{
			return false;
		}
		
		Str strFileFullPath = decl_ptr->path + "\\" + decl_ptr->materialFileName;
		Str16 wstrFileFullPath;
		MGStrOp::toString(strFileFullPath.c_str(), wstrFileFullPath);

		CsvReader csv_reader;
		// MG_CN_MODIFY
		IMGExternalPackManager *packManager = EngineMain::getInstance().getPackManager();
		if (!csv_reader.create(wstrFileFullPath, packManager))
		{
			std::string strLog = "";
			MGStrOp::toString(wstrFileFullPath.c_str(),strLog);
			
			MG_LOG(out_error,"Â·¾¶´íÎó£º%s\n",strLog.c_str());
			Str8 error_msg = "ResourceManager::load material declaration file ERROR: " + strFileFullPath;
			MG_MESSAGE(error_msg.c_str());
			//DYNAMIC_ASSERT(false);
			return false;
		}

		Str matGroupName = decl_ptr->path + "\\" + decl_ptr->materialFileName;
		ResourceManager::MaterialDecls& matDecls = ResourceManager::getSingletonPtr()->mMaterialDeclsGroups[matGroupName];
		matDecls.clear();
		
		int row_count = csv_reader.count();
		for ( int row = 0; row < row_count; row++ )
		{
			CsvData* csv_data = csv_reader.findValue(row);

			if ( !csv_data )
				continue;

			U32 matDecls_ID = 0;
			MGStrOp::toU32(csv_data->mData[MATERIAL_TEMPLATE_ID].c_str(), matDecls_ID);

			MaterialDeclaration *matDecl = new MaterialDeclaration;
			MG::MaterialManager::getInstance().praseScript( csv_data->mData, matDecl );
			matDecls.push_back(*matDecl);

			delete matDecl;
		}

		return true;
	}
	//---------------------------------------------------------------------------------
	Bool MaterialResourceConfig::loadMaterialParam(ModelDeclaration* decls)
	{
		/*MG::ResourceManager::getSingletonPtr()->mMaterialParamDecls.clear();

		if ( !decls->materialFileName )
			return false;

		Str16 wstrFileName;
		MG::MGStrOp::toString(decls->materialFileName, wstrFileName);

		CsvReader csv_reader;
		if ( !csv_reader.create(wstrFileName) )
		{
			MG_MESSAGE("ResourceManager::load material param declarations ERROR");
			DYNAMIC_ASSERT(false);
			return false;
		}

		int row_count = csv_reader.count();

		for ( int row = 0; row < row_count; row++ )
		{
			CsvData* csv_data = csv_reader.findValue(row);

			if ( !csv_data )
				continue;

			U32 matParam_ID = 0;
			MGStrOp::toU32(csv_data->mData[MATERIAL_PARAM_ID].c_str(), matParam_ID);
			MaterialParamDeclaration& matDecl = ResourceManager::getSingletonPtr()->mMaterialParamDecls[matParam_ID];

			matDecl.matParamID = matParam_ID;
		}*/

		return true;
	}
	//------------------------------------------------------------------------------------------------
	void MaterialResourceConfig::unLoad()
	{
		MG::ResourceManager::getSingletonPtr()->mMaterialDeclsGroups.clear();
		//MG::ResourceManager::getSingletonPtr()->mMaterialParamDecls.clear();
	}
}
