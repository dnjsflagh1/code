/******************************************************************************/
#ifndef _LOGINNETPACKET_H_
#define _LOGINNETPACKET_H_
/******************************************************************************/

#include "CommonGameDefine.h"
#include "NetDefine.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //��Ϸ�ʺŰ�����
    /******************************************************************************/
    enum LoginNetPacketType
    {
		PT_LOGIN_UNKNOW = 0,
		PT_LOGIN_S2S_SERVER_LOGIN,					//������֮��ĵ�������

		PT_F2M_MAPLIST,								

		PT_LOGIN_F2L_FRONT_SERVER_LOGIN,			//FrontServer ���� LoginServer
		PT_LOGIN_L2F_LOGIN_FRONT_SERVER_RESULT,		//FrontServer ���� LoginServer ���ؽ��

        PT_LOGIN_C2L_ACC_LOGIN = 20,				//�ͻ����˺ŵ�½LoginServer		
		PT_LOGIN_L2C_ACC_LOGIN_FAIL,				//�ͻ����˺ŵ���ʧ����Ϣ
		PT_LOGIN_L2C_ACC_LOGIN_QUEUE_INFO,

		PT_LOGIN_L2C_ACC_LOGIN_SUCCESS,				//�ͻ����˺ŵ���ɹ���Ϣ

		PT_LOGIN_C2F_ACC_LOGIN,						//�ͻ����˺ŵ���FrontServer
        PT_LOGIN_C2F_ACC_LOGOUT,					//�ͻ����˺ŵ���FrontServer
		PT_LOGIN_F2C_ACC_LOGIN_RESULT,				//�ͻ����˺ŵ���FrontServer���ؽ��

		PT_LOGIN_F2L_CLIENT_LOGIN,					//�ͻ����˺ŵ���֪ͨ����֤
		PT_LOGIN_L2F_CLIENT_CHECKED,				//�ͻ����˺ŵ�����֤���
		PT_LOGIN_F2L_CLIENT_LOGOUT,					//�ͻ����˺ŵǳ�

        PT_LOGIN_F2C_OPEN_CREATECLANUI,				//[FrontServer -> Client] ֪ͨ�ͻ��˴򿪴�������Ľ���
        PT_LOGIN_F2C_OPEN_CLANCONTROLUI,			//[FrontServer -> Client] ֪ͨ�ͻ��˴�����������
        PT_LOGIN_C2F_CREATE_CLAN,					//[Client -> FrontServer] ����������������塣
        PT_LOGIN_F2C_CREATE_CLAN_RESULT,			//[FrontServer -> Client] ���ط�������������Ľ��
        PT_LOGIN_C2F_SELECT_CLAN,					//[Client -> FrontServer] ���������ѡ�����塣
        PT_LOGIN_F2C_SELECT_CLAN_RESULT,			//[FrontServer -> Client] ���ط�����ѡ������Ľ��
        PT_LOGIN_C2F_DELETE_CLAN,					//[Client -> FrontServer] ���������ɾ�����塣
        PT_LOGIN_F2C_DELETE_CLAN_RESULT,			//[FrontServer -> Client] ���ط�����ɾ������Ľ��

        PT_LOGIN_C2F_JOINGAME,						//[Client -> FrontServer] �ͻ��������¼game

		PT_LOGIN_F2A_JOINGAME,						//[FrontServer -> ChatServer]ǰ̨������֪ͨ����������ͻ��˽�����Ϸ
		PT_LOGIN_F2A_EXITGAME,						//[FrontServer -> ChatServer]ǰ̨������֪ͨ����������ͻ����뿪��Ϸ
		PT_LOGIN_F2A_CLIENTLIST_INGAME,				//[FrontServer -> ChatServer]ǰ̨�����¼���������ʱ����Ϸ�еĿͻ��˶���
		
        PT_LOGIN_F2C_OPENCRETEGENREALUI,			//[FrontServer -> Client] ������������أ�����ɹ����ǽ�����Ϸ��
        PT_LOGIN_C2F_CREATE_GENERAL,				//[Client -> FrontServer] �ͻ������󴴽��佫��
        PT_LOGIN_F2C_CREATE_GENERAL_RESULT,			//[FrontServer -> Client] �ͻ��˷��ش����佫�����

		// ��׳�Լ��
		PT_LOGIN_L2F_CHECK_INFRONTSERVER,
		PT_LOGIN_F2L_CHECK_INFRONTSERVER_RESULT,
		PT_LOGIN_M2F_CHECK_INFRONTSERVER,
		PT_LOGIN_F2M_CHECK_INFRONTSERVER_RESULT,
    };
    
	/******************************************************************************/
	//��¼�Ŷ�����
	/******************************************************************************/
    enum LOGIN_LINE_UP_TYPE
	{
          login_line_up_busy = 1,
		  login_line_up_full

	};


#pragma pack (push)
#pragma pack (1)

    //**********************************************************************
    //������֮�����
    struct PT_LOGIN_S2S_LOGIN_DATA
    {
        U8  serverType;
        U32 code; 
		U32 serverId;
		U64 serverUniqueFlag;
		Char16 name[MAX_SERVER_NAME_LEN];
    };

    struct PT_LOGIN_S2S_LOGIN_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_S2S_LOGIN_DATA);
    };

	//**********************************************************************

	struct NetMapServer
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
    };

	//**********************************************************************
    //�ͻ����ʺŵ���
    struct  PT_LOGIN_C2L_LOGIN_DATA
    {
		Char16 accName[MAX_ACCOUNT_LONGIN_NAME_LEN];
		Char16 accPsw[MAX_ACCOUNT_LONGIN_PSW_LEN];
    };
    struct PT_LOGIN_C2L_LOGIN_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_C2L_LOGIN_DATA);
    };

	//**********************************************************************
	//Loginserver����FrontServer��Ϣ���ͻ���
	struct  PT_LOGIN_L2C_LOGIN_SUCCESS_DATA
	{
		Char	ip[MG_NET_MAX_IP_LEN];
		I32		port;
	};
    struct PT_LOGIN_L2C_LOGIN_SUCCESS_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_L2C_LOGIN_SUCCESS_DATA);
    };

	//**********************************************************************
	//Loginserver���ص�½������Ϣ
	struct  PT_LOGIN_L2C_ACC_LOGIN_QUEUE_INFO_DATA
	{   
		Byte type;
		I32 waitCount;
	};
    struct PT_LOGIN_L2C_ACC_LOGIN_QUEUE_INFO_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_L2C_ACC_LOGIN_QUEUE_INFO_DATA);
    };

	//**********************************************************************
	//FrontServer��½LoginServer��Ϣ
	struct PT_LOGIN_F2L_LOGIN_DATA 
	{
		Char	ip[MG_NET_MAX_IP_LEN];
		I32		port;
	};
    struct PT_LOGIN_F2L_LOGIN_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_F2L_LOGIN_DATA);
    };

	//**********************************************************************
	//Clinet��½FrontServer��Ϣ
	struct PT_LOGIN_C2F_LOGIN_DATA
	{
		PT_LOGIN_C2L_LOGIN_DATA data;
	};
    struct PT_LOGIN_C2F_LOGIN_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_C2F_LOGIN_DATA);
    };

	//**********************************************************************
	//Client��½FrontServer���
	enum PT_LOGIN_F2C_LOGIN_RESULT_TYPE 
	{
		LCFT_LOGIN_UNKNOW,
		LCFT_LOGIN_SUCCESS,			
		LCFT_LOGIN_FAIL,	
	};
	struct PT_LOGIN_F2C_LOGIN_RESULT_DATA
	{
		I8 result;
	};
    struct PT_LOGIN_F2C_LOGIN_RESULT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_F2C_LOGIN_RESULT_DATA);
    };
	//**********************************************************************
	//FrontServer���͸�LoginServer�Ŀͻ���У����Ϣ
	struct	PT_LOGIN_F2L_CLIENT_LOGIN_DATA
	{
		I32 clientNetId;
		PT_LOGIN_C2L_LOGIN_DATA data;
	};
    struct PT_LOGIN_F2L_CLIENT_LOGIN_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_F2L_CLIENT_LOGIN_DATA);
    };
	//**********************************************************************
	//FrontServer���͸�LoginServer�Ŀͻ��˵ǳ���Ϣ
	struct	PT_LOGIN_F2L_CLIENT_LOGOUT_DATA
	{
		Char16	accName[MAX_ACCOUNT_LONGIN_NAME_LEN];
	};
    struct PT_LOGIN_F2L_CLIENT_LOGOUT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_F2L_CLIENT_LOGOUT_DATA);
    };
	//**********************************************************************
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
	//**********************************************************************
	//FrontServer��½LoginServer���
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
	//**********************************************************************
	//LoginServer���ظ�FrontServerУ����
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
    //**********************************************************************
    struct PT_LOGIN_F2C_SIMPLECLANDATABASE
    {
        U64 clandatabaseid;				//����ID
        U64 accountid;                  //���ID
        U8  status;                     //״̬
        U8  ancestry;				    //Ѫͳ
        Char16 clanhomelandname[MAX_CHARACTER_NAME_LEN];	//������
        Char16 clanname[MAX_CHARACTER_NAME_LEN];			//������
        U8  armyemblem;                //���
        U8  armyemblemcolor;           //�����ɫ
        U8  bg;                        //����ͼ��
        U8  bgcolor;                   //������ɫ
        U32 clanbagsize;               //���屳��
        U64 mainGenrealId;             //���佫
        U32 regionID;                  //������������
        U8  regionType;                //��ͼ����
    };
    struct PT_LOGIN_F2C_SIMPLECLANDATABASE_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_F2C_SIMPLECLANDATABASE);
    };
    //**********************************************************************
    struct PT_LOGIN_F2C_OPEN_CLANCONTROLUI_DATA
    {
        UInt nCount;
        PT_LOGIN_F2C_SIMPLECLANDATABASE clanDatabase[1]; 
    };
    struct PT_LOGIN_F2C_OPEN_CLANCONTROLUI_DATA_INFO
    {
        static const Int elmentSize = sizeof (PT_LOGIN_F2C_SIMPLECLANDATABASE);
        static const Int headSize   = sizeof (PT_LOGIN_F2C_OPEN_CLANCONTROLUI_DATA) - sizeof(PT_LOGIN_F2C_SIMPLECLANDATABASE);
    };
    //**********************************************************************
    struct PT_LOGIN_C2F_CREATE_CLAN_DATA
    {
         PT_LOGIN_F2C_SIMPLECLANDATABASE clanDatabase;
    };
    struct PT_LOGIN_C2F_CREATE_CLAN_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_C2F_CREATE_CLAN_DATA);
    };
    //**********************************************************************
    enum CreateClanResult
    {
        CreateClanResult_Succeed = 0,
        CreateClanResult_NameExistOrUnlaw,
        CreateClanResult_OverMaxCreateS,
        CreateClanResult_OverMaxCreateR,
        CreateClanResult_OtherError,
		CreateClanResult_NoPlayer,				//û��Player ��Ϣ
		CreateClanResult_DB_Error,				//���ݿ����ʧ��

        CreateClanResult_Max
    };
    struct PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA
    {
         CreateClanResult result;
    };
    struct PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA);
    };
    //**********************************************************************
    struct PT_LOGIN_C2F_SELECT_CLAN_DATA
    {
        U64 clandatabaseid;            //����ID
    };
    struct PT_LOGIN_C2F_SELECT_CLAN_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_C2F_SELECT_CLAN_DATA);
    };
    //**********************************************************************
    enum SelectClanResult
    {
        SelectClanResult_Succeed = 0,
        SelectClanResult_ClanUnexist,        //���岻����
        SelectClanResult_ClanOndelete,       //��������ɾ����
        SelectClanResult_OtherError,         //����δ֪����

        SelectClanResult_Max
    };
    struct PT_LOGIN_F2C_SELECT_CLAN_RESULT_DATA
    {
        SelectClanResult result;
    };
    struct PT_LOGIN_F2C_SELECT_CLAN_RESULT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_F2C_SELECT_CLAN_RESULT_DATA);
    };
    //**********************************************************************
    struct PT_LOGIN_C2F_DELETE_CLAN_DATA
    {
         U64 clandatabaseid;            //����ID
    };
    struct PT_LOGIN_C2F_DELETE_CLAN_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_C2F_DELETE_CLAN_DATA);
    };
    //**********************************************************************
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
	//**********************************************************************
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
	//**********************************************************************
	struct PT_LOGIN_F2A_CLIENTLIST_INGAME_DATA
	{
		U16 count;
		PT_LOGIN_F2A_JOINGAME_DATA data[1];
	};
	struct PT_LOGIN_F2A_CLIENTLIST_INGAME_DATA_INFO
	{
		static const Int elmentSize = sizeof (PT_LOGIN_F2A_JOINGAME_DATA);
		static const Int headSize   = sizeof (PT_LOGIN_F2A_CLIENTLIST_INGAME_DATA) - sizeof(PT_LOGIN_F2A_JOINGAME_DATA);
	};

	//**********************************************************************
	struct PT_LOGIN_F2A_EXITGAME_DATA
	{
		Char16	clanName[MAX_CLAN_NAME];
	};
	struct PT_LOGIN_F2A_EXITGAME_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LOGIN_F2A_EXITGAME_DATA);
	};
    //**********************************************************************
    struct PT_LOGIN_C2F_CREATE_GENERAL_DATA
    {
        Char16			name[MAX_CHARACTER_NAME_LEN];
        Char16			charZiName[MAX_CHARACTER_NAME_LEN];
        U32				characterTemplateID;
		U32				charArtIcon;
		RegionIdType    maplistid;
		Int             maplisttype;
		U32             pointerid;
		U32             resID;
    };
    struct PT_LOGIN_C2F_CREATE_GENERAL_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_C2F_CREATE_GENERAL_DATA);
    };
    //**********************************************************************
    enum CreateGenrealResult
    {
        CreateGenrealResult_Succeed = 0,
        CreateGenrealResult_OtherError,

        CreateGenrealResult_Max
    };
    struct PT_LOGIN_F2C_CREATE_GENERAL_RESULT_DATA
    {
        CreateGenrealResult result;
        Bool                isGenreal;
        IdType              genrealID;
    };
    struct PT_LOGIN_F2C_CREATE_GENERAL_RESULT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_LOGIN_F2C_CREATE_GENERAL_RESULT_DATA);
    };
	//--------------------------------------------------------------------
	enum LOGIN_INFRONTSERVER_CHECK_RESULT
	{
		Login_Infrontserver_Check_Result_Success = 0,
		Login_Infrontserver_Check_Result_Fail
	};
	//--------------------------------------------------------------------
    //**********************************************************************
	struct PT_LOGIN_L2F_CHECK_INFRONTSERVER_DATA
	{
		Char16 accountName[MAX_ACCOUNT_LONGIN_NAME_LEN];
	};
	struct PT_LOGIN_L2F_CHECK_INFRONTSERVER_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LOGIN_L2F_CHECK_INFRONTSERVER_DATA);
	};
	//**********************************************************************
	struct PT_LOGIN_F2L_CHECK_INFRONTSERVER_RESULT_DATA
	{
		Char16 accountName[MAX_ACCOUNT_LONGIN_NAME_LEN];
		Byte		  result;
	};
	struct PT_LOGIN_F2L_CHECK_INFRONTSERVER_RESULT_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LOGIN_F2L_CHECK_INFRONTSERVER_RESULT_DATA);
	};
	//**********************************************************************
	struct PT_LOGIN_M2F_CHECK_INFRONTSERVER_DATA
	{
		Char16 accountName[MAX_ACCOUNT_LONGIN_NAME_LEN];
	};
	struct PT_LOGIN_M2F_CHECK_INFRONTSERVER_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LOGIN_M2F_CHECK_INFRONTSERVER_DATA);
	};
	//**********************************************************************
	struct PT_LOGIN_F2M_CHECK_INFRONTSERVER_RESULT_DATA
	{
		Char16 accountName[MAX_ACCOUNT_LONGIN_NAME_LEN];
		Byte		  result;
	};
	struct PT_LOGIN_F2M_CHECK_INFRONTSERVER_RESULT_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_LOGIN_F2M_CHECK_INFRONTSERVER_RESULT_DATA);
	};
	//**********************************************************************
#pragma pack (pop)

}

/******************************************************************************/

#endif