/******************************************************************************/
#ifndef _LOGINMANAGER_H_
#define _LOGINMANAGER_H_
/******************************************************************************/
#include "Lock.h"
#include "LoginNetPacket.h"
#include "FrontServerPreqs.h"
#include "WorldCorePreqs.h"
#include "CharacterResourceConfig.h"
/******************************************************************************/
namespace MG
{
    class ClientObjectPtr;
	class ClientObject;

	/******************************************************************************/
	/*�ʺŵ������
		# �������LoginServer��֤ͨ������ҡ�
	*/
	/******************************************************************************/
	class LoginManager
	{
	public:
		SINGLETON_INSTANCE(LoginManager);
		LoginManager();
		virtual	~LoginManager();

        //-----------------------------------------------------------------------------------
        // Main
        //-----------------------------------------------------------------------------------

		/// ��ʼ���ͷ���ʼ��
		Bool			initialize(DBDriver* Driver,SServerSetting* setting);
		void			uninitialize();

		/// �����̸���
		void			update();


        //-----------------------------------------------------------------------------------
        //  Account 
        //  Relate to LoginServer And Client
        //-----------------------------------------------------------------------------------

		/// ����ͻ��˵���
		void			handleClientLogin( I32 id, Char16* accName, Char16* accPsw );
		/// ����ͻ��˵ǳ�
		void			handleClientLogout( ClientObject* clientPtr );

        /// ����ͻ��˵���ɹ�
        void			onClientLoginSuccessedFromLoginServer( ClientObject* clientPtr, AccountIdType accID );


        /// ����LoginServer�Ͽ�
        void			handleLoginServerDisconnect();
        
		//-----------------------------------------------------------------------------------
		//  Check
		//-----------------------------------------------------------------------------------

		/// LoginServer���ͻ����Ƿ����
		void			handleCheckClientInServerFromLs(I32 loginServerNetId,I32 clientNetId,I32 clientNetIdInFs);
		/// MapServer���ͻ����Ƿ����
		void			handleCheckClientInServerFromMs(I32 mapServerNetId,I32 clientNetId);
		// ����LoginServer�������ͻ��˴��ڽ��
		void			sendClientInFsCheckResultToLs(I32 loginServerNetId,Bool result);

        //-----------------------------------------------------------------------------------
        //  Clan
        //-----------------------------------------------------------------------------------

		/// ����ͻ���ѡ������
		//U8              handleClanSelect( I32 clientID, I32 clanId );

        // ֪ͨ�ͻ��˴����崴������
       void            sendClientOpenCreateClan( I32 id );
        // ֪ͨ�ͻ��˴�����������
        void            sendClientOpenControlClan( I32 id );
        // ����ɾ������Ľ��
        void            sendClientDeleteClanResult( I32 id, U8 result );

		//������������Ϣ
		CreateClanResult			handleClientCreateClan(I32 id, ClanData& _clanData);

		//-----------------------------------------------------------------------------------
		//  PlayerCharacter
		//-----------------------------------------------------------------------------------
		
		CreateGenrealResult			handleClientCreateGenreal(I32 id, PlayerCharacterData& _PlayerCharacterData, const CharacterResInfo* _pCreateChar);

		//-----------------------------------------------------------------------------------
		//  JoinGame
		//-----------------------------------------------------------------------------------
		//�����½��Ϣ
		void						handleClientJoinGame(I32 id, PlayerIdType accountId);

	private:
		CreateClanResult			checkClanDataLawful(ClanData* _clandata, SPlayerPtr& pSPlayerPtr);
		CreateGenrealResult			checkGenrealDataLawful(PlayerCharacterData* _PlayerCharacterData, SPlayerPtr& pSPlayerPtr);
	};
}
#endif



