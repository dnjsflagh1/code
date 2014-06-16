/******************************************************************************/
#ifndef _PLAYERCHARACTERNETPACKET_H_
#define _PLAYERCHARACTERNETPACKET_H_
/******************************************************************************/
#include "CommonGameDefine.h"
#include "NetDefine.h"
/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //玩家角色包类型
    /******************************************************************************/
    enum PlayerCharacterNetPacketType
    {
		PT_PLAYERCHARACTER_UNKNOWN = 0,

		
		/*元林虎*/PT_PLAYERCHARACTER_C2F_JUMP_REGION,		// [Client -> Server] 角色跳转区域
		/*元林虎*/PT_PLAYERCHARACTER_F2M_JUMP_REGION,
		/*元林虎*/PT_PLAYERCHARACTER_M2F_JUMP_REGION,
		/*元林虎*/PT_PLAYERCHARACTER_F2C_JUMP_REGION,
		/*元林虎*/PT_PLAYERCHARACTER_F2M_JUMP_EMPTY_REGION,	//切换武将， 把某个武将的指针从地图删除
		/*元林虎*/PT_PLAYERCHARACTER_C2F_JUMP_REGION_TIRO,	//跳入新手副本

		//另外3种跳地图方式
		/*元林虎*/PT_PLAYERCHARACTER_C2F_JUMP_OUT_REGION,			//从Place跳转到大地图
		/*元林虎*/PT_PLAYERCHARACTER_F2M_JUMP_CAMPAIGN_REGION,	//战斗副本地图
		/*元林虎*/PT_PLAYERCHARACTER_C2F_JUMP_LAST_REGION,		//跳回上一个地图

#if 0
		PT_PLAYERCHARACTER_M2F_CHANGE_REGION,		//在MapServer改变了 副本信息， 同步到FrontServer
#endif

		/*季晶晶*/PT_PLAYERCHARACTER_C2S_MOVE_POS,		// [Client -> Server] 位置移动
        /*季晶晶*/PT_PLAYERCHARACTER_S2C_MOVE_POS,		// [Server -> Client] 位置移动
		/*季晶晶*/PT_PLAYERCHARACTER_C2S_STOP_MOVE,
		/*季晶晶*/PT_PLAYERCHARACTER_S2C_STOP_MOVE,

		/*季晶晶*/PT_PLAYERCHARACTER_F2C_SKILL_INFO,		//发送技能信息
		/*季晶晶*/PT_PLAYERCHARACTER_F2M_SKILL_INFO,		//发送技能信息

		/*季晶晶*/PT_PLAYERCHARACTER_S2C_ENTER_FIGHT,
		/*季晶晶*/PT_PLAYERCHARACTER_S2C_END_FIGHT,
    };

#pragma pack (push)
#pragma pack (1)
//**********************************************************************

	//-----------------------------------------------------
	enum ChatarcterJumpRegionResult
	{
		ChatarcterJumpRegionResult_Succeed,
		ChatarcterJumpRegionResult_Fail,

		ChatarcterJumpRegionResult_Fail_Crash,
	};


	/**********************************************************************
    //@名字:        PT_PLAYERCHARACTER_C2F_JUMP_REGION
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_PLAYERCHARACTER_C2F_JUMP_REGION_DATA
	{
		PlayerCharacterIdType	playerCharacterId;
		RegionIdType			toRegionId;
		Byte					toRegionType;
		InstanceUIdType			toInstanceUId;			//0: 第一次进入该区域， >0: 进入指定的副本区域
		Int						pointId;				//跳转点 id
		//跳转点：
	};

	struct PT_PLAYERCHARACTER_C2F_JUMP_REGION_INFO
	{
		static const Int dataSize = sizeof (PT_PLAYERCHARACTER_C2F_JUMP_REGION_DATA);
	};

	class PT_PLAYERCHARACTER_C2F_JUMP_REGION_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_PLAYERCHARACTER_C2F_JUMP_REGION_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_PLAYER_CHARACTER;
            mType                               =   PT_PLAYERCHARACTER_C2F_JUMP_REGION;
            mBaseDataSize                       =   PT_PLAYERCHARACTER_C2F_JUMP_REGION_INFO::dataSize ;

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

    // 角色区域跳转:
	//-----------------------------------------------------
	//struct PT_PLAYERCHARACTER_C2F_JUMP_REGION_DATA
	//{
	//	PlayerCharacterIdType	playerCharacterId;
	//	RegionIdType			toRegionId;
	//	Byte					toRegionType;
	//	InstanceUIdType			toInstanceUId;			//0: 第一次进入该区域， >0: 进入指定的副本区域
	//	Int						pointId;				//跳转点 id
	//	//跳转点：
	//};
 //   struct PT_PLAYERCHARACTER_C2F_JUMP_REGION_DATA_INFO
 //   {
 //       static const Int dataSize = sizeof (PT_PLAYERCHARACTER_C2F_JUMP_REGION_DATA);
 //   };

	/**********************************************************************
    //@名字:        PT_PLAYERCHARACTER_C2F_JUMP_REGION_TIRO
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_PLAYERCHARACTER_C2F_JUMP_REGION_TIRO_DATA
	{
		PlayerCharacterIdType	playerCharacterId;
		RegionIdType			toRegionId;
		Byte					toRegionType;
		InstanceUIdType			toInstanceUId;			//0: 第一次进入该区域， >0: 进入指定的副本区域
		Int						pointId;				//跳转点 id
		NetIdType				mapServerNetId;
	};

	struct PT_PLAYERCHARACTER_C2F_JUMP_REGION_TIRO_INFO
	{
		static const Int dataSize = sizeof (PT_PLAYERCHARACTER_C2F_JUMP_REGION_TIRO_DATA);
	};

	class PT_PLAYERCHARACTER_C2F_JUMP_REGION_TIRO_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_PLAYERCHARACTER_C2F_JUMP_REGION_TIRO_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_PLAYER_CHARACTER;
            mType                               =   PT_PLAYERCHARACTER_C2F_JUMP_REGION_TIRO;
            mBaseDataSize                       =   PT_PLAYERCHARACTER_C2F_JUMP_REGION_TIRO_INFO::dataSize ;

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
    //@名字:        PT_PLAYERCHARACTER_F2M_JUMP_REGION
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_PLAYERCHARACTER_F2M_JUMP_REGION_DATA
	{
		PlayerCharacterIdType		playerCharacterId;
		RegionIdType				toRegionId;
		Byte						toRegionType;
		InstanceUIdType				toInstanceId;
		Int							pointId;
	};
	struct PT_PLAYERCHARACTER_F2M_JUMP_REGION_INFO
	{
		static const Int dataSize = sizeof (PT_PLAYERCHARACTER_F2M_JUMP_REGION_DATA);
	};


	class PT_PLAYERCHARACTER_F2M_JUMP_REGION_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_PLAYERCHARACTER_F2M_JUMP_REGION_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_PLAYER_CHARACTER;
            mType                               =   PT_PLAYERCHARACTER_F2M_JUMP_REGION;
            mBaseDataSize                       =   PT_PLAYERCHARACTER_F2M_JUMP_REGION_INFO::dataSize ;

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

  //  struct PT_PLAYERCHARACTER_F2M_JUMP_REGION_DATA
  //  {
  //      PlayerCharacterIdType		playerCharacterId;
		//RegionIdType				toRegionId;
		//Byte						toRegionType;
		//InstanceUIdType				toInstanceId;
		//Int							pointId;
  //  };
  //  struct PT_PLAYERCHARACTER_F2M_JUMP_REGION_DATA_INFO
  //  {
  //      static const Int dataSize = sizeof (PT_PLAYERCHARACTER_F2M_JUMP_REGION_DATA);
  //  };


	//-----------------------------------------------------

	/**********************************************************************
    //@名字:        PT_PLAYERCHARACTER_M2F_JUMP_REGION
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_PLAYERCHARACTER_M2F_JUMP_REGION_DATA
	{
		U64							clientNetIdInFront;
		PlayerCharacterIdType		playerCharacterId;
		RegionIdType				toRegionId;
		Byte						toRegionType;
		InstanceUIdType				toInstanceId;			//所属副本id
		ChatarcterJumpRegionResult	jumpResult;
	};
	struct PT_PLAYERCHARACTER_M2F_JUMP_REGION_INFO
	{
		static const Int dataSize = sizeof (PT_PLAYERCHARACTER_M2F_JUMP_REGION_DATA);
	};


	class PT_PLAYERCHARACTER_M2F_JUMP_REGION_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_PLAYERCHARACTER_M2F_JUMP_REGION_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_PLAYER_CHARACTER;
            mType                               =   PT_PLAYERCHARACTER_M2F_JUMP_REGION;
            mBaseDataSize                       =   PT_PLAYERCHARACTER_M2F_JUMP_REGION_INFO::dataSize ;

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

	//struct PT_PLAYERCHARACTER_M2F_JUMP_REGION_DATA
	//{
	//	U64							clientNetIdInFront;
	//	PlayerCharacterIdType		playerCharacterId;
	//	RegionIdType				toRegionId;
	//	Byte						toRegionType;
	//	InstanceUIdType				toInstanceId;			//所属副本id
	//	ChatarcterJumpRegionResult	jumpResult;
	//};
	//struct PT_PLAYERCHARACTER_M2F_JUMP_REGION_DATA_INFO
	//{
	//	static const Int dataSize = sizeof (PT_PLAYERCHARACTER_M2F_JUMP_REGION_DATA);
	//};


	//**********************************************************************
	/**********************************************************************
    //@名字:        PT_PLAYERCHARACTER_F2C_JUMP_REGION
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_PLAYERCHARACTER_F2C_JUMP_REGION_DATA
	{
		Byte					jumpResult;
		PlayerCharacterIdType	playerCharacterId;
		RegionIdType			regionId;
		Byte					regionType;
		InstanceUIdType			instanceUId;
	};

	struct PT_PLAYERCHARACTER_F2C_JUMP_REGION_INFO
	{
		static const Int dataSize = sizeof (PT_PLAYERCHARACTER_F2C_JUMP_REGION_DATA);
	};

	class PT_PLAYERCHARACTER_F2C_JUMP_REGION_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_PLAYERCHARACTER_F2C_JUMP_REGION_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_PLAYER_CHARACTER;
            mType                               =   PT_PLAYERCHARACTER_F2C_JUMP_REGION;
            mBaseDataSize                       =   PT_PLAYERCHARACTER_F2C_JUMP_REGION_INFO::dataSize ;

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

	//struct PT_PLAYERCHARACTER_F2C_JUMP_REGION_DATA
	//{
	//	Byte					jumpResult;
	//	PlayerCharacterIdType	playerCharacterId;
	//	RegionIdType			regionId;
	//	Byte					regionType;
	//	InstanceUIdType			instanceUId;
	//};

	//struct PT_PLAYERCHARACTER_F2C_JUMP_REGION_DATA_INFO
	//{
	//	static const Int dataSize = sizeof (PT_PLAYERCHARACTER_F2C_JUMP_REGION_DATA);
	//};

	//**********************************************************************

	/**********************************************************************
    //@名字:        PT_PLAYERCHARACTER_F2M_JUMP_EMPTY_REGION
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_PLAYERCHARACTER_F2M_JUMP_EMPTY_REGION_DATA
	{
		AccountIdType			accountId;
		PlayerCharacterIdType	playerCharacterId;
	};

	struct PT_PLAYERCHARACTER_F2M_JUMP_EMPTY_REGION_INFO
	{
		static const Int dataSize = sizeof (PT_PLAYERCHARACTER_F2M_JUMP_EMPTY_REGION_DATA);
	};

	class PT_PLAYERCHARACTER_F2M_JUMP_EMPTY_REGION_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_PLAYERCHARACTER_F2M_JUMP_EMPTY_REGION_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_PLAYER_CHARACTER;
            mType                               =   PT_PLAYERCHARACTER_F2M_JUMP_EMPTY_REGION;
            mBaseDataSize                       =   PT_PLAYERCHARACTER_F2M_JUMP_EMPTY_REGION_INFO::dataSize ;

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
    //@名字:        PT_PLAYERCHARACTER_C2F_JUMP_OUT_REGION
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_PLAYERCHARACTER_C2F_JUMP_OUT_REGION_DATA
	{
		AccountIdType			accountId;
		PlayerCharacterIdType	playerCharacterId;
	};

	struct PT_PLAYERCHARACTER_C2F_JUMP_OUT_REGION_INFO
	{
		static const Int dataSize = sizeof (PT_PLAYERCHARACTER_C2F_JUMP_OUT_REGION_DATA);
	};
	class PT_PLAYERCHARACTER_C2F_JUMP_OUT_REGION_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_PLAYERCHARACTER_C2F_JUMP_OUT_REGION_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_PLAYER_CHARACTER;
            mType                               =   PT_PLAYERCHARACTER_C2F_JUMP_OUT_REGION;
            mBaseDataSize                       =   PT_PLAYERCHARACTER_C2F_JUMP_OUT_REGION_INFO::dataSize ;

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

	//struct PT_PLAYERCHARACTER_C2F_JUMP_OUT_REGION_DATA
	//{
	//	AccountIdType			accountId;
	//	PlayerCharacterIdType	playerCharacterId;
	//};

	//struct PT_PLAYERCHARACTER_C2F_JUMP_OUT_REGION_DATA_INFO
	//{
	//	static const Int dataSize = sizeof (PT_PLAYERCHARACTER_C2F_JUMP_OUT_REGION_DATA);
	//};

	//-----------------------------------------------------

	/**********************************************************************
    //@名字:        PT_PLAYERCHARACTER_F2M_JUMP_CAMPAIGN_REGION
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_PLAYERCHARACTER_F2M_JUMP_CAMPAIGN_REGION_DATA
	{
		PlayerCharacterIdType		playerCharacterId;
		RegionIdType				toRegionId;
		Byte						toRegionType;
		InstanceIdType				toInstanceId;
		Byte						jumpType;
		Byte						jumpIndex;
		Bool						isBattleLeader;		//是否是攻击方或 防守方的 队长
		U32							prepareTimeSecond;			//准备的时间  【秒】

		PT_PLAYERCHARACTER_F2M_JUMP_CAMPAIGN_REGION_DATA()
			:isBattleLeader(false)
		{
		}
	};

	struct PT_PLAYERCHARACTER_F2M_JUMP_CAMPAIGN_REGION_INFO
	{
		static const Int dataSize = sizeof (PT_PLAYERCHARACTER_F2M_JUMP_CAMPAIGN_REGION_DATA);
	};

	class PT_PLAYERCHARACTER_F2M_JUMP_CAMPAIGN_REGION_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_PLAYERCHARACTER_F2M_JUMP_CAMPAIGN_REGION_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_PLAYER_CHARACTER;
            mType                               =   PT_PLAYERCHARACTER_F2M_JUMP_CAMPAIGN_REGION;
            mBaseDataSize                       =   PT_PLAYERCHARACTER_F2M_JUMP_CAMPAIGN_REGION_INFO::dataSize ;

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

	//struct PT_PLAYERCHARACTER_F2M_JUMP_CAMPAIGN_REGION_DATA
	//{
	//	PlayerCharacterIdType		playerCharacterId;
	//	RegionIdType				toRegionId;
	//	Byte						toRegionType;
	//	InstanceIdType				toInstanceId;
	//	Byte						jumpType;
	//	Byte						jumpIndex;
	//	Bool						isBattleLeader;		//是否是攻击方或 防守方的 队长
	//	U32							prepareTimeSecond;			//准备的时间  【秒】

	//	PT_PLAYERCHARACTER_F2M_JUMP_CAMPAIGN_REGION_DATA()
	//	{
	//		isBattleLeader = false;
	//	}
	//};

	//struct PT_PLAYERCHARACTER_F2M_JUMP_CAMPAIGN_REGION_DATA_INFO
	//{
	//	static const Int dataSize = sizeof (PT_PLAYERCHARACTER_F2M_JUMP_CAMPAIGN_REGION_DATA);
	//};

	//**********************************************************************
	/**********************************************************************
    //@名字:        PT_PLAYERCHARACTER_C2F_JUMP_LAST_REGION
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_PLAYERCHARACTER_C2F_JUMP_LAST_REGION_DATA
	{
		PlayerCharacterIdType	playerCharacterId;
	};

	struct PT_PLAYERCHARACTER_C2F_JUMP_LAST_REGION_INFO
	{
		static const Int dataSize = sizeof (PT_PLAYERCHARACTER_C2F_JUMP_LAST_REGION_DATA);
	};

	class PT_PLAYERCHARACTER_C2F_JUMP_LAST_REGION_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_PLAYERCHARACTER_C2F_JUMP_LAST_REGION_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_PLAYER_CHARACTER;
            mType                               =   PT_PLAYERCHARACTER_C2F_JUMP_LAST_REGION;
            mBaseDataSize                       =   PT_PLAYERCHARACTER_C2F_JUMP_LAST_REGION_INFO::dataSize ;

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

	//struct PT_PLAYERCHARACTER_C2F_JUMP_LAST_REGION_DATA
	//{
	//	PlayerCharacterIdType	playerCharacterId;
	//};

	//struct PT_PLAYERCHARACTER_C2F_JUMP_LAST_REGION_DATA_INFO
	//{
	//	static const Int dataSize = sizeof (PT_PLAYERCHARACTER_C2F_JUMP_LAST_REGION_DATA);
	//};
	

	////**********************************************************************
#if 0
	struct PT_PLAYERCHARACTER_M2F_CHANGE_REGION_DATA
	{
		U64				playerCharacterId;
		Byte			toRegionType;
		UInt			toRegionID;
		I32				toInstanceId;			//所属副本id
	};

	struct PT_PLAYERCHARACTER_M2F_CHANGE_REGION_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_PLAYERCHARACTER_M2F_CHANGE_REGION_DATA);
	};
#endif

    //**********************************************************************
	struct PT_PLAYERCHARACTER_C2S_MOVE_POS_DATA
	{
		GameObjectIndexIdInSceneType	playercharacterIndex;
		NetVec2Data 					startMovePos;
		NetVec2Data 					endMovePos;
		Bool							isBlockCheck;
	};

    struct PT_PLAYERCHARACTER_C2S_MOVE_POS_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_PLAYERCHARACTER_C2S_MOVE_POS_DATA);
    };

	//-----------------------------------------------------
	struct PT_PLAYERCHARACTER_S2C_MOVE_POS_DATA
	{
		GameObjectIndexIdInSceneType	playercharacterIndex;
		NetVec2Data 					startMovePos;
		NetVec2Data 					endMovePos;
		U64								startMoveTime;
		Bool							isBlockCheck;
	};
    struct PT_PLAYERCHARACTER_S2C_MOVE_POS_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_PLAYERCHARACTER_S2C_MOVE_POS_DATA);
    };

	//**********************************************************************
	struct PT_PLAYERCHARACTER_C2S_STOP_MOVE_DATA
	{
		GameObjectIndexIdInSceneType				playercharacterIndex;
	};

	struct PT_PLAYERCHARACTER_C2S_STOP_MOVE_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_PLAYERCHARACTER_C2S_STOP_MOVE_DATA);
	};

	//-----------------------------------------------------
	struct PT_PLAYERCHARACTER_S2C_STOP_MOVE_DATA
	{
		GameObjectIndexIdInSceneType				playercharacter_index;
	};

	struct PT_PLAYERCHARACTER_S2C_STOP_MOVE_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_PLAYERCHARACTER_S2C_STOP_MOVE_DATA);
	};

	//**********************************************************************
	struct PT_PLAYERCHARACTER_F2C_SKILL_INFO_DATA
	{
		IdType			playercharacterId;
		UInt			skillNum;
		SkillNetData	skillList[1];
	};
    struct PT_PLAYERCHARACTER_F2C_SKILL_INFO_DATA_INFO
    {
        static const Int headSize   = sizeof (PT_PLAYERCHARACTER_F2C_SKILL_INFO_DATA) - sizeof (SkillNetData);
        static const Int elemetSize = sizeof (SkillNetData);
    };

	//-------------------------------------------------------------------------------
	struct PT_PLAYERCHARACTER_F2M_SKILL_INFO_DATA 
	{
		IdType			playercharacterId;
		UInt			skillNum;
		SkillNetData	skillList[1];
	};
	struct PT_PLAYERCHARACTER_F2M_SKILL_INFO_DATA_INFO
	{
		static const Int headSize   = sizeof (PT_PLAYERCHARACTER_F2M_SKILL_INFO_DATA) - sizeof (SkillNetData);
		static const Int elemetSize = sizeof (SkillNetData);
	};

	//**********************************************************************
	struct PT_PLAYERCHARACTER_S2C_ENTER_FIGHT_DATA
	{
		GameObjectIndexIdInSceneType			playercharacterIndex;
	};
	struct PT_PLAYERCHARACTER_S2C_ENTER_FIGHT_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_PLAYERCHARACTER_S2C_ENTER_FIGHT_DATA);
	};

	//-------------------------------------------------------------------------------
	struct PT_PLAYERCHARACTER_S2C_END_FIGHT_DATA
	{
		GameObjectIndexIdInSceneType			playercharacterIndex;
	};
	struct PT_PLAYERCHARACTER_S2C_END_FIGHT_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_PLAYERCHARACTER_S2C_END_FIGHT_DATA);
	};

	//**********************************************************************
	//角色信息
	struct CharInfo 
	{
		UInt	id;
		UInt	accountId;
		UInt	serverId;
		Char16	name[MAX_ACCOUNT_LONGIN_NAME_LEN];
		U8		state;
	};

	//**********************************************************************
	//FrontServer返回给Client的角色列表 
	struct PT_LOGIN_F2C_CHARACTER_LIST_DATA
	{
		I8 charNum;
		Char charList[1];//角色列表
	};
    struct PT_LOGIN_F2C_CHARACTER_LIST_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_F2C_CHARACTER_LIST_DATA);
    };
	//**********************************************************************
	struct PT_LOGIN_C2F_SELECT_CHARACTER_DATA
	{
		UInt characterId;
	};
    struct PT_LOGIN_C2F_SELECT_CHARACTER_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_C2F_SELECT_CHARACTER_DATA);
    };
#pragma pack (pop)
}

/******************************************************************************/

#endif