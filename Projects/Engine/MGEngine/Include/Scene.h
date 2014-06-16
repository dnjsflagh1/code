/******************************************************************************/
#ifndef _SCENE_H_
#define _SCENE_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "IScene.h"
#include "Camera.h"
#include "Gui.h"
#include "TerrainManager.h"
#include "Entity.h"
#include "EntityGroup.h"
#include "StaticEntitySet.h"
#include "EffectEntity.h"
#include "TerrainDecal.h"
#include "SceneXmlSerializer.h"
#include "EffectXmlSerializer.h"
#include "SceneObjectController.h"
#include "WireframeManager.h"
#include "ActionManager.h"
#include "BlockManager.h"
#include "DynamicBlockObjectSceneManager.h"
#include "PathFindingManager.h"
#include "ShadowManager.h"
#include "MiniMapManager.h"
#include "CollisionSystem.h"
#include "CompositorManager.h"
#include "TreeManager.h"
#include "SceneDebuger.h"

// CN_MODIFY
#include "PUEffect.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//游戏场景
	/******************************************************************************/
    class Scene : public IScene, public Ogre::SceneManager::Listener, public Ogre::RenderSystem::Listener, public Ogre::RenderQueueListener
	{
        friend class Camera;
        friend class Gui;
        friend class Terrain;
        friend class MGRaySceneQuery;
        friend class CollisionSystem;
		friend class SceneObjectController;

	public:

        Scene(CChar* sceneName, CChar* camName);
        virtual ~Scene();
        
        /// 渲染之前需要做的事情
                void                    preRendering();
        /// 渲染之后需要做的事情
                void                    postRendering();

        /// 更新场景
        virtual Bool                    update( Flt delta );

        ///////////////////////////////////////////////////////////////////////////////////////

    public:

        /// 增加一个LOD
        virtual void                    addLod(UInt index, Flt distance); 
        virtual void                    clearLod(); 
        virtual UInt                    getLodCount(); 
        virtual LodInfo                 getLod(UInt index); 

        ///////////////////////////////////////////////////////////////////////////////////////

    public:

        /// 应用显示参数修改
        virtual void                    applyRenderConfig();
        /// 显示分辨率修改
        virtual void                    applyResolutionConfig(UInt nScreenX, UInt nScreenY);

        ///////////////////////////////////////////////////////////////////////////////////////
        
    public:
        
        /// 得到场景序列化对象
        virtual SceneXmlSerializer*     getXmlSerializer();

		/// 得到特效序列化对象
		//virtual EffectXmlSerializer*	getEffectSerializer();
        ///////////////////////////////////////////////////////////////////////////////////////

    public:

		/// 得到场景对象控制器
		virtual SceneObjectController*  getSceneObjectController(Bool isCreateController = true);

        /// 设置资源加载监听器
        virtual void                    setResourceLoadListener(ResourceLoadListener* listener);
		/// 设置资源存储监听器
		virtual void                    setResourceSaveListener(ResourceSaveListener* listener);
        /// 得到资源加载监听器
        virtual ResourceLoadListener*   getResourceLoadListener();
		/// 得到资源存储监听器
		virtual ResourceSaveListener*   getResourceSaveListener();

        ///////////////////////////////////////////////////////////////////////////////////////

    public:

        /// 删除场景对象. 
        virtual void                    destroySceneObject(CChar* name, SceneObjectTypes type); 
        /// 清空所有对象. 
        virtual void                    clear(); 

        ///////////////////////////////////////////////////////////////////////////////////////

    public:

		/// 设置单位缩放 //参考单位为米
		virtual void                    setUnitScale( Flt scale ){mUnitScale=scale;}; 
		/// 得到单位缩放 //参考单位为米
		virtual Flt						getUnitScale(){return mUnitScale;}; 

        ///////////////////////////////////////////////////////////////////////////////////////

    public:

        //得到查询标志位
        static Int                      getQueryMask( SceneObjectTypes type );
    
        ///////////////////////////////////////////////////////////////////////////////////////

    public:

        /// 创建摄像机
        virtual Camera*                 createCamera(CChar* name); 
        /// 卸载所有摄像机
        virtual void                    destroyAllCamera();
		/// 得到摄像机
		virtual Camera*                 getCamera(CChar* name); 
        /// 更新摄像机
        virtual void                    updateAllCamera( Flt delta );

        /// 得到Viewport
        virtual Viewport*               getMainViewport(); 
  
        ///////////////////////////////////////////////////////////////////////////////////////

    public:

        /// 设置活动的摄像机
        virtual void                    setActiveCamera(CChar* name);
		virtual Camera*	                getActiveCamera();
		//virtual	Ogre::Camera*			getActiveShadowCamera();
		virtual Ogre::String			getActiveShadowCameraName() const { return mActiveShadowCasterCameraName; }
        ///////////////////////////////////////////////////////////////////////////////////////

    public:

        /// 创建灯光 
        virtual ILight*                 createLight(CChar* name) ; 
        /// 得到灯光
        virtual ILight*                 getLight(CChar* name); 
		/// 销毁灯光
		virtual void					destroyLight(CChar* name);
        /// 创建默认灯光 
        virtual ILight*                 createDefaultLight() ; 
        /// 得到默认灯光
        virtual ILight*                 getDefaultLight(); 
        /// 卸载灯光 
        virtual void                    destroyAllLight() ;

        ///////////////////////////////////////////////////////////////////////////////////////

    public:
		
		/// 创建实体 
		virtual Entity*                 createEntity(CChar* name, U32 modelDeclID); 
		/// 创建实体 
		virtual Entity*                 createEntity(U32 modelDeclID,CChar* prefixName=NULL); 
		/// 创建槽位实体,供特效绑定使用
		virtual Entity*                 createSlotEntity(CChar* name, U32 modelDeclID); 
		/// 创建槽位实体,供特效绑定使用
		virtual Entity*                 createSlotEntity(U32 modelDeclID,CChar* prefixName=NULL); 
		/// 销毁实体
        virtual void                    destroyEntity(CChar* name);
		/// 销毁槽位实体
		virtual void                    destroySlotEntity(CChar* name); 
        /// 得到实体 
        virtual Entity*                 getEntity(CChar* name); 
		/// 顺序访问Entity
		virtual Entity*					getEntity(U32 index);
		/// 得到槽位实体 
		virtual Entity*                 getEntityfromSlot(CChar* name); 
		/// 根据槽位获取Entity
		virtual Entity*					getEntityfromSlot(U32 slot);
		/// 得到指定组实体数量
		virtual UInt					getEntityCount();
        /// 得到指定组实体数量
        virtual UInt                    getEntityCount(CChar* group);
        /// 得到指定组实体
        virtual void                    getEntityList(CChar* group, IEntity** buff, UInt count);
        /// 卸载实体 
        virtual void                    destroyAllEntity();
        /// 更新实体 
        virtual void                    updateAllEntity( Flt delta, RENDER_STATE state = RS_IDLE );

        /// 创建实体附属物
        virtual void                    createEntityStaticAccessorys( IEntity* entity, U32 componentID );
		/// 动态创建实体附属物
		virtual bool					createEntityDynamicAccessorys( IEntity* entity, CChar* suffix, U32 resourceID, SceneObjectTypes resourceType, IEntityAccessory* accessoryInfo, Bool isCreateEntity = false );
		/// 根据PUEffect对象指针来绑定实体,而不根据effectResID
		bool							createEntityDynamicAccessorys( IEntity* entity, PUEffect* puEffect, IEntityAccessory* accessoryInfo);
		/// 动态销毁实体附属物
		virtual void					destroyEntityDynamicAccessorys( IEntity* entity, CChar* name );

        ///////////////////////////////////////////////////////////////////////////////////////

    public:

		/// 创建实体 组
		virtual EntityGroup*			createEntityGroup(CChar* name, U32 modelDeclID,UInt num); 
		/// 创建实体组
		virtual EntityGroup*			createEntityGroup(U32 modelDeclID,UInt num,CChar* prefixName = NULL); 
		/// 得到实体组 
		virtual EntityGroup*			getEntityGroup(CChar* name); 
		/// 销毁实体组
		virtual void                    destroyEntityGroup(CChar* name); 
		/// 卸载实体组
		virtual void                    destroyAllEntityGroup();
		/// 更新实体组 
		virtual void                    updateAllEntityGroup( Flt delta, RENDER_STATE state = RS_IDLE );

        /// 创建实体组附属物
        virtual void                    createEntityGroupAccessorys( IEntityGroup* entity, U32 componentID  );

        ///////////////////////////////////////////////////////////////////////////////////////

    public:

        /// 创建静态实体 
        virtual void                    addStaticEntity(U32 modelDeclID,
                                            Vec3& pos, Qua& orientation, Vec3& scale, Bool isRandom, 
                                            Str staticGroup, Bool isReset); 
        /// 创建静态实体 
        virtual void                    addStaticEntityAccessorys( U32 componentID, Vec3& pos, Qua& orientation, Vec3& scale ); 

        /// 得到静态实体组
        virtual StaticEntitySet*        getStaticEntitySet( U32 modelDeclID );
      
        /// 构建静态实体 
        virtual void                    buildStaticEntity(); 

    protected:

        /// 创建静态实体 组
        virtual StaticEntitySet*        createStaticEntitySet(U32 modelDeclID); 

        /// 卸载静态实体 
        virtual void                    destroyAllStaticEntity();

        /// 更新态实体 
        virtual void                    updateStaticEntity( Flt delta );

        ///////////////////////////////////////////////////////////////////////////////////////

    public:
		///////////////////////////////////////////////////////////////////////////////////////
		// 新的特效 CN_MODIFY
		virtual EffectComponent*		createEffectComponent(CChar* name, U32 effectResID, Bool isAutoDestroy = true, Bool isAutoStart = true);

		virtual EffectComponent*		createEffectComponent(U32 effectResID, Bool isAutoDestroy = true, Bool isAutoStart = true);

		virtual EffectComponent*		createEffectComponent(CChar* name, CChar* fullfilename, Bool isAutoDestroy = true, Bool isAutoStart = true);

		virtual EffectComponent*		createEffectComponent(CChar* fullfilename, Bool isAutoDestroy = true, Bool isAutoStart = true);

		virtual EffectComponent*		createEmptyEffectComponent();

		virtual EffectComponent*		createEmptyEffectComponent(CChar* name);
		/// 销毁新的特效
		virtual void                    destroyEffectComponent(CChar* name) ; 
		/// 得到新的特效
		virtual EffectComponent*        getEffectComponent(CChar* name) ; 
		/// 得到新的特效
		virtual EffectComponent*        getEffectComponent(U32 index) ; 
		/// 卸载新的特效
		virtual void                    destroyAllEffectComponent() ;
		/// 更新新的特效 
		virtual void                    updateAllEffectComponent( Flt delta );
		///////////////////////////////////////////////////////////////////////////////////////

		/// 创建EffectComponent里的PU
		virtual PUEffect*				createPUEffect(CChar* name, CChar* effectTemplate, Bool isAutoDestroy = true, Bool isAutoStart = true);
		/// 创建EffectComponent里的PU
		virtual PUEffect*				createPUEffect(CChar* effectTemplate, Bool isAutoDestroy = true, Bool isAutoStart = true);
		/// 创建EffectComponent里的PU
		virtual PUEffect*				createPUEffect(U32 effectResID, Bool isAutoDestroy = true, Bool isAutoStart = true);
		/// 创建EffectComponent里的PU
		virtual PUEffect*				createPUEffect(CChar* name, U32 effectResID, Bool isAutoDestroy = true, Bool isAutoStart = true);
		/// 销毁EffectComponent里的PU
		virtual void					destroyPUEffect(CChar* name) ; 
		/// 得到EffectComponent里的PU
		virtual PUEffect*			    getPUEffect(CChar* name) ; 
		/// 卸载EffectComponent里的PU
		virtual void		            destroyAllPUEffect() ;
		/// 更新EffectComponent里的PU 
		virtual void		            updateAllPUEffect( Flt delta );

		/// 创建特效
        virtual EffectEntity*           createEffectEntity(CChar* name, U32 effectResID, Bool isAutoDestroy = true, Bool isAutoStart = true) ; 
        /// 创建特效
        virtual EffectEntity*           createEffectEntity(U32 effectResID, Bool isAutoDestroy = true, Bool isAutoStart = true) ; 
        /// 销毁特效
        virtual void                    destroyEffectEntity(CChar* name) ; 
        /// 得到特效
        virtual EffectEntity*           getEffectEntity(CChar* name) ; 
        /// 卸载特效
        virtual void                    destroyAllEffectEntity() ;
        /// 更新特效 
        virtual void                    updateAllEffectEntity( Flt delta );

        ///////////////////////////////////////////////////////////////////////////////////////

        ///// 创建地形贴花集合
        //virtual ITerrainDecalSet*       createTerrainDecalSet(CChar* name, UInt num, CChar* texFileName);
        ///// 创建地形贴花集合
        //virtual ITerrainDecalSet*       createTerrainDecalSet(UInt num, CChar* texFileName);
        ///// 销毁地形贴花
        //virtual void                    destroyTerrainDecalSet(CChar* name); 
        ///// 得到地形贴花
        //virtual TerrainDecalSet*        getTerrainDecalSet(CChar* name); 
        ///// 卸载地形贴花
        //virtual void                    destroyAllTerrainDecalSet();
        ///// 更新地形贴花
        //virtual void                    updateAllTerrainDecalSet( Flt delta, RENDER_STATE state = RS_IDLE );

		///////////////////////////////////////////////////////////////////////////////////////

		/// 创建高精度贴花集合
		virtual IDecalSet*				createDecalSet(CChar* name, UInt num, CChar* texFileName, IDecalType type);
		/// 创建高精度贴花集合
		virtual IDecalSet*				createDecalSet(UInt num, CChar* texFileName, IDecalType type);
		/// 销毁高精度贴花
		virtual void                    destroyDecalSet(CChar* name); 
		/// 得到高精度贴花
		virtual IDecalSet*				getDecalSet(CChar* name); 
		/// 卸载高精度贴花
		virtual void                    destroyAllDecalSet();
		/// 更新高精度贴花
		void							updateAllDecalSet( Flt delta, RENDER_STATE state = RS_IDLE );
        ///////////////////////////////////////////////////////////////////////////////////////

        /// 创建Gui.
        virtual Gui*                    createGui(CChar* resourceFileName, CChar* coreFileName, Str8 fontName, IPointer*& pIPointer, IFont*& pIFont); 
        /// 卸载Gui
        virtual void                    destroyGui();

				Gui*					getGui() { return mGui; }
    
        ///////////////////////////////////////////////////////////////////////////////////////

        /// 得到小地图管理器
        virtual MiniMapManager*         getMiniMapManager();
        /// 得到阴影管理器
        virtual ShadowManager*          getShadowManager(); 
        /// 得到线框管理器
        virtual WireframeManager*       getWireframeManager(); 
        /// 得到地形对象
        virtual TerrainManager*         getTerrainManager();
        /// 得到地形对象
        Ogre::SceneManager*             getOgreSceneManager(){return mOgreSceneManager;};
        /// 得到碰撞系统对象
        virtual CollisionSystem*        getCollisionSystem();
        /// 得到行为管理对象
        virtual IActionManager*         getActionManager();
        /// 得到障碍管理对象
        virtual BlockManager*           getBlockManager();

		virtual DynamicBlockObjectSceneManager*getDynamicBlockObjectSceneManager();
        /// 得到寻路管理器
        virtual PathFindingManager*     getPathFindingManager();
        /// 得到合成器管理者
        virtual CompositorManager*      getCompositorManager();
		/// 得到合成器管理者
		virtual TreeManager*			getTreeManager();
        /// 得到调试器
        virtual SceneDebuger*			getSceneDebuger();

        ///////////////////////////////////////////////////////////////////////////////////////

        /// 设置环境光
        virtual void                    setAmbientLight(const Color& colour);
        /// 得到环境光
        virtual Color                   getAmbientLight();
		/// 创建网格
		virtual void					createEffectGrid();
        ///////////////////////////////////////////////////////////////////////////////////////

    protected:

        /// 创建Ogre场景管理
        void                            createOgreScene(CChar* sceneName, CChar* camName);
        /// 卸载Ogre场景管理.
        void                            destroyOgreScene();

        ///////////////////////////////////////////////////////////////////////////////////////

    protected:

        /// Overridden from SceneManager::Listener
        virtual void                    preFindVisibleObjects(Ogre::SceneManager* source, 
                                            Ogre::SceneManager::IlluminationRenderStage irs, Ogre::Viewport* v);
        virtual void                    postFindVisibleObjects(SceneManager* source, 
                                            Ogre::SceneManager::IlluminationRenderStage irs, Viewport* v);

        virtual void                    shadowTextureCasterPreViewProj(Ogre::Light* light, Ogre::Camera* camera, size_t iteration);
        virtual void                    shadowTexturesUpdated(size_t numberOfShadowTextures);

        virtual void                    renderQueueStarted(uint8 queueGroupId, const String& invocation, bool& skipThisInvocation);
        virtual void                    renderQueueEnded(uint8 queueGroupId, const String& invocation, bool& repeatThisInvocation);

        ///////////////////////////////////////////////////////////////////////////////////////

        /// Overridden from RenderSystem::Listener
        virtual void                    eventOccurred(const String& eventName,  const NameValuePairList* parameters);
        /// 当设备丢失
        void                            onDeviceLost();
        /// 当设备重置
        void                            onDeviceReset();

        ///////////////////////////////////////////////////////////////////////////////////////


        ///////////////////////////////////////////////////////////////////////////////////////


        /// 更新debug信息
        void                            updateDebugInfo();

	protected:

		/// 单位缩放
		Flt	    mUnitScale;

        ResourceLoadListener* mResourceLoadListener;

		ResourceSaveListener* mResourceSaveListener;

        ///////////////////////////////////////////////////////////////////////////////////////

        /// Ogre的场景管理对象
		Ogre::SceneManager* mOgreSceneManager;
        /// Ogre的渲染视角对象
		Ogre::Viewport*  mOgreViewport;
        /// Gui对象
		Gui* mGui;
        /// 碰撞系统对象
        CollisionSystem* mCollisionSystem;
        /// 折线对象
        WireframeManager* mWireframeManager;
        /// 行为管理对象
        ActionManager* mActionManager;
        /// 障碍管理对象
        BlockManager* mBlockManager;

		DynamicBlockObjectSceneManager* mDynamicBlockObjectSceneManager;
        /// 寻路管理器
        PathFindingManager* mPathFindingManager;
        /// 合成器管理者
        CompositorManager* mCompositorManager;
        // 调试器
        SceneDebuger* mSceneDebuger;
        
        ///////////////////////////////////////////////////////////////////////////////////////

        /// 摄像机列表
        std::map<String, Camera*> mCameras;
		/// 活动摄像机
		Camera* mActiveCamera;

		/// 阴影投射摄像机
		Ogre::String mActiveShadowCasterCameraName;

        ///////////////////////////////////////////////////////////////////////////////////////

        /// 灯光列表
        std::map<String, Light*> mLights;

        ///////////////////////////////////////////////////////////////////////////////////////

        /// 实体列表
        std::map<String, Entity*> mEntitys;
		/// 槽位实体列表
		std::map<String, Entity*> mSlotEntitys;
        /// 实体名字
        NameGenerator mEntityNameGenerator;

        ///////////////////////////////////////////////////////////////////////////////////////

		/// 实体组列表
		std::map<String, EntityGroup*> mEntityGroup;
		/// 实体名字
		NameGenerator mEntityGroupNameGenerator;

        ///////////////////////////////////////////////////////////////////////////////////////

        /// 静态实体集列表
        std::map<U32, StaticEntitySet*> mStaticEntitySets;

        ///////////////////////////////////////////////////////////////////////////////////////

        /// EffectEntity列表
        std::map<String, EffectEntity*> mEffectEntitys;
        /// EffectEntity名字
        NameGenerator mEffectEntityNameGenerator;

		///////////////////////////////////////////////////////////////////////////////////////

		/// 新的Effect列表 CN_MODIFY
		std::map<String, EffectComponent*> mEffectComponents;
		/// EffectComponent名字
		NameGenerator mEffectComponentNameGenerator;
		/// 空的EffectComponent名字
		NameGenerator mEmptyEffectComponentNameGenerator;

		/// 新的EffectComponent里的PU列表
		std::map<String, PUEffect*> mPUEffects;
		/// PUEffect名字
		NameGenerator mPUEffectNameGenerator;

        ///////////////////////////////////////////////////////////////////////////////////////

        ///// TerrainDecalSet列表
        //std::map<String, TerrainDecalSet*> mTerrainDecalSets;
        ///// TerrainDecalSet名字
        //NameGenerator mTerrainDecalSetNameGenerator;

		/// DecalSet列表
		std::map<String, IDecalSet*> mDecalSets;
		/// DecalSet名字
		NameGenerator mDecalSetNameGenerator;

        ///////////////////////////////////////////////////////////////////////////////////////

        /// 小地图
        MiniMapManager* mMiniMapManager;

        /// 阴影管理
        ShadowManager* mShadowManager;

        /// 场景地形组对象
        TerrainManager* mTerrainManager;

        /// 场景序列化对象
        SceneXmlSerializer* mSceneXmlSerializer;

		/// 场景对象控制器
		SceneObjectController* mSceneObjectController;

		///
		//TreeManager* mTreeManager;
        ///////////////////////////////////////////////////////////////////////////////////////

        // LOD 列表
        std::vector<LodInfo> mLodInfos;

        ///////////////////////////////////////////////////////////////////////////////////////

        Flt mCurrFarClipDistance;


	};
	
}

/******************************************************************************/

#endif
