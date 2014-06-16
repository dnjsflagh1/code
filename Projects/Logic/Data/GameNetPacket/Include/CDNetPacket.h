/******************************************************************************/
#ifndef _CD_NETPACKET_H_
#define _CD_NETPACKET_H_
/******************************************************************************/
#include "CommonGameDefine.h"
#include "NetDefine.h"
#include "GameNetPacket.h"
/******************************************************************************/

namespace MG
{
	/**********************************************************************
	//@������:      �쿪��
	//@Э����:      ???
	**********************************************************************/

    /******************************************************************************/
    //��Ұ�����
    /******************************************************************************/
    enum CDNetPacketType
    {
        PT_CD_UNKNOWN = 0,

        PT_CD_F2C_CDLIST,											//��������CD�������½�ɫ������CD����DB�л�ã�
        PT_CD_M2C_CITY,												//���ͳ���CD

    };

    /******************************************************************************/


#pragma pack (push)
#pragma pack (1)

    //////////////////////////////////////////////////////////////////////////////

    ///���ݰ�����
    struct  CDNetData
    {
        U32 cdId;
        U32 cdLiveTime;
		U32 cdTotalTime;
    };
    struct CDNetData_INFO
    {
        static const Int dataSize = sizeof(CDNetData);
    };
    //------------------------------------------------------------------------------------------
	//**********************************************************************
	//@����:        PT_CD_F2C_CDLIST
	//@����:        frontServerr��ͻ��˷���buff�б�
	//@��ע:        ��½ʱ���ʹ�DB��ȡ��CD����
	//**********************************************************************/
    struct PT_CD_F2C_CDLIST_DATA
    {
        Byte            masterType;			//��ɫ����
        IdType          masterID;			//��ɫID��һ��ָ�佫��
        U32             cdNum;				//CD������
        CDNetData       cddata[1];			//CD��Ϣ
    };
    struct PT_CD_F2C_CDLIST_DATA_INFO
    {
        static const Int dataSize = sizeof(PT_CD_F2C_CDLIST_DATA) - CDNetData_INFO::dataSize;
    };
	
	class PT_CD_F2C_CDLIST_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_CD_F2C_CDLIST_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_CD;
			mType                               =   PT_CD_F2C_CDLIST;
			mBaseDataSize                       =   PT_CD_F2C_CDLIST_DATA_INFO::dataSize ;

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
    //------------------------------------------------------------------------------------------
    
    //////////////////////////////////////////////////////////////////////////////
#pragma pack (pop)
}

/******************************************************************************/
#endif