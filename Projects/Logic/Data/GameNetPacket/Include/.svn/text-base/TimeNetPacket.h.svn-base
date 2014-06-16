/******************************************************************************/
#ifndef _TIMENETPACKET_H_
#define _TIMENETPACKET_H_
/******************************************************************************/
#include "CommonGameDefine.h"
#include "NetDefine.h"
#include "WorldCoreDefine.h"
/******************************************************************************/

namespace MG
{
	/******************************************************************************/
	//聊天相关类型
	/******************************************************************************/
	enum TimeNetPacket
	{
		PT_TIME_E2S_SYNC,	// CenterServer同步时间到其他服务器
		PT_TIME_S2C_SYNC,	// 服务器同步时间到客户端
		PT_TIME_S2E_GET		// 普通服务器向Center索要时间
	};

    //////////////////////////////////////////////////////////////////////////////////

	struct PT_TIME_E2S_SYNC_DATA
	{
		U64 currTime;		//当前时间
	};

    struct PT_TIME_E2S_SYNC_DATA_INFO
    {
          static const Int  dataSize = sizeof (PT_TIME_E2S_SYNC_DATA);
    };

    //////////////////////////////////////////////////////////////////////////////////
	struct PT_TIME_S2C_SYNC_DATA
	{
		U64 currTime;		//当前时间
	};

    struct PT_TIME_S2C_SYNC_DATA_INFO
    {

		static const Int dataSize = sizeof (PT_TIME_S2C_SYNC_DATA);

    };
	//////////////////////////////////////////////////////////////////////////////////
	struct PT_TIME_S2E_GETTIME_DATA
	{
	};

	struct PT_TIME_S2E_GETTIME_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_TIME_S2E_GETTIME_DATA);
	};
}
#endif