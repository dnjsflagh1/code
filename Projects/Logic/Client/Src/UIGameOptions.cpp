//*****************************************************************************************************************
#include "stdafx.h"
#include "UIGameOptions.h"
#include "ClientMain.h"
#include "GameSoundManager.h"
#include "UISystemSetting.h"
#include "GameMain.h"
#include "UIMessageBox.h"
#include "UIYesNoMsgBox.h"
//*****************************************************************************************************************
namespace MG
{
    void UIGameOptions::setEvent()
    {
        IButton* pButton = getLayout()->getButton("button_exit");
        pButton->getWidget()->setMouseButtonClickEvent(onClickExit);
        getLayout()->getButton("button_rlogin")->getWidget()->setMouseButtonClickEvent(onClickRlogin);
		getLayout()->getButton("button_return")->getWidget()->setMouseButtonClickEvent(onClickReturn);
		
		getLayout()->getButton("button_func")->getWidget()->setMouseButtonClickEvent(onClickFuncSet);
		getLayout()->getButton("button_video")->getWidget()->setMouseButtonClickEvent(onClickVideoSet);
		getLayout()->getButton("button_audio")->getWidget()->setMouseButtonClickEvent(onClickAudioSet);
		getLayout()->getButton("button_network")->getWidget()->setMouseButtonClickEvent(onClickNetworkSet);
    }
    //------------------------------------------------------------------------------------------------
    void UIGameOptions::onClickExit( void* widget )
    {
		UIYesNoMsgBox::getInstance().showHint(L"�˳���Ϸ��ʾ",L"��ȷ��Ҫ�˳���Ϸ",
			(void*)(&UIGameOptions::getInstance()),exitGame,NULL,NULL);
		//ClientMain::getInstance().quitApplication();
    }
	//------------------------------------------------------------------------------------------------
	void UIGameOptions::exitGame(void* arg)
	{
        UIYesNoMsgBox::getInstance().closeGui();
		ClientMain::getInstance().quitApplication();
	}
	//------------------------------------------------------------------------------------------------
	void UIGameOptions::reLogin(void* arg)
	{
		GameMain::getInstance().stopAndRestore();
		//���²��ŵ�¼����
		GameSoundManager::getInstance().play(10001);
	}
	//------------------------------------------------------------------------------------------------
	void UIGameOptions::onClickRlogin( void* widget )
	{
		UIYesNoMsgBox::getInstance().showHint(L"���ص���½������ʾ",L"��ȷ��Ҫ���ص���½����",
			(void*)(&UIGameOptions::getInstance()),reLogin,NULL,NULL);
	}
	//------------------------------------------------------------------------------------------------
	void UIGameOptions::onClickReturn( void* widget )
	{
		if ( UIGameOptions::getInstance().isOpen() )
			UIGameOptions::getInstance().closeGui();
	}
	//------------------------------------------------------------------------------------------------
	void UIGameOptions::onClickFuncSet( void* widget )
	{
		UISystemSetting::getInstance().openGui();
		UISystemSetting::getInstance().setSettingType(SYS_SET_TYPE_FUNCTION);

	}
	//------------------------------------------------------------------------------------------------
	void UIGameOptions::onClickVideoSet( void* widget )
	{
      UISystemSetting::getInstance().openGui();
	  UISystemSetting::getInstance().setSettingType(SYS_SET_TYPE_VIDEO);

	}
	//------------------------------------------------------------------------------------------------
	void UIGameOptions::onClickAudioSet( void* widget )
	{
        UISystemSetting::getInstance().openGui();
		UISystemSetting::getInstance().setSettingType(SYS_SET_TYPE_AUDIO);

	}
	//------------------------------------------------------------------------------------------------
	void UIGameOptions::onClickNetworkSet( void* widget )
	{
		UISystemSetting::getInstance().openGui();
		UISystemSetting::getInstance().setSettingType(SYS_SET_TYPE_NETWORK);

	}
}