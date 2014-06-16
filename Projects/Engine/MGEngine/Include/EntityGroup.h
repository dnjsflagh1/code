/******************************************************************************/
#ifndef _ENTITYGROUP_H_
#define _ENTITYGROUP_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "IEntity.h"
#include "ILogicBinder.h"
#include "OgreEntity.h"
#include "OgreEntityWrapper.h"
#include "IEntityGroup.h"
#include "CollisionSystem.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //��Ϸʵ�����
    /******************************************************************************/
    class EntityGroupInstance : public IEntity, public ISceneNode
    {
	public:
		EntityGroupInstance(Str groupName,EntityGroup* entityGroup, 
			InstancedGeometry::InstancedObject* instancedObj, InstancedGeometry::BatchInstance* batchInstance);
		virtual ~EntityGroupInstance();

        /// �������ǰ
        virtual void                        preRendering();
        /// �������ǰ
        virtual void                        postRendering();

        //����
        void                                update( Flt delta );

		/// �õ�����
		virtual SceneObjectTypes            getType();

		/// �õ��ռ�ڵ�
		virtual ISceneNode*                 getSceneNode();

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
        /// �Ƿ���Ⱦ
        virtual void						setRenderingDirty();

    public:

        /// ������������
        void                                createAnimationController(Str groupName);
        /// ���ٶ�������
        void                                destroyAnimationController();
        /// ���¶�������
        void                                updateAnimationController( Flt delta );

    public:
        //ISceneNode

        /// �õ���������
        virtual IScene*                     getScene();

        /// ���ÿɼ���
        virtual void                        setVisible(Bool visible) ;
        /// �õ��ɼ���
        virtual Bool                        getVisible() ;

        /////////////////////////////////////////////////////////////////////////////////////

        /// ����λ������.
        virtual void                        setPosition(Vec3& pos) ;
        /// �õ�λ������.
        virtual void                        getPosition(Vec3& pos) ;
		/// ���ó�ʼλ��ƫ��. 
		virtual void						setPositionOffset(const Vec3& offset);
		/// ��ȡ��ʼλ��ƫ��. 
		virtual const Vec3&					getPositionOffset() const;
		/// �õ���Ļ����
		virtual void                        getScreenPosition(Vec2& outPos) ;
		
        /// �õ�λ�ñ仯��ǩ. 
        virtual Bool                        getPositionDirty();
        /// ���λ�ñ仯��ǩ. 
        virtual void                        clearPositionDirty();

        /// ���λ��.
        virtual void                        translate(Vec3& d, TransformSpace relativeTo = TS_PARENT) ;

        /////////////////////////////////////////////////////////////////////////////////////

        /// ��������.
        virtual void                        setScale(Vec3& scale) ;
        /// �õ�����.
        virtual void                        getScale(Vec3& scale) ;
		/// ���ó�ʼ����. 
		virtual void						setInitScale(const Vec3& scale);
		/// ��ȡ��ʼ����. 
		virtual const Vec3&					getInitScale() const;
        /// �õ����ű仯��ǩ. 
        virtual Bool                        getScaleDirty();
        /// ������ű仯��ǩ. 
        virtual void                        clearScaleDirty() ;

        /////////////////////////////////////////////////////////////////////////////////////

        /// ����4Ԫ��.
        virtual void                        setOrientation(Qua& quaternion) ;
        /// �õ�4Ԫ��.
        virtual void                        getOrientation(Qua& quaternion) ;
        /// �õ�4Ԫ���仯��ǩ.  
        virtual Bool                        getOrientationDirty();
        /// �õ�4Ԫ���仯��ǩ.  
        virtual void                        clearOrientationDirty();

        /// ���÷���.
        virtual void                        setDirection(Vec3& vec, TransformSpace relativeTo = TS_WORLD) ;
        /// �õ�����.
        virtual void                        getDirection(Vec3& vec);

        /// ����ĳ��.
        virtual void                        lookAt(Vec3& targetPoint, TransformSpace relativeTo = TS_WORLD) ;

        /// roll��ת.
        virtual void                        roll( Flt angle, TransformSpace relativeTo = TS_LOCAL) ;
        /// pitch��ת.
        virtual void                        pitch( Flt angle, TransformSpace relativeTo = TS_LOCAL) ;
        /// yaw��ת.
        virtual void                        yaw( Flt angle, TransformSpace relativeTo = TS_LOCAL) ;

        /// ����ĳ�᷽����ת.
        virtual void                        rotate( Vec3& axis, Flt& angle, TransformSpace relativeTo = TS_LOCAL) ;

        /////////////////////////////////////////////////////////////////////////////////////

        /// ��������
        virtual void                        stickTerrain() ;

        /////////////////////////////////////////////////////////////////////////////////////


    private:

        EntityGroup*                mEntityGroup;
        InstancedGeometry::InstancedObject* 
                                    mInstancedObject;
		InstancedGeometry::BatchInstance*
									mBatchInstance;
		// �Ƿ���Ⱦ
		Bool						mRendering;				
        /// ����������
        AnimationController*        mAnimationController;
        /// �ϰ�����
        DynamicBlockObject*         mDynamicBlockObject;
        /// ��ײ����
        CollisionObject*            mCollisionObject;
        /// �����Ｏ�϶���
        EntityAccessoryCollection*  mEntityAccessoryCollection;

        /// �������߷���
        Vec3                        mTerrainRayDir1;
        /// �������߷���
        Vec3                        mTerrainRayDir2;

		//�߻�����ĳ�ʼλ��ƫ��
		Vec3								mPositionOffset;
		//�߻�����ĳ�ʼ��С����
		Vec3								mInitScale;

        //������
        Vector3                     mLocalDirectionVector;
        Vector3                     mWorldDirectionNormalisedVector;

        //�ɼ���
        Bool                        mVisible;

    };


    /******************************************************************************/
    //��Ϸʵ�������
    /******************************************************************************/
    class EntityGroup : public IEntityGroup,  public MovableObject::Listener
    {
        friend class MGRaySceneQuery;
        friend class Scene;
        friend class EntityGroupInstance;
        friend class CollisionSystem;

    public:
        EntityGroup(CChar* entityName, ModelDeclaration* modelDeclaration, Scene* scene, UInt num);
        virtual ~EntityGroup();
        
	public:

        /// �������ǰ
        virtual void                    preRendering();
        /// �������ǰ
        virtual void                    postRendering();

		/// ����
		virtual Bool                    update( Flt delta );
        virtual void                    refresh();

        /// Ӧ����Ⱦ����
        virtual void                    applyRenderConfig();
        /// ���ÿɼ���
        void                            applyVisibleFlag();

        /// �õ�����
        virtual SceneObjectTypes        getType();
        /// �õ��ռ�ڵ�
        virtual ISceneNode*             getSceneNode();

		// �õ�ʵ������
		virtual UInt					getEntityNum();
		/// �õ�ʵ�����
		virtual IEntity*				getEntity(UInt index);

        /// �õ�ģ��ʵ��
        virtual OgreEntityWrapper*      getModelObject();

		Scene*							getScene();

	protected:

		/// ����Instanced
		virtual void                    createInstancedGeometry( CChar* entityName, ModelDeclaration* modelDeclaration, UInt num );
		/// ����Instanced
		virtual void                    destroyInstancedGeometry();

    protected:

        virtual bool                    objectRendering(const MovableObject*, const Ogre::Camera*);

	protected:

		Scene*								mScene;
		OgreEntityWrapper*					mOgreEntityTemplate;
		InstancedGeometry*					mInstancedGeometry;
    
        typedef std::vector<EntityGroupInstance*>  EntityGroupInstancesList;
        typedef std::map<const Ogre::MovableObject *, EntityGroupInstancesList> EntityGroupInstancesMap;
		EntityGroupInstancesMap	    mEntityGroupInstanceMap;
        EntityGroupInstancesList	mEntityGroupInstanceList;

        /// ʵ������
        NameGenerator mEntityInstanceNameGenerator;
    };

}

/******************************************************************************/

#endif
