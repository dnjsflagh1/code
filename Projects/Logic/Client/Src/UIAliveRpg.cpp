//*************************************************************************************

#include "stdafx.h"
#include "UIAliveRpg.h"
#include "RegionNetPacketProcesser.h"
#include "CPlayer.h"

//*************************************************************************************
namespace MG
{
	//--------------------------------------------------------------------------------
	UIAliveRpg::UIAliveRpg()
	{
	}

	UIAliveRpg::~UIAliveRpg()
	{

	}

	void UIAliveRpg::setEvent()
	{
		//ԭ�ظ���
		{
			IButton* btnCreate = getLayout()->getButton("Btn_Alive_CurPos");
			DYNAMIC_ASSERT(btnCreate);
			btnCreate->getWidget()->setMouseButtonClickEvent(onClickButtonAliveCurPos);
		}

		//����㸴��
		{
			IButton* btnCreate = getLayout()->getButton("Btn_Alive_AlivePos");
			DYNAMIC_ASSERT(btnCreate);
			btnCreate->getWidget()->setMouseButtonClickEvent(onClickButtonAliveRelivePos);
		}
	}

	MG::Bool UIAliveRpg::openGui()
	{
		if (false == UIObject::isOpen())
		{
			UIObject::openGui();
			UIShowGeneralInfo();
			return true;
		}
		else
		{

		}
		return false;
	}

	void UIAliveRpg::UIShowGeneralInfo()
	{
		CPlayerCharacter*  myPlayerCharacter = CPlayer::getInstance().getMainGenreal();
		if (NULL == myPlayerCharacter)
		{
			return;
		}

		//����
		{
			IText* name = getLayout()->getText("edt_name");
			DYNAMIC_ASSERT(name);
			name->getWidget()->setCaption(myPlayerCharacter->getNormalName());
		}

		//ʱ��
		{
			ITimeText* time = getLayout()->getTimeText("edt_time");
			DYNAMIC_ASSERT(time);
			time->setCoolDownTime(30*1000);
		}
	}

	void UIAliveRpg::onClickButtonAliveCurPos( void* widget )
	{
		//ԭ�ظ���
		const PlayerCharacterIdType playerCharacterId =  CPlayer::getInstance().getMainGenreal()->getID();
		RegionNetPacketProcesser::getInstance().sendPlayerCharacterSetAlive(playerCharacterId, AliveType_User_CurPos);

		UIAliveRpg::getInstance().closeGui();
	}

	void UIAliveRpg::onClickButtonAliveRelivePos( void* widget )
	{
		//����㸴��
		const PlayerCharacterIdType playerCharacterId =  CPlayer::getInstance().getMainGenreal()->getID();
		RegionNetPacketProcesser::getInstance().sendPlayerCharacterSetAlive(playerCharacterId, AliveType_User_AlivePos);

		UIAliveRpg::getInstance().closeGui();
	}
}