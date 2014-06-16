/******************************************************************************/
#ifndef _CHATNETPACKET_H_
#define _CHATNETPACKET_H_
/******************************************************************************/
#include "CommonGameDefine.h"
#include "NetDefine.h"
#include "WorldCoreDefine.h"
/******************************************************************************/

namespace MG
{
	/******************************************************************************/
	//@负责人:      王育安
	//@协助人:      邓黄超
	/******************************************************************************/
	enum ChatNetPacket
	{
		//同地图聊天
		/*PT_CHAT_C2F_REGION,
		PT_CHAT_F2M_REGION,
		PT_CHAT_M2C_REGION,*/
		//两人聊天
		/*PT_CHAT_C2F_TWO_PERSON,
		PT_CHAT_F2M_TWO_PERSON,
		PT_CHAT_M2C_TWO_PERSON,*/


		//@------------地域聊天-----------
		// 政区
		// 同界
		PT_CHAT_C2F_ONE_WORLD,
		PT_CHAT_F2A_ONE_WORLD,
		PT_CHAT_A2M_ONE_WORLD,
		PT_CHAT_M2F_ONE_WORLD,
		PT_CHAT_F2C_ONE_WORLD,

		// 同州
		PT_CHAT_C2F_ONE_ZHOU,
		PT_CHAT_F2A_ONE_ZHOU,
		PT_CHAT_A2M_ONE_ZHOU,
		PT_CHAT_M2F_ONE_ZHOU,
		PT_CHAT_F2C_ONE_ZHOU,
		// 同郡
		PT_CHAT_C2F_ONE_JUN,
		PT_CHAT_F2A_ONE_JUN,
		PT_CHAT_A2M_ONE_JUN,
		PT_CHAT_M2F_ONE_JUN,
		PT_CHAT_F2C_ONE_JUN,
		// 同县
		PT_CHAT_C2F_ONE_XIAN,
		PT_CHAT_F2A_ONE_XIAN,
		PT_CHAT_A2M_ONE_XIAN,
		PT_CHAT_M2F_ONE_XIAN,
		PT_CHAT_F2C_ONE_XIAN,

		// 区域
		// 同城
		PT_CHAT_C2F_ONE_CITY,
		PT_CHAT_F2A_ONE_CITY,
		PT_CHAT_A2M_ONE_CITY,
		PT_CHAT_M2F_ONE_CITY,
		PT_CHAT_F2C_ONE_CITY,
		// 同地图
		PT_CHAT_C2F_ONE_REGION,
		PT_CHAT_F2A_ONE_REGION,
		PT_CHAT_A2M_ONE_REGION,
		PT_CHAT_M2C_ONE_REGION,
		// 同视野
		PT_CHAT_C2F_ONE_VIEW,
		PT_CHAT_F2A_ONE_VIEW,
		PT_CHAT_A2M_ONE_VIEW,
		PT_CHAT_M2F_ONE_VIEW,
		PT_CHAT_F2C_ONE_VIEW,

		//@-----------关系聊天--------------
		// 两人
		PT_CHAT_C2F_TWO_PERSON,
		PT_CHAT_F2A_TWO_PERSON,
		//PT_CHAT_A2F_TWO_PERSON,
		PT_CHAT_A2C_TWO_PERSON,
		

		// 同队
		PT_CHAT_C2F_ONE_GROUP,
		PT_CHAT_F2A_ONE_GROUP,
		PT_CHAT_A2F_ONE_GROUP,
		PT_CHAT_F2C_ONE_GROUP,
		// 同盟
		PT_CHAT_C2F_ONE_ALLIANCE,
		PT_CHAT_F2A_ONE_ALLIANCE,
		PT_CHAT_A2F_ONE_ALLIANCE,
		PT_CHAT_F2C_ONE_ALLIANCE,		
		// 同势力
		PT_CHAT_C2F_ONE_FORCE,
		PT_CHAT_F2A_ONE_FORCE,
		PT_CHAT_A2F_ONE_FORCE,
		PT_CHAT_F2C_ONE_FORCE,
		// 其他-----------------------------------------
		// 全服
		PT_CHAT_C2F_FULL_SERVER,
		PT_CHAT_F2A_FULL_SERVER,
		//PT_CHAT_A2F_FULL_SERVER,
		PT_CHAT_A2C_FULL_SERVER,

		// 聊天结果 成功or失败
		PT_CHAT_A2F_RESULT,
		PT_CHAT_F2C_RESULT,
		PT_CHAT_M2C_RESULT,

	};

	//////////////////////////////////////////////////////////////////////////////////
	enum chat_result
	{
		chat_result_success,		//成功
		chat_result_unknown,
		chat_result_no_money,		//金钱不够
		chat_result_no_item,		//没有物品
		chat_result_lack_of_item,	//物品数量不够
		chat_result_no_permission,	//没有权限
		chat_result_level_limit,	//等级限制
		chat_result_friend_absence  //朋友不在线
	};
	//============================================================================
#pragma pack (push)
#pragma pack (1)
	//数据包结构
	//------------------------------------------------------------------------------
	// 2人聊天
	//------------------------------------------------------------------------------
	//**********************************************************************
	//@名字:        PT_CHAT_C2F_TWO_PERSON
	//@功能:        客户端向FrontServer两人聊天的消息
	//@备注:        ???
	//**********************************************************************/
	struct PT_CHAT_C2F_TWO_PERSON_DATA
	{
		Byte	channel;
		Char16	senderClanName[MAX_CLAN_NAME];
		Char16	recverClanName[MAX_CLAN_NAME];
		U16		dataSize;
		Char8	data[1];
	};
	struct PT_CHAT_C2F_TWO_PERSON_DATA_INFO
	{

		static Int  dataSize(PT_CHAT_C2F_TWO_PERSON_DATA* data)
		{ 
			static Int  headSize    = sizeof (PT_CHAT_C2F_TWO_PERSON_DATA) - sizeof( Char8 );
			static Int  charSize    = sizeof (Char8);

			return headSize + charSize * data->dataSize;
		};
	};
	class PT_CHAT_C2F_TWO_PERSON_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_CHAT_C2F_TWO_PERSON_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_CHAT;
			mType                               =   PT_CHAT_C2F_TWO_PERSON;
			//mBaseDataSize                       =   PT_CHAT_C2F_TWO_PERSON_DATA_INFO::dataSize ;

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

		virtual Bool checkDataValid( GameNetPacketData* data, I32 dataLen )
		{
			if ( data->channel != mChannel )
				return false;
			if ( data->type != mType )
				return false;
			if ( dataLen != PT_CHAT_C2F_TWO_PERSON_DATA_INFO::dataSize((PT_CHAT_C2F_TWO_PERSON_DATA*)data) )
				return false;
			return true;
		}
	};

	//------------------------------------------------------------------------------
	//**********************************************************************
	//@名字:        PT_CHAT_F2A_TWO_PERSON
	//@功能:        FrontServer向ChatServer两人聊天的消息
	//@备注:        ???
	//**********************************************************************/
	struct PT_CHAT_F2A_TWO_PERSON_DATA 
	{
		Byte	channel;
		Char16	senderClanName[MAX_CLAN_NAME];
		I32		senderNetIdInFront;
		Char16	recverClanName[MAX_CLAN_NAME];
		U16		dataSize;
		Char8	data[1];
	};
	struct PT_CHAT_F2A_TWO_PERSON_DATA_INFO
	{

		static Int  dataSize(PT_CHAT_F2A_TWO_PERSON_DATA* data)
		{ 
			static Int  headSize    = sizeof (PT_CHAT_F2A_TWO_PERSON_DATA) - sizeof( Char8 );
			static Int  charSize    = sizeof (Char8);

			return headSize + charSize * data->dataSize;
		};
	};

	class PT_CHAT_F2A_TWO_PERSON_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_CHAT_F2A_TWO_PERSON_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_CHAT;
			mType                               =   PT_CHAT_F2A_TWO_PERSON;
			//mBaseDataSize                       =   PT_CHAT_F2A_TWO_PERSON_DATA_INFO::dataSize ;

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
			if ( dataLen != PT_CHAT_F2A_TWO_PERSON_DATA_INFO::dataSize((PT_CHAT_F2A_TWO_PERSON_DATA*)data) )
				return false;
			return true;
		}
	};
	//------------------------------------------------------------------------------
	//**********************************************************************
	//@名字:        PT_CHAT_A2C_TWO_PERSON
	//@功能:        ChatServer向FrontServer转发给客户端的两人聊天的消息
	//@备注:        ???
	//**********************************************************************/
	struct PT_CHAT_A2C_TWO_PERSON_DATA 
	{
		Byte	channel;
		Char16	senderClanName[MAX_CLAN_NAME];
		U16		dataSize;
		Char8	data[1];
	};
	struct PT_CHAT_A2C_TWO_PERSON_DATA_INFO
	{

		static Int  dataSize(PT_CHAT_A2C_TWO_PERSON_DATA* data)
		{ 
			static Int  headSize    = sizeof (PT_CHAT_A2C_TWO_PERSON_DATA) - sizeof( Char8 );
			static Int  charSize    = sizeof (Char8);

			return headSize + charSize * data->dataSize;
		};
	};
	class PT_CHAT_A2C_TWO_PERSON_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_CHAT_A2C_TWO_PERSON_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_CHAT;
			mType                               =   PT_CHAT_A2C_TWO_PERSON;
			//mBaseDataSize                       =   PT_CHAT_F2A_TWO_PERSON_DATA_INFO::dataSize ;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_S2S2C;

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
			if ( dataLen != PT_CHAT_A2C_TWO_PERSON_DATA_INFO::dataSize((PT_CHAT_A2C_TWO_PERSON_DATA*)data) )
				return false;
			return true;
		}
	};
	//------------------------------------------------------------------------------
	// 同地图
	//------------------------------------------------------------------------------
	//**********************************************************************
	//@名字:        PT_CHAT_C2F_ONE_REGION
	//@功能:        Client向FrontServer发送的同地图聊天的消息
	//@备注:        ???
	//**********************************************************************/
	struct PT_CHAT_C2F_ONE_REGION_DATA
	{
		Byte	channel;
		Char16	senderClanName[MAX_CLAN_NAME];
		U32		regionId;
		U16		regionType;
		U16		dataSize;
		Char8	data[1];
	};
	struct PT_CHAT_C2F_ONE_REGION_DATA_INFO
	{
		static Int  dataSize(PT_CHAT_C2F_ONE_REGION_DATA* data)
		{ 
			static Int  headSize    = sizeof (PT_CHAT_C2F_ONE_REGION_DATA) - sizeof( Char8 );
			static Int  charSize    = sizeof (Char8);
			return headSize + charSize * data->dataSize;
		};
	};
	class PT_CHAT_C2F_ONE_REGION_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_CHAT_C2F_ONE_REGION_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_CHAT;
			mType                               =   PT_CHAT_C2F_ONE_REGION;
			//mBaseDataSize                       =   PT_CHAT_F2A_TWO_PERSON_DATA_INFO::dataSize ;

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

		virtual Bool checkDataValid( GameNetPacketData* data, I32 dataLen )
		{
			if ( data->channel != mChannel )
				return false;
			if ( data->type != mType )
				return false;
			if ( dataLen != PT_CHAT_C2F_ONE_REGION_DATA_INFO::dataSize((PT_CHAT_C2F_ONE_REGION_DATA*)data) )
				return false;
			return true;
		}
	};
	//-----------------------------------------------------------------------------
	//**********************************************************************
	//@名字:        PT_CHAT_F2A_ONE_REGION
	//@功能:        Client向FrontServer发送的同地图聊天的消息
	//@备注:        ???
	//**********************************************************************/
	struct PT_CHAT_F2A_ONE_REGION_DATA 
	{
		Byte	channel;
		Char16	senderClanName[MAX_CLAN_NAME];
		U32		regionId;
		U16		regionType;
		I32		senderNetIdInFrontServer;
		U32		mapServerId;
		U16		dataSize;
		Char8	data[1];
	};
	struct PT_CHAT_F2A_ONE_REGION_DATA_INFO
	{

		static Int  dataSize(PT_CHAT_F2A_ONE_REGION_DATA* data)
		{ 
			static Int  headSize    = sizeof (PT_CHAT_F2A_ONE_REGION_DATA) - sizeof( Char8 );
			static Int  charSize    = sizeof (Char8);
			return headSize + charSize * data->dataSize;
		};
	};
	class PT_CHAT_F2A_ONE_REGION_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_CHAT_F2A_ONE_REGION_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_CHAT;
			mType                               =   PT_CHAT_F2A_ONE_REGION;
			//mBaseDataSize                       =   PT_CHAT_F2A_TWO_PERSON_DATA_INFO::dataSize ;

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
			if ( dataLen != PT_CHAT_F2A_ONE_REGION_DATA_INFO::dataSize((PT_CHAT_F2A_ONE_REGION_DATA*)data) )
				return false;
			return true;
		}
	};
	//-----------------------------------------------------------------------------
	//**********************************************************************
	//@名字:        PT_CHAT_A2M_ONE_REGION
	//@功能:        ChatServer向MapServer发送的同地图聊天的消息
	//@备注:        ???
	//**********************************************************************/
	struct PT_CHAT_A2M_ONE_REGION_DATA 
	{
		Byte	channel;
		U64		accountId;
		Char16	senderClanName[MAX_CLAN_NAME];
		U32		regionId;
		U16		regionType;
		U16		dataSize;
		Char8	data[1];
	};
	struct PT_CHAT_A2M_ONE_REGION_DATA_INFO
	{
		static Int  dataSize(PT_CHAT_A2M_ONE_REGION_DATA* data)
		{ 
			static Int  headSize    = sizeof (PT_CHAT_A2M_ONE_REGION_DATA) - sizeof( Char8 );
			static Int  charSize    = sizeof (Char8);
			return headSize + charSize * data->dataSize;
		};
	};
	class PT_CHAT_A2M_ONE_REGION_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_CHAT_A2M_ONE_REGION_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_CHAT;
			mType                               =   PT_CHAT_A2M_ONE_REGION;
			//mBaseDataSize                       =   PT_CHAT_F2A_TWO_PERSON_DATA_INFO::dataSize ;

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
			if ( dataLen != PT_CHAT_A2M_ONE_REGION_DATA_INFO::dataSize((PT_CHAT_A2M_ONE_REGION_DATA*)data) )
				return false;
			return true;
		}
	};
	//-----------------------------------------------------------------------------
	//**********************************************************************
	//@名字:        PT_CHAT_M2C_ONE_REGION
	//@功能:        MapServer向FrontServer转发给Client的同地图聊天的消息
	//@备注:        ???
	//**********************************************************************/
	struct PT_CHAT_M2C_ONE_REGION_DATA 
	{
		Byte	channel;
		Char16	senderClanName[MAX_CLAN_NAME];
		U16		dataSize;
		Char8	data[1];
	};
	struct PT_CHAT_M2C_ONE_REGION_DATA_INFO
	{

		static Int  dataSize(PT_CHAT_M2C_ONE_REGION_DATA* data)
		{ 
			static Int  headSize    = sizeof (PT_CHAT_M2C_ONE_REGION_DATA) - sizeof( Char8 );
			static Int  charSize    = sizeof (Char8);
			return headSize + charSize * data->dataSize;
		};
	};
	class PT_CHAT_M2C_ONE_REGION_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_CHAT_M2C_ONE_REGION_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_CHAT;
			mType                               =   PT_CHAT_M2C_ONE_REGION;
			//mBaseDataSize                       =   PT_CHAT_F2A_TWO_PERSON_DATA_INFO::dataSize ;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_S2S2C;

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
			if ( dataLen != PT_CHAT_M2C_ONE_REGION_DATA_INFO::dataSize((PT_CHAT_M2C_ONE_REGION_DATA*)data) )
				return false;
			return true;
		}
	};
	//------------------------------------------------------------------------------
	// 全服聊天
	//------------------------------------------------------------------------------
	//**********************************************************************
	//@名字:        PT_CHAT_C2F_FULL_SERVER
	//@功能:        Client向FrontServer的全服聊天的消息
	//@备注:        ???
	//**********************************************************************/
    struct PT_CHAT_C2F_FULL_SERVER_DATA
	{
		Byte	channel;
		Char16	senderClanName[MAX_CLAN_NAME];
		U16		dataSize;
		Char8	data[1];

	};
	struct PT_CHAT_C2F_FULL_SERVER_DATA_INFO
	{
		static Int dataSize(PT_CHAT_C2F_FULL_SERVER_DATA* data)
		{
			 static Int headSize = sizeof(PT_CHAT_C2F_FULL_SERVER_DATA) - sizeof( Char8 );
             static Int  charSize    = sizeof (Char8);
             return headSize + charSize * data->dataSize;
		}

	};
	class PT_CHAT_C2F_FULL_SERVER_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_CHAT_C2F_FULL_SERVER_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_CHAT;
			mType                               =   PT_CHAT_C2F_FULL_SERVER;
			//mBaseDataSize                       =   PT_CHAT_F2A_TWO_PERSON_DATA_INFO::dataSize ;

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

		virtual Bool checkDataValid( GameNetPacketData* data, I32 dataLen )
		{
			if ( data->channel != mChannel )
				return false;
			if ( data->type != mType )
				return false;
			if ( dataLen != PT_CHAT_C2F_FULL_SERVER_DATA_INFO::dataSize((PT_CHAT_C2F_FULL_SERVER_DATA*)data) )
				return false;
			return true;
		}
	};
	//**********************************************************************
	//@名字:        PT_CHAT_F2A_FULL_SERVER
	//@功能:        FrontServer向ChatServer的全服聊天的消息
	//@备注:        ???
	//**********************************************************************/
	struct PT_CHAT_F2A_FULL_SERVER_DATA
	{
		Byte	channel;
		Char16	senderClanName[MAX_CLAN_NAME];
		I32		senderNetIdInFront;
		U16		dataSize;
		Char8	data[1];

	};
	struct PT_CHAT_F2A_FULL_SERVER_DATA_INFO
	{
		static Int dataSize(PT_CHAT_F2A_FULL_SERVER_DATA* data)
		{
			static Int headSize = sizeof(PT_CHAT_F2A_FULL_SERVER_DATA) - sizeof( Char8 );
			static Int  charSize    = sizeof (Char8);
			return headSize + charSize * data->dataSize;
			
		}

	};
	class PT_CHAT_F2A_FULL_SERVER_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_CHAT_F2A_FULL_SERVER_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_CHAT;
			mType                               =   PT_CHAT_F2A_FULL_SERVER;
			//mBaseDataSize                       =   PT_CHAT_F2A_FULL_SERVER_DATA_INFO::dataSize ;

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
			if ( dataLen != PT_CHAT_F2A_FULL_SERVER_DATA_INFO::dataSize((PT_CHAT_F2A_FULL_SERVER_DATA*)data) )
				return false;
			return true;
		}
	};
	//**********************************************************************
	//@名字:        PT_CHAT_A2C_FULL_SERVER
	//@功能:        FrontServer向ChatServer的转发给客户端全服聊天的消息
	//@备注:        ???
	//**********************************************************************/
	struct PT_CHAT_A2C_FULL_SERVER_DATA 
	{
		Byte	channel;
		Char16	senderClanName[MAX_CLAN_NAME];
		U16		dataSize;
		Char8	data[1];
	};
	struct PT_CHAT_A2C_FULL_SERVER_DATA_INFO
	{

		static Int  dataSize(PT_CHAT_A2C_FULL_SERVER_DATA* data)
		{ 
			static Int  headSize    = sizeof (PT_CHAT_A2C_FULL_SERVER_DATA) - sizeof( Char8 );
			static Int  charSize    = sizeof (Char8);

			return headSize + charSize * data->dataSize;
		};
	};
	class PT_CHAT_A2C_FULL_SERVER_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_CHAT_A2C_FULL_SERVER_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_CHAT;
			mType                               =   PT_CHAT_A2C_FULL_SERVER;
			//mBaseDataSize                       =   PT_CHAT_A2C_FULL_SERVER_DATA_INFO::dataSize ;

			mLevel                              =   GPL_LOGIC;
			mFlow                               =   GPFL_S2S2C;

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
			if ( dataLen != PT_CHAT_A2C_FULL_SERVER_DATA_INFO::dataSize((PT_CHAT_A2C_FULL_SERVER_DATA*)data) )
				return false;
			return true;
		}
	};
	//------------------------------------------------------------------------------
	// 聊天结果
	//------------------------------------------------------------------------------
	//**********************************************************************
	//@名字:       PT_CHAT_F2C_RESULT
	//@功能:       FrontServer向Client的聊天的结果
	//@备注:       ???
	//**********************************************************************/
	struct PT_CHAT_F2C_RESULT_DATA 
	{
		Byte	channel;
		Byte	result;
	};
	struct PT_CHAT_F2C_RESULT_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_CHAT_F2C_RESULT_DATA);
	};
	class PT_CHAT_F2C_RESULT_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_CHAT_F2C_RESULT_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_CHAT;
			mType                               =   PT_CHAT_F2C_RESULT;
			mBaseDataSize                       =   PT_CHAT_F2C_RESULT_DATA_INFO::dataSize ;

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
	//------------------------------------------------------------------------------
	//**********************************************************************
	//@名字:       PT_CHAT_A2F_RESULT
	//@功能:       CenterServer向FrontServer的聊天的结果
	//@备注:       ???
	//**********************************************************************/
	struct PT_CHAT_A2F_RESULT_DATA 
	{
		Byte	channel;
		I32		senderNetIdInFront;
		Byte	result;
	};
	struct PT_CHAT_A2F_RESULT_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_CHAT_A2F_RESULT_DATA);
	};
	class PT_CHAT_A2F_RESULT_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_CHAT_A2F_RESULT_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_CHAT;
			mType                               =   PT_CHAT_A2F_RESULT;
			mBaseDataSize                       =   PT_CHAT_A2F_RESULT_DATA_INFO::dataSize ;

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
    //============================================================================
	/*struct PT_CHAT_F2M_REGION_DATA
	{
		I32				channelId;
		IdType			genrealId;
		IdType			mapId;
		REGION_OBJ_TYPE	mapType;
		//Char16			senderClanName[MAX_CLAN_NAME];//氏族名称
		I32				chatDataSize;
		Char			chatData[1];
	};
    struct PT_CHAT_F2M_REGION_DATA_INFO
    {
        static Int  dataSize(PT_CHAT_F2M_REGION_DATA* data)
        { 
            static Int  headSize        = sizeof (PT_CHAT_F2M_REGION_DATA) - sizeof( Char );
            static Int  charSize    = sizeof (Char);

            return headSize + charSize * data->chatDataSize;
        };
    };

    //////////////////////////////////////////////////////////////////////////////////
	struct PT_CHAT_M2C_REGION_DATA
	{
		I32		channelId;
		Char16	senderClanName[MAX_CLAN_NAME];//氏族名称 暂时用主将名
		I32		chatDataSize;
		Char	chatData[1];
	};
    struct PT_CHAT_M2C_REGION_DATA_INFO
    {
        static const Int dataSize = sizeof(PT_CHAT_M2C_REGION_DATA);
    };*/

   //-----------------------------------------------------------------------------------------
	#pragma pack (pop)
}
#endif
