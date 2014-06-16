//*************************************************************************************
#include "stdafx.h"
#include "UISelectPlace.h"
#include "PlayerNetPacketProcesser.h"
#include "PlayCharacterNetPacketProcesser.h"
#include "CSceneManager.h"
#include "CPlayer.h"
#include "UIInteractiveControl.h"
//#include "CWorldManager.h"
//*************************************************************************************
namespace MG
{
	//--------------------------------------------------------------------------------
	void UISelectPlace::setEvent()
	{
		IForm* mainForm = getLayout()->getForm("_Main");
		mainForm->setWindowButtonPressedEvent(onClickCloseBtn);
		IButton* enterPlaceButton = getLayout()->getButton("enterPlace");
		enterPlaceButton->getWidget()->setMouseButtonClickEvent(onEnterPlace);
		IButton* returnMapButton = getLayout()->getButton("return");
		returnMapButton->getWidget()->setMouseButtonClickEvent(onReturnMap);
	}
	//--------------------------------------------------------------------------------
	Bool UISelectPlace::openGui()
	{
		 return UIObject::openGui();
	}
	//--------------------------------------------------------------------------------
	MG::Bool UISelectPlace::closeGui()
	{
		return UIObject::closeGui();
	}
	//--------------------------------------------------------------------------------
	void UISelectPlace::setTitle( CChar16* title )
	{
		if(title)
		{
			IForm* mainForm  = getLayout()->getForm("_Main");

			if (mainForm)
			{
				mainForm->getWidget()->setCaption(title);
			}
		}
	}
	//--------------------------------------------------------------------------------
	void UISelectPlace::setDesc( CChar16* desc )
	{
		if (desc)
		{
			IEdit* descEdit = getLayout()->getEdit("desc");
			
			if (descEdit)
			{
				descEdit->setCaption(desc);
			}
			
		}
	}
	//--------------------------------------------------------------------------------
	void UISelectPlace::onClickCloseBtn( void* widget )
	{
		DYNAMIC_ASSERT(widget);
		UISelectPlace::getInstance().closeGui();
		UISelectPlace::getInstance().setCurrPlaceObj(0);
		UISelectPlace::getInstance().setCurrCharacterId(0);
		//UISelectPlace::getInstance().closeGui();

	}
	//--------------------------------------------------------------------------------
	void UISelectPlace::onEnterPlace( void* widget )
	{
		
		UIInteractiveControl::getInstance().clearInteractiveInfo();
		//PlayerNetPacketProcesser::getInstance().sendPlayerEnterRegion(ROT_PLACE, UISelectPlace::getInstance().getCurrPlaceObjId(),0);m
		//角色调地图
		PlayCharacterNetPacketProcesser::getInstance().jumpMapForUI( UISelectPlace::getInstance().mCharacterId,MT_Place, 
			UISelectPlace::getInstance().mCurrPlaceObjId,0,0);

		//玩家摄像机跳地图
		//const AccountIdType accountId = CPlayer::getInstance().getAccountID();
		//PlayerNetPacketProcesser::getInstance().sendPlayerEnterRegionByCharId(accountId, UISelectPlace::getInstance().mCharacterId);
	}

	void UISelectPlace::setCurrPlaceObj( PlaceIdType placeObjId )
	{
		mCurrPlaceObjId = placeObjId;
	}

	PlaceIdType UISelectPlace::getCurrPlaceObjId()
	{
		return mCurrPlaceObjId;
	}

	void UISelectPlace::onReturnMap( void* widget )
	{
          
	}
	//--------------------------------------------------------------------------------
	void UISelectPlace::openPlaceDialog( PlaceIdType placeId,PlayerCharacterIdType characterId )
	{
        if (placeId == 0 || characterId == 0)
           return;
		
		//设置标题
        setTitle(L"据点对话");
        //设置描述

		mCurrPlaceObjId = placeId;
		mCharacterId = characterId;
        openGui();
        
	}
	//--------------------------------------------------------------------------------
	void UISelectPlace::setCurrCharacterId( PlayerCharacterIdType characterId )
	{
            mCharacterId = characterId;
	}
	//--------------------------------------------------------------------------------
	MG::PlayerCharacterIdType UISelectPlace::getCurrCharacterId()
	{
             return mCharacterId;
	}
	//--------------------------------------------------------------------------------
}