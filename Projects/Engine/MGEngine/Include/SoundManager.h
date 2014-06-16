/******************************************************************************/
#ifndef _SOUNDMANAGER_H_
#define _SOUNDMANAGER_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "ISoundManager.h"
#include "Singleton.h"

/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //声音对象
    /******************************************************************************/
    class SoundAL : public ISound
    {
    public:
        SoundAL(OgreAL::Sound* sound);
        virtual ~SoundAL();

    public:

        // 播放声音
        virtual void    play() ;
        // 是否播放
        virtual Bool    isPlaying() ;
        // 停止播放
        virtual void    stop() ;
        // 是否停止
        virtual Bool    isStopped() ;
        // 暂停
        virtual void    pause() ;
        // 是否暂停
        virtual Bool    isPaused() ;
        // 淡入
        virtual void    fadeIn( Flt fadeTime ) ;
        // 淡出
        virtual void    fadeOut( Flt fadeTime ) ;
        // 设置循环
        virtual void    setLoop(Bool isLoop) ;
        // 是否循环
        virtual Bool    isLooping() ;
        // 设置优先级
        virtual void    setPriority(SoundPriority priority) ;

    private:

        OgreAL::Sound* mSoundAL;
    };



    /******************************************************************************/
    //声音管理器
    /******************************************************************************/
    class SoundALManager : public ISoundManager, public MGSingleton<SoundALManager>
    {
    public:
        SINGLETON_DECLARE( SoundALManager )
        SoundALManager();
        virtual ~SoundALManager();

        // 创建声音
        virtual ISound*     createOrRetriveSound(CChar* name, CChar* fileName, CChar* filePath, Bool isLoop);

		// 停止声音
		virtual void		stopAll(void);
		
        // 销毁声音
        virtual void        destroyAllSound();

		//查找声音
		virtual ISound*     retrieveSound(CChar* name);

		//创建新对象并存储
		virtual Bool        createNewAndSave(CChar* name, CChar* fileName, CChar* filePath, Bool isLoop);
    protected:

        //创建声音系统
        void                createOgreAL();
        //销毁声音系统
        void                destroyOgreAL();

    private:
        
        OgreAL::SoundManager * mSoundManager;

        std::map<Str,SoundAL*> mSounds;
    };

}

/******************************************************************************/

#endif
