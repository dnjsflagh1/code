/******************************************************************************/
#include "stdafx.h"
#include "CAIEntityGroupPathFindingPursueAttackInAdvance.h"
#include "CAIManager.h"
#include "CAIEntityPathFindingPursueAttackInAdvance.h"
#include "CCharacterSceneEntity.h"
/******************************************************************************/

namespace MG
{

    //--------------------------------------------------------------------------

    Str CAIEntityGroupPathFindingPursueAttackInAdvance::STATE_NAME = "CAIEntityGroupPathFindingPursueAttackInAdvance";

    //--------------------------------------------------------------------------
    CAIEntityGroupPathFindingPursueAttackInAdvance::CAIEntityGroupPathFindingPursueAttackInAdvance()
        :CAIEntityGroup(STATE_NAME)
		, mTargetType(GOT_UNKNOWN)
		, mTargetId(0)
		, mTargetIndex(0)
    {

    }

    //--------------------------------------------------------------------------
    CAIEntityGroupPathFindingPursueAttackInAdvance::~CAIEntityGroupPathFindingPursueAttackInAdvance()
    {

    }

    //-----------------------------------------------------------------------
    void CAIEntityGroupPathFindingPursueAttackInAdvance::update( Flt delta )
    {


    }

    //-----------------------------------------------------------------------
    Bool CAIEntityGroupPathFindingPursueAttackInAdvance::isFinished()
    {


        return false;
    }

    //-----------------------------------------------------------------------
    void CAIEntityGroupPathFindingPursueAttackInAdvance::onEnter()
    {
		CCharacterSceneEntity* characterEntity = NULL;

		for( std::map<GAMEOBJ_TYPE,AIEntityTypeGroupList>::iterator gameObjectIt = mGameObjectList.begin(); gameObjectIt != mGameObjectList.end(); ++gameObjectIt)
		{
			for(std::map<IdType, AIEntityGroupList>::iterator entityGroupIt = gameObjectIt->second.objectGroupList.begin(); entityGroupIt != gameObjectIt->second.objectGroupList.end(); ++entityGroupIt)
			{
				for(std::map<IdType, AIEntity>::iterator entityTypeGroupIt = entityGroupIt->second.objectList.begin(); entityTypeGroupIt != entityGroupIt->second.objectList.end(); ++entityTypeGroupIt)
				{
					characterEntity = entityTypeGroupIt->second.entity;
					if(!characterEntity || characterEntity->getDynamicData()->isDied)
					{
						continue;
					}

					CAIEntityPathFindingPursueAttackInAdvance* ai = CAIManager::getInstance().createCAIEntityPathFindingPursueAttackInAdvance(entityTypeGroupIt->second.entity); 
					if(mTargetId != 0)
					{
						ai->setTarget(mTargetType, mTargetId, mTargetIndex);
					}
					else
					{
						ai->setTarget(mTargetPos);
					}

					ai->setUseSkillId(mSkillId);
					ai->setAIEntityGroup(this);
					ai->setIsSelectTargetObject(true);
					
					characterEntity->getAIStateManager().push(ai);
				}
			}
		}
    }

    //-----------------------------------------------------------------------
    void CAIEntityGroupPathFindingPursueAttackInAdvance::onLeave()
    {

    }

	//-----------------------------------------------------------------------
	void CAIEntityGroupPathFindingPursueAttackInAdvance::setTarget(GAMEOBJ_TYPE gameType, GameObjectIdType id, UInt index)
	{
		mTargetType = gameType;
		mTargetId = id;
		mTargetIndex = index;
	}

	//-----------------------------------------------------------------------
	void CAIEntityGroupPathFindingPursueAttackInAdvance::setTarget(Vec3 pos)
	{
		mTargetPos = pos;
	}

	//-----------------------------------------------------------------------
	void CAIEntityGroupPathFindingPursueAttackInAdvance::setUseSkillId(IdType skillId)
	{
		mSkillId = skillId;
	}

}