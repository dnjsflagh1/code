///***************************************************************************
#ifndef _ANIMATIONCONTROLLER_H_
#define _ANIMATIONCONTROLLER_H_
///***************************************************************************

#include "EnginePreqs.h"
#include "IAnimationController.h"

///***************************************************************************

namespace MG
{

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

    class AnimationController : public IAnimationController
    {
    public:
        AnimationController();
        virtual ~AnimationController();

        // ���Ӽ�����
        virtual void    addAnimationLisitener( Str name, IAnimationControllerListener* lisitener );
        // �Ƴ�������
        virtual void    removeAnimationLisitener( Str name );

        /// �����Ƿ���Բ��Ŷ���״̬ 
        virtual void    setEnabled( CChar* animName, Bool enable );
        /// �õ��Ƿ���Բ��Ŷ���״̬ 
        virtual Bool    getEnabled( CChar* animName ) ;

        /// �����Ŷ��� 
        virtual void    play( CChar* animName, Bool isReset = true ) ;
        /// ��ͣ���� 
        virtual void    pause( CChar* animName ) ;
        /// �������� 
        virtual void    resume( CChar* animName ) ;
        /// ֹͣ���� 
        virtual void    stop( CChar* animName ) ;
        /// ֹͣ���ж��� 
        virtual void    stopAll() ;

        /// �õ������б� 
        virtual	void    getAnimationList( std::vector<Str>& list ) ;
        /// �Ƿ����ָ������ 
        virtual Bool    hasAnimation( CChar* animName ) ;

        /// �Ƿ����ڲ��Ŷ��� 
        virtual Bool    isPlaying( CChar* animName ) ;

		/// �Ƿ����ڲ���Idle���� 
		virtual Bool    isIdlePlaying() ;

        /// �õ������ܳ��� 
        virtual Flt     getLength( CChar* animName ) ;

        /// ���ó�ʼ���� 
        virtual void    setIsIdle( Bool isIdle, CChar* animName ) ;

        /// ���ö������ʱ�� 
        virtual void    setBlendingTime(Flt time) ;
        /// �õ��������ʱ�� 
        virtual Flt     getBlendingTime(void) const ;

        /// �����Ƿ��϶��� 
        virtual void    setBlendingEnable(Bool enable) ;
        /// �õ��Ƿ��϶��� 
        virtual Bool    getBlendingEnable(void) const ;
        /// �����Ƿ���ָ������ 
        virtual void    setBlendingEnable( CChar* animName, Bool enable) ;
        /// �õ��Ƿ���ָ������ 
        virtual Bool    getBlendingEnable( CChar* animName) ;

        /// ���ö����Ƿ񵹲� 
        virtual void    setReverse( CChar* animName, Bool isReverse ) ;
        /// �õ������Ƿ񵹲� 
        virtual Bool    isReverse( CChar* animName ) ;

        /// ���ö���λ�� 
        ///@note: pos: 0 - getLength
        virtual void    setTimePosition( CChar* animName, Flt pos) ;
        /// �õ�����λ�� 
        virtual Flt     getTimePosition( CChar* animName ) ;

        /// ���ö���Ȩ�� 
        ///@note: wight: 0 - 1
        virtual void    setWeight( CChar* animName, Flt wight) ;
        /// �õ�����λ�� 
        virtual Flt     getWeight( CChar* animName ) ;

        /// ���ö���ѭ�� 
        virtual void    setLoop( CChar* animName, Bool isLoop ) ;
        /// �õ�����ѭ������ 
        virtual Bool    isLoop( CChar* animName ) ;

        /// ���õ�������ϣ��Ƿ�ͣ�������һ֡ 
        virtual void    setLastFrameStopEnable( CChar* animName, Bool  enable ) ;
        /// �õ�����������ϣ��Ƿ�ͣ�������һ֡ 
        virtual Bool    getLastFrameStopEnable( CChar* animName ) ;

        /** ���ö����������ʱ��� 
        @note: rate:  1       : ���ڱ�׼�ٶ�
        0 - 1   : С�ڱ�׼�ٶ�  
        1 - max : ���ڱ�׼�ٶ�  
        */
        virtual void    setRate( CChar* animName, Flt rate ) ;
        /// �õ����������ٶ� 
        virtual Flt     getRate( CChar* animName ) ;

        /// ���ö����������ȼ� 
        virtual void    setPriority( CChar* animName, Int priority ) ;
        /// �õ������������ȼ� 
        virtual Int     getPriority( CChar* animName ) ;

        /// ���ö���������� 
        virtual void    setCategory( CChar* animName, Int category ) ;
        /// �õ������������ 
        virtual Int     getCategory( CChar* animName ) ;
		/// ��ô������������������ģ������ID
		virtual U32		getParentModelDeclID() { return mParentModelDeclID;}

		virtual void	setParentModelDeclID(U32 modelDeclID) { mParentModelDeclID = modelDeclID; }

    public:

        /// ���
        void            clear();

        /// ���ع������� 
        void            loadSkeletonAnimation(Ogre::AnimationStateSet* animSet, Ogre::SkeletonInstance* mSkeleton);
        /// ���ض��㶯�� 
        void            loadVertexAnimation(Ogre::Entity* entity);

        /// ���ط��붯�� 
        Bool            loadSeparateAnimation(Str animName);

        /// ���Ӷ��� 
        void            addAnimation(Str animName, Ogre::AnimationState * animState);

        /// ���¶���״̬ 
        void            update( Real delta );

    protected:

		/// ��ģ����Դ��ID
		U32	mParentModelDeclID;
        /// �������ʱ�� 
        Real mBlendingTime;
        /// �Ƿ񶯻���� 
        Bool mBlendingEnable;

        /// ������Ϣ 
        struct AnimationInfo
        {
            Ogre::AnimationState* animationState;	// Ogre::AnimationState
            Int					  category;			// ������ڶ������
            Real				  priority;			// ���ȼ�
            Real				  rate;				// ����
            Bool				  isPaused;		    // �Ƿ��ݶ�
            Bool				  isPlaying;		// �Ƿ񲥷���
            Bool				  isReverse;        // �Ƿ񵹲�
            Bool				  isStopLastFrame;  // ��������ϣ��Ƿ�ͣ�������һ֡
            Bool                  isBlendingEnable; // �Ƿ���
            Bool				  isIdle;			// �Ƿ��ǳ�ʼ������
            Bool				  isChangeDirty;	// �Ƿ��б仯
            Bool				  isActive;			// �Ƿ��б仯
        };

		/// ��ȡ����
		void			applyAnimInfo(Str animName, AnimationController::AnimationInfo* animInfo);

        /// �����б� 
        typedef std::map<Str, AnimationInfo> AnimationMap;
        typedef AnimationMap::iterator AnimationMap_iter;
        typedef AnimationMap::const_iterator AnimationMap_constIter;
        AnimationMap mAnimations;

        /// ������б�
        typedef std::map<Str, AnimationInfo*> ActiveAnimationMap;
        typedef ActiveAnimationMap::iterator  ActiveAnimationMap_iter;
        ActiveAnimationMap mActiveAnimations;

        Ogre::SkeletonInstance* mSkeleton;
        Ogre::AnimationStateSet* mAnimSet;

    protected:

        /// �õ�������Ϣ����
        AnimationInfo*  getAnimationInfo( const Str& animName );
        /// ���ӻ����
        void            setActive( const Str& animName, Bool active, Bool isIgnoreIdle = true );

        /// ���»����
        void            updateActiveAnimationPool( void );

        /// �����ͻ����
        void            handleConflictAnimations( const Str& animName );
        /// �жϵ�ǰ�Ƿ������Ŷ���
        Bool            canAnimationPlayable( const Str& animName );
        /// �ж϶����Ƿ��ͻ
        Bool            isAnimationConflict( const AnimationInfo* info1, const AnimationInfo* info2 );

        /// �õ����ڲ��Ŷ���������
        Int             getAnimationPlayingCount();

		/// �ϲ���Ŀ������Ƿ��Դ��������
		Bool			isSeparateSkeletonCompatible(Skeleton::BoneHandleMap boneHandleMap, Skeleton* srcSkeleton, Skeleton* destSkeleton);

        /// ���ó�ʼ�����Ƿ���Ч
        void            setIdleEnable( Bool enable, Real weight = 1.0, bool isBlending = true, Real rate = 1.0 );
        /// ���³�ʼ����
        void            updateIdle( Real delta );
        /// ���¶���ʱ��λ��
        void            updateTimePosition( Real delta, const Str& animName, AnimationInfo* anim );
        /// ���¶���Ȩ��
        void            updateWeight( Real delta, const Str& animName, AnimationInfo* anim );

        /// ������ʼ��������
        void            startAnimation( const Str& animName, Bool isReset = true );
        /// ����������������
        void            stopAnimation( const Str& animName );
        /// �رն�������
        void            closeAnimation( const Str& animName );

        /// ����������ʼ�����¼� 
        void            fireStart( const Str& animName );
        /// �����������������¼� 
        void            fireStop( const Str& animName );
        /// ��������ѭ���¼� 
        void            fireLoop( const Str& animName );


    private:

        std::map<Str,IAnimationControllerListener*>  mLisiteners;
    };


}
///***************************************************************************

#endif

