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
        <帐号登入管理>
        # 首先登入LoginServer,成功后会得到分配到的FrontServer地址
        # 然后登入FrontServer.成功后则登入流程完毕
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


        //登入状态
        enum LoginState   
        {
            LS_IDLE,
            LS_SEL_SERVER,
            LS_LOGIN_ACCOUNT,
            LS_READY_GAME,
            LS_SEL_CLAN
        };

	public:
        
        //开始登入
        void    start();

        //重新开始登入
        //回到最初登入界面
        void    restore();

	//@{
	//	登入账号相关方法

        //开始帐号登入
        void    startAccountLogin();
		//登入LoginServer
		void	loginToLoginServer(Str16& accName, Str16& accPsw);
		
		//void    handleClientLoginQueueInfo(Byte type, I32 waitAccount);

        //登入LoginServer失败
        void    onLoginToLoginServerFailed( I8 errorResult );
        //登入LoginServer成功
        void    onLoginToLoginServerSuccessed( CChar* frontSvrIP, I32 frontSvrPort );

        //登入FrontServer
        void	loginToFrontServer();
        //登入FrontServer结果事件
		void	onRecvLoginToFrontServerResult( I8 result, PlayerIdType accountId );
        //打开创建氏族界面
        void    openClanCreateUI( );
        //打开氏族控制界面
        void    openClanControlUI();
        //创建氏族的结果
        void    handleCreateClanResult( CreateClanResult result );
        //删除氏族的结果
        void    handleClanDeleteResult( DeleteClanResult result );
        //向服务器请求创建氏族。
        void    sendToFrontServerCreateClan( CClan* pClan );
        // 处理选择氏族
        //void    handleSelectClanResult( SelectClanResult index );
        // 向服务器请求删除氏族
        void    sendToFrontServerSelectClan( U64 clanId );
        // 向服务器请求删除氏族
        void    sendToFrontServerDeleteClan( U64 clanId );
        // 向服务器请求加入game
        void    sendToFrontServerJoingame();
        // 向服务器请求加入game
        void    sendToFrontServerExitgame(  );
        // 向服务器请求创建武将
        void    sendToFrontServerCreateGenreal(U32 resID, PlayerCharacterData* pPlayerCharacterData );
        // 处理创建
        void    openGenrealCreateUI();
        // 处理创建
        void    handleCreateGenrealResult( CreateGenrealResult index, PlayerCharacterIdType genrealID );

        // 处理创建
        void    handleGenrealInfo();
	//@}

        
	//@{
	//	服务器相关方法
        /*
            # 登入服务器断开事件
            # 如果在输入帐号界面,则退回到选择登入服务器界面
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
        I32     mPasswordErrorNum;                  //输入密码失败次数。
        I32     mPasswordErrorMax;                  //输入密码失败的最大次数。
    };

}
#endif