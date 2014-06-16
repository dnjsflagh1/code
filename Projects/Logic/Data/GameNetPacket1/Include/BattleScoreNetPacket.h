/******************************************************************************/
#ifndef _BATTLESCORE_NETPACKET_H_
#define _BATTLESCORE_NETPACKET_H_
/******************************************************************************/
#include "CommonGameDefine.h"
#include "NetDefine.h"
#include "GameNetPacket.h"
/******************************************************************************/

namespace MG
{
	/******************************************************************************/
	//玩家角色包类型
	/******************************************************************************/
	enum BattleScoreNetPacketType
	{
		PT_BATTLESCORE_UNKNOWN = 0,

		PT_BATTLESCORE_M2C_NOTIFY,		// [MapServer -> Client]	//公告

	};

#pragma pack (push)
#pragma pack (1)

	/**********************************************************************
    //@名字:        PT_BATTLESCORE_M2C_NOTIFY
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
    struct PT_BATTLESCORE_M2C_NOTIFY_DATA
    {
		Int		rankId;
	};
	struct PT_BATTLESCORE_M2C_NOTIFY_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_BATTLESCORE_M2C_NOTIFY_DATA);
	};
	class PT_BATTLESCORE_M2C_NOTIFY_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_BATTLESCORE_M2C_NOTIFY_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_BATTLE_SCORE;
            mType                               =   PT_BATTLESCORE_M2C_NOTIFY;
            mBaseDataSize                       =   PT_BATTLESCORE_M2C_NOTIFY_DATA_INFO::dataSize ;

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

	//**********************************************************************

	//struct PT_BATTLESCORE_M2C_NOTIFY_DATA
	//{
	//	Int		rankId;
	//};

	//struct PT_BATTLESCORE_M2C_NOTIFY_DATA_INFO
	//{
	//	static const Int dataSize = sizeof (PT_BATTLESCORE_M2C_NOTIFY_DATA);
	//};
#pragma pack (pop)
}

/******************************************************************************/

#endif	//_BATTLESCORE_NETPACKET_H_