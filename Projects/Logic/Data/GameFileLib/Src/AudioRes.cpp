//******************************************************************************************
#include "stdafx.h"
#include "AudioRes.h"
//******************************************************************************************
namespace MG
{
	//-----------------------------------------------------------------------------------------------
	enum 
	{
		COL_AUDIO_RES_ID		= 0,
		COL_AUDIO_RES_NOTE		= 1,
		COL_AUDIO_RES_TYPE		= 2,
		COL_AUDIO_RES_FILE_PATH = 3,
		COL_AUDIO_RES_FILE_NAME = 4,
	};
	
	//-----------------------------------------------------------------------------------------------
	AudioRes::AudioRes()
	{

	}
	//--------------------------------------------------------------------------------
	AudioRes::~AudioRes()
	{
	}
	//--------------------------------------------------------------------------------
	Bool AudioRes::load(Str16 fileName)
	{
		CsvReader csvreader;

		if(!csvreader.create(fileName))
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

			AudioResInfo* tempInfo = new AudioResInfo;

			MGStrOp::toString(csvdata->mData[COL_AUDIO_RES_ID].c_str(), tempInfo->id);

			U32 type = 0;
			MGStrOp::toU32(csvdata->mData[COL_AUDIO_RES_TYPE].c_str(), type);
			tempInfo->type		= (AudioResType)type;
			DYNAMIC_ASSERT(tempInfo->type > ART_INIT && tempInfo->type < ART_MAX);
			
			MGStrOp::toString(csvdata->mData[COL_AUDIO_RES_FILE_PATH].c_str(), tempInfo->filePath);
			MGStrOp::toString(csvdata->mData[COL_AUDIO_RES_FILE_NAME].c_str(), tempInfo->fileName);

			//tempInfo->id		= csvdata->mData[COL_AUDIO_RES_ID];
			
			//tempInfo->type		= (AudioResType)type;
			//tempInfo->filePath	= csvdata->mData[COL_AUDIO_RES_FILE_PATH];
			//tempInfo->fileName	= csvdata->mData[COL_AUDIO_RES_FILE_NAME];


			mAudioRes[tempInfo->id] = tempInfo;
		}

		return true;
	}

	//--------------------------------------------------------------------------------
	AudioResInfo* AudioRes::getAudioRsInfoById(Str id)
	{
		std::map<Str, AudioResInfo*>::iterator iter = mAudioRes.find(id);
		if (iter != mAudioRes.end())
		{
			return iter->second;
		}

		return NULL;
	}

}