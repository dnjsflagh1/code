//***************************************************************************************************
#include "stdafx.h"
#include "UIArmyFunction.h"
#include "CSceneManager.h"
#include "CPlayer.h"
#include "ClientMain.h"
#include "UIIconAtrRecouse.h"
#include "TroopNetPacketProcesser.h"
#include "MGMath.h"
//***************************************************************************************************
namespace MG
{
	//CTroopGroupEntity* UIArmyFunction::mSelectTroopGroupEntity = NULL;
	//CPlayerTroopGroup* UIArmyFunction::mSelectTroopGroup = NULL;
	CPlayerCharacterEntity* UIArmyFunction::mSelectPlayerCharacterEntity = NULL;
	CPlayerCharacter* UIArmyFunction::mSelectPlayerCharacter = NULL;

    UIArmyFunction::UIArmyFunction()
    {
		mState = army_click_state_null;
    }
    //----------------------------------------------------------------------------------------
    UIArmyFunction::~UIArmyFunction()
    {

    }
    //----------------------------------------------------------------------------------------
    void UIArmyFunction::setEvent()
    {
		mImgSoldier1Pos1 = getLayout()->getImage("img_soldier1")->getWidget()->getPosition();
		mImgSoldier2Pos1 = getLayout()->getImage("img_soldier2")->getWidget()->getPosition();
		mImgSoldier3Pos1 = getLayout()->getImage("img_soldier3")->getWidget()->getPosition();
		
		Vec2 size;
		Flt high = 80.0f;
		mImgSoldier1Pos2 = mImgSoldier1Pos1;
		mImgSoldier1Pos2.y = mImgSoldier1Pos1.y - high;
		mImgSoldier2Pos2 = mImgSoldier2Pos1;
		mImgSoldier2Pos2.y = mImgSoldier2Pos1.y - high;
		mImgSoldier3Pos2 = mImgSoldier3Pos1;
		mImgSoldier3Pos2.y = mImgSoldier3Pos1.y - high;

		size = getLayout()->getImage("img_soldier1")->getWidget()->getSize();
		mImgGeneralSkillPos3 = getLayout()->getImage("img_generalSkill")->getWidget()->getPosition();
		mImgGeneralSkillPos2 = mImgGeneralSkillPos3;
		mImgGeneralSkillPos2.x = mImgGeneralSkillPos3.x - size.x;
		mImgGeneralSkillPos1 = mImgGeneralSkillPos2;
		mImgGeneralSkillPos1.x = mImgGeneralSkillPos2.x - size.x;	
		mImgSoldierCmdPos3 = getLayout()->getImage("img_soldierCmd")->getWidget()->getPosition();
		mImgSoldierCmdPos2 = mImgSoldierCmdPos3;
		mImgSoldierCmdPos2.x = mImgSoldierCmdPos3.x - size.x;
		mImgSoldierCmdPos1 = mImgSoldierCmdPos2;
		mImgSoldierCmdPos1.x = mImgSoldierCmdPos2.x - size.x;

        Char8 temp[32] = "";
        IButton* button = NULL;
        for (Int i= 1; i<4; i++)
        {
            sprintf_s(temp, 32, "btn_general%d", i);
            button = getLayout()->getButton(temp);
            button->getWidget()->setMouseButtonClickEvent(onClickGeneral);
            button->getWidget()->setUserData( i-1 + army_click_state_general1 );
        }
		
        for (Int i= 1; i<4; i++)
        {
            sprintf_s(temp, 32, "btn_soldier%d", i);
            button = getLayout()->getButton(temp);
            button->getWidget()->setMouseButtonClickEvent(onClickSoldier);
            button->getWidget()->setUserData(i-1 + army_click_state_soldier1);
        }
		
		button = getLayout()->getButton("btn_cmd6");
		button->getWidget()->setMouseButtonClickEvent(onClickSoldierSkill);
        button->getWidget()->setUserData(army_click_state_soldier_skill1);
		button = getLayout()->getButton("btn_cmd7");
		button->getWidget()->setMouseButtonClickEvent(onClickSoldierSkill);
        button->getWidget()->setUserData(army_click_state_soldier_skill1);
		button = getLayout()->getButton("btn_cmd8");
		button->getWidget()->setMouseButtonClickEvent(onClickSoldierSkill);
        button->getWidget()->setUserData(army_click_state_soldier_skill1);

		button = getLayout()->getButton("btn_cmd1");
		button->getWidget()->setMouseButtonClickEvent(onClickTroopGroupRight);

		button = getLayout()->getButton("btn_cmd2");
		button->getWidget()->setMouseButtonClickEvent(onClickTroopGroupLeft);

		button = getLayout()->getButton("btn_cmd5");
		button->getWidget()->setMouseButtonClickEvent(onClickTroopGroupStopMove);

		IIcon* icon = NULL;
        for (Int i=1; i<9; i++)
        {
            sprintf_s(temp, 32, "icon_skill%d", i);
            icon = getLayout()->getIcon(temp);
            icon->getWidget()->setMouseButtonReleasedEvent(onClickGeneralSkill);
            icon->getWidget()->setUserData(i-1);
        }
    
    }
	//----------------------------------------------------------------------------------------
	void UIArmyFunction::onClickGeneral( void* widget )
	{
        DYNAMIC_ASSERT(widget);
        IButton* pButton = (IButton*)widget;
        IAny* pAny = pButton->getWidget()->getUserData();
        DYNAMIC_ASSERT(pAny);
        Int* pIndex = pAny->castType<Int>();
        DYNAMIC_ASSERT(pIndex);

		UIArmyFunction::getInstance().setState(army_click_state(*pIndex));
		UIArmyFunction::getInstance().adjustUi();
		
		UIArmyFunction::getInstance().clearGeneralSkillIcon();

		CPlayerCharacter* playerCharacter = CPlayer::getInstance().getActiveClan()->getPlayerCharacterByIndex((UInt)0);
		if(!playerCharacter)
		{
			return;
		}

        CPlayerCharacterEntity* playerCharacterEntity = CSceneManager::getInstance().getPlayerCharacterEntity( playerCharacter->getID() );
		if(!playerCharacterEntity)
		{
			return;
		}
		
		mSelectPlayerCharacterEntity = playerCharacterEntity;
		mSelectPlayerCharacter = playerCharacter;
		//mSelectIndex = 0;
		//ClientMain::getInstance().getGameObjectOpCtrl()->addSelected( playerCharacterEntity );
		//CSceneManager::getInstance().getEngineScene()->getActiveCamera()->focusPosition(playerCharacterEntity->getPos());

		/*CSkillManagerForCharacter* skillManager = playerCharacter->getSkillManager();
		SkillObject* skillObject = NULL;
		Char8 tempStr[20] = "";
		for(UInt i = 0; i < skillManager->getSkillNum(); ++i)
		{
			skillObject = skillManager->getSkill(i);
			if(!skillObject)
			{
				continue;
			}

			const IconArtResInfo* iconInfo = UIIconArtRecouse::getInstance().getIconArtResInfo(skillObject->getBaseInfo()->iconID);
			if(iconInfo)
			{
				sprintf_s(tempStr, sizeof(tempStr), "icon_skill%d", i + 1);
				IIcon* icon = UIArmyFunction::getInstance().getLayout()->getIcon(tempStr);
				icon->setTexture(iconInfo->ResName, iconInfo->GroupName, iconInfo->ItemName);
			}
		}*/
	}
	
	//----------------------------------------------------------------------------------------
	void UIArmyFunction::onClickSoldier( void* widget )
	{
        DYNAMIC_ASSERT(widget);
        IButton* pButton = (IButton*)widget;
        IAny* pAny = pButton->getWidget()->getUserData();
        DYNAMIC_ASSERT(pAny);
        Int* pIndex = pAny->castType<Int>();
        DYNAMIC_ASSERT(pIndex);

		UIArmyFunction::getInstance().setState(army_click_state(*pIndex));
		UIArmyFunction::getInstance().adjustUi();

		//CPlayerTroopGroup* troop = CPlayer::getInstance().getActiveClan()->getPlayerTroopGroup(CPlayer::getInstance().getSelectId());
		//if(!troop)
		//{
		//	return;
		//}
       
  //      CTroopGroupEntity* troopEntity = CSceneManager::getInstance().getTroopGroupEntity( troop->getID() );
		//if(troopEntity)
		//{
		//	mSelectTroopGroupEntity = troopEntity;
		//	mSelectTroopGroup = troop;
		//	//mSelectIndex = 0;
		//	//ClientMain::getInstance().getGameObjectOpCtrl()->addSelected( troopEntity );
		//	//CSceneManager::getInstance().getEngineScene()->getActiveCamera()->focusPosition(troopEntity->getPos());
		//}

	}
	
	//----------------------------------------------------------------------------------------
	void UIArmyFunction::onClickGeneralSkill( void* widget , int x, int y, MouseCode index)
	{
        DYNAMIC_ASSERT(widget);
        IIcon* pIcon = (IIcon*)widget;
        IAny* pAny = pIcon->getWidget()->getUserData();
        DYNAMIC_ASSERT(pAny);
        Int* pIndex = pAny->castType<Int>();
        DYNAMIC_ASSERT(pIndex);

		//UIArmyFunction::getInstance().setState(army_click_state_soldier_skill1);
		//UIArmyFunction::getInstance().adjustUi();
		if(!mSelectPlayerCharacterEntity || !mSelectPlayerCharacter)
		{
			return;
		}

		//CSkillManagerForCharacter* skillManager = mSelectPlayerCharacter->getSkillManager();
		//if(!skillManager)
		//{
		//	return;
		//}

		//SkillObject* skillObject = skillManager->getSkill((UInt)(*pIndex));
		////if(!skillObject || mSelectPlayerCharacter->checkSkillCD(skillObject->getBaseInfo()) == false)
		////{
		////	return;
		////}

		//ClientMain::getInstance().getGameObjectOpCtrl()->requestUseSkill(mSelectPlayerCharacterEntity, skillObject->getBaseInfo()->id);

	}

	
	//----------------------------------------------------------------------------------------
	void UIArmyFunction::onClickSoldierSkill( void* widget )
	{
        DYNAMIC_ASSERT(widget);
        IButton* pButton = (IButton*)widget;
        IAny* pAny = pButton->getWidget()->getUserData();
        DYNAMIC_ASSERT(pAny);
        Int* pIndex = pAny->castType<Int>();
        DYNAMIC_ASSERT(pIndex);

		//if(!mSelectTroopGroup || !mSelectTroopGroupEntity)
		//{
		//	return;
		//}

		/*CPlayerTroop* playerTroop = (CPlayerTroop*)mSelectTroopGroup->getTroop(0);
		if(!playerTroop)
		{
			return;
		}

		CSkillManagerForCharacter* skillManager = playerTroop->getSkillManager();
		if(!skillManager)
		{
			return;
		}
		
		SkillObject* skillObject = skillManager->getSkill((UInt)(*pIndex - army_click_state_soldier_skill1));
		if(!skillObject)
		{
			return;
		}

		ClientMain::getInstance().getGameObjectOpCtrl()->requestUseSkill(mSelectTroopGroupEntity, skillObject->getBaseInfo()->id);*/

	}

	
	//----------------------------------------------------------------------------------------
	void UIArmyFunction::onClickTroopGroupRight(void* widget)
	{
		//if(!mSelectTroopGroup || !mSelectTroopGroupEntity)
		//{
		//	return;
		//}

		//Vec3 dir = mSelectTroopGroupEntity->getDir();
		//dir = rotateVector(dir, -30 * (MG_PI / 180));
		//TroopNetPacketProcesser::getInstance().sendTroopGroupYawToDir(mSelectTroopGroupEntity->getID(), dir);
		//mSelectTroopGroupEntity->yawToDir(dir);
	}

	//----------------------------------------------------------------------------------------
	void UIArmyFunction::onClickTroopGroupLeft(void *widget)
	{
		//if(!mSelectTroopGroup || !mSelectTroopGroupEntity)
		//{
		//	return;
		//}

		//Vec3 dir = mSelectTroopGroupEntity->getDir();
		//dir = rotateVector(dir, 30 * (MG_PI / 180));
		//TroopNetPacketProcesser::getInstance().sendTroopGroupYawToDir(mSelectTroopGroupEntity->getID(), dir);
		//mSelectTroopGroupEntity->yawToDir(dir);
	}

	//----------------------------------------------------------------------------------------
	void UIArmyFunction::onClickTroopGroupStopMove(void *widget)
	{
		//if(!mSelectTroopGroup || !mSelectTroopGroupEntity)
		//{
		//	return;
		//}
		//
		//TroopNetPacketProcesser::getInstance().sendTroopGroupStopMove(mSelectTroopGroupEntity->getID());
		//mSelectTroopGroupEntity->stopMove();
	}

	//----------------------------------------------------------------------------------------
	void UIArmyFunction::clearGeneralSkillIcon()
	{
		Char8 tempStr[20] = "";
		for(UInt i = 0; i < 8; ++i)
		{

			sprintf_s(tempStr, sizeof(tempStr), "icon_skill%d", i + 1);
			IIcon* icon = UIArmyFunction::getInstance().getLayout()->getIcon(tempStr);
			icon->setTexture("", "", "");
		}
	}

	//----------------------------------------------------------------------------------------
	void UIArmyFunction::clearSelect()
	{
		clearSelectPlayerCharacter();
		clearSelectTroopGroup();
	}

	//----------------------------------------------------------------------------------------
	void UIArmyFunction::clearSelectPlayerCharacter()
	{
		mSelectPlayerCharacterEntity = NULL;
		mSelectPlayerCharacter = NULL;
	}

	//----------------------------------------------------------------------------------------
	void UIArmyFunction::clearSelectTroopGroup()
	{
		//mSelectTroopGroupEntity = NULL;
		//mSelectTroopGroup = NULL;
	}

	//----------------------------------------------------------------------------------------
	void UIArmyFunction::setState( army_click_state state )
	{
		mState = state;
	}
	//----------------------------------------------------------------------------------------
	void UIArmyFunction::adjustUi()
	{
		switch(mState)
		{
		case army_click_state_null:
			{
				getLayout()->getImage("img_generalSkill")->getWidget()->setVisible(false);
				getLayout()->getImage("img_soldierCmd")->getWidget()->setVisible(false);
			}
			break;
		case army_click_state_general1:
			{
				getLayout()->getImage("img_soldier1")->getWidget()->setPosition(mImgSoldier1Pos2);
				getLayout()->getImage("img_soldier2")->getWidget()->setPosition(mImgSoldier2Pos1);
				getLayout()->getImage("img_soldier3")->getWidget()->setPosition(mImgSoldier3Pos1);
				//¼ÓÔØ¼¼ÄÜÀ¸ ÃüÁîÀ¸£º
				getLayout()->getImage("img_generalSkill")->getWidget()->setPosition(mImgGeneralSkillPos1);
				getLayout()->getImage("img_generalSkill")->getWidget()->setVisible(true);
				getLayout()->getImage("img_soldierCmd")->getWidget()->setVisible(false);
			}
			break;
		case army_click_state_general2:
			{

				getLayout()->getImage("img_soldier1")->getWidget()->setPosition(mImgSoldier1Pos1);
				getLayout()->getImage("img_soldier2")->getWidget()->setPosition(mImgSoldier2Pos2);
				getLayout()->getImage("img_soldier3")->getWidget()->setPosition(mImgSoldier3Pos1);
				getLayout()->getImage("img_generalSkill")->getWidget()->setPosition(mImgGeneralSkillPos2);
				getLayout()->getImage("img_generalSkill")->getWidget()->setVisible(true);
				getLayout()->getImage("img_soldierCmd")->getWidget()->setVisible(false);
			}
			break;
		case army_click_state_general3:
			{
				getLayout()->getImage("img_soldier1")->getWidget()->setPosition(mImgSoldier1Pos1);
				getLayout()->getImage("img_soldier2")->getWidget()->setPosition(mImgSoldier2Pos1);
				getLayout()->getImage("img_soldier3")->getWidget()->setPosition(mImgSoldier3Pos2);
				getLayout()->getImage("img_generalSkill")->getWidget()->setPosition(mImgGeneralSkillPos3);
				getLayout()->getImage("img_generalSkill")->getWidget()->setVisible(true);
				getLayout()->getImage("img_soldierCmd")->getWidget()->setVisible(false);
			}
			break;
		case army_click_state_soldier1:
			{
				getLayout()->getImage("img_soldier1")->getWidget()->setPosition(mImgSoldier1Pos2);
				getLayout()->getImage("img_soldier2")->getWidget()->setPosition(mImgSoldier2Pos1);
				getLayout()->getImage("img_soldier3")->getWidget()->setPosition(mImgSoldier3Pos1);
				getLayout()->getImage("img_soldierCmd")->getWidget()->setPosition(mImgSoldierCmdPos1);
				getLayout()->getImage("img_generalSkill")->getWidget()->setVisible(false);
				getLayout()->getImage("img_soldierCmd")->getWidget()->setVisible(true);
			}
			break;
		case army_click_state_soldier2:
			{
				getLayout()->getImage("img_soldier1")->getWidget()->setPosition(mImgSoldier1Pos1);
				getLayout()->getImage("img_soldier2")->getWidget()->setPosition(mImgSoldier2Pos2);
				getLayout()->getImage("img_soldier3")->getWidget()->setPosition(mImgSoldier3Pos1);
				getLayout()->getImage("img_soldierCmd")->getWidget()->setPosition(mImgSoldierCmdPos2);
				getLayout()->getImage("img_generalSkill")->getWidget()->setVisible(false);
				getLayout()->getImage("img_soldierCmd")->getWidget()->setVisible(true);
			}
			break;
		case army_click_state_soldier3:
			{
				getLayout()->getImage("img_soldier1")->getWidget()->setPosition(mImgSoldier1Pos1);
				getLayout()->getImage("img_soldier2")->getWidget()->setPosition(mImgSoldier2Pos1);
				getLayout()->getImage("img_soldier3")->getWidget()->setPosition(mImgSoldier3Pos2);
				getLayout()->getImage("img_soldierCmd")->getWidget()->setPosition(mImgSoldierCmdPos3);
				getLayout()->getImage("img_generalSkill")->getWidget()->setVisible(false);
				getLayout()->getImage("img_soldierCmd")->getWidget()->setVisible(true);
			}
			break;
		}
	}
	//----------------------------------------------------------------------------------------

}