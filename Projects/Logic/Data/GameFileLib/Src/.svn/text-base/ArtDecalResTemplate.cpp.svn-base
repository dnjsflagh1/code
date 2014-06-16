//******************************************************************************************
#include "stdafx.h"
#include "ArtDecalResTemplate.h"
//******************************************************************************************
namespace MG
{
	enum 
	{
		ID,
		NOTES,
		NAME,
		ADVANCETYPE,
		USETYPE,
		RESPACKID,				
		FILEPATH,				
		FILENAME,			
		REPLACERESID,		
	};

	ArtDecalResTemplate::ArtDecalResTemplate()
	{

	}
	//-------------------------------------------------------------------------------------------
	ArtDecalResTemplate::~ArtDecalResTemplate()
	{
		clear();
	}
	//-------------------------------------------------------------------------------------------
	// MG_CN_MODIFY
	Bool ArtDecalResTemplate::load(Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/)
	{
		CsvReader csvreader;
		// MG_CN_MODIFY
		if(!csvreader.create(fileName, packManager))
		{
			return false;
		}

		CsvData* csvdata = NULL;
		Int rowCount = csvreader.count();
		for(Int i = 0; i < rowCount; ++i)
		{
			csvdata = csvreader.findValue(i);
			if(!csvdata)
			{
				continue;
			}

			ArtDecalResInfo* tempInfo = MG_NEW ArtDecalResInfo;

			MGStrOp::toU32(csvdata->mData[ID].c_str(),	tempInfo->Id);
			UInt temp = 0;
			MGStrOp::toU32(csvdata->mData[ADVANCETYPE].c_str(), temp);
			tempInfo->advanceType = (DecalAdvanceType)temp;
			MGStrOp::toU32(csvdata->mData[USETYPE].c_str(), temp);
			tempInfo->useType = (DecalUseType)temp;
			MGStrOp::toU32(csvdata->mData[RESPACKID].c_str(), tempInfo->resPackId);
			tempInfo->filePath = csvdata->mData[FILEPATH];
			tempInfo->fileName = csvdata->mData[FILENAME];
			MGStrOp::toU32(csvdata->mData[REPLACERESID].c_str(), tempInfo->replaceResId);

			if (getArtDecalResInfo(tempInfo->Id))
			{
				DYNAMIC_ASSERT(false);
				MG_SAFE_DELETE(tempInfo);
				continue;
			}

			mArtDecalResInfoList[tempInfo->Id] = tempInfo;
		}

		return true;
	}
	//-------------------------------------------------------------------------------------------
	const ArtDecalResInfo* ArtDecalResTemplate::getArtDecalResInfo( UInt id )
	{
		std::map<U32, ArtDecalResInfo*>::iterator it = mArtDecalResInfoList.find(id);
		if (it != mArtDecalResInfoList.end())
		{
			return it->second;
		}
		return NULL;
	}
	//-------------------------------------------------------------------------------------------
	void ArtDecalResTemplate::clear()
	{
		std::map<U32, ArtDecalResInfo*>::iterator it = mArtDecalResInfoList.begin();
		for (; it != mArtDecalResInfoList.end(); it++)
		{
			MG_SAFE_DELETE(it->second);
		}
		mArtDecalResInfoList.clear();
	}
	//-------------------------------------------------------------------------------------------

}