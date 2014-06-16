/******************************************************************************/
#ifndef _PLACENETPACKET_H_
#define _PLACENETPACKET_H_
/******************************************************************************/
#include "CommonGameDefine.h"
#include "NetDefine.h"
#include "GameNetPacket.h"
/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //�ݵ����ݰ��������
    /******************************************************************************/
    enum PlaceNetPacket
    {
        PT_PLACE_UNKNOW = 0,

        PT_PLACE_S2C_BASE_INFO,		        // �ݵ��������

		PT_PLACE_C2F_CLICED_INFO,			// �ͻ����������ݵ� 
		PT_PLACE_F2M_CLICED_INFO,			// FrontServerת���ͻ����������ݵ㵽MapServer
		PT_PLACE_M2C_CLICED_INFO,			// MapServer���ؾݵ����ݸ��ͻ���

    };

#pragma pack (push)
#pragma pack (1)
	//**********************************************************************
	struct PT_PLACE_S2C_BASE_INFO_DATA
	{
		Int nNum;
	};
    struct PT_PLACE_S2C_BASE_INFO_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_PLACE_S2C_BASE_INFO_DATA);
    };
	//**********************************************************************
	struct PT_PLACE_C2F_CLICED_INFO_DATA
	{
		IdType			placeId;		// �ݵ�ID
		NetVec2Data placePos;		// �ݵ�λ��
		NetVec2Data placeDir;		// �ݵ㷽��
	};
    struct PT_PLACE_C2F_CLICED_INFO_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_PLACE_C2F_CLICED_INFO_DATA);
    };
	//**********************************************************************
	struct PT_PLACE_F2M_CLICED_INFO_DATA
	{
		IdType			accountId;		// �˺�ID
		IdType			placeId;		// �ݵ�ID
		NetVec2Data placePos;		// �ݵ�λ��
		NetVec2Data placeDir;		// �ݵ㷽��

	};
    struct PT_PLACE_F2M_CLICED_INFO_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_PLACE_F2M_CLICED_INFO_DATA);
    };
	//**********************************************************************
	struct PT_PLACE_M2C_CLICED_INFO_DATA
	{
		IdType			placeId;		//�ݵ�ID
	};
    struct PT_PLACE_M2C_CLICED_INFO_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_PLACE_M2C_CLICED_INFO_DATA);
    };

#pragma pack (pop)
}

/******************************************************************************/

#endif