//************************************************************************************************
#ifndef _GENERAL_RECRUIT_NET_PACKET_H_
#define _GENERAL_RECRUIT_NET_PACKET_H_
//************************************************************************************************
#include "CommonGameDefine.h"
#include "NetDefine.h"
#include "GameNetPacket.h"
//************************************************************************************************
namespace MG
{
    /******************************************************************************/
    //游戏属性包类型
    /******************************************************************************/
    enum GeneralRecruitNetPacketType
    {
        PT_GR_UNKNOW = 0,

		PT_GR_C2F_FRESH_RANDOM_GENERAL,

		PT_GR_C2F_RANDOM_GENERAL_LIST,				//请求刷新随机武将
		PT_GR_F2C_RANDOM_GENERAL_LIST_BEGIN,
		PT_GR_F2C_RANDOM_GENERAL_LIST,
		PT_GR_F2C_RANDOM_GENERAL_LIST_END,
        
		PT_GR_C2F_GENERAL_RECRUIT_CONFIRM,			//确认招募随机武将
		PT_GR_F2C_GENERAL_RECRUIT_CONFIRM,			//

		PT_GR_F2C_GENERAL_RECRUIT_RESUILT,			//结果

		PT_GR_C2F_CHANGE_GENERAL,					//切换武将

		PT_GR_F2C_CLEAR_CLAN,						//切换武将前清除家族信息

		PT_GR_F2C_RECRUIT_GENERAL_LIST_BEGIN,		//发送已招募过的武将列表
		PT_GR_F2C_RECRUIT_GENERAL_LIST,
		PT_GR_F2C_RECRUIT_GENERAL_LIST_END,
    };

#pragma pack (push)
#pragma pack (1)
	
	/******************************************************************************/
	struct NetRandomGeneralInfo	//随机武将随机属性信息
	{
		U32			charTemplateId;
		Char16		name[MAX_CHARACTER_NAME_LEN];
		Flt			charAttrRand[DB_RECORD_ATTR_NUM];   	//角色的随机天赋属性
		Flt			charAttrRandAdd[DB_RECORD_ATTR_NUM];	//角色的随机天赋属性等级附加
		UInt		charAttrAppendId;						//角色属性基本附加iD
		UInt		charAttrAppendLvlId;					//角色属性等级附加iD
		Int			index;									//索引值
		Int			age;									//当前年龄
		Int			lifeSpan;								//寿命

		NetRandomGeneralInfo()
			:charTemplateId(0)
			,charAttrAppendId(0)
			,charAttrAppendLvlId(0)
			,index(0)
			,age(0)
			,lifeSpan(0)
		{
			memset(name, 0, sizeof(name));
			memset(charAttrRand, 0, sizeof(charAttrRand));
			memset(charAttrRandAdd, 0, sizeof(charAttrRandAdd));
		}
	};

	/******************************************************************************/
	struct NetRecuitGeneralInfo	//已招募的武将信息
	{
		U64			uin;				//唯一ID
		U32			charTemplateId;
		
		NetRecuitGeneralInfo()
			:uin(0)
			,charTemplateId(0)
		{
		}
	};

	/******************************************************************************/
	enum Recruit_Result
	{
		Recruit_Result_Success,				//成功
		Recruit_Result_Error_Index,			//索引不对
		Recruit_Result_Error_DB,			//数据库出错
		Recruit_Result_Full,				//超出武将招募数
		Recruit_Result_Change_myself,		//不能切换当前武将

		Recruit_Result_Max,
	};

    /**********************************************************************
    //@名字:        PT_GR_C2F_FRESH_RANDOM_GENERAL
    //@功能:        请求刷新随机武将
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
    struct PT_GR_C2F_FRESH_RANDOM_GENERAL_DATA
    {
		U32 GeneralRecruitId;
    };

    struct PT_GR_C2F_FRESH_RANDOM_GENERAL_INFO
    {
        static const Int dataSize = sizeof (PT_GR_C2F_FRESH_RANDOM_GENERAL_DATA);
    };

    class PT_GR_C2F_FRESH_RANDOM_GENERAL_DESCRIBE : public GameNetPacketDataDescribe
    {
    public:
        PT_GR_C2F_FRESH_RANDOM_GENERAL_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_GENERAL_RECRUIT;
            mType                               =   PT_GR_C2F_FRESH_RANDOM_GENERAL;
            mBaseDataSize                       =   PT_GR_C2F_FRESH_RANDOM_GENERAL_INFO::dataSize ;

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
    //@名字:        PT_GR_C2F_RANDOM_GENERAL_LIST
    //@功能:        请求获取随机武将的列表
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
    struct PT_GR_C2F_RANDOM_GENERAL_LIST_DATA
    {
		U32 GeneralRecruitId;
    };

    struct PT_GR_C2F_RANDOM_GENERAL_LIST_INFO
    {
        static const Int dataSize = sizeof (PT_GR_C2F_RANDOM_GENERAL_LIST_DATA);
    };

    class PT_GR_C2F_RANDOM_GENERAL_LIST_DESCRIBE : public GameNetPacketDataDescribe
    {
    public:
        PT_GR_C2F_RANDOM_GENERAL_LIST_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_GENERAL_RECRUIT;
            mType                               =   PT_GR_C2F_RANDOM_GENERAL_LIST;
            mBaseDataSize                       =   PT_GR_C2F_RANDOM_GENERAL_LIST_INFO::dataSize ;

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
    //@名字:        PT_GR_F2C_RANDOM_GENERAL_LIST_BEGIN
    //@功能:        发送获取随机武将的列表 开始
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
    struct PT_GR_F2C_RANDOM_GENERAL_LIST_BEGIN_DATA
    {

    };

    struct PT_GR_F2C_RANDOM_GENERAL_LIST_BEGIN_INFO
    {
        static const Int dataSize = sizeof (PT_GR_F2C_RANDOM_GENERAL_LIST_BEGIN);
    };

    class PT_GR_F2C_RANDOM_GENERAL_LIST_BEGIN_DESCRIBE : public GameNetPacketDataDescribe
    {
    public:
        PT_GR_F2C_RANDOM_GENERAL_LIST_BEGIN_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_GENERAL_RECRUIT;
            mType                               =   PT_GR_F2C_RANDOM_GENERAL_LIST_BEGIN;
            mBaseDataSize                       =   PT_GR_F2C_RANDOM_GENERAL_LIST_BEGIN_INFO::dataSize ;

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
    //@名字:        PT_GR_F2C_RANDOM_GENERAL_LIST
    //@功能:        发送获取随机武将的列表
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
    struct PT_GR_F2C_RANDOM_GENERAL_LIST_DATA
    {
		U32						addGeneralNum;
		NetRandomGeneralInfo	addGeneralInfo[1];
    };

    struct PT_GR_F2C_RANDOM_GENERAL_LIST_INFO
    {
		static Int const 	netAddGeneralInfoSize = sizeof (NetRandomGeneralInfo);
		static Int const 	headSize = sizeof (PT_GR_F2C_RANDOM_GENERAL_LIST_DATA) - sizeof(NetRandomGeneralInfo);
		static Int       	dataSize(PT_GR_F2C_RANDOM_GENERAL_LIST_DATA* data)
		{ 
			return PT_GR_F2C_RANDOM_GENERAL_LIST_INFO::headSize + PT_GR_F2C_RANDOM_GENERAL_LIST_INFO::netAddGeneralInfoSize * data->addGeneralNum;
		};
    };

    class PT_GR_F2C_RANDOM_GENERAL_LIST_DESCRIBE : public GameNetPacketDataDescribe
    {
    public:
        PT_GR_F2C_RANDOM_GENERAL_LIST_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_GENERAL_RECRUIT;
            mType                               =   PT_GR_F2C_RANDOM_GENERAL_LIST;
            //mBaseDataSize                       =   PT_GR_F2C_GENERAL_LIST_INFO::dataSize ;

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
			if ( dataLen != PT_GR_F2C_RANDOM_GENERAL_LIST_INFO::dataSize((PT_GR_F2C_RANDOM_GENERAL_LIST_DATA*)data) )
				return false;
			return true;
		}
    };

	/**********************************************************************
    //@名字:        PT_GR_F2C_RANDOM_GENERAL_LIST_END
    //@功能:        请求获取随机武将的列表
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
    struct PT_GR_F2C_RANDOM_GENERAL_LIST_END_DATA
    {

    };

    struct PT_GR_F2C_RANDOM_GENERAL_LIST_END_INFO
    {
        static const Int dataSize = sizeof (PT_GR_F2C_RANDOM_GENERAL_LIST_END_DATA);
    };

    class PT_GR_F2C_RANDOM_GENERAL_LIST_END_DESCRIBE : public GameNetPacketDataDescribe
    {
    public:
        PT_GR_F2C_RANDOM_GENERAL_LIST_END_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_GENERAL_RECRUIT;
            mType                               =   PT_GR_F2C_RANDOM_GENERAL_LIST_END;
            mBaseDataSize                       =   PT_GR_F2C_RANDOM_GENERAL_LIST_END_INFO::dataSize ;

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
    //@名字:        PT_GR_C2F_GENERAL_RECRUIT_CONFIRM
    //@功能:        确认招募随机武将
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
    struct PT_GR_C2F_GENERAL_RECRUIT_CONFIRM_DATA
    {
		U32 index;
    };

    struct PT_GR_C2F_GENERAL_RECRUIT_CONFIRM_INFO
    {
        static const Int dataSize = sizeof (PT_GR_C2F_GENERAL_RECRUIT_CONFIRM_DATA);
    };

    class PT_GR_C2F_GENERAL_RECRUIT_CONFIRM_DESCRIBE : public GameNetPacketDataDescribe
    {
    public:
        PT_GR_C2F_GENERAL_RECRUIT_CONFIRM_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_GENERAL_RECRUIT;
            mType                               =   PT_GR_C2F_GENERAL_RECRUIT_CONFIRM;
            mBaseDataSize                       =   PT_GR_C2F_GENERAL_RECRUIT_CONFIRM_INFO::dataSize ;

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
    //@名字:        PT_GR_F2C_GENERAL_RECRUIT_CONFIRM
    //@功能:        确认招募随机武将
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
    struct PT_GR_F2C_GENERAL_RECRUIT_CONFIRM_DATA
    {
		U32 index;
    };

    struct PT_GR_F2C_GENERAL_RECRUIT_CONFIRM_INFO
    {
        static const Int dataSize = sizeof (PT_GR_F2C_GENERAL_RECRUIT_CONFIRM_DATA);
    };

    class PT_GR_F2C_GENERAL_RECRUIT_CONFIRM_DESCRIBE : public GameNetPacketDataDescribe
    {
    public:
        PT_GR_F2C_GENERAL_RECRUIT_CONFIRM_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_GENERAL_RECRUIT;
            mType                               =   PT_GR_F2C_GENERAL_RECRUIT_CONFIRM;
            mBaseDataSize                       =   PT_GR_F2C_GENERAL_RECRUIT_CONFIRM_INFO::dataSize ;

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
    //@名字:        PT_GR_F2C_GENERAL_RECRUIT_RESUILT
    //@功能:        招募随机武将结果
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
    struct PT_GR_F2C_GENERAL_RECRUIT_RESUILT_DATA
    {
		Int		result;
    };

    struct PT_GR_F2C_GENERAL_RECRUIT_RESUILT_INFO
    {
        static const Int dataSize = sizeof (PT_GR_F2C_GENERAL_RECRUIT_RESUILT_DATA);
    };

    class PT_GR_F2C_GENERAL_RECRUIT_RESUILT_DESCRIBE : public GameNetPacketDataDescribe
    {
    public:
        PT_GR_F2C_GENERAL_RECRUIT_RESUILT_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_GENERAL_RECRUIT;
            mType                               =   PT_GR_F2C_GENERAL_RECRUIT_RESUILT;
            mBaseDataSize                       =   PT_GR_F2C_GENERAL_RECRUIT_RESUILT_INFO::dataSize ;

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
    //@名字:        PT_GR_C2F_CHANGE_GENERAL
    //@功能:        切换武将
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
    struct PT_GR_C2F_CHANGE_GENERAL_DATA
    {
		PlayerCharacterIdType charId;
    };

    struct PT_GR_C2F_CHANGE_GENERAL_INFO
    {
        static const Int dataSize = sizeof (PT_GR_C2F_CHANGE_GENERAL_DATA);
    };

    class PT_GR_C2F_CHANGE_GENERAL_DESCRIBE : public GameNetPacketDataDescribe
    {
    public:
        PT_GR_C2F_CHANGE_GENERAL_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_GENERAL_RECRUIT;
            mType                               =   PT_GR_C2F_CHANGE_GENERAL;
            mBaseDataSize                       =   PT_GR_C2F_CHANGE_GENERAL_INFO::dataSize ;

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
    //@名字:        PT_GR_F2C_CLEAR_CLAN
    //@功能:        切换武将前清除家族信息
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
    struct PT_GR_F2C_CLEAR_CLAN_DATA
    {

    };

    struct PT_GR_F2C_CLEAR_CLAN_INFO
    {
        static const Int dataSize = sizeof (PT_GR_F2C_CLEAR_CLAN_DATA);
    };

    class PT_GR_F2C_CLEAR_CLAN_DESCRIBE : public GameNetPacketDataDescribe
    {
    public:
        PT_GR_F2C_CLEAR_CLAN_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_GENERAL_RECRUIT;
            mType                               =   PT_GR_F2C_CLEAR_CLAN;
            mBaseDataSize                       =   PT_GR_F2C_CLEAR_CLAN_INFO::dataSize ;

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
    //@名字:        PT_GR_F2C_RECRUIT_GENERAL_LIST_BEGIN
    //@功能:        发送已招募过的武将列表 开始
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
    struct PT_GR_F2C_RECRUIT_GENERAL_LIST_BEGIN_DATA
    {

    };

    struct PT_GR_F2C_RECRUIT_GENERAL_LIST_BEGIN_INFO
    {
        static const Int dataSize = sizeof (PT_GR_F2C_RECRUIT_GENERAL_LIST_BEGIN_DATA);
    };

    class PT_GR_F2C_RECRUIT_GENERAL_LIST_BEGIN_DESCRIBE : public GameNetPacketDataDescribe
    {
    public:
        PT_GR_F2C_RECRUIT_GENERAL_LIST_BEGIN_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_GENERAL_RECRUIT;
            mType                               =   PT_GR_F2C_RECRUIT_GENERAL_LIST_BEGIN;
            mBaseDataSize                       =   PT_GR_F2C_RECRUIT_GENERAL_LIST_BEGIN_INFO::dataSize ;

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
    //@名字:        PT_GR_F2C_RECRUIT_GENERAL_LIST
    //@功能:        发送已招募过的武将列表
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
    struct PT_GR_F2C_RECRUIT_GENERAL_LIST_DATA
    {
		Int						addGeneralNum;
		NetRecuitGeneralInfo	addGeneralInfo[1];
    };

    struct PT_GR_F2C_RECRUIT_GENERAL_LIST_INFO
    {
		static Int const 	netAddGeneralInfoSize = sizeof (NetRecuitGeneralInfo);
		static Int const 	headSize = sizeof (PT_GR_F2C_RECRUIT_GENERAL_LIST_DATA) - sizeof(NetRecuitGeneralInfo);
		static Int       	dataSize(PT_GR_F2C_RECRUIT_GENERAL_LIST_DATA* data)
		{ 
			return PT_GR_F2C_RECRUIT_GENERAL_LIST_INFO::headSize + PT_GR_F2C_RECRUIT_GENERAL_LIST_INFO::netAddGeneralInfoSize * data->addGeneralNum;
		};
    };

    class PT_GR_F2C_RECRUIT_GENERAL_LIST_DESCRIBE : public GameNetPacketDataDescribe
    {
    public:
        PT_GR_F2C_RECRUIT_GENERAL_LIST_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_GENERAL_RECRUIT;
            mType                               =   PT_GR_F2C_RECRUIT_GENERAL_LIST;
            //mBaseDataSize                       =   PT_GR_F2C_GENERAL_LIST_INFO::dataSize ;

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
			if ( dataLen != PT_GR_F2C_RECRUIT_GENERAL_LIST_INFO::dataSize((PT_GR_F2C_RECRUIT_GENERAL_LIST_DATA*)data) )
				return false;
			return true;
		}
    };

	/**********************************************************************
    //@名字:        PT_GR_F2C_RECRUIT_GENERAL_LIST_END
    //@功能:        发送已招募过的武将列表 结束
    //@负责人:      元林虎
    //@协助人:      ???
    //@备注:        ???
    **********************************************************************/
    struct PT_GR_F2C_RECRUIT_GENERAL_LIST_END_DATA
    {

    };

    struct PT_GR_F2C_RECRUIT_GENERAL_LIST_END_INFO
    {
        static const Int dataSize = sizeof (PT_GR_F2C_RECRUIT_GENERAL_LIST_END_DATA);
    };

    class PT_GR_F2C_RECRUIT_GENERAL_LIST_END_DESCRIBE : public GameNetPacketDataDescribe
    {
    public:
        PT_GR_F2C_RECRUIT_GENERAL_LIST_END_DESCRIBE()
            :GameNetPacketDataDescribe()
        {
            mChannel                            =   GNPC_GENERAL_RECRUIT;
            mType                               =   PT_GR_F2C_RECRUIT_GENERAL_LIST_END;
            mBaseDataSize                       =   PT_GR_F2C_RECRUIT_GENERAL_LIST_END_INFO::dataSize ;

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
#endif	//_GENERAL_RECRUIT_NET_PACKET_H_
//************************************************************************************************