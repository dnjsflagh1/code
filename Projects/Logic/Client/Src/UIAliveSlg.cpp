//*************************************************************************************

#include "stdafx.h"
#include "UIAliveSlg.h"
#include "RegionNetPacketProcesser.h"
#include "CPlayer.h"

//*************************************************************************************
namespace MG
{
	//--------------------------------------------------------------------------------
	UIAliveSlg::UIAliveSlg()
	{
	}

	UIAliveSlg::~UIAliveSlg()
	{

	}

	void UIAliveSlg::setEvent()
	{
		//原地复活
		{
			IButton* btnCreate = getLayout()->getButton("Btn_Alive_CurPos");
			DYNAMIC_ASSERT(btnCreate);
			btnCreate->getWidget()->setMouseButtonClickEvent(onClickButtonAliveCurPos);
		}
	}

	MG::Bool UIAliveSlg::openGui()
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

	void UIAliveSlg::UIShowGeneralInfo()
	{
		CPlayerCharacter*  myPlayerCharacter = CPlayer::getInstance().getMainGenreal();
		if (NULL == myPlayerCharacter)
		{
			return;
		}

		//名字
		{
			IText* name = getLayout()->getText("edt_name");
			DYNAMIC_ASSERT(name);
			name->getWidget()->setCaption(myPlayerCharacter->getNormalName());
		}

		//时间
		{
			ITimeText* time = getLayout()->getTimeText("edt_time");
			DYNAMIC_ASSERT(time);
			time->setCoolDownTime(30*1000);
		}
	}

	void UIAliveSlg::onClickButtonAliveCurPos( void* widget )
	{
		const PlayerCharacterIdType playerCharacterId =  CPlayer::getInstance().getMainGenreal()->getID();
		RegionNetPacketProcesser::getInstance().sendPlayerCharacterSetAlive(playerCharacterId, AliveType_User_CurPos);

		UIAliveSlg::getInstance().closeGui();
	}
}