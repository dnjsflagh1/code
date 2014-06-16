/******************************************************************************/
#ifndef _SCENENODESPECIALMOVEACTION_H_
#define _SCENENODESPECIALMOVEACTION_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "LinedState.h"
#include "ISceneNodeAction.h"
#include "SceneNodeAction.h"

/******************************************************************************/
namespace MG
{
    

    /******************************************************************************/
    //场景节点对象抛物线移动行为
    /******************************************************************************/
    class SceneNodeParabolaMoveToAction : public SceneNodeLineMoveToAction
    {
    public:
        SceneNodeParabolaMoveToAction( ISceneNode* object );
        virtual ~SceneNodeParabolaMoveToAction();
        //状态名字
        static Str STATE_NAME;
    public:

    protected:
        virtual void	onEnter();

        virtual void	onLeave();

        virtual void	update( Flt delta );

        virtual Bool	isFinished();

    private:
        /// 上升的速度
        Flt				mSpeedY;
        ///重力
        Flt				mGravity;

    };


    /******************************************************************************/
    //场景节点对象曲线移动行为
    /******************************************************************************/
    class SceneNodeCurveMoveToAction : public SceneNodeLineMoveToAction
    {
    public:
        SceneNodeCurveMoveToAction( ISceneNode* object );
        virtual ~SceneNodeCurveMoveToAction();
        //状态名字
        static Str STATE_NAME;
    public:

    protected:
        virtual void	onEnter();

        virtual void	onLeave();

        virtual void	update( Flt delta );

        virtual Bool	isFinished();

    private:
        /// 上升的速度
        Flt				mSpeedZ;
        ///重力
        Flt				mGravity;

        Vector3			mMoveDis;
        Vector3			mMoveDir;

    };
}

/******************************************************************************/

#endif