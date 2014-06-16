/******************************************************************************/
#ifndef _GMLOGINNETPACKET_H_
#define _GMLOGINNETPACKET_H_
/******************************************************************************/

#include "CommonGameDefine.h"
#include "NetDefine.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //游戏帐号包类型
    /******************************************************************************/
    enum GMAccountNetPacketType
    {
		GMPT_CGMM_ACC_LOGIN,
		GMPT_GMMC_ACC_LOGIN_RESULT,

		GMPT_CGMM_ACC_CREATE,
		GMPT_GMMC_ACC_CREATE_RESULT,

		GMPT_CGMM_ACC_DELETE,
		GMPT_GMMC_ACC_DELETE_RESULT,

		GMPT_CGMM_ACC_UPDATE,
		GMPT_GMMC_ACC_UPDATE_RESULT,

		GMPT_CGMM_ACC_UPDATE_PSW,
		GMPT_CGMM_ACC_UPDATE_PSW_RESULT,

		GMPT_CGMM_ACC_SELECT,
		GMPT_GMMC_ACC_SELECT_RESULT,

    };
    
	/******************************************************************************/
	//登录排队类型
	/******************************************************************************/
#pragma pack (push)
#pragma pack (1)
	enum gm_account_operate_result
	{
		gaor_success = 0,			//帐号操作成功
		gaor_lack_authority,		//权限不够
		gaor_errname_or_errpsw,		//帐号或密码错误
		gaor_errname,				//用户名错误
		gaor_err_psw,				//密码错误
		gaor_err_version,			//版本不匹配
		gaor_timeout,				//超时
	};

	enum gm_authority
	{
		gmat_null           = 0,
		gmat_supreme        = (1<<0),

		gmat_level_1        = (1<<1),
		gmat_level_2        = (1<<2),
		gmat_level_3        = (1<<3),
		gmat_level_4        = (1<<4),
	};
	//**********************************************************************
	//GM帐号登入
	struct GMPT_CGMM_ACC_LOGIN_DATA
	{
		Char16	accName[MAX_ACCOUNT_LONGIN_NAME_LEN];
		Char16	accPsw[MAX_ACCOUNT_LONGIN_PSW_LEN];
		Char8	clientVersionNum[MAX_VERSION_NUM_LEN];	
	};
	struct GMPT_CGMM_ACC_LOGIN_DATA_INFO
	{
		static const Int dataSize = sizeof (GMPT_CGMM_ACC_LOGIN_DATA);
	};
	//GM登录返回
	struct GMPT_GMMC_ACC_LOGIN_RESULT_DATA
	{
		Byte result;
		Int gmId;
		Int authority;	
	};
	struct GMPT_GMMC_ACC_LOGIN_RESULT_DATA_INFO
	{
		static const Int dataSize = sizeof (GMPT_GMMC_ACC_LOGIN_RESULT_DATA);
	};
	//**********************************************************************
	//创建GM帐号
	struct GMPT_CGMM_ACC_CREATE_DATA
	{
		Char16	accName[MAX_ACCOUNT_LONGIN_NAME_LEN];
		Char16	accPsw[MAX_ACCOUNT_LONGIN_PSW_LEN];
		Int	authority;
	};
	struct GMPT_CGMM_ACC_CREATE_DATA_INFO
	{
		static const Int dataSize = sizeof (GMPT_CGMM_ACC_CREATE_DATA);
	};
	//创建GM帐号返回
	struct GMPT_GMMC_ACC_CREATE_RESULT_DATA
	{
		Int	  gmId;
		Byte  result;
	};
	struct GMPT_GMMC_ACC_CREATE_RESULT_DATA_INFO
	{
		static const Int dataSize = sizeof (GMPT_GMMC_ACC_CREATE_RESULT_DATA);
	};
	//**********************************************************************
	//删除GM帐号
	struct GMPT_CGMM_ACC_DELETE_DATA
	{
		Char16	accName[MAX_ACCOUNT_LONGIN_NAME_LEN];
	};
	struct GMPT_CGMM_ACC_DELETE_DATA_INFO
	{
		static const Int dataSize = sizeof (GMPT_CGMM_ACC_DELETE_DATA);
	};
	//删除GM帐号返回
	struct GMPT_GMMC_ACC_DELETE_RESULT_DATA
	{
		Int	  gmId;
		Byte  result;
	};
	struct GMPT_GMMC_ACC_DELETE_RESULT_DATA_INFO
	{
		static const Int dataSize = sizeof (GMPT_GMMC_ACC_DELETE_RESULT_DATA);
	};
	//**********************************************************************
	//修改GM
	struct GMPT_CGMM_ACC_UPDATE_DATA
	{
		Char16	accName[MAX_ACCOUNT_LONGIN_NAME_LEN];
		Char16	newAccPsw[MAX_ACCOUNT_LONGIN_PSW_LEN];
		Int		gmId;
		Int		authority;
	};
	struct GMPT_CGMM_ACC_UPDATE_DATA_INFO
	{
		static const Int dataSize = sizeof (GMPT_CGMM_ACC_UPDATE_DATA);
	};
	//修改GM返回
	struct GMPT_GMMC_ACC_UPDATE_RESULT_DATA
	{
		Int	  gmId;
		Byte  result;
	};
	struct GMPT_GMMC_ACC_UPDATE_RESULT_DATA_INFO
	{
		static const Int dataSize = sizeof (GMPT_GMMC_ACC_UPDATE_RESULT_DATA);
	};
	//**********************************************************************
	//查询GM账号
	struct NetGMPlayer
	{
		Char16	accName[MAX_ACCOUNT_LONGIN_NAME_LEN];
		Char16	accPsw[MAX_ACCOUNT_LONGIN_PSW_LEN];
		I32		netId;
		Int		authority;
		Byte	online;
		Int		gmId;
	};
	struct GMPT_CGMM_ACC_SELECT_DATA
	{
	};
	struct GMPT_CGMM_ACC_SELECT_DATA_INFO
	{
		static const Int dataSize = sizeof (GMPT_CGMM_ACC_UPDATE_DATA);
	};
	//查询GM账号返回
	struct GMPT_GMMC_ACC_SELECT_RESULT_DATA
	{
		Int			count;
		NetGMPlayer	GMPlayerGroup[1];
	};
	struct GMPT_GMMC_ACC_SELECT_RESULT_DATA_INFO
	{
		static const Int GMPlayerSize = sizeof(NetGMPlayer);
		static const Int headSize = sizeof (GMPT_GMMC_ACC_SELECT_RESULT_DATA) - GMPlayerSize;
		static const Int dataSize(GMPT_GMMC_ACC_SELECT_RESULT_DATA* data)
		{
			return headSize + data->count * GMPlayerSize;
		}
	};


#pragma pack (pop)

}

/******************************************************************************/

#endif