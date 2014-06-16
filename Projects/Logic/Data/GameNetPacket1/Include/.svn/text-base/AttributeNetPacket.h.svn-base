//************************************************************************************************
#ifndef _H_ATTRIBUTENETPACKET_
#define _H_ATTRIBUTENETPACKET_
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
    enum AttrNetPacketType
    {
        PT_ATTR_UNKNOW = 0,

        //伤害，技能治疗，道具治疗
        PT_ATTR_F2C_ATTR_HPMPSP,			//front 发送给client逻辑
        PT_ATTR_S2C_ATTR_HPMPSP,			//向client场景同步

        PT_ATTR_M2F_ATTR_HPMPSP,			//向frontsever发送治疗包

		PT_ATTR_F2M_ATTR_LEVEL,				//向MapServer转送等级提升的消息
		PT_ATTR_M2C_ATTR_LEVEL,				//向client同步等级提升的消息

        
    };

#pragma pack (push)
#pragma pack (1)

	//**********************************************************************
	//@名字:        PT_ATTR_S2C_ATTR_HPMPSP
	//@功能:        向客户端同步血魔（消耗或补充）的消息
	//@备注:        ???
	//**********************************************************************/
    struct PT_ATTR_S2C_ATTR_HPMPSP_DATA
    {
        U64		Id;                                 //角色ID
        Byte    objType;                            //角色类型（武将，军队，建筑物 等）
		U64		masterId;							//技能使用者的id
		Byte    masterType;							//角色类型（武将，军队，建筑物 等）
        Byte    resultType;                         //最终的结果（无效，吸收，死亡，受伤，回复）
        Byte	damageType;                         //减伤类型（血，法，怒气，或都有）
        UInt	val;								//最终值
		Byte    hateVal;							//仇恨值
    };
    struct PT_ATTR_S2C_ATTR_HPMPSP_INFO
    {
        static const Int dataSize = sizeof (PT_ATTR_S2C_ATTR_HPMPSP_DATA);
    };
    class PT_ATTR_S2C_ATTR_HPMPSP_DESCRIBE : public GameNetPacketDataDescribe
    {
    public:
        PT_ATTR_S2C_ATTR_HPMPSP_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_ATTRIBUTE;
            mType                               =   PT_ATTR_S2C_ATTR_HPMPSP;
            mBaseDataSize                       =   PT_ATTR_S2C_ATTR_HPMPSP_INFO::dataSize ;

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
	//@名字:        PT_ATTR_F2C_ATTR_HPMPSP
	//@功能:        向客户端逻辑对象血魔（消耗或补充）的消息
	//@备注:        主要用于通知客户端更新面板信息，和逻辑对象数据
	//**********************************************************************/

    //-----------------------------------------------------
    struct PT_ATTR_F2C_ATTR_HPMPSP_DATA
    {
        Byte    resultType;                         //最终的结果（无效，吸收，死亡，受伤，回复）
        Byte	damageType;                         //减伤类型（血，法，怒气，或都有）
        UInt	val;                                //最终值。
		U64		Id;                                 //角色id
    };
    struct PT_ATTR_F2C_ATTR_HPMPSP_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_ATTR_F2C_ATTR_HPMPSP_DATA);
    };

	class PT_ATTR_F2C_ATTR_HPMPSP_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_ATTR_F2C_ATTR_HPMPSP_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_ATTRIBUTE;
			mType                               =   PT_ATTR_F2C_ATTR_HPMPSP;
			mBaseDataSize                       =   PT_ATTR_F2C_ATTR_HPMPSP_DATA_INFO::dataSize ;

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
	//@名字:        PT_ATTR_M2F_ATTR_HPMPSP
	//@功能:        向frontServer法术逻辑对象血魔（消耗或补充）的消息
	//@备注:        主要用于frontServer通知DB更新，通知客户端逻辑对象
	//**********************************************************************/
    //-----------------------------------------------------
    struct  PT_ATTR_M2F_ATTR_HPMPSP_DATA
    {   
        Byte    resultType;                         //最终的结果（无效，吸收，死亡，受伤，回复）
        Byte	damageType;                         //减伤类型（血，法，怒气，或都有）
        U32     value;                              //最终值。
		AccountIdType accountId;
		IdType	Id;                                 //角色ID
    };
    struct PT_ATTR_M2F_ATTR_HPMPSP_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_ATTR_M2F_ATTR_HPMPSP_DATA);
    };
	class PT_ATTR_M2F_ATTR_HPMPSP_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_ATTR_M2F_ATTR_HPMPSP_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_ATTRIBUTE;
			mType                               =   PT_ATTR_M2F_ATTR_HPMPSP;
			mBaseDataSize                       =   PT_ATTR_M2F_ATTR_HPMPSP_DATA_INFO::dataSize ;

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
    //-----------------------------------------------------------------------------------------
	//**********************************************************************
	//@名字:        PT_ATTR_M2C_ATTR_LEVEL
	//@功能:        向客户端同步玩家升级的消息
	//@备注:        通知客户端实体对象更新玩家等级。或者播放玩家升级特效。
	//**********************************************************************/
	struct PT_ATTR_M2C_ATTR_LEVEL_DATA 
	{
		AccountIdType			accountId;
		Byte					levelType;
		U32						level;
		PlayerCharacterIdType	charId;
		U32						hp;
		U32						hpMax;
		U32						mp;
		U32						mpMax;
	};
	struct PT_ATTR_M2C_ATTR_LEVEL_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_ATTR_M2C_ATTR_LEVEL_DATA);
	};
	class PT_ATTR_M2C_ATTR_LEVEL_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_ATTR_M2C_ATTR_LEVEL_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_ATTRIBUTE;
			mType                               =   PT_ATTR_M2C_ATTR_LEVEL;
			mBaseDataSize                       =   PT_ATTR_M2C_ATTR_LEVEL_DATA_INFO::dataSize ;

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
	//-----------------------------------------------------------------------------------------
	//**********************************************************************
	//@名字:        PT_ATTR_F2M_ATTR_LEVEL
	//@功能:        向mapServer发送玩家升级的消息的消息
	//@备注:        主要用于mapServer更新玩家等级和广播
	//**********************************************************************/
	struct  PT_ATTR_F2M_ATTR_LEVEL_DATA
	{
		Byte					levelType;
		U32						level;
		PlayerCharacterIdType	charId;
	};
	struct PT_ATTR_F2M_ATTR_LEVEL_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_ATTR_F2M_ATTR_LEVEL_DATA);
	};
	class PT_ATTR_F2M_ATTR_LEVEL_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_ATTR_F2M_ATTR_LEVEL_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_ATTRIBUTE;
			mType                               =   PT_ATTR_F2M_ATTR_LEVEL;
			mBaseDataSize                       =   PT_ATTR_F2M_ATTR_LEVEL_DATA_INFO::dataSize ;

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

#pragma pack (pop)
}
//************************************************************************************************
#endif
//************************************************************************************************