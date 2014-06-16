/******************************************************************************/
#include "stdafx.h"
#include "CAIEntityPathFindingMoveInAdvance.h"
#include "IActionManager.h"
#include "CCharacterSceneEntity.h"
#include "IBlockManager.h"
#include "PlayCharacterNetPacketProcesser.h"
#include "MonsterNetPacketProcesser.h"
#include "CTroopSoldierEntity.h"
#include "CTroopEntity.h"
#include "TroopNetPacketProcesser.h"
#include "IDynamicBlockObject.h"
#include "CPlayer.h"
#include "CAIGroup.h"
#include "CSceneManager.h"
#include "ClientMain.h"

/******************************************************************************/

namespace MG
{

#define RESUMECHECKBLOCK 1500
#define RESUMEPATNFINDTIME 1500


    //--------------------------------------------------------------------------

    Str CAIEntityPathFindingMoveInAdvance::STATE_NAME = "CAIEntityPathFindingMoveInAdvance";

    //--------------------------------------------------------------------------
    CAIEntityPathFindingMoveInAdvance::CAIEntityPathFindingMoveInAdvance( CCharacterSceneEntity* characterSceneEntity )
        :LinedStateObject(STATE_NAME)
		,mCharacterSceneEntity(characterSceneEntity)
		,mPathFindingMoveInAdvanceAction(NULL)
		,mPauseThinkTime(0)
		,mMoveLength(0)
		,mPatherRadius(0)
		,mBlockDiameter(0)
		,mState(AIEMT_NORMAL)
		,mAIEntityGroup(NULL)
		,mCheckBlockTime(0)
		,mIsBlockCheck(true)
		,mIsStartDynamicFind(true)
		,mStartPathFindTime(0)
		,mIsStaticMove(true)
		,mIsPathFinderWait(false)
    {
    }

    //--------------------------------------------------------------------------
    CAIEntityPathFindingMoveInAdvance::~CAIEntityPathFindingMoveInAdvance()
    {
    }

    //-----------------------------------------------------------------------
    void CAIEntityPathFindingMoveInAdvance::update( Flt delta )
    {
		if(mCharacterSceneEntity->getDynamicData()->isDied || !mCharacterSceneEntity->getIsCanMove())
		{
			destroy();
			return;
		}

		checkAndUpdateState(delta);
    }

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingMoveInAdvance::onEnter()
	{
		if(mCharacterSceneEntity->getDynamicData()->isDied || !mCharacterSceneEntity->getIsCanMove())
		{
			destroy();
			return;
		}

        mPauseThinkTime = 0;
        mTotleThinkTime = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////

		mCharacterSceneEntity->getActionStateManager().addListener( this ); 

		ISceneNode* sceneNode = mCharacterSceneEntity->getEntity()->getSceneNode();

        ////////////////////////////////////////////////////////////////////////////////////////////////

		// ������̬�ϰ�����
		IDynamicBlockObject* dynamicBlockObject = mCharacterSceneEntity->getEntity()->createOrRetrieveDynamicBlockObject();

		// ����Ѱ·�㷨����
		mPathFindingMoveInAdvanceAction = sceneNode->getScene()->getActionManager()->createSceneNodePathFindingMoveInAdvanceAction(dynamicBlockObject);
		// ����Ŀ���,Ȼ�����Ŀ���
		if ( mPathFindingMoveInAdvanceAction->setMoveToDestination(mDestination , true) == false )
        {
            destroy();
            return;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////

		// ��������
		Vec3 currPos;
		sceneNode->getPosition(currPos);
		currPos.y = 0;
		mStaticCurrDestinationNodePos = currPos;
		// �õ�Ѱ·�뾶
		mPatherRadius = mCharacterSceneEntity->getEntity()->getModelObject()->getPatherRadius();
		// ͨ���뾶�������ռ�������С
		mBlockDiameter = mPatherRadius * 2 / sceneNode->getScene()->getBlockManager()->getDynamicBlockGridSize();

		// �ж�Ŀ����Ƿ�Ϊ��̬�ϰ�����������˳�
		// TODO:֮����Ҫ������߽�㣬Ȼ���ƶ����߽��
		if( sceneNode->getScene()->getBlockManager()->isStaticBlock(mDestination) )
		{
			destroy();
			return;
		}

        ////////////////////////////////////////////////////////////////////////////////////////////////

		// ��ʼ���㾲̬Ѱ·,�����Ч���˳�
        if ( calculateAndDoStaticPathFinding() == PFR_ERROR )
            return;

		// ����״̬Ϊ��̬Ѱ·�ƶ�
		mState = AIEMT_STATICMOVE;
		mRealDestination = mDestination;
		mRealDestination.y = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////

		// �����߼���ɫ����״̬Ϊ�ƶ�
		mCharacterSceneEntity->setIsMoving(true);

		mCheckBlockTime = MGTimeOp::getCurrTick();
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingMoveInAdvance::onLeave()
	{
		mCharacterSceneEntity->getActionStateManager().removeListener( this ); 

		ISceneNode* sceneNode = mCharacterSceneEntity->getEntity()->getSceneNode();

		// �ͷ�Ѱ·����
		sceneNode->getScene()->getActionManager()->destroySceneNodePathFindingMoveInAdvanceAction(mPathFindingMoveInAdvanceAction);
		mCharacterSceneEntity->setIsMoving(false);

		if (CSceneManager::getInstance().isLoadingScene()==false) 
			requestStopMove();
	}

	//-----------------------------------------------------------------------
	Bool CAIEntityPathFindingMoveInAdvance::isFinished()
	{
		// ���㵱ǰ���Ŀ���ľ����Ƿ�С�ڽ����ľ��룬����ǵĻ����˳�
		return isArriveOnDestination( mRealDestination );
	}

	//###################################################################################################################################

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingMoveInAdvance::checkAndUpdateState( Flt delta )
	{

        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // ����һ������ֹͣ˼��    

        if ( mTotleThinkTime > 1000 )
        {
            destroy();
        }else
        {
            mTotleThinkTime += delta;
        }

		///////////////////////////////////////////////////////////////////////////////////////////////////

		// ֹͣ˼��ʱ��β�����AI
        // һ���ڷ���������Ϣ��ĵȴ�
		if ( mPauseThinkTime > 0 )
		{
			mPauseThinkTime -= delta;
			return;
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////

		if( MGTimeOp::getCurrTick() - mCheckBlockTime >= RESUMECHECKBLOCK)
		{
			mIsBlockCheck  = true;
		}

		if( MGTimeOp::getCurrTick() > mStartPathFindTime )
		{
			mIsStartDynamicFind = true;
		}

		// �õ��ײ���ƶ���Ϊ����ĵ�ǰ״̬
        CMoveAcionState moveActionState = getMoveAcionState();

		// ���Ϊ�ȴ�����Ҫִ��AI
        // һ��Ϊ��ʱ����������̬�ϰ���ĵȴ�
		if ( moveActionState==MAS_MOVEWAIT )
        {
			mIsPathFinderWait = false;
            //
			return ;
        }else
		// ������ƶ�����Ҫִ��AI
		if ( moveActionState==MAS_MOVING )
        {
			mIsPathFinderWait = false;
            //
			return ;
        }else
		// ���Ϊֹͣ����Ҫ���¼���Ѱ·
        // һ��Ϊ��ʱ��������̬�ϰ����ֹͣ
		if (  moveActionState==MAS_MOVESTOP && mIsBlockCheck )
		{
			if(mIsBlockCheck == true)
			{
				if(!mIsPathFinderWait)
				{
					mStartPathFindTime = MGTimeOp::getCurrTick() + 300;
					mIsStartDynamicFind = false;
					mIsPathFinderWait = true;
				};

				if(!mIsStartDynamicFind)
				{
					return;
				}

				// ��ʱ���¼��㶯̬�ϰ�
				PathFindingResult pathFindingResult = calculateAndDoDynamicPathFinding();
				if ( pathFindingResult == PFR_ALREADY_ARRIVE )
				{
					// ����Ѿ������յ����˳�
					if ( mPathFindingMoveInAdvanceAction->isLastStaticDestination() )
					{
						destroy();
					}else
					{
						mState = AIEMT_STATICMOVE;
					}
				}
				//else if( pathFindingResult == PFR_LOSE_WAY )
				//{
				//	destroy();
				//}
				else if( pathFindingResult != PFR_SUCCESS )
				{
					mIsBlockCheck = false;
					mCheckBlockTime = MGTimeOp::getCurrTick();
				}

				mStartPathFindTime = MGTimeOp::getCurrTick() + RESUMEPATNFINDTIME;
				mIsStartDynamicFind = false;
				mIsPathFinderWait = false;
			}

            // �˳�
			return;
		}else
        // û�п�ʼ�ײ���ƶ���Ϊ
        if ( moveActionState==MAS_NULL )
        {
            // һ��ֻ��һ��ʼ����ִ����
        }

		///////////////////////////////////////////////////////////////////////////////////////////////////

		if ( mState == AIEMT_DYNAMICMOVE )
		{
			if ( mPathFindingMoveInAdvanceAction->isLastDynamicDestination() )
			{
                // ����Ƕ�̬Ѱ·����ɵ�ʱ�� �Ϳ��Լ�����һ����̬Ѱ·��
				mState = AIEMT_STATICMOVE;
			}else
			{
				if ( isArriveOnDestination(mDynamicCurrDestinationNodePos) )
				{
                    // �����̬Ѱ·��ǰ���Ѿ����ˣ��������һ���ڵ�
					mDynamicCurrDestinationNodePos = mPathFindingMoveInAdvanceAction->goNextDynamicDestination();
					requestMoveTo(mDynamicCurrDestinationNodePos, mIsBlockCheck);
				}else
				{
					requestMoveTo(mDynamicCurrDestinationNodePos, mIsBlockCheck);
					//DYNAMIC_ASSERT( false );
				}
			}
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////

		if ( mState == AIEMT_STATICMOVE )
		{
			if ( mPathFindingMoveInAdvanceAction->isLastStaticDestination() )
			{
                // ����ƶ���Ŀ������˳�
				if( isArriveOnDestination(mDestination) )
				{
					destroy();
				}else
                {
                    // ischeck
                    if ( false )
                    {
                        calculateAndDoStaticPathFinding();
                    }else
                    {
						if(moveActionState == MAS_MOVESTOP)
						{
							requestMoveTo(mDestination, mIsBlockCheck);
						}
                        //DYNAMIC_ASSERT_LOG( false, "not path find last static node" );
					    //destroy();
                    }
                }
			}else
            {
                if ( isArriveOnDestination(mStaticCurrDestinationNodePos) )
                {
                    // �����̬Ѱ·��ǰ���Ѿ����ˣ��������һ���ڵ�
                    mStaticCurrDestinationNodePos = mPathFindingMoveInAdvanceAction->goNextStaticDestination();
                    requestMoveTo(mStaticCurrDestinationNodePos, mIsBlockCheck);
                }else
                {
                    // ischeck
                    if ( false )
                    {
                        requestMoveTo(mStaticCurrDestinationNodePos, mIsBlockCheck);
                    }else
                    {
                        //DYNAMIC_ASSERT_LOG( false, "not path find curr static node" );
                        destroy();
                    }
                }
            }
		}
	}


    //-----------------------------------------------------------------------
    PathFindingResult CAIEntityPathFindingMoveInAdvance::calculateAndDoStaticPathFinding()
    {
        PathFindingResult result = mPathFindingMoveInAdvanceAction->calculateStaticPathFinding();
        // ��ʼ���㾲̬Ѱ·,�����Ч���˳�
        if( result == PFR_ERROR )
        {
            destroy();
        }else
        if( result == PFR_ALREADY_ARRIVE )
        {
            destroy();
        }else
        {
            mStaticCurrDestinationNodePos = mPathFindingMoveInAdvanceAction->goNextStaticDestination();

            mState = AIEMT_STATICMOVE;	

            requestMoveTo(mStaticCurrDestinationNodePos, mIsBlockCheck);
        }

		mIsStaticMove = true;


        //if ( isCheckStaticAccessiblePos )
        //{
        //    Vec3 currStaticPosNode = mPathFindingMoveInAdvanceAction->getCurrStaticDestination();
        //    Vec3 accessibleDestination;

        //    if ( getNearestAccessiblePos( currStaticPosNode, accessibleDestination ) )
        //    {
        //        mStaticNodePos = accessibleDestination;
        //        mPathFindingMoveInAdvanceAction->setCurrStaticDestination(accessibleDestination);

        //        mState = AIEMT_STATICMOVE;//��������������requestMoveTo(mStaticNodePos)ǰ��

        //        requestMoveTo(mStaticNodePos);
        //    }else
        //    {
        //        stopThink(2);
        //    }
        //}

        return result;
    }

    //-----------------------------------------------------------------------
    PathFindingResult CAIEntityPathFindingMoveInAdvance::calculateAndDoDynamicPathFinding()
    {
        PathFindingResult result = mPathFindingMoveInAdvanceAction->calculateDynamicPathFindingBetweenStaticNode();

        if( result != PFR_ERROR )
        {
			if( result != PFR_LOSE_WAY )
			{
				if( result != PFR_ALREADY_ARRIVE ) 
				{
					mDynamicCurrDestinationNodePos = mPathFindingMoveInAdvanceAction->goNextDynamicDestination();

					mState = AIEMT_DYNAMICMOVE;	

					requestMoveTo(mDynamicCurrDestinationNodePos, mIsBlockCheck);
				}
			}
        }

		mIsStaticMove = false;

        return result;
    }

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingMoveInAdvance::stopThink( Flt time )
	{
		mPauseThinkTime = time;
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingMoveInAdvance::resumeThink()
	{
		mPauseThinkTime = 0;
	}

	//-----------------------------------------------------------------------
	Bool CAIEntityPathFindingMoveInAdvance::isArriveOnDestination( Vec3 des )
	{
		Vec3 currPos;
		mCharacterSceneEntity->getEntity()->getSceneNode()->getPosition(currPos);
		currPos.y = 0;
		des.y = 0;

		Flt dis = ( des - currPos ).length();

		// TODO:
		if(dis <= 1)
		{
			return true;
		}

		return false;
	}

	//-----------------------------------------------------------------------
	Bool CAIEntityPathFindingMoveInAdvance::getNearestAccessiblePos( Vec3 centerPos, Vec3& nearestAccessiblePos )
	{
		Vec3 currPos;
		mCharacterSceneEntity->getEntity()->getSceneNode()->getPosition(currPos);
		currPos.y = 0;
		centerPos.y = 0;

		Vec3 dir = currPos - centerPos;
		Flt disLen = dir.length();

		dir.normalise();

		Bool result = CSceneManager::getInstance().getEngineScene()->getBlockManager()->getPosNearestAccessiblePos(centerPos, dir, disLen, mBlockDiameter, nearestAccessiblePos);

		return result;
	}

    //-----------------------------------------------------------------------
    CMoveAcionState CAIEntityPathFindingMoveInAdvance::getMoveAcionState()
    {
        LinedStateObject* stateObj = mCharacterSceneEntity->getActionStateManager().getState( CCSEntityLineMoveAcion::STATE_NAME, true );
        if ( stateObj )
        {
            CCSEntityLineMoveAcion* moveAction = dynamic_cast<CCSEntityLineMoveAcion*>(stateObj);
            if ( moveAction )
            {
                CMoveAcionState blockState = moveAction->getMoveAcionState();
                return blockState;
            }
        }

        return MAS_NULL;
    }

    //-----------------------------------------------------------------------
    void CAIEntityPathFindingMoveInAdvance::setDestination(Vec3 pos)
    {
        mDestination = pos;
		mDestination.y = 0;
    }

	 //-----------------------------------------------------------------------
	void CAIEntityPathFindingMoveInAdvance::setUnblockPosDestination(Vec3 pos)
	{
		DYNAMIC_ASSERT(mCharacterSceneEntity);

		IDynamicBlockObject* dynamicBlockObject = mCharacterSceneEntity->getEntity()->createOrRetrieveDynamicBlockObject();
		if(!dynamicBlockObject)
		{
			mDestination = pos;
			return;
		}

		Vec3 currPos = mCharacterSceneEntity->getPos();
		pos.y = 0;

		Vec3 dir = currPos - pos;
		Flt dis = dir.length();
		dir.normalise();

		Vec3 destination;
		//if(ClientMain::getInstance().getScene()->getBlockManager()->getPosNearestAccessiblePos(pos, dir, dis, dynamicBlockObject->getDynamicBlockGridDiameter(), destination))
		//{
		//	mDestination = destination;
		//}
		//else
		//{
			mDestination = pos;
		//}
	}	

    //-----------------------------------------------------------------------
	Vec3 CAIEntityPathFindingMoveInAdvance::getDestination()
	{
		return mRealDestination;
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingMoveInAdvance::requestStopMove()
	{
		if(mCharacterSceneEntity->getType() == GOT_SOLDIER)
		{
			CTroopSoldierEntity* troopSoldierEntity = (CTroopSoldierEntity*)mCharacterSceneEntity;

            if ( ClientMain::getInstance().isConsole() )
            {
			    troopSoldierEntity->stopMoveToAction();
            }else
            {
				CClan* clan = CPlayer::getInstance().getActiveClan();
				if(!clan)
				{
					return;
				}

                //TroopNetPacketProcesser::getInstance().sendTroopSoldierStopMoveToPackBuffer(
                //    clan->getFocusRegionType(), 
                //    clan->getFocusRegionID(), 
                //    CPlayer::getInstance().getInstanceUid(), 
                //    troopSoldierEntity->getTroopEntity()->getID(), 
                //    troopSoldierEntity->getID());
            }
		}
		else if(mCharacterSceneEntity->getType() == GOT_TROOP)
		{

			if ( ClientMain::getInstance().isConsole() )
			{
				mCharacterSceneEntity->stopMoveToAction();
			}else
			{
				CClan* clan = CPlayer::getInstance().getActiveClan();
				if(!clan)
				{
					return;
				}

				//TroopNetPacketProcesser::getInstance().sendTroopEntityStopMoveToPackBuffer(clan->getFocusRegionType(), CPlayer::getInstance().getActiveClan()->getFocusRegionID(), CPlayer::getInstance().getInstanceUid(), mCharacterSceneEntity->getID());
			}
		}
		else
		{
            if ( ClientMain::getInstance().isConsole() )
            {
                mCharacterSceneEntity->stopMoveToAction();
            }else
            {
                PlayCharacterNetPacketProcesser::getInstance().sendPlayerCharacterStopMoveToPackBuffer(mCharacterSceneEntity->getID());
            }
		}
	}
	
	//-----------------------------------------------------------------------
	void CAIEntityPathFindingMoveInAdvance::requestMoveTo( Vec3 moveToPos, Bool isBlockCheck )
	{

        ////////////////////////////////////////////////////////////////////////////////////////

        // ֹͣ˼��2���ӣ����յ���Ӧ��ʱ��Żָ�˼��
        stopThink(2000);

		////////////////////////////////////////////////////////////////////////////////////////

		Vec3 currPos;
		mCharacterSceneEntity->getEntity()->getSceneNode()->getPosition(currPos);
		currPos.y = 0;

        mRequestStartPosition = currPos;
 
		////////////////////////////////////////////////////////////////////////////////////////

		if(mCharacterSceneEntity->getType() == GOT_PLAYERCHARACTER)
		{
            if ( ClientMain::getInstance().isConsole() )
            {   
				ISceneNodeGridLineMoveToAction::MoveToPathFindType moveToPathFindType = ISceneNodeGridLineMoveToAction::PFT_DYNAMIC;
				Bool isStaticMove = getIsStaticMove();
				if(isStaticMove)
				{
					moveToPathFindType = ISceneNodeGridLineMoveToAction::PFT_STATIC;
				}
				else
				{
					moveToPathFindType = ISceneNodeGridLineMoveToAction::PFT_DYNAMIC;
				}

                mCharacterSceneEntity->doMoveToAction(currPos, moveToPos, 0, mIsBlockCheck, moveToPathFindType);
            }else
            {
			    PlayCharacterNetPacketProcesser::getInstance().sendPlayerCharacterMoveToPackBuffer(
                    mCharacterSceneEntity->getID(), 
                    currPos, 
                    moveToPos,
					mIsBlockCheck);
            }
		}
		else if(mCharacterSceneEntity->getType() == GOT_SOLDIER)
		{
            CTroopSoldierEntity* troopSoldierEntity = (CTroopSoldierEntity*)mCharacterSceneEntity;

            if ( ClientMain::getInstance().isConsole() )
            {  
                troopSoldierEntity->doMoveToAction(currPos, moveToPos, 0, mIsBlockCheck);
            }else
            {
				CClan* clan = CPlayer::getInstance().getActiveClan();
				if(!clan)
				{
					return;
				}

                //TroopNetPacketProcesser::getInstance().sendTroopSoldierMoveToPackBuffer(
                //    clan->getFocusRegionType(), 
                //    clan->getFocusRegionID(), 
                //    CPlayer::getInstance().getInstanceUid(), 
                //    troopSoldierEntity->getTroopEntity()->getID(), 
                //    troopSoldierEntity->getID(), 
                //    currPos, 
                //    moveToPos);
            }
		}
		else if(mCharacterSceneEntity->getType() == GOT_MONSTER)
		{
	//		MonsterNetPacketProcesser::getInstance().sendMonsterMoveToPackBuffer(mCharacterSceneEntity->getID(), currPos, moveToPos);
		}
		else if(mCharacterSceneEntity->getType() == GOT_TROOP)
		{
            if ( ClientMain::getInstance().isConsole() )
            { 

				ISceneNodeGridLineMoveToAction::MoveToPathFindType moveToPathFindType = ISceneNodeGridLineMoveToAction::PFT_DYNAMIC;

				Bool isStaticMove = getIsStaticMove();
				if(isStaticMove)
				{
					moveToPathFindType = ISceneNodeGridLineMoveToAction::PFT_STATIC;
				}
				else
				{
					moveToPathFindType = ISceneNodeGridLineMoveToAction::PFT_DYNAMIC;
				}

                mCharacterSceneEntity->doMoveToAction(currPos, moveToPos, 0, mIsBlockCheck, moveToPathFindType);

            }else
            {
				CClan* clan = CPlayer::getInstance().getActiveClan();
				if(!clan)
				{
					return;
				}

				//TroopNetPacketProcesser::getInstance().sendTroopEntityMoveToPackBuffer(
				//	clan->getFocusRegionType(), 
				//	clan->getFocusRegionID(), 
				//	CPlayer::getInstance().getInstanceUid(), 
				//	mCharacterSceneEntity->getID(), 
				//	currPos, 
				//	moveToPos, mIsBlockCheck);
            }
		}
		else
        {
            DYNAMIC_ASSERT( false );
        }

		////////////////////////////////////////////////////////////////////////////////////////
	}

	//-----------------------------------------------------------------------
	CCharacterSceneEntity*	CAIEntityPathFindingMoveInAdvance::getOwner()
	{
		return mCharacterSceneEntity;
	}

	//-----------------------------------------------------------------------
	Bool CAIEntityPathFindingMoveInAdvance::getIsStaticMove()
	{
		return mIsStaticMove;
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingMoveInAdvance::setAIEntityGroup( CAIEntityGroup* aiEntityGroup )
	{
		mAIEntityGroup = aiEntityGroup;
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingMoveInAdvance::onLinedStateAdd(LinedStateObject* obj)
	{
		if ( obj->getName() == CCSEntityLineMoveAcion::STATE_NAME )
		{
			resumeThink();
		}
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingMoveInAdvance::onLinedStateRemove(LinedStateObject* obj)
	{
		
	}


}