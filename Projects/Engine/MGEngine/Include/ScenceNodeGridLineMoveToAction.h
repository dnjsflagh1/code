/******************************************************************************/
#ifndef _SCENCENODEGRIDLINEMOVETOACTION_H_
#define _SCENCENODEGRIDLINEMOVETOACTION_H_
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
	class SceneNodeGridLineMoveToAction : public ISceneNodeGridLineMoveToAction
	{
	public:

		SceneNodeGridLineMoveToAction( ISceneNode* sceneNode, IDynamicBlockObject* dynamicBlockobject = NULL);
		virtual ~SceneNodeGridLineMoveToAction();
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

		void							setMoveToPathFindType( MoveToPathFindType moveToPathFindType );
        /// 是否停止中
        Bool                            isBlockStop();
        /// 设置是否检测碰撞
        void                            setBlockCheck( Bool enable );
        /// 设置是否遇到碰撞等待，如果设置false,遇到障碍则退出action
        void                            setIsWait( Bool enable );

		Bool                            getIsWait();


		Bool							getIsMoving();

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

		virtual void					onLinedStateChanged(LinedStateObject* obj);

		void							notifyMoveToStateChange();

    protected:

        // 刷新式更新障碍
        Bool                            checkAndRefreshBlock( Vec3 src, Vec3 dest );
        // 抢占式更新障碍
        Bool                            checkAndGrabBlock( Vec3 src, Vec3 dest );

	protected:

        // 障碍管理对象
		BlockManager*		   			 mBlockManager;
        // 场景节点对象
		ISceneNode*			   			 mSceneNode;
        // 动态障碍对象
		IDynamicBlockObject*			 mDynamicBlockObject;
        // 动态障碍对象是否检测碰撞
        Bool                             mBlockEnable;   
		/// 是否移动
		Bool				   			 mIsMoving;
		/// 移动开始的位置
		Vec3				   			 mMoveStartPosition;
		/// 移动的目标位置
		Vec3				   			 mMoveDestination;
		/// 移动的长度
		Flt					   			 mMoveLength;
		/// 当前移动的长度
		Flt					   			 mCurrMoveLength;
		/// 移动的方向
		Vec3				   			 mMoveVelocity;
        /// 移动的单位方向
        Vec3				   			 mMoveVelocityN;
        /// 移动检测碰撞的方向
        Vec3				   			 mMoveCheckBlockVelocity;

		/// 移动的速度
		Flt					   			 mMoveSpeed;
		/// 是否贴地面
		Bool				   			 mIsStickTerrain;
		/// 是否忽略高度
		Bool				   			 mIsIgnoreHeight;

        // 是否有障碍
        Bool                             mIsRefreshBlock;
		/// 是否启用扰动草
		Bool                             mIsPerturbGrass;
		/// 扰动半径
		Flt								 mPerturbRadiu;
		/// 扰动频率(每秒几次)
		UInt							 mPerturbFrequnce;
		/// 最后一次扰动时间
		clock_t							 mLastPerturbTime;

        // 设置是否遇到障碍停止
        Bool                             mIsWait;
        // 设置是否检测碰撞
        Bool                             mIsBlockCheck;

		Flt					   			 mSceneNodeRadius;
		Int					   			 mBlockDiameter;
		std::vector<PassGridBlock>		 mPassBlockGridList;
		UInt							 mCurrPassGridBlockListIndex;
		UInt							 mNextPassGridBlockIndex;

		MoveToPathFindType				mMoveToPathFindType;

	};
}

/******************************************************************************/

#endif
