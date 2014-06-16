/******************************************************************************/
#include "StdAfx.h"
#include "CoreManager.h"
#include "GlobalOptions.h"
#include "OperationManager.h"
#include "AppDataConfig.h"
#include "Utility.h"
//#include "MapObjectInfo.h"
//#include "PlaceObjectInfo.h"
//#include "DistrictObjectInfo.h"
//#include "PlaceTemplateInfo.h"
//#include "DistrictTemplateInfo.h"
//#include "MapResourceInfo.h"
//#include "MapAreaObjectInfo.h"
/******************************************************************************/


namespace SceneEditor {

    //-----------------------------------------------------------------------
    CoreManager::CoreManager()
        :mEngineMain(NULL)
        ,mStopUpdateDirty(false)
        ,mMainScene(NULL)
		,mMapObjInfoList(NULL)
		,mPlaceObjInfoList(NULL)
    {
    }
    //-----------------------------------------------------------------------
    CoreManager::~CoreManager()
    {
		
    }
    //-----------------------------------------------------------------------
    Bool CoreManager::initialize()
    {
		std::string name = "SEConfig.ini";
		System::String^ appDataPath = System::Environment::GetFolderPath(System::Environment::SpecialFolder::ApplicationData);
		AppDataManager::getInstance()->loadFromFile(name,StrToChar8(appDataPath).getChar8());

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
		//保存配置
		System::String^ appDataPath = System::Environment::GetFolderPath(System::Environment::SpecialFolder::ApplicationData);
		AppDataManager::getInstance()->saveToFile("SEConfig.ini",StrToChar8(appDataPath).getChar8());

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

        FormSet::main_form->CreateControl();
        FormSet::scene_form->CreateControl();

        FormSet::main_form->AddOwnedForm( FormSet::scene_form );

		//设置上次打开文件目录
		std::string str = AppDataManager::getInstance()->getMapFilePath();
		if (!str.empty())
		{
			System::String^ mapFilePath = TypeConverter::Char8ToStr(str.c_str());
			FormSet::main_form->mLastFocusDir = mapFilePath;
		}
        
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
        config.waterEffectDeclFileName	    = "Config\\Game\\ArtRes\\WaterEffectResource.csv";
        config.grassEffectDeclFileName	    = "Config\\Game\\ArtRes\\GrassEffectResource.csv";
        config.terrainTextureDeclFileName   = "Config\\Game\\ArtRes\\TerrainTexture.xml";
        config.treeResourceFileName         = "Config\\Game\\ArtRes\\TreeResource.csv";
        config.grassResourceFileName        = "Config\\Game\\ArtRes\\GrassResource.csv";

        config.windowsHandle                = (HWND)FormSet::scene_form->Handle.ToInt32();
        config.windowName                   = "SceneEditor"; 
        config.screenWidth                  = 1024;
        config.screenHeight                 = 768 ; 
        config.isFullScreen                 = false;

		config.fsaa							= 4;
		config.isVsync						= false;

		config.packManager					= NULL;


		// 编辑模式
		mEngineMain->setMode( EM_EDITOR );

        if ( mEngineMain->initialize( &config ) == false )
            return false;

        //设置区域显示
        mEngineMain->display()->setTerrainRegionDisplayEnabled( true );

		//设置是否启用光照贴图
		bool enable = AppDataManager::getInstance()->isLightMapEnbale();
		mEngineMain->display()->setTerrainLightmapEnabled(enable);

		//设置阴影类型和是否显示阴影
		unsigned int type = AppDataManager::getInstance()->getShadowType();
		mEngineMain->display()->setShadowType((MG::ShadowType)type);
		bool receive = AppDataManager::getInstance()->isReceiveShadow();
		mEngineMain->display()->setTerrainReceiveDynamicShadowsEnabled(receive);

		//设置雾等级
		UInt level = AppDataManager::getInstance()->getFogLevel();
		mEngineMain->display()->setFogLevel((MG::FogLevel)level);

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

		//使设置生效
		mEngineMain->display()->apply();
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

		//mMapObjInfoList = new std::map<IdType, MapObjectInfo*>;
		//mPlaceObjInfoList = new std::map<IdType, PlaceObjectInfo*>;

		//MapObjectInfos::getInstance().loadFile(L"Config\\World\\MapObject.csv", NULL, mMapObjInfoList, LFT_EDIT);
		//DistrictInfos::getInstance().loadFile(L"Config\\World\\DistrictTemplate.csv");
		//DistrictObjectInfos::getInstance().loadFile(L"Config\\World\\DistrictObject.csv", LFT_EDIT);
		//PlaceTemplateInfos::getInstance().loadFile(L"Config\\World\\CityTemplate.csv");
		//PlaceObjectInfos::getInstance().loadFile(L"Config\\World\\CityObject.csv", NULL, mPlaceObjInfoList, LFT_EDIT);
		//MapResourceInfos::getInstance().loadFile(L"Config\\World\\ArtMapRes.csv");
		
        return true;
    }
    //-----------------------------------------------------------------------
    Bool CoreManager::unLoadGameFile()
    {
        return true;
    }
}

