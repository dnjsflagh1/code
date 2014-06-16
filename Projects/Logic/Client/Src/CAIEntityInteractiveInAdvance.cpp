/******************************************************************************/
#include "stdafx.h"
#include "CAIEntityInteractiveInAdvance.h"
#include "CAIManager.h"
#include "CCharacterSceneEntity.h"
#include "IBlockManager.h"
#include "ClientMain.h"
#include "UINpc.h"
#include "UISelectPlace.h"
#include "COrdinaryBuildingEntity.h"
#include "CSceneManager.h"
#include "OrdinaryBuildingData.h"
#include "UIInteractiveControl.h"
/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------

	Str CAIEntityInteractiveInAdvance::STATE_NAME = "CAIEntityInteractiveInAdvance";

	//--------------------------------------------------------------------------
	CAIEntityInteractiveInAdvance::CAIEntityInteractiveInAdvance( CCharacterSceneEntity* characterSceneEntity )
		:LinedStateObject(STATE_NAME)
		,mCharacterSceneEntity(characterSceneEntity)
		,mPathFindingMoveAI(NULL)
        ,mState(IAS_NULL)
		,mIsFinished(false)
	{

	}

	//--------------------------------------------------------------------------
	CAIEntityInteractiveInAdvance::~CAIEntityInteractiveInAdvance()
	{

	}

	//-----------------------------------------------------------------------
	void CAIEntityInteractiveInAdvance::update( Flt delta )
	{
		if(mCharacterSceneEntity->getDynamicData()->isDied)
		{
			destroy();
			return;
		}

		switch(mState)
		{
		case IAS_MOVETO:
			updateMoveToPos();
			break;

		case IAS_INTERACTIVE:
			updateInteractive();
			break;
		}
	}

	//-----------------------------------------------------------------------
	Bool CAIEntityInteractiveInAdvance::isFinished()
	{
		return mIsFinished;
	}

	//-----------------------------------------------------------------------
	void CAIEntityInteractiveInAdvance::onEnter()
	{
		if(mCharacterSceneEntity->getDynamicData()->isDied)
		{
			destroy();
			return;
		}

        mTargetSceneEntity = getTargetSceneEntity();
        if ( mTargetSceneEntity == NULL )
        {
            destroy();
            return;
        }

		mInteractiveDis = getInteractiveDis(mCharacterSceneEntity, mTargetSceneEntity);

		mTargetSceneEntity->getEntity()->getSceneNode()->getPosition(mDestination);
		mDestination.y = 0;

		mPathFindingMoveAI = CAIManager::getInstance().createCAIEntityPathFindingMoveInAdvance(mCharacterSceneEntity);
		mPathFindingMoveAI->setDestination(mDestination);
        mPathFindingMoveAI->addListener( this );
		mCharacterSceneEntity->getAIStateManager().push(mPathFindingMoveAI, false);

		mState = IAS_MOVETO;
	}

	//-----------------------------------------------------------------------
	void CAIEntityInteractiveInAdvance::onLeave()
	{
        if ( mPathFindingMoveAI )
        {
            mPathFindingMoveAI->destroy();
        }
	}

    //--------------------------------------------------------------------------
    void CAIEntityInteractiveInAdvance::setTargetSceneEntity(CSceneEntity* sceneEntity)
    {
        mTargetSceneEntity      =   sceneEntity;
        if ( mTargetSceneEntity )
        {
            mTargetSceneEntityType  =   sceneEntity->getType();
            mTargetSceneEntityID    =   sceneEntity->getID();
        }
    }

    //--------------------------------------------------------------------------
    CSceneEntity* CAIEntityInteractiveInAdvance::getTargetSceneEntity()
    {
        if ( mTargetSceneEntity )
        {
            CSceneEntity* entity = CSceneManager::getInstance().getSceneEntity( mTargetSceneEntityID, mTargetSceneEntityType );
            if ( mTargetSceneEntity==entity )
            {
                return mTargetSceneEntity;
            }else
            {
                mTargetSceneEntity = NULL;
            }
        }

        return NULL;
    }

    //--------------------------------------------------------------------------
    void CAIEntityInteractiveInAdvance::onLinedStateLifeTimeOver(LinedStateObject* obj)
    {
        if ( mPathFindingMoveAI == obj )
        {
            mPathFindingMoveAI = NULL;
        }
    }

	//--------------------------------------------------------------------------
	Flt CAIEntityInteractiveInAdvance::getInteractiveDis( CCharacterSceneEntity* owner, CSceneEntity* target )
	{
		IEntity* entity = owner->getEntity();
		Flt targetSceneEntityWidth = target->getEntity()->getModelObject()->getPatherRadius();
		Flt	ownerSceneEntityWidth = owner->getEntity()->getModelObject()->getWidth();

		Flt dis = targetSceneEntityWidth + ownerSceneEntityWidth;

		return dis;
	}

	//--------------------------------------------------------------------------
	void CAIEntityInteractiveInAdvance::updateMoveToPos()
	{
		Flt dis = (mDestination - mCharacterSceneEntity->getPos()).length();

		if(mInteractiveDis >= dis)
		{
			if ( mPathFindingMoveAI )
			{
				mPathFindingMoveAI->destroy();
				mPathFindingMoveAI = NULL;
			}
			mState = IAS_INTERACTIVE;
		}
	}

	//--------------------------------------------------------------------------
	void CAIEntityInteractiveInAdvance::updateInteractive()
	{
        /////////////////////////////////////////////////////////////////////////////////////////////////////

        mState = IAS_NULL;
        mIsFinished = true;

        /////////////////////////////////////////////////////////////////////////////////////////////////////

        mTargetSceneEntity = getTargetSceneEntity();
        if ( mTargetSceneEntity == NULL )
        {
            return;
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////

		GAMEOBJ_TYPE gameObjectType = mTargetSceneEntity->getType();
		if(gameObjectType == GOT_NPC)
		{
			Str strTemplateID = mTargetSceneEntity->getEntity()->getCustomAttr("CharID");
			Int templateID;
			if ( strTemplateID.empty() == false )
			{
				MGStrOp::toI32(strTemplateID.c_str(),templateID);
			}
			UINpc::getInstance().openGeneralTalkDialog(templateID, mCharacterSceneEntity->getID());
			UIInteractiveControl::getInstance().setInteractiveObject(mTargetSceneEntity->getID(),mCharacterSceneEntity->getID(),gameObjectType);

			Vec3 targetPos;
			mTargetSceneEntity->getWorldPos(targetPos);
			targetPos.y = 0;

			Vec3 dir = mCharacterSceneEntity->getPos() - targetPos;
			dir.normalise();

			mTargetSceneEntity->getEntity()->getSceneNode()->setDirection(dir);

			mTargetSceneEntity->playAnimation("hi", false);
		}
		else if(gameObjectType == GOT_ORDINARY_BUILDING)
		{
			COrdinaryBuildingEntity* ordinaryBuildingEntity = (COrdinaryBuildingEntity*)mTargetSceneEntity;
			if(ordinaryBuildingEntity->getDynamicData()->buildingType == OBLT_PLACE)
			{
				Str& placeIdStr = ordinaryBuildingEntity->getEntity()->getCustomAttr("PlaceID");
				I32 placeId = -1;
				if ( placeIdStr.empty() == false )
				{
					MGStrOp::toI32(placeIdStr.c_str(),placeId);
				}
				DYNAMIC_ASSERT(placeId > 0);
				UISelectPlace::getInstance().openPlaceDialog(placeId,mCharacterSceneEntity->getID());
				UIInteractiveControl::getInstance().setInteractiveObject(mTargetSceneEntity->getID(),mCharacterSceneEntity->getID(),gameObjectType);

			}
		}
		else if(gameObjectType == GOT_ITEM)
		{
			OperationObjectGroup* currOperationObjectGroup =  GameObjectOpCtrl::getInstance().getCurrOperationObjectGroup();
			if(currOperationObjectGroup)
			{
				currOperationObjectGroup->pickItem((CItemEntity*)mTargetSceneEntity);
			}
		}
	}

}