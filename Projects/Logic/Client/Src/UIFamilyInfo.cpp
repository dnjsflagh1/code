//***************************************************************************************************
#include "stdafx.h"
#include "UIFamilyInfo.h"


#include "CPlayer.h"
#include "UIMessageBox.h"
//***************************************************************************************************

namespace MG
{
	 //----------------------------------------------------------------------------------------
	UIFamilyInfo::UIFamilyInfo()
	{

	}
	 //----------------------------------------------------------------------------------------
	UIFamilyInfo::~UIFamilyInfo()
	{

	}
	 //----------------------------------------------------------------------------------------
	void UIFamilyInfo::setEvent()
	{

	}

	void UIFamilyInfo::initFamilyInfo()
	{
		CClan* pClan = CPlayer::getInstance().getActiveClan();
		assert(pClan);

		Str16 tempName = pClan->getClanHomeLandName() + pClan->getName() + L"氏";
		IText* txtname = getLayout()->getText("nametext-family");
		txtname->getWidget()->setCaption(tempName);
        //数据库里还没有氏族等级字段，先写死
		Str16 tempLV(L"氏族等级：1");

		IText* txtlv = getLayout()->getText("LVtext-family");
		txtlv->getWidget()->setCaption(tempLV);



	}

	MG::Bool UIFamilyInfo::openGui()
	{
			initFamilyInfo();
			return UIObject::openGui();
	}
}