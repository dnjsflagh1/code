******************************************************************************/
#include "stdafx.h"
#include "SAIController.h"
#include "SAISeekHelp.h"
#include "SCharacter.h"
#include "SWorldManager.h"
#include "STroop.h"
#include "WorldCoreDefine.h"

//#include "FightManager.h"
/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------

	Str SAISeekHelp::STATE_NAME = "SAISeekHelp";

	//--------------------------------------------------------------------------
	SAISeekHelp::SAISeekHelp( SCharacter* owner )
		:LinedStateObject(STATE_NAME)
		,SAI(owner)
		,mSeekHelpRadius(0)
		,mTargetType(GOT_UNKNOWN)
		,mTargetId(0)
		,mTargetIndex(0)
	{
		mAIType = AIT_SEEKHELP;
	}

	//--------------------------------------------------------------------------
	SAISeekHelp::~SAISeekHelp()
	{
	}

	//-----------------------------------------------------------------------
	void SAISeekHelp::onEnter()
	{
		if(mOwner->isDead())
		{
			destroy();
			return;
		}

		SRegionObjectBase* regionObject = 0;//mOwner->getCurrentRegionObject();
		if(!regionObject)
		{
			destroy();
			return ;
		}

		Vec3 ownerPos = mOwner->getPos();

		Flt tempDis = 0;
		SMonster* tempMonster = NULL;

#if 0
		std::map<GameObjectIdType, SMonster*>* monsterList = 0;//regionObject->getMonsterList();
		if(monsterList)
		{
			for(std::map<GameObjectIdType, SMonster*>::iterator it = monsterList->begin(); it != monsterList->end(); ++it)
			{
				tempMonster = it->second;
				if(!tempMonster || tempMonster == mOwner)
				{
					continue;
				}

				tempDis = (tempMonster->getPos() - ownerPos).length();
				if(tempDis <= mSeekHelpRadius)
				{
					for(UInt i = 0; i < mSeekHelpTemplateList.size(); ++i)
					{
						if(mSeekHelpTemplateList[i] == tempMonster->getCharacterTemplateID())
						{
							tempMonster->getAIController()->setHelpMoveToState();
						}
					}
				}
			}
		}
#endif
		destroy();
	}

	//-----------------------------------------------------------------------
	void SAISeekHelp::update( Flt delta )
	{

	}

	//-----------------------------------------------------------------------
	void SAISeekHelp::onLeave()
	{

	}

	//-----------------------------------------------------------------------
	Bool SAISeekHelp::isFinished()
	{
		return true;
	}

	//-----------------------------------------------------------------------
	void SAISeekHelp::setSeekHelpRadius( Flt seekHelpRadius )
	{
		mSeekHelpRadius = seekHelpRadius;
	}

	//-----------------------------------------------------------------------
	void SAISeekHelp::setSeekHelpTemplate( std::vector<UInt>& seekHelpTemplateList )
	{
		for(UInt i = 0; i < seekHelpTemplateList.size(); ++i)
		{
			if(seekHelpTemplateList[i] != 0)
			{
				mSeekHelpTemplateList.push_back(seekHelpTemplateList[i]);
			}
			
		}
	}

	//-----------------------------------------------------------------------
	void SAISeekHelp::setTarget( GAMEOBJ_TYPE targetType, IdType targetId, UInt targetIndex )
	{
		mTargetType = targetType;
		mTargetId = targetId;
		mTargetIndex = targetIndex;
	}

}