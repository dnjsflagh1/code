//*************************************************************************************
#include "stdafx.h"
#include "UIAccountLogin.h"
#include "TemplateSimplePro.h"
#include "ClientNetApplyManager.h"
#include "UICharacterLogin.h"
#include "LoginManager.h"
//*************************************************************************************
namespace MG
{
	
	//--------------------------------------------------------------------------------
	void UICharacterLogin::onClickLoginFrontServer(void* widget)
	{
	}

	//--------------------------------------------------------------------------------
	/*void UICharacterLogin::createPlayerCharacter( PT_ACC_C2F_LOGIN_DATA* data,I32 dataSize )
	{

	}*/

	//--------------------------------------------------------------------------------
	void UICharacterLogin::setEvent()
	{
		//IEdit* name = getLayout()->getEdit("Edit_name");
		//name->setSelectAcceptEvent(onSelectAcceptEvent);

		//IEdit* password = getLayout()->getEdit("Edit_password");
		//password->setSelectAcceptEvent(onSelectAcceptEvent);

		//IText* textname = getLayout()->getText("Text_name");
		//textname->getWidget()->setCaption(L"ÕËºÅ");

		//IText* textpassword = getLayout()->getText("Text_password");
		//textpassword->getWidget()->setCaption(L"ÃÜÂë");

		IButton* btnLogin = getLayout()->getButton("Btn_3");
		btnLogin->setMouseButtonClickEvent(onClickLoginFrontServer);
		
		btnLogin = getLayout()->getButton("Btn_1");
		btnLogin->setMouseButtonClickEvent(onClickSelectPlayerCharacter);
	}

	//--------------------------------------------------------------------------------
	void UICharacterLogin::setPanelValue( Char16* frontServerName, Char* ip, I32 port)
	{
		IText* text = getLayout()->getText("Text_cha");
		std::wstring ipStr;
		Char16 temp[2048] ={0};
		MGStrOp::toString(ip,ipStr);

		MGStrOp::sprintf(temp,2048,
			L"ÕËºÅÃû%s£¬\tIP%s,\nPort%d,\n",
			frontServerName,ipStr.c_str(),port);

		if (text)
		{
			text->getWidget()->setCaption(temp);
		}
	}

	//--------------------------------------------------------------------------------
	void UICharacterLogin::onClickSelectPlayerCharacter( void* widget )
	{
	}
	
}