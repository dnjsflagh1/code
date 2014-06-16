//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: GameSoundManager.h
//        Author: yuanlinhu
//          Date: 2011-12-29
//          Time: 16:15
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2011-12-29      add
//////////////////////////////////////////////////////////////
/******************************************************************************/

#ifndef _GAME_SOUND_MANAGER_H_
#define _GAME_SOUND_MANAGER_H_

/******************************************************************************/
#include "ClientPreqs.h"
/******************************************************************************/
namespace MG
{
	class GameSoundManager
	{
	public:
		
		//控制音乐播放
		enum 
		{
			STATUS_SILENCE,
            STATUS_BACKGROUND,
			STATUS_SKILL,
			STATUS_MAX,
		};

		GameSoundManager();
		~GameSoundManager();
		SINGLETON_INSTANCE(GameSoundManager)

        Bool initialize();
        //set
		void setBackGroundAudioStatus(Bool status);
		void setSkillAudioStatus(Bool status);
		//void setAllAudioStatus(Bool status);
       // Bool isAllStatusOff();
		
	    void  setSilenceStatus(Bool status);
		//
		void play(U32 id);
		void stop(U32 id);
		void stopAll();
		//Bool isFileExist(CChar* filepath,CChar* filename);

	private:
		//ISound*	createOrRetriveSound(CChar* name,Bool isLoop);
        Bool mAudioStatus[STATUS_MAX];
		void revertBackGroundSoundPlaying(Bool isPlay);
		
        //存储当前背景的音乐,暂停之后可以继续播放.
		Str8 mCurrentBackGroundSound;

	};
}

#endif	//_GAME_SOUND_MANAGER_H_