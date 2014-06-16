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
	//@������:      �쿪��
	//@Э����:      ???
	**********************************************************************/

    /******************************************************************************/
    //��Ϸ���԰�����
    /******************************************************************************/
    enum AttrNetPacketType
    {
        PT_ATTR_UNKNOW = 0,

        //�˺����������ƣ���������
        PT_ATTR_F2C_ATTR_HPMPSP,			//front ���͸�client�߼�
        PT_ATTR_S2C_ATTR_HPMPSP,			//��client����ͬ��

        PT_ATTR_M2F_ATTR_HPMPSP,			//��frontsever�������ư�

		PT_ATTR_F2M_ATTR_LEVEL,				//��MapServerת�͵ȼ���������Ϣ
		PT_ATTR_M2C_ATTR_LEVEL,				//��clientͬ���ȼ���������Ϣ

        
    };

#pragma pack (push)
#pragma pack (1)

	//**********************************************************************
	//@����:        PT_ATTR_S2C_ATTR_HPMPSP
	//@����:        ��ͻ���ͬ��Ѫħ�����Ļ򲹳䣩����Ϣ
	//@��ע:        ???
	//**********************************************************************/
    struct PT_ATTR_S2C_ATTR_HPMPSP_DATA
    {
        U64		Id;                                 //��ɫID
        Byte    objType;                            //��ɫ���ͣ��佫�����ӣ������� �ȣ�
		U64		masterId;							//����ʹ���ߵ�id
		Byte    masterType;							//��ɫ���ͣ��佫�����ӣ������� �ȣ�
        Byte    resultType;                         //���յĽ������Ч�����գ����������ˣ��ظ���
        Byte	damageType;                         //�������ͣ�Ѫ������ŭ�������У�
        UInt	val;								//����ֵ
		Byte    hateVal;							//���ֵ
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
	//@����:        PT_ATTR_F2C_ATTR_HPMPSP
	//@����:        ��ͻ����߼�����Ѫħ�����Ļ򲹳䣩����Ϣ
	//@��ע:        ��Ҫ����֪ͨ�ͻ��˸��������Ϣ�����߼���������
	//**********************************************************************/

    //-----------------------------------------------------
    struct PT_ATTR_F2C_ATTR_HPMPSP_DATA
    {
        Byte    resultType;                         //���յĽ������Ч�����գ����������ˣ��ظ���
        Byte	damageType;                         //�������ͣ�Ѫ������ŭ�������У�
        UInt	val;                                //����ֵ��
		U64		Id;                                 //��ɫid
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
	//@����:        PT_ATTR_M2F_ATTR_HPMPSP
	//@����:        ��frontServer�����߼�����Ѫħ�����Ļ򲹳䣩����Ϣ
	//@��ע:        ��Ҫ����frontServer֪ͨDB���£�֪ͨ�ͻ����߼�����
	//**********************************************************************/
    //-----------------------------------------------------
    struct  PT_ATTR_M2F_ATTR_HPMPSP_DATA
    {   
        Byte    resultType;                         //���յĽ������Ч�����գ����������ˣ��ظ���
        Byte	damageType;                         //�������ͣ�Ѫ������ŭ�������У�
        U32     value;                              //����ֵ��
		AccountIdType accountId;
		IdType	Id;                                 //��ɫID
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
	//@����:        PT_ATTR_M2C_ATTR_LEVEL
	//@����:        ��ͻ���ͬ�������������Ϣ
	//@��ע:        ֪ͨ�ͻ���ʵ����������ҵȼ������߲������������Ч��
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
	//@����:        PT_ATTR_F2M_ATTR_LEVEL
	//@����:        ��mapServer���������������Ϣ����Ϣ
	//@��ע:        ��Ҫ����mapServer������ҵȼ��͹㲥
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