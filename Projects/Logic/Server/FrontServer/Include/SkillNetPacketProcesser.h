/******************************************************************************/
#ifndef _SKILLNETPAKCETPROCESSER_H_
#define _SKILLNETPAKCETPROCESSER_H_
/******************************************************************************/


#include "FrontServerPreqs.h"
#include "SkillNetPacket.h"

/******************************************************************************/
namespace MG
{

	class SkillNetPacketProcesser
	{
	public:
		SINGLETON_INSTANCE(SkillNetPacketProcesser);
		SkillNetPacketProcesser();
		~SkillNetPacketProcesser();

		Bool	processClientPacket(I32 id, NetEventRecv* packet);


    public:

        //发送客户端学习技能结果
        void    sendPlayerCharacterLearnSkillResultToClient( I32 id, IdType characterId, IdType skillId, Byte learnResult);

		void    sendPlayerCharacterLearnSkillToMapServer( I32 mapserverNetid, IdType characterId, IdType skillId, UInt skillLevel);

		void	sendPlayCharacterInjectEmitterSkillRequireToPackBuffer( SSkillObject* skillObject );

		void	sendPlayCharacterInjectPointSkillRequireToPackBuffer( SSkillObject* skillObject );
	
		void	sendPlayCharacterInjectObjectSkillRequireToPackBuffer( SSkillObject* skillObject );

		void	sendTroopInjectObjectSkillRequireToPackBuffer( SSkillObject* skillObject );

		void	sendMonsterInjectEmitterSkillRequireToPackBuffer( SSkillObject* skillObject );

		void	sendMonsterInjectPointSkillRequireToPackBuffer( SSkillObject* skillObject );

		void	sendMonsterInjectObjectSkillRequireToPackBuffer( SSkillObject* skillObject );

		//接受到吟唱技能要求消息
		void	onRecvPlayCharacterClantSkillRequire( I32 id, PT_SKILL_C2M_PLAYERCHARACTER_CLANT_DATA* data );

		//接受到中断释放技能要求消息
		void	onRecvPlayCharacterEndInjectSkill( I32 id, PT_SKILL_C2M_PLAYERCHARACTER_END_INJECT_DATA* data );

		//接受到释放目标对象技能要求消息
		void	onRecvPlayCharacterInjectObjectSkillRequire( I32 id, PT_SKILL_C2M_PLAYERCHARACTER_INJECT_OBJECT_DATA* data );

		//接受到释放发射体技能要求消息
		void	onRecvPlayCharacterInjectEmitterSkillRequire( I32 id, PT_SKILL_C2M_PLAYERCHARACTER_INJECT_EMITTER_DATA* data );
		//接受到释放点技能要求消息
		void	onRecvPlayCharacterInjectPointSkillRequire( I32 id, PT_SKILL_C2M_PLAYERCHARACTER_INJECT_POINT_DATA* data );

		//接受到吟唱技能要求消息
		void	onRecvMonsterClantSkillRequire( I32 id, PT_SKILL_C2M_MONSTER_CLANT_DATA* data );

		//接受到中断释放技能要求消息
		void	onRecvMonsterEndInjectSkill( I32 id, PT_SKILL_C2M_MONSTER_END_INJECT_DATA* data );

		//接受到释放目标对象技能要求消息
		void	onRecvMonsterInjectObjectSkillRequire( I32 id, PT_SKILL_C2M_MONSTER_INJECT_OBJECT_DATA* data );

		//接受到释放发射体技能要求消息
		void	onRecvMonsterInjectEmitterSkillRequire( I32 id, PT_SKILL_C2M_MONSTER_INJECT_EMITTER_DATA* data );
		//接受到释放点技能要求消息
		void	onRecvMonsterInjectPointSkillRequire( I32 id, PT_SKILL_C2M_MONSTER_INJECT_POINT_DATA* data );

		//接受到吟唱技能要求消息
		void	onRecvTroopClantSkillRequire( I32 id, PT_SKILL_C2M_TROOP_CLANT_DATA* data );

		//接受到释放发射体技能要求消息
		void	onRecvTroopInjectEmitterSkillRequire( I32 id, PT_SKILL_C2M_TROOP_INJECT_EMITTER_DATA* data );
		//接受到释放点技能要求消息
		void	onRecvTroopInjectPointSkillRequire( I32 id, PT_SKILL_C2M_TROOP_INJECT_POINT_DATA* data );
		//接受到释放目标对象技能要求消息
		void	onRecvTroopInjectObjectSkillRequire( I32 id, PT_SKILL_C2M_TROOP_INJECT_OBJECT_DATA* data );

		//接受到中断释放技能要求消息
		void	onRecvTroopEndInjectSkill( I32 id, PT_SKILL_C2M_TROOP_END_INJECT_DATA* data );

	protected:

		// 当收到角色学习技能消息
		void    onRecvPlayerCharacterLearnSkill(I32 id, PT_SKILL_C2F_LEARN_DATA* data);

		//接受到吟唱技能要求消息
		void	onRecvBuildingClantSkillRequire( I32 id, PT_SKILL_C2M_BUILDING_CLANT_DATA* data );

		//接受到释放发射体技能要求消息
		void	onRecvBuildingInjectEmitterSkillRequire( I32 id, PT_SKILL_C2M_BUILDING_INJECT_EMITTER_DATA* data );
		//接受到释放点技能要求消息
		void	onRecvBuildingInjectPointSkillRequire( I32 id, PT_SKILL_C2M_BUILDING_INJECT_POINT_DATA* data );
		//接受到释放目标对象技能要求消息
		void	onRecvBuildingInjectObjectSkillRequire( I32 id, PT_SKILL_C2M_BUILDING_INJECT_OBJECT_DATA* data );

		//接受到中断释放技能要求消息
		void	onRecvBuildingEndInjectSkill( I32 id, PT_SKILL_C2F_BUILDING_END_INJECT_DATA* data );

		//接受技能击中包
		void    onRecvPlayerCharacterAffectCollisonPlayerCharacter(I32 id, PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA* data);

		void    onRecvPlayerCharacterAffectCollisonTroop(I32 id, PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_TROOP_DATA* data);

		void    onRecvPlayerCharacterAffectCollisonBuilding(I32 id, PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_BUILDING_DATA* data);

		void    onRecvPlayerCharacterAffectCollisonMonster(I32 id, PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_MONSTER_DATA* data);

		void    onRecvMonsterAffectCollisonPlayerCharacter(I32 id, PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA* data);

		void    onRecvMonsterAffectCollisonTroop(I32 id, PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_TROOP_DATA* data);

		void    onRecvMonsterAffectCollisonBuilding(I32 id, PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_BUILDING_DATA* data);

		void    onRecvMonsterAffectCollisonMonster(I32 id, PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_MONSTER_DATA* data);

		void    onRecvTroopAffectCollisonTroop(I32 id, PT_SKILL_C2M_TROOP_AFFECT_COLLISION_TROOP_DATA* data);

		void    onRecvTroopAffectCollisonPlayerCharacter(I32 id, PT_SKILL_C2M_TROOP_AFFECT_COLLISION_PLAYERCHARACTER_DATA* data);

		void    onRecvTroopAffectCollisonBuilding(I32 id, PT_SKILL_C2M_TROOP_AFFECT_COLLISION_BUILDING_DATA* data);

		void    onRecvTroopAffectCollisonMonster(I32 id, PT_SKILL_C2M_TROOP_AFFECT_COLLISION_MONSTER_DATA* data);

		void    onRecvBuildingAffectCollisonBuilding(I32 id, PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_BUILDING_DATA* data);

		void    onRecvBuildingAffectCollisonTroop(I32 id, PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_TROOP_DATA* data);

		void    onRecvBuildingAffectCollisonPlayerCharacter(I32 id, PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_PLAYERCHARACTER_DATA* data);

		void    onRecvBuildingAffectCollisonMonster(I32 id, PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_MONSTER_DATA* data);

		void	onRecvSkillSummonBuilding(I32 id, PT_SKILL_C2M_SUMMON_BUILDING_DATA* data);
	};
}

#endif