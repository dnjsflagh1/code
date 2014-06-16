/******************************************************************************/
#include "StdAfx.h"
#include "CoreManager.h"
#include "GlobalOptions.h"
#include "OperationManager.h"
#include "CharacterList.h"
#include "CharacterArmyList.h"
#include "CharacterBuildList.h"
#include "CharacterGenrealList.h"
#include "CharacterNpcList.h"
#include "CharacterObjectList.h"
#include "CharacterMonsterList.h"
#include "DialogueVassal.h"
#include "PointTemplate.h"
#include "TroopTemplate.h"
#include "ArtMapResCsv.h"
#include "PlaceListCsv.h"
#include "GameCameraConfig.h"

//#include "MapObjectInfo.h"
//#include "PlaceObjectInfo.h"
//#include "DistrictObjectInfo.h"
//#include "PlaceTemplateInfo.h"
//#include "DistrictTemplateInfo.h"
//#include "MapResourceInfo.h"
//#include "MapAreaObjectInfo.h"
/******************************************************************************/


namespace GameMapEditor {

    //-----------------------------------------------------------------------
    CoreManager::CoreManager()
        :mEngineMain(NULL)
        ,mStopUpdateDirty(false)
        ,mMainScene(NULL)
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
        FormSet::main_form->Show();
        FormSet::scene_form->Show();
        FormSet::main_form->initialize();
		FormSet::mapload_form->initialize();

        mCurrUpdateTicks = GetTickCount() * 0.001;
        mLastUpdateTicks = mCurrUpdateTicks;
        mUpdateDelta = 0.0;
        while( mStopUpdateDirty == false )
        {
            //System::Windows::Forms::Application::DoEvents();
            if ( FormSet::main_form->Visible == false )
                break;

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

        FormSet::main_form->update();

        OperationManager::getInstance().update( delta );

		mEngineMain->render( (Flt)delta );

        return true;
    }
    //-----------------------------------------------------------------------
    Bool CoreManager::loadForm()
    {
        // Initialize Window
        //// Enabling Windows XP visual effects before any controls are created
        System::Windows::Forms::Application::EnableVisualStyles();
        System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false); 

		FormSet::scene_form	= gcnew SceneForm();
        FormSet::main_form  = gcnew MainForm();
		FormSet::mapload_form = gcnew MapLoadForm();

        FormSet::main_form->CreateControl();
        FormSet::scene_form->CreateControl();
		FormSet::mapload_form->CreateControl();

        FormSet::main_form->AddOwnedForm( FormSet::scene_form );
        
        return true;
    }
    //-----------------------------------------------------------------------
    Bool CoreManager::unLoadForm()
    {


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
        config.resFileName                  = "EditorData\\ResourcesPathSetting.cfg";

		config.logFileName                  = "Log\\EngineCore.log";

        config.modelDeclFileName            = "Config\\Game\\ArtRes\\ArtModelRes.csv";
        config.accessoryDeclFileName        = "Config\\Game\\ArtRes\\EntityAccessoryDeclaration.csv";
        config.effectDeclFileName           = "Config\\Game\\ArtRes\\ArtEffectRes.csv";
		config.effectComponentDeclFileName  = "Config\\Game\\ArtRes\\ArtEffectComponentRes.csv";
        config.waterEffectDeclFileName      = "Config\\Game\\ArtRes\\WaterEffectResource.csv";
        config.grassEffectDeclFileName      = "Config\\Game\\ArtRes\\GrassEffectResource.csv";
        config.terrainTextureDeclFileName   = "Config\\Game\\ArtRes\\TerrainTexture.xml";
        config.treeResourceFileName         = "Config\\Game\\ArtRes\\TreeResource.csv";
        config.grassResourceFileName        = "Config\\Game\\ArtRes\\GrassResource.csv";

		config.windowsHandle                = (HWND)FormSet::scene_form->Handle.ToInt32();
		config.windowName                   = "GameMapEditor"; 
		config.screenWidth                  = 1024;
		config.screenHeight                 = 768 ;
		config.isFullScreen                 = false;

		config.fsaa							= 0;
		config.isVsync						= false;

		config.packManager					= NULL;

		// 编辑模式
		mEngineMain->setMode( EM_EDITOR );

		if ( mEngineMain->initialize( &config ) == false )
			return false;

		//设置区域显示
		mEngineMain->display()->setTerrainRegionDisplayEnabled( true );

		//@创建场景
		mMainScene  = mEngineMain->createScene("MainSceneManager","MainCamera");
		mMainScene->getXmlSerializer()->createSceneContent();

		initScene();

		return true;
    }
    //-----------------------------------------------------------------------
    void CoreManager::initScene()
    {
        //设置摄像机控制方式
        OperationManager::getInstance().revertCamera();
        mMainScene->getSceneObjectController()->setEnable( true );

		//设置资源监听
		mMainScene->setResourceSaveListener(&OperationManager::getInstance());
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
    Bool CoreManager::loadGameFile()
    {
        unLoadGameFile();
		
		CharacterArmyList::getInstance();
		CharacterBuildList::getInstance();
		CharacterGenrealList::getInstance();
		CharacterNpcList::getInstance();
		CharacterObjectList::getInstance();
		CharacterMonsterList::getInstance();
		CharacterTemplate::getInstance();
		PointTemplate::getInstance();
		ArtMapResCsv::getInstance();
		PlaceListCsv::getInstance();
		MapListCsv::getInstance();
		GameCameraConfig::getInstance();
        DialogueVassal::getInstance();

        //ADD:
        //NPC Building Map Place Point 表的加载

		if ( CharacterArmyList::getInstance().loadFile(L"Config\\Game\\Character\\CharacterArmyList.csv") == false )
			return false;
		if ( CharacterBuildList::getInstance().loadFile(L"Config\\Game\\Character\\CharacterBuildList.csv") == false )
			return false;
		if ( CharacterGenrealList::getInstance().loadFile(L"Config\\Game\\Character\\\\CharacterGeneralList.csv") == false )
			return false;
		if ( CharacterNpcList::getInstance().loadFile(L"Config\\Game\\Character\\CharacterNpcList.csv") == false )
			return false;
		if ( CharacterObjectList::getInstance().loadFile(L"Config\\Game\\Character\\CharacterObjectList.csv") == false )
			return false;
		if ( CharacterMonsterList::getInstance().loadFile(L"Config\\Game\\Character\\CharacterMonsterList.csv") == false )
			return false;
		if ( CharacterTemplate::getInstance().loadFile(L"Config\\Game\\Character\\CharacterList.csv") == false )
			return false;

		if ( PointTemplate::getInstance().load(L"Config\\Game\\ArtRes\\ArtPointRes.csv") == false )
			return false;
		if ( ArtMapResCsv::getInstance().load(L"Config\\Game\\ArtRes\\ArtMapRes.csv") == false )
			return false;
        if ( GameCameraConfig::getInstance().load(L"Config\\Game\\ArtRes\\CameraSetList.csv") == false )
            return false;

		if ( PlaceListCsv::getInstance().load(L"Config\\Game\\World\\PlaceList.csv") == false )
			return false;
		if ( MapListCsv::getInstance().load(L"Config\\Game\\World\\MapList.csv") == false )
			return false;

        return true;
    }
    //-----------------------------------------------------------------------
    Bool CoreManager::unLoadGameFile()
    {
        return true;
    }
}

