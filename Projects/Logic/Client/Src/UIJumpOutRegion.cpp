//*************************************************************************************************************************
#include "stdafx.h"
#include "UIJumpOutRegion.h"
#include "PlayCharacterNetPacketProcesser.h"
#include "PlayerNetPacketProcesser.h"
#include "CPlayer.h"
#include "CPlayerCharacter.h"
#include "UIMessageBox.h"
//*************************************************************************************************************************
namespace MG
{
	//-----------------------------------------------------------------------
	void UIJumpOutRegion::setEvent()
	{
		
		//�佫����ͼ
		{
			IButton* btn =  getLayout()->getButton("Btn_JumpOut_Character");
			DYNAMIC_ASSERT(btn);
			if (btn)
			{
				btn->getWidget()->setMouseButtonClickEvent(onClickJumpOutCharacter);
			}
		}
	}

	//-----------------------------------------------------------------------
	void UIJumpOutRegion::onClickJumpOutCharacter(void* widget)
	{
		CPlayer* myPlayer = &(CPlayer::getInstance());
		CPlayerCharacter* myCharacter = myPlayer->getActiveClan()->getMainGenreal();
		DYNAMIC_ASSERT(NULL != myCharacter);
		if (MT_Distribution == myCharacter->getRegionType())
		{
			UIMessageBox::getInstance().showHint(L"����ǰ�� ���ͼ��");
			return;
		}

		if (MT_Place != myCharacter->getRegionType())
		{
			UIMessageBox::getInstance().showHint(L"ֻ���ڳ��� �������ͼ");
			return;
		}

		PlayCharacterNetPacketProcesser::getInstance().sendPlayerCharacterJumpOutRegion(myPlayer->getAccountID(), myCharacter->getID());
		//PlayerNetPacketProcesser::getInstance().sendPlayerEnterRegionByCharId(myPlayer->getAccountID(), myCharacter->getID());
	}

	//-----------------------------------------------------------------------
}