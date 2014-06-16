#include "stdafx.h"
#include "LoginForm.h"
#include "GMToolManager.h"
namespace MG
{

	//-----------------------------------------------------------------------------
	void LoginForm::startLogin()
	{
		BEGINDELEGATE(LoginForm,startLogin)
			ENDDELEGATE

		GMFormSet::LOADING_FORM->showMessage("Loading Resource...");
		GMToolManager::getInstance().loadMainFormStaticConfig();
		if (GMFormSet::MAIN_FORM)
			//GMFormSet::MAIN_FORM->shieldAuthorityLimitedUI();

		this->Hide();
		GMFormSet::LOADING_FORM->Hide();

		if (GMFormSet::MAIN_FORM)
			GMFormSet::MAIN_FORM->Show();
	}
	//-----------------------------------------------------------------------------
	void LoginForm::quitLogin( DWORD reason )
	{
		BEGINDELEGATE(LoginForm,quitLogin)
			ADDDELEGATEPARAMETER reason
			ENDDELEGATE

			if (GMFormSet::MAIN_FORM)
				GMFormSet::MAIN_FORM->Hide();
		GMFormSet::LOADING_FORM->Hide();

		this->Show();
	}
	//-----------------------------------------------------------------------------
	void LoginForm::loadGameTextConfig()
	{
		BEGINDELEGATE(LoginForm,loadGameTextConfig)
			ENDDELEGATE

			INIT_CONFIG_TEXT

			SET_CONFIG_TEXT_GROUP(L"Login");
		this->Text          = GET_CONFIG_TEXT(L"windows_title",L"Login");
		lbl_title->Text     = GET_CONFIG_TEXT(L"main_title",L"GMTool");
		gbo_input->Text     = GET_CONFIG_TEXT(L"main_group_name",L"Login");
		lbl_username->Text  = GET_CONFIG_TEXT(L"lable_username",L"username");
		lbl_password->Text  = GET_CONFIG_TEXT(L"lable_password",L"password");
		btn_login->Text     = GET_CONFIG_TEXT(L"btn_login",L"Login");
		btn_exit->Text      = GET_CONFIG_TEXT(L"btn_exit",L"Exit");
	}
	//-----------------------------------------------------------------------------
	System::Void LoginForm::btn_exit_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		//GMToolManager::getInstance().getGMClient()->logout();
		//this->Hide();
		//this->Close();
	}
	//-----------------------------------------------------------------------------
	System::Void LoginForm::btn_login_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		IGMClient* gmClient = GMToolManager::getInstance().getGMClient();

		String^ name        = edt_username->Text;
		String^ password    = edt_password->Text;
		StringToChar c_name(name);
		StringToChar c_password(password);

		//check
		if (String::IsNullOrEmpty(name))
		{
			gmClient->showWarningMessageByC(L"Login",L"name_null",L"name can't null!");
			return;
		}
		if (String::IsNullOrEmpty(password))
		{
			gmClient->showWarningMessageByC(L"Login",L"password_null",L"password can't null!");
			return;
		}

		//login
		this->Hide();
		this->Refresh();
		GMFormSet::LOADING_FORM->showMessage("Login Server...");

		gm_account_operate_result result_desc = gmClient->getGMManager()->login(c_name.str_char,c_password.str_char);

		if ( result_desc == gaor_timeout )
		{
			gmClient->showWarningMessageByC(L"Login",L"login_timeout",L"timeout!");
		}else
		if ( result_desc == gaor_errname_or_errpsw )
		{
			gmClient->showWarningMessageByC(L"Login",L"login_errname_or_errpsw",L"gaor_errname_or_errpsw!");
		}else
		if ( result_desc == gaor_errname )
		{
			gmClient->showWarningMessageByC(L"Login",L"login_no_gm_account",L"no_gm_account!");
		}else
		if ( result_desc == gaor_err_psw )
		{
			gmClient->showWarningMessageByC(L"Login",L"login_password_not_match",L"password_not_match!");
		}else
		if ( result_desc == gaor_err_version )
		{
			gmClient->showWarningMessageByC(L"Login",L"login_identifier_not_match",L"identifier_not_match!");
		}


		if ( result_desc == gaor_success )
		{
			gmClient->logByC(L"Login",L"login_successed",L"login_successed!");
			this->startLogin();
		}else
		{
			this->quitLogin(result_desc);
		}
								//king.wang Test
								//  this->startLogin();*/
	}
}