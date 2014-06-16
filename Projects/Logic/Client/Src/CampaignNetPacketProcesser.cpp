
/******************************************************************************/
#include "stdafx.h"
#include "CampaignNetPacketProcesser.h"
#include "ClientNetApplyManager.h"
#include "CPlayer.h"
#include "UIManage.h"
#include "UIMessageBox.h"
#include "UIArmyFunction.h"
#include "UIGenrealPicture.h"
#include "ClientMain.h"
#include "GameSoundManager.h"
#include "CCampaignManager.h"
#include "UICampaignListNew.h"
#include "UICampaignInfoNew.h"
#include "UICampaignSystemNew.h"
#include "UICampaignInviteDefense.h"
#include "UICampaignBarrack.h"
#include "CSceneManager.h"
#include "CTroopEntity.h"
#include "MessageManager.h"
#include "CTroopSoldierEntity.h"
#include "UIBattleScore.h"
#include "CRegionManager.h"
#include "UICampaignWinLoseMsg.h"
#include "UICampaignFight.h"
#include "UICampaignWar.h"
#include "UISLGTimeLeft.h"
#include "UISLGTeam.h"
/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------
	Bool CampaignNetPacketProcesser::processFrontServerPacket(I32 id,NetEventRecv* packet)
	{
		if ( packet->getChannel() == GNPC_CAMPAIGN )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_CAMPAIGN_T2C_ERROR:
				onRecvCampaignError( id, (PT_CAMPAIGN_T2C_ERROR_DATA*)data->data );
				break;
			case PT_CAMPAIGN_T2C_CAMPAIGN_LIST_BEGIN:
				onRecvCampaignListBegin( id, (PT_CAMPAIGN_T2C_CAMPAIGN_LIST_BEGIN_DATA*)data->data );
				break;
			case PT_CAMPAIGN_T2C_CAMPAIGN_LIST:
				onRecvCampaignList( id, (PT_CAMPAIGN_T2C_CAMPAIGN_LIST_DATA*)data->data );
				break;
			case PT_CAMPAIGN_T2C_CAMPAIGN_LIST_END:
				onRecvCampaignListEnd( id, (PT_CAMPAIGN_T2C_CAMPAIGN_LIST_END_DATA*)data->data );
				break;
			case PT_CAMPAIGN_T2C_CREATE:
				onRecvCampaignCreate( id, (PT_CAMPAIGN_T2C_CREATE_DATA*)data->data );
				break;
			case PT_CAMPAIGN_F2C_ENTER_ATTACK:
				onRecvCampaignEnterAttack( id, (PT_CAMPAIGN_F2C_ENTER_ATTACK_DATA*)data->data );
				break;
			case PT_CAMPAIGN_F2C_ENTER_DEFENSE:
				onRecvCampaignEnterDefense( id, (PT_CAMPAIGN_F2C_ENTER_DEFENSE_DATA*)data->data );
				break;
			case PT_CAMPAIGN_T2C_CAMPAIGN_INFO:
				onRecvCampaignInfo( id, (PT_CAMPAIGN_T2C_CAMPAIGN_INFO_DATA*)data->data );
				break;
			case PT_CAMPAIGN_F2C_MEMBER_LIST:
				onRecvCampaignMemberList( id, (PT_CAMPAIGN_F2C_MEMBER_LIST_DATA*)data->data );
				break;
			case PT_CAMPAIGN_M2C_INVITE_DEFENSE_REGION:
				onRecvCampaignInviteDefense( id, (PT_CAMPAIGN_M2C_INVITE_DEFENSE_REGION_DATA*)data->data );
				break;
			case PT_CAMPAIGN_M2C_END:
				onRecvCampaignEnd( id, (PT_CAMPAIGN_M2C_END_DATA*)data->data );
				break;
			case PT_CAMPAIGN_T2C_READY_MYSELF:
				onRecvCampaignReadyMySelf( id, (PT_CAMPAIGN_T2C_READY_MYSELF_DATA*)data->data );
				break;
			case PT_CAMPAIGN_T2C_LEAVE:
				onRecvCampaignLeave( id, (PT_CAMPAIGN_T2C_LEAVE_DATA*)data->data );
				break;
			case PT_CAMPAIGN_T2C_DESTROY:
				onRecvCampaignDestroy( id, (PT_CAMPAIGN_T2C_DESTROY_DATA*)data->data );
				break;
			case PT_CAMPAIGN_T2C_START_NEW_CAMPAIGN:
				onRecvCampaignStartNewCampaign( id, (PT_CAMPAIGN_T2C_START_NEW_CAMPAIGN_DATA*)data->data );
				break;
			case PT_CAMPAIGN_M2C_CHANGE_CAMP_CONTROL:
				onRecvCampaignChangeCampControl( id, (PT_CAMPAIGN_M2C_CHANGE_CAMP_CONTROL_DATA*)data->data );
				break;
			case PT_CAMPAIGN_M2C_CHANGE_TROOP_CONTROL:
				onRecvCampaignChangeTroopControl( id, (PT_CAMPAIGN_M2C_CHANGE_TROOP_CONTROL_DATA*)data->data );
				break;
			case PT_CAMPAIGN_M2C_TROOP_CONTROLLER_LIST:
				onRecvCampaignTroopControllerList( id, (PT_CAMPAIGN_M2C_TROOP_CONTROLLER_LIST_DATA*)data->data );
				break;
			case PT_CAMPAIGN_F2C_LEAVE_IN_CAMPAIGN:
				onRecvCampaignLeaveInCampaign( id, (PT_CAMPAIGN_F2C_LEAVE_IN_CAMPAIGN_DATA*)data->data );
				break;
			default:
				DYNAMIC_ASSERT(0);
				break;
			}
			return true;
		}
		return false;
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignListBegin( I32 id, PT_CAMPAIGN_T2C_CAMPAIGN_LIST_BEGIN_DATA* data )
	{
		CCampaignManager::getInstance().clearPrepareCampaign();
	}
	
	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignList( I32 id, PT_CAMPAIGN_T2C_CAMPAIGN_LIST_DATA* data )
	{
		for (Int i=0; i<data->addCampainNum; ++i)
		{
			NetCampainInfo* campInfo = &(data->addCampainInfo[i]);

			SCampaign* newCampaign = CCampaignManager::getInstance().createCampaign(0, campInfo->accountId, campInfo->campaignId,
				campInfo->creatorClanName, campInfo->campaignName, campInfo->targetRegionId, (REGION_OBJ_TYPE)campInfo->targetRegionType);

			ClanArmy*	newMember = newCampaign->getAttackHostMemberInfoByClanId(campInfo->creatorClanId);
			DYNAMIC_ASSERT(NULL != newMember);
			//newMember->playerCharacterInfo.playerCharacterId	= data->creatorPlayerCharacterId;
			newMember->playerCharacterInfo.charArtIcon			= campInfo->charArtIcon;
			newMember->playerCharacterInfo.playerCharacterName	= campInfo->creatorPlayerCharacterName;

			DYNAMIC_ASSERT(NULL != newCampaign);
			newCampaign->setAttackRealMemberNum(campInfo->memberNum);
		}

	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignListEnd( I32 id, PT_CAMPAIGN_T2C_CAMPAIGN_LIST_END_DATA* data )
	{
		UICampaignListNew::getInstance().loadCampaignList();
		UICampaignListNew::getInstance().openGui();
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignCreate( I32 id, PT_CAMPAIGN_T2C_CREATE_DATA* data )
	{
		AccountIdType	accountId		= data->campaignInfo.accountId;
		CampaignIdType	campaignId		= data->campaignInfo.campaignId;
		RegionIdType	targetRegionId	= data->campaignInfo.targetRegionId;
		Char16*			creatorName		= data->campaignInfo.creatorClanName;
		Char16*			campaignName	= data->campaignInfo.campaignName;
		REGION_OBJ_TYPE targetRegionType = (REGION_OBJ_TYPE)data->campaignInfo.targetRegionType;

		CCampaignManager* test = &(CCampaignManager::getInstance());
		SCampaign* newCampaign = CCampaignManager::getInstance().createCampaign(0, accountId, campaignId, creatorName, campaignName,
			targetRegionId, targetRegionType);

		DYNAMIC_ASSERT(NULL != newCampaign);

		ClanArmy*	newMember = newCampaign->getAttackHostMemberInfoByClanId(data->campaignInfo.creatorClanId);
		DYNAMIC_ASSERT(NULL != newMember);
		//newMember->playerCharacterInfo.playerCharacterId	= data->creatorPlayerCharacterId;
		newMember->playerCharacterInfo.charArtIcon			= data->campaignInfo.charArtIcon;
		newMember->playerCharacterInfo.playerCharacterName	= data->campaignInfo.creatorPlayerCharacterName;

		CPlayer* myPlayer = &(CPlayer::getInstance());


		UICampaignInfoNew::getInstance().clearAllCampaignInfo();
		if (accountId == myPlayer->getAccountID())
		{
			UICampaignFight::getInstance().clear();
			myPlayer->setMyCampaign(newCampaign);


			CPlayerCharacter* myCharacter = CPlayer::getInstance().getMainGenreal();
			DYNAMIC_ASSERT(NULL != myCharacter);
			UICampaignInfoNewSingle tempInfo;
			tempInfo.charArtIcon = myCharacter->getData()->charArtIcon;
			tempInfo.level	= myCharacter->getLevel();
			tempInfo.curHP	= myCharacter->getHp();
			tempInfo.maxHP	= myCharacter->getHp();
			tempInfo.curMP	= myCharacter->getMp();
			tempInfo.maxMP	= myCharacter->getMp();
			tempInfo.clanName = data->campaignInfo.creatorPlayerCharacterName;
			tempInfo.isMe	= true;

			UICampaignInfoNew::getInstance().setTargetRegionId(data->campaignInfo.targetRegionId);
			UICampaignInfoNew::getInstance().modifyLeaderInfo(&tempInfo);
			UICampaignSystemNew::getInstance().openGui();


			UICampaignFight::getInstance().addCampaignFightInfo(FORCE_ATTACK, myCharacter->getData()->charArtIcon, POSITION_1, true);
			CPlayer::getInstance().setForce(FORCE_ATTACK);
		}
		else
		{
			UICampaignListNew::getInstance().UIReFresh();
		}


		//UICampaignSystemNew::getInstance().openGui();
#if 0
		//FUNDETECTION(__MG_FUNC__);
		const U64	creatorClanId		 = data->campaignInfo.campaignId;
		const U64	targetRegionId		 = data->campaignInfo.targetRegionId;
		const Char16*	creatorName		 = data->campaignInfo.creatorName;
		const Char16*	campaignName	 = data->campaignInfo.campaignName;

		CPlayer* myPlayer = &(CPlayer::getInstance());
		CCampaignSystemInRegion* myCapaignSystem = myPlayer->getCampaignSystem();
		myCapaignSystem->createCampaign(0, creatorClanId, creatorName, targetRegionId, campaignName);

		//加载CampaignList
		UICampaignList::getInstance().reload();

		const U64 clandId = myPlayer->getActiveClan()->getClanID();
		Campaign* myCampaign = myCapaignSystem->getPrepareCampaign(creatorClanId);
		if(clandId == creatorClanId)
		{
			//我自己创建的房间
			myCapaignSystem->enterCampaignByCreator(0, creatorClanId, creatorClanId, creatorName);
			myCapaignSystem->setMyCampaign(myCampaign);
			
			//是我自己创建的战斗， 直接打开队伍信息
			UICampaignCreate::getInstance().closeGui();

			UICampaignInfo::getInstance().reload();
			UICampaignInfo::getInstance().openGui();
		}
		else
		{
			if (NULL == myCampaign)
			{
				UICampaignList::getInstance().openGui();
			}
		}

#endif


	}


	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignEnterAttack( I32 id, PT_CAMPAIGN_F2C_ENTER_ATTACK_DATA* data )
	{
		Bool isMe = false;

		DYNAMIC_ASSERT(data->targetRegionId > 0);
		UICampaignInfoNew::getInstance().setTargetRegionId(data->targetRegionId);
		
		NetCampaignMemberInfo* newMemberInfo = &(data->newMember);
		if (newMemberInfo->accountId == CPlayer::getInstance().getAccountID())
		{
			isMe = true;
		}
		UICampaignInfoNewSingle tempInfo;
		tempInfo.charArtIcon	= newMemberInfo->charArtIcon;
		tempInfo.level 			= newMemberInfo->level;
		tempInfo.curHP 			= newMemberInfo->hp;
		tempInfo.maxHP 			= newMemberInfo->hp;
		tempInfo.curMP 			= newMemberInfo->mp;
		tempInfo.maxMP 			= newMemberInfo->mp;
		tempInfo.clanName		= newMemberInfo->playerCharacterName;
		tempInfo.isMe			= isMe;

		if (true == newMemberInfo->isHost)
		{
			UICampaignInfoNew::getInstance().modifyLeaderInfo(&tempInfo);
			UICampaignInfoNew::getInstance().UIReFresh();
		}
		else
		{
			UICampaignInfoNew::getInstance().addMemberInfo(newMemberInfo->position, &tempInfo);
		}
		
		if (true == isMe)
		{
			//我自己的信息
			{
				SCampaign* myCampaign = CCampaignManager::getInstance().getPrepareCampaign(data->campaignId);
				CPlayer::getInstance().setMyCampaign(myCampaign);
				CPlayer::getInstance().setForce(FORCE_ATTACK);

			}

			UICampaignListNew::getInstance().closeGui();
			UICampaignInfoNew::getInstance().openGui();
		}
		else
		{
			UICampaignInfoNew::getInstance().UIReFresh();
		}

		//加到内存
		{
			SCampaign* newCampaign = CCampaignManager::getInstance().enterCampaignJoinAttackList(0, data->newMember.accountId, data->campaignId, data->newMember.clanId, data->newMember.playerCharacterName);
			ClanArmy*	newMember = newCampaign->getAttackMemberInfoByClanId(data->newMember.clanId);
			DYNAMIC_ASSERT(NULL != newMember);
			newMember->playerCharacterInfo.playerCharacterId	= data->newMember.playerCharacterId;
			newMember->playerCharacterInfo.charArtIcon			= data->newMember.charArtIcon;
			newMember->playerCharacterInfo.playerCharacterName	= data->newMember.playerCharacterName;


			UICampaignFight::getInstance().addCampaignFightInfo(FORCE_ATTACK, data->newMember.charArtIcon, (POSITION)data->newMember.position, data->newMember.isHost);
			//加入同一force的信息
			if (CPlayer::getInstance().getForce() == FORCE_ATTACK && isMe == false)
			{
				UISLGTeam::getInstance().addTeamMember(newMemberInfo->position, newMemberInfo->playerCharacterId);
			}
		}
		
		
		//FUNDETECTION(__MG_FUNC__);
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignEnterDefense( I32 id, PT_CAMPAIGN_F2C_ENTER_DEFENSE_DATA* data )
	{
		if (data->newMember.accountId == CPlayer::getInstance().getAccountID())
		{
			CCampaignManager* temp = &(CCampaignManager::getInstance());
			//我自己
			SCampaign* myCampaign = CCampaignManager::getInstance().getBattleCampaign(data->campaignId);
			if (NULL != myCampaign)
			{
				CPlayer::getInstance().setMyCampaign(myCampaign);
				myCampaign->setCampaignIsStart(true);
			}
			CPlayer::getInstance().setForce(FORCE_DEFENSE);
			
			CRegionObject* regionObj = CRegionManager::getInstance().getRegionObjectById((REGION_OBJ_TYPE)data->regionType, data->regionId);
			regionObj->setStartCampaignTime(GetCurrentTime() + data->prepareTimeSecond * 1000);

			UICampaignWar::getInstance().setIsShow(true);
			UICampaignWar::getInstance().setCountDownTime(data->prepareTimeSecond);
			//UICampaignListNew::getInstance().openGui();

			if(false == UICampaignFight::getInstance().getIsShow())
			{
				UICampaignFight::getInstance().setIsShow(true);
			}

		}

		//加到内存
		{
			SCampaign* curCampaign = CCampaignManager::getInstance().getBattleCampaign(data->campaignId);
			if (NULL != curCampaign)
			{
				curCampaign->joinDefenseList(0, data->newMember.accountId, data->newMember.clanId, L"");

				ClanArmy* newMember	= curCampaign->getDefenseMemberInfoByClanId(data->newMember.clanId);
				DYNAMIC_ASSERT(NULL != newMember);
				newMember->playerCharacterInfo.playerCharacterId	= data->newMember.playerCharacterId;
				newMember->playerCharacterInfo.charArtIcon			= data->newMember.charArtIcon;
				newMember->playerCharacterInfo.playerCharacterName	= data->newMember.playerCharacterName;
			}
			

			UICampaignFight::getInstance().addCampaignFightInfo(FORCE_DEFENSE, data->newMember.charArtIcon, (POSITION)data->newMember.position, false);
			
			NetCampaignMemberInfo* newMemberInfo = &(data->newMember);
			if (CPlayer::getInstance().getForce() == FORCE_DEFENSE)
			{
				UISLGTeam::getInstance().addTeamMember(newMemberInfo->position, newMemberInfo->playerCharacterId);
			}
			UICampaignFight::getInstance().UIFresh();
		}

		//Bool	bSuccess = campaign->joinAttackList(frontServerNetId, accountId, myClanId, clanName);
		//if (true == bSuccess)
		//{
		//	//成功
		//	Int memberNum = campaign->getAttackRealMemberNum();
		//	campaign->setAttackRealMemberNum(++memberNum);
		//	return campaign;
	}

	void CampaignNetPacketProcesser::onRecvCampaignInfo( I32 id, PT_CAMPAIGN_T2C_CAMPAIGN_INFO_DATA* data )
	{
		SCampaign* curCampaign = CCampaignManager::getInstance().getBattleCampaign(data->campaignInfo.campaignId);
		if (NULL != curCampaign)
		{
			return;
		}

		AccountIdType	accountId		= data->campaignInfo.accountId;
		CampaignIdType	campaignId		= data->campaignInfo.campaignId;
		RegionIdType	targetRegionId	= data->campaignInfo.targetRegionId;
		Char16*			creatorName		= data->campaignInfo.creatorClanName;
		Char16*			campaignName	= data->campaignInfo.campaignName;
		REGION_OBJ_TYPE targetRegionType = (REGION_OBJ_TYPE)data->campaignInfo.targetRegionType;

		CCampaignManager* test = &(CCampaignManager::getInstance());
		SCampaign* newCampaign = CCampaignManager::getInstance().createCampaign(0, accountId, campaignId, creatorName, campaignName,
			targetRegionId, targetRegionType);


		SCampaign* battleCamp = CCampaignManager::getInstance().popPrepareCampaign(campaignId);
		if (NULL == battleCamp)
		{
			//DYNAMIC_ASSERT(0);
			return;
		}

		CCampaignManager::getInstance().addCampaignStart(battleCamp, 0);
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignMemberList( I32 id, PT_CAMPAIGN_F2C_MEMBER_LIST_DATA* data )
	{
		DYNAMIC_ASSERT(data->addMemberNum >= 0);
		for (Int i=0; i<data->addMemberNum; ++i)
		{
			NetCampaignMemberInfo* newMemberInfo = &(data->addMemberInfo[i]);
			UICampaignInfoNewSingle tempInfo;
			tempInfo.charArtIcon = newMemberInfo->charArtIcon;
			tempInfo.level = newMemberInfo->level;
			tempInfo.curHP = newMemberInfo->hp;
			tempInfo.maxHP = newMemberInfo->hp;
			tempInfo.curMP = newMemberInfo->mp;
			tempInfo.maxMP = newMemberInfo->mp;
			tempInfo.clanName = newMemberInfo->playerCharacterName;
			if (ARMY_READY_CONFIRM == newMemberInfo->readyState)
			{
				tempInfo.isReady = true;
			}
			else if(ARMY_READY_CANCEL == newMemberInfo->readyState)
			{
				tempInfo.isReady = false;
			}
			else
			{
				DYNAMIC_ASSERT(0);
			}

			if (CPlayer::getInstance().getAccountID() == newMemberInfo->accountId)
			{
				//我自己的信息
				continue;
			}

			if (true == newMemberInfo->isHost)
			{
				//房主信息
				UICampaignInfoNew::getInstance().modifyLeaderInfo(&tempInfo);
				UICampaignInfoNew::getInstance().UIReFresh();

				CCampaignManager* temp = &(CCampaignManager::getInstance());
				
				UICampaignFight::getInstance().addCampaignFightInfo(FORCE_ATTACK, newMemberInfo->charArtIcon, POSITION_1, true);
			}
			else
			{
				if (FORCE_ATTACK == data->force)
				{
					//其他玩家信息
					UICampaignInfoNew::getInstance().addMemberInfo(newMemberInfo->position, &tempInfo);
					UICampaignInfoNew::getInstance().UIReFresh();

					CCampaignManager* temp = &(CCampaignManager::getInstance());
					SCampaign* newCampaign = CCampaignManager::getInstance().getPrepareCampaign(data->campaignId);
					if (NULL == newCampaign)
					{
						newCampaign = CCampaignManager::getInstance().getBattleCampaign(data->campaignId);
					}
					DYNAMIC_ASSERT(NULL != newCampaign);
					newCampaign->joinAttackList(0, newMemberInfo->accountId, newMemberInfo->clanId, newMemberInfo->playerCharacterName);

					//SCampaign* newCampaign = CCampaignManager::getInstance().enterCampaignJoinAttackList(0, newMemberInfo->accountId, data->campaignId, newMemberInfo->clanId, newMemberInfo->playerCharacterName);
					ClanArmy*	newMember = newCampaign->getAttackMemberInfoByClanId(newMemberInfo->clanId);
					DYNAMIC_ASSERT(NULL != newMember);
					newMember->playerCharacterInfo.playerCharacterId	= newMemberInfo->playerCharacterId;
					newMember->playerCharacterInfo.charArtIcon			= newMemberInfo->charArtIcon;
					newMember->playerCharacterInfo.playerCharacterName	= newMemberInfo->playerCharacterName;
					
					UICampaignFight::getInstance().addCampaignFightInfo(FORCE_ATTACK, newMemberInfo->charArtIcon, (POSITION)newMemberInfo->position, newMemberInfo->isHost);

				}
				else if(FORCE_DEFENSE == data->force)
				{
					SCampaign* newCampaign = CCampaignManager::getInstance().getBattleCampaign(data->campaignId);
					newCampaign->joinDefenseList(0, newMemberInfo->accountId, newMemberInfo->clanId, newMemberInfo->playerCharacterName);
					ClanArmy*	newMember = newCampaign->getDefenseMemberInfoByClanId(newMemberInfo->clanId);
					DYNAMIC_ASSERT(NULL != newMember);
					newMember->playerCharacterInfo.playerCharacterId	= newMemberInfo->playerCharacterId;
					newMember->playerCharacterInfo.charArtIcon			= newMemberInfo->charArtIcon;
					newMember->playerCharacterInfo.playerCharacterName	= newMemberInfo->playerCharacterName;

					UICampaignFight::getInstance().addCampaignFightInfo(FORCE_DEFENSE, newMemberInfo->charArtIcon, (POSITION)newMemberInfo->position, false);
				}
				else
				{
					DYNAMIC_ASSERT(0);
				}			
			}
			//加入team信息
			if (CPlayer::getInstance().getForce() == data->force)
			{
				UISLGTeam::getInstance().addTeamMember(newMemberInfo->position, newMemberInfo->playerCharacterId);
			}

		}
		
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignInviteDefense( I32 id, PT_CAMPAIGN_M2C_INVITE_DEFENSE_REGION_DATA* data )
	{
		SCampaign* myCampaign = CPlayer::getInstance().getMyCampaign();
		if (NULL == myCampaign)
		{
			UICampaignInviteDefense::getInstance().setCampaignInfo(data->toRegionId, data->toInstanceId, data->campaignId);
			UICampaignInviteDefense::getInstance().openGui();
		}
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignEnd( I32 id, PT_CAMPAIGN_M2C_END_DATA* data )
	{
		UICampaignInfoNew::getInstance().clearAllCampaignInfo();

		if (data->campaignId == CPlayer::getInstance().getMyCampaignId())
		{
			UICampaignFight::getInstance().clear();
			//设置 UI关闭时间
			SCampaign* myCampaign = CPlayer::getInstance().getMyCampaign();
			UICampaignWinLoseMsg::getInstance().setTime(myCampaign->getTimeListInfo()->time4);
			UIBattleScore::getInstance().setTime(myCampaign->getTimeListInfo()->time5);
			

			UIBattleScore::getInstance().addForceInfo(data->forceInfo, (FORCE)data->winnerForce);
			UIBattleScore::getInstance().addBattleScore(data->addBattleScoreNum, data->addBattleScoreInfo, (FORCE)data->winnerForce);

			//UIBattleScore::getInstance().openGui();
			

			const FORCE myForce = CPlayer::getInstance().getForce();
			const FORCE winnerForce = (FORCE)data->winnerForce;
			DYNAMIC_ASSERT(myForce == FORCE_ATTACK || myForce == FORCE_DEFENSE);
			if (myForce == winnerForce)
			{
				//我自己 胜利
				GameSoundManager::getInstance().play(60016);
				UIBattleScore::getInstance().setItemGroupId(data->winnerItemGroupId);
				UIBattleScore::getInstance().setCampaignResult(CampaignResult_Win);
				UICampaignWinLoseMsg::getInstance().setCampaignResult(CampaignResult_Win);
			}
			else
			{
				//我自己 失败
				GameSoundManager::getInstance().play(60017);
				UIBattleScore::getInstance().setItemGroupId(data->loserItemGroupId);
				UIBattleScore::getInstance().setCampaignResult(CampaignResult_Lose);
				UICampaignWinLoseMsg::getInstance().setCampaignResult(CampaignResult_Lose);
			}

			UICampaignWinLoseMsg::getInstance().openGui();

			CPlayer::getInstance().setMyCampaign(NULL);
		}


		CCampaignManager::getInstance().destroyCampaign(data->campaignId);
	
		UICampaignListNew::getInstance().UIReFresh();

	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignReadyMySelf( I32 id, PT_CAMPAIGN_T2C_READY_MYSELF_DATA* data )
	{
		UICampaignInfoNewSingle* memberInfo = UICampaignInfoNew::getInstance().getMemberInfoByPosition((POSITION)data->myPosition);
		DYNAMIC_ASSERT(NULL != memberInfo);
		if (ARMY_READY_CONFIRM == (ARMY_READY_STATE)data->readyState)
		{
			memberInfo->isReady = true;
		}
		else if(ARMY_READY_CANCEL == (ARMY_READY_STATE)data->readyState)
		{
			memberInfo->isReady = false;
		}
		else
		{
			DYNAMIC_ASSERT(0);
		}
		
		//UICampaignInfoNew::getInstance().UIReFresh();
		UICampaignInfoNew::getInstance().UIReFreshMemberList();
#if 0
		//FUNDETECTION(__MG_FUNC__);
		const U64 regionId		= data->regionId;
		const U64 campaignId	= data->campaignId;
		const U64 clanId		= data->clanId;
		const Byte force		= data->force;
		const Byte position		= data->position;
		const Byte readyState	= data->readyState;
		const U64 myHeroId		= data->myHeroId;
		const U64 myTroopId		= data->myTroopId;
		const U64 myTroopTemplateId = data->myTroopTemplateId;


		CPlayer* myPlayer = &(CPlayer::getInstance());
		CCampaignSystemInRegion* myCapaignSystem = myPlayer->getCampaignSystem();
		if (NULL == myCapaignSystem)
		{
			return;
		}

		Campaign* myCampaign = myCapaignSystem->getPrepareCampaign(campaignId);
		if (NULL == myCampaign)
		{
			return;
		}

		myCampaign->setCampaignReadyStateMySelf(clanId, force, position, readyState, myHeroId, myTroopId,myTroopTemplateId, data->myHeroName);

		UICampaignInfo::getInstance().UIFreshWithReload();
#endif
	}

#if 0
	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignStandByList( I32 id, PT_CAMPAIGN_SC_STANDBY_LIST_DATA* data )
	{

		//FUNDETECTION(__MG_FUNC__);
		UICampaignList::getInstance().closeGui();

		U64 campaignId		= data->campaignId;
		U64	targetRegionId  = data->regionId;

		CPlayer* myPlayer = &(CPlayer::getInstance());
		CCampaignSystemInRegion* myCapaignSystem = myPlayer->getCampaignSystem();
		Campaign* myCampaign = myCapaignSystem->getPrepareCampaign(campaignId);
		myCapaignSystem->setMyCampaign(myCampaign);

		for (Int i=0; i<data->standbyCount; ++i)
		{
			myCapaignSystem->joinStandByListByNew(campaignId, data->standbyList[i].clanId,data->standbyList[i].clanName, 
																	(FORCE)data->force, data->standbyList[i].position,
																	data->standbyList[i].readyState,
																	data->standbyList[i].playerCharacterInfo.playerCharacterId,
																	data->standbyList[i].troopInfo.troopId,
																	data->standbyList[i].troopInfo.troopTemplateId,
																	data->standbyList[i].playerCharacterInfo.playerCharacterName);

		}

		
		UICampaignInfo::getInstance().UIFreshWithReload();
		UICampaignInfo::getInstance().openGui();


	}
#endif
#if 0
	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignWaitingList( I32 id, PT_CAMPAIGN_SC_WAITING_LIST_DATA* data )
	{
		//FUNDETECTION(__MG_FUNC__);
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignJoin( I32 id, PT_CAMPAIGN_SC_JOIN_STANDBY_DATA* data )
	{
		//FUNDETECTION(__MG_FUNC__);
	}
#endif
#if 0
	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignJoinMySelf( I32 id, PT_CAMPAIGN_SC_JOIN_STANDBY_MYSELF_DATA* data )
	{

		//FUNDETECTION(__MG_FUNC__);
		const U64	regionId	= data->regionId;
		const U64	campaignId	= data->campaignId;
		const U64	joinClanId	= data->joinClanId;
		const Byte	force		= data->force;
		const Byte	position	= data->position;

		CPlayer* myPlayer = &(CPlayer::getInstance());
		CCampaignSystemInRegion* myCapaignSystem = myPlayer->getCampaignSystem();
		Campaign* myCampaign = myCapaignSystem->getPrepareCampaign(campaignId);
		
		myCapaignSystem->joinStandByListByNew(campaignId, joinClanId, data->clanName, (FORCE)force, position, 
											(Byte)ARMY_READY_CANCEL, 0, 0, 0);
		
		UICampaignInfo::getInstance().reload();
		if(joinClanId == myPlayer->getActiveClan()->getClanID())
		{
			//我自己
			myCapaignSystem->setMyCampaign(myCampaign);
			UICampaignInfo::getInstance().UIFreshWithReload();
			
		}
		else
		{
			UICampaignInfo::getInstance().UIFreshWithReload();
		}	

	}
#endif

#if 0
	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignEndBattle( I32 id, PT_CAMPAIGN_SC_END_BATTLE_DATA* data )
	{

		MG_LOG(out_sys," >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> CampaignNetPacketProcesser::onRecvCampaignEndBattle >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> \n");
		//FUNDETECTION(__MG_FUNC__);
		const U64 regionId = data->regionId;
		const U64 campaignId = data->campaignId;
		const FORCE winner = (FORCE)data->winnerForce;

		CPlayer* myPlayer = &(CPlayer::getInstance());
		CCampaignSystemInRegion* myCapaignSystem = myPlayer->getCampaignSystem();
		Campaign* destroyCampaign = myCapaignSystem->getPrepareCampaign(campaignId);
		Campaign* myCampaign = myCapaignSystem->getMyCampaign();

		Bool isMyCampaign = false;
		if (NULL != myCampaign && campaignId == myCampaign->getId())
		{
			myCapaignSystem->setMyCampaign(NULL);
			isMyCampaign = true;
		}

		//删除战斗房间
		myCapaignSystem->destroyBattleCampaign(campaignId);

		if (true == isMyCampaign)
		{
			if (FORCE_ATTACK == winner)
			{
				UIMessageBox::getInstance().showHint(L"战斗结束, 攻击方胜利");
			}
			else if(FORCE_DEFENSE == winner)
			{
				UIMessageBox::getInstance().showHint(L"战斗结束, 防守方胜利");
			}
			else
			{
				DYNAMIC_ASSERT(0);
			}


			//播放音乐
			GameSoundManager::getInstance().play(2);
		}

	}
#endif
	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignLeave( I32 id, PT_CAMPAIGN_T2C_LEAVE_DATA* data )
	{
		//UIMessageBox::getInstance().showHint(L"玩家离开");
		//MessageManager::getInstance().addChatMsgForTest("玩家离开 accountId[%d]\n", data->accountId);

		Bool isMe = false;

		const AccountIdType 	accountId	= data->accountId;
		const CampaignIdType 	campaignId	= data->campaignId;
		const ClanIdType	 	clanId		= data->clanId;
		const POSITION			position	= (POSITION)data->myPosition;
		if (accountId == CPlayer::getInstance().getAccountID())
		{
			isMe = true;
		}
		
		UICampaignInfoNew::getInstance().clearMemberInfo(position);
		UICampaignInfoNew::getInstance().UIClearMemberInfoByIndex(position);

		if (true == isMe)
		{
			UICampaignFight::getInstance().clear();
			////我自己的信息
			SCampaign* myCampaign = CCampaignManager::getInstance().getPrepareCampaign(campaignId);
			CCampaignManager::getInstance().destroyCampaign(campaignId);
			CPlayer::getInstance().setMyCampaign(NULL);
			UICampaignInfoNew::getInstance().clearAllCampaignInfo();
			UICampaignInfoNew::getInstance().UIClear();
			UICampaignInfoNew::getInstance().closeGui();
		}
		else
		{
			//其他玩家离开
			SCampaign* leaveCampaign = CCampaignManager::getInstance().getPrepareCampaign(campaignId);

			ClanArmy* leaveMember = leaveCampaign->getAttackMemberInfoByClanId(clanId);
			if(NULL == leaveMember)
			{
				return;
			}
			DYNAMIC_ASSERT(NULL != leaveMember);
			//清空该玩家信息
			leaveMember->clear();
			DYNAMIC_ASSERT(true == leaveMember->empty());

			UICampaignInfoNew::getInstance().UIReFresh();
		}
#if 0
		//FUNDETECTION(__MG_FUNC__);
		const U64 regionId = data->regionId;
		const U64 campaignId = data->campaignId;
		const U64 clanId = data->clanId;

		CPlayer* myPlayer = &(CPlayer::getInstance());
		CCampaignSystemInRegion* myCapaignSystem = myPlayer->getCampaignSystem();
		Campaign* myCampaign = myCapaignSystem->getPrepareCampaign(campaignId);

		if (clanId == CPlayer::getInstance().getActiveClan()->getClanID())
		{
			//我离开
			UIManager::getInstance().closeCampaignLayout();
			myCapaignSystem->destroyPrepareCampaign(data->campaignId);
			myCapaignSystem->setMyCampaign(NULL);

			//UICampaignList::getInstance().reload();
			UIMessageBox::getInstance().showHint(L"我离开房间");
		}
		else
		{
			myCapaignSystem->leavePrepareCampaign(campaignId, clanId);

			
			//UICampaignList::getInstance().reload();
			
			//UICampaignInfo::getInstance().UIFreshWithReload();

			UIMessageBox::getInstance().showHint(L"玩家离开房间");
		}
#endif

	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignLeaveInCampaign( I32 id, PT_CAMPAIGN_F2C_LEAVE_IN_CAMPAIGN_DATA* data )
	{
		CampaignIdType campaignId = data->campaignId;
		if(campaignId == CPlayer::getInstance().getMyCampaignId())
		{
			CPlayer::getInstance().setMyCampaign(NULL);
			UICampaignFight::getInstance().clear();
		}

		SCampaign* myCampaign = CCampaignManager::getInstance().getBattleCampaign(campaignId);
		CCampaignManager::getInstance().destroyCampaign(campaignId);
		
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignDestroy( I32 id, PT_CAMPAIGN_T2C_DESTROY_DATA* data )
	{
		//MessageManager::getInstance().addChatMsgForTest("房间摧毁 Id[%d]\n", data->campaignId);

		Bool isMe = false;

		const CampaignIdType campaignId = data->campaignId;

		CCampaignManager::getInstance().destroyCampaign(campaignId);
		//UICampaignListNew::getInstance().loadCampaignList();
		
		//我自己的信息
		const SCampaign* myCampaign = CPlayer::getInstance().getMyCampaign();
		if ( (NULL != myCampaign) && (campaignId == myCampaign->getCampaignId()) )
		{
			//我的信息
			UICampaignFight::getInstance().clear();
			CPlayer::getInstance().setMyCampaign(NULL);
			UICampaignInfoNew::getInstance().clearAllCampaignInfo();
			//UICampaignInfoNew::getInstance().UIReFresh();
			UICampaignInfoNew::getInstance().UIClear();	
			UICampaignInfoNew::getInstance().closeGui();
		}
		else
		{
			UICampaignListNew::getInstance().UIReFresh();
		}
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignStartNewCampaign( I32 id, PT_CAMPAIGN_T2C_START_NEW_CAMPAIGN_DATA* data )
	{
		Bool isMe = false;

		const CampaignIdType campaignId = data->campaignId;

		SCampaign* battleCamp = CCampaignManager::getInstance().popPrepareCampaign(campaignId);
		if (NULL == battleCamp)
		{
			//DYNAMIC_ASSERT(0);
			return;
		}

		CCampaignManager::getInstance().addCampaignStart(battleCamp, 0);
		//UICampaignListNew::getInstance().loadCampaignList();

		SCampaign* myCampaign = CPlayer::getInstance().getMyCampaign();
		
		if ( (NULL != myCampaign) && (campaignId == myCampaign->getCampaignId()) )
		{
			//我自己的信息
			myCampaign->setCampaignIsStart(true);
			CRegionObject* regionObj = CRegionManager::getInstance().getRegionObjectById((REGION_OBJ_TYPE)data->regionType, data->regionId);
			regionObj->setStartCampaignTime(GetCurrentTime() + data->prepareTimeSecond*1000);

			UICampaignFight::getInstance().setIsShow(true);
			UICampaignWar::getInstance().setIsShow(true);
			UICampaignWar::getInstance().setCountDownTime(data->prepareTimeSecond);
		}
		else
		{
			//别人的战场开了
			UICampaignListNew::getInstance().UIReFresh();
		}
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignChangeCampControl( I32 id, PT_CAMPAIGN_M2C_CHANGE_CAMP_CONTROL_DATA* data )
	{
		//int kk = 0;
		//MessageManager::getInstance().addChatMsgForTest("改变军营的控制权 campId[%d], ControllerAccountId[%d]\n",
		//	data->campId, data->targetControlerAccountId);
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignChangeTroopControl( I32 id, PT_CAMPAIGN_M2C_CHANGE_TROOP_CONTROL_DATA* data )
	{
		const AccountIdType targetControllerAccountId = data->targetControlerAccountId;

		for (Int i=0; i<data->addNum; ++i)
		{
			const TroopIdType troopId = data->addMemberInfo[i].troopId;

			CTroopEntity* troopObject = CSceneManager::getInstance().getTroopEntity(troopId);
			if (NULL != troopObject)
			{
				troopObject->getDynamicData()->belongPlayerID  = targetControllerAccountId;
				CTroopSoldierEntity* troopSoldierEntity = NULL;

				for(UInt j = 0; j < troopObject->getSoldierEntitysNum(); ++j)
				{
					troopSoldierEntity = troopObject->getSoldierEntitysByIndex(j);
					if(!troopSoldierEntity)
					{
						continue;
					}

					troopSoldierEntity->getDynamicData()->belongPlayerID = targetControllerAccountId;
				}
			}

			MessageManager::getInstance().addChatMsgForTest("改变军队的控制权 troopId[%d], ControllerAccountId[%I64i]\n",
														troopId, targetControllerAccountId);
		}
		
		int kk = 0;
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignTroopControllerList( I32 id, PT_CAMPAIGN_M2C_TROOP_CONTROLLER_LIST_DATA* data )
	{
		UICampaignBarrack::getInstance().clear();
		UICampaignBarrack::getInstance().loadData(data->campId, data->troopCurControllerAccountId, data->addMemberNum, data->addMemberInfo, &(data->campInfo) );
		
		if (UICampaignBarrack::getInstance().isOpen())
		{
			UICampaignBarrack::getInstance().UIFresh();
		}
		else
		{
			UICampaignBarrack::getInstance().openGui();
		}

	}
#if 0
	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignKick( I32 id, PT_CAMPAIGN_SC_KICK_CLAN_DATA* data )
	{

		//FUNDETECTION(__MG_FUNC__);
		const U64 regionId		= data->regionId;
		const U64 campaignId	= data->campaignId;
		const U64 kickClanId	= data->kickClanId;
		const FORCE force		= (FORCE)data->force;
		const Byte position		= data->position;

		CPlayer* myPlayer = &(CPlayer::getInstance());
		CCampaignSystemInRegion* myCapaignSystem = myPlayer->getCampaignSystem();
		Campaign* myCampaign = myCapaignSystem->getPrepareCampaign(campaignId);

		if (kickClanId == CPlayer::getInstance().getActiveClan()->getClanID())
		{
			//我离开
			UIManager::getInstance().closeCampaignLayout();
			myCapaignSystem->destroyPrepareCampaign(data->campaignId);
			//myCapaignSystem->setMyCampaign(NULL);

			//UICampaignList::getInstance().reload();
			UIMessageBox::getInstance().showHint(L"我被踢出房间");
		}
		else
		{
			myCapaignSystem->kickCampaignClan(campaignId, kickClanId, force, position);


			//UICampaignList::getInstance().reload();

			//UICampaignInfo::getInstance().UIFreshWithReload();

			UIMessageBox::getInstance().showHint(L"玩家被踢出房间");
		}

	}
#endif
#if 0
	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignJoinWaiting( I32 id, PT_CAMPAIGN_SC_JOIN_WATING_DATA* data )
	{
		//FUNDETECTION(__MG_FUNC__);
	}
#endif
#if 0
	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignArmyList( I32 id, PT_CAMPAIGN_SC_ARMYLIST_DATA* data )
	{
		//FUNDETECTION(__MG_FUNC__);
	}
#endif
#if 0
	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignReady( I32 id, PT_CAMPAIGN_SC_READY_DATA* data )
	{
		//FUNDETECTION(__MG_FUNC__);
	}
#endif

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignError( I32 id, PT_CAMPAIGN_T2C_ERROR_DATA* data )
	{
		//FUNDETECTION(__MG_FUNC__);
		Char16  errorMsg[64] = L"";
		MGStrOp::sprintf(errorMsg, _countof(errorMsg), L"campaignerror%d", data->error);

		UIMessageBox::getInstance().showHint(
			L"campaignfail", L"campaignfailtitle", L"campaignfailtitle=", 
			L"campaignfail", errorMsg, errorMsg,
			this, NULL);
	}


	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::sendCampaignCreate(ClanIdType creatorClanId, RegionIdType targetRegionId, const Char16* campaignName, REGION_OBJ_TYPE targetRegionType)
	{
        ///////////////////////////////////////////////////////////////////////////

        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );


        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_CAMPAIGN;
            packet->type    = PT_CAMPAIGN_C2F_CREATE;

            // 转换逻辑包
            PT_CAMPAIGN_C2F_CREATE_DATA* sendData = (PT_CAMPAIGN_C2F_CREATE_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->creatorClanId	=creatorClanId;
                sendData->targetRegionId = targetRegionId;
				sendData->targetRegionType = targetRegionType;
                WStrnCpyS(sendData->campaignName, campaignName, MAX_CAMPAIGN_NAME);

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_CAMPAIGN_C2F_CREATE_INFO::dataSize );
            }
        }

        ///////////////////////////////////////////////////////////////////////////
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::sendCampaignChangeCampControl(const CampaignIdType	campaignId, const AccountIdType	ownerAccountId, const CampIdType campId, const AccountIdType targetControlerAccountId)
	{
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );


		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_C2F_CHANGE_CAMP_CONTROL;

			// 转换逻辑包
			PT_CAMPAIGN_C2F_CHANGE_CAMP_CONTROL_DATA* sendData = (PT_CAMPAIGN_C2F_CHANGE_CAMP_CONTROL_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->campaignId				= campaignId;
				sendData->ownerAccountId			= ownerAccountId;
				sendData->campId					= campId;
				sendData->targetControlerAccountId	= targetControlerAccountId;


				// 发送数据
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_C2F_CHANGE_CAMP_CONTROL_INFO::dataSize );
			}
		}

		///////////////////////////////////////////////////////////////////////////
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::sendCampaignTroopControllerList(const AccountIdType myAccountId, const CampaignIdType myCampainId, const CampIdType campId)
	{
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_C2F_TROOP_CONTROLLER_LIST;

			// 转换逻辑包
			PT_CAMPAIGN_C2F_TROOP_CONTROLLER_LIST_DATA* sendData = (PT_CAMPAIGN_C2F_TROOP_CONTROLLER_LIST_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->myAccountId	= myAccountId;
				sendData->campaignId	= myCampainId;
				sendData->campId		= campId;

				// 发送数据
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_C2F_TROOP_CONTROLLER_LIST_INFO::dataSize );
			}
		}
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::sendCampaignEnter(const ClanIdType myClanId, const CampaignIdType campaignId)
	{
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_CAMPAIGN;
            packet->type    = PT_CAMPAIGN_C2F_ENTER_ATTACK;

            // 转换逻辑包
            PT_CAMPAIGN_C2F_ENTER_ATTACK_DATA* sendData = (PT_CAMPAIGN_C2F_ENTER_ATTACK_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->myClanId	 = myClanId;
                sendData->campaignId = campaignId;

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_CAMPAIGN_C2F_ENTER_ATTACK_INFO::dataSize );
            }
        }
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::sendCampaignJoinDefense(const RegionIdType targetRegionId, const CampaignIdType campaignId, const ClanIdType myClanId)
	{
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_C2F_ENTER_DEFENSE;

			// 转换逻辑包
			PT_CAMPAIGN_C2F_ENTER_DEFENSE_DATA* sendData = (PT_CAMPAIGN_C2F_ENTER_DEFENSE_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->myClanId	 = myClanId;
				sendData->campaignId = campaignId;

				// 发送数据
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_C2F_ENTER_DEFENSE_INFO::dataSize );
			}
		}
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::sendCampaignEndManual(CampaignIdType campaignId)
	{
		if (campaignId <= 0)
		{
			return;
		}

		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_C2F_END_MANUAL;

			// 转换逻辑包
			PT_CAMPAIGN_C2F_END_MANUAL_DATA* sendData = (PT_CAMPAIGN_C2F_END_MANUAL_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->campaignId = campaignId;

				// 发送数据
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_C2F_END_MANUAL_INFO::dataSize );
			}
		}
	}

	void CampaignNetPacketProcesser::sendCampaignLeaveScore(PlayerCharacterIdType playerCharacterId, U32 itemGroupId)
	{
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_C2F_END_SCORE;

			// 转换逻辑包
			PT_CAMPAIGN_C2F_END_SCORE_DATA* sendData = (PT_CAMPAIGN_C2F_END_SCORE_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->playerCharacterId = playerCharacterId;
				sendData->itemGroupId = itemGroupId;

				// 发送数据
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_C2F_END_SCORE_INFO::dataSize );
			}
		}
	}
#if 0
	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::sendCampaignJoinMySelf(U64 regionId, U64 campaignId, U64 joinClanId, Byte force, Byte position)
	{
        // 获得一个发送【服务端】缓存
        NetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_CAMPAIGN;
            packet->type    = PT_CAMPAIGN_C2F_JOIN_STANDBY_MYSELF;

            // 转换逻辑包
            PT_CAMPAIGN_C2F_JOIN_STANDBY_MYSELF_DATA* sendData = (PT_CAMPAIGN_C2F_JOIN_STANDBY_MYSELF_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->regionId	= regionId;
                sendData->campaignId = campaignId;
                sendData->joinClanId = joinClanId;
                sendData->force		= force;
                sendData->position	= position;

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_CAMPAIGN_C2F_JOIN_STANDBY_MYSELF_DATA_INFO::dataSize );
            }
        }
		
	}

#endif

#if 0
	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::sendWaitingJoin(U64 regionId, U64 campaignId, U64 myClanId, U64 targetClanId)
	{
        // 获得一个发送【服务端】缓存
        NetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_CAMPAIGN;
            packet->type    = PT_CAMPAIGN_C2F_JOIN_WATING;

            // 转换逻辑包
            PT_CAMPAIGN_C2F_JOIN_WATING_DATA* sendData = (PT_CAMPAIGN_C2F_JOIN_WATING_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->regionId	= regionId;
                sendData->campaignId = campaignId;
                sendData->creatorId	= myClanId;
                sendData->joinClanId = targetClanId;

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_CAMPAIGN_C2F_JOIN_WATING_DATA_INFO::dataSize );
            }
        }
		
	}

#endif

#if 0
	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::sendCampaignReady(U64 regionId, U64 campaignId, U64 myClanId, ARMY_READY_STATE readyState)
	{
        // 获得一个发送【服务端】缓存
        NetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_CAMPAIGN;
            packet->type    = PT_CAMPAIGN_C2F_READY;

            // 转换逻辑包
            PT_CAMPAIGN_C2F_READY_DATA* sendData = (PT_CAMPAIGN_C2F_READY_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->regionId		= regionId;
                sendData->campaignId	= campaignId;
                sendData->myClanId		= myClanId;
                //sendData->targetClanId	= targetClanId;
                sendData->readyState	= (Byte)readyState;

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_CAMPAIGN_C2F_READY_DATA_INFO::dataSize );
            }
        }

	}
#endif
	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::sendCampaignReadyMySelf(CampaignIdType campaignId, ClanIdType myClanId, PlayerCharacterIdType playerCharacterId)
	{
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_CAMPAIGN;
            packet->type    = PT_CAMPAIGN_C2F_READY_MYSELF;

            // 转换逻辑包
            PT_CAMPAIGN_C2F_READY_MYSELF_DATA* sendData = (PT_CAMPAIGN_C2F_READY_MYSELF_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->campaignId		= campaignId;
                sendData->myClanId			= myClanId;
                sendData->playerCharacterId	= playerCharacterId;

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_CAMPAIGN_C2F_READY_MYSELF_INFO::dataSize );
            }
        }
			
    }

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::sendCampaignLeave(CampaignIdType campaignId, ClanIdType clanId)
	{
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_CAMPAIGN;
            packet->type    = PT_CAMPAIGN_C2F_LEAVE;

            // 转换逻辑包
            PT_CAMPAIGN_C2F_LEAVE_DATA* sendData = (PT_CAMPAIGN_C2F_LEAVE_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                //sendData->regionId	= regionId;
                sendData->campaignId = campaignId;
                sendData->clanId		= clanId;

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_CAMPAIGN_C2F_LEAVE_INFO::dataSize );
            }
        }
			
    }

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::sendCampaignLeaveInCampaign(CampaignIdType campaignId, ClanIdType clanId)
	{
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_C2F_LEAVE_IN_CAMPAIGN;

			// 转换逻辑包
			PT_CAMPAIGN_C2F_LEAVE_IN_CAMPAIGN_DATA* sendData = (PT_CAMPAIGN_C2F_LEAVE_IN_CAMPAIGN_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				//sendData->regionId	= regionId;
				sendData->campaignId = campaignId;
				sendData->clanId		= clanId;

				// 发送数据
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_C2F_LEAVE_IN_CAMPAIGN_INFO::dataSize );
			}
		}

	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::sendCampaignList()
	{
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_CAMPAIGN;
            packet->type    = PT_CAMPAIGN_C2F_CAMPAIGN_LIST;

            // 转换逻辑包
            PT_CAMPAIGN_C2F_CAMPAIGN_LIST_DATA* sendData = (PT_CAMPAIGN_C2F_CAMPAIGN_LIST_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                //sendData->targetRegionId	= regionId;

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_CAMPAIGN_C2F_CAMPAIGN_LIST_INFO::dataSize );
            }
        }	
    }

#if 0
	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::sendCampaignKickClan(const U64 regionId, const U64 campaignId, const U64 myClanId, const U64 kickClanId, const Byte force, const Byte position)
	{
        // 获得一个发送【服务端】缓存
        NetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_CAMPAIGN;
            packet->type    = PT_CAMPAIGN_C2F_KICK_CLAN;

            // 转换逻辑包
            PT_CAMPAIGN_C2F_KICK_CLAN_DATA* sendData = (PT_CAMPAIGN_C2F_KICK_CLAN_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->regionId	= regionId;
                sendData->campaignId	= campaignId;
                sendData->clanId		= myClanId;
                sendData->kickClanId = kickClanId;
                sendData->force		= force;
                sendData->position	= position;

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_CAMPAIGN_C2F_KICK_CLAN_DATA_INFO::dataSize );
            }
        }
			
    }
#endif
	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::sendCampaignStart(const CampaignIdType campaignId, const ClanIdType starterClanId )
	{
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_CAMPAIGN;
            packet->type    = PT_CAMPAIGN_C2F_START;

            // 转换逻辑包
            PT_CAMPAIGN_C2F_START_DATA* sendData = (PT_CAMPAIGN_C2F_START_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                //sendData->regionId	= regionId;
                sendData->campaignId = campaignId;
                sendData->starterClanId	= starterClanId;

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_CAMPAIGN_C2F_START_INFO::dataSize );
            }
        }
		
	}

#if 0
	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::sendCampaignArmyList(U64 regionId, U64 campaignId, U64 clanId, 
		U64 playerCharacterId, U64 troopId)
	{
        // 获得一个发送【服务端】缓存
        NetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_CAMPAIGN;
            packet->type    = PT_CAMPAIGN_CS_ARMYLIST;

            // 转换逻辑包
            PT_CAMPAIGN_CS_ARMYLIST_DATA* sendData = (PT_CAMPAIGN_CS_ARMYLIST_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->regionId	= regionId;
                sendData->campaignId = campaignId;
                sendData->myClanId	= clanId;
                sendData->playCharacterInfo.playerCharacterId = playerCharacterId;
                sendData->troopInfo.troopId = troopId;

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_CAMPAIGN_CS_ARMYLIST_DATA_INFO::dataSize );
            }
        }
		
	}
#endif

	//--------------------------------------------------------------------------
}
