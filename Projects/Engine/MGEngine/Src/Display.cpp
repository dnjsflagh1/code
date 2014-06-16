/******************************************************************************/
#include "stdafx.h"
#include "Display.h"
#include "EngineMain.h"
#include "TerrainTilesOptions.h"
#include "TerrainTilesMaterialA.h"
#include "InputManager.h"
#include "Scene.h"
#include "OgreConfigOptionMap.h"

/******************************************************************************/

namespace MG
{
	#define MINI_VEDIO_MODE "1024 x 768 @ 32-bit colour"

    SINGLETON_DEFINE( Display )
    //-----------------------------------------------------------------------
    Display::Display()
        :mTerrainColorMappingEnabled(true)
        ,mTerrainNormalMappingEnabled(false)
        ,mTerrainParallaxMappingEnabled(false)
        ,mTerrainSpecularMappingEnabled(false)
        ,mTerrainLightmapEnabled(false)
        ,mTerrainReceiveDynamicShadowsEnabled(false)
        ,mTerrainRegionDisplayEnabledEnabled(false)
        ,mWaterReflectionEnabled(true)
        ,mWaterRefractionEnabled(false)
        ,mWaterDepthCheckEnabled(false)
        ,mTerrainTextureFiltering(TFL_BILINEAR)
        ,mEntityNormalMapEnable(false)
        ,mEntitySaMapEnable(false)
        ,mEntityGroupNormalMapEnable(false)
        ,mEntityGroupSaMapEnable(false)
        ,mEntityLightingMapEnable(false)
        ,mEntityReceiveDynamicShadowsEnabled(false)
		,mShadowType(SCL_NONE)
        ,mTerrainTextureMipmapBias(-2)
        ,mIsFullScreen(false)
        ,mFogLevel(FOL_NONE)
        ,mScaleBiasSpecular(Vec4(1, 0.03, -0.04, 128))
        ,mGammaEnabled(false)
        ,mFSAA(2)
        ,mVsync(true)
        ,mVsyncInterval(2)
        ,mWireframeMode(false)
        ,mTerrainGridsVisible(false)
        ,mTerrainLightingParameter(Vec4(1,0.5,0,1))
        ,mShadowParameter(Vec4(0,0,0,0))
        ,mFogColour(ColourValue::White)
        ,mFogStart(0)
        ,mFogEnd(1000)
        ,mFogDensity(0.002)
		,mTerrainWaterVisible(true)
        ,mIsDebugNoTerrain(false)
        ,mIsDebugNoWater(false)
        ,mIsDebugNoSpeedTree(false)
		,mIsDebugNoSpeedGrass(false)
        ,mIsDebugNoStaticEntity(false)
        ,mIsDebugNoStaticEffect(false)
        ,mIsDebugNoEntity(false)
        ,mIsDebugShowBlock(false)
    {
        mDefaultWindowSize.x = 1024;
        mDefaultWindowSize.y = 768;
		mDefaultColorDepths = 32;
		mCurWindowSize.x = 0;
		mCurWindowSize.y = 0;
    }
    //-----------------------------------------------------------------------
    Display::~Display()
    {
        
    }
    //-----------------------------------------------------------------------
	UInt Display::getWidth()
	{
		return OgreMainInterface::renderWindow->getWidth();
	}
    //-----------------------------------------------------------------------
	UInt Display::getHeight()
	{
		return OgreMainInterface::renderWindow->getHeight();
	}
    //-----------------------------------------------------------------------
	UInt Display::getActWidth()
	{
		Viewport* port = OgreMainInterface::renderWindow->getViewport(0);
		if ( port )
		{
			return port->getActualWidth();
		}
		return getWidth();
	}
	//-----------------------------------------------------------------------
	UInt Display::getActHeight()
	{
		Viewport* port = OgreMainInterface::renderWindow->getViewport(0);
		if ( port )
		{
			return port->getActualHeight();
		}
		return getHeight();
	}
	//-----------------------------------------------------------------------
    void Display::update()
    {
        IInput* input =  EngineMain::getInstance().input();

        if ( input->isAltOn() && input->isKeyPressed(KC_RETURN) )
        {
			setVideoMode(!mIsFullScreen, mCurWindowSize.x, mCurWindowSize.y, true);
        }
		if ( input->isAltOn() && input->isKeyPressed(KC_F12) )
		{
			doScreenShot( ".\\ScreenShot", "" );
		}

    }
	//-----------------------------------------------------------------------
	void Display::setVideoMode(Bool isFullScreen, U32 width, U32 height, Bool immediately)
	{
		if ( !OgreMainInterface::root && 
			!OgreMainInterface::root->getRenderSystem() )
			return;

		//最小分辨率是1024 X 768
		if ( width < (U32)mDefaultWindowSize.x || width * height < (U32)mDefaultWindowSize.x * (U32)mDefaultWindowSize.y )
		{
			width = mDefaultWindowSize.x;
			height = mDefaultWindowSize.y;
		}

		if ( isFullScreen == mIsFullScreen &&
			width == mCurWindowSize.x &&
			height == mCurWindowSize.y )
			return;

		mCurWindowSize.x = width;
		mCurWindowSize.y = height;
		mIsFullScreen = isFullScreen;

		///////////////////////////////////////////////////////////////////////////////////////////////
		///设置分辨率
		char mode[32];
		ZeroMemory(mode, sizeof(mode));
		sprintf_s( mode, sizeof(mode), "%d x %d @ 32-bit colour", width, height );

		//查询显卡是否支持这个分辨率， 不支持就设置为1024*768
		ConfigOptionMap& configOptMap = OgreMainInterface::root->getRenderSystem()->getConfigOptions();
		ConfigOptionMap::iterator optIter = configOptMap.find("Video Mode");
		if ( optIter != configOptMap.end() )
		{
			ConfigOption* optVideoMode = &optIter->second;

			StringVector::const_iterator itValue =
				std::find(optVideoMode->possibleValues.begin(),
				optVideoMode->possibleValues.end(),
				mode );

			if (itValue == optVideoMode->possibleValues.end())
			{
				mCurWindowSize.x = mDefaultWindowSize.x;
				mCurWindowSize.y = mDefaultWindowSize.y;
				
				ZeroMemory(mode, sizeof(mode));
				sprintf_s(mode, sizeof(mode), "%s", MINI_VEDIO_MODE);
			}
		}
		else
		{
			DYNAMIC_EEXCEPT_LOG("The configuation for current RenderSystem has not been initialised!\n");
		}
		
		OgreMainInterface::root->getRenderSystem()->setConfigOption( "Video Mode", mode );		

		///////////////////////////////////////////////////////////////////////////////////////////////
		///设置全屏
		OgreMainInterface::root->getRenderSystem()->setConfigOption( "Full Screen", mIsFullScreen?"Yes":"No" );

		//////////////////////////////////////////////////////////////////////////////////////////////
		///是否立刻生效
		if ( immediately && OgreMainInterface::renderWindow )
		{
			OgreMainInterface::renderWindow->setFullscreen(mIsFullScreen, mCurWindowSize.x, mCurWindowSize.y);
			InputManager::getSingleton().setWindowExtents(getActWidth(), getActHeight());
			EngineMain::getInstance().applyResolutionConfig(getActWidth(), getActHeight());
		}

		//其实VideoMode起变化了的话，可用的FSAA也会起变化， 现在没有找到API.....	
	}
	//-----------------------------------------------------------------------
	Bool Display::getVideoMode(Bool& isFullScreen, U32& width, U32& height)
	{
		isFullScreen = mIsFullScreen;
		width = mCurWindowSize.x;
		height = mCurWindowSize.y;
		
		return true;
	}
	//-----------------------------------------------------------------------
	Bool Display::getVideoModeList(std::vector<VecI2>& videoModeList)
	{
		videoModeList.clear();
		
		U32 miniWidth = mDefaultWindowSize.x;
		U32 miniHeight = mDefaultWindowSize.y;

		ConfigOptionMap& configOptMap = OgreMainInterface::root->getRenderSystem()->getConfigOptions();

		ConfigOptionMap::iterator optIter = configOptMap.find("Video Mode");

		if ( optIter != configOptMap.end() )
		{
			ConfigOption* optVideoMode = &optIter->second;
			for ( U32 i = 0; i < optVideoMode->possibleValues.size(); i++ )
			{
				Str8 videoMode = optVideoMode->possibleValues[i];

				//颜色位数是否是32位
				U32 colorDepths = 0;
				size_t pos = videoMode.find_first_of('-');

				if ( pos != Str8::npos )
				{
					Str8 szColorDepths = videoMode.substr(0, pos);
					pos = szColorDepths.rfind(' ');
					if ( pos != Str8::npos && pos != szColorDepths.length() - 1 )
					{
						szColorDepths = szColorDepths.substr(pos+1);
						MGStrOp::toU32(szColorDepths.c_str(), colorDepths);
					}
				}

				//如果不是32位，就不放入列表
				if ( colorDepths != mDefaultColorDepths )
					continue;
				
				//如果解析结果大于最小分辨率， 就加入可视列表
				size_t length = videoMode.length();
				
				U32 currWidth = 0;
				U32 currHeight = 0;
				pos = videoMode.find_first_of('@');
				
				if ( pos != Str8::npos )
				{
					Str8 szWidthHeight = videoMode.substr(0, pos - 1);
					pos = szWidthHeight.find_first_of('x');

					if ( pos != Str8::npos )
					{
						Str8 szHeight;
						Str8 szWidth;
						szWidth = szWidthHeight.substr(0, pos - 1);
						pos = szWidthHeight.find(' ', pos + 1);
						if ( pos != Str8::npos )
						{
							szHeight = szWidthHeight.substr(pos + 1);

							MGStrOp::toU32(szHeight.c_str(), currHeight);
							MGStrOp::toU32(szWidth.c_str(),currWidth);

							//假如该可用分辨率大于最小分辨率， 加入列表
							if ( currWidth >= miniWidth &&
								currWidth * currHeight >= miniWidth * miniHeight )
							{
								videoModeList.push_back(VecI2(currWidth, currHeight));
							}
						}
					}
				}
			}
		}
		return true;
	}
    //-----------------------------------------------------------------------
	Bool Display::isFullScreen()
	{
		return mIsFullScreen;
	}

    //-----------------------------------------------------------------------
    void Display::setEntityNormalMapEnable(Bool enable)
    {
        mEntityNormalMapEnable = enable;
    }

    //-----------------------------------------------------------------------
    void Display::setEntitySaMapEnable(Bool enable)
    {
        mEntitySaMapEnable = enable;
    }

    //-----------------------------------------------------------------------
    void Display::setEntityGroupNormalMapEnable(Bool enable)
    {
        mEntityGroupNormalMapEnable = enable;
    }

    //-----------------------------------------------------------------------
    void Display::setEntityGroupSaMapEnable(Bool enable)
    {
        mEntityGroupSaMapEnable = enable;
    }

    //-----------------------------------------------------------------------
    void Display::setEntityReceiveDynamicShadowsEnabled(Bool enable)
    {
        mEntityReceiveDynamicShadowsEnabled = enable;
    }

    //-----------------------------------------------------------------------
    Bool Display::getEntityReceiveDynamicShadowsEnabled()
    {
        if ( mShadowType == SCL_NONE )
            return false;

        return mEntityReceiveDynamicShadowsEnabled;
    }

    //-----------------------------------------------------------------------
    void Display::setEntityLightingMapEnable(Bool enable)
    {
        mEntityLightingMapEnable = enable;
    }

    //-----------------------------------------------------------------------
    UInt Display::getBatchCount()
    {
        Ogre::RenderWindow * window = OgreMainInterface::renderWindow;
        if (window)
        {
            return window->getBatchCount();
        }
        return 0;
    }
    //-----------------------------------------------------------------------
    Flt Display::getLastFPS()
    {
        Ogre::RenderWindow * window = OgreMainInterface::renderWindow;
        if (window)
        {
            return window->getLastFPS();
        }
        return 0;
    }
    //-----------------------------------------------------------------------
    Flt Display::getLastAverageFPS()
    {
        Ogre::RenderWindow * window = OgreMainInterface::renderWindow;
        if (window)
        {
            return window->getAverageFPS();
        }
        return 0;
    }
    //-----------------------------------------------------------------------
    UInt Display::getTriangleCount()
    {
        Ogre::RenderWindow * window = OgreMainInterface::renderWindow;
        if (window)
        {
            return window->getTriangleCount();
        }
        return 0;
    }

	//-----------------------------------------------------------------------
    void Display::setShadowType(ShadowType type)
	{
		mShadowType = type;
	}

    //-----------------------------------------------------------------------
    void Display::setup()
    {
		Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(TFO_ANISOTROPIC);
		Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(7);

        //LogManager::getSingleton().setLogDetail(LL_BOREME);
    }
    //-----------------------------------------------------------------------
    void Display::apply()
    {
        EngineMain::getInstance().applyRenderConfig();

        if ( OgreMainInterface::root->getRenderSystem() )
        {
            OgreMainInterface::root->getRenderSystem()->validateConfigOptions();
        }
        
    }
    //-----------------------------------------------------------------------
    void Display::setTerrainMipmapBias( Flt bias )
    {
        mTerrainTextureMipmapBias = bias;
    }
    //-----------------------------------------------------------------------
    void Display::setTerrainTextureFiltering( TextureFiltering filter)
    {
        mTerrainTextureFiltering = filter;
    }

    //-----------------------------------------------------------------------
    void Display::setTerrainColorMappingEnabled( Bool enable)
    {
        mTerrainColorMappingEnabled = enable;
    }

    //-----------------------------------------------------------------------
    void Display::setTerrainNormalMappingEnabled( Bool enable)
    {
        mTerrainNormalMappingEnabled = enable;
    }

    //-----------------------------------------------------------------------
    void Display::setTerrainParallaxMappingEnabled( Bool enable)
    {   
        mTerrainParallaxMappingEnabled = enable;
    }

    //-----------------------------------------------------------------------
    void Display::setTerrainSpecularMappingEnabled( Bool enable)
    {
        mTerrainSpecularMappingEnabled = enable;
    }

    //-----------------------------------------------------------------------
    void Display::setTerrainLightmapEnabled( Bool enable)
    {
        // 暂时屏蔽
        mTerrainLightmapEnabled = enable;
    }

    //-----------------------------------------------------------------------
    void Display::setTerrainReceiveDynamicShadowsEnabled( Bool enable)
    {
        mTerrainReceiveDynamicShadowsEnabled = enable;
    }

    //-----------------------------------------------------------------------
    Bool Display::getTerrainReceiveDynamicShadowsEnabled()
    {
        if ( mShadowType == SCL_NONE )
            return false;

        return mTerrainReceiveDynamicShadowsEnabled;
    }

    //-----------------------------------------------------------------------
    void Display::setTerrainRegionDisplayEnabled( Bool enable)
    {
        mTerrainRegionDisplayEnabledEnabled = enable;
    }

    //-----------------------------------------------------------------------
    void Display::setWaterReflectionEnabled( Bool enable)
    {
        mWaterReflectionEnabled = enable;
    }

	//-----------------------------------------------------------------------
	void Display::setWaterRefractionEnabled( Bool enable)
	{
		mWaterRefractionEnabled = enable;
	}

    //-----------------------------------------------------------------------
    void Display::setWaterDepthCheckEnabled( Bool enable)
    {
        mWaterDepthCheckEnabled = enable;
    }

    //-----------------------------------------------------------------------
    void Display::setFogEnable( Bool enable )
    {
        if ( enable )
        {
            setFogLevel( mFogLevel, Color(mFogColour.r,mFogColour.g,mFogColour.b,mFogColour.a), mFogDensity, mFogStart, mFogEnd);
        }else
        {
            Scene* scene = EngineMain::getInstance().getFirstScene();
            if ( scene )
            {
                scene->getOgreSceneManager()->setFog(FOG_NONE, mFogColour, mFogDensity, mFogStart, mFogEnd);
            }
        }
    }

    //-----------------------------------------------------------------------
    void Display::setFogLevel(FogLevel level, Color color, Flt expDensity, Flt linearStart, Flt linearEnd)
    {
        mFogLevel = level;
        mFogColour  = ColourValue(color.r,color.g,color.b,1);
        mFogStart   = linearStart;
        mFogEnd     = linearEnd;
        mFogDensity = expDensity;

        //Color color = ColorSet::white(), Flt expDensity=0.002, Flt linearStart=0, Flt linearEnd=1000

        Scene* scene = EngineMain::getInstance().getFirstScene();
        if ( scene )
        {
            // 设置雾
            //scene->getOgreSceneManager()->setFog(FOG_LINEAR, ColourValue(0.7, 0.7, 0.8), 0, 10000, 25000);

            if ( level == FOL_NONE )
            {
                scene->getOgreSceneManager()->setFog(FOG_NONE, mFogColour, mFogDensity, mFogStart, mFogEnd);
            }else
            if ( level == FOL_EXP )
            {
                scene->getOgreSceneManager()->setFog(FOG_EXP, mFogColour, mFogDensity, mFogStart, mFogEnd);
                scene->getMainViewport()->setBackgroundColour( mFogColour );
            }else
            if ( level == FOL_LINEAR )
            {
                scene->getOgreSceneManager()->setFog(FOG_LINEAR, mFogColour, mFogDensity, mFogStart, mFogEnd);
                scene->getMainViewport()->setBackgroundColour( mFogColour );
            }
        }
    }

    //-----------------------------------------------------------------------
    Color Display::getFogColor()
    {
        Scene* scene = EngineMain::getInstance().getFirstScene();
        if ( scene )
        {
            ColourValue oColor = scene->getOgreSceneManager()->getFogColour();
            mFogColour.r = oColor.r;
            mFogColour.g = oColor.g;
            mFogColour.b = oColor.b;
        }
        return Color(mFogColour.r,mFogColour.g,mFogColour.b,mFogColour.a);
    }

    //-----------------------------------------------------------------------
    Flt Display::getFogExpDensity()
    {
        Scene* scene = EngineMain::getInstance().getFirstScene();
        if ( scene )
        {
            return scene->getOgreSceneManager()->getFogDensity();
        }
        return mFogDensity;
    }

    //-----------------------------------------------------------------------
    Flt Display::getFogLinearStart()
    {
        Scene* scene = EngineMain::getInstance().getFirstScene();
        if ( scene )
        {
            return scene->getOgreSceneManager()->getFogStart();
        }
        return mFogStart;
    }

    //-----------------------------------------------------------------------
    Flt Display::getFogLinearEnd()
    {
        Scene* scene = EngineMain::getInstance().getFirstScene();
        if ( scene )
        {
            return scene->getOgreSceneManager()->getFogEnd();
        }
        return mFogEnd;
    }

    //-----------------------------------------------------------------------
    void Display::setScaleBiasSpecular(Vec4 sbs)
    {
        mScaleBiasSpecular = sbs;
    }

    //-----------------------------------------------------------------------
    void Display::setGammaEnabled(Bool enable)
    {
        mGammaEnabled = enable;
    }

    //-----------------------------------------------------------------------
    void Display::getRenderSystemSetting(  Ogre::NameValuePairList& list )
    {
        list["FSAA"] = Ogre::StringConverter::toString((size_t)mFSAA);
        list["VSync"] = mVsync?"Yes":"No";
        list["VSync Interval"] = Ogre::StringConverter::toString((size_t)mVsyncInterval);
    }

    //-----------------------------------------------------------------------
    void Display::setFSAA(U32 fsaa, Str fsaaHint)
    {
		//FSAA MODE internal format just like "8 [Qulity]"
		////////////////////////////////////////////////////////////////////////////////////////////////
		char reqFSAA[32];

		if ( fsaaHint.size() <= 1 )
		{
			sprintf_s( reqFSAA, _countof(reqFSAA), "%d", fsaa);
		}
		else
		{
			sprintf_s( reqFSAA, _countof(reqFSAA), "%d [%s]", fsaa, fsaaHint.c_str());
		}
		
		////////////////////////////////////////////////////////////////////////////////////////////////

		Bool found = false;

		ConfigOptionMap& configOptMap = OgreMainInterface::root->getRenderSystem()->getConfigOptions();

		ConfigOptionMap::iterator optIter = configOptMap.find("FSAA");

		if ( optIter != configOptMap.end() )
		{
			ConfigOption& configOption = optIter->second;
			for ( size_t i = 0; i < configOption.possibleValues.size(); i++ )
			{
				if ( configOption.possibleValues[i].compare(reqFSAA) == 0 )
				{
					found = true;
                    break;
				}
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////

		if ( !found )
		{
			mFSAA = 0;
			mFSAAHint.clear();

			ZeroMemory( reqFSAA, sizeof(reqFSAA) );
			sprintf_s( reqFSAA, _countof(reqFSAA), "%d [%s]", mFSAA, mFSAAHint.c_str());
		}
		else
		{
			mFSAA = fsaa;
			mFSAAHint = fsaaHint;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////

		if ( OgreMainInterface::root->getRenderSystem() )
		{
			OgreMainInterface::root->getRenderSystem()->setConfigOption( "FSAA", reqFSAA );
		}

		////////////////////////////////////////////////////////////////////////////////////////////////

    }

	//-----------------------------------------------------------------------
	Bool Display::getFSAAList(std::vector<std::pair<U32, Str>>& outFsaaList)
	{
		outFsaaList.clear();

		ConfigOptionMap& configOptMap = OgreMainInterface::root->getRenderSystem()->getConfigOptions();

		ConfigOptionMap::iterator optIter = configOptMap.find("FSAA");

		if ( optIter != configOptMap.end() )
		{
			ConfigOption& configOption = optIter->second;
			for ( size_t i = 0; i < configOption.possibleValues.size(); i++ )
			{
				U32 fsaa = 0;
				Str	fsaaHint;

				//split fsaa information from string
				Ogre::StringVector Value = Ogre::StringUtil::split(configOption.possibleValues[i], " ");
				
				if ( Value.size() > 0 )
				{
					if ( Value.size() > 1 )
					{
						fsaaHint = Value[1];

						//trim left & trim right
						fsaaHint.erase(fsaaHint.find_last_not_of(']') + 1);
						fsaaHint.erase(0, fsaaHint.find_first_not_of('['));
					}

					if ( MGStrOp::toU32(Value[0].c_str(), fsaa) )
					{
						outFsaaList.push_back(std::pair<U32, Str>(fsaa, fsaaHint));
					}
				}
			}
		}

		return outFsaaList.size() > 0;
	}

    //-----------------------------------------------------------------------
    void Display::setVsync(Bool enable)
    {
        mVsync = enable;

        if ( OgreMainInterface::root->getRenderSystem() )
        {
            OgreMainInterface::root->getRenderSystem()->setConfigOption( "VSync", mVsync?"Yes":"No" );
        }
    }
	
    //-----------------------------------------------------------------------
    void Display::setVsyncInterval(UInt interval)
    {
        mVsyncInterval = interval;

        if ( OgreMainInterface::root->getRenderSystem() )
        {
            OgreMainInterface::root->getRenderSystem()->setConfigOption( "VSync Interval", Ogre::StringConverter::toString((size_t)mVsyncInterval) );
        }
    }

    //-----------------------------------------------------------------------
    void Display::setWireframeMode( Bool enable )
    {
        Scene* scene = EngineMain::getInstance().getFirstScene();
        if ( scene )
        {
            if ( enable )
            {
                scene->getActiveCamera()->getOgreCamera()->setPolygonMode( PM_WIREFRAME );
            }else
            {
                scene->getActiveCamera()->getOgreCamera()->setPolygonMode( PM_SOLID );
            }

           mWireframeMode = enable;
        }
    }

    //-----------------------------------------------------------------------
    void Display::setTerrainGridsVisible( Bool visible )
    {
        Scene* scene = EngineMain::getInstance().getFirstScene();
        if ( scene )
        {
            ITerrainGridsDecorator* decorator = scene->getWireframeManager()->createTerrainGridsDecorator( "DefaultTerrainGridsDecorator" );
            
            if ( decorator )
            {
                decorator->setVisible( visible );
            }
            
            mTerrainGridsVisible = visible;
        }
    }

    //-----------------------------------------------------------------------
    void Display::setTerrainLightingParameter( Vec4 parameter )
    {
        mTerrainLightingParameter = parameter;
    }

    //-----------------------------------------------------------------------
    void Display::setShadowParameter( Vec4 parameter )
    {
        mShadowParameter = parameter;
    }

	//-----------------------------------------------------------------------
	void Display::setEntityVisible( Bool visible, Bool immediately )
	{
		mEntityVisible = visible;

		if ( immediately )
		{
			Scene* scene = EngineMain::getInstance().getFirstScene();

			if ( scene )
			{
				Ogre::SceneManager* sm = scene->getOgreSceneManager();

				if ( sm )
				{
					Viewport* port = sm->getCurrentViewport();

					if ( port )
					{
						if ( !visible )
						{
							uint mask = SOV_ENTITY | SOV_DYNAMIC_SHADOW | SOV_STATIC_SHADOW;
							port->setVisibilityMask( port->getVisibilityMask() & ~mask );
						}
						else
						{
							uint mask = SOV_ENTITY | SOV_DYNAMIC_SHADOW | SOV_STATIC_SHADOW;
							port->setVisibilityMask( port->getVisibilityMask() | mask );
						}
					}
				}
			}
		}
	}

	//-----------------------------------------------------------------------
	void Display::setTerrainWaterVisible( Bool visible, Bool immediately )
	{
		mTerrainWaterVisible = visible;

		if ( immediately )
		{
			Scene* scene = EngineMain::getInstance().getFirstScene();

			if ( scene )
			{
				Ogre::SceneManager* sm = scene->getOgreSceneManager();

				if ( sm )
				{
					Viewport* port = sm->getCurrentViewport();

					if ( port )
					{
						if ( !visible )
						{
							port->setVisibilityMask( port->getVisibilityMask() & ~SOV_WATER );
						}
						else
						{
							port->setVisibilityMask( port->getVisibilityMask() | SOV_WATER );
						}
					}
				}
			}
		}	
	}
	//-----------------------------------------------------------------------
	void Display::doScreenShot( Str filePath, Str fileName )
	{
		/////////////////////////////////////////////////////////////////////////////////////////

		// 截图不需要截UI，关闭所有UI.

		std::vector<Str> layoutsClosed;
		
		Gui* gui = EngineMain::getInstance().getFirstScene()->getGui();
		if ( gui )
		{
			std::map<Str, Layout*>& layouts = gui->getAllLayOuts();
			for ( std::map<Str, Layout*>::iterator iter = layouts.begin(); iter != layouts.end(); iter++ )
			{
				Layout* layout = iter->second;
				if ( layout->isVisible() )
				{
					layout->setVisible(false);
					layoutsClosed.push_back(iter->first);
				}
			}
		}

		OgreMainInterface::root->renderOneFrame();
		
		/////////////////////////////////////////////////////////////////////////////////////////

		Bool pathExist = false;

		WIN32_FIND_DATA wfd;
		FindFirstFile(filePath.c_str(),&wfd);
		if( ( wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) == FILE_ATTRIBUTE_DIRECTORY )
		{
			pathExist = true;
		}

		if ( !pathExist )
		{
			CreateDirectory(filePath.c_str(), NULL);
		}

		/////////////////////////////////////////////////////////////////////////////////////////

		if ( fileName.empty() )
			fileName = "Screen_Shot";

		if ( filePath.empty() )
			filePath = ".\\";

		Str filePrefix = filePath;
		filePrefix += "\\";
		filePrefix += fileName;
		filePrefix += "_";

		OgreMainInterface::renderWindow->writeContentsToTimestampedFile(filePrefix, Str(".png"));

		/////////////////////////////////////////////////////////////////////////////////////////

		// 打开那些在函数开头被关闭的GUI

		if ( gui )
		{
			for ( size_t i = 0; i < layoutsClosed.size(); i++ )
			{
				Layout* layout = gui->getLayOut(layoutsClosed[i]);
				if ( layout )
				{
					layout->setVisible(true);
				}
			}
		}

		/////////////////////////////////////////////////////////////////////////////////////////
	}
	//-----------------------------------------------------------------------
}