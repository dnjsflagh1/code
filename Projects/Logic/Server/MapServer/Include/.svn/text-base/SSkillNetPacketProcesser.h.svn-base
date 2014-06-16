/******************************************************************************/
#ifndef _SSKILLNETPACKETPROCESSER_H_
#define _SSKILLNETPACKETPROCESSER_H_
/******************************************************************************/

#include "SkillNetPacket.h"
#include "MapServerPreqs.h"

/******************************************************************************/
namespace MG
{

	class SSkillNetPacketProcesser
	{
	public:
		SINGLETON_INSTANCE(SSkillNetPacketProcesser);
		SSkillNetPacketProcesser();
		virtual ~SSkillNetPacketProcesser();

		Bool	processFrontServerPacket(I32 id, NetEventRecv* packet);

	public:

		// 当收到角色学习技能消息
		void    onRecvPlayerCharacterLearnSkill(I32 id, PT_SKILL_F2M_LEARN_DATA* data);

        // 当收到吟唱技能从前端服务器
		void	onRecvPlayCharacterClantSkillFromFrontServer(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_PLAYERCHARACTER_CLANT_DATA* data);

        		// 当收到瞬发技能从前端服务器
		void	onRecvPlayCharacterInjectEmitterSkill(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_PLAYERCHARACTER_INJECT_EMITTER_DATA* data);
		// 当收到点技能从前端服务器
		void	onRecvPlayCharacterInjectPointSkill(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_PLAYERCHARACTER_INJECT_POINT_DATA* data);
		// 当收到对象技能从前端服务器
		void	onRecvPlayCharacterInjectObjectSkill(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_PLAYERCHARACTER_INJECT_OBJECT_DATA* data);

		void	onRecvPlayCharacterInjectEndSkill(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_PLAYERCHARACTER_END_INJECT_DATA* data);

		void	sendMonsterInjectSkillToClient( SMonster* monster, SSkillObject* skillObject ); 

		void	onRecvTroopUseSkill(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2S_TROOP_USE_SKILL_DATA* data);
		// 当收到吟唱技能从前端服务器
		void	onRecvTroopClantSkillFromFrontServer(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_TROOP_CLANT_DATA* data);
		// 当收到瞬发技能从前端服务器
		void	onRecvTroopInjectEmitterSkill(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_TROOP_INJECT_EMITTER_DATA* data);
		// 当收到点技能从前端服务器
		void	onRecvTroopInjectPointSkill(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_TROOP_INJECT_POINT_DATA* data);
		// 当收到对象技能从前端服务器
		void	onRecvTroopInjectObjectSkill(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_TROOP_INJECT_OBJECT_DATA* data);

	public:
		// 当收到吟唱技能从前端服务器
		void	onRecvBuildingClantSkillFromFrontServer(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_BUILDING_CLANT_DATA* data);
		// 当收到瞬发技能从前端服务器
		void	onRecvBuildingInjectEmitterSkill(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_BUILDING_INJECT_EMITTER_DATA* data);
		// 当收到点技能从前端服务器
		void	onRecvBuildingInjectPointSkill(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_BUILDING_INJECT_POINT_DATA* data);
		// 当收到对象技能从前端服务器
		void	onRecvBuildingInjectObjectSkill(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_BUILDING_INJECT_OBJECT_DATA* data);

		//接受技能击中包
		void    onRecvPlaycharacterAffectCollisonPlaycharacter(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA* data); 

		void    onRecvPlaycharacterAffectCollisonTroop(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_TROOP_DATA* data); 

		void    onRecvPlaycharacterAffectCollisonBuilding(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_BUILDING_DATA* data);

		void    onRecvPlaycharacterAffectCollisonMonster(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_MONSTER_DATA* data); 

		void    onRecvTroopAffectCollisonPlaycharacter(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_TROOP_AFFECT_COLLISION_PLAYERCHARACTER_DATA* data); 

		void    onRecvTroopAffectCollisonTroop(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_TROOP_AFFECT_COLLISION_TROOP_DATA* data); 

		void    onRecvTroopAffectCollisonBuilding(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_TROOP_AFFECT_COLLISION_BUILDING_DATA* data);

		void    onRecvTroopAffectCollisonMonster(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_TROOP_AFFECT_COLLISION_MONSTER_DATA* data);

		void    onRecvBuildingAffectCollisonPlaycharacter(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_PLAYERCHARACTER_DATA* data); 

		void    onRecvBuildingAffectCollisonTroop(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_TROOP_DATA* data); 

		void    onRecvBuildingAffectCollisonBuilding(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_BUILDING_DATA* data); 

		void    onRecvBuildingAffectCollisonMonster(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_MONSTER_DATA* data); 

		void    onRecvMonsterAffectCollisonPlaycharacter(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA* data); 

		void    onRecvMonsterAffectCollisonTroop(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_TROOP_DATA* data); 

		void    onRecvMonsterAffectCollisonBuilding(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_BUILDING_DATA* data);

		void    onRecvMonsterAffectCollisonMonster(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_MONSTER_DATA* data);

		void	onRecvSkillSummonBuilding(I32 id, PT_SKILL_C2M_SUMMON_BUILDING_DATA* data);
	};
}

#endif