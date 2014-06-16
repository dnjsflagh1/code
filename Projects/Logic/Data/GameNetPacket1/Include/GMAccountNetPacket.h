/******************************************************************************/
#ifndef _GMLOGINNETPACKET_H_
#define _GMLOGINNETPACKET_H_
/******************************************************************************/

#include "CommonGameDefine.h"
#include "NetDefine.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //��Ϸ�ʺŰ�����
    /******************************************************************************/
    enum GMAccountNetPacketType
    {
		GMPT_CGMM_ACC_LOGIN,
		GMPT_GMMC_ACC_LOGIN_RESULT,

		GMPT_CGMM_ACC_CREATE,
		GMPT_GMMC_ACC_CREATE_RESULT,

		GMPT_CGMM_ACC_DELETE,
		GMPT_GMMC_ACC_DELETE_RESULT,

		GMPT_CGMM_ACC_UPDATE,
		GMPT_GMMC_ACC_UPDATE_RESULT,

		GMPT_CGMM_ACC_UPDATE_PSW,
		GMPT_CGMM_ACC_UPDATE_PSW_RESULT,

		GMPT_CGMM_ACC_SELECT,
		GMPT_GMMC_ACC_SELECT_RESULT,

    };
    
	/******************************************************************************/
	//��¼�Ŷ�����
	/******************************************************************************/
#pragma pack (push)
#pragma pack (1)
	enum gm_account_operate_result
	{
		gaor_success = 0,			//�ʺŲ����ɹ�
		gaor_lack_authority,		//Ȩ�޲���
		gaor_errname_or_errpsw,		//�ʺŻ��������
		gaor_errname,				//�û�������
		gaor_err_psw,				//�������
		gaor_err_version,			//�汾��ƥ��
		gaor_timeout,				//��ʱ
	};

	enum gm_authority
	{
		gmat_null           = 0,
		gmat_supreme        = (1<<0),

		gmat_level_1        = (1<<1),
		gmat_level_2        = (1<<2),
		gmat_level_3        = (1<<3),
		gmat_level_4        = (1<<4),
	};
	//**********************************************************************
	//GM�ʺŵ���
	struct GMPT_CGMM_ACC_LOGIN_DATA
	{
		Char16	accName[MAX_ACCOUNT_LONGIN_NAME_LEN];
		Char16	accPsw[MAX_ACCOUNT_LONGIN_PSW_LEN];
		Char8	clientVersionNum[MAX_VERSION_NUM_LEN];	
	};
	struct GMPT_CGMM_ACC_LOGIN_DATA_INFO
	{
		static const Int dataSize = sizeof (GMPT_CGMM_ACC_LOGIN_DATA);
	};
	//GM��¼����
	struct GMPT_GMMC_ACC_LOGIN_RESULT_DATA
	{
		Byte result;
		Int gmId;
		Int authority;	
	};
	struct GMPT_GMMC_ACC_LOGIN_RESULT_DATA_INFO
	{
		static const Int dataSize = sizeof (GMPT_GMMC_ACC_LOGIN_RESULT_DATA);
	};
	//**********************************************************************
	//����GM�ʺ�
	struct GMPT_CGMM_ACC_CREATE_DATA
	{
		Char16	accName[MAX_ACCOUNT_LONGIN_NAME_LEN];
		Char16	accPsw[MAX_ACCOUNT_LONGIN_PSW_LEN];
		Int	authority;
	};
	struct GMPT_CGMM_ACC_CREATE_DATA_INFO
	{
		static const Int dataSize = sizeof (GMPT_CGMM_ACC_CREATE_DATA);
	};
	//����GM�ʺŷ���
	struct GMPT_GMMC_ACC_CREATE_RESULT_DATA
	{
		Int	  gmId;
		Byte  result;
	};
	struct GMPT_GMMC_ACC_CREATE_RESULT_DATA_INFO
	{
		static const Int dataSize = sizeof (GMPT_GMMC_ACC_CREATE_RESULT_DATA);
	};
	//**********************************************************************
	//ɾ��GM�ʺ�
	struct GMPT_CGMM_ACC_DELETE_DATA
	{
		Char16	accName[MAX_ACCOUNT_LONGIN_NAME_LEN];
	};
	struct GMPT_CGMM_ACC_DELETE_DATA_INFO
	{
		static const Int dataSize = sizeof (GMPT_CGMM_ACC_DELETE_DATA);
	};
	//ɾ��GM�ʺŷ���
	struct GMPT_GMMC_ACC_DELETE_RESULT_DATA
	{
		Int	  gmId;
		Byte  result;
	};
	struct GMPT_GMMC_ACC_DELETE_RESULT_DATA_INFO
	{
		static const Int dataSize = sizeof (GMPT_GMMC_ACC_DELETE_RESULT_DATA);
	};
	//**********************************************************************
	//�޸�GM
	struct GMPT_CGMM_ACC_UPDATE_DATA
	{
		Char16	accName[MAX_ACCOUNT_LONGIN_NAME_LEN];
		Char16	newAccPsw[MAX_ACCOUNT_LONGIN_PSW_LEN];
		Int		gmId;
		Int		authority;
	};
	struct GMPT_CGMM_ACC_UPDATE_DATA_INFO
	{
		static const Int dataSize = sizeof (GMPT_CGMM_ACC_UPDATE_DATA);
	};
	//�޸�GM����
	struct GMPT_GMMC_ACC_UPDATE_RESULT_DATA
	{
		Int	  gmId;
		Byte  result;
	};
	struct GMPT_GMMC_ACC_UPDATE_RESULT_DATA_INFO
	{
		static const Int dataSize = sizeof (GMPT_GMMC_ACC_UPDATE_RESULT_DATA);
	};
	//**********************************************************************
	//��ѯGM�˺�
	struct NetGMPlayer
	{
		Char16	accName[MAX_ACCOUNT_LONGIN_NAME_LEN];
		Char16	accPsw[MAX_ACCOUNT_LONGIN_PSW_LEN];
		I32		netId;
		Int		authority;
		Byte	online;
		Int		gmId;
	};
	struct GMPT_CGMM_ACC_SELECT_DATA
	{
	};
	struct GMPT_CGMM_ACC_SELECT_DATA_INFO
	{
		static const Int dataSize = sizeof (GMPT_CGMM_ACC_UPDATE_DATA);
	};
	//��ѯGM�˺ŷ���
	struct GMPT_GMMC_ACC_SELECT_RESULT_DATA
	{
		Int			count;
		NetGMPlayer	GMPlayerGroup[1];
	};
	struct GMPT_GMMC_ACC_SELECT_RESULT_DATA_INFO
	{
		static const Int GMPlayerSize = sizeof(NetGMPlayer);
		static const Int headSize = sizeof (GMPT_GMMC_ACC_SELECT_RESULT_DATA) - GMPlayerSize;
		static const Int dataSize(GMPT_GMMC_ACC_SELECT_RESULT_DATA* data)
		{
			return headSize + data->count * GMPlayerSize;
		}
	};


#pragma pack (pop)

}

/******************************************************************************/

#endif