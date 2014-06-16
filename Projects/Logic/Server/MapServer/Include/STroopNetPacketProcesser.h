/******************************************************************************/
#ifndef _STROOPNETPACKETPROCESSER_H_
#define _STROOPNETPACKETPROCESSER_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "TroopNetPacket.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	//角色相关网络消息处理
	/******************************************************************************/
	class STroopNetPacketProcesser
	{
	public:
		SINGLETON_INSTANCE(STroopNetPacketProcesser);
		STroopNetPacketProcesser();
		~STroopNetPacketProcesser();

		Bool	processFrontServerPacket(I32 id, NetEventRecv* packet);
		Bool	processMapServerPacket(I32 id, NetEventRecv* packet);

	public:
		//一些具体发送包方法
        //发送角色伤害包给客户端
        //void sendTroopDamageToClient( STroopNew* troopObj, DamageType reducetype, UInt val );
        //发送角色伤害包给mapserver
        //void sendTroopDamageToFrontServer( STroopNew* troopObj, AttackType attackType, DamageType reducetype, UInt val  );

		void onRecvTroopSoldierMove(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_TROOP_SOLDIER_C2S_MOVE_POS_DATA* data);
		void onRecvTroopSoldierStopMove(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_TROOP_SOLDIER_C2S_STOP_MOVE_DATA* data);

		void onRecvTroopMove(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_TROOP_C2S_MOVE_POS_DATA* data);
		void onRecvTroopStopMove(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_TROOP_C2S_STOP_MOVE_DATA* data);

		void broadcastTroopEnterFight(STroop* troop);
		void broadcastTroopEndFight(STroop* troop);

		
	protected:
		//一些具体处理包方法
		void onRecvTroopJumpRegion(I32 id, PT_TROOP_GROUP_F2M_JUMP_REGION_DATA* data);

        //void    onRecvTroopAttrFormFrontServer( I32 id, PT_TROOP_F2M_ATTR_DATA* data);

		void broadcastTroopMove(SRegionObjectBase* region, GameObjectIndexIdInSceneType troopIndex, NetVec2 startMovePos, NetVec2 endMovePos, Bool isBlockCheck, SPlayer* owner = NULL);
		void broadcastTroopStopMove(SRegionObjectBase* region, GameObjectIndexIdInSceneType troopIndex, SPlayer* owner = NULL);
		void broadcastTroopSoldierMove(SRegionObjectBase* region, GameObjectIndexIdInSceneType troopId, Byte troopSoldierIndex, NetVec2 startMovePos, NetVec2 endMovePos, SPlayer* owner = NULL);
		void broadcastTroopSoldierStopMove(SRegionObjectBase* region, GameObjectIndexIdInSceneType troopId, Byte troopSoldierIndex, SPlayer* owner = NULL);

	};

}


#endif	//_STROOPNETPACKETPROCESSER_H_