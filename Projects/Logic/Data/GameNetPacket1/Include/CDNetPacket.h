/******************************************************************************/
#ifndef _CD_NETPACKET_H_
#define _CD_NETPACKET_H_
/******************************************************************************/
#include "CommonGameDefine.h"
#include "NetDefine.h"
#include "GameNetPacket.h"
/******************************************************************************/

namespace MG
{
	/**********************************************************************
	//@负责人:      徐开超
	//@协助人:      ???
	**********************************************************************/

    /******************************************************************************/
    //玩家包类型
    /******************************************************************************/
    enum CDNetPacketType
    {
        PT_CD_UNKNOWN = 0,

        PT_CD_F2C_CDLIST,											//发送氏族CD，氏族下角色的所有CD（从DB中获得）
        PT_CD_M2C_CITY,												//发送城市CD

    };

    /******************************************************************************/


#pragma pack (push)
#pragma pack (1)

    //////////////////////////////////////////////////////////////////////////////

    ///数据包声明
    struct  CDNetData
    {
        U32 cdId;
        U32 cdLiveTime;
		U32 cdTotalTime;
    };
    struct CDNetData_INFO
    {
        static const Int dataSize = sizeof(CDNetData);
    };
    //------------------------------------------------------------------------------------------
	//**********************************************************************
	//@名字:        PT_CD_F2C_CDLIST
	//@功能:        frontServerr向客户端发送buff列表
	//@备注:        登陆时发送从DB读取的CD数据
	//**********************************************************************/
    struct PT_CD_F2C_CDLIST_DATA
    {
        Byte            masterType;			//角色类型
        IdType          masterID;			//角色ID（一般指武将）
        U32             cdNum;				//CD的数量
        CDNetData       cddata[1];			//CD信息
    };
    struct PT_CD_F2C_CDLIST_DATA_INFO
    {
        static const Int dataSize = sizeof(PT_CD_F2C_CDLIST_DATA) - CDNetData_INFO::dataSize;
    };
	
	class PT_CD_F2C_CDLIST_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_CD_F2C_CDLIST_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_CD;
			mType                               =   PT_CD_F2C_CDLIST;
			mBaseDataSize                       =   PT_CD_F2C_CDLIST_DATA_INFO::dataSize ;

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
    //------------------------------------------------------------------------------------------
    
    //////////////////////////////////////////////////////////////////////////////
#pragma pack (pop)
}

/******************************************************************************/
#endif