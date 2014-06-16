/******************************************************************************/
#ifndef _CAMPAIGNNETPACKET_H_
#define _CAMPAIGNNETPACKET_H_
/******************************************************************************/
#include "CommonGameDefine.h"
#include "NetDefine.h"
#include "GameNetPacket.h"
/******************************************************************************/

namespace MG
{
	/******************************************************************************/
	//据点数据包想关类型
	/******************************************************************************/
	enum CampaignNetPacket
	{
		PT_CAMPAIGN_UNKNOW = 0,				//											code	test

		PT_CAMPAIGN_C2F_CAMPAIGN_LIST,			//所有战役的列表							【新版本 2012.5.22】
		PT_CAMPAIGN_F2T_CAMPAIGN_LIST,
		PT_CAMPAIGN_T2C_CAMPAIGN_LIST_BEGIN,
		PT_CAMPAIGN_T2C_CAMPAIGN_LIST,
		PT_CAMPAIGN_T2C_CAMPAIGN_LIST_END,
		
		PT_CAMPAIGN_C2F_CREATE,					//发起战斗请求								【新版本 2012.5.22】
		PT_CAMPAIGN_F2T_CREATE,
		PT_CAMPAIGN_T2C_CREATE,					//广播给区域的人新增一个战斗				【新版本 2012.5.22】

		
		PT_CAMPAIGN_C2F_ENTER_ATTACK,			//进入房间									【新版本 2012.5.22】
		PT_CAMPAIGN_F2T_ENTER_ATTACK,
		PT_CAMPAIGN_T2F_ENTER_ATTACK,
		PT_CAMPAIGN_F2C_ENTER_ATTACK,

		PT_CAMPAIGN_C2F_ENTER_DEFENSE,			//加入防守方
		PT_CAMPAIGN_F2T_ENTER_DEFENSE,
		PT_CAMPAIGN_T2F_ENTER_DEFENSE,			//广播给所有的防守方 ， 修改对应内存
		PT_CAMPAIGN_F2C_ENTER_DEFENSE,

		PT_CAMPAIGN_T2C_CAMPAIGN_INFO,			//给防守方 发送房间信息， 以便在客户端创建一份


		PT_CAMPAIGN_T2F_MEMBER_LIST,
		PT_CAMPAIGN_F2C_MEMBER_LIST,			//房间内玩家的信息 返回给新玩家			//【新版本 2012.6.18】
		
		PT_CAMPAIGN_C2F_READY_MYSELF,			//准备状况									ok		ok
		PT_CAMPAIGN_F2T_READY_MYSELF,			//											ok		ok
		PT_CAMPAIGN_T2C_READY_MYSELF,			//需要广播

		PT_CAMPAIGN_C2F_LEAVE,					//玩家离开房间
		PT_CAMPAIGN_F2T_LEAVE,
		PT_CAMPAIGN_T2C_LEAVE,

		PT_CAMPAIGN_C2F_LEAVE_IN_CAMPAIGN,		//战斗中离开
		PT_CAMPAIGN_F2T_LEAVE_IN_CAMPAIGN,		//
		PT_CAMPAIGN_T2F_LEAVE_IN_CAMPAIGN,		//
		PT_CAMPAIGN_F2C_LEAVE_IN_CAMPAIGN,		//

		PT_CAMPAIGN_T2C_DESTROY,				//房主离开， 摧毁房间

		PT_CAMPAIGN_C2F_START,					//开始战斗											【新版本 2012.5.22】
		PT_CAMPAIGN_F2T_START,					//													【新版本 2012.5.22】
		PT_CAMPAIGN_T2F_START,
		PT_CAMPAIGN_F2M_START,					//MapServer 创建一个 攻城副本
		PT_CAMPAIGN_M2T_START_NEW_INSTANCE,		//攻城副本信息 返回给CenterServer， 并准备跳转地图
		PT_CAMPAIGN_T2F_START_JUMP_REGION,		//根据副本信息 跳转到相应的地图						【新版本 2012.5.22】
		
		PT_CAMPAIGN_T2C_START_NEW_CAMPAIGN,		//广播给所有的客户端

		PT_CAMPAIGN_T2M_INVITE_DEFENSE_REGION,
		PT_CAMPAIGN_M2C_INVITE_DEFENSE_REGION,
		
		PT_CAMPAIGN_C2F_END_MANUAL,				//手动结束 战斗，  ChinaJoy版本用
		PT_CAMPAIGN_F2T_END_MANUAL,

		PT_CAMPAIGN_T2F_END,					//战斗结束, 通知FrontServer 将区域的战斗ID 设置为0
		PT_CAMPAIGN_F2M_END,
		PT_CAMPAIGN_M2C_END,

		PT_CAMPAIGN_C2F_END_SCORE,				//离开结算界面

		PT_CAMPAIGN_T2C_ERROR,					//战斗相关错误信息

		PT_CAMPAIGN_C2F_CHANGE_CAMP_CONTROL,	//控制兵营的控制权
		PT_CAMPAIGN_F2T_CHANGE_CAMP_CONTROL,
		PT_CAMPAIGN_T2F_CHANGE_CAMP_CONTROL,			
		PT_CAMPAIGN_F2M_CHANGE_CAMP_CONTROL,
		PT_CAMPAIGN_M2C_CHANGE_CAMP_CONTROL,
		PT_CAMPAIGN_M2C_CHANGE_TROOP_CONTROL,	//军队的控制权也要跟着改变

		PT_CAMPAIGN_C2F_TROOP_CONTROLLER_LIST,
		PT_CAMPAIGN_F2T_TROOP_CONTROLLER_LIST,
		PT_CAMPAIGN_T2F_TROOP_CONTROLLER_LIST,
		PT_CAMPAIGN_F2M_TROOP_CONTROLLER_LIST,
		PT_CAMPAIGN_M2C_TROOP_CONTROLLER_LIST,


		PT_CAMPAIGN_T2F_CREATE_CAMP_BY_CONTROLER,		//创建军营， 一次性创建多个
		PT_CAMPAIGN_F2M_CREATE_CAMP_BY_CONTROLER,

		PT_CAMPAIGN_F2T_DISCONNECT,						//玩家掉线 离开战场


		PT_CAMPAIGN_T2F_CHANGE_CAMP_OWNER,				//改变军营的创建者
		PT_CAMPAIGN_F2M_CHANGE_CAMP_OWNER,
		PT_CAMPAIGN_M2C_CHANGE_CAMP_OWNER,

		PT_CAMPAIGN_M2T_MAIN_CAMP_DESTROY,				//主兵营摧毁， 战斗结束


	};

#pragma pack (push)
#pragma pack (1)
	
	//战斗相关错误信息
	enum CAMPAIGN_ERROR
	{
		REGION_ID_ERROR				= 0,				//错误的区域ID
		REGION_BELONG_ID_ERROR		= 1,				//所属区域的ID错误
		CAMPAIGN_ID_ERROR			= 2,				//战斗ID 错误
		REGION_HAS_CAMPAIGM			= 3,				//该区域已经有战斗
		NO_RIGHT					= 4,				//没有权限操作
		CREATOR_ENTER_FAIL			= 5,				//创建者直接进入准备状态 失败
		CREATE_FAIL					= 6,				//创建战斗失败
		CAMPAIGN_ENTER_FAIL			= 7,				//进入房间失败
		CAMPAIGN_JOIN_FAIL			= 8,				//从大厅列表进入战斗列表失败
		CAMPAIGN_READY_CONFIRM_FAIL	= 9,				//设置准备状态失败
		CAMPAIGN_JOIN_WAITING_FAIL	= 10,				//从战斗状态转到等待大厅失败
		CAMPAIGN_KICK_FAIL			= 11,				//踢人失败
		CAMPAIGN_START_FAIL			= 12,				//开始战斗失败

		CAMPAIGN_ENTER_FULL,							//满人
		CAMPAIGN_LEAVE_FAIL,
	};

	////////////////////////////////////////////////////////////////////////////////
	struct NetCampainInfo
	{
		AccountIdType		accountId;
		CampaignIdType		campaignId;
		RegionIdType		targetRegionId;
		Byte				targetRegionType;
		ClanIdType			creatorClanId;
		U32					charArtIcon;
		Char16				creatorPlayerCharacterName[MAX_CHARACTER_NAME_LEN];
		Char16				creatorClanName[MAX_CLAN_NAME];
		Char16				campaignName[MAX_CAMPAIGN_NAME];

		Int					memberNum;				//房间里的人数
	};

	//////////////////////////////////////////////////////////////////////////////////
	struct NetCampaignMemberInfo
	{
		AccountIdType			accountId;
		ClanIdType				clanId;
		PlayerCharacterIdType	playerCharacterId;
		Char16					playerCharacterName[MAX_CHARACTER_NAME_LEN];
		Byte					position;
		Byte					readyState;				//是否准备
		Bool					isHost;					//0. 一般会员， 1. 房主

		Int						level;
		U32						charArtIcon;
		Int						hp;
		Int						mp;
	};

	//////////////////////////////////////////////////////////////////////////////////
	struct NetTroopChangeControlInfo
	{
		TroopIdType troopId;
	};

	//////////////////////////////////////////////////////////////////////////////////
	struct NetTroopControllerInfo
	{
		AccountIdType			accountId;
		Int						templateId;
		U32						charArtIcon;
		PlayerCharacterIdType	playerCharacterId;
		Char16					playerCharacterName[MAX_CHARACTER_NAME_LEN];
	};

	//////////////////////////////////////////////////////////////////////////////////
	struct NetAddCampaignEnd
	{
		//战斗结束 发送战斗统计信息
		Byte	force;						//势力
		Char16	playerCharacterName[MAX_CHARACTER_NAME_LEN];	//将领名字
		Int		killGeneralPoint;			//击破敌将数
		Int		killArmyPoint;				//击破军队数
		Int		destoryForcePoint;			//击破重要据点数
		Int		constructBuild;				//建造设施
		Int		healGeneralPoint;			//治疗武将总量
		Int		deathPoint;					//死亡次数
		Int		battleAchievement;			//战役功绩
		Int		RankList;					//战役评价
	};

	//////////////////////////////////////////////////////////////////////////////////
	struct NetCampInfo
	{
		Int troopNum;
		Int campHp;
	};


	////////////////////////////////////////////////////////////////////////////////
	struct NetAddForceInfo
	{
		//战斗结束 根据势力计算 总数
		Byte			force;
		RegionIdType	regionId;
		//Int				generalNum;		//武将的总量
		Int				troopNum;		//军队的总量
	};

	/**********************************************************************
    //@名字:        PT_CAMPAIGN_C2F_CAMPAIGN_LIST
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	//所有战役的列表
	struct PT_CAMPAIGN_C2F_CAMPAIGN_LIST_DATA
	{
	};

	struct PT_CAMPAIGN_C2F_CAMPAIGN_LIST_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_C2F_CAMPAIGN_LIST_DATA);
	};

	class PT_CAMPAIGN_C2F_CAMPAIGN_LIST_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_C2F_CAMPAIGN_LIST_DATA_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_C2F_CAMPAIGN_LIST;
            mBaseDataSize                       =   PT_CAMPAIGN_C2F_CAMPAIGN_LIST_INFO::dataSize ;

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

	////所有战役的列表
	//struct PT_CAMPAIGN_C2F_CAMPAIGN_LIST_DATA
	//{
	//};
	//struct PT_CAMPAIGN_C2F_CAMPAIGN_LIST_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_C2F_CAMPAIGN_LIST_DATA);
	//};

	//////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
    //@名字:        PT_CAMPAIGN_F2T_CAMPAIGN_LIST
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_F2T_CAMPAIGN_LIST_DATA
	{
		NetIdType		clientNetId;
		AccountIdType	accountId;
	};
	struct PT_CAMPAIGN_F2T_CAMPAIGN_LIST_INFO
	{
		static Int const  dataSize = sizeof(PT_CAMPAIGN_F2T_CAMPAIGN_LIST_DATA);
	};

	class PT_CAMPAIGN_F2T_CAMPAIGN_LIST_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_F2T_CAMPAIGN_LIST_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_F2T_CAMPAIGN_LIST;
            mBaseDataSize                       =   PT_CAMPAIGN_F2T_CAMPAIGN_LIST_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_F2T_CAMPAIGN_LIST_DATA
	//{
	//	NetIdType		clientNetId;
	//	AccountIdType	accountId;
	//};
	//struct PT_CAMPAIGN_F2T_CAMPAIGN_LIST_DATA_INFO
	//{
	//	static Int const  dataSize = sizeof(PT_CAMPAIGN_F2T_CAMPAIGN_LIST_DATA);
	//};

	//////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
    //@名字:        PT_CAMPAIGN_T2C_CAMPAIGN_LIST_BEGIN
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_T2C_CAMPAIGN_LIST_BEGIN_DATA
	{

	};

	struct PT_CAMPAIGN_T2C_CAMPAIGN_LIST_BEGIN_INFO
	{
		static Int const  dataSize = sizeof(PT_CAMPAIGN_T2C_CAMPAIGN_LIST_BEGIN_DATA);
	};

	class PT_CAMPAIGN_T2C_CAMPAIGN_LIST_BEGIN_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_T2C_CAMPAIGN_LIST_BEGIN_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_T2C_CAMPAIGN_LIST_BEGIN;
            mBaseDataSize                       =   PT_CAMPAIGN_T2C_CAMPAIGN_LIST_BEGIN_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_T2C_CAMPAIGN_LIST_BEGIN_DATA
	//{

	//};
	//struct PT_CAMPAIGN_T2C_CAMPAIGN_LIST_BEGIN_DATA_INFO
	//{
	//	static Int const  dataSize = sizeof(PT_CAMPAIGN_T2C_CAMPAIGN_LIST_BEGIN_DATA);
	//};


	//////////////////////////////////////////////////////////////////////////////////
	struct PT_CAMPAIGN_T2C_CAMPAIGN_LIST_DATA
	{
		NetIdType		clientNetId;
		Int				addCampainNum;
		NetCampainInfo	addCampainInfo[1];	//创建者的信息和房间里成员列表
	};

	struct PT_CAMPAIGN_T2C_CAMPAIGN_LIST_DATA_INFO
	{
		static Int const 	netAddCampainInfoSize = sizeof (NetCampainInfo);
		static Int const 	headSize = sizeof (PT_CAMPAIGN_T2C_CAMPAIGN_LIST_DATA) - sizeof( NetCampainInfo );
		static Int       	dataSize(PT_CAMPAIGN_T2C_CAMPAIGN_LIST_DATA* data)
		{ 
			return PT_CAMPAIGN_T2C_CAMPAIGN_LIST_DATA_INFO::headSize + PT_CAMPAIGN_T2C_CAMPAIGN_LIST_DATA_INFO::netAddCampainInfoSize * data->addCampainNum;
		};
	};

	//////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
    //@名字:        PT_CAMPAIGN_T2C_CAMPAIGN_LIST_END
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_T2C_CAMPAIGN_LIST_END_DATA
	{

	};

	struct PT_CAMPAIGN_T2C_CAMPAIGN_LIST_END_INFO
	{
		static Int const  dataSize = sizeof(PT_CAMPAIGN_T2C_CAMPAIGN_LIST_END_DATA);
	};

	class PT_CAMPAIGN_T2C_CAMPAIGN_LIST_END_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_T2C_CAMPAIGN_LIST_END_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_T2C_CAMPAIGN_LIST_END;
            mBaseDataSize                       =   PT_CAMPAIGN_T2C_CAMPAIGN_LIST_END_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_T2C_CAMPAIGN_LIST_END_DATA
	//{

	//};
	//struct PT_CAMPAIGN_T2C_CAMPAIGN_LIST_END_DATA_INFO
	//{
	//	static Int const  dataSize = sizeof(PT_CAMPAIGN_T2C_CAMPAIGN_LIST_END_DATA);
	//};

	//////////////////////////////////////////////////////////////////////////////////

	/**********************************************************************
    //@名字:        PT_CAMPAIGN_C2F_CREATE
    //@功能:        发起战斗请求
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	//发起战斗请求
	struct PT_CAMPAIGN_C2F_CREATE_DATA
	{
		ClanIdType		creatorClanId;						//战斗创建者
		Char16			campaignName[MAX_CAMPAIGN_NAME];	//战斗的名字

		RegionIdType	targetRegionId;						//攻击目标
		Byte			targetRegionType;
	};

	struct PT_CAMPAIGN_C2F_CREATE_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_C2F_CREATE_DATA);
	};

	class PT_CAMPAIGN_C2F_CREATE_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_C2F_CREATE_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_C2F_CREATE;
            mBaseDataSize                       =   PT_CAMPAIGN_C2F_CREATE_INFO::dataSize ;

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

	////发起战斗请求
	//struct PT_CAMPAIGN_C2F_CREATE_DATA
	//{
	//	ClanIdType		creatorClanId;						//战斗创建者
	//	Char16			campaignName[MAX_CAMPAIGN_NAME];	//战斗的名字
	//	
	//	RegionIdType	targetRegionId;						//攻击目标
	//	Byte			targetRegionType;
	//};
 //   struct PT_CAMPAIGN_C2F_CREATE_DATA_INFO
 //   {
 //       static const Int dataSize = sizeof(PT_CAMPAIGN_C2F_CREATE_DATA);
 //   };

	//////////////////////////////////////////////////////////////////////////////////

	/**********************************************************************
    //@名字:        PT_CAMPAIGN_F2T_CREATE
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_F2T_CREATE_DATA
	{
		U64						accountId;
		NetIdType				clientNetId;
		ClanIdType				creatorClanId;						//战斗创建者
		Char16					creatorClanName[MAX_CLAN_NAME];
		PlayerCharacterIdType	creatorPlayerCharacterId;
		U32						charArtIcon;
		Char16					creatorPlayerCharacterName[MAX_CHARACTER_NAME_LEN];
		RegionIdType			targetRegionId;						//攻击目标
		Byte					targetRegionType;
		Char16					campaignName[MAX_CAMPAIGN_NAME];	//战斗的名字
	};

	struct PT_CAMPAIGN_F2T_CREATE_INFO
	{
		static Int const  dataSize = sizeof(PT_CAMPAIGN_F2T_CREATE_DATA);
	};

	class PT_CAMPAIGN_F2T_CREATE_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_F2T_CREATE_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_F2T_CREATE;
            mBaseDataSize                       =   PT_CAMPAIGN_F2T_CREATE_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_F2T_CREATE_DATA
	//{
	//	U64						accountId;
	//	NetIdType				clientNetId;
	//	ClanIdType				creatorClanId;						//战斗创建者
	//	Char16					creatorClanName[MAX_CLAN_NAME];
	//	PlayerCharacterIdType	creatorPlayerCharacterId;
	//	U32						charArtIcon;
	//	Char16					creatorPlayerCharacterName[MAX_CHARACTER_NAME_LEN];
	//	RegionIdType			targetRegionId;						//攻击目标
	//	Byte					targetRegionType;
	//	Char16					campaignName[MAX_CAMPAIGN_NAME];	//战斗的名字
	//};
	//struct PT_CAMPAIGN_F2T_CREATE_DATA_INFO
	//{
	//	static Int const  dataSize = sizeof(PT_CAMPAIGN_F2T_CREATE_DATA);
	//};
	//////////////////////////////////////////////////////////////////////////////////

	/**********************************************************************
    //@名字:        PT_CAMPAIGN_T2C_CREATE
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct	PT_CAMPAIGN_T2C_CREATE_DATA
	{
		NetCampainInfo	campaignInfo;

	};

	struct PT_CAMPAIGN_T2C_CREATE_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_T2C_CREATE_DATA);
	};


	class PT_CAMPAIGN_T2C_CREATE_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_T2C_CREATE_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_T2C_CREATE;
            mBaseDataSize                       =   PT_CAMPAIGN_T2C_CREATE_INFO::dataSize ;

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


    //////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
    //@名字:        PT_CAMPAIGN_C2F_ENTER_ATTACK
    //@功能:        进入房间，但并为加入
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	//进入房间，但并为加入
	struct PT_CAMPAIGN_C2F_ENTER_ATTACK_DATA
	{
		ClanIdType			myClanId;
		CampaignIdType		campaignId;
	};
	struct PT_CAMPAIGN_C2F_ENTER_ATTACK_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_C2F_ENTER_ATTACK_DATA);
	};

	class PT_CAMPAIGN_C2F_ENTER_ATTACK_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_C2F_ENTER_ATTACK_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_C2F_ENTER_ATTACK;
            mBaseDataSize                       =   PT_CAMPAIGN_C2F_ENTER_ATTACK_INFO::dataSize ;

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

	////进入房间，但并为加入
	//struct PT_CAMPAIGN_C2F_ENTER_ATTACK_DATA
	//{
	//	ClanIdType			myClanId;
	//	CampaignIdType		campaignId;
	//};
 //   struct PT_CAMPAIGN_C2F_ENTER_ATTACK_DATA_INFO
 //   {
 //       static const Int dataSize = sizeof(PT_CAMPAIGN_C2F_ENTER_ATTACK_DATA);
 //   };

	//////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
    //@名字:        PT_CAMPAIGN_F2T_ENTER_ATTACK
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	//进入房间，但并为加入
	struct PT_CAMPAIGN_F2T_ENTER_ATTACK_DATA
	{
		NetIdType				clientNetId;
		AccountIdType			accountId;
		CampaignIdType			campaignId;
		ClanIdType				myClanId;
		Char16					myClanName[MAX_CLAN_NAME];
		PlayerCharacterIdType	myPlayerCharacterId;
		U32						charArtIcon;
		Char16					myPlayerCharacterName[MAX_CHARACTER_NAME_LEN];
	};
	struct PT_CAMPAIGN_F2T_ENTER_ATTACK_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_F2T_ENTER_ATTACK_DATA);
	};

	class PT_CAMPAIGN_F2T_ENTER_ATTACK_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_F2T_ENTER_ATTACK_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_F2T_ENTER_ATTACK;
            mBaseDataSize                       =   PT_CAMPAIGN_F2T_ENTER_ATTACK_INFO::dataSize ;

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

	////进入房间，但并为加入
	//struct PT_CAMPAIGN_F2T_ENTER_ATTACK_DATA
	//{
	//	NetIdType				clientNetId;
	//	AccountIdType			accountId;
	//	CampaignIdType			campaignId;
	//	ClanIdType				myClanId;
	//	Char16					myClanName[MAX_CLAN_NAME];
	//	PlayerCharacterIdType	myPlayerCharacterId;
	//	U32						charArtIcon;
	//	Char16					myPlayerCharacterName[MAX_CHARACTER_NAME_LEN];
	//};
	//struct PT_CAMPAIGN_F2T_ENTER_ATTACK_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_F2T_ENTER_ATTACK_DATA);
	//};

	//////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
    //@名字:        PT_CAMPAIGN_T2F_ENTER_ATTACK
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	//进入房间，但并为加入
	struct PT_CAMPAIGN_T2F_ENTER_ATTACK_DATA
	{
		AccountIdType			toPlayerAccount;			//发给哪个玩家
		CampaignIdType			campaignId;
		RegionIdType			targetRegionId;
		NetCampaignMemberInfo	newMember;
	};

	struct PT_CAMPAIGN_T2F_ENTER_ATTACK_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_T2F_ENTER_ATTACK_DATA);
	};

	class PT_CAMPAIGN_T2F_ENTER_ATTACK_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_T2F_ENTER_ATTACK_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_T2F_ENTER_ATTACK;
            mBaseDataSize                       =   PT_CAMPAIGN_T2F_ENTER_ATTACK_INFO::dataSize ;

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

	////进入房间，但并为加入
	//struct PT_CAMPAIGN_T2F_ENTER_ATTACK_DATA
	//{
	//	AccountIdType			toPlayerAccount;			//发给哪个玩家
	//	CampaignIdType			campaignId;
	//	RegionIdType			targetRegionId;
	//	NetCampaignMemberInfo	newMember;
	//};
	//struct PT_CAMPAIGN_T2F_ENTER_ATTACK_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_T2F_ENTER_ATTACK_DATA);
	//};

	//////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
    //@名字:        PT_CAMPAIGN_F2C_ENTER_ATTACK
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	//进入房间，但并为加入
	struct PT_CAMPAIGN_F2C_ENTER_ATTACK_DATA
	{
		CampaignIdType			campaignId;
		RegionIdType			targetRegionId;
		NetCampaignMemberInfo	newMember;
	};
	struct PT_CAMPAIGN_F2C_ENTER_ATTACK_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_F2C_ENTER_ATTACK_DATA);
	};

	class PT_CAMPAIGN_F2C_ENTER_ATTACK_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_F2C_ENTER_ATTACK_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_F2C_ENTER_ATTACK;
            mBaseDataSize                       =   PT_CAMPAIGN_F2C_ENTER_ATTACK_INFO::dataSize ;

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

	////进入房间，但并为加入
	//struct PT_CAMPAIGN_F2C_ENTER_ATTACK_DATA
	//{
	//	CampaignIdType			campaignId;
	//	RegionIdType			targetRegionId;
	//	NetCampaignMemberInfo	newMember;
	//};
	//struct PT_CAMPAIGN_F2C_ENTER_ATTACK_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_F2C_ENTER_ATTACK_DATA);
	//};


	//////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
    //@名字:        PT_CAMPAIGN_C2F_ENTER_DEFENSE
    //@功能:        加入防守方
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	//加入防守方
	struct PT_CAMPAIGN_C2F_ENTER_DEFENSE_DATA
	{
		ClanIdType			myClanId;
		CampaignIdType		campaignId;
	};

	struct PT_CAMPAIGN_C2F_ENTER_DEFENSE_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_C2F_ENTER_DEFENSE_DATA);
	};

	class PT_CAMPAIGN_C2F_ENTER_DEFENSE_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_C2F_ENTER_DEFENSE_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_C2F_ENTER_DEFENSE;
            mBaseDataSize                       =   PT_CAMPAIGN_C2F_ENTER_DEFENSE_INFO::dataSize ;

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

	////进入房间，加入防守方
	//struct PT_CAMPAIGN_C2F_ENTER_DEFENSE_DATA
	//{
	//	ClanIdType			myClanId;
	//	CampaignIdType		campaignId;
	//};

	//struct PT_CAMPAIGN_C2F_ENTER_DEFENSE_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_C2F_ENTER_DEFENSE_DATA);
	//};
	
	//////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
    //@名字:        PT_CAMPAIGN_F2T_ENTER_DEFENSE
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_F2T_ENTER_DEFENSE_DATA
	{
		NetIdType				clientNetId;
		AccountIdType			accountId;
		CampaignIdType			campaignId;
		ClanIdType				myClanId;
		Char16					myClanName[MAX_CLAN_NAME];
		PlayerCharacterIdType	myPlayerCharacterId;
		U32						charArtIcon;
		Char16					myPlayerCharacterName[MAX_CHARACTER_NAME_LEN];
	};

	struct PT_CAMPAIGN_F2T_ENTER_DEFENSE_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_F2T_ENTER_DEFENSE_DATA);
	};

	class PT_CAMPAIGN_F2T_ENTER_DEFENSE_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_F2T_ENTER_DEFENSE_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_F2T_ENTER_DEFENSE;
            mBaseDataSize                       =   PT_CAMPAIGN_F2T_ENTER_DEFENSE_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_F2T_ENTER_DEFENSE_DATA
	//{
	//	NetIdType				clientNetId;
	//	AccountIdType			accountId;
	//	CampaignIdType			campaignId;
	//	ClanIdType				myClanId;
	//	Char16					myClanName[MAX_CLAN_NAME];
	//	PlayerCharacterIdType	myPlayerCharacterId;
	//	U32						charArtIcon;
	//	Char16					myPlayerCharacterName[MAX_CHARACTER_NAME_LEN];
	//};
	//struct PT_CAMPAIGN_F2T_ENTER_DEFENSE_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_F2T_ENTER_DEFENSE_DATA);
	//};

	//////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
    //@名字:        PT_CAMPAIGN_T2F_ENTER_DEFENSE
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_T2F_ENTER_DEFENSE_DATA
	{
		AccountIdType			toAccountId;
		CampaignIdType			campaignId;
		RegionIdType			regionId;
		Byte					regionType;
		U32						prepareTimeSecond;			//准备的时间  【秒】
		NetCampaignMemberInfo	newMember;
	};

	struct PT_CAMPAIGN_T2F_ENTER_DEFENSE_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_T2F_ENTER_DEFENSE_DATA);
	};

	class PT_CAMPAIGN_T2F_ENTER_DEFENSE_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_T2F_ENTER_DEFENSE_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_T2F_ENTER_DEFENSE;
            mBaseDataSize                       =   PT_CAMPAIGN_T2F_ENTER_DEFENSE_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_T2F_ENTER_DEFENSE_DATA
	//{
	//	AccountIdType			toAccountId;
	//	CampaignIdType			campaignId;
	//	RegionIdType			regionId;
	//	Byte					regionType;
	//	U32						prepareTimeSecond;			//准备的时间  【秒】
	//	NetCampaignMemberInfo	newMember;
	//};

	//struct PT_CAMPAIGN_T2F_ENTER_DEFENSE_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_T2F_ENTER_DEFENSE_DATA);
	//};
	
	//////////////////////////////////////////////////////////////////////////////////

	/**********************************************************************
    //@名字:        PT_CAMPAIGN_F2C_ENTER_DEFENSE
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_F2C_ENTER_DEFENSE_DATA
	{
		CampaignIdType			campaignId;
		AccountIdType			toAccountId;
		RegionIdType			regionId;
		Byte					regionType;
		U32						prepareTimeSecond;			//准备的时间  【秒】
		NetCampaignMemberInfo	newMember;
	};

	struct PT_CAMPAIGN_F2C_ENTER_DEFENSE_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_F2C_ENTER_DEFENSE_DATA);
	};

	class PT_CAMPAIGN_F2C_ENTER_DEFENSE_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_F2C_ENTER_DEFENSE_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_F2C_ENTER_DEFENSE;
            mBaseDataSize                       =   PT_CAMPAIGN_F2C_ENTER_DEFENSE_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_F2C_ENTER_DEFENSE_DATA
	//{
	//	CampaignIdType			campaignId;
	//	AccountIdType			toAccountId;
	//	RegionIdType			regionId;
	//	Byte					regionType;
	//	U32						prepareTimeSecond;			//准备的时间  【秒】
	//	NetCampaignMemberInfo	newMember;
	//};

	//struct PT_CAMPAIGN_F2C_ENTER_DEFENSE_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_F2C_ENTER_DEFENSE_DATA);
	//};
	
	//////////////////////////////////////////////////////////////////////////////////
	
	/**********************************************************************
    //@名字:        PT_CAMPAIGN_T2C_CAMPAIGN_INFO
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_T2C_CAMPAIGN_INFO_DATA
	{
		NetCampainInfo	campaignInfo;
	};

	struct PT_CAMPAIGN_T2C_CAMPAIGN_INFO_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_T2C_CAMPAIGN_INFO_DATA);
	};

	class PT_CAMPAIGN_T2C_CAMPAIGN_INFO_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_T2C_CAMPAIGN_INFO_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_T2C_CAMPAIGN_INFO;
            mBaseDataSize                       =   PT_CAMPAIGN_T2C_CAMPAIGN_INFO_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_T2C_CAMPAIGN_INFO_DATA
	//{
	//	NetCampainInfo	campaignInfo;
	//};

	//struct PT_CAMPAIGN_T2C_CAMPAIGN_INFO_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_T2C_CAMPAIGN_INFO_DATA);
	//};
	//////////////////////////////////////////////////////////////////////////////////
	struct PT_CAMPAIGN_T2F_MEMBER_LIST_DATA
	{
		NetIdType					frontServerNetId;
		AccountIdType				accountId;
		CampaignIdType				campaignId;
		Byte						force;
		Int							addMemberNum;
		NetCampaignMemberInfo		addMemberInfo[1];	//所有房间里的玩家
	};

	struct PT_CAMPAIGN_T2F_MEMBER_LIST_DATA_INFO
	{
		static Int const     netAddMemberInfoSize = sizeof (NetCampaignMemberInfo);
		static Int const     headSize = sizeof (PT_CAMPAIGN_T2F_MEMBER_LIST_DATA) - sizeof(NetCampaignMemberInfo);
		static Int          dataSize(PT_CAMPAIGN_T2F_MEMBER_LIST_DATA* data)
		{ 
			return PT_CAMPAIGN_T2F_MEMBER_LIST_DATA_INFO::headSize + PT_CAMPAIGN_T2F_MEMBER_LIST_DATA_INFO::netAddMemberInfoSize * data->addMemberNum;
		};
	};

	//////////////////////////////////////////////////////////////////////////////////
	struct PT_CAMPAIGN_F2C_MEMBER_LIST_DATA
	{
		NetIdType					frontServerNetId;
		CampaignIdType				campaignId;
		Byte						force;
		Int							addMemberNum;
		NetCampaignMemberInfo		addMemberInfo[1];	//所有房间里的玩家
	};

	struct PT_CAMPAIGN_F2C_MEMBER_LIST_DATA_INFO
	{
		static Int const     netAddMemberInfoSize = sizeof (NetCampaignMemberInfo);
		static Int const     headSize = sizeof (PT_CAMPAIGN_F2C_MEMBER_LIST_DATA) - sizeof(NetCampaignMemberInfo);
		static Int          dataSize(PT_CAMPAIGN_F2C_MEMBER_LIST_DATA* data)
		{ 
			return PT_CAMPAIGN_F2C_MEMBER_LIST_DATA_INFO::headSize + PT_CAMPAIGN_F2C_MEMBER_LIST_DATA_INFO::netAddMemberInfoSize * data->addMemberNum;
		};
	};
	//////////////////////////////////////////////////////////////////////////////////

	/**********************************************************************
    //@名字:        PT_CAMPAIGN_C2F_READY_MYSELF
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_C2F_READY_MYSELF_DATA
	{
		U64 	campaignId;
		U64 	myClanId;
		U64 	playerCharacterId;			    //选择的武将ID
	};

	struct PT_CAMPAIGN_C2F_READY_MYSELF_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_C2F_READY_MYSELF_DATA);
	};

	class PT_CAMPAIGN_C2F_READY_MYSELF_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_C2F_READY_MYSELF_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_C2F_READY_MYSELF;
            mBaseDataSize                       =   PT_CAMPAIGN_C2F_READY_MYSELF_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_C2F_READY_MYSELF_DATA
	//{
	//	U64 	campaignId;
	//	U64 	myClanId;
	//	U64 	playerCharacterId;			    //选择的武将ID
	//};

 //   struct PT_CAMPAIGN_C2F_READY_MYSELF_DATA_INFO
 //   {
 //       static const Int dataSize = sizeof(PT_CAMPAIGN_C2F_READY_MYSELF_DATA);
 //   };
    
    //////////////////////////////////////////////////////////////////////////////////

	/**********************************************************************
    //@名字:        PT_CAMPAIGN_F2T_READY_MYSELF
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_F2T_READY_MYSELF_DATA
	{
		NetIdType				clientNetId;
		CampaignIdType 			campaignId;
		ClanIdType 				myClanId;
		PlayerCharacterIdType	playerCharacterId;

	};
	struct PT_CAMPAIGN_F2T_READY_MYSELF_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_F2T_READY_MYSELF_DATA);
	};

	class PT_CAMPAIGN_F2T_READY_MYSELF_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_F2T_READY_MYSELF_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_F2T_READY_MYSELF;
            mBaseDataSize                       =   PT_CAMPAIGN_F2T_READY_MYSELF_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_F2T_READY_MYSELF_DATA
	//{
	//	NetIdType				clientNetId;
	//	CampaignIdType 			campaignId;
	//	ClanIdType 				myClanId;
	//	PlayerCharacterIdType	playerCharacterId;
	//	
	//};
 //   struct PT_CAMPAIGN_F2T_READY_MYSELF_DATA_INFO
 //   {
 //       static const Int dataSize = sizeof(PT_CAMPAIGN_F2T_READY_MYSELF_DATA);
 //   };

    //////////////////////////////////////////////////////////////////////////////////
/**********************************************************************
    //@名字:        PT_CAMPAIGN_T2C_READY_MYSELF
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_T2C_READY_MYSELF_DATA
	{
		CampaignIdType 			campaignId;
		ClanIdType 				myClanId;
		Byte					myPosition;
		PlayerCharacterIdType	playerCharacterId;
		Byte					readyState;			                    //1. 确认   2.取消
	};

	struct PT_CAMPAIGN_T2C_READY_MYSELF_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_T2C_READY_MYSELF_DATA);
	};


	class PT_CAMPAIGN_T2C_READY_MYSELF_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_T2C_READY_MYSELF_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_T2C_READY_MYSELF;
            mBaseDataSize                       =   PT_CAMPAIGN_T2C_READY_MYSELF_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_T2C_READY_MYSELF_DATA
	//{
	//	CampaignIdType 			campaignId;
	//	ClanIdType 				myClanId;
	//	Byte					myPosition;
	//	PlayerCharacterIdType	playerCharacterId;
	//	Byte					readyState;			                    //1. 确认   2.取消

	//};
 //   struct PT_CAMPAIGN_T2C_READY_MYSELF_DATA_INFO
 //   {
 //       static const Int dataSize = sizeof(PT_CAMPAIGN_T2C_READY_MYSELF_DATA);
 //   };
 //   
    //////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
    //@名字:        PT_CAMPAIGN_C2F_LEAVE
    //@功能:        玩家离开房间
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	//玩家离开房间
	struct PT_CAMPAIGN_C2F_LEAVE_DATA
	{
		//U64 	regionId;
		CampaignIdType 	campaignId;
		ClanIdType 		clanId;
	};
	struct PT_CAMPAIGN_C2F_LEAVE_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_C2F_LEAVE_DATA);
	};

	class PT_CAMPAIGN_C2F_LEAVE_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_C2F_LEAVE_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_C2F_LEAVE;
            mBaseDataSize                       =   PT_CAMPAIGN_C2F_LEAVE_INFO::dataSize ;

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

	////玩家离开房间
	//struct PT_CAMPAIGN_C2F_LEAVE_DATA
	//{
	//	//U64 	regionId;
	//	CampaignIdType 	campaignId;
	//	ClanIdType 		clanId;
	//};
 //   struct PT_CAMPAIGN_C2F_LEAVE_DATA_INFO
 //   {
 //       static const Int dataSize = sizeof(PT_CAMPAIGN_C2F_LEAVE_DATA);
 //   };

    //////////////////////////////////////////////////////////////////////////////////

	/**********************************************************************
    //@名字:        PT_CAMPAIGN_F2T_LEAVE
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_F2T_LEAVE_DATA
	{
		AccountIdType		accountId;
		NetIdType			clientNetId;
		CampaignIdType 		campaignId;
		ClanIdType	 		clanId;
	};

	struct PT_CAMPAIGN_F2T_LEAVE_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_F2T_LEAVE_DATA);
	};

	class PT_CAMPAIGN_F2T_LEAVE_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_F2T_LEAVE_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_F2T_LEAVE;
            mBaseDataSize                       =   PT_CAMPAIGN_F2T_LEAVE_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_F2T_LEAVE_DATA
	//{
	//	AccountIdType		accountId;
	//	NetIdType			clientNetId;
	//	CampaignIdType 		campaignId;
	//	ClanIdType	 		clanId;
	//};

 //   struct PT_CAMPAIGN_F2T_LEAVE_DATA_INFO
 //   {
 //       static const Int dataSize = sizeof(PT_CAMPAIGN_F2T_LEAVE_DATA);
 //   };

    //////////////////////////////////////////////////////////////////////////////////

	/**********************************************************************
    //@名字:        PT_CAMPAIGN_T2C_LEAVE
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_T2C_LEAVE_DATA
	{
		AccountIdType		accountId;
		CampaignIdType 		campaignId;
		ClanIdType	 		clanId;
		Byte				myPosition;
	};
	struct PT_CAMPAIGN_T2C_LEAVE_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_T2C_LEAVE_DATA);
	};

	class PT_CAMPAIGN_T2C_LEAVE_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_T2C_LEAVE_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_T2C_LEAVE;
            mBaseDataSize                       =   PT_CAMPAIGN_T2C_LEAVE_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_T2C_LEAVE_DATA
	//{
	//	AccountIdType		accountId;
	//	CampaignIdType 		campaignId;
	//	ClanIdType	 		clanId;
	//	Byte				myPosition;
	//};
 //   struct PT_CAMPAIGN_T2C_LEAVE_DATA_INFO
 //   {
 //       static const Int dataSize = sizeof(PT_CAMPAIGN_T2C_LEAVE_DATA);
 //   };

	//////////////////////////////////////////////////////////////////////////////////

	/**********************************************************************
    //@名字:        PT_CAMPAIGN_C2F_LEAVE_IN_CAMPAIGN
    //@功能:        战斗中离开
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	//玩家离开房间
	struct PT_CAMPAIGN_C2F_LEAVE_IN_CAMPAIGN_DATA
	{
		CampaignIdType 	campaignId;
		ClanIdType 		clanId;
	};
	struct PT_CAMPAIGN_C2F_LEAVE_IN_CAMPAIGN_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_C2F_LEAVE_IN_CAMPAIGN_DATA);
	};

	class PT_CAMPAIGN_C2F_LEAVE_IN_CAMPAIGN_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_C2F_LEAVE_IN_CAMPAIGN_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_C2F_LEAVE_IN_CAMPAIGN;
            mBaseDataSize                       =   PT_CAMPAIGN_C2F_LEAVE_IN_CAMPAIGN_INFO::dataSize ;

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

	/**********************************************************************
    //@名字:        PT_CAMPAIGN_F2T_LEAVE_IN_CAMPAIGN
    //@功能:        战斗中离开
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	//玩家离开房间
	struct PT_CAMPAIGN_F2T_LEAVE_IN_CAMPAIGN_DATA
	{
		AccountIdType		accountId;
		NetIdType			clientNetId;
		CampaignIdType 		campaignId;
		ClanIdType	 		clanId;
	};
	struct PT_CAMPAIGN_F2T_LEAVE_IN_CAMPAIGN_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_F2T_LEAVE_IN_CAMPAIGN_DATA);
	};

	class PT_CAMPAIGN_F2T_LEAVE_IN_CAMPAIGN_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_F2T_LEAVE_IN_CAMPAIGN_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_F2T_LEAVE_IN_CAMPAIGN;
            mBaseDataSize                       =   PT_CAMPAIGN_F2T_LEAVE_IN_CAMPAIGN_INFO::dataSize ;

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

	/**********************************************************************
    //@名字:        PT_CAMPAIGN_T2F_LEAVE_IN_CAMPAIGN
    //@功能:        战斗中离开
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	//玩家离开房间
	struct PT_CAMPAIGN_T2F_LEAVE_IN_CAMPAIGN_DATA
	{
		AccountIdType	accountId;
		CampaignIdType 	campaignId;
	};
	struct PT_CAMPAIGN_T2F_LEAVE_IN_CAMPAIGN_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_T2F_LEAVE_IN_CAMPAIGN_DATA);
	};

	class PT_CAMPAIGN_T2F_LEAVE_IN_CAMPAIGN_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_T2F_LEAVE_IN_CAMPAIGN_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_T2F_LEAVE_IN_CAMPAIGN;
            mBaseDataSize                       =   PT_CAMPAIGN_T2F_LEAVE_IN_CAMPAIGN_INFO::dataSize ;

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

	/**********************************************************************
    //@名字:        PT_CAMPAIGN_F2C_LEAVE_IN_CAMPAIGN
    //@功能:        战斗中离开
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	//玩家离开房间
	struct PT_CAMPAIGN_F2C_LEAVE_IN_CAMPAIGN_DATA
	{
		CampaignIdType 	campaignId;
	};
	struct PT_CAMPAIGN_F2C_LEAVE_IN_CAMPAIGN_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_F2C_LEAVE_IN_CAMPAIGN_DATA);
	};

	class PT_CAMPAIGN_F2C_LEAVE_IN_CAMPAIGN_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_F2C_LEAVE_IN_CAMPAIGN_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_F2C_LEAVE_IN_CAMPAIGN;
            mBaseDataSize                       =   PT_CAMPAIGN_F2C_LEAVE_IN_CAMPAIGN_INFO::dataSize ;

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

	/**********************************************************************
    //@名字:        PT_CAMPAIGN_T2C_DESTROY
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_T2C_DESTROY_DATA
	{
		CampaignIdType 	campaignId;
	};

	struct PT_CAMPAIGN_T2C_DESTROY_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_T2C_DESTROY_DATA);
	};

	class PT_CAMPAIGN_T2C_DESTROY_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_T2C_DESTROY_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_T2C_DESTROY;
            mBaseDataSize                       =   PT_CAMPAIGN_T2C_DESTROY_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_T2C_DESTROY_DATA
	//{
	//	CampaignIdType 	campaignId;
	//};
	//struct PT_CAMPAIGN_T2C_DESTROY_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_T2C_DESTROY_DATA);
	//};


	//////////////////////////////////////////////////////////////////////////////////

	/**********************************************************************
    //@名字:        PT_CAMPAIGN_C2F_START
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	//开始战斗
	struct	PT_CAMPAIGN_C2F_START_DATA
	{
		U64 	campaignId;
		U64 	starterClanId;
	};

	struct PT_CAMPAIGN_C2F_START_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_C2F_START_DATA);
	};

	class PT_CAMPAIGN_C2F_START_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_C2F_START_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_C2F_START;
            mBaseDataSize                       =   PT_CAMPAIGN_C2F_START_INFO::dataSize ;

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
	////开始战斗
	//struct	PT_CAMPAIGN_C2F_START_DATA
	//{
	//	U64 	campaignId;
	//	U64 	starterClanId;
	//};

 //   struct PT_CAMPAIGN_C2F_START_DATA_INFO
 //   {
 //       static const Int dataSize = sizeof(PT_CAMPAIGN_C2F_START_DATA);
 //   };

	//////////////////////////////////////////////////////////////////////////////////

	/**********************************************************************
    //@名字:        PT_CAMPAIGN_F2T_START
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_F2T_START_DATA
	{
		NetIdType		clientNetId;
		CampaignIdType 	campaignId;
		ClanIdType 		starterClanId;
		AccountIdType	accountId;
	};

	struct PT_CAMPAIGN_F2T_START_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_F2T_START_DATA);
	};

	class PT_CAMPAIGN_F2T_START_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_F2T_START_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_F2T_START;
            mBaseDataSize                       =   PT_CAMPAIGN_F2T_START_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_F2T_START_DATA
	//{
	//	NetIdType		clientNetId;
	//	CampaignIdType 	campaignId;
	//	ClanIdType 		starterClanId;
	//	AccountIdType	accountId;
	//};

	//struct PT_CAMPAIGN_F2T_START_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_F2T_START_DATA);
	//};

	//////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
    //@名字:        PT_CAMPAIGN_T2F_START
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_T2F_START_DATA
	{
		AccountIdType	accountId;
		RegionIdType	targetRegionId;
		CampaignIdType 	campaignId;
	};

	struct PT_CAMPAIGN_T2F_START_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_T2F_START_DATA);
	};

	class PT_CAMPAIGN_T2F_START_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_T2F_START_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_T2F_START;
            mBaseDataSize                       =   PT_CAMPAIGN_T2F_START_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_T2F_START_DATA
	//{
	//	AccountIdType	accountId;
	//	RegionIdType	targetRegionId;
	//	CampaignIdType 	campaignId;
	//};

	//struct PT_CAMPAIGN_T2F_START_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_T2F_START_DATA);
	//};
    //////////////////////////////////////////////////////////////////////////////////

	/**********************************************************************
    //@名字:        PT_CAMPAIGN_F2M_START
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct	PT_CAMPAIGN_F2M_START_DATA
	{
		AccountIdType		accountId;
		RegionIdType		targetRegionId;
		CampaignIdType 		campaignId;
	};
	struct PT_CAMPAIGN_F2M_START_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_F2M_START_DATA);
	};
	class PT_CAMPAIGN_F2M_START_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_F2M_START_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_F2M_START;
            mBaseDataSize                       =   PT_CAMPAIGN_F2M_START_INFO::dataSize ;

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

	//struct	PT_CAMPAIGN_F2M_START_DATA
	//{
	//	AccountIdType		accountId;
	//	RegionIdType		targetRegionId;
	//	CampaignIdType 		campaignId;
	//};
 //   struct PT_CAMPAIGN_F2M_START_DATA_INFO
 //   {
 //       static const Int dataSize = sizeof(PT_CAMPAIGN_F2M_START_DATA);
 //   };

	//////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
    //@名字:        PT_CAMPAIGN_M2T_START_NEW_INSTANCE
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_M2T_START_NEW_INSTANCE_DATA
	{
		CampaignIdType 		campaignId;
		RegionIdType		targetRegionId;
		InstanceUIdType		instanceUid;
	};

	struct PT_CAMPAIGN_M2T_START_NEW_INSTANCE_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_M2T_START_NEW_INSTANCE_DATA);
	};

	class PT_CAMPAIGN_M2T_START_NEW_INSTANCE_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_M2T_START_NEW_INSTANCE_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_M2T_START_NEW_INSTANCE;
            mBaseDataSize                       =   PT_CAMPAIGN_M2T_START_NEW_INSTANCE_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_M2T_START_NEW_INSTANCE_DATA
	//{
	//	CampaignIdType 		campaignId;
	//	RegionIdType		targetRegionId;
	//	InstanceUIdType		instanceUid;
	//};

	//struct PT_CAMPAIGN_M2T_START_NEW_INSTANCE_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_M2T_START_NEW_INSTANCE_DATA);
	//};

	//////////////////////////////////////////////////////////////////////////////////

	/**********************************************************************
    //@名字:        PT_CAMPAIGN_T2F_START_JUMP_REGION
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_T2F_START_JUMP_REGION_DATA
	{
		AccountIdType		accountId;
		ClanIdType			clanId;
		RegionIdType		toRegionId;
		Byte				toRegionType;
		InstanceIdType		toInstanceId;
		JUMP_TYPE			jumpType;
		Byte				jumpIndex;
		Bool				isBattleLeader;				//是否是攻击方或 防守方的 队长
		U32					prepareTimeSecond;			//准备的时间  【秒】
	};

	struct PT_CAMPAIGN_T2F_START_JUMP_REGION_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_T2F_START_JUMP_REGION_DATA);
	};

	class PT_CAMPAIGN_T2F_START_JUMP_REGION_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_T2F_START_JUMP_REGION_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_T2F_START_JUMP_REGION;
            mBaseDataSize                       =   PT_CAMPAIGN_T2F_START_JUMP_REGION_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_T2F_START_JUMP_REGION_DATA
	//{
	//	AccountIdType		accountId;
	//	ClanIdType			clanId;
	//	RegionIdType		toRegionId;
	//	Byte				toRegionType;
	//	InstanceIdType		toInstanceId;
	//	JUMP_TYPE			jumpType;
	//	Byte				jumpIndex;
	//	Bool				isBattleLeader;				//是否是攻击方或 防守方的 队长
	//	U32					prepareTimeSecond;			//准备的时间  【秒】
	//};

	//struct PT_CAMPAIGN_T2F_START_JUMP_REGION_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_T2F_START_JUMP_REGION_DATA);
	//};
	
	//////////////////////////////////////////////////////////////////////////////////

	/**********************************************************************
    //@名字:        PT_CAMPAIGN_T2C_START_NEW_CAMPAIGN
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct	PT_CAMPAIGN_T2C_START_NEW_CAMPAIGN_DATA
	{
		CampaignIdType 		campaignId;
		RegionIdType		regionId;
		Byte				regionType;
		U32					prepareTimeSecond;			//准备的时间  【秒】
	};

	struct PT_CAMPAIGN_T2C_START_NEW_CAMPAIGN_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_T2C_START_NEW_CAMPAIGN_DATA);
	};

	class PT_CAMPAIGN_T2C_START_NEW_CAMPAIGN_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_T2C_START_NEW_CAMPAIGN_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_T2C_START_NEW_CAMPAIGN;
            mBaseDataSize                       =   PT_CAMPAIGN_T2C_START_NEW_CAMPAIGN_INFO::dataSize ;

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

	//struct	PT_CAMPAIGN_T2C_START_NEW_CAMPAIGN_DATA
	//{
	//	CampaignIdType 		campaignId;
	//	RegionIdType		regionId;
	//	Byte				regionType;
	//	U32					prepareTimeSecond;			//准备的时间  【秒】
	//};

	//struct PT_CAMPAIGN_T2C_START_NEW_CAMPAIGN_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_T2C_START_NEW_CAMPAIGN_DATA);
	//};


	//////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
    //@名字:        PT_CAMPAIGN_T2M_INVITE_DEFENSE_REGION
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_T2M_INVITE_DEFENSE_REGION_DATA
	{
		RegionIdType		toRegionId;
		InstanceIdType		toInstanceId;		//0: 第一次进入该区域， >0: 进入指定的副本区域
		CampaignIdType		campaignId;
	};

	struct PT_CAMPAIGN_T2M_INVITE_DEFENSE_REGION_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_T2M_INVITE_DEFENSE_REGION_DATA);
	};

	class PT_CAMPAIGN_T2M_INVITE_DEFENSE_REGION_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_T2M_INVITE_DEFENSE_REGION_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_T2M_INVITE_DEFENSE_REGION;
            mBaseDataSize                       =   PT_CAMPAIGN_T2M_INVITE_DEFENSE_REGION_INFO::dataSize;

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

	//struct PT_CAMPAIGN_T2M_INVITE_DEFENSE_REGION_DATA
	//{
	//	RegionIdType		toRegionId;
	//	InstanceIdType		toInstanceId;		//0: 第一次进入该区域， >0: 进入指定的副本区域
	//	CampaignIdType		campaignId;
	//};

	//struct PT_CAMPAIGN_T2M_INVITE_DEFENSE_REGION_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_T2M_INVITE_DEFENSE_REGION_DATA);
	//};

	//////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
    //@名字:        PT_CAMPAIGN_M2C_INVITE_DEFENSE_REGION
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_M2C_INVITE_DEFENSE_REGION_DATA
	{
		RegionIdType		toRegionId;
		InstanceIdType		toInstanceId;		//0: 第一次进入该区域， >0: 进入指定的副本区域
		CampaignIdType		campaignId;
	};

	struct PT_CAMPAIGN_M2C_INVITE_DEFENSE_REGION_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_M2C_INVITE_DEFENSE_REGION_DATA);
	};

	class PT_CAMPAIGN_M2C_INVITE_DEFENSE_REGION_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_M2C_INVITE_DEFENSE_REGION_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_M2C_INVITE_DEFENSE_REGION;
            mBaseDataSize                       =   PT_CAMPAIGN_M2C_INVITE_DEFENSE_REGION_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_M2C_INVITE_DEFENSE_REGION_DATA
	//{
	//	RegionIdType		toRegionId;
	//	InstanceIdType		toInstanceId;		//0: 第一次进入该区域， >0: 进入指定的副本区域
	//	CampaignIdType		campaignId;
	//};

	//struct PT_CAMPAIGN_M2C_INVITE_DEFENSE_REGION_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_M2C_INVITE_DEFENSE_REGION_DATA);
	//};
	//////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
    //@名字:        PT_CAMPAIGN_C2F_END_MANUAL
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_C2F_END_MANUAL_DATA
	{
		CampaignIdType		campaignId;
	};

	struct PT_CAMPAIGN_C2F_END_MANUAL_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_C2F_END_MANUAL_DATA);
	};

	class PT_CAMPAIGN_C2F_END_MANUAL_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_C2F_END_MANUAL_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_C2F_END_MANUAL;
            mBaseDataSize                       =   PT_CAMPAIGN_C2F_END_MANUAL_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_C2F_END_MANUAL_DATA
	//{
	//	CampaignIdType		campaignId;
	//};

	//struct PT_CAMPAIGN_C2F_END_MANUAL_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_C2F_END_MANUAL_DATA);
	//};

	//////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
    //@名字:        PT_CAMPAIGN_F2T_END_MANUAL
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_F2T_END_MANUAL_DATA
	{
		CampaignIdType		campaignId;
	};

	struct PT_CAMPAIGN_F2T_END_MANUAL_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_F2T_END_MANUAL_DATA);
	};

	class PT_CAMPAIGN_F2T_END_MANUAL_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_F2T_END_MANUAL_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_F2T_END_MANUAL;
            mBaseDataSize                       =   PT_CAMPAIGN_F2T_END_MANUAL_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_F2T_END_MANUAL_DATA
	//{
	//	CampaignIdType		campaignId;
	//};

	//struct PT_CAMPAIGN_F2T_END_MANUAL_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_F2T_END_MANUAL_DATA);
	//};
	//////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
    //@名字:        PT_CAMPAIGN_T2F_END
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_T2F_END_DATA
	{
		RegionIdType		targetRegionId;
		InstanceUIdType 	targetInstanceUId;
		CampaignIdType		campaignId;
		RegionIdType		fromRegionId;		//战役发起者的地图
		Byte				winnerForce;		//胜利者的势力
	};

	struct PT_CAMPAIGN_T2F_END_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_T2F_END_DATA);
	};

	class PT_CAMPAIGN_T2F_END_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_T2F_END_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_T2F_END;
            mBaseDataSize                       =   PT_CAMPAIGN_T2F_END_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_T2F_END_DATA
	//{
	//	RegionIdType		targetRegionId;
	//	InstanceUIdType 	targetInstanceUId;
	//	CampaignIdType		campaignId;
	//	RegionIdType		fromRegionId;		//战役发起者的地图
	//	Byte				winnerForce;		//胜利者的势力
	//};

	//struct PT_CAMPAIGN_T2F_END_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_T2F_END_DATA);
	//};

	//////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
    //@名字:        PT_CAMPAIGN_F2M_END
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_F2M_END_DATA
	{
		RegionIdType		targetRegionId;
		InstanceUIdType 	targetInstanceUId;
		CampaignIdType		campaignId;
		RegionIdType		fromRegionId;		//战役发起者的地图
		Byte				winnerForce;		//胜利者的势力
	};

	struct PT_CAMPAIGN_F2M_END_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_F2M_END_DATA);
	};

	class PT_CAMPAIGN_F2M_END_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_F2M_END_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_F2M_END;
            mBaseDataSize                       =   PT_CAMPAIGN_F2M_END_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_F2M_END_DATA
	//{
	//	RegionIdType		targetRegionId;
	//	InstanceUIdType 	targetInstanceUId;
	//	CampaignIdType		campaignId;
	//	RegionIdType		fromRegionId;		//战役发起者的地图
	//	Byte				winnerForce;		//胜利者的势力
	//};

	//struct PT_CAMPAIGN_F2M_END_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_F2M_END_DATA);
	//};


	//////////////////////////////////////////////////////////////////////////////////
	struct PT_CAMPAIGN_M2C_END_DATA
	{
		CampaignIdType		campaignId;
		Byte				winnerForce;		//胜利者的势力
		U32					winnerItemGroupId;
		U32					loserItemGroupId;
		NetAddForceInfo		forceInfo[2];		//胜利者和失败者的信息  总体信息

		Int					addBattleScoreNum;
		NetAddCampaignEnd	addBattleScoreInfo[1];

	};

	struct PT_CAMPAIGN_M2C_END_DATA_INFO
	{            
		static Int  const headSize        = sizeof (PT_CAMPAIGN_M2C_END_DATA) - sizeof( NetAddCampaignEnd );
		static Int  const netAddBattleScoreInfoSize    = sizeof (NetAddCampaignEnd);
		static Int  dataSize(PT_CAMPAIGN_M2C_END_DATA* data)
		{ 
			return headSize + netAddBattleScoreInfoSize * data->addBattleScoreNum;
		};
	};

	//////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
    //@名字:        PT_CAMPAIGN_C2F_END_SCORE
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_C2F_END_SCORE_DATA
	{
		//CampaignIdType		campaignId;
		//AccountIdType			accountId;
		PlayerCharacterIdType	playerCharacterId;
		U32						itemGroupId;
	};

	struct PT_CAMPAIGN_C2F_END_SCORE_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_C2F_END_SCORE_DATA);
	};

	class PT_CAMPAIGN_C2F_END_SCORE_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_C2F_END_SCORE_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_C2F_END_SCORE;
            mBaseDataSize                       =   PT_CAMPAIGN_C2F_END_SCORE_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_C2F_END_SCORE_DATA
	//{
	//	//CampaignIdType		campaignId;
	//	//AccountIdType			accountId;
	//	PlayerCharacterIdType	playerCharacterId;
	//	U32						itemGroupId;
	//};

	//struct PT_CAMPAIGN_C2F_END_SCORE_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_C2F_END_SCORE_DATA);
	//};


	//////////////////////////////////////////////////////////////////////////////////
	//struct PT_CAMPAIGN_T2C_END_DATA
	//{
	//	U64 	campaignId;
	//	Byte	winnerForce;		//胜利者的势力
	//};
	//
	//struct PT_CAMPAIGN_T2C_END_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_T2C_END_DATA);
	//};

	//////////////////////////////////////////////////////////////////////////////////




    //////////////////////////////////////////////////////////////////////////////////

	//struct	PT_CAMPAIGN_SC_START_DATA
	//{
	//	U64		regionId;
	//	U64 	campaignId;
	//};
 //   struct PT_CAMPAIGN_SC_START_DATA_INFO
 //   {
 //       static const Int dataSize = sizeof(PT_CAMPAIGN_SC_START_DATA);
 //   };

    //////////////////////////////////////////////////////////////////////////////////

#if 0
	struct PT_CAMPAIGN_SC_END_BATTLE_DATA
	{
		U64		regionId;
		U64 	campaignId;
		Byte	winnerForce;		//胜利者的势力
	};
    struct PT_CAMPAIGN_SC_END_BATTLE_DATA_INFO
    {
        static const Int dataSize = sizeof(PT_CAMPAIGN_SC_END_BATTLE_DATA);
    };
#endif

    //////////////////////////////////////////////////////////////////////////////////

#if 0
	struct PT_CAMPAIGN_T2F_ERROR_DATA
	{
		CAMPAIGN_ERROR	error;
		NetIdType		clientNetId;
	};

	struct PT_CAMPAIGN_T2F_ERROR_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_T2F_ERROR_DATA);
	};
#endif

	//////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
    //@名字:        PT_CAMPAIGN_T2C_ERROR
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_T2C_ERROR_DATA
	{
		CAMPAIGN_ERROR	error;
	};

	struct PT_CAMPAIGN_T2C_ERROR_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_T2C_ERROR_DATA);
	};

	class PT_CAMPAIGN_T2C_ERROR_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_T2C_ERROR_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_T2C_ERROR;
            mBaseDataSize                       =   PT_CAMPAIGN_T2C_ERROR_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_T2C_ERROR_DATA
	//{
	//	CAMPAIGN_ERROR	error;
	//};

	//struct PT_CAMPAIGN_T2C_ERROR_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_T2C_ERROR_DATA);
	//};

	//////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
    //@名字:        PT_CAMPAIGN_C2F_CHANGE_CAMP_CONTROL
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_C2F_CHANGE_CAMP_CONTROL_DATA
	{
		CampaignIdType	campaignId;
		AccountIdType	ownerAccountId;
		CampIdType		campId;
		AccountIdType	targetControlerAccountId;
	};

	struct PT_CAMPAIGN_C2F_CHANGE_CAMP_CONTROL_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_C2F_CHANGE_CAMP_CONTROL_DATA);
	};

	class PT_CAMPAIGN_C2F_CHANGE_CAMP_CONTROL_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_C2F_CHANGE_CAMP_CONTROL_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_C2F_CHANGE_CAMP_CONTROL;
            mBaseDataSize                       =   PT_CAMPAIGN_C2F_CHANGE_CAMP_CONTROL_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_C2F_CHANGE_CAMP_CONTROL_DATA
	//{
	//	CampaignIdType	campaignId;
	//	AccountIdType	ownerAccountId;
	//	CampIdType		campId;
	//	AccountIdType	targetControlerAccountId;
	//};

	//struct PT_CAMPAIGN_C2F_CHANGE_CAMP_CONTROL_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_C2F_CHANGE_CAMP_CONTROL_DATA);
	//};

	//////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
    //@名字:        PT_CAMPAIGN_F2T_CHANGE_CAMP_CONTROL
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_F2T_CHANGE_CAMP_CONTROL_DATA
	{
		CampaignIdType	campaignId;
		AccountIdType	ownerAccountId;
		CampIdType		campId;
		AccountIdType	targetControlerAccountId;
	};

	struct PT_CAMPAIGN_F2T_CHANGE_CAMP_CONTROL_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_F2T_CHANGE_CAMP_CONTROL_DATA);
	};

	class PT_CAMPAIGN_F2T_CHANGE_CAMP_CONTROL_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_F2T_CHANGE_CAMP_CONTROL_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_F2T_CHANGE_CAMP_CONTROL;
            mBaseDataSize                       =   PT_CAMPAIGN_F2T_CHANGE_CAMP_CONTROL_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_F2T_CHANGE_CAMP_CONTROL_DATA
	//{
	//	CampaignIdType	campaignId;
	//	AccountIdType	ownerAccountId;
	//	CampIdType		campId;
	//	AccountIdType	targetControlerAccountId;
	//};

	//struct PT_CAMPAIGN_F2T_CHANGE_CAMP_CONTROL_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_F2T_CHANGE_CAMP_CONTROL_DATA);
	//};

	//////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
    //@名字:        PT_CAMPAIGN_T2F_CHANGE_CAMP_CONTROL
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_T2F_CHANGE_CAMP_CONTROL_DATA
	{
		RegionIdType	targetRegionId;
		InstanceUIdType targetInstanceUId;
		AccountIdType	ownerAccountId;
		CampIdType		campId;
		AccountIdType	targetControlerAccountId;
	};

	struct PT_CAMPAIGN_T2F_CHANGE_CAMP_CONTROL_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_T2F_CHANGE_CAMP_CONTROL_DATA);
	};


	class PT_CAMPAIGN_T2F_CHANGE_CAMP_CONTROL_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_T2F_CHANGE_CAMP_CONTROL_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_T2F_CHANGE_CAMP_CONTROL;
            mBaseDataSize                       =   PT_CAMPAIGN_T2F_CHANGE_CAMP_CONTROL_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_T2F_CHANGE_CAMP_CONTROL_DATA
	//{
	//	RegionIdType	targetRegionId;
	//	InstanceUIdType targetInstanceUId;
	//	AccountIdType	ownerAccountId;
	//	CampIdType		campId;
	//	AccountIdType	targetControlerAccountId;
	//};

	//struct PT_CAMPAIGN_T2F_CHANGE_CAMP_CONTROL_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_T2F_CHANGE_CAMP_CONTROL_DATA);
	//};

	//////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
    //@名字:        PT_CAMPAIGN_F2M_CHANGE_CAMP_CONTROL
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_F2M_CHANGE_CAMP_CONTROL_DATA
	{
		RegionIdType	targetRegionId;
		InstanceUIdType targetInstanceUId;

		AccountIdType	ownerAccountId;
		CampIdType		campId;
		AccountIdType	targetControlerAccountId;
	};

	struct PT_CAMPAIGN_F2M_CHANGE_CAMP_CONTROL_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_F2M_CHANGE_CAMP_CONTROL_DATA);
	};

	class PT_CAMPAIGN_F2M_CHANGE_CAMP_CONTROL_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_F2M_CHANGE_CAMP_CONTROL_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_F2M_CHANGE_CAMP_CONTROL;
            mBaseDataSize                       =   PT_CAMPAIGN_F2M_CHANGE_CAMP_CONTROL_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_F2M_CHANGE_CAMP_CONTROL_DATA
	//{
	//	RegionIdType	targetRegionId;
	//	InstanceUIdType targetInstanceUId;

	//	AccountIdType	ownerAccountId;
	//	CampIdType		campId;
	//	AccountIdType	targetControlerAccountId;
	//};

	//struct PT_CAMPAIGN_F2M_CHANGE_CAMP_CONTROL_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_F2M_CHANGE_CAMP_CONTROL_DATA);
	//};

	//////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
    //@名字:        PT_CAMPAIGN_M2C_CHANGE_CAMP_CONTROL
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_M2C_CHANGE_CAMP_CONTROL_DATA
	{
		CampIdType		campId;
		AccountIdType	targetControlerAccountId;
	};

	struct PT_CAMPAIGN_M2C_CHANGE_CAMP_CONTROL_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_M2C_CHANGE_CAMP_CONTROL_DATA);
	};

	class PT_CAMPAIGN_M2C_CHANGE_CAMP_CONTROL_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_M2C_CHANGE_CAMP_CONTROL_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_M2C_CHANGE_CAMP_CONTROL;
            mBaseDataSize                       =   PT_CAMPAIGN_M2C_CHANGE_CAMP_CONTROL_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_M2C_CHANGE_CAMP_CONTROL_DATA
	//{
	//	CampIdType		campId;
	//	AccountIdType	targetControlerAccountId;
	//};

	//struct PT_CAMPAIGN_M2C_CHANGE_CAMP_CONTROL_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_M2C_CHANGE_CAMP_CONTROL_DATA);
	//};
	

	//////////////////////////////////////////////////////////////////////////////////
	struct PT_CAMPAIGN_M2C_CHANGE_TROOP_CONTROL_DATA
	{
		CampIdType					campId;
		AccountIdType				targetControlerAccountId;
		Int							addNum;
		NetTroopChangeControlInfo	addMemberInfo[1];
	};

	struct PT_CAMPAIGN_M2C_CHANGE_TROOP_CONTROL_DATA_INFO
	{
		static Int const     netAddMemberInfoSize = sizeof (NetTroopChangeControlInfo);
		static Int const     headSize = sizeof (PT_CAMPAIGN_M2C_CHANGE_TROOP_CONTROL_DATA) - sizeof(NetTroopChangeControlInfo);
		static Int			 dataSize(PT_CAMPAIGN_M2C_CHANGE_TROOP_CONTROL_DATA* data)
		{ 
			return PT_CAMPAIGN_M2C_CHANGE_TROOP_CONTROL_DATA_INFO::headSize + PT_CAMPAIGN_M2C_CHANGE_TROOP_CONTROL_DATA_INFO::netAddMemberInfoSize * data->addNum;
		};
	};

	//////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
    //@名字:        PT_CAMPAIGN_C2F_TROOP_CONTROLLER_LIST
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_C2F_TROOP_CONTROLLER_LIST_DATA
	{
		AccountIdType	myAccountId;
		CampaignIdType	campaignId;
		CampIdType		campId;
	};

	struct PT_CAMPAIGN_C2F_TROOP_CONTROLLER_LIST_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_C2F_TROOP_CONTROLLER_LIST_DATA);
	};

	class PT_CAMPAIGN_C2F_TROOP_CONTROLLER_LIST_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_C2F_TROOP_CONTROLLER_LIST_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_C2F_TROOP_CONTROLLER_LIST;
            mBaseDataSize                       =   PT_CAMPAIGN_C2F_TROOP_CONTROLLER_LIST_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_C2F_TROOP_CONTROLLER_LIST_DATA
	//{
	//	AccountIdType	myAccountId;
	//	CampaignIdType	campaignId;
	//	CampIdType		campId;
	//};

	//struct PT_CAMPAIGN_C2F_TROOP_CONTROLLER_LIST_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_C2F_TROOP_CONTROLLER_LIST_DATA);
	//};

	
	//////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
    //@名字:        PT_CAMPAIGN_F2T_TROOP_CONTROLLER_LIST
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_F2T_TROOP_CONTROLLER_LIST_DATA
	{
		AccountIdType	myAccountId;
		CampaignIdType	campaignId;
		ClanIdType		myClanId;
		CampIdType		campId;
	};

	struct PT_CAMPAIGN_F2T_TROOP_CONTROLLER_LIST_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_F2T_TROOP_CONTROLLER_LIST_DATA);
	};

	class PT_CAMPAIGN_F2T_TROOP_CONTROLLER_LIST_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_F2T_TROOP_CONTROLLER_LIST_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_F2T_TROOP_CONTROLLER_LIST;
            mBaseDataSize                       =   PT_CAMPAIGN_F2T_TROOP_CONTROLLER_LIST_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_F2T_TROOP_CONTROLLER_LIST_DATA
	//{
	//	AccountIdType	myAccountId;
	//	CampaignIdType	campaignId;
	//	ClanIdType		myClanId;
	//	CampIdType		campId;
	//};

	//struct PT_CAMPAIGN_F2T_TROOP_CONTROLLER_LIST_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_F2T_TROOP_CONTROLLER_LIST_DATA);
	//};

	//////////////////////////////////////////////////////////////////////////////////
	struct PT_CAMPAIGN_T2F_TROOP_CONTROLLER_LIST_DATA
	{
		AccountIdType			myAccountId;
		RegionIdType			targetRegionId;
		InstanceUIdType 		targetInstanceUId;
		CampIdType				campId;
		AccountIdType			campOwnerAccountId;
		AccountIdType			troopCurControllerAccountId;
		Int						addMemberNum;
		NetTroopControllerInfo	addMemberInfo[1];
	};

	struct PT_CAMPAIGN_T2F_TROOP_CONTROLLER_LIST_DATA_INFO
	{
		static Int const     netAddMemberInfoSize = sizeof (NetTroopControllerInfo);
		static Int const     headSize = sizeof (PT_CAMPAIGN_T2F_TROOP_CONTROLLER_LIST_DATA) - sizeof(NetTroopControllerInfo);
		static Int          dataSize(PT_CAMPAIGN_T2F_TROOP_CONTROLLER_LIST_DATA* data)
		{ 
			return PT_CAMPAIGN_T2F_TROOP_CONTROLLER_LIST_DATA_INFO::headSize + PT_CAMPAIGN_T2F_TROOP_CONTROLLER_LIST_DATA_INFO::netAddMemberInfoSize * data->addMemberNum;
		};
	};

	//////////////////////////////////////////////////////////////////////////////////
	struct PT_CAMPAIGN_F2M_TROOP_CONTROLLER_LIST_DATA
	{
		AccountIdType			myAccountId;
		RegionIdType			targetRegionId;
		InstanceUIdType 		targetInstanceUId;
		CampIdType				campId;
		AccountIdType			campOwnerAccountId;
		AccountIdType			troopCurControllerAccountId;
		Int						addMemberNum;
		NetTroopControllerInfo	addMemberInfo[1];
	};

	struct PT_CAMPAIGN_F2M_TROOP_CONTROLLER_LIST_DATA_INFO
	{
		static Int const     netAddMemberInfoSize = sizeof (NetTroopControllerInfo);
		static Int const     headSize = sizeof (PT_CAMPAIGN_F2M_TROOP_CONTROLLER_LIST_DATA) - sizeof(NetTroopControllerInfo);
		static Int          dataSize(PT_CAMPAIGN_F2M_TROOP_CONTROLLER_LIST_DATA* data)
		{ 
			return PT_CAMPAIGN_F2M_TROOP_CONTROLLER_LIST_DATA_INFO::headSize + PT_CAMPAIGN_F2M_TROOP_CONTROLLER_LIST_DATA_INFO::netAddMemberInfoSize * data->addMemberNum;
		};
	};

	//////////////////////////////////////////////////////////////////////////////////
	struct PT_CAMPAIGN_M2C_TROOP_CONTROLLER_LIST_DATA
	{
		CampIdType				campId;
		AccountIdType			campOwnerAccountId;
		AccountIdType			troopCurControllerAccountId;
		NetCampInfo				campInfo;
		Int						addMemberNum;
		NetTroopControllerInfo	addMemberInfo[1];
	};

	struct PT_CAMPAIGN_M2C_TROOP_CONTROLLER_LIST_DATA_INFO
	{
		static Int const     netAddMemberInfoSize = sizeof (NetTroopControllerInfo);
		static Int const     headSize = sizeof (PT_CAMPAIGN_M2C_TROOP_CONTROLLER_LIST_DATA) - sizeof(NetTroopControllerInfo);
		static Int          dataSize(PT_CAMPAIGN_M2C_TROOP_CONTROLLER_LIST_DATA* data)
		{ 
			return PT_CAMPAIGN_M2C_TROOP_CONTROLLER_LIST_DATA_INFO::headSize + PT_CAMPAIGN_M2C_TROOP_CONTROLLER_LIST_DATA_INFO::netAddMemberInfoSize * data->addMemberNum;
		};
	};

	//////////////////////////////////////////////////////////////////////////////////
	//struct PT_CAMPAIGN_T2F_TROOP_CONTROLLER_LIST_DATA
	//{
	//	CampIdType				campId;
	//	AccountIdType			campOwnerAccountId;
	//	AccountIdType			troopCurControllerAccountId;
	//	Int						addMemberNum;
	//	NetTroopControllerInfo	addMemberInfo[1];
	//};

	//struct PT_CAMPAIGN_T2F_TROOP_CONTROLLER_LIST_DATA_INFO
	//{
	//	static Int const     netAddMemberInfoSize = sizeof (NetTroopControllerInfo);
	//	static Int const     headSize = sizeof (PT_CAMPAIGN_T2F_TROOP_CONTROLLER_LIST_DATA) - sizeof(NetTroopControllerInfo);
	//	static Int          dataSize(PT_CAMPAIGN_T2F_TROOP_CONTROLLER_LIST_DATA* data)
	//	{ 
	//		return PT_CAMPAIGN_T2F_TROOP_CONTROLLER_LIST_DATA_INFO::headSize + PT_CAMPAIGN_T2F_TROOP_CONTROLLER_LIST_DATA_INFO::netAddMemberInfoSize * data->addMemberNum;
	//	};
	//};
	//////////////////////////////////////////////////////////////////////////////////

	//struct PT_CAMPAIGN_T2C_TROOP_CONTROLLER_LIST_DATA
	//{
	//	CampIdType				campId;
	//	AccountIdType			campOwnerAccountId;
	//	Int						addMemberNum;
	//	NetTroopControllerInfo	addMemberInfo[1];
	//};

	//struct PT_CAMPAIGN_T2C_TROOP_CONTROLLER_LIST_DATA_INFO
	//{
	//	static Int const     netAddMemberInfoSize = sizeof (NetTroopControllerInfo);
	//	static Int const     headSize = sizeof (PT_CAMPAIGN_T2C_TROOP_CONTROLLER_LIST_DATA) - sizeof(NetTroopControllerInfo);
	//	static Int          dataSize(PT_CAMPAIGN_T2C_TROOP_CONTROLLER_LIST_DATA* data)
	//	{ 
	//		return PT_CAMPAIGN_T2C_TROOP_CONTROLLER_LIST_DATA_INFO::headSize + PT_CAMPAIGN_T2C_TROOP_CONTROLLER_LIST_DATA_INFO::netAddMemberInfoSize * data->addMemberNum;
	//	};
	//};

	//////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
    //@名字:        PT_CAMPAIGN_T2F_CREATE_CAMP_BY_CONTROLER
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_T2F_CREATE_CAMP_BY_CONTROLER_DATA
	{
		CampaignIdType	campaignId;
		RegionIdType	targetRegionId;
		InstanceUIdType targetInstanceUId;
		AccountIdType	targetControlerAccountId;
		Byte			campForce;
		Int				campNum;
		Int				campIndexStart;
	};

	struct PT_CAMPAIGN_T2F_CREATE_CAMP_BY_CONTROLER_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_T2F_CREATE_CAMP_BY_CONTROLER_DATA);
	};


	class PT_CAMPAIGN_T2F_CREATE_CAMP_BY_CONTROLER_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_T2F_CREATE_CAMP_BY_CONTROLER_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_T2F_CREATE_CAMP_BY_CONTROLER;
            mBaseDataSize                       =   PT_CAMPAIGN_T2F_CREATE_CAMP_BY_CONTROLER_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_T2F_CREATE_CAMP_BY_CONTROLER_DATA
	//{
	//	CampaignIdType	campaignId;
	//	RegionIdType	targetRegionId;
	//	InstanceUIdType targetInstanceUId;
	//	AccountIdType	targetControlerAccountId;
	//	Byte			campForce;
	//	Int				campNum;
	//	Int				campIndexStart;
	//};

	//struct PT_CAMPAIGN_T2F_CREATE_CAMP_BY_CONTROLER_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_T2F_CREATE_CAMP_BY_CONTROLER_DATA);
	//};

	//////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
    //@名字:        PT_CAMPAIGN_F2M_CREATE_CAMP_BY_CONTROLER
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_F2M_CREATE_CAMP_BY_CONTROLER_DATA
	{
		CampaignIdType	campaignId;
		RegionIdType	targetRegionId;
		InstanceUIdType targetInstanceUId;
		AccountIdType	targetControlerAccountId;
		Byte			campForce;
		Int				campNum;
		Int				campIndexStart;
	};

	struct PT_CAMPAIGN_F2M_CREATE_CAMP_BY_CONTROLER_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_F2M_CREATE_CAMP_BY_CONTROLER_DATA);
	};
	class PT_CAMPAIGN_F2M_CREATE_CAMP_BY_CONTROLER_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_F2M_CREATE_CAMP_BY_CONTROLER_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_F2M_CREATE_CAMP_BY_CONTROLER;
            mBaseDataSize                       =   PT_CAMPAIGN_F2M_CREATE_CAMP_BY_CONTROLER_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_F2M_CREATE_CAMP_BY_CONTROLER_DATA
	//{
	//	CampaignIdType	campaignId;
	//	RegionIdType	targetRegionId;
	//	InstanceUIdType targetInstanceUId;
	//	AccountIdType	targetControlerAccountId;
	//	Byte			campForce;
	//	Int				campNum;
	//	Int				campIndexStart;
	//};

	//struct PT_CAMPAIGN_F2M_CREATE_CAMP_BY_CONTROLER_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_F2M_CREATE_CAMP_BY_CONTROLER_DATA);
	//};

	//////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
    //@名字:        PT_CAMPAIGN_F2T_DISCONNECT
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_F2T_DISCONNECT_DATA
	{
		ClanIdType		clanId;
		//CampaignIdType	campaignId;
	};

	struct PT_CAMPAIGN_F2T_DISCONNECT_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_F2T_DISCONNECT_DATA);
	};

	class PT_CAMPAIGN_F2T_DISCONNECT_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_F2T_DISCONNECT_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_F2T_DISCONNECT;
            mBaseDataSize                       =   PT_CAMPAIGN_F2T_DISCONNECT_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_F2T_DISCONNECT_DATA
	//{
	//	ClanIdType		clanId;
	//	//CampaignIdType	campaignId;
	//};

	//struct PT_CAMPAIGN_F2T_DISCONNECT_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_F2T_DISCONNECT_DATA);
	//};
	
	//////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
    //@名字:        PT_CAMPAIGN_T2F_CHANGE_CAMP_OWNER
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_T2F_CHANGE_CAMP_OWNER_DATA
	{
		RegionIdType	targetRegionId;
		InstanceUIdType targetInstanceUId;
		AccountIdType	accountId;
	};

	struct PT_CAMPAIGN_T2F_CHANGE_CAMP_OWNER_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_T2F_CHANGE_CAMP_OWNER_DATA);
	};
	class PT_CAMPAIGN_T2F_CHANGE_CAMP_OWNER_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_T2F_CHANGE_CAMP_OWNER_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_T2F_CHANGE_CAMP_OWNER;
            mBaseDataSize                       =   PT_CAMPAIGN_T2F_CHANGE_CAMP_OWNER_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_T2F_CHANGE_CAMP_OWNER_DATA
	//{
	//	RegionIdType	targetRegionId;
	//	InstanceUIdType targetInstanceUId;
	//	AccountIdType	accountId;
	//};

	//struct PT_CAMPAIGN_T2F_CHANGE_CAMP_OWNER_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_T2F_CHANGE_CAMP_OWNER_DATA);
	//};

	//////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
    //@名字:        PT_CAMPAIGN_F2M_CHANGE_CAMP_OWNER
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_F2M_CHANGE_CAMP_OWNER_DATA
	{
		RegionIdType	targetRegionId;
		InstanceUIdType targetInstanceUId;
		AccountIdType	accountId;
	};

	struct PT_CAMPAIGN_F2M_CHANGE_CAMP_OWNER_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_F2M_CHANGE_CAMP_OWNER_DATA);
	};
	class PT_CAMPAIGN_F2M_CHANGE_CAMP_OWNER_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_CAMPAIGN_F2M_CHANGE_CAMP_OWNER_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_F2M_CHANGE_CAMP_OWNER;
            mBaseDataSize                       =   PT_CAMPAIGN_F2M_CHANGE_CAMP_OWNER_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_F2M_CHANGE_CAMP_OWNER_DATA
	//{
	//	RegionIdType	targetRegionId;
	//	InstanceUIdType targetInstanceUId;
	//	AccountIdType	accountId;
	//};

	//struct PT_CAMPAIGN_F2M_CHANGE_CAMP_OWNER_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_F2M_CHANGE_CAMP_OWNER_DATA);
	//};

	
	//////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
    //@名字:        PT_CAMPAIGN_M2C_CHANGE_CAMP_OWNER
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_M2C_CHANGE_CAMP_OWNER_DATA
	{
		RegionIdType	targetRegionId;
		InstanceUIdType targetInstanceUId;
		AccountIdType	accountId;
	};

	struct PT_CAMPAIGN_M2C_CHANGE_CAMP_OWNER_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_M2C_CHANGE_CAMP_OWNER_DATA);
	};


	class PT_CAMPAIGN_M2C_CHANGE_CAMP_OWNER_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
       PT_CAMPAIGN_M2C_CHANGE_CAMP_OWNER_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_M2C_CHANGE_CAMP_OWNER;
            mBaseDataSize                       =   PT_CAMPAIGN_M2C_CHANGE_CAMP_OWNER_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_M2C_CHANGE_CAMP_OWNER_DATA
	//{
	//	RegionIdType	targetRegionId;
	//	InstanceUIdType targetInstanceUId;
	//	AccountIdType	accountId;
	//};

	//struct PT_CAMPAIGN_M2C_CHANGE_CAMP_OWNER_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_M2C_CHANGE_CAMP_OWNER_DATA);
	//};

	//////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
    //@名字:        PT_CAMPAIGN_M2T_MAIN_CAMP_DESTROY
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_CAMPAIGN_M2T_MAIN_CAMP_DESTROY_DATA
	{
		CampaignIdType 		campaignId;
		FORCE				campForce;
	};

	struct PT_CAMPAIGN_M2T_MAIN_CAMP_DESTROY_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_M2T_MAIN_CAMP_DESTROY_DATA);
	};
	class PT_CAMPAIGN_M2T_MAIN_CAMP_DESTROY_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
       PT_CAMPAIGN_M2T_MAIN_CAMP_DESTROY_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_CAMPAIGN;
            mType                               =   PT_CAMPAIGN_M2T_MAIN_CAMP_DESTROY;
            mBaseDataSize                       =   PT_CAMPAIGN_M2T_MAIN_CAMP_DESTROY_INFO::dataSize ;

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

	//struct PT_CAMPAIGN_M2T_MAIN_CAMP_DESTROY_DATA
	//{
	//	CampaignIdType 		campaignId;
	//	FORCE				campForce;
	//};

	//struct PT_CAMPAIGN_M2T_MAIN_CAMP_DESTROY_DATA_INFO
	//{
	//	static const Int dataSize = sizeof(PT_CAMPAIGN_M2T_MAIN_CAMP_DESTROY_DATA);
	//};

	//////////////////////////////////////////////////////////////////////////////////

#if 0
	struct NetCampaignPlayCharacterInfo		//武将信息
	{
		U64			playerCharacterId;
		Char16		playerCharacterName[MAX_CHARACTER_NAME_LEN];
	};
#endif
#if 0
	struct NetCampaignTroopInfo			//军队信息
	{
		U64		troopId;
		U64		troopTemplateId;
	};
#endif
#if 0
	struct NetWaitingInfo
	{
		ClanIdType		clanId;
		Char16	clanName[MAX_CLAN_NAME];
	};
#endif
#if 0
	struct NetStandByList
	{
		ClanIdType						clanId;
		Char16							clanName[MAX_CLAN_NAME];
		Byte							readyState;
		Byte							position;

		NetCampaignTroopInfo			troopInfo;				//军队信息
		NetCampaignPlayCharacterInfo	playerCharacterInfo;	//武将信息
	};
#endif
	//////////////////////////////////////////////////////////////////////////////////
#if 0
	struct PT_CAMPAIGN_T2F_CREATE_DATA
	{
		NetIdType		clientNetId;
		NetCampainInfo	campaignInfo;
	};

	struct PT_CAMPAIGN_T2F_CREATE_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_T2F_CREATE_DATA);
	};
#endif
	//////////////////////////////////////////////////////////////////////////////////
#if 0
	//////////////////////////////////////////////////////////////////////////////////
	struct PT_CAMPAIGN_F2C_CAMPAIGN_LIST_DATA
	{
		Int				addCampainNum;
		NetCampainInfo	addCampainInfo[1];	//创建者的信息和房间里成员列表
	};

	struct PT_CAMPAIGN_F2C_CAMPAIGN_LIST_DATA_INFO
	{
		static Int const     netAddCampainInfoSize = sizeof (NetCampainInfo);
		static Int const     headSize = sizeof (PT_CAMPAIGN_F2C_CAMPAIGN_LIST_DATA) - sizeof( NetCampainInfo );
		static Int          dataSize(PT_CAMPAIGN_F2C_CAMPAIGN_LIST_DATA* data)
		{ 
			return PT_CAMPAIGN_F2C_CAMPAIGN_LIST_DATA_INFO::headSize + PT_CAMPAIGN_F2C_CAMPAIGN_LIST_DATA_INFO::netAddCampainInfoSize * data->addCampainNum;
		};
	};
#endif
	//////////////////////////////////////////////////////////////////////////////////
#if 0
	struct PT_CAMPAIGN_F2M_ENTER_DATA
	{
		U64		accountId;
		U64		myClanId;
		U64		campaignId;
		U64		regionId;
		Char16	clanName[MAX_CLAN_NAME];
	};
	struct PT_CAMPAIGN_F2M_ENTER_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_F2M_ENTER_DATA);
	};

	//////////////////////////////////////////////////////////////////////////////////
	struct PT_CAMPAIGN_SC_ENTER_DATA
	{
		U64		regionId;
		U64		campaignId;
		U64		newClanId;
		Char16	clanName[MAX_CLAN_NAME];
	};

	struct PT_CAMPAIGN_SC_ENTER_DATA_INFO
	{
		static Int const  dataSize = sizeof(PT_CAMPAIGN_SC_ENTER_DATA);
	};

	//////////////////////////////////////////////////////////////////////////////////

	struct PT_CAMPAIGN_SC_WAITING_LIST_DATA
	{
		U64				regionId;
		U64				campaignId;

		Int				waitingCount;
		NetWaitingInfo	waitingList[1];
	};
	struct PT_CAMPAIGN_SC_WAITING_LIST_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_SC_WAITING_LIST_DATA);
	};

	//////////////////////////////////////////////////////////////////////////////////

	struct PT_CAMPAIGN_SC_STANDBY_LIST_DATA
	{
		U64				regionId;
		U64				campaignId;

		Byte			force;					//0.攻击方 1.防守方
		Int				standbyCount;
		NetStandByList	standbyList[1];
	};
	struct PT_CAMPAIGN_SC_STANDBY_LIST_DATA_INFO
	{
		static const Int    netStandbyListSize = sizeof (NetStandByList);
		static const Int    headSize = sizeof (PT_CAMPAIGN_SC_STANDBY_LIST_DATA) - sizeof( NetStandByList );
		static Int          dataSize(PT_CAMPAIGN_SC_STANDBY_LIST_DATA* data)
		{ 
			return PT_CAMPAIGN_SC_STANDBY_LIST_DATA_INFO::headSize + PT_CAMPAIGN_SC_STANDBY_LIST_DATA_INFO::netStandbyListSize * data->standbyCount;
		};
		//static const Int dataSize = sizeof(PT_CAMPAIGN_SC_STANDBY_LIST_DATA);
	};

	//////////////////////////////////////////////////////////////////////////////////
	//进入选中的战役房位置
	struct PT_CAMPAIGN_C2F_JOIN_STANDBY_DATA
	{
		U64		regionId;
		U64		campaignId;
		U64		creatorId;				//房主
		U64		joinClanId;				//目标

	};
	struct PT_CAMPAIGN_C2F_JOIN_STANDBY_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_C2F_JOIN_STANDBY_DATA);
	};

	//////////////////////////////////////////////////////////////////////////////////
	struct PT_CAMPAIGN_F2M_JOIN_STANDBY_DATA
	{
		U64		accountId;

		U64		regionId;
		U64		campaignId;
		U64		creatorId;				//房主
		U64		joinClanId;
	};
	struct PT_CAMPAIGN_F2M_JOIN_STANDBY_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_F2M_JOIN_STANDBY_DATA);
	};

	//////////////////////////////////////////////////////////////////////////////////

	struct PT_CAMPAIGN_SC_JOIN_STANDBY_DATA
	{
		U64		regionId;
		U64		campaignId;
		U64		joinClanId;
	};
	struct PT_CAMPAIGN_SC_JOIN_STANDBY_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_SC_JOIN_STANDBY_DATA);
	};

	//////////////////////////////////////////////////////////////////////////////////

	//进入选中的战役房位置【自己操作】
	struct PT_CAMPAIGN_C2F_JOIN_STANDBY_MYSELF_DATA 
	{
		U64		regionId;
		U64		campaignId;
		U64		joinClanId;			//进入位置的人
		Byte	force;				//0. 攻击， 1.防守
		Byte	position;			//位置

	};
	struct PT_CAMPAIGN_C2F_JOIN_STANDBY_MYSELF_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_C2F_JOIN_STANDBY_MYSELF_DATA);
	};

	//////////////////////////////////////////////////////////////////////////////////

	struct PT_CAMPAIGN_F2M_JOIN_STANDBY_MYSELF_DATA
	{
		U64		accountId;

		U64		regionId;
		U64		campaignId;
		U64		joinClanId;
		Byte	force;				//0. 攻击， 1.防守
		Byte	position;			//位置
		Char16	clanName[MAX_CLAN_NAME];
	};
	struct PT_CAMPAIGN_F2M_JOIN_STANDBY_MYSELF_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_F2M_JOIN_STANDBY_MYSELF_DATA);
	};

	//////////////////////////////////////////////////////////////////////////////////

	struct PT_CAMPAIGN_SC_JOIN_STANDBY_MYSELF_DATA
	{
		U64		regionId;
		U64		campaignId;
		U64		joinClanId;
		Byte	force;				//0. 攻击， 1.防守
		Byte	position;			//位置
		Char16	clanName[MAX_CLAN_NAME];
		U64 	myHeroId;			//选择的武将ID
		U64 	myTroopId;			//选择的军队ID
	};
	struct PT_CAMPAIGN_SC_JOIN_STANDBY_MYSELF_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_SC_JOIN_STANDBY_MYSELF_DATA);
	};
#endif

	//////////////////////////////////////////////////////////////////////////////////
#if 0
	struct PT_CAMPAIGN_C2F_JOIN_WATING_DATA
	{
		U64		regionId;
		U64		campaignId;
		U64		creatorId;				//房主
		U64		joinClanId;				//目标
	};
	struct PT_CAMPAIGN_C2F_JOIN_WATING_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_C2F_JOIN_WATING_DATA);
	};

	//////////////////////////////////////////////////////////////////////////////////

	struct PT_CAMPAIGN_F2M_JOIN_WATING_DATA
	{
		U64		accountId;

		U64		regionId;
		U64		campaignId;
		U64		creatorId;				//房主
		U64		joinClanId;				//目标
	};
	struct PT_CAMPAIGN_F2M_JOIN_WATING_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_F2M_JOIN_WATING_DATA);
	};

	//////////////////////////////////////////////////////////////////////////////////

	struct PT_CAMPAIGN_SC_JOIN_WATING_DATA
	{
		U64		regionId;
		U64		campaignId;
		U64		joinClanId;

	};
	struct PT_CAMPAIGN_SC_JOIN_WATING_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_SC_JOIN_WATING_DATA);
	};

	//////////////////////////////////////////////////////////////////////////////////

	//确认准备
	struct PT_CAMPAIGN_C2F_READY_DATA
	{
		U64 	regionId;
		U64 	campaignId;
		U64 	myClanId;
		U64		targetClanId;
		Byte	readyState;		//1. 确认   2.取消
	};
	struct PT_CAMPAIGN_C2F_READY_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_C2F_READY_DATA);
	};

	//////////////////////////////////////////////////////////////////////////////////

	struct PT_CAMPAIGN_F2M_READY_DATA
	{
		U64		accountId;
		U64 	regionId;
		U64 	campaignId;
		U64 	myClanId;
		U64		targetClanId;
		Byte	readyState;		//1. 确认   2.取消
	};
	struct PT_CAMPAIGN_F2M_READY_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_F2M_READY_DATA);
	};

	//////////////////////////////////////////////////////////////////////////////////

	struct PT_CAMPAIGN_SC_READY_DATA
	{
		U64 	regionId;
		U64 	campaignId;
		U64 	clanId;
		Byte	readyState;		//1. 确认   2.取消
	};
	struct PT_CAMPAIGN_SC_READY_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_SC_READY_DATA);
	};
#endif
	//////////////////////////////////////////////////////////////////////////////////
#if 0
	//发送玩家的征战部队信息
	struct PT_CAMPAIGN_CS_ARMYLIST_DATA
	{
		U64								regionId;
		U64								campaignId;
		U64								myClanId;
		NetCampaignPlayCharacterInfo	playCharacterInfo;
		NetCampaignTroopInfo			troopInfo;
	};
	struct PT_CAMPAIGN_CS_ARMYLIST_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_CS_ARMYLIST_DATA);
	};

	//////////////////////////////////////////////////////////////////////////////////

	struct PT_CAMPAIGN_SC_ARMYLIST_DATA
	{
		U64								clanId;
		NetCampaignPlayCharacterInfo	playCharacterInfo;
		NetCampaignTroopInfo			troopInfo;
	};
	struct PT_CAMPAIGN_SC_ARMYLIST_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_SC_ARMYLIST_DATA);
	};
#endif
	//////////////////////////////////////////////////////////////////////////////////
#if 0
	//踢出玩家
	struct PT_CAMPAIGN_C2F_KICK_CLAN_DATA
	{
		U64		regionId;
		U64 	campaignId;
		U64 	clanId;
		U64 	kickClanId;
		Byte	force;
		Byte	position;
	};
	struct PT_CAMPAIGN_C2F_KICK_CLAN_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_C2F_KICK_CLAN_DATA);
	};

	//////////////////////////////////////////////////////////////////////////////////

	struct PT_CAMPAIGN_F2M_KICK_CLAN_DATA
	{
		U64		accountId;

		U64 	regionId;
		U64 	campaignId;
		U64 	clanId;
		U64 	kickClanId;
		Byte	force;
		Byte	position;
	};
	struct PT_CAMPAIGN_F2M_KICK_CLAN_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_F2M_KICK_CLAN_DATA);
	};

	//////////////////////////////////////////////////////////////////////////////////

	//踢出玩家
	struct PT_CAMPAIGN_SC_KICK_CLAN_DATA
	{
		U64 	regionId;
		U64 	campaignId;
		U64		kickClanId;
		Byte	force;
		Byte	position;
	};
	struct PT_CAMPAIGN_SC_KICK_CLAN_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_SC_KICK_CLAN_DATA);
	};
#endif
	//////////////////////////////////////////////////////////////////////////////////

#if 0
	struct PT_CAMPAIGN_T2F_INVITE_DEFENSE_REGION_DATA
	{
		//AccountIdType		accountId;
		//ClanIdType			clanId;
		//U64					playerCharacterId;
		U64					toRegionId;
		InstanceIdType		toInstanceId;		//0: 第一次进入该区域， >0: 进入指定的副本区域
		//JUMP_TYPE			jumpType;			//
		//Byte				jumpIndex;			//
	};

	struct PT_CAMPAIGN_T2F_INVITE_DEFENSE_REGION_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_T2F_INVITE_DEFENSE_REGION_DATA);
	};

	//////////////////////////////////////////////////////////////////////////////////
	struct PT_CAMPAIGN_F2M_INVITE_DEFENSE_REGION_DATA
	{
		//AccountIdType		accountId;
		//ClanIdType			clanId;
		//U64					playerCharacterId;
		RegionIdType		toRegionId;
		InstanceIdType		toInstanceId;		//0: 第一次进入该区域， >0: 进入指定的副本区域
		//JUMP_TYPE			jumpType;			//
		//Byte				jumpIndex;			//
	};

	struct PT_CAMPAIGN_F2M_INVITE_DEFENSE_REGION_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_F2M_INVITE_DEFENSE_REGION_DATA);
	};
#endif
#if 0
#endif

#if 0
#endif
	//////////////////////////////////////////////////////////////////////////////////
#if 0
#endif
	//////////////////////////////////////////////////////////////////////////////////
#if 0
	struct PT_CAMPAIGN_SC_ERROR_DATA
	{
		CAMPAIGN_ERROR	error;
	};

	struct PT_CAMPAIGN_SC_ERROR_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_CAMPAIGN_SC_ERROR_DATA);
	};
#endif
#if 0
#endif

	//////////////////////////////////////////////////////////////////////////////////
#pragma pack (pop)
}

/******************************************************************************/

#endif	//_CAMPAIGNNETPACKET_H_