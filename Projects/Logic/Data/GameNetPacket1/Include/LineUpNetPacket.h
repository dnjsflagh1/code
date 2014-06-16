/******************************************************************************/
#ifndef _LINEUPNETPACKET_H_
#define _LINEUPNETPACKET_H_
/******************************************************************************/

#include "CommonGameDefine.h"
#include "NetDefine.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //��Ϸ�ŶӰ�����
    /******************************************************************************/
    enum LineUpNetPacketType
    {
		PT_LINE_UP_L2C,
		PT_LINE_UP_C2L_CANCLE_CMD,
		PT_LINE_UP_L2C_CANCLE_CMD_RELULT,

		PT_LINE_UP_F2C,
		PT_LINE_UP_C2F_CANCLE_CMD,
		PT_LINE_UP_F2C_CANCLE_CMD_RELULT,
		
    };
    
	/******************************************************************************/
	//��Ϸ�Ŷ���Ϣ����
	/******************************************************************************/
    enum LINE_UP_TYPE
	{
        line_up_busy_lc_account_login = 1,				//����Login�Ŷ�
		line_up_busy_lc_server_full,					//��������������
		line_up_busy_fc_account_login,					//�ʺŵ�¼FrontServer�Ŷ�
		line_up_busy_fc_create_clan,					//���������Ŷ�
		line_up_busy_fc_del_clan,						//ɾ�������Ŷ�
		line_up_busy_fc_create_character,				//������ɫ�Ŷ�
		line_up_busy_fc_join_game						//������Ϸ��ͼ�Ŷ�
	};


#pragma pack (push)
#pragma pack (1)

	//**********************************************************************
	//@����:        PT_LINE_UP_L2C
	//@����:        Loginserver���ص�½������Ϣ���ͻ���
	//@��ע:        ???
	//**********************************************************************/
	struct  PT_LINE_UP_L2C_DATA
	{   
		Byte type;
		I32	waitCount;
	};
	struct PT_LINE_UP_L2C_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LINE_UP_L2C_DATA);
	};
	class PT_LINE_UP_L2C_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LINE_UP_L2C_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LINE_UP;
			mType                               =   PT_LINE_UP_L2C;
			mBaseDataSize                       =   PT_LINE_UP_L2C_DATA_INFO::dataSize ;

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
	//@����:       PT_LINE_UP_C2L_CANCLE_CMD
	//@����:       Client��LoginServer����ȡ���Ŷ�����
	//@��ע:        ???
	//**********************************************************************/
	struct  PT_LINE_UP_C2L_CANCLE_CMD_DATA
	{   
		Byte type;
	};
	struct PT_LINE_UP_C2L_CANCLE_CMD_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LINE_UP_C2L_CANCLE_CMD_DATA);
	};
	class PT_LINE_UP_C2L_CANCLE_CMD_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LINE_UP_C2L_CANCLE_CMD_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LINE_UP;
			mType                               =   PT_LINE_UP_C2L_CANCLE_CMD;
			mBaseDataSize                       =   PT_LINE_UP_C2L_CANCLE_CMD_DATA_INFO::dataSize ;

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
	};
	//**********************************************************************
	//@����:       PT_LINE_UP_L2C_CANCLE_CMD_RELULT
	//@����:       LoginServer����ȡ���Ŷ���������Client
	//@��ע:        ???
	//**********************************************************************/
	struct  PT_LINE_UP_L2C_CANCLE_CMD_RELULT_DATA
	{   
		Byte type;
		Byte result;
	};
	struct PT_LINE_UP_L2C_CANCLE_CMD_RELULT_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LINE_UP_L2C_CANCLE_CMD_RELULT_DATA);
	};
	class PT_LINE_UP_L2C_CANCLE_CMD_RELULT_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LINE_UP_L2C_CANCLE_CMD_RELULT_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LINE_UP;
			mType                               =   PT_LINE_UP_L2C_CANCLE_CMD_RELULT;
			mBaseDataSize                       =	PT_LINE_UP_L2C_CANCLE_CMD_RELULT_DATA_INFO::dataSize ;

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
	//@����:       PT_LINE_UP_F2C
	//@����:       FrontServer���ص�½������Ϣ��Client
	//@��ע:        ???
	//**********************************************************************/
	struct  PT_LINE_UP_F2C_DATA
	{   
		Byte type;
		I32 waitCount;
	};
	struct PT_LINE_UP_F2C_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LINE_UP_F2C_DATA);
	};
	class PT_LINE_UP_F2C_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LINE_UP_F2C_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LINE_UP;
			mType                               =   PT_LINE_UP_F2C;
			mBaseDataSize                       =	PT_LINE_UP_F2C_DATA_INFO::dataSize ;

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
	//@����:       PT_LINE_UP_C2F_CANCLE_CMD
	//@����:       Client��FrontServer����ȡ���Ŷ�����
	//@��ע:        ???
	//**********************************************************************/
	struct  PT_LINE_UP_C2F_CANCLE_CMD_DATA
	{   
		Byte type;
	};
	struct PT_LINE_UP_C2F_CANCLE_CMD_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LINE_UP_C2F_CANCLE_CMD_DATA);
	};
	class PT_LINE_UP_C2F_CANCLE_CMD_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LINE_UP_C2F_CANCLE_CMD_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LINE_UP;
			mType                               =   PT_LINE_UP_C2F_CANCLE_CMD;
			mBaseDataSize                       =	PT_LINE_UP_C2F_CANCLE_CMD_DATA_INFO::dataSize ;

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
	};
	//**********************************************************************
	//@����:      PT_LINE_UP_F2C_CANCLE_CMD_RELULT
	//@����:      FrontServer����ȡ���Ŷӽ����Client
	//@��ע:      ???
	//**********************************************************************/
	struct  PT_LINE_UP_F2C_CANCLE_CMD_RELULT_DATA
	{   
		Byte type;
		Byte result;
	};
	struct PT_LINE_UP_F2C_CANCLE_CMD_RELULT_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LINE_UP_F2C_CANCLE_CMD_RELULT_DATA);
	};
	class PT_LINE_UP_F2C_CANCLE_CMD_RELULT_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LINE_UP_F2C_CANCLE_CMD_RELULT_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LINE_UP;
			mType                               =   PT_LINE_UP_F2C_CANCLE_CMD_RELULT;
			mBaseDataSize                       =	PT_LINE_UP_F2C_CANCLE_CMD_RELULT_DATA_INFO::dataSize ;

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
#pragma pack (pop)

}

/******************************************************************************/

#endif