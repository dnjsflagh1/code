/******************************************************************************/
#include "stdafx.h"
#include "CAIEntityRandomPathFindingMoveAndGuardInAdvance.h"
#include "CAIEntityPathFindingMoveAndGuardInAdvance.h"
#include "CCharacterSceneEntity.h"
#include "CAIManager.h"
/******************************************************************************/

namespace MG
{

    //--------------------------------------------------------------------------

    Str CAIEntityRandomPathFindingMoveAndGuardInAdvance::STATE_NAME = "CAIEntityRandomPathFindingMoveAndGuardInAdvance";

    //--------------------------------------------------------------------------
    CAIEntityRandomPathFindingMoveAndGuardInAdvance::CAIEntityRandomPathFindingMoveAndGuardInAdvance( CCharacterSceneEntity* characterSceneEntity )
        :LinedStateObject(STATE_NAME)
		,mCharacterSceneEntity(characterSceneEntity)
		,mGuardRadius(0)
    {

    }

    //--------------------------------------------------------------------------
    CAIEntityRandomPathFindingMoveAndGuardInAdvance::~CAIEntityRandomPathFindingMoveAndGuardInAdvance()
    {

    }

    //-----------------------------------------------------------------------
    void CAIEntityRandomPathFindingMoveAndGuardInAdvance::update( Flt delta )
    {
		Vec3 currPos = mCharacterSceneEntity->getPos();
		if((currPos - mDestination).length() <= 1)
		{
			mDestination = getRandomMoveToPos();
			CAIEntityPathFindingMoveAndGuardInAdvance*  pathFindingMoveAndGuardInAdvance = CAIManager::getInstance().createCAIEntityPathFindingMoveAndGuardInAdvance(mCharacterSceneEntity);
			pathFindingMoveAndGuardInAdvance->setDestination(mDestination);

			mCharacterSceneEntity->getAIStateManager().push(pathFindingMoveAndGuardInAdvance, false);
		}

    }

    //-----------------------------------------------------------------------
    Bool CAIEntityRandomPathFindingMoveAndGuardInAdvance::isFinished()
    {


        return false;
    }

    //-----------------------------------------------------------------------
    void CAIEntityRandomPathFindingMoveAndGuardInAdvance::onEnter()
    {
		if(mCharacterSceneEntity->getDynamicData()->isDied)
		{
			destroy();
			return;
		}

		Vec3 currPos = mCharacterSceneEntity->getPos();
    }

    //-----------------------------------------------------------------------
    void CAIEntityRandomPathFindingMoveAndGuardInAdvance::onLeave()
    {

    }

	//-----------------------------------------------------------------------
	Vec3 CAIEntityRandomPathFindingMoveAndGuardInAdvance::getRandomMoveToPos()
	{
		Vec3 dir(1,0,0);
		Int angle = MGRandom::getInstance().rand_ab_One(0, 360);
		Int dis = MGRandom::getInstance().rand_ab_One(0, mGuardRadius);
		dir = MGMath::rotateVector(dir, angle * (MG_PI / 180));
		return mCharacterSceneEntity->getPos() + dir * dis;
	}


}