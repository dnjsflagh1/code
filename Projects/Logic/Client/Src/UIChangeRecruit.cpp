//***************************************************************************************************
#include "stdafx.h"
#include "UIChangeRecruit.h"
#include "CPlayerCharacter.h"
#include "UIMessageBox.h"
#include "CGeneralRecruitNetPacketProcessor.h"
#include "CPlayer.h"
//***************************************************************************************************
namespace MG
{
	UIChangeRecruit::UIChangeRecruit()
		:mSelectGeneralId(0)
	{

	}

	//----------------------------------------------------------------------------------------
	UIChangeRecruit::~UIChangeRecruit()
	{

	}

	//----------------------------------------------------------------------------------------
	void UIChangeRecruit::setEvent()
	{
		IButton* btnConfirm = getLayout()->getButton("btn_confirm");
		DYNAMIC_ASSERT(btnConfirm);
		btnConfirm->getWidget()->setMouseButtonClickEvent(onEventConfirmBtn);

	}

	//--------------------------------------------------------------------------------------
	void UIChangeRecruit::restore()
	{
		
	}

	//--------------------------------------------------------------------------------------
	void UIChangeRecruit::onEventConfirmBtn(void* widget)
	{
		U64	generalId = UIChangeRecruit::getInstance().getSelectGeneralId();
		if (generalId <= 0)
		{
			UIMessageBox::getInstance().showHint(L"请选择武将!\n");
			return;
		}

		if(generalId == CPlayer::getInstance().getMainPlayerCharacterId())
		{
			UIMessageBox::getInstance().showHint(L"不能选择当前武将， 请换其他武将!\n");
		}
		else
		{
			CGeneralRecruitNetPacketProcessor::getInstance().sendChangeGeneral(generalId);

		}
	}

	//--------------------------------------------------------------------------------------
	bool UIChangeRecruit::openGui()
	{
		if (false == UIObject::isOpen())
		{
			UIObject::openGui();
			std::map<U64, CPlayerCharacter*>* playerCharacter = CPlayer::getInstance().getActiveClan()->getPlayerCharacterList();
			UIFresh();
		}
		else
		{
			UIObject::closeGui();
		}

		return false;
	}

	void UIChangeRecruit::UIFresh()
	{
		IMixListRow* pMixListRow = NULL;
		IMixList* pMixList = getLayout()->getMixList("mixlist_generalList");
		DYNAMIC_ASSERT(pMixList);
		pMixList->removeAllLine();

		pMixList->setClickMixListRow(onClickGeneralInfo);

		std::map<U64, CPlayerCharacter*>* playerCharacter = CPlayer::getInstance().getActiveClan()->getPlayerCharacterList();

		std::map<U64, CPlayerCharacter*>::iterator iter = playerCharacter->begin();
		for (; iter != playerCharacter->end(); ++iter)
		{
			CPlayerCharacter* tempChar = iter->second;
			IMixListRow* pMixListRow = pMixList->addLine(tempChar->getCharacterTemplateID(), tempChar->getNormalName());

			//设置名字
			pMixListRow->getChildWidget(0)->setCaption(tempChar->getNormalName());
			pMixListRow->getWidget()->setUserData(tempChar);

			//设置状态
			//根据状态设置图片。

		}
	}

	void UIChangeRecruit::onClickGeneralInfo(void* widget, Int index)
	{
		IMixList* listMainZone = (IMixList*)widget;

		IMixListRow* row = listMainZone->getMixListRowByIndex(index);

		IAny* pAny = row->getWidget()->getUserData();
		CPlayerCharacter** info = pAny->castType<CPlayerCharacter*>(pAny);
		DYNAMIC_ASSERT(NULL != info);
		UIChangeRecruit::getInstance().setSelectGeneralId((*info)->getID());

	}

	void UIChangeRecruit::clearRecruitGeneralList()
	{
		mRecruitGeneralList.clear();
	}

	void UIChangeRecruit::loadRecruitGeneralInfo(NetRecuitGeneralInfo* generalInfo)
	{
		std::map<U64, CPlayerCharacter*>::iterator iter = mRecruitGeneralList.find(generalInfo->uin);
		if (iter != mRecruitGeneralList.end())
		{
			//找到， id 重复
			return;
		}

		CPlayerCharacter* character = MG_NEW CPlayerCharacter();

		character->getData()->mId					= generalInfo->uin;
		character->getData()->mCharacterTemplateID	= generalInfo->charTemplateId;
		character->getData()->mName					= L"xxa";

		mRecruitGeneralList[generalInfo->uin] = character;
	}

	std::map<U64, CPlayerCharacter*>* UIChangeRecruit::getRecruitGeneralList()
	{
		return &mRecruitGeneralList;
	}

	void UIChangeRecruit::setSelectGeneralId(U64 generalId)
	{
		mSelectGeneralId = generalId;
	}

	U64 UIChangeRecruit::getSelectGeneralId() const
	{
		return mSelectGeneralId;
	}
}