//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\MapServer\Include\SPlayerNew.h
//        Author: yuanlinhu
//          Date: 2012-3-13
//          Time: 15:44
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-13      add
//////////////////////////////////////////////////////////////


/******************************************************************************/
#ifndef _S_PLAYER_IDENTIFY_INFO_H_
#define _S_PLAYER_IDENTIFY_INFO_H_
/******************************************************************************/

#include "MapServerPreqs.h"

/******************************************************************************/

namespace MG
{
	/******************************************************************************/
	//客户端玩家对象管理
	//主要用于绑定地图对象和客户端玩家之间的关系，客户端玩家和FrontServer之间的关系
	//用于同步等相关操作
	/******************************************************************************/

	// SPlayer 标识数据
	struct SPlayerIdentifyInfo
	{
		// 帐号
		AccountIdType accountId;
		// 对应FrontServer的编号
		NetIdType frontServerId;
		// 对应FrontServer的ClientNetID
		NetIdType clientNetIdInFrontServer;
		// 家族id
		ClanIdType clanId;

		void clear()
		{
			accountId = 0;
			frontServerId = -1;
			clientNetIdInFrontServer = -1;
			clanId = 0;
		}
	};

}

#endif	//namespace MG