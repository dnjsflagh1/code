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
    //��Ϸʵ�����
    /******************************************************************************/
	class Entity : public IEntity , public MovableObject::Listener
    {
        friend class Scene;
    public:
		explicit Entity(CChar* entityName, ModelDeclaration* modelDeclaration, Scene* scene);
        explicit Entity(CChar* entityName, CChar* groupName, CChar* modelname, Scene* scene);

        virtual ~Entity();

        /// �������ǰ
        virtual void                        preRendering();
        /// �������ǰ
        virtual void                        postRendering();

        /// ����
        virtual void                        update( Flt delta );

        /// �õ�����
        virtual SceneObjectTypes            getType();

        /// �õ��ռ�ڵ�
        virtual MGSceneNode*                getSceneNode();

        /// �õ�ģ��ʵ��
        virtual OgreEntityWrapper*          getModelObject();

        /// �õ�����������
        virtual IAnimationController*       getAnimationController();

        /// ������ȡ���ϰ�����
        virtual IDynamicBlockObject*        createOrRetrieveDynamicBlockObject();

		virtual IDynamicBlockObject*		getDynamicBlockObject();

        void                                destroyDynamicBlockObject();

        /// ������ȡ����ײ����
        virtual ICollisionObject*           createOrRetrieveCollisionObject();
        void                                destroyCollisionObject();

        /// �õ�������������
        virtual IEntityAccessoryCollection* getEntityAccessoryCollection();

		/// �Ƿ���Ⱦ
		virtual Bool						isRendering();

		virtual void						setRenderGroup(U8 group, U8 priority = 100);

    protected:

        /// ������������
        void                                createAnimationController(U32 modelDeclId, Str path);
        /// ���ٶ�������
        void                                destroyAnimationController();
        /// ���¶�������
        void                                updateAnimationController( Flt delta );

    protected:

		virtual bool						objectRendering(const Ogre::MovableObject*, const Ogre::Camera*);

    private:

		// ��������
        Scene*                          mScene;
		// �Ƿ���Ⱦ
		Bool							mRendering;
		// ʵ����Ⱦ����
        OgreEntityWrapper*              mOgreEntityWrapper;
        /// ����������
        AnimationController*            mAnimationController;
        /// �ϰ�����
        DynamicBlockObject*             mDynamicBlockObject;
        /// ��ײ����
        CollisionObject*                mCollisionObject;
        /// �����Ｏ�϶���
        EntityAccessoryCollection*      mEntityAccessoryCollection;
    };

}

/******************************************************************************/

#endif
