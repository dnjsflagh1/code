/******************************************************************************/
#ifndef _TROOPNETPACKETPROCESSER_H_
#define _TROOPNETPACKETPROCESSER_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "TroopNetPacket.h"
#include "GameNetEvent.h"

/******************************************************************************/
namespace MG
{
	class TroopNetPacketProcesser
	{
		SINGLETON_INSTANCE(TroopNetPacketProcesser)

		Bool	processFrontServerPacket(I32 id, NetEventRecv* packet);


		//������ת��ͼ
		void	sendTroopGroupJumpRegion(IdType troopId, IdType toRegionId,REGION_OBJ_TYPE toRegionType);

		//�����ƶ�
        void	sendTroopEntityMoveToPackBuffer( GameObjectIndexIdInSceneType troopIndex, Vec3 startMovePos, Vec3 endMovePos, Bool isBlockCheck );

		void	sendTroopEntityStopMoveToPackBuffer( GameObjectIndexIdInSceneType troopIndex );

		void	sendTroopSoldierMove( GameObjectIndexIdInSceneType troopIndex, Int soldierIndex, Vec3 startMovePos, Vec3 endMovePos );

		void    sendTroopSoldierMoveToPackBuffer( GameObjectIndexIdInSceneType troopIndex, Int soldierIndex, Vec3 startMovePos, Vec3 endMovePos );

		void    sendTroopSoldierStopMoveToPackBuffer( GameObjectIndexIdInSceneType troopIndex, Int soldierIndex );


		//����С���ƶ�
		//void	sendTroopSoldierMove(IdType troopId, Byte troopIndex, Vec3 pos);

		void	onRecvTroopEntityMove( I32 id, PT_TROOP_S2C_MOVE_POS_DATA* data );
		void	onRecvTroopEntityStopMove( I32 id, PT_TROOP_S2C_STOP_MOVE_DATA* data );

		void	onRecvTroopSoldierMove( I32 id, PT_TROOP_SOLDIER_S2C_MOVE_POS_DATA* data );
		void	onRecvTroopSoldierStopMove( I32 id, PT_TROOP_SOLDIER_S2C_STOP_MOVE_DATA* data );


		void    onRecvTroopSkillInfo(I32 id, PT_TROOP_GROUP_F2C_SKILL_INFO_DATA* data);

		void    onRecvTroopEnterFight(I32 id, PT_TROOP_S2C_ENTER_FIGHT_DATA* data);
		void    onRecvTroopEndFight(I32 id, PT_TROOP_S2C_END_FIGHT_DATA* data);

	};
}

#endif //_TROOPNETPACKETPROCESSER_H_
