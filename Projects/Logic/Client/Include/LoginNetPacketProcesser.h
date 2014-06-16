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
    //帐号登入消息处理
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
        //发送登入请求到登入服务器
        void	sendLoginPacketToLoginServer(CChar16* name, CChar16* password,Char8* clientVersion);

    protected:
        
        //客户端登入失败结果
        void    onClientLoginFailedFromLoginServer( I32 id , PT_LOGIN_L2C_LOGIN_FAIL_DATA* data );
        //客户端登入成功结果
        void    onClientLoginSuccessedFromLoginServer( I32 id , PT_LOGIN_L2C_LOGIN_SUCCESS_DATA* data );
		//客户端登陆排队信息
		//void    onClientLoginQueueInfoFromLoginServer( I32 id , PT_LOGIN_L2C_ACC_LOGIN_QUEUE_INFO_DATA* data );
		////客户端登陆排队信息
		//void    onClientLoginQueueInfoFromFrontServer( I32 id , PT_LOGIN_F2C_ACC_LOGIN_QUEUE_INFO_DATA* data );
		void	onRecvLoginVersionError(I32 id , PT_SERVER_S2C_LOGIN_VERSION_ERROR_DATA* data);
    //@ }

    //************************************************************

    //@{ FrontServer
    public:
        //发送登入请求到前端服务器
        void	sendLoginPacketToFrontServer(CChar16* name, CChar16* password);

        //发送选择角色请求到前端服务器
        void	sendSelectCharacterPacketToFrontServer(UInt id);

        //发送创建氏族信息到FrontServer
        void    sendClanInfoToFrontServer( CClan* pClan );

        //发送需要删除的氏族到FrontServer
        //void    sendSelectClanToFrontServer( ClanIdType clanid );

        //发送需要删除的氏族到FrontServer
        void    sendDeleteClanToFrontServer( ClanIdType clanid );

        //发送进入游戏的请求到FrontServer
        void    sendJoingameToFrontServer();

        //退出游戏。
        void    sendToFrontServerExitgame();

        //发送创建武将的信息到FrontServer
        void    sendCreateGenrealToFrontServer(U32 resID, PlayerCharacterData* pCharacterData );

    protected:

        //客户端登入结果
        void    onRecvClientLoginResultFromFrontServer( I32 id , PT_LOGIN_F2C_LOGIN_RESULT_DATA* data );
        //打开氏族创建界面
        void    onRecvClientOpenCreateClanUIFromFrontServer( I32 id );
		//当收到客户端信息
		void	onRecvClientClanInfoFromFrontServer(I32 id, PT_LOGIN_F2C_CLAN_DATA_DATA* data );
        //打开氏族管理界面
        void    onRecvClientOpenClanControlUIFromFrontServer( I32 id );
        //创建氏族的结果反馈
        void    onRecvClientCreateClanResultFromFrontServer( I32 id, PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA* data );
        //删除氏族的结果反馈
        //void    onRecvClientSelectClanResultFromFrontServer( I32 id, PT_LOGIN_F2C_SELECT_CLAN_RESULT_DATA* data );
        //删除氏族的结果反馈
        void    onRecvClientDeleteClanResultFromFrontServer( I32 id, PT_LOGIN_F2C_DELETE_CLAN_RESULT_DATA* data );
        //点击进入游戏的结果反馈
        void    onRecvClientOpenCreateGenrealUIFromFrontServer( I32 id );
        //创建武将结果反馈
        void    onRecvClientCreateGenrealResultFromFrontServer( I32 id, PT_LOGIN_F2C_CREATE_GENERAL_RESULT_DATA* data );
    //@ }
		
    };

}
#endif