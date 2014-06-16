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

		Bool	processFrontServerPacket(CClient* client, NetEventRecv* packet);


		//军队跳转地图
		void	sendTroopGroupJumpRegion(I32 frontServerNetId,IdType troopId, IdType toRegionId,REGION_OBJ_TYPE toRegionType);

		//军队移动
		//void	sendTroopGroupMoveToPackBuffer(CClient* client,IdType troopId, Vec3 pos){};
		void	sendTroopEntityMoveToPackBuffer(CClient* client, REGION_OBJ_TYPE regionType,  RegionIdType regionId, InstanceUIdType instanceUid, IdType troopId, Vec3 startMovePos, Vec3 endMovePos );

		void	sendTroopGroupMove(I32 frontServerNetId,IdType troopId, Vec3 pos);

		void	sendTroopGroupMoveToObject(I32 frontServerNetId,IdType troopGroupId, IdType targetId, GAMEOBJ_TYPE targetType, Flt radius, Bool isCommand);

		void    sendTroopGroupYawToDir(I32 frontServerNetId,IdType troopGroupId, Vec3 dir);

		void	sendTroopEntityStopMoveToPackBuffer(CClient* client, REGION_OBJ_TYPE regionType,  RegionIdType regionId, InstanceUIdType instanceUid, IdType troopId );
		void    sendTroopGroupStopMove(I32 frontServerNetId,IdType troopGroupId);

		void	sendTroopMoveToObject(I32 frontServerNetId,IdType troopGroupId, Int troopIndex, IdType targetId, Int targetIndex, GAMEOBJ_TYPE targetType, Flt radius, Bool isCommand);

		void	sendTroopSoldierMove(I32 frontServerNetId, IdType troopId, Int troopIndex, Vec3 startMovePos, Vec3 endMovePos );

		void    sendTroopSoldierMoveToPackBuffer(CClient* client, REGION_OBJ_TYPE regionType,  RegionIdType regionId, InstanceUIdType instanceUid, IdType troopId, Int troopIndex, Vec3 startMovePos, Vec3 endMovePos );

		void    sendTroopSoldierStopMoveToPackBuffer(CClient* client, REGION_OBJ_TYPE regionType,  RegionIdType regionId, InstanceUIdType instanceUid, IdType troopId, Int troopIndex );

		//军队小组移动
		//void	sendTroopSoldierMove(IdType troopId, Byte troopIndex, Vec3 pos);

		void	onRecvTroopEntityMove( CClient* client, PT_TROOP_S2C_MOVE_POS_DATA* data );
		void	onRecvTroopGroupMoveToObject( CClient* client, PT_TROOP_GROUP_S2C_MOVE_OBJECT_DATA* data );
		void	onRecvTroopGroupYawToDir( CClient* client, PT_TROOP_GROUP_S2C_YAW_DIR_DATA* data );
		void	onRecvTroopEntityStopMove( CClient* client, PT_TROOP_S2C_STOP_MOVE_DATA* data );
		void	onRecvTroopMoveToObject( CClient* client, PT_TROOP_S2C_MOVE_OBJECT_DATA* data );
		void	onRecvTroopSoldierMove( CClient* client, PT_TROOP_SOLDIER_S2C_MOVE_POS_DATA* data );
		void	onRecvTroopSoldierStopMove( CClient* client, PT_TROOP_SOLDIER_S2C_STOP_MOVE_DATA* data );


		void    onRecvTroopSkillInfo(CClient* client, PT_TROOP_GROUP_F2C_SKILL_INFO_DATA* data);

	};
}

#endif //_TROOPNETPACKETPROCESSER_H_
