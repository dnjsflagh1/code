/******************************************************************************/
#ifndef _IENTITYACCESSORY_H_
#define _IENTITYACCESSORY_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"


/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //��Ϸʵ�帽������
    /******************************************************************************/
    class  IEntityAccessory
    {
	public:

        ISceneObject*   sceneObject;

        Vec3            relativePosition;
        Qua             relativeQuaternion;
        Str             bindBoneName;
        Bool            isSyncAnimation;
        Bool            isDepositLifeTime;

        IEntityAccessory()
            :sceneObject(NULL)
            ,relativePosition(Vec3(0,0,0))
            ,relativeQuaternion(Qua(1,0,0,0))
            ,bindBoneName("")
            ,isSyncAnimation(true)
            ,isDepositLifeTime(true)
        {
        }
    };


    /******************************************************************************/
    //��Ϸʵ�帽�������ӿ�
    /******************************************************************************/
    class IEntityAccessoryCollection
    {
    public: 

        // ��ʵ��
        virtual void                        attachObject( Str name, IEntityAccessory& accessory ) = 0;
        // �Ƴ�ʵ��
        virtual void                        detachObject( Str name ) = 0;

        // �õ���ʵ��
        virtual IEntityAccessory*           getAttachObject( Str name ) = 0;

        // �õ���ʵ������
        virtual UInt                        getAttachObjectCount() = 0;
        virtual IEntityAccessory*           getAttachObject(UInt index) = 0;

		// ���¶���֮���������λ��
		virtual void						postFindVisibleObjects() = 0;

    };
    
}

/******************************************************************************/
#endif
