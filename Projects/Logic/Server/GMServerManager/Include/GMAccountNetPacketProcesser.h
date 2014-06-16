/******************************************************************************/
#ifndef _GMACCOUNTNETPACKETPROCESSER_H_
#define _GMACCOUNTNETPACKETPROCESSER_H_
/******************************************************************************/

#include "GMAccountNetPacket.h"
/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //GM帐号相关网络消息处理
    /******************************************************************************/

    class GMAccountNetPacketProcesser
    {
    public:
        SINGLETON_INSTANCE(GMAccountNetPacketProcesser);
        GMAccountNetPacketProcesser();
        ~GMAccountNetPacketProcesser();

        Bool	processGMClientPacket(I32 id, NetEventRecv* packet);

		
	//************************************************************
	public:
		//发送GM登入验证结果给客户端
		void	sendGMClientLoginResult( I32 id, Byte result,Int authority);
		
		//当客户端登入
		void	onGMClientLogin( I32 id, GMPT_CGMM_ACC_LOGIN_DATA* data );
       

    };
}
#endif

