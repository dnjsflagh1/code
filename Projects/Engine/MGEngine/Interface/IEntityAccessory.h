/******************************************************************************/
#ifndef _IENTITYACCESSORY_H_
#define _IENTITYACCESSORY_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"


/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //游戏实体附属声明
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
    //游戏实体附属物管理接口
    /******************************************************************************/
    class IEntityAccessoryCollection
    {
    public: 

        // 绑定实体
        virtual void                        attachObject( Str name, IEntityAccessory& accessory ) = 0;
        // 移除实体
        virtual void                        detachObject( Str name ) = 0;

        // 得到绑定实体
        virtual IEntityAccessory*           getAttachObject( Str name ) = 0;

        // 得到绑定实体数量
        virtual UInt                        getAttachObjectCount() = 0;
        virtual IEntityAccessory*           getAttachObject(UInt index) = 0;

		// 更新动画之后更新他的位置
		virtual void						postFindVisibleObjects() = 0;

    };
    
}

/******************************************************************************/
#endif
