
/******************************************************************************/
#ifndef _ISOUNDMANAGER_H
#define _ISOUNDMANAGER_H
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //�������ȼ�
    /******************************************************************************/
    enum SoundPriority
    {
        SP_LOW,
        SP_NORMAL,
        SP_HIGH
    };

    /******************************************************************************/
    //��������
    /******************************************************************************/
    class ISound
    {
    public:
        
        // ��������
        virtual void    play() = 0;
        // �Ƿ񲥷�
        virtual Bool    isPlaying() = 0;
        // ֹͣ����
        virtual void    stop() = 0;
        // �Ƿ�ֹͣ
        virtual Bool    isStopped() = 0;
        // ��ͣ
        virtual void    pause() = 0;
        // �Ƿ���ͣ
        virtual Bool    isPaused() = 0;
        // ����
        virtual void    fadeIn( Flt fadeTime ) = 0;
        // ����
        virtual void    fadeOut( Flt fadeTime ) = 0;
        // ����ѭ��
        virtual void    setLoop(Bool isLoop) = 0;
        // �Ƿ�ѭ��
        virtual Bool    isLooping() = 0;
        // �������ȼ�
        virtual void    setPriority(SoundPriority priority) = 0;
    };


    /******************************************************************************/
    //����������
    /******************************************************************************/
    class ISoundManager
    {
    public:
        // ��������
        virtual ISound*     createOrRetriveSound(CChar* name, CChar* fileName, CChar* filePath, Bool isLoop) = 0;

		// ֹͣ����
		virtual void		stopAll(void) = 0;
        
		//ȡ������
		virtual ISound*      retrieveSound(CChar* name) = 0;
        
		//�������������洢
		virtual Bool        createNewAndSave(CChar* name, CChar* fileName, CChar* filePath, Bool isLoop) = 0;
    };

}

/******************************************************************************/
#endif







