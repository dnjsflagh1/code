/******************************************************************************/
#ifndef _NETTRANSPONDNETPACKET_H_
#define _NETTRANSPONDNETPACKET_H_
/******************************************************************************/
#include "CommonGameDefine.h"
#include "NetDefine.h"
/******************************************************************************/

namespace MG
{
	/******************************************************************************/
	//服务器转发类型
	/******************************************************************************/
	enum NetTranspondNetPacketType
	{
		PT_NETTRANPOND_F2S_FROM_CLIENT,         //[FrontServer To Server]客户端通过FrontServer验证后转发
		PT_NETTRANPOND_M2F_GROUP_TO_CLIENT,     //[MapServer To FrontServer]转发去客户端
		PT_NETTRANPOND_A2F_GROUP_TO_CLIENT,     //[ChatServer To FrontServer]转发去客户端

		PT_NETTRANPOND_F2T_FROM_CLIENT,			//[FrontServer To CenterServer]客户端通过FrontServer验证后转发
		PT_NETTRANPOND_T2F_GROUP_TO_CLIENT,		//[CenterServer To FrontServer]转发去客户端

		PT_NETTRANPOND_T2F_GROUP_TO_ALL_CLIENT,	//[CenterServer To FrontServer]广播给所以的客户端
	};
	
#pragma pack (push)
#pragma pack (1)

    /******************************************************************************/
    //转发客户端的数据
    /******************************************************************************/

	struct PT_NETTRANPOND_CLIENT_DATA
	{
		I32					client_net_id;
		U64					account_id;
		GameNetPacketData   data;
	};
    struct PT_NETTRANPOND_CLIENT_DATA_INFO
    {
        static const Int headSize = sizeof (PT_NETTRANPOND_CLIENT_DATA) - sizeof(GameNetPacketData) ;
        static const Int dataSize = sizeof (PT_NETTRANPOND_CLIENT_DATA);
    };

	/////////////////////////////////////////////////////////////////////

	struct ClientNetInfo
	{
		I32					client_net_id;
		U64					account_id;
	};
	struct PT_NETTRANPOND_CLIENT_GROUP_DATA
	{		
        U16                 clientNetInfoCount;
        U16                 dataSize;
		GameNetPacketData   data;
		//由于使用了两个动态结构，下面的动态的ClientNetInfo无法声明
		//需要采用偏移后来解析此结构
		// ClientNetInfo[clientData]
    };
    struct PT_NETTRANPOND_CLIENT_GROUP_DATA_INFO
    {
        static const Int headSize           = sizeof (PT_NETTRANPOND_CLIENT_GROUP_DATA) - sizeof(GameNetPacketData);
        static const Int clientNetInfoSize  = sizeof (ClientNetInfo);

        static Int dataSize( PT_NETTRANPOND_CLIENT_GROUP_DATA* data )
        {
            return  PT_NETTRANPOND_CLIENT_GROUP_DATA_INFO::headSize +
                data->dataSize +
                PT_NETTRANPOND_CLIENT_GROUP_DATA_INFO::clientNetInfoSize * data->clientNetInfoCount;
        }

    };
    
    /////////////////////////////////////////////////////////////////////

	//------------------------------------------------------
#pragma pack (pop)
}

/******************************************************************************/

#endif