/******************************************************************************/
#ifndef _DBNETPACKET_H_
#define _DBNETPACKET_H_
/******************************************************************************/
#include "CommonGameDefine.h"
#include "NetDefine.h"
#include "WorldCoreDefine.h"
/******************************************************************************/

namespace MG
{
	/******************************************************************************/
	//数据库操作相关类型
	/******************************************************************************/
	enum DbNetPacket
	{
		PT_DB_S2D_SEL_ACCOUNT,			//服务器向 DbServer请求账户信息
		PT_DB_D2S_SEL_ACCOUNT_RESULT,	//服务器向 DbServer请求账户信息
	};

#pragma pack (push)
#pragma pack (1)
	/******************************************************************************/
	//数据库操作的数据
	/******************************************************************************/
	struct PackAccountData
	{
		I32		clientNetId;
		Char16	accName[MAX_ACCOUNT_LONGIN_NAME_LEN];
		Char16	accPsw[MAX_ACCOUNT_LONGIN_PSW_LEN];
	};

	struct PT_DB_S2D_SEL_ACCOUNT_DATA
	{
		I32				serverNetId;
		I32				accNum;
		PackAccountData	accInfo[1];
	};
	struct PT_DB_S2D_SEL_ACCOUNT_DATA_INFO
	{
		static const Int accountInfoSize	= sizeof (PackAccountData);
		static const Int headSize           = sizeof (PT_DB_S2D_SEL_ACCOUNT_DATA) - accountInfoSize;
		static Int dataSize( PT_DB_S2D_SEL_ACCOUNT_DATA* data )
		{
			return  PT_DB_S2D_SEL_ACCOUNT_DATA_INFO::headSize +
				PT_DB_S2D_SEL_ACCOUNT_DATA_INFO::accountInfoSize * data->accNum;
		}
	};
	
	//////////////////////////////////////////////////////////////////////////////	
	struct  PackAccountSelRelultData
	{
		I32 clientNetId;
		// 为0时表示失败
		U64 accountId;		
	};

	struct PT_DB_D2S_SEL_ACCOUNT_RESULT_DATA
	{
		I32							serverNetId;
		I32							accNum;
		PackAccountSelRelultData	accResultData[1];
	};
	struct PT_DB_D2S_SEL_ACCOUNT_RESULT_DATA_INFO
	{
		static const Int accResultDataSize	= sizeof (PackAccountSelRelultData);
		static const Int headSize           = sizeof (PT_DB_D2S_SEL_ACCOUNT_RESULT_DATA) - accResultDataSize;
		static Int dataSize( PT_DB_D2S_SEL_ACCOUNT_RESULT_DATA* data )
		{
			return  PT_DB_D2S_SEL_ACCOUNT_RESULT_DATA_INFO::headSize +
				PT_DB_D2S_SEL_ACCOUNT_RESULT_DATA_INFO::accResultDataSize * data->accNum;
		}
	};

}
#pragma pack (pop)
#endif