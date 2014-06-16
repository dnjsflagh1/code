/******************************************************************************/
#ifndef _LOGINNETPACKET_H_
#define _LOGINNETPACKET_H_
/******************************************************************************/

#include "CommonGameDefine.h"
#include "NetDefine.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //游戏帐号包类型
    /******************************************************************************/
    enum LoginNetPacketType
    {
		PT_LOGIN_UNKNOW = 0,
		PT_LOGIN_S2S_SERVER_LOGIN,					//服务器之间的登入请求

		PT_F2M_MAPLIST,								

		PT_LOGIN_F2L_FRONT_SERVER_LOGIN,			//FrontServer 登入 LoginServer
		PT_LOGIN_L2F_LOGIN_FRONT_SERVER_RESULT,		//FrontServer 登入 LoginServer 返回结果

        PT_LOGIN_C2L_ACC_LOGIN = 20,				//客户端账号登陆LoginServer		
		PT_LOGIN_L2C_ACC_LOGIN_FAIL,				//客户端账号登入失败消息
		PT_LOGIN_L2C_ACC_LOGIN_QUEUE_INFO,

		PT_LOGIN_L2C_ACC_LOGIN_SUCCESS,				//客户端账号登入成功消息

		PT_LOGIN_C2F_ACC_LOGIN,						//客户端账号登入FrontServer
        PT_LOGIN_C2F_ACC_LOGOUT,					//客户端账号登入FrontServer
		PT_LOGIN_F2C_ACC_LOGIN_RESULT,				//客户端账号登入FrontServer返回结果

		PT_LOGIN_F2L_CLIENT_LOGIN,					//客户端账号登入通知和验证
		PT_LOGIN_L2F_CLIENT_CHECKED,				//客户端账号登入验证结果
		PT_LOGIN_F2L_CLIENT_LOGOUT,					//客户端账号登出

        PT_LOGIN_F2C_OPEN_CREATECLANUI,				//[FrontServer -> Client] 通知客户端打开创建氏族的界面
        PT_LOGIN_F2C_OPEN_CLANCONTROLUI,			//[FrontServer -> Client] 通知客户端打开氏族管理界面
        PT_LOGIN_C2F_CREATE_CLAN,					//[Client -> FrontServer] 请求服务器创建氏族。
        PT_LOGIN_F2C_CREATE_CLAN_RESULT,			//[FrontServer -> Client] 返回服务器创建氏族的结果
        PT_LOGIN_C2F_SELECT_CLAN,					//[Client -> FrontServer] 请求服务器选择氏族。
        PT_LOGIN_F2C_SELECT_CLAN_RESULT,			//[FrontServer -> Client] 返回服务器选择氏族的结果
        PT_LOGIN_C2F_DELETE_CLAN,					//[Client -> FrontServer] 请求服务器删除氏族。
        PT_LOGIN_F2C_DELETE_CLAN_RESULT,			//[FrontServer -> Client] 返回服务器删除氏族的结果

        PT_LOGIN_C2F_JOINGAME,						//[Client -> FrontServer] 客户端请求登录game

		PT_LOGIN_F2A_JOINGAME,						//[FrontServer -> ChatServer]前台服务器通知聊天服务器客户端进入游戏
		PT_LOGIN_F2A_EXITGAME,						//[FrontServer -> ChatServer]前台服务器通知聊天服务器客户端离开游戏
		PT_LOGIN_F2A_CLIENTLIST_INGAME,				//[FrontServer -> ChatServer]前台服务登录聊天服务器时在游戏中的客户端对象
		
        PT_LOGIN_F2C_OPENCRETEGENREALUI,			//[FrontServer -> Client] 服务器结果返回，如果成功就是进入游戏。
        PT_LOGIN_C2F_CREATE_GENERAL,				//[Client -> FrontServer] 客户端请求创建武将。
        PT_LOGIN_F2C_CREATE_GENERAL_RESULT,			//[FrontServer -> Client] 客户端返回创建武将结果。

		// 健壮性检测
		PT_LOGIN_L2F_CHECK_INFRONTSERVER,
		PT_LOGIN_F2L_CHECK_INFRONTSERVER_RESULT,
		PT_LOGIN_M2F_CHECK_INFRONTSERVER,
		PT_LOGIN_F2M_CHECK_INFRONTSERVER_RESULT,
    };
    
	/******************************************************************************/
	//登录排队类型
	/******************************************************************************/
    enum LOGIN_LINE_UP_TYPE
	{
          login_line_up_busy = 1,
		  login_line_up_full

	};


#pragma pack (push)
#pragma pack (1)

    //**********************************************************************
    //服务器之间登入
    struct PT_LOGIN_S2S_LOGIN_DATA
    {
        U8  serverType;
        U32 code; 
		U32 serverId;
		U64 serverUniqueFlag;
		Char16 name[MAX_SERVER_NAME_LEN];
    };

    struct PT_LOGIN_S2S_LOGIN_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_S2S_LOGIN_DATA);
    };

	//**********************************************************************

	struct NetMapServer
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
    };

	//**********************************************************************
    //客户端帐号登入
    struct  PT_LOGIN_C2L_LOGIN_DATA
    {
		Char16 accName[MAX_ACCOUNT_LONGIN_NAME_LEN];
		Char16 accPsw[MAX_ACCOUNT_LONGIN_PSW_LEN];
    };
    struct PT_LOGIN_C2L_LOGIN_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_C2L_LOGIN_DATA);
    };

	//**********************************************************************
	//Loginserver返回FrontServer信息到客户端
	struct  PT_LOGIN_L2C_LOGIN_SUCCESS_DATA
	{
		Char	ip[MG_NET_MAX_IP_LEN];
		I32		port;
	};
    struct PT_LOGIN_L2C_LOGIN_SUCCESS_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_L2C_LOGIN_SUCCESS_DATA);
    };

	//**********************************************************************
	//Loginserver返回登陆队列信息
	struct  PT_LOGIN_L2C_ACC_LOGIN_QUEUE_INFO_DATA
	{   
		Byte type;
		I32 waitCount;
	};
    struct PT_LOGIN_L2C_ACC_LOGIN_QUEUE_INFO_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_L2C_ACC_LOGIN_QUEUE_INFO_DATA);
    };

	//**********************************************************************
	//FrontServer登陆LoginServer信息
	struct PT_LOGIN_F2L_LOGIN_DATA 
	{
		Char	ip[MG_NET_MAX_IP_LEN];
		I32		port;
	};
    struct PT_LOGIN_F2L_LOGIN_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_F2L_LOGIN_DATA);
    };

	//**********************************************************************
	//Clinet登陆FrontServer信息
	struct PT_LOGIN_C2F_LOGIN_DATA
	{
		PT_LOGIN_C2L_LOGIN_DATA data;
	};
    struct PT_LOGIN_C2F_LOGIN_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_C2F_LOGIN_DATA);
    };

	//**********************************************************************
	//Client登陆FrontServer结果
	enum PT_LOGIN_F2C_LOGIN_RESULT_TYPE 
	{
		LCFT_LOGIN_UNKNOW,
		LCFT_LOGIN_SUCCESS,			
		LCFT_LOGIN_FAIL,	
	};
	struct PT_LOGIN_F2C_LOGIN_RESULT_DATA
	{
		I8 result;
	};
    struct PT_LOGIN_F2C_LOGIN_RESULT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_F2C_LOGIN_RESULT_DATA);
    };
	//**********************************************************************
	//FrontServer发送给LoginServer的客户端校验信息
	struct	PT_LOGIN_F2L_CLIENT_LOGIN_DATA
	{
		I32 clientNetId;
		PT_LOGIN_C2L_LOGIN_DATA data;
	};
    struct PT_LOGIN_F2L_CLIENT_LOGIN_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_F2L_CLIENT_LOGIN_DATA);
    };
	//**********************************************************************
	//FrontServer发送给LoginServer的客户端登出消息
	struct	PT_LOGIN_F2L_CLIENT_LOGOUT_DATA
	{
		Char16	accName[MAX_ACCOUNT_LONGIN_NAME_LEN];
	};
    struct PT_LOGIN_F2L_CLIENT_LOGOUT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_F2L_CLIENT_LOGOUT_DATA);
    };
	//**********************************************************************
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
	//**********************************************************************
	//FrontServer登陆LoginServer结果
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
	//**********************************************************************
	//LoginServer返回给FrontServer校验结果
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
    //**********************************************************************
    struct PT_LOGIN_F2C_SIMPLECLANDATABASE
    {
        U64 clandatabaseid;				//氏族ID
        U64 accountid;                  //玩家ID
        U8  status;                     //状态
        U8  ancestry;				    //血统
        Char16 clanhomelandname[MAX_CHARACTER_NAME_LEN];	//郡望名
        Char16 clanname[MAX_CHARACTER_NAME_LEN];			//氏族名
        U8  armyemblem;                //旗徽
        U8  armyemblemcolor;           //旗徽颜色
        U8  bg;                        //背景图案
        U8  bgcolor;                   //背景颜色
        U32 clanbagsize;               //氏族背包
        U64 mainGenrealId;             //主武将
        U32 regionID;                  //氏族所在区域
        U8  regionType;                //地图类型
    };
    struct PT_LOGIN_F2C_SIMPLECLANDATABASE_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_F2C_SIMPLECLANDATABASE);
    };
    //**********************************************************************
    struct PT_LOGIN_F2C_OPEN_CLANCONTROLUI_DATA
    {
        UInt nCount;
        PT_LOGIN_F2C_SIMPLECLANDATABASE clanDatabase[1]; 
    };
    struct PT_LOGIN_F2C_OPEN_CLANCONTROLUI_DATA_INFO
    {
        static const Int elmentSize = sizeof (PT_LOGIN_F2C_SIMPLECLANDATABASE);
        static const Int headSize   = sizeof (PT_LOGIN_F2C_OPEN_CLANCONTROLUI_DATA) - sizeof(PT_LOGIN_F2C_SIMPLECLANDATABASE);
    };
    //**********************************************************************
    struct PT_LOGIN_C2F_CREATE_CLAN_DATA
    {
         PT_LOGIN_F2C_SIMPLECLANDATABASE clanDatabase;
    };
    struct PT_LOGIN_C2F_CREATE_CLAN_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_C2F_CREATE_CLAN_DATA);
    };
    //**********************************************************************
    enum CreateClanResult
    {
        CreateClanResult_Succeed = 0,
        CreateClanResult_NameExistOrUnlaw,
        CreateClanResult_OverMaxCreateS,
        CreateClanResult_OverMaxCreateR,
        CreateClanResult_OtherError,
		CreateClanResult_NoPlayer,				//没有Player 信息
		CreateClanResult_DB_Error,				//数据库操作失败

        CreateClanResult_Max
    };
    struct PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA
    {
         CreateClanResult result;
    };
    struct PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA);
    };
    //**********************************************************************
    struct PT_LOGIN_C2F_SELECT_CLAN_DATA
    {
        U64 clandatabaseid;            //氏族ID
    };
    struct PT_LOGIN_C2F_SELECT_CLAN_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_C2F_SELECT_CLAN_DATA);
    };
    //**********************************************************************
    enum SelectClanResult
    {
        SelectClanResult_Succeed = 0,
        SelectClanResult_ClanUnexist,        //氏族不存在
        SelectClanResult_ClanOndelete,       //氏族正在删除中
        SelectClanResult_OtherError,         //其它未知错误

        SelectClanResult_Max
    };
    struct PT_LOGIN_F2C_SELECT_CLAN_RESULT_DATA
    {
        SelectClanResult result;
    };
    struct PT_LOGIN_F2C_SELECT_CLAN_RESULT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_F2C_SELECT_CLAN_RESULT_DATA);
    };
    //**********************************************************************
    struct PT_LOGIN_C2F_DELETE_CLAN_DATA
    {
         U64 clandatabaseid;            //氏族ID
    };
    struct PT_LOGIN_C2F_DELETE_CLAN_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_C2F_DELETE_CLAN_DATA);
    };
    //**********************************************************************
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
	//**********************************************************************
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
	//**********************************************************************
	struct PT_LOGIN_F2A_CLIENTLIST_INGAME_DATA
	{
		U16 count;
		PT_LOGIN_F2A_JOINGAME_DATA data[1];
	};
	struct PT_LOGIN_F2A_CLIENTLIST_INGAME_DATA_INFO
	{
		static const Int elmentSize = sizeof (PT_LOGIN_F2A_JOINGAME_DATA);
		static const Int headSize   = sizeof (PT_LOGIN_F2A_CLIENTLIST_INGAME_DATA) - sizeof(PT_LOGIN_F2A_JOINGAME_DATA);
	};

	//**********************************************************************
	struct PT_LOGIN_F2A_EXITGAME_DATA
	{
		Char16	clanName[MAX_CLAN_NAME];
	};
	struct PT_LOGIN_F2A_EXITGAME_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LOGIN_F2A_EXITGAME_DATA);
	};
    //**********************************************************************
    struct PT_LOGIN_C2F_CREATE_GENERAL_DATA
    {
        Char16			name[MAX_CHARACTER_NAME_LEN];
        Char16			charZiName[MAX_CHARACTER_NAME_LEN];
        U32				characterTemplateID;
		U32				charArtIcon;
		RegionIdType    maplistid;
		Int             maplisttype;
		U32             pointerid;
		U32             resID;
    };
    struct PT_LOGIN_C2F_CREATE_GENERAL_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_C2F_CREATE_GENERAL_DATA);
    };
    //**********************************************************************
    enum CreateGenrealResult
    {
        CreateGenrealResult_Succeed = 0,
        CreateGenrealResult_OtherError,

        CreateGenrealResult_Max
    };
    struct PT_LOGIN_F2C_CREATE_GENERAL_RESULT_DATA
    {
        CreateGenrealResult result;
        Bool                isGenreal;
        IdType              genrealID;
    };
    struct PT_LOGIN_F2C_CREATE_GENERAL_RESULT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_F2C_CREATE_GENERAL_RESULT_DATA);
    };
	//--------------------------------------------------------------------
	enum LOGIN_INFRONTSERVER_CHECK_RESULT
	{
		Login_Infrontserver_Check_Result_Success = 0,
		Login_Infrontserver_Check_Result_Fail
	};
	//--------------------------------------------------------------------
    //**********************************************************************
	struct PT_LOGIN_L2F_CHECK_INFRONTSERVER_DATA
	{
		Char16 accountName[MAX_ACCOUNT_LONGIN_NAME_LEN];
	};
	struct PT_LOGIN_L2F_CHECK_INFRONTSERVER_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LOGIN_L2F_CHECK_INFRONTSERVER_DATA);
	};
	//**********************************************************************
	struct PT_LOGIN_F2L_CHECK_INFRONTSERVER_RESULT_DATA
	{
		Char16 accountName[MAX_ACCOUNT_LONGIN_NAME_LEN];
		Byte		  result;
	};
	struct PT_LOGIN_F2L_CHECK_INFRONTSERVER_RESULT_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LOGIN_F2L_CHECK_INFRONTSERVER_RESULT_DATA);
	};
	//**********************************************************************
	struct PT_LOGIN_M2F_CHECK_INFRONTSERVER_DATA
	{
		Char16 accountName[MAX_ACCOUNT_LONGIN_NAME_LEN];
	};
	struct PT_LOGIN_M2F_CHECK_INFRONTSERVER_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LOGIN_M2F_CHECK_INFRONTSERVER_DATA);
	};
	//**********************************************************************
	struct PT_LOGIN_F2M_CHECK_INFRONTSERVER_RESULT_DATA
	{
		Char16 accountName[MAX_ACCOUNT_LONGIN_NAME_LEN];
		Byte		  result;
	};
	struct PT_LOGIN_F2M_CHECK_INFRONTSERVER_RESULT_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LOGIN_F2M_CHECK_INFRONTSERVER_RESULT_DATA);
	};
	//**********************************************************************
#pragma pack (pop)

}

/******************************************************************************/

#endif