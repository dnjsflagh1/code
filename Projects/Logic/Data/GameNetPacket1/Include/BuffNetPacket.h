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
	//@������:      �쿪��
	//@Э����:      ???
	**********************************************************************/

	/******************************************************************************/
	//��Ϸ���԰�����
	/******************************************************************************/
	enum BuffNetPacketType
	{
		PT_BUFF_UNKNOW = 0,

		PT_BUFF_F2M_PLAYERCHARACTER_BUFFDATA_LIST,				//frontServer��DB���͸�MapServer
		PT_BUFF_M2F_PLAYERCHARACTER_BUFFDATA,					//MapServer����frontServer����DB
		PT_BUFF_M2C_PLAYERCHARACTER_BUFFDATA_LIST,				//MapServerͬ�������ͻ���
		PT_BUFF_M2C_PLAYERCHARACTER_BUFFDATA,					//MapServerͬ�������ͻ���
	
	};

#pragma pack (push)
#pragma pack (1)

	///���ݰ�����
	//**********************************************************************
	struct netBuffData 
	{
		Int timeUse;			//״̬��ʹ��ʱ��
		Int curAddNum;			//״̬�ĵ��Ӳ��
		Int buffId;				//״̬��Id
	};
	struct netBuffInfoData 
	{
		static const Int dataSize = sizeof (netBuffData);
	};

	//**********************************************************************
	//@����:        PT_BUFF_M2F_PLAYERCHARACTER_BUFFDATA
	//@����:        mapServer��frontServer���͸���buff����Ϣ
	//@��ע:        ֪ͨfrontServer����DB
	//**********************************************************************/
	//----------------------------------------------------------------
	struct PT_BUFF_M2F_PLAYERCHARACTER_BUFFDATA_Data
	{
		U64			acountId;		//����˺�ID
		U64			dbId;			//����µ��佫��ɫID
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
	//@����:        PT_BUFF_M2C_PLAYERCHARACTER_BUFFDATA
	//@����:        mapServer��ͻ���ͬ���¼ӵ�buff��
	//@��ע:        
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
	//@����:        PT_BUFF_F2M_PLAYERCHARACTER_BUFFDATA_LIST
	//@����:        frontServer��mapServer����buff�б�
	//@��ע:        ���ʹ�DB�ж�ȡ��buff�б�
	//**********************************************************************/
	struct PT_BUFF_F2M_PLAYERCHARACTER_BUFFDATA_LIST_Data 
	{
		U64			dbId;					//�佫��DBID
		UInt		ncount;					//buff�ĸ���
		netBuffData	buffdatalist[1];		//buff�б���Ϣ
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
	//@����:        PT_BUFF_M2C_PLAYERCHARACTER_BUFFDATA_LIST
	//@����:        mapServerr��ͻ���ͬ��buff�б�
	//@��ע:        
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