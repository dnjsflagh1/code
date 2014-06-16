/******************************************************************************/
#ifndef _SKILLNETPACKETPROCESSER_H_
#define _SKILLNETPACKETPROCESSER_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "SkillNetPacket.h"
#include "GameNetEvent.h"	
#include "CSkillUseManager.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //����������Ϣ����
    /******************************************************************************/
	class SkillNetPacketProcesser
	{
	public:
		SkillNetPacketProcesser();
		~SkillNetPacketProcesser();
		SINGLETON_INSTANCE(SkillNetPacketProcesser)

		Bool	processFrontServerPacket(I32 id,NetEventRecv* packet);

	public:

		 void	sendCharacterUseSkillPacketToPackBuffer(CSkillObject* skillObject);

		//����ѧϰ���������
		//void	sendLearnSkillRequestPacket(CSkillManagerForCharacter* skillMgr, IdType skillid);

		//�����������������
        void	sendPlayCharacterClantSkillRequestPacketToPackBuffer(CSkillObject* skillObject);
		void	sendPlayCharacterClantSkillRequestPacket(CSkillObject* skillObject);

        //�����ͷż��������
        void	sendPlayCharacterInjectSkillRequestPacketToPackBuffer(CSkillObject* skillObject);
        void	sendPlayCharacterInjectSkillRequestPacket(CSkillObject* skillObject);

		//�����жϷ��似�ܰ�
        void	sendPlayCharacterEndInjectSkillPacketToPackBuffer(CSkillObject* skillObject);
		void	sendPlayCharacterEndInjectSkillPacket(CSkillObject* skillObject);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////

		void	sendTroopUseSkillRequestPacketToPackBuffer(CSkillObject* skillObject);

		//�����������������
        void	sendTroopClantSkillRequestPacketToPackBuffer(CSkillObject* skillObject);
		void	sendTroopClantSkillRequestPacket(CSkillObject* skillObject);

		//�����ͷż��������
        void	sendTroopInjectSkillRequestPacketToPackBuffer(CSkillObject* skillObject);
		void	sendTroopInjectSkillRequestPacket(CSkillObject* skillObject);

		//�����жϷ��似�ܰ�
        void	sendTroopEndInjectSkillPacketToPackBuffer(CSkillObject* skillObject);
		void	sendTroopEndInjectSkillPacket(CSkillObject* skillObject);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//�����������������
        void	sendBuildingClantSkillRequestPacketToPackBuffer(CSkillObject* skillObject){};
		void	sendBuildingClantSkillRequestPacket(CSkillObject* skillObject);

		//�����ͷż��������
        void	sendBuildingInjectSkillRequestPacketToPackBuffer(CSkillObject* skillObject){};
		void	sendBuildingInjectSkillRequestPacket(CSkillObject* skillObject);

		//�����жϷ��似�ܰ�
        void	sendBuildingEndInjectSkillPacketToPackBuffer(CSkillObject* skillObject){};
		void	sendBuildingEndInjectSkillPacket(CSkillObject* skillObject);


		////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//���ͼ�����ײ��
		void    sendSkillCharacterCollisionAffectCharacter(GAMEOBJ_TYPE injectCharacterType, CCharacterSceneEntity* injectCharacter, GAMEOBJ_TYPE affectCharacterType, CCharacterSceneEntity* affectCharacter, UInt affectTotal, IdType skillId, IdType mapId, Vec3 affectPos = Vec3(0,0,0));

		void	sendSkillPlayerCharacterCollisionAffectPlayerCharacterPacket(GameObjectIndexIdInSceneType injectCharacterIndex, GameObjectIndexIdInSceneType affectCharacterIndex, UInt affectTotal, IdType skillId);

		void	sendSkillPlayerCharacterCollisionAffectTroopPacket(GameObjectIndexIdInSceneType injectCharacterIndex, GameObjectIndexIdInSceneType affectTroopIndex, UInt affectSoldierIndex, UInt affectTotal, IdType skillId);

		void	sendSkillPlayerCharacterCollisionAffectBuildingPacket(GameObjectIndexIdInSceneType injectCharacterIndex, GameObjectIndexIdInSceneType affectBuildingIndex, UInt affectTotal, IdType skillId, IdType mapId);

		void	sendSkillPlayerCharacterCollisionAffectMonsterPacket(GameObjectIndexIdInSceneType injectCharacterIndex, GameObjectIndexIdInSceneType affectMonsterIndex, UInt affectTotal, IdType skillId, Vec3 affectPos);

		void	sendSkillTroopCollisionAffectTroopPacket(GameObjectIndexIdInSceneType injectTroopIndex, UInt injectSoldierIndex, GameObjectIndexIdInSceneType affectTroopIndex, UInt affectSoldierIndex, UInt affectTotal, IdType skillId);

		void	sendSkillTroopCollisionAffectPlayerCharacterPacket(GameObjectIndexIdInSceneType injectTroopIndex, UInt injectSoldierIndex, GameObjectIndexIdInSceneType affectCharacterIndex, UInt affectTotal, IdType skillId);

		void	sendSkillTroopCollisionAffectBuildingPacket(GameObjectIndexIdInSceneType injectTroopIndex, UInt injectSoldierIndex, GameObjectIndexIdInSceneType affectBuildingIndex, UInt affectTotal, IdType skillId, IdType mapId);

		void	sendSkillTroopCollisionAffectMonsterPacket(GameObjectIndexIdInSceneType injectTroopIndex, UInt injectSoldierIndex, IdType affectMonsterIndex, UInt affectTotal, IdType skillId);

		void	sendSkillBuildingCollisionAffectTroopPacket(GameObjectIndexIdInSceneType injectBuildingIndex, GameObjectIndexIdInSceneType affectTroopIndex, UInt affectSoldierIndex, UInt affectTotal, IdType skillId);

		void	sendSkillBuildingCollisionAffectPlayerCharacterPacket(GameObjectIndexIdInSceneType injectBuildingIndex, GameObjectIndexIdInSceneType affectCharacterIndex, UInt affectTotal, IdType skillId);

		void	sendSkillBuildingCollisionAffectBuildingPacket(GameObjectIndexIdInSceneType injectBuildingIndex, GameObjectIndexIdInSceneType affecBuildingIndex, UInt affectTotal, IdType skillId, IdType mapId);

		void	sendSkillBuildingCollisionAffectMonsterPacket(GameObjectIndexIdInSceneType injectBuildingIndex, GameObjectIndexIdInSceneType affecMonsterIndex, UInt affectTotal, IdType skillId, IdType mapId);

		void	sendSkillMonsterCollisionAffectPlayerCharacterPacket(GameObjectIndexIdInSceneType injectMonsterIndex, GameObjectIndexIdInSceneType affectCharacterIndex, UInt affectTotal, IdType skillId);

		void	sendSkillMonsterCollisionAffectTroopPacket(GameObjectIndexIdInSceneType injectMonsterIndex, GameObjectIndexIdInSceneType affectTroopIndex, UInt affectSoldierIndex, UInt affectTotal, IdType skillId);

		void	sendSkillMonsterCollisionAffectBuildingPacket(GameObjectIndexIdInSceneType injectMonsterIndex, GameObjectIndexIdInSceneType affecBuildingIndex, UInt affectTotal, IdType skillId, IdType mapId);

		void	sendSkillMonsterCollisionAffectMonsterPacket(GameObjectIndexIdInSceneType injectMonsterIndex, GameObjectIndexIdInSceneType affecMonsterIndex, UInt affectTotal, IdType skillId);


		//////////////////////////////////////////////////////////////////////////////////////////////////////////////

		void	sendSkillSummonBuildingPacket(IdType characterId, IdType skillId, IdType mapId, Byte mapType, IdType templateId, NetVec2 pos);

		//���ܵ���������Ҫ����Ϣ
		void	onRecvPlayCharacterClantSkillRequire( PT_SKILL_M2C_PLAYERCHARACTER_CLANT_DATA* data );


		//���ܵ��ͷ����巢����Ҫ����Ϣ
		void	onRecvPlayCharacterInjectEmitterSkillRequire( PT_SKILL_M2C_PLAYERCHARACTER_INJECT_EMITTER_DATA* data );
		//���ܵ��ͷŵ㼼��Ҫ����Ϣ
		void	onRecvPlayCharacterInjectPointSkillRequire( PT_SKILL_M2C_PLAYERCHARACTER_INJECT_POINT_DATA* data );
		//���ܵ��ͷ�Ŀ�������Ҫ����Ϣ
		void	onRecvPlayCharacterInjectObjectSkillRequire( PT_SKILL_M2C_PLAYERCHARACTER_INJECT_OBJECT_DATA* data );

		void	onRecvPlayCharacterInjectEndSkillRequire( PT_SKILL_M2C_PLAYERCHARACTER_END_INJECT_DATA* data );


		//���ܵ���������Ҫ����Ϣ
		void	onRecvMonsterClantSkillRequire( PT_SKILL_M2C_MONSTER_CLANT_DATA* data );

		//���ܵ��ͷ����巢����Ҫ����Ϣ
		void	onRecvMonsterInjectEmitterSkillRequire( PT_SKILL_M2C_MONSTER_INJECT_EMITTER_DATA* data );
		//���ܵ��ͷŵ㼼��Ҫ����Ϣ
		void	onRecvMonsterInjectPointSkillRequire( PT_SKILL_M2C_MONSTER_INJECT_POINT_DATA* data );
		//���ܵ��ͷ�Ŀ�������Ҫ����Ϣ
		void	onRecvMonsterInjectObjectSkillRequire( PT_SKILL_M2C_MONSTER_INJECT_OBJECT_DATA* data );

		void	onRecvMonsterInjectEndSkillRequire( PT_SKILL_M2C_MONSTER_END_INJECT_DATA* data );

		//���ܵ��ͷ�Ŀ�������Ҫ����Ϣ
		void	onRecvTroopInjectObjectSkillRequire( PT_SKILL_M2C_TROOP_INJECT_OBJECT_DATA* data );

		//���ܵ��ͷ�˲������Ҫ����Ϣ
		void	onRecvTroopInjectEmitterSkillRequire( PT_SKILL_M2C_TROOP_INJECT_EMITTER_DATA* data );

		//���ܵ��ͷŵ㼼��Ҫ����Ϣ
		void	onRecvTroopInjectPointSkillRequire( PT_SKILL_M2C_TROOP_INJECT_POINT_DATA* data );


		void	onRecvTroopUseSkillRequire( PT_SKILL_S2C_TROOP_USE_SKILL_DATA* data );

	protected:

        //���ܵ�ѧϰ���ܽ����Ϣ
		void	onRecvLearnSkillResult( PT_SKILL_F2C_LEARN_RESULT_DATA* data );

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//���ܵ���������Ҫ����Ϣ
		void	onRecvTroopClantSkillRequire( PT_SKILL_M2C_TROOP_CLANT_DATA* data );




		//////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//���ܵ���������Ҫ����Ϣ
		void	onRecvBuildingClantSkillRequire( PT_SKILL_M2C_BUILDING_CLANT_DATA* data );

		//���ܵ��ͷ�˲������Ҫ����Ϣ
		void	onRecvBuildingInjectInstantSkillRequire( PT_SKILL_M2C_BUILDING_INJECT_EMITTER_DATA* data );
		//���ܵ��ͷŵ㼼��Ҫ����Ϣ
		void	onRecvBuildingInjectPointSkillRequire( PT_SKILL_M2C_BUILDING_INJECT_POINT_DATA* data );
		//���ܵ��ͷ�Ŀ�������Ҫ����Ϣ
		void	onRecvBuildingInjectObjectSkillRequire( PT_SKILL_M2C_BUILDING_INJECT_OBJECT_DATA* data );
	};
}

/******************************************************************************/

#endif
