/******************************************************************************/
#include "stdafx.h"
#include "GameSettingManager.h"
#include "GameSettingConfig.h"
#include "ClientMain.h"
#include "GameSoundManager.h"
#include "CSceneManager.h"
/******************************************************************************/

namespace MG
{
	//-------------------------------------------------------------------------------
	GameSettingManager::GameSettingManager()
	{
		mIsLoad = false;
		mEngineInitConfig = MG_NEW EngineInitConfig;
	}
	//-------------------------------------------------------------------------------
	GameSettingManager::~GameSettingManager()
	{
		removeAllListeners();

		MG_SAFE_DELETE(mEngineInitConfig);
	}
	//-------------------------------------------------------------------------------
	// MG_CN_MODIFY
	Bool GameSettingManager::initialize( CChar16* configFileName )
	{
		IMGExternalPackManager* mgExPackManager = ClientMain::getInstance().getMGPackManager();
		mIsLoad = GameSettingConfig::getInstance().load(configFileName, mgExPackManager);
		return mIsLoad;
	}
	//-------------------------------------------------------------------------------
	Bool GameSettingManager::resetInitConfig()
	{
		IEngineMain* engine = ClientMain::getInstance().getEngine();
		if ( !engine )
			return false;

		if ( engine->display() )
		{
			IDisplay* display = engine->display();

			//恢复显示数据
			setVsync(display->getVsync());
			setFSAA(display->getFSAA(), display->getFSAAHint());

			Bool isFullScreen = false;
			U32 width = 0, height = 0;
			display->getVideoMode(isFullScreen, width, height);
			setVideoMode(isFullScreen, width, height);
		}
		return true;
	}
	//-------------------------------------------------------------------------------
	Bool GameSettingManager::restoreInitConfig()
	{
		if ( !mIsLoad )
			return false;

		if ( !restoreEngineInitConfig() )
			return false;

		return true;
	}
	//-------------------------------------------------------------------------------
	void GameSettingManager::restoreRuningConfig()
	{
		IEngineMain* engine = ClientMain::getInstance().getEngine();
		if ( !engine ) 
			return;

        // 加载场景的时候调用
		//applyDisplayConfig( true );

		applyAllAudioConfig();
	}
	//-------------------------------------------------------------------------------
	Bool GameSettingManager::restoreEngineInitConfig()
	{
		//默认值
		//////////////////////////////////////////////////////////////////////////////////////
		if ( !mEngineInitConfig )
			return false;
#ifdef _DEBUG
		mEngineInitConfig->pluginFileName                = "Config\\Engine\\Plugins_d.cfg";
#else
		mEngineInitConfig->pluginFileName                = "Config\\Engine\\Plugins.cfg";
#endif
		mEngineInitConfig->configFileName                = "Config\\Engine\\DisplaySetting.cfg";
        mEngineInitConfig->resFileName                   = "Config\\Engine\\ResourcesPathSetting.cfg";

		mEngineInitConfig->logFileName                   = "Log\\EngineCore.log";

		mEngineInitConfig->modelDeclFileName             = "Config\\Game\\ArtRes\\ArtModelRes.csv";
		mEngineInitConfig->accessoryDeclFileName         = "Config\\Game\\ArtRes\\EntityAccessoryDeclaration.csv";
		mEngineInitConfig->effectDeclFileName            = "Config\\Game\\ArtRes\\ArtEffectRes.csv";
		mEngineInitConfig->effectComponentDeclFileName   = "Config\\Game\\ArtRes\\ArtEffectComponentRes.csv";
		mEngineInitConfig->waterEffectDeclFileName	     = "Config\\Game\\ArtRes\\WaterEffectResource.csv";
		mEngineInitConfig->grassEffectDeclFileName	     = "Config\\Game\\ArtRes\\GrassEffectResource.csv";
		mEngineInitConfig->terrainTextureDeclFileName    = "Config\\Game\\ArtRes\\TerrainTexture.xml";
        mEngineInitConfig->treeResourceFileName          = "Config\\Game\\ArtRes\\TreeResource.csv";
        mEngineInitConfig->grassResourceFileName         = "Config\\Game\\ArtRes\\GrassResource.csv";


		mEngineInitConfig->windowsHandle                 = 0;
		mEngineInitConfig->windowName                    = "MG"; 
		mEngineInitConfig->screenWidth                   = 1024;
		mEngineInitConfig->screenHeight                  = 768 ; 
		mEngineInitConfig->isFullScreen                  = false;
		mEngineInitConfig->fsaa						    = 0;
		mEngineInitConfig->isVsync					    = false;
		
		// MG_CN_MODIFY
		mEngineInitConfig->packManager					= ClientMain::getInstance().getPackManager();

		//////////////////////////////////////////////////////////////////////////////////////

		//获得修正值
		//全屏
		getVideoMode(mEngineInitConfig->isFullScreen, mEngineInitConfig->screenWidth, mEngineInitConfig->screenHeight);
		//垂直同步
		getVsync(mEngineInitConfig->isVsync);
		//反锯齿
		getFSAA(mEngineInitConfig->fsaa, mEngineInitConfig->fsaaHint);

		return true;
	}
	//-------------------------------------------------------------------------------
	void GameSettingManager::saveConfig()
	{
		//GameSettingConfig::getInstance().clear();
		GameSettingConfig::getInstance().save();
	}

    //-------------------------------------------------------------------------------
    void GameSettingManager::applyHardwareConfig()
    {
        applyVsync();
        applyFSAA();
        applyVideoMode();	
    }

    //-------------------------------------------------------------------------------
    void GameSettingManager::applyDisplayConfig( Bool isImme )
    {
        applyPostFx();
        applyShadowLevel();
        applyMaterialLevel();
        applyFog();

        applyUseHighLevelModel();
        applyUseHighLevelTexture();
        applyUseDetailTerrainObject();
        applyParticleLevel();
        applyUseWaterReflection();

        // 是否立即响应
        if ( isImme )
        {
            IEngineMain* engine = ClientMain::getInstance().getEngine();
            if ( engine )
            {
                IDisplay* display = engine->display();
                if ( display )
                    display->apply();
            }
        }

		// 通知所有监听者
		notifyApplyDisplayConfig();
    }

	//-------------------------------------------------------------------------------
	Bool GameSettingManager::getVideoModeList(std::vector<VecI2>& reslist)
	{
		IEngineMain* engineMain = ClientMain::getInstance().getEngine();
		if ( !engineMain )
			return false;

		return engineMain->display()->getVideoModeList(reslist);
	}
	//-------------------------------------------------------------------------------
	Bool GameSettingManager::getVideoMode(Bool& isFullScreen, U32& width, U32& height )
	{
		Bool result = false;
		U32 w = 0, h = 0;
		U32 rlt = 0;
		Str16 str = GameSettingConfig::getInstance().getSettingProperty(GAME_SETTING_SECTION_DISPLAY, DISPLAY_SETTING_RESOLUTION);
		if ( !str.empty() )
		{
			//正确的格式类似“1280x768” 或者 “1280X768”
			size_t pos = str.find_first_of(L"x");
			if ( pos == std::wstring::npos )
				pos = str.find_first_of(L"X");

			if ( pos != std::wstring::npos )
			{
				if ( MGStrOp::toU32(str.substr(0, pos).c_str(), w ) &&
					MGStrOp::toU32(str.substr(pos+1).c_str(), h ) )
				{
					if ( MGStrOp::toU32(GameSettingConfig::getInstance().getSettingProperty(GAME_SETTING_SECTION_DISPLAY, DISPLAY_SETTING_FULLSCREEN).c_str(), rlt) )
					{
						result = true;
					}
				}
			}
		}

		if ( result )
		{
			width = w;
			height = h;
			isFullScreen = (rlt != 0);
		}

		return result;
	}
	//-------------------------------------------------------------------------------
	void GameSettingManager::setVideoMode( Bool isFullScreen, U32 width, U32 height )
	{
		wchar_t res[16];
		ZeroMemory(res, sizeof(res));
		swprintf_s( res, _countof(res), L"%dx%d", width, height);
		GameSettingConfig::getInstance().setSettingProperty(GAME_SETTING_SECTION_DISPLAY, DISPLAY_SETTING_RESOLUTION, Str16(res));
	
		Str16 str;
		MGStrOp::toString(isFullScreen, str);
		GameSettingConfig::getInstance().setSettingProperty(GAME_SETTING_SECTION_DISPLAY, DISPLAY_SETTING_FULLSCREEN, str);
	}
	//-------------------------------------------------------------------------------
	void GameSettingManager::applyVideoMode()
	{
		U32 width = 0;
		U32 height = 0;
		Bool isFullScreen = 0;

		getVideoMode(isFullScreen, width, height);

		IEngineMain* engine = ClientMain::getInstance().getEngine();
		if ( !engine || !engine->display() )
			return;

		IDisplay* display = engine->display();
		display->setVideoMode(isFullScreen, width, height, true);
				
		//设置视屏模式的时候， display会把输入的值合法化， 
		//合法化之后的值可能和原来的值不一样，所以要重新把正确的值
		//返还给GamesettingManager.
		if ( display->getVideoMode( isFullScreen, width, height ) )
		{
			setVideoMode(isFullScreen, width, height);
		}	
	}
	//-------------------------------------------------------------------------------
	Bool GameSettingManager::getVsync( Bool& isVsync )
	{
		I32 rlt = 0;
		if ( MGStrOp::toI32( GameSettingConfig::getInstance().getSettingProperty(GAME_SETTING_SECTION_DISPLAY, DISPLAY_SETTING_VSYNC).c_str(), rlt ) )
		{
			isVsync = ( rlt != 0 );
			return true;
		}
		return false;
	}
	//-------------------------------------------------------------------------------
	void GameSettingManager::setVsync( Bool isVsync )
	{
		Str16 result;
		MGStrOp::toString((U32)isVsync, result);
		GameSettingConfig::getInstance().setSettingProperty(GAME_SETTING_SECTION_DISPLAY, DISPLAY_SETTING_VSYNC, result);
	}
	//-------------------------------------------------------------------------------
	void GameSettingManager::applyVsync()
	{
		Bool isVsync = false;
		getVsync(isVsync);

		//TODO
		//重设垂直同步
		IEngineMain* engineMain = ClientMain::getInstance().getEngine();
		if ( !engineMain || !engineMain->display() )
			return;

		IDisplay* display = engineMain->display();
		display->setVsync(isVsync);

		if ( isVsync )
			display->setVsyncInterval(0);
		else
			display->setVsyncInterval(1);

		setVsync(display->getVsync());
	}
	//-------------------------------------------------------------------------------
	Bool GameSettingManager::getFSAAList( std::vector<FSAA_MODE>& outFsaaList )
	{
		IEngineMain* engineMain = ClientMain::getInstance().getEngine();
		if ( !engineMain || !engineMain->display() )
			return false;

		std::vector<std::pair<U32, Str>> displayFsaaList;
		if ( !engineMain->display()->getFSAAList(displayFsaaList) || displayFsaaList.size() == 0 )
			return false;

		outFsaaList.resize(displayFsaaList.size());

		for ( U32 i = 0; i < outFsaaList.size(); i++ )
		{
			MG::MGStrOp::toString(displayFsaaList[i].first, outFsaaList[i].FSAA_SAMPLE );
			MG::MGStrOp::toString(displayFsaaList[i].second.c_str(), outFsaaList[i].FSAA_HINT );

			if ( outFsaaList[i].FSAA_HINT.size() == 1 )
				outFsaaList[i].FSAA_HINT.clear();
		}

		return true;
	}
	//-------------------------------------------------------------------------------
	Bool GameSettingManager::getFSAA( U32& fsaa, Str8& fsaaHint )
	{
		fsaa = 0;
		fsaaHint.clear();

		Str16 wfsaaSample;
		Str16 wfsaaHint;

		fromFSAAIniInfo(GameSettingConfig::getInstance().getSettingProperty(GAME_SETTING_SECTION_DISPLAY, DISPLAY_SETTING_FSAA), 
			wfsaaSample, wfsaaHint);

		MGStrOp::toU32( wfsaaSample.c_str(), fsaa );
		MGStrOp::toString( wfsaaHint.c_str(), fsaaHint );

		return true;
	}
	//-------------------------------------------------------------------------------
	Bool GameSettingManager::getFSAA( Str16& fsaa, Str16& fsaaHint )
	{
		fsaa.clear();
		fsaaHint.clear();

		fromFSAAIniInfo(GameSettingConfig::getInstance().getSettingProperty(GAME_SETTING_SECTION_DISPLAY, DISPLAY_SETTING_FSAA), 
			fsaa, fsaaHint);
		
		return !fsaa.empty();
	}
	//-------------------------------------------------------------------------------
	void GameSettingManager::setFSAA( Str16 fsaa, Str16 FsaaHint )
	{
		GameSettingConfig::getInstance().setSettingProperty(GAME_SETTING_SECTION_DISPLAY, DISPLAY_SETTING_FSAA, toFSAAIniInfo(fsaa, FsaaHint));
	}
	//-------------------------------------------------------------------------------
	void GameSettingManager::setFSAA( U32 fsaa, Str8 szFsaaHint )
	{
		Str16 wszFSAA;
		Str16 wszFSAAHint;

		MGStrOp::toString(fsaa, wszFSAA);
		MGStrOp::toString(szFsaaHint.c_str(), wszFSAAHint);
	
		GameSettingConfig::getInstance().setSettingProperty(GAME_SETTING_SECTION_DISPLAY, DISPLAY_SETTING_FSAA, toFSAAIniInfo(wszFSAA, wszFSAAHint));
	}
	//-------------------------------------------------------------------------------
	void GameSettingManager::applyFSAA()
	{
		//获取存储的fsaa信息
		U32 fsaaSample = 0;
		Str fsaaHint;
		Str16 wfsaaSample;
		Str16 wfsaaHint;
		
		getFSAA(wfsaaSample, wfsaaHint);
		
		//TODO
		//重新设置FSAA
		IEngineMain* engineMain = ClientMain::getInstance().getEngine();
		if ( engineMain && engineMain->display() )
		{
			IDisplay* display = engineMain->display();

			//设置fsaa和fsaaHint
			MGStrOp::toU32(wfsaaSample.c_str(), fsaaSample);
			MGStrOp::toString(wfsaaHint.c_str(), fsaaHint);

			display->setFSAA(fsaaSample, fsaaHint);

			//因为这个值有可能会被修正，返回修正后的值
			//修正GameSettingManager的值
			fsaaSample = display->getFSAA();
			fsaaHint = display->getFSAAHint();

			MGStrOp::toString(fsaaSample, wfsaaSample);
			MGStrOp::toString(fsaaHint.c_str(), wfsaaHint);
		}
		
		setFSAA(wfsaaSample, wfsaaHint);
	}
	//-------------------------------------------------------------------------------
	Str16 GameSettingManager::toFSAAIniInfo(Str16 fsaa, Str16 fsaaHint)
	{
		if ( fsaa.compare(L"\0") == 0 )
			fsaa.clear();

		if ( fsaaHint.size() == 1 )
			fsaaHint.clear();

		wchar_t outString[32] = {0};

		if ( !fsaa.empty() && !fsaaHint.empty() )
		{
			swprintf_s(outString, _countof(outString), L"%s(%s)", fsaa.c_str(), fsaaHint.c_str());
		}
		else if ( !fsaa.empty() && fsaaHint.empty() )
		{
			swprintf_s(outString, _countof(outString), L"%s", fsaa.c_str());
		}
		else
		{
			swprintf_s(outString, _countof(outString), L"%d", 0);
		}

		return Str16(outString);
	}
	//-------------------------------------------------------------------------------
	void GameSettingManager::fromFSAAIniInfo(const Str16& fsaaInfo, Str16 &outFsaa, Str16 &outFsaaHint)
	{
		outFsaa.clear();
		outFsaaHint.clear();

		if ( fsaaInfo.empty() )
			return;

		size_t splitPos = fsaaInfo.find_first_of(L'(');
		outFsaa = fsaaInfo.substr(0, splitPos);

		size_t left_trim = outFsaa.find_first_not_of(L' ');
		outFsaa.erase( 0, left_trim );

		size_t right_trim = outFsaa.find_last_not_of(L' ');
		if ( right_trim != Str16::npos )
			outFsaa.erase( right_trim + 1);

		if ( splitPos != Str16::npos )
		{
			outFsaaHint = fsaaInfo.substr(splitPos);

			left_trim = outFsaaHint.find_last_of(L'(');
			outFsaaHint.erase( 0, left_trim + 1 );
			
			right_trim = outFsaaHint.find_first_of(L')');
			if ( right_trim != Str16::npos )
				outFsaaHint.erase( right_trim );
		}
	}
	//-------------------------------------------------------------------------------
	Bool GameSettingManager::getPostFx( post_fx_level& level )
	{
		U32 rlt = 0;
		if ( MGStrOp::toU32( GameSettingConfig::getInstance().getSettingProperty(GAME_SETTING_SECTION_DISPLAY, DISPLAY_SETTING_POST_FX_LEVEL).c_str(), rlt ) )
		{
			level = (post_fx_level)rlt;
			if ( level > POST_FX_HIGH )
				level = POST_FX_NONE;
			return true;
		}
		return false;
	}
	//-------------------------------------------------------------------------------
	void GameSettingManager::setPostFx( post_fx_level level )
	{
		Str16 result;
		MGStrOp::toString((U32)level, result);
		GameSettingConfig::getInstance().setSettingProperty(GAME_SETTING_SECTION_DISPLAY, DISPLAY_SETTING_POST_FX_LEVEL, result);
	}
	//-------------------------------------------------------------------------------
	void GameSettingManager::applyPostFx()
	{
		post_fx_level level = POST_FX_NONE;
		getPostFx(level);
		
		IScene* scene =	ClientMain::getInstance().getScene();
		if ( scene )
		{
			if ( level == POST_FX_NONE )
			{
				scene->getCompositorManager()->setCompositorEnable( "MG_POST_BLOOM", false );
			}
			else
			{
				scene->getCompositorManager()->setCompositorEnable( "MG_POST_BLOOM", true );
			}
		}

		setPostFx(level);
	}
	//-------------------------------------------------------------------------------
	Bool GameSettingManager::getShadowLevel(shadow_level& level)
	{
		U32 rlt = 0;
		if ( MGStrOp::toU32( GameSettingConfig::getInstance().getSettingProperty(GAME_SETTING_SECTION_DISPLAY, DISPLAY_SETTING_SHADOW_LEVEL).c_str(), rlt ) )
		{
			level = (shadow_level)rlt;
			if ( level > SHADOW_LEVEL_HIGH )
				level = SHADOW_LEVEL_NONE;
			return true;
		}
		return false;
	}
	//-------------------------------------------------------------------------------
	void GameSettingManager::setShadowLevel(shadow_level level)
	{
		Str16 result;
		MGStrOp::toString((U32)level, result);
		GameSettingConfig::getInstance().setSettingProperty(GAME_SETTING_SECTION_DISPLAY, DISPLAY_SETTING_SHADOW_LEVEL, result);
	}
	//-------------------------------------------------------------------------------
	void GameSettingManager::applyShadowLevel()
	{
		shadow_level level = SHADOW_LEVEL_NONE;
		getShadowLevel(level);

		IEngineMain* engine =	ClientMain::getInstance().getEngine();
		if ( !engine )
			return;

		IDisplay* display = engine->display();
		if ( display )
		{
			if ( level == SHADOW_LEVEL_NONE )
			{
				display->setShadowType(SCL_NONE);
				display->setTerrainReceiveDynamicShadowsEnabled(false);
				display->setTerrainLightmapEnabled(false);
			}
			else if ( level == SHADOW_LEVEL_LOW )
			{
				display->setShadowType(SCL_NONE);
				display->setTerrainReceiveDynamicShadowsEnabled(false);
				display->setTerrainLightmapEnabled(true);
			}
			else if ( level == SHADOW_LEVEL_MID )
			{
				display->setShadowType(SCL_UNIFORM_FOCUSED_DEPTH_TEXTURE);
				display->setTerrainReceiveDynamicShadowsEnabled(true);
				display->setTerrainLightmapEnabled(true);

				//加入DECL, 现在还没有
			}
			else if ( level == SHADOW_LEVEL_HIGH )
			{
                //display->setShadowType(SCL_UNIFORM_FOCUSED_DEPTH_TEXTURE);
				display->setShadowType(SCL_LISPSM_DEPTH_TEXTURE);
				display->setTerrainReceiveDynamicShadowsEnabled(true);
				display->setTerrainLightmapEnabled(true);
			}	
		}

		setShadowLevel(level);
	}
	//-------------------------------------------------------------------------------
	Bool GameSettingManager::getMaterialLevel(material_level& level)
	{
		U32 rlt = 0;
		if ( MGStrOp::toU32( GameSettingConfig::getInstance().getSettingProperty(GAME_SETTING_SECTION_DISPLAY, DISPLAY_SETTING_MATERIAL_LEVEL).c_str(), rlt ) )
		{
			level = (material_level)rlt;
			if ( level > MATERIAL_LEVEL_MAX )
				level = MATERIAL_LEVEL_LOW;
			return true;
		}
		return false;
	}
	//-------------------------------------------------------------------------------
	void GameSettingManager::setMaterialLevel(material_level level)
	{
		Str16 result;
		MGStrOp::toString((U32)level, result);
		GameSettingConfig::getInstance().setSettingProperty(GAME_SETTING_SECTION_DISPLAY, DISPLAY_SETTING_MATERIAL_LEVEL, result);
	}

    //-------------------------------------------------------------------------------
    void GameSettingManager::applyFog()
    {
        IEngineMain* engine =	ClientMain::getInstance().getEngine();
        if ( !engine )
            return;

        IDisplay* display = engine->display();
        if ( display )
        {   
            //FogColor
            Color fogColour = display->getFogColor();

            //FogExpDensity
            Flt expExpDensity = display->getFogExpDensity();

            //FogLinearStart
            Flt linearStart = display->getFogLinearStart();

            //FogLinearEnd
            Flt linearEnd = display->getFogLinearEnd();

            display->setFogLevel( FOL_LINEAR, fogColour, expExpDensity, linearStart, linearEnd);
        }
    }

	//-------------------------------------------------------------------------------
	void GameSettingManager::applyMaterialLevel()
	{
		material_level level = MATERIAL_LEVEL_LOW;
		getMaterialLevel(level);

		IEngineMain* engine =	ClientMain::getInstance().getEngine();
		if ( !engine )
			return;

		IDisplay* display = engine->display();
		if ( display )
		{
            display->setEntityNormalMapEnable(false);
            display->setTerrainNormalMappingEnabled(false);
            display->setEntitySaMapEnable(false);
            display->setTerrainSpecularMappingEnabled(false);
            display->setEntityReceiveDynamicShadowsEnabled(false);

			if ( level == MATERIAL_LEVEL_LOW )
			{

			}
    // 临时屏蔽中高选项
    /*
			else 
            if ( level == MATERIAL_LEVEL_MID )
			{
                display->setTerrainNormalMappingEnabled(true);
				display->setEntityNormalMapEnable(false);
				display->setEntitySaMapEnable(false);
				display->setTerrainSpecularMappingEnabled(false);
				display->setEntityReceiveDynamicShadowsEnabled(false);
			}
			else 
            if ( level == MATERIAL_LEVEL_HIGH )
			{
				display->setEntityNormalMapEnable(true);
				display->setTerrainNormalMappingEnabled(true);
				display->setEntitySaMapEnable(true);
				display->setTerrainSpecularMappingEnabled(true);
				display->setEntityReceiveDynamicShadowsEnabled(false);
			}
    */
			else 
            if ( level == MATERIAL_LEVEL_HIGH || MATERIAL_LEVEL_MAX  )
			{
                if ( CSceneManager::getInstance().getMapType() == MT_Distribution )
                {
				    display->setTerrainNormalMappingEnabled(true);
                    display->setTerrainSpecularMappingEnabled(true);
                }

				//display->setEntityNormalMapEnable(true);
				//display->setEntitySaMapEnable(true);

				display->setEntityReceiveDynamicShadowsEnabled(true);
			}	
		}

		setMaterialLevel(level);
	}
	//-------------------------------------------------------------------------------
	Bool GameSettingManager::getParticleLevel(particle_level& level)
	{
		U32 rlt = 0;
		if ( MGStrOp::toU32( GameSettingConfig::getInstance().getSettingProperty(GAME_SETTING_SECTION_DISPLAY, DISPLAY_SETTING_PARTICLE_LEVEL).c_str(), rlt ) )
		{
			level = (particle_level)rlt;
			if ( level > PARTICLE_LEVEL_LOW )
				level = PARTICLE_LEVEL_LOW;
			return true;
		}
		return false;
	}
	//-------------------------------------------------------------------------------
	void GameSettingManager::setParticleLevel(particle_level level)
	{
		Str16 result;
		MGStrOp::toString((U32)level, result);
		GameSettingConfig::getInstance().setSettingProperty(GAME_SETTING_SECTION_DISPLAY, DISPLAY_SETTING_PARTICLE_LEVEL, result);
	}
	//-------------------------------------------------------------------------------
	void GameSettingManager::applyParticleLevel()
	{
		particle_level level = PARTICLE_LEVEL_LOW;
		getParticleLevel(level);

		IEngineMain* engine =	ClientMain::getInstance().getEngine();
		if ( !engine )
			return;

		IDisplay* display = engine->display();
		if ( display )
		{
			if ( level == PARTICLE_LEVEL_LOW )
			{

			}
			else if ( level == PARTICLE_LEVEL_MID )
			{

			}
			else if ( level == PARTICLE_LEVEL_HIGH )
			{
				
			}
		}

		setParticleLevel(level);
	}
	//-------------------------------------------------------------------------------
	Bool GameSettingManager::getUseWaterReflection(Bool& isWaterReflection)
	{
		U32 rlt = 0;
		if ( MGStrOp::toU32( GameSettingConfig::getInstance().getSettingProperty(GAME_SETTING_SECTION_DISPLAY, DISPLAY_SETTING_ENABLE_WATER_REFLECTION).c_str(), rlt ) )
		{
			isWaterReflection = (rlt != 0);
			return true;
		}
		return false;
	}
	//-------------------------------------------------------------------------------
	void GameSettingManager::setUseWaterReflection(Bool isWaterReflection)
	{
		Str16 result;
		MGStrOp::toString((U32)isWaterReflection, result);
		GameSettingConfig::getInstance().setSettingProperty(GAME_SETTING_SECTION_DISPLAY, DISPLAY_SETTING_ENABLE_WATER_REFLECTION, result);
	}
	//-------------------------------------------------------------------------------
	void GameSettingManager::applyUseWaterReflection()
	{
		Bool isUse = false;
		getUseWaterReflection( isUse );
		
		IEngineMain* engine =	ClientMain::getInstance().getEngine();
		if ( !engine || !engine->display() )
			return;

		IDisplay* display = engine->display();
		display->setWaterReflectionEnabled(isUse);

		setUseWaterReflection(display->getWaterReflectionEnabled());
	}
	//-------------------------------------------------------------------------------
	Bool GameSettingManager::getUseHighLevelModel(Bool& isUseHighLevelModel)
	{
		U32 rlt = 0;
		if ( MGStrOp::toU32( GameSettingConfig::getInstance().getSettingProperty(GAME_SETTING_SECTION_DISPLAY, DISPLAY_SETTING_ENABLE_HIGH_LEVEL_MODEL).c_str(), rlt ) )
		{
			isUseHighLevelModel = (rlt != 0);
			return true;
		}
		return false;
	}
	//-------------------------------------------------------------------------------
	void GameSettingManager::setUseHighLevelModel(Bool isUseHighLevelModel)
	{
		Str16 result;
		MGStrOp::toString((U32)isUseHighLevelModel, result);
		GameSettingConfig::getInstance().setSettingProperty(GAME_SETTING_SECTION_DISPLAY, DISPLAY_SETTING_ENABLE_HIGH_LEVEL_MODEL, result);
	}
	//-------------------------------------------------------------------------------
	void GameSettingManager::applyUseHighLevelModel()
	{
		Bool isUse = false;
		getUseHighLevelModel( isUse );

		IEngineMain* engine =	ClientMain::getInstance().getEngine();
		if ( !engine || !engine->display() )
			return;

		//切换高模
		setUseHighLevelModel( isUse );
	}
	//-------------------------------------------------------------------------------
	Bool GameSettingManager::getUseHighLevelTexture(Bool& isUseHighLevelTexture)
	{
		U32 rlt = 0;
		if ( MGStrOp::toU32( GameSettingConfig::getInstance().getSettingProperty(GAME_SETTING_SECTION_DISPLAY, DISPLAY_SETTING_ENABLE_HIGH_LEVEL_TEXTURE).c_str(), rlt ) )
		{
			isUseHighLevelTexture = (rlt != 0);
			return true;
		}
		return false;
	}
	//-------------------------------------------------------------------------------
	void GameSettingManager::setUseHighLevelTexture(Bool isUseHighLevelTexture)
	{
		Str16 result;
		MGStrOp::toString((U32)isUseHighLevelTexture, result);
		GameSettingConfig::getInstance().setSettingProperty(GAME_SETTING_SECTION_DISPLAY, DISPLAY_SETTING_ENABLE_HIGH_LEVEL_TEXTURE, result);
	}
	//-------------------------------------------------------------------------------
	void GameSettingManager::applyUseHighLevelTexture()
	{
		Bool isUse = false;
		getUseHighLevelTexture( isUse );
		
		IEngineMain* engine = ClientMain::getInstance().getEngine();
		if ( !engine || !engine->display() )
			return;

		//切换到高精度贴图
		setUseHighLevelTexture( isUse );
	}
	//-------------------------------------------------------------------------------
	Bool GameSettingManager::getUseDetailTerrainObject(Bool& isUseDetailTerrainObject)
	{
		U32 rlt = 0;
		if ( MGStrOp::toU32( GameSettingConfig::getInstance().getSettingProperty(GAME_SETTING_SECTION_DISPLAY, DISPLAY_SETTING_ENABLE_DETAIL_TERRAIN_OBJECT).c_str(), rlt ) )
		{
			isUseDetailTerrainObject = (rlt != 0);
			return true;
		}
		return false;
	}
	//-------------------------------------------------------------------------------
	void GameSettingManager::setUseDetailTerrainObject(Bool isUseDetailTerrainObject)
	{
		Str16 result;
		MGStrOp::toString((U32)isUseDetailTerrainObject, result);
		GameSettingConfig::getInstance().setSettingProperty(GAME_SETTING_SECTION_DISPLAY, DISPLAY_SETTING_ENABLE_DETAIL_TERRAIN_OBJECT, result);	
	}
	//-------------------------------------------------------------------------------
	void GameSettingManager::applyUseDetailTerrainObject()
	{
		Bool isUse = false;
		getUseDetailTerrainObject( isUse );

		IEngineMain* engine = ClientMain::getInstance().getEngine();
		if ( !engine || !engine->display() )
			return;

		//使用地表杂物
		setUseDetailTerrainObject( isUse );
	}
	//-------------------------------------------------------------------------------
	void GameSettingManager::applyAllAudioConfig()
	{
		applyAudioEnable();
		applyBGMEnable();

		notifyApplyAudioConfig();
	}
	//-------------------------------------------------------------------------------
	Bool GameSettingManager::getAudioEnable(Bool& enable)
	{
		U32 rlt = 0;

		if ( MGStrOp::toU32(( GameSettingConfig::getInstance().getSettingProperty(GAME_SETTING_SECTION_SOUND, SOUND_SETTING_ENABLE_SOUND)).c_str(), rlt) )
		{
			enable = (rlt != 0);
			return true;
		}

		return false;
	}
	//-------------------------------------------------------------------------------
	void GameSettingManager::setAudioEnable(Bool enable)
	{
		Str16 result;
		MGStrOp::toString((U32)enable, result);
		GameSettingConfig::getInstance().setSettingProperty(GAME_SETTING_SECTION_SOUND, SOUND_SETTING_ENABLE_SOUND, result);
	}
	//-------------------------------------------------------------------------------
	void GameSettingManager::applyAudioEnable()
	{
		Bool enable = false;
		getAudioEnable(enable);

		GameSoundManager* soundMgr = &GameSoundManager::getInstance();
		if ( soundMgr )
		{
			soundMgr->setSilenceStatus( enable );
			
		}
		setAudioEnable(enable);
	}
	//-------------------------------------------------------------------------------
	Bool GameSettingManager::getBGMEnable(Bool& enable)
	{
		U32 rlt = 0;

		if ( MGStrOp::toU32(( GameSettingConfig::getInstance().getSettingProperty(GAME_SETTING_SECTION_SOUND, SOUND_SETTING_ENABLE_BGM)).c_str(), rlt) )
		{
			enable = (rlt != 0);
			return true;
		}

		return false;
	}
	//-------------------------------------------------------------------------------
	void GameSettingManager::setBGMEnable(Bool enable)
	{
		Str16 result;
		MGStrOp::toString((U32)enable, result);
		GameSettingConfig::getInstance().setSettingProperty(GAME_SETTING_SECTION_SOUND, SOUND_SETTING_ENABLE_BGM, result);
	}
	//-------------------------------------------------------------------------------
	void GameSettingManager::applyBGMEnable()
	{
		Bool enable = false;
		getBGMEnable(enable);

		GameSoundManager* soundMgr = &GameSoundManager::getInstance();
		if ( soundMgr )
		{
			soundMgr->setBackGroundAudioStatus( enable );

		}
		setBGMEnable(enable);
	}
	//--------------------------------------------------------------------------------
	MG::Str8 GameSettingManager::getTrueFontName()
	{
		Str8 tempFontName;
		MGStrOp::toString(( GameSettingConfig::getInstance().getSettingProperty(GAME_SETTING_SECTION_FONT, FONT_SETTING_FONTNAME)).c_str(), tempFontName);
		
		return tempFontName;
	}
	//--------------------------------------------------------------------------------
	void GameSettingManager::setTrueFontName( Str8 fontName )
	{
		Str16 result;
		MGStrOp::toString(fontName.c_str(), result);
		GameSettingConfig::getInstance().setSettingProperty(GAME_SETTING_SECTION_FONT, FONT_SETTING_FONTNAME, result);
	}

    //--------------------------------------------------------------------------------
    Bool GameSettingManager::isDebugNoTerrain()
    {
        Str8 isDebugEnable;
        MGStrOp::toString(( GameSettingConfig::getInstance().getSettingProperty(GAME_SETTING_DEBUG, DEBUG_NO_TERRAIN)).c_str(), isDebugEnable);

        if ( isDebugEnable == "1" )
        {
            return true;
        }

        return false;
    }

    //--------------------------------------------------------------------------------
    Bool GameSettingManager::isDebugNoWater()
    {
        Str8 isDebugEnable;
        MGStrOp::toString(( GameSettingConfig::getInstance().getSettingProperty(GAME_SETTING_DEBUG, DEBUG_NO_WATER)).c_str(), isDebugEnable);

        if ( isDebugEnable == "1" )
        {
            return true;
        }

        return false;
    }

    //--------------------------------------------------------------------------------
    Bool GameSettingManager::isDebugNoSpeedTree()
    {
        Str8 isDebugEnable;
        MGStrOp::toString(( GameSettingConfig::getInstance().getSettingProperty(GAME_SETTING_DEBUG, DEBUG_NO_SPEEDTREE)).c_str(), isDebugEnable);

        if ( isDebugEnable == "1" )
        {
            return true;
        }

        return false;
    }

	//--------------------------------------------------------------------------------
	Bool GameSettingManager::isDebugNoSpeedGrass()
	{
		Str8 isDebugEnable;
		MGStrOp::toString(( GameSettingConfig::getInstance().getSettingProperty(GAME_SETTING_DEBUG, DEBUG_NO_SPEEDGRASS)).c_str(), isDebugEnable);

		if ( isDebugEnable == "1" )
		{
			return true;
		}

		return false;
	}

    //--------------------------------------------------------------------------------
    Bool GameSettingManager::isDebugNoStaticEntity()
    {
        Str8 isDebugEnable;
        MGStrOp::toString(( GameSettingConfig::getInstance().getSettingProperty(GAME_SETTING_DEBUG, DEBUG_NO_STATIC_ENTITY)).c_str(), isDebugEnable);

        if ( isDebugEnable == "1" )
        {
            return true;
        }

        return false;
    }

    //--------------------------------------------------------------------------------
    Bool GameSettingManager::isDebugNoStaticEffect()
    {
        Str8 isDebugEnable;
        MGStrOp::toString(( GameSettingConfig::getInstance().getSettingProperty(GAME_SETTING_DEBUG, DEBUG_NO_STATIC_EFFECT)).c_str(), isDebugEnable);

        if ( isDebugEnable == "1" )
        {
            return true;
        }

        return false;
    }

    //--------------------------------------------------------------------------------
    Bool GameSettingManager::isDebugNoEntity()
    {
        Str8 isDebugEnable;
        MGStrOp::toString(( GameSettingConfig::getInstance().getSettingProperty(GAME_SETTING_DEBUG, DEBUG_NO_ENTITY)).c_str(), isDebugEnable);

        if ( isDebugEnable == "1" )
        {
            return true;
        }

        return false;
    }

    //--------------------------------------------------------------------------------
    Bool GameSettingManager::isDebugNoBuilding()
    {
        Str8 isDebugEnable;
        MGStrOp::toString(( GameSettingConfig::getInstance().getSettingProperty(GAME_SETTING_DEBUG, DEBUG_NO_BUILDING)).c_str(), isDebugEnable);

        if ( isDebugEnable == "1" )
        {
            return true;
        }

        return false;
    }

    //--------------------------------------------------------------------------------
    Bool GameSettingManager::isDebugNoNpc()
    {
        Str8 isDebugEnable;
        MGStrOp::toString(( GameSettingConfig::getInstance().getSettingProperty(GAME_SETTING_DEBUG, DEBUG_NO_NPC)).c_str(), isDebugEnable);

        if ( isDebugEnable == "1" )
        {
            return true;
        }

        return false;
    }

    //--------------------------------------------------------------------------------
    Bool GameSettingManager::isDebugNoItem()
    {
        Str8 isDebugEnable;
        MGStrOp::toString(( GameSettingConfig::getInstance().getSettingProperty(GAME_SETTING_DEBUG, DEBUG_NO_ITEM)).c_str(), isDebugEnable);

        if ( isDebugEnable == "1" )
        {
            return true;
        }

        return false;
    }

    //--------------------------------------------------------------------------------
    Bool GameSettingManager::isDebugShowBlock()
    {
        Str8 isDebugEnable;
        MGStrOp::toString(( GameSettingConfig::getInstance().getSettingProperty(GAME_SETTING_DEBUG, DEBUG_SHOW_BLOCK)).c_str(), isDebugEnable);

        if ( isDebugEnable == "1" )
        {
            return true;
        }

        return false;
    }

    //--------------------------------------------------------------------------------
    Bool GameSettingManager::configSetting( IEngineMain* engineMain )
    {
        IDisplay* display = engineMain->display();
 
        if ( isDebugNoTerrain() )
        {
            display->setDebugNoTerrain( true );
        }

        if ( isDebugNoWater() )
        {
            display->setDebugNoWater( true );
        }

        if ( isDebugNoSpeedTree() )
        {
            display->setDebugNoSpeedTree( true );
        }

        if ( isDebugNoStaticEntity() )
        {
            display->setDebugNoStaticEntity( true );
        }

        if ( isDebugNoStaticEffect() )
        {
            display->setDebugNoStaticEffect( true );
        }

        if ( isDebugNoEntity() )
        {
            display->setDebugNoEntity( true );
        }
        
        if ( isDebugShowBlock() )
        {
            display->setDebugShowBlock( true );
        }

        return true;
    }

	//--------------------------------------------------------------------------------
	void GameSettingManager::notifyApplyDisplayConfig()
	{
		std::map<Str, GameSettingManagerListener*>::iterator iter = mListeners.begin();
		for ( ; iter != mListeners.end(); iter++ )
		{
			iter->second->onApplyDisplayConfig();
		}
	}
	//--------------------------------------------------------------------------------
	void GameSettingManager::notifyApplyAudioConfig()
	{
		std::map<Str, GameSettingManagerListener*>::iterator iter = mListeners.begin();
		for ( ; iter != mListeners.end(); iter++ )
		{
			iter->second->onApplyAudioConfig();
		}
	}
	//--------------------------------------------------------------------------------
	void GameSettingManager::addListener( Str name, GameSettingManagerListener* listener )
	{
		mListeners[name] = listener;
	}
	//--------------------------------------------------------------------------------
	void GameSettingManager::removeListener(Str name)
	{
		std::map<Str, GameSettingManagerListener*>::iterator iter = mListeners.find(name);
		if ( iter != mListeners.end() )
		{
			mListeners.erase(iter);
		}
	}
	//--------------------------------------------------------------------------------
	void GameSettingManager::removeAllListeners()
	{
		mListeners.clear();
	}


	//--------------------------------------------------------------------------------
}
