/******************************************************************************/
#include "StdAfx.h"
#include "CoreManager.h"
#include "GlobalOptions.h"
#include "OperationManager.h"
/******************************************************************************/


namespace ParticleEditor {

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
        config.logFileName                  = "Log\\EngineCore.log";
        config.modelDeclFileName            = "Config\\Resource\\ModelResource.csv";
		config.accessoryDeclFileName        = "Config\\Resource\\EntityAccessoryDeclaration.csv";
        config.terrainTextureDeclFileName   = "Config\\Resource\\TerrainTexture.xml";

		config.effectDeclFileName			= "Config\\Resource\\EffectResource.csv";
		config.waterEffectDeclFileName		= "Config\\Resource\\WaterEffectResource.csv";
		config.grassEffectDeclFileName		= "Config\\Resource\\GrassEffectResource.csv";

        config.resFileName                  = "EditorData\\ResourcesPathSetting.cfg";
        
        config.windowsHandle                = (HWND)FormSet::scene_form->Handle.ToInt32();
        config.windowName                   = "ParticleEditor"; 
        config.screenWidth                  = 1024;
        config.screenHeight                 = 768 ; 
        config.isFullScreen                 = false;
        
        if ( mEngineMain->initialize( config ) == false )
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

