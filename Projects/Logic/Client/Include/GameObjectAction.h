/******************************************************************************/
#ifndef _GAMEOBJECTACTION_H_
#define _GAMEOBJECTACTION_H_
/******************************************************************************/

#include "LinedState.h"
#include "GameObject.h"

/******************************************************************************/

namespace MG
{
    

    /******************************************************************************/
    //游戏对象移动行为
    /******************************************************************************/
    class GameObjectMoveToAction : public LinedStateObject
    {
    public:
        GameObjectMoveToAction( GameObject* object, Vec3 dest, Str animName, Flt speed = 1);
        virtual ~GameObjectMoveToAction();

    public:
        
        //状态名字
        static Str STATE_NAME;

        ///更新事件
        virtual void        update();
        ///是否结束了
        virtual Bool        isFinished();
        ///进去状态事件
        virtual void        onEnter();
        ///离开状态事件
        virtual void        onLeave();

    private:
        
        GameObject* mObject;
        Vec3 mDestination;
        Str mAnimName;
        Flt mSpeed;
    };

}


/******************************************************************************/

#endif //