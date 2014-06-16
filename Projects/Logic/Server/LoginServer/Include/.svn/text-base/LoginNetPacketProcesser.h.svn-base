/******************************************************************************/
#ifndef _LOGINNETPACKETPROCESSER_H_
#define _LOGINNETPACKETPROCESSER_H_
/******************************************************************************/

#include "NetAddress.h"
#include "GameNetPacket.h"
#include "LoginNetPacket.h"

/******************************************************************************/
namespace MG
{
	class LoginManager;
	/******************************************************************************/
	//帐号登入消息处理
	/******************************************************************************/
	class LoginNetPacketProcesser
	{
	public:
		SINGLETON_INSTANCE(LoginNetPacketProcesser);
		
		Bool	processClientPacket(I32 id,NetEventRecv* packet);
		Bool	processFrontServerPacket(I32 id,NetEventRecv* packet);
	
	//************************************************************

	//@{ FrontServer
	public:
		//发送FrontServer登入结果消息
		void	sendFrontServerLoginResult(I32 id, I8 result=0);
		//发送客户端登入FrontServer结果消息
		void	sendClientLoginFrontServerResult(I32 id, I32 clientNetID, Char16* accName, Char16* accPsw, U64 accID, I8 result=0);
		///检测客户端是否还在FrontSrrver
		void	sendCheckClientInFrontServer(I32 frontServerId,I32 clientNetIdInFs,I32 clientNetIdInLs);
		//重复登录 通知FrontServer 踢出玩家
		//void    sendFrontServerKickoutClient(I32 frontServerId,I32 clientNetIdInFs);
	protected:
		//当FrontServer登入事件
		void	onFrontServerLogin(I32 id, PT_LOGIN_F2L_LOGIN_DATA* data);
		//当客户端登入FrontServer事件
		void	onClientLoginFrontServer(I32 id, PT_LOGIN_F2L_CLIENT_LOGIN_DATA* data);
		//当客户端登出FrontServer事件
		void	onClientLogoutFrontServer(PT_LOGIN_F2L_CLIENT_LOGOUT_DATA* data);
		//当收到Front检测客户端是否还在
		void	onCheckClientInFrontServerResult(PT_LOGIN_F2L_CHECK_INFRONTSERVER_RESULT_DATA* data);
		
	//@ }

	//************************************************************

	//@{ Client
	public:
		//发送客户端登入错误结果
		void	sendLoginErrorPacketToClient(I32 id, I8 errorResult);
		//发送客户端登入成功结果
		void	sendLoginSuccessPacketToClient(I32 id, CChar* ip, I32 port);
		///发送登陆情况给客户端
		//void	sendLoginQueueInfoToClient(I32 netId,Byte type,I32 waitCount = 0);
		void	sendClientLoginErrVersionInfo(I32 id,Char8* errorInfo,I32 errorInfoSize);
	protected:
		//当客户端登入LoginServer事件
		void	onClientLogin(I32 id, PT_LOGIN_C2L_LOGIN_DATA* data);
	//@ }

	};
}
#endif