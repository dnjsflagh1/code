//***************************************************************************************************
#include "stdafx.h"

#include "ChannelInfo.h"
//#include "MapObject.h"
//#include "PlaceObject.h"
#include "UICharacterJumpRegion.h"
//#include "ChatNetPacket.h"
//#include "PlayerCharacter.h"
#include "PlayCharacterNetPacketProcesser.h"
//#include "RegionObject.h"
//***************************************************************************************************
namespace MG
{
    UICharacterJumpRegion::UICharacterJumpRegion()
    {
		mCurrSelectRegion	= NULL;
		mCurrCharacter		= NULL;		
    }
    //----------------------------------------------------------------------------------------
    UICharacterJumpRegion::~UICharacterJumpRegion()
    {

    }
    //----------------------------------------------------------------------------------------
    void UICharacterJumpRegion::setEvent()
    {
		IForm* mainForm = getLayout()->getForm("_Main");
		DYNAMIC_ASSERT(mainForm);
		mainForm->setWindowButtonPressedEvent(onClickCloseBtn);

		IButton* btn = getLayout()->getButton("btn_ok");
		DYNAMIC_ASSERT(btn);
		btn->getWidget()->setMouseButtonClickEvent(onEnterRegion);

		btn = getLayout()->getButton("btn_cancel");
		DYNAMIC_ASSERT(btn);
		btn->getWidget()->setMouseButtonClickEvent(onClickCloseBtn);

    }
	//----------------------------------------------------------------------------------------
	Bool UICharacterJumpRegion::openGui()
	{
		return UIObject::openGui();
	}
	//----------------------------------------------------------------------------------------
	void UICharacterJumpRegion::setCurrRegion( CRegionObject* region )
	{
		//DYNAMIC_ASSERT(region);
		mCurrSelectRegion = region;
	}
	//----------------------------------------------------------------------------------------
	void UICharacterJumpRegion::onClickCloseBtn( void* widget )
	{
		DYNAMIC_ASSERT(widget);
		UICharacterJumpRegion::getInstance().setCurrRegion(NULL);
		UICharacterJumpRegion::getInstance().setCurrCharacter(NULL);
		UICharacterJumpRegion::getInstance().closeGui();
	}
	//----------------------------------------------------------------------------------------
	CRegionObject* UICharacterJumpRegion::getCurrSelectRegion()
	{
		return mCurrSelectRegion;
	}
	//----------------------------------------------------------------------------------------
	void UICharacterJumpRegion::onEnterRegion( void* widget )
	{
#if 0
		DYNAMIC_ASSERT(widget);
		CRegionObjectNew* regionObj = UICharacterJumpRegion::getInstance().getCurrSelectRegion();
		PlayCharacterNetPacketProcesser::getInstance().sendPlayerCharacterJumpRegion(
		UICharacterJumpRegion::getInstance().getCurrCharacter()->getID(),regionObj->getID(),regionObj->getType());
		UICharacterJumpRegion::getInstance().closeGui();
#endif
	}
	//----------------------------------------------------------------------------------------
	void UICharacterJumpRegion::setCurrCharacter( CPlayerCharacter* character )
	{
		//DYNAMIC_ASSERT(character);
		mCurrCharacter = character;
	}
	//----------------------------------------------------------------------------------------
	CPlayerCharacter* UICharacterJumpRegion::getCurrCharacter()
	{
		return mCurrCharacter;
	}

	//----------------------------------------------------------------------------------------




}