/******************************************************************************/
#ifndef _ENTITYACCESSORY_H_
#define _ENTITYACCESSORY_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "IEntityAccessory.h"
#include "ISceneNode.h"
#include "AnimationController.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    // 实体附属物集合
    /******************************************************************************/
    class EntityAccessoryCollection : public IEntityAccessoryCollection, public IAnimationControllerListener, public ISceneNodeLisitener
    {
    public:

        EntityAccessoryCollection( IEntity* parent, Scene* scene );
        virtual ~EntityAccessoryCollection();


        // 更新
        void                                update( Flt delta );

		// 更新所有的位置相关信息
		void								postFindVisibleObjects();

        /////////////////////////////////////////////////////////////////////

        // 绑定实体
        virtual void                        attachObject( Str name, IEntityAccessory& accessory );
        // 移除实体
        virtual void                        detachObject( Str name );

        // 得到绑定实体
        virtual IEntityAccessory*           getAttachObject( Str name );

        // 得到绑定实体数量
        virtual UInt                        getAttachObjectCount();
        virtual IEntityAccessory*           getAttachObject(UInt index);

    protected:

        // 更新位置
        void                                updateObjectLocation( IEntityAccessory& accessory );
		// 更新大小
		void								updateObjectScale( IEntityAccessory& accessory );

        // 解除所有实体对象
        void                                detachAllObject();

        // 准备绑定实体 
        void                                prepareAttachObject( IEntityAccessory& accessory );
        // 准备移除实体
        void                                prepareDetachObject( IEntityAccessory& accessory );

        // 是否是有效的附属物
        Bool                                isValidAttachObject( IEntityAccessory& accessory );

    protected:

        virtual void                        onAnimationStart(CChar* animName);
        virtual void                        onAnimationStop(CChar* animName);
        virtual void                        onAnimationLoop(CChar* animName);

		virtual void						onRemove( ISceneNode* node );

    protected:

        IEntity*        mParent;
        Scene*          mScene;

        std::map< Str, IEntityAccessory >  mAttachs;

    };
}

/******************************************************************************/

#endif
