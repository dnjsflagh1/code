//***************************************************************************************************
#include "stdafx.h"

#include "ChannelInfo.h"
//#include "MapObject.h"
//#include "PlaceObject.h"
#include "UIJumpRegion.h"
//#include "ChatNetPacket.h"
#include "PlayCharacterNetPacketProcesser.h"
//#include "RegionObject.h"
//***************************************************************************************************
namespace MG
{
    UIJumpRegion::UIJumpRegion()
    {
		mCurrCharacterId = 0;
		mCurrSelectRegion = 0;
    }
    //----------------------------------------------------------------------------------------
    UIJumpRegion::~UIJumpRegion()
    {

    }
    //----------------------------------------------------------------------------------------
    void UIJumpRegion::setEvent()
    {
		IForm* mainForm = getLayout()->getForm("_Main");
		DYNAMIC_ASSERT(mainForm);
		mainForm->setWindowButtonPressedEvent(onClickCloseBtn);

		IList* regionList = getLayout()->getList("list_regionMap");
		DYNAMIC_ASSERT(regionList);
		regionList->setEventListMouseItemActivate(onSelectRegion);

		IButton* enterBtn = getLayout()->getButton("btn_enterRegion");
		DYNAMIC_ASSERT(enterBtn);
		enterBtn->getWidget()->setMouseButtonClickEvent(onEnterRegion);
    }
	//----------------------------------------------------------------------------------------
	Bool UIJumpRegion::openGui()
	{
		return UIObject::openGui();
	}
	//----------------------------------------------------------------------------------------
	void UIJumpRegion::addRegion( CRegionObject* region )
	{
#if 0
		IList* regionList = getLayout()->getList("list_regionMap");
		DYNAMIC_ASSERT(regionList);
		if (region->getType() == ROT_MAP)
		{
			//mRegionMap[regionList->getItemCount()] = region;
			//MapObject_OldVersion* mapObj = (MapObject_OldVersion*)region;
			//regionList->addItem(mapObj->getMapObjInfo()->name);
		}
		else if ((region->getType() == ROT_PLACE))
		{

			//PlaceObject_OldVersion* placeObj = (PlaceObject_OldVersion*)region;
			//mRegionMap[regionList->getItemCount()] = region;
			//regionList->addItem(placeObj->getPlaceObjInfo()->name);
		}
		else
		{
			Int kkkk = 0;
		}
#endif
		
	}
	//----------------------------------------------------------------------------------------
	void UIJumpRegion::_clear()
	{
		IList* regionList = getLayout()->getList("list_regionMap");
		DYNAMIC_ASSERT(regionList);
		regionList->removeAllItems();
		mRegionMap.clear();
		
	}
	//----------------------------------------------------------------------------------------
	void UIJumpRegion::onClickCloseBtn( void* widget )
	{
		DYNAMIC_ASSERT(widget);
		UIJumpRegion::getInstance()._clear();
		UIJumpRegion::getInstance().closeGui();
	}
	//----------------------------------------------------------------------------------------
	void UIJumpRegion::onSelectRegion( void* widget, Int index )
	{
		DYNAMIC_ASSERT(widget);
		UIJumpRegion::getInstance().setCurrRegionIndex(index);

	}
	//----------------------------------------------------------------------------------------
	void UIJumpRegion::setCurrRegionIndex(U32 index)
	{
		mCurrSelectRegion = index;
	}
	//----------------------------------------------------------------------------------------
	CRegionObject* UIJumpRegion::getCurrSelectRegion()
	{
		if (mRegionMap.empty())
		{
			return NULL;
		}
		std::map<U32,CRegionObject*>::iterator it = mRegionMap.find(mCurrSelectRegion);
		if (it != mRegionMap.end())
		{
			return it->second;
		}
		return NULL;
	}
	//----------------------------------------------------------------------------------------
	void UIJumpRegion::onEnterRegion( void* widget )
	{
#if 0
		DYNAMIC_ASSERT(widget);
		CRegionObjectNew* regionObj = UIJumpRegion::getInstance().getCurrSelectRegion();
		PlayCharacterNetPacketProcesser::getInstance().sendPlayerCharacterJumpRegion(
			UIJumpRegion::getInstance().getCurrCharacterId(),regionObj->getID(),regionObj->getType());
#endif
	}
	//----------------------------------------------------------------------------------------
	void UIJumpRegion::setCurrCharacter( IdType characterId )
	{
		mCurrCharacterId =characterId;
	}
	//----------------------------------------------------------------------------------------
	IdType UIJumpRegion::getCurrCharacterId()
	{
		return mCurrCharacterId;
	}
	//----------------------------------------------------------------------------------------




}