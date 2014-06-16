//*************************************************************************************

#include "stdafx.h"
#include "UIBattleScore.h"
#include "CRegionManager.h"
#include "CPlayer.h"
#include "CampaignNetPacketProcesser.h"
#include "PlayCharacterNetPacketProcesser.h"
#include "PlayerNetPacketProcesser.h"
#include "ItemGroupTemplate.h"
#include "ItemMoneyTemplate.h"
#include "ItemExpListCsv.h"
#include "UIItemTips.h"
#include "CItemManager.h"
//*************************************************************************************
namespace MG
{
	UIBattleScore::UIBattleScore()
		:mCurBattleInfoForce(FORCE_INIT)
		,mItemGroupId(0)
		,mCloseTimeSecond(0)
		,mCampaignResult(CampaignResult_Init)
	{
	}

	UIBattleScore::~UIBattleScore()
	{
	}

	void UIBattleScore::setEvent()
	{
		//【右边按钮】
		{
			IButton* btnConfirm = getLayout()->getButton("Btn_Right");
			btnConfirm->getWidget()->setMouseButtonClickEvent(onEventConfirm);
		}

		//【右边按钮】
		{
			IButton* btnConfirm = getLayout()->getButton("Btn_Left");
			btnConfirm->getWidget()->setMouseButtonClickEvent(onEventConfirm);
		}

		//【右边按钮】
		{
			IButton* btnConfirm = getLayout()->getButton("Btn_Leave");
			btnConfirm->getWidget()->setMouseButtonClickEvent(onEventLeave);
		}

		//icon
		Char8 temp[24] = "";
		IWidget* p = NULL;
		for (Int i=1; i<=5; i++)
		{
			sprintf_s(temp, 24, "gruse%d", i);
			p = getLayout()->getWidget(temp);
			p->setToolTipsEvent(onEventToolTips);
			p->setNeedToolTip(true);
			IconInfo info;
			info.group = ICON_GROUP_ITEMSHOP;
			info.type = ICON_TYPE_ITEM;
			info.index = i;
			p->setUserData(info);
		}
		
	}

	void UIBattleScore::setCloseTime(Flt seconds)
	{
		getLayout()->getWidget(MAIN_WIDGET)->setCloseEvent(seconds, onCloseTimeCallBack);
	}

	void UIBattleScore::setTime(U32 time)
	{
		mCloseTimeSecond  = time;
	}

	void UIBattleScore::onCloseTimeCallBack(void* widget)
	{
		UIBattleScore::getInstance().onEventLeave(widget);
	}

	Bool UIBattleScore::openGui()
	{
		if (  false == UIObject::isOpen() )
		{
			DYNAMIC_ASSERT(mCloseTimeSecond > 0);
			setCloseTime(mCloseTimeSecond);
			UIObject::openGui();
			UIFresh();
		}
		else
		{
			UIObject::closeGui();
		}

		return false;
	}

	//------------------------------------------------------------------------
	void UIBattleScore::onEventConfirm(void* widget)
	{
		UIBattleScore::getInstance().UIFreshByButton();
	}

	//------------------------------------------------------------------------
	void UIBattleScore::onEventLeave(void* widget)
	{
		AccountIdType accountId =  CPlayer::getInstance().getAccountID();
		PlayerCharacterIdType playerCharacterId = CPlayer::getInstance().getMainPlayerCharacterId();
		const U32 itemGroupId = UIBattleScore::getInstance().getItemGroupId();
		CampaignNetPacketProcesser::getInstance().sendCampaignLeaveScore(playerCharacterId, itemGroupId);

		//退出战场
		PlayCharacterNetPacketProcesser::getInstance().sendPlayerCharacterJumpLastRegion(playerCharacterId);
		//PlayerNetPacketProcesser::getInstance().sendPlayerEnterRegionByCharId(accountId, playerCharacterId);
	}

	//------------------------------------------------------------------------
	void UIBattleScore::UIFresh()
	{
		FORCE myForce = CPlayer::getInstance().getForce();
		DYNAMIC_ASSERT(myForce == FORCE_ATTACK || myForce == FORCE_DEFENSE);
		
		UIFreshByForce(myForce);
		UIFreshItem(getItemGroupId());
		UIFreshByForceWinLose();
	}
	//------------------------------------------------------------------------
	void UIBattleScore::UIFreshByButton()
	{
		DYNAMIC_ASSERT(mCurBattleInfoForce == FORCE_ATTACK || mCurBattleInfoForce == FORCE_DEFENSE);

		if (mCurBattleInfoForce == FORCE_ATTACK)
		{
			UIFreshByForce(FORCE_DEFENSE);
		}
		else if (mCurBattleInfoForce == FORCE_DEFENSE)
		{
			UIFreshByForce(FORCE_ATTACK);
		}
		else
		{
			DYNAMIC_ASSERT(0);
		}
	}

	void UIBattleScore::UIFreshByForceWinLose()
	{
		std::string strItemName = "";
		if (mCampaignResult == CampaignResult_Win)
		{
			strItemName = "1";
		}
		else if(mCampaignResult == CampaignResult_Lose)
		{
			strItemName = "2";
		}
		else
		{
			DYNAMIC_ASSERT(0);
		}


		IImage *headimg = getLayout()->getImage("Image_WinLose");
		headimg->setItemResource("Main_Icon_War");
		headimg->setItemGroup("Wars");
		headimg->setItemName(strItemName);
	}

	void UIBattleScore::setCampaignResult(CampaignResult result)
	{
		DYNAMIC_ASSERT(result > CampaignResult_Init && result <CampaignResult_Max);
		mCampaignResult = result;
	}

	//------------------------------------------------------------------------
	void UIBattleScore::UIFreshByForce(const FORCE force)
	{
		std::vector<BattleScoreInfo>* battleScoreList = NULL;
		ForceInfo* forceInfo = NULL;
		if (force == FORCE_ATTACK)
		{
			battleScoreList = &mAttackBattleScoreList;
			forceInfo = &mAttackInfo;
		}
		else if (force == FORCE_DEFENSE)
		{
			battleScoreList = &mDefenseBattleScoreList;
			forceInfo = &mDefenseInfo;
		}
		else
		{
			DYNAMIC_ASSERT(0);
		}

		mCurBattleInfoForce = force;
		UIFreshMainMixList(battleScoreList);
		UIFreshText(forceInfo);
	}

	//------------------------------------------------------------------------
	void UIBattleScore::UIFreshItem(U32 groupItemId)
	{
		std::vector<const ItemGroupInfo*>* groupList = ItemGroupTemplate::getInstance().getItemGroupListByGroupId(groupItemId);
		DYNAMIC_ASSERT(NULL != groupList);

		Int ItemIndex = 0;
		for (std::vector<const ItemGroupInfo*>::iterator iter = groupList->begin(); iter != groupList->end(); ++iter)
		{
			const ItemGroupInfo* itemGroup = *iter;

			const ItemInfo* iteminfo = ItemTemplate::getInstance().getItemInfo(itemGroup->ItemTemplateId);
			DYNAMIC_ASSERT(iteminfo);
			DYNAMIC_ASSERT(iteminfo->ItemType > ITEM_TYPE_NONE && iteminfo->ItemType < ITEM_TYPE_MAX);

			if (ITEM_TYPE_EXP == iteminfo->ItemType)
			{
				Char16 temp[64] = L"";
				swprintf_s(temp, 64, L"%d", iteminfo->mItemExpInfo->price * itemGroup->ItemNum);

				IWidget* pWidget = getLayout()->getWidget("text_exp");
				pWidget->setCaption(temp);

			}
			else if(ITEM_TYPE_MONEY == iteminfo->ItemType)
			{
				Char16 temp[64] = L"";

				U32 money = iteminfo->mItemMoneyInfo->Price * itemGroup->ItemNum;
				U32 money_guan = money/1000;
				U32 money_wen = money%1000;

				if (money_guan > 0)
				{
					//显示【贯】
					IWidget* pWidgetguan = getLayout()->getWidget("text_money_guan");
					swprintf_s(temp, 64, L"%d", money_guan);
					pWidgetguan->setCaption(temp);
				}


				//显示【文】
				IWidget* pWidgetwen = getLayout()->getWidget("text_money_wen");
				swprintf_s(temp, 64, L"%d", money_wen);
				pWidgetwen->setCaption(temp);



			}
			else
			{
				IImage* pImage = NULL;
				IWidget* pWidget = NULL;
				Char8 temp[64] = "";

				ItemIndex++;
				//图片
				sprintf_s(temp, 64, "gruse%d", ItemIndex);
				pImage = getLayout()->getImage(temp); 
				Str8 resName, groupName, itemName;
				iteminfo->getItemBaseIconResouce(resName, groupName, itemName);
				pImage->setTexture(resName, groupName, itemName);
				IconInfo* pInfo = pImage->getWidget()->getUserData()->castType<IconInfo>();
				DYNAMIC_ASSERT(pInfo);
				pInfo->tempID = iteminfo->getItemBaseTemplateID();
				//pInfo->dbID = dbId;
				pImage->getWidget()->setUserData(*pInfo);

				//数量
				sprintf_s(temp, 64, "grtext%d", ItemIndex);
				pWidget = getLayout()->getWidget(temp);
				Char16 tempNumStr[16] = L"";
				swprintf_s(tempNumStr, 16, L"%d", itemGroup->ItemNum * itemGroup->ItemNum);
				pWidget->setCaption(tempNumStr) ;
			}

		}
	}

	//------------------------------------------------------------------------
	void UIBattleScore::UIFreshMainMixList(std::vector<BattleScoreInfo>* battleScoreList)
	{
		IMixList* listMainZone = getLayout()->getMixList("mixList_BattleScore");
		DYNAMIC_ASSERT(listMainZone);

		listMainZone->removeAllLine();

		for (Int i=0; i<battleScoreList->size(); ++i)
		{
			listMainZone->addLine(i,L"");
			IMixListRow* row = listMainZone->getMixListRow(i);

			//一行数据
			BattleScoreInfo* info = &(battleScoreList->at(i));
			row->getChildWidget(0)->setCaption(info->strGeneralName);
			row->getChildWidget(1)->setCaption(info->strKillGeneralPoint);
			row->getChildWidget(2)->setCaption(info->strKillArmyPoint);
			row->getChildWidget(3)->setCaption(L"-");
			row->getChildWidget(4)->setCaption(L"-");
			row->getChildWidget(5)->setCaption(L"-");
			row->getChildWidget(6)->setCaption(info->strDeathPoint);
			row->getChildWidget(7)->setCaption(info->strBattleAchievement);
			row->getChildWidget(8)->setCaption(info->strRankList);

			//居中显示
			for (Int i=0; i<9; ++i)
			{
				row->getChildWidget(i)->getText()->setTextAlign(Center);
			}

		}
	}

	//------------------------------------------------------------------------
	void UIBattleScore::UIFreshText(const ForceInfo* forceInfo)
	{
		//军队信息
		{
			IForm* mainForm = getLayout()->getForm("_Main");
			mainForm->setItemTexture("Main_Icon_War", "Wars", forceInfo->strWinResult);
		}

		//地区信息
		{
			IText* text = getLayout()->getText("Text_Region");
			text->getWidget()->setCaption(forceInfo->strRegionName);
		}

		//武将信息
		{
			IText* text = getLayout()->getText("Text_GeneralNum");
			text->getWidget()->setCaption(forceInfo->generalNum);
		}
		
		//军队信息
		{
			IText* text = getLayout()->getText("Text_TroopNum");
			text->getWidget()->setCaption(forceInfo->troopNum);
		}
	}

	//------------------------------------------------------------------------
	void UIBattleScore::addForceInfo(const NetAddForceInfo* forceInfo, const FORCE winnerForce)
	{
		mAttackInfo.clear();
		mDefenseInfo.clear();
		DYNAMIC_ASSERT(forceInfo[0].force == FORCE_ATTACK && forceInfo[1].force == FORCE_DEFENSE);
		
		wchar_t temp[32] = L"";
		
		//攻击方的信息
		{
			mAttackInfo.clear();
			CRegionObject* regionObj = CRegionManager::getInstance().getRegionObjectById(ROT_PLACE, forceInfo[0].regionId);
			mAttackInfo.strRegionName = regionObj->getRegionNameStr16();
			swprintf(temp, 32, L"%d", mAttackBattleScoreList.size());
			mAttackInfo.generalNum = temp;
			swprintf(temp, 32, L"%d", forceInfo[0].troopNum);
			mAttackInfo.troopNum = temp;

			if (forceInfo[0].force == winnerForce)
			{
				//我是胜利方
				mAttackInfo.strWinResult = "1";
			}
			else
			{
				//我是失败方
				mAttackInfo.strWinResult = "2";
			}
		}

		//攻击方的信息
		{
			mDefenseInfo.clear();
			CRegionObject* regionObj = CRegionManager::getInstance().getRegionObjectById(ROT_PLACE, forceInfo[1].regionId);
			mDefenseInfo.strRegionName = regionObj->getRegionNameStr16();
			swprintf(temp, 32, L"%d", mDefenseBattleScoreList.size());
			mDefenseInfo.generalNum = temp;
			swprintf(temp, 32, L"%d", forceInfo[1].troopNum);
			mDefenseInfo.troopNum = temp;

			if (forceInfo[1].force == winnerForce)
			{
				//我是胜利方
				mDefenseInfo.strWinResult = "1";
			}
			else
			{
				//我是失败方
				mDefenseInfo.strWinResult = "2";
			}
		}
		
		int kk = 0;

	}
	//------------------------------------------------------------------------
	void UIBattleScore::addBattleScore(const Int num, const NetAddCampaignEnd* info, const FORCE winnerForce)
	{
		mAttackBattleScoreList.clear();
		mDefenseBattleScoreList.clear();
		
		wchar_t temp[32] = L"";
		for (Int i=0; i<num; ++i)
		{
			BattleScoreInfo battleScoreInfo;
			
			battleScoreInfo.strGeneralName = info[i].playerCharacterName;
			swprintf(temp, 32, L"%d", info[i].killGeneralPoint);
			battleScoreInfo.strKillGeneralPoint = temp;
			swprintf(temp, 32, L"%d", info[i].killArmyPoint);
			battleScoreInfo.strKillArmyPoint = temp;
			swprintf(temp, 32, L"%d", info[i].destoryForcePoint);
			battleScoreInfo.strDestoryForcePoint = temp;
			swprintf(temp, 32, L"%d", info[i].constructBuild);
			battleScoreInfo.strConstructBuild = temp;
			swprintf(temp, 32, L"%d", info[i].healGeneralPoint);
			battleScoreInfo.strHealGeneralPoint = temp;
			swprintf(temp, 32, L"%d", info[i].deathPoint);
			battleScoreInfo.strDeathPoint = temp;
			swprintf(temp, 32, L"%d", info[i].battleAchievement);
			battleScoreInfo.strBattleAchievement = temp;
			swprintf(temp, 32, L"%d级", info[i].RankList);
			battleScoreInfo.strRankList = temp;

			if (FORCE_ATTACK == info[i].force)
			{
				mAttackBattleScoreList.push_back(battleScoreInfo);
			}
			else if (FORCE_DEFENSE == info[i].force)
			{
				mDefenseBattleScoreList.push_back(battleScoreInfo);
			}
			else
			{
				DYNAMIC_ASSERT(0);
			}
		}
	}

	void UIBattleScore::setItemGroupId(U32 itemGroupId)
	{
		mItemGroupId = itemGroupId;
	}

	U32 UIBattleScore::getItemGroupId() const
	{
		return mItemGroupId;
	}

	void UIBattleScore::onEventToolTips( void* pWidget, Bool isShow, Int left, Int top )
	{
		DYNAMIC_ASSERT(pWidget);
		IWidget* pIcon = (IWidget*)pWidget;
		IAny* pAny = pIcon->getUserData();
		DYNAMIC_ASSERT(pAny);
		IconInfo* pInfo = pAny->castType<IconInfo>();
		DYNAMIC_ASSERT(pInfo);

		if ( pInfo->tempID )
		{
			if ( isShow == false )
			{
				UIItemTips::getInstance().closeGui();
			}
			else
			{
				if ( pInfo->dbID )
				{
					PlayerItem* pItem = CItemManager::getInstance().findItem(pInfo->dbID);
					DYNAMIC_ASSERT(pItem);
					UIItemTips::getInstance().openItemTips(pItem, pIcon->getAbsoluteCoord());
				}
				else
				{
					const ItemInfo* pItemInfo = ItemTemplate::getInstance().getItemInfo(pInfo->tempID);
					UIItemTips::getInstance().openItemTips(pItemInfo, pIcon->getAbsoluteCoord());
				}
			}
		}
	}
	//------------------------------------------------------------------------
}