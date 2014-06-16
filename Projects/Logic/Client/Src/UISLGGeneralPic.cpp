//***************************************************************************************************
#include "stdafx.h"
#include "UISLGGeneralPic.h"
#include "CPlayer.h"
#include "CSceneManager.h"
#include "ClientMain.h"

#include "SLGCameraOpCtrl.h"
#include "ArtIconResCsv.h"
#include "UISLGSkillInfo.h"
//***************************************************************************************************
namespace MG
{
	UISLGGeneralPic::UISLGGeneralPic() : mCharacterId(0)
    {

    }
    //----------------------------------------------------------------------------------------
    UISLGGeneralPic::~UISLGGeneralPic()
    {

    }
    //----------------------------------------------------------------------------------------
    void UISLGGeneralPic::setEvent()
    {
		
		IImage* img = getLayout()->getImage("pic");
		DYNAMIC_ASSERT(img);
		img->getWidget()->setMouseButtonClickEvent(onClickGenrealHead);
		
	}
	
	//----------------------------------------------------------------------------------------
	void UISLGGeneralPic::onClickGenrealHead( void* widget )
	{
		DYNAMIC_ASSERT(widget);
		IdType id = CPlayer::getInstance().getActiveClan()->getMainGenrealID();
		SLGCameraOpCtrl::getInstance().focusPos(id);
		UISLGSkillInfo::getInstance().UIRefresh(true,-1);
	}
	//----------------------------------------------------------------------------------------
	void UISLGGeneralPic::setCharacterId(IdType id)
	{
		DYNAMIC_ASSERT(id);
		if (id != mCharacterId)
		{
			mCharacterId = id;

			CPlayerCharacter* playerCharacter = CPlayer::getInstance().getActiveClan()->getPlayerCharacter(mCharacterId);
			DYNAMIC_ASSERT(playerCharacter);

			///ÉèÖÃÍ¼Ïñ
			const ArtIconResCsvInfo* tempResInfo =ArtIconResCsv::getInstance().getIconArtResInfo(playerCharacter->getData()->charArtIcon);       
			DYNAMIC_ASSERT_LOG(tempResInfo,"tempResInfo == NULL!");
			if (tempResInfo != NULL)
			{
				IImage *headimg = getLayout()->getImage("pic");
				headimg->setItemGroup(tempResInfo->GroupName);
				headimg->setItemResource(tempResInfo->ResName);
				headimg->setItemName(tempResInfo->ItemName);
			}
		}
	}
}