//*************************************************************************************
#include "stdafx.h"
#include "shellAPI.h"
#include "UIAccountLogin.h"
#include "LoginManager.h"
#include "ClientMain.h"
#include "UIMessageBox.h"
#include "GameMain.h"
#include "VersionSwitch.h"
#include "GameSoundManager.h"
#include "CGameMessageConfig.h"
#include "UIYesNoMsgBox.h"
//*************************************************************************************
namespace MG
{

	//--------------------------------------------------------------------------------
    void UIAccountLogin::setEvent()
    {
        IEdit* name = getLayout()->getEdit("edit_account");
        name->setSelectAcceptEvent(onSelectAcceptEvent);

        IEdit* password = getLayout()->getEdit("edit_password");
        password->setSelectAcceptEvent(onSelectAcceptEvent);

		IButton* btnLogin = getLayout()->getButton("button_ok");
		btnLogin->getWidget()->setMouseButtonClickEvent(onLogin);

        IButton* btnReset = getLayout()->getButton("button_reset");
		btnReset->getWidget()->setMouseButtonClickEvent(onReset);
        
		IButton* btnGoback = getLayout()->getButton("btn_goback");
		btnGoback->getWidget()->setMouseButtonClickEvent(onClickGoBack);

		//IButton* btnRegister = getLayout()->getButton("button_reg");
		//btnRegister->getWidget()->setMouseButtonClickEvent(onRegister);

		//IButton* btnReCharge = getLayout()->getButton("button_charge");
		//btnReCharge->getWidget()->setMouseButtonClickEvent(onReCharge);

		//IButton* btnFind = getLayout()->getButton("button_findpwd");
		//btnFind->getWidget()->setMouseButtonClickEvent(onFindPwd);

		//IButton* btnExit = getLayout()->getButton("button_exit");
		//btnExit->getWidget()->setMouseButtonClickEvent(onExitGame);

		//IButton* btnViewHome = getLayout()->getButton("button_viewhome");
		//btnViewHome->getWidget()->setMouseButtonClickEvent(onViewHomePage);

		IButton* cboxagree = getLayout()->getButton("cbox_agree");
        cboxagree->getWidget()->setMouseButtonClickEvent(onCboxAgreeClick);

		IButton* exitBtn = getLayout()->getButton("exit_btn");
		exitBtn->getWidget()->setMouseButtonClickEvent(onExitGame);

    }

	//--------------------------------------------------------------------------------
    void UIAccountLogin::onSelectAcceptEvent( void* widget )
    {
        if ( widget )
		{
			UIAccountLogin::getInstance().checkCanSend();
		}
	}         

	//--------------------------------------------------------------------------------
    void UIAccountLogin::checkCanSend()
    {
        //获取输入的帐号和密码。
		IEdit* name = getLayout()->getEdit("edit_account");
		std::wstring nameStr = name->getCaption();

		IEdit* password = getLayout()->getEdit("edit_password");
		std::wstring passwordStr = password->getCaption();

		if (nameStr.length()<1)
		{
			return;
		}
		if (passwordStr.length()<1)
		{
			return;
		}
        
        if (!mIsAgreeUserPro)
        {
			UIMessageBox::getInstance().showHint(L"同意用户协议,才能继续游戏!");
			return;
        }
         
        //检查帐号和密码是否合乎规则。
        //if ()
        //{
            LoginManager::getInstance().loginToLoginServer(nameStr,passwordStr);
            //成功发送出后，游戏进入等待
            //关闭输入帐号界面
            //closeGui();
        //}
        //else
        //{
            /*UIMessageBox::getInstance().showHint(
                L"", L"", L"", 
                L"", L"", L"",
                this, onClickMsgBoxRuleError
                );*/
        //}

		
    }
	
	//--------------------------------------------------------------------------------
	void UIAccountLogin::onLogin( void* widget )
	{
		if ( widget )
		{
			UIAccountLogin::getInstance().checkCanSend();
		}
	}
    //--------------------------------------------------------------------------------
    Bool UIAccountLogin::openGui()
    {
        if ( UIObject::openGui() )
        {
			restore();
            getLayout()->getButton("cbox_agree")->setStateCheck(true);
			Str16 versionStr; 
			MGStrOp::toString(CLIENT_VERSION_NUMBER,versionStr);
			
			IText* txt = getLayout()->getText("version_txt");
			txt->getWidget()->setCaption(versionStr);
            return true;
        }
        return false;
    }
	//--------------------------------------------------------------------------------
	void UIAccountLogin::onReset( void* widget )
	{
		UIAccountLogin::getInstance().restore();

	}
	//--------------------------------------------------------------------------------
	void UIAccountLogin::restore()
	{
		IEdit* name = getLayout()->getEdit("edit_account");
		name->setCaption(L"");

		IEdit* password = getLayout()->getEdit("edit_password");
		password->setCaption(L"");

	}

	//--------------------------------------------------------------------------------
	void UIAccountLogin::onRegister( void* widget )
	{
        ShellExecute(NULL,"open","http://yxz.kx1d.com/",NULL,NULL,SW_SHOWNORMAL);
	}
	//--------------------------------------------------------------------------------
	void UIAccountLogin::onReCharge( void* widget )
	{
        ShellExecute(NULL,"open","http://yxz.kx1d.com/",NULL,NULL,SW_SHOWNORMAL);

	}
	//--------------------------------------------------------------------------------
	void UIAccountLogin::onFindPwd( void* widget )
	{
       ShellExecute(NULL,"open","http://yxz.kx1d.com/",NULL,NULL,SW_SHOWNORMAL);
    
	}
	//--------------------------------------------------------------------------------
	void UIAccountLogin::onExitGame( void* widget )
	{
		Str16 tempTitle = CGameMessageConfig::getInstance().getStr(L"AccountLogin",L"exitGameTitle",L"");
		Str16 tempContent = CGameMessageConfig::getInstance().getStr(L"AccountLogin",L"exitGameContent",L"");
		UIYesNoMsgBox::getInstance().showHint(tempTitle,tempContent, (void*)(&UIAccountLogin::getInstance()),onConfirmExitGame, NULL, NULL);           
	}
	//--------------------------------------------------------------------------------
	void UIAccountLogin::onViewHomePage( void* widget )
	{
          ShellExecute(NULL,"open","http://yxz.kx1d.com/",NULL,NULL,SW_SHOWNORMAL);

	}
	//--------------------------------------------------------------------------------
	void UIAccountLogin::onCboxAgreeClick( void* widget )
	{
		if (widget)
		{
			UIAccountLogin::getInstance().setCboxAgree();
		}
	}
	//--------------------------------------------------------------------------------
	void UIAccountLogin::setCboxAgree()
	{

       Bool state = getLayout()->getButton("cbox_agree")->getStateCheck();
	   if (!state)
	   {
	     getLayout()->getButton("cbox_agree")->setStateCheck(true);
		 mIsAgreeUserPro = true;
	   }
	   else
	   {
         getLayout()->getButton("cbox_agree")->setStateCheck(false);
		 mIsAgreeUserPro = false;
	   }
   
	}
  //--------------------------------------------------------------------------------
	void UIAccountLogin::update(Flt delta)
	{
		
		if (this->isOpen())
		{

			//检查是否按了Tab
			if(ClientMain::getInstance().getEngine()->input()->isKeyReleased(KC_TAB))
			{
				IWidget* edit_account = getLayout()->getWidget("edit_account");
				IWidget* edit_password = getLayout()->getWidget("edit_password");
				Bool   account_focus = edit_account->isKeyFocus();
				Bool   password_focus =edit_password->isKeyFocus();

				if ( account_focus )
				{
					edit_password->setKeyFocus(true); 
				}
				else
				{
					edit_account->setKeyFocus(true);
				}

			}

		}
		

	}
	//--------------------------------------------------------------------------------
	void UIAccountLogin::goBack()
	{
		GameMain::getInstance().stopAndRestore();
		//重新播放登录音乐
		GameSoundManager::getInstance().play(10001);
	}
	//--------------------------------------------------------------------------------
	void UIAccountLogin::onClickGoBack(void* widget)
	{   
		if (widget)
		{
			Str16 tempTitle = CGameMessageConfig::getInstance().getStr(L"AccountLogin",L"returnToSelectServerTitle",L"");
			Str16 tempContent = CGameMessageConfig::getInstance().getStr(L"AccountLogin",L"returnToSelectServerContent",L"");
			UIYesNoMsgBox::getInstance().showHint(tempTitle,tempContent, (void*)(&UIAccountLogin::getInstance()),onReturnSelectServerConfirm, NULL, NULL);           
		}
	}
	//--------------------------------------------------------------------------------
	void UIAccountLogin::onReturnSelectServerConfirm(void* arg)
	{ 
		 UIAccountLogin::getInstance().goBack();
	}
	//--------------------------------------------------------------------------------
	void UIAccountLogin::onConfirmExitGame(void* arg)
	{ 
		ClientMain::getInstance().quitApplication();
	}
}