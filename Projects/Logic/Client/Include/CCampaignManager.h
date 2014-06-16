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
#ifndef _C_CAMPAIGN_MANAGER_H_
#define _C_CAMPAIGN_MANAGER_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "CampaignManager.h"

/******************************************************************************/

/******************************************************************************/
namespace MG
{
	/**********************************************************************/
	class CCampaignManager : public CampaignManager
	{
	public:
		CCampaignManager();
		~CCampaignManager();
		SINGLETON_INSTANCE(CCampaignManager);
	};
}

#endif	//_C_CAMPAIGN_MANAGER_H_