/******************************************************************************/
#include "stdafx.h"
#include "ScenceNodeGridLineMoveToAction.h"
#include "MGEngineUtility.h"
#include "ISceneNode.h"
#include "IScene.h"
#include "ITerrain.h"
#include "MGSceneNode.h"
#include "LinedState.h"
#include "BlockManager.h"
#include "ITree.h"
#include "IDynamicBlockObject.h"
#include "IBlockObjectSceneManager.h"
/******************************************************************************/

namespace MG
{
	static int lock_value = 2;
	/******************************************************************************/
	//SceneNodeGridLineMoveToAction
	/******************************************************************************/
	Str SceneNodeGridLineMoveToAction::STATE_NAME = "SceneNodeGridLineMoveToAction";
	//-----------------------------------------------------------------------
	SceneNodeGridLineMoveToAction::SceneNodeGridLineMoveToAction( ISceneNode* sceneNode, IDynamicBlockObject* dynamicBlockobject )
		:ISceneNodeGridLineMoveToAction(STATE_NAME)
		,mMoveSpeed(1)
		,mIsMoving(false)
		,mIsStickTerrain(true)
		,mBlockManager(NULL)
		,mSceneNodeRadius(0)
		,mBlockDiameter(0)
		,mIsIgnoreHeight(true)
		,mIsPerturbGrass(false)
		,mPerturbRadiu(2.0f)
		,mPerturbFrequnce(3)
		,mLastPerturbTime(clock())
		,mDynamicBlockObject(dynamicBlockobject)
		,mCurrPassGridBlockListIndex(0)
		,mNextPassGridBlockIndex(0)
        ,mIsRefreshBlock(true)
        ,mIsWait(false)
        ,mIsBlockCheck(true)
		,mSceneNode(sceneNode)
		,mMoveToPathFindType(PFT_DYNAMIC)
	{	 
        IScene* scene = mSceneNode->getScene();
        if(scene)
        {
            mBlockManager = (BlockManager*)scene->getBlockManager();
        }
	}	

	//-----------------------------------------------------------------------
	SceneNodeGridLineMoveToAction::~SceneNodeGridLineMoveToAction()
	{

	}

	//-----------------------------------------------------------------------
	void SceneNodeGridLineMoveToAction::setMoveSpeed( Flt speed )
	{
		mMoveSpeed = speed;
	}

	//-----------------------------------------------------------------------
	void SceneNodeGridLineMoveToAction::setMoveToDestination( const Vec3& dest )
	{
        mMoveDestination = dest;
		if ( mIsIgnoreHeight )
			mMoveDestination.y = 0;
	}

	//-----------------------------------------------------------------------
	void SceneNodeGridLineMoveToAction::setIgnoreHeight( Bool isIgnoreHeight )
	{
		mIsIgnoreHeight = isIgnoreHeight;
	}

	//-----------------------------------------------------------------------
	void SceneNodeGridLineMoveToAction::setMoveToPathFindType( MoveToPathFindType moveToPathFindType )
	{
		mMoveToPathFindType = moveToPathFindType;
	}

    //-----------------------------------------------------------------------
    Bool SceneNodeGridLineMoveToAction::isBlockStop()
    {
        return !mIsRefreshBlock;
    }

    //-----------------------------------------------------------------------
    void SceneNodeGridLineMoveToAction::setBlockCheck( Bool enable )
    {
        mIsBlockCheck = enable;
    }

    //-----------------------------------------------------------------------
    void SceneNodeGridLineMoveToAction::setIsWait( Bool enable )
    {
        mIsWait = enable;

		if(mIsBlockCheck)
		{
			notifyMoveToStateChange();
		}
    }

	//-----------------------------------------------------------------------
	Bool SceneNodeGridLineMoveToAction::getIsWait()
	{
		return mIsWait;
	}

	 //-----------------------------------------------------------------------
	Bool SceneNodeGridLineMoveToAction::getIsMoving()
	{
		return mIsMoving;
	}

	//-----------------------------------------------------------------------
	void SceneNodeGridLineMoveToAction::setStickTerrain( Bool isStickTerrain )
	{
		mIsStickTerrain = isStickTerrain;
	}

	//-----------------------------------------------------------------------
	// 设置是否启用扰动草
	void SceneNodeGridLineMoveToAction::setPerturbEnable( Bool isPerturb )
	{
		mIsPerturbGrass = isPerturb;  
	}

	//-----------------------------------------------------------------------
	// 设置扰动草半径
	void SceneNodeGridLineMoveToAction::setPerturbRadiu( Flt radiu )
	{
		mPerturbRadiu = radiu;
	}

	//-----------------------------------------------------------------------
	// 设置扰动草频率
	void SceneNodeGridLineMoveToAction::setPerturbFrequnce( UInt freq )
	{
		mPerturbFrequnce = freq;
	}

    //-----------------------------------------------------------------------
    void SceneNodeGridLineMoveToAction::onEnter()
    {
		if(!mDynamicBlockObject)
		{
			mIsBlockCheck = false;
		}

        mSceneNode->getPosition( mMoveStartPosition );
        if ( mIsIgnoreHeight )
            mMoveStartPosition.y = 0;

        /////////////////////////////////////////////////////////////////////////////////////

        mMoveLength     = ( mMoveDestination - mMoveStartPosition ).length();

        mMoveVelocityN  = ( mMoveDestination - mMoveStartPosition );
        mMoveVelocityN.normalise();

        /////////////////////////////////////////////////////////////////////////////////////

        mMoveVelocity   = mMoveVelocityN * mMoveSpeed;
        mCurrMoveLength = 0;

        mMoveVelocityN  = mMoveVelocityN * BlockManager::DYNAMIC_BLOCK_GRID_SIZE;
        mIsMoving = true;
        mIsRefreshBlock = true;
    }

    //-----------------------------------------------------------------------
    void SceneNodeGridLineMoveToAction::onLeave()
    {
        mIsMoving = false;
    }

	//-----------------------------------------------------------------------
	void SceneNodeGridLineMoveToAction::onLinedStateChanged(LinedStateObject* obj)
	{
		if(!obj)
		{
			return;
		}

		SceneNodeGridLineMoveToAction* sceneNodeGridLineMoveToAction = (SceneNodeGridLineMoveToAction*)obj;

		Bool isWait = sceneNodeGridLineMoveToAction->getIsWait();
		Bool isMoving = sceneNodeGridLineMoveToAction->getIsMoving();

		if(!isWait && !isMoving)
		{
			mIsWait = true;
		}
		else if(!isWait && isMoving)
		{
			mIsWait = false;
		}
		else if(isWait)
		{
			mIsWait = true;
		}
		else
		{
			DYNAMIC_ASSERT(0);
		}

	}

    //-----------------------------------------------------------------------
    Bool SceneNodeGridLineMoveToAction::isFinished()
    {
        //if ( mIsMoving == false )
        //{
        //    return true;
        //}

        if ( mCurrMoveLength >= mMoveLength )
        {
            return true;
        }

        return false;
    }

	//-----------------------------------------------------------------------
	void SceneNodeGridLineMoveToAction::update( Flt delta )
	{
		if ( !mIsWait )
		{		
            // 当前位置
            Vec3 currPos;
            mSceneNode->getPosition( currPos );

            // 忽略高度
			if ( mIsIgnoreHeight )
				currPos. y = 0;

            // 计算目标位置
			Vec3 moveDest =  currPos + mMoveVelocity * delta;

            // 已经移动的位置
			mCurrMoveLength = ( moveDest - mMoveStartPosition ).length();

            // 判断是否已经超过移动目标距离，是的话则停止移动
			if ( mCurrMoveLength > mMoveLength )
			{
				moveDest = mMoveDestination;
				//mIsMoving = false;
			}

			Bool isRefreshBlock = checkAndRefreshBlock( currPos, moveDest );

            // 检测和刷新障碍
            if ( isRefreshBlock )
            {
			    mSceneNode->setPosition( moveDest );
				mIsMoving = true;

				//扰动在经过点周围的草
				clock_t t = clock();
				if (mIsPerturbGrass && (t - mLastPerturbTime > CLOCKS_PER_SEC/mPerturbFrequnce))
				{
					ITreeManager* pTreeMgr = mSceneNode->getScene()->getTreeManager();
					pTreeMgr->setGrassPerturbCircle(currPos,mPerturbRadiu);
					mLastPerturbTime = clock();
				}

            }else
			{
                mIsMoving = false;
            }

			if(mIsRefreshBlock != isRefreshBlock)
			{
				mIsRefreshBlock = isRefreshBlock;
				notifyChanged();
			}
			
            // 贴地
			if ( mIsStickTerrain )
			{
				mSceneNode->stickTerrain();
			}
		}
		else
		{
			mIsMoving = false;
		}
	}

    //-----------------------------------------------------------------------
    Bool SceneNodeGridLineMoveToAction::checkAndRefreshBlock( Vec3 src, Vec3 dest )
    {
        if ( mIsBlockCheck == false )
		{
			if(mDynamicBlockObject)
			{
				mDynamicBlockObject->refreshBlock( src, dest );
			}

            return true;
		}
      
        Bool isBlock = false;

        Vec3 detectionPos = dest;

		IDynamicBlockObject* collideBlockObject = NULL;
		Flt objectRadius = mDynamicBlockObject->getObjectRadius();

		Flt checkBlcokLenght = 0;
		if(mMoveToPathFindType == PFT_STATIC)
		{
			checkBlcokLenght = (mMoveDestination - src).length();
			checkBlcokLenght /= 3;
		}

		isBlock = mSceneNode->getScene()->getDynamicBlockObjectSceneManager()->isBlockBetweenTwoPos(mDynamicBlockObject, src, detectionPos, objectRadius, collideBlockObject, mMoveToPathFindType, checkBlcokLenght);

		mDynamicBlockObject->setCollideBlockObject(collideBlockObject);
        
        // 刷性障碍
        if( !isBlock )
        {
            mDynamicBlockObject->refreshBlock( src, dest );
        }

        // 更新障碍标志位
        //if ( mIsBlock != isBlock )
        //{
        //    mIsBlock = isBlock;
        //    this->notifyChanged();
        //}
            
        return !isBlock;
    }

    //-----------------------------------------------------------------------
    Bool SceneNodeGridLineMoveToAction::checkAndGrabBlock( Vec3 src, Vec3 dest )
    {
        //Vector3 currPos = MGEngineUtility::getPosition( mSceneNode );

        //UInt currIndex = mBlockManager->getDynamicBlockIndexByWorldPos(Vec3(currPos.x, 0, currPos.z));

        // 抢先占领
        //if(mCurrPassGridBlockListIndex < mPassBlockGridList.size())
        //{
        /*			for(UInt i = 0; i < mPassBlockGridList.size(); ++i)
        {
        if(currIndex == mPassBlockGridList[i].passGridBlockIndex)
        {
        i++;

        if(i >= mPassBlockGridList.size())
        {
        break;
        }

        UInt oldIndex = 0;
        UInt newIndex = 0;

        Vec3 nextBlockGridPos = mPassBlockGridList[i].passGridBlockPos;

        oldIndex = mBlockManager->getDynamicBlockIndexByWorldPos(Vec3(currPos.x, 0, currPos.z));
        newIndex = mBlockManager->getDynamicBlockIndexByWorldPos(nextBlockGridPos);

        if(oldIndex != newIndex)
        {
        mDynamicBlockObject->refreshBlock(Vec3(currPos.x, 0, currPos.z), nextBlockGridPos);
        }

        break;
        }
        }*/
        //if(currIndex == mNextPassGridBlockIndex)
        //{
        //	UInt oldIndex = 0;
        //	UInt newIndex = 0;

        //	Vec3 nextBlockGridPos = mPassBlockGridList[mCurrPassGridBlockListIndex].passGridBlockPos;

        //	oldIndex = mBlockManager->getDynamicBlockIndexByWorldPos(Vec3(currPos.x, 0, currPos.z));
        //	newIndex = mBlockManager->getDynamicBlockIndexByWorldPos(nextBlockGridPos);

        //	if(oldIndex != newIndex)
        //	{
        //		mDynamicBlockObject->refreshBlock(Vec3(currPos.x, 0, currPos.z), nextBlockGridPos);
        //	}

        //	mCurrPassGridBlockListIndex++;
        //	mNextPassGridBlockIndex = mPassBlockGridList[mCurrPassGridBlockListIndex].passGridBlockIndex;
        //}
        //}

        return true;
    }

	//-----------------------------------------------------------------------
	void SceneNodeGridLineMoveToAction::notifyMoveToStateChange()
	{
		SceneNodeGridLineMoveToAction* sceneNodeGridLineMoveToAction = NULL;
		for(std::list<LinedStateObjectListener*>::iterator it = mListener.begin(); it != mListener.end(); ++it)
		{
			sceneNodeGridLineMoveToAction = dynamic_cast<SceneNodeGridLineMoveToAction*>(*it);
			if(!sceneNodeGridLineMoveToAction || sceneNodeGridLineMoveToAction == this)
			{
				continue;
			}

			sceneNodeGridLineMoveToAction->onLinedStateChanged(this);
		}
	}
}