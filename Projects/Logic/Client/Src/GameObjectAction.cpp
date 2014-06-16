/******************************************************************************/
#include "stdafx.h"
#include "GameObjectAction.h"
/******************************************************************************/

namespace MG
{

    Str GameObjectMoveToAction::STATE_NAME = "GameObjectMoveToAction";
    //-----------------------------------------------------------------------
    GameObjectMoveToAction::GameObjectMoveToAction( GameObject* object, Vec3 dest, Str animName, Flt speed)
        :LinedStateObject(STATE_NAME)
        ,mObject(object)
        ,mDestination(dest)
        ,mAnimName(animName)
        ,mSpeed(speed)
    {
        
    }

    //-----------------------------------------------------------------------
    GameObjectMoveToAction::~GameObjectMoveToAction()
    {

    }

    //-----------------------------------------------------------------------
    void GameObjectMoveToAction::update()
    {
        
    }

    //-----------------------------------------------------------------------
    Bool GameObjectMoveToAction::isFinished()
    {
        //是否移动结束
        return false;
    }

    //-----------------------------------------------------------------------
    void GameObjectMoveToAction::onEnter()
    {
        //开始移动并且播放动作
    }

    //-----------------------------------------------------------------------
    void GameObjectMoveToAction::onLeave()
    {
        //停止播放动作

    }




}