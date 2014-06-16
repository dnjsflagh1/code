/******************************************************************************/
#ifndef _SCENENODEACTION_H_
#define _SCENENODEACTION_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "LinedState.h"
#include "ISceneNodeAction.h"

/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //场景节点对象移动行为
    /******************************************************************************/
    class SceneNodeLineMoveToAction : public ISceneNodeLineMoveToAction
    {
    public:
        SceneNodeLineMoveToAction( ISceneNode* object );
		SceneNodeLineMoveToAction( ISceneNode* object, Str SUBSTATE_NAME );

        virtual ~SceneNodeLineMoveToAction();
        //状态名字
        static Str STATE_NAME;

    public:

        /// 设置移动速度
        void                            setMoveSpeed( Flt speed );
        /// 移动到指定位置
        void                            setMoveToDestination( const Vec3& dest );
        /// 设置是否贴地面
        void                            setStickTerrain( Bool isStickTerrain );
		/// 设置是否忽略高度差, 只计算2维距离
		void				            setIgnoreHeight( Bool isIgnoreHeight );
		// 设置是否启用扰动草
		void							setPerturbEnable( Bool isPerturb );
		// 设置扰动草半径
		void							setPerturbRadiu( Flt radiu );
		// 设置扰动草频率
		void							setPerturbFrequnce( UInt freq );

    protected:

        ///更新事件
        virtual void                    update( Flt delta );
        ///是否结束了
        virtual Bool                    isFinished();
        ///进去状态事件
        virtual void                    onEnter();
        ///离开状态事件
        virtual void                    onLeave();

	protected:

		ISceneNode*			    mSceneNode;
        /// 是否移动
        Bool				    mIsMoving;
        /// 移动开始的位置
        Vector3				    mMoveStartPosition;
        /// 移动的目标位置
        Vector3				    mMoveDestination;
        /// 移动的长度
        Flt					    mMoveLength;
        /// 当前移动的长度
        Flt					    mCurrMoveLength;
        /// 移动的方向
        Vector3				    mMoveVelocity;
        /// 移动的速度
        Flt					    mMoveSpeed;
        /// 是否贴地面
        Bool				    mIsStickTerrain;
		/// 是否忽略高度
		Bool				    mIsIgnoreHeight;
		/// 是否启用扰动草
		Bool                             mIsPerturbGrass;
		/// 扰动半径
		Flt								 mPerturbRadiu;
		/// 扰动频率(每秒几次)
		UInt							 mPerturbFrequnce;
		/// 最后一次扰动时间
		clock_t							 mLastPerturbTime;

    };

    /******************************************************************************/
    //场景节点对象转向行为
    /******************************************************************************/
    class SceneNodeYawToAction : public ISceneNodeYawToAction
    {
    public:
        SceneNodeYawToAction( ISceneNode* object );
        virtual ~SceneNodeYawToAction();
        //状态名字
        static Str STATE_NAME;

    public:

        /// 设置Y轴转向速度
        void                setYawSpeed( Flt speed );
        /// 围绕Y轴转向指定方向，正数表示逆时针转动，负数表示顺时针转动
        void                setYawToDirection( const Vec3& dir );
        void                setYawToDirection( const Vec3& startPos, const Vec3& endPos );
        /// 围绕Y轴转向指定位置
        void                setYawToPosition( const Vec3& pos );
		/// 设置是否立即
		void                setIsImmediately( Bool isImmediately ){mIsImmediately=isImmediately;}

    protected:

        ///更新事件
        virtual void        update( Flt delta );
        ///是否结束了
        virtual Bool        isFinished();
        ///进去状态事件
        virtual void        onEnter();
        ///离开状态事件
        virtual void        onLeave();

    private:

        ISceneNode* mSceneNode;

        /// 是否转向
        Bool mIsYawing;
        /// Y轴转向目标方向
        Vector3 mDstDirection;
        /// Y轴转向目标方向
        Flt mYawDir;
        /// Y轴转向目标速度
        Flt mYawRotateSpeed;
		/// 是否立即
		Bool mIsImmediately;
    };

	/******************************************************************************/
	//场景节点对象PITCH转向行为
	/******************************************************************************/
	class SceneNodePitchToAction : public ISceneNodePitchToAction
	{
	public:
		SceneNodePitchToAction( ISceneNode* object );
		virtual ~SceneNodePitchToAction();
		//状态名字
		static Str STATE_NAME;

	public:

		/// 设置X轴转向速度
		void                setPitchSpeed( Flt speed );
		/// 围绕X轴转向的方向
		void                setDestAngle( Flt radian );
		/// 设置是否立即
		void                setIsImmediately( Bool isImmediately ){mIsImmediately=isImmediately;}

	protected:

		///更新事件
		virtual void        update( Flt delta );
		///是否结束了
		virtual Bool        isFinished();
		///进去状态事件
		virtual void        onEnter();
		///离开状态事件
		virtual void        onLeave();

	private:

		ISceneNode* mSceneNode;

		/// 是否转向
		Bool mIsPitching;
		/// X轴转向的方向
		Flt mPitchDir;
		/// X转向速度
		Flt mPitchRotateSpeed;
		/// X轴原有的角度
		Flt mSrcPitch;
		/// X轴转向的角度
		Flt mDstPitch;
		/// 是否立即
		Bool mIsImmediately;
	};

	/******************************************************************************/
	//场景节点对象转动朝向行为
	/******************************************************************************/
	class SceneNodeDirectToAction : public ISceneNodeDirectToAction
	{
	public:

		SceneNodeDirectToAction( ISceneNode* object );
		virtual ~SceneNodeDirectToAction();
		//状态名字
		static Str STATE_NAME;

	public: 

		/// 设置转动速度
		void				setShiftSpeed( Flt speed ) { mShiftSpeed = speed; }
		
		/// 获取转动速度
		Flt					getShiftSpeed() { return mShiftSpeed; }

		/// 设置目标方向
		void				setDestDirection( Vec3 dir );

		/// 获取目标方向
		Vec3				getDestDirection() { return mDestDirection; }

		/// 是否立刻生效
		void				setImmediately(bool immediately) { mIsImmediately = immediately; }

		/// 是否结束了
		Bool				isFinished();

	protected:

		/// 更新事件
		virtual void        update( Flt delta );
		/// 进去状态事件
		virtual void        onEnter();
		/// 离开状态事件
		virtual void        onLeave();

	private:

		/// 场景节点
		ISceneNode*			mSceneNode;
		/// 转向的速度, 单位是弧度
		Flt					mShiftSpeed;
		/// 外部输入的目标指向
		Vec3				mDestDirection;
		/// 起始方向
		Vec3				mOriginalDirection;	
		/// 旋转轴
		Vec3				mRotateAxis;
		/// 总的距离
		Flt					mTotalRadianDist;
		/// 当前的距离
		Flt					mCurrRadianDist;
		/// 是否立刻转移到目标角度
		Bool				mIsImmediately;
	};


}

/******************************************************************************/

#endif