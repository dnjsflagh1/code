//***********************************************************************************************
#include "stdafx.h"
#include "CreateClanResConfig.h"
//***********************************************************************************************

namespace MG
{

   //-----------------------------------------------------------------------------------
	CreateClanResConfig::~CreateClanResConfig()
	{
         clear();
	}
  //-----------------------------------------------------------------------------------
	// MG_CN_MODIFY
	MG::Bool CreateClanResConfig::load( Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/ )
	{ 
		CsvReader csvreader;
		// MG_CN_MODIFY
		if(!csvreader.create(fileName, packManager))
		{
			return false;
		}

		CsvData* csvdata = NULL;
		Int RowCount = csvreader.count();

		for(int i = 0; i < RowCount; ++i)
		{
			csvdata = csvreader.findValue(i);
			if(!csvdata)
			{
				continue;
			}

			CreateClanResInfo* res_info = new CreateClanResInfo();
			MGStrOp::toU32(csvdata->mData[CHARACTER_ID].c_str(),res_info->id);
			MGStrOp::toU32(csvdata->mData[CHARACTER_TEMPLATEID].c_str(),res_info->templateid);
			res_info->name = csvdata->mData[CHARACTER_NAME].c_str();

			mCreateClanResList[res_info->id] = res_info;

		}
		return true;


	}
   //-----------------------------------------------------------------------------------
	const CreateClanResInfo* CreateClanResConfig::getCreateResInfo( U32 id )
	{
		std::map<U32,CreateClanResInfo*> ::iterator it = mCreateClanResList.find(id);
		if (it != mCreateClanResList.end() )
		{
			return it->second;
		}
		return NULL;

	}
   //-----------------------------------------------------------------------------------
	const std::map<U32, CreateClanResInfo*> CreateClanResConfig::getCreateResInfoList() const
	{
             return mCreateClanResList;
	}
	//-----------------------------------------------------------------------------------			
	void CreateClanResConfig::clear()
	{
		std::map<U32, CreateClanResInfo*>::iterator front = mCreateClanResList.begin();
		std::map<U32, CreateClanResInfo*>::iterator back = mCreateClanResList.end();
		while (front != back)
		{
			delete front->second;
			++front;
		}

		mCreateClanResList.clear();
	}
	//-----------------------------------------------------------------------------------

}