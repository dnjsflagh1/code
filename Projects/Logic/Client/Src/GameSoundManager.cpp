/******************************************************************************/
#include "stdafx.h"
#include "GameSoundManager.h"
#include "AudioResourceConfig.h"
#include "ClientMain.h"
/******************************************************************************/
namespace MG
{
	//----------------------------------------------------------------------------------------
	GameSoundManager::GameSoundManager()
	{
		memset(mAudioStatus,true,sizeof(mAudioStatus));
	}

	//----------------------------------------------------------------------------------------
	GameSoundManager::~GameSoundManager()
	{

	}
	//----------------------------------------------------------------------------------------
	void GameSoundManager::play(U32 id)
	{
		const AudioResInfo* audioInfo = AudioResourceConfig::getInstance().getAudioResourceInfo(id);
		//DYNAMIC_ASSERT(NULL != audioInfo);

		if ( !audioInfo )
			return;

		//
		Str8 audio_name     = audioInfo->name;
		Str8 audio_filename = audioInfo->fileName;
        Str8 audio_filepath = audioInfo->filePath;
		
        //将当前背景音乐存储,stop then play ..
        if (audioInfo->loopType == ART_BACK_GROUND)
        {
			mCurrentBackGroundSound = audio_name;
        }
        
		//静音
		if (true == mAudioStatus[STATUS_SILENCE])
			return;

        switch(audioInfo->loopType)
		{

		case ART_BACK_GROUND:		//背景音乐， 循环播放
			{
				if (mAudioStatus[STATUS_BACKGROUND] == false)
				     break;
				ClientMain::getInstance().getEngine()->soundMgr()->stopAll();
				ClientMain::getInstance().getEngine()->soundMgr()->createOrRetriveSound(audio_name.c_str(),audio_filename.c_str(),audio_filepath.c_str(),true)->play();
			} 
			break;
		case ART_BACK_EFFECT:		//特效音乐， 播放一次
			{
				if (mAudioStatus[STATUS_SKILL] == false)
				    break;
				ClientMain::getInstance().getEngine()->soundMgr()->createOrRetriveSound(audio_name.c_str(),audio_filename.c_str(),audio_filepath.c_str(),false)->play();
			}
			break;
		default:
			{
				DYNAMIC_ASSERT(0);
			}
			break;
		}
		
	}

	//----------------------------------------------------------------------------------------
	void GameSoundManager::stop(U32 id)
	{
        
		const AudioResInfo* audioInfo = AudioResourceConfig::getInstance().getAudioResourceInfo(id);
		DYNAMIC_ASSERT(NULL != audioInfo);

		if ( !audioInfo )
			return;

		Str8 audio_name = audioInfo->name;
		ClientMain::getInstance().getEngine()->soundMgr()->retrieveSound(audio_name.c_str())->stop();



	}

	//----------------------------------------------------------------------------------------
	void GameSoundManager::stopAll()
	{
		ClientMain::getInstance().getEngine()->soundMgr()->stopAll();
	}

	MG::Bool GameSoundManager::initialize()
	{
		//创建游戏中的预载Sound对象
		Str8 audio_name;
		Str8 audio_filename;
		Str8 audio_filepath;
		U32  audio_replaceid;
        std::map<U32, AudioResInfo*> tempList = AudioResourceConfig::getInstance().getPreloadAudioResourceInfo();

		if (tempList.empty())
		    return true;

		std::map<U32, AudioResInfo*>::iterator It = tempList.begin();
		while(It != tempList.end())
		{
		   audio_replaceid =  (It->second)->replaceResID;
           audio_name      =  (It->second)->name;
           audio_filename  =  (It->second)->fileName;
		   audio_filepath  =  (It->second)->filePath;
           

		   //不存在资源文件，则需要替换
		   if ((!MG::FileOp::isExistFile(audio_filepath,audio_filename))&&(audio_replaceid != 0))
           {
                const AudioResInfo* audioInfo = AudioResourceConfig::getInstance().getAudioResourceInfo(audio_replaceid);
                audio_filename = audioInfo->fileName;
           }
		   

		   switch((It->second)->loopType)
		   {

		   case ART_BACK_GROUND:
			   {
				   if(!(ClientMain::getInstance().getEngine()->soundMgr()->createNewAndSave(audio_name.c_str(),audio_filename.c_str(),audio_filepath.c_str(),true)))
					   DYNAMIC_ASSERT(0);

			   } 
			   break;
		   case ART_BACK_EFFECT:
			   {
				  if(!(ClientMain::getInstance().getEngine()->soundMgr()->createNewAndSave(audio_name.c_str(),audio_filename.c_str(),audio_filepath.c_str(),false)))
					  DYNAMIC_ASSERT(0);
			   }
			   break;
		   default:
			   {
				   DYNAMIC_ASSERT(0);
			   }
			   break;
		   }

		   It++;
		}
		return true;        
	}

	void GameSoundManager::setBackGroundAudioStatus( Bool status )
	{
          mAudioStatus[STATUS_BACKGROUND] = status;
		  if (mCurrentBackGroundSound.length() > 0)
		  {     
			    revertBackGroundSoundPlaying(status);
		  }

	}

	void GameSoundManager::setSkillAudioStatus( Bool status )
	{
        mAudioStatus[STATUS_SKILL] = status;

	}

	/*void GameSoundManager::setAllAudioStatus( Bool status )
	{
         U32 i= 0;
		 if (status == false)
		 {
			 for (;i<STATUS_MAX;i++)
			 {
				 mAudioStatus[i] = status;
			 }
			 stopAll();
		 }

	}
  */
	/*MG::Bool GameSoundManager::isAllStatusOff()
	{
		Bool status = true;
		U32 i= 0;
		for (;i<STATUS_MAX;i++)
		{
			if (mAudioStatus[i] == true)
			{
                 status = false;
				 break;
			}
			
		}
        
		return status;
	}*/
	
	//----------------------------------------------------------------------------------------
	void GameSoundManager::revertBackGroundSoundPlaying(Bool isPlay)
	{
		ISound* iSound = ClientMain::getInstance().getEngine()->soundMgr()->retrieveSound(mCurrentBackGroundSound.c_str());
		DYNAMIC_ASSERT_LOG(iSound,"iSound == NULL, audioName not exist!");
		if (iSound == NULL)
		   return;
		//静音
		if ( mAudioStatus[STATUS_SILENCE])
		{
           return;
		}
        if (isPlay)
        {
			iSound->play();
        }
		else
		{
			iSound->stop();
		}
		

	}

	void GameSoundManager::setSilenceStatus( Bool status )
	{
        mAudioStatus[STATUS_SILENCE] = status;
		if (status)
		{
			stopAll();
		}
	}
	//----------------------------------------------------------------------------------------
}