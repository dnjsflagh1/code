//******************************************************************************************
#include "stdafx.h"
#include "VideoResourceConfig.h"
//******************************************************************************************
namespace MG
{
	VideoResourceConfig::~VideoResourceConfig()
	{
		clear();
	}
	//-----------------------------------------------------------------------------------
	// MG_CN_MODIFY
	MG::Bool VideoResourceConfig::load( Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/)
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

			VideoResInfo* res_info = new VideoResInfo;

			MGStrOp::toU32(csvdata->mData[VIDEO_ID].c_str(),      res_info->videoResID     );
			MGStrOp::toU32(csvdata->mData[VIDEO_PRELOAD_TYPE].c_str(),      (U32&)res_info->preloadType  );
			MGStrOp::toU32(csvdata->mData[VIDEO_USAGE].c_str(),      (U32&)res_info->videoUsage     );
			MGStrOp::toU32(csvdata->mData[VIDEO_LOOP_TYPE].c_str(),      (U32&)res_info->loopType  );

			MGStrOp::toU32(csvdata->mData[VIDEO_PACK_ID].c_str(),      res_info->replaceResID	);
			MGStrOp::toU32(csvdata->mData[VIDEO_REPLACE_ID].c_str(),      res_info->replaceResID     );
			MGStrOp::toU32(csvdata->mData[VIDEO_DEF_VOLUMN].c_str(),      res_info->volumn	);
			
			MGStrOp::toString(csvdata->mData[VIDEO_NAME].c_str(),   res_info->name	        );
			MGStrOp::toString(csvdata->mData[VIDEO_PATH].c_str(),   res_info->path	        );
			MGStrOp::toString(csvdata->mData[VIDEO_FILE_NAME].c_str(),   res_info->fileName	        );

			mVideoResourceList[res_info->videoResID] = res_info;
		}

		return true;
	}
	//-----------------------------------------------------------------------------------
	const VideoResInfo* VideoResourceConfig::getVideoResourceInfo( U32 id )
	{
		std::map<U32, VideoResInfo*>::iterator it = mVideoResourceList.find(id);
		if (it != mVideoResourceList.end())
		{
			return it->second;
		}
		return NULL;
	}
	//-----------------------------------------------------------------------------------
	void VideoResourceConfig::clear()
	{
		std::map<U32, VideoResInfo*>::iterator front = mVideoResourceList.begin();
		std::map<U32, VideoResInfo*>::iterator back = mVideoResourceList.end();
		while (front != back)
		{
			delete front->second;
			++front;
		}

		mVideoResourceList.clear();
	}
}
