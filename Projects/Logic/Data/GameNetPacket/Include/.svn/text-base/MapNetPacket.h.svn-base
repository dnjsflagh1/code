/******************************************************************************/
#ifndef _MAPNETPACKET_H_
#define _MAPNETPACKET_H_
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
    enum MapNetPacket
    {
        PT_MAP_UNKNOW = 0,

        PT_MAP_M2C_BASE_INFO,		        //分块地图基础数据

    };

#pragma pack (push)
#pragma pack (1)

	/**********************************************************************
    //@名字:        PT_MAP_M2C_BASE_INFO
    //@功能:        分块地图基础数据 发送给 客户端
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_MAP_M2C_BASE_INFO_DATA
	{
		Int numTest;
	};
	struct PT_MAP_M2C_BASE_INFO_INFO
	{
		static const Int dataSize = sizeof (PT_MAP_M2C_BASE_INFO_DATA);
	};
	class PT_MAP_M2C_BASE_INFO_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_MAP_M2C_BASE_INFO_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_MAP;
            mType                               =   PT_MAP_M2C_BASE_INFO;
            mBaseDataSize                       =   PT_MAP_M2C_BASE_INFO_INFO::dataSize ;

            mLevel                              =   GPL_LOGIC;
            mFlow                               =   GPFL_S2C;

            mReplaceLevelInSendQueue            =   GPRL_NONE;
            mReplaceIndexInSendQueue            =   0;
            mReplaceLevelInRecvQueue            =   GPRL_NONE;
            mReplaceIndexInRecvQueue            =   0;

            mDiscardLevelInSendQueue            =   GPDL_NORMAL;
            mDiscardLevelInRecvQueue            =   GPDL_NORMAL;

            mBlockWaitLevelInSendQueue          =   GPWL_NONE;
            mBlockWaitMaxTimeInSendQueue        =   0;
            mBlockWaitReplyChannelInSendQueue   =   0;
            mBlockWaitReplyTypeInSendQueue      =   0;

            mBlockWaitLevelInRecvQueue          =   GPWL_NONE;
            mBlockWaitMaxTimeInRecvQueue        =   0;
            mBlockWaitReplyChannelInRecvQueue   =   0;
            mBlockWaitReplyTypeInRecvQueue      =   0;
        }
    };

#pragma pack (pop)
}

/******************************************************************************/

#endif