/******************************************************************************/
#ifndef _SMONSTERNETPACKETPROCESSER_H_
#define _SMONSTERNETPACKETPROCESSER_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "LoginNetPacket.h"
#include "MonsterNetPacket.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	//��ɫ���������Ϣ����
	/******************************************************************************/
	class SMonsterNetPacketProcesser
	{
	public:
		SINGLETON_INSTANCE(SMonsterNetPacketProcesser);
		SMonsterNetPacketProcesser();
		~SMonsterNetPacketProcesser();

		Bool	processFrontServerPacket(I32 id, NetEventRecv* packet);
		Bool	processMapServerPacket(I32 id, NetEventRecv* packet);

	public:
	
		//�㲥��ɫ�ƶ���Ϣ
		void	broadcastMonsterMove(SMonster* monster, NetVec2 startMovePos, NetVec2 endMovePos);

		void	broadcastInstantMonsterMove(SMonster* monster, NetVec2 moveToPos );

		void	broadcastMonsterStopMove(SMonster* monster);

		void	broadcastMonsterEnterFight(SMonster* monster);

		void	broadcastMonsterEndFight(SMonster* monster);


		//////////////////////////////////////////////////////////////////////////
		void   sendMonsterBeKilledByPlayerCharacter(I32 id, MonsterIdType monsterID, PlayerCharacterIdType playerCharacterId,PlayerIdType playerID,
			NetIdType clientIdInFrontServer);

	protected:

	};

}


#endif