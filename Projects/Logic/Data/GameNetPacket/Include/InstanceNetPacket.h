
/******************************************************************************/

#ifndef _INSTANCE_NET_PACKET_H_
#define _INSTANCE_NET_PACKET_H_

/******************************************************************************/

#include "CommonGameDefine.h"
#include "NetDefine.h"
#include "GameNetPacket.h"

/******************************************************************************/

#pragma pack (push)
#pragma pack (1)

/******************************************************************************/
namespace MG
{
#if 0
	/******************************************************************************/
	//据点数据包想关类型
	/******************************************************************************/
	enum InstanceNetPacket
	{
		PT_INSTANCE_UNKNOW = 0,

		PT_INSTANCE_C2M_TIRO_LIST,		//新手副本列表
		PT_INSTANCE_M2C_TIRO_LIST,		
	};
	
	
	//**********************************************************************
	struct PT_INSTANCE_C2M_TIRO_LIST_DATA
	{
		RegionIdType	regionId;
		Byte			retionType;
	};

	struct PT_INSTANCE_C2M_TIRO_LIST_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_INSTANCE_C2M_TIRO_LIST_DATA);
	};

	//**********************************************************************
	struct NetAddTiroInfo
	{
		InstanceIdType		instanceId;
		Int					curPlayerNum;		//当前人数
		Int					maxPlayerNum;		//最大人数
	};

	struct PT_INSTANCE_M2C_TIRO_LIST_DATA
	{
		RegionIdType		regionId;
		REGION_OBJ_TYPE		regionType;
		Int					addTiroNum;
		NetAddTiroInfo		tiroInfo[1];
	};

	struct PT_INSTANCE_M2C_TIRO_LIST_DATA_INFO
	{
		static Int  const headSize        = sizeof (PT_INSTANCE_M2C_TIRO_LIST_DATA) - sizeof( NetAddTiroInfo ); 
		static Int  const netAddTiroInfoSize  = sizeof (NetAddTiroInfo);

		static Int  dataSize(PT_INSTANCE_M2C_TIRO_LIST_DATA* data)
		{ 
			return headSize + netAddTiroInfoSize * data->addTiroNum;
		};
	};
#endif
}

#pragma pack (pop)

/******************************************************************************/

#endif	//_INSTANCE_NET_PACKET_H_