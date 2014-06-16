//***************************************************************************************************
#include "stdafx.h"
#include "UIBigCityMiniMap.h"
#include "CSceneManager.h"
#include "ClientMain.h"
#include "IInput.h"
#include "PlayerNetPacketProcesser.h"
#include "CPlayer.h"
#include "UIMessageBox.h"
#include "GameRadar.h"
#include "SLGCameraOpCtrl.h"
//***************************************************************************************************
namespace MG
{
    UIBigCityMiniMap::UIBigCityMiniMap()
    {
		GameRadar* gameRadar = dynamic_cast<GameRadar*>(GameMiniMapManager::getInstance().getMiniMap( "Radar" ));
		if ( gameRadar )
		{
			gameRadar->setListener(this);
		}
    }
    //----------------------------------------------------------------------------------------
    UIBigCityMiniMap::~UIBigCityMiniMap()
    {
		GameRadar* gameRadar = dynamic_cast<GameRadar*>(GameMiniMapManager::getInstance().getMiniMap( "Radar" ));
		if ( gameRadar )
		{
			gameRadar->setListener(NULL);
		}
    }
    //----------------------------------------------------------------------------------------
    void UIBigCityMiniMap::setEvent()
    {
		getLayout()->getImage("map_pic")->getWidget()->setMouseButtonClickEvent(onClickMiniMap);
		getLayout()->getImage("map_pic")->getWidget()->setMouseDragEvent(onDragMiniMap);
    }

	//----------------------------------------------------------------------------------------
	void UIBigCityMiniMap::init()
	{
	}

	 //----------------------------------------------------------------------------------------
	void UIBigCityMiniMap::onClickSetFlag( void* widget )
	{
		DYNAMIC_ASSERT(widget);

	}
	 //----------------------------------------------------------------------------------------
	void UIBigCityMiniMap::onClickPathSearch( void* widget )
	{
		DYNAMIC_ASSERT(widget);

	}
	 //----------------------------------------------------------------------------------------
	void UIBigCityMiniMap::onClickMap( void* widget )
	{
		DYNAMIC_ASSERT(widget);

	}
	//----------------------------------------------------------------------------------------
	void UIBigCityMiniMap::onDragMiniMap( void* widget, Int left, Int top )
	{
		DYNAMIC_ASSERT(widget);

		IWidget* _widget = static_cast<IWidget*>(widget);
		if ( _widget )
		{
			IInput* inputMgr = ClientMain::getInstance().getEngine()->input();
			ITerrainManager* terrainMgr = ClientMain::getInstance().getScene()->getTerrainManager();

			if ( !inputMgr ||
				!terrainMgr )
				return;

			CoordI coordi = _widget->getAbsoluteCoord();
			Vec2 mousePos = inputMgr->getMousePos();

			VecI2 containerPos;
			containerPos.x = (U32)mousePos.x - (U32)coordi.left;
			containerPos.y = (U32)mousePos.y - (U32)coordi.top;

			GameRadar* gameRadar = dynamic_cast<GameRadar*>(GameMiniMapManager::getInstance().getMiniMap( "Radar" ));
			if ( gameRadar )
			{
				VecI2 imagePos = gameRadar->convertContainerPositionToImagePosition( containerPos );  
				Vec2 world2DPos = gameRadar->convertImagePositionToWorldPosition(imagePos);

				if ( !SLGCameraOpCtrl::getInstance().isTrackCamera() )
				{
					Flt height = 0.0f;
					if ( terrainMgr->getStickHeight( world2DPos, height ) )
						SLGCameraOpCtrl::getInstance().focusPos( Vec3(world2DPos.x, height, world2DPos.y) );
				}
			}
		}
	}
	//----------------------------------------------------------------------------------------
	void UIBigCityMiniMap::onClickMiniMap( void* widget )
	{
		DYNAMIC_ASSERT(widget);

		IWidget* _widget = static_cast<IWidget*>(widget);
		if ( _widget )
		{
			IInput* inputMgr = ClientMain::getInstance().getEngine()->input();
			ITerrainManager* terrainMgr = ClientMain::getInstance().getScene()->getTerrainManager();

			if ( !inputMgr ||
				!terrainMgr )
				return;

			CoordI coordi = _widget->getAbsoluteCoord();
			Vec2 mousePos = inputMgr->getMousePos();

			VecI2 containerPos;
			containerPos.x = (U32)mousePos.x - (U32)coordi.left;
			containerPos.y = (U32)mousePos.y - (U32)coordi.top;

			GameRadar* gameRadar = dynamic_cast<GameRadar*>(GameMiniMapManager::getInstance().getMiniMap( "Radar" ));
			if ( gameRadar )
			{
				VecI2 imagePos = gameRadar->convertContainerPositionToImagePosition( containerPos );  
				Vec2 world2DPos = gameRadar->convertImagePositionToWorldPosition(imagePos);

				if ( !SLGCameraOpCtrl::getInstance().isTrackCamera() )
				{
					Flt height = 0.0f;
					if ( terrainMgr->getStickHeight( world2DPos, height ) )
						SLGCameraOpCtrl::getInstance().focusPos( Vec3(world2DPos.x, height, world2DPos.y) );
				}
			}
		}
	}
	//----------------------------------------------------------------------------------------
	void UIBigCityMiniMap::setMapName( Str16 mapName )
	{
        getLayout()->getText("map_name")->getWidget()->setCaption(mapName);
	}
	//----------------------------------------------------------------------------------------
	void UIBigCityMiniMap::update(Flt delta)
	{
		//if ( ClientMain::getInstance() )
	}
	//----------------------------------------------------------------------------------------
	void UIBigCityMiniMap::onMiniMapLoaded(GameMiniMap* miniMap)
	{
		GameRadar* gameRadar = dynamic_cast<GameRadar*>(miniMap);
		if ( gameRadar )
		{
			gameRadar->setContainerWidget(getLayout()->getImage("map_pic"));
		}
	}
	//----------------------------------------------------------------------------------------
	void UIBigCityMiniMap::onMiniMapUnLoad(GameMiniMap* miniMap)
	{
		GameRadar* gameRadar = dynamic_cast<GameRadar*>(miniMap);
		if ( gameRadar )
		{
			gameRadar->releaseContainerWidget(getLayout()->getImage("map_pic"));
		}
	}
}