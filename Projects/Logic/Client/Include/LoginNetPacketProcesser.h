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

        Bool	processLoginServerPacket(I32 id,NetEventRecv* packet);
        Bool	processFrontServerPacket(I32 id,NetEventRecv* packet);

    //************************************************************

    //@{ LoginServer
    public:
        //���͵������󵽵��������
        void	sendLoginPacketToLoginServer(CChar16* name, CChar16* password,Char8* clientVersion);

    protected:
        
        //�ͻ��˵���ʧ�ܽ��
        void    onClientLoginFailedFromLoginServer( I32 id , PT_LOGIN_L2C_LOGIN_FAIL_DATA* data );
        //�ͻ��˵���ɹ����
        void    onClientLoginSuccessedFromLoginServer( I32 id , PT_LOGIN_L2C_LOGIN_SUCCESS_DATA* data );
		//�ͻ��˵�½�Ŷ���Ϣ
		//void    onClientLoginQueueInfoFromLoginServer( I32 id , PT_LOGIN_L2C_ACC_LOGIN_QUEUE_INFO_DATA* data );
		////�ͻ��˵�½�Ŷ���Ϣ
		//void    onClientLoginQueueInfoFromFrontServer( I32 id , PT_LOGIN_F2C_ACC_LOGIN_QUEUE_INFO_DATA* data );
		void	onRecvLoginVersionError(I32 id , PT_SERVER_S2C_LOGIN_VERSION_ERROR_DATA* data);
    //@ }

    //************************************************************

    //@{ FrontServer
    public:
        //���͵�������ǰ�˷�����
        void	sendLoginPacketToFrontServer(CChar16* name, CChar16* password);

        //����ѡ���ɫ����ǰ�˷�����
        void	sendSelectCharacterPacketToFrontServer(UInt id);

        //���ʹ���������Ϣ��FrontServer
        void    sendClanInfoToFrontServer( CClan* pClan );

        //������Ҫɾ�������嵽FrontServer
        //void    sendSelectClanToFrontServer( ClanIdType clanid );

        //������Ҫɾ�������嵽FrontServer
        void    sendDeleteClanToFrontServer( ClanIdType clanid );

        //���ͽ�����Ϸ������FrontServer
        void    sendJoingameToFrontServer();

        //�˳���Ϸ��
        void    sendToFrontServerExitgame();

        //���ʹ����佫����Ϣ��FrontServer
        void    sendCreateGenrealToFrontServer(U32 resID, PlayerCharacterData* pCharacterData );

    protected:

        //�ͻ��˵�����
        void    onRecvClientLoginResultFromFrontServer( I32 id , PT_LOGIN_F2C_LOGIN_RESULT_DATA* data );
        //�����崴������
        void    onRecvClientOpenCreateClanUIFromFrontServer( I32 id );
		//���յ��ͻ�����Ϣ
		void	onRecvClientClanInfoFromFrontServer(I32 id, PT_LOGIN_F2C_CLAN_DATA_DATA* data );
        //������������
        void    onRecvClientOpenClanControlUIFromFrontServer( I32 id );
        //��������Ľ������
        void    onRecvClientCreateClanResultFromFrontServer( I32 id, PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA* data );
        //ɾ������Ľ������
        //void    onRecvClientSelectClanResultFromFrontServer( I32 id, PT_LOGIN_F2C_SELECT_CLAN_RESULT_DATA* data );
        //ɾ������Ľ������
        void    onRecvClientDeleteClanResultFromFrontServer( I32 id, PT_LOGIN_F2C_DELETE_CLAN_RESULT_DATA* data );
        //���������Ϸ�Ľ������
        void    onRecvClientOpenCreateGenrealUIFromFrontServer( I32 id );
        //�����佫�������
        void    onRecvClientCreateGenrealResultFromFrontServer( I32 id, PT_LOGIN_F2C_CREATE_GENERAL_RESULT_DATA* data );
    //@ }
		
    };

}
#endif