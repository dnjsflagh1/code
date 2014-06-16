/******************************************************************************/
#ifndef _ENTITY_H_
#define _ENTITY_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "IEntity.h"
#include "ILogicBinder.h"
#include "OgreEntity.h"
#include "OgreEntityWrapper.h"
#include "MGSceneNode.h"
/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //游戏实体对象
    /******************************************************************************/
	class Entity : public IEntity , public MovableObject::Listener
    {
        friend class Scene;
    public:
		explicit Entity(CChar* entityName, ModelDeclaration* modelDeclaration, Scene* scene);
        explicit Entity(CChar* entityName, CChar* groupName, CChar* modelname, Scene* scene);

        virtual ~Entity();

        /// 引擎更新前
        virtual void                        preRendering();
        /// 引擎更新前
        virtual void                        postRendering();

        /// 更新
        virtual void                        update( Flt delta );

        /// 得到类型
        virtual SceneObjectTypes            getType();

        /// 得到空间节点
        virtual MGSceneNode*                getSceneNode();

        /// 得到模型实体
        virtual OgreEntityWrapper*          getModelObject();

        /// 得到动画控制器
        virtual IAnimationController*       getAnimationController();

        /// 创建或取回障碍对象
        virtual IDynamicBlockObject*        createOrRetrieveDynamicBlockObject();

		virtual IDynamicBlockObject*		getDynamicBlockObject();

        void                                destroyDynamicBlockObject();

        /// 创建或取回碰撞对象
        virtual ICollisionObject*           createOrRetrieveCollisionObject();
        void                                destroyCollisionObject();

        /// 得到附属物管理对象
        virtual IEntityAccessoryCollection* getEntityAccessoryCollection();

		/// 是否被渲染
		virtual Bool						isRendering();

		virtual void						setRenderGroup(U8 group, U8 priority = 100);

    protected:

        /// 创建动画管理
        void                                createAnimationController(U32 modelDeclId, Str path);
        /// 销毁动画管理
        void                                destroyAnimationController();
        /// 更新动画管理
        void                                updateAnimationController( Flt delta );

    protected:

		virtual bool						objectRendering(const Ogre::MovableObject*, const Ogre::Camera*);

    private:

		// 场景对象
        Scene*                          mScene;
		// 是否被渲染
		Bool							mRendering;
		// 实体渲染对象
        OgreEntityWrapper*              mOgreEntityWrapper;
        /// 动画管理器
        AnimationController*            mAnimationController;
        /// 障碍对象
        DynamicBlockObject*             mDynamicBlockObject;
        /// 碰撞对象
        CollisionObject*                mCollisionObject;
        /// 附属物集合对象
        EntityAccessoryCollection*      mEntityAccessoryCollection;
    };

}

/******************************************************************************/

#endif
