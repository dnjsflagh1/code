//***********************************************************************************************
#include "stdafx.h"
#include "CharacterResourceConfig.h"
//***********************************************************************************************

namespace MG
{
  
	CharacterResourceConfig::~CharacterResourceConfig()
	{
		clear();

	}
    //-----------------------------------------------------------------------------------
	// MG_CN_MODIFY
	MG::Bool CharacterResourceConfig::load( Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/ )
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

			CharacterResInfo* res_info = new CharacterResInfo();
			MGStrOp::toU32(csvdata->mData[CHARACTER_ID].c_str(),res_info->id);
			MGStrOp::toU32(csvdata->mData[CHARACTER_TEMPLATEID].c_str(),res_info->templateid);
			res_info->name = csvdata->mData[CHARACTER_NAME].c_str();
			MGStrOp::toU32(csvdata->mData[CHARACTER_MAPLISTID].c_str(),res_info->maplistid);
            MGStrOp::toU32(csvdata->mData[CHARACTER_POINTRESId].c_str(),res_info->pointresid);
			MGStrOp::toI32(csvdata->mData[CHARACTER_MAPLISTTYPE].c_str(),(I32&)res_info->maplisttype);
			mCharacterResourceList[res_info->id] = res_info;
            
		}
		return true;

	}
    //-----------------------------------------------------------------------------------
	const CharacterResInfo* CharacterResourceConfig::getCharacterResourceInfo( U32 id )
	{
		std::map<U32,CharacterResInfo*> ::iterator it = mCharacterResourceList.find(id);
		if (it != mCharacterResourceList.end() )
		{
			return it->second;
		}
		return NULL;


	}
    //-----------------------------------------------------------------------------------
	void CharacterResourceConfig::clear()
	{
		std::map<U32, CharacterResInfo*>::iterator front = mCharacterResourceList.begin();
		std::map<U32, CharacterResInfo*>::iterator back = mCharacterResourceList.end();
		while (front != back)
		{
			delete front->second;
			++front;
		}

		mCharacterResourceList.clear();

	}
	 //-----------------------------------------------------------------------------------
	const std::map<U32, CharacterResInfo*> CharacterResourceConfig::getCharacterResourceInfoList() const
	{
		return mCharacterResourceList;

	}
	 //-----------------------------------------------------------------------------------  
	const Bool CharacterResourceConfig::verifyResourceCorrectness( U32 resID, U32 templateid, U32 maplistid, Int maplisttype ) 
	{
         std::map<U32,CharacterResInfo*> ::iterator it = mCharacterResourceList.find(resID);
		 if (it != mCharacterResourceList.end())
		 {
             CharacterResInfo* info = it->second;
             if (info->templateid == templateid && info->maplistid == maplistid && info->maplisttype == maplisttype)
             {
                    return true;
             }
			 else
			 {
				 return false;
			 }
		 }

		 return false;
	}

}