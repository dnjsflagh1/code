/******************************************************************************/
#include "stdafx.h"
#include "SFightMainManager.h"
#include "SFightManager.h"
#include "SCharacter.h"
#include "SWorldManager.h"
/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------------
	SFightMainManager::SFightMainManager()
	{

	}

	//-----------------------------------------------------------------------------
	SFightMainManager::~SFightMainManager()
	{

	}

	//-----------------------------------------------------------------------
	void SFightMainManager::addAndUpdateFightOnAppoint( SCharacter* fightCharacter, SCharacter* fightOtherCharacter )
	{

	}

	//-----------------------------------------------------------------------
	void SFightMainManager::addAndUpdateFightOnUseAttackSkill( SCharacter* fightCharacter, SCharacter* fightOtherCharacter, UInt hateVal )
	{
		SFightManager* fightManager = fightOtherCharacter->getFightManager();
		if(!fightManager)
		{
			return;
		}

		fightManager->addAndUpdateFightInfo(fightCharacter, fightOtherCharacter->getID(), hateVal);

		fightManager = fightCharacter->getFightManager();
		if(!fightManager)
		{
			return;
		}

		fightManager->addAndUpdateFightInfo(fightOtherCharacter, fightOtherCharacter->getID(), 0);
	}

	//-----------------------------------------------------------------------
	void SFightMainManager::addAndUpdateFightOnGuard( SCharacter* fightCharacter, SCharacter* fightOtherCharacter )
	{
		SFightManager* fightManager = fightOtherCharacter->getFightManager();
		if(!fightManager)
		{
			return;
		}

		fightManager->addAndUpdateFightInfo(fightCharacter, fightCharacter->getID(), 0);

		fightManager = fightCharacter->getFightManager();
		if(!fightManager)
		{
			return;
		}

		fightManager->addAndUpdateFightInfo(fightOtherCharacter, fightCharacter->getID(), 5);
	}

	//-----------------------------------------------------------------------
	void SFightMainManager::addAndUpdateFightOnUseAuxiliarySkill( SCharacter* fightCharacter, SCharacter* fightOtherCharacter, UInt hateVal )
	{
		addAndUpdateAllFight(fightCharacter , fightOtherCharacter, hateVal, false);
	}

	//-----------------------------------------------------------------------
	void SFightMainManager::delFightOnScope( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID )
	{

	}

	//-----------------------------------------------------------------------
	void SFightMainManager::delFightOnEndTime( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID )
	{

	}

	//-----------------------------------------------------------------------
	void SFightMainManager::delFightOnPursue( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID )
	{

	}

	//-----------------------------------------------------------------------
	void SFightMainManager::delAllFightInfo( SCharacter* character )
	{
		character->clearFightAITriggerCount();

		SFightManager* fightManager = character->getFightManager();
		if(!fightManager)
		{
			return;
		}

		std::map<IdType, FightInfo>* fightInfoList = fightManager->getFightInfoList();

		SCharacter* fightOtherCharacter = NULL;
		InstanceUIdType currInstanceId = character->getCharacterData()->mInstanceUId;

		for( std::map<IdType, FightInfo>::iterator it = fightInfoList->begin(); it != fightInfoList->end(); ++it )
		{
			((SCharacter*)it->second.fightObject)->getFightManager()->delFightInfo(character);
		}

		fightManager->delAllFightInfo();
	}

	//-----------------------------------------------------------------------
	void SFightMainManager::addAndUpdateAllFight( SCharacter* fightCharacter, SCharacter* fightOtherCharacter, UInt hateVal, Bool isOwnerAdd )
	{
		SFightManager* fightManager = NULL;

		std::map<IdType, FightInfo>* fightInfoList = NULL;
		if(isOwnerAdd)
		{
			fightManager = fightCharacter->getFightManager();
			if(!fightManager)
			{
				return;
			}

			fightInfoList = fightManager->getFightInfoList();

			for( std::map<IdType, FightInfo>::iterator it = fightInfoList->begin(); it != fightInfoList->end(); ++it )
			{
				it->second.hateVal += hateVal;
			}
		}
		else
		{
			fightInfoList = fightOtherCharacter->getFightManager()->getFightInfoList();

			//SCharacter* character = NULL;
			for(std::map<IdType, FightInfo>::iterator it = fightInfoList->begin(); it != fightInfoList->end(); ++it)
			{
				//character = SWorldManager::getInstance().getCharacterFromMemory(fightCharacter->getRegionType(), fightCharacter->getRegionID(), fightCharacter->getCurrentRealRegionObject()->getInstanceUId(), it->second.fightObject->getType(), it->second.fightObject->getID());
				//if(!character)
				//{
				//	continue;
				//}

				fightManager = fightCharacter->getFightManager();
				if(!fightManager)
				{
					continue;
				}

				fightManager->addAndUpdateFightInfo(fightOtherCharacter, fightCharacter->getID(), hateVal);
			}
		}

	}
}

