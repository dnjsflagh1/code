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
        //�Ƿ��ƶ�����
        return false;
    }

    //-----------------------------------------------------------------------
    void GameObjectMoveToAction::onEnter()
    {
        //��ʼ�ƶ����Ҳ��Ŷ���
    }

    //-----------------------------------------------------------------------
    void GameObjectMoveToAction::onLeave()
    {
        //ֹͣ���Ŷ���

    }




}