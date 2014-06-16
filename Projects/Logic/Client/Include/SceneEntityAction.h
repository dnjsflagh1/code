/******************************************************************************/
#ifndef _SCENEENTITYACTION_H_
#define _SCENEENTITYACTION_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "LinedState.h"
#include "ISceneNodeAction.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    // 移动状态
    // 临时放在这里，如果有公用则移动到公用的地方
    /******************************************************************************/
    enum CMoveAcionState
    {
        MAS_NULL,
        MAS_MOVING,
        MAS_MOVEWAIT,
        MAS_MOVESTOP
    };


    /******************************************************************************/
    //游戏对象直线移动行为
    /******************************************************************************/
    class CCSEntityLineMoveAcion : public LinedStateObject, public LinedStateObjectListener
    {
    public:
        CCSEntityLineMoveAcion( CSceneEntity* entity, Vec3 startPos, Vec3 endPos, Flt startTime );
        virtual ~CCSEntityLineMoveAcion();

    public:

        //状态名字
        static Str STATE_NAME;

        ///更新事件
        virtual void        update( Flt delta );
        ///是否结束了
        virtual Bool        isFinished();
        ///进去状态事件
        virtual void        onEnter();
        ///离开状态事件
        virtual void        onLeave();
        ///状态改变事件
        virtual void        onMoveAcionStateChanged( CMoveAcionState state );

        ////////////////////////////////////////////////////////////////////////////////////

        void                setAnimation( Str animName, Bool isAutoAnimEnd = true );
        void				setMoveSpeed(Flt speed);
        void				setYawSpeed(Flt speed);

		////////////////////////////////////////////////////////////////////////////////////

		void				setBlockCheck( Bool isBlockCheck );

		void				setMoveToPathFindType( ISceneNodeGridLineMoveToAction::MoveToPathFindType moveToPathFindType );

        ////////////////////////////////////////////////////////////////////////////////////

        CMoveAcionState     getMoveAcionState();
        void                setMoveAcionState( CMoveAcionState state );

        ////////////////////////////////////////////////////////////////////////////////////

		void				setIsWait( Bool isWait );

		////////////////////////////////////////////////////////////////////////////////////

		Vec3				getDestination();

		void				addEntityLineMoveAcionListener( CCSEntityLineMoveAcion* moveAcion );

		////////////////////////////////////////////////////////////////////////////////////

		ISceneNodeGridLineMoveToAction* getCurrSceneNodeGridLineMoveToAction();
        
    protected:

        Bool                isNeedMoveToStartPos();
        void                moveToStartPos();
        void                moveToEndPos();


        virtual void        onLinedStateEnter(LinedStateObject* obj);
        virtual void        onLinedStateLeave(LinedStateObject* obj);
        virtual void        onLinedStateChanged(LinedStateObject* obj);

    protected:

        // 计算实际速度
        void                calculateRealMoveSpeed( );

        // 检测是否实体在起始点并创建引擎无碰撞移动Action

        // 创建引擎碰撞直线移动Acion


    private:

        CSceneEntity*  mEntity;

        CMoveAcionState mCMoveAcionState;

        Vec3        mStartPos;
        Vec3        mEndPos;
        Flt         mDelayPushTime;

        Str         mAnimName;
        Bool        mIsAutoAnimEnd;
        Bool        mAnimPlaying;

		Bool		mIsBlockCheck;

        Flt         mMoveSpeed;
        Flt         mRealMoveSpeed;
        Flt         mYawSpeed;

		Flt			mPathRadius;

		Bool		mIsStartMove;

        ISceneNodeGridLineMoveToAction* mSceneNodeLineMoveToStartPosAction;
        ISceneNodeGridLineMoveToAction* mSceneNodeLineMoveToEndPosAction;
        Bool        mIsPrepareMoveEndPos;
        Bool        mIsAlreadyMoveEndPos;
		Str			mSceneNodeLineMoveToActionName;

		IBlockManager*	mBlockManager;

		std::vector<CCSEntityLineMoveAcion*> mMoveAcionListenerList;

		ISceneNodeGridLineMoveToAction::MoveToPathFindType mMoveToPathFindType;

		Flt			mWaitTime;
		Bool		mIsWaitMove;
		Flt			mWaitMoveTime;

        // 移动灰尘特效调用
        //MoveDustEffectCollection

    };


    /******************************************************************************/
    //请求交互行为
    /******************************************************************************/

    class CCSEntityRequestInteractAcion : public LinedStateObject
    {
    public:
        
        CCSEntityRequestInteractAcion( CSceneEntity* requestEntity, CSceneEntity* desEntity );
        virtual ~CCSEntityRequestInteractAcion();

    public:

        //状态名字
        static Str STATE_NAME;


        ///更新事件
        virtual void        update( Flt delta );
        ///是否结束了
        virtual Bool        isFinished();
        ///进去状态事件
        virtual void        onEnter();
        ///离开状态事件
        virtual void        onLeave();

        /////////////////////////////////////////////////////////////////////

        // 得到合适的交互点位置
        Vec3                getSuitableInteractPosition();

    private:

        // 请求交互对象
        CSceneEntity*  mRequestEntity;

        // 交互目标对象
        CSceneEntity*  mDesEntity;
    };


    


}


/******************************************************************************/

#endif //