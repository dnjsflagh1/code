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
    //�����ڵ�����������ƶ���Ϊ
    /******************************************************************************/
    class SceneNodeParabolaMoveToAction : public SceneNodeLineMoveToAction
    {
    public:
        SceneNodeParabolaMoveToAction( ISceneNode* object );
        virtual ~SceneNodeParabolaMoveToAction();
        //״̬����
        static Str STATE_NAME;
    public:

    protected:
        virtual void	onEnter();

        virtual void	onLeave();

        virtual void	update( Flt delta );

        virtual Bool	isFinished();

    private:
        /// �������ٶ�
        Flt				mSpeedY;
        ///����
        Flt				mGravity;

    };


    /******************************************************************************/
    //�����ڵ���������ƶ���Ϊ
    /******************************************************************************/
    class SceneNodeCurveMoveToAction : public SceneNodeLineMoveToAction
    {
    public:
        SceneNodeCurveMoveToAction( ISceneNode* object );
        virtual ~SceneNodeCurveMoveToAction();
        //״̬����
        static Str STATE_NAME;
    public:

    protected:
        virtual void	onEnter();

        virtual void	onLeave();

        virtual void	update( Flt delta );

        virtual Bool	isFinished();

    private:
        /// �������ٶ�
        Flt				mSpeedZ;
        ///����
        Flt				mGravity;

        Vector3			mMoveDis;
        Vector3			mMoveDir;

    };
}

/******************************************************************************/

#endif