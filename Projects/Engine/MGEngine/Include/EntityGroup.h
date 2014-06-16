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
    //游戏实体对象
    /******************************************************************************/
    class EntityGroupInstance : public IEntity, public ISceneNode
    {
	public:
		EntityGroupInstance(Str groupName,EntityGroup* entityGroup, 
			InstancedGeometry::InstancedObject* instancedObj, InstancedGeometry::BatchInstance* batchInstance);
		virtual ~EntityGroupInstance();

        /// 引擎更新前
        virtual void                        preRendering();
        /// 引擎更新前
        virtual void                        postRendering();

        //更新
        void                                update( Flt delta );

		/// 得到类型
		virtual SceneObjectTypes            getType();

		/// 得到空间节点
		virtual ISceneNode*                 getSceneNode();

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
        /// 是否被渲染
        virtual void						setRenderingDirty();

    public:

        /// 创建动画管理
        void                                createAnimationController(Str groupName);
        /// 销毁动画管理
        void                                destroyAnimationController();
        /// 更新动画管理
        void                                updateAnimationController( Flt delta );

    public:
        //ISceneNode

        /// 得到所属场景
        virtual IScene*                     getScene();

        /// 设置可见性
        virtual void                        setVisible(Bool visible) ;
        /// 得到可见性
        virtual Bool                        getVisible() ;

        /////////////////////////////////////////////////////////////////////////////////////

        /// 设置位置坐标.
        virtual void                        setPosition(Vec3& pos) ;
        /// 得到位置坐标.
        virtual void                        getPosition(Vec3& pos) ;
		/// 设置初始位置偏移. 
		virtual void						setPositionOffset(const Vec3& offset);
		/// 获取初始位置偏移. 
		virtual const Vec3&					getPositionOffset() const;
		/// 得到屏幕坐标
		virtual void                        getScreenPosition(Vec2& outPos) ;
		
        /// 得到位置变化标签. 
        virtual Bool                        getPositionDirty();
        /// 清除位置变化标签. 
        virtual void                        clearPositionDirty();

        /// 相对位移.
        virtual void                        translate(Vec3& d, TransformSpace relativeTo = TS_PARENT) ;

        /////////////////////////////////////////////////////////////////////////////////////

        /// 设置缩放.
        virtual void                        setScale(Vec3& scale) ;
        /// 得到缩放.
        virtual void                        getScale(Vec3& scale) ;
		/// 设置初始缩放. 
		virtual void						setInitScale(const Vec3& scale);
		/// 获取初始缩放. 
		virtual const Vec3&					getInitScale() const;
        /// 得到缩放变化标签. 
        virtual Bool                        getScaleDirty();
        /// 清除缩放变化标签. 
        virtual void                        clearScaleDirty() ;

        /////////////////////////////////////////////////////////////////////////////////////

        /// 设置4元数.
        virtual void                        setOrientation(Qua& quaternion) ;
        /// 得到4元数.
        virtual void                        getOrientation(Qua& quaternion) ;
        /// 得到4元数变化标签.  
        virtual Bool                        getOrientationDirty();
        /// 得到4元数变化标签.  
        virtual void                        clearOrientationDirty();

        /// 设置方向.
        virtual void                        setDirection(Vec3& vec, TransformSpace relativeTo = TS_WORLD) ;
        /// 得到方向.
        virtual void                        getDirection(Vec3& vec);

        /// 朝向某点.
        virtual void                        lookAt(Vec3& targetPoint, TransformSpace relativeTo = TS_WORLD) ;

        /// roll旋转.
        virtual void                        roll( Flt angle, TransformSpace relativeTo = TS_LOCAL) ;
        /// pitch旋转.
        virtual void                        pitch( Flt angle, TransformSpace relativeTo = TS_LOCAL) ;
        /// yaw旋转.
        virtual void                        yaw( Flt angle, TransformSpace relativeTo = TS_LOCAL) ;

        /// 沿着某轴方向旋转.
        virtual void                        rotate( Vec3& axis, Flt& angle, TransformSpace relativeTo = TS_LOCAL) ;

        /////////////////////////////////////////////////////////////////////////////////////

        /// 贴近地面
        virtual void                        stickTerrain() ;

        /////////////////////////////////////////////////////////////////////////////////////


    private:

        EntityGroup*                mEntityGroup;
        InstancedGeometry::InstancedObject* 
                                    mInstancedObject;
		InstancedGeometry::BatchInstance*
									mBatchInstance;
		// 是否被渲染
		Bool						mRendering;				
        /// 动画管理器
        AnimationController*        mAnimationController;
        /// 障碍对象
        DynamicBlockObject*         mDynamicBlockObject;
        /// 碰撞对象
        CollisionObject*            mCollisionObject;
        /// 附属物集合对象
        EntityAccessoryCollection*  mEntityAccessoryCollection;

        /// 地面射线方向
        Vec3                        mTerrainRayDir1;
        /// 地面射线方向
        Vec3                        mTerrainRayDir2;

		//策划定义的初始位置偏移
		Vec3								mPositionOffset;
		//策划定义的初始大小缩放
		Vec3								mInitScale;

        //正朝向
        Vector3                     mLocalDirectionVector;
        Vector3                     mWorldDirectionNormalisedVector;

        //可见度
        Bool                        mVisible;

    };


    /******************************************************************************/
    //游戏实体对象组
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

        /// 引擎更新前
        virtual void                    preRendering();
        /// 引擎更新前
        virtual void                    postRendering();

		/// 更新
		virtual Bool                    update( Flt delta );
        virtual void                    refresh();

        /// 应用渲染配置
        virtual void                    applyRenderConfig();
        /// 设置可见组
        void                            applyVisibleFlag();

        /// 得到类型
        virtual SceneObjectTypes        getType();
        /// 得到空间节点
        virtual ISceneNode*             getSceneNode();

		// 得到实体数量
		virtual UInt					getEntityNum();
		/// 得到实体对象
		virtual IEntity*				getEntity(UInt index);

        /// 得到模型实体
        virtual OgreEntityWrapper*      getModelObject();

		Scene*							getScene();

	protected:

		/// 创建Instanced
		virtual void                    createInstancedGeometry( CChar* entityName, ModelDeclaration* modelDeclaration, UInt num );
		/// 销毁Instanced
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

        /// 实体名字
        NameGenerator mEntityInstanceNameGenerator;
    };

}

/******************************************************************************/

#endif
