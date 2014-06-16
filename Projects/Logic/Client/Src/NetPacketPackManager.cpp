/******************************************************************************/
#include "stdafx.h"
#include "NetPacketPackManager.h"
#include "NetAddress.h"
#include "ClientNetApplyManager.h"
#include "CPlayer.h"
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------------
    NetPacketPackManager::NetPacketPackManager()
		:mIntervalTime(0)
    {
        
    }

    //-----------------------------------------------------------------------------
    NetPacketPackManager::~NetPacketPackManager()
    {

    }


    //-----------------------------------------------------------------------------
    void NetPacketPackManager::update( Flt delta )
    {
		mIntervalTime += delta;
		if(mIntervalTime >= 0)
		{
			packSend();
			mIntervalTime = 0;
		}
    }

	//-----------------------------------------------------------------------------
	void NetPacketPackManager::addPacketToBuff(  PackNetPacketType packetType, GAMEOBJ_TYPE gameObjectType, Char8* sendData , GameObjectIdType gameObjectID, Int gameObjectIndex )
	{

		clearMutexPacket(gameObjectType, gameObjectID, gameObjectIndex);

		if(packetType == PT_PLAYERCHARACTER_MOVE)
		{
			PT_PLAYERCHARACTER_C2S_MOVE_POS_DATA data = *((PT_PLAYERCHARACTER_C2S_MOVE_POS_DATA*)sendData);
			mPlayerCharacterMovePakectList[gameObjectID] = data;
		}
		else if(packetType == PT_PLAYERCHARACTER_STOP_MOVE)
		{
			PT_PLAYERCHARACTER_C2S_STOP_MOVE_DATA data = *((PT_PLAYERCHARACTER_C2S_STOP_MOVE_DATA*)sendData);
			mPlayerCharacterStopMovePakectList[gameObjectID] = data;
		}
		else if(packetType == PT_PLAYERCHARACTER_CLANT)
		{
			PT_SKILL_C2M_PLAYERCHARACTER_CLANT_DATA data = *((PT_SKILL_C2M_PLAYERCHARACTER_CLANT_DATA*)sendData);
			mPlayerCharacterClantPakectList[gameObjectID] = data;
		}
		else if(packetType == PT_PLAYERCHARACTER_INJECT_EMITTER)
		{
			PT_SKILL_C2M_PLAYERCHARACTER_INJECT_EMITTER_DATA data = *((PT_SKILL_C2M_PLAYERCHARACTER_INJECT_EMITTER_DATA*)sendData);
			mPlayerCharacterInjectEmitterPakectList[gameObjectID] = data;
		}
		else if(packetType == PT_PLAYERCHARACTER_INJECT_OBJECT)
		{
			PT_SKILL_C2M_PLAYERCHARACTER_INJECT_OBJECT_DATA data = *((PT_SKILL_C2M_PLAYERCHARACTER_INJECT_OBJECT_DATA*)sendData);
			mPlayerCharacterInjectObjectPakectList[gameObjectID] = data;
		}
		else if(packetType == PT_PLAYERCHARACTER_INJECT_POINT)
		{
			PT_SKILL_C2M_PLAYERCHARACTER_INJECT_POINT_DATA data = *((PT_SKILL_C2M_PLAYERCHARACTER_INJECT_POINT_DATA*)sendData);
			mPlayerCharacterInjectPointPakectList[gameObjectID] = data;
		}
		else if(packetType == PT_PLAYERCHARACTER_INJECT_END)
		{
			PT_SKILL_C2M_PLAYERCHARACTER_END_INJECT_DATA data = *((PT_SKILL_C2M_PLAYERCHARACTER_END_INJECT_DATA*)sendData);
			mPlayerCharacterInjectEndPakectList[gameObjectID] = data;
		}
		else if (packetType == PT_PLAYERCHARACTER_AFFECT_COLLISION_PLAYERCHARACTER)
		{
			PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA data = *((PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA*)sendData);
			mMapPcAffectPc[gameObjectID] = data;
		}
		else if (packetType == PT_PLAYERCHARACTER_AFFECT_COLLISION_TROOP)
		{
			PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_TROOP_DATA data = *((PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_TROOP_DATA*)sendData);
			mMapPcAffectTp[gameObjectID] = data;
		}
		else if (packetType == PT_PLAYERCHARACTER_AFFECT_COLLISION_BUILDING)
		{
			PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_BUILDING_DATA data = *((PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_BUILDING_DATA*)sendData);
			mMapPcAffectBd[gameObjectID] = data;
		}
		else if (packetType == PT_PLAYERCHARACTER_AFFECT_COLLISION_MONSTER)
		{
			PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_MONSTER_DATA data = *((PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_MONSTER_DATA*)sendData);
			mMapPcAffectMt[gameObjectID] = data;
		}
		else if (packetType == PT_MONSTER_AFFECT_COLLISION_PLAYERCHARACTER)
		{
			PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA data = *((PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA*)sendData);
			mMapMtAffectPc[gameObjectID] = data;
		}
		else if (packetType == PT_MONSTER_AFFECT_COLLISION_TROOP)
		{
			PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_TROOP_DATA data = *((PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_TROOP_DATA*)sendData);
			mMapMtAffectTp[gameObjectID] = data;
		}
		else if (packetType == PT_MONSTER_AFFECT_COLLISION_BUILDING)
		{
			PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_BUILDING_DATA data = *((PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_BUILDING_DATA*)sendData);
			mMapMtAffectBd[gameObjectID] = data;
		}
		else if (packetType == PT_MONSTER_AFFECT_COLLISION_MONSTER)
		{
			PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_MONSTER_DATA data = *((PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_MONSTER_DATA*)sendData);
			mMapMtAffectMt[gameObjectID] = data;
		}
		else if (packetType == PT_TROOP_AFFECT_COLLISION_TROOP)
		{
			PT_SKILL_C2M_TROOP_AFFECT_COLLISION_TROOP_DATA data = *((PT_SKILL_C2M_TROOP_AFFECT_COLLISION_TROOP_DATA*)sendData);
			mMapTpAffectTp[gameObjectID] = data;
		}
		else if (packetType == PT_TROOP_AFFECT_COLLISION_PLAYERCHARACTER)
		{
			PT_SKILL_C2M_TROOP_AFFECT_COLLISION_PLAYERCHARACTER_DATA data = *((PT_SKILL_C2M_TROOP_AFFECT_COLLISION_PLAYERCHARACTER_DATA*)sendData);
			mMapTpAffectPc[gameObjectID] = data;
		}
		else if (packetType == PT_TROOP_AFFECT_COLLISION_BUILDING)
		{
			PT_SKILL_C2M_TROOP_AFFECT_COLLISION_BUILDING_DATA data = *((PT_SKILL_C2M_TROOP_AFFECT_COLLISION_BUILDING_DATA*)sendData);
			mMapTpAffectBd[gameObjectID] = data;
		}
		else if (packetType == PT_TROOP_AFFECT_COLLISION_MONSTER)
		{
			PT_SKILL_C2M_TROOP_AFFECT_COLLISION_MONSTER_DATA data = *((PT_SKILL_C2M_TROOP_AFFECT_COLLISION_MONSTER_DATA*)sendData);
			mMapTpAffectMt[gameObjectID] = data;
		}
		else if (packetType == PT_BUILDING_AFFECT_COLLISION_PLAYERCHARACTER)
		{
			PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_PLAYERCHARACTER_DATA data = *((PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_PLAYERCHARACTER_DATA*)sendData);
			mMapBdAffectPc[gameObjectID] = data;
		}
		else if (packetType == PT_BUILDING_AFFECT_COLLISION_BUILDING)
		{
			PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_BUILDING_DATA data = *((PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_BUILDING_DATA*)sendData);
			mMapBdAffectBd[gameObjectID] = data;
		}
		else if (packetType == PT_BUILDING_AFFECT_COLLISION_TROOP)
		{
			PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_TROOP_DATA data = *((PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_TROOP_DATA*)sendData);
			mMapBdAffectTp[gameObjectID] = data;
		}
		else if (packetType == PT_BUILDING_AFFECT_COLLISION_MONSTER)
		{
			PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_MONSTER_DATA data = *((PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_MONSTER_DATA*)sendData);
			mMapBdAffectMt[gameObjectID] = data;
		}
		else if(packetType == PT_TROOP_SOLDIER_MOVE)
		{
			std::map<TroopIdType, TroopC2SMovePosData>::iterator it = mTroopMovePakectList.find(gameObjectID);
			if(it == mTroopMovePakectList.end())
			{
				TroopC2SMovePosData troopSoldierMovePakectList;
				mTroopMovePakectList[gameObjectID] = troopSoldierMovePakectList;
			}
			
			PT_TROOP_SOLDIER_C2S_MOVE_POS_DATA data = *((PT_TROOP_SOLDIER_C2S_MOVE_POS_DATA*)sendData);
			mTroopMovePakectList[gameObjectID].troopSoldierMovePakectList[gameObjectIndex] = data;
		}
		else if(packetType == PT_TROOP_SOLDIER_STOP_MOVE)
		{
			std::map<TroopIdType, TroopC2SStopMoveData>::iterator it = mTroopStopMovePakectList.find(gameObjectID);
			if(it == mTroopStopMovePakectList.end())
			{
				TroopC2SStopMoveData troopSoldierStopMovePakectList;
				mTroopStopMovePakectList[gameObjectID] = troopSoldierStopMovePakectList;
			}

			PT_TROOP_SOLDIER_C2S_STOP_MOVE_DATA data = *((PT_TROOP_SOLDIER_C2S_STOP_MOVE_DATA*)sendData);
			mTroopStopMovePakectList[gameObjectID].troopSoldierStopMovePakectList[gameObjectIndex] = data;
		}
		else if(packetType == PT_TROOP_SOLDIER_CLANT)
		{
			std::map<TroopIdType, TroopC2SClantData>::iterator it = mTroopClantPakectList.find(gameObjectID);
			if(it == mTroopClantPakectList.end())
			{
				TroopC2SClantData troopSoldierClantPakectList;
				mTroopClantPakectList[gameObjectID] = troopSoldierClantPakectList;
			}

			PT_SKILL_C2M_TROOP_CLANT_DATA data = *((PT_SKILL_C2M_TROOP_CLANT_DATA*)sendData);
			mTroopClantPakectList[gameObjectID].troopSoldierClantPakectList[gameObjectIndex] = data;
		}
		else if(packetType == PT_TROOP_SOLDIER_INJECT_END)
		{
			std::map<TroopIdType, TroopC2SEndInjectData>::iterator it = mTroopEndInjectPakectList.find(gameObjectID);
			if(it == mTroopEndInjectPakectList.end())
			{
				TroopC2SEndInjectData troopSoldierEndInjectPakectList;
				mTroopEndInjectPakectList[gameObjectID] = troopSoldierEndInjectPakectList;
			}

			PT_SKILL_C2M_TROOP_END_INJECT_DATA data = *((PT_SKILL_C2M_TROOP_END_INJECT_DATA*)sendData);
			mTroopEndInjectPakectList[gameObjectID].troopSoldierEndInjectPakectList[gameObjectIndex] = data;
		}
		else if(packetType == PT_TROOP_SOLDIER_INJECT_OBJECT)
		{
			std::map<TroopIdType, TroopC2SInjectObjectData>::iterator it = mTroopInjectObjectPakectList.find(gameObjectID);
			if(it == mTroopInjectObjectPakectList.end())
			{
				TroopC2SInjectObjectData troopSoldierInjectObjectPakectList;
				mTroopInjectObjectPakectList[gameObjectID] = troopSoldierInjectObjectPakectList;
			}

			PT_SKILL_C2M_TROOP_INJECT_OBJECT_DATA data = *((PT_SKILL_C2M_TROOP_INJECT_OBJECT_DATA*)sendData);
			mTroopInjectObjectPakectList[gameObjectID].troopSoldierInjectObjectPakectList[gameObjectIndex] = data;
		}
		else if(packetType == PT_TROOP_SOLDIER_INJECT_EMITTER)
		{
			std::map<TroopIdType, TroopC2SInjectEmitterData>::iterator it = mTroopInjectEmitterPakectList.find(gameObjectID);
			if(it == mTroopInjectEmitterPakectList.end())
			{
				TroopC2SInjectEmitterData troopSoldierInjectEmitterPakectList;
				mTroopInjectEmitterPakectList[gameObjectID] = troopSoldierInjectEmitterPakectList;
			}

			PT_SKILL_C2M_TROOP_INJECT_EMITTER_DATA data = *((PT_SKILL_C2M_TROOP_INJECT_EMITTER_DATA*)sendData);
			mTroopInjectEmitterPakectList[gameObjectID].troopSoldierInjectEmitterPakectList[gameObjectIndex] = data;
		}
		else if(packetType == PT_TROOP_SOLDIER_INJECT_POINT)
		{
			std::map<TroopIdType, TroopC2SInjectPointData>::iterator it = mTroopInjectPointPakectList.find(gameObjectID);
			if(it == mTroopInjectPointPakectList.end())
			{
				TroopC2SInjectPointData troopSoldierInjectPointPakectList;
				mTroopInjectPointPakectList[gameObjectID] = troopSoldierInjectPointPakectList;
			}

			PT_SKILL_C2M_TROOP_INJECT_POINT_DATA data = *((PT_SKILL_C2M_TROOP_INJECT_POINT_DATA*)sendData);
			mTroopInjectPointPakectList[gameObjectID].troopSoldierInjectPointPakectList[gameObjectIndex] = data;
		}
		else if(packetType == PT_TROOP_MOVE)
		{
			PT_TROOP_C2S_MOVE_POS_DATA data = *((PT_TROOP_C2S_MOVE_POS_DATA*)sendData);
			mTroopMovePakectListNew[gameObjectID] = data;
		}
		else if(packetType == PT_TROOP_STOP_MOVE)
		{
			PT_TROOP_C2S_STOP_MOVE_DATA data = *((PT_TROOP_C2S_STOP_MOVE_DATA*)sendData);
			mTroopStopMovePakectListNew[gameObjectID] = data;
		}
		else if(packetType == PT_TROOP_USE_SKILL)
		{
			PT_SKILL_C2S_TROOP_USE_SKILL_DATA data = *((PT_SKILL_C2S_TROOP_USE_SKILL_DATA*)sendData);
			mTroopUseSkillPakectList[gameObjectID] = data;
		}

		
	}

	//-----------------------------------------------------------------------------
	void NetPacketPackManager::clearMutexPacket( GAMEOBJ_TYPE gameObjectType, GameObjectIdType gameObjectID, Int gameObjectIndex )
	{
		if(gameObjectType == GOT_PLAYERCHARACTER)
		{
			std::map<PlayerCharacterIdType, PT_PLAYERCHARACTER_C2S_MOVE_POS_DATA>::iterator movePacketIt;
			movePacketIt = mPlayerCharacterMovePakectList.find(gameObjectID);
			if(movePacketIt != mPlayerCharacterMovePakectList.end())
			{
				mPlayerCharacterMovePakectList.erase(movePacketIt);
				return;
			}

			std::map<PlayerCharacterIdType, PT_PLAYERCHARACTER_C2S_STOP_MOVE_DATA>::iterator stopMovePacketIt;
			stopMovePacketIt = mPlayerCharacterStopMovePakectList.find(gameObjectID);
			if(stopMovePacketIt != mPlayerCharacterStopMovePakectList.end())
			{
				mPlayerCharacterStopMovePakectList.erase(stopMovePacketIt);
				return;
			}

			std::map<PlayerCharacterIdType, PT_SKILL_C2M_PLAYERCHARACTER_CLANT_DATA>::iterator clantPacketIt;
			clantPacketIt = mPlayerCharacterClantPakectList.find(gameObjectID);
			if(clantPacketIt != mPlayerCharacterClantPakectList.end())
			{
				mPlayerCharacterClantPakectList.erase(clantPacketIt);
				return;
			}

			std::map<PlayerCharacterIdType, PT_SKILL_C2M_PLAYERCHARACTER_INJECT_OBJECT_DATA>::iterator injectObjectPacketIt;
			injectObjectPacketIt = mPlayerCharacterInjectObjectPakectList.find(gameObjectID);
			if(injectObjectPacketIt != mPlayerCharacterInjectObjectPakectList.end())
			{
				mPlayerCharacterInjectObjectPakectList.erase(injectObjectPacketIt);
				return;
			}

			std::map<PlayerCharacterIdType, PT_SKILL_C2M_PLAYERCHARACTER_INJECT_POINT_DATA>::iterator injectPointPacketIt;
			injectPointPacketIt = mPlayerCharacterInjectPointPakectList.find(gameObjectID);
			if(injectPointPacketIt != mPlayerCharacterInjectPointPakectList.end())
			{
				mPlayerCharacterInjectPointPakectList.erase(injectPointPacketIt);
				return;
			}

			std::map<PlayerCharacterIdType, PT_SKILL_C2M_PLAYERCHARACTER_INJECT_EMITTER_DATA>::iterator injectEmitterPacketIt;
			injectEmitterPacketIt = mPlayerCharacterInjectEmitterPakectList.find(gameObjectID);
			if(injectEmitterPacketIt != mPlayerCharacterInjectEmitterPakectList.end())
			{
				mPlayerCharacterInjectEmitterPakectList.erase(injectEmitterPacketIt);
				return;
			}

		}
		else if(gameObjectType == GOT_MONSTER)
		{
#if 0
			std::map<MonsterIdType, PT_MONSTER_C2S_MOVE_POS_DATA>::iterator movePacketIt;
			movePacketIt = mMonsterMovePakectList.find(gameObjectID);
			if(movePacketIt != mMonsterMovePakectList.end())
			{
				mMonsterMovePakectList.erase(movePacketIt);
				return;
			}

			std::map<MonsterIdType, PT_MONSTER_C2S_STOP_MOVE_DATA>::iterator stopMovePacketIt;
			stopMovePacketIt = mMonsterStopMovePakectList.find(gameObjectID);
			if(stopMovePacketIt != mMonsterStopMovePakectList.end())
			{
				mMonsterStopMovePakectList.erase(stopMovePacketIt);
				return;
			}

			std::map<MonsterIdType, PT_SKILL_C2M_MONSTER_CLANT_DATA>::iterator clantPacketIt;
			clantPacketIt = mMonsterClantPakectList.find(gameObjectID);
			if(clantPacketIt != mMonsterClantPakectList.end())
			{
				mMonsterClantPakectList.erase(clantPacketIt);
				return;
			}

			std::map<MonsterIdType, PT_SKILL_C2M_MONSTER_INJECT_OBJECT_DATA>::iterator injectObjectPacketIt;
			injectObjectPacketIt = mMonsterInjectObjectPakectList.find(gameObjectID);
			if(injectObjectPacketIt != mMonsterInjectObjectPakectList.end())
			{
				mMonsterInjectObjectPakectList.erase(injectObjectPacketIt);
				return;
			}

			std::map<MonsterIdType, PT_SKILL_C2M_MONSTER_INJECT_POINT_DATA>::iterator injectPointPacketIt;
			injectPointPacketIt = mMonsterInjectPointPakectList.find(gameObjectID);
			if(injectPointPacketIt != mMonsterInjectPointPakectList.end())
			{
				mMonsterInjectPointPakectList.erase(injectPointPacketIt);
				return;
			}

			std::map<MonsterIdType, PT_SKILL_C2M_MONSTER_INJECT_EMITTER_DATA>::iterator injectEmitterPacketIt;
			injectEmitterPacketIt = mMonsterInjectEmitterPakectList.find(gameObjectID);
			if(injectEmitterPacketIt != mMonsterInjectEmitterPakectList.end())
			{
				mMonsterInjectEmitterPakectList.erase(injectEmitterPacketIt);
				return;
			}
#endif
		}
		else if(gameObjectType == GOT_SOLDIER)
		{
			{
				std::map<TroopIdType, TroopC2SMovePosData>::iterator troopMovePacketIt;
				troopMovePacketIt = mTroopMovePakectList.find(gameObjectID);

				if(troopMovePacketIt != mTroopMovePakectList.end())
				{
					std::map<TroopSoldierIdType, PT_TROOP_SOLDIER_C2S_MOVE_POS_DATA>::iterator	troopSoldierMovePakectIt;
					troopSoldierMovePakectIt = troopMovePacketIt->second.troopSoldierMovePakectList.find(gameObjectIndex);

					if(troopSoldierMovePakectIt != troopMovePacketIt->second.troopSoldierMovePakectList.end())
					{
						troopMovePacketIt->second.troopSoldierMovePakectList.erase(troopSoldierMovePakectIt);
					}

					return;
				}

			}

			{
				std::map<TroopIdType, TroopC2SStopMoveData>::iterator troopStopMovePacketIt;
				troopStopMovePacketIt = mTroopStopMovePakectList.find(gameObjectID);

				if(troopStopMovePacketIt != mTroopStopMovePakectList.end())
				{
					std::map<TroopSoldierIdType, PT_TROOP_SOLDIER_C2S_STOP_MOVE_DATA>::iterator	troopSoldierStopMovePakectIt;
					troopSoldierStopMovePakectIt = troopStopMovePacketIt->second.troopSoldierStopMovePakectList.find(gameObjectIndex);

					if(troopSoldierStopMovePakectIt != troopStopMovePacketIt->second.troopSoldierStopMovePakectList.end())
					{
						troopStopMovePacketIt->second.troopSoldierStopMovePakectList.erase(troopSoldierStopMovePakectIt);
					}

					return;
				}
			}

			{
				std::map<TroopIdType, TroopC2SClantData>::iterator troopClantPacketIt;
				troopClantPacketIt = mTroopClantPakectList.find(gameObjectID);

				if(troopClantPacketIt != mTroopClantPakectList.end())
				{
					std::map<TroopSoldierIdType, PT_SKILL_C2M_TROOP_CLANT_DATA>::iterator	troopSoldierClantPakectIt;
					troopSoldierClantPakectIt = troopClantPacketIt->second.troopSoldierClantPakectList.find(gameObjectIndex);

					if(troopSoldierClantPakectIt != troopClantPacketIt->second.troopSoldierClantPakectList.end())
					{
						troopClantPacketIt->second.troopSoldierClantPakectList.erase(troopSoldierClantPakectIt);
					}

					return;
				}
			}

			{
				std::map<TroopIdType, TroopC2SInjectObjectData>::iterator troopInjectObjectPacketIt;
				troopInjectObjectPacketIt = mTroopInjectObjectPakectList.find(gameObjectID);

				if(troopInjectObjectPacketIt != mTroopInjectObjectPakectList.end())
				{
					std::map<TroopSoldierIdType, PT_SKILL_C2M_TROOP_INJECT_OBJECT_DATA>::iterator	troopSoldierInjectObjectPakectIt;
					troopSoldierInjectObjectPakectIt = troopInjectObjectPacketIt->second.troopSoldierInjectObjectPakectList.find(gameObjectIndex);

					if(troopSoldierInjectObjectPakectIt != troopInjectObjectPacketIt->second.troopSoldierInjectObjectPakectList.end())
					{
						troopInjectObjectPacketIt->second.troopSoldierInjectObjectPakectList.erase(troopSoldierInjectObjectPakectIt);
					}

					return;
				}
			}

			{
				std::map<TroopIdType, TroopC2SInjectEmitterData>::iterator troopInjectEmitterPacketIt;
				troopInjectEmitterPacketIt = mTroopInjectEmitterPakectList.find(gameObjectID);

				if(troopInjectEmitterPacketIt != mTroopInjectEmitterPakectList.end())
				{
					std::map<TroopSoldierIdType, PT_SKILL_C2M_TROOP_INJECT_EMITTER_DATA>::iterator	troopSoldierInjectEmitterPakectIt;
					troopSoldierInjectEmitterPakectIt = troopInjectEmitterPacketIt->second.troopSoldierInjectEmitterPakectList.find(gameObjectIndex);

					if(troopSoldierInjectEmitterPakectIt != troopInjectEmitterPacketIt->second.troopSoldierInjectEmitterPakectList.end())
					{
						troopInjectEmitterPacketIt->second.troopSoldierInjectEmitterPakectList.erase(troopSoldierInjectEmitterPakectIt);
					}

					return;
				}
			}

		}
		else if(gameObjectType == GOT_TROOP)
		{
			std::map<TroopIdType, PT_TROOP_C2S_MOVE_POS_DATA>::iterator movePacketIt;
			movePacketIt = mTroopMovePakectListNew.find(gameObjectID);
			if(movePacketIt != mTroopMovePakectListNew.end())
			{
				mTroopMovePakectListNew.erase(movePacketIt);
				return;
			}

			std::map<TroopIdType, PT_TROOP_C2S_STOP_MOVE_DATA>	::iterator stopMovePacketIt;
			stopMovePacketIt = mTroopStopMovePakectListNew.find(gameObjectID);
			if(stopMovePacketIt != mTroopStopMovePakectListNew.end())
			{
				mTroopStopMovePakectListNew.erase(stopMovePacketIt);
				return;
			}
		}
	}

    //-----------------------------------------------------------------------------
    GameNetSendDataBufferPtr NetPacketPackManager::getSendBuff( PT_PACK_C2S_CHARACTER_DATA*& characterPack )
    {
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_PACK;
            packet->type    = PT_CHARACTER_C2S_PACK;

            characterPack = (PT_PACK_C2S_CHARACTER_DATA*)packet->data;
            characterPack->playerId = CPlayer::getInstance().getAccountID();
            characterPack->regionId = CPlayer::getInstance().getActiveClan()->getFocusRegionID();
            characterPack->regionType = CPlayer::getInstance().getActiveClan()->getFocusRegionType();
            characterPack->packetNum = 0;
        }

        return dataPtr ;
    }
    
	//-----------------------------------------------------------------------------
	void NetPacketPackManager::clear()
	{
		mMapPcAffectPc.clear();
		mMapPcAffectTp.clear();
		mMapPcAffectBd.clear();
		mMapPcAffectMt.clear();

		mMapMtAffectPc.clear();	
		mMapMtAffectTp.clear();
		mMapMtAffectBd.clear();
		mMapMtAffectMt.clear();

		mMapTpAffectTp.clear();		
		mMapTpAffectPc.clear();
		mMapTpAffectBd.clear();
		mMapTpAffectMt.clear();

		mMapBdAffectPc.clear();
		mMapBdAffectBd.clear();
		mMapBdAffectTp.clear();
		mMapBdAffectMt.clear();

		mPlayerCharacterMovePakectList.clear();
		mPlayerCharacterStopMovePakectList.clear();
		mPlayerCharacterClantPakectList.clear();
		mPlayerCharacterInjectEndPakectList.clear();
		mPlayerCharacterInjectObjectPakectList.clear();
		mPlayerCharacterInjectPointPakectList.clear();
		mPlayerCharacterInjectEmitterPakectList.clear();

		//mMonsterMovePakectList.clear();
		//mMonsterStopMovePakectList.clear();
		//mMonsterClantPakectList.clear();
		//mMonsterInjectEndPakectList.clear();
		//mMonsterInjectObjectPakectList.clear();
		//mMonsterInjectPointPakectList.clear();
		//mMonsterInjectEmitterPakectList.clear();

		mTroopUseSkillPakectList.clear();

		mTroopMovePakectListNew.clear();
		mTroopStopMovePakectListNew.clear();

		mTroopMovePakectList.clear();
		mTroopStopMovePakectList.clear();
		mTroopClantPakectList.clear();
		mTroopEndInjectPakectList.clear();
		mTroopInjectObjectPakectList.clear();
		mTroopInjectEmitterPakectList.clear();
		mTroopInjectPointPakectList.clear();
	}

    //-----------------------------------------------------------------------------
    void NetPacketPackManager::packSend()
    {

		if(mPlayerCharacterMovePakectList.size() == 0 
			&& mPlayerCharacterStopMovePakectList.size() == 0 
			&& mPlayerCharacterClantPakectList.size() == 0 
			&& mPlayerCharacterInjectEndPakectList.size() == 0 
			&& mPlayerCharacterInjectObjectPakectList.size() == 0 
			&& mPlayerCharacterInjectPointPakectList.size() == 0 
			&& mPlayerCharacterInjectEmitterPakectList.size() == 0
			&& mTroopMovePakectList.size() == 0 
			&& mTroopStopMovePakectList.size() == 0 
			&& mTroopClantPakectList.size() == 0 
			&& mTroopEndInjectPakectList.size() == 0 
			&& mTroopInjectObjectPakectList.size() == 0
			&& mTroopInjectEmitterPakectList.size() == 0
			&& mTroopInjectPointPakectList.size() == 0
			//&& mMonsterMovePakectList.size() == 0 
			//&& mMonsterStopMovePakectList.size() == 0
			//&& mMonsterClantPakectList.size() == 0 
			//&& mMonsterInjectEndPakectList.size() == 0 
			//&& mMonsterInjectObjectPakectList.size() == 0
			//&& mMonsterInjectEmitterPakectList.size() == 0
			//&& mMonsterInjectPointPakectList.size() == 0
			&& mMapPcAffectPc.size() == 0			
			&& mMapPcAffectTp.size() == 0	
			&& mMapPcAffectBd.size() == 0	
			&& mMapPcAffectMt.size() == 0	
			&& mMapMtAffectPc.size() == 0	
			&& mMapMtAffectTp.size() == 0	
			&& mMapMtAffectBd.size() == 0	
			&& mMapMtAffectMt.size() == 0	
			&& mMapTpAffectTp.size() == 0	
			&& mMapTpAffectPc.size() == 0	
			&& mMapTpAffectBd.size() == 0	
			&& mMapTpAffectMt.size() == 0	
			&& mMapBdAffectPc.size() == 0	
			&& mMapBdAffectBd.size() == 0	
			&& mMapBdAffectTp.size() == 0	
			&& mMapBdAffectMt.size() == 0
			&& mTroopMovePakectListNew.size() == 0
			&& mTroopStopMovePakectListNew.size() == 0
			&& mTroopUseSkillPakectList.size() == 0
			)
		{
			return;
		}

        PT_PACK_C2S_CHARACTER_DATA* characterPack = NULL;
		GameNetSendDataBufferPtr dataPtr = getSendBuff( characterPack );
        DYNAMIC_ASSERT_LOG( characterPack != NULL, "characterPack is NULL!");

		// 当前发送数据头大小
		I32 sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_PACK_C2S_CHARACTER_DATA_INFO::headSize;
		// 准备发送数据大小
		I32 prepareSendDataSize = sendDataHeadSize;

		for(std::map<PlayerCharacterIdType, PT_PLAYERCHARACTER_C2S_MOVE_POS_DATA>::iterator it = mPlayerCharacterMovePakectList.begin(); it != mPlayerCharacterMovePakectList.end(); ++it)
		{ 
			if ( prepareSendDataSize + sizeof(PT_PACK_C2S_PLAYERCHARACTER_MOVE_DATA) >= dataPtr->getLogicDataMaxSize() )
			{
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					prepareSendDataSize );

                dataPtr = getSendBuff( characterPack );
				prepareSendDataSize  = sendDataHeadSize;
			}

			PT_PACK_C2S_PLAYERCHARACTER_MOVE_DATA* playerCharacterMoveData = (PT_PACK_C2S_PLAYERCHARACTER_MOVE_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
			playerCharacterMoveData->type = PT_PLAYERCHARACTER_MOVE;

			playerCharacterMoveData->packet = it->second;
			prepareSendDataSize += sizeof(PT_PACK_C2S_PLAYERCHARACTER_MOVE_DATA);
			characterPack->packetNum++;
		}

		for(std::map<PlayerCharacterIdType, PT_PLAYERCHARACTER_C2S_STOP_MOVE_DATA>::iterator it = mPlayerCharacterStopMovePakectList.begin(); it != mPlayerCharacterStopMovePakectList.end(); ++it)
		{ 
			if ( prepareSendDataSize + sizeof(PT_PACK_C2S_PLAYERCHARACTER_STOP_MOVE_DATA) >= dataPtr->getLogicDataMaxSize() )
			{
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					prepareSendDataSize );

                dataPtr = getSendBuff( characterPack );
                prepareSendDataSize  = sendDataHeadSize;
			}

			PT_PACK_C2S_PLAYERCHARACTER_STOP_MOVE_DATA* playerCharacterStopMoveData = (PT_PACK_C2S_PLAYERCHARACTER_STOP_MOVE_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
			playerCharacterStopMoveData->type = PT_PLAYERCHARACTER_STOP_MOVE;

			playerCharacterStopMoveData->packet = it->second;
			prepareSendDataSize += sizeof(PT_PACK_C2S_PLAYERCHARACTER_STOP_MOVE_DATA);
			characterPack->packetNum++;
		}

		for(std::map<PlayerCharacterIdType, PT_SKILL_C2M_PLAYERCHARACTER_CLANT_DATA>::iterator it = mPlayerCharacterClantPakectList.begin(); it != mPlayerCharacterClantPakectList.end(); ++it)
		{ 
			if ( prepareSendDataSize + sizeof(PT_PACK_C2M_PLAYERCHARACTER_CLANT_DATA) >= dataPtr->getLogicDataMaxSize() )
			{
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					prepareSendDataSize );

                dataPtr = getSendBuff( characterPack );
                prepareSendDataSize  = sendDataHeadSize;
			}

			PT_PACK_C2M_PLAYERCHARACTER_CLANT_DATA* playerCharacterClantData = (PT_PACK_C2M_PLAYERCHARACTER_CLANT_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
			playerCharacterClantData->type = PT_PLAYERCHARACTER_CLANT;

			playerCharacterClantData->packet = it->second;
			prepareSendDataSize += sizeof(PT_PACK_C2M_PLAYERCHARACTER_CLANT_DATA);
			characterPack->packetNum++;
		}

		for(std::map<PlayerCharacterIdType, PT_SKILL_C2M_PLAYERCHARACTER_INJECT_OBJECT_DATA>::iterator it = mPlayerCharacterInjectObjectPakectList.begin(); it != mPlayerCharacterInjectObjectPakectList.end(); ++it)
		{ 
			if ( prepareSendDataSize + sizeof(PT_PACK_C2M_PLAYERCHARACTER_INJECT_OBJECT_DATA) >= dataPtr->getLogicDataMaxSize() )
			{
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					prepareSendDataSize );

                dataPtr = getSendBuff( characterPack );
                prepareSendDataSize  = sendDataHeadSize;
			}

			PT_PACK_C2M_PLAYERCHARACTER_INJECT_OBJECT_DATA* playerCharacterInjectObjectData = (PT_PACK_C2M_PLAYERCHARACTER_INJECT_OBJECT_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
			playerCharacterInjectObjectData->type = PT_PLAYERCHARACTER_INJECT_OBJECT;

			playerCharacterInjectObjectData->packet = it->second;
			prepareSendDataSize += sizeof(PT_PACK_C2M_PLAYERCHARACTER_INJECT_OBJECT_DATA);
			characterPack->packetNum++;
		}

		for(std::map<PlayerCharacterIdType, PT_SKILL_C2M_PLAYERCHARACTER_INJECT_POINT_DATA>::iterator it = mPlayerCharacterInjectPointPakectList.begin(); it != mPlayerCharacterInjectPointPakectList.end(); ++it)
		{ 

			if ( prepareSendDataSize + sizeof(PT_PACK_C2M_PLAYERCHARACTER_INJECT_POINT_DATA) >= dataPtr->getLogicDataMaxSize() )
			{
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					prepareSendDataSize );

                dataPtr = getSendBuff( characterPack );
                prepareSendDataSize  = sendDataHeadSize;
			}

			PT_PACK_C2M_PLAYERCHARACTER_INJECT_POINT_DATA* playerCharacterInjectPointData = (PT_PACK_C2M_PLAYERCHARACTER_INJECT_POINT_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
			playerCharacterInjectPointData->type = PT_PLAYERCHARACTER_INJECT_POINT;

			playerCharacterInjectPointData->packet = it->second;
			prepareSendDataSize += sizeof(PT_PACK_C2M_PLAYERCHARACTER_INJECT_POINT_DATA);
			characterPack->packetNum++;
		}

		for(std::map<PlayerCharacterIdType, PT_SKILL_C2M_PLAYERCHARACTER_INJECT_EMITTER_DATA>::iterator it = mPlayerCharacterInjectEmitterPakectList.begin(); it != mPlayerCharacterInjectEmitterPakectList.end(); ++it)
		{ 

			if ( prepareSendDataSize + sizeof(PT_PACK_C2M_PLAYERCHARACTER_INJECT_EMITTER_DATA) >= dataPtr->getLogicDataMaxSize() )
			{
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					prepareSendDataSize );

                dataPtr = getSendBuff( characterPack );
                prepareSendDataSize  = sendDataHeadSize;
			}

			PT_PACK_C2M_PLAYERCHARACTER_INJECT_EMITTER_DATA* playerCharacterInjectEmitterData = (PT_PACK_C2M_PLAYERCHARACTER_INJECT_EMITTER_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
			playerCharacterInjectEmitterData->type = PT_PLAYERCHARACTER_INJECT_EMITTER;

			playerCharacterInjectEmitterData->packet = it->second;
			prepareSendDataSize += sizeof(PT_PACK_C2M_PLAYERCHARACTER_INJECT_EMITTER_DATA);
			characterPack->packetNum++;
		}

		for(std::map<PlayerCharacterIdType, PT_SKILL_C2M_PLAYERCHARACTER_END_INJECT_DATA>::iterator it = mPlayerCharacterInjectEndPakectList.begin(); it != mPlayerCharacterInjectEndPakectList.end(); ++it)
		{ 
			if ( prepareSendDataSize + sizeof(PT_PACK_C2M_PLAYERCHARACTER_END_INJECT_DATA) >= dataPtr->getLogicDataMaxSize() )
			{
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					prepareSendDataSize );

                dataPtr = getSendBuff( characterPack );
                prepareSendDataSize  = sendDataHeadSize;
			}

			PT_PACK_C2M_PLAYERCHARACTER_END_INJECT_DATA* playerCharacterInjectEndData = (PT_PACK_C2M_PLAYERCHARACTER_END_INJECT_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
			playerCharacterInjectEndData->type = PT_PLAYERCHARACTER_INJECT_END;

			playerCharacterInjectEndData->packet = it->second;
			prepareSendDataSize += sizeof(PT_PACK_C2M_PLAYERCHARACTER_END_INJECT_DATA);
			characterPack->packetNum++;
		}

		{
			for(std::map<TroopIdType, PT_TROOP_C2S_MOVE_POS_DATA>::iterator it = mTroopMovePakectListNew.begin(); it != mTroopMovePakectListNew.end(); ++it)
			{ 
				if ( prepareSendDataSize + sizeof(PT_PACK_C2S_TROOP_MOVE_DATA) >= dataPtr->getLogicDataMaxSize() )
				{
					ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
						prepareSendDataSize );

                    dataPtr = getSendBuff( characterPack );
                    prepareSendDataSize  = sendDataHeadSize;
				}

				PT_PACK_C2S_TROOP_MOVE_DATA* troopMoveData = (PT_PACK_C2S_TROOP_MOVE_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
				troopMoveData->type = PT_TROOP_MOVE;

				troopMoveData->packet = it->second;
				prepareSendDataSize += sizeof(PT_PACK_C2S_TROOP_MOVE_DATA);
				characterPack->packetNum++;
			}
		}

		{
			for(std::map<TroopIdType, PT_TROOP_C2S_STOP_MOVE_DATA>::iterator it = mTroopStopMovePakectListNew.begin(); it != mTroopStopMovePakectListNew.end(); ++it)
			{ 
				if ( prepareSendDataSize + sizeof(PT_PACK_C2S_TROOP_STOP_MOVE_DATA) >= dataPtr->getLogicDataMaxSize() )
				{
					ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
						prepareSendDataSize );

                    dataPtr = getSendBuff( characterPack );
                    prepareSendDataSize  = sendDataHeadSize;
				}

				PT_PACK_C2S_TROOP_STOP_MOVE_DATA* troopStopMoveData = (PT_PACK_C2S_TROOP_STOP_MOVE_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
				troopStopMoveData->type = PT_TROOP_STOP_MOVE;

				troopStopMoveData->packet = it->second;
				prepareSendDataSize += sizeof(PT_PACK_C2S_TROOP_STOP_MOVE_DATA);
				characterPack->packetNum++;
			}
		}

		{
			for(std::map<TroopIdType, PT_SKILL_C2S_TROOP_USE_SKILL_DATA>::iterator it = mTroopUseSkillPakectList.begin(); it != mTroopUseSkillPakectList.end(); ++it)
			{ 
				if ( prepareSendDataSize + sizeof(PT_PACK_C2S_TROOP_USE_SKILL_DATA) >= dataPtr->getLogicDataMaxSize() )
				{
					ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
						prepareSendDataSize );

                    dataPtr = getSendBuff( characterPack );
                    prepareSendDataSize  = sendDataHeadSize;
				}

				PT_PACK_C2S_TROOP_USE_SKILL_DATA* troopUseSkillData = (PT_PACK_C2S_TROOP_USE_SKILL_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
				troopUseSkillData->type = PT_TROOP_USE_SKILL;

				troopUseSkillData->packet = it->second;
				prepareSendDataSize += sizeof(PT_PACK_C2S_TROOP_USE_SKILL_DATA);
				characterPack->packetNum++;
			}
		}

		for(std::map<TroopIdType, TroopC2SMovePosData>::iterator troopMoveIt = mTroopMovePakectList.begin(); troopMoveIt != mTroopMovePakectList.end(); ++troopMoveIt)
		{ 
			for(std::map<TroopSoldierIdType, PT_TROOP_SOLDIER_C2S_MOVE_POS_DATA>::iterator troopSoldierMoveIt = troopMoveIt->second.troopSoldierMovePakectList.begin(); troopSoldierMoveIt != troopMoveIt->second.troopSoldierMovePakectList.end(); ++troopSoldierMoveIt)
			{
				if ( prepareSendDataSize + sizeof(PT_PACK_C2S_TROOP_SOLDIER_MOVE_DATA) >= dataPtr->getLogicDataMaxSize() )
				{
					ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
						prepareSendDataSize );

                    dataPtr = getSendBuff( characterPack );
                    prepareSendDataSize  = sendDataHeadSize;
				}

				PT_PACK_C2S_TROOP_SOLDIER_MOVE_DATA* troopSoldierMoveData = (PT_PACK_C2S_TROOP_SOLDIER_MOVE_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
				troopSoldierMoveData->type = PT_TROOP_SOLDIER_MOVE;
	
				troopSoldierMoveData->packet = troopSoldierMoveIt->second;
				prepareSendDataSize += sizeof(PT_PACK_C2S_TROOP_SOLDIER_MOVE_DATA);
				characterPack->packetNum++;
			}
		}

		{
		    for(std::map<TroopIdType, TroopC2SStopMoveData>::iterator troopStopMoveIt = mTroopStopMovePakectList.begin(); troopStopMoveIt != mTroopStopMovePakectList.end(); ++troopStopMoveIt)
		    { 
			    for(std::map<TroopSoldierIdType, PT_TROOP_SOLDIER_C2S_STOP_MOVE_DATA>::iterator troopSoldierStopMoveIt = troopStopMoveIt->second.troopSoldierStopMovePakectList.begin(); troopSoldierStopMoveIt != troopStopMoveIt->second.troopSoldierStopMovePakectList.end(); ++troopSoldierStopMoveIt)
			    {
				    if ( prepareSendDataSize + sizeof(PT_PACK_C2S_TROOP_SOLDIER_STOP_MOVE_DATA) >= dataPtr->getLogicDataMaxSize() )
				    {
					    ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
						    prepareSendDataSize );

                        dataPtr = getSendBuff( characterPack );
                        prepareSendDataSize  = sendDataHeadSize;
				    }

				    PT_PACK_C2S_TROOP_SOLDIER_STOP_MOVE_DATA* troopSoldierStopMoveData = (PT_PACK_C2S_TROOP_SOLDIER_STOP_MOVE_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
				    troopSoldierStopMoveData->type = PT_TROOP_SOLDIER_STOP_MOVE;

				    troopSoldierStopMoveData->packet = troopSoldierStopMoveIt->second;
				    prepareSendDataSize += sizeof(PT_PACK_C2S_TROOP_SOLDIER_STOP_MOVE_DATA);
				    characterPack->packetNum++;
			    }
		    }
		}

		{
		    for(std::map<TroopIdType, TroopC2SClantData>::iterator troopClantIt = mTroopClantPakectList.begin(); troopClantIt != mTroopClantPakectList.end(); ++troopClantIt)
		    { 
			    for(std::map<TroopSoldierIdType, PT_SKILL_C2M_TROOP_CLANT_DATA>::iterator troopSoldierClantIt = troopClantIt->second.troopSoldierClantPakectList.begin(); troopSoldierClantIt != troopClantIt->second.troopSoldierClantPakectList.end(); ++troopSoldierClantIt)
			    {
				    if ( prepareSendDataSize + sizeof(PT_PACK_C2M_TROOP_SOLDIER_CLANT_DATA) >= dataPtr->getLogicDataMaxSize() )
				    {
					    ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
						    prepareSendDataSize );

                        dataPtr = getSendBuff( characterPack );
                        prepareSendDataSize  = sendDataHeadSize;
				    }

				    PT_PACK_C2M_TROOP_SOLDIER_CLANT_DATA* troopSoldierClantData = (PT_PACK_C2M_TROOP_SOLDIER_CLANT_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
				    troopSoldierClantData->type = PT_TROOP_SOLDIER_CLANT;

				    troopSoldierClantData->packet = troopSoldierClantIt->second;
				    prepareSendDataSize += sizeof(PT_PACK_C2M_TROOP_SOLDIER_CLANT_DATA);
				    characterPack->packetNum++;
			    }

		    }
		}

		{
		    for(std::map<TroopIdType, TroopC2SEndInjectData>::iterator troopEndInjectIt = mTroopEndInjectPakectList.begin(); troopEndInjectIt != mTroopEndInjectPakectList.end(); ++troopEndInjectIt)
		    { 
			    for(std::map<TroopSoldierIdType, PT_SKILL_C2M_TROOP_END_INJECT_DATA>::iterator troopSoldierEndInjectIt = troopEndInjectIt->second.troopSoldierEndInjectPakectList.begin(); troopSoldierEndInjectIt != troopEndInjectIt->second.troopSoldierEndInjectPakectList.end(); ++troopSoldierEndInjectIt)
			    {
				    if ( prepareSendDataSize + sizeof(PT_PACK_C2M_TROOP_SOLDIER_END_INJECT_DATA) >= dataPtr->getLogicDataMaxSize() )
				    {
					    ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
						    prepareSendDataSize );

                        dataPtr = getSendBuff( characterPack );
                        prepareSendDataSize  = sendDataHeadSize;
				    }

				    PT_PACK_C2M_TROOP_SOLDIER_END_INJECT_DATA* troopSoldierEndInjectData = (PT_PACK_C2M_TROOP_SOLDIER_END_INJECT_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
				    troopSoldierEndInjectData->type = PT_TROOP_SOLDIER_INJECT_END;

				    troopSoldierEndInjectData->packet = troopSoldierEndInjectIt->second;
				    prepareSendDataSize += sizeof(PT_PACK_C2M_TROOP_SOLDIER_END_INJECT_DATA);
				    characterPack->packetNum++;
			    }
		    }

		}

		{
			for(std::map<TroopIdType, TroopC2SInjectObjectData>::iterator troopInjectObjectIt = mTroopInjectObjectPakectList.begin(); troopInjectObjectIt != mTroopInjectObjectPakectList.end(); ++troopInjectObjectIt)
			{ 
				for(std::map<TroopSoldierIdType, PT_SKILL_C2M_TROOP_INJECT_OBJECT_DATA>::iterator troopSoldierInjectObjectIt = troopInjectObjectIt->second.troopSoldierInjectObjectPakectList.begin(); troopSoldierInjectObjectIt != troopInjectObjectIt->second.troopSoldierInjectObjectPakectList.end(); ++troopSoldierInjectObjectIt)
				{
					if ( prepareSendDataSize + sizeof(PT_PACK_C2M_TROOP_SOLDIER_INJECT_OBJECT_DATA) >= dataPtr->getLogicDataMaxSize() )
					{
						ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
							prepareSendDataSize );

                        dataPtr = getSendBuff( characterPack );
                        prepareSendDataSize  = sendDataHeadSize;
					}

					PT_PACK_C2M_TROOP_SOLDIER_INJECT_OBJECT_DATA* troopSoldierInjectObjectData = (PT_PACK_C2M_TROOP_SOLDIER_INJECT_OBJECT_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
					troopSoldierInjectObjectData->type = PT_TROOP_SOLDIER_INJECT_OBJECT;

					troopSoldierInjectObjectData->packet = troopSoldierInjectObjectIt->second;
					prepareSendDataSize += sizeof(PT_PACK_C2M_TROOP_SOLDIER_INJECT_OBJECT_DATA);
					characterPack->packetNum++;
				}
			}
		}

		{
			for(std::map<TroopIdType, TroopC2SInjectEmitterData>::iterator troopInjectEmitterIt = mTroopInjectEmitterPakectList.begin(); troopInjectEmitterIt != mTroopInjectEmitterPakectList.end(); ++troopInjectEmitterIt)
			{ 
				for(std::map<TroopSoldierIdType, PT_SKILL_C2M_TROOP_INJECT_EMITTER_DATA>::iterator troopSoldierInjectEmitterIt = troopInjectEmitterIt->second.troopSoldierInjectEmitterPakectList.begin(); troopSoldierInjectEmitterIt != troopInjectEmitterIt->second.troopSoldierInjectEmitterPakectList.end(); ++troopSoldierInjectEmitterIt)
				{
					if ( prepareSendDataSize + sizeof(PT_PACK_C2M_TROOP_SOLDIER_INJECT_EMITTER_DATA) >= dataPtr->getLogicDataMaxSize() )
					{
						ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
							prepareSendDataSize );

                        dataPtr = getSendBuff( characterPack );
                        prepareSendDataSize  = sendDataHeadSize;
					}

					PT_PACK_C2M_TROOP_SOLDIER_INJECT_EMITTER_DATA* troopSoldierInjectEmitterData = (PT_PACK_C2M_TROOP_SOLDIER_INJECT_EMITTER_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
					troopSoldierInjectEmitterData->type = PT_TROOP_SOLDIER_INJECT_EMITTER;

					troopSoldierInjectEmitterData->packet = troopSoldierInjectEmitterIt->second;
					prepareSendDataSize += sizeof(PT_PACK_C2M_TROOP_SOLDIER_INJECT_EMITTER_DATA);
					characterPack->packetNum++;
				}
			}
		}

		{
			for(std::map<TroopIdType, TroopC2SInjectPointData>::iterator troopInjectPointIt = mTroopInjectPointPakectList.begin(); troopInjectPointIt != mTroopInjectPointPakectList.end(); ++troopInjectPointIt)
			{ 
				for(std::map<TroopSoldierIdType, PT_SKILL_C2M_TROOP_INJECT_POINT_DATA>::iterator troopSoldierInjectPointIt = troopInjectPointIt->second.troopSoldierInjectPointPakectList.begin(); troopSoldierInjectPointIt != troopInjectPointIt->second.troopSoldierInjectPointPakectList.end(); ++troopSoldierInjectPointIt)
				{
					if ( prepareSendDataSize + sizeof(PT_PACK_C2M_TROOP_SOLDIER_INJECT_POINT_DATA) >= dataPtr->getLogicDataMaxSize() )
					{
						ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
							prepareSendDataSize );

                        dataPtr = getSendBuff( characterPack );
                        prepareSendDataSize  = sendDataHeadSize;
					}

					PT_PACK_C2M_TROOP_SOLDIER_INJECT_POINT_DATA* troopSoldierInjectPointData = (PT_PACK_C2M_TROOP_SOLDIER_INJECT_POINT_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
					troopSoldierInjectPointData->type = PT_TROOP_SOLDIER_INJECT_POINT;

					troopSoldierInjectPointData->packet = troopSoldierInjectPointIt->second;
					prepareSendDataSize += sizeof(PT_PACK_C2M_TROOP_SOLDIER_INJECT_POINT_DATA);
					characterPack->packetNum++;
				}
			}
		}

		{
#if 0
			for(std::map<MonsterIdType, PT_MONSTER_C2S_MOVE_POS_DATA>::iterator it = mMonsterMovePakectList.begin(); it != mMonsterMovePakectList.end(); ++it)
			{ 
				if ( prepareSendDataSize + sizeof(PT_PACK_C2S_MONSTER_MOVE_DATA) >= dataPtr->getLogicDataMaxSize() )
				{
					ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
						prepareSendDataSize );

                    dataPtr = getSendBuff( characterPack );
                    prepareSendDataSize  = sendDataHeadSize;
				}

				PT_PACK_C2S_MONSTER_MOVE_DATA* monsterMoveData = (PT_PACK_C2S_MONSTER_MOVE_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
				monsterMoveData->type = PT_MONSTER_MOVE;

				monsterMoveData->packet = it->second;
				prepareSendDataSize += sizeof(PT_PACK_C2S_MONSTER_MOVE_DATA);
				characterPack->packetNum++;
			}
#endif
		}

		{
#if 0
			for(std::map<MonsterIdType, PT_MONSTER_C2S_STOP_MOVE_DATA>::iterator it = mMonsterStopMovePakectList.begin(); it != mMonsterStopMovePakectList.end(); ++it)
			{ 
				if ( prepareSendDataSize + sizeof(PT_PACK_C2S_MONSTER_STOP_MOVE_DATA) >= dataPtr->getLogicDataMaxSize() )
				{
					ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
						prepareSendDataSize );

                    dataPtr = getSendBuff( characterPack );
                    prepareSendDataSize  = sendDataHeadSize;
				}

				PT_PACK_C2S_MONSTER_STOP_MOVE_DATA* monsterStopMoveData = (PT_PACK_C2S_MONSTER_STOP_MOVE_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
				monsterStopMoveData->type = PT_MONSTER_STOP_MOVE;

				monsterStopMoveData->packet = it->second;
				prepareSendDataSize += sizeof(PT_PACK_C2S_MONSTER_STOP_MOVE_DATA);
				characterPack->packetNum++;
			}
#endif
		}

#if 0
		{
			for(std::map<MonsterIdType, PT_SKILL_C2M_MONSTER_CLANT_DATA>::iterator it = mMonsterClantPakectList.begin(); it != mMonsterClantPakectList.end(); ++it)
			{ 
				if ( prepareSendDataSize + sizeof(PT_PACK_C2M_MONSTER_CLANT_DATA) >= dataPtr->getLogicDataMaxSize() )
				{
					ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
						prepareSendDataSize );

                    dataPtr = getSendBuff( characterPack );
                    prepareSendDataSize  = sendDataHeadSize;
				}

				PT_PACK_C2M_MONSTER_CLANT_DATA* monsterClantData = (PT_PACK_C2M_MONSTER_CLANT_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
				monsterClantData->type = PT_MONSTER_CLANT;

				monsterClantData->packet = it->second;
				prepareSendDataSize += sizeof(PT_PACK_C2M_MONSTER_CLANT_DATA);
				characterPack->packetNum++;
			}
		}

		{
			for(std::map<MonsterIdType, PT_SKILL_C2M_MONSTER_INJECT_OBJECT_DATA>::iterator it = mMonsterInjectObjectPakectList.begin(); it != mMonsterInjectObjectPakectList.end(); ++it)
			{ 
				if ( prepareSendDataSize + sizeof(PT_PACK_C2M_MONSTER_INJECT_OBJECT_DATA) >= dataPtr->getLogicDataMaxSize() )
				{
					ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
						prepareSendDataSize );

                    dataPtr = getSendBuff( characterPack );
                    prepareSendDataSize  = sendDataHeadSize;
				}

				PT_PACK_C2M_MONSTER_INJECT_OBJECT_DATA* monsterInjectObjectData = (PT_PACK_C2M_MONSTER_INJECT_OBJECT_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
				monsterInjectObjectData->type = PT_MONSTER_INJECT_OBJECT;

				monsterInjectObjectData->packet = it->second;
				prepareSendDataSize += sizeof(PT_PACK_C2M_MONSTER_INJECT_OBJECT_DATA);
				characterPack->packetNum++;
			}
		}

		{
			for(std::map<MonsterIdType, PT_SKILL_C2M_MONSTER_INJECT_POINT_DATA>::iterator it = mMonsterInjectPointPakectList.begin(); it != mMonsterInjectPointPakectList.end(); ++it)
			{ 

				if ( prepareSendDataSize + sizeof(PT_PACK_C2M_MONSTER_INJECT_POINT_DATA) >= dataPtr->getLogicDataMaxSize() )
				{
					ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
						prepareSendDataSize );

                    dataPtr = getSendBuff( characterPack );
                    prepareSendDataSize  = sendDataHeadSize;
				}

				PT_PACK_C2M_MONSTER_INJECT_POINT_DATA* monsterInjectPointData = (PT_PACK_C2M_MONSTER_INJECT_POINT_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
				monsterInjectPointData->type = PT_MONSTER_INJECT_POINT;

				monsterInjectPointData->packet = it->second;
				prepareSendDataSize += sizeof(PT_PACK_C2M_MONSTER_INJECT_POINT_DATA);
				characterPack->packetNum++;
			}
		}

		{
			for(std::map<MonsterIdType, PT_SKILL_C2M_MONSTER_INJECT_EMITTER_DATA>::iterator it = mMonsterInjectEmitterPakectList.begin(); it != mMonsterInjectEmitterPakectList.end(); ++it)
			{ 

				if ( prepareSendDataSize + sizeof(PT_PACK_C2M_MONSTER_INJECT_EMITTER_DATA) >= dataPtr->getLogicDataMaxSize() )
				{
					ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
						prepareSendDataSize );

                    dataPtr = getSendBuff( characterPack );
                    prepareSendDataSize  = sendDataHeadSize;
				}

				PT_PACK_C2M_MONSTER_INJECT_EMITTER_DATA* monsterInjectEmitterData = (PT_PACK_C2M_MONSTER_INJECT_EMITTER_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
				monsterInjectEmitterData->type = PT_MONSTER_INJECT_EMITTER;

				monsterInjectEmitterData->packet = it->second;
				prepareSendDataSize += sizeof(PT_PACK_C2M_MONSTER_INJECT_EMITTER_DATA);
				characterPack->packetNum++;
			}
		}

		{
			for(std::map<MonsterIdType, PT_SKILL_C2M_MONSTER_END_INJECT_DATA>::iterator it = mMonsterInjectEndPakectList.begin(); it != mMonsterInjectEndPakectList.end(); ++it)
			{ 
				if ( prepareSendDataSize + sizeof(PT_PACK_C2M_MONSTER_END_INJECT_DATA) >= dataPtr->getLogicDataMaxSize() )
				{
					ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
						prepareSendDataSize );

                    dataPtr = getSendBuff( characterPack );
                    prepareSendDataSize  = sendDataHeadSize;
				}

				PT_PACK_C2M_MONSTER_END_INJECT_DATA* monsterInjectEndData = (PT_PACK_C2M_MONSTER_END_INJECT_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
				monsterInjectEndData->type = PT_MONSTER_INJECT_END;

				monsterInjectEndData->packet = it->second;
				prepareSendDataSize += sizeof(PT_PACK_C2M_MONSTER_END_INJECT_DATA);
				characterPack->packetNum++;
			}
		}
#endif

//1
		{
			std::map<PlayerCharacterIdType, PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA>::iterator front = mMapPcAffectPc.begin();
			std::map<PlayerCharacterIdType, PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA>::iterator back = mMapPcAffectPc.end();
			for(; front != back; ++front)
			{ 
				if ( prepareSendDataSize + sizeof(PT_PLAYERCHARACTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA) >= dataPtr->getLogicDataMaxSize() )
				{
					ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
						prepareSendDataSize );

                    dataPtr = getSendBuff( characterPack );
                    prepareSendDataSize  = sendDataHeadSize;
				}

				PT_PLAYERCHARACTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA* playerCharacterInjectEndData = (PT_PLAYERCHARACTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
				playerCharacterInjectEndData->type = PT_PLAYERCHARACTER_AFFECT_COLLISION_PLAYERCHARACTER;

				playerCharacterInjectEndData->packet = front->second;
				prepareSendDataSize += sizeof(PT_PLAYERCHARACTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA);
				characterPack->packetNum++;

			}
		}

		{
			std::map<PlayerCharacterIdType, PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_TROOP_DATA>::iterator front = mMapPcAffectTp.begin();
			std::map<PlayerCharacterIdType, PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_TROOP_DATA>::iterator back = mMapPcAffectTp.end();
			for(; front != back; ++front)
			{ 
				if ( prepareSendDataSize + sizeof(PT_PLAYERCHARACTER_AFFECT_COLLISION_TROOP_DATA) >= dataPtr->getLogicDataMaxSize() )
				{
					ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
						prepareSendDataSize );

                    dataPtr = getSendBuff( characterPack );
                    prepareSendDataSize  = sendDataHeadSize;
				}

				PT_PLAYERCHARACTER_AFFECT_COLLISION_TROOP_DATA* playerCharacterInjectEndData = (PT_PLAYERCHARACTER_AFFECT_COLLISION_TROOP_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
				playerCharacterInjectEndData->type = PT_PLAYERCHARACTER_AFFECT_COLLISION_TROOP;

				playerCharacterInjectEndData->packet = front->second;
				prepareSendDataSize += sizeof(PT_PLAYERCHARACTER_AFFECT_COLLISION_TROOP_DATA);
				characterPack->packetNum++;

			}
		}

		{
			std::map<PlayerCharacterIdType, PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_BUILDING_DATA>::iterator front = mMapPcAffectBd.begin();
			std::map<PlayerCharacterIdType, PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_BUILDING_DATA>::iterator back = mMapPcAffectBd.end();
			for(; front != back; ++front)
			{ 
				if ( prepareSendDataSize + sizeof(PT_PLAYERCHARACTER_AFFECT_COLLISION_BUILDING_DATA) >= dataPtr->getLogicDataMaxSize() )
				{
					ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
						prepareSendDataSize );

                    dataPtr = getSendBuff( characterPack );
                    prepareSendDataSize  = sendDataHeadSize;
				}

				PT_PLAYERCHARACTER_AFFECT_COLLISION_BUILDING_DATA* playerCharacterInjectEndData = (PT_PLAYERCHARACTER_AFFECT_COLLISION_BUILDING_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
				playerCharacterInjectEndData->type = PT_PLAYERCHARACTER_AFFECT_COLLISION_BUILDING;

				playerCharacterInjectEndData->packet = front->second;
				prepareSendDataSize += sizeof(PT_PLAYERCHARACTER_AFFECT_COLLISION_BUILDING_DATA);
				characterPack->packetNum++;
			}
		}

		{
			std::map<PlayerCharacterIdType, PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_MONSTER_DATA>::iterator front = mMapPcAffectMt.begin();
			std::map<PlayerCharacterIdType, PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_MONSTER_DATA>::iterator back = mMapPcAffectMt.end();
			for(; front != back; ++front)
			{ 
				if ( prepareSendDataSize + sizeof(PT_PLAYERCHARACTER_AFFECT_COLLISION_MONSTER_DATA) >= dataPtr->getLogicDataMaxSize() )
				{
					ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
						prepareSendDataSize );

                    dataPtr = getSendBuff( characterPack );
                    prepareSendDataSize  = sendDataHeadSize;
				}

				PT_PLAYERCHARACTER_AFFECT_COLLISION_MONSTER_DATA* playerCharacterInjectEndData = (PT_PLAYERCHARACTER_AFFECT_COLLISION_MONSTER_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
				playerCharacterInjectEndData->type = PT_PLAYERCHARACTER_AFFECT_COLLISION_MONSTER;

				playerCharacterInjectEndData->packet = front->second;
				prepareSendDataSize += sizeof(PT_PLAYERCHARACTER_AFFECT_COLLISION_MONSTER_DATA);
				characterPack->packetNum++;

			}
		}
//2
		{
			std::map<PlayerCharacterIdType, PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA>::iterator front = mMapMtAffectPc.begin();
			std::map<PlayerCharacterIdType, PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA>::iterator back = mMapMtAffectPc.end();
			for(; front != back; ++front)
			{ 
				if ( prepareSendDataSize + sizeof(PT_MONSTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA) >= dataPtr->getLogicDataMaxSize() )
				{
					ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
						prepareSendDataSize );

                    dataPtr = getSendBuff( characterPack );
                    prepareSendDataSize  = sendDataHeadSize;
				}

				PT_MONSTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA* playerCharacterInjectEndData = (PT_MONSTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
				playerCharacterInjectEndData->type = PT_MONSTER_AFFECT_COLLISION_PLAYERCHARACTER;

				playerCharacterInjectEndData->packet = front->second;
				prepareSendDataSize += sizeof(PT_MONSTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA);
				characterPack->packetNum++;

			}
		}
//3
		{
			std::map<PlayerCharacterIdType, PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_TROOP_DATA>::iterator front = mMapMtAffectTp.begin();
			std::map<PlayerCharacterIdType, PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_TROOP_DATA>::iterator back = mMapMtAffectTp.end();
			for(; front != back; ++front)
			{ 
				if ( prepareSendDataSize + sizeof(PT_MONSTER_AFFECT_COLLISION_TROOP_DATA) >= dataPtr->getLogicDataMaxSize() )
				{
					ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
						prepareSendDataSize );

                    dataPtr = getSendBuff( characterPack );
                    prepareSendDataSize  = sendDataHeadSize;
				}

				PT_MONSTER_AFFECT_COLLISION_TROOP_DATA* playerCharacterInjectEndData = (PT_MONSTER_AFFECT_COLLISION_TROOP_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
				playerCharacterInjectEndData->type = PT_MONSTER_AFFECT_COLLISION_TROOP;

				playerCharacterInjectEndData->packet = front->second;
				prepareSendDataSize += sizeof(PT_MONSTER_AFFECT_COLLISION_TROOP_DATA);
				characterPack->packetNum++;

			}
		}
//4

		{
			std::map<PlayerCharacterIdType, PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_BUILDING_DATA>::iterator front = mMapMtAffectBd.begin();
			std::map<PlayerCharacterIdType, PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_BUILDING_DATA>::iterator back = mMapMtAffectBd.end();
			for(; front != back; ++front)
			{ 
				if ( prepareSendDataSize + sizeof(PT_MONSTER_AFFECT_COLLISION_BUILDING_DATA) >= dataPtr->getLogicDataMaxSize() )
				{
					ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
						prepareSendDataSize );

                    dataPtr = getSendBuff( characterPack );
                    prepareSendDataSize  = sendDataHeadSize;
				}

				PT_MONSTER_AFFECT_COLLISION_BUILDING_DATA* playerCharacterInjectEndData = (PT_MONSTER_AFFECT_COLLISION_BUILDING_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
				playerCharacterInjectEndData->type = PT_MONSTER_AFFECT_COLLISION_BUILDING;

				playerCharacterInjectEndData->packet = front->second;
				prepareSendDataSize += sizeof(PT_MONSTER_AFFECT_COLLISION_BUILDING_DATA);
				characterPack->packetNum++;

			}
		}
//5
		{
			std::map<PlayerCharacterIdType, PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_MONSTER_DATA>::iterator front = mMapMtAffectMt.begin();
			std::map<PlayerCharacterIdType, PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_MONSTER_DATA>::iterator back = mMapMtAffectMt.end();
			for(; front != back; ++front)
			{ 
				if ( prepareSendDataSize + sizeof(PT_MONSTER_AFFECT_COLLISION_MONSTER_DATA) >= dataPtr->getLogicDataMaxSize() )
				{
					ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
						prepareSendDataSize );

                    dataPtr = getSendBuff( characterPack );
                    prepareSendDataSize  = sendDataHeadSize;
				}

				PT_MONSTER_AFFECT_COLLISION_MONSTER_DATA* playerCharacterInjectEndData = (PT_MONSTER_AFFECT_COLLISION_MONSTER_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
				playerCharacterInjectEndData->type = PT_MONSTER_AFFECT_COLLISION_MONSTER;

				playerCharacterInjectEndData->packet = front->second;
				prepareSendDataSize += sizeof(PT_MONSTER_AFFECT_COLLISION_MONSTER_DATA);
				characterPack->packetNum++;

			}
		}
//6
		{
			std::map<PlayerCharacterIdType, PT_SKILL_C2M_TROOP_AFFECT_COLLISION_TROOP_DATA>::iterator front = mMapTpAffectTp.begin();
			std::map<PlayerCharacterIdType, PT_SKILL_C2M_TROOP_AFFECT_COLLISION_TROOP_DATA>::iterator back = mMapTpAffectTp.end();
			for(; front != back; ++front)
			{ 
				if ( prepareSendDataSize + sizeof(PT_TROOP_AFFECT_COLLISION_TROOP_DATA) >= dataPtr->getLogicDataMaxSize() )
				{
					ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
						prepareSendDataSize );

                    dataPtr = getSendBuff( characterPack );
                    prepareSendDataSize  = sendDataHeadSize;
				}

				PT_TROOP_AFFECT_COLLISION_TROOP_DATA* playerCharacterInjectEndData = (PT_TROOP_AFFECT_COLLISION_TROOP_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
				playerCharacterInjectEndData->type = PT_TROOP_AFFECT_COLLISION_TROOP;

				playerCharacterInjectEndData->packet = front->second;
				prepareSendDataSize += sizeof(PT_TROOP_AFFECT_COLLISION_TROOP_DATA);
				characterPack->packetNum++;
			}
		}

//7
		{
			std::map<PlayerCharacterIdType, PT_SKILL_C2M_TROOP_AFFECT_COLLISION_PLAYERCHARACTER_DATA>::iterator front = mMapTpAffectPc.begin();
			std::map<PlayerCharacterIdType, PT_SKILL_C2M_TROOP_AFFECT_COLLISION_PLAYERCHARACTER_DATA>::iterator back = mMapTpAffectPc.end();
			for(; front != back; ++front)
			{ 
				if ( prepareSendDataSize + sizeof(PT_TROOP_AFFECT_COLLISION_PLAYERCHARACTER_DATA) >= dataPtr->getLogicDataMaxSize() )
				{
					ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
						prepareSendDataSize );

                    dataPtr = getSendBuff( characterPack );
                    prepareSendDataSize  = sendDataHeadSize;
				}

				PT_TROOP_AFFECT_COLLISION_PLAYERCHARACTER_DATA* playerCharacterInjectEndData = (PT_TROOP_AFFECT_COLLISION_PLAYERCHARACTER_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
				playerCharacterInjectEndData->type = PT_TROOP_AFFECT_COLLISION_PLAYERCHARACTER;

				playerCharacterInjectEndData->packet = front->second;
				prepareSendDataSize += sizeof(PT_TROOP_AFFECT_COLLISION_PLAYERCHARACTER_DATA);
				characterPack->packetNum++;

			}
		}
//8
		{
			std::map<PlayerCharacterIdType, PT_SKILL_C2M_TROOP_AFFECT_COLLISION_BUILDING_DATA>::iterator front = mMapTpAffectBd.begin();
			std::map<PlayerCharacterIdType, PT_SKILL_C2M_TROOP_AFFECT_COLLISION_BUILDING_DATA>::iterator back = mMapTpAffectBd.end();
			for(; front != back; ++front)
			{ 
				if ( prepareSendDataSize + sizeof(PT_TROOP_AFFECT_COLLISION_BUILDING_DATA) >= dataPtr->getLogicDataMaxSize() )
				{
					ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
						prepareSendDataSize );

                    dataPtr = getSendBuff( characterPack );
                    prepareSendDataSize  = sendDataHeadSize;
				}

				PT_TROOP_AFFECT_COLLISION_BUILDING_DATA* playerCharacterInjectEndData = (PT_TROOP_AFFECT_COLLISION_BUILDING_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
				playerCharacterInjectEndData->type = PT_TROOP_AFFECT_COLLISION_BUILDING;

				playerCharacterInjectEndData->packet = front->second;
				prepareSendDataSize += sizeof(PT_TROOP_AFFECT_COLLISION_BUILDING_DATA);
				characterPack->packetNum++;

			}
		}
//9
		{
			std::map<PlayerCharacterIdType, PT_SKILL_C2M_TROOP_AFFECT_COLLISION_MONSTER_DATA>::iterator front = mMapTpAffectMt.begin();
			std::map<PlayerCharacterIdType, PT_SKILL_C2M_TROOP_AFFECT_COLLISION_MONSTER_DATA>::iterator back = mMapTpAffectMt.end();
			for(; front != back; ++front)
			{ 
				if ( prepareSendDataSize + sizeof(PT_TROOP_AFFECT_COLLISION_MONSTER_DATA) >= dataPtr->getLogicDataMaxSize() )
				{
					ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
						prepareSendDataSize );

                    dataPtr = getSendBuff( characterPack );
                    prepareSendDataSize  = sendDataHeadSize;
				}

				PT_TROOP_AFFECT_COLLISION_MONSTER_DATA* playerCharacterInjectEndData = (PT_TROOP_AFFECT_COLLISION_MONSTER_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
				playerCharacterInjectEndData->type = PT_TROOP_AFFECT_COLLISION_MONSTER;

				playerCharacterInjectEndData->packet = front->second;
				prepareSendDataSize += sizeof(PT_TROOP_AFFECT_COLLISION_MONSTER_DATA);
				characterPack->packetNum++;

			}
		}
//10
		{
			std::map<PlayerCharacterIdType, PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_PLAYERCHARACTER_DATA>::iterator front = mMapBdAffectPc.begin();
			std::map<PlayerCharacterIdType, PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_PLAYERCHARACTER_DATA>::iterator back = mMapBdAffectPc.end();
			for(; front != back; ++front)
			{ 
				if ( prepareSendDataSize + sizeof(PT_BUILDING_AFFECT_COLLISION_PLAYERCHARACTER_DATA) >= dataPtr->getLogicDataMaxSize() )
				{
					ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
						prepareSendDataSize );

                    dataPtr = getSendBuff( characterPack );
                    prepareSendDataSize  = sendDataHeadSize;
				}

				PT_BUILDING_AFFECT_COLLISION_PLAYERCHARACTER_DATA* playerCharacterInjectEndData = (PT_BUILDING_AFFECT_COLLISION_PLAYERCHARACTER_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
				playerCharacterInjectEndData->type = PT_BUILDING_AFFECT_COLLISION_PLAYERCHARACTER;

				playerCharacterInjectEndData->packet = front->second;
				prepareSendDataSize += sizeof(PT_BUILDING_AFFECT_COLLISION_PLAYERCHARACTER_DATA);
				characterPack->packetNum++;

			}
		}
//11
		{
			std::map<PlayerCharacterIdType, PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_BUILDING_DATA>::iterator front = mMapBdAffectBd.begin();
			std::map<PlayerCharacterIdType, PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_BUILDING_DATA>::iterator back = mMapBdAffectBd.end();
			for(; front != back; ++front)
			{ 
				if ( prepareSendDataSize + sizeof(PT_BUILDING_AFFECT_COLLISION_BUILDING_DATA) >= dataPtr->getLogicDataMaxSize() )
				{
					ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
						prepareSendDataSize );

                    dataPtr = getSendBuff( characterPack );
                    prepareSendDataSize  = sendDataHeadSize;
				}

				PT_BUILDING_AFFECT_COLLISION_BUILDING_DATA* playerCharacterInjectEndData = (PT_BUILDING_AFFECT_COLLISION_BUILDING_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
				playerCharacterInjectEndData->type = PT_BUILDING_AFFECT_COLLISION_BUILDING;

				playerCharacterInjectEndData->packet = front->second;
				prepareSendDataSize += sizeof(PT_BUILDING_AFFECT_COLLISION_BUILDING_DATA);
				characterPack->packetNum++;

			}
		}
//12
		{
			std::map<PlayerCharacterIdType, PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_TROOP_DATA>::iterator front = mMapBdAffectTp.begin();
			std::map<PlayerCharacterIdType, PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_TROOP_DATA>::iterator back = mMapBdAffectTp.end();
			for(; front != back; ++front)
			{ 
				if ( prepareSendDataSize + sizeof(PT_BUILDING_AFFECT_COLLISION_TROOP_DATA) >= dataPtr->getLogicDataMaxSize() )
				{
					ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
						prepareSendDataSize );

                    dataPtr = getSendBuff( characterPack );
                    prepareSendDataSize  = sendDataHeadSize;
				}

				PT_BUILDING_AFFECT_COLLISION_TROOP_DATA* playerCharacterInjectEndData = (PT_BUILDING_AFFECT_COLLISION_TROOP_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
				playerCharacterInjectEndData->type = PT_BUILDING_AFFECT_COLLISION_TROOP;

				playerCharacterInjectEndData->packet = front->second;
				prepareSendDataSize += sizeof(PT_BUILDING_AFFECT_COLLISION_TROOP_DATA);
				characterPack->packetNum++;

			}
		}
//13
		{
			std::map<PlayerCharacterIdType, PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_MONSTER_DATA>::iterator front = mMapBdAffectMt.begin();
			std::map<PlayerCharacterIdType, PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_MONSTER_DATA>::iterator back = mMapBdAffectMt.end();
			for(; front != back; ++front)
			{ 
				if ( prepareSendDataSize + sizeof(PT_BUILDING_AFFECT_COLLISION_MONSTER_DATA) >= dataPtr->getLogicDataMaxSize() )
				{
					ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
						prepareSendDataSize );

                    dataPtr = getSendBuff( characterPack );
                    prepareSendDataSize  = sendDataHeadSize;
				}

				PT_BUILDING_AFFECT_COLLISION_MONSTER_DATA* playerCharacterInjectEndData = (PT_BUILDING_AFFECT_COLLISION_MONSTER_DATA*)(characterPack->data + (prepareSendDataSize - sendDataHeadSize));
				playerCharacterInjectEndData->type = PT_BUILDING_AFFECT_COLLISION_MONSTER;

				playerCharacterInjectEndData->packet = front->second;
				prepareSendDataSize += sizeof(PT_BUILDING_AFFECT_COLLISION_MONSTER_DATA);
				characterPack->packetNum++;

			}
		}

        //---------------------------------------------------------------------------------------------
		if ( dataPtr.isNull() == false )
		{
            if ( characterPack && (characterPack->packetNum > 0) )
            {
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    prepareSendDataSize );
                dataPtr.setNull();
            }
		}

        //---------------------------------------------------------------------------------------------

		mPlayerCharacterMovePakectList.clear();
		mPlayerCharacterStopMovePakectList.clear();
		mPlayerCharacterClantPakectList.clear();
		mPlayerCharacterInjectEndPakectList.clear();
		mPlayerCharacterInjectObjectPakectList.clear();
		mPlayerCharacterInjectPointPakectList.clear();
		mPlayerCharacterInjectEmitterPakectList.clear();

		mTroopMovePakectListNew.clear();
		mTroopStopMovePakectListNew.clear();

		mTroopUseSkillPakectList.clear();

		mTroopMovePakectList.clear();
		mTroopStopMovePakectList.clear();
		mTroopClantPakectList.clear();
		mTroopEndInjectPakectList.clear();
		mTroopInjectObjectPakectList.clear();
		mTroopInjectEmitterPakectList.clear();
		mTroopInjectPointPakectList.clear();

		//mMonsterMovePakectList.clear();
		//mMonsterStopMovePakectList.clear();
		//mMonsterClantPakectList.clear();
		//mMonsterInjectEndPakectList.clear();
		//mMonsterInjectObjectPakectList.clear();
		//mMonsterInjectEmitterPakectList.clear();
		//mMonsterInjectPointPakectList.clear();

		mMapPcAffectPc.clear();
		mMapPcAffectTp.clear();	
		mMapPcAffectBd.clear();
		mMapPcAffectMt.clear();

		mMapMtAffectPc.clear();
		mMapMtAffectTp.clear();
		mMapMtAffectBd.clear();
		mMapMtAffectMt.clear();

		mMapTpAffectTp.clear();
		mMapTpAffectPc.clear();
		mMapTpAffectBd.clear();
		mMapTpAffectMt.clear();

		mMapBdAffectPc.clear();
		mMapBdAffectBd.clear();
		mMapBdAffectTp.clear();
		mMapBdAffectMt.clear();
	}

}