//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: VedioResourceConfig.h
//        Author: xvyadong
//          Date: 2012-2-9
//          Time: 15:15
// Description: 
//			1.读取视频配置
//
// modify History:
//      <author>    <time>        <descript>
//      xvyadong    2012-2-9      add
//////////////////////////////////////////////////////////////
//***********************************************************************************************
#ifndef _H_VIDEO_RES_CONFIG
#define _H_VIDEO_RES_CONFIG
//***********************************************************************************************
#include "GameFilePreqs.h"
//***********************************************************************************************
namespace MG
{
	enum
	{
		VIDEO_ID = 0,
		VIDEO_NAME,
		VIDEO_PRELOAD_TYPE,
		VIDEO_USAGE,
		VIDEO_LOOP_TYPE,
		VIDEO_PACK_ID,
		VIDEO_PATH,
		VIDEO_FILE_NAME,
		VIDEO_REPLACE_ID,
		VIDEO_DEF_VOLUMN,
	};
	//--------------------------------------------------------------------------
	//videoResID		资源ID;
	//videoUsage		视频用途;
	//preloadType		预读类型;
	//loopType			循环类型;
	//resPackID			所属资源包;
	//replaceResID		替代资源ID;
	//volumn			默认音量;
	//name				视频名称;
	//path				视频路径;
	//fileName			视频文件名;
	//--------------------------------------------------------------------------
	struct VideoResInfo
	{
		U32             videoResID			;
		U8				videoUsage			;
		U8				preloadType			;
		U8				loopType			;
		U32				resPackID			;
		U32				replaceResID		;
		U32				volumn				;
		Str8            name				;
		Str8            path				;
		Str8			fileName			;
	};
	//--------------------------------------------------------------------------
	class VideoResourceConfig
	{
	public:
		VideoResourceConfig(){;}
		~VideoResourceConfig();
		SINGLETON_INSTANCE(VideoResourceConfig);

	public:
		// MG_CN_MODIFY
		Bool                    load(Str16 fileName, IMGExternalPackManager* packManager = NULL);
		const VideoResInfo*		getVideoResourceInfo(U32 videoResID);

	private:

		void                    clear();

	private:

		std::map<U32, VideoResInfo*>  mVideoResourceList;

	};
}
//***********************************************************************************************
#endif
//***********************************************************************************************