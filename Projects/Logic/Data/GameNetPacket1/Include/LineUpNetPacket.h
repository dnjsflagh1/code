/******************************************************************************/
#ifndef _LINEUPNETPACKET_H_
#define _LINEUPNETPACKET_H_
/******************************************************************************/

#include "CommonGameDefine.h"
#include "NetDefine.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //游戏排队包类型
    /******************************************************************************/
    enum LineUpNetPacketType
    {
		PT_LINE_UP_L2C,
		PT_LINE_UP_C2L_CANCLE_CMD,
		PT_LINE_UP_L2C_CANCLE_CMD_RELULT,

		PT_LINE_UP_F2C,
		PT_LINE_UP_C2F_CANCLE_CMD,
		PT_LINE_UP_F2C_CANCLE_CMD_RELULT,
		
    };
    
	/******************************************************************************/
	//游戏排队信息类型
	/******************************************************************************/
    enum LINE_UP_TYPE
	{
        line_up_busy_lc_account_login = 1,				//连接Login排队
		line_up_busy_lc_server_full,					//服务器人数已满
		line_up_busy_fc_account_login,					//帐号登录FrontServer排队
		line_up_busy_fc_create_clan,					//创建家族排队
		line_up_busy_fc_del_clan,						//删除家族排队
		line_up_busy_fc_create_character,				//创建角色排队
		line_up_busy_fc_join_game						//进入游戏地图排队
	};


#pragma pack (push)
#pragma pack (1)

	//**********************************************************************
	//@名字:        PT_LINE_UP_L2C
	//@功能:        Loginserver返回登陆队列信息给客户端
	//@备注:        ???
	//**********************************************************************/
	struct  PT_LINE_UP_L2C_DATA
	{   
		Byte type;
		I32	waitCount;
	};
	struct PT_LINE_UP_L2C_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LINE_UP_L2C_DATA);
	};
	class PT_LINE_UP_L2C_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LINE_UP_L2C_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LINE_UP;
			mType                               =   PT_LINE_UP_L2C;
			mBaseDataSize                       =   PT_LINE_UP_L2C_DATA_INFO::dataSize ;

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
	//@名字:       PT_LINE_UP_C2L_CANCLE_CMD
	//@功能:       Client向LoginServer请求取消排队命令
	//@备注:        ???
	//**********************************************************************/
	struct  PT_LINE_UP_C2L_CANCLE_CMD_DATA
	{   
		Byte type;
	};
	struct PT_LINE_UP_C2L_CANCLE_CMD_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LINE_UP_C2L_CANCLE_CMD_DATA);
	};
	class PT_LINE_UP_C2L_CANCLE_CMD_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LINE_UP_C2L_CANCLE_CMD_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LINE_UP;
			mType                               =   PT_LINE_UP_C2L_CANCLE_CMD;
			mBaseDataSize                       =   PT_LINE_UP_C2L_CANCLE_CMD_DATA_INFO::dataSize ;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_C2S;

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
	//@名字:       PT_LINE_UP_L2C_CANCLE_CMD_RELULT
	//@功能:       LoginServer返回取消排队命令结果给Client
	//@备注:        ???
	//**********************************************************************/
	struct  PT_LINE_UP_L2C_CANCLE_CMD_RELULT_DATA
	{   
		Byte type;
		Byte result;
	};
	struct PT_LINE_UP_L2C_CANCLE_CMD_RELULT_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LINE_UP_L2C_CANCLE_CMD_RELULT_DATA);
	};
	class PT_LINE_UP_L2C_CANCLE_CMD_RELULT_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LINE_UP_L2C_CANCLE_CMD_RELULT_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LINE_UP;
			mType                               =   PT_LINE_UP_L2C_CANCLE_CMD_RELULT;
			mBaseDataSize                       =	PT_LINE_UP_L2C_CANCLE_CMD_RELULT_DATA_INFO::dataSize ;

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
	//@名字:       PT_LINE_UP_F2C
	//@功能:       FrontServer返回登陆队列信息给Client
	//@备注:        ???
	//**********************************************************************/
	struct  PT_LINE_UP_F2C_DATA
	{   
		Byte type;
		I32 waitCount;
	};
	struct PT_LINE_UP_F2C_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LINE_UP_F2C_DATA);
	};
	class PT_LINE_UP_F2C_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LINE_UP_F2C_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LINE_UP;
			mType                               =   PT_LINE_UP_F2C;
			mBaseDataSize                       =	PT_LINE_UP_F2C_DATA_INFO::dataSize ;

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
	//@名字:       PT_LINE_UP_C2F_CANCLE_CMD
	//@功能:       Client向FrontServer请求取消排队命令
	//@备注:        ???
	//**********************************************************************/
	struct  PT_LINE_UP_C2F_CANCLE_CMD_DATA
	{   
		Byte type;
	};
	struct PT_LINE_UP_C2F_CANCLE_CMD_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LINE_UP_C2F_CANCLE_CMD_DATA);
	};
	class PT_LINE_UP_C2F_CANCLE_CMD_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LINE_UP_C2F_CANCLE_CMD_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LINE_UP;
			mType                               =   PT_LINE_UP_C2F_CANCLE_CMD;
			mBaseDataSize                       =	PT_LINE_UP_C2F_CANCLE_CMD_DATA_INFO::dataSize ;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_C2S;

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
	//@名字:      PT_LINE_UP_F2C_CANCLE_CMD_RELULT
	//@功能:      FrontServer返回取消排队结果给Client
	//@备注:      ???
	//**********************************************************************/
	struct  PT_LINE_UP_F2C_CANCLE_CMD_RELULT_DATA
	{   
		Byte type;
		Byte result;
	};
	struct PT_LINE_UP_F2C_CANCLE_CMD_RELULT_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LINE_UP_F2C_CANCLE_CMD_RELULT_DATA);
	};
	class PT_LINE_UP_F2C_CANCLE_CMD_RELULT_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LINE_UP_F2C_CANCLE_CMD_RELULT_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LINE_UP;
			mType                               =   PT_LINE_UP_F2C_CANCLE_CMD_RELULT;
			mBaseDataSize                       =	PT_LINE_UP_F2C_CANCLE_CMD_RELULT_DATA_INFO::dataSize ;

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
#pragma pack (pop)

}

/******************************************************************************/

#endif