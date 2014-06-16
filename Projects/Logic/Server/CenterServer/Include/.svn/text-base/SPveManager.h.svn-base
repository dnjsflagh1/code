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
#ifndef _S_PVE_MANAGER_H_
#define _S_PVE_MANAGER_H_
/******************************************************************************/

#include "CenterServerPreqs.h"
#include "SPveRoom.h"

/******************************************************************************/

/******************************************************************************/
namespace MG
{
	/**********************************************************************/
	class SPveManager
	{
	public:
		SPveManager();
		~SPveManager();
		SINGLETON_INSTANCE(SPveManager);

		std::map<AccountIdType, SPveRoom*>*			getPveRoomList();
		
		SPveRoom* createPveRoom(AccountIdType accountId, const Char16* pveRoomName);
		SPveRoom* getPveRoom(AccountIdType accountId);
		SPveRoom* popPveRoom(AccountIdType accountId);
		void	  delPveRoom(AccountIdType accountId);
		

	private:
		SimpleMapDataSetManager<AccountIdType, SPveRoom>		mPveRoomManager;
		std::map<AccountIdType, SPveRoom*>						mPveStartList;			//已进入副本的 房间列表
	};
}

#endif	//_S_PVE_MANAGER_H_