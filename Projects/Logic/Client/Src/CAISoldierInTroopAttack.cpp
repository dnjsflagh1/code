/******************************************************************************/
#include "stdafx.h"
#include "CAISoldierInTroopAttack.h"
#include "CSceneManager.h"
#include "CCharacterSceneEntity.h"
#include "SkillBaseInfo.h"
#include "CSkillUseManager.h"
#include "SkillNetPacketProcesser.h"
#include "SkillInfoList.h"
#include "ShortRangeGeneralAttackSkillTemplate.h"
#include "LongRangeGeneralAttackSkillTemplate.h"
#include "SingleTargetSkillTemplate.h"
#include "CAIManager.h"
#include "IBlockManager.h"
#include "ClientMain.h"
#include "CAITroopObjectSendSkillPacket.h"
#include "CTroopSoldierEntity.h"
#include "CTroopEntity.h"
#include "CharacterSkillTempLate.h"
#include "SkillBaseInfo.h"
#include "CPlayer.h"
#include "CSkillOwnManager.h"
#include "CharacterList.h"
#include "CAIController.h"
#include "CActionManager.h"
/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------

	Str CAISoldierInTroopAttack::STATE_NAME = "CAISoldierInTroopAttack";

	//--------------------------------------------------------------------------
	CAISoldierInTroopAttack::CAISoldierInTroopAttack( CTroopEntity* troopEntity )
		:mTroopEntity(troopEntity)
	{

	}

	//--------------------------------------------------------------------------
	CAISoldierInTroopAttack::~CAISoldierInTroopAttack()
	{

	}

	//-----------------------------------------------------------------------
	void CAISoldierInTroopAttack::setUseSkill( IdType skillId )
	{
		mSkillId = skillId;
	}

	//-----------------------------------------------------------------------
	void CAISoldierInTroopAttack::setTarget( GAMEOBJ_TYPE targetType, IdType targetId, Vec3 taegetPos )
	{
		mTargetType = targetType;
		mTargetId = targetId;
		mTaegetPos = taegetPos;
	}

	//-----------------------------------------------------------------------
	void CAISoldierInTroopAttack::onUseSkill()
	{
		std::map<UInt, CTroopSoldierEntity*>* troopSoldierEntityList = mTroopEntity->getSoldierEntitysList();
		if(!troopSoldierEntityList)
		{
			return;
		}

		CCharacterSceneEntity* targetCharacter = CSceneManager::getInstance().getCharacterSceneEntity(mTargetType, mTargetId);
		if(!targetCharacter || targetCharacter->getDynamicData()->isDied)
		{
			return;
		}

		LinedStateObject* linedStateObject = NULL;

		Bool isFinished = true;

		CSkillObject* skillObject = NULL;

		CTroopSoldierEntity* troopSoldierEntity = NULL;
		CCSEntityInjectSkillAcion* injectSkillAcion = NULL;

		Flt delayPushTime = 0;

		for(std::map<UInt, CTroopSoldierEntity*>::iterator it = troopSoldierEntityList->begin(); it != troopSoldierEntityList->end(); ++it)
		{
			troopSoldierEntity = it->second;
			if(!troopSoldierEntity)
			{
				continue;
			}

			Flt dis = (troopSoldierEntity->getPos() - targetCharacter->getPos()).length();

			UInt multiple = dis / 10;
			if(multiple >= 10)
			{
				delayPushTime = dis / 100;
			}
			else if(multiple >= 1)
			{
				delayPushTime = dis / 10;
			}
			else
			{
				delayPushTime = dis;
			}

			delayPushTime /= 10;

			skillObject = setSkillObject(troopSoldierEntity);
			if(!skillObject)
			{
				continue;
			}

			injectSkillAcion = CActionManager::getInstance().createCCSEntityInjectSkillAcion(skillObject);
			injectSkillAcion->setDelayPushTime(delayPushTime);
			troopSoldierEntity->getActionStateManager().delayPush(injectSkillAcion);
		}
	}

	//-----------------------------------------------------------------------
	CSkillObject* CAISoldierInTroopAttack::setSkillObject( CTroopSoldierEntity* troopSoldierEntity )
	{
		CCharacterSceneEntity* targetCharacter = CSceneManager::getInstance().getCharacterSceneEntity(mTargetType, mTargetId);
		if(!targetCharacter)
		{
			return NULL;
		}

		SkillInfo* skillInfo  = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(mSkillId);
		if(!skillInfo)
		{
			return NULL;
		}

		UInt index = 0;
		GAMEOBJ_TYPE targetType = mTargetType;
		SkillType skillType = skillInfo->skillType;

		CSkillObject* skillObject = (CSkillObject*)troopSoldierEntity->getSkillUseManager()->prepareUseSkill(mSkillId);
		if(!skillObject)
		{
			return skillObject;
		}

		if(skillType == SKT_SELFAREA || skillType == SKT_TARGETPOSAREA || skillType == SKT_PARABOLAAREA)
		{
			skillObject->setTargetPosition(mTaegetPos);
		}
		else if( skillType == SKT_SHORTRANGEGENERAL || skillType == SKT_LONGRANGEGENERAL  || skillType == SKT_SINGLETARGET || skillType == SKT_LONGRANGEAUXILIARY )
		{
			if(targetCharacter->getType() == GOT_TROOP)
			{
				targetType = GOT_SOLDIER;

				index = troopSoldierEntity->getID();
				if( index >= ((CTroopEntity*)targetCharacter)->getSoldierEntitysNum() )
				{
					index = 0;
				}
				
			}

			skillObject->setTargetObject(targetType, mTargetId, index);
		}

		return skillObject;
	}

}