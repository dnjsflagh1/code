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

		Str16 tempName = pClan->getClanHomeLandName() + pClan->getName() + L"��";
		IText* txtname = getLayout()->getText("nametext-family");
		txtname->getWidget()->setCaption(tempName);
        //���ݿ��ﻹû������ȼ��ֶΣ���д��
		Str16 tempLV(L"����ȼ���1");

		IText* txtlv = getLayout()->getText("LVtext-family");
		txtlv->getWidget()->setCaption(tempLV);



	}

	MG::Bool UIFamilyInfo::openGui()
	{
			initFamilyInfo();
			return UIObject::openGui();
	}
}