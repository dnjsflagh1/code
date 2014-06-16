//***************************************************************************************************
#include "stdafx.h"
#include "UISystemSetting.h"
#include "ClientMain.h"
#include "GameSettingManager.h"

//***************************************************************************************************
namespace MG
{

	//----------------------------------------------------------------------------------------
	UISystemSetting::UISystemSetting()
	{

	}
	//----------------------------------------------------------------------------------------
	UISystemSetting::~UISystemSetting()
	{

	}
	//----------------------------------------------------------------------------------------
	void UISystemSetting::setEvent()
	{
        //
       //getLayout()->getButton("btn_function")->getWidget()->setMouseButtonClickEvent(onClickBtnFunction);
	   getLayout()->getButton("btn_video")->getWidget()->setMouseButtonClickEvent(onClickBtnVideo);
	   getLayout()->getButton("btn_audio")->getWidget()->setMouseButtonClickEvent(onClickBtnAudio);
	   //getLayout()->getButton("btn_network")->getWidget()->setMouseButtonClickEvent(onClickBtnBtnNetWork);
	   //

	   getLayout()->getButton("btn_network")->getWidget()->setEnabled(false);
	   getLayout()->getButton("btn_function")->getWidget()->setEnabled(false);
	  
	   //////////////////////////////////////////////////////////////////////////////////////////////////////////////
	   //video setting
	   //////////////////////////////////////////////////////////////////////////////////////////////////////////////

	   getLayout()->getButton("btn_videook")->getWidget()->setMouseButtonClickEvent(onClickBtnApplyVideo);

	   getLayout()->getButton("cbox_fullscreen")->getWidget()->setMouseButtonClickEvent(onClickCheckBtnEnableFullScreen);
	   getLayout()->getButton("cbox_vsync")->getWidget()->setMouseButtonClickEvent(onClickCheckBtnEnableVsync);
	   getLayout()->getButton("cbox_waterreflect")->getWidget()->setMouseButtonClickEvent(onClickCheckBtnEnableWaterReflection);
	   getLayout()->getButton("cbox_PreciseModel")->getWidget()->setMouseButtonClickEvent(onClickCheckBtnEnableHighLevelModel);
	   getLayout()->getButton("cbox_PreciseTexture")->getWidget()->setMouseButtonClickEvent(onClickCheckBtnEnableHighLevelTexture);
	   getLayout()->getButton("cbox_DetailTerrainObject")->getWidget()->setMouseButtonClickEvent(onClickCheckBtnEnableHighLevelTerrainObject);

	   getLayout()->getComboBox("edit_resolution")->setComboAcceptEvent(onSelectCommoboxIndex);
	   getLayout()->getComboBox("edit_aliasing")->setComboAcceptEvent(onSelectCommoboxIndex);

	   IHScroll* it =getLayout()->getHScroll("HScroll_PostFX");
	   //IViewScroll* it = getLayout()->getViewScroll("HScroll_PostFX");
	   assert(it);
	   /* getLayout()->getHScroll("HScroll_PostFX")->setScrollChangePositionEvent(onHScrollPostionSetPostFXLevel);
	   getLayout()->getHScroll("HScroll_Shadow")->setScrollChangePositionEvent(onHScrollPostionSetShadowLevel);
	   getLayout()->getHScroll("HScroll_Particle")->setScrollChangePositionEvent(onHScrollPostionSetParticleLevel);
	   getLayout()->getHScroll("HScroll_Material")->setScrollChangePositionEvent(onHScrollPostionSetMaterialLevel);*/

	   //////////////////////////////////////////////////////////////////////////////////////////////////////////////
       //audio setting
	   getLayout()->getButton("btn_audiook")->getWidget()->setMouseButtonClickEvent(onClickBtnApplyAudio);
	   getLayout()->getButton("cbox_bgsound")->getWidget()->setMouseButtonClickEvent(onClickCheckBtnEnableBgSound);
	   getLayout()->getButton("cbox_silence")->getWidget()->setMouseButtonClickEvent(onClickCheckBtnEnableSilence);
	   //////////////////////////////////////////////////////////////////////////////////////////////////////////////
	   //
	   _onClickBtnVideo();


	}
	//----------------------------------------------------------------------------------------
	Bool UISystemSetting::openGui()
	{
		restore();
		return UIObject::openGui();
	}
	//----------------------------------------------------------------------------------------
	void UISystemSetting::restore()
	{
		restoreVideoSetting();
		restoreAudioSetting();
	}
	//----------------------------------------------------------------------------------------
	void UISystemSetting::restoreAudioSetting()
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////
		
		// 音乐总开关

		IButton* checkBtn = getLayout()->getButton("cbox_silence");
		if ( checkBtn )
		{
			Bool isEnable = false;
			GameSettingManager::getInstance().getAudioEnable(isEnable);
			checkBtn->setStateCheck(isEnable);
		}

		// 背景音开关

		checkBtn = getLayout()->getButton("cbox_bgsound");
		if ( checkBtn )
		{
			Bool isEnable = false;
			GameSettingManager::getInstance().getBGMEnable(isEnable);
			checkBtn->setStateCheck(isEnable);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	//----------------------------------------------------------------------------------------
	void UISystemSetting::applyAudioSetting()
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////
		
		// 音乐总开关

		IButton* checkBtn = getLayout()->getButton("cbox_silence");
		if ( checkBtn )
		{
			Bool enable = checkBtn->getStateCheck();
			GameSettingManager::getInstance().setAudioEnable(enable);
		}

		// 背景音乐开关

		checkBtn = getLayout()->getButton("cbox_bgsound");
		if ( checkBtn )
		{
			Bool enable = checkBtn->getStateCheck();
			GameSettingManager::getInstance().setBGMEnable(enable);
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////
		//GameSettingManager::getInstance().applyAuidoConfig(true);applyAllAudioConfig();
		GameSettingManager::getInstance().applyAllAudioConfig();
		GameSettingManager::getInstance().saveConfig();
		///////////////////////////////////////////////////////////////////////////////////////////////////
	}
	//----------------------------------------------------------------------------------------
	void UISystemSetting::restoreVideoSetting()
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////
		//分辨率
		IComboBox* comboBox = getLayout()->getComboBox("edit_resolution");
		if ( comboBox )
		{
			std::vector<VecI2> resList;
			if ( GameSettingManager::getInstance().getVideoModeList(resList) )
			{
				comboBox->removeAllItems();

				for ( U32 i = 0; i < resList.size(); i++ )
				{
					wchar_t name[32];
					swprintf_s( name, _countof(name), L"%d x %d", resList[i].x, resList[i].y );
					comboBox->addItem( name, resList[i] );
				}
			}

			bool isFullScreen = false;
			U32 width = 0;
			U32 height = 0;

			if ( GameSettingManager::getInstance().getVideoMode(isFullScreen, width, height) )
			{
				for ( U32 i = 0; i < comboBox->getItemCount(); i++ )
				{
					IAny* any_data = comboBox->getItemDataAt(i);
					if ( any_data )
					{
						VecI2* size = any_data->castType<VecI2>();

						if ( size && 
							size->x == width && 
							size->y == height )
						{
							comboBox->setIndexSelected(i);
							break;
						}
					}
				}
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////
		//FSAA

		comboBox = getLayout()->getComboBox("edit_aliasing");
		if ( comboBox )
		{
			std::vector<GameSettingManager::FSAA_MODE> fsaaList;

			if ( GameSettingManager::getInstance().getFSAAList(fsaaList) )
			{
				comboBox->removeAllItems();

				for ( U32 i = 0; i < fsaaList.size(); i++ )
				{
					GameSettingManager::FSAA_MODE& fsaaMode = fsaaList[i];

					////////////////////////////////////////////////////////////

					//组成新的格式，显示在UI上
					////////////////////////////////////////////////////////////
					if ( !fsaaMode.FSAA_SAMPLE.empty() )
					{
						Str16 name;

						name = fsaaMode.FSAA_SAMPLE;
						name += L'x';
						
						if ( !fsaaMode.FSAA_HINT.empty() )
						{
							name += L' ';
							name += fsaaMode.FSAA_HINT;
						}
						
						comboBox->addItem( name, fsaaMode );
					}
				}

				//获得选中控件
				////////////////////////////////////////////////////////////
				Str16 szFsaaSample;
				Str16 szfsaaHint;

				if ( GameSettingManager::getInstance().getFSAA(szFsaaSample, szfsaaHint) )
				{
					for ( U32 i = 0; i < comboBox->getItemCount(); i++ )
					{
						IAny* any_data = comboBox->getItemDataAt(i);
						if ( any_data )
						{
							GameSettingManager::FSAA_MODE* combo_data = any_data->castType<GameSettingManager::FSAA_MODE>();

							if ( combo_data &&
								combo_data->FSAA_SAMPLE.compare(szFsaaSample) == 0 &&
								combo_data->FSAA_HINT.compare(szfsaaHint) == 0 )
							{
								comboBox->setIndexSelected(i);
								break;
							}
						}
					}
				}
				////////////////////////////////////////////////////////////
			}
			else
			{
				comboBox->getWidget()->setEnabled(false);
			}
		}


		////////////////////////////////////////////////////////////////////////////////////////////////////
		//后期特效
		IHScroll* hscroll = getLayout()->getHScroll("HScroll_PostFX");
		//IViewScroll* hscroll = getLayout()->getViewScroll("HScroll_PostFX");
		assert(hscroll);
		if ( hscroll )
		{
			GameSettingManager::post_fx_level level = GameSettingManager::POST_FX_NONE;
			GameSettingManager::getInstance().getPostFx(level);
			
			if ( level == GameSettingManager::POST_FX_NONE )
			{
				hscroll->setScrollPosition(0);
			}
			else if (  level == GameSettingManager::POST_FX_LOW )
			{
				hscroll->setScrollPosition(1);
			}
			else if (  level == GameSettingManager::POST_FX_MID )
			{
				hscroll->setScrollPosition(2);
			}
			else if (  level == GameSettingManager::POST_FX_HIGH )
			{
				hscroll->setScrollPosition(3);
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////
		//阴影
		hscroll = getLayout()->getHScroll("HScroll_Shadow");
		if ( hscroll )
		{
			GameSettingManager::shadow_level level = GameSettingManager::SHADOW_LEVEL_NONE;
			GameSettingManager::getInstance().getShadowLevel(level);

			if ( level == GameSettingManager::SHADOW_LEVEL_NONE )
			{
				hscroll->setScrollPosition(0);
			}
			else if (  level == GameSettingManager::SHADOW_LEVEL_LOW )
			{
				hscroll->setScrollPosition(1);
			}
			else if (  level == GameSettingManager::SHADOW_LEVEL_MID )
			{
				hscroll->setScrollPosition(2);
			}
			else if (  level == GameSettingManager::SHADOW_LEVEL_HIGH )
			{
				hscroll->setScrollPosition(3);
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////
		//材质
		hscroll = getLayout()->getHScroll("HScroll_Material");
		if ( hscroll )
		{
			GameSettingManager::material_level level = GameSettingManager::MATERIAL_LEVEL_LOW;
			GameSettingManager::getInstance().getMaterialLevel(level);

			if ( level == GameSettingManager::MATERIAL_LEVEL_LOW )
			{
				hscroll->setScrollPosition(0);
			}
			else if (  level == GameSettingManager::MATERIAL_LEVEL_MID )
			{
				hscroll->setScrollPosition(1);
			}
			else if (  level == GameSettingManager::MATERIAL_LEVEL_HIGH )
			{
				hscroll->setScrollPosition(2);
			}
			else if (  level == GameSettingManager::MATERIAL_LEVEL_MAX )
			{
				hscroll->setScrollPosition(3);
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////
		//阴影
		hscroll = getLayout()->getHScroll("HScroll_Particle");
		if ( hscroll )
		{
			GameSettingManager::particle_level level = GameSettingManager::PARTICLE_LEVEL_LOW;
			GameSettingManager::getInstance().getParticleLevel(level);

			if ( level == GameSettingManager::PARTICLE_LEVEL_LOW )
			{
				hscroll->setScrollPosition(0);
			}
			else if (  level == GameSettingManager::PARTICLE_LEVEL_MID )
			{
				hscroll->setScrollPosition(1);
			}
			else if (  level == GameSettingManager::PARTICLE_LEVEL_HIGH )
			{
				hscroll->setScrollPosition(2);
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////
		//是否全屏
		IButton* checkBtn = getLayout()->getButton("cbox_fullscreen");
		if ( checkBtn )
		{
			U32 width = 0;
			U32 height = 0;
			Bool isFullScreen = false;

			GameSettingManager::getInstance().getVideoMode(isFullScreen, width, height);
			
			if ( isFullScreen )
			{
				checkBtn->setStateCheck(true);
			}
			else
			{
				checkBtn->setStateCheck(false);
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////
		//是否垂直扫描
		checkBtn = getLayout()->getButton("cbox_vsync");
		if ( checkBtn )
		{
			Bool isVsync = false;
			GameSettingManager::getInstance().getVsync(isVsync);

			if ( isVsync )
			{
				checkBtn->setStateCheck(true);
			}
			else
			{
				checkBtn->setStateCheck(false);
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////
		//是否使用水反光
		checkBtn = getLayout()->getButton("cbox_waterreflect");
		if ( checkBtn )
		{
			Bool isVsync = false;
			GameSettingManager::getInstance().getUseWaterReflection(isVsync);

			if ( isVsync )
			{
				checkBtn->setStateCheck(true);
			}
			else
			{
				checkBtn->setStateCheck(false);
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////
		//是否使用高模
		checkBtn = getLayout()->getButton("cbox_PreciseModel");
		if ( checkBtn )
		{
			Bool isUse = false;
			GameSettingManager::getInstance().getUseHighLevelModel(isUse);

			if ( isUse )
			{
				checkBtn->setStateCheck(true);
			}
			else
			{
				checkBtn->setStateCheck(false);
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////
		//是否使用高精度贴图
		checkBtn = getLayout()->getButton("cbox_PreciseTexture");
		if ( checkBtn )
		{
			Bool isUse = false;
			GameSettingManager::getInstance().getUseHighLevelTexture(isUse);

			if ( isUse )
			{
				checkBtn->setStateCheck(true);
			}
			else
			{
				checkBtn->setStateCheck(false);
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////
		//是否使用细致地表物件
		checkBtn = getLayout()->getButton("cbox_DetailTerrainObject");
		if ( checkBtn )
		{
			Bool isUse = false;
			GameSettingManager::getInstance().getUseDetailTerrainObject(isUse);

			if ( isUse )
			{
				checkBtn->setStateCheck(true);
			}
			else
			{
				checkBtn->setStateCheck(false);
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////

	}
	//----------------------------------------------------------------------------------------
	void UISystemSetting::applyVideoSetting()
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////
		//后期特效
		IHScroll* hscroll = getLayout()->getHScroll("HScroll_PostFX");
		if ( hscroll )
		{
			size_t pos = hscroll->getScrollPosition();

			if ( hscroll->getScrollPosition() <= 0  )//无
			{
				GameSettingManager::getInstance().setPostFx(GameSettingManager::POST_FX_NONE);
			}
			else if ( hscroll->getScrollPosition() <= 1 )//低
			{
				GameSettingManager::getInstance().setPostFx(GameSettingManager::POST_FX_LOW);
			}
			else if ( hscroll->getScrollPosition() <= 2 )//中
			{
				GameSettingManager::getInstance().setPostFx(GameSettingManager::POST_FX_MID);
			}
			else if ( hscroll->getScrollPosition() <= 3 )//高
			{
				GameSettingManager::getInstance().setPostFx(GameSettingManager::POST_FX_HIGH);
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////
		//阴影等级
		hscroll = getLayout()->getHScroll("HScroll_Shadow");
		if ( hscroll )
		{
			size_t pos = hscroll->getScrollPosition();

			if ( hscroll->getScrollPosition() <= 0  )//无
			{
				GameSettingManager::getInstance().setShadowLevel(GameSettingManager::SHADOW_LEVEL_NONE);
			}
			else if ( hscroll->getScrollPosition() <= 1 )//低
			{
				GameSettingManager::getInstance().setShadowLevel(GameSettingManager::SHADOW_LEVEL_LOW);
			}
			else if ( hscroll->getScrollPosition() <= 2 )//中
			{
				GameSettingManager::getInstance().setShadowLevel(GameSettingManager::SHADOW_LEVEL_MID);
			}
			else if ( hscroll->getScrollPosition() <= 3 )//高
			{
				GameSettingManager::getInstance().setShadowLevel(GameSettingManager::SHADOW_LEVEL_HIGH);
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////
		//材质等级
		hscroll = getLayout()->getHScroll("HScroll_Material");
		if ( hscroll )
		{
			size_t pos = hscroll->getScrollPosition();

			if ( hscroll->getScrollPosition() <= 0  )//无
			{
				GameSettingManager::getInstance().setMaterialLevel(GameSettingManager::MATERIAL_LEVEL_LOW);
			}
			else if ( hscroll->getScrollPosition() <= 1 )//低
			{
				GameSettingManager::getInstance().setMaterialLevel(GameSettingManager::MATERIAL_LEVEL_MID);
			}
			else if ( hscroll->getScrollPosition() <= 2 )//中
			{
				GameSettingManager::getInstance().setMaterialLevel(GameSettingManager::MATERIAL_LEVEL_HIGH);
			}
			else if ( hscroll->getScrollPosition() <= 3 )//高
			{
				GameSettingManager::getInstance().setMaterialLevel(GameSettingManager::MATERIAL_LEVEL_MAX);
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////
		//粒子等级
		hscroll = getLayout()->getHScroll("HScroll_Particle");
		if ( hscroll )
		{
			size_t pos = hscroll->getScrollPosition();

			if ( hscroll->getScrollPosition() <= 0  )//无
			{
				GameSettingManager::getInstance().setParticleLevel(GameSettingManager::PARTICLE_LEVEL_LOW);
			}
			else if ( hscroll->getScrollPosition() <= 1 )//低
			{
				GameSettingManager::getInstance().setParticleLevel(GameSettingManager::PARTICLE_LEVEL_MID);
			}
			else if ( hscroll->getScrollPosition() <= 2 )//中
			{
				GameSettingManager::getInstance().setParticleLevel(GameSettingManager::PARTICLE_LEVEL_HIGH);
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////
		//是否垂直同步
		IButton* checkBtn = getLayout()->getButton("cbox_vsync");
		if ( checkBtn )
		{
			Bool isVsync = checkBtn->getStateCheck();
			GameSettingManager::getInstance().setVsync(isVsync);
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////
		//是否开启水面倒影
		checkBtn = getLayout()->getButton("cbox_waterreflect");
		if ( checkBtn )
		{
			Bool isWaterReflect = checkBtn->getStateCheck();
			GameSettingManager::getInstance().setUseWaterReflection(isWaterReflect);
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////
		//是否显示高精度模型
		checkBtn = getLayout()->getButton("cbox_PreciseModel");
		if ( checkBtn )
		{
			Bool isUse = checkBtn->getStateCheck();
			GameSettingManager::getInstance().setUseHighLevelModel(isUse);
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////
		//是否显示高精度贴图
		checkBtn = getLayout()->getButton("cbox_PreciseTexture");
		if ( checkBtn )
		{
			Bool isUse = checkBtn->getStateCheck();
			GameSettingManager::getInstance().setUseHighLevelTexture(isUse);
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////
		//是否显示地形细节
		checkBtn = getLayout()->getButton("cbox_DetailTerrainObject");
		if ( checkBtn )
		{
			Bool isUse = checkBtn->getStateCheck();
			GameSettingManager::getInstance().setUseDetailTerrainObject(isUse);
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////
		//设置FSAA
		GameSettingManager::FSAA_MODE* FSAA = NULL;

		IComboBox* comboBox = getLayout()->getComboBox("edit_aliasing");
		if ( comboBox )
		{
			IAny* any_data = comboBox->getItemDataAt(comboBox->getIndexSelected());
			FSAA = any_data->castType<GameSettingManager::FSAA_MODE>();

			if ( FSAA )
			{
				GameSettingManager::getInstance().setFSAA( FSAA->FSAA_SAMPLE, FSAA->FSAA_HINT);
			}
		}

		
		////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////
		//设置视频模式
		Bool isFullScreen = false;
		VecI2* size = NULL;

		checkBtn = getLayout()->getButton("cbox_fullscreen");
		if ( checkBtn )
		{
			isFullScreen = checkBtn->getStateCheck();
		}

		comboBox = getLayout()->getComboBox("edit_resolution");
		if ( comboBox )
		{
			IAny* any_data = comboBox->getItemDataAt(comboBox->getIndexSelected());
			size = any_data->castType<VecI2>();
		}

		if ( size )
			GameSettingManager::getInstance().setVideoMode( isFullScreen, size->x, size->y );
		////////////////////////////////////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////////////////////////////////
		GameSettingManager::getInstance().applyDisplayConfig(true);

		GameSettingManager::getInstance().applyHardwareConfig();

		GameSettingManager::getInstance().saveConfig();
		///////////////////////////////////////////////////////////////////////////////////////////////////

	}
	//----------------------------------------------------------------------------------------
	void UISystemSetting::setSettingType( SysSettingType sysSetType )
	{
		//2012-09-07 没有提供network,function
		/*if (sysSetType == SYS_SET_TYPE_FUNCTION)
		{
             _setImageVisible("bg_function",true);
			 _setImageVisible("bg_video",false);
			 _setImageVisible("bg_audio",false);
			 _setImageVisible("bg_network",false);

		}*/
		if (sysSetType == SYS_SET_TYPE_VIDEO)
		{
			_setImageVisible("bg_video",true);
			//_setImageVisible("bg_function",false);
			_setImageVisible("bg_audio",false);
			//_setImageVisible("bg_network",false);
			getLayout()->getButton("btn_video")->setStateCheck(true);
			getLayout()->getButton("btn_audio")->setStateCheck(false);

		}
		else if (sysSetType == SYS_SET_TYPE_AUDIO)
		{
            _setImageVisible("bg_audio",true);
			//_setImageVisible("bg_function",false);
			_setImageVisible("bg_video",false);
			//_setImageVisible("bg_network",false);
			getLayout()->getButton("btn_video")->setStateCheck(false);
			getLayout()->getButton("btn_audio")->setStateCheck(true);
		}
		/*else if (sysSetType == SYS_SET_TYPE_NETWORK)
		{
			 _setImageVisible("bg_network",true);
			 _setImageVisible("bg_function",false);
			 _setImageVisible("bg_video",false);
			 _setImageVisible("bg_audio",false);

		}*/
		else
		{
			//DYNAMIC_ASSERT(0);
			return;
		}

	}
	//----------------------------------------------------------------------------------------
	void UISystemSetting::_setImageVisible( const Str8& name,Bool bVisiable )
	{
        getLayout()->getImage(name)->getWidget()->setVisible(bVisiable);

	}
	//----------------------------------------------------------------------------------------
	void UISystemSetting::onClickBtnFunction( void* widget )
	{
		DYNAMIC_ASSERT(widget);
		UISystemSetting::getInstance()._onClickBtnFunction();

	}
	//----------------------------------------------------------------------------------------
	void UISystemSetting::onClickBtnVideo( void* widget )
	{
		DYNAMIC_ASSERT(widget);
		UISystemSetting::getInstance()._onClickBtnVideo();

	}
	//----------------------------------------------------------------------------------------
	void UISystemSetting::onClickBtnAudio( void* widget )
	{
		DYNAMIC_ASSERT(widget);
		UISystemSetting::getInstance()._onClickBtnAudio();

	}
	//----------------------------------------------------------------------------------------
	void UISystemSetting::onClickBtnBtnNetWork( void* widget )
	{
		DYNAMIC_ASSERT(widget);
		UISystemSetting::getInstance()._onClickBtnBtnNetWork();

	}
	//----------------------------------------------------------------------------------------
	void UISystemSetting::onClickBtnApplyVideo( void* widget )
	{
		DYNAMIC_ASSERT(widget);
		UISystemSetting::getInstance()._onClickBtnApplyVideo();
		UISystemSetting::getInstance().closeGui();
	}
	//----------------------------------------------------------------------------------------
	void UISystemSetting::onClickBtnApplyAudio( void* widget )
	{
		DYNAMIC_ASSERT(widget);
		UISystemSetting::getInstance()._onClickBtnApplyAudio();
		UISystemSetting::getInstance().closeGui();
	}	
	//----------------------------------------------------------------------------------------
	void UISystemSetting::_onClickBtnFunction()
	{
		getLayout()->getButton("btn_video")->setStateCheck(false);
		getLayout()->getButton("btn_audio")->setStateCheck(false);
		getLayout()->getButton("btn_network")->setStateCheck(false);
		getLayout()->getButton("btn_function")->setStateCheck(true);

		//_setImageVisible("bg_function",true);
		_setImageVisible("bg_video",false);
		_setImageVisible("bg_audio",false);
		//_setImageVisible("bg_network",false);

	}
	//----------------------------------------------------------------------------------------
	void UISystemSetting::_onClickBtnVideo()
	{
		getLayout()->getButton("btn_video")->setStateCheck(true);
		getLayout()->getButton("btn_audio")->setStateCheck(false);
		getLayout()->getButton("btn_network")->setStateCheck(false);
		getLayout()->getButton("btn_function")->setStateCheck(false);

		_setImageVisible("bg_video",true);
		//_setImageVisible("bg_function",false);
		_setImageVisible("bg_audio",false);
		//_setImageVisible("bg_network",false);

	}
	//----------------------------------------------------------------------------------------
	void UISystemSetting::_onClickBtnAudio()
	{
		getLayout()->getButton("btn_video")->setStateCheck(false);
		getLayout()->getButton("btn_audio")->setStateCheck(true);
		getLayout()->getButton("btn_network")->setStateCheck(false);
		getLayout()->getButton("btn_function")->setStateCheck(false);

		_setImageVisible("bg_audio",true);
		//_setImageVisible("bg_function",false);
		_setImageVisible("bg_video",false);
		//_setImageVisible("bg_network",false);

	}
	//----------------------------------------------------------------------------------------
	void UISystemSetting::_onClickBtnBtnNetWork()
	{
		getLayout()->getButton("btn_video")->setStateCheck(false);
		getLayout()->getButton("btn_audio")->setStateCheck(false);
		getLayout()->getButton("btn_network")->setStateCheck(true);
		getLayout()->getButton("btn_function")->setStateCheck(false);

		//_setImageVisible("bg_network",true);
		//_setImageVisible("bg_function",false);
		_setImageVisible("bg_video",false);
		_setImageVisible("bg_audio",false);

	}
	//----------------------------------------------------------------------------------------
	void UISystemSetting::_onClickBtnApplyVideo()
	{
		applyVideoSetting();
	}
	//----------------------------------------------------------------------------------------
	void UISystemSetting::_onClickBtnApplyAudio()
	{
		applyAudioSetting();
	}
	//----------------------------------------------------------------------------------------
	void UISystemSetting::onHScrollPostionSetPostFXLevel(void* widget, Int pos)
	{
		//char msg[16];
		//ZeroMemory(msg, 16);
		//sprintf_s( msg, _countof(msg), "%d\n", pos );

		//OutputDebugString(msg);

	}
	//----------------------------------------------------------------------------------------
	void UISystemSetting::onHScrollPostionSetShadowLevel(void* widget, Int pos)
	{
		//char msg[16];
		//ZeroMemory(msg, 16);
		//sprintf_s( msg, _countof(msg), "%d\n", pos );

		//OutputDebugString(msg);

	}
	//----------------------------------------------------------------------------------------
	void UISystemSetting::onHScrollPostionSetParticleLevel(void *widget, Int pos)
	{
		
	}
	//----------------------------------------------------------------------------------------
	void UISystemSetting::onHScrollPostionSetMaterialLevel(void *widget, Int pos)
	{

	}
	//----------------------------------------------------------------------------------------
	void UISystemSetting::onClickCheckBtnEnableFullScreen(void* widget)
	{
		IWidget* iwidget = (IWidget*)widget;
		if ( iwidget )
		{
			IButton* ibutton = iwidget->getButton();
			if ( ibutton )
			{
				ibutton->setStateCheck(!ibutton->getStateCheck());
			}
		}
	}
	//----------------------------------------------------------------------------------------
	void UISystemSetting::onClickCheckBtnEnableVsync(void* widget)
	{
		IWidget* iwidget = (IWidget*)widget;
		if ( iwidget )
		{
			IButton* ibutton = iwidget->getButton();
			if ( ibutton )
			{
				ibutton->setStateCheck(!ibutton->getStateCheck());
			}
		}
	}
	//----------------------------------------------------------------------------------------
	void UISystemSetting::onClickCheckBtnEnableWaterReflection(void* widget)
	{
		IWidget* iwidget = (IWidget*)widget;
		if ( iwidget )
		{
			IButton* ibutton = iwidget->getButton();
			if ( ibutton )
			{
				ibutton->setStateCheck(!ibutton->getStateCheck());
			}
		}
	}
	//----------------------------------------------------------------------------------------
	void UISystemSetting::onClickCheckBtnEnableHighLevelModel(void* widget)
	{
		IWidget* iwidget = (IWidget*)widget;
		if ( iwidget )
		{
			IButton* ibutton = iwidget->getButton();
			if ( ibutton )
			{
				ibutton->setStateCheck(!ibutton->getStateCheck());
			}
		}
	}
	//----------------------------------------------------------------------------------------
	void UISystemSetting::onClickCheckBtnEnableHighLevelTexture(void* widget)
	{
		IWidget* iwidget = (IWidget*)widget;
		if ( iwidget )
		{
			IButton* ibutton = iwidget->getButton();
			if ( ibutton )
			{
				ibutton->setStateCheck(!ibutton->getStateCheck());
			}
		}
	}
	//----------------------------------------------------------------------------------------
	void UISystemSetting::onClickCheckBtnEnableHighLevelTerrainObject(void* widget)
	{
		IWidget* iwidget = (IWidget*)widget;
		if ( iwidget )
		{
			IButton* ibutton = iwidget->getButton();
			if ( ibutton )
			{
				ibutton->setStateCheck(!ibutton->getStateCheck());
			}
		}
	}
	//----------------------------------------------------------------------------------------
	void UISystemSetting::onSelectCommoboxIndex(void* widget, Int index)
	{
		
		IWidget* iwidget = (IWidget*)widget;
		if (widget)
		{
			IComboBox* icombobox = iwidget->getComboBox();
			if(icombobox)
			{
				icombobox->setIndexSelected(index);
			}
		}
	}
	//----------------------------------------------------------------------------------------
	void UISystemSetting::onClickCheckBtnEnableBgSound( void* widget )
	{
			 IWidget* iwidget = (IWidget*)widget;
			 if (iwidget)
			 {
                  IButton* ibutton = iwidget->getButton();
				  if (ibutton)
				  {
                        ibutton->setStateCheck(!ibutton->getStateCheck());

				  }
			 }
	}

	void UISystemSetting::onClickCheckBtnEnableSilence( void* widget )
	{
		IWidget* iwidget = (IWidget*)widget;
		if (iwidget)
		{
			IButton* ibutton = iwidget->getButton();
			if (ibutton)
			{
				ibutton->setStateCheck(!ibutton->getStateCheck());

			}
		}
	}
	//----------------------------------------------------------------------------------------


}