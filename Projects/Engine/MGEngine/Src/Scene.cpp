/******************************************************************************/
/******************************************************************************/
#include "stdafx.h"
#include "EffectComponent.h"
#include "Scene.h"
#include "EngineMain.h"
#include "Gui.h"
#include "Camera.h"
#include "Light.h"
#include "Entity.h"
#include "EffectEntity.h"
#include "SceneXmlSerializer.h"
#include "TerrainChunk.h"
#include "TerrainManager.h"
#include "InputManager.h"
#include "CollisionSystem.h"
#include "IEntityAccessory.h"
#include "Display.h"
#include "TerrainTilesOptions.h"
#include "TerrainTilesMaterialA.h"
#include "ShadowManager.h"
#include "PUEffect.h"
#include "IFont.h"
#include "IPointer.h"
#include "HighLevelDecal.h"
/******************************************************************************/

namespace MG
{

    #define ENTITY_POOL_CATEGORY 3201
    #define EFFECTENTITY_POOL_CATEGORY 3202
    
    //-----------------------------------------------------------------------
    Scene::Scene(CChar* sceneName, CChar* camName)
        :mOgreSceneManager(NULL)
        ,mOgreViewport(NULL)
        ,mGui(NULL)
        ,mWireframeManager(NULL)
        ,mTerrainManager(NULL)
        ,mShadowManager(NULL)
        ,mMiniMapManager(NULL)
        ,mSceneXmlSerializer(NULL)
        ,mEntityNameGenerator("Entity")
		,mEntityGroupNameGenerator("EntityGroup")
        ,mEffectEntityNameGenerator("EffectEntity")
		,mEffectComponentNameGenerator("EffectComponent")
		,mEmptyEffectComponentNameGenerator("EmptyComponent")
		,mPUEffectNameGenerator("PUEffect")
        //,mTerrainDecalSetNameGenerator("TerrainDecalSet")
		,mDecalSetNameGenerator("DecalSet")
		,mSceneObjectController(NULL)
		,mActiveCamera(NULL)
		,mUnitScale(1.0)
        ,mResourceLoadListener(NULL)
		,mResourceSaveListener(NULL)
        ,mSceneDebuger(NULL)
    {
        mMiniMapManager     = MG_NEW MiniMapManager( this );
        mShadowManager      = MG_NEW ShadowManager( this );
        mBlockManager       = MG_NEW BlockManager( this );
		mDynamicBlockObjectSceneManager = MG_NEW DynamicBlockObjectSceneManager(this);
        mPathFindingManager = MG_NEW PathFindingManager( this );
        mActionManager      = MG_NEW ActionManager( this );
		mCollisionSystem    = MG_NEW CollisionSystem( this );

		createOgreScene(sceneName,camName);

        mTerrainManager     = MG_NEW TerrainManager( this ) ;
        mSceneXmlSerializer = MG_NEW SceneXmlSerializer( this ) ;
        mCompositorManager  = MG_NEW CompositorManager( this ) ;
        mSceneDebuger       = MG_NEW SceneDebuger( this ) ;
		TreeManager::getInstance().setScene(this);

        // 增加LOD 信息
        addLod(0,20);
        addLod(1,40);
        addLod(2,60);
    }
    //-----------------------------------------------------------------------
    Scene::~Scene()
    {
        clear();

        MG_SAFE_DELETE( mSceneXmlSerializer );
        MG_SAFE_DELETE( mTerrainManager );
        MG_SAFE_DELETE( mCollisionSystem );
        MG_SAFE_DELETE( mWireframeManager );
        MG_SAFE_DELETE( mActionManager );
        MG_SAFE_DELETE( mPathFindingManager );
        MG_SAFE_DELETE( mBlockManager );
        MG_SAFE_DELETE( mShadowManager );
        MG_SAFE_DELETE( mMiniMapManager );
        MG_SAFE_DELETE( mCompositorManager );
        MG_SAFE_DELETE( mSceneDebuger );

        destroyGui();
        destroyAllCamera();
        destroyOgreScene();
    }
    //-----------------------------------------------------------------------
    void Scene::clear()
    {
		MG_SAFE_DELETE(mSceneObjectController);

		/////////////////////////////////////////////////////

		mActiveShadowCasterCameraName = "";

        /////////////////////////////////////////////////////

        destroyAllEntity();
        destroyAllEntityGroup();
        destroyAllLight();
        destroyAllStaticEntity();
        destroyAllEffectEntity();
        //destroyAllTerrainDecalSet();
		destroyAllDecalSet();

        /////////////////////////////////////////////////////

        getTerrainManager()->unLoad();

        /////////////////////////////////////////////////////

        if ( mWireframeManager )
            mWireframeManager->clear();


        if ( mSceneDebuger )
        {
            mSceneDebuger->clear();
        }

        /////////////////////////////////////////////////////

        if ( mOgreSceneManager )
        {
            mOgreSceneManager->destroyAllAnimations();
            mOgreSceneManager->destroyAllEntities();
			mOgreSceneManager->destroyAllInstancedGeometry();
            mOgreSceneManager->destroyAllLights();
            mOgreSceneManager->destroyAllManualObjects();
            mOgreSceneManager->destroyAllMovableObjects();
        }

        /////////////////////////////////////////////////////

        if ( mBlockManager )
            mBlockManager->unLoad();

        if ( mCollisionSystem )
            mCollisionSystem->clear();
        
        if ( mPathFindingManager )
            mPathFindingManager->unLoad();

        /////////////////////////////////////////////////////

		{
			if ( EngineMain::getInstance().getMode() == EM_EDITOR )
			{
				TreeManager::getInstance().clear();
			}
			else
			{
				TreeManager::getInstance().ClearBuildAllTreeAndGrass();
			}
		}

        /////////////////////////////////////////////////////

		if ( mResourceLoadListener )
			mResourceLoadListener->onClearResourceLoadListener();

        /////////////////////////////////////////////////////

    }

    //-----------------------------------------------------------------------
    void Scene::preRendering()
    {
        if ( mGui )
        {
            mGui->preUpdate();
        }

        updateAllEntity( 0, RS_PRE );
        updateAllEntityGroup( 0, RS_PRE );
        //updateAllTerrainDecalSet( 0, RS_PRE );
		updateAllDecalSet( 0, RS_PRE);

		TreeManager::getInstance().update(!EngineMain::getInstance().isTreeManagerLocked());

		mActiveShadowCasterCameraName = "";
    }

    //-----------------------------------------------------------------------
    void Scene::postRendering()
    {
       // updateAllEntity( 0, RS_POST );
       // updateAllEntityGroup( 0, RS_POST );
    }

    //-----------------------------------------------------------------------
    Bool Scene::update( Flt delta )
    {
        /////////////////////////////////////////////////////

        if ( mShadowManager )
            mShadowManager->update( delta );

        /////////////////////////////////////////////////////

        if ( mTerrainManager )
            mTerrainManager->update( delta );

        /////////////////////////////////////////////////////

        if ( mWireframeManager )
            mWireframeManager->update( delta );

        /////////////////////////////////////////////////////

        if ( mBlockManager )
            mBlockManager->update( delta );

        if ( mPathFindingManager )
            mPathFindingManager->update( delta );

        if ( mCollisionSystem )
            mCollisionSystem->update( delta );

        /////////////////////////////////////////////////////

		if ( mCompositorManager )
			mCompositorManager->update( delta );
        
        /////////////////////////////////////////////////////

        if ( mSceneObjectController )
            mSceneObjectController->update( delta );

        if ( mSceneDebuger )
            mSceneDebuger->update( delta );

        /////////////////////////////////////////////////////

        updateAllCamera( delta );
        updateAllEntity( delta );
		updateAllEntityGroup( delta );
        updateAllEffectEntity( delta );
		// CN_MODIFY
		updateAllEffectComponent( delta );
        //updateAllTerrainDecalSet( delta );
		updateAllDecalSet( delta );
        updateStaticEntity( delta );

        /////////////////////////////////////////////////////

        //if (mTreeManager)
        //    mTreeManager->update();

        /////////////////////////////////////////////////////

		//MyGui的更新函数
        mGui->update(delta);

        /////////////////////////////////////////////////////

		TreeManager::getInstance().update(!EngineMain::getInstance().isTreeManagerLocked());

        updateDebugInfo();

        /////////////////////////////////////////////////////

        return true;
    }

    //-----------------------------------------------------------------------
    void Scene::addLod(UInt index, Flt distance)
    {
        if ( mLodInfos.size() == index )
        {
            LodInfo info;
            info.index = index;
            info.distance = distance;
            mLodInfos.push_back(info);
        }
    }
    //-----------------------------------------------------------------------
    void Scene::clearLod()
    {
        mLodInfos.clear();
    }
    //-----------------------------------------------------------------------
    UInt Scene::getLodCount()
    {
        return mLodInfos.size();
    }
    //-----------------------------------------------------------------------
    LodInfo Scene::getLod(UInt index)
    {
        return mLodInfos[index];
    }
    //-----------------------------------------------------------------------
    void Scene::applyResolutionConfig(UInt nScreenX, UInt nScreenY)
    {
        if ( mGui )
			mGui->resizeWindow();
    }
    //-----------------------------------------------------------------------
    void Scene::applyRenderConfig()
    {
		// shadow
		mShadowManager->applyRenderConfig();

        // entity
        {
            std::map<String, Entity*>::iterator iter = mEntitys.begin();
            std::map<String, Entity*>::iterator end_iter = mEntitys.end();
            for( ; iter != end_iter; iter++ )
            {
                iter->second->getModelObject()->applyRenderConfig();
            }
        }

        //entity group
        {
            std::map<String, EntityGroup*>::iterator iter = mEntityGroup.begin();
            std::map<String, EntityGroup*>::iterator end_iter = mEntityGroup.end();
            for( ; iter != end_iter; iter++ )
            {
                iter->second->applyRenderConfig();
            }
        }

        //static entity set
        {
            std::map<U32, StaticEntitySet*>::iterator iter  = mStaticEntitySets.begin();
            std::map<U32, StaticEntitySet*>::iterator end_iter = mStaticEntitySets.end();
            for( ; iter != end_iter; iter++ )
            {
                iter->second->applyRenderConfig();
            }
        }

		//sceneManager
		if ( mOgreSceneManager )
		{
			IDisplay* display = EngineMain::getInstance().display();
			Viewport* port = mOgreSceneManager->getCurrentViewport();

			if ( display && port )
			{
				if ( !display->getEntityVisible() )
				{
					uint mask = SOV_ENTITY;
					port->setVisibilityMask( port->getVisibilityMask() & ~mask );

				}
				else
				{
					uint mask = SOV_ENTITY;
					port->setVisibilityMask( port->getVisibilityMask() | mask );
				}

				if ( !display->getTerrainWaterVisible() )
				{
					port->setVisibilityMask( port->getVisibilityMask() & ~SOV_WATER );
				}
				else
				{
					port->setVisibilityMask( port->getVisibilityMask() | SOV_WATER );
				}
			}
		}
        
        //terrain
        mTerrainManager->applyRenderConfig();

		//tree
		//mTreeManager->applyRenderConfig();
		TreeManager::getInstance().applyRenderConfig();

		//static Geometery
		buildStaticEntity();
    }
    //-----------------------------------------------------------------------
    SceneXmlSerializer* Scene::getXmlSerializer()
    {
        return mSceneXmlSerializer;
    }
	//-----------------------------------------------------------------------
	//EffectXmlSerializer* Scene::getEffectSerializer()
	//{
	//	return mEffectXmlSerializer;
	//}
	//-----------------------------------------------------------------------
	SceneObjectController* Scene::getSceneObjectController(Bool isCreateController)
	{
		if ( isCreateController && mSceneObjectController == NULL )
		{
			mSceneObjectController = MG_NEW SceneObjectController(this);
		}
		return mSceneObjectController;
	}

    //-----------------------------------------------------------------------
    void Scene::setResourceLoadListener(ResourceLoadListener* listener)
    {
        mResourceLoadListener = listener;

		if ( mResourceLoadListener )
			mResourceLoadListener->onInitResourceLoadListener();
    }

    //-----------------------------------------------------------------------
    ResourceLoadListener* Scene::getResourceLoadListener()
    {
        return mResourceLoadListener;
    }

	//-----------------------------------------------------------------------
	void Scene::setResourceSaveListener(ResourceSaveListener* listener)
	{
		mResourceSaveListener = listener;
	}

	//-----------------------------------------------------------------------
	ResourceSaveListener* Scene::getResourceSaveListener()
	{
		return mResourceSaveListener;
	}

    //-----------------------------------------------------------------------
    void Scene::destroySceneObject(CChar* name, SceneObjectTypes type)
    {
        switch (type)
        {
        case SOT_ENTITY:
            destroyEntity( name );
            break;
		case SOT_EFFECTENTITY:
			destroyEffectEntity( name );
			break;
        case SOT_TREE:
            getTreeManager()->destroyTree( name );
			break;
		case SOT_GRASS:
			getTreeManager()->destroyGrass( name );
            break;
		case EOT_PU:
			destroyPUEffect( name );
			break;
        }
    }
    //-----------------------------------------------------------------------
    void Scene::updateDebugInfo()
    {   
#ifdef _DEBUG


#endif

    }
    //-----------------------------------------------------------------------
    void Scene::createOgreScene(CChar* sceneName, CChar* camName)
    {
        destroyOgreScene();

        Ogre::Root * root = OgreMainInterface::root;
        Ogre::RenderWindow * window = OgreMainInterface::renderWindow;

        ////////////////////////////////////////////////////////////////

        RenderSystem* renderSystem = root->getRenderSystem();
        if ( renderSystem )
        {
            renderSystem->addListener( this );
        }

        ////////////////////////////////////////////////////////////////

        //创建场景对象
        mOgreSceneManager = root->createSceneManager(Ogre::ST_GENERIC, sceneName);
        mOgreSceneManager->setAmbientLight(ColourValue(0.2, 0.2, 0.2));

        //使用摄像机相对位置渲染
        //世界坐标原点变换到摄像机的原点
        //需要远景时使用
        //mOgreSceneManager->setCameraRelativeRendering(true);

        //创建摄像机对象
        Camera* cam = createCamera(camName);
		mActiveCamera = cam;

        //增加窗口视角
        mOgreViewport = window->addViewport(cam->mOgreCamera);
        //mOgreViewport->setBackgroundColour(Ogre::ColourValue(1,1,1,1));
        mOgreViewport->setBackgroundColour(Ogre::ColourValue(0,0,0,1));

        //mOgreViewport->setVisibilityMask( SOV_ENTITY | SOV_EFFECTENTITY | SOV_GROUND | SOV_WATER );

        //设置方向比例
		cam->mOgreCamera->setAutoAspectRatio(false);
		cam->mOgreCamera->setAspectRatio( Ogre::Real(mOgreViewport->getActualWidth()) / 
			Ogre::Real(mOgreViewport->getActualHeight()));

        ///增加监听
        mOgreSceneManager->addListener(this);
        mOgreSceneManager->addRenderQueueListener(this);

        // 创建碰撞检测系统
        mCollisionSystem->initialize( mOgreSceneManager );
    }
	//-----------------------------------------------------------------------
	void Scene::createEffectGrid()
	{
		getWireframeManager()->createEffectGridsDecorator("EffectGrid");
	}
    //-----------------------------------------------------------------------
    void Scene::destroyOgreScene()
    {
        Ogre::Root * root = OgreMainInterface::root;
        Ogre::RenderWindow * window = OgreMainInterface::renderWindow;

        if (mOgreSceneManager)
		{
            ////////////////////////////////////////////////////////////////

            RenderSystem* renderSystem = root->getRenderSystem();
            if ( renderSystem )
            {
                renderSystem->removeListener( this );
            }
            
            ////////////////////////////////////////////////////////////////

            if (mShadowManager)
                mShadowManager->unInitialize();
           
            // 移除碰撞检测系统
            if ( mCollisionSystem )
                mCollisionSystem->unInitialize();

            ///移除监听
            mOgreSceneManager->removeListener(this);
            mOgreSceneManager->removeRenderQueueListener(this);

            //销毁场景所有摄像机
            destroyAllCamera();
        
            //销毁场景对象
			root->destroySceneManager(mOgreSceneManager);
            mOgreSceneManager = NULL;

            //移除所有视角对象
            window->removeAllViewports();
		}
    }
    
    //-----------------------------------------------------------------------
    void Scene::preFindVisibleObjects(Ogre::SceneManager* source, 
        Ogre::SceneManager::IlluminationRenderStage irs, Ogre::Viewport* v)

    {
        if ( getActiveCamera()->getOgreCamera()->getViewport() == v )
        {
            Display::getSingleton().setFogEnable( true );
        }else
        {
            Display::getSingleton().setFogEnable( false );
        }
    }
    //-----------------------------------------------------------------------
    void Scene::postFindVisibleObjects(SceneManager* source, 
        Ogre::SceneManager::IlluminationRenderStage irs, Viewport* v)
    {
        if ( mSceneObjectController )
        {
            mSceneObjectController->postFindVisibleObjects( source, irs, v );
        }
        if ( mWireframeManager )
        {
            mWireframeManager->postFindVisibleObjects( source, irs, v );
        }
        if ( mSceneDebuger )
        {
            mSceneDebuger->postFindVisibleObjects( source, irs, v );
        }

		std::map<String, Entity*>::iterator iter = mEntitys.begin();
		std::map<String, Entity*>::iterator end_iter = mEntitys.end();
		for( ; iter != end_iter; iter++ )
		{
			Entity* entity = iter->second;
			if ( entity && entity->getEntityAccessoryCollection() )
			{
				entity->getEntityAccessoryCollection()->postFindVisibleObjects();
			}
		}
    }

    //-----------------------------------------------------------------------
    void Scene::shadowTextureCasterPreViewProj(Ogre::Light* light, Ogre::Camera* camera, size_t iteration)
    {
        if ( mShadowManager )
            mShadowManager->shadowTextureCasterPreViewProj(light, camera, iteration);

		//this->getOgreSceneManager()->getCamera();

		mActiveShadowCasterCameraName = camera->getName();
    }

    //-----------------------------------------------------------------------
    void Scene::shadowTexturesUpdated(size_t numberOfShadowTextures)
    {
        if ( mShadowManager )
            mShadowManager->shadowTexturesUpdated(numberOfShadowTextures);
    }

    //-----------------------------------------------------------------------
    void Scene::renderQueueStarted(uint8 queueGroupId, const String& invocation, bool& skipThisInvocation)
    {
        // MainScene
        if ( invocation.empty() )
        {
            if ( (queueGroupId == Ogre::RENDER_QUEUE_SKIES_EARLY) || (queueGroupId == Ogre::RENDER_QUEUE_SKIES_LATE) )
            {
                Ogre::Camera* cam      = getActiveCamera()->getOgreCamera();
                Ogre::Root * root = OgreMainInterface::root;
                RenderSystem* renderSystem = root->getRenderSystem();

                mCurrFarClipDistance   = cam->getFarClipDistance();

                cam->setFarClipDistance( 10000 );

                renderSystem->_setProjectionMatrix( cam->getProjectionMatrixRS() );

                const Matrix4& vmat = cam->getViewMatrix();

                renderSystem->_setViewMatrix(vmat);

                //Display::getSingleton().setFogEnable( false );

                Color fogColor = Display::getSingleton().getFogColor();
                getOgreSceneManager()->setFog(FOG_LINEAR, ColourValue(fogColor.r,fogColor.g,fogColor.b,1), 0.0006, 500, 2000);
            }
        }
    }

    //-----------------------------------------------------------------------
    void Scene::renderQueueEnded(uint8 queueGroupId, const String& invocation, bool& repeatThisInvocation)
    {
        // MainScene
        if ( invocation.empty() )
        {
            if ( (queueGroupId == Ogre::RENDER_QUEUE_SKIES_EARLY) || (queueGroupId == Ogre::RENDER_QUEUE_SKIES_LATE) )
            {
                Ogre::Camera* cam      = getActiveCamera()->getOgreCamera();
                Ogre::Root * root = OgreMainInterface::root;
                RenderSystem* renderSystem = root->getRenderSystem();

                cam->setFarClipDistance( mCurrFarClipDistance );

                renderSystem->_setProjectionMatrix( cam->getProjectionMatrixRS() );

                const Matrix4& vmat = cam->getViewMatrix();

                renderSystem->_setViewMatrix(vmat);

                Display::getSingleton().setFogEnable( true );
            }
        }

        if (queueGroupId == Ogre::RENDER_QUEUE_WORLD_GEOMETRY_1)
        {
            //::OutputDebugString("RENDER_QUEUE_MAIN\n");

            Ogre::Camera* pMainCamera	= getActiveCamera()->getOgreCamera();
            Ogre::Camera* pCurrCamera	= OgreMainInterface::root->getRenderSystem()->_getViewport()->getCamera();
			Ogre::Camera* pShadowCamera	= NULL;
			if (this->getOgreSceneManager()->hasCamera(mActiveShadowCasterCameraName))
			{
				pShadowCamera = this->getOgreSceneManager()->getCamera(mActiveShadowCasterCameraName);
			}
            if (pCurrCamera == NULL)
            {
                return;
            }

            Ogre::Viewport* mainVp = getActiveCamera()->getOgreCamera()->getViewport();
            Ogre::Viewport* currentVp = OgreMainInterface::root->getRenderSystem()->_getViewport();

            if (pCurrCamera == pShadowCamera)
            {
                if ( invocation == "SHADOWS"  )
                {
                    if ( pCurrCamera->isReflected() == false )
                    {
						TreeManager::getInstance().render(SpeedTree::RENDER_PASS_SHADOW, pCurrCamera);
                    }
                }
            }
            else
            if  (pCurrCamera == pMainCamera)
            {
                if ( pCurrCamera->isReflected() == false )
                {
                    TreeManager::getInstance().render(SpeedTree::RENDER_PASS_STANDARD, pCurrCamera);
                }else
                {
                    TreeManager::getInstance().render(SpeedTree::RENDER_PASS_REFLECT, pCurrCamera);
                }
            }
        }
    }

    //-----------------------------------------------------------------------
    void Scene::eventOccurred(const String& eventName,  const NameValuePairList* parameters)
    {
        if ( eventName == "DeviceLost" )
        {
            onDeviceLost();
        }else
        if ( eventName == "DeviceRestored" )
        {
            onDeviceReset();
        }
    }

    //-----------------------------------------------------------------------
    void Scene::onDeviceLost()
    {
        //tree
        //mTreeManager->onLostDevice();
		TreeManager::getInstance().onLostDevice();
    }

    //-----------------------------------------------------------------------
    void Scene::onDeviceReset()
    {
        //static entity set
        {
            std::map<U32, StaticEntitySet*>::iterator iter  = mStaticEntitySets.begin();
            std::map<U32, StaticEntitySet*>::iterator end_iter = mStaticEntitySets.end();
            for( ; iter != end_iter; iter++ )
            {
                iter->second->reset();
            }
        }

        //terrain
        if ( mTerrainManager )
        {
            mTerrainManager->reset();
        }
        
        //tree
        //mTreeManager->onResetDevice();
		TreeManager::getInstance().onLostDevice();

        InputManager::getSingleton().setWindowExtents(Display::getSingletonPtr()->getActWidth(), Display::getSingletonPtr()->getActHeight());
    }
   
    //-----------------------------------------------------------------------
    Camera* Scene::createCamera(CChar* name)
    {
        //没有做重名检测，外部维护
        Camera* newCamera = MG_NEW Camera(name, this); 
		newCamera->setName(name);
        mCameras[name] = newCamera;
        return newCamera;
    }
    //-----------------------------------------------------------------------
    void Scene::destroyAllCamera()
    {
        std::map<String, Camera*>::iterator iter = mCameras.begin();
        std::map<String, Camera*>::iterator end_iter = mCameras.end();
        for( ; iter != end_iter; iter++ )
        {
            MG_SAFE_DELETE( iter->second );
        }
        mCameras.clear();
    }
	//-----------------------------------------------------------------------
	Camera* Scene::getCamera(CChar* name)
	{
		std::map<String, Camera*>::iterator iter_find = mCameras.find( name );
		std::map<String, Camera*>::iterator end_iter = mCameras.end();
		if ( iter_find!=end_iter )
		{
			return iter_find->second;
		}
		return NULL;
	}

    //-----------------------------------------------------------------------
    Viewport* Scene::getMainViewport()
    {
        return mOgreViewport;
    }

    //-----------------------------------------------------------------------
    void Scene::updateAllCamera( Flt delta )
    {
        std::map<String, Camera*>::iterator iter = mCameras.begin();
        std::map<String, Camera*>::iterator end_iter = mCameras.end();
        for( ; iter != end_iter; iter++ )
        {
            iter->second->update( delta );
        }
    }
    //-----------------------------------------------------------------------
    void Scene::setActiveCamera(CChar* name)
    {
        //TODO:
    }
	//-----------------------------------------------------------------------
	Camera*	Scene::getActiveCamera()
	{
		return mActiveCamera;
	}
    //-----------------------------------------------------------------------
    ILight* Scene::createLight(CChar* name)
    {
        //没有做重名检测，外部维护
        Light* newLight = MG_NEW Light(name, this); 
		newLight->setName(name);
        mLights[name] = newLight;
        return newLight;
    }
    //-----------------------------------------------------------------------
    ILight* Scene::getLight(CChar* name)
    {
        std::map<String, Light*>::iterator iter = mLights.find(name);
        if ( iter != mLights.end() )
        {
            return iter->second;
        }
        return NULL;
    }

	//-----------------------------------------------------------------------
	void Scene::destroyLight( CChar* name )
	{
		std::map<String, Light*>::iterator iter = mLights.find(name);
		if ( iter != mLights.end() )
		{
			MG_SAFE_DELETE( iter->second );
			mLights.erase( iter );
		}
	}

    //-----------------------------------------------------------------------
    ILight* Scene::createDefaultLight()
    {
        return createLight("EnvironmentLight");
    }
    //-----------------------------------------------------------------------
    ILight* Scene::getDefaultLight()
    {
        ILight* light = getLight("EnvironmentLight");
        if ( light == NULL )
        {
            light = createDefaultLight();
            light->setLightType(ILight::LT_DIRECTIONAL);
            light->setDirection(Vec3(0.55f, -0.3f, 0.75f));
        }
        return light;
    }
    //-----------------------------------------------------------------------
    void Scene::destroyAllLight()
    {
        std::map<String, Light*>::iterator iter = mLights.begin();
        std::map<String, Light*>::iterator end_iter = mLights.end();
        for( ; iter != end_iter; iter++ )
        {
            MG_SAFE_DELETE( iter->second );
        }
        mLights.clear();
    }
    //-----------------------------------------------------------------------
    Entity* Scene::createEntity(CChar* name, U32 modelDeclID)
    {
        Entity* newEntity = getEntity( name );
        DYNAMIC_ASSERT(newEntity==NULL);
        if ( newEntity )
            return NULL;

        ModelDeclaration* modelDecl = MG::ResourceManager::getSingletonPtr()->getModelDeclaration(modelDeclID);
        //newEntity = MG_NEW Entity(name, modelDecl, this); 
        newEntity = MG_POOL_NEW_T(Entity, ENTITY_POOL_CATEGORY)(name, modelDecl, this);

		newEntity->setName(name);
        mEntitys[name] = newEntity;

		//根据模型表初始化缩放
		Vec3 scale(modelDecl->zoonX,modelDecl->zoonY,modelDecl->zoonZ);
		newEntity->getSceneNode()->setInitScale(scale);

		//根据模型表初始化悬空
		newEntity->getSceneNode()->setPositionOffset(Vec3(0,modelDecl->offsetY,0));

        return newEntity;
    }
    //-----------------------------------------------------------------------
    Entity* Scene::createEntity(U32 modelDeclID,CChar* prefixName)
    {
        Int i = 0;
        while( i++<1000 )
        {    
			String name = mEntityNameGenerator.generate();
            if ( prefixName )
                name = Str(prefixName) + name;
            if ( getEntity(name.c_str()) == NULL )
            {
                return createEntity( name.c_str(), modelDeclID );
            }
        }
        return NULL;
    }
	//-----------------------------------------------------------------------
	Entity* Scene::createSlotEntity( CChar* name, U32 modelDeclID )
	{
		Entity* newEntity = getEntity( name );
		DYNAMIC_ASSERT(newEntity==NULL);
		if ( newEntity )
			return NULL;

		ModelDeclaration* modelDecl = MG::ResourceManager::getSingletonPtr()->getModelDeclaration(modelDeclID);
		newEntity = MG_POOL_NEW_T(Entity, ENTITY_POOL_CATEGORY)(name, modelDecl, this);

		newEntity->setName(name);
		mSlotEntitys[name] = newEntity;
		return newEntity;
	}
	//-----------------------------------------------------------------------
	Entity* Scene::createSlotEntity( U32 modelDeclID,CChar* prefixName/*=NULL*/ )
	{
		Int i = 0;
		while( i++<1000 )
		{    
			String name = mEntityNameGenerator.generate();
			if ( prefixName )
				name = Str(prefixName) + name;
			if ( getEntityfromSlot(name.c_str()) == NULL )
			{
				return createSlotEntity( name.c_str(), modelDeclID );
			}
		}
		return NULL;
	}
    //-----------------------------------------------------------------------
    void Scene::destroyEntity(CChar* name)
    {
        std::map<String, Entity*>::iterator iter = mEntitys.find(name);
        if ( iter != mEntitys.end() )
        {
            MG_POOL_DELETE_T(iter->second, Entity, ENTITY_POOL_CATEGORY);
            //MG_SAFE_DELETE( iter->second );
            mEntitys.erase(iter);
        }
	}
	//-----------------------------------------------------------------------
	void Scene::destroySlotEntity( CChar* name )
	{
		std::map<String, Entity*>::iterator iter = mSlotEntitys.find(name);
		if ( iter != mSlotEntitys.end() )
		{
			MG_POOL_DELETE_T(iter->second, Entity, ENTITY_POOL_CATEGORY);
			mSlotEntitys.erase(iter);
		}
	}
    //-----------------------------------------------------------------------
	Entity* Scene::getEntity(U32 index)
	{
		std::map<String, Entity*>::iterator iter = mEntitys.begin();
		std::advance(iter, index);

		if( iter != mEntitys.end() )
		{
			return iter->second;
		}

		return NULL;
	}
	//-----------------------------------------------------------------------
    Entity* Scene::getEntity(CChar* name)
    {
        std::map<String, Entity*>::iterator iter = mEntitys.find(name);
        if ( iter != mEntitys.end() )
        {
            return iter->second;
        }
        return NULL;
    }
	//-----------------------------------------------------------------------
	Entity* Scene::getEntityfromSlot(U32 slot)
	{
		std::map<String, Entity*>::iterator iter = mSlotEntitys.begin();
		std::advance(iter, slot);

		if( iter != mSlotEntitys.end() )
		{
			return iter->second;
		}

		return NULL;
	}
	//-----------------------------------------------------------------------
	Entity* Scene::getEntityfromSlot( CChar* name )
	{
		std::map<String, Entity*>::iterator iter = mSlotEntitys.find(name);
		if ( iter != mSlotEntitys.end() )
		{
			return iter->second;
		}
		return NULL;
	}
	//-----------------------------------------------------------------------
	UInt Scene::getEntityCount()
	{
		return mEntitys.size();
	}
    //-----------------------------------------------------------------------
    UInt Scene::getEntityCount(CChar* group)
    {
        UInt count = 0;
        std::map<String, Entity*>::iterator iter = mEntitys.begin();
        std::map<String, Entity*>::iterator end_iter = mEntitys.end();
        for( ; iter != end_iter; iter++ )
        {
            if ( iter->second->getGroup() == group )
            {
                count++;
            }
        }
        return count;
    }
    //-----------------------------------------------------------------------
    void Scene::getEntityList(CChar* group, IEntity** buff, UInt count)
    {
        UInt i = 0;
        std::map<String, Entity*>::iterator iter = mEntitys.begin();
        std::map<String, Entity*>::iterator end_iter = mEntitys.end();
        for( ; iter != end_iter; iter++ )
        {
            if ( iter->second->getGroup() == group )
            {
                IEntity*  entity = iter->second;
                buff[i] = entity;

                i++;

                if (i>=count)
                {
                    break;
                }
            }
        }
    }
    //-----------------------------------------------------------------------
    void Scene::destroyAllEntity()
    {
        std::map<String, Entity*>::iterator iter = mEntitys.begin();
        std::map<String, Entity*>::iterator end_iter = mEntitys.end();
        for( ; iter != end_iter; iter++ )
        {
            MG_POOL_DELETE_T(iter->second, Entity, ENTITY_POOL_CATEGORY);
            //MG_SAFE_DELETE( iter->second );
        }
        mEntitys.clear();

		//////////////////////////////////////////////////////////////////////////
		/// 销毁槽位实体
		std::map<String, Entity*>::iterator slotIter = mSlotEntitys.begin();
		std::map<String, Entity*>::iterator slotEnd_iter = mSlotEntitys.end();
		for( ; slotIter != slotEnd_iter; slotIter++ )
		{
			MG_POOL_DELETE_T(slotIter->second, Entity, ENTITY_POOL_CATEGORY);
		}
		mSlotEntitys.clear();
		mEntityNameGenerator.reset();
    }

    //-----------------------------------------------------------------------
    void Scene::updateAllEntity( Flt delta, RENDER_STATE state )
    {
        std::map<String, Entity*>::iterator iter = mEntitys.begin();
        std::map<String, Entity*>::iterator end_iter = mEntitys.end();
        for( ; iter != end_iter; iter++ )
        {
            if ( state == RS_PRE )
            {
                iter->second->preRendering();
            }else
            if ( state == RS_POST )
            {
                iter->second->postRendering();
            }else
            {
                iter->second->update( delta );
            }
        }
		
		//////////////////////////////////////////////////////////////////////////
		/// 更新槽位实体
		std::map<String, Entity*>::iterator slotIter = mSlotEntitys.begin();
		std::map<String, Entity*>::iterator slotEnd_iter = mSlotEntitys.end();
		for( ; slotIter != slotEnd_iter; slotIter++ )
		{
			if ( state == RS_PRE )
			{
				slotIter->second->preRendering();
			}else
			if ( state == RS_POST )
			{
				slotIter->second->postRendering();
			}else
			{
				slotIter->second->update( delta );
			}
		}
    }

	//-----------------------------------------------------------------------
	void Scene::destroyEntityDynamicAccessorys( IEntity* entity, CChar* name )
	{
		if ( !entity )
			return;

		IEntityAccessoryCollection* entity_accessory_collection = entity->getEntityAccessoryCollection();
		if ( entity_accessory_collection )
			entity_accessory_collection->detachObject( name );
	}

    //-----------------------------------------------------------------------
	bool Scene::createEntityDynamicAccessorys( IEntity* entity, CChar* suffix, U32 resourceID, SceneObjectTypes resourceType, IEntityAccessory* accessoryInfo, Bool isCreateEntity )
	{
		if ( !entity || !accessoryInfo )
			return false;

		IEntityAccessoryCollection* entity_accessory_collection = entity->getEntityAccessoryCollection();
		if ( !entity_accessory_collection )
			return false;

		//确定子实体名称
		Str final_name;
		{
			Str suffix_num, suffix_type;

			if ( resourceType == SOT_ENTITY )
			{
				suffix_type = "_entity_";
			}
			else if ( resourceType == SOT_EFFECTENTITY )
			{
				suffix_type = "_effect_";
			}

			U32 parentAttachCount = entity->getEntityAccessoryCollection()->getAttachObjectCount();
			MGStrOp::toString(parentAttachCount,suffix_num);

			final_name = entity->getName() + "_accessories_" + suffix_num + suffix_type + suffix;
		}
		
		if ( isCreateEntity )
		{
			// 通过组件ID 创建各种附属物
			if ( resourceType == SOT_ENTITY )
			{
				accessoryInfo->sceneObject = createEntity( final_name.c_str(), resourceID );
			}
			else if ( resourceType == SOT_EFFECTENTITY )
			{
				// CN_MODIFY
				accessoryInfo->sceneObject = createEffectComponent( final_name.c_str(), resourceID , !accessoryInfo->isDepositLifeTime );
			}
		}
		
		if ( !accessoryInfo->sceneObject || !accessoryInfo->sceneObject->getSceneNode() )
			return false;

		IEntityAccessory entity_accessory;
		entity_accessory.sceneObject        = accessoryInfo->sceneObject;
		entity_accessory.relativePosition   = accessoryInfo->relativePosition;
		entity_accessory.relativeQuaternion = accessoryInfo->relativeQuaternion;
		entity_accessory.bindBoneName       = accessoryInfo->bindBoneName;
		entity_accessory.isSyncAnimation    = accessoryInfo->isSyncAnimation;
		entity_accessory.isDepositLifeTime  = accessoryInfo->isDepositLifeTime;
		entity_accessory_collection->attachObject(final_name, entity_accessory);

		return true;
	}

	//-----------------------------------------------------------------------
	bool Scene::createEntityDynamicAccessorys( IEntity* entity, PUEffect* puEffect, IEntityAccessory* accessoryInfo )
	{
		if ( !entity || !accessoryInfo )
			return false;

		IEntityAccessoryCollection* entity_accessory_collection = entity->getEntityAccessoryCollection();
		if ( !entity_accessory_collection )
			return false;

		//确定子实体名称
		Str final_name;
		{
			Str suffix_num, suffix_type;

			suffix_type = "_pueffect";

			U32 parentAttachCount = entity->getEntityAccessoryCollection()->getAttachObjectCount();
			MGStrOp::toString(parentAttachCount,suffix_num);

			final_name = entity->getName() + "_accessories_" + suffix_num + suffix_type + puEffect->getName();
		}

		if ( !accessoryInfo->sceneObject || !accessoryInfo->sceneObject->getSceneNode() )
			return false;

		IEntityAccessory *entity_accessory = MG_NEW IEntityAccessory;
		entity_accessory->sceneObject = accessoryInfo->sceneObject;
		entity_accessory->relativePosition = accessoryInfo->relativePosition;
		entity_accessory->relativeQuaternion = accessoryInfo->relativeQuaternion;
		entity_accessory->bindBoneName = accessoryInfo->bindBoneName;
		entity_accessory->isSyncAnimation = accessoryInfo->isSyncAnimation;
		entity_accessory->isDepositLifeTime = accessoryInfo->isDepositLifeTime;

		entity_accessory_collection->attachObject(final_name, *entity_accessory);

		MG_DELETE entity_accessory;

		return true;
	}

	//-----------------------------------------------------------------------
    void Scene::createEntityStaticAccessorys( IEntity* entity, U32 componentID )
    {
		if ( !entity )
			return;

		IEntityAccessoryCollection* entity_accessory_collection = entity->getEntityAccessoryCollection();
		if ( !entity_accessory_collection )
			return;

        // 读取附属物的表格
		U32 entityAccessoriesNum = MG::ResourceManager::getSingleton().getNumEntityAccessories( componentID );
		if ( entityAccessoriesNum > 0 )
		{
			for ( UInt i = 0; i < entityAccessoriesNum; i++ )
			{ 
				const EntityAccessoryDeclaration* decl = MG::ResourceManager::getSingleton().getEntityAccessoryDeclaration( componentID, i );
				if ( !decl )
					continue;

				//确定子实体名称
				ISceneObject* sub_object = NULL;
				U32 parentAttachCount = entity->getEntityAccessoryCollection()->getAttachObjectCount();

				Str suffix;
				MGStrOp::toString( parentAttachCount, suffix ); 

				Str final_name;
				final_name = entity->getName() + L"_subEntity_" + suffix;

				// 通过组件ID 创建各种附属物
				if ( decl->resourceType == SOT_ENTITY )
				{
					sub_object = createEntity( final_name.c_str(), decl->resourceID );
				}
				else if ( decl->resourceType == SOT_EFFECTENTITY )
				{
					// CN_MODIFY
					sub_object = createEffectComponent( final_name.c_str(), decl->resourceID, !decl->isDepositLifeTime );
				}

				if ( !sub_object || !sub_object->getSceneNode() )
					continue;

				IEntityAccessory *entity_accessory = MG_NEW IEntityAccessory;
				entity_accessory->sceneObject = sub_object;
				entity_accessory->relativePosition = decl->derivedPos;
				entity_accessory->relativeQuaternion = decl->derivedQuaternion;
				entity_accessory->bindBoneName = decl->bindBoneName;
				entity_accessory->isSyncAnimation = decl->isSyncAnimation;
				entity_accessory->isDepositLifeTime = decl->isDepositLifeTime;

				entity_accessory_collection->attachObject(final_name, *entity_accessory);

				// 绑定附属物到Entity
				MG_SAFE_DELETE(entity_accessory);
			}
		}
    }
	//-----------------------------------------------------------------------
	EntityGroup* Scene::createEntityGroup(CChar* name, U32 modelDeclID,UInt num)
	{
		EntityGroup* newEntityGroup = getEntityGroup( name );
		DYNAMIC_ASSERT(newEntityGroup==NULL);
		if ( newEntityGroup )
			return NULL;

		ModelDeclaration* modelDecl = MG::ResourceManager::getSingletonPtr()->getModelDeclaration(modelDeclID);
		newEntityGroup = MG_NEW EntityGroup(name, modelDecl, this, num); 
		newEntityGroup->setName(name);
		mEntityGroup[name] = newEntityGroup;

		return newEntityGroup;
	}
	//-----------------------------------------------------------------------
	EntityGroup* Scene::createEntityGroup(U32 modelDeclID,UInt num,CChar* prefixName)
	{
		Int i = 0;
		while( i++<1000 )
		{
			String name = mEntityNameGenerator.generate();
			if ( prefixName )
				name = Str(prefixName) + name;

			if ( getEntityGroup(name.c_str()) == NULL )
			{
				return createEntityGroup( name.c_str(), modelDeclID, num );
			}
		}
		return NULL;

	}
	//-----------------------------------------------------------------------
	EntityGroup* Scene::getEntityGroup(CChar* name)
	{
		std::map<String, EntityGroup*>::iterator iter = mEntityGroup.find(name);
		if ( iter != mEntityGroup.end() )
		{
			return iter->second;
		}
		return NULL;
	}
	//-----------------------------------------------------------------------
	void Scene::destroyEntityGroup(CChar* name)
	{
		std::map<String, EntityGroup*>::iterator iter = mEntityGroup.find(name);
		if ( iter != mEntityGroup.end() )
		{
			MG_SAFE_DELETE( iter->second );
			mEntityGroup.erase(iter);
		}
	}
	//-----------------------------------------------------------------------
	void Scene::destroyAllEntityGroup()
	{
		std::map<String, EntityGroup*>::iterator iter = mEntityGroup.begin();
		std::map<String, EntityGroup*>::iterator end_iter = mEntityGroup.end();
		for( ; iter != end_iter; iter++ )
		{
			MG_SAFE_DELETE( iter->second );
		}
		mEntityGroup.clear();
		mEntityGroupNameGenerator.reset();
	}
	//-----------------------------------------------------------------------
	void Scene::updateAllEntityGroup( Flt delta, RENDER_STATE state )
	{
		std::map<String, EntityGroup*>::iterator iter = mEntityGroup.begin();
		std::map<String, EntityGroup*>::iterator end_iter = mEntityGroup.end();
		for( ; iter != end_iter; iter++ )
		{
            if ( state == RS_PRE )
            {
                iter->second->preRendering();
            }else
            if ( state == RS_POST )
            {
                iter->second->postRendering();
            }else
            {
                iter->second->update( delta );
            }
		}
	}

    //-----------------------------------------------------------------------
    void Scene::createEntityGroupAccessorys( IEntityGroup* entity, U32 componentID  )
    {

    }

    //-----------------------------------------------------------------------
    void Scene::addStaticEntity(U32 modelDeclID,
        Vec3& pos, Qua& orientation, Vec3& scale, Bool isRandom, 
        Str staticGroup, Bool isReset)
    {
        StaticEntitySet* entitySet = createStaticEntitySet( modelDeclID );

        if ( entitySet )
        {
            entitySet->addStaticEntity( pos, orientation, scale, isRandom, staticGroup, isReset );
        }
    }

    //-----------------------------------------------------------------------
    void Scene::addStaticEntityAccessorys( U32 componentID, Vec3& pos, Qua& orientation, Vec3& scale )
    {
        // 读取附属物的表格
        // 通过组件ID 创建各种静态附属物addStaticEntity
        // 设置附属物位置

    }
    
    //-----------------------------------------------------------------------
    StaticEntitySet* Scene::createStaticEntitySet(U32 modelDeclID)
    {
        StaticEntitySet* entitySet = getStaticEntitySet( modelDeclID );
        
        if ( entitySet == NULL )
        {
            entitySet = MG_NEW StaticEntitySet( modelDeclID, this );
            mStaticEntitySets[ modelDeclID ] = entitySet;
        }

        return entitySet;
    }

    //-----------------------------------------------------------------------
    StaticEntitySet* Scene::getStaticEntitySet(U32 modelDeclID)
    {
        std::map<U32, StaticEntitySet*>::iterator iter = mStaticEntitySets.find( modelDeclID );
        if ( iter != mStaticEntitySets.end() )
        {
            return iter->second;
        }
        return NULL;
    }

    //-----------------------------------------------------------------------
    void Scene::destroyAllStaticEntity()
    {
        std::map<U32, StaticEntitySet*>::iterator iter = mStaticEntitySets.begin();
        for ( ;iter != mStaticEntitySets.end();iter++ )
        {
            MG_SAFE_DELETE( iter->second );
        }
        mStaticEntitySets.clear();
    }

    //-----------------------------------------------------------------------
    void Scene::buildStaticEntity()
    {
        std::map<U32, StaticEntitySet*>::iterator iter = mStaticEntitySets.begin();
        for ( ;iter != mStaticEntitySets.end();iter++ )
        {
            iter->second->buildStaticEntity();
        }
    }
    //-----------------------------------------------------------------------
    void Scene::updateStaticEntity( Flt delta )
    {
        std::map<U32, StaticEntitySet*>::iterator iter = mStaticEntitySets.begin();
        for ( ;iter != mStaticEntitySets.end();iter++ )
        {
            iter->second->update( delta );
        }
    }
    //-----------------------------------------------------------------------
	// CN_MODIFY
	EffectComponent* Scene::createEffectComponent( CChar* name, U32 effectResID, Bool isAutoDestroy, Bool isAutoStart)
	{
		EffectComponent* newEffectComponent = getEffectComponent( name );
		DYNAMIC_ASSERT(newEffectComponent==NULL);
		if ( newEffectComponent )
			return NULL;

		newEffectComponent = MG_NEW EffectComponent(name, effectResID, this, isAutoDestroy, isAutoStart); 

		if ( newEffectComponent && 
			newEffectComponent->initialised() )
		{
			newEffectComponent->setName(name);
			mEffectComponents[name] = newEffectComponent;
			return newEffectComponent;
		}

		return NULL;
	}
	//-----------------------------------------------------------------------
	EffectComponent* Scene::createEffectComponent( U32 effectResID, Bool isAutoDestroy, Bool isAutoStart)
	{
		Int i = 0;
		while( i++<1000 )
		{        
			String name = mEffectComponentNameGenerator.generate();
			if ( getEffectComponent(name.c_str()) == NULL )
			{
				return createEffectComponent( name.c_str(), effectResID, isAutoDestroy, isAutoStart);
			}
		}
		return NULL;
	}
	//-----------------------------------------------------------------------
	EffectComponent* Scene::createEffectComponent( CChar* name, CChar* fullfilename, Bool isAutoDestroy /*= true*/, Bool isAutoStart /*= true*/ )
	{
		EffectComponent* newEffectComponent = getEffectComponent( name );
		DYNAMIC_ASSERT(newEffectComponent==NULL);
		if ( newEffectComponent )
			return NULL;

		newEffectComponent = MG_NEW EffectComponent(name, fullfilename, this, isAutoDestroy, isAutoStart); 

		if ( newEffectComponent && 
			newEffectComponent->initialised() )
		{
			newEffectComponent->setName(name);
			mEffectComponents[name] = newEffectComponent;
			return newEffectComponent;
		}

		return NULL;
	}
	//-----------------------------------------------------------------------
	EffectComponent* Scene::createEffectComponent( CChar* fullfilename, Bool isAutoDestroy /*= true*/, Bool isAutoStart /*= true*/ )
	{
		Int i = 0;
		while( i++<1000 )
		{        
			String name = mEffectComponentNameGenerator.generate();
			if ( getEffectComponent(name.c_str()) == NULL )
			{
				return createEffectComponent( name.c_str(), fullfilename, isAutoDestroy, isAutoStart);
			}
		}
		return NULL;
	}
	//-----------------------------------------------------------------------
	EffectComponent* Scene::createEmptyEffectComponent( CChar* name )
	{
		EffectComponent* newEffectComponent = getEffectComponent( name );
		DYNAMIC_ASSERT(newEffectComponent==NULL);
		if ( newEffectComponent )
			return NULL;

		newEffectComponent = MG_NEW EffectComponent(name, this); 

		if ( newEffectComponent )
		{
			newEffectComponent->setName(name);
			mEffectComponents[name] = newEffectComponent;
			return newEffectComponent;
		}

		return NULL;
	}
	//-----------------------------------------------------------------------
	EffectComponent* Scene::createEmptyEffectComponent()
	{
		Int i = 0;
		while( i++<1000 )
		{        
			String name = mEmptyEffectComponentNameGenerator.generate();
			if ( getEffectComponent(name.c_str()) == NULL )
			{
				return createEmptyEffectComponent( name.c_str() );
			}
		}
		return NULL;
	}
	//-----------------------------------------------------------------------
	void Scene::destroyEffectComponent( CChar* name )
	{
		std::map<String, EffectComponent*>::iterator iter = mEffectComponents.find(name);
		if ( iter != mEffectComponents.end() )
		{
			MG_SAFE_DELETE( iter->second );
			mEffectComponents.erase(iter);
		}
	}
	//-----------------------------------------------------------------------
	EffectComponent* Scene::getEffectComponent( CChar* name )
	{
		std::map<String, EffectComponent*>::iterator iter = mEffectComponents.find(name);
		if ( iter != mEffectComponents.end() )
		{
			return iter->second;
		}
		return NULL;
	}
	//-----------------------------------------------------------------------
	EffectComponent* Scene::getEffectComponent( U32 index )
	{
		std::map<String, EffectComponent*>::iterator iter = mEffectComponents.begin();
		std::advance(iter, index);

		if( iter != mEffectComponents.end() )
		{
			return iter->second;
		}

		return NULL;
	}
	//-----------------------------------------------------------------------
	void Scene::destroyAllEffectComponent()
	{
		std::map<String, EffectComponent*>::iterator iter = mEffectComponents.begin();
		std::map<String, EffectComponent*>::iterator end_iter = mEffectComponents.end();
		for( ; iter != end_iter; iter++ )
		{
			MG_SAFE_DELETE( iter->second );
		}
		mEffectComponents.clear();
		mEffectComponentNameGenerator.reset();
		mEmptyEffectComponentNameGenerator.reset();
	}
	//-----------------------------------------------------------------------
	void Scene::updateAllEffectComponent( Flt delta )
	{
		std::map<String, EffectComponent*>::iterator iter = mEffectComponents.begin();
		std::map<String, EffectComponent*>::iterator end_iter = mEffectComponents.end();
		for( ; iter != end_iter;  )
		{
			if ( iter->second->update( delta ) == false )
			{
				MG_SAFE_DELETE( iter->second );
				iter = mEffectComponents.erase( iter );
			}else
			{
				iter++;
			}
		}
	}
	//-----------------------------------------------------------------------
	PUEffect* Scene::createPUEffect( CChar* name, CChar* effectTemplate, Bool isAutoDestroy /*= true*/, Bool isAutoStart /*= true*/ )
	{
		PUEffect* newPUEffect = getPUEffect( name );
		DYNAMIC_ASSERT(newPUEffect==NULL);
		if ( newPUEffect )
			return NULL;

		newPUEffect = MG_NEW PUEffect(name, effectTemplate, this, isAutoDestroy, isAutoStart); 

		if ( newPUEffect )
		{
			newPUEffect->setName(name);
			mPUEffects[name] = newPUEffect;
			return newPUEffect;
		}

		return NULL;
	}
	//-----------------------------------------------------------------------
	PUEffect* Scene::createPUEffect( CChar* effectTemplate, Bool isAutoDestroy /*= true*/, Bool isAutoStart /*= true*/ )
	{
		Int i = 0;
		while( i++<1000 )
		{        
			String name = mPUEffectNameGenerator.generate();
			if ( getPUEffect(name.c_str()) == NULL )
			{
				return createPUEffect( name.c_str(), effectTemplate, isAutoDestroy, isAutoStart );
			}
		}
		return NULL;
	}
	//-----------------------------------------------------------------------
	PUEffect* Scene::createPUEffect( U32 effectResID, Bool isAutoDestroy /*= true*/, Bool isAutoStart /*= true*/ )
	{
		Int i = 0;
		while( i++<1000 )
		{        
			String name = mPUEffectNameGenerator.generate();
			if ( getPUEffect(name.c_str()) == NULL )
			{
				return createPUEffect( name.c_str(), effectResID, isAutoDestroy, isAutoStart );
			}
		}
		return NULL;
	}
	//-----------------------------------------------------------------------
	PUEffect* Scene::createPUEffect( CChar* name, U32 effectResID, Bool isAutoDestroy /*= true*/, Bool isAutoStart /*= true*/ )
	{
		PUEffect* newPUEffect = getPUEffect( name );
		DYNAMIC_ASSERT(newPUEffect==NULL);
		if ( newPUEffect )
			return NULL;

		newPUEffect = MG_NEW PUEffect(name, effectResID, this, isAutoDestroy, isAutoStart); 

		if ( newPUEffect )
		{
			newPUEffect->setName(name);
			mPUEffects[name] = newPUEffect;
			return newPUEffect;
		}

		return NULL;
	}
	//-----------------------------------------------------------------------
	void Scene::destroyPUEffect( CChar* name )
	{
		std::map<String, PUEffect*>::iterator iter = mPUEffects.find(name);
		if ( iter != mPUEffects.end() )
		{
			MG_SAFE_DELETE( iter->second );
			mPUEffects.erase(iter);
		}
	}
	//-----------------------------------------------------------------------
	PUEffect* Scene::getPUEffect( CChar* name )
	{
		std::map<String, PUEffect*>::iterator iter = mPUEffects.find(name);
		if ( iter != mPUEffects.end() )
		{
			return iter->second;
		}
		return NULL;
	}
	//-----------------------------------------------------------------------
	void Scene::destroyAllPUEffect()
	{
		std::map<String, PUEffect*>::iterator iter = mPUEffects.begin();
		std::map<String, PUEffect*>::iterator end_iter = mPUEffects.end();
		for( ; iter != end_iter; iter++ )
		{
			MG_SAFE_DELETE( iter->second );
		}
		mPUEffects.clear();
		mEffectComponentNameGenerator.reset();
		mEmptyEffectComponentNameGenerator.reset();
	}
	//-----------------------------------------------------------------------
	void Scene::updateAllPUEffect( Flt delta )
	{
		std::map<String, PUEffect*>::iterator iter = mPUEffects.begin();
		std::map<String, PUEffect*>::iterator end_iter = mPUEffects.end();
		for( ; iter != end_iter;  )
		{
			if ( iter->second->update( delta ) == false )
			{
				MG_SAFE_DELETE( iter->second );
				iter = mPUEffects.erase( iter );
			}else
			{
				iter++;
			}
		}
	}
	//-----------------------------------------------------------------------
    EffectEntity* Scene::createEffectEntity(CChar* name, U32 effectResID, Bool isAutoDestroy,Bool isAutoStart)
    {
        EffectEntity* newEffectEntity = getEffectEntity( name );
        DYNAMIC_ASSERT(newEffectEntity==NULL);
        if ( newEffectEntity )
            return NULL;

        newEffectEntity = MG_NEW EffectEntity(name, effectResID, this, isAutoDestroy, isAutoStart); 

		if ( newEffectEntity && 
			newEffectEntity->initialised() )
		{
			newEffectEntity->setName(name);
			mEffectEntitys[name] = newEffectEntity;
			return newEffectEntity;
		}

		return NULL;
    }
    //-----------------------------------------------------------------------
    EffectEntity* Scene::createEffectEntity(U32 effectResID, Bool isAutoDestroy, Bool isAutoStart)
    {
        Int i = 0;
        while( i++<1000 )
        {        
			String name = mEffectEntityNameGenerator.generate();
            if ( getEffectEntity(name.c_str()) == NULL )
            {
                return createEffectEntity( name.c_str(), effectResID, isAutoDestroy, isAutoStart );
            }
        }
        return NULL;
    }
    //-----------------------------------------------------------------------
    void Scene::destroyEffectEntity(CChar* name)
    {
        std::map<String, EffectEntity*>::iterator iter = mEffectEntitys.find(name);
        if ( iter != mEffectEntitys.end() )
        {
            MG_SAFE_DELETE( iter->second );
            mEffectEntitys.erase(iter);
        }
    }
    //-----------------------------------------------------------------------
    EffectEntity* Scene::getEffectEntity(CChar* name)
    {
        std::map<String, EffectEntity*>::iterator iter = mEffectEntitys.find(name);
        if ( iter != mEffectEntitys.end() )
        {
            return iter->second;
        }
        return NULL;
    }
    //-----------------------------------------------------------------------
    void Scene::destroyAllEffectEntity()
    {
        std::map<String, EffectEntity*>::iterator iter = mEffectEntitys.begin();
        std::map<String, EffectEntity*>::iterator end_iter = mEffectEntitys.end();
        for( ; iter != end_iter; iter++ )
        {
            MG_SAFE_DELETE( iter->second );
        }
        mEffectEntitys.clear();
		mEffectEntityNameGenerator.reset();
    }
    //-----------------------------------------------------------------------
    void Scene::updateAllEffectEntity( Flt delta )
    {
        std::map<String, EffectEntity*>::iterator iter = mEffectEntitys.begin();
        std::map<String, EffectEntity*>::iterator end_iter = mEffectEntitys.end();
        for( ; iter != end_iter;  )
        {
            if ( iter->second->update( delta ) == false )
            {
                MG_SAFE_DELETE( iter->second );
                iter = mEffectEntitys.erase( iter );
            }else
            {
                iter++;
            }
        }
    }
    //-----------------------------------------------------------------------
    //ITerrainDecalSet* Scene::createTerrainDecalSet(CChar* name, UInt num, CChar* texFileName)
    //{
    //    TerrainDecalSet* newDecalSet = getTerrainDecalSet( name );
    //    DYNAMIC_ASSERT(newDecalSet==NULL);
    //    if ( newDecalSet )
    //        return NULL;

    //    newDecalSet = MG_NEW TerrainDecalSet(name, texFileName, num, this); 
    //    mTerrainDecalSets[name] = newDecalSet;
    //    return newDecalSet;
    //}

    ////-----------------------------------------------------------------------
    //ITerrainDecalSet* Scene::createTerrainDecalSet(UInt num, CChar* texFileName)
    //{
    //    Int i = 0;
    //    while( i++<1000 )
    //    {        
    //        String name = mTerrainDecalSetNameGenerator.generate();
    //        if ( getEffectEntity(name.c_str()) == NULL )
    //        {
    //            return createTerrainDecalSet( name.c_str(), num, texFileName );
    //        }
    //    }
    //    return NULL;
    //}

    ////-----------------------------------------------------------------------
    //void Scene::destroyTerrainDecalSet(CChar* name)
    //{
    //    std::map<String, TerrainDecalSet*>::iterator iter = mTerrainDecalSets.find(name);
    //    if ( iter != mTerrainDecalSets.end() )
    //    {
    //        MG_SAFE_DELETE( iter->second );
    //        mTerrainDecalSets.erase(iter);
    //    }
    //}

    ////-----------------------------------------------------------------------
    //TerrainDecalSet* Scene::getTerrainDecalSet(CChar* name)
    //{
    //    std::map<String, TerrainDecalSet*>::iterator iter = mTerrainDecalSets.find(name);
    //    if ( iter != mTerrainDecalSets.end() )
    //    {
    //        return iter->second;
    //    }
    //    return NULL;
    //}

    ////-----------------------------------------------------------------------
    //void Scene::destroyAllTerrainDecalSet()
    //{
    //    std::map<String, TerrainDecalSet*>::iterator iter = mTerrainDecalSets.begin();
    //    std::map<String, TerrainDecalSet*>::iterator end_iter = mTerrainDecalSets.end();
    //    for( ; iter != end_iter; iter++ )
    //    {
    //        MG_SAFE_DELETE( iter->second );
    //    }
    //    mTerrainDecalSets.clear();
    //    mTerrainDecalSetNameGenerator.reset();
    //}


    ////-----------------------------------------------------------------------
    //void Scene::updateAllTerrainDecalSet( Flt delta, RENDER_STATE state )
    //{
    //    std::map<String, TerrainDecalSet*>::iterator iter = mTerrainDecalSets.begin();
    //    std::map<String, TerrainDecalSet*>::iterator end_iter = mTerrainDecalSets.end();
    //    for( ; iter != end_iter; iter++ )
    //    {
    //        if ( state == RS_PRE )
    //        {
    //            iter->second->preRendering();
    //        }else
    //        if ( state == RS_POST )
    //        {
    //            iter->second->postRendering();
    //        }else
    //        {
    //            iter->second->update( delta );
    //        }

    //        iter->second->update( delta );
    //    }
    //}
	IDecalSet* Scene::createDecalSet(CChar* name, UInt num, CChar* texFileName, IDecalType type)
	{
		IDecalSet* newDecalSet = getDecalSet( name );
		DYNAMIC_ASSERT(newDecalSet==NULL);
		if ( newDecalSet )
			return NULL;

		switch (type)
		{
		case DT_SIMPLE:
			newDecalSet = MG_NEW TerrainDecalSet(name, texFileName, num, this); 
			break;
		case DT_HIGHLEVEL:
			newDecalSet = MG_NEW HighLevelDecalSet(name, texFileName, num, this); 
			break;
		}

		mDecalSets[name] = newDecalSet;
		return newDecalSet;
	}

	//-----------------------------------------------------------------------
	IDecalSet* Scene::createDecalSet(UInt num, CChar* texFileName, IDecalType type)
	{
		Int i = 0;
		while( i++<1000 )
		{        
			String name = mDecalSetNameGenerator.generate();
			if ( getEffectEntity(name.c_str()) == NULL )
			{
				return createDecalSet( name.c_str(), num, texFileName, type);
			}
		}
		return NULL;
	}

	//-----------------------------------------------------------------------
	void Scene::destroyDecalSet(CChar* name)
	{
		std::map<String, IDecalSet*>::iterator iter = mDecalSets.find(name);
		if ( iter != mDecalSets.end() )
		{
			MG_SAFE_DELETE( iter->second );
			mDecalSets.erase(iter);
		}
	}

	//-----------------------------------------------------------------------
	IDecalSet* Scene::getDecalSet(CChar* name)
	{
		std::map<String, IDecalSet*>::iterator iter = mDecalSets.find(name);
		if ( iter != mDecalSets.end() )
		{
			return iter->second;
		}
		return NULL;
	}

	//-----------------------------------------------------------------------
	void Scene::destroyAllDecalSet()
	{
		std::map<String, IDecalSet*>::iterator iter = mDecalSets.begin();
		std::map<String, IDecalSet*>::iterator end_iter = mDecalSets.end();
		for( ; iter != end_iter; iter++ )
		{
			MG_SAFE_DELETE( iter->second );
		}
		mDecalSets.clear();
		mDecalSetNameGenerator.reset();
	}

	//-----------------------------------------------------------------------
	void Scene::updateAllDecalSet( Flt delta, RENDER_STATE state/* = RS_IDLE */)
	{
		std::map<String, IDecalSet*>::iterator iter = mDecalSets.begin();
		std::map<String, IDecalSet*>::iterator end_iter = mDecalSets.end();
		for( ; iter != end_iter; iter++ )
		{
	        if ( state == RS_PRE )
	        {
	            iter->second->preRendering();
	        }else
	        if ( state == RS_POST )
	        {
	            iter->second->postRendering();
	        }else
	        {
	            iter->second->update( delta );
	        }

	        iter->second->update( delta );
		}
	}

    //-----------------------------------------------------------------------
    Gui* Scene::createGui(CChar* resourceFileName, CChar* coreFileName, Str8 fontName, IPointer*& pIPointer, IFont*& pIFont)
    {
        DYNAMIC_ASSERT( mGui == NULL );
        mGui = MG_NEW Gui(resourceFileName, coreFileName, this); 

        InputManager::getSingletonPtr()->addKeyListener(mGui, "Gui");
        InputManager::getSingletonPtr()->addMouseListener(mGui, "Gui");

		mGui->init(fontName, pIPointer, pIFont);

        return mGui;
    }
    //-----------------------------------------------------------------------
    void Scene::destroyGui()
    {
        InputManager::getSingletonPtr()->removeKeyListener("Gui");
        InputManager::getSingletonPtr()->removeMouseListener("Gui");
        MG_SAFE_DELETE( mGui );
    }
    //-----------------------------------------------------------------------
    WireframeManager* Scene::getWireframeManager()
    {
        if ( mWireframeManager == NULL )
        {
            mWireframeManager = MG_NEW WireframeManager(this);
        }
        return mWireframeManager;
    }
    //-----------------------------------------------------------------------
    MiniMapManager* Scene::getMiniMapManager()
    {
        return mMiniMapManager;
    }
    //-----------------------------------------------------------------------
    ShadowManager* Scene::getShadowManager()
    {
        return mShadowManager;
    }
    //-----------------------------------------------------------------------
    TerrainManager* Scene::getTerrainManager()
    {
        return mTerrainManager;
    }
    //-----------------------------------------------------------------------
    CollisionSystem* Scene::getCollisionSystem()
    {
        return mCollisionSystem;
    }
    //-----------------------------------------------------------------------
    IActionManager* Scene::getActionManager()
    {   
        return mActionManager;
    }
    //-----------------------------------------------------------------------
    BlockManager* Scene::getBlockManager()
    {
        return mBlockManager;
    }
	//-----------------------------------------------------------------------
	DynamicBlockObjectSceneManager* Scene::getDynamicBlockObjectSceneManager()
	{
		return mDynamicBlockObjectSceneManager;
	}
    //-----------------------------------------------------------------------
    PathFindingManager* Scene::getPathFindingManager()
    {
        return mPathFindingManager;
    }
    //-----------------------------------------------------------------------
    CompositorManager* Scene::getCompositorManager()
    {
        return mCompositorManager;
    }
	//-----------------------------------------------------------------------
	TreeManager* Scene::getTreeManager()
	{
		//return mTreeManager;
		return &TreeManager::getInstance();
	}
    //-----------------------------------------------------------------------
    SceneDebuger* Scene::getSceneDebuger()
    {
        return mSceneDebuger;
    }
    //-----------------------------------------------------------------------
    void Scene::setAmbientLight(const Color& colour)
    {
        if ( mOgreSceneManager )
        {
            ColourValue colourValue(colour.r,colour.g,colour.b,colour.a);
            mOgreSceneManager->setAmbientLight( colourValue );
        }
    }
    //-----------------------------------------------------------------------
    Color Scene::getAmbientLight()
    {
        Color color;
        if ( mOgreSceneManager )
        {
            ColourValue colourValue = mOgreSceneManager->getAmbientLight();
            color.r = colourValue.r;
            color.g = colourValue.g;
            color.b = colourValue.b;
            color.a = colourValue.a;
        }
        return color;
    }
    //-----------------------------------------------------------------------
    Int Scene::getQueryMask( SceneObjectTypes type )
    {
		if ( type == SOT_ENTITY || type == SOT_ENTITY_GROUP || type == SOT_TREE || type == SOT_EFFECTENTITY )
        {
            return SceneManager::ENTITY_TYPE_MASK;
        }
        else
        if ( type == SOT_GROUND )
        {
            return 0x16000000;
        }

        return 0;
    }


}

