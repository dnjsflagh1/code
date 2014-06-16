/******************************************************************************/
#include "stdafx.h"
#include "SFightManager.h"
#include "GameObject.h"
#include "SCharacter.h"
#include "SPlayerCharacterNetPacketProcesser.h"
#include "SMonsterNetPacketProcesser.h"
#include "STroopNetPacketProcesser.h"
#include "SMonster.h"
#include "STroop.h"
/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------------
	SFightManager::SFightManager( GameObject* owner )
		:FightManager(owner)
	{

	}

	//-----------------------------------------------------------------------------
	SFightManager::~SFightManager()
	{

	}

	//------------------------------------------------------------------------------------
	FightInfo* SFightManager::addFightInfo( IdType fightInfoID, GameObject* fightObject, UInt hateVal )
	{
		if(mFightList.size() == 0)
		{
			mEnterFightPos = ((SCharacter*)mOwner)->getPos();
		}

		FightInfo* fightInfo = FightManager::addFightInfo(fightInfoID, fightObject, hateVal);

		return fightInfo;
	}

	//------------------------------------------------------------------------------------
	void SFightManager::notifyEnterFight( GameObject* fightObject )
	{
		FightManager::notifyEnterFight(fightObject);

		GAMEOBJ_TYPE gameObjType = fightObject->getType();
		if(gameObjType == GOT_PLAYERCHARACTER)
		{
			SPlayerCharacterNetPacketProcesser::getInstance().broadcastPlayerCharacterEnterFight((SPlayerCharacter*)fightObject);
		}
		else if(gameObjType == GOT_MONSTER)
		{
			SMonster* monster = (SMonster*)fightObject;
			monster->setMoveSpeed(monster->getSAttributeSystem()->getRideSpeed());
			SMonsterNetPacketProcesser::getInstance().broadcastMonsterEnterFight(monster);
		}
		else if(gameObjType == GOT_TROOP)
		{
			STroopNetPacketProcesser::getInstance().broadcastTroopEnterFight((STroop*)fightObject);
		}
	}

	//------------------------------------------------------------------------------------
	void SFightManager::notifyEndFight( GameObject* fightObject )
	{
		FightManager::notifyEndFight(fightObject);

		GAMEOBJ_TYPE gameObjType = fightObject->getType();
		if(gameObjType == GOT_PLAYERCHARACTER)
		{
			SPlayerCharacterNetPacketProcesser::getInstance().broadcastPlayerCharacterEndFight((SPlayerCharacter*)fightObject);
		}
		else if(gameObjType == GOT_MONSTER)
		{
			SMonster* monster = (SMonster*)fightObject;
			monster->setMoveSpeed(monster->getSAttributeSystem()->getMoveSpeed());
			SMonsterNetPacketProcesser::getInstance().broadcastMonsterEndFight(monster);
		}
		else if(gameObjType == GOT_TROOP)
		{
			STroopNetPacketProcesser::getInstance().broadcastTroopEndFight((STroop*)fightObject);
		}
	}




}