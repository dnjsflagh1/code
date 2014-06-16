/******************************************************************************/
#ifndef _LOGINNETPACKET_H_
#define _LOGINNETPACKET_H_
/******************************************************************************/

#include "CommonGameDefine.h"
#include "NetDefine.h"

/******************************************************************************/

namespace MG
{
	/**********************************************************************
	//@������:      ������
	//@Э����:      ???
	**********************************************************************/

    /******************************************************************************/
    //��Ϸ�ʺŰ�����
    /******************************************************************************/
    enum LoginNetPacketType
    {
		PT_LOGIN_UNKNOW = 0,
		PT_LOGIN_S2S_SERVER_LOGIN,					//������֮��ĵ�������
		
		//  ��Э���Ѿ���������ȷ�ϣ���ʱע�ͣ�
		//PT_F2M_MAPLIST,								

		PT_LOGIN_F2L_FRONT_SERVER_LOGIN,			//FrontServer ���� LoginServer
		PT_LOGIN_L2F_LOGIN_FRONT_SERVER_RESULT,		//FrontServer ���� LoginServer ���ؽ��
        PT_LOGIN_L2F_LOGIN_FRONT_KICKOUT_CLIENT,    //�ظ���¼ LoginServer֪ͨFrontServer �߳����

        PT_LOGIN_C2L_ACC_LOGIN,						//�ͻ����˺ŵ�½LoginServer		
		PT_LOGIN_L2C_ACC_LOGIN_FAIL,				//�ͻ����˺ŵ���ʧ����Ϣ

		PT_LOGIN_L2C_ACC_LOGIN_SUCCESS,				//�ͻ����˺ŵ���ɹ���Ϣ

		PT_LOGIN_C2F_ACC_LOGIN,						//�ͻ����˺ŵ���FrontServer
        PT_LOGIN_C2F_ACC_LOGOUT,					//�ͻ����˺ŵ���FrontServer
		PT_LOGIN_F2C_ACC_LOGIN_RESULT,				//�ͻ����˺ŵ���FrontServer���ؽ��

		PT_LOGIN_F2L_CLIENT_LOGIN,					//�ͻ����˺ŵ���֪ͨ����֤
		PT_LOGIN_L2F_CLIENT_CHECKED,				//�ͻ����˺ŵ�����֤���
		PT_LOGIN_F2L_CLIENT_LOGOUT,					//�ͻ����˺ŵǳ�

		//���崴������
        PT_LOGIN_F2C_OPEN_CREATECLANUI,				//[FrontServer -> Client] ֪ͨ�ͻ��˴򿪴�������Ľ���
		PT_LOGIN_C2F_CREATE_CLAN,					//[Client -> FrontServer] ����������������塣
		PT_LOGIN_F2C_CREATE_CLAN_RESULT,			//[FrontServer -> Client] ���ط�������������Ľ��
		PT_LOGIN_F2C_CLAN_DATA,						//[FrontServer -> Client] ������������

		//��ɫ��������
		PT_LOGIN_F2C_OPENCRETEGENREALUI,			//[FrontServer -> Client] ������������أ�����ɹ����ǽ�����Ϸ��
		PT_LOGIN_C2F_CREATE_GENERAL,				//[Client -> FrontServer] �ͻ������󴴽��佫��
		PT_LOGIN_F2C_CREATE_GENERAL_RESULT,			//[FrontServer -> Client] �ͻ��˷��ش����佫�����

		//����������
		PT_LOGIN_F2C_OPEN_CLANCONTROLUI,			//[FrontServer -> Client] ֪ͨ�ͻ��˴�����������
		PT_LOGIN_C2F_DELETE_CLAN,					//[Client -> FrontServer] ���������ɾ�����塣
		PT_LOGIN_F2C_DELETE_CLAN_RESULT,			//[FrontServer -> Client] ���ط�����ɾ������Ľ��
        PT_LOGIN_C2F_JOINGAME,						//[Client -> FrontServer] �ͻ��������¼game

		PT_LOGIN_F2A_JOINGAME,						//[FrontServer -> ChatServer]ǰ̨������֪ͨ����������ͻ��˽�����Ϸ
		PT_LOGIN_F2A_EXITGAME,						//[FrontServer -> ChatServer]ǰ̨������֪ͨ����������ͻ����뿪��Ϸ
		PT_LOGIN_F2A_CLIENTLIST_INGAME,				//[FrontServer -> ChatServer]ǰ̨�����¼���������ʱ����Ϸ�еĿͻ��˶���

		// ��׳�Լ��
		PT_LOGIN_L2F_CHECK_INFRONTSERVER,
		PT_LOGIN_F2L_CHECK_INFRONTSERVER_RESULT,
		PT_LOGIN_M2F_CHECK_INFRONTSERVER,
		PT_LOGIN_F2M_CHECK_INFRONTSERVER_RESULT,

		// �������汾��������Ϣ����
		PT_SERVER_S2S_LOGIN_VERSION_ERROR,
		// �ͻ��˰汾��������Ϣ����
		PT_SERVER_S2C_LOGIN_VERSION_ERROR

    };
    
	/******************************************************************************/
	//��¼�Ŷ�����
	/******************************************************************************/
#pragma pack (push)
#pragma pack (1)

    //**********************************************************************
    //������֮�����
	//**********************************************************************
	//@����:        PT_LOGIN_S2S_SERVER_LOGIN
	//@����:        ������֮��ĵ�¼
	//@��ע:        ???
	//**********************************************************************/
    struct PT_LOGIN_S2S_LOGIN_DATA
    {
        U8		serverType;
        U32		code; 
		U32		serverId;
		U64		serverUniqueFlag;
		Char8	serverVersion[MAX_VERSION_NUM_LEN];
		Char16	name[MAX_SERVER_NAME_LEN];
    };

    struct PT_LOGIN_S2S_LOGIN_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_S2S_LOGIN_DATA);
    };
	class PT_LOGIN_S2S_LOGIN_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_S2S_LOGIN_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_S2S_SERVER_LOGIN;
			mBaseDataSize                       =   PT_LOGIN_S2S_LOGIN_DATA_INFO::dataSize;

			mLevel                              =   GPL_SYS;
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
	//**********************************************************************
	//  ��Э���Ѿ���������ȷ�ϣ���ʱע�ͣ�
	/*struct NetMapServer
	{
		Char	ip[MG_NET_MAX_IP_LEN];
		I32		port;
	};
	struct PT_F2M_MAPLIST_DATA
	{
		Int				num;
		NetMapServer	mapInfo[1];
	};
    struct PT_F2M_MAPLIST_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_F2M_MAPLIST_DATA);
    };*/
	//**********************************************************************
    //�ͻ����ʺŵ���
	//**********************************************************************
	//@����:        PT_LOGIN_C2L_ACC_LOGIN
	//@����:        Client��¼LoginServer
	//@��ע:        �ͻ����ʺŵ���
	//**********************************************************************/
    struct  PT_LOGIN_C2L_LOGIN_DATA
    {
		Char16	accName[MAX_ACCOUNT_LONGIN_NAME_LEN];
		Char16	accPsw[MAX_ACCOUNT_LONGIN_PSW_LEN];
		Char8	clientVersionNum[MAX_VERSION_NUM_LEN];	
    };
    struct PT_LOGIN_C2L_LOGIN_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_C2L_LOGIN_DATA);
    };
	class PT_LOGIN_C2L_LOGIN_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_C2L_LOGIN_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_C2L_ACC_LOGIN;
			mBaseDataSize                       =   PT_LOGIN_C2L_LOGIN_DATA_INFO::dataSize;

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
	//Loginserver����FrontServer��Ϣ���ͻ���
	//**********************************************************************
	//@����:        PT_LOGIN_L2C_ACC_LOGIN_SUCCESS
	//@����:        LoginServer���ظ��ͻ��˵�¼�ɹ����
	//@��ע:        ???
	//**********************************************************************/
	struct  PT_LOGIN_L2C_LOGIN_SUCCESS_DATA
	{
		Char	ip[MG_NET_MAX_IP_LEN];
		I32		port;
	};
    struct PT_LOGIN_L2C_LOGIN_SUCCESS_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_L2C_LOGIN_SUCCESS_DATA);
    };
	class PT_LOGIN_L2C_LOGIN_SUCCESS_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_L2C_LOGIN_SUCCESS_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_L2C_ACC_LOGIN_SUCCESS;
			mBaseDataSize                       =   PT_LOGIN_L2C_LOGIN_SUCCESS_DATA_INFO::dataSize;

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
	//@����:        PT_LOGIN_F2L_FRONT_SERVER_LOGIN
	//@����:        FrontServer��½LoginServer��Ϣ
	//@��ע:        ???
	//**********************************************************************/
	struct PT_LOGIN_F2L_LOGIN_DATA 
	{
		Char	ip[MG_NET_MAX_IP_LEN];
		I32		port;
	};
    struct PT_LOGIN_F2L_LOGIN_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_F2L_LOGIN_DATA);
    };
	class PT_LOGIN_F2L_LOGIN_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_F2L_LOGIN_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_F2L_FRONT_SERVER_LOGIN;
			mBaseDataSize                       =   PT_LOGIN_F2L_LOGIN_DATA_INFO::dataSize;

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
	//**********************************************************************
	//Clinet��½FrontServer��Ϣ
	//**********************************************************************
	//@����:        PT_LOGIN_C2F_ACC_LOGIN
	//@����:        Client��¼FrontServer
	//@��ע:        ???
	//**********************************************************************/
	struct PT_LOGIN_C2F_LOGIN_DATA
	{
		PT_LOGIN_C2L_LOGIN_DATA data;
	};
    struct PT_LOGIN_C2F_LOGIN_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_C2F_LOGIN_DATA);
    };
	class PT_LOGIN_C2F_LOGIN_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_C2F_LOGIN_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_C2F_ACC_LOGIN;
			mBaseDataSize                       =   PT_LOGIN_C2F_LOGIN_DATA_INFO::dataSize;

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
	//@����:        PT_LOGIN_F2C_ACC_LOGIN_RESULT
	//@����:        FrontServer���ص�¼���Cleint
	//@��ע:        ???
	//**********************************************************************/
	//Client��½FrontServer���
	enum PT_LOGIN_F2C_LOGIN_RESULT_TYPE 
	{
		LCFT_LOGIN_UNKNOW,
		LCFT_LOGIN_SUCCESS,			
		LCFT_LOGIN_FAIL,	
	};
	struct PT_LOGIN_F2C_LOGIN_RESULT_DATA
	{
		I8						result;
		PlayerIdType			accountId;
	};
    struct PT_LOGIN_F2C_LOGIN_RESULT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_F2C_LOGIN_RESULT_DATA);
    };
	class PT_LOGIN_F2C_LOGIN_RESULT_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_F2C_LOGIN_RESULT_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_F2C_ACC_LOGIN_RESULT;
			mBaseDataSize                       =   PT_LOGIN_F2C_LOGIN_RESULT_DATA_INFO::dataSize;

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
	//@����:        PT_LOGIN_F2L_CLIENT_LOGIN
	//@����:		FrontServer���͸�LoginServer�Ŀͻ���У����Ϣ
	//@��ע:        ???
	//**********************************************************************/
	struct	PT_LOGIN_F2L_CLIENT_LOGIN_DATA
	{
		I32 clientNetIdInFrontServer;
		PT_LOGIN_C2L_LOGIN_DATA data;
	};
    struct PT_LOGIN_F2L_CLIENT_LOGIN_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_F2L_CLIENT_LOGIN_DATA);
    };
	class PT_LOGIN_F2L_CLIENT_LOGIN_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_F2L_CLIENT_LOGIN_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_F2L_CLIENT_LOGIN;
			mBaseDataSize                       =   PT_LOGIN_F2L_CLIENT_LOGIN_DATA_INFO::dataSize;

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
	//**********************************************************************
	//@����:        PT_LOGIN_F2L_CLIENT_LOGOUT
	//@����:		FrontServer���͸�LoginServer�Ŀͻ��˵ǳ���Ϣ
	//@��ע:        ???
	//**********************************************************************/
	struct	PT_LOGIN_F2L_CLIENT_LOGOUT_DATA
	{
		Char16	accName[MAX_ACCOUNT_LONGIN_NAME_LEN];
	};
    struct PT_LOGIN_F2L_CLIENT_LOGOUT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_F2L_CLIENT_LOGOUT_DATA);
    };
	class PT_LOGIN_F2L_CLIENT_LOGOUT_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_F2L_CLIENT_LOGOUT_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_F2L_CLIENT_LOGOUT;
			mBaseDataSize                       =   PT_LOGIN_F2L_CLIENT_LOGOUT_DATA_INFO::dataSize;

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
	//**********************************************************************
	//@����:        PT_LOGIN_L2C_ACC_LOGIN_FAIL
	//@����:		LoginServer���͸�Client�Ŀͻ��˵�¼ʧ����Ϣ
	//@��ע:        ???
	//**********************************************************************/
	//��½ʧ�ܽ��
	enum PT_LOGIN_L2C_LOGIN_FAIL_TYPE 
	{
		LFFT_LOGIN_UNKNOW,
		LCFT_LOGIN_REDUPLICATE,			//�ظ�����
		LCFT_LOGIN_NONE_FRONTSERVER,	//û�е��������
		LCFT_LOGIN_IDENTITY_ERROR,		//�˺Ż��������
		LCFT_LOGIN_IDENTITY_ERROR_MAX,	//�˺Ż�����������̫��
		LCFT_LOGIN_LOCK,				//�˺ű�����
	};
	struct PT_LOGIN_L2C_LOGIN_FAIL_DATA
	{
		I8 errResult;
	};
    struct PT_LOGIN_L2C_LOGIN_FAIL_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_L2C_LOGIN_FAIL_DATA);
    };
	class PT_LOGIN_L2C_LOGIN_FAIL_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_L2C_LOGIN_FAIL_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_L2C_ACC_LOGIN_FAIL;
			mBaseDataSize                       =   PT_LOGIN_L2C_LOGIN_FAIL_DATA_INFO::dataSize;

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
	//@����:        PT_LOGIN_L2F_LOGIN_FRONT_SERVER_RESULT
	//@����:		FrontServer��½LoginServer���
	//@��ע:        ???
	//**********************************************************************/
	
	enum PT_LOGIN_L2F_LOGIN_RESULT_TYPE 
	{
		LFRT_LOGIN_UNKNOW,
		LFRT_LOGIN_SUCCESS,			
		LFRT_LOGIN_FAIL,	
	};
	struct PT_LOGIN_L2F_LOGIN_RESULT_DATA
	{
		I8 result;
	};
    struct PT_LOGIN_L2F_LOGIN_RESULT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_L2F_LOGIN_RESULT_DATA);
    };
	class PT_LOGIN_L2F_LOGIN_RESULT_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_L2F_LOGIN_RESULT_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_L2F_LOGIN_FRONT_SERVER_RESULT;
			mBaseDataSize                       =   PT_LOGIN_L2F_LOGIN_RESULT_DATA_INFO::dataSize;

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
	//**********************************************************************
	//@����:        PT_LOGIN_L2F_CLIENT_CHECKED
	//@����:		LoginServer���ظ�FrontServer�ͻ��˵�¼У����
	//@��ע:        ???
	//**********************************************************************/
	
	enum PT_LOGIN_L2F_CLIENT_CHECKED_TYPE 
	{
		LFCT_LOGIN_UNKNOW,
		LFCT_LOGIN_SUCCESS,			
		LFCT_LOGIN_FAIL,	
	};
	struct PT_LOGIN_L2F_CLIENT_CHECKED_DATA
	{
		I8		result;
		I32		clientNetID;
		PT_LOGIN_C2L_LOGIN_DATA data;
		U64	accID;
	};
    struct PT_LOGIN_L2F_CLIENT_CHECKED_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_L2F_CLIENT_CHECKED_DATA);
    };
	class PT_LOGIN_L2F_CLIENT_CHECKED_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_L2F_CLIENT_CHECKED_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_L2F_CLIENT_CHECKED;
			mBaseDataSize                       =   PT_LOGIN_L2F_CLIENT_CHECKED_DATA_INFO::dataSize;

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
	//**********************************************************************
	//@����:        PT_LOGIN_F2C_CLAN_DATA
	//@����:		FrontServer���ؼ����б���ͻ���
	//@��ע:        ???
	//**********************************************************************/
    //**********************************************************************
    struct PT_LOGIN_F2C_CLAN_DATA_DATA
    {
		PlayerIdType			accountId;
        ClanIdType				clandatabaseid;				//����ID
		PlayerCharacterIdType	mainGenrealId;				//���佫
		PlayerCharacterIdType	wiseGenrealId;				//��ʦ
		PlayerCharacterIdType	commanderGenrealId;			//ͳ��
		PlayerCharacterIdType	curGenrealId;				//��ǰʹ�õ��佫
		RegionIdType			regionID;                  //������������
		UInt					clanLevel;
		UInt					clanExp[4];
		UInt					clanMoney[16];
		U32						clanbagsize;               //���屳��  
		U32						ConstellationId;			//�����ػ�����ID
        U8						armyemblem;                //���
        U8						armyemblemcolor;           //�����ɫ
        U8						bg;                        //����ͼ��
        U8						bgcolor;                   //������ɫ
		U8						status;                     //״̬  
		Char16					clanhomelandname[MAX_CHARACTER_NAME_LEN];	//������
		Char16					clanname[MAX_CHARACTER_NAME_LEN];			//������
    };
    struct PT_LOGIN_F2C_CLAN_DATA_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_F2C_CLAN_DATA_DATA);
    };
	class PT_LOGIN_F2C_DATA_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_F2C_DATA_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_F2C_CLAN_DATA;
			mBaseDataSize                       =   PT_LOGIN_F2C_CLAN_DATA_DATA_INFO::dataSize;

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
			if ( dataLen != PT_LOGIN_F2C_CLAN_DATA_DATA_INFO::dataSize )
				return false;
			return true;
		}
	};
    //**********************************************************************
	//@����:        PT_LOGIN_C2F_CREATE_CLAN
	//@����:		Client���ʹ���������Ϣ��FrontServer
	//@��ע:        ???
	//**********************************************************************/
    struct PT_LOGIN_C2F_CREATE_CLAN_DATA
    {
		PlayerIdType			accountid;                  //���ID
		U32						ConstellationId;			//�����ػ�����ID
		U8						armyemblem;                //���
		U8						armyemblemcolor;           //�����ɫ
		U8						bg;                        //����ͼ��
		U8						bgcolor;                   //������ɫ
		Char16					clanhomelandname[MAX_CHARACTER_NAME_LEN];	//������
		Char16					clanname[MAX_CHARACTER_NAME_LEN];			//������
    };
    struct PT_LOGIN_C2F_CREATE_CLAN_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_C2F_CREATE_CLAN_DATA);
    };
	class PT_LOGIN_C2F_CREATE_CLAN_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_C2F_CREATE_CLAN_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_C2F_CREATE_CLAN;
			mBaseDataSize                       =   PT_LOGIN_C2F_CREATE_CLAN_DATA_INFO::dataSize;

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
	//@����:        PT_LOGIN_F2C_CREATE_CLAN_RESULT
	//@����:		FrontServer���ش�����������Client
	//@��ע:        ???
	//**********************************************************************/
    enum CreateClanResult
    {
        CreateClanResult_Succeed = 0,
        CreateClanResult_NameExistOrUnlaw,
        CreateClanResult_CreateMemory_Error,   //�����ڴ�ʧ��
        CreateClanResult_DB_Error,            //���ݿ����ʧ��
        CreateClanResult_OtherError,
		CreateClanResult_NoPlayer,				//û��Player ��Ϣ
        CreateClanResult_Max
    };
    struct PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA
    {
         CreateClanResult		result;
		 ClanIdType				clanId;
		 RegionIdType			regionID;                  //������������
		 U32					clanbagsize;               //���屳��
    };
    struct PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA);
    };
	class PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_F2C_CREATE_CLAN_RESULT;
			mBaseDataSize                       =   PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA_INFO::dataSize;

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
	//@����:        PT_LOGIN_C2F_DELETE_CLAN
	//@����:		Client����ɾ�������FrontServer
	//@��ע:        ???
	//**********************************************************************/
    struct PT_LOGIN_C2F_DELETE_CLAN_DATA
    {
		PlayerIdType	accountId;
        ClanIdType		clandatabaseid;            //����ID
    };
    struct PT_LOGIN_C2F_DELETE_CLAN_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_C2F_DELETE_CLAN_DATA);
    };
	class PT_LOGIN_C2F_DELETE_CLAN_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_C2F_DELETE_CLAN_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_C2F_DELETE_CLAN;
			mBaseDataSize                       =   PT_LOGIN_C2F_DELETE_CLAN_DATA_INFO::dataSize;

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
	//@����:        PT_LOGIN_F2C_DELETE_CLAN_RESULT
	//@����:		FrontServer����ɾ����������Client
	//@��ע:        ???
	//**********************************************************************/
    enum DeleteClanResult
    {
        DeleteClanResult_Succeed = 0,
        DeleteClanResult_PswdError,
        DeleteClanResult_ClanUnexist,
        DeleteClanResult_ClanOndelete,
        DeleteClanResult_OtherError,

        DeleteClanResult_Max
    };
    struct PT_LOGIN_F2C_DELETE_CLAN_RESULT_DATA
    {
         DeleteClanResult result;
    };
    struct PT_LOGIN_F2C_DELETE_CLAN_RESULT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_F2C_DELETE_CLAN_RESULT_DATA);
    };
	class PT_LOGIN_F2C_DELETE_CLAN_RESULT_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_F2C_DELETE_CLAN_RESULT_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_F2C_DELETE_CLAN_RESULT;
			mBaseDataSize                       =   PT_LOGIN_F2C_DELETE_CLAN_RESULT_DATA_INFO::dataSize;

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
	//@����:        PT_LOGIN_F2A_JOINGAME
	//@����:		FrontServer���Ϳͻ��˽�����Ϸ��ChatServer
	//@��ע:        ???
	//**********************************************************************/
	struct PT_LOGIN_F2A_JOINGAME_DATA
	{
		Char16	clanName[MAX_CLAN_NAME];
		I32		clientNetId;
		U64		accountId;
	};
	struct PT_LOGIN_F2A_JOINGAME_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LOGIN_F2A_JOINGAME_DATA);
	};
	class PT_LOGIN_F2A_JOINGAME_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_F2A_JOINGAME_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_F2A_JOINGAME;
			mBaseDataSize                       =   PT_LOGIN_F2A_JOINGAME_DATA_INFO::dataSize;

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
	//**********************************************************************
	//@����:        PT_LOGIN_F2A_CLIENTLIST
	//@����:		FrontServer�������߿ͻ����б��ChatServer
	//@��ע:        ???
	//**********************************************************************/
	struct PT_LOGIN_F2A_CLIENTLIST_INGAME_DATA
	{
		U16 count;
		PT_LOGIN_F2A_JOINGAME_DATA data[1];
	};
	struct PT_LOGIN_F2A_CLIENTLIST_INGAME_DATA_INFO
	{
		static const Int elmentSize = sizeof (PT_LOGIN_F2A_JOINGAME_DATA);
		static const Int headSize   = sizeof (PT_LOGIN_F2A_CLIENTLIST_INGAME_DATA) - sizeof(PT_LOGIN_F2A_JOINGAME_DATA);
		static const Int dataSize(PT_LOGIN_F2A_CLIENTLIST_INGAME_DATA* data)
		{
			return headSize + data->count * elmentSize;
		}
	};
	class PT_LOGIN_F2A_CLIENTLIST_INGAME_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_F2A_CLIENTLIST_INGAME_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_F2A_CLIENTLIST_INGAME;
			//mBaseDataSize                       =   PT_LOGIN_F2A_CLIENTLIST_INGAME_DATA_INFO::dataSize;

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
		virtual Bool checkDataValid( GameNetPacketData* data, I32 dataLen )
		{
			if ( data->channel != mChannel )
				return false;
			if ( data->type != mType )
				return false;
			if ( dataLen != PT_LOGIN_F2A_CLIENTLIST_INGAME_DATA_INFO::dataSize((PT_LOGIN_F2A_CLIENTLIST_INGAME_DATA*)data) )
				return false;
			return true;
		}
	};
	//**********************************************************************
	//@����:        PT_LOGIN_F2A_EXITGAME
	//@����:		FrontServer�����ڿͻ���������Ϣ��ChatServer
	//@��ע:        ???
	//**********************************************************************/
	struct PT_LOGIN_F2A_EXITGAME_DATA
	{
		Char16	clanName[MAX_CLAN_NAME];
	};
	struct PT_LOGIN_F2A_EXITGAME_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LOGIN_F2A_EXITGAME_DATA);
	};
	class PT_LOGIN_F2A_EXITGAME_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_F2A_EXITGAME_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_F2A_EXITGAME;
			mBaseDataSize                       =   PT_LOGIN_F2A_EXITGAME_DATA_INFO::dataSize;

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
    //**********************************************************************
	//@����:        PT_LOGIN_C2F_CREATE_GENERAL
	//@����:		Client������ɫ������Ϣ��FrontServer
	//@��ע:        ???
	//**********************************************************************/
    struct PT_LOGIN_C2F_CREATE_GENERAL_DATA
    {
        Char16			name[MAX_CHARACTER_NAME_LEN];
        Char16			charSurName[MAX_CHARACTER_NAME_LEN];
        U32             charArtIcon;
		U32             resID;
		PlayerIdType	accountId;
    };
    struct PT_LOGIN_C2F_CREATE_GENERAL_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_C2F_CREATE_GENERAL_DATA);
    };
	class PT_LOGIN_C2F_CREATE_GENERAL_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_C2F_CREATE_GENERAL_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_C2F_CREATE_GENERAL;
			mBaseDataSize                       =   PT_LOGIN_C2F_CREATE_GENERAL_DATA_INFO::dataSize;

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
	//@����:        PT_LOGIN_F2C_CREATE_GENERAL_RESULT
	//@����:		FrontServer�����ڿͻ���������Ϣ��ChatServer
	//@��ע:        ???
	//**********************************************************************/
    enum CreateGenrealResult
    {
        CreateGenrealResult_Succeed = 0,
        CreateGenrealResult_Error_NotPlayer,
		CreateGenrealResult_Error_NotClan,
		CreateGenrealResult_Error_Memory,
		CreateGenrealResult_Error_DB,
		CreateGenrealResult_Error_Name,

        CreateGenrealResult_Max
    };
    struct PT_LOGIN_F2C_CREATE_GENERAL_RESULT_DATA
    {
        CreateGenrealResult					result;
        PlayerCharacterIdType				genrealID;
		ClanIdType							clanId;
		RegionIdType						regionId;
		U32									regionType;
		U32									charTempId;
    };
    struct PT_LOGIN_F2C_CREATE_GENERAL_RESULT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_F2C_CREATE_GENERAL_RESULT_DATA);
    };
	class PT_LOGIN_F2C_CREATE_GENERAL_RESULT_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_F2C_CREATE_GENERAL_RESULT_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_F2C_CREATE_GENERAL_RESULT;
			mBaseDataSize                       =   PT_LOGIN_F2C_CREATE_GENERAL_RESULT_DATA_INFO::dataSize;

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
	//--------------------------------------------------------------------
	//**********************************************************************
	//@����:        PT_LOGIN_C2F_JOINGAME
	//@����:		client���ͽ�����Ϸ��Ϣ��FrontServer
	//@��ע:        ???
	//**********************************************************************/
	struct  PT_LOGIN_C2F_JOINGAME_DATA
	{
		PlayerIdType	accountId;
	};
	//-----------------------------------------------------------------------------
	struct  PT_LOGIN_C2F_JOINGAME_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LOGIN_C2F_JOINGAME_DATA);
	};
	//-----------------------------------------------------------------------------
	class PT_LOGIN_C2F_JOINGAME_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_C2F_JOINGAME_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_C2F_JOINGAME;
			mBaseDataSize                       =   PT_LOGIN_C2F_JOINGAME_DATA_INFO::dataSize;

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
	//--------------------------------------------------------------------
	enum LOGIN_INFRONTSERVER_CHECK_RESULT
	{
		Login_Infrontserver_Check_Result_Fail = 0,
		Login_Infrontserver_Check_Result_Success = 1
		
	};
	//--------------------------------------------------------------------
	//**********************************************************************
	//@����:        PT_LOGIN_L2F_CHECK_INFRONTSERVER
	//@����:		LoginServer���ͼ��ͻ����Ƿ�����Ϸ����Ϣ��FrontServer
	//@��ע:        ???
	//**********************************************************************/
	struct PT_LOGIN_L2F_CHECK_INFRONTSERVER_DATA
	{
		I32 clientNetIdInFrontServer;
		I32 clientNetIdInLoginServer;
	};
	struct PT_LOGIN_L2F_CHECK_INFRONTSERVER_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LOGIN_L2F_CHECK_INFRONTSERVER_DATA);
	};
	class PT_LOGIN_L2F_CHECK_INFRONTSERVER_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_L2F_CHECK_INFRONTSERVER_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_L2F_CHECK_INFRONTSERVER;
			mBaseDataSize                       =   PT_LOGIN_L2F_CHECK_INFRONTSERVER_DATA_INFO::dataSize;

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
	//**********************************************************************
	//@����:        PT_LOGIN_F2L_CHECK_INFRONTSERVER_RESULT
	//@����:		FrontServer���ؼ��ͻ����Ƿ�����Ϸ�еĽ����LoginServer
	//@��ע:        ???
	//**********************************************************************/
	struct PT_LOGIN_F2L_CHECK_INFRONTSERVER_RESULT_DATA
	{
		//Char16	accountName[MAX_ACCOUNT_LONGIN_NAME_LEN];
		I32		clientNetIdInLoginServer;
		Byte	result;
	};
	struct PT_LOGIN_F2L_CHECK_INFRONTSERVER_RESULT_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LOGIN_F2L_CHECK_INFRONTSERVER_RESULT_DATA);
	};
	class PT_LOGIN_F2L_CHECK_INFRONTSERVER_RESULT_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_F2L_CHECK_INFRONTSERVER_RESULT_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_F2L_CHECK_INFRONTSERVER_RESULT;
			mBaseDataSize                       =   PT_LOGIN_F2L_CHECK_INFRONTSERVER_RESULT_DATA_INFO::dataSize;

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
	//**********************************************************************
	//@����:        PT_LOGIN_M2F_CHECK_INFRONTSERVER
	//@����:		MapServer���ͼ��ͻ����Ƿ�����Ϸ����Ϣ��FrontServer
	//@��ע:        ???
	//**********************************************************************/
	struct PT_LOGIN_M2F_CHECK_INFRONTSERVER_DATA
	{
		I32 clientNetIdInFrontServer;
	};
	struct PT_LOGIN_M2F_CHECK_INFRONTSERVER_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LOGIN_M2F_CHECK_INFRONTSERVER_DATA);
	};
	class PT_LOGIN_M2F_CHECK_INFRONTSERVER_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_M2F_CHECK_INFRONTSERVER_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_M2F_CHECK_INFRONTSERVER;
			mBaseDataSize                       =   PT_LOGIN_M2F_CHECK_INFRONTSERVER_DATA_INFO::dataSize;

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
	//**********************************************************************
	//@����:        PT_LOGIN_F2M_CHECK_INFRONTSERVER_RESULT
	//@����:		FrontServer���ؼ��ͻ����Ƿ�����Ϸ�еĽ����MapServer
	//@��ע:        ???
	//**********************************************************************/
	struct PT_LOGIN_F2M_CHECK_INFRONTSERVER_RESULT_DATA
	{
		I32		clientNetIdInFrontServer;
		Byte	result;
	};
	struct PT_LOGIN_F2M_CHECK_INFRONTSERVER_RESULT_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LOGIN_F2M_CHECK_INFRONTSERVER_RESULT_DATA);
	};
	class PT_LOGIN_F2M_CHECK_INFRONTSERVER_RESULT_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_LOGIN_F2M_CHECK_INFRONTSERVER_RESULT_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_LOGIN_F2M_CHECK_INFRONTSERVER_RESULT;
			mBaseDataSize                       =   PT_LOGIN_F2M_CHECK_INFRONTSERVER_RESULT_DATA_INFO::dataSize;

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
	//**********************************************************************
	//@����:        PT_SERVER_S2S_LOGIN_VERSION_ERROR
	//@����:		������֮�䷵�ص�¼�������汾��Ϣ
	//@��ע:        ???
	//**********************************************************************/
	struct PT_SERVER_S2S_LOGIN_VERSION_ERROR_DATA
	{
		Char16	serverName[MAX_SERVER_NAME_LEN];
		Byte	serverType;
		I32		dataSize;
		Char8	errorInfo[1];
	};
	struct PT_SERVER_S2S_LOGIN_VERSION_ERROR_DATA_INFO
	{
		static const Int headSize = sizeof (PT_SERVER_S2S_LOGIN_VERSION_ERROR_DATA) - sizeof(Char8);
		static Int dataSize(PT_SERVER_S2S_LOGIN_VERSION_ERROR_DATA* data)
		{
			return headSize + data->dataSize;
		}
	};
	class PT_SERVER_S2S_LOGIN_VERSION_ERROR_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_SERVER_S2S_LOGIN_VERSION_ERROR_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_SERVER_S2S_LOGIN_VERSION_ERROR;
			//mBaseDataSize                       =   PT_SERVER_S2S_LOGIN_VERSION_ERROR_DATA_INFO::dataSize;

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
		virtual Bool checkDataValid( GameNetPacketData* data, I32 dataLen )
		{
			if ( data->channel != mChannel )
				return false;
			if ( data->type != mType )
				return false;
			if ( dataLen != PT_SERVER_S2S_LOGIN_VERSION_ERROR_DATA_INFO::dataSize((PT_SERVER_S2S_LOGIN_VERSION_ERROR_DATA*)data) )
				return false;
			return true;
		}
	};
	//**********************************************************************
	//@����:        PT_SERVER_S2C_LOGIN_VERSION_ERROR
	//@����:		���������ص�¼�������汾��Ϣ���ͻ���
	//@��ע:        ???
	//**********************************************************************/
	struct PT_SERVER_S2C_LOGIN_VERSION_ERROR_DATA
	{
		I32		dataSize;
		Char8	errorInfo[1];
	};
	struct PT_SERVER_S2C_LOGIN_VERSION_ERROR_DATA_INFO
	{
		static const Int headSize = sizeof (PT_SERVER_S2C_LOGIN_VERSION_ERROR_DATA) - sizeof(Char8);
		static Int dataSize(PT_SERVER_S2C_LOGIN_VERSION_ERROR_DATA* data)
		{
			return headSize + data->dataSize;
		}
	};
	class PT_SERVER_S2C_LOGIN_VERSION_ERROR_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{
	public:
		PT_SERVER_S2C_LOGIN_VERSION_ERROR_DATA_DESCRIBE()
			:GameNetPacketDataDescribe()
		{
			mChannel                            =   GNPC_LOGIN;
			mType                               =   PT_SERVER_S2C_LOGIN_VERSION_ERROR;
			//mBaseDataSize                       =   PT_SERVER_S2C_LOGIN_VERSION_ERROR_DATA_INFO::dataSize;

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
		virtual Bool checkDataValid( GameNetPacketData* data, I32 dataLen )
		{
			if ( data->channel != mChannel )
				return false;
			if ( data->type != mType )
				return false;
			if ( dataLen != PT_SERVER_S2C_LOGIN_VERSION_ERROR_DATA_INFO::dataSize((PT_SERVER_S2C_LOGIN_VERSION_ERROR_DATA*)data) )
				return false;
			return true;
		}
	};
	//**********************************************************************
	//@����:		Loginserver֪ͨFrontServer�ظ���¼���
	//@��ע:        ???
	//**********************************************************************/
	/*struct PT_LOGIN_L2F_LOGIN_FRONT_KICKOUT_CLIENT_DATA
	{
        U64 clientAccountId;
	};
	struct PT_LOGIN_L2F_LOGIN_FRONT_KICKOUT_CLIENT_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LOGIN_L2F_LOGIN_FRONT_KICKOUT_CLIENT_DATA); 
	};
    
	struct PT_LOGIN_L2F_LOGIN_FRONT_KICKOUT_CLIENT_DATA_DESCRIBE : public GameNetPacketDataDescribe
	{

	};
	*/
	//**********************************************************************
#pragma pack (pop)

}

/******************************************************************************/

#endif