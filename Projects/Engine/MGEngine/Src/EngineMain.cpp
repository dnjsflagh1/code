/******************************************************************************/
#include "stdafx.h"
#include "EngineMain.h"
#include "Application.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "Display.h"
#include "ResourceManager.h"
#include "Gui.h"
#include "Scene.h"
#include "MGCapabilities.h"
#include "EditorSystem.h"
#include "EngineUtil.h"
#include "OgreTextAreaOverlayElement.h"
#include "IMGPackExterInterface.h"
#include "MGExternalPackManager.h"
#include "ExternalOgreResourceManager.h"
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    Ogre::Root * OgreMainInterface::root = NULL;
    Ogre::RenderWindow * OgreMainInterface::renderWindow = NULL;
    //-----------------------------------------------------------------------
    EngineMain::EngineMain()
        :mApp(NULL)
        ,mInputMgr(NULL)
        ,mDisplay(NULL)
        ,mResourceMgr(NULL)
        ,mSoundMgr(NULL)
        ,mRenderLocker(false)
		,mTreeManagerLocker(false)
		,mOgrePackManager(NULL)
		,mMGPackManager(NULL)
		,mEngineMode(EM_NORMAL)
    {
    }
    //-----------------------------------------------------------------------
    EngineMain::~EngineMain()
    {
        
    }
	//-----------------------------------------------------------------------
	bool EngineMain::initialize( const EngineInitConfig* pConfig )
	{
		if ( !pConfig )
			return false;

		//------------------------------------------------------------------

		// 日志系统
		LogSystem::getInstance().setGameLogicLogPath("log//engine");
		LogSystem::getInstance().setSysLogPath("log//engine");

		LogSystem::getInstance().setEnableConsole(false);
		LogSystem::getInstance().setSaveToFile(true);

#ifdef _DEBUG
		LogSystem::getInstance().setLogLevel( out_max );
#endif

		//------------------------------------------------------------------

		const EngineInitConfig& config = *pConfig;
		
		Bool isFullScreen = config.isFullScreen;
		U32 screenWidth = config.screenWidth;
		U32 screenHeight = config.screenHeight;

		// MG_CN_MODIFY

		if ( pConfig->packManager )
		{
			mOgrePackManager = MG_NEW ExOgreResourceManager(pConfig->packManager);
			mMGPackManager   = MG_NEW MGExternalPackManager(pConfig->packManager);
		}

		// 初始化引擎。 configFileName 文件仅仅用来保证ogre原有初始化流程，其中的数据会被EngineInitConfig替换
        OgreMainInterface::root = MG_NEW Ogre::Root( config.pluginFileName, config.configFileName, 
			config.logFileName, mOgrePackManager );
		OgreMainInterface::root->restoreConfig();

		////////////////////////////////////////////////////////////////////////
		mDisplay = MG_NEW Display(); 

		// 仅仅设置Ogre内部参数，但是不响应。在创建窗体的时候才响应。
		mDisplay->setFSAA( config.fsaa, config.fsaaHint );

		mDisplay->setVsync( config.isVsync );
		if ( config.isVsync )
			mDisplay->setVsyncInterval(0);
		else
			mDisplay->setVsyncInterval(1);

		mDisplay->setVideoMode( isFullScreen, screenWidth, screenHeight );
		mDisplay->getVideoMode( isFullScreen, screenWidth, screenHeight );
		
		mDisplay->setup();

		////////////////////////////////////////////////////////////////////////

        // 应用程序管理
        mApp = MG_NEW Application(); 		
		// 创建窗体
        mApp->createWindow( config.windowName, screenWidth, screenHeight, isFullScreen, config.windowsHandle );
		// 定位资源
        locateResources( config.resFileName );
		// 加载资源
        loadResources();

        ////////////////////////////////////////////////////////////////////////

        //输入输出
        mInputMgr = MG_NEW InputManager();

        // 输入控制器
        mInputMgr->initialise( OgreMainInterface::renderWindow, pConfig->inputHandle);

        ////////////////////////////////////////////////////////////////////////

        //资源管理
        mResourceMgr = MG_NEW ResourceManager(); 
        // 加载资源文件
        mResourceMgr->loadDeclarations( config );
        mResourceMgr->loadTerrainTextureLayerDeclarations( config.terrainTextureDeclFileName );

        ////////////////////////////////////////////////////////////////////////

        //声音管理器
        mSoundMgr = MG_NEW SoundALManager();

        ////////////////////////////////////////////////////////////////////////

        // 性能检测
        if ( MGCapabilities::getInstance().check() == false )
            return false;

        ////////////////////////////////////////////////////////////////////////

		// CN_MODIFY
		if (!TreeManager::getInstance().load(config.treeResourceFileName, config.grassResourceFileName, pConfig->packManager))
		{
			return false;
		}

        //TreeManager::TREE_CSV_FILE  = config.treeResourceFileName;
        //TreeManager::GRASS_CSV_FILE = config.grassResourceFileName;

        ////////////////////////////////////////////////////////////////////////

		return true;
	}
	//-----------------------------------------------------------------------
	bool EngineMain::uninitialize()
	{
		TreeManager::getInstance().unload();
        destroyAllScene();

        MG_SAFE_DELETE( mInputMgr );
        MG_SAFE_DELETE( mSoundMgr );
        MG_SAFE_DELETE( mDisplay );
        MG_SAFE_DELETE( mApp );
        MG_SAFE_DELETE( mResourceMgr );

        MG_SAFE_DELETE( OgreMainInterface::root );

		MG_SAFE_DELETE(mMGPackManager);
		MG_SAFE_DELETE(mOgrePackManager);

		return true;
	}

	//-----------------------------------------------------------------------
	void EngineMain::setMode( EngineMode mode )
	{
		mEngineMode = mode;
	}

	//-----------------------------------------------------------------------
	EngineMode EngineMain::getMode()
	{
		return mEngineMode;
	}

    //-----------------------------------------------------------------------
    IScene* EngineMain::createScene( CChar* sceneName, CChar* camName )
    {
        //没有做重名检测，外部维护
        Scene* newScene = MG_NEW Scene(sceneName, camName); 
        mScenes[sceneName] = newScene;
        return newScene;
    }
    //-----------------------------------------------------------------------
    void EngineMain::destroyAllScene()
    {
        std::map<String, Scene*>::iterator iter = mScenes.begin();
        std::map<String, Scene*>::iterator end_iter = mScenes.end();
        for( ; iter != end_iter; iter++ )
        {
            MG_SAFE_DELETE( iter->second );
        }
        mScenes.clear();
    }
    //-----------------------------------------------------------------------
    Scene* EngineMain::getFirstScene()
    {
        std::map<String, Scene*>::iterator iter = mScenes.begin();
        if ( iter!=mScenes.end() )
        {
            return iter->second;
        }
        return NULL;
    }
    //-----------------------------------------------------------------------
    IApplication* EngineMain::app()
    {
        return mApp;
    }
    //-----------------------------------------------------------------------
    IInput* EngineMain::input()
    {
        return mInputMgr;
    }
    //-----------------------------------------------------------------------
    ISoundManager* EngineMain::soundMgr()
    {
        return mSoundMgr;
    }
    //-----------------------------------------------------------------------
    IResourceManager* EngineMain::resourceMgr()
    {
        return mResourceMgr;
    }
	//-----------------------------------------------------------------------
	IDisplay*	EngineMain::display()
	{
		return mDisplay;
	}

    //-----------------------------------------------------------------------
    IEditorSystem* EngineMain::editorSystem()
    {
        return &EditorSystem::getInstance();
    }

    //-----------------------------------------------------------------------
    IEngineUtil* EngineMain::engineUtil()
    {
        return &EngineUtil::getInstance();
    }

    //-----------------------------------------------------------------------
	IMGExternalPackManager* EngineMain::getPackManager()
	{
		return mMGPackManager;
	}

    //-----------------------------------------------------------------------
    void EngineMain::locateResources(CChar* filename)
    {
		Ogre::ConfigFile cf;
        cf.load(filename);
        
        // Go through all sections & settings in the file
		Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

        Ogre::String secName, typeName, archName;
        while (seci.hasMoreElements())
        {
            secName = seci.peekNextKey();
			Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
			Ogre::ConfigFile::SettingsMultiMap::iterator i;
            for (i = settings->begin(); i != settings->end(); ++i)
            {
                typeName = i->first;
                archName = i->second;
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
                // OS X does not set the working directory relative to the app,
                // In order to make things portable on OS X we need to provide
                // the loading with it's own bundle path location
                ResourceGroupManager::getSingleton().addResourceLocation(
                    Ogre::String(macBundlePath() + "/" + archName), typeName, secName);
#else
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                    archName, typeName, secName);
#endif
            }
        }
    }
    //-----------------------------------------------------------------------
    void EngineMain::loadResources()
    {
        Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    }
    //-----------------------------------------------------------------------
    bool EngineMain::update( Flt delta )
    {
        Ogre::RenderWindow* window = OgreMainInterface::renderWindow;

        // 判断是否窗口关闭了
        Bool result = !window->isClosed();

        if( window->isActive() && 
            !window->isClosed() ) 
        {
            // 消息处理
            Ogre::WindowEventUtilities::messagePump();

            // 输入捕捉 
            mInputMgr->update( delta );

            // 更新场景
            std::map<String, Scene*>::iterator iter = mScenes.begin();
            std::map<String, Scene*>::iterator end_iter = mScenes.end();
            for( ; iter != end_iter; iter++ )
            {
                iter->second->update( delta );
            }

            //更新显示
            mDisplay->update();
		}

        return result;
    }

    //-----------------------------------------------------------------------
    void EngineMain::lockRender()
    {
        mRenderLocker = true;
    }

    //-----------------------------------------------------------------------
    void EngineMain::unLockRender()
    {
        mRenderLocker = false;
    }

	//-----------------------------------------------------------------------
	void EngineMain::lockTreeManager() 
	{ 
		mTreeManagerLocker = true; 
	}

	//-----------------------------------------------------------------------
	void EngineMain::unLockTreeManager() 
	{ 
		mTreeManagerLocker = false; 
	}

	//-----------------------------------------------------------------------
	Bool EngineMain::isTreeManagerLocked()
	{
		return mTreeManagerLocker;
	}

    //-----------------------------------------------------------------------
    Bool EngineMain::render( Flt delta )
    {
        if ( !mRenderLocker )
        {
            // 初始化渲染目标
            OgreMainInterface::root->getRenderSystem()->_initRenderTargets();

            // 渲染前处理
            preRendering();
            {
                // 渲染单帧
                OgreMainInterface::root->renderOneFrame( delta );
            }
            // 渲染后处理
            postRendering();
			//::OutputDebugString("END\n");
        }

        return false;
    }

    //-----------------------------------------------------------------------
    void EngineMain::preRendering()
    {
        std::map<String, Scene*>::iterator iter = mScenes.begin();
        while (iter != mScenes.end())
        {
            iter->second->preRendering();
            ++iter;
        }
    }

    //-----------------------------------------------------------------------
    void EngineMain::postRendering()
    {
        std::map<String, Scene*>::iterator iter = mScenes.begin();
        while (iter != mScenes.end())
        {
            iter->second->postRendering();
            ++iter;
        }
    }

    //-----------------------------------------------------------------------
    void EngineMain::applyRenderConfig()
    {
        std::map<String, Scene*>::iterator iter = mScenes.begin();
        while (iter != mScenes.end())
        {
            iter->second->applyRenderConfig();
            ++iter;
        }
    }
    //-----------------------------------------------------------------------
    void EngineMain::applyResolutionConfig(UInt nScreenX, UInt nScreenY)
    {
        std::map<String, Scene*>::iterator iter = mScenes.begin();
        while (iter != mScenes.end())
        {
            iter->second->applyResolutionConfig(nScreenX, nScreenY);
            ++iter;
        }
    }
	//-----------------------------------------------------------------------
	void EngineMain::renderOneFrame( Flt delta )
	{
		OgreMainInterface::root->renderOneFrame(delta);
	}
}


