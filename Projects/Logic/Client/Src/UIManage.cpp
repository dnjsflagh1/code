//****************************************************************************************************
#include "stdafx.h"
#include "UIManage.h"
#include "ClientMain.h"
#ifdef _DEBUG
#include "TemplateUI.h"
#include "TemplateSimplePro.h"
#endif
#include "UIAccountLogin.h"
#include "UISelectServer.h"
#include "UICharacterLogin.h"
#include "UIMessageBox.h"
#include "UIClanCreate.h"
#include "UIClanControl.h"
#include "UICreateCharacter.h"
//#include "UICampaignCreate.h"
#include "UISelectPlace.h"
//#include "UICampaignList.h"
//#include "UICampaignInfo.h"
#include "UISystemSetting.h"
#include "UIClanRoleControl.h"
#include "UIChatSendMsg.h"
#include "UIChatCommonShow.h"
#include "UIJumpRegion.h"
#include "UIBroadCast.h"
#include "UIRPGMiniMap.h"
#include "UIGameTick.h"
#include "UIMainFunction.h"
#include "UIGameCalendar.h"
#include "UINpc.h"
#include "UIArmyFunction.h"
#include "UIProgress.h"
#include "UICharacterJumpRegion.h"
#include "UIItemShop.h"
#include "UIGenrealPicture.h"
#include "UIGameOptions.h"
#include "UIPopupMenu.h"
#include "UIClanInfo.h"
#include "UITiroChangeInstance.h"
#include "UISkillTips.h"

#include "UIItemTips.h"
#include "UIFamilyInfo.h"
#include "UIQuestManager.h"
#include "UISkillOperate.h"

//战斗 UI
#include "UICampaignListNew.h"
#include "UICampaignInfoNew.h"
#include "UICampaignInviteDefense.h"
#include "UICampaignCountDown.h"

#include "UIBattleScore.h"	//战斗统计
#include "UICampaignWinLoseMsg.h"
#include "UICampaignFight.h"
#include "UICampaignWar.h"
//战斗 UI End

#include "HandleDropEvent.h"
#include "UIPlaceTips.h"

#include "UILoadingProgress.h"
#include "UICampaignBarrack.h"
#include "UIAnyIcon.h"
#include "UIYesNoMsgBox.h"
#include "UIEditYesNoMsgBox.h"
#include "UILoginLineUp.h"
#include "UIPveScore.h"
#include "UIPveCreate.h"

#include "UIAliveRpg.h"
#include "UIAliveSlg.h"

#include "UIJumpOutRegion.h"
#include "UISplitItem.h"
#include "UIRecruitGeneral.h"
#include "UIChangeRecruit.h"
#include "UIRPGTargetPic.h"
#include "UISLGGeneralPic.h"
#include "UISLGTeam.h"
#include "UISLGCommand.h"
#include "UISLGLeaveBattle.h"
#include "UISLGMap.h"
#include "UISLGTimeLeft.h"
#include "UISLGUP.h"
#include "UISLGSkillInfo.h"
#include "UISLGCalendar.h"
#include "UIBigCityMiniMap.h"
#include "UIBigCityCommand.h"
//****************************************************************************************************
namespace MG
{

    //-------------------------------------------------------------------------------
    UIManager::UIManager()
    {
		mGameType = GameType_Rpg;
    }
    //-------------------------------------------------------------------------------
    UIManager::~UIManager()
    {

    }
    //-------------------------------------------------------------------------------
    bool UIManager::loadLayout()
    {
        HandleDropEvent::getInstance().setEvent();
        //ClientMain::getInstance().getGui()->loadLayOut("Wallpaper0.layout");
#ifdef _DEBUG
        /*if ( TemplateUI::getInstance().initialize("TestMode.layout") == false )
           return false;*/
#endif

        if ( UIAccountLogin::getInstance().initialize("Account.layout") == false )
            return false; 
         if ( UISelectServer::getInstance().initialize("SelectServer.layout") == false )
            return false;
		if ( UILoginLineUp::getInstance().initialize("paidui.layout") == false )
			return false;
        if ( UIMessageBox::getInstance().initialize("msgBox.layout") == false )
            return false;
        if ( UIClanCreate::getInstance().initialize("clanCreate.layout") == false )
            return false;
        if ( UIClanControl::getInstance().initialize("clanControl.layout") == false )
            return false;
        if ( UICreateCharacter::getInstance().initialize("createCharacter.layout") == false )
            return false;
		if ( UISelectPlace::getInstance().initialize("SelectPlace.layout") == false)
			return false;
		if ( UILoadingProgress::getInstance().initialize("Loading.layout") == false )
			return false;
		
		//if ( UIGameInfo::getInstance().initialize("DemoGameInfo.layout") == false )
			//return false;
		if ( UISystemInfoBroadCast::getInstance().initialize("DemoSystemInfoRollBroadCast.layout") == false )
			return false;
		if ( UIGMInfoBroadCast::getInstance().initialize("DemoGmInfoRollBroadCast.layout") == false )
			return false;
		
		//if ( UIGameTick::getInstance().initialize("DemoGameTick.layout") == false )
			//return false;
		if ( UINpc::getInstance().initialize("dialog.layout") == false )
			return false;
		if (UIFamilyInfo::getInstance().initialize("MainFamily.layout")== false)                 //new
			return false;
		//主界面
		if (UIChatSendMsg::getInstance().initialize("ChatSendMsg.layout")==false)
			return false;
		if (UIChatCommonShow::getInstance().initialize("ChatCommonShow.layout")==false)
			return false;
		if ( UIMainFunciton::getInstance().initialize("MainFunc.layout") == false )
			return false;
		//RPG 主界面
		if ( UISkillOperate::getInstance().initialize("RPG\\SkillOperate.layout") == false )
			return false;
		if ( UIGenrealPicture::getInstance().initialize("RPG\\GeneralInfo.layout") == false )
			return false;
		if ( UIRPGMiniMap::getInstance().initialize("RPG\\RPG_MiniMap.layout") == false )
			return false;
		if (UIRPGTargetPic::getInstance().initialize("RPG\\RPG_TargetPic.layout") == false)
			return false;
		//SLG 主界面
		if (UISLGGeneralPic::getInstance().initialize("SLG\\Slg_General.layout") == false)
			return false;

		if (UISLGTeam::getInstance().initialize("SLG\\Slg_Team.layout") == false)
			return false;

		if (UISLGMap::getInstance().initialize("SLG\\SLGmap.layout") == false)
			return false;
		

		if (UISLGLeaveBattle::getInstance().initialize("SLG\\Slg_leaveBattle.layout") == false)
			return false;

		if (UISLGSkillInfo::getInstance().initialize("SLG\\Slg_SkillInfo.layout") == false)
			return false;
		if (UISLGUp::getInstance().initialize("SLG\\Slg_Up.layout") == false)
			return false;
		if (UISLGTimeLeft::getInstance().initialize("SLG\\Slg_TimeLeft.layout") == false)
			return false;
		if (UISLGCommand::getInstance().initialize("SLG\\Slg_Command.layout") == false)
			return false;
		if (UISLGCalendar::getInstance().initialize("SLG\\Slg_Calendar.layout") == false)
			return false;

		//大地图主界面
		if (UIBigCityMiniMap::getInstance().initialize("Map\\map.layout") == false)
			return false;
		if (UIBigCityCommand::getInstance().initialize("Map\\BigCity_Command.layout") == false)
			return false;

		if (UISkillTips::getInstance().initialize("tips_skill.layout") ==  false)
			return false;
		
		//if (UIGameCalendar::getInstance().initialize("GameCalendar.layout") == false)
        //    return false;
		if ( UIGameOptions::getInstance().initialize("SystemMenu.layout") == false )
			return false;
		if (UISystemSetting::getInstance().initialize("SystemSetting.layout") == false)
		    return false;

        //角色
		//if ( UIJumpRegion::getInstance().initialize("CharJumpRegion.layout") == false )
			//return false;
        //物品和商店
        if ( UIItemShop::getInstance().initialize("Shop.layout") == false )
            return false;

        if ( UIPopupMenu::getInstance().initialize("DemoPopupMenu.layout") == false )
            return false;

        if ( UIClanInfo::getInstance().initialize("ClanInfo.layout") == false ) 
            return false;
        if ( UIItemTips::getInstance().initialize("itemTips.layout") == false )
            return false;

		//新手副本跳转
		if ( UITiroChangeInstance::getInstance().initialize("TiroChangeInstance.layout") == false )
			return false;

		//跳大地图
		if ( UIJumpOutRegion::getInstance().initialize("JumpOut\\JumpOut.layout") == false )
			return false;

		//战斗 新版本
		if (UICampaignListNew::getInstance().initialize("Campaign\\CampaignListNew.layout") == false)
			return false;
		if (UICampaignInfoNew::getInstance().initialize("Campaign\\CampaignInfoNew.layout") == false)
			return false;
		if (UICampaignInviteDefense::getInstance().initialize("Campaign\\CampaignInviteDefense.layout") == false)
			return false;
		if (UICampaignBarrack::getInstance().initialize("Campaign\\CampaignBarrack.layout") == false)
			return false;

		if (UICampaignCountDown::getInstance().initialize("Campaign\\CampaignCountDown.layout") == false)
			return false;

		if (UICampaignWar::getInstance().initialize("Campaign\\CampaignWar.layout") == false)
			return false;


		if (UICampaignWinLoseMsg::getInstance().initialize("Campaign\\CampaignWinLoseMsg.layout") == false)
			return false;

		if (UICampaignFight::getInstance().initialize("Campaign\\CampaignFight.layout") == false)
			return false;

		


		if ( UIQuestManager::getInstance().initialize("questManager.layout") == false)
			return false;

        if ( UIPlaceTips::getInstance().initialize("PlaceTips.layout") == false )
            return false;
		if ( UIAnyIcon::getInstance().initialize("AnyIcon.layout") == false )
			return false;
		if ( UIYesNoMsgBox::getInstance().initialize("YesNoMsgBox.layout") == false )
			return false;
		/*if ( UIEditYesNoMsgBox::getInstance().initialize("EditYesNoMsgBox.layout") == false )
			return false;*/
		
		//BattleScore
		if ( UIBattleScore::getInstance().initialize("BattleScore\\BattleScore_new.layout") == false )
			return false;

		//PVE
		if ( UIPveScore::getInstance().initialize("PVE\\PveScore.layout") == false )
			return false;
		//
		if ( UIPveCreate::getInstance().initialize("PVE\\PveCreate.layout") == false )
			return false;
		
		//复活
		if ( UIAliveRpg::getInstance().initialize("GeneralAlive_rpg.layout") == false )
			return false;
		if ( UIAliveSlg::getInstance().initialize("GeneralAlive_slg.layout") == false )
			return false;
		//拆分
		if ( UISplitItem::getInstance().initialize("SplitItem.layout") == false )
			return false;

		//招募将领
		if ( UIRecruitGeneral::getInstance().initialize("Generalrecruitment.layout") == false )
			return false;

		//招募将领
		if ( UIChangeRecruit::getInstance().initialize("generalsplayed.layout") == false )
			return false;
		

        return true;
    }

    //-------------------------------------------------------------------------------
    void UIManager::closeAllLayout()
    {
        //TODO:
        Int nCount = mUIObjList.size();
        for ( Int i=0; i<nCount; i++ )
        {
            mUIObjList[i]->closeGui(true);
        }
    }

	//-------------------------------------------------------------------------------
	void UIManager::closeCampaignLayout()
	{
		//UICampaignCreate::getInstance().closeGui();
		//UICampaignList::getInstance().closeGui();
		//UICampaignInfo::getInstance().closeGui();
	}

    //-------------------------------------------------------------------------------
    void UIManager::addUIObj( UIObject* pObj )
    {
       mUIObjList.push_back(pObj);
    }
    //-------------------------------------------------------------------------------
    void UIManager::update(Flt delta)
    {
		//FUNDETECTION(__MG_FUNC__);

        checkEsc();
		checkEnter();
		mainGUIControl();

        Int nCount = mUIObjList.size();
        for ( Int i=0; i<nCount; i++ )
        {
            mUIObjList[i]->update(delta);
        }
    }
    //-------------------------------------------------------------------------------
    void UIManager::restore()
    {
        //FUNDETECTION(__MG_FUNC__);
        Int nCount = mUIObjList.size();
        for ( Int i=0; i<nCount; i++ )
        {
            mUIObjList[i]->restore();
        }
		mGameType = GameType_Rpg;
    }
    //-------------------------------------------------------------------------------
    void UIManager::checkEsc()
    {
        if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_ESCAPE ))
        {
            if ( UIGameOptions::getInstance().isOpen() )
                UIGameOptions::getInstance().closeGui();
            else
                UIGameOptions::getInstance().openGui();
        }
    }
	//-------------------------------------------------------------------------------
	void UIManager::checkEnter()
	{
		if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_RETURN ))
		{
			if (UIChatSendMsg::getInstance().isOpen())
			{
				UIChatSendMsg::getInstance().setIputFocus();
			}
			
		}

	}

	void UIManager::mainGUIControl()
	{
		if (ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_G ) 
			&& ClientMain::getInstance().getEngine()->input()->isCtrlOn())
		{
			if (UIChatSendMsg::getInstance().isOpen())
               {
				   closeAllLayout();
               }
			else
			{
					loadUI();

			}
		}
		
	}
	//-------------------------------------------------------------------------------
	void UIManager::loadUI()
	{
		//加载公用界面
		UIChatSendMsg::getInstance().openGui();
		UIMainFunciton::getInstance().openGui();
		UIChatCommonShow::getInstance().openGui();
		//UISLGCalendar::getInstance().openGui();
		loadUIWithGameType(mGameType);
		//
		
	}
	//-------------------------------------------------------------------------------
	void UIManager::loadUIWithGameType(GameType mode)
	{
		if (mode == GameType_Slg)
		{
			UISLGGeneralPic::getInstance().openGui();
			UISLGTeam::getInstance().openGui();
			UISLGMap::getInstance().openGui();
			//等倒计时结束在弹出
			//UISLGLeaveBattle::getInstance().openGui();
			//UISLGTimeLeft::getInstance().openGui();
			//UISLGSkillInfo::getInstance().openGui();
			
			UISLGCommand::getInstance().openGui();
			
		}
		else if (mode == GameType_Max)
		{
			UISLGGeneralPic::getInstance().openGui();
			UIBigCityMiniMap::getInstance().openGui();
			UIBigCityCommand::getInstance().openGui();
		}
		else
		{
			//默认RPG
			UIGenrealPicture::getInstance().openGui();
			UIRPGMiniMap::getInstance().openGui();
			UISkillOperate::getInstance().openGui();
		}			
	}
	//-------------------------------------------------------------------------------
}