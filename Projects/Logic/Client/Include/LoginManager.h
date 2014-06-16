/******************************************************************************/
#ifndef _LOGINMANAGER_H_
#define _LOGINMANAGER_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "LoginNetPacket.h"
#include "PlayerNetPacket.h"

/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    /*
        <�ʺŵ������>
        # ���ȵ���LoginServer,�ɹ����õ����䵽��FrontServer��ַ
        # Ȼ�����FrontServer.�ɹ���������������
    */
    /******************************************************************************/
    class CPlayer;
    class CClan;
    class CPlayerCharacter;
    /******************************************************************************/
    class LoginManager
    {
    public:
        LoginManager();
        virtual ~LoginManager();
        SINGLETON_INSTANCE(LoginManager);


        //����״̬
        enum LoginState   
        {
            LS_IDLE,
            LS_SEL_SERVER,
            LS_LOGIN_ACCOUNT,
            LS_READY_GAME,
            LS_SEL_CLAN
        };

	public:
        
        //��ʼ����
        void    start();

        //���¿�ʼ����
        //�ص�����������
        void    restore();

	//@{
	//	�����˺���ط���

        //��ʼ�ʺŵ���
        void    startAccountLogin();
		//����LoginServer
		void	loginToLoginServer(Str16& accName, Str16& accPsw);
		
		//void    handleClientLoginQueueInfo(Byte type, I32 waitAccount);

        //����LoginServerʧ��
        void    onLoginToLoginServerFailed( I8 errorResult );
        //����LoginServer�ɹ�
        void    onLoginToLoginServerSuccessed( CChar* frontSvrIP, I32 frontSvrPort );

        //����FrontServer
        void	loginToFrontServer();
        //����FrontServer����¼�
		void	onRecvLoginToFrontServerResult( I8 result, PlayerIdType accountId );
        //�򿪴����������
        void    openClanCreateUI( );
        //��������ƽ���
        void    openClanControlUI();
        //��������Ľ��
        void    handleCreateClanResult( CreateClanResult result );
        //ɾ������Ľ��
        void    handleClanDeleteResult( DeleteClanResult result );
        //����������󴴽����塣
        void    sendToFrontServerCreateClan( CClan* pClan );
        // ����ѡ������
        //void    handleSelectClanResult( SelectClanResult index );
        // �����������ɾ������
        void    sendToFrontServerSelectClan( U64 clanId );
        // �����������ɾ������
        void    sendToFrontServerDeleteClan( U64 clanId );
        // ��������������game
        void    sendToFrontServerJoingame();
        // ��������������game
        void    sendToFrontServerExitgame(  );
        // ����������󴴽��佫
        void    sendToFrontServerCreateGenreal(U32 resID, PlayerCharacterData* pPlayerCharacterData );
        // ������
        void    openGenrealCreateUI();
        // ������
        void    handleCreateGenrealResult( CreateGenrealResult index, PlayerCharacterIdType genrealID );

        // ������
        void    handleGenrealInfo();
	//@}

        
	//@{
	//	��������ط���
        /*
            # ����������Ͽ��¼�
            # ����������ʺŽ���,���˻ص�ѡ��������������
        */
		void	onLoginServerDisconnect();

	//@}

    protected:
        static void onClickMsgBoxLoginFailError(void* user);
        static void onClickMsgBoxConnectError(void* user);
	private:
		Str 	mFrontServerIp;
		I32		mFrontServerPort;
        LoginState  mLoginState;
        I32     mPasswordErrorNum;                  //��������ʧ�ܴ�����
        I32     mPasswordErrorMax;                  //��������ʧ�ܵ���������
    };

}
#endif