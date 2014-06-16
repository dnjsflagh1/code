/******************************************************************************/
#include "GlobalOption.h"

#include "Define.h"
#include "CoreManager.h"
#include "OperationManager.h"
#include "AddObjectTabDialog.h"
#include "RenderWindow.h"
#include "ExComponentWidget.h"
#include "EntityWidget.h"
#include "EffectWidget.h"
#include "EventWidget.h"
#include "IEffectXmlSerializer.h"
#include "IEffectComponent.h"
#include "IEffectComponentTimeLine.h"
/******************************************************************************/


namespace EffectEditor {

	//-----------------------------------------------------------------------
	CoreManager::CoreManager()
		:mEngineMain(NULL)
		,mStopUpdateDirty(false)
		,mMainScene(NULL)
		,mCurrentComponent(NULL)
	{
	}
	//-----------------------------------------------------------------------
	CoreManager::~CoreManager()
	{

	}
	//-----------------------------------------------------------------------
	Bool CoreManager::initialize()
	{
		if ( loadLib() == false )
			return false;
		if ( loadForm() == false )
			return false;
		if ( loadEngine() == false )
			return false;
		if ( loadGameFile() == false )
			return false;

		return true;
	}
	//-----------------------------------------------------------------------
	Bool CoreManager::uninitialize()
	{
		unLoadEngine();
		unLoadForm();
		unLoadLib();
		unLoadGameFile();

		return true;
	}
	//-----------------------------------------------------------------------
	void CoreManager::stop()
	{
		mStopUpdateDirty = true;
	}
	//-----------------------------------------------------------------------
	void CoreManager::run()
	{
		WindowSet::main_win->show();
		WindowSet::main_win->setWindowModality(Qt::WindowModal);

		mCurrUpdateTicks = GetTickCount() * 0.001;
		mLastUpdateTicks = mCurrUpdateTicks;
		mUpdateDelta = 0.0;

		IDisplay* display = mEngineMain->display();

		while( mStopUpdateDirty == false )
		{
			if (!WindowSet::main_win->isVisible())
			{
				break;
			}

			Flt fps = display->getLastAverageFPS();
			WindowSet::main_win->updateStatusBar(fps);

			mCurrUpdateTicks = GetTickCount() * 0.001;
			mUpdateDelta = mCurrUpdateTicks - mLastUpdateTicks;
			mLastUpdateTicks = mCurrUpdateTicks;
			if ( update( mUpdateDelta ) == false )
				break;
		}

	}

	//-----------------------------------------------------------------------
	Bool CoreManager::update( Dbl delta )
	{
		if ( mEngineMain->update( (Flt)delta ) == false )
			return false;

		WindowSet::main_win->update((Flt)delta);

		OperationManager::getInstance().update( delta );

		mEngineMain->render( (Flt)delta );

		return true;
	}
	//-----------------------------------------------------------------------
	Bool CoreManager::loadForm()
	{
		WindowSet::main_win = new MainWindow();

		return true;
	}
	//-----------------------------------------------------------------------
	Bool CoreManager::unLoadForm()
	{
		MG_SAFE_DELETE(WindowSet::main_win);
		return true;
	}
	//-----------------------------------------------------------------------
	Bool CoreManager::loadLib()
	{
		GET_MGENGINE_INTERFACE_PROC proc; 

		std::wstring dllName;
#ifdef _DEBUG
		dllName = L"Core\\MGEngine_d.dll";
#else
		dllName = L"Core\\MGEngine.dll";
#endif

		if (mEngineDllLoader.load(dllName.c_str(),false)) 
		{ 
			proc = (GET_MGENGINE_INTERFACE_PROC) mEngineDllLoader.getProcAddress("GET_MGENGINE_INTERFACE"); 
			if (NULL != proc) 
			{
				mEngineMain = (MG::IEngineMain*)proc(); 
				if (mEngineMain==NULL)
				{
					MG::MsgBox::show("Load IEngineMain Failed!");
					return false;
				}
			}else
			{
				MG::MsgBox::show("Don't Find IEngineMain Entry!");
				return false;
			}
		}else
		{
			MG::MsgBox::show("Don't Load IEngineMain DLL!");
			return false;
		}

		return true;
	}
	//-----------------------------------------------------------------------
	Bool CoreManager::unLoadLib()
	{
		mEngineDllLoader.unload();
		return true;
	}
	//-----------------------------------------------------------------------
	Bool CoreManager::loadEngine()
	{
		EngineInitConfig config;

#ifdef _DEBUG
		config.pluginFileName               = "Config\\Engine\\Plugins_d.cfg";
#else
		config.pluginFileName               = "Config\\Engine\\Plugins.cfg";
#endif
		config.configFileName               = "Config\\Engine\\DisplaySetting.cfg";
		config.resFileName                  = "EditorData\\EffectRes.cfg";

		config.logFileName                  = "Log\\Effect.log";

		config.modelDeclFileName            = "Config\\Game\\ArtRes\\ArtModelRes.csv";
		config.accessoryDeclFileName        = "Config\\Game\\ArtRes\\EntityAccessoryDeclaration.csv";
		config.effectDeclFileName           = "Config\\Game\\ArtRes\\ArtEffectRes.csv";
		config.effectComponentDeclFileName  = "Config\\Game\\ArtRes\\ArtEffectComponentRes.csv";
		config.waterEffectDeclFileName      = "Config\\Game\\ArtRes\\WaterEffectResource.csv";
		config.grassEffectDeclFileName      = "Config\\Game\\ArtRes\\GrassEffectResource.csv";
		config.terrainTextureDeclFileName   = "Config\\Game\\ArtRes\\TerrainTexture.xml";
		config.treeResourceFileName         = "Config\\Game\\ArtRes\\TreeResource.csv";
		config.grassResourceFileName        = "Config\\Game\\ArtRes\\GrassResource.csv";

		config.windowsHandle                = WindowSet::main_win->getHandle();
		config.inputHandle					= WindowSet::main_win->getInputHandle();

		config.windowName                   = "EffectEditor"; 
		config.screenWidth                  = WindowSet::main_win->getWidth();
		config.screenHeight                 = WindowSet::main_win->getHeight() ;
		config.isFullScreen                 = false;

		config.fsaa							= 0;
		config.isVsync						= false;

		config.packManager					= NULL;

		if ( mEngineMain->initialize( &config ) == false )
			return false;

		AddObjectTabDialog::getInstance().initList();

		//设置区域显示
		mEngineMain->display()->setTerrainRegionDisplayEnabled( true );

		//@创建场景
		mMainScene  = mEngineMain->createScene("EffectEditorManager","EffectCamera");

		mMainScene->createEffectGrid();
		initScene();
		return true;
	}
	//-----------------------------------------------------------------------
	void CoreManager::clearScene()
	{
		// 删除所有场景
		mEngineMain->destroyAllScene();

		WindowSet::main_win->clear();
	}
	//-----------------------------------------------------------------------
	void CoreManager::initScene(Str name)
	{
		mEngineMain->setMode(EM_EDITOR);
		//clearScene();
		IEffectComponent* component = NULL;
		if (!name.empty())
			component = mMainScene->createEmptyEffectComponent(name.c_str());
		else
			component = mMainScene->createEmptyEffectComponent();

		mComponentMap[component->getName()] = component;
		WindowSet::main_win->getExComponentWidget()->addNameToList(component->getName());
		setCurrentComponent(component->getName());
		
		component->getEffectXmlSerializer()->createEffectComponentFormat();

		//设置摄像机控制方式
		OperationManager::getInstance().revertCamera();

		ICamera* camera = mMainScene->getActiveCamera();
		camera->getSceneNode()->setPosition(Vec3(0, 2, -8));
		camera->getSceneNode()->setDirection(Vec3(0, 0, 1));
		// 设置光照

		ILight* light = mMainScene->getLight( "SpotLight" );

		if ( !light )
			light = mMainScene->createLight( "SpotLight" );

		if ( light )
		{
			Vec3 lightPos;

			light->setLightType(ILight::LT_DIRECTIONAL);
			light->getSceneNode()->setPosition(Vec3(0, 80, 0));
			light->getSceneNode()->setDirection(Vec3(0.0f,-1.0f,0.0f));
			light->setDiffuseColour(COLOR_WHITE);
			mMainScene->setAmbientLight(COLOR_WHITE);
		}
	}
	//-----------------------------------------------------------------------
	void CoreManager::setDisplayMode( U32 width, U32 height )
	{
		if (!mEngineMain)
			return;

		IDisplay* display = mEngineMain->display();
		if (display)
		{
			display->setVideoMode(false, width, height, true);
		}
	}
	//-----------------------------------------------------------------------
	Bool CoreManager::unLoadEngine()
	{
		Bool result = false;

		if ( mEngineMain )
		{
			result = mEngineMain->uninitialize();
		}

		return result;
	}
	//-----------------------------------------------------------------------
	IScene* CoreManager::getScene()
	{
		return mMainScene;
	}
	//-----------------------------------------------------------------------
	IEngineMain* CoreManager::getEngineMain()
	{
		return mEngineMain;
	}   
	//-----------------------------------------------------------------------
	IEffectComponent* CoreManager::getCurEffectComponent()
	{
		return mCurrentComponent;
	}
	//-----------------------------------------------------------------------
	IEffectComponent* CoreManager::getEffectComponent( Str name )
	{
		ComponentMap::iterator iter = mComponentMap.find(name);
		if ( iter != mComponentMap.end() )
		{
			return iter->second;
		}
		return NULL;
	}
	//-----------------------------------------------------------------------
	void CoreManager::destoryEffectComponent( Str name )
	{
		ComponentMap::iterator iter = mComponentMap.begin();
		for ( ; iter != mComponentMap.end(); iter++)
		{
			if ( StrCmp((iter->first).c_str(), name.c_str()) == 0)
			{
				mMainScene->destroyEffectComponent(name.c_str());
				mComponentMap.erase(iter);
				if (mComponentMap.size() < 1)
					mCurrentComponent = NULL;
				return;
			}
		}
	}
	//-----------------------------------------------------------------------
	void CoreManager::setCurrentComponent( Str name )
	{
		// 设置当前Component.
		mCurrentComponent = getEffectComponent(name.c_str());

		if (!mCurrentComponent)
			return;

		setEntityList();
		setEffectList();
		setEventMap();
	}
	//-----------------------------------------------------------------------
	void CoreManager::setEntityList()
	{
		std::list<Str> list;
		
		EntityMap entitymap = mCurrentComponent->getModelEffectMap();
		EntityMap::iterator iter = entitymap.begin();
		for (; iter != entitymap.end(); iter++)
		{
			list.push_back(iter->first);
		}
		
		WindowSet::main_win->getExComponentWidget()->getEntityWidget()->setEntityList(list);
	}
	//-----------------------------------------------------------------------
	void CoreManager::setEffectList()
	{
		std::list<Str> list;

		PUEffectMap effectmap = mCurrentComponent->getPUEffectMap();
		PUEffectMap::iterator iter = effectmap.begin();
		for (; iter != effectmap.end(); iter++)
		{
			list.push_back(iter->first);
		}

		WindowSet::main_win->getExComponentWidget()->getEffectWidget()->setEffectList(list);
	}
	//-----------------------------------------------------------------------
	void CoreManager::setEventMap()
	{
		std::map<Str, Str> returnmap;

		std::list<IEffectEvent*> eventList = mCurrentComponent->getTimeEventList();
		std::list<IEffectEvent*>::iterator iter = eventList.begin();
		for (; iter != eventList.end(); iter++)
		{
			IEffectEvent* event = (*iter);
			returnmap[event->getName()] = event->getEventName();
		}
		
		WindowSet::main_win->getExComponentWidget()->getEventWidget()->setEventMap(returnmap);
	}
	//-----------------------------------------------------------------------
	Bool CoreManager::loadGameFile()
	{
		unLoadGameFile();

		return true;
	}
	//-----------------------------------------------------------------------
	Bool CoreManager::unLoadGameFile()
	{
		return true;
	}

}


