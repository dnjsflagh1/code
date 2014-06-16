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
	//�ʺŵ�����Ϣ����
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
		//����FrontServer��������Ϣ
		void	sendFrontServerLoginResult(I32 id, I8 result=0);
		//���Ϳͻ��˵���FrontServer�����Ϣ
		void	sendClientLoginFrontServerResult(I32 id, I32 clientNetID, Char16* accName, Char16* accPsw, U64 accID, I8 result=0);
		///���ͻ����Ƿ���FrontSrrver
		void	sendCheckClientInFrontServer(I32 frontServerId,I32 clientNetIdInFs,I32 clientNetIdInLs);
		//�ظ���¼ ֪ͨFrontServer �߳����
		//void    sendFrontServerKickoutClient(I32 frontServerId,I32 clientNetIdInFs);
	protected:
		//��FrontServer�����¼�
		void	onFrontServerLogin(I32 id, PT_LOGIN_F2L_LOGIN_DATA* data);
		//���ͻ��˵���FrontServer�¼�
		void	onClientLoginFrontServer(I32 id, PT_LOGIN_F2L_CLIENT_LOGIN_DATA* data);
		//���ͻ��˵ǳ�FrontServer�¼�
		void	onClientLogoutFrontServer(PT_LOGIN_F2L_CLIENT_LOGOUT_DATA* data);
		//���յ�Front���ͻ����Ƿ���
		void	onCheckClientInFrontServerResult(PT_LOGIN_F2L_CHECK_INFRONTSERVER_RESULT_DATA* data);
		
	//@ }

	//************************************************************

	//@{ Client
	public:
		//���Ϳͻ��˵��������
		void	sendLoginErrorPacketToClient(I32 id, I8 errorResult);
		//���Ϳͻ��˵���ɹ����
		void	sendLoginSuccessPacketToClient(I32 id, CChar* ip, I32 port);
		///���͵�½������ͻ���
		//void	sendLoginQueueInfoToClient(I32 netId,Byte type,I32 waitCount = 0);
		void	sendClientLoginErrVersionInfo(I32 id,Char8* errorInfo,I32 errorInfoSize);
	protected:
		//���ͻ��˵���LoginServer�¼�
		void	onClientLogin(I32 id, PT_LOGIN_C2L_LOGIN_DATA* data);
	//@ }

	};
}
#endif