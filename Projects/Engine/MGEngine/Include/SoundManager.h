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
    //��������
    /******************************************************************************/
    class SoundAL : public ISound
    {
    public:
        SoundAL(OgreAL::Sound* sound);
        virtual ~SoundAL();

    public:

        // ��������
        virtual void    play() ;
        // �Ƿ񲥷�
        virtual Bool    isPlaying() ;
        // ֹͣ����
        virtual void    stop() ;
        // �Ƿ�ֹͣ
        virtual Bool    isStopped() ;
        // ��ͣ
        virtual void    pause() ;
        // �Ƿ���ͣ
        virtual Bool    isPaused() ;
        // ����
        virtual void    fadeIn( Flt fadeTime ) ;
        // ����
        virtual void    fadeOut( Flt fadeTime ) ;
        // ����ѭ��
        virtual void    setLoop(Bool isLoop) ;
        // �Ƿ�ѭ��
        virtual Bool    isLooping() ;
        // �������ȼ�
        virtual void    setPriority(SoundPriority priority) ;

    private:

        OgreAL::Sound* mSoundAL;
    };



    /******************************************************************************/
    //����������
    /******************************************************************************/
    class SoundALManager : public ISoundManager, public MGSingleton<SoundALManager>
    {
    public:
        SINGLETON_DECLARE( SoundALManager )
        SoundALManager();
        virtual ~SoundALManager();

        // ��������
        virtual ISound*     createOrRetriveSound(CChar* name, CChar* fileName, CChar* filePath, Bool isLoop);

		// ֹͣ����
		virtual void		stopAll(void);
		
        // ��������
        virtual void        destroyAllSound();

		//��������
		virtual ISound*     retrieveSound(CChar* name);

		//�����¶��󲢴洢
		virtual Bool        createNewAndSave(CChar* name, CChar* fileName, CChar* filePath, Bool isLoop);
    protected:

        //��������ϵͳ
        void                createOgreAL();
        //��������ϵͳ
        void                destroyOgreAL();

    private:
        
        OgreAL::SoundManager * mSoundManager;

        std::map<Str,SoundAL*> mSounds;
    };

}

/******************************************************************************/

#endif
