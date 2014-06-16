//************************************************************************************************
#ifndef _H_BUFFNETPACKET_
#define _H_BUFFNETPACKET_
//************************************************************************************************
#include "CommonGameDefine.h"
#include "NetDefine.h"
#include "GameNetPacket.h"
//************************************************************************************************
namespace MG
{
	/**********************************************************************
	//@负责人:      徐开超
	//@协助人:      ???
	**********************************************************************/

	/******************************************************************************/
	//游戏属性包类型
	/******************************************************************************/
	enum BuffNetPacketType
	{
		PT_BUFF_UNKNOW = 0,

		PT_BUFF_F2M_PLAYERCHARACTER_BUFFDATA_LIST,				//frontServer从DB发送给MapServer
		PT_BUFF_M2F_PLAYERCHARACTER_BUFFDATA,					//MapServer发给frontServer更新DB
		PT_BUFF_M2C_PLAYERCHARACTER_BUFFDATA_LIST,				//MapServer同步给给客户端
		PT_BUFF_M2C_PLAYERCHARACTER_BUFFDATA,					//MapServer同步给给客户端
	
	};

#pragma pack (push)
#pragma pack (1)

	///数据包声明
	//**********************************************************************
	struct netBuffData 
	{
		Int timeUse;			//状态的使用时间
		Int curAddNum;			//状态的叠加层次
		Int buffId;				//状态的Id
	};
	struct netBuffInfoData 
	{
		static const Int dataSize = sizeof (netBuffData);
	};

	//**********************************************************************
	//@名字:        PT_BUFF_M2F_PLAYERCHARACTER_BUFFDATA
	//@功能:        mapServer向frontServer发送更新buff的消息
	//@备注:        通知frontServer更新DB
	//**********************************************************************/
	//----------------------------------------------------------------
	struct PT_BUFF_M2F_PLAYERCHARACTER_BUFFDATA_Data
	{
		U64			acountId;		//玩家账号ID
		U64			dbId;			//玩家下的武将角色ID
		netBuffData	buffdatalist;	//buffdata
	};
	struct PT_BUFF_M2F_PLAYERCHARACTER_BUFFDATA_INFO_Data
	{
		static const Int dataSize = sizeof (PT_BUFF_M2F_PLAYERCHARACTER_BUFFDATA_Data);
	};
	class PT_BUFF_M2F_PLAYERCHARACTER_BUFFDATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_BUFF_M2F_PLAYERCHARACTER_BUFFDATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_BUFF;
			mType                               =   PT_BUFF_M2F_PLAYERCHARACTER_BUFFDATA;
			mBaseDataSize                       =   PT_BUFF_M2F_PLAYERCHARACTER_BUFFDATA_INFO_Data::dataSize ;

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
	//--------------------------------------------------------------
	//**********************************************************************
	//@名字:        PT_BUFF_M2C_PLAYERCHARACTER_BUFFDATA
	//@功能:        mapServer向客户端同步新加的buff。
	//@备注:        
	//**********************************************************************/
	typedef PT_BUFF_M2F_PLAYERCHARACTER_BUFFDATA_Data			PT_BUFF_M2C_PLAYERCHARACTER_BUFFDATA_Data;
	typedef PT_BUFF_M2F_PLAYERCHARACTER_BUFFDATA_INFO_Data		PT_BUFF_M2C_PLAYERCHARACTER_BUFFDATA_INFO_Data;
	//--------------------------------------------------------------
	class PT_BUFF_M2C_PLAYERCHARACTER_BUFFDATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_BUFF_M2C_PLAYERCHARACTER_BUFFDATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_BUFF;
			mType                               =   PT_BUFF_M2C_PLAYERCHARACTER_BUFFDATA;
			mBaseDataSize                       =   PT_BUFF_M2C_PLAYERCHARACTER_BUFFDATA_INFO_Data::dataSize ;

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
	//--------------------------------------------------------------
	//**********************************************************************
	//@名字:        PT_BUFF_F2M_PLAYERCHARACTER_BUFFDATA_LIST
	//@功能:        frontServer向mapServer发送buff列表
	//@备注:        发送从DB中读取的buff列表
	//**********************************************************************/
	struct PT_BUFF_F2M_PLAYERCHARACTER_BUFFDATA_LIST_Data 
	{
		U64			dbId;					//武将的DBID
		UInt		ncount;					//buff的个数
		netBuffData	buffdatalist[1];		//buff列表信息
	};
	struct  PT_BUFF_F2M_PLAYERCHARACTER_BUFFDATA_LIST_INFO_Data
	{
		static const Int dataSize = sizeof (PT_BUFF_F2M_PLAYERCHARACTER_BUFFDATA_LIST_Data);
	};
	class PT_BUFF_F2M_PLAYERCHARACTER_BUFFDATA_LIST_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_BUFF_F2M_PLAYERCHARACTER_BUFFDATA_LIST_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_BUFF;
			mType                               =   PT_BUFF_F2M_PLAYERCHARACTER_BUFFDATA_LIST;
			mBaseDataSize                       =   PT_BUFF_F2M_PLAYERCHARACTER_BUFFDATA_LIST_INFO_Data::dataSize ;

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
	//--------------------------------------------------------------
	//**********************************************************************
	//@名字:        PT_BUFF_M2C_PLAYERCHARACTER_BUFFDATA_LIST
	//@功能:        mapServerr向客户端同步buff列表
	//@备注:        
	//**********************************************************************/
	typedef PT_BUFF_F2M_PLAYERCHARACTER_BUFFDATA_LIST_Data			PT_BUFF_M2C_PLAYERCHARACTER_BUFFDATA_LIST_Data;
	typedef PT_BUFF_F2M_PLAYERCHARACTER_BUFFDATA_LIST_INFO_Data		PT_BUFF_M2C_PLAYERCHARACTER_BUFFDATA_LIST_INFO_Data;
	//--------------------------------------------------------------
	class PT_BUFF_M2C_PLAYERCHARACTER_BUFFDATA_LIST_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_BUFF_M2C_PLAYERCHARACTER_BUFFDATA_LIST_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_BUFF;
			mType                               =   PT_BUFF_M2C_PLAYERCHARACTER_BUFFDATA_LIST;
			mBaseDataSize                       =   PT_BUFF_M2C_PLAYERCHARACTER_BUFFDATA_LIST_INFO_Data::dataSize ;

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
	
#pragma pack (pop)
}
//************************************************************************************************
#endif
//************************************************************************************************