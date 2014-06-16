/******************************************************************************/
#ifndef _ACCOUNTNETPACKET_H_
#define _ACCOUNTNETPACKET_H_
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
        PT_ACC_C2L_LOGIN,				//Client登陆Login
		PT_ACC_L2C_LOGIN_SUCCESS,		//Login信息给client
		PT_ACC_F2L_LOGIN,				//Front登陆Login
		PT_ACC_C2F_LOGIN,				//Client登陆Front
		PT_ACC_F2L_CLIENT_LOGIN,
		PT_ACC_L2F_CLIENT_CHECKED,
		PT_ACC_F2C_CHARACTER_LIST,
		PT_ACC_C2F_SELECT_CHARACTER,
		PT_ACC_C2F_CREATE_CHARACTER,
		PT_ACC_LOGIN_RESULT,			//登陆错误号		
    };

#pragma pack (push)
#pragma pack (1)

    //客户端帐号登入
    struct  PT_ACC_C2L_LOGIN_DATA
    {
		Char16 accName[MAX_ACCOUNT_LONGIN_NAME_LEN];
		Char16 accPsw[MAX_ACCOUNT_LONGIN_PSW_LEN];
    };
	
	//Loginserver返回FrontServer信息
	struct  PT_ACC_L2C_LOGIN_SUCCESS_DATA
	{
		Char16		name[MAX_SERVER_NAME_LEN];
		Char		ip[MG_NET_MAX_IP_LEN];
		I32			port;
	};

	//FrontServer登陆LoginServer信息
	struct PT_ACC_F2L_LOGIN_DATA 
	{
		Char16	name[MAX_SERVER_NAME_LEN];
		Char	ip[MG_NET_MAX_IP_LEN];
		I32		port;
	};

	//Clinet登陆FrontServer信息
	struct PT_ACC_C2F_LOGIN_DATA
	{
		PT_ACC_C2L_LOGIN_DATA data;
	};
	
	//FrontServer发送给LoginServer的客户端校验信息
	struct	PT_ACC_F2L_CLIENT_LOGIN_DATA
	{
		I32 clientNetId;
		PT_ACC_C2L_LOGIN_DATA data;
	};
	
	//登陆错误号
	struct PT_ACC_LOGIN_RESULT_DATA
	{
		I8 errResult;
	};
	
	//LoginServer返回给FrontServer校验结果
	struct PT_ACC_L2F_CLIENT_CHECKED_DATA
	{
		I32 clientNetId;
		UInt accountId;
		Bool isChecked;
	};

	//角色信息
	struct CharInfo 
	{
		UInt	id;
		UInt	accountId;
		UInt	serverId;
		Char16	name[MAX_ACCOUNT_LONGIN_NAME_LEN];
		U8		state;
	};

	//FrontServer返回给Client的角色列表 
	struct PT_ACC_F2C_CHARACTER_LIST_DATA
	{
		I8 charNum;
		Char charList[1];//角色列表
	};

	struct PT_ACC_C2F_SELECT_CHARACTER_DATA
	{
		UInt characterId;
	};
	
	struct PT_ACC_C2F_CREATE_CHARACTER_DATA
	{
		//此处数据待定
	};
#pragma pack (pop)
}

/******************************************************************************/

#endif