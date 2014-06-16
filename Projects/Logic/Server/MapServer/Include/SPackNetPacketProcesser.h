/******************************************************************************/
#ifndef _SPACKNETPACKETPROCESSER_H_
#define _SPACKNETPACKETPROCESSER_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "LoginNetPacket.h"
#include "PackNetPacket.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	//��ɫ���������Ϣ����
	/******************************************************************************/
	class SPackNetPacketProcesser
	{
	public:
		SINGLETON_INSTANCE(SPackNetPacketProcesser);
		SPackNetPacketProcesser();
		~SPackNetPacketProcesser();

		Bool	processFrontServerPacket(I32 id, NetEventRecv* packet);
		Bool	processMapServerPacket(I32 id, NetEventRecv* packet);

	public:
		////һЩ���巢�Ͱ�����

		//void sendPlayerCharacterJumpregionResult(SPlayerCharacter* playerCharacter);

		////�㲥��ɫ�ƶ���Ϣ
		//void	broadcastPlayerCharacterMove(SPlayerCharacter* playerCharacter, NetVec2 startMovePos);


	protected:
		//һЩ���崦�������

		void	onRecvCharacterPackFromFrontServer( I32 id , PT_PACK_C2S_CHARACTER_DATA* data);

	protected:
  

	};

}


#endif