//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Common\DataSource\GameFileLib\Include\AudioRes.h
//        Author: yuanlinhu
//          Date: 2011-12-29
//          Time: 15:22
//   Description: 
//			Create File
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2011-12-29      add
//////////////////////////////////////////////////////////////

//******************************************************************************************
#ifndef _H_AUDIO_RES_
#define _H_AUDIO_RES_
//******************************************************************************************
#include "GameFilePreqs.h"
//******************************************************************************************
#define ID_LEN				10
#define FILE_PATH_LEN		30
#define FILE_NAME_LEN		30

//******************************************************************************************
namespace MG
{

	enum AudioResType
	{
		ART_INIT		= 0,
		ART_BACK_GROUND	= 1,		//背景音乐		--循环播放
		ART_BACK_EFFECT	= 2,		//特效			--播放一次
		ART_MAX,
	};

	struct AudioResInfo
	{
		Str				id;
		AudioResType	type;
		Str				filePath;
		Str				fileName;

		AudioResInfo()
			:type(ART_INIT)
		{
			id.reserve(ID_LEN);
			filePath.reserve(FILE_PATH_LEN);
			fileName.reserve(FILE_NAME_LEN);
		}
	};
	
	//-------------------------------------------------------------------------------
	class AudioRes
	{
	public:
		AudioRes();
		~AudioRes();
		SINGLETON_INSTANCE(AudioRes);

	public:
		Bool            load(Str16 fileName);

		AudioResInfo*	getAudioRsInfoById(Str id);
	private:
		std::map<Str, AudioResInfo*>        mAudioRes;

	};

}
//*****************************************************************************************************************
#endif
//*****************************************************************************************************************