//***********************************************************************************************
#include "stdafx.h"
#include "AudioResourceConfig.h"
//***********************************************************************************************
namespace MG
{
	AudioResourceConfig::~AudioResourceConfig()
	{
		clear();
	}
	//-----------------------------------------------------------------------------------
	// MG_CN_MODIFY
	MG::Bool AudioResourceConfig::load( Str16 fileName, IMGExternalPackManager* packManager/* = NULL */)
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

			AudioResInfo* res_info = new AudioResInfo;

			MGStrOp::toU32(csvdata->mData[AUDIO_ID].c_str(),      res_info->audioResID   );
			U32 temp = 0;

			MGStrOp::toU32(csvdata->mData[AUDIO_PRELOAD_TYPE].c_str(),      temp);
			res_info->preloadType = (U8)temp;
			MGStrOp::toU32(csvdata->mData[AUDIO_USAGE].c_str(),      temp     );
             res_info->audioUsage = (U8)temp;
			MGStrOp::toU32(csvdata->mData[AUDIO_LOOP_TYPE].c_str(),      temp  );
             res_info->loopType = (U8)temp;

			MGStrOp::toU32(csvdata->mData[AUDIO_PACK_ID].c_str(),      res_info->replaceResID	);
			MGStrOp::toU32(csvdata->mData[AUDIO_REPLACE_ID].c_str(),      res_info->replaceResID     );
			MGStrOp::toU32(csvdata->mData[AUDIO_DEF_VOLUMN].c_str(),      res_info->volumn	);
			MGStrOp::toU32(csvdata->mData[AUDIO_DISTANCE].c_str(),   res_info->distance       );
			MGStrOp::toI32(csvdata->mData[AUDIO_VOLUMNCHANGE].c_str(),   res_info->volumnChange	        );

			MGStrOp::toString(csvdata->mData[AUDIO_NAME].c_str(),   res_info->name	        );
			MGStrOp::toString(csvdata->mData[AUDIO_FILE_NAME].c_str(),   res_info->fileName	        );
			MGStrOp::toString(csvdata->mData[AUDIO_FILE_PATH].c_str(),  res_info->filePath);

			mAudioResourceList[res_info->audioResID] = res_info;
		}

		return true;
	}
	//-----------------------------------------------------------------------------------
	const AudioResInfo* AudioResourceConfig::getAudioResourceInfo( U32 id )
	{
		std::map<U32, AudioResInfo*>::iterator it = mAudioResourceList.find(id);
		if (it != mAudioResourceList.end())
		{
			return it->second;
		}
		return NULL;
	}
	//-----------------------------------------------------------------------------------
	void AudioResourceConfig::clear()
	{
		std::map<U32, AudioResInfo*>::iterator front = mAudioResourceList.begin();
		std::map<U32, AudioResInfo*>::iterator back = mAudioResourceList.end();
		while (front != back)
		{
			delete front->second;
			++front;
		}

		mAudioResourceList.clear();
	}

	std::map<U32, AudioResInfo*> AudioResourceConfig::getAudioResourceList()
	{
		return mAudioResourceList;

	}

	std::map<U32, AudioResInfo*> AudioResourceConfig::getPreloadAudioResourceInfo()
	{
        std::map<U32, AudioResInfo*> tempAudioList;
		if (!mAudioResourceList.empty())
		{
			std::map<U32, AudioResInfo*>::iterator It = mAudioResourceList.begin();
			while (It != mAudioResourceList.end())
			{
                if ((It->second)->preloadType == 1)
                {
					tempAudioList[(It->second)->audioResID] = It->second;
                }
				
				It++;
			}
		}

		return tempAudioList;

	}
}