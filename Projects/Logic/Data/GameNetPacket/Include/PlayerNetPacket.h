/******************************************************************************/
#ifndef _PLAYERNETPACKET_H_
#define _PLAYERNETPACKET_H_
/******************************************************************************/
#include "CommonGameDefine.h"
#include "NetDefine.h"
#include "GameNetPacket.h"
#include "NetVec2.h"
#include "PlayerItem.h"
/******************************************************************************/


namespace MG
{
    /******************************************************************************/
    //玩家包类型
    /******************************************************************************/
    enum PlayerNetPacketType
    {
		PT_PLAYER_UNKNOWN = 0,

		/*元林虎*/PT_PLAYER_C2F_PRINT_TEST,						//打印FrontServer内存信息
		/*元林虎*/PT_PLAYER_F2M_PRINT_TEST,						//打印MapServer内存信息

		/*元林虎*/PT_PLAYER_C2F_TIRO_LIST,						//新手副本的列表
		/*元林虎*/PT_PLAYER_F2M_TIRO_LIST,
		/*元林虎*/PT_PLAYER_M2C_TIRO_LIST_BEGIN,
		/*元林虎*/PT_PLAYER_M2C_TIRO_LIST,
		/*元林虎*/PT_PLAYER_M2C_TIRO_LIST_END,
		
		/*元林虎*/PT_PLAYER_S2S_SYNC_ALL_LIST_END,				//重启MapServer后同步【Player】，【PlayerCharacter】，【TroopGroup】列表

		/*元林虎*/PT_PLAYER_M2C_REMAIN_PLAYERCHARACTER_LIST,	// 发送【Remain角色】信息给客户端	ok

		/*元林虎*/PT_PLAYER_C2F_JUMP_REGION = 100,				// 客户端请求跳转区域
		/*元林虎*/PT_PLAYER_F2M_JUMP_REGION,					// 请求跳转区域			ok
		/*元林虎*/PT_PLAYER_M2F_JUMP_REGION,
		/*元林虎*/PT_PLAYER_F2C_JUMP_REGION,					// 服务器告知客户端进入地图。

		/*元林虎*/PT_PLAYER_C2F_JUMP_REGION_BY_CHAR_ID,			// 客户端请求跳转区域
		/*元林虎*/PT_PLAYER_F2M_JUMP_REGION_BY_CHAR_ID,			// 请求跳转区域			ok


		/*王育安*/PT_PLAYER_F2M_LOGIN,							// 通知玩家登入	ok
		/*王育安*/PT_PLAYER_F2M_LOGOUT,		                    // 通知玩家登出	ok

		/*王育安*/PT_PLAYER_F2M_PLAYERCHARACTER_INFO_LIST,        // 发送角色信息给MapServer	ok
		/*王育安*/PT_PLAYER_F2M_PLAYERCHARACTER_EQUIP_INFO_LIST,  // 发送角色装备信息给MapServer
		
		/*王育安*/PT_PLAYER_F2M_TROOP_INFO_LIST,					// 发送军队信息给MapServer
		/*王育安*/PT_PLAYER_F2M_BATTLE_INFO_LIST,					// 发送战场建筑物信息给MapServer

		/*王育安*/PT_PLAYER_F2C_PLAYERCHARACTER_INFO_LIST,		// 发送角色信息给客户端
		/*王育安*/PT_PLAYER_F2C_TROOP_INFO_LIST,                  //发送军队信息给Client	
		/*邓黄超*/PT_PLAYER_F2C_MAIN_PLAYERCHARACTER_INFO        //发送主武将信息
    };

	/******************************************************************************/


#pragma pack (push)
#pragma pack (1)

	//数据包声明
	//**********************************************************************
	enum PlayerJumpResult
	{
		PlayerJump_Success,					//跳转成功
		PlayerJump_Failed,
		PlayerJump_ServerCrash,				//服务器当机， 无法跳转
	};

	//////////////////////////////////////////////////////////////////////////////

	struct NetPlayerCharacterInfo
	{
		Char16	name[MAX_CHARACTER_NAME_LEN];
		Char16  surName[MAX_CHARACTER_NAME_LEN];

		IdType	Id;
		IdType  charClanId;                     //角色所属氏族ID
		IdType  accountId;              
		U32     characterTemplateID;
		U32     charCurAge;
		U32     charLifeSpan;
		U32     charLvl;        
		U32     charExp1;       
		U32     charExp2;       
		U32     charExp3;       
		U32     charHP;         
		U32     charMP;         
		U32     charLineageNum; 
		U32		charArtMashID1; 
		U32		charArtMashID2; 
		U32     charArtIcon;     
		U32     charOfficialPos;
		U32     charInfluenceID;
		U32     charSkillPointAll;     
		U32     charNoAssignSkillPoint;
		U32     charState;             
		U32     charLifeState;  
		U32		charAttrAppendId;
		U32		charAttrAppendLvlAddId;


		NetVec2Data 		genrealPos;
		NetVec2Data 		charDir;
		Byte			regionType;
		U32				regionId;
		U32				maxHp;
		U32				maxMp;
		Flt				attrRand[DB_RECORD_ATTR_NUM];
		Flt				attrRandAdd[DB_RECORD_ATTR_NUM];
	};

	//////////////////////////////////////////////////////////////////////////////

	struct NetTroopInfo
	{
		IdType	Id;
		IdType  charClanId;                     //角色所属氏族ID
		IdType  accountId;
		U32     troopTemplateID;

		NetVec2Data	genrealPos;
		Byte		regionType;		//ROT_BACK_STAGE
		U64			regionId;
		U32			hp;
		U32			mp;
		U32			maxHp;
		U32			maxMp;
		Char16		troopName[MAX_TROOP_NAME_LEN];
	};


	struct NetAddTiroInfo
	{
		InstanceUIdType		instanceUId;		//副本 唯一ID
		Int					curPlayerNum;		//当前人数
		Int					maxPlayerNum;		//最大人数
	};

	/**********************************************************************
    //@名字:        PT_PLAYER_C2F_TIRO_LIST
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
    struct PT_PLAYER_C2F_TIRO_LIST_DATA
    {
		//RegionIdType	regionId;
		//Byte			regionType;
	};

	struct PT_PLAYER_C2F_TIRO_LIST_INFO
	{
		static const Int dataSize = sizeof (PT_PLAYER_C2F_TIRO_LIST_DATA);
	};

	class PT_PLAYER_C2F_TIRO_LIST_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_PLAYER_C2F_TIRO_LIST_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_PLAYER;
            mType                               =   PT_PLAYER_C2F_TIRO_LIST;
            mBaseDataSize                       =   PT_PLAYER_C2F_TIRO_LIST_INFO::dataSize ;

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
	////**********************************************************************
	//struct PT_PLAYER_C2F_TIRO_LIST_DATA
	//{
	//	RegionIdType	regionId;
	//	Byte			regionType;
	//};

	//struct PT_PLAYER_C2F_TIRO_LIST_DATA_INFO
	//{
	//	static const Int dataSize = sizeof (PT_PLAYER_C2F_TIRO_LIST_DATA);
	//};

	//////////////////////////////////////////////////////////////////////////////

	/**********************************************************************
    //@名字:        PT_PLAYER_F2M_TIRO_LIST
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
    struct PT_PLAYER_F2M_TIRO_LIST_DATA
    {
		AccountIdType	accountId;
		NetIdType		mapServerNetId;
	};
	struct PT_PLAYER_F2M_TIRO_LIST_INFO
	{
		static const Int dataSize = sizeof (PT_PLAYER_F2M_TIRO_LIST_DATA);
	};
	class PT_PLAYER_F2M_TIRO_LIST_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_PLAYER_F2M_TIRO_LIST_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_PLAYER;
            mType                               =   PT_PLAYER_F2M_TIRO_LIST;
            mBaseDataSize                       =   PT_PLAYER_F2M_TIRO_LIST_INFO::dataSize ;

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
/*	struct PT_PLAYER_F2M_TIRO_LIST_DATA
	{
		AccountIdType	accountId;
		RegionIdType	regionId;
		Byte			regionType;
	};

	struct PT_PLAYER_F2M_TIRO_LIST_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_PLAYER_F2M_TIRO_LIST_DATA);
	};	
 */   
	//////////////////////////////////////////////////////////////////////////////

	/**********************************************************************
    //@名字:        PT_PLAYER_M2C_TIRO_LIST_BEGIN
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
    struct PT_PLAYER_M2C_TIRO_LIST_BEGIN_DATA
    {
		NetIdType			mapServerNetId;
	};

	struct PT_PLAYER_M2C_TIRO_LIST_BEGIN_INFO
	{
		static const Int dataSize = sizeof (PT_PLAYER_M2C_TIRO_LIST_BEGIN_DATA);
	};

	class PT_PLAYER_M2C_TIRO_LIST_BEGIN_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_PLAYER_M2C_TIRO_LIST_BEGIN_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_PLAYER;
            mType                               =   PT_PLAYER_M2C_TIRO_LIST_BEGIN;
            mBaseDataSize                       =   PT_PLAYER_M2C_TIRO_LIST_BEGIN_INFO::dataSize ;

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
    //@名字:        PT_PLAYER_M2C_TIRO_LIST
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
    struct PT_PLAYER_M2C_TIRO_LIST_DATA
    {
		NetIdType			mapServerNetId;
		RegionIdType		regionId;
		Byte				regionType;
		Int					addTiroNum;
		NetAddTiroInfo		addTiroInfo[1];
	};

	struct PT_PLAYER_M2C_TIRO_LIST_INFO
	{
		static Int  const headSize        = sizeof (PT_PLAYER_M2C_TIRO_LIST_DATA) - sizeof( NetAddTiroInfo ); 
		static Int  const netAddTiroInfoSize  = sizeof (NetAddTiroInfo);

		static Int  dataSize(PT_PLAYER_M2C_TIRO_LIST_DATA* data)
		{ 
			return headSize + netAddTiroInfoSize * data->addTiroNum;
		};
	};

	class PT_PLAYER_M2C_TIRO_LIST_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_PLAYER_M2C_TIRO_LIST_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_PLAYER;
            mType                               =   PT_PLAYER_M2C_TIRO_LIST;
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
			if ( dataLen != PT_PLAYER_M2C_TIRO_LIST_INFO::dataSize((PT_PLAYER_M2C_TIRO_LIST_DATA*)data) )
				return false;
			return true;
		}
    };



	//struct PT_PLAYER_M2C_TIRO_LIST_DATA
	//{
	//	RegionIdType		regionId;
	//	Byte				regionType;
	//	Int					addTiroNum;
	//	NetAddTiroInfo		addTiroInfo[1];
	//};

	//struct PT_PLAYER_M2C_TIRO_LIST_DATA_INFO
	//{
	//	static Int  const headSize        = sizeof (PT_PLAYER_M2C_TIRO_LIST_DATA) - sizeof( NetAddTiroInfo ); 
	//	static Int  const netAddTiroInfoSize  = sizeof (NetAddTiroInfo);

	//	static Int  dataSize(PT_PLAYER_M2C_TIRO_LIST_DATA* data)
	//	{ 
	//		return headSize + netAddTiroInfoSize * data->addTiroNum;
	//	};
	//};
	//**********************************************************************

	/**********************************************************************
    //@名字:        PT_PLAYER_M2C_TIRO_LIST_END
    //@功能:        ???
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
    struct PT_PLAYER_M2C_TIRO_LIST_END_DATA
    {
		NetIdType			mapServerNetId;
	};

	struct PT_PLAYER_M2C_TIRO_LIST_END_INFO
	{
		static const Int dataSize = sizeof (PT_PLAYER_M2C_TIRO_LIST_END_DATA);
	};

	class PT_PLAYER_M2C_TIRO_LIST_END_DESCRIBE : public GameNetPacketDataDescribe
	{
    public:
        PT_PLAYER_M2C_TIRO_LIST_END_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_PLAYER;
            mType                               =   PT_PLAYER_M2C_TIRO_LIST_END;
            mBaseDataSize                       =   PT_PLAYER_M2C_TIRO_LIST_END_INFO::dataSize ;

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



	/////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
	//@名字:        PT_PLAYER_S2S_SYNC_ALL_LIST_END
	//@功能:        ???
	//@负责人:      元林虎
	//@协助人:      ???
	//@备注:        ???
	**********************************************************************/
	struct PT_PLAYER_S2S_SYNC_ALL_LIST_END_DATA
	{
	};
	struct PT_PLAYER_S2S_SYNC_ALL_LIST_END_INFO
	{
		static const Int dataSize = sizeof (PT_PLAYER_S2S_SYNC_ALL_LIST_END_DATA);
	};
	class PT_PLAYER_S2S_SYNC_ALL_LIST_END_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_PLAYER_S2S_SYNC_ALL_LIST_END_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_PLAYER;
			mType                               =   PT_PLAYER_S2S_SYNC_ALL_LIST_END;
			mBaseDataSize                       =   PT_PLAYER_S2S_SYNC_ALL_LIST_END_INFO::dataSize ;

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
	//@名字:        PT_PLAYER_F2M_TIRO_LIST
	//@功能:        ???
	//@负责人:      元林虎
	//@协助人:      ???
	//@备注:        ???
	**********************************************************************/
	struct PT_PLAYER_M2C_REMAIN_PLAYERCHARACTER_LIST_DATA
	{
		Int						remainPlayerCharacterNum;
		NetPlayerCharacterInfo	remainPlayerCharacter[1];
	};

	struct PT_PLAYER_M2C_REMAIN_PLAYERCHARACTER_LIST_INFO
	{
		static Int  const headSize        = sizeof (PT_PLAYER_M2C_REMAIN_PLAYERCHARACTER_LIST_DATA) - sizeof(NetPlayerCharacterInfo); 
		static Int  const netAddPlayerCharacterInfoSize  = sizeof (NetPlayerCharacterInfo);

		static Int  dataSize(PT_PLAYER_M2C_REMAIN_PLAYERCHARACTER_LIST_DATA* data)
		{ 
			return headSize + netAddPlayerCharacterInfoSize * data->remainPlayerCharacterNum;
		};
	};

	class PT_PLAYER_M2C_REMAIN_PLAYERCHARACTER_LIST_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_PLAYER_M2C_REMAIN_PLAYERCHARACTER_LIST_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_PLAYER;
			mType                               =   PT_PLAYER_M2C_REMAIN_PLAYERCHARACTER_LIST;
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
			if ( dataLen != PT_PLAYER_M2C_REMAIN_PLAYERCHARACTER_LIST_INFO::dataSize((PT_PLAYER_M2C_REMAIN_PLAYERCHARACTER_LIST_DATA*)data) )
				return false;
			return true;
		}
	};

	/**********************************************************************
	//@名字:        PT_PLAYER_C2F_JUMP_REGION
	//@功能:        ???
	//@负责人:      元林虎
	//@协助人:      ???
	//@备注:        ???
	**********************************************************************/
	struct PT_PLAYER_C2F_JUMP_REGION_DATA
	{
		RegionIdType	    regionId;
		Byte				regionType;
		InstanceUIdType		instanceUid;
	};

	struct PT_PLAYER_C2F_JUMP_REGION_INFO
	{
		static const Int dataSize = sizeof (PT_PLAYER_C2F_JUMP_REGION_DATA);
	};

	class PT_PLAYER_C2F_JUMP_REGION_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_PLAYER_C2F_JUMP_REGION_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_PLAYER;
			mType                               =   PT_PLAYER_C2F_JUMP_REGION;
			mBaseDataSize                       =   PT_PLAYER_C2F_JUMP_REGION_INFO::dataSize ;

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
	//@名字:        PT_PLAYER_F2M_JUMP_REGION
	//@功能:        ???
	//@负责人:      元林虎
	//@协助人:      ???
	//@备注:        ???
	**********************************************************************/
	struct PT_PLAYER_F2M_JUMP_REGION_DATA
	{
		AccountIdType		accountId;
		Byte				regionType;
		RegionIdType		regionId;
		InstanceUIdType		instanceUid;
	};
	struct PT_PLAYER_F2M_JUMP_REGION_INFO
	{
		static const Int dataSize = sizeof (PT_PLAYER_F2M_JUMP_REGION_DATA);
	};
	class PT_PLAYER_F2M_JUMP_REGION_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_PLAYER_F2M_JUMP_REGION_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_PLAYER;
			mType                               =   PT_PLAYER_F2M_JUMP_REGION;
			mBaseDataSize                       =   PT_PLAYER_F2M_JUMP_REGION_INFO::dataSize ;

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
	//@名字:        PT_PLAYER_M2F_JUMP_REGION
	//@功能:        ???
	//@负责人:      元林虎
	//@协助人:      ???
	//@备注:        ???
	**********************************************************************/
	struct PT_PLAYER_M2F_JUMP_REGION_DATA
	{
		I32					client_net_id;
		Byte				regionType;
		RegionIdType 		regionId;
		InstanceUIdType		instanceUid;
		PlayerJumpResult	jumpResult;
		Byte				force;
		NetVec2Data			pos;
		NetVec2Data			dir;
	};
	struct PT_PLAYER_M2F_JUMP_REGION_INFO
	{
		static const Int dataSize = sizeof (PT_PLAYER_M2F_JUMP_REGION_DATA);
	};
	class PT_PLAYER_M2F_JUMP_REGION_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_PLAYER_M2F_JUMP_REGION_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_PLAYER;
			mType                               =   PT_PLAYER_M2F_JUMP_REGION;
			mBaseDataSize                       =   PT_PLAYER_M2F_JUMP_REGION_INFO::dataSize ;

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
	//@名字:        PT_PLAYER_F2C_JUMP_REGION
	//@功能:        ???
	//@负责人:      元林虎
	//@协助人:      ???
	//@备注:        ???
	**********************************************************************/
	struct PT_PLAYER_F2C_JUMP_REGION_DATA
	{
		Byte				regionType;
		RegionIdType 		regionId;
		InstanceUIdType		instanceUid;
		PlayerJumpResult	jumpResult;
		Byte				force;
		NetVec2Data			pos;
		NetVec2Data			dir;
	};
	struct PT_PLAYER_F2C_JUMP_REGION_INFO
	{
		static const Int dataSize = sizeof (PT_PLAYER_F2C_JUMP_REGION_DATA);
	};
	class PT_PLAYER_F2C_JUMP_REGION_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_PLAYER_F2C_JUMP_REGION_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_PLAYER;
			mType                               =   PT_PLAYER_F2C_JUMP_REGION;
			mBaseDataSize                       =   PT_PLAYER_F2C_JUMP_REGION_INFO::dataSize ;

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

	/////////////////////////////////////////////////////////////////////////////////
	/**********************************************************************
	//@名字:        PT_PLAYER_C2F_JUMP_REGION_BY_CHAR_ID
	//@功能:        ???
	//@负责人:      元林虎
	//@协助人:      ???
	//@备注:        ???
	**********************************************************************/
	struct PT_PLAYER_C2F_JUMP_REGION_BY_CHAR_ID_DATA
	{
		AccountIdType			accountId;
		PlayerCharacterIdType	playerCharacterId;
	};
	struct PT_PLAYER_C2F_JUMP_REGION_BY_CHAR_ID_INFO
	{
		static const Int dataSize = sizeof (PT_PLAYER_C2F_JUMP_REGION_BY_CHAR_ID_DATA);
	};
	class PT_PLAYER_C2F_JUMP_REGION_BY_CHAR_ID_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_PLAYER_C2F_JUMP_REGION_BY_CHAR_ID_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_PLAYER;
			mType                               =   PT_PLAYER_C2F_JUMP_REGION_BY_CHAR_ID;
			mBaseDataSize                       =   PT_PLAYER_C2F_JUMP_REGION_BY_CHAR_ID_INFO::dataSize ;

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
	//@名字:        PT_PLAYER_F2M_JUMP_REGION_BY_CHAR_ID
	//@功能:        ???
	//@负责人:      元林虎
	//@协助人:      ???
	//@备注:        ???
	**********************************************************************/
	struct PT_PLAYER_F2M_JUMP_REGION_BY_CHAR_ID_DATA
	{
		AccountIdType			accountId;
		PlayerCharacterIdType	playerCharacterId;
	};
	struct PT_PLAYER_F2M_JUMP_REGION_BY_CHAR_ID_INFO
	{
		static const Int dataSize = sizeof (PT_PLAYER_F2M_JUMP_REGION_BY_CHAR_ID_DATA);
	};
	class PT_PLAYER_F2M_JUMP_REGION_BY_CHAR_ID_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_PLAYER_F2M_JUMP_REGION_BY_CHAR_ID_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_PLAYER;
			mType                               =   PT_PLAYER_F2M_JUMP_REGION_BY_CHAR_ID;
			mBaseDataSize                       =   PT_PLAYER_F2M_JUMP_REGION_BY_CHAR_ID_INFO::dataSize ;

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
	//通知玩家登入
	struct PT_PLAYER_F2M_LOGIN_DATA
	{
		AccountIdType	accountId;
        IdType          clanId;                     //角色所属氏族ID
		I32				clientId;
		Byte			regionType;
		I32				regionID;
	};
    struct PT_PLAYER_F2M_LOGIN_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_PLAYER_F2M_LOGIN_DATA);
    };

    //////////////////////////////////////////////////////////////////////////////

	//通知玩家登出
	struct PT_PLAYER_F2M_LOGOUT_DATA
	{
		AccountIdType	accountId;
	};
    struct PT_PLAYER_F2M_LOGOUT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_PLAYER_F2M_LOGOUT_DATA);
    };
	
    /////////////////////////////////////////////////////////////////////////////////

	//发送角色信息给MapServer
	struct PT_PLAYER_F2M_PLAYERCHARACTER_INFO_LIST_DATA
	{
		Int						playerCharacterNum;
		NetPlayerCharacterInfo	playerCharacter[1];
	};
    struct PT_PLAYER_F2M_PLAYERCHARACTER_INFO_LIST_DATA_INFO
    {
        static const Int elementSize    = sizeof (NetPlayerCharacterInfo);
        static const Int headSize       = sizeof (PT_PLAYER_F2M_PLAYERCHARACTER_INFO_LIST_DATA) - sizeof (NetPlayerCharacterInfo);
        static const Int dataSize       = sizeof (PT_PLAYER_F2M_PLAYERCHARACTER_INFO_LIST_DATA);
    };
    /////////////////////////////////////////////////////////////////////////////////
    
	//发送角色装备信息给MapServer
	struct netPlayerItemEquip 
	{
		U32						equipId;
		U32						randAppendID;
		U32						strengthenAppendID;
		U32						curStrengthenLv;
	};
	struct netPlayerCharacterEquip
	{
		PlayerCharacterIdType   charid;
		netPlayerItemEquip      equipAttr[ITEM_EQUIP_SLOT_TYPE_MAX];
	};
	struct PT_PLAYER_F2M_PLAYERCHARACTER_EQUIP_INFO_LIST_DATA
	{
		Int                     playerCharacterNum;
		netPlayerCharacterEquip playerCharacterEquip[1];
	};
	struct PT_PLAYER_F2M_PLAYERCHARACTER_EQUIP_INFO_LIST_DATA_INFO
	{  
		static const Int elementSize    = sizeof (netPlayerCharacterEquip);
		static const Int headSize       = sizeof (PT_PLAYER_F2M_PLAYERCHARACTER_EQUIP_INFO_LIST_DATA) - sizeof(netPlayerCharacterEquip);
	};

    /////////////////////////////////////////////////////////////////////////////////

	//发生军队信息给MapServer
	struct PT_PLAYER_F2M_TROOP_INFO_LIST_DATA
	{
		Int						troopNum;
		NetTroopInfo			troopInfo[1];
	};
    struct PT_PLAYER_F2M_TROOP_INFO_LIST_DATA_INFO
    {
        static const Int elementSize    = sizeof (NetTroopInfo);
        static const Int headSize       = sizeof (PT_PLAYER_F2M_TROOP_INFO_LIST_DATA) - sizeof (NetTroopInfo);
    };

    /////////////////////////////////////////////////////////////////////////////////

	//struct PT_PLAYER_F2M_BATTLE_INFO_LIST_DATA
	//{
	//	Int						buildingNum;
	//	NetBattleBuildingInfo	buildingInfo[1];
	//};

	//struct PT_PLAYER_S2S_SYNC_ALL_LIST_END_DATA
	//{
	//};

	//struct PT_PLAYER_S2S_SYNC_ALL_LIST_END_DATA_INFO
	//{
	//	static const Int dataSize = sizeof (PT_PLAYER_S2S_SYNC_ALL_LIST_END_DATA);
	//};
    /////////////////////////////////////////////////////////////////////////////////

    //发生军队信息给Client
    struct  PT_PLAYER_F2C_TROOP_INFO_LIST_DATA
    {
        Int						troopNum;
        NetTroopInfo			troopInfo[1];
    };
    struct PT_PLAYER_F2C_TROOP_INFO_LIST_DATA_INFO
    {
        static const Int elementSize    = sizeof(NetTroopInfo);
        static const Int headSize       = sizeof (PT_PLAYER_F2C_TROOP_INFO_LIST_DATA) - sizeof (NetTroopInfo);
    };
    
    /////////////////////////////////////////////////////////////////////////////////
    
	// 发送角色信息给客户端
	struct PT_PLAYER_F2C_PLAYERCHARACTER_INFO_LIST_DATA
	{
        Int						remainPlayerCharacterNum;
		NetPlayerCharacterInfo	remainPlayerCharacter[1];
	};
    struct PT_PLAYER_F2C_PLAYERCHARACTER_INFO_LIST_DATA_INFO
    {
        static const Int elementSize    = sizeof(NetPlayerCharacterInfo);
        static const Int headSize       = sizeof (PT_PLAYER_F2C_PLAYERCHARACTER_INFO_LIST_DATA) - sizeof(NetPlayerCharacterInfo);
        static const Int dataSize       = sizeof (PT_PLAYER_F2C_PLAYERCHARACTER_INFO_LIST_DATA);
    };
    
	//发送设置主武将信息给客服端
    struct PT_PLAYER_F2C_MAIN_PLAYERCHARACTER_INFO_DATA
	{
          IdType generalId;
	};
    struct PT_PLAYER_F2C_MAIN_PLAYERCHARACTER_INFO_DATA_INFO
	{
         static const Int dataSize = sizeof(PT_PLAYER_F2C_MAIN_PLAYERCHARACTER_INFO_DATA);
	};
    /////////////////////////////////////////////////////////////////////////////////

	////发送【Remain角色】信息给客户端
	//struct PT_PLAYER_M2C_REMAIN_PLAYERCHARACTER_INFO_LIST_DATA
	//{
	//	Int						remainPlayerCharacterNum;
	//	NetPlayerCharacterInfo	remainPlayerCharacter[1];
	//};
 //   struct PT_PLAYER_M2C_REMAIN_PLAYERCHARACTER_INFO_LIST_DATA_INFO
 //   {
	//	static const Int elementSize = sizeof(NetPlayerCharacterInfo);
	//	static const Int headSize    = sizeof (PT_PLAYER_M2C_REMAIN_PLAYERCHARACTER_INFO_LIST_DATA) - sizeof(NetPlayerCharacterInfo);
 //       static const Int dataSize	= sizeof (PT_PLAYER_M2C_REMAIN_PLAYERCHARACTER_INFO_LIST_DATA);
 //   };



    /////////////////////////////////////////////////////////////////////////////////

	//struct PT_PLAYER_M2C_JUMP_REGION_DATA
	//{
	//	Byte	regionType;
	//	U64	    regionId;
	//	Int		placeCount;
	//	IdType	placeIds[1];
	//};



	/////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////

	//struct PT_PLAYER_F2C_JUMP_REGION_ERROR_DATA
	//{
	//	Player_Jump_Error_Type error;
	//};

	////客户端请求跳转区域
	//struct PT_PLAYER_C2F_JUMP_REGION_DATA
	//{
	//	RegionIdType	    regionId;
	//	Byte				regionType;
	//	InstanceUIdType		instanceUid;
	//};
 //   struct PT_PLAYER_C2F_JUMP_REGION_DATA_INFO
 //   {
 //       static const Int dataSize = sizeof (PT_PLAYER_C2F_JUMP_REGION_DATA);
 //   };

    /////////////////////////////////////////////////////////////////////////////////

	////请求跳转区域
	//struct PT_PLAYER_F2M_JUMP_REGION_DATA
	//{
	//	AccountIdType		accountId;
	//	Byte				regionType;
	//	RegionIdType		regionId;
	//	InstanceUIdType		instanceUid;
	//};
	//struct PT_PLAYER_F2M_JUMP_REGION_DATA_INFO
	//{
	//	static const Int dataSize = sizeof (PT_PLAYER_F2M_JUMP_REGION_DATA);
	//};

	/////////////////////////////////////////////////////////////////////////////////


	//struct PT_PLAYER_M2F_JUMP_REGION_DATA
	//{
	//	I32					client_net_id;
	//	Byte				regionType;
	//	U64	    			regionId;
	//	InstanceUIdType		instanceUid;
	//	PlayerJumpResult	jumpResult;
	//	Byte				force;
	//	NetVec2Data			pos;
	//};
	//struct PT_PLAYER_M2F_JUMP_REGION_DATA_INFO
	//{
	//	static const Int dataSize = sizeof (PT_PLAYER_M2F_JUMP_REGION_DATA);
	//};


	/////////////////////////////////////////////////////////////////////////////////

	////服务器告知客户端进入地图
	//struct PT_PLAYER_F2C_JUMP_REGION_DATA
	//{   
	//	Byte				regionType;
	//	U64	    			regionId;
	//	InstanceUIdType		instanceUid;
	//	PlayerJumpResult	jumpResult;
	//	Byte				force;
	//	NetVec2Data			pos;
	//};
	//struct PT_PLAYER_F2C_JUMP_REGION_DATA_INFO
	//{
	//	static const Int dataSize = sizeof (PT_PLAYER_F2C_JUMP_REGION_DATA);
	//};


	
	//struct PT_PLAYER_C2F_JUMP_REGION_BY_CHAR_ID_DATA
	//{
	//	AccountIdType			accountId;
	//	PlayerCharacterIdType	playerCharacterId;
	//};

	//struct PT_PLAYER_C2F_JUMP_REGION_BY_CHAR_ID_DATA_INFO
	//{
	//	static const Int dataSize = sizeof (PT_PLAYER_C2F_JUMP_REGION_BY_CHAR_ID_DATA);
	//};

	/////////////////////////////////////////////////////////////////////////////////

	//struct PT_PLAYER_F2M_JUMP_REGION_BY_CHAR_ID_DATA
	//{
	//	AccountIdType			accountId;
	//	PlayerCharacterIdType	playerCharacterId;

	//};
	//struct PT_PLAYER_F2M_JUMP_REGION_BY_CHAR_ID_DATA_INFO
	//{
	//	static const Int dataSize = sizeof (PT_PLAYER_F2M_JUMP_REGION_BY_CHAR_ID_DATA);
	//};
	/////////////////////////////////////////////////////////////////////////////////
#pragma pack (pop)
}

/******************************************************************************/

#endif