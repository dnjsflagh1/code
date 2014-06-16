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
	//��Ϸ����
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
        
        /// ��Ⱦ֮ǰ��Ҫ��������
                void                    preRendering();
        /// ��Ⱦ֮����Ҫ��������
                void                    postRendering();

        /// ���³���
        virtual Bool                    update( Flt delta );

        ///////////////////////////////////////////////////////////////////////////////////////

    public:

        /// ����һ��LOD
        virtual void                    addLod(UInt index, Flt distance); 
        virtual void                    clearLod(); 
        virtual UInt                    getLodCount(); 
        virtual LodInfo                 getLod(UInt index); 

        ///////////////////////////////////////////////////////////////////////////////////////

    public:

        /// Ӧ����ʾ�����޸�
        virtual void                    applyRenderConfig();
        /// ��ʾ�ֱ����޸�
        virtual void                    applyResolutionConfig(UInt nScreenX, UInt nScreenY);

        ///////////////////////////////////////////////////////////////////////////////////////
        
    public:
        
        /// �õ��������л�����
        virtual SceneXmlSerializer*     getXmlSerializer();

		/// �õ���Ч���л�����
		//virtual EffectXmlSerializer*	getEffectSerializer();
        ///////////////////////////////////////////////////////////////////////////////////////

    public:

		/// �õ��������������
		virtual SceneObjectController*  getSceneObjectController(Bool isCreateController = true);

        /// ������Դ���ؼ�����
        virtual void                    setResourceLoadListener(ResourceLoadListener* listener);
		/// ������Դ�洢������
		virtual void                    setResourceSaveListener(ResourceSaveListener* listener);
        /// �õ���Դ���ؼ�����
        virtual ResourceLoadListener*   getResourceLoadListener();
		/// �õ���Դ�洢������
		virtual ResourceSaveListener*   getResourceSaveListener();

        ///////////////////////////////////////////////////////////////////////////////////////

    public:

        /// ɾ����������. 
        virtual void                    destroySceneObject(CChar* name, SceneObjectTypes type); 
        /// ������ж���. 
        virtual void                    clear(); 

        ///////////////////////////////////////////////////////////////////////////////////////

    public:

		/// ���õ�λ���� //�ο���λΪ��
		virtual void                    setUnitScale( Flt scale ){mUnitScale=scale;}; 
		/// �õ���λ���� //�ο���λΪ��
		virtual Flt						getUnitScale(){return mUnitScale;}; 

        ///////////////////////////////////////////////////////////////////////////////////////

    public:

        //�õ���ѯ��־λ
        static Int                      getQueryMask( SceneObjectTypes type );
    
        ///////////////////////////////////////////////////////////////////////////////////////

    public:

        /// ���������
        virtual Camera*                 createCamera(CChar* name); 
        /// ж�����������
        virtual void                    destroyAllCamera();
		/// �õ������
		virtual Camera*                 getCamera(CChar* name); 
        /// ���������
        virtual void                    updateAllCamera( Flt delta );

        /// �õ�Viewport
        virtual Viewport*               getMainViewport(); 
  
        ///////////////////////////////////////////////////////////////////////////////////////

    public:

        /// ���û�������
        virtual void                    setActiveCamera(CChar* name);
		virtual Camera*	                getActiveCamera();
		//virtual	Ogre::Camera*			getActiveShadowCamera();
		virtual Ogre::String			getActiveShadowCameraName() const { return mActiveShadowCasterCameraName; }
        ///////////////////////////////////////////////////////////////////////////////////////

    public:

        /// �����ƹ� 
        virtual ILight*                 createLight(CChar* name) ; 
        /// �õ��ƹ�
        virtual ILight*                 getLight(CChar* name); 
		/// ���ٵƹ�
		virtual void					destroyLight(CChar* name);
        /// ����Ĭ�ϵƹ� 
        virtual ILight*                 createDefaultLight() ; 
        /// �õ�Ĭ�ϵƹ�
        virtual ILight*                 getDefaultLight(); 
        /// ж�صƹ� 
        virtual void                    destroyAllLight() ;

        ///////////////////////////////////////////////////////////////////////////////////////

    public:
		
		/// ����ʵ�� 
		virtual Entity*                 createEntity(CChar* name, U32 modelDeclID); 
		/// ����ʵ�� 
		virtual Entity*                 createEntity(U32 modelDeclID,CChar* prefixName=NULL); 
		/// ������λʵ��,����Ч��ʹ��
		virtual Entity*                 createSlotEntity(CChar* name, U32 modelDeclID); 
		/// ������λʵ��,����Ч��ʹ��
		virtual Entity*                 createSlotEntity(U32 modelDeclID,CChar* prefixName=NULL); 
		/// ����ʵ��
        virtual void                    destroyEntity(CChar* name);
		/// ���ٲ�λʵ��
		virtual void                    destroySlotEntity(CChar* name); 
        /// �õ�ʵ�� 
        virtual Entity*                 getEntity(CChar* name); 
		/// ˳�����Entity
		virtual Entity*					getEntity(U32 index);
		/// �õ���λʵ�� 
		virtual Entity*                 getEntityfromSlot(CChar* name); 
		/// ���ݲ�λ��ȡEntity
		virtual Entity*					getEntityfromSlot(U32 slot);
		/// �õ�ָ����ʵ������
		virtual UInt					getEntityCount();
        /// �õ�ָ����ʵ������
        virtual UInt                    getEntityCount(CChar* group);
        /// �õ�ָ����ʵ��
        virtual void                    getEntityList(CChar* group, IEntity** buff, UInt count);
        /// ж��ʵ�� 
        virtual void                    destroyAllEntity();
        /// ����ʵ�� 
        virtual void                    updateAllEntity( Flt delta, RENDER_STATE state = RS_IDLE );

        /// ����ʵ�帽����
        virtual void                    createEntityStaticAccessorys( IEntity* entity, U32 componentID );
		/// ��̬����ʵ�帽����
		virtual bool					createEntityDynamicAccessorys( IEntity* entity, CChar* suffix, U32 resourceID, SceneObjectTypes resourceType, IEntityAccessory* accessoryInfo, Bool isCreateEntity = false );
		/// ����PUEffect����ָ������ʵ��,��������effectResID
		bool							createEntityDynamicAccessorys( IEntity* entity, PUEffect* puEffect, IEntityAccessory* accessoryInfo);
		/// ��̬����ʵ�帽����
		virtual void					destroyEntityDynamicAccessorys( IEntity* entity, CChar* name );

        ///////////////////////////////////////////////////////////////////////////////////////

    public:

		/// ����ʵ�� ��
		virtual EntityGroup*			createEntityGroup(CChar* name, U32 modelDeclID,UInt num); 
		/// ����ʵ����
		virtual EntityGroup*			createEntityGroup(U32 modelDeclID,UInt num,CChar* prefixName = NULL); 
		/// �õ�ʵ���� 
		virtual EntityGroup*			getEntityGroup(CChar* name); 
		/// ����ʵ����
		virtual void                    destroyEntityGroup(CChar* name); 
		/// ж��ʵ����
		virtual void                    destroyAllEntityGroup();
		/// ����ʵ���� 
		virtual void                    updateAllEntityGroup( Flt delta, RENDER_STATE state = RS_IDLE );

        /// ����ʵ���鸽����
        virtual void                    createEntityGroupAccessorys( IEntityGroup* entity, U32 componentID  );

        ///////////////////////////////////////////////////////////////////////////////////////

    public:

        /// ������̬ʵ�� 
        virtual void                    addStaticEntity(U32 modelDeclID,
                                            Vec3& pos, Qua& orientation, Vec3& scale, Bool isRandom, 
                                            Str staticGroup, Bool isReset); 
        /// ������̬ʵ�� 
        virtual void                    addStaticEntityAccessorys( U32 componentID, Vec3& pos, Qua& orientation, Vec3& scale ); 

        /// �õ���̬ʵ����
        virtual StaticEntitySet*        getStaticEntitySet( U32 modelDeclID );
      
        /// ������̬ʵ�� 
        virtual void                    buildStaticEntity(); 

    protected:

        /// ������̬ʵ�� ��
        virtual StaticEntitySet*        createStaticEntitySet(U32 modelDeclID); 

        /// ж�ؾ�̬ʵ�� 
        virtual void                    destroyAllStaticEntity();

        /// ����̬ʵ�� 
        virtual void                    updateStaticEntity( Flt delta );

        ///////////////////////////////////////////////////////////////////////////////////////

    public:
		///////////////////////////////////////////////////////////////////////////////////////
		// �µ���Ч CN_MODIFY
		virtual EffectComponent*		createEffectComponent(CChar* name, U32 effectResID, Bool isAutoDestroy = true, Bool isAutoStart = true);

		virtual EffectComponent*		createEffectComponent(U32 effectResID, Bool isAutoDestroy = true, Bool isAutoStart = true);

		virtual EffectComponent*		createEffectComponent(CChar* name, CChar* fullfilename, Bool isAutoDestroy = true, Bool isAutoStart = true);

		virtual EffectComponent*		createEffectComponent(CChar* fullfilename, Bool isAutoDestroy = true, Bool isAutoStart = true);

		virtual EffectComponent*		createEmptyEffectComponent();

		virtual EffectComponent*		createEmptyEffectComponent(CChar* name);
		/// �����µ���Ч
		virtual void                    destroyEffectComponent(CChar* name) ; 
		/// �õ��µ���Ч
		virtual EffectComponent*        getEffectComponent(CChar* name) ; 
		/// �õ��µ���Ч
		virtual EffectComponent*        getEffectComponent(U32 index) ; 
		/// ж���µ���Ч
		virtual void                    destroyAllEffectComponent() ;
		/// �����µ���Ч 
		virtual void                    updateAllEffectComponent( Flt delta );
		///////////////////////////////////////////////////////////////////////////////////////

		/// ����EffectComponent���PU
		virtual PUEffect*				createPUEffect(CChar* name, CChar* effectTemplate, Bool isAutoDestroy = true, Bool isAutoStart = true);
		/// ����EffectComponent���PU
		virtual PUEffect*				createPUEffect(CChar* effectTemplate, Bool isAutoDestroy = true, Bool isAutoStart = true);
		/// ����EffectComponent���PU
		virtual PUEffect*				createPUEffect(U32 effectResID, Bool isAutoDestroy = true, Bool isAutoStart = true);
		/// ����EffectComponent���PU
		virtual PUEffect*				createPUEffect(CChar* name, U32 effectResID, Bool isAutoDestroy = true, Bool isAutoStart = true);
		/// ����EffectComponent���PU
		virtual void					destroyPUEffect(CChar* name) ; 
		/// �õ�EffectComponent���PU
		virtual PUEffect*			    getPUEffect(CChar* name) ; 
		/// ж��EffectComponent���PU
		virtual void		            destroyAllPUEffect() ;
		/// ����EffectComponent���PU 
		virtual void		            updateAllPUEffect( Flt delta );

		/// ������Ч
        virtual EffectEntity*           createEffectEntity(CChar* name, U32 effectResID, Bool isAutoDestroy = true, Bool isAutoStart = true) ; 
        /// ������Ч
        virtual EffectEntity*           createEffectEntity(U32 effectResID, Bool isAutoDestroy = true, Bool isAutoStart = true) ; 
        /// ������Ч
        virtual void                    destroyEffectEntity(CChar* name) ; 
        /// �õ���Ч
        virtual EffectEntity*           getEffectEntity(CChar* name) ; 
        /// ж����Ч
        virtual void                    destroyAllEffectEntity() ;
        /// ������Ч 
        virtual void                    updateAllEffectEntity( Flt delta );

        ///////////////////////////////////////////////////////////////////////////////////////

        ///// ����������������
        //virtual ITerrainDecalSet*       createTerrainDecalSet(CChar* name, UInt num, CChar* texFileName);
        ///// ����������������
        //virtual ITerrainDecalSet*       createTerrainDecalSet(UInt num, CChar* texFileName);
        ///// ���ٵ�������
        //virtual void                    destroyTerrainDecalSet(CChar* name); 
        ///// �õ���������
        //virtual TerrainDecalSet*        getTerrainDecalSet(CChar* name); 
        ///// ж�ص�������
        //virtual void                    destroyAllTerrainDecalSet();
        ///// ���µ�������
        //virtual void                    updateAllTerrainDecalSet( Flt delta, RENDER_STATE state = RS_IDLE );

		///////////////////////////////////////////////////////////////////////////////////////

		/// �����߾�����������
		virtual IDecalSet*				createDecalSet(CChar* name, UInt num, CChar* texFileName, IDecalType type);
		/// �����߾�����������
		virtual IDecalSet*				createDecalSet(UInt num, CChar* texFileName, IDecalType type);
		/// ���ٸ߾�������
		virtual void                    destroyDecalSet(CChar* name); 
		/// �õ��߾�������
		virtual IDecalSet*				getDecalSet(CChar* name); 
		/// ж�ظ߾�������
		virtual void                    destroyAllDecalSet();
		/// ���¸߾�������
		void							updateAllDecalSet( Flt delta, RENDER_STATE state = RS_IDLE );
        ///////////////////////////////////////////////////////////////////////////////////////

        /// ����Gui.
        virtual Gui*                    createGui(CChar* resourceFileName, CChar* coreFileName, Str8 fontName, IPointer*& pIPointer, IFont*& pIFont); 
        /// ж��Gui
        virtual void                    destroyGui();

				Gui*					getGui() { return mGui; }
    
        ///////////////////////////////////////////////////////////////////////////////////////

        /// �õ�С��ͼ������
        virtual MiniMapManager*         getMiniMapManager();
        /// �õ���Ӱ������
        virtual ShadowManager*          getShadowManager(); 
        /// �õ��߿������
        virtual WireframeManager*       getWireframeManager(); 
        /// �õ����ζ���
        virtual TerrainManager*         getTerrainManager();
        /// �õ����ζ���
        Ogre::SceneManager*             getOgreSceneManager(){return mOgreSceneManager;};
        /// �õ���ײϵͳ����
        virtual CollisionSystem*        getCollisionSystem();
        /// �õ���Ϊ�������
        virtual IActionManager*         getActionManager();
        /// �õ��ϰ��������
        virtual BlockManager*           getBlockManager();

		virtual DynamicBlockObjectSceneManager*getDynamicBlockObjectSceneManager();
        /// �õ�Ѱ·������
        virtual PathFindingManager*     getPathFindingManager();
        /// �õ��ϳ���������
        virtual CompositorManager*      getCompositorManager();
		/// �õ��ϳ���������
		virtual TreeManager*			getTreeManager();
        /// �õ�������
        virtual SceneDebuger*			getSceneDebuger();

        ///////////////////////////////////////////////////////////////////////////////////////

        /// ���û�����
        virtual void                    setAmbientLight(const Color& colour);
        /// �õ�������
        virtual Color                   getAmbientLight();
		/// ��������
		virtual void					createEffectGrid();
        ///////////////////////////////////////////////////////////////////////////////////////

    protected:

        /// ����Ogre��������
        void                            createOgreScene(CChar* sceneName, CChar* camName);
        /// ж��Ogre��������.
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
        /// ���豸��ʧ
        void                            onDeviceLost();
        /// ���豸����
        void                            onDeviceReset();

        ///////////////////////////////////////////////////////////////////////////////////////


        ///////////////////////////////////////////////////////////////////////////////////////


        /// ����debug��Ϣ
        void                            updateDebugInfo();

	protected:

		/// ��λ����
		Flt	    mUnitScale;

        ResourceLoadListener* mResourceLoadListener;

		ResourceSaveListener* mResourceSaveListener;

        ///////////////////////////////////////////////////////////////////////////////////////

        /// Ogre�ĳ����������
		Ogre::SceneManager* mOgreSceneManager;
        /// Ogre����Ⱦ�ӽǶ���
		Ogre::Viewport*  mOgreViewport;
        /// Gui����
		Gui* mGui;
        /// ��ײϵͳ����
        CollisionSystem* mCollisionSystem;
        /// ���߶���
        WireframeManager* mWireframeManager;
        /// ��Ϊ�������
        ActionManager* mActionManager;
        /// �ϰ��������
        BlockManager* mBlockManager;

		DynamicBlockObjectSceneManager* mDynamicBlockObjectSceneManager;
        /// Ѱ·������
        PathFindingManager* mPathFindingManager;
        /// �ϳ���������
        CompositorManager* mCompositorManager;
        // ������
        SceneDebuger* mSceneDebuger;
        
        ///////////////////////////////////////////////////////////////////////////////////////

        /// ������б�
        std::map<String, Camera*> mCameras;
		/// ������
		Camera* mActiveCamera;

		/// ��ӰͶ�������
		Ogre::String mActiveShadowCasterCameraName;

        ///////////////////////////////////////////////////////////////////////////////////////

        /// �ƹ��б�
        std::map<String, Light*> mLights;

        ///////////////////////////////////////////////////////////////////////////////////////

        /// ʵ���б�
        std::map<String, Entity*> mEntitys;
		/// ��λʵ���б�
		std::map<String, Entity*> mSlotEntitys;
        /// ʵ������
        NameGenerator mEntityNameGenerator;

        ///////////////////////////////////////////////////////////////////////////////////////

		/// ʵ�����б�
		std::map<String, EntityGroup*> mEntityGroup;
		/// ʵ������
		NameGenerator mEntityGroupNameGenerator;

        ///////////////////////////////////////////////////////////////////////////////////////

        /// ��̬ʵ�弯�б�
        std::map<U32, StaticEntitySet*> mStaticEntitySets;

        ///////////////////////////////////////////////////////////////////////////////////////

        /// EffectEntity�б�
        std::map<String, EffectEntity*> mEffectEntitys;
        /// EffectEntity����
        NameGenerator mEffectEntityNameGenerator;

		///////////////////////////////////////////////////////////////////////////////////////

		/// �µ�Effect�б� CN_MODIFY
		std::map<String, EffectComponent*> mEffectComponents;
		/// EffectComponent����
		NameGenerator mEffectComponentNameGenerator;
		/// �յ�EffectComponent����
		NameGenerator mEmptyEffectComponentNameGenerator;

		/// �µ�EffectComponent���PU�б�
		std::map<String, PUEffect*> mPUEffects;
		/// PUEffect����
		NameGenerator mPUEffectNameGenerator;

        ///////////////////////////////////////////////////////////////////////////////////////

        ///// TerrainDecalSet�б�
        //std::map<String, TerrainDecalSet*> mTerrainDecalSets;
        ///// TerrainDecalSet����
        //NameGenerator mTerrainDecalSetNameGenerator;

		/// DecalSet�б�
		std::map<String, IDecalSet*> mDecalSets;
		/// DecalSet����
		NameGenerator mDecalSetNameGenerator;

        ///////////////////////////////////////////////////////////////////////////////////////

        /// С��ͼ
        MiniMapManager* mMiniMapManager;

        /// ��Ӱ����
        ShadowManager* mShadowManager;

        /// �������������
        TerrainManager* mTerrainManager;

        /// �������л�����
        SceneXmlSerializer* mSceneXmlSerializer;

		/// �������������
		SceneObjectController* mSceneObjectController;

		///
		//TreeManager* mTreeManager;
        ///////////////////////////////////////////////////////////////////////////////////////

        // LOD �б�
        std::vector<LodInfo> mLodInfos;

        ///////////////////////////////////////////////////////////////////////////////////////

        Flt mCurrFarClipDistance;


	};
	
}

/******************************************************************************/

#endif
