/******************************************************************************/
#include "stdafx.h"
#include "SceneNodeAction.h"
#include "SceneNodePathFindingAction.h"
#include "MGEngineUtility.h"
#include "ISceneNode.h"
#include "IScene.h"
#include "ITerrain.h"
#include "MGSceneNode.h"
#include "PathFindingManager.h"
#include "IBlockManager.h"
#include "DynamicBlockObject.h"
#include "BlockObject.h"
/******************************************************************************/

namespace MG
{

    #define STATIC_FINDPATH_MAX_PATHCELL_LENGTH 10000
    #define STATIC_FINDPATH_MAX_DYNAMICBLOCK_COUNT 5000
    #define DYNAMIC_FINDPATH_MAX_PATHCELL_LENGTH 1000
    #define DYNAMIC_FINDPATH_MAX_DYNAMICBLOCK_COUNT 500

    /******************************************************************************/
    //SceneNodeMoveToByFindPathAction
    /******************************************************************************/

    //-----------------------------------------------------------------------
    SceneNodePathFindingMoveInAdvanceAction::SceneNodePathFindingMoveInAdvanceAction(  IDynamicBlockObject* object )
        :mDynamicBlockObject(object)
		,mCurrStaticDestinationIndex(0)
		,mCurrDynamicDestinationIndex(0)
		,mSceneNode(NULL)
    {
		mSceneNode = mDynamicBlockObject->getSceneObject()->getSceneNode();
    }	 

    //-----------------------------------------------------------------------
    SceneNodePathFindingMoveInAdvanceAction::~SceneNodePathFindingMoveInAdvanceAction()
    {

    }

    //-----------------------------------------------------------------------
    Bool SceneNodePathFindingMoveInAdvanceAction::setMoveToDestination( Vec3& dest, Bool isAdjuest )
    {
        Bool result = true/*false*/;
        mMoveDestination    = dest;

   //     IScene* scene = mSceneNode->getScene();
   //     if(scene)
   //     {
   //         Int diameter = mDynamicBlockObject->getDynamicBlockGridDiameter();

			//Vec3 startPos;
			//mSceneNode->getPosition( startPos );
			//startPos.y = 0;

			//Vec3 dis = startPos - dest;

			//Vec3 dir = MGMath::normaliseVector(dis);
			//dir.y = 0;
			//result = scene->getBlockManager()->getPosNearestAccessiblePosForDir(dest, dir, mDynamicBlockObject->getObjectRadius() * 2, diameter, mMoveDestination);
			//if(result)
			//{
			//	dest = mMoveDestination;
			//}
			//else
			//{
			//	result = scene->getBlockManager()->getPosNearestAccessiblePos(dest, dir, dis.length(), diameter, mMoveDestination);
			//	if(result)
			//	{
			//		dest = mMoveDestination;
			//	}
			//}


   //         //result = scene->getBlockManager()->getPosNearestAccessiblePos( dest, diameter, mMoveDestination, mDynamicBlockObject);
   //     }

		mMoveDestination.y  = 0;

        return result;
    }

    //-----------------------------------------------------------------------
    PathFindingResult SceneNodePathFindingMoveInAdvanceAction::calculateStaticPathFinding()
    {
        // 获得寻路计算对象
		IPathFindingManager* pathFindingManager = mSceneNode->getScene()->getPathFindingManager();
		PathFinder2*	staticPathFinder    = (PathFinder2*)pathFindingManager->getStaticPathFinder();

        // 障碍直径
		Int dynamicDiameter = mDynamicBlockObject->getStaticBlockGridDiameter();

        // 获得当前点作为起始点
		Vec3 startPos;
        mSceneNode->getPosition( startPos );
		startPos.y = 0;

        // 忽略列表
		std::map<UInt, UInt> ignorePosList;

        // 得到起始和目标网格坐标
        VecU2 startCellPoint ;
        VecU2 targetCellPoint ;
        staticPathFinder->convertWorldPositionToGridPoint( startPos, startCellPoint );
        staticPathFinder->convertWorldPositionToGridPoint( mMoveDestination, targetCellPoint );
        
        // 开始寻路
        PathFindingResult result = staticPathFinder->findPath(startCellPoint, targetCellPoint, 
                    ignorePosList, dynamicDiameter, 
                    STATIC_FINDPATH_MAX_PATHCELL_LENGTH, STATIC_FINDPATH_MAX_DYNAMICBLOCK_COUNT);

        // 寻路结果
		if( result != PFR_ERROR )
		{
            if ( result != PFR_ALREADY_ARRIVE )
            {
                //mStaticMoveNodeList = staticPathFinder->getCombineFindPathNodeResult();
                mStaticMoveNodeList = staticPathFinder->getSmoothFindPathNodeResult();

                mCurrStaticDestinationIndex = 0;
            }
		}else
        {
            DYNAMIC_ASSERT( false );
        }

		return result;
    }

    //-----------------------------------------------------------------------
    PathFindingResult SceneNodePathFindingMoveInAdvanceAction::calculateDynamicPathFindingBetweenStaticNode()
    {
        // 障碍直径
		Flt objectRadius = mDynamicBlockObject->getObjectRadius();
        // 临时加宽碰撞
        //dynamicDiameter+=1;

        // 得到寻路计算对象
		IPathFindingManager* pathFindingManager = mSceneNode->getScene()->getPathFindingManager();
		PathFinder21*	dynamicPathFinder       = (PathFinder21*)pathFindingManager->getDynamicPathFinder();


        // 获得当前点作为起始点
        Vec3 startPos;
        mSceneNode->getPosition( startPos );
        startPos.y = 0;

  //      // 获得忽略列表
		//std::map<UInt, UInt> ignorePosList;
  //      mDynamicBlockObject->getCurrLocationDynamicBlockIndexList( ignorePosList );

  //      // 得到起始和目标网格坐标
  //      VecU2 startCellPoint ;
  //      VecU2 targetCellPoint ;
  //      dynamicPathFinder->convertWorldPositionToGridPoint( startPos, startCellPoint );
  //      dynamicPathFinder->convertWorldPositionToGridPoint( mStaticMoveNodeList[mCurrStaticDestinationIndex], targetCellPoint );

        // 开始寻路
        //PathFindingResult result = dynamicPathFinder->findPath(startCellPoint, targetCellPoint, 
        //                ignorePosList, dynamicDiameter, 
        //                DYNAMIC_FINDPATH_MAX_PATHCELL_LENGTH, DYNAMIC_FINDPATH_MAX_DYNAMICBLOCK_COUNT);


		// 注释！！！！！！！！！！！！！！！！！！！！！！11


		Vec3 endPos = mStaticMoveNodeList[mCurrStaticDestinationIndex];

		RectF findPathRect;
		Vec3 disVec = endPos - startPos;
		disVec.y = 0;
		Flt disRadius = disVec.length() + objectRadius;

		if(startPos.z > endPos.z)
		{
			findPathRect.top = endPos.z - disRadius;
			findPathRect.bottom = startPos.z + disRadius;
		}
		else
		{
			findPathRect.top = startPos.z - disRadius;
			findPathRect.bottom = endPos.z + disRadius;
		}

		if(startPos.x > endPos.x)
		{
			findPathRect.right = startPos.x + disRadius;
			findPathRect.left = endPos.x - disRadius;
		}
		else
		{
			findPathRect.right = endPos.x + disRadius;
			findPathRect.left = startPos.x - disRadius;
		}

		DynamicBlockObject* dynamicBlockObject = (DynamicBlockObject*)mDynamicBlockObject;
		BlockObject* pathFinder = dynamicBlockObject;

		PathFindingResult result = dynamicPathFinder->findPath(pathFinder, 
						startPos, 
						endPos, 
		                findPathRect,
		               DYNAMIC_FINDPATH_MAX_PATHCELL_LENGTH, DYNAMIC_FINDPATH_MAX_DYNAMICBLOCK_COUNT);


        // 寻路结果
		if( result != PFR_ERROR )
		{
			if ( result != PFR_ALREADY_ARRIVE )
            {
                mDynamicMoveNodeList = dynamicPathFinder->getCombineFindPathNodeResult();
                //mDynamicMoveNodeList = dynamicPathFinder->getSmoothFindPathNodeResult();
                mCurrDynamicDestinationIndex = 0;
            }

        }else
        {
            DYNAMIC_ASSERT( false );
        }

		return result;
    }

    //-----------------------------------------------------------------------
    Vec3 SceneNodePathFindingMoveInAdvanceAction::getCurrDynamicDestination()
    {
        if ( mDynamicMoveNodeList.size() == 0 )
            return mMoveDestination;

		return mDynamicMoveNodeList[mCurrDynamicDestinationIndex];
    }

    //-----------------------------------------------------------------------
    Vec3 SceneNodePathFindingMoveInAdvanceAction::goNextDynamicDestination()
    {
        if ( mDynamicMoveNodeList.size() == 0 )
            return mMoveDestination;

		if((UInt)mCurrDynamicDestinationIndex < mDynamicMoveNodeList.size() - 1)
		{
			mCurrDynamicDestinationIndex++;
		}
		
        return mDynamicMoveNodeList[mCurrDynamicDestinationIndex];
    }

	//-----------------------------------------------------------------------
	Bool SceneNodePathFindingMoveInAdvanceAction::isLastDynamicDestination()
	{
        if ( mDynamicMoveNodeList.size() == 0 )
            return true;

		if( (UInt)(mCurrDynamicDestinationIndex + 1) == mDynamicMoveNodeList.size() )
			return true;

		return false;
	}

	//-----------------------------------------------------------------------
	Vec3 SceneNodePathFindingMoveInAdvanceAction::goNextStaticDestination()
	{
        if ( mStaticMoveNodeList.size() == 0 )
            return mMoveDestination;

		if((UInt)(mCurrStaticDestinationIndex + 1) < mStaticMoveNodeList.size())
		{
			mCurrStaticDestinationIndex++;
		}
		
		return mStaticMoveNodeList[mCurrStaticDestinationIndex];
	}

	//-----------------------------------------------------------------------
	Bool SceneNodePathFindingMoveInAdvanceAction::isLastStaticDestination()
	{
        if ( mStaticMoveNodeList.size() == 0 )
            return true;

		if( (UInt)(mCurrStaticDestinationIndex+1) == mStaticMoveNodeList.size() )
			return true;

		return false;
	}

	//-----------------------------------------------------------------------
	Vec3 SceneNodePathFindingMoveInAdvanceAction::getCurrStaticDestination()
	{
        if ( mStaticMoveNodeList.size() == 0 )
            return mMoveDestination;
		return mStaticMoveNodeList[mCurrStaticDestinationIndex];
	}

	//-----------------------------------------------------------------------
	void SceneNodePathFindingMoveInAdvanceAction::setCurrStaticDestination( Vec3 pos )
	{
        if ( mStaticMoveNodeList.size() > 0 )
		    mStaticMoveNodeList[mCurrStaticDestinationIndex] = pos;
	}

	//-----------------------------------------------------------------------
	void SceneNodePathFindingMoveInAdvanceAction::setFinalStaticDestination( Vec3 pos )
	{
        if ( mStaticMoveNodeList.size() > 0 )
		    mStaticMoveNodeList[mStaticMoveNodeList.size() - 1] = pos;
	}
    

}
