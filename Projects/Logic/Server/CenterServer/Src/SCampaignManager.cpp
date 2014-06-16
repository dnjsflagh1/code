/******************************************************************************/

#include "stdafx.h"
#include "SCampaignManager.h"
#include "SCampaignNetPacketProcesser.h"
#include "PrintDialog.h"

/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------------
	SCampaignManager::SCampaignManager()
	{

	}

	//-----------------------------------------------------------------------------
	SCampaignManager::~SCampaignManager()
	{

	}

	//-----------------------------------------------------------------------------
	SCampaign* SCampaignManager::getCampaignByClanId(const ClanIdType clanId)
	{
		//��׼���С����б��в���
		{
			std::map<ClanIdType, SCampaign*>* prepareCampaignList = getPrepareCampaignList();

			for (std::map<ClanIdType, SCampaign*>::iterator iter = prepareCampaignList->begin(); iter != prepareCampaignList->end(); ++iter)
			{
				ClanArmy* clanArmy = iter->second->getClanArmyByClanId(clanId);
				if (NULL != clanArmy && false == clanArmy->empty())
				{
					return iter->second;
				}
			}
		}
		
		//����ʼս�������б��в���
		{
			std::map<ClanIdType, SCampaign*>* battleCampaignList = getOnBattleCampaignList();

			for (std::map<ClanIdType, SCampaign*>::iterator iter = battleCampaignList->begin(); iter != battleCampaignList->end(); ++iter)
			{
				ClanArmy* clanArmy = iter->second->getClanArmyByClanId(clanId);
				if (NULL != clanArmy && false == clanArmy->empty())
				{
					return iter->second;
				}
			}
		}

		//�����㡿�б��в���
		{
			std::map<ClanIdType, SCampaign*>* battleCampaignList = getEndCampaignList();

			for (std::map<ClanIdType, SCampaign*>::iterator iter = battleCampaignList->begin(); iter != battleCampaignList->end(); ++iter)
			{
				ClanArmy* clanArmy = iter->second->getClanArmyByClanId(clanId);
				if (NULL != clanArmy && false == clanArmy->empty())
				{
					return iter->second;
				}
			}
		}
		
		return NULL;
	}

	//-----------------------------------------------------------------------------
	void SCampaignManager::sendCampaignEndPacket(SCampaign* campaign, const FORCE winnerForce)
	{
		DYNAMIC_ASSERT(winnerForce == FORCE_ATTACK || winnerForce == FORCE_DEFENSE);
		campaign->setWinnerForce(winnerForce);

		//����ս������
		//SCampaignNetPacketProcesser::getInstance().sendCampaignEndToClient(campaign);
		SCampaignNetPacketProcesser::getInstance().sendCampaignEndToFrontServer(campaign);
	}

	//-----------------------------------------------------------------------------
	void SCampaignManager::sendCampaignDestroyPacket(SCampaign* campaign, const FORCE winnerForce)
	{
		DYNAMIC_ASSERT(winnerForce == FORCE_ATTACK || winnerForce == FORCE_DEFENSE);
		campaign->setWinnerForce(winnerForce);

		std::map<POSITION, ClanArmy*>* hostList			 = campaign->getAttackHostList();
		std::map<POSITION, ClanArmy*>* attackMemberList  = campaign->getAttackMemberList();
		std::map<POSITION, ClanArmy*>* defenseMemberList = campaign->getDefenseMemberList();
		DYNAMIC_ASSERT(hostList->size() == 1);		//������һ������

		//��ת��ͼ
		RegionIdType mainRegionId = campaign->getCampaignTargetRegionId();
		SCampaignNetPacketProcesser::getInstance().sendCampaignMemberJumpRegionToFrontServer(hostList, mainRegionId, 0, JUMP_NORMAL, 0);
		SCampaignNetPacketProcesser::getInstance().sendCampaignMemberJumpRegionToFrontServer(attackMemberList, mainRegionId, 0, JUMP_NORMAL, 0);
		SCampaignNetPacketProcesser::getInstance().sendCampaignMemberJumpRegionToFrontServer(defenseMemberList, mainRegionId, 0, JUMP_NORMAL, 0);
	}
	//-----------------------------------------------------------------------------
}
