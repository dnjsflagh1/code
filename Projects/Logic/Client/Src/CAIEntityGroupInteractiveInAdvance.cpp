/******************************************************************************/
#include "stdafx.h"
#include "CAIEntityGroupInteractiveInAdvance.h"
#include "CAIEntityInteractiveInAdvance.h"
#include "CAIManager.h"
#include "CCharacterSceneEntity.h"
/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------

	Str CAIEntityGroupInteractiveInAdvance::STATE_NAME = "CAIEntityGroupInteractiveInAdvance";

	//--------------------------------------------------------------------------
	CAIEntityGroupInteractiveInAdvance::CAIEntityGroupInteractiveInAdvance()
		:CAIEntityGroup(STATE_NAME)
		,mSceneEntity(NULL)
	{

	}

	//--------------------------------------------------------------------------
	CAIEntityGroupInteractiveInAdvance::~CAIEntityGroupInteractiveInAdvance()
	{

	}

	//-----------------------------------------------------------------------
	void CAIEntityGroupInteractiveInAdvance::update( Flt delta )
	{


	}

	//-----------------------------------------------------------------------
	Bool CAIEntityGroupInteractiveInAdvance::isFinished()
	{


		return false;
	}

	//-----------------------------------------------------------------------
	void CAIEntityGroupInteractiveInAdvance::onEnter()
	{
		for( std::map<GAMEOBJ_TYPE,AIEntityTypeGroupList>::iterator gameObjectIt = mGameObjectList.begin(); gameObjectIt != mGameObjectList.end(); ++gameObjectIt)
		{
			switch(gameObjectIt->first)
			{
			case GOT_PLAYERCHARACTER:
				for(std::map<IdType, AIEntityGroupList>::iterator entityGroupIt = gameObjectIt->second.objectGroupList.begin(); entityGroupIt != gameObjectIt->second.objectGroupList.end(); ++entityGroupIt)
				{
					for(std::map<IdType, AIEntity>::iterator entityIt = entityGroupIt->second.objectList.begin(); entityIt != entityGroupIt->second.objectList.end(); ++entityIt)
					{
						CAIEntityInteractiveInAdvance* ai = CAIManager::getInstance().createCAIEntityInteractiveInAdvance(entityIt->second.entity); 
						ai->setTargetSceneEntity(mSceneEntity);
						entityIt->second.entity->getAIStateManager().push(ai);
					}
				}

				break;
			}
		}
	}

	//-----------------------------------------------------------------------
	void CAIEntityGroupInteractiveInAdvance::onLeave()
	{

	}

	//--------------------------------------------------------------------------
	void CAIEntityGroupInteractiveInAdvance::setTargetSceneEntity(CSceneEntity* sceneEntity)
	{
		mSceneEntity = sceneEntity;
	}
}