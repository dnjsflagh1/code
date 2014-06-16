/******************************************************************************/
#ifndef _PLACENETPACKET_H_
#define _PLACENETPACKET_H_
/******************************************************************************/
#include "CommonGameDefine.h"
#include "NetDefine.h"
#include "GameNetPacket.h"
/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //据点数据包想关类型
    /******************************************************************************/
    enum PlaceNetPacket
    {
        PT_PLACE_UNKNOW = 0,

        PT_PLACE_S2C_BASE_INFO,		        // 据点基础数据

		PT_PLACE_C2F_CLICED_INFO,			// 客户端请求点击据点 
		PT_PLACE_F2M_CLICED_INFO,			// FrontServer转发客户端请求点击据点到MapServer
		PT_PLACE_M2C_CLICED_INFO,			// MapServer返回据点数据给客户端

    };

#pragma pack (push)
#pragma pack (1)
	//**********************************************************************
	struct PT_PLACE_S2C_BASE_INFO_DATA
	{
		Int nNum;
	};
    struct PT_PLACE_S2C_BASE_INFO_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_PLACE_S2C_BASE_INFO_DATA);
    };
	//**********************************************************************
	struct PT_PLACE_C2F_CLICED_INFO_DATA
	{
		IdType			placeId;		// 据点ID
		NetVec2Data placePos;		// 据点位置
		NetVec2Data placeDir;		// 据点方向
	};
    struct PT_PLACE_C2F_CLICED_INFO_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_PLACE_C2F_CLICED_INFO_DATA);
    };
	//**********************************************************************
	struct PT_PLACE_F2M_CLICED_INFO_DATA
	{
		IdType			accountId;		// 账号ID
		IdType			placeId;		// 据点ID
		NetVec2Data placePos;		// 据点位置
		NetVec2Data placeDir;		// 据点方向

	};
    struct PT_PLACE_F2M_CLICED_INFO_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_PLACE_F2M_CLICED_INFO_DATA);
    };
	//**********************************************************************
	struct PT_PLACE_M2C_CLICED_INFO_DATA
	{
		IdType			placeId;		//据点ID
	};
    struct PT_PLACE_M2C_CLICED_INFO_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_PLACE_M2C_CLICED_INFO_DATA);
    };

#pragma pack (pop)
}

/******************************************************************************/

#endif