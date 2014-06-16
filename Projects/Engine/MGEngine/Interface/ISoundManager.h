
/******************************************************************************/
#ifndef _ISOUNDMANAGER_H
#define _ISOUNDMANAGER_H
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //声音优先级
    /******************************************************************************/
    enum SoundPriority
    {
        SP_LOW,
        SP_NORMAL,
        SP_HIGH
    };

    /******************************************************************************/
    //声音对象
    /******************************************************************************/
    class ISound
    {
    public:
        
        // 播放声音
        virtual void    play() = 0;
        // 是否播放
        virtual Bool    isPlaying() = 0;
        // 停止播放
        virtual void    stop() = 0;
        // 是否停止
        virtual Bool    isStopped() = 0;
        // 暂停
        virtual void    pause() = 0;
        // 是否暂停
        virtual Bool    isPaused() = 0;
        // 淡入
        virtual void    fadeIn( Flt fadeTime ) = 0;
        // 淡出
        virtual void    fadeOut( Flt fadeTime ) = 0;
        // 设置循环
        virtual void    setLoop(Bool isLoop) = 0;
        // 是否循环
        virtual Bool    isLooping() = 0;
        // 设置优先级
        virtual void    setPriority(SoundPriority priority) = 0;
    };


    /******************************************************************************/
    //声音管理器
    /******************************************************************************/
    class ISoundManager
    {
    public:
        // 创建声音
        virtual ISound*     createOrRetriveSound(CChar* name, CChar* fileName, CChar* filePath, Bool isLoop) = 0;

		// 停止声音
		virtual void		stopAll(void) = 0;
        
		//取回声音
		virtual ISound*      retrieveSound(CChar* name) = 0;
        
		//创建新声音并存储
		virtual Bool        createNewAndSave(CChar* name, CChar* fileName, CChar* filePath, Bool isLoop) = 0;
    };

}

/******************************************************************************/
#endif







