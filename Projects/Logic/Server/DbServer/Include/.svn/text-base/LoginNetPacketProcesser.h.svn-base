/******************************************************************************/
#ifndef _LOGINETPACKETPROCESSER_H_
#define _LOGINETPACKETPROCESSER_H_
/******************************************************************************/
#include "DbNetPacket.h"
/******************************************************************************/

namespace MG
{
	class LoginNetPacketProcesser
	{
	public:
		SINGLETON_INSTANCE(LoginNetPacketProcesser);
		LoginNetPacketProcesser();
		~LoginNetPacketProcesser();

		Bool	processLoginServerPacket(I32 id, NetEventRecv* packet);	
		void	onLoginServerSelAccount(I32 id, PT_DB_S2D_SEL_ACCOUNT_DATA* data);
		void	sendSelAccountResultToLoginServer(PackAccountSelRelultData* data,I32 accCount);
	 };
}
#endif