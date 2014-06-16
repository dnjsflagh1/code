//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: AudioResourceConfig.h
//        Author: xvyadong
//          Date: 2012-2-9
//          Time: 15:15
// Description: 
//			1.��ȡ��Ƶ����
//
// modify History:
//      <author>    <time>        <descript>
//      xvyadong    2012-2-9      add
//////////////////////////////////////////////////////////////
//***********************************************************************************************
#ifndef _H_AUDIO_RES_CONFIG
#define _H_AUDIO_RES_CONFIG
//***********************************************************************************************
#include "GameFilePreqs.h"
//***********************************************************************************************
namespace MG
{
	//--------------------------------------------------------------------------
	enum
	{
		ART_INIT		= 0,
		ART_BACK_EFFECT = 1,		//��Ч			--����һ��
		ART_BACK_GROUND = 2,		//��������		--ѭ������
		ART_MAX,
	};
	//--------------------------------------------------------------------------
	enum
	{
		AUDIO_ID = 0,
		AUDIO_NAME =2,     //����Note�ֶ�
		AUDIO_PRELOAD_TYPE,
		AUDIO_USAGE,
		AUDIO_LOOP_TYPE,
		AUDIO_PACK_ID,
		AUDIO_FILE_PATH,
		AUDIO_FILE_NAME,
		AUDIO_REPLACE_ID,
		AUDIO_DEF_VOLUMN,
		AUDIO_DISTANCE,
		AUDIO_VOLUMNCHANGE,
	};
	//--------------------------------------------------------------------------
	//videoResID		��ԴID;
	//videoUsage		��Ƶ��;;
	//preloadType		Ԥ������;
	//loopType			ѭ������;
	//resPackID			������Դ��;
	//replaceResID		�����ԴID;
	//volumn			Ĭ������;
	//volumnChange		�����仯;
	//distance			������Դ�ľ���;
	//name				��Ƶ����;
	//path				��Ƶ·��;
	//fileName			��Ƶ�ļ���;
	//--------------------------------------------------------------------------
	struct AudioResInfo
	{
		U32             audioResID			;
		U8				audioUsage			;
		U8				preloadType			;
		U8				loopType			;
		U32				resPackID			;
		U32				replaceResID		;
		U32				volumn				;
		U32				distance			;
		Int				volumnChange		;
		Str8            name				;
		Str8			fileName			;
		Str8            filePath            ;
	};
	//--------------------------------------------------------------------------
	class AudioResourceConfig
	{
	public:
		AudioResourceConfig(){;}
		~AudioResourceConfig();
		SINGLETON_INSTANCE(AudioResourceConfig);

	public:
		// MG_CN_MODIFY
		Bool                          load(Str16 fileName, IMGExternalPackManager* packManager = NULL);
		const AudioResInfo*		      getAudioResourceInfo(U32 AudioResID);
		std::map<U32, AudioResInfo*>  getPreloadAudioResourceInfo();
        std::map<U32, AudioResInfo*>  getAudioResourceList();

	private:

		void                    clear();

	private:

		std::map<U32, AudioResInfo*>  mAudioResourceList;

	};
}
//***********************************************************************************************
#endif
//***********************************************************************************************