///***************************************************************************
#ifndef _IANIMATIONCONTROLLER_H_
#define _IANIMATIONCONTROLLER_H_
///***************************************************************************

#include "MGEngineInterfacePreqs.h"

///***************************************************************************

namespace MG
{

    /*
    -----------------------------------------------------------------------------
    ʵ�ֶ�������
    -----------------------------------------------------------------------------
    */
    class IAnimationControllerListener
    {
    public:

        virtual void onAnimationStart(CChar* animName){};
        virtual void onAnimationStop(CChar* animName){};
        virtual void onAnimationLoop(CChar* animName){};

    };

    /*
    -----------------------------------------------------------------------------
    ʵ�ֶ�������

    @note: 
    1.��ͬ���Ķ������Ż���Ӱ��
    2.���󲥷��¶���ʱ,���󶯻�ͬһ�������ڲ��Ŷ��������ȼ�����������󶯻���
    �򲻸ı䵱ǰ���Ŷ���״̬�����С�ڵ������󶯻���
    ���滻��ǰ����Ϊ���󶯻���
    -----------------------------------------------------------------------------
    */

    class IAnimationController
    {
    public:

        // ���Ӽ�����
        virtual void    addAnimationLisitener( Str name, IAnimationControllerListener* lisitener ) = 0;
        // �Ƴ�������
        virtual void    removeAnimationLisitener( Str name ) = 0;

        /// �����Ƿ���Բ��Ŷ���״̬ 
        virtual void    setEnabled( CChar* animName, Bool enable ) = 0;
        /// �õ��Ƿ���Բ��Ŷ���״̬ 
        virtual Bool    getEnabled( CChar* animName ) = 0;

        /// �����Ŷ��� 
        virtual void    play( CChar* animName, Bool isReset = true ) = 0;
        /// ��ͣ���� 
        virtual void    pause( CChar* animName ) = 0;
        /// �������� 
        virtual void    resume( CChar* animName ) = 0;
        /// ֹͣ���� 
        virtual void    stop( CChar* animName ) = 0;
        /// ֹͣ���ж��� 
        virtual void    stopAll() = 0;

        /// �õ������б� 
        virtual	void    getAnimationList( std::vector<Str>& list ) = 0;
        /// �Ƿ����ָ������ 
        virtual Bool    hasAnimation( CChar* animName ) = 0;

        /// �Ƿ����ڲ��Ŷ��� 
        virtual Bool    isPlaying( CChar* animName ) = 0;

		/// �Ƿ����ڲ���Idle���� 
		virtual Bool    isIdlePlaying()  = 0;

        /// �õ������ܳ��� 
        virtual Flt     getLength( CChar* animName ) = 0;

        /// ���ó�ʼ���� 
        virtual void    setIsIdle( Bool isIdle, CChar* animName) = 0;

        /// ���ö������ʱ�� 
        virtual void    setBlendingTime(Flt time) = 0;
        /// �õ��������ʱ�� 
        virtual Flt     getBlendingTime(void) const = 0;

        /// �����Ƿ��϶��� 
        virtual void    setBlendingEnable(Bool enable) = 0;
        /// �õ��Ƿ��϶��� 
        virtual Bool    getBlendingEnable(void) const = 0;
        /// �����Ƿ���ָ������ 
        virtual void    setBlendingEnable( CChar* animName, Bool enable) = 0;
        /// �õ��Ƿ���ָ������ 
        virtual Bool    getBlendingEnable( CChar* animName) = 0;

        /// ���ö����Ƿ񵹲� 
        virtual void    setReverse( CChar* animName, Bool isReverse ) = 0;
        /// �õ������Ƿ񵹲� 
        virtual Bool    isReverse( CChar* animName ) = 0;

        /// ���ö���λ�� 
        ///@note: pos: 0 - getLength
        virtual void    setTimePosition( CChar* animName, Flt pos) = 0;
        /// �õ�����λ�� 
        virtual Flt     getTimePosition( CChar* animName ) = 0;

        /// ���ö���Ȩ�� 
        ///@note: wight: 0 - 1
        virtual void    setWeight( CChar* animName, Flt wight) = 0;
        /// �õ�����λ�� 
        virtual Flt     getWeight( CChar* animName ) = 0;

        /// ���ö���ѭ�� 
        virtual void    setLoop( CChar* animName, Bool isLoop ) = 0;
        /// �õ�����ѭ������ 
        virtual Bool    isLoop( CChar* animName ) = 0;

        /// ���õ�������ϣ��Ƿ�ͣ�������һ֡ 
        virtual void    setLastFrameStopEnable( CChar* animName, Bool  enable ) = 0;
        /// �õ�����������ϣ��Ƿ�ͣ�������һ֡ 
        virtual Bool    getLastFrameStopEnable( CChar* animName ) = 0;

        /** ���ö����������ʱ��� 
            @note: rate:  1       : ���ڱ�׼�ٶ�
            0 - 1   : С�ڱ�׼�ٶ�  
            1 - max : ���ڱ�׼�ٶ�  
        */
        virtual void    setRate( CChar* animName, Flt rate ) = 0;
        /// �õ����������ٶ� 
        virtual Flt     getRate( CChar* animName ) = 0;

        /// ���ö����������ȼ� 
        virtual void    setPriority( CChar* animName, Int priority ) = 0;
        /// �õ������������ȼ� 
        virtual Int     getPriority( CChar* animName ) = 0;

        /// ���ö���������� 
        virtual void    setCategory( CChar* animName, Int category ) = 0;
        /// �õ������������ 
        virtual Int     getCategory( CChar* animName ) = 0;

		/// ��ô������������������ģ������ID
		virtual U32		getParentModelDeclID() = 0;

		virtual void	setParentModelDeclID(U32 modelDeclID) = 0;

        /////////////////////////////////////////////////////////////////////////////////

    };


}
///***************************************************************************

#endif

