/******************************************************************************/
#ifndef _LOGINNETPACKETPROCESSER_H_
#define _LOGINNETPACKETPROCESSER_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "NetAddress.h"
#include "GameNetPacket.h"
#include "LoginNetPacket.h"
#include "PlayerNetPacket.h"

/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //�ʺŵ�����Ϣ����
    /******************************************************************************/
    class CPlayer;
    class CPlayerCharacter;
    class CClan;
    /******************************************************************************/
    class LoginNetPacketProcesser
    {
    public:
        SINGLETON_INSTANCE(LoginNetPacketProcesser);
		Bool	processLoginServerPacket(CClient* client,NetEventRecv* packet);
		Bool	processFrontServerPacket(CClient* client,NetEventRecv* packet);
    //************************************************************

    //@{ LoginServer
    public:
        //���͵������󵽵��������
        void	sendLoginPacketToLoginServer(I32 netId,CChar16* name, CChar16* password);

    protected:
        
        //�ͻ��˵���ʧ�ܽ��
        void    onClientLoginFailedFromLoginServer( CClient* client , PT_LOGIN_L2C_LOGIN_FAIL_DATA* data );
        //�ͻ��˵���ɹ����
        void    onClientLoginSuccessedFromLoginServer( CClient* client , PT_LOGIN_L2C_LOGIN_SUCCESS_DATA* data );
		//�ͻ��˵�½�Ŷ���Ϣ
		//void    onClientLoginQueueInfoFromLoginServer( CClient* client , PT_LOGIN_L2C_ACC_LOGIN_QUEUE_INFO_DATA* data );
    //@ }

    //************************************************************

    //@{ FrontServer
    public:
        //���͵�������ǰ�˷�����
        void	sendLoginPacketToFrontServer(I32 netId,CChar16* name, CChar16* password);

        //����ѡ���ɫ����ǰ�˷�����
        void	sendSelectCharacterPacketToFrontServer(I32 netId,UInt id);

        //���ʹ���������Ϣ��FrontServer
        void    sendClanInfoToFrontServer(I32 netId, CClan* pClan );

        //������Ҫɾ�������嵽FrontServer
        void    sendSelectClanToFrontServer(I32 netId, U64 clanid );

        //������Ҫɾ�������嵽FrontServer
        void    sendDeleteClanToFrontServer(I32 netId, U64 clanid );

        //���ͽ�����Ϸ������FrontServer
        void    sendJoingameToFrontServer(I32 netId);

        //�˳���Ϸ��
        void    sendToFrontServerExitgame(I32 netId);

        //���ʹ����佫����Ϣ��FrontServer
        void    sendCreateGenrealToFrontServer(I32 netId, PlayerCharacterData* pCharacterData );

    protected:

        //�ͻ��˵�����
        void    onRecvClientLoginResultFromFrontServer( CClient* client , PT_LOGIN_F2C_LOGIN_RESULT_DATA* data );
        //�����崴������
        void    onRecvClientOpenCreateClanUIFromFrontServer( CClient* client );
        //������������
        void    onRecvClientOpenClanControlUIFromFrontServer( CClient* client);

		void	onRecvClientClanInfoFromFrontServer( CClient* client, PT_LOGIN_F2C_CLAN_LIST_DATA* data );
		//��������Ľ������
        void    onRecvClientCreateClanResultFromFrontServer( CClient* client, PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA* data );
        //ɾ������Ľ������
        void    onRecvClientSelectClanResultFromFrontServer( CClient* client, PT_LOGIN_F2C_SELECT_CLAN_RESULT_DATA* data );
        //ɾ������Ľ������
        void    onRecvClientDeleteClanResultFromFrontServer( CClient* client, PT_LOGIN_F2C_DELETE_CLAN_RESULT_DATA* data );
        //���������Ϸ�Ľ������
        void    onRecvClientOpenCreateGenrealUIFromFrontServer( CClient* client );
        //�����佫�������
        void    onRecvClientCreateGenrealResultFromFrontServer( CClient* client, PT_LOGIN_F2C_CREATE_GENERAL_RESULT_DATA* data );
		
		//@ }
		
    };

}
#endif