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
		Bool	processLoginServerPacket(CClient* client,NetEventRecv* packet);
		Bool	processFrontServerPacket(CClient* client,NetEventRecv* packet);
    //************************************************************

    //@{ LoginServer
    public:
        //发送登入请求到登入服务器
        void	sendLoginPacketToLoginServer(I32 netId,CChar16* name, CChar16* password);

    protected:
        
        //客户端登入失败结果
        void    onClientLoginFailedFromLoginServer( CClient* client , PT_LOGIN_L2C_LOGIN_FAIL_DATA* data );
        //客户端登入成功结果
        void    onClientLoginSuccessedFromLoginServer( CClient* client , PT_LOGIN_L2C_LOGIN_SUCCESS_DATA* data );
		//客户端登陆排队信息
		//void    onClientLoginQueueInfoFromLoginServer( CClient* client , PT_LOGIN_L2C_ACC_LOGIN_QUEUE_INFO_DATA* data );
    //@ }

    //************************************************************

    //@{ FrontServer
    public:
        //发送登入请求到前端服务器
        void	sendLoginPacketToFrontServer(I32 netId,CChar16* name, CChar16* password);

        //发送选择角色请求到前端服务器
        void	sendSelectCharacterPacketToFrontServer(I32 netId,UInt id);

        //发送创建氏族信息到FrontServer
        void    sendClanInfoToFrontServer(I32 netId, CClan* pClan );

        //发送需要删除的氏族到FrontServer
        void    sendSelectClanToFrontServer(I32 netId, U64 clanid );

        //发送需要删除的氏族到FrontServer
        void    sendDeleteClanToFrontServer(I32 netId, U64 clanid );

        //发送进入游戏的请求到FrontServer
        void    sendJoingameToFrontServer(I32 netId);

        //退出游戏。
        void    sendToFrontServerExitgame(I32 netId);

        //发送创建武将的信息到FrontServer
        void    sendCreateGenrealToFrontServer(I32 netId, PlayerCharacterData* pCharacterData );

    protected:

        //客户端登入结果
        void    onRecvClientLoginResultFromFrontServer( CClient* client , PT_LOGIN_F2C_LOGIN_RESULT_DATA* data );
        //打开氏族创建界面
        void    onRecvClientOpenCreateClanUIFromFrontServer( CClient* client );
        //打开氏族管理界面
        void    onRecvClientOpenClanControlUIFromFrontServer( CClient* client);

		void	onRecvClientClanInfoFromFrontServer( CClient* client, PT_LOGIN_F2C_CLAN_LIST_DATA* data );
		//创建氏族的结果反馈
        void    onRecvClientCreateClanResultFromFrontServer( CClient* client, PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA* data );
        //删除氏族的结果反馈
        void    onRecvClientSelectClanResultFromFrontServer( CClient* client, PT_LOGIN_F2C_SELECT_CLAN_RESULT_DATA* data );
        //删除氏族的结果反馈
        void    onRecvClientDeleteClanResultFromFrontServer( CClient* client, PT_LOGIN_F2C_DELETE_CLAN_RESULT_DATA* data );
        //点击进入游戏的结果反馈
        void    onRecvClientOpenCreateGenrealUIFromFrontServer( CClient* client );
        //创建武将结果反馈
        void    onRecvClientCreateGenrealResultFromFrontServer( CClient* client, PT_LOGIN_F2C_CREATE_GENERAL_RESULT_DATA* data );
		
		//@ }
		
    };

}
#endif