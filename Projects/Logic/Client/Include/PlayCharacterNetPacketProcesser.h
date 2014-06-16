/******************************************************************************/
#ifndef _PLAYERCHARACTERNETPACKETPROCESSER_H_
#define _PLAYERCHARACTERNETPACKETPROCESSER_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "NetAddress.h"
#include "GameNetEvent.h"
#include "PlayerCharacterNetPacket.h"
#include "MapListCsv.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//角色消息分派对象
	/******************************************************************************/
	class PlayCharacterNetPacketProcesser
	{
	public:
		SINGLETON_INSTANCE(PlayCharacterNetPacketProcesser)

		Bool	processFrontServerPacket(I32 id,NetEventRecv* packet);

        // 发送到NetPacketPackManager缓冲区中打包发送
		void	sendPlayerCharacterMoveToPackBuffer(GameObjectIndexIdInSceneType id, Vec3 startMovePos, Vec3 endMovePos, Bool isBlockCheck);
		void	sendPlayerCharacterMove(GameObjectIndexIdInSceneType id, Vec3 startMovePos, Vec3 endMovePos);

		void	sendPlayerCharacterStopMoveToPackBuffer(GameObjectIndexIdInSceneType id);

		//跳入指定MapServer服务器的新手村
		void	sendPlayerCharacterJumpTiroRegion(NetIdType mapServerNetId, PlayerCharacterIdType playerCharacterId, REGION_OBJ_TYPE toRegionType, RegionIdType toRegionId, InstanceUIdType instanceUId, Int pointId = 0);
		
		//跳地图
		void	sendPlayerCharacterJumpRegion(PlayerCharacterIdType playerCharacterId, REGION_OBJ_TYPE regionType, RegionIdType toRegionId, InstanceUIdType instanceUId, Int pointId = 0);
		
		//提供给UI的跳转地图接口， 底层调用sendPlayerCharacterJumpRegion
		void	jumpMapForUI(PlayerCharacterIdType playerCharacterId, MapType mapType, RegionIdType mapId, InstanceUIdType instanceId, Int pointId = 0);
		
		//跳大地图
		void	sendPlayerCharacterJumpOutRegion();
		void	sendPlayerCharacterJumpOutRegion(AccountIdType accountId, PlayerCharacterIdType playerCharacterId);


		//跳回上一个地图
		void	sendPlayerCharacterJumpLastRegion(PlayerCharacterIdType playerCharacterId);
		

		void	onRecvPlayerCharacterMove( I32 id, PT_PLAYERCHARACTER_S2C_MOVE_POS_DATA* data );
		void	onRecvPlayerCharacterStopMove( I32 id, PT_PLAYERCHARACTER_S2C_STOP_MOVE_DATA* data );

		void	onRecvPlayerCharacterJumpRegion(I32 id, PT_PLAYERCHARACTER_F2C_JUMP_REGION_DATA* data);
		//void    onRecvSyncPlayerCharacterDamage(I32 id, PT_PLAYERCHARACTER_S2C_DAMAGE_DATA* data);
		//void    onRecvPlayerCharacterDamage(I32 id, PT_PLAYERCHARACTER_F2C_DAMAGE_DATA* data); 

		void    onRecvPlayerCharacterSkillInfo(I32 id, PT_PLAYERCHARACTER_F2C_SKILL_INFO_DATA* data);

		void    onRecvPlayerCharacterEnterFight(I32 id, PT_PLAYERCHARACTER_S2C_ENTER_FIGHT_DATA* data);

		void    onRecvPlayerCharacterEndFight(I32 id, PT_PLAYERCHARACTER_S2C_END_FIGHT_DATA* data);


	private:
		void	sendPlayerCharacterPackBuffer(IdType id);
		
	};
}

#endif