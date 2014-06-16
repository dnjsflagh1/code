/******************************************************************************/
#ifndef _REGIONNETPACKET_H_
#define _REGIONNETPACKET_H_
/******************************************************************************/

#include "CommonGameDefine.h"
#include "NetDefine.h"
#include "GameNetPacket.h"

/******************************************************************************/



/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//区域数据包想关类型
	/******************************************************************************/
	enum RegionNetPacketType
	{
		PT_REGION_UNKNOW = 0,

		/*元林虎*/PT_REGION_M2C_ADD_PLAYER_CHARACTER,		//区域增加玩家角色
		/*元林虎*/PT_REGION_M2C_REMOVE_PLAYER_CHARACTER,	//区域移除玩家角色

		/*元林虎*/PT_REGION_C2F_ADD_BUILDING,				//区域增加建筑物
		/*元林虎*/PT_REGION_F2M_ADD_BUILDING,
		/*元林虎*/PT_REGION_M2C_ADD_BUILDING,

		/*元林虎*/PT_REGION_M2C_ADD_MONSTER,				// 增加怪物
		/*元林虎*/PT_REGION_M2C_MONSTER_ALIVE,				// 怪物复活
		
		/*元林虎*/PT_REGION_M2C_MONSTER_AI_CONTROL,			//Monter AI 的 控制权

		/*元林虎*/PT_REGION_M2C_CREATE_TROOP,				//创建军队， 客户端需要计算 军队的位子，并把位子信息反馈给服务器，然后广播给其他客户端
		/*元林虎*/PT_REGION_C2F_CREATE_TROOP_RET,			//返回军队和士兵的位置
		/*元林虎*/PT_REGION_F2M_CREATE_TROOP_RET,
		/*元林虎*/PT_REGION_M2C_ADD_TROOP,					//新军队正式进入地图

		/*元林虎*/PT_REGION_M2C_END_LOAD_SCENE,				//场景加载完成

		/*元林虎*/PT_REGION_C2F_PLAYER_CHARACTER_ALIVE,
		/*元林虎*/PT_REGION_F2M_PLAYER_CHARACTER_ALIVE,
		/*元林虎*/PT_REGION_M2F_PLAYER_CHARACTER_ALIVE,		//玩家角色复活
		/*元林虎*/PT_REGION_F2C_PLAYER_CHARACTER_ALIVE,
		/*元林虎*/PT_REGION_M2C_PLAYER_CHARACTER_ALIVE,

		/*元林虎*/PT_REGION_C2M_TEST,						//测试用的消息
		/*元林虎*/PT_REGION_C2M_TEST1,						//测试用的消息
		/*元林虎*/PT_REGION_C2M_ADD_TROOP_TEST,				//测试版本， 通过快捷键 手动创建军队


		/*待定,暂不用*/PT_REGION_C2F_REMOVE_BUILDING,		//区域移除建筑物
		/*待定,暂不用*/PT_REGION_F2M_REMOVE_BUILDING,
		/*待定,暂不用*/PT_REGION_M2C_REMOVE_BUILDING,

		/*季晶晶*/PT_REGION_M2C_CREATE_APPEAR_PLAYER_CHARACTER,
		/*季晶晶*/PT_REGION_M2C_DESTROY_DISAPPEAR_PLAYER_CHARACTER,

		/*季晶晶*/PT_REGION_M2C_APPEAR_PLAYER_CHARACTER,
		/*季晶晶*/PT_REGION_M2C_DISAPPEAR_PLAYER_CHARACTER,

		/*季晶晶*/PT_REGION_M2C_CREATE_APPEAR_BUILDING,
		/*季晶晶*/PT_REGION_M2C_DESTROY_DISAPPEAR_BUILDING,

		/*季晶晶*/PT_REGION_M2C_APPEAR_BUILDING,
		/*季晶晶*/PT_REGION_M2C_DISAPPEAR_BUILDING,

		/*季晶晶*/PT_REGION_M2C_CREATE_APPEAR_MONSTER,
		/*季晶晶*/PT_REGION_M2C_DESTROY_DISAPPEAR_MONSTER,

		/*季晶晶*/PT_REGION_M2C_APPEAR_MONSTER,
		/*季晶晶*/PT_REGION_M2C_DISAPPEAR_MONSTER,

		/*季晶晶*/PT_REGION_M2C_CREATE_APPEAR_TROOP,
		/*季晶晶*/PT_REGION_M2C_DESTROY_DISAPPEAR_TROOP,

		/*季晶晶*/PT_REGION_M2C_APPEAR_TROOP_SOLDIER,
		/*季晶晶*/PT_REGION_M2C_DISAPPEAR_TROOP_SOLDIER,

		PT_REGION_MAX
	};

	//**********************************************************************

#pragma pack (push)
#pragma pack (1)
	
	//**********************************************************************
	struct NetMonsterIdInfo
	{
		MonsterIdType	monsterId;
	};

	//区域增加建筑物
	struct NetAddBuildingInfo
	{
		U64				uId;					//唯一的标示符 由Mapserver生成，并广播给客户端
		U64				belongAccountId;		//所属者ID
		U64				buildingTemplateId;		//模板Id
		Byte			buildingType;
		U64	    		regionId;

		Byte			force;					//势力

		NetVec2Data 	pos;					//位置
		NetVec2Data 	dir;					//方向
		Int				hp;
	};

		
	//军队
	struct NetAddTroopInfo
	{
		Byte				force;
		U64					playerId;
		U64					troopId;
		U64					troopTemplateId;
		NetVec2Data 		pos;
		NetVec2Data 		dir;	
		Int					hp;
		Int					mp;
		Int					maxHp;
		Int					maxMp;
		Flt					moveSpeed;

		Int					soldierNum;			//有几个军队
		//NetVec2Data 		soldierPos[50];		//暂时用于测试
	};
	
	struct NetAddPlayerCharacterInfo
	{
		U64				playerId;
		U64				character_id;
		U32             characterTemplateID;            //角色模板ID
		Char16			name[MAX_CHARACTER_NAME_LEN];
		Char16          surNmae[MAX_CHARACTER_NAME_LEN]; 
        UInt            artIconId;
        U32             level;
		//位置
		NetVec2Data		pos;
		NetVec2Data		moveToPos;

		//朝向
		NetVec2Data 	dir;

		Int				mp;
		Int				hp;
		Int             mpmax;
		Int             hpmax;
		Byte			force;			//势力
		Bool			isBattleLeader;
		Flt				moveSpeed;
	};

	//怪物
	struct NetAddMonsterInfo
	{
		//AccountIdType	controllerAccountId;
		U64				monsterId;			//UID
		U64				charTemplateId;
        

		Char16			name[MAX_CHARACTER_NAME_LEN];
		Char16          surNmae[MAX_CHARACTER_NAME_LEN]; 
        UInt            artIconId;
        U32             level;

		NetVec2Data 	pos;
		NetVec2Data 	moveToPos;
		NetVec2Data 	dir;

		Int				maxHp;
		Int				maxMp;

		Int				hp;
		Int				mp;

		Flt				moveSpeed;
	};

	/**********************************************************************
    //@名字:        PT_REGION_M2C_ADD_PLAYER_CHARACTER
    //@功能:        区域增加一个玩家角色
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_REGION_M2C_ADD_PLAYER_CHARACTER_DATA
	{
		Int								addPlayerNum;
		NetAddPlayerCharacterInfo		addPlayerInfo[1];
	};
	struct PT_REGION_M2C_ADD_PLAYER_CHARACTER_INFO
	{
		static Int  const headSize        = sizeof (PT_REGION_M2C_ADD_PLAYER_CHARACTER_DATA) - sizeof( NetAddPlayerCharacterInfo ); 
		static Int  const netAddPlayerCharacterInfoSize  = sizeof (NetAddPlayerCharacterInfo);

		static Int  dataSize(PT_REGION_M2C_ADD_PLAYER_CHARACTER_DATA* data)
		{
		   return headSize + netAddPlayerCharacterInfoSize * data->addPlayerNum;
		};
	};
	class PT_REGION_M2C_ADD_PLAYER_CHARACTER_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_REGION_M2C_ADD_PLAYER_CHARACTER_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_REGION;
			mType                               =   PT_REGION_M2C_ADD_PLAYER_CHARACTER;
			//mBaseDataSize                       =   PT_PLAYER_M2C_TIRO_LIST_INFO::dataSize ;

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
			if ( dataLen != PT_REGION_M2C_ADD_PLAYER_CHARACTER_INFO::dataSize((PT_REGION_M2C_ADD_PLAYER_CHARACTER_DATA*)data) )
				return false;
			return true;
		}
	};

	//**********************************************************************
	//区域增加一个玩家角色
	//struct NetAddPlayerCharacterInfo
	//{
	//	U64				playerId;
	//	U64				character_id;
	//	U32             characterTemplateID;            //角色模板ID
	//	Char16			name[MAX_CHARACTER_NAME_LEN];
	//	Char16          surNmae[MAX_CHARACTER_NAME_LEN]; 
	//	
	//	//位置
	//	NetVec2Data		pos;
	//	NetVec2Data		moveToPos;
	//	
	//	//朝向
	//	NetVec2Data 	dir;

	//	Int				mp;
	//	Int				hp;
 //       Int             mpmax;
 //       Int             hpmax;
	//	Byte			force;			//势力
	//	Bool			isBattleLeader;
	//	Flt				moveSpeed;
	//};
	//struct PT_REGION_M2C_ADD_PLAYER_CHARACTER_DATA
	//{
	//	Int								addPlayerNum;
	//	NetAddPlayerCharacterInfo		addPlayerInfo[1];
	//};
 //   struct PT_REGION_M2C_ADD_PLAYER_CHARACTER_DATA_INFO
 //   {
	//	static Int  const headSize        = sizeof (PT_REGION_M2C_ADD_PLAYER_CHARACTER_DATA) - sizeof( NetAddPlayerCharacterInfo ); 
	//	static Int  const netAddPlayerCharacterInfoSize  = sizeof (NetAddPlayerCharacterInfo);

 //       static Int  dataSize(PT_REGION_M2C_ADD_PLAYER_CHARACTER_DATA* data)
 //       {
 //           return headSize + netAddPlayerCharacterInfoSize * data->addPlayerNum;
 //       };
 //   };

	/**********************************************************************
	//@名字:        PT_REGION_M2C_REMOVE_PLAYER_CHARACTER
	//@功能:        区域移除一个玩家角色
	//@负责人:      元林虎
	//@协助人:      ???
	//@备注:        ???
	**********************************************************************/
	struct PT_REGION_M2C_REMOVE_PLAYER_CHARACTER_DATA
	{
		U64  character_id;
	};
	struct PT_REGION_M2C_REMOVE_PLAYER_CHARACTER_INFO
	{
		static const Int dataSize = sizeof (PT_REGION_M2C_REMOVE_PLAYER_CHARACTER_DATA);
	};
	class PT_REGION_M2C_REMOVE_PLAYER_CHARACTER_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_REGION_M2C_REMOVE_PLAYER_CHARACTER_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_REGION;
			mType                               =   PT_REGION_M2C_REMOVE_PLAYER_CHARACTER;
			mBaseDataSize                       =   PT_REGION_M2C_REMOVE_PLAYER_CHARACTER_INFO::dataSize ;

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
	/**********************************************************************
	//@名字:        PT_REGION_C2F_ADD_BUILDING_DATA
	//@功能:
	//@负责人:      元林虎
	//@协助人:      ???
	//@备注:        ???
	**********************************************************************/
	struct PT_REGION_C2F_ADD_BUILDING_DATA
	{
		PlayerCharacterIdType	characterId;
		RegionIdType			regionId;
		Byte					regionType;
		Int						addBuildingNum;
		NetAddBuildingInfo		addBuildingInfo[1];
	};
	struct PT_REGION_C2F_ADD_BUILDING_INFO
	{
		static Int  const headSize					= sizeof (PT_REGION_C2F_ADD_BUILDING_DATA) - sizeof(NetAddBuildingInfo); 
		static Int  const netAddBuildingInfoSize	= sizeof (NetAddBuildingInfo);

		static Int  dataSize(PT_REGION_C2F_ADD_BUILDING_DATA* data)
		{ 
			return headSize + netAddBuildingInfoSize * data->addBuildingNum;
		};
	};
	class PT_REGION_C2F_ADD_BUILDING_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_REGION_C2F_ADD_BUILDING_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_REGION;
			mType                               =   PT_REGION_C2F_ADD_BUILDING;
			//mBaseDataSize                       =   PT_REGION_C2F_ADD_BUILDING_INFO::dataSize ;

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
			if ( dataLen != PT_REGION_C2F_ADD_BUILDING_INFO::dataSize((PT_REGION_C2F_ADD_BUILDING_DATA*)data) )
				return false;
			return true;
		}
	};

	/**********************************************************************
	//@名字:        PT_REGION_F2M_ADD_BUILDING
	//@功能:
	//@负责人:      元林虎
	//@协助人:      ???
	//@备注:        ???
	**********************************************************************/
	struct PT_REGION_F2M_ADD_BUILDING_DATA
	{
		PlayerCharacterIdType	characterId;
		RegionIdType			regionId;
		Byte					regionType;
		Int						addBuildingNum;
		NetAddBuildingInfo		addBuildingInfo[1];
	};
	struct PT_REGION_F2M_ADD_BUILDING_INFO
	{
		static Int  const headSize					= sizeof (PT_REGION_F2M_ADD_BUILDING_DATA) - sizeof(NetAddBuildingInfo); 
		static Int  const netAddBuildingInfoSize	= sizeof (NetAddBuildingInfo);

		static Int  dataSize(PT_REGION_F2M_ADD_BUILDING_DATA* data)
		{ 
			return headSize + netAddBuildingInfoSize * data->addBuildingNum;
		};
	};
	class PT_REGION_F2M_ADD_BUILDING_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_REGION_F2M_ADD_BUILDING_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_REGION;
			mType                               =   PT_REGION_F2M_ADD_BUILDING;
			//mBaseDataSize                       =   PT_REGION_C2F_ADD_BUILDING_INFO::dataSize ;

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
			if ( dataLen != PT_REGION_F2M_ADD_BUILDING_INFO::dataSize((PT_REGION_F2M_ADD_BUILDING_DATA*)data) )
				return false;
			return true;
		}
	};
	/**********************************************************************
	//@名字:        PT_REGION_M2C_ADD_BUILDING
	//@功能:
	//@负责人:      元林虎
	//@协助人:      ???
	//@备注:        ???
	**********************************************************************/
	struct PT_REGION_M2C_ADD_BUILDING_DATA
	{
		Int						addBuildingNum;
		NetAddBuildingInfo		addBuildingInfo[1];
	};
	struct PT_REGION_M2C_ADD_BUILDING_INFO
	{
		static Int  const headSize					= sizeof (PT_REGION_M2C_ADD_BUILDING_DATA) - sizeof(NetAddBuildingInfo); 
		static Int  const netAddBuildingInfoSize	= sizeof (NetAddBuildingInfo);

		static Int  dataSize(PT_REGION_M2C_ADD_BUILDING_DATA* data)
		{ 
			return headSize + netAddBuildingInfoSize * data->addBuildingNum;
		};
	};
	class PT_REGION_M2C_ADD_BUILDING_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_REGION_M2C_ADD_BUILDING_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_REGION;
			mType                               =   PT_REGION_M2C_ADD_BUILDING;
			//mBaseDataSize                       =   PT_REGION_C2F_ADD_BUILDING_INFO::dataSize ;

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
			if ( dataLen != PT_REGION_M2C_ADD_BUILDING_INFO::dataSize((PT_REGION_M2C_ADD_BUILDING_DATA*)data) )
				return false;
			return true;
		}
	};

	/**********************************************************************
    //@名字:        PT_REGION_M2C_ADD_MONSTER
    //@功能:
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_REGION_M2C_ADD_MONSTER_DATA
	{
		RegionIdType			regionId;
		Int						addNum;
		NetAddMonsterInfo		addInfo[1];
	};

	struct PT_REGION_M2C_ADD_MONSTER_INFO
	{
		static Int  const headSize        = sizeof (PT_REGION_M2C_ADD_MONSTER_DATA) - sizeof( NetAddMonsterInfo ); 
		static Int  const netAddInfoSize  = sizeof (NetAddMonsterInfo);

		static Int  dataSize(PT_REGION_M2C_ADD_MONSTER_DATA* data)
		{ 
			return headSize + netAddInfoSize * data->addNum;
		};
	};

	class PT_REGION_M2C_ADD_MONSTER_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_REGION_M2C_ADD_MONSTER_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_REGION;
			mType                               =   PT_REGION_M2C_ADD_MONSTER;
			//mBaseDataSize                       =   PT_PLAYER_M2C_TIRO_LIST_INFO::dataSize ;

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
			if ( dataLen != PT_REGION_M2C_ADD_MONSTER_INFO::dataSize((PT_REGION_M2C_ADD_MONSTER_DATA*)data) )
				return false;
			return true;
		}

	};
	//
	////怪物
	//struct NetAddMonsterInfo
	//{
	//	//AccountIdType	controllerAccountId;
	//	U64				monsterId;			//UID
	//	U64				charTemplateId;

	//	NetVec2Data 		pos;
	//	NetVec2Data 		moveToPos;
	//	NetVec2Data 		dir;

	//	Int				maxHp;
	//	Int				maxMp;

	//	Int				hp;
	//	Int				mp;

	//	Flt				moveSpeed;
	//};

	//struct PT_REGION_M2C_ADD_MONSTER_DATA
	//{
	//	RegionIdType			regionId;
	//	Int						addNum;
	//	NetAddMonsterInfo		addInfo[1];
	//};
	//struct PT_REGION_M2C_ADD_MONSTER_DATA_INFO
	//{
	//	static Int  const headSize        = sizeof (PT_REGION_M2C_ADD_MONSTER_DATA) - sizeof( NetAddMonsterInfo ); 
	//	static Int  const netAddInfoSize  = sizeof (NetAddMonsterInfo);

	//	static Int  dataSize(PT_REGION_M2C_ADD_MONSTER_DATA* data)
	//	{ 
	//		return headSize + netAddInfoSize * data->addNum;
	//	};
	//};

	/******************************************************************************/
	/**********************************************************************
    //@名字:        PT_REGION_M2C_MONSTER_ALIVE
    //@功能:
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/

	struct PT_REGION_M2C_MONSTER_ALIVE_DATA
	{
		NetAddMonsterInfo		monsterInfo;
	};

	struct PT_REGION_M2C_MONSTER_ALIVE_INFO
	{
		static const Int dataSize = sizeof (PT_REGION_M2C_MONSTER_ALIVE_DATA);
	};

	class PT_REGION_M2C_MONSTER_ALIVE_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_REGION_M2C_MONSTER_ALIVE_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_PLAYER;
			mType                               =   PT_REGION_M2C_MONSTER_ALIVE;
			mBaseDataSize                       =   PT_REGION_M2C_MONSTER_ALIVE_INFO::dataSize ;

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

	//struct PT_REGION_M2C_MONSTER_ALIVE_DATA
	//{
	//	NetAddMonsterInfo		monsterInfo;
	//};

	//struct PT_REGION_M2C_MONSTER_ALIVE_DATA_INFO
	//{
	//	static const Int dataSize = sizeof (PT_REGION_M2C_MONSTER_ALIVE_DATA);
	//};

	/**********************************************************************
    //@名字:        PT_REGION_M2C_MONSTER_AI_CONTROL
    //@功能:        AI 控制权
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_REGION_M2C_MONSTER_AI_CONTROL_DATA
	{
		AccountIdType			controlerAccountId;			//控制者的 ID
		Int						addMonsterAINum;
		NetMonsterIdInfo		addMonsterAIInfo[1];
	};

	struct PT_REGION_M2C_MONSTER_AI_CONTROL_INFO
	{
		static Int  const headSize        = sizeof (PT_REGION_M2C_MONSTER_AI_CONTROL_DATA) - sizeof( NetMonsterIdInfo ); 
		static Int  const netAddMonsterAIInfoSize  = sizeof (NetMonsterIdInfo);

		static Int  dataSize(PT_REGION_M2C_MONSTER_AI_CONTROL_DATA* data)
		{ 
			return headSize + netAddMonsterAIInfoSize * data->addMonsterAINum;
		};
	};

	class PT_REGION_M2C_MONSTER_AI_CONTROL_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_REGION_M2C_MONSTER_AI_CONTROL_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_REGION;
            mType                               =   PT_REGION_M2C_MONSTER_AI_CONTROL;
            //mBaseDataSize                       =   PT_PLAYER_M2C_TIRO_LIST_INFO::dataSize ;

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
			if ( dataLen != PT_REGION_M2C_MONSTER_AI_CONTROL_INFO::dataSize((PT_REGION_M2C_MONSTER_AI_CONTROL_DATA*)data) )
				return false;
			return true;
		}
    };

	//struct NetMonsterIdInfo
	//{
	//	MonsterIdType	monsterId;
	//};

	//struct PT_REGION_M2C_MONSTER_AI_CONTROL_DATA
	//{
	//	AccountIdType			controlerAccountId;			//控制者的 ID
	//	Int						addMonsterAINum;
	//	NetMonsterIdInfo		addMonsterAIInfo[1];
	//};

	//struct PT_REGION_M2C_MONSTER_AI_CONTROL_DATA_INFO
	//{
	//	static Int  const headSize        = sizeof (PT_REGION_M2C_MONSTER_AI_CONTROL_DATA) - sizeof( NetMonsterIdInfo ); 
	//	static Int  const netAddMonsterAIInfoSize  = sizeof (NetMonsterIdInfo);

	//	static Int  dataSize(PT_REGION_M2C_MONSTER_AI_CONTROL_DATA* data)
	//	{ 
	//		return headSize + netAddMonsterAIInfoSize * data->addMonsterAINum;
	//	};
	//};
	

	/**********************************************************************
    //@名字:        PT_REGION_M2C_CREATE_TROOP
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_REGION_M2C_CREATE_TROOP_DATA
	{
		TroopIdType			troopGroupId;
		Int					troopTemplateId;	//模版ID
		NetVec2Data 		pos;				//中心位置
		NetVec2Data 		dir;
		Int					troopNum;
		Int					soldierNum;			//士兵个数
		CampIdType			campId;				//兵营
		RegionIdType		regionId;
		Int					regionType;
		InstanceUIdType		instanceId;
	};

	struct PT_REGION_M2C_CREATE_TROOP_INFO
	{
		static const Int dataSize = sizeof (PT_REGION_M2C_CREATE_TROOP_DATA);
	};

	class PT_REGION_M2C_CREATE_TROOP_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_REGION_M2C_CREATE_TROOP_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_REGION;
            mType                               =   PT_REGION_M2C_CREATE_TROOP;
            mBaseDataSize                       =   PT_REGION_M2C_CREATE_TROOP_INFO::dataSize ;

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
    //@名字:        PT_REGION_C2F_CREATE_TROOP_RET
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_REGION_C2F_CREATE_TROOP_RET_DATA
	{
		TroopIdType			troopGroupId;
		//NetVec2Data 		pos;			//中心位置
		RegionIdType		regionId;
		Int					regionType;
		InstanceUIdType		instanceId;
		Int					troopNum;		//士兵个数
		NetVec2Data 		troopPos[1];
	};

	struct PT_REGION_C2F_CREATE_TROOP_RET_INFO
	{
		static Int  const headSize        = sizeof (PT_REGION_C2F_CREATE_TROOP_RET_DATA) - sizeof( NetVec2Data); 
		static Int  const netAddTroopRetInfoSize  = sizeof (NetVec2Data);

		static Int  dataSize(PT_REGION_C2F_CREATE_TROOP_RET_DATA* data)
		{ 
			return headSize + netAddTroopRetInfoSize * data->troopNum;
		};
	};
	class PT_REGION_C2F_CREATE_TROOP_RET_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_REGION_C2F_CREATE_TROOP_RET_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_REGION;
            mType                               =   PT_REGION_C2F_CREATE_TROOP_RET;
            //mBaseDataSize                       =   PT_PLAYER_M2C_TIRO_LIST_INFO::dataSize ;

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
			if ( dataLen != PT_REGION_C2F_CREATE_TROOP_RET_INFO::dataSize((PT_REGION_C2F_CREATE_TROOP_RET_DATA*)data) )
				return false;
			return true;
		}
    };


	/**********************************************************************/
	/**********************************************************************
    //@名字:        PT_REGION_F2M_CREATE_TROOP_RET
    //@功能:        返回军队和士兵的位置
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_REGION_F2M_CREATE_TROOP_RET_DATA
	{
		AccountIdType		accountId;
		
		TroopIdType			troopGroupId;
		//NetVec2Data 		pos;			//中心位置
		RegionIdType		regionId;
		Int					regionType;
		InstanceUIdType		instanceUId;
		Int					troopNum;		//
		NetVec2Data 		troopPos[1];
	};

	struct PT_REGION_F2M_CREATE_TROOP_RET_INFO
	{
		static Int  const headSize        = sizeof (PT_REGION_F2M_CREATE_TROOP_RET_DATA) - sizeof( NetVec2Data ); 
		static Int  const netAddTroopRetInfoSize  = sizeof (NetVec2Data);

		static Int  dataSize(PT_REGION_F2M_CREATE_TROOP_RET_DATA* data)
		{ 
			return headSize + netAddTroopRetInfoSize * data->troopNum;
		};
	};

	class PT_REGION_F2M_CREATE_TROOP_RET_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_REGION_F2M_CREATE_TROOP_RET_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_REGION;
            mType                               =   PT_REGION_F2M_CREATE_TROOP_RET;
            //mBaseDataSize                       =   PT_PLAYER_M2C_TIRO_LIST_INFO::dataSize ;

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
			if ( dataLen != PT_REGION_F2M_CREATE_TROOP_RET_INFO::dataSize((PT_REGION_F2M_CREATE_TROOP_RET_DATA*)data) )
				return false;
			return true;
		}
    };

	/**********************************************************************
    //@名字:        PT_REGION_M2C_ADD_TROOP
    //@功能:        返回军队和士兵的位置
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_REGION_M2C_ADD_TROOP_DATA
	{
		Int						addTroopNum;
		NetAddTroopInfo			addTroopInfo[1];
	};

	struct PT_REGION_M2C_ADD_TROOP_INFO
	{
		static Int  const headSize        = sizeof (PT_REGION_M2C_ADD_TROOP_DATA) - sizeof( NetAddTroopInfo ); 
		static Int  const netAddTroopInfoSize  = sizeof (NetAddTroopInfo);

		static Int  dataSize(PT_REGION_M2C_ADD_TROOP_DATA* data)
		{ 
			return headSize + netAddTroopInfoSize * data->addTroopNum;
		};
	};

	class PT_REGION_M2C_ADD_TROOP_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_REGION_M2C_ADD_TROOP_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_REGION;
            mType                               =   PT_REGION_M2C_ADD_TROOP;
            //mBaseDataSize                       =   PT_PLAYER_M2C_TIRO_LIST_INFO::dataSize ;

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
			if ( dataLen != PT_REGION_M2C_ADD_TROOP_INFO::dataSize((PT_REGION_M2C_ADD_TROOP_DATA*)data) )
				return false;
			return true;
		}
    };


		/**********************************************************************
    //@名字:        PT_REGION_M2C_END_LOAD_SCENE
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_REGION_M2C_END_LOAD_SCENE_DATA
	{

	};

	struct PT_REGION_M2C_END_LOAD_SCENE_INFO
	{
		static const Int dataSize = sizeof (PT_REGION_M2C_END_LOAD_SCENE_DATA);
	};

	class PT_REGION_M2C_END_LOAD_SCENE_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_REGION_M2C_END_LOAD_SCENE_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_REGION;
            mType                               =   PT_REGION_M2C_END_LOAD_SCENE;
            mBaseDataSize                       =   PT_REGION_M2C_END_LOAD_SCENE_INFO::dataSize ;

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

	//struct PT_REGION_M2C_END_LOAD_SCENE_DATA
	//{

	//};

	//struct PT_REGION_M2C_END_LOAD_SCENE_DATA_INFO
	//{
	//	static const Int dataSize = sizeof (PT_REGION_M2C_END_LOAD_SCENE_DATA);
	//};
	

	////区域移除一个玩家角色
	//struct PT_REGION_M2C_REMOVE_PLAYER_CHARACTER_DATA
	//{
	//	U64  character_id;
	//};
 //   struct PT_REGION_M2C_REMOVE_PLAYER_CHARACTER_DATA_INFO
 //   {
 //       static const Int dataSize = sizeof (PT_REGION_M2C_REMOVE_PLAYER_CHARACTER_DATA);
 //   };

	//**********************************************************************
	/**********************************************************************
    //@名字:        PT_REGION_C2F_PLAYER_CHARACTER_ALIVE
    //@功能:        区域移除一个玩家角色
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_REGION_C2F_PLAYER_CHARACTER_ALIVE_DATA
	{
		AccountIdType				accountId;
		PlayerCharacterIdType		playerCharacterId;
		Byte						aliveType;
	};

	struct PT_REGION_C2F_PLAYER_CHARACTER_ALIVE_INFO
	{
		static const Int dataSize = sizeof (PT_REGION_C2F_PLAYER_CHARACTER_ALIVE_DATA);
	};

	class PT_REGION_C2F_PLAYER_CHARACTER_ALIVE_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_REGION_C2F_PLAYER_CHARACTER_ALIVE_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_REGION;
            mType                               =   PT_REGION_C2F_PLAYER_CHARACTER_ALIVE;
            mBaseDataSize                       =   PT_REGION_C2F_PLAYER_CHARACTER_ALIVE_INFO::dataSize ;

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

	//struct PT_REGION_C2F_PLAYER_CHARACTER_ALIVE_DATA
	//{
	//	AccountIdType				accountId;
	//	PlayerCharacterIdType		playerCharacterId;
	//	Byte						aliveType;
	//};

	//struct PT_REGION_C2F_PLAYER_CHARACTER_ALIVE_DATA_INFO
	//{
	//	static const Int dataSize = sizeof (PT_REGION_C2F_PLAYER_CHARACTER_ALIVE_DATA);
	//};
	//**********************************************************************
	
	/**********************************************************************
    //@名字:        PT_REGION_F2M_PLAYER_CHARACTER_ALIVE
    //@功能:       
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_REGION_F2M_PLAYER_CHARACTER_ALIVE_DATA
	{
		AccountIdType				accountId;
		PlayerCharacterIdType		playerCharacterId;
		Byte						aliveType;
	};

	struct PT_REGION_F2M_PLAYER_CHARACTER_ALIVE_INFO
	{
		static const Int dataSize = sizeof (PT_REGION_F2M_PLAYER_CHARACTER_ALIVE_DATA);
	};

	class PT_REGION_F2M_PLAYER_CHARACTER_ALIVE_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_REGION_F2M_PLAYER_CHARACTER_ALIVE_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_REGION;
            mType                               =   PT_REGION_F2M_PLAYER_CHARACTER_ALIVE;
            mBaseDataSize                       =   PT_REGION_F2M_PLAYER_CHARACTER_ALIVE_INFO::dataSize ;

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

	//struct PT_REGION_F2M_PLAYER_CHARACTER_ALIVE_DATA
	//{
	//	AccountIdType				accountId;
	//	PlayerCharacterIdType		playerCharacterId;
	//	Byte						aliveType;
	//};

	//struct PT_REGION_F2M_PLAYER_CHARACTER_ALIVE_DATA_INFO
	//{
	//	static const Int dataSize = sizeof (PT_REGION_F2M_PLAYER_CHARACTER_ALIVE_DATA);
	//};
	//**********************************************************************
	/**********************************************************************
    //@名字:        PT_REGION_M2F_PLAYER_CHARACTER_ALIVE
    //@功能:        
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_REGION_M2F_PLAYER_CHARACTER_ALIVE_DATA
	{
		AccountIdType				accountId;
		PlayerCharacterIdType		playerCharacterId;
	};
	struct PT_REGION_M2F_PLAYER_CHARACTER_ALIVE_INFO
	{
		static const Int dataSize = sizeof (PT_REGION_M2F_PLAYER_CHARACTER_ALIVE_DATA);
	};

	class PT_REGION_M2F_PLAYER_CHARACTER_ALIVE_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_REGION_M2F_PLAYER_CHARACTER_ALIVE_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_REGION;
            mType                               =   PT_REGION_M2F_PLAYER_CHARACTER_ALIVE;
            mBaseDataSize                       =   PT_REGION_M2F_PLAYER_CHARACTER_ALIVE_INFO::dataSize ;

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

	//struct PT_REGION_M2F_PLAYER_CHARACTER_ALIVE_DATA
	//{
	//	AccountIdType				accountId;
	//	PlayerCharacterIdType		playerCharacterId;
	//};
 //   struct PT_REGION_M2F_PLAYER_CHARACTER_ALIVE_DATA_INFO
 //   {
 //       static const Int dataSize = sizeof (PT_REGION_M2F_PLAYER_CHARACTER_ALIVE_DATA);
 //   };

	//**********************************************************************
	/**********************************************************************
    //@名字:        PT_REGION_F2C_PLAYER_CHARACTER_ALIVE
    //@功能:        
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_REGION_F2C_PLAYER_CHARACTER_ALIVE_DATA
	{
		PlayerCharacterIdType playerCharacterId;
	};
	struct PT_REGION_F2C_PLAYER_CHARACTER_ALIVE_INFO
	{
		static const Int dataSize = sizeof (PT_REGION_F2C_PLAYER_CHARACTER_ALIVE_DATA);
	};


	class PT_REGION_F2C_PLAYER_CHARACTER_ALIVE_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_REGION_F2C_PLAYER_CHARACTER_ALIVE_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_REGION;
            mType                               =   PT_REGION_F2C_PLAYER_CHARACTER_ALIVE;
            mBaseDataSize                       =   PT_REGION_F2C_PLAYER_CHARACTER_ALIVE_INFO::dataSize ;

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

	//struct PT_REGION_F2C_PLAYER_CHARACTER_ALIVE_DATA
	//{
	//	PlayerCharacterIdType playerCharacterId;
	//};
	//struct PT_REGION_F2C_PLAYER_CHARACTER_ALIVE_DATA_INFO
	//{
	//	static const Int dataSize = sizeof (PT_REGION_F2C_PLAYER_CHARACTER_ALIVE_DATA);
	//};
	//
	//**********************************************************************
	/**********************************************************************
    //@名字:        PT_REGION_M2C_PLAYER_CHARACTER_ALIVE
    //@功能:        
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
	struct PT_REGION_M2C_PLAYER_CHARACTER_ALIVE_DATA
	{
		NetAddPlayerCharacterInfo		playerInfo;
	};

	struct PT_REGION_M2C_PLAYER_CHARACTER_ALIVE_INFO
	{
		static const Int dataSize = sizeof (PT_REGION_M2C_PLAYER_CHARACTER_ALIVE_DATA);
	};

	class PT_REGION_M2C_PLAYER_CHARACTER_ALIVE_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_REGION_M2C_PLAYER_CHARACTER_ALIVE_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_REGION;
            mType                               =   PT_REGION_M2C_PLAYER_CHARACTER_ALIVE;
            mBaseDataSize                       =   PT_REGION_M2C_PLAYER_CHARACTER_ALIVE_INFO::dataSize ;

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
	//@名字:        PT_REGION_C2M_TEST
	//@功能:        ???
	//@负责人:      元林虎
	//@协助人:      ???
	//@备注:        ???
	**********************************************************************/
	struct PT_REGION_C2M_TEST_DATA
	{
		AccountIdType accountId;
	};

	struct PT_REGION_C2M_TEST_INFO
	{
		static const Int dataSize = sizeof (PT_REGION_C2M_TEST_DATA);
	};

	class PT_REGION_C2M_TEST_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_REGION_C2M_TEST_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_REGION;
			mType                               =   PT_REGION_C2M_TEST;
			mBaseDataSize                       =   PT_REGION_C2M_TEST_INFO::dataSize ;

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
	/**********************************************************************
	//@名字:        PT_REGION_C2M_ADD_TROOP_TEST
	//@功能:        ???
	//@负责人:      元林虎
	//@协助人:      ???
	//@备注:        ???
	**********************************************************************/
	struct PT_REGION_C2M_ADD_TROOP_TEST_DATA
	{
		AccountIdType accountId;
	};

	struct PT_REGION_C2M_ADD_TROOP_TEST_INFO
	{
		static const Int dataSize = sizeof (PT_REGION_C2M_ADD_TROOP_TEST_DATA);
	};

	class PT_REGION_C2M_ADD_TROOP_TEST_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_REGION_C2M_ADD_TROOP_TEST_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_REGION;
			mType                               =   PT_REGION_C2M_ADD_TROOP_TEST;
			mBaseDataSize                       =   PT_REGION_C2M_ADD_TROOP_TEST_INFO::dataSize ;

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
	struct PT_REGION_M2C_CREATE_APPEAR_PLAYER_CHARACTER_DATA
	{
		Int								addPlayerNum;
		NetAddPlayerCharacterInfo		addPlayerInfo[1];
	};

	struct PT_REGION_M2C_CREATE_APPEAR_PLAYER_CHARACTER_DATA_INFO
	{
		static Int  const headSize        = sizeof (PT_REGION_M2C_CREATE_APPEAR_PLAYER_CHARACTER_DATA) - sizeof( NetAddPlayerCharacterInfo ); 
		static Int  const netAddPlayerCharacterInfoSize  = sizeof (NetAddPlayerCharacterInfo);

		static Int  dataSize(PT_REGION_M2C_CREATE_APPEAR_PLAYER_CHARACTER_DATA* data)
		{
			return headSize + netAddPlayerCharacterInfoSize * data->addPlayerNum;
		};
	};


	//struct PT_REGION_M2C_PLAYER_CHARACTER_ALIVE_DATA
	//{
	//	NetAddPlayerCharacterInfo		playerInfo;
	//};

 //   struct PT_REGION_M2C_PLAYER_CHARACTER_ALIVE_DATA_INFO
 //   {
 //       static const Int dataSize = sizeof (PT_REGION_M2C_PLAYER_CHARACTER_ALIVE_DATA);
 //   };

	//*******************************************************************
	struct PT_REGION_M2C_DESTROY_DISAPPEAR_PLAYER_CHARACTER_DATA
	{
		GameObjectIndexIdInSceneType  characterIndex;
	};

	struct PT_REGION_M2C_DESTROY_DISAPPEAR_PLAYER_CHARACTER_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_REGION_M2C_DESTROY_DISAPPEAR_PLAYER_CHARACTER_DATA);
	};


	//*******************************************************************
	struct NetAppearPlayerCharacterInfo
	{
		U64				playerId;
		GameObjectIndexIdInSceneType				characterIndex;
		U32             characterTemplateID;            //角色模板ID
		Char16			name[MAX_CHARACTER_NAME_LEN];

		//位置
		NetVec2Data pos;

		//朝向
		NetVec2Data	dir;

		Int				mp;
		Int				hp;
		Int             mpmax;
		Int             hpmax;
		Byte			force;			//势力
		Bool			isBattleLeader;
		Flt				moveSpeed;
	};

	//*******************************************************************

	struct PT_REGION_M2C_APPEAR_PLAYER_CHARACTER_DATA
	{
		Int								appearPlayerNum;
		NetAppearPlayerCharacterInfo	appearPlayerInfo[1];
	};

	struct PT_REGION_M2C_APPEAR_PLAYER_CHARACTER_DATA_INFO
	{
		static Int  const headSize        = sizeof (PT_REGION_M2C_APPEAR_PLAYER_CHARACTER_DATA) - sizeof( NetAddPlayerCharacterInfo ); 
		static Int  const netAppearPlayerCharacterInfoSize  = sizeof (NetAddPlayerCharacterInfo);

		static Int  dataSize(PT_REGION_M2C_APPEAR_PLAYER_CHARACTER_DATA* data)
		{
			return headSize + netAppearPlayerCharacterInfoSize * data->appearPlayerNum;
		};
	};

	//*******************************************************************
	struct PT_REGION_M2C_DISAPPEAR_PLAYER_CHARACTER_DATA
	{
		GameObjectIndexIdInSceneType  characterIndex;
	};

	struct PT_REGION_M2C_DISAPPEAR_PLAYER_CHARACTER_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_REGION_M2C_DISAPPEAR_PLAYER_CHARACTER_DATA);
	};



	
	

	////区域增加建筑物
	//struct NetAddBuildingInfoFront
	//{
	//	U64					templateId;
	//	NetVec2Data 	pos;										//位置

	//};


	
	//struct PT_REGION_C2F_ADD_BUILDING_DATA
	//{
	//	U64						characterId;
	//	U64						regionId;
	//	Byte					regionType;
	//	Int						addBuildingNum;
	//	NetAddBuildingInfo		addBuildingInfo[1];

	//};
 //   struct PT_REGION_C2F_ADD_BUILDING_DATA_INFO
 //   {

 //   };
	//**********************************************************************

	//struct PT_REGION_F2M_ADD_BUILDING_DATA
	//{
	//	U64						accountId;
	//	U64						characterId;
	//	U64						regionId;
	//	Byte					regionType;
	//	Int						addBuildingNum;
	//	NetAddBuildingInfo		addBuildingInfo[1];
	//};
 //   struct PT_REGION_F2M_ADD_BUILDING_DATA_INFO
 //   {
 //       //static const Int dataSize = sizeof (PT_REGION_F2M_ADD_BUILDING_DATA);
 //   };


	//**********************************************************************

	//struct PT_REGION_M2C_ADD_BUILDING_DATA
	//{
	//	Int					addBuildingNum;
	//	NetAddBuildingInfo	addBuildingInfo[1];
	//};
 //   struct PT_REGION_M2C_ADD_BUILDING_DATA_INFO
	//{            
	//	static Int  const headSize        = sizeof (PT_REGION_M2C_ADD_BUILDING_DATA) - sizeof( NetAddBuildingInfo );
	//	static Int  const netAddBuildingInfoSize    = sizeof (NetAddBuildingInfo);
 //       static Int  dataSize(PT_REGION_M2C_ADD_BUILDING_DATA* data)
 //       { 
 //           return headSize + netAddBuildingInfoSize * data->addBuildingNum;
 //       };
 //   };

	//**********************************************************************

	struct PT_REGION_M2C_CREATE_APPEAR_BUILDING_DATA
	{
		Int					addBuildingNum;
		NetAddBuildingInfo	addBuildingInfo[1];
	};

	
	struct PT_REGION_M2C_CREATE_APPEAR_BUILDING_DATA_INFO
	{
		static Int  const headSize        = sizeof (PT_REGION_M2C_CREATE_APPEAR_BUILDING_DATA) - sizeof( NetAddBuildingInfo );
		static Int  const netAddBuildingInfoSize    = sizeof (NetAddBuildingInfo);
		static Int  dataSize(PT_REGION_M2C_CREATE_APPEAR_BUILDING_DATA* data)
		{ 
			return headSize + netAddBuildingInfoSize * data->addBuildingNum;
		};
	};

	//**********************************************************************
	struct PT_REGION_C2F_REMOVE_BUILDING_DATA
	{
		U64  buildingId;
	};
    struct PT_REGION_C2F_REMOVE_BUILDING_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_REGION_C2F_REMOVE_BUILDING_DATA);
    };
	//**********************************************************************
	struct PT_REGION_F2M_REMOVE_BUILDING_DATA
	{
		U64	 accountId;
		U64  buildingId;
	};
    struct PT_REGION_F2M_REMOVE_BUILDING_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_REGION_F2M_REMOVE_BUILDING_DATA);
    };
	//**********************************************************************
	struct PT_REGION_M2C_REMOVE_BUILDING_DATA
	{
		U64  buildingId;
	};
    struct PT_REGION_M2C_REMOVE_BUILDING_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_REGION_M2C_REMOVE_BUILDING_DATA);
    };

	//*******************************************************************
	struct PT_REGION_M2C_DESTROY_DISAPPEAR_BUILDING_DATA
	{
		GameObjectIndexIdInSceneType  buildingIndex;
	};

	struct PT_REGION_M2C_DESTROY_DISAPPEAR_BUILDING_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_REGION_M2C_DESTROY_DISAPPEAR_BUILDING_DATA);
	};

	//*******************************************************************
	struct NetAppearBuildingInfo
	{
		GameObjectIndexIdInSceneType				index;										//唯一的标示符 由Mapserver生成，并广播给客户端
		U64				belongAccountId;							//所属者ID
		U64				buildingTemplateId;							//模板Id
		Byte			buildingType;
		U64	    		regionId;

		Byte			force;									//势力

		NetVec2Data		pos;									//位置
		NetVec2Data		dir;									//方向
		Int				hp;
	};

	//*******************************************************************

	struct PT_REGION_M2C_APPEAR_BUILDING_DATA
	{
		Int					appearBuildingNum;
		NetAddBuildingInfo	appearBuildingInfo[1];
	};

	struct PT_REGION_M2C_APPEAR_BUILDING_DATA_INFO
	{
		static Int  const headSize        = sizeof (PT_REGION_M2C_APPEAR_BUILDING_DATA) - sizeof( NetAppearBuildingInfo );
		static Int  const netAppearBuildingInfoSize    = sizeof (NetAppearBuildingInfo);
		static Int  dataSize(PT_REGION_M2C_APPEAR_BUILDING_DATA* data)
		{ 
			return headSize + netAppearBuildingInfoSize * data->appearBuildingNum;
		};
	};

	//*******************************************************************
	struct PT_REGION_M2C_DISAPPEAR_BUILDING_DATA
	{
		GameObjectIndexIdInSceneType  buildingIndex;
	};

	struct PT_REGION_M2C_DISAPPEAR_BUILDING_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_REGION_M2C_DISAPPEAR_BUILDING_DATA);
	};


	//**********************************************************************

	////第三方角色
	//struct NetAddThirthPartInfo
	//{
	//	U64				charTemplateId;

	//	NetVec2Data pos;
	//	Vec3			dir;
	//};

	//struct PT_REGION_M2C_ADD_TRITH_PART_CHARACTER_DATA
	//{
	//	U64						regionId;
	//	Byte					regionType;
	//	Int						addNum;
	//	NetAddThirthPartInfo	addInfo[1];
	//};
	//struct PT_REGION_M2C_ADD_TRITH_PART_CHARACTER_DATA_INFO
	//{
	//	static Int  const headSize        = sizeof (PT_REGION_M2C_ADD_TRITH_PART_CHARACTER_DATA) - sizeof( NetAddThirthPartInfo ); 
	//	static Int  const netAddInfoSize  = sizeof (NetAddThirthPartInfo);

	//	static Int  dataSize(PT_REGION_M2C_ADD_TRITH_PART_CHARACTER_DATA* data)
	//	{ 
	//		return headSize + netAddInfoSize * data->addNum;
	//	};
	//};

	/******************************************************************************/
	



	/******************************************************************************/
	struct PT_REGION_M2C_CREATE_APPEAR_MONSTER_DATA
	{
		RegionIdType			regionId;
		Int						addNum;
		NetAddMonsterInfo		addInfo[1];
	};


	struct PT_REGION_M2C_CREATE_APPEAR_MONSTER_DATA_INFO
	{
		static Int  const headSize        = sizeof (PT_REGION_M2C_CREATE_APPEAR_MONSTER_DATA) - sizeof( NetAddMonsterInfo ); 
		static Int  const netAddInfoSize  = sizeof (NetAddMonsterInfo);

		static Int  dataSize(PT_REGION_M2C_CREATE_APPEAR_MONSTER_DATA* data)
		{ 
			return headSize + netAddInfoSize * data->addNum;
		};
	};

	/******************************************************************************/
	struct PT_REGION_M2C_DESTROY_DISAPPEAR_MONSTER_DATA
	{
		RegionIdType			regionId;
		Int						num;
		GameObjectIndexIdInSceneType			monsterIndex[1];
	};


	struct PT_REGION_M2C_DESTROY_DISAPPEAR_MONSTER_DATA_INFO
	{
		static Int  const headSize        = sizeof (PT_REGION_M2C_DESTROY_DISAPPEAR_MONSTER_DATA) - sizeof( MonsterIdType ); 
		static Int  const netAddInfoSize  = sizeof (MonsterIdType);

		static Int  dataSize(PT_REGION_M2C_DESTROY_DISAPPEAR_MONSTER_DATA* data)
		{ 
			return headSize + netAddInfoSize * data->num;
		};
	};




	//*******************************************************************

	struct NetAppearMonsterInfo
	{
		U64				monsterId;			//UID
		U64				charTemplateId;

		NetVec2Data pos;
		Vec3			dir;

		Int				maxHp;
		Int				maxMp;

		Int				hp;
		Int				mp;

		Flt				moveSpeed;
	};

	struct PT_REGION_M2C_APPEAR_MONSTER_DATA
	{
		Int						appearMonsterNum;
		NetAppearMonsterInfo	appearMonsterInfo[1];
	};

	struct PT_REGION_M2C_APPEAR_MONSTER_DATA_INFO
	{
		static Int  const headSize        = sizeof (PT_REGION_M2C_APPEAR_MONSTER_DATA) - sizeof( NetAppearMonsterInfo );
		static Int  const netAppearBuildingInfoSize    = sizeof (NetAppearMonsterInfo);
		static Int  dataSize(PT_REGION_M2C_APPEAR_MONSTER_DATA* data)
		{ 
			return headSize + netAppearBuildingInfoSize * data->appearMonsterNum;
		};
	};

	//*******************************************************************
	struct PT_REGION_M2C_DISAPPEAR_MONSTER_DATA
	{
		GameObjectIndexIdInSceneType  monsterIndex;
	};

	struct PT_REGION_M2C_DISAPPEAR_MONSTER_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_REGION_M2C_DISAPPEAR_MONSTER_DATA);
	};


	////怪物
	//struct NetAddMonsterInfoFront
	//{
	//	U64				monsterId;			//UID
	//	U64				monsterTemplateId;

	//	RegionIdType			regionId;
	//	Int						regionType;
	//	InstanceUIdType			instanceUId;
	//};

	/******************************************************************************/
	//struct PT_REGION_M2F_ADD_MONSTER_DATA
	//{
	//	U64							regionId;
	//	Byte						regionType;
	//	Int							addNum;
	//	NetAddMonsterInfoFront		addInfo[1];
	//};
	//struct PT_REGION_M2F_ADD_MONSTER_DATA_INFO
	//{
	//	static Int  const headSize        = sizeof (PT_REGION_M2F_ADD_MONSTER_DATA) - sizeof( NetAddMonsterInfo ); 
	//	static Int  const netAddInfoSize  = sizeof (NetAddThirthPartInfo);

	//	static Int  dataSize(PT_REGION_M2F_ADD_MONSTER_DATA* data)
	//	{ 
	//		return headSize + netAddInfoSize * data->addNum;
	//	};
	//};
	/******************************************************************************/
	//军营
	//struct NetAddCampInfo
	//{
	//	CampIdType			campId;
	//	AccountIdType		belongAccountId;		//控制者ID
	//	U64					campTemplateId;
	//	Byte				force;
	//	NetVec2Data 	pos;
	//	Int					armyNum;			//有几个军队
	//	Int					troopNum;			//每个军队 有几个部队
	//	Int					hp;
	//	Int					mp;
	//	Int					hpMax;
	//	Int					mpMax;

	//};

	//struct PT_REGION_M2C_ADD_CAMP_DATA
	//{
	//	Int						addCampNum;
	//	NetAddCampInfo			addCampInfo[1];
	//};

	//struct PT_REGION_M2C_ADD_CAMP_DATA_INFO
	//{
	//	static Int  const headSize        = sizeof (PT_REGION_M2C_ADD_CAMP_DATA) - sizeof( NetAddCampInfo ); 
	//	static Int  const netAddCampInfoSize  = sizeof (NetAddCampInfo);

	//	static Int  dataSize(PT_REGION_M2C_ADD_CAMP_DATA* data)
	//	{ 
	//		return headSize + netAddCampInfoSize * data->addCampNum;
	//	};
	//};
	
	//需要由客户端来计算军队和士兵的位子
	//struct PT_REGION_M2C_CREATE_TROOP_DATA
	//{
	//	TroopIdType			troopGroupId;
	//	Int					troopTemplateId;	//模版ID
	//	NetVec2Data 		pos;				//中心位置
	//	NetVec2Data 		dir;
	//	Int					troopNum;
	//	Int					soldierNum;			//士兵个数
	//	CampIdType			campId;				//兵营
	//	RegionIdType		regionId;
	//	Int					regionType;
	//	InstanceUIdType		instanceId;
	//};

	//struct PT_REGION_M2C_CREATE_TROOP_DATA_INFO
	//{
	//	static const Int dataSize = sizeof (PT_REGION_M2C_CREATE_TROOP_DATA);
	//};

	//返回军队和士兵的位置
	//struct PT_REGION_C2F_CREATE_TROOP_RET_DATA
	//{
	//	TroopIdType			troopGroupId;
	//	//NetVec2Data 		pos;			//中心位置
	//	RegionIdType		regionId;
	//	Int					regionType;
	//	InstanceUIdType		instanceId;
	//	Int					troopNum;		//士兵个数
	//	NetVec2Data 		troopPos[1];
	//};

	//struct PT_REGION_C2F_CREATE_TROOP_RET_DATA_INFO
	//{
	//	static Int  const headSize        = sizeof (PT_REGION_C2F_CREATE_TROOP_RET_DATA) - sizeof( NetVec2Data); 
	//	static Int  const netAddTroopRetInfoSize  = sizeof (NetVec2Data);

	//	static Int  dataSize(PT_REGION_C2F_CREATE_TROOP_RET_DATA* data)
	//	{ 
	//		return headSize + netAddTroopRetInfoSize * data->troopNum;
	//	};
	//};
	

	//返回军队和士兵的位置
	//struct PT_REGION_F2M_CREATE_TROOP_RET_DATA
	//{
	//	AccountIdType		accountId;
	//	
	//	TroopIdType			troopGroupId;
	//	//NetVec2Data 		pos;			//中心位置
	//	RegionIdType		regionId;
	//	Int					regionType;
	//	InstanceUIdType		instanceUId;
	//	Int					troopNum;		//
	//	NetVec2Data 		troopPos[1];
	//};

	//struct PT_REGION_F2M_CREATE_TROOP_RET_DATA_INFO
	//{
	//	//static const Int dataSize = sizeof (PT_REGION_F2M_CREATE_TROOP_RET_DATA);

	//	static Int  const headSize        = sizeof (PT_REGION_F2M_CREATE_TROOP_RET_DATA) - sizeof( NetVec2Data ); 
	//	static Int  const netAddTroopRetInfoSize  = sizeof (NetVec2Data);

	//	static Int  dataSize(PT_REGION_F2M_CREATE_TROOP_RET_DATA* data)
	//	{ 
	//		return headSize + netAddTroopRetInfoSize * data->troopNum;
	//	};
	//};
	
	
	/******************************************************************************/

	////军队
	//struct NetAddTroopInfo
	//{
	//	Byte				force;
	//	U64					playerId;
	//	U64					troopId;
	//	U64					troopTemplateId;
	//	NetVec2Data 		pos;
	//	NetVec2Data 		dir;	
	//	Int					hp;
	//	Int					mp;
	//	Int					maxHp;
	//	Int					maxMp;
	//	Flt					moveSpeed;

	//	Int					soldierNum;			//有几个军队
	//	//NetVec2Data 		soldierPos[50];		//暂时用于测试
	//};

	//struct PT_REGION_M2C_ADD_TROOP_DATA
	//{
	//	Int						addTroopNum;
	//	NetAddTroopInfo			addTroopInfo[1];
	//};

	//struct PT_REGION_M2C_ADD_TROOP_DATA_INFO
	//{
	//	static Int  const headSize        = sizeof (PT_REGION_M2C_ADD_TROOP_DATA) - sizeof( NetAddTroopInfo ); 
	//	static Int  const netAddTroopInfoSize  = sizeof (NetAddTroopInfo);

	//	static Int  dataSize(PT_REGION_M2C_ADD_TROOP_DATA* data)
	//	{ 
	//		return headSize + netAddTroopInfoSize * data->addTroopNum;
	//	};
	//};

	//**********************************************************************
	struct PT_REGION_M2C_CREATE_APPEAR_TROOP_DATA
	{
		Int						addTroopNum;
		NetAddTroopInfo			addTroopInfo[1];
	};


	struct PT_REGION_M2C_CREATE_APPEAR_TROOP_DATA_INFO
	{
		static Int  const headSize        = sizeof (PT_REGION_M2C_CREATE_APPEAR_TROOP_DATA) - sizeof( NetAddTroopInfo ); 
		static Int  const netAddTroopInfoSize  = sizeof (NetAddTroopInfo);

		static Int  dataSize(PT_REGION_M2C_CREATE_APPEAR_TROOP_DATA* data)
		{ 
			return headSize + netAddTroopInfoSize * data->addTroopNum;
		};
	};

	//**********************************************************************

	

	//**********************************************************************

	//struct NetAddTroopInfoFront 
	//{
	//	NetAddTroopInfo			troopInfo;
	//	RegionIdType			regionId;
	//	Int						regionType;
	//	InstanceUIdType			instanceUId;
	//};

	//struct PT_REGION_M2F_ADD_TROOP_DATA
	//{
	//	Int						addTroopNum;
	//	NetAddTroopInfoFront	addTroopInfo[1];
	//};

	//struct PT_REGION_M2F_ADD_TROOP_DATA_INFO
	//{
	//	static Int  const headSize        = sizeof (PT_REGION_M2F_ADD_TROOP_DATA) - sizeof( NetAddTroopInfoFront ); 
	//	static Int  const netAddTroopInfoSize  = sizeof (NetAddTroopInfoFront);

	//	static Int  dataSize(PT_REGION_M2F_ADD_TROOP_DATA* data)
	//	{
	//		return headSize + netAddTroopInfoSize * data->addTroopNum;
	//	};
	//};

	//**********************************************************************


	//**********************************************************************
}

/******************************************************************************/
#pragma pack (pop)
#endif