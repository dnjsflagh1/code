/******************************************************************************/
#ifndef _SKILLNETPACKETPROCESSER_H_
#define _SKILLNETPACKETPROCESSER_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "SkillNetPacket.h"
#include "GameNetEvent.h"	
/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //技能网络消息处理
    /******************************************************************************/
	class SkillNetPacketProcesser
	{
	public:
		SkillNetPacketProcesser();
		~SkillNetPacketProcesser();
		SINGLETON_INSTANCE(SkillNetPacketProcesser)

		Bool	processFrontServerPacket(CClient* client,NetEventRecv* packet);

	public:

		//发送学习技能请求包
		//void	sendLearnSkillRequestPacket(CSkillManagerForCharacter* skillMgr, IdType skillid);

		//发送吟唱技能请求包
        void	sendPlayCharacterClantSkillRequestPacketToPackBuffer(CClient* client);
		void	sendPlayCharacterClantSkillRequestPacket(CClient* client,CSkillObject* skillObject);

        //发送释放技能请求包
        void	sendPlayCharacterInjectSkillRequestPacketToPackBuffer(CClient* client);
        void	sendPlayCharacterInjectSkillRequestPacket(CClient* client,CSkillObject* skillObject);

		//发送中断发射技能包
        void	sendPlayCharacterEndInjectSkillPacketToPackBuffer(CClient* client);
		void	sendPlayCharacterEndInjectSkillPacket(CClient* client,CSkillObject* skillObject);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//发送吟唱技能请求包
		void	sendMonsterClantSkillRequestPacketToPackBuffer(CClient* client,CSkillObject* skillObject);

		//发送释放技能请求包
		void	sendMonsterInjectSkillRequestPacketToPackBuffer(CClient* client,CSkillObject* skillObject);

		//发送中断发射技能包
		void	sendMonsterEndInjectSkillPacketToPackBuffer(CClient* client,CSkillObject* skillObject);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////


		//发送吟唱技能请求包
        void	sendTroopClantSkillRequestPacketToPackBuffer(CClient* client,CSkillObject* skillObject);
		void	sendTroopClantSkillRequestPacket(CClient* client,CSkillObject* skillObject);

		//发送释放技能请求包
        void	sendTroopInjectSkillRequestPacketToPackBuffer(CClient* client,CSkillObject* skillObject);
		void	sendTroopInjectSkillRequestPacket(CClient* client,CSkillObject* skillObject);

		//发送中断发射技能包
        void	sendTroopEndInjectSkillPacketToPackBuffer(CClient* client,CSkillObject* skillObject);
		void	sendTroopEndInjectSkillPacket(CClient* client,CSkillObject* skillObject);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//发送吟唱技能请求包
        void	sendBuildingClantSkillRequestPacketToPackBuffer(CClient* client,CSkillObject* skillObject){};
		void	sendBuildingClantSkillRequestPacket(CClient* client,CSkillObject* skillObject);

		//发送释放技能请求包
        void	sendBuildingInjectSkillRequestPacketToPackBuffer(CClient* client,CSkillObject* skillObject){};
		void	sendBuildingInjectSkillRequestPacket(CClient* client,CSkillObject* skillObject);

		//发送中断发射技能包
        void	sendBuildingEndInjectSkillPacketToPackBuffer(CClient* client,CSkillObject* skillObject){};
		void	sendBuildingEndInjectSkillPacket(CClient* client,CSkillObject* skillObject);


		////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//发送技能碰撞包
		//void    sendSkillCharacterCollisionAffectCharacter(GAMEOBJ_TYPE injectCharacterType, CCharacter* injectCharacter, GAMEOBJ_TYPE affectCharacterType, CCharacterSceneEntity* affectCharacter, UInt affectTotal, IdType skillId, IdType mapId);

		void	sendSkillPlayerCharacterCollisionAffectPlayerCharacterPacket(CClient* client);

		void	sendSkillPlayerCharacterCollisionAffectTroopPacket(CClient* client,IdType injectCharacterId, IdType affectTroopId, UInt affectSoldierIndex, UInt affectTotal, IdType skillId);

		void	sendSkillPlayerCharacterCollisionAffectBuildingPacket(CClient* client,IdType injectCharacterId, IdType affectBuildingId, UInt affectTotal, IdType skillId, IdType mapId);

		void	sendSkillPlayerCharacterCollisionAffectMonsterPacket(CClient* client,IdType injectCharacterId, IdType affectMonsterId, UInt affectTotal, IdType skillId);

		void	sendSkillTroopCollisionAffectTroopPacket(CClient* client,IdType injectTroopId, UInt injectSoldierIndex, IdType affectTroopId, UInt affectSoldierIndex, UInt affectTotal, IdType skillId);

		void	sendSkillTroopCollisionAffectPlayerCharacterPacket(CClient* client,IdType injectTroopId, UInt injectSoldierIndex, IdType affectCharacterId, UInt affectTotal, IdType skillId);

		void	sendSkillTroopCollisionAffectBuildingPacket(CClient* client,IdType injectTroopGroupId, UInt injectTroopId, IdType affectBuildingId, UInt affectTotal, IdType skillId, IdType mapId);

		void	sendSkillTroopCollisionAffectMonsterPacket(CClient* client,IdType injectTroopGroupId, UInt injectTroopId, IdType affectMonsterId, UInt affectTotal, IdType skillId);

		void	sendSkillBuildingCollisionAffectTroopPacket(CClient* client,IdType injectBuildingId, IdType affectTroopGroupId, UInt affectTroopId, UInt affectTotal, IdType skillId);

		void	sendSkillBuildingCollisionAffectPlayerCharacterPacket(CClient* client,IdType injectBuildingId, IdType affectCharacterId, UInt affectTotal, IdType skillId);

		void	sendSkillBuildingCollisionAffectBuildingPacket(CClient* client,IdType injectBuildingId, IdType affecBuildingId, UInt affectTotal, IdType skillId, IdType mapId);

		void	sendSkillBuildingCollisionAffectMonsterPacket(CClient* client,IdType injectBuildingId, IdType affecMonsterId, UInt affectTotal, IdType skillId, IdType mapId);

		void	sendSkillMonsterCollisionAffectPlayerCharacterPacket(CClient* client,IdType injectMonsterId, IdType affectCharacterId, UInt affectTotal, IdType skillId);

		void	sendSkillMonsterCollisionAffectTroopPacket(CClient* client,IdType injectMonsterId, IdType affectTroopId, UInt affectSoldierIndex, UInt affectTotal, IdType skillId);

		void	sendSkillMonsterCollisionAffectBuildingPacket(CClient* client,IdType injectMonsterId, IdType affectBuildingId, UInt affectTotal, IdType skillId, IdType mapId);

		void	sendSkillMonsterCollisionAffectMonsterPacket(CClient* client,IdType injectMonsterId, IdType affectMonsterId, UInt affectTotal, IdType skillId);


		//////////////////////////////////////////////////////////////////////////////////////////////////////////////

		void	sendSkillSummonBuildingPacket(CClient* client,IdType characterId, IdType skillId, IdType mapId, Byte mapType, IdType templateId, NetVec2 pos);

		//接受到吟唱技能要求消息
		void	onRecvPlayCharacterClantSkillRequire(CClient* client, PT_SKILL_M2C_PLAYERCHARACTER_CLANT_DATA* data );


		//接受到释发射体发技能要求消息
		void	onRecvPlayCharacterInjectEmitterSkillRequire(CClient* client, PT_SKILL_M2C_PLAYERCHARACTER_INJECT_EMITTER_DATA* data );
		//接受到释放点技能要求消息
		void	onRecvPlayCharacterInjectPointSkillRequire(CClient* client, PT_SKILL_M2C_PLAYERCHARACTER_INJECT_POINT_DATA* data );
		//接受到释放目标对象技能要求消息
		void	onRecvPlayCharacterInjectObjectSkillRequire(CClient* client, PT_SKILL_M2C_PLAYERCHARACTER_INJECT_OBJECT_DATA* data );

		void	onRecvPlayCharacterInjectEndSkillRequire(CClient* client, PT_SKILL_M2C_PLAYERCHARACTER_END_INJECT_DATA* data );


		//接受到吟唱技能要求消息
		void	onRecvMonsterClantSkillRequire( CClient* client,PT_SKILL_M2C_MONSTER_CLANT_DATA* data );

		//接受到释发射体发技能要求消息
		void	onRecvMonsterInjectEmitterSkillRequire(CClient* client, PT_SKILL_M2C_MONSTER_INJECT_EMITTER_DATA* data );
		//接受到释放点技能要求消息
		void	onRecvMonsterInjectPointSkillRequire( CClient* client,PT_SKILL_M2C_MONSTER_INJECT_POINT_DATA* data );
		//接受到释放目标对象技能要求消息
		void	onRecvMonsterInjectObjectSkillRequire(CClient* client, PT_SKILL_M2C_MONSTER_INJECT_OBJECT_DATA* data );

		void	onRecvMonsterInjectEndSkillRequire(CClient* client, PT_SKILL_M2C_MONSTER_END_INJECT_DATA* data );

		//接受到释放目标对象技能要求消息
		void	onRecvTroopInjectObjectSkillRequire(CClient* client, PT_SKILL_M2C_TROOP_INJECT_OBJECT_DATA* data );

		//接受到释放瞬发技能要求消息
		void	onRecvTroopInjectEmitterSkillRequire(CClient* client, PT_SKILL_M2C_TROOP_INJECT_EMITTER_DATA* data );

	protected:

        //接受到学习技能结果消息
		void	onRecvLearnSkillResult(CClient* client, PT_SKILL_F2C_LEARN_RESULT_DATA* data );

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//接受到吟唱技能要求消息
		void	onRecvTroopClantSkillRequire(CClient* client, PT_SKILL_M2C_TROOP_CLANT_DATA* data );

		//接受到释放点技能要求消息
		void	onRecvTroopInjectPointSkillRequire(CClient* client, PT_SKILL_M2C_TROOP_INJECT_POINT_DATA* data );


		//////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//接受到吟唱技能要求消息
		void	onRecvBuildingClantSkillRequire(CClient* client, PT_SKILL_M2C_BUILDING_CLANT_DATA* data );

		//接受到释放瞬发技能要求消息
		void	onRecvBuildingInjectInstantSkillRequire(CClient* client, PT_SKILL_M2C_BUILDING_INJECT_EMITTER_DATA* data );
		//接受到释放点技能要求消息
		void	onRecvBuildingInjectPointSkillRequire(CClient* client, PT_SKILL_M2C_BUILDING_INJECT_POINT_DATA* data );
		//接受到释放目标对象技能要求消息
		void	onRecvBuildingInjectObjectSkillRequire(CClient* client, PT_SKILL_M2C_BUILDING_INJECT_OBJECT_DATA* data );
	};
}

/******************************************************************************/

#endif
