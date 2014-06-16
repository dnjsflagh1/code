//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\CenterServer\Include\SCampaignManager.h
//        Author: yuanlinhu
//          Date: 2012-5-14
//          Time: 15:24
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-5-14      add
//////////////////////////////////////////////////////////////


/******************************************************************************/
#ifndef _S_CAMPAIGN_MANAGER_H_
#define _S_CAMPAIGN_MANAGER_H_
/******************************************************************************/

#include "CenterServerPreqs.h"
#include "CampaignManager.h"

/******************************************************************************/

/******************************************************************************/
namespace MG
{
	/**********************************************************************/
	class SCampaignManager : public CampaignManager
	{
	public:
		SCampaignManager();
		~SCampaignManager();
		SINGLETON_INSTANCE(SCampaignManager);

		virtual void	sendCampaignEndPacket(SCampaign* campaign, const FORCE winnerForce);
		virtual void	sendCampaignDestroyPacket(SCampaign* campaign, const FORCE winnerForce);

		SCampaign*		getCampaignByClanId(const ClanIdType clanId);
	};
}

#endif	//_S_CAMPAIGN_MANAGER_H_