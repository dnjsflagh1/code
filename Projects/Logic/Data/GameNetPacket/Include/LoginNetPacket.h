/******************************************************************************/
#ifndef _LOGINNETPACKET_H_
#define _LOGINNETPACKET_H_
/******************************************************************************/

#include "CommonGameDefine.h"
#include "NetDefine.h"

/******************************************************************************/

namespace MG
{
	/**********************************************************************
	//@负责人:      王育安
	//@协助人:      ???
	**********************************************************************/

    /******************************************************************************/
    //游戏帐号包类型
    /******************************************************************************/
    enum LoginNetPacketType
    {
		PT_LOGIN_UNKNOW = 0,
		PT_LOGIN_S2S_SERVER_LOGIN,					//服务器之间的登入请求
		
		//  此协议已经废弃（需确认，暂时注释）
		//PT_F2M_MAPLIST,								

		PT_LOGIN_F2L_FRONT_SERVER_LOGIN,			//FrontServer 登入 LoginServer
		PT_LOGIN_L2F_LOGIN_FRONT_SERVER_RESULT,		//FrontServer 登入 LoginServer 返回结果
        PT_LOGIN_L2F_LOGIN_FRONT_KICKOUT_CLIENT,    //重复登录 LoginServer通知FrontServer 踢出玩家

        PT_LOGIN_C2L_ACC_LOGIN,						//客户端账号登陆LoginServer		
		PT_LOGIN_L2C_ACC_LOGIN_FAIL,				//客户端账号登入失败消息

		PT_LOGIN_L2C_ACC_LOGIN_SUCCESS,				//客户端账号登入成功消息

		PT_LOGIN_C2F_ACC_LOGIN,						//客户端账号登入FrontServer
        PT_LOGIN_C2F_ACC_LOGOUT,					//客户端账号登入FrontServer
		PT_LOGIN_F2C_ACC_LOGIN_RESULT,				//客户端账号登入FrontServer返回结果

		PT_LOGIN_F2L_CLIENT_LOGIN,					//客户端账号登入通知和验证
		PT_LOGIN_L2F_CLIENT_CHECKED,				//客户端账号登入验证结果
		PT_LOGIN_F2L_CLIENT_LOGOUT,					//客户端账号登出

		//氏族创建界面
        PT_LOGIN_F2C_OPEN_CREATECLANUI,				//[FrontServer -> Client] 通知客户端打开创建氏族的界面
		PT_LOGIN_C2F_CREATE_CLAN,					//[Client -> FrontServer] 请求服务器创建氏族。
		PT_LOGIN_F2C_CREATE_CLAN_RESULT,			//[FrontServer -> Client] 返回服务器创建氏族的结果
		PT_LOGIN_F2C_CLAN_DATA,						//[FrontServer -> Client] 发送氏族数据

		//角色创建界面
		PT_LOGIN_F2C_OPENCRETEGENREALUI,			//[FrontServer -> Client] 服务器结果返回，如果成功就是进入游戏。
		PT_LOGIN_C2F_CREATE_GENERAL,				//[Client -> FrontServer] 客户端请求创建武将。
		PT_LOGIN_F2C_CREATE_GENERAL_RESULT,			//[FrontServer -> Client] 客户端返回创建武将结果。

		//氏族管理界面
		PT_LOGIN_F2C_OPEN_CLANCONTROLUI,			//[FrontServer -> Client] 通知客户端打开氏族管理界面
		PT_LOGIN_C2F_DELETE_CLAN,					//[Client -> FrontServer] 请求服务器删除氏族。
		PT_LOGIN_F2C_DELETE_CLAN_RESULT,			//[FrontServer -> Client] 返回服务器删除氏族的结果
        PT_LOGIN_C2F_JOINGAME,						//[Client -> FrontServer] 客户端请求登录game

		PT_LOGIN_F2A_JOINGAME,						//[FrontServer -> ChatServer]前台服务器通知聊天服务器客户端进入游戏
		PT_LOGIN_F2A_EXITGAME,						//[FrontServer -> ChatServer]前台服务器通知聊天服务器客户端离开游戏
		PT_LOGIN_F2A_CLIENTLIST_INGAME,				//[FrontServer -> ChatServer]前台服务登录聊天服务器时在游戏中的客户端对象

		// 健壮性检测
		PT_LOGIN_L2F_CHECK_INFRONTSERVER,
		PT_LOGIN_F2L_CHECK_INFRONTSERVER_RESULT,
		PT_LOGIN_M2F_CHECK_INFRONTSERVER,
		PT_LOGIN_F2M_CHECK_INFRONTSERVER_RESULT,

		// 服务器版本检测错误信息反馈
		PT_SERVER_S2S_LOGIN_VERSION_ERROR,
		// 客户端版本检测错误信息反馈
		PT_SERVER_S2C_LOGIN_VERSION_ERROR

    };
    
	/******************************************************************************/
	//登录排队类型
	/******************************************************************************/
#pragma pack (push)
#pragma pack (1)

    //**********************************************************************
    //服务器之间登入
	//**********************************************************************
	//@名字:        PT_LOGIN_S2S_SERVER_LOGIN
	//@功能:        服务器之间的登录
	//@备注:        ???
	//**********************************************************************/
    struct PT_LOGIN_S2S_LOGIN_DATA
    {
        U8		serverType;
        U32		code; 
		U32		serverId;
		U64		serverUniqueFlag;
		Char8	serverVersion[MAX_VERSION_NUM_LEN];
		Char16	name[MAX_SERVER_NAME_LEN];
    };

    struct PT_LOGIN_S2S_LOGIN_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_S2S_LOGIN_DATA);
    };
	class PT_LOGIN_S2S_LOGIN_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_S2S_LOGIN_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_S2S_SERVER_LOGIN;
			mBaseDataSize                       =   PT_LOGIN_S2S_LOGIN_DATA_INFO::dataSize;

			mLevel                              =   GPL_SYS;
			mFlow                               =   GPFL_S2S;

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
	//  此协议已经废弃（需确认，暂时注释）
	/*struct NetMapServer
	{
		Char	ip[MG_NET_MAX_IP_LEN];
		I32		port;
	};
	struct PT_F2M_MAPLIST_DATA
	{
		Int				num;
		NetMapServer	mapInfo[1];
	};
    struct PT_F2M_MAPLIST_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_F2M_MAPLIST_DATA);
    };*/
	//**********************************************************************
    //客户端帐号登入
	//**********************************************************************
	//@名字:        PT_LOGIN_C2L_ACC_LOGIN
	//@功能:        Client登录LoginServer
	//@备注:        客户端帐号登入
	//**********************************************************************/
    struct  PT_LOGIN_C2L_LOGIN_DATA
    {
		Char16	accName[MAX_ACCOUNT_LONGIN_NAME_LEN];
		Char16	accPsw[MAX_ACCOUNT_LONGIN_PSW_LEN];
		Char8	clientVersionNum[MAX_VERSION_NUM_LEN];	
    };
    struct PT_LOGIN_C2L_LOGIN_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_C2L_LOGIN_DATA);
    };
	class PT_LOGIN_C2L_LOGIN_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_C2L_LOGIN_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_C2L_ACC_LOGIN;
			mBaseDataSize                       =   PT_LOGIN_C2L_LOGIN_DATA_INFO::dataSize;

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
	//Loginserver返回FrontServer信息到客户端
	//**********************************************************************
	//@名字:        PT_LOGIN_L2C_ACC_LOGIN_SUCCESS
	//@功能:        LoginServer返回给客户端登录成果结果
	//@备注:        ???
	//**********************************************************************/
	struct  PT_LOGIN_L2C_LOGIN_SUCCESS_DATA
	{
		Char	ip[MG_NET_MAX_IP_LEN];
		I32		port;
	};
    struct PT_LOGIN_L2C_LOGIN_SUCCESS_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_L2C_LOGIN_SUCCESS_DATA);
    };
	class PT_LOGIN_L2C_LOGIN_SUCCESS_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_L2C_LOGIN_SUCCESS_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_L2C_ACC_LOGIN_SUCCESS;
			mBaseDataSize                       =   PT_LOGIN_L2C_LOGIN_SUCCESS_DATA_INFO::dataSize;

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
	//@名字:        PT_LOGIN_F2L_FRONT_SERVER_LOGIN
	//@功能:        FrontServer登陆LoginServer信息
	//@备注:        ???
	//**********************************************************************/
	struct PT_LOGIN_F2L_LOGIN_DATA 
	{
		Char	ip[MG_NET_MAX_IP_LEN];
		I32		port;
	};
    struct PT_LOGIN_F2L_LOGIN_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_F2L_LOGIN_DATA);
    };
	class PT_LOGIN_F2L_LOGIN_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_F2L_LOGIN_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_F2L_FRONT_SERVER_LOGIN;
			mBaseDataSize                       =   PT_LOGIN_F2L_LOGIN_DATA_INFO::dataSize;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_S2S;

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
	//Clinet登陆FrontServer信息
	//**********************************************************************
	//@名字:        PT_LOGIN_C2F_ACC_LOGIN
	//@功能:        Client登录FrontServer
	//@备注:        ???
	//**********************************************************************/
	struct PT_LOGIN_C2F_LOGIN_DATA
	{
		PT_LOGIN_C2L_LOGIN_DATA data;
	};
    struct PT_LOGIN_C2F_LOGIN_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_C2F_LOGIN_DATA);
    };
	class PT_LOGIN_C2F_LOGIN_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_C2F_LOGIN_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_C2F_ACC_LOGIN;
			mBaseDataSize                       =   PT_LOGIN_C2F_LOGIN_DATA_INFO::dataSize;

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
	//@名字:        PT_LOGIN_F2C_ACC_LOGIN_RESULT
	//@功能:        FrontServer返回登录结果Cleint
	//@备注:        ???
	//**********************************************************************/
	//Client登陆FrontServer结果
	enum PT_LOGIN_F2C_LOGIN_RESULT_TYPE 
	{
		LCFT_LOGIN_UNKNOW,
		LCFT_LOGIN_SUCCESS,			
		LCFT_LOGIN_FAIL,	
	};
	struct PT_LOGIN_F2C_LOGIN_RESULT_DATA
	{
		I8						result;
		PlayerIdType			accountId;
	};
    struct PT_LOGIN_F2C_LOGIN_RESULT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_F2C_LOGIN_RESULT_DATA);
    };
	class PT_LOGIN_F2C_LOGIN_RESULT_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_F2C_LOGIN_RESULT_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_F2C_ACC_LOGIN_RESULT;
			mBaseDataSize                       =   PT_LOGIN_F2C_LOGIN_RESULT_DATA_INFO::dataSize;

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
	//@名字:        PT_LOGIN_F2L_CLIENT_LOGIN
	//@功能:		FrontServer发送给LoginServer的客户端校验信息
	//@备注:        ???
	//**********************************************************************/
	struct	PT_LOGIN_F2L_CLIENT_LOGIN_DATA
	{
		I32 clientNetIdInFrontServer;
		PT_LOGIN_C2L_LOGIN_DATA data;
	};
    struct PT_LOGIN_F2L_CLIENT_LOGIN_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_F2L_CLIENT_LOGIN_DATA);
    };
	class PT_LOGIN_F2L_CLIENT_LOGIN_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_F2L_CLIENT_LOGIN_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_F2L_CLIENT_LOGIN;
			mBaseDataSize                       =   PT_LOGIN_F2L_CLIENT_LOGIN_DATA_INFO::dataSize;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_S2S;

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
	//@名字:        PT_LOGIN_F2L_CLIENT_LOGOUT
	//@功能:		FrontServer发送给LoginServer的客户端登出消息
	//@备注:        ???
	//**********************************************************************/
	struct	PT_LOGIN_F2L_CLIENT_LOGOUT_DATA
	{
		Char16	accName[MAX_ACCOUNT_LONGIN_NAME_LEN];
	};
    struct PT_LOGIN_F2L_CLIENT_LOGOUT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_F2L_CLIENT_LOGOUT_DATA);
    };
	class PT_LOGIN_F2L_CLIENT_LOGOUT_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_F2L_CLIENT_LOGOUT_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_F2L_CLIENT_LOGOUT;
			mBaseDataSize                       =   PT_LOGIN_F2L_CLIENT_LOGOUT_DATA_INFO::dataSize;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_S2S;

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
	//@名字:        PT_LOGIN_L2C_ACC_LOGIN_FAIL
	//@功能:		LoginServer发送给Client的客户端登录失败消息
	//@备注:        ???
	//**********************************************************************/
	//登陆失败结果
	enum PT_LOGIN_L2C_LOGIN_FAIL_TYPE 
	{
		LFFT_LOGIN_UNKNOW,
		LCFT_LOGIN_REDUPLICATE,			//重复登入
		LCFT_LOGIN_NONE_FRONTSERVER,	//没有登入服务器
		LCFT_LOGIN_IDENTITY_ERROR,		//账号或密码错误
		LCFT_LOGIN_IDENTITY_ERROR_MAX,	//账号或密码错误次数太多
		LCFT_LOGIN_LOCK,				//账号被锁定
	};
	struct PT_LOGIN_L2C_LOGIN_FAIL_DATA
	{
		I8 errResult;
	};
    struct PT_LOGIN_L2C_LOGIN_FAIL_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_L2C_LOGIN_FAIL_DATA);
    };
	class PT_LOGIN_L2C_LOGIN_FAIL_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_L2C_LOGIN_FAIL_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_L2C_ACC_LOGIN_FAIL;
			mBaseDataSize                       =   PT_LOGIN_L2C_LOGIN_FAIL_DATA_INFO::dataSize;

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
	//@名字:        PT_LOGIN_L2F_LOGIN_FRONT_SERVER_RESULT
	//@功能:		FrontServer登陆LoginServer结果
	//@备注:        ???
	//**********************************************************************/
	
	enum PT_LOGIN_L2F_LOGIN_RESULT_TYPE 
	{
		LFRT_LOGIN_UNKNOW,
		LFRT_LOGIN_SUCCESS,			
		LFRT_LOGIN_FAIL,	
	};
	struct PT_LOGIN_L2F_LOGIN_RESULT_DATA
	{
		I8 result;
	};
    struct PT_LOGIN_L2F_LOGIN_RESULT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_L2F_LOGIN_RESULT_DATA);
    };
	class PT_LOGIN_L2F_LOGIN_RESULT_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_L2F_LOGIN_RESULT_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_L2F_LOGIN_FRONT_SERVER_RESULT;
			mBaseDataSize                       =   PT_LOGIN_L2F_LOGIN_RESULT_DATA_INFO::dataSize;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_S2S;

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
	//@名字:        PT_LOGIN_L2F_CLIENT_CHECKED
	//@功能:		LoginServer返回给FrontServer客户端登录校验结果
	//@备注:        ???
	//**********************************************************************/
	
	enum PT_LOGIN_L2F_CLIENT_CHECKED_TYPE 
	{
		LFCT_LOGIN_UNKNOW,
		LFCT_LOGIN_SUCCESS,			
		LFCT_LOGIN_FAIL,	
	};
	struct PT_LOGIN_L2F_CLIENT_CHECKED_DATA
	{
		I8		result;
		I32		clientNetID;
		PT_LOGIN_C2L_LOGIN_DATA data;
		U64	accID;
	};
    struct PT_LOGIN_L2F_CLIENT_CHECKED_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_L2F_CLIENT_CHECKED_DATA);
    };
	class PT_LOGIN_L2F_CLIENT_CHECKED_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_L2F_CLIENT_CHECKED_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_L2F_CLIENT_CHECKED;
			mBaseDataSize                       =   PT_LOGIN_L2F_CLIENT_CHECKED_DATA_INFO::dataSize;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_S2S;

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
	//@名字:        PT_LOGIN_F2C_CLAN_DATA
	//@功能:		FrontServer返回家族列表给客户端
	//@备注:        ???
	//**********************************************************************/
    //**********************************************************************
    struct PT_LOGIN_F2C_CLAN_DATA_DATA
    {
		PlayerIdType			accountId;
        ClanIdType				clandatabaseid;				//氏族ID
		PlayerCharacterIdType	mainGenrealId;				//主武将
		PlayerCharacterIdType	wiseGenrealId;				//军师
		PlayerCharacterIdType	commanderGenrealId;			//统领
		PlayerCharacterIdType	curGenrealId;				//当前使用的武将
		RegionIdType			regionID;                  //氏族所在区域
		UInt					clanLevel;
		UInt					clanExp[4];
		UInt					clanMoney[16];
		U32						clanbagsize;               //氏族背包  
		U32						ConstellationId;			//氏族守护星宿ID
        U8						armyemblem;                //旗徽
        U8						armyemblemcolor;           //旗徽颜色
        U8						bg;                        //背景图案
        U8						bgcolor;                   //背景颜色
		U8						status;                     //状态  
		Char16					clanhomelandname[MAX_CHARACTER_NAME_LEN];	//郡望名
		Char16					clanname[MAX_CHARACTER_NAME_LEN];			//氏族名
    };
    struct PT_LOGIN_F2C_CLAN_DATA_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_F2C_CLAN_DATA_DATA);
    };
	class PT_LOGIN_F2C_DATA_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_F2C_DATA_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_F2C_CLAN_DATA;
			mBaseDataSize                       =   PT_LOGIN_F2C_CLAN_DATA_DATA_INFO::dataSize;

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
			if ( dataLen != PT_LOGIN_F2C_CLAN_DATA_DATA_INFO::dataSize )
				return false;
			return true;
		}
	};
    //**********************************************************************
	//@名字:        PT_LOGIN_C2F_CREATE_CLAN
	//@功能:		Client发送创建家族消息给FrontServer
	//@备注:        ???
	//**********************************************************************/
    struct PT_LOGIN_C2F_CREATE_CLAN_DATA
    {
		PlayerIdType			accountid;                  //玩家ID
		U32						ConstellationId;			//氏族守护星宿ID
		U8						armyemblem;                //旗徽
		U8						armyemblemcolor;           //旗徽颜色
		U8						bg;                        //背景图案
		U8						bgcolor;                   //背景颜色
		Char16					clanhomelandname[MAX_CHARACTER_NAME_LEN];	//郡望名
		Char16					clanname[MAX_CHARACTER_NAME_LEN];			//氏族名
    };
    struct PT_LOGIN_C2F_CREATE_CLAN_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_C2F_CREATE_CLAN_DATA);
    };
	class PT_LOGIN_C2F_CREATE_CLAN_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_C2F_CREATE_CLAN_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_C2F_CREATE_CLAN;
			mBaseDataSize                       =   PT_LOGIN_C2F_CREATE_CLAN_DATA_INFO::dataSize;

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
	//@名字:        PT_LOGIN_F2C_CREATE_CLAN_RESULT
	//@功能:		FrontServer返回创建家族结果给Client
	//@备注:        ???
	//**********************************************************************/
    enum CreateClanResult
    {
        CreateClanResult_Succeed = 0,
        CreateClanResult_NameExistOrUnlaw,
        CreateClanResult_CreateMemory_Error,   //创建内存失败
        CreateClanResult_DB_Error,            //数据库操作失败
        CreateClanResult_OtherError,
		CreateClanResult_NoPlayer,				//没有Player 信息
        CreateClanResult_Max
    };
    struct PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA
    {
         CreateClanResult		result;
		 ClanIdType				clanId;
		 RegionIdType			regionID;                  //氏族所在区域
		 U32					clanbagsize;               //氏族背包
    };
    struct PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA);
    };
	class PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_F2C_CREATE_CLAN_RESULT;
			mBaseDataSize                       =   PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA_INFO::dataSize;

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
	//@名字:        PT_LOGIN_C2F_DELETE_CLAN
	//@功能:		Client发送删除家族给FrontServer
	//@备注:        ???
	//**********************************************************************/
    struct PT_LOGIN_C2F_DELETE_CLAN_DATA
    {
		PlayerIdType	accountId;
        ClanIdType		clandatabaseid;            //氏族ID
    };
    struct PT_LOGIN_C2F_DELETE_CLAN_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_C2F_DELETE_CLAN_DATA);
    };
	class PT_LOGIN_C2F_DELETE_CLAN_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_C2F_DELETE_CLAN_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_C2F_DELETE_CLAN;
			mBaseDataSize                       =   PT_LOGIN_C2F_DELETE_CLAN_DATA_INFO::dataSize;

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
	//@名字:        PT_LOGIN_F2C_DELETE_CLAN_RESULT
	//@功能:		FrontServer返回删除家族结果给Client
	//@备注:        ???
	//**********************************************************************/
    enum DeleteClanResult
    {
        DeleteClanResult_Succeed = 0,
        DeleteClanResult_PswdError,
        DeleteClanResult_ClanUnexist,
        DeleteClanResult_ClanOndelete,
        DeleteClanResult_OtherError,

        DeleteClanResult_Max
    };
    struct PT_LOGIN_F2C_DELETE_CLAN_RESULT_DATA
    {
         DeleteClanResult result;
    };
    struct PT_LOGIN_F2C_DELETE_CLAN_RESULT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_F2C_DELETE_CLAN_RESULT_DATA);
    };
	class PT_LOGIN_F2C_DELETE_CLAN_RESULT_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_F2C_DELETE_CLAN_RESULT_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_F2C_DELETE_CLAN_RESULT;
			mBaseDataSize                       =   PT_LOGIN_F2C_DELETE_CLAN_RESULT_DATA_INFO::dataSize;

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
	//@名字:        PT_LOGIN_F2A_JOINGAME
	//@功能:		FrontServer发送客户端进入游戏给ChatServer
	//@备注:        ???
	//**********************************************************************/
	struct PT_LOGIN_F2A_JOINGAME_DATA
	{
		Char16	clanName[MAX_CLAN_NAME];
		I32		clientNetId;
		U64		accountId;
	};
	struct PT_LOGIN_F2A_JOINGAME_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LOGIN_F2A_JOINGAME_DATA);
	};
	class PT_LOGIN_F2A_JOINGAME_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_F2A_JOINGAME_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_F2A_JOINGAME;
			mBaseDataSize                       =   PT_LOGIN_F2A_JOINGAME_DATA_INFO::dataSize;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_S2S;

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
	//@名字:        PT_LOGIN_F2A_CLIENTLIST
	//@功能:		FrontServer发送在线客户端列表给ChatServer
	//@备注:        ???
	//**********************************************************************/
	struct PT_LOGIN_F2A_CLIENTLIST_INGAME_DATA
	{
		U16 count;
		PT_LOGIN_F2A_JOINGAME_DATA data[1];
	};
	struct PT_LOGIN_F2A_CLIENTLIST_INGAME_DATA_INFO
	{
		static const Int elmentSize = sizeof (PT_LOGIN_F2A_JOINGAME_DATA);
		static const Int headSize   = sizeof (PT_LOGIN_F2A_CLIENTLIST_INGAME_DATA) - sizeof(PT_LOGIN_F2A_JOINGAME_DATA);
		static const Int dataSize(PT_LOGIN_F2A_CLIENTLIST_INGAME_DATA* data)
		{
			return headSize + data->count * elmentSize;
		}
	};
	class PT_LOGIN_F2A_CLIENTLIST_INGAME_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_F2A_CLIENTLIST_INGAME_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_F2A_CLIENTLIST_INGAME;
			//mBaseDataSize                       =   PT_LOGIN_F2A_CLIENTLIST_INGAME_DATA_INFO::dataSize;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_S2S;

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
			if ( dataLen != PT_LOGIN_F2A_CLIENTLIST_INGAME_DATA_INFO::dataSize((PT_LOGIN_F2A_CLIENTLIST_INGAME_DATA*)data) )
				return false;
			return true;
		}
	};
	//**********************************************************************
	//@名字:        PT_LOGIN_F2A_EXITGAME
	//@功能:		FrontServer发送在客户端离线消息给ChatServer
	//@备注:        ???
	//**********************************************************************/
	struct PT_LOGIN_F2A_EXITGAME_DATA
	{
		Char16	clanName[MAX_CLAN_NAME];
	};
	struct PT_LOGIN_F2A_EXITGAME_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LOGIN_F2A_EXITGAME_DATA);
	};
	class PT_LOGIN_F2A_EXITGAME_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_F2A_EXITGAME_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_F2A_EXITGAME;
			mBaseDataSize                       =   PT_LOGIN_F2A_EXITGAME_DATA_INFO::dataSize;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_S2S;

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
	//@名字:        PT_LOGIN_C2F_CREATE_GENERAL
	//@功能:		Client创建角色离线消息给FrontServer
	//@备注:        ???
	//**********************************************************************/
    struct PT_LOGIN_C2F_CREATE_GENERAL_DATA
    {
        Char16			name[MAX_CHARACTER_NAME_LEN];
        Char16			charSurName[MAX_CHARACTER_NAME_LEN];
        U32             charArtIcon;
		U32             resID;
		PlayerIdType	accountId;
    };
    struct PT_LOGIN_C2F_CREATE_GENERAL_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_C2F_CREATE_GENERAL_DATA);
    };
	class PT_LOGIN_C2F_CREATE_GENERAL_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_C2F_CREATE_GENERAL_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_C2F_CREATE_GENERAL;
			mBaseDataSize                       =   PT_LOGIN_C2F_CREATE_GENERAL_DATA_INFO::dataSize;

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
	//@名字:        PT_LOGIN_F2C_CREATE_GENERAL_RESULT
	//@功能:		FrontServer发送在客户端离线消息给ChatServer
	//@备注:        ???
	//**********************************************************************/
    enum CreateGenrealResult
    {
        CreateGenrealResult_Succeed = 0,
        CreateGenrealResult_Error_NotPlayer,
		CreateGenrealResult_Error_NotClan,
		CreateGenrealResult_Error_Memory,
		CreateGenrealResult_Error_DB,
		CreateGenrealResult_Error_Name,

        CreateGenrealResult_Max
    };
    struct PT_LOGIN_F2C_CREATE_GENERAL_RESULT_DATA
    {
        CreateGenrealResult					result;
        PlayerCharacterIdType				genrealID;
		ClanIdType							clanId;
		RegionIdType						regionId;
		U32									regionType;
		U32									charTempId;
    };
    struct PT_LOGIN_F2C_CREATE_GENERAL_RESULT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_F2C_CREATE_GENERAL_RESULT_DATA);
    };
	class PT_LOGIN_F2C_CREATE_GENERAL_RESULT_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_F2C_CREATE_GENERAL_RESULT_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_F2C_CREATE_GENERAL_RESULT;
			mBaseDataSize                       =   PT_LOGIN_F2C_CREATE_GENERAL_RESULT_DATA_INFO::dataSize;

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
	//--------------------------------------------------------------------
	//**********************************************************************
	//@名字:        PT_LOGIN_C2F_JOINGAME
	//@功能:		client发送进入游戏消息给FrontServer
	//@备注:        ???
	//**********************************************************************/
	struct  PT_LOGIN_C2F_JOINGAME_DATA
	{
		PlayerIdType	accountId;
	};
	//-----------------------------------------------------------------------------
	struct  PT_LOGIN_C2F_JOINGAME_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LOGIN_C2F_JOINGAME_DATA);
	};
	//-----------------------------------------------------------------------------
	class PT_LOGIN_C2F_JOINGAME_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_C2F_JOINGAME_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_C2F_JOINGAME;
			mBaseDataSize                       =   PT_LOGIN_C2F_JOINGAME_DATA_INFO::dataSize;

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
	//--------------------------------------------------------------------
	enum LOGIN_INFRONTSERVER_CHECK_RESULT
	{
		Login_Infrontserver_Check_Result_Fail = 0,
		Login_Infrontserver_Check_Result_Success = 1
		
	};
	//--------------------------------------------------------------------
	//**********************************************************************
	//@名字:        PT_LOGIN_L2F_CHECK_INFRONTSERVER
	//@功能:		LoginServer发送检测客户端是否在游戏中消息给FrontServer
	//@备注:        ???
	//**********************************************************************/
	struct PT_LOGIN_L2F_CHECK_INFRONTSERVER_DATA
	{
		I32 clientNetIdInFrontServer;
		I32 clientNetIdInLoginServer;
	};
	struct PT_LOGIN_L2F_CHECK_INFRONTSERVER_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LOGIN_L2F_CHECK_INFRONTSERVER_DATA);
	};
	class PT_LOGIN_L2F_CHECK_INFRONTSERVER_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_L2F_CHECK_INFRONTSERVER_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_L2F_CHECK_INFRONTSERVER;
			mBaseDataSize                       =   PT_LOGIN_L2F_CHECK_INFRONTSERVER_DATA_INFO::dataSize;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_S2S;

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
	//@名字:        PT_LOGIN_F2L_CHECK_INFRONTSERVER_RESULT
	//@功能:		FrontServer返回检测客户端是否在游戏中的结果给LoginServer
	//@备注:        ???
	//**********************************************************************/
	struct PT_LOGIN_F2L_CHECK_INFRONTSERVER_RESULT_DATA
	{
		//Char16	accountName[MAX_ACCOUNT_LONGIN_NAME_LEN];
		I32		clientNetIdInLoginServer;
		Byte	result;
	};
	struct PT_LOGIN_F2L_CHECK_INFRONTSERVER_RESULT_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LOGIN_F2L_CHECK_INFRONTSERVER_RESULT_DATA);
	};
	class PT_LOGIN_F2L_CHECK_INFRONTSERVER_RESULT_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_F2L_CHECK_INFRONTSERVER_RESULT_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_F2L_CHECK_INFRONTSERVER_RESULT;
			mBaseDataSize                       =   PT_LOGIN_F2L_CHECK_INFRONTSERVER_RESULT_DATA_INFO::dataSize;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_S2S;

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
	//@名字:        PT_LOGIN_M2F_CHECK_INFRONTSERVER
	//@功能:		MapServer发送检测客户端是否在游戏中消息给FrontServer
	//@备注:        ???
	//**********************************************************************/
	struct PT_LOGIN_M2F_CHECK_INFRONTSERVER_DATA
	{
		I32 clientNetIdInFrontServer;
	};
	struct PT_LOGIN_M2F_CHECK_INFRONTSERVER_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LOGIN_M2F_CHECK_INFRONTSERVER_DATA);
	};
	class PT_LOGIN_M2F_CHECK_INFRONTSERVER_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_M2F_CHECK_INFRONTSERVER_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_M2F_CHECK_INFRONTSERVER;
			mBaseDataSize                       =   PT_LOGIN_M2F_CHECK_INFRONTSERVER_DATA_INFO::dataSize;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_S2S;

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
	//@名字:        PT_LOGIN_F2M_CHECK_INFRONTSERVER_RESULT
	//@功能:		FrontServer返回检测客户端是否在游戏中的结果给MapServer
	//@备注:        ???
	//**********************************************************************/
	struct PT_LOGIN_F2M_CHECK_INFRONTSERVER_RESULT_DATA
	{
		I32		clientNetIdInFrontServer;
		Byte	result;
	};
	struct PT_LOGIN_F2M_CHECK_INFRONTSERVER_RESULT_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LOGIN_F2M_CHECK_INFRONTSERVER_RESULT_DATA);
	};
	class PT_LOGIN_F2M_CHECK_INFRONTSERVER_RESULT_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_F2M_CHECK_INFRONTSERVER_RESULT_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_F2M_CHECK_INFRONTSERVER_RESULT;
			mBaseDataSize                       =   PT_LOGIN_F2M_CHECK_INFRONTSERVER_RESULT_DATA_INFO::dataSize;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_S2S;

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
	//@名字:        PT_SERVER_S2S_LOGIN_VERSION_ERROR
	//@功能:		服务器之间返回登录代码错误版本信息
	//@备注:        ???
	//**********************************************************************/
	struct PT_SERVER_S2S_LOGIN_VERSION_ERROR_DATA
	{
		Char16	serverName[MAX_SERVER_NAME_LEN];
		Byte	serverType;
		I32		dataSize;
		Char8	errorInfo[1];
	};
	struct PT_SERVER_S2S_LOGIN_VERSION_ERROR_DATA_INFO
	{
		static const Int headSize = sizeof (PT_SERVER_S2S_LOGIN_VERSION_ERROR_DATA) - sizeof(Char8);
		static Int dataSize(PT_SERVER_S2S_LOGIN_VERSION_ERROR_DATA* data)
		{
			return headSize + data->dataSize;
		}
	};
	class PT_SERVER_S2S_LOGIN_VERSION_ERROR_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_SERVER_S2S_LOGIN_VERSION_ERROR_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_SERVER_S2S_LOGIN_VERSION_ERROR;
			//mBaseDataSize                       =   PT_SERVER_S2S_LOGIN_VERSION_ERROR_DATA_INFO::dataSize;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_S2S;

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
			if ( dataLen != PT_SERVER_S2S_LOGIN_VERSION_ERROR_DATA_INFO::dataSize((PT_SERVER_S2S_LOGIN_VERSION_ERROR_DATA*)data) )
				return false;
			return true;
		}
	};
	//**********************************************************************
	//@名字:        PT_SERVER_S2C_LOGIN_VERSION_ERROR
	//@功能:		服务器返回登录代码错误版本信息给客户端
	//@备注:        ???
	//**********************************************************************/
	struct PT_SERVER_S2C_LOGIN_VERSION_ERROR_DATA
	{
		I32		dataSize;
		Char8	errorInfo[1];
	};
	struct PT_SERVER_S2C_LOGIN_VERSION_ERROR_DATA_INFO
	{
		static const Int headSize = sizeof (PT_SERVER_S2C_LOGIN_VERSION_ERROR_DATA) - sizeof(Char8);
		static Int dataSize(PT_SERVER_S2C_LOGIN_VERSION_ERROR_DATA* data)
		{
			return headSize + data->dataSize;
		}
	};
	class PT_SERVER_S2C_LOGIN_VERSION_ERROR_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_SERVER_S2C_LOGIN_VERSION_ERROR_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_SERVER_S2C_LOGIN_VERSION_ERROR;
			//mBaseDataSize                       =   PT_SERVER_S2C_LOGIN_VERSION_ERROR_DATA_INFO::dataSize;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_S2S;

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
			if ( dataLen != PT_SERVER_S2C_LOGIN_VERSION_ERROR_DATA_INFO::dataSize((PT_SERVER_S2C_LOGIN_VERSION_ERROR_DATA*)data) )
				return false;
			return true;
		}
	};
	//**********************************************************************
	//@功能:		Loginserver通知FrontServer重复登录玩家
	//@备注:        ???
	//**********************************************************************/
	/*struct PT_LOGIN_L2F_LOGIN_FRONT_KICKOUT_CLIENT_DATA
	{
        U64 clientAccountId;
	};
	struct PT_LOGIN_L2F_LOGIN_FRONT_KICKOUT_CLIENT_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LOGIN_L2F_LOGIN_FRONT_KICKOUT_CLIENT_DATA); 
	};
    
	struct PT_LOGIN_L2F_LOGIN_FRONT_KICKOUT_CLIENT_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{

	};
	*/
	//**********************************************************************
#pragma pack (pop)

}

/******************************************************************************/

#endif