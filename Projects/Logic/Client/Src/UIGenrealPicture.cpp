//***************************************************************************************************
#include "stdafx.h"
#include "UIGenrealPicture.h"
#include "CPlayer.h"
#include "CSceneManager.h"
#include "ClientMain.h"

#include "SLGCameraOpCtrl.h"
#include "ArtIconResCsv.h"
//***************************************************************************************************
namespace MG
{
	UIGenrealPicture::UIGenrealPicture() : mCharacterId(0)
    {

    }
    //----------------------------------------------------------------------------------------
    UIGenrealPicture::~UIGenrealPicture()
    {

    }
    //----------------------------------------------------------------------------------------
    void UIGenrealPicture::setEvent()
    {
		
		IImage* img = getLayout()->getImage("head-large01");
		DYNAMIC_ASSERT(img);
		img->getWidget()->setMouseButtonDoubleClickEvent(onDoubleClickGenrealHead);
		
	}
	//----------------------------------------------------------------------------------------
	Bool UIGenrealPicture::setCharacterId(IdType id)
	{
		mCharacterId = id;

		if (id == 0)
		{
			return false;
		}

		setMp(mCharacterId);
		//setSp(mCharacterId);
		setHp(mCharacterId);

		CPlayerCharacter* playerCharacter = CPlayer::getInstance().getActiveClan()->getPlayerCharacter(id);
		DYNAMIC_ASSERT(playerCharacter);

		setGenrealName(playerCharacter->getNormalName());
        
		///ÉèÖÃÍ¼Ïñ
		const ArtIconResCsvInfo* tempResInfo =ArtIconResCsv::getInstance().getIconArtResInfo(playerCharacter->getData()->charArtIcon);       
		DYNAMIC_ASSERT_LOG(tempResInfo,"tempResInfo == NULL!");
		if (tempResInfo != NULL)
		{
			IImage *headimg = getLayout()->getImage("head-large01");
			headimg->setItemGroup(tempResInfo->SmallGroupName);
			headimg->setItemResource(tempResInfo->SmallResName);
			headimg->setItemName(tempResInfo->SmallItemName);
		}
		setLV(playerCharacter->getLevel());
		return true;
	}
	//----------------------------------------------------------------------------------------
	void UIGenrealPicture::setMp(PlayerCharacterIdType playerCharacterId)
	{
		if ( playerCharacterId != mCharacterId)
		  return;

		CPlayerCharacter* playerCharacter = CPlayer::getInstance().getActiveClan()->getPlayerCharacter(playerCharacterId);
		DYNAMIC_ASSERT(playerCharacter);

		setMp(playerCharacter);

	}
	//----------------------------------------------------------------------------------------
	void UIGenrealPicture::setSp(PlayerCharacterIdType playerCharacterId)
	{
		//IProgress* progress = getLayout()->getProgress("process_mp");
		//DYNAMIC_ASSERT(progress);
		//if (!progress)
		//{
		//	return;
		//}

		//progress->setProgressPosition(currSP/(1.f*maxSp));
	}
	//----------------------------------------------------------------------------------------
	void UIGenrealPicture::setHp(PlayerCharacterIdType playerCharacterId)
	{
		if ( playerCharacterId != mCharacterId)
			return;

		CPlayerCharacter* playerCharacter = CPlayer::getInstance().getActiveClan()->getPlayerCharacter(playerCharacterId);
		DYNAMIC_ASSERT(playerCharacter);
		setHp(playerCharacter);

	}
	//----------------------------------------------------------------------------------------
	void UIGenrealPicture::setLV( U32 lv )
	{
		Str16 tempLV(L"");
		MGStrOp::toString(lv,tempLV);
		IText* txtlv = getLayout()->getText("lvtext-large01");
		txtlv->getWidget()->setCaption(tempLV);
	}

	void UIGenrealPicture::setHp(CPlayerCharacter* playerCharacter)
	{
		IProgress* progress = getLayout()->getProgress("HP-large01");
		DYNAMIC_ASSERT(progress);

		Flt currHp = playerCharacter->getHp();
		Flt maxHp = playerCharacter->getMaxHp();

		progress->setProgressPosition( currHp/maxHp );

		Char16 tempMpMsg[32] = {0};
		swprintf_s(tempMpMsg, 32, L"%d/%d",(Int)currHp , (Int)maxHp);
		progress->getWidget()->setCaption(tempMpMsg);
	}

	void UIGenrealPicture::setSp(CPlayerCharacter* playerCharacter)
	{

	}

	void UIGenrealPicture::setMp(CPlayerCharacter* playerCharacter)
	{
		IProgress* progress = getLayout()->getProgress("MP-large01");
		DYNAMIC_ASSERT(progress);

		Flt currMp = playerCharacter->getMp();
		Flt maxMp = playerCharacter->getMaxMp();

		progress->setProgressPosition( currMp/maxMp );

		Char16 tempMpMsg[32] = {0};
		swprintf_s(tempMpMsg, 32, L"%d/%d",(Int)currMp , (Int)maxMp);
		progress->getWidget()->setCaption(tempMpMsg);
	}

	void UIGenrealPicture::setLV(CPlayerCharacter* playerCharacter)
	{
		U32 level = (U32)playerCharacter->getLevel();
		setLV(level);
	}

	//----------------------------------------------------------------------------------------
	void UIGenrealPicture::setGenrealHead( UInt index )
	{
		IImage* img = getLayout()->getImage("img_head");
		DYNAMIC_ASSERT(img);
		//get....
		//img->setItemGroup()
		//img->setItemName()
	}
	//----------------------------------------------------------------------------------------
	void UIGenrealPicture::setGenrealName( Str16 name )
	{
		IText* text = getLayout()->getText("nametext-large01");
		DYNAMIC_ASSERT(text);
		if (!text)
		{
			return;
		}
		text->getWidget()->setCaption(name);
	}
	//----------------------------------------------------------------------------------------
	void UIGenrealPicture::onDoubleClickGenrealHead( void* widget )
	{
		DYNAMIC_ASSERT(widget);
		IdType id = CPlayer::getInstance().getActiveClan()->getMainGenrealID();
		SLGCameraOpCtrl::getInstance().focusPos(id);
	}
	//----------------------------------------------------------------------------------------
	IdType UIGenrealPicture::getCharacterId()
	{
		return mCharacterId;
	}

	void UIGenrealPicture::update(Flt delta)
	{
		/*
		if (!isOpen())
		{
			return;
		}
		CPlayerCharacter* playerCharacter = CPlayer::getInstance().getActiveClan()->getPlayerCharacter(mCharacterId);
        if (!playerCharacter)
		{
			return;
		}

		setMp(playerCharacter->getMaxMp(),playerCharacter->getMp());
		//setSp(playerCharacter->getMaxSp(),playerCharacter->getSp());
		setHp(playerCharacter->getMaxHp(),playerCharacter->getHp());
		setLV(playerCharacter->getLevel());
		*/
		
	}

	
	//----------------------------------------------------------------------------------------
}