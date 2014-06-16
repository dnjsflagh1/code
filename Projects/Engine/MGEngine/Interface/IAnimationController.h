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
    实现动画监听
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
    实现动画控制

    @note: 
    1.不同类别的动画播放互不影响
    2.请求播放新动画时,请求动画同一类别的正在播放动画的优先级如果大于请求动画，
    则不改变当前播放动画状态，如果小于等于请求动画，
    则替换当前动画为请求动画。
    -----------------------------------------------------------------------------
    */

    class IAnimationController
    {
    public:

        // 增加监听器
        virtual void    addAnimationLisitener( Str name, IAnimationControllerListener* lisitener ) = 0;
        // 移除监听器
        virtual void    removeAnimationLisitener( Str name ) = 0;

        /// 设置是否可以播放动画状态 
        virtual void    setEnabled( CChar* animName, Bool enable ) = 0;
        /// 得到是否可以播放动画状态 
        virtual Bool    getEnabled( CChar* animName ) = 0;

        /// 正播放动画 
        virtual void    play( CChar* animName, Bool isReset = true ) = 0;
        /// 暂停动画 
        virtual void    pause( CChar* animName ) = 0;
        /// 继续动画 
        virtual void    resume( CChar* animName ) = 0;
        /// 停止动画 
        virtual void    stop( CChar* animName ) = 0;
        /// 停止所有动画 
        virtual void    stopAll() = 0;

        /// 得到动画列表 
        virtual	void    getAnimationList( std::vector<Str>& list ) = 0;
        /// 是否存在指名动画 
        virtual Bool    hasAnimation( CChar* animName ) = 0;

        /// 是否正在播放动画 
        virtual Bool    isPlaying( CChar* animName ) = 0;

		/// 是否正在播放Idle动画 
		virtual Bool    isIdlePlaying()  = 0;

        /// 得到动画总长度 
        virtual Flt     getLength( CChar* animName ) = 0;

        /// 设置初始动作 
        virtual void    setIsIdle( Bool isIdle, CChar* animName) = 0;

        /// 设置动画混合时间 
        virtual void    setBlendingTime(Flt time) = 0;
        /// 得到动画混合时间 
        virtual Flt     getBlendingTime(void) const = 0;

        /// 设置是否混合动画 
        virtual void    setBlendingEnable(Bool enable) = 0;
        /// 得到是否混合动画 
        virtual Bool    getBlendingEnable(void) const = 0;
        /// 设置是否混合指定动画 
        virtual void    setBlendingEnable( CChar* animName, Bool enable) = 0;
        /// 得到是否混合指定动画 
        virtual Bool    getBlendingEnable( CChar* animName) = 0;

        /// 设置动画是否倒播 
        virtual void    setReverse( CChar* animName, Bool isReverse ) = 0;
        /// 得到动画是否倒播 
        virtual Bool    isReverse( CChar* animName ) = 0;

        /// 设置动画位置 
        ///@note: pos: 0 - getLength
        virtual void    setTimePosition( CChar* animName, Flt pos) = 0;
        /// 得到动画位置 
        virtual Flt     getTimePosition( CChar* animName ) = 0;

        /// 设置动画权重 
        ///@note: wight: 0 - 1
        virtual void    setWeight( CChar* animName, Flt wight) = 0;
        /// 得到动画位置 
        virtual Flt     getWeight( CChar* animName ) = 0;

        /// 设置动画循环 
        virtual void    setLoop( CChar* animName, Bool isLoop ) = 0;
        /// 得到动画循环设置 
        virtual Bool    isLoop( CChar* animName ) = 0;

        /// 设置当播放完毕，是否停留在最后一帧 
        virtual void    setLastFrameStopEnable( CChar* animName, Bool  enable ) = 0;
        /// 得到，当播放完毕，是否停留在最后一帧 
        virtual Bool    getLastFrameStopEnable( CChar* animName ) = 0;

        /** 设置动画播放速率比例 
            @note: rate:  1       : 等于标准速度
            0 - 1   : 小于标准速度  
            1 - max : 大于标准速度  
        */
        virtual void    setRate( CChar* animName, Flt rate ) = 0;
        /// 得到动画播放速度 
        virtual Flt     getRate( CChar* animName ) = 0;

        /// 设置动画播放优先级 
        virtual void    setPriority( CChar* animName, Int priority ) = 0;
        /// 得到动画播放优先级 
        virtual Int     getPriority( CChar* animName ) = 0;

        /// 设置动画播放类别 
        virtual void    setCategory( CChar* animName, Int category ) = 0;
        /// 得到动画播放类别 
        virtual Int     getCategory( CChar* animName ) = 0;

		/// 获得创建这个动画控制器的模型声明ID
		virtual U32		getParentModelDeclID() = 0;

		virtual void	setParentModelDeclID(U32 modelDeclID) = 0;

        /////////////////////////////////////////////////////////////////////////////////

    };


}
///***************************************************************************

#endif

