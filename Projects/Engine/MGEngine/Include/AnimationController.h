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
    实现动画控制

    @note: 
    1.不同类别的动画播放互不影响
    2.请求播放新动画时,请求动画同一类别的正在播放动画的优先级如果大于请求动画，
    则不改变当前播放动画状态，如果小于等于请求动画，
    则替换当前动画为请求动画。
    -----------------------------------------------------------------------------
    */

    class AnimationController : public IAnimationController
    {
    public:
        AnimationController();
        virtual ~AnimationController();

        // 增加监听器
        virtual void    addAnimationLisitener( Str name, IAnimationControllerListener* lisitener );
        // 移除监听器
        virtual void    removeAnimationLisitener( Str name );

        /// 设置是否可以播放动画状态 
        virtual void    setEnabled( CChar* animName, Bool enable );
        /// 得到是否可以播放动画状态 
        virtual Bool    getEnabled( CChar* animName ) ;

        /// 正播放动画 
        virtual void    play( CChar* animName, Bool isReset = true ) ;
        /// 暂停动画 
        virtual void    pause( CChar* animName ) ;
        /// 继续动画 
        virtual void    resume( CChar* animName ) ;
        /// 停止动画 
        virtual void    stop( CChar* animName ) ;
        /// 停止所有动画 
        virtual void    stopAll() ;

        /// 得到动画列表 
        virtual	void    getAnimationList( std::vector<Str>& list ) ;
        /// 是否存在指名动画 
        virtual Bool    hasAnimation( CChar* animName ) ;

        /// 是否正在播放动画 
        virtual Bool    isPlaying( CChar* animName ) ;

		/// 是否正在播放Idle动画 
		virtual Bool    isIdlePlaying() ;

        /// 得到动画总长度 
        virtual Flt     getLength( CChar* animName ) ;

        /// 设置初始动作 
        virtual void    setIsIdle( Bool isIdle, CChar* animName ) ;

        /// 设置动画混合时间 
        virtual void    setBlendingTime(Flt time) ;
        /// 得到动画混合时间 
        virtual Flt     getBlendingTime(void) const ;

        /// 设置是否混合动画 
        virtual void    setBlendingEnable(Bool enable) ;
        /// 得到是否混合动画 
        virtual Bool    getBlendingEnable(void) const ;
        /// 设置是否混合指定动画 
        virtual void    setBlendingEnable( CChar* animName, Bool enable) ;
        /// 得到是否混合指定动画 
        virtual Bool    getBlendingEnable( CChar* animName) ;

        /// 设置动画是否倒播 
        virtual void    setReverse( CChar* animName, Bool isReverse ) ;
        /// 得到动画是否倒播 
        virtual Bool    isReverse( CChar* animName ) ;

        /// 设置动画位置 
        ///@note: pos: 0 - getLength
        virtual void    setTimePosition( CChar* animName, Flt pos) ;
        /// 得到动画位置 
        virtual Flt     getTimePosition( CChar* animName ) ;

        /// 设置动画权重 
        ///@note: wight: 0 - 1
        virtual void    setWeight( CChar* animName, Flt wight) ;
        /// 得到动画位置 
        virtual Flt     getWeight( CChar* animName ) ;

        /// 设置动画循环 
        virtual void    setLoop( CChar* animName, Bool isLoop ) ;
        /// 得到动画循环设置 
        virtual Bool    isLoop( CChar* animName ) ;

        /// 设置当播放完毕，是否停留在最后一帧 
        virtual void    setLastFrameStopEnable( CChar* animName, Bool  enable ) ;
        /// 得到，当播放完毕，是否停留在最后一帧 
        virtual Bool    getLastFrameStopEnable( CChar* animName ) ;

        /** 设置动画播放速率比例 
        @note: rate:  1       : 等于标准速度
        0 - 1   : 小于标准速度  
        1 - max : 大于标准速度  
        */
        virtual void    setRate( CChar* animName, Flt rate ) ;
        /// 得到动画播放速度 
        virtual Flt     getRate( CChar* animName ) ;

        /// 设置动画播放优先级 
        virtual void    setPriority( CChar* animName, Int priority ) ;
        /// 得到动画播放优先级 
        virtual Int     getPriority( CChar* animName ) ;

        /// 设置动画播放类别 
        virtual void    setCategory( CChar* animName, Int category ) ;
        /// 得到动画播放类别 
        virtual Int     getCategory( CChar* animName ) ;
		/// 获得创建这个动画控制器的模型声明ID
		virtual U32		getParentModelDeclID() { return mParentModelDeclID;}

		virtual void	setParentModelDeclID(U32 modelDeclID) { mParentModelDeclID = modelDeclID; }

    public:

        /// 清除
        void            clear();

        /// 加载骨骼动画 
        void            loadSkeletonAnimation(Ogre::AnimationStateSet* animSet, Ogre::SkeletonInstance* mSkeleton);
        /// 加载顶点动画 
        void            loadVertexAnimation(Ogre::Entity* entity);

        /// 加载分离动画 
        Bool            loadSeparateAnimation(Str animName);

        /// 增加动画 
        void            addAnimation(Str animName, Ogre::AnimationState * animState);

        /// 更新动画状态 
        void            update( Real delta );

    protected:

		/// 父模型资源表ID
		U32	mParentModelDeclID;
        /// 动画混合时间 
        Real mBlendingTime;
        /// 是否动画混合 
        Bool mBlendingEnable;

        /// 动画信息 
        struct AnimationInfo
        {
            Ogre::AnimationState* animationState;	// Ogre::AnimationState
            Int					  category;			// 类别，用于动画混合
            Real				  priority;			// 优先级
            Real				  rate;				// 速率
            Bool				  isPaused;		    // 是否暂定
            Bool				  isPlaying;		// 是否播放中
            Bool				  isReverse;        // 是否倒播
            Bool				  isStopLastFrame;  // 当播放完毕，是否停留在最后一帧
            Bool                  isBlendingEnable; // 是否混合
            Bool				  isIdle;			// 是否是初始化动作
            Bool				  isChangeDirty;	// 是否有变化
            Bool				  isActive;			// 是否有变化
        };

		/// 获取配置
		void			applyAnimInfo(Str animName, AnimationController::AnimationInfo* animInfo);

        /// 动画列表 
        typedef std::map<Str, AnimationInfo> AnimationMap;
        typedef AnimationMap::iterator AnimationMap_iter;
        typedef AnimationMap::const_iterator AnimationMap_constIter;
        AnimationMap mAnimations;

        /// 活动动画列表
        typedef std::map<Str, AnimationInfo*> ActiveAnimationMap;
        typedef ActiveAnimationMap::iterator  ActiveAnimationMap_iter;
        ActiveAnimationMap mActiveAnimations;

        Ogre::SkeletonInstance* mSkeleton;
        Ogre::AnimationStateSet* mAnimSet;

    protected:

        /// 得到动画信息对象
        AnimationInfo*  getAnimationInfo( const Str& animName );
        /// 增加活动动画
        void            setActive( const Str& animName, Bool active, Bool isIgnoreIdle = true );

        /// 更新活动动画
        void            updateActiveAnimationPool( void );

        /// 处理冲突动画
        void            handleConflictAnimations( const Str& animName );
        /// 判断当前是否允许播放动画
        Bool            canAnimationPlayable( const Str& animName );
        /// 判断动画是否冲突
        Bool            isAnimationConflict( const AnimationInfo* info1, const AnimationInfo* info2 );

        /// 得到正在播放动画的数量
        Int             getAnimationPlayingCount();

		/// 合并的目标骨骼是否和源骨骼适配
		Bool			isSeparateSkeletonCompatible(Skeleton::BoneHandleMap boneHandleMap, Skeleton* srcSkeleton, Skeleton* destSkeleton);

        /// 设置初始动作是否有效
        void            setIdleEnable( Bool enable, Real weight = 1.0, bool isBlending = true, Real rate = 1.0 );
        /// 更新初始动作
        void            updateIdle( Real delta );
        /// 更新动画时间位置
        void            updateTimePosition( Real delta, const Str& animName, AnimationInfo* anim );
        /// 更新动画权重
        void            updateWeight( Real delta, const Str& animName, AnimationInfo* anim );

        /// 启动开始动画播放
        void            startAnimation( const Str& animName, Bool isReset = true );
        /// 启动结束动画播放
        void            stopAnimation( const Str& animName );
        /// 关闭动画播放
        void            closeAnimation( const Str& animName );

        /// 动画启动开始播放事件 
        void            fireStart( const Str& animName );
        /// 动画启动结束播放事件 
        void            fireStop( const Str& animName );
        /// 动画周期循环事件 
        void            fireLoop( const Str& animName );


    private:

        std::map<Str,IAnimationControllerListener*>  mLisiteners;
    };


}
///***************************************************************************

#endif

