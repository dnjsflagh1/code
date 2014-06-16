/******************************************************************************/
#ifndef _LOGINNETPACKETPROCESSER_H_
#define _LOGINNETPACKETPROCESSER_H_
/******************************************************************************/

#include "LoginNetPacket.h"
#include "SPlayer.h"
/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //�ʺ����������Ϣ����
    /******************************************************************************/
    class SPlayer;
    class SClan;
    /******************************************************************************/
	struct MapServerInfo;

    class LoginNetPacketProcesser
    {
    public:
        SINGLETON_INSTANCE(LoginNetPacketProcesser);
        LoginNetPacketProcesser();
        ~LoginNetPacketProcesser();

        Bool	processClientPacket(I32 id, NetEventRecv* packet);
        Bool	processLoginServerPacket(I32 id, NetEventRecv* packet);
        Bool	processMapServerPacket(I32 id, NetEventRecv* packet);

		
	//************************************************************

	//@{ LoginServer
	public:
		//���Ϳͻ��˼�����Ϣ��LoginServer
		void	sendClientListenInfoToLoginServer( CChar* clientListenIp, I32 clientListenPort );
		//���Ϳͻ��˵�����֤�����LoginServer
		void	sendClientLoginCheckToLoginServer( I32 clientID, Char16* accName, Char16* accPsw );
		//���Ϳͻ��˵ǳ������LoginServer
		void	sendClientLogoutToLoginServer(CChar16* accName );
		// ���ͼ��Client���ڵĽ����LoginServer
		void	sendCheckClientInServerRelultToLs(I32 clientNetIdInLs,Bool result);

	protected:
		//�����ܵ��ͻ��˵�������LoginServer
		void	onRecvClientLoginResultFromLoginServer( I32 id , PT_LOGIN_L2F_CLIENT_CHECKED_DATA* data);
		//���յ�LoginServer��֤�ͻ����Ƿ���FrontServer
		void	onRecvCheckClientInServerFromLs(I32 id,PT_LOGIN_L2F_CHECK_INFRONTSERVER_DATA* data);
		
	//@ }

	//************************************************************
	//@{ MapServer
	public:
		void	sendMapServerListToMapServer( I32 id, std::vector<MapServerInfo*>& mapVec  );
		void	broadMapServerListToMapServer( std::map< I32, MapServerInfo* > &MapServerList );
		void	sendCheckClientInServerRelultToMs(I32 mapServerNetId,I32 clientNetId,Bool result);

		//���յ�MapServer��֤�ͻ����Ƿ���FrontServer
		void	onRecvCheckClientInServerFromMs(I32 ,PT_LOGIN_M2F_CHECK_INFRONTSERVER_DATA* data);
		//@ }
	//************************************************************
	//@{ ChatServer
	public:
		void	sendClientJoinGameToChatServer(I32 clientNetId,U64 accountId, CChar16* clanName);
		void	sendClientExitGameToChatServer(CChar16* clanName);
		void	sendClientListInGameToChatServer();
	protected:
		
	//@ }
	//************************************************************

	//@{ Client
	public:
		
		//���Ϳͻ��˵���FrontServer���
		void	sendClientConnectFrontServerResult( I32 id, PT_LOGIN_F2C_LOGIN_RESULT_TYPE result, PlayerIdType accountId );
        
		//����������Ϣ���ͻ���
		void    sendClientClanInfo( I32 id, ClanData* _pClanData );
		//���Ϳͻ���������������Ϣ����֪ͨ�ͻ��˴����
        void    sendClientOpenClanControlUI( I32 id );
        
		
		//֪ͨ�ͻ��˴����崴�����
        void    sendClientOpenClanCreateUI( I32 id );
        //���Ϳͻ��˴���������
        void    sendClientClanCreateResult( I32 id, CreateClanResult result, const ClanData& _clandata);
        //���Ϳͻ��˴���������
        void    sendClientClanSelectResult( I32 id, I32 index );
        //���Ϳͻ���ɾ��������
        void    sendClientClanDeleteResult( I32 id, I32 index );
        //���Ϳͻ��˵�����Ϸ�Ľ��
        void    sendClientOpenGenrealCreateUI( I32 id );
        //���Ϳͻ��˴����佫�Ľ��
        void    sendClientCreateGenrealResult( I32 id, I32 index, Bool isGenreal, IdType genrealID );
		
		//void	sendLoginQueueInfoToClient(I32 id, Byte type,I32 count = 0);
	public:

		//���ͻ��˵���
		void	onClientLogin( I32 id, PT_LOGIN_C2F_LOGIN_DATA* data );
        //���ͻ��˵ǳ�
        void	onClientLogout( I32 id );

        //�ͻ��˴�������
        void    onClientCreateClan( I32 id, PT_LOGIN_C2F_CREATE_CLAN_DATA* data );

        //�ͻ���ѡ������
        //void    onClientSelectClan( I32 id, PT_LOGIN_C2F_SELECT_CLAN_DATA* data );

        //�ͻ���ɾ������
        void    onClientDeleteClan( I32 id, PT_LOGIN_C2F_DELETE_CLAN_DATA* data );

        //�ͻ������������Ϸ
        void    onClientJoinGame( I32 id, PT_LOGIN_C2F_JOINGAME_DATA* data );

        //�ͻ������󴴽����佫
        void    onClientCreateGenreal( I32 id, PT_LOGIN_C2F_CREATE_GENERAL_DATA* data );
	//@ }

    };
}
#endif
