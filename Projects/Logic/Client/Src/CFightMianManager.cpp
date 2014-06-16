/******************************************************************************/
#include "stdafx.h"
#include "CFightMainManager.h"
#include "CTroopEntity.h"
#include "CCharacterSceneEntity.h"
#include "CSceneManager.h"
#include "FightManager.h"
/******************************************************************************/

namespace MG
{
	////-----------------------------------------------------------------------------
	//CFightMainManager::CFightMainManager()
	//{

	//}

	////-----------------------------------------------------------------------------
	//CFightMainManager::~CFightMainManager()
	//{

	//}

	////-----------------------------------------------------------------------
	//void CFightMainManager::addAndUpdateFightOnAppoint( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID )
	//{
	//
	//}

	////-----------------------------------------------------------------------
	//void CFightMainManager::addAndUpdateFightOnUseAttackSkill( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID, IdType skillId, IdType addHateGameObjID, UInt hateVal )
	//{
	//	if(fightOtherObjectType == GOT_TROOP)
	//	{
	//		CTroopObject* fightOtherTroop = CSceneManager::getInstance().getTroopObject(fightOtherObjectID);
	//		if(!fightOtherTroop)
	//		{
	//			return;
	//		}

	//		fightOtherTroop->getFightManager()->addAndUpdateFightInfo(fightObjectType, fightObjectID, fightObjectID, 0);
	//	}
	//	else
	//	{
	//		CCharacterSceneEntity* fightOtherEntity = CSceneManager::getInstance().getCharacterSceneEntity(fightOtherObjectType, fightOtherObjectID);
	//		if(!fightOtherEntity)
	//		{
	//			return;
	//		}

	//		fightOtherEntity->getFightManager()->addAndUpdateFightInfo(fightObjectType, fightObjectID, fightObjectID, 0);
	//	}

	//	if(fightObjectType == GOT_TROOP)
	//	{
	//		CTroopObject* fightTroop = CSceneManager::getInstance().getTroopObject(fightObjectID);
	//		if(!fightTroop)
	//		{
	//			return;
	//		}

	//		fightTroop->getFightManager()->addAndUpdateFightInfo(fightOtherObjectType, fightOtherObjectID, fightObjectID, hateVal);
	//	}
	//	else
	//	{
	//		CCharacterSceneEntity* fightEntity = CSceneManager::getInstance().getCharacterSceneEntity(fightObjectType, fightObjectID);
	//		if(!fightEntity)
	//		{
	//			return;
	//		}

	//		fightEntity->getFightManager()->addAndUpdateFightInfo(fightOtherObjectType, fightOtherObjectID, fightObjectID, hateVal);
	//	}
	//}

	////-----------------------------------------------------------------------
	//void CFightMainManager::addAndUpdateFightOnGuard( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID )
	//{
	//	if(fightOtherObjectType == GOT_TROOP)
	//	{
	//		CTroopObject* fightOtherTroop = CSceneManager::getInstance().getTroopObject(fightOtherObjectID);
	//		if(!fightOtherTroop)
	//		{
	//			return;
	//		}

	//		fightOtherTroop->getFightManager()->addAndUpdateFightInfo(fightObjectType, fightObjectID, fightObjectID, 0);
	//	}
	//	else
	//	{
	//		CCharacterSceneEntity* fightOtherEntity = CSceneManager::getInstance().getCharacterSceneEntity(fightOtherObjectType, fightOtherObjectID);
	//		if(!fightOtherEntity)
	//		{
	//			return;
	//		}

	//		fightOtherEntity->getFightManager()->addAndUpdateFightInfo(fightObjectType, fightObjectID, fightObjectID, 0);
	//	}

	//	if(fightObjectType == GOT_TROOP)
	//	{
	//		CTroopObject* fightTroop = CSceneManager::getInstance().getTroopObject(fightObjectID);
	//		if(!fightTroop)
	//		{
	//			return;
	//		}

	//		fightTroop->getFightManager()->addAndUpdateFightInfo(fightOtherObjectType, fightOtherObjectID, fightObjectID, 10);
	//	}
	//	else
	//	{
	//		CCharacterSceneEntity* fightEntity = CSceneManager::getInstance().getCharacterSceneEntity(fightObjectType, fightObjectID);
	//		if(!fightEntity)
	//		{
	//			return;
	//		}

	//		fightEntity->getFightManager()->addAndUpdateFightInfo(fightOtherObjectType, fightOtherObjectID, fightObjectID, 10);
	//	}
	//}

	////-----------------------------------------------------------------------
	//void CFightMainManager::addAndUpdateFightOnUseAuxiliarySkill( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID, UInt hateVal )
	//{
	//	if(fightObjectType == GOT_TROOP)
	//	{
	//		CTroopObject* fightTroop = CSceneManager::getInstance().getTroopObject(fightObjectID);
	//		if(!fightTroop)
	//		{
	//			return;
	//		}


	//		addAndUpdateAllFight(fightObjectType, fightObjectID, fightOtherObjectType, fightOtherObjectID, hateVal, false);
	//	}
	//	else
	//	{
	//		CCharacterSceneEntity* fightEntity = CSceneManager::getInstance().getCharacterSceneEntity(fightObjectType, fightObjectID);
	//		if(!fightEntity)
	//		{
	//			return;
	//		}

	//		addAndUpdateAllFight(fightObjectType, fightObjectID, fightOtherObjectType, fightOtherObjectID, hateVal, false);
	//	}
	//}

	////-----------------------------------------------------------------------
	//void CFightMainManager::delFightOnScope( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID )
	//{

	//}

	////-----------------------------------------------------------------------
	//void CFightMainManager::delFightOnEndTime( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID )
	//{
	//
	//}

	////-----------------------------------------------------------------------
	//void CFightMainManager::delFightOnPursue( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID )
	//{
	//	
	//}

	////-----------------------------------------------------------------------
	//void CFightMainManager::delAllFightInfo( GAMEOBJ_TYPE gameObjectType, IdType gameObjectID )
	//{
	//	FightManager* fightManager = NULL;
	//	std::map<IdType, FightInfo>* fightInfoList = NULL;

	//	if(gameObjectType == GOT_TROOP)
	//	{
	//		CTroopObject* troopObject = CSceneManager::getInstance().getTroopObject(gameObjectID);
	//		if(!troopObject)
	//		{
	//			return;
	//		}
	//		
	//		troopObject->clearFightAITriggerCount();

	//		fightManager = troopObject->getFightManager();
	//		if(!fightManager)
	//		{
	//			return;
	//		}
	//	}
	//	else
	//	{
	//		CCharacterSceneEntity* characterEntity = CSceneManager::getInstance().getCharacterSceneEntity(gameObjectType, gameObjectID);
	//		if(!characterEntity)
	//		{
	//			return;
	//		}

	//		characterEntity->clearFightAITriggerCount();

	//		fightManager = characterEntity->getFightManager();
	//		if(!fightManager)
	//		{
	//			return;
	//		}
	//	}

	//	fightInfoList = fightManager->getFightInfoList();
	//	for( std::map<IdType, FightInfo>::iterator it = fightInfoList->begin(); it != fightInfoList->end(); ++it )
	//	{
	//		if(it->second.fightObject->getType() == GOT_TROOP)
	//		{
	//			CTroopObject* fightObjectTroop = CSceneManager::getInstance().getTroopObject(it->second.fightObjectID);
	//			if(!fightObjectTroop)
	//			{
	//				return;
	//			}

	//			fightObjectTroop->getFightManager()->delFightInfo(gameObjectType, gameObjectID);
	//		}
	//		else
	//		{
	//			CCharacterSceneEntity* fightObjectEntity = CSceneManager::getInstance().getCharacterSceneEntity(it->second.fightObject->getType(), it->second.fightObjectID);
	//			if(!fightObjectEntity)
	//			{
	//				return;
	//			}

	//			fightObjectEntity->getFightManager()->delFightInfo(gameObjectType, gameObjectID);
	//		}
	//	}

	//	fightManager->delAllFightInfo();
	//}

	////-----------------------------------------------------------------------
	//void CFightMainManager::addAndUpdateAllFight( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID, UInt hateVal, Bool isOwnerAdd )
	//{
	//	std::map<IdType, FightInfo>* fightInfoList = NULL;

	//	if(fightObjectType == GOT_TROOP)
	//	{
	//		CTroopObject* fightTroop = CSceneManager::getInstance().getTroopObject(fightObjectID);
	//		if(!fightTroop)
	//		{
	//			return;
	//		}

	//		fightInfoList = fightTroop->getFightManager()->getFightInfoList();
	//	}
	//	else
	//	{
	//		CCharacterSceneEntity* fightEntity = CSceneManager::getInstance().getCharacterSceneEntity(fightObjectType, fightObjectID);
	//		if(!fightEntity)
	//		{
	//			return;
	//		}

	//		fightInfoList = fightEntity->getFightManager()->getFightInfoList();
	//	}

	//	if(isOwnerAdd)
	//	{
	//		for( std::map<IdType, FightInfo>::iterator it = fightInfoList->begin(); it != fightInfoList->end(); ++it )
	//		{
	//			it->second.hateVal += hateVal;
	//		}
	//	}
	//	else
	//	{
	//		for( std::map<IdType, FightInfo>::iterator it = fightInfoList->begin(); it != fightInfoList->end(); ++it )
	//		{
	//			if(it->second.fightObject->getType() == GOT_TROOP)
	//			{
	//				CTroopObject* fightObjectTroop = CSceneManager::getInstance().getTroopObject(it->second.fightObjectID);
	//				if(!fightObjectTroop)
	//				{
	//					return;
	//				}

	//				fightObjectTroop->getFightManager()->addAndUpdateFightInfo(fightOtherObjectType, fightOtherObjectID, fightObjectID, hateVal);
	//			}
	//			else
	//			{
	//				CCharacterSceneEntity* fightObjectEntity = CSceneManager::getInstance().getCharacterSceneEntity(it->second.fightObject->getType(), it->second.fightObjectID);
	//				if(!fightObjectEntity)
	//				{
	//					return;
	//				}

	//				fightObjectEntity->getFightManager()->addAndUpdateFightInfo(fightOtherObjectType, fightOtherObjectID, fightObjectID, hateVal);
	//			}
	//		}
	//	}
	//}

	////-----------------------------------------------------------------------
	//FightManager* CFightMainManager::getFightManager( GAMEOBJ_TYPE gameObjType, IdType gameObjID )
	//{
	//	FightManager* fightManager = NULL;

	//	if(gameObjType != GOT_TROOP)
	//	{
	//		CTroopObject* troopObject = CSceneManager::getInstance().getTroopObject(gameObjID);
	//		if(!troopObject)
	//		{
	//			return false;
	//		}

	//		fightManager = troopObject->getFightManager();
	//	}
	//	else
	//	{
	//		CCharacterSceneEntity* characterSceneEntity = CSceneManager::getInstance().getCharacterSceneEntity(gameObjType, gameObjID);
	//		if(!characterSceneEntity)
	//		{
	//			return false;
	//		}

	//		fightManager = characterSceneEntity->getFightManager();
	//	}

	//	return fightManager;
	//}
}