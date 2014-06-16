/******************************************************************************/
#ifndef _H_SYSLOGNETPACKET_
#define _H_SYSLOGNETPACKET_
/******************************************************************************/
#include "CommonGameDefine.h"
#include "NetDefine.h"
#include "GameNetPacket.h"
/******************************************************************************/

namespace MG
{

	/**********************************************************************
	//@负责人:      邓黄超
	//@协助人:      徐开超
	**********************************************************************/

    /******************************************************************************/
    //游戏系统日志包类型
    /******************************************************************************/
    enum SysLogNetPacketType
    {
        PT_SYSLOG_UNKNOW = 0,

        //test
        PT_SYSLOG_ACCOUNT_OPERATE,                //帐号的操作
		//end test

		//账号的登入登出
		PT_SYSLOG_PLAYER_LOGIN,

		//武将的登入登出
		PT_SYSLOG_CHARACTER_LOGIN,

        PT_SYSLOG_MAX
    };

#pragma pack (push)
#pragma pack (1)

    //**********************************************************************
	//test
    struct  PT_SYSLOG_ACCOUNT_OPERATE_DATA
    {
        Byte                    type;                               //帐号使用的类型
        U64                     accountID;                          //帐号ID
        U64                     time;                               //操作的时间
        Char16                  name[MAX_ACCOUNT_LONGIN_NAME_LEN];  //玩家帐号名
    };
    struct PT_SYSLOG_ACCOUNT_OPERATE_DATA_INFO
    {
        static const I32 dataSize = sizeof(PT_SYSLOG_ACCOUNT_OPERATE_DATA);
    };
	//end test
    
	//-------------------------------------------------------------------------------------
	struct netPlayerLogData
	{
		Byte			type;
		U32				ipAddress;
		AccountIdType	playerId;
		U64				logTime;
	};
	struct netPlayerLogData_Info
	{
		static const I32 dataSize = sizeof(netPlayerLogData);
	};
	//**********************************************************************
	//@名字:        PT_SYSLOG_PLAYER_LOGIN
	//@功能:        
	//@备注:        
	//**********************************************************************/
	
	typedef			netPlayerLogData			PT_SYSLOG_PLAYER_LOGIN_Data;
	typedef			netPlayerLogData_Info		PT_SYSLOG_PLAYER_LOGIN_DATA_INFO;
	//**********************************************************************
	class PT_SYSLOG_PLAYER_LOGIN_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_SYSLOG_PLAYER_LOGIN_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_SYSLOG;
			mType                               =   PT_SYSLOG_PLAYER_LOGIN;
			mBaseDataSize                       =   PT_SYSLOG_PLAYER_LOGIN_DATA_INFO::dataSize ;

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
	//-------------------------------------------------------------------------------------
	struct netCharacterLogData
	{
		Byte						type;
		U32							ipAddress;
		Char16						name[MAX_CHARACTER_NAME_LEN];
		Char16						surName[MAX_CHARACTER_NAME_LEN];
		PlayerCharacterIdType		characterId;	
		AccountIdType				playerId;
		U64							logTime;
		
	};
	struct netCharacterLogData_Info
	{
		static const I32 dataSize = sizeof(netCharacterLogData);
	};
	//**********************************************************************
	//@名字:        PT_SYSLOG_CHARACTER_LOGIN
	//@功能:        
	//@备注:        
	//**********************************************************************/

	typedef			netCharacterLogData				PT_SYSLOG_CHARACTER_LOGIN_Data;
	typedef			netCharacterLogData_Info		PT_SYSLOG_CHARACTER_LOGIN_DATA_INFO;
	//**********************************************************************
	class PT_SYSLOG_CHARACTER_LOGIN_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_SYSLOG_CHARACTER_LOGIN_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_SYSLOG;
			mType                               =   PT_SYSLOG_CHARACTER_LOGIN;
			mBaseDataSize                       =   PT_SYSLOG_CHARACTER_LOGIN_DATA_INFO::dataSize ;

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
#pragma pack (pop)
}

/******************************************************************************/

#endif // _H_SYSLOGNETPACKET_