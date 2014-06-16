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
    //��Ϸ���԰�����
    /******************************************************************************/
    enum GeneralRecruitNetPacketType
    {
        PT_GR_UNKNOW = 0,

		PT_GR_C2F_FRESH_RANDOM_GENERAL,

		PT_GR_C2F_RANDOM_GENERAL_LIST,				//����ˢ������佫
		PT_GR_F2C_RANDOM_GENERAL_LIST_BEGIN,
		PT_GR_F2C_RANDOM_GENERAL_LIST,
		PT_GR_F2C_RANDOM_GENERAL_LIST_END,
        
		PT_GR_C2F_GENERAL_RECRUIT_CONFIRM,			//ȷ����ļ����佫
		PT_GR_F2C_GENERAL_RECRUIT_CONFIRM,			//

		PT_GR_F2C_GENERAL_RECRUIT_RESUILT,			//���

		PT_GR_C2F_CHANGE_GENERAL,					//�л��佫

		PT_GR_F2C_CLEAR_CLAN,						//�л��佫ǰ���������Ϣ

		PT_GR_F2C_RECRUIT_GENERAL_LIST_BEGIN,		//��������ļ�����佫�б�
		PT_GR_F2C_RECRUIT_GENERAL_LIST,
		PT_GR_F2C_RECRUIT_GENERAL_LIST_END,
    };

#pragma pack (push)
#pragma pack (1)
	
	/******************************************************************************/
	struct NetRandomGeneralInfo	//����佫���������Ϣ
	{
		U32			charTemplateId;
		Char16		name[MAX_CHARACTER_NAME_LEN];
		Flt			charAttrRand[DB_RECORD_ATTR_NUM];   	//��ɫ������츳����
		Flt			charAttrRandAdd[DB_RECORD_ATTR_NUM];	//��ɫ������츳���Եȼ�����
		UInt		charAttrAppendId;						//��ɫ���Ի�������iD
		UInt		charAttrAppendLvlId;					//��ɫ���Եȼ�����iD
		Int			index;									//����ֵ
		Int			age;									//��ǰ����
		Int			lifeSpan;								//����

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
	struct NetRecuitGeneralInfo	//����ļ���佫��Ϣ
	{
		U64			uin;				//ΨһID
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
		Recruit_Result_Success,				//�ɹ�
		Recruit_Result_Error_Index,			//��������
		Recruit_Result_Error_DB,			//���ݿ����
		Recruit_Result_Full,				//�����佫��ļ��
		Recruit_Result_Change_myself,		//�����л���ǰ�佫

		Recruit_Result_Max,
	};

    /**********************************************************************
    //@����:        PT_GR_C2F_FRESH_RANDOM_GENERAL
    //@����:        ����ˢ������佫
    //@������:      Ԫ�ֻ�
    //@Э����:      ???
    //@��ע:        ???
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
    //@����:        PT_GR_C2F_RANDOM_GENERAL_LIST
    //@����:        �����ȡ����佫���б�
    //@������:      Ԫ�ֻ�
    //@Э����:      ???
    //@��ע:        ???
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
    //@����:        PT_GR_F2C_RANDOM_GENERAL_LIST_BEGIN
    //@����:        ���ͻ�ȡ����佫���б� ��ʼ
    //@������:      Ԫ�ֻ�
    //@Э����:      ???
    //@��ע:        ???
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
    //@����:        PT_GR_F2C_RANDOM_GENERAL_LIST
    //@����:        ���ͻ�ȡ����佫���б�
    //@������:      Ԫ�ֻ�
    //@Э����:      ???
    //@��ע:        ???
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
    //@����:        PT_GR_F2C_RANDOM_GENERAL_LIST_END
    //@����:        �����ȡ����佫���б�
    //@������:      Ԫ�ֻ�
    //@Э����:      ???
    //@��ע:        ???
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
    //@����:        PT_GR_C2F_GENERAL_RECRUIT_CONFIRM
    //@����:        ȷ����ļ����佫
    //@������:      Ԫ�ֻ�
    //@Э����:      ???
    //@��ע:        ???
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
    //@����:        PT_GR_F2C_GENERAL_RECRUIT_CONFIRM
    //@����:        ȷ����ļ����佫
    //@������:      Ԫ�ֻ�
    //@Э����:      ???
    //@��ע:        ???
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
    //@����:        PT_GR_F2C_GENERAL_RECRUIT_RESUILT
    //@����:        ��ļ����佫���
    //@������:      Ԫ�ֻ�
    //@Э����:      ???
    //@��ע:        ???
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
    //@����:        PT_GR_C2F_CHANGE_GENERAL
    //@����:        �л��佫
    //@������:      Ԫ�ֻ�
    //@Э����:      ???
    //@��ע:        ???
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
    //@����:        PT_GR_F2C_CLEAR_CLAN
    //@����:        �л��佫ǰ���������Ϣ
    //@������:      Ԫ�ֻ�
    //@Э����:      ???
    //@��ע:        ???
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
    //@����:        PT_GR_F2C_RECRUIT_GENERAL_LIST_BEGIN
    //@����:        ��������ļ�����佫�б� ��ʼ
    //@������:      Ԫ�ֻ�
    //@Э����:      ???
    //@��ע:        ???
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
    //@����:        PT_GR_F2C_RECRUIT_GENERAL_LIST
    //@����:        ��������ļ�����佫�б�
    //@������:      Ԫ�ֻ�
    //@Э����:      ???
    //@��ע:        ???
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
    //@����:        PT_GR_F2C_RECRUIT_GENERAL_LIST_END
    //@����:        ��������ļ�����佫�б� ����
    //@������:      Ԫ�ֻ�
    //@Э����:      ???
    //@��ע:        ???
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