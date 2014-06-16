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
	/*帐号登入管理
		# 负责管理LoginServer验证通过的玩家。
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

		/// 初始化和反初始化
		Bool			initialize(DBDriver* Driver,SServerSetting* setting);
		void			uninitialize();

		/// 主进程更新
		void			update();


        //-----------------------------------------------------------------------------------
        //  Account 
        //  Relate to LoginServer And Client
        //-----------------------------------------------------------------------------------

		/// 处理客户端登入
		void			handleClientLogin( I32 id, Char16* accName, Char16* accPsw );
		/// 处理客户端登出
		void			handleClientLogout( ClientObject* clientPtr );

        /// 处理客户端登入成功
        void			onClientLoginSuccessedFromLoginServer( ClientObject* clientPtr, AccountIdType accID );


        /// 处理LoginServer断开
        void			handleLoginServerDisconnect();
        
		//-----------------------------------------------------------------------------------
		//  Check
		//-----------------------------------------------------------------------------------

		/// LoginServer检测客户端是否存在
		void			handleCheckClientInServerFromLs(I32 loginServerNetId,I32 clientNetId,I32 clientNetIdInFs);
		/// MapServer检测客户端是否存在
		void			handleCheckClientInServerFromMs(I32 mapServerNetId,I32 clientNetId);
		// 发送LoginServer检验结果客户端存在结果
		void			sendClientInFsCheckResultToLs(I32 loginServerNetId,Bool result);

        //-----------------------------------------------------------------------------------
        //  Clan
        //-----------------------------------------------------------------------------------

		/// 处理客户端选择氏族
		//U8              handleClanSelect( I32 clientID, I32 clanId );

        // 通知客户端打开氏族创建界面
       void            sendClientOpenCreateClan( I32 id );
        // 通知客户端打开氏族管理界面
        void            sendClientOpenControlClan( I32 id );
        // 发送删除氏族的结果
        void            sendClientDeleteClanResult( I32 id, U8 result );

		//处理创建氏族信息
		CreateClanResult			handleClientCreateClan(I32 id, ClanData& _clanData);

		//-----------------------------------------------------------------------------------
		//  PlayerCharacter
		//-----------------------------------------------------------------------------------
		
		CreateGenrealResult			handleClientCreateGenreal(I32 id, PlayerCharacterData& _PlayerCharacterData, const CharacterResInfo* _pCreateChar);

		//-----------------------------------------------------------------------------------
		//  JoinGame
		//-----------------------------------------------------------------------------------
		//处理登陆信息
		void						handleClientJoinGame(I32 id, PlayerIdType accountId);

	private:
		CreateClanResult			checkClanDataLawful(ClanData* _clandata, SPlayerPtr& pSPlayerPtr);
		CreateGenrealResult			checkGenrealDataLawful(PlayerCharacterData* _PlayerCharacterData, SPlayerPtr& pSPlayerPtr);
	};
}
#endif



