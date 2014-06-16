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
    //��Ϸ�����ƶ���Ϊ
    /******************************************************************************/
    class GameObjectMoveToAction : public LinedStateObject
    {
    public:
        GameObjectMoveToAction( GameObject* object, Vec3 dest, Str animName, Flt speed = 1);
        virtual ~GameObjectMoveToAction();

    public:
        
        //״̬����
        static Str STATE_NAME;

        ///�����¼�
        virtual void        update();
        ///�Ƿ������
        virtual Bool        isFinished();
        ///��ȥ״̬�¼�
        virtual void        onEnter();
        ///�뿪״̬�¼�
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