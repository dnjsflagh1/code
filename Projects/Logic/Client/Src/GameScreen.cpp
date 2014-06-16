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

        // ���ò���
        GameMain::getInstance().addOperatorCtrls( &GameObjectOpCtrl::getInstance() );

        // ���������
        ICamera* camera = ClientMain::getInstance().getScene()->getActiveCamera();
		if ( camera )
		{
			camera->setNearClipDistance(2);
			camera->setFarClipDistance(2000);
			camera->setFov(45);

			SLGCameraOpCtrl::getInstance().setCamera( camera );
			GameMain::getInstance().addOperatorCtrls( &SLGCameraOpCtrl::getInstance() );
		}

		// ��������Դ��ȡ������
		ClientMain::getInstance().getScene()->setResourceLoadListener(this);

		// ����tree������
		ClientMain::getInstance().getEngine()->unLockTreeManager();

		// ������Ϸ
		UIClanControl::getInstance().joinGame();
    }

    //-----------------------------------------------------------------------------
    void GameScreen::onLeave()
    {
        // ��ղ�������
        GameMain::getInstance().clearOperatorCtrls();
        // ���AI
        CAIManager::getInstance().clear();
		// ���������������
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
		// ���������������
		NetPacketPackManager::getInstance().clear();
    }

    //-----------------------------------------------------------------------------
    void GameScreen::onEndLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType )
    {
        // ���ؽ���
		CRegionObject* currRegion = CSceneManager::getInstance().getCurrRegion();
		DYNAMIC_ASSERT(currRegion);
		GameType currType = currRegion->getGameType();
		UIManager::getInstance().setGameType(currType);
        UIManager::getInstance().loadUI();
		
		

        /////////////////////////////////////////////////////////////////////////////////////////////

        //���þ�ͷ����
        CRegionObject* newRegion = CRegionManager::getInstance().getRegionObjectById(regionType, regionId);
        if ( newRegion && newRegion->getData() )
        {
            ArtMapResCsvInfo* mapResInfo = newRegion->getData()->getArtMapResCsvInfo();

			 //���þ�ͷ
			U32	cameraID = ( newRegion->getGameType() == GameType_Rpg ) ? mapResInfo->rpgCameraId: mapResInfo->slgCameraId;
            const GameCameraConfigInfo* camInfo = GameCameraConfig::getInstance().getGameCameraConfigInfo(cameraID);
            if ( camInfo )
            {	
                SLGCameraOpCtrl::getInstance().applyCameraSetting(camInfo);
            }

            //����С��ͼ��Ϣ
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
                    // �����ͼ����
                    MapType mapType = newRegion->getData()->getMapListCsvInfo()->mapType;

                    //�������ͼ��UI
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
        // ���AI
        CAIManager::getInstance().clear();

        //�ͷ�С��ͼ
        GameMiniMap* minimap = GameMiniMapManager::getInstance().getMiniMap("Radar");
        if ( minimap )
        {
            minimap->unloadMap();
        }

        //����������ʱ��Ҫ������ͷ��Ѫ�ݹص���
        HeadDamageManage::getInstance().clearAllImage();

		// ���������������
		NetPacketPackManager::getInstance().clear();
    }



}


