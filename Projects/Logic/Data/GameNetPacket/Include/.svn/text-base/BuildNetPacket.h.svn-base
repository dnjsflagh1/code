/******************************************************************************/
#ifndef _BATTLEBUILDNETPACKET_H_
#define _BATTLEBUILDNETPACKET_H_
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
    enum BuildNetPacket
    {
        PT_BUILD_UNKNOW = 0,

		PT_BUILD_M2C_CHANGE_BELONG_PLAYER,			//建筑物的所属玩家ID

    };

#pragma pack (push)
#pragma pack (1)

    ///////////////////////////////////////////////////////////////////////
    
	/**********************************************************************
    //@名字:        PT_BUILD_M2C_CHANGE_BELONG_PLAYER
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct NetBuildChangeBelongPlayerInfo
	{
		BuildingIdType	buildingId;
	};

    struct PT_BUILD_M2C_CHANGE_BELONG_PLAYER_DATA
    {
		AccountIdType					targetBelongAccountId;
		Int								addNum;
		NetBuildChangeBelongPlayerInfo	addMemberInfo[1];
	};

	struct PT_BUILD_M2C_CHANGE_BELONG_PLAYER_INFO
	{
		static Int const     netAddMemberInfoSize = sizeof (NetBuildChangeBelongPlayerInfo);
		static Int const     headSize = sizeof (PT_BUILD_M2C_CHANGE_BELONG_PLAYER_DATA) - sizeof(NetBuildChangeBelongPlayerInfo);
		static Int			 dataSize(PT_BUILD_M2C_CHANGE_BELONG_PLAYER_DATA* data)
		{ 
			return PT_BUILD_M2C_CHANGE_BELONG_PLAYER_INFO::headSize + PT_BUILD_M2C_CHANGE_BELONG_PLAYER_INFO::netAddMemberInfoSize * data->addNum;
		};
	};

	class PT_BUILD_M2C_CHANGE_BELONG_PLAYER_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_BUILD_M2C_CHANGE_BELONG_PLAYER_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_BUILDING;
            mType                               =   PT_BUILD_M2C_CHANGE_BELONG_PLAYER;
            //mBaseDataSize                       =   PT_BUILD_M2C_CHANGE_BELONG_PLAYER_INFO::dataSize;

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

		virtual Bool checkDataValid( GameNetPacketData* data, I32 dataLen )
		{
			if ( data->channel != mChannel )
				return false;
			if ( data->type != mType )
				return false;
			if ( dataLen != PT_BUILD_M2C_CHANGE_BELONG_PLAYER_INFO::dataSize((PT_BUILD_M2C_CHANGE_BELONG_PLAYER_DATA*)data) )
				return false;
			return true;
		}
    };
    //**********************************************************************
	//
	//struct PT_BUILD_M2C_CHANGE_BELONG_PLAYER_DATA
	//{
	//	
	//};
	//struct PT_BUILD_M2C_CHANGE_BELONG_PLAYER_DATA_INFO
	//{
	//	static Int const     netAddMemberInfoSize = sizeof (NetBuildChangeBelongPlayerInfo);
	//	static Int const     headSize = sizeof (PT_BUILD_M2C_CHANGE_BELONG_PLAYER_DATA) - sizeof(NetBuildChangeBelongPlayerInfo);
	//	static Int			 dataSize(PT_BUILD_M2C_CHANGE_BELONG_PLAYER_DATA* data)
	//	{ 
	//		return PT_BUILD_M2C_CHANGE_BELONG_PLAYER_DATA_INFO::headSize + PT_BUILD_M2C_CHANGE_BELONG_PLAYER_DATA_INFO::netAddMemberInfoSize * data->addNum;
	//	};
	//};

    //**********************************************************************

#pragma pack (pop)
}

/******************************************************************************/

#endif