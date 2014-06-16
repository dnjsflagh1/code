/******************************************************************************/
#ifndef _PLAYERCHARACTERNETPACKETPROCESSER_H__
#define _PLAYERCHARACTERNETPACKETPROCESSER_H__
/******************************************************************************/

#include "ClientPreqs.h"
#include "NetAddress.h"
#include "GameNetEvent.h"
#include "PlayerCharacterNetPacket.h"

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

		Bool	processFrontServerPacket(CClient* client,NetEventRecv* packet);

        // 发送到NetPacketPackManager缓冲区中打包发送
		void	sendPlayerCharacterMoveToPackBuffer(CClient* client,IdType id, Vec3 startMovePos, Vec3 endMovePos);
		void	sendPlayerCharacterMove(I32 frontServerNetId,IdType id, Vec3 startMovePos, Vec3 endMovePos);
		void	sendPlayerCharacterJumpRegion(I32 frontServerNetId,IdType playerCharacterId,IdType toRegionId,REGION_OBJ_TYPE toRegionType, InstanceIdType instanceId,Int pointId = 0);

		void	onRecvPlayerCharacterMove( CClient* client, PT_PLAYERCHARACTER_S2C_MOVE_POS_DATA* data );
		void	onRecvPlayerCharacterJumpRegion(CClient* client, PT_PLAYERCHARACTER_F2C_JUMP_REGION_DATA* data);
		//void    onRecvSyncPlayerCharacterDamage(CClient* client, PT_PLAYERCHARACTER_S2C_DAMAGE_DATA* data);
		//void    onRecvPlayerCharacterDamage(CClient* client, PT_PLAYERCHARACTER_F2C_DAMAGE_DATA* data); 
		void    onRecvPlayerCharacterSkillInfo(CClient* client, PT_PLAYERCHARACTER_F2C_SKILL_INFO_DATA* data);
		//void    onRecvPlayerCharacterJumpRegionError(CClient* client, PT_PLAYERCHARACTER_F2C_JUMP_REGION_ERROR_DATA* data);

	private:
		void	sendPlayerCharacterPackBuffer(I32 frontServerNetId,IdType id);
		
	};
}

#endif