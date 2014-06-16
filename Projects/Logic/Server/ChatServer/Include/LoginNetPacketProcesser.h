/******************************************************************************/
#ifndef _LOGINNETPACKETPROCESSER_H_
#define _LOGINNETPACKETPROCESSER_H_
/******************************************************************************/
#include "LoginNetPacket.h"
/******************************************************************************/

namespace MG
{
	class LoginNetPacketProcesser
	{
	public:
		SINGLETON_INSTANCE(LoginNetPacketProcesser);
		LoginNetPacketProcesser();
		~LoginNetPacketProcesser();

		Bool	processFrontPacket(I32 id, NetEventRecv* packet);
		// ���ͻ��˽��롢�뿪��Ϸ
		void	onRecvClientJoinGameFromFrontServer(I32 id, PT_LOGIN_F2A_JOINGAME_DATA* data);
		void	onRecvClientExitGameFromFrontServer(I32 id, PT_LOGIN_F2A_EXITGAME_DATA* data);
		void	onRecvClientListInGameFromFrontServer(I32 id, PT_LOGIN_F2A_CLIENTLIST_INGAME_DATA* data);
		
	};
}
#endif //_LOGINNETPACKETPROCESSER_H_