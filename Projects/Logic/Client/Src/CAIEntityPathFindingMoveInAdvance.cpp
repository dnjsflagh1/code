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

		// 创建动态障碍对象
		IDynamicBlockObject* dynamicBlockObject = mCharacterSceneEntity->getEntity()->createOrRetrieveDynamicBlockObject();

		// 创建寻路算法对象
		mPathFindingMoveInAdvanceAction = sceneNode->getScene()->getActionManager()->createSceneNodePathFindingMoveInAdvanceAction(dynamicBlockObject);
		// 设置目标点,然后调整目标点
		if ( mPathFindingMoveInAdvanceAction->setMoveToDestination(mDestination , true) == false )
        {
            destroy();
            return;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////

		// 计算数据
		Vec3 currPos;
		sceneNode->getPosition(currPos);
		currPos.y = 0;
		mStaticCurrDestinationNodePos = currPos;
		// 得到寻路半径
		mPatherRadius = mCharacterSceneEntity->getEntity()->getModelObject()->getPatherRadius();
		// 通过半径计算出所占用网格大小
		mBlockDiameter = mPatherRadius * 2 / sceneNode->getScene()->getBlockManager()->getDynamicBlockGridSize();

		// 判断目标点是否为静态障碍，如果是则退出
		// TODO:之后需要计算出边界点，然后移动到边界点
		if( sceneNode->getScene()->getBlockManager()->isStaticBlock(mDestination) )
		{
			destroy();
			return;
		}

        ////////////////////////////////////////////////////////////////////////////////////////////////

		// 开始计算静态寻路,如果无效则退出
        if ( calculateAndDoStaticPathFinding() == PFR_ERROR )
            return;

		// 设置状态为静态寻路移动
		mState = AIEMT_STATICMOVE;
		mRealDestination = mDestination;
		mRealDestination.y = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////

		// 设置逻辑角色对象状态为移动
		mCharacterSceneEntity->setIsMoving(true);

		mCheckBlockTime = MGTimeOp::getCurrTick();
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingMoveInAdvance::onLeave()
	{
		mCharacterSceneEntity->getActionStateManager().removeListener( this ); 

		ISceneNode* sceneNode = mCharacterSceneEntity->getEntity()->getSceneNode();

		// 释放寻路对象
		sceneNode->getScene()->getActionManager()->destroySceneNodePathFindingMoveInAdvanceAction(mPathFindingMoveInAdvanceAction);
		mCharacterSceneEntity->setIsMoving(false);

		if (CSceneManager::getInstance().isLoadingScene()==false) 
			requestStopMove();
	}

	//-----------------------------------------------------------------------
	Bool CAIEntityPathFindingMoveInAdvance::isFinished()
	{
		// 计算当前点和目标点的距离是否小于结束的距离，如果是的话则退出
		return isArriveOnDestination( mRealDestination );
	}

	//###################################################################################################################################

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingMoveInAdvance::checkAndUpdateState( Flt delta )
	{

        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // 超过一分钟则停止思考    

        if ( mTotleThinkTime > 1000 )
        {
            destroy();
        }else
        {
            mTotleThinkTime += delta;
        }

		///////////////////////////////////////////////////////////////////////////////////////////////////

		// 停止思考时间段不进行AI
        // 一般在发送网络消息后的等待
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

		// 得到底层的移动行为对象的当前状态
        CMoveAcionState moveActionState = getMoveAcionState();

		// 如果为等待则不需要执行AI
        // 一般为短时间内遇到动态障碍后的等待
		if ( moveActionState==MAS_MOVEWAIT )
        {
			mIsPathFinderWait = false;
            //
			return ;
        }else
		// 如果在移动则不需要执行AI
		if ( moveActionState==MAS_MOVING )
        {
			mIsPathFinderWait = false;
            //
			return ;
        }else
		// 如果为停止则需要重新计算寻路
        // 一般为长时间遇到动态障碍后的停止
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

				// 此时重新计算动态障碍
				PathFindingResult pathFindingResult = calculateAndDoDynamicPathFinding();
				if ( pathFindingResult == PFR_ALREADY_ARRIVE )
				{
					// 如果已经到了终点则退出
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

            // 退出
			return;
		}else
        // 没有开始底层的移动行为
        if ( moveActionState==MAS_NULL )
        {
            // 一般只有一开始会出现此情况
        }

		///////////////////////////////////////////////////////////////////////////////////////////////////

		if ( mState == AIEMT_DYNAMICMOVE )
		{
			if ( mPathFindingMoveInAdvanceAction->isLastDynamicDestination() )
			{
                // 如果是动态寻路段完成的时候 就可以继续下一个静态寻路段
				mState = AIEMT_STATICMOVE;
			}else
			{
				if ( isArriveOnDestination(mDynamicCurrDestinationNodePos) )
				{
                    // 如果动态寻路当前点已经到了，则继续下一个节点
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
                // 如果移动到目标点则退出
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
                    // 如果静态寻路当前点已经到了，则继续下一个节点
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
        // 开始计算静态寻路,如果无效则退出
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

        //        mState = AIEMT_STATICMOVE;//单击版把这个放在requestMoveTo(mStaticNodePos)前面

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

        // 停止思考2分钟，当收到响应的时候才恢复思考
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