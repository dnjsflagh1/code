/******************************************************************************/
#ifndef _NETPACKETPACKMANAGER_H_
#define _NETPACKETPACKMANAGER_H_
/******************************************************************************/
#include "ClientPreqs.h"
#include "Singleton.h"
#include "GameNetPacket.h"
#include "PackNetPacket.h"
#include "PlayerCharacterNetPacket.h"
#include "TroopNetPacket.h"
/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    // 打包处理管理
    // 
    /******************************************************************************/

	struct TroopC2SMovePosData
	{
		std::map<TroopSoldierIdType, PT_TROOP_SOLDIER_C2S_MOVE_POS_DATA>			troopSoldierMovePakectList;
	};

	struct TroopC2SStopMoveData
	{
		std::map<TroopSoldierIdType, PT_TROOP_SOLDIER_C2S_STOP_MOVE_DATA>			troopSoldierStopMovePakectList;
	};

	struct TroopC2SClantData
	{
		std::map<TroopSoldierIdType, PT_SKILL_C2M_TROOP_CLANT_DATA>					troopSoldierClantPakectList;
	};

	struct TroopC2SEndInjectData
	{
		std::map<TroopSoldierIdType, PT_SKILL_C2M_TROOP_END_INJECT_DATA>			troopSoldierEndInjectPakectList;
	};

	struct TroopC2SInjectObjectData
	{
		std::map<TroopSoldierIdType, PT_SKILL_C2M_TROOP_INJECT_OBJECT_DATA>			troopSoldierInjectObjectPakectList;
	};

	struct TroopC2SInjectEmitterData
	{
		std::map<TroopSoldierIdType, PT_SKILL_C2M_TROOP_INJECT_EMITTER_DATA>		troopSoldierInjectEmitterPakectList;
	};


    class NetPacketPackManager
    {
    public:
        //SINGLETON_INSTANCE(NetPacketPackManager);
        NetPacketPackManager(CClient* client);
        virtual ~NetPacketPackManager();

       
        void																					update( Flt delta );

        ///////////////////////////////////////////////////////////////////

        // 场景对象消息打包

        // @ 注意军队的移动包需要分类刷选
        // @ 注意如果有重复的对象包,则覆盖

        //增加军队移动包
        //增加将领移动包
        //增加军队技能包
        //增加将领技能包

        ///////////////////////////////////////////////////////////////////

        // 每间隔一段时间打包发送
        // 会有多种时间段,需要分类管理发送
        void																					packSend();

		void																					addPacketToBuff(  PackNetPacketType packetType, GAMEOBJ_TYPE gameObjectType, Char8* sendData , GameObjectIdType gameObjectID, Int gameObjectIndex = 0 );

	protected:
		void																					clearMutexPacket( GAMEOBJ_TYPE gameObjectType, GameObjectIdType gameObjectID, Int gameObjectIndex = 0 );
		CClient*																				mClient;
    private:

		std::map<PlayerCharacterIdType, PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA>		mMapPcAffectPc;
		std::map<PlayerCharacterIdType, PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_TROOP_DATA>				mMapPcAffectTp;		
		std::map<PlayerCharacterIdType, PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_BUILDING_DATA>			mMapPcAffectBd;
		std::map<PlayerCharacterIdType, PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_MONSTER_DATA>				mMapPcAffectMt;

		std::map<MonsterIdType, PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA>						mMapMtAffectPc;	
		std::map<MonsterIdType, PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_TROOP_DATA>								mMapMtAffectTp;
		std::map<MonsterIdType, PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_BUILDING_DATA>							mMapMtAffectBd;
		std::map<MonsterIdType, PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_MONSTER_DATA>								mMapMtAffectMt;

		std::map<TroopIdType, PT_SKILL_C2M_TROOP_AFFECT_COLLISION_TROOP_DATA>									mMapTpAffectTp;		
		std::map<TroopIdType, PT_SKILL_C2M_TROOP_AFFECT_COLLISION_PLAYERCHARACTER_DATA>							mMapTpAffectPc;
		std::map<TroopIdType, PT_SKILL_C2M_TROOP_AFFECT_COLLISION_BUILDING_DATA>								mMapTpAffectBd;
		std::map<TroopIdType, PT_SKILL_C2M_TROOP_AFFECT_COLLISION_MONSTER_DATA>									mMapTpAffectMt;

		std::map<BuildingIdType, PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_PLAYERCHARACTER_DATA>				mMapBdAffectPc;
		std::map<BuildingIdType, PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_BUILDING_DATA>					mMapBdAffectBd;
		std::map<BuildingIdType, PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_TROOP_DATA>						mMapBdAffectTp;
		std::map<BuildingIdType, PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_MONSTER_DATA>						mMapBdAffectMt;

		std::map<PlayerCharacterIdType, PT_PLAYERCHARACTER_C2S_MOVE_POS_DATA>					mPlayerCharacterMovePakectList;
		std::map<PlayerCharacterIdType, PT_PLAYERCHARACTER_C2S_STOP_MOVE_DATA>					mPlayerCharacterStopMovePakectList;
		std::map<PlayerCharacterIdType, PT_SKILL_C2M_PLAYERCHARACTER_CLANT_DATA>				mPlayerCharacterClantPakectList;
		std::map<PlayerCharacterIdType, PT_SKILL_C2M_PLAYERCHARACTER_END_INJECT_DATA>			mPlayerCharacterInjectEndPakectList;
		std::map<PlayerCharacterIdType, PT_SKILL_C2M_PLAYERCHARACTER_INJECT_OBJECT_DATA>		mPlayerCharacterInjectObjectPakectList;
		std::map<PlayerCharacterIdType, PT_SKILL_C2M_PLAYERCHARACTER_INJECT_POINT_DATA>			mPlayerCharacterInjectPointPakectList;
		std::map<PlayerCharacterIdType, PT_SKILL_C2M_PLAYERCHARACTER_INJECT_EMITTER_DATA>		mPlayerCharacterInjectEmitterPakectList;

		std::map<MonsterIdType, PT_MONSTER_C2S_MOVE_POS_DATA>									mMonsterMovePakectList;
		std::map<MonsterIdType, PT_MONSTER_C2S_STOP_MOVE_DATA>									mMonsterStopMovePakectList;
		std::map<MonsterIdType, PT_SKILL_C2M_MONSTER_CLANT_DATA>								mMonsterClantPakectList;
		std::map<MonsterIdType, PT_SKILL_C2M_MONSTER_END_INJECT_DATA>							mMonsterInjectEndPakectList;
		std::map<MonsterIdType, PT_SKILL_C2M_MONSTER_INJECT_OBJECT_DATA>						mMonsterInjectObjectPakectList;
		std::map<MonsterIdType, PT_SKILL_C2M_MONSTER_INJECT_POINT_DATA>							mMonsterInjectPointPakectList;
		std::map<MonsterIdType, PT_SKILL_C2M_MONSTER_INJECT_EMITTER_DATA>						mMonsterInjectEmitterPakectList;

		std::map<TroopIdType, TroopC2SMovePosData>												mTroopMovePakectList;
		std::map<TroopIdType, TroopC2SStopMoveData>												mTroopStopMovePakectList;
		std::map<TroopIdType, TroopC2SClantData>												mTroopClantPakectList;
		std::map<TroopIdType, TroopC2SEndInjectData>											mTroopEndInjectPakectList;
		std::map<TroopIdType, TroopC2SInjectObjectData>											mTroopInjectObjectPakectList;
		std::map<TroopIdType, TroopC2SInjectEmitterData>										mTroopInjectEmitterPakectList;

		Flt																						mIntervalTime;
    };

}

/******************************************************************************/

#endif