//***************************************************************************************************
#include "stdafx.h"
#include "UIMiniMap.h"
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
    UIMiniMap::UIMiniMap()
    {
		GameRadar* gameRadar = dynamic_cast<GameRadar*>(GameMiniMapManager::getInstance().getMiniMap( "Radar" ));
		if ( gameRadar )
		{
			gameRadar->setListener(this);
		}
    }
    //----------------------------------------------------------------------------------------
    UIMiniMap::~UIMiniMap()
    {
		GameRadar* gameRadar = dynamic_cast<GameRadar*>(GameMiniMapManager::getInstance().getMiniMap( "Radar" ));
		if ( gameRadar )
		{
			gameRadar->setListener(NULL);
		}
    }
    //----------------------------------------------------------------------------------------
    void UIMiniMap::setEvent()
    {
		getLayout()->getButton("biaoji")->getWidget()->setMouseButtonClickEvent(onClickSetFlag);
		getLayout()->getButton("xunlu")->getWidget()->setMouseButtonClickEvent(onClickPathSearch);
		getLayout()->getButton("map")->getWidget()->setMouseButtonClickEvent(onClickMap);
		getLayout()->getImage("minimap")->getWidget()->setMouseButtonClickEvent(onClickMiniMap);
		getLayout()->getImage("minimap")->getWidget()->setMouseDragEvent(onDragMiniMap);
    }

	//----------------------------------------------------------------------------------------
	void UIMiniMap::init()
	{
	}

	 //----------------------------------------------------------------------------------------
	void UIMiniMap::onClickSetFlag( void* widget )
	{
		DYNAMIC_ASSERT(widget);

	}
	 //----------------------------------------------------------------------------------------
	void UIMiniMap::onClickPathSearch( void* widget )
	{
		DYNAMIC_ASSERT(widget);

	}
	 //----------------------------------------------------------------------------------------
	void UIMiniMap::onClickMap( void* widget )
	{
		DYNAMIC_ASSERT(widget);

	}
	//----------------------------------------------------------------------------------------
	void UIMiniMap::onDragMiniMap( void* widget, Int left, Int top )
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
	void UIMiniMap::onClickMiniMap( void* widget )
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
	void UIMiniMap::setMapName( Str16 mapName )
	{
        getLayout()->getText("maptext")->getWidget()->setCaption(mapName);
	}
	//----------------------------------------------------------------------------------------
	void UIMiniMap::update(Flt delta)
	{
		//if ( ClientMain::getInstance() )
	}
	//----------------------------------------------------------------------------------------
	void UIMiniMap::onMiniMapLoaded(GameMiniMap* miniMap)
	{
		GameRadar* gameRadar = dynamic_cast<GameRadar*>(miniMap);
		if ( gameRadar )
		{
			gameRadar->setContainerWidget(getLayout()->getImage("minimap"));
		}
	}
	//----------------------------------------------------------------------------------------
	void UIMiniMap::onMiniMapUnLoad(GameMiniMap* miniMap)
	{
		GameRadar* gameRadar = dynamic_cast<GameRadar*>(miniMap);
		if ( gameRadar )
		{
			gameRadar->releaseContainerWidget(getLayout()->getImage("minimap"));
		}
	}
}