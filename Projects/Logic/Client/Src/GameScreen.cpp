/******************************************************************************/
#include "stdafx.h"
#include "GameScreen.h"
#include "ClientMain.h"
#include "GameMain.h"
#include "CSceneManager.h"
#include "CAIManager.h"
#include "HeadDamageManage.h"
#include "GameMiniMapManager.h"
#include "SLGCameraOpCtrl.h"
#include "GameObjectOpCtrl.h"
#include "UIManage.h"
#include "CRegionObject.h"
#include "CRegionManager.h"
#include "GameRadarConfig.h"
#include "UIRPGMiniMap.h"
#include "UISLGMap.h"
#include "UIBigCityMiniMap.h"
#include "UIJumpOutRegion.h"
#include "UIClanControl.h"
#include "UILoadingProgress.h"
#include "LoginManager.h"
#include "NetPacketPackManager.h"
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------------
    Str GameScreen::STATE_NAME = "GameScreen";
    //-----------------------------------------------------------------------------
    GameScreen::GameScreen()
        :IScreen( STATE_NAME )
    {
        setManagedLifeTime( false );
    }

    //-----------------------------------------------------------------------------
    GameScreen::~GameScreen()
    {
    }

    //-----------------------------------------------------------------------------
    void GameScreen::update( Flt delta )
    {
        HeadDamageManage::getInstance().update( delta );
        GameMiniMapManager::getInstance().update( delta );
    }

    //-----------------------------------------------------------------------------
    Bool GameScreen::isFinished()
    {

        return false;
    }

    //-----------------------------------------------------------------------------
    void GameScreen::onEnter()
    {
        GameMain::getInstance().clearOperatorCtrls();

        // 设置操作
        GameMain::getInstance().addOperatorCtrls( &GameObjectOpCtrl::getInstance() );

        // 设置摄像机
        ICamera* camera = ClientMain::getInstance().getScene()->getActiveCamera();
		if ( camera )
		{
			camera->setNearClipDistance(2);
			camera->setFarClipDistance(2000);
			camera->setFov(45);

			SLGCameraOpCtrl::getInstance().setCamera( camera );
			GameMain::getInstance().addOperatorCtrls( &SLGCameraOpCtrl::getInstance() );
		}

		// 设置了资源读取监听器
		ClientMain::getInstance().getScene()->setResourceLoadListener(this);

		// 开启tree管理器
		ClientMain::getInstance().getEngine()->unLockTreeManager();

		// 进入游戏
		UIClanControl::getInstance().joinGame();
    }

    //-----------------------------------------------------------------------------
    void GameScreen::onLeave()
    {
        // 清空操作管理
        GameMain::getInstance().clearOperatorCtrls();
        // 清空AI
        CAIManager::getInstance().clear();
		// 清空网络打包管理器
		NetPacketPackManager::getInstance().clear();
    }

	//-----------------------------------------------------------------------------
	void GameScreen::onInitResourceLoadListener()
	{
		mTerrainTotalProgress = 0.3f;
		mObjectTotalProgress = 0.7f;
	}

	//-----------------------------------------------------------------------------
	void GameScreen::onClearResourceLoadListener()
	{
		mFreshTime = 0.0f;
	}

	//-----------------------------------------------------------------------
	void GameScreen::preLoadTerrainChunk( UInt index, UInt total )
	{

	}

	//-----------------------------------------------------------------------
	void GameScreen::postLoadTerrainChunk( UInt index, UInt total )
	{
		Flt cur_progress = UILoadingProgress::getInstance().getValue();

		if ( total == 0 )
		{
			UILoadingProgress::getInstance().setValue(mTerrainTotalProgress);
			ClientMain::getInstance().getEngine()->renderOneFrame( ClientMain::getInstance().getDelta() );
			return;
		}

		Flt inc_progress = mTerrainTotalProgress / (Flt)total;		
		cur_progress += ( inc_progress );
		UILoadingProgress::getInstance().setValue(cur_progress);

		ClientMain::getInstance().getEngine()->renderOneFrame( ClientMain::getInstance().getDelta() );
	}

	//-----------------------------------------------------------------------
	void GameScreen::preloadObject( UInt index, UInt total )
	{
	}

	//-----------------------------------------------------------------------
	void GameScreen::postloadObject( ISceneObject* object, UInt index, UInt total )
	{
		if ( total == 0 )
		{
			UILoadingProgress::getInstance().setValue(mTerrainTotalProgress + mObjectTotalProgress);
			ClientMain::getInstance().getEngine()->renderOneFrame( ClientMain::getInstance().getDelta() );
			return;
		}

		Flt new_progress = Flt(index + 1) / (Flt)total * mObjectTotalProgress + mTerrainTotalProgress;		
		UILoadingProgress::getInstance().setValue(new_progress);

		if ( new_progress - mFreshTime > 0.01f )
		{
			mFreshTime = new_progress;

			ClientMain::getInstance().getEngine()->renderOneFrame( ClientMain::getInstance().getDelta() );
		}			
	}

    //-----------------------------------------------------------------------------
    void GameScreen::onStartLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType )
    {
		// 清空网络打包管理器
		NetPacketPackManager::getInstance().clear();
    }

    //-----------------------------------------------------------------------------
    void GameScreen::onEndLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType )
    {
        // 加载界面
		CRegionObject* currRegion = CSceneManager::getInstance().getCurrRegion();
		DYNAMIC_ASSERT(currRegion);
		GameType currType = currRegion->getGameType();
		UIManager::getInstance().setGameType(currType);
        UIManager::getInstance().loadUI();
		
		

        /////////////////////////////////////////////////////////////////////////////////////////////

        //设置镜头参数
        CRegionObject* newRegion = CRegionManager::getInstance().getRegionObjectById(regionType, regionId);
        if ( newRegion && newRegion->getData() )
        {
            ArtMapResCsvInfo* mapResInfo = newRegion->getData()->getArtMapResCsvInfo();

			 //设置镜头
			U32	cameraID = ( newRegion->getGameType() == GameType_Rpg ) ? mapResInfo->rpgCameraId: mapResInfo->slgCameraId;
            const GameCameraConfigInfo* camInfo = GameCameraConfig::getInstance().getGameCameraConfigInfo(cameraID);
            if ( camInfo )
            {	
                SLGCameraOpCtrl::getInstance().applyCameraSetting(camInfo);
            }

            //设置小地图信息
			U32 radarID = ( newRegion->getGameType() == GameType_Rpg ) ? mapResInfo->rpgRadarId : mapResInfo->slgRadarId;
            const GameRadarConfigInfo* radarInfo = GameRadarConfig::getInstance().getGameRadarConfigInfo(radarID);
            if ( radarInfo )
            {	
                GameMiniMap* minimap = GameMiniMapManager::getInstance().getMiniMap("Radar");
                if ( minimap )
                {
                    minimap->loadMap( radarInfo->fileName, radarInfo->filePath, radarInfo->worldSize, radarInfo->worldCenter );
                    
                    Str16 mapName = newRegion->getData()->getMapListCsvInfo()->mapName;
					
					if (currType == GameType_Slg)
					{
						UISLGMap::getInstance().setMapName(mapName);
					}
					else if (currType == GameType_Max)
					{
						UIBigCityMiniMap::getInstance().setMapName(mapName);
					}
					else
						UIRPGMiniMap::getInstance().setMapName(mapName);
                    // 保存地图类型
                    MapType mapType = newRegion->getData()->getMapListCsvInfo()->mapType;

                    //跳出大地图的UI
                    if (MT_Distribution == mapType || MT_Place == mapType)
                    {
                        UIJumpOutRegion::getInstance().closeGui();
                    }
                    else if(MT_Instance == mapType)
                    {
                        UIJumpOutRegion::getInstance().openGui();
                    }
                }
            }
        }
    }

    //-----------------------------------------------------------------------------
    void GameScreen::onUnloadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType )
    {
        // 清空AI
        CAIManager::getInstance().clear();

        //释放小地图
        GameMiniMap* minimap = GameMiniMapManager::getInstance().getMiniMap("Radar");
        if ( minimap )
        {
            minimap->unloadMap();
        }

        //当场景销毁时，要把所有头顶血泡关掉。
        HeadDamageManage::getInstance().clearAllImage();

		// 清空网络打包管理器
		NetPacketPackManager::getInstance().clear();
    }



}


