/******************************************************************************/
#ifndef _GMACCOUNTOPNETPACKETPROCESSER_H_
#define _GMACCOUNTOPNETPACKETPROCESSER_H_
/******************************************************************************/
#include "GMAccountNetPacket.h"
#include "GameNetEvent.h"
/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //GM帐号操作消息处理
    /******************************************************************************/
    
    class GMAccountOpNetPacketProcesser
    {
    public:
        SINGLETON_INSTANCE(GMAccountOpNetPacketProcesser);

        Bool	processGMServerManagerPacket(I32 id,NetEventRecv* packet);

    //************************************************************

    public:
        //发送登入请求到登入服务器
        void	sendLoginPacketToGMServerManager(CChar16* name, CChar16* password,Char8* clientVersion);


    protected:
        
        //登录结果
        void    onGMLoginResultFromLoginServer( I32 id , GMPT_GMMC_ACC_LOGIN_RESULT_DATA* data );
 	
    };

}
#endif