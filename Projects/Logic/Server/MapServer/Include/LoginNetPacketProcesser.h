/******************************************************************************/
#ifndef _LOGIN_NET_PACKET_PROCESSER_H_
#define _LOGIN_NET_PACKET_PROCESSER_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "GameNetEvent.h"
#include "LoginNetPacket.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //服务器间登陆相关网络消息处理
	//客户端登陆相关消息处理
    /******************************************************************************/
    class LoginNetPacketProcesser
    {
    public:
        SINGLETON_INSTANCE(LoginNetPacketProcesser);
        LoginNetPacketProcesser();
        ~LoginNetPacketProcesser();

        Bool	processFrontServerPacket(I32 id, NetEventRecv* packet);

    public:

        //一些具体处理包方法


		//当收到Front检测客户端是否还在
		void	onCheckClientInFrontServerResult(PT_LOGIN_F2M_CHECK_INFRONTSERVER_RESULT_DATA* data);

		// 此协议已经废弃（需确认，暂时注释）
		//void	onRecvMapListFromFrontServer( I32 id, PT_F2M_MAPLIST_DATA* data);
        //一些具体发送包方法

		///检测客户端是否还在FrontSrrver
		void	sendCheckClientInFrontServer(I32 frontServerId,I32 clientNetIdInFs);


    };

}


#endif	//_LOGIN_NET_PACKET_PROCESSER_H_