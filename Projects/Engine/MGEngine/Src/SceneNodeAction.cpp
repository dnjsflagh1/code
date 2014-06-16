/******************************************************************************/
#include "stdafx.h"
#include "SceneNodeAction.h"
#include "MGEngineUtility.h"
#include "ISceneNode.h"
#include "IScene.h"
#include "ITerrain.h"
#include "MGSceneNode.h"
#include "LinedState.h"
#include "IBlockManager.h"
#include "ITree.h"
/******************************************************************************/

namespace MG
{
	static int lock_value = 2;
    /******************************************************************************/
    //SceneNodeMoveToAction
    /******************************************************************************/
    Str SceneNodeLineMoveToAction::STATE_NAME = "SceneNodeLineMoveToAction";
    //-----------------------------------------------------------------------
    SceneNodeLineMoveToAction::SceneNodeLineMoveToAction( ISceneNode* object )
        :ISceneNodeLineMoveToAction(STATE_NAME)
        ,mSceneNode(object)
        ,mMoveSpeed(1)
        ,mIsMoving(false)
        ,mIsStickTerrain(true)
		,mIsPerturbGrass(false)
		,mPerturbRadiu(2.0f)
		,mPerturbFrequnce(3)
		,mLastPerturbTime(clock())
    {	 
    }	

	 //-----------------------------------------------------------------------
	SceneNodeLineMoveToAction::SceneNodeLineMoveToAction( ISceneNode* object, Str SUBSTATE_NAME )
		:ISceneNodeLineMoveToAction(SUBSTATE_NAME)
		,mSceneNode(object)
		,mMoveSpeed(1)
		,mIsMoving(false)
		,mIsStickTerrain(true)
	{

	}

    //-----------------------------------------------------------------------
    SceneNodeLineMoveToAction::~SceneNodeLineMoveToAction()
    {
        
    }

    //-----------------------------------------------------------------------
    void SceneNodeLineMoveToAction::setMoveSpeed( Flt speed )
    {
        mMoveSpeed = speed;
    }
    
    //-----------------------------------------------------------------------
    void SceneNodeLineMoveToAction::setMoveToDestination( const Vec3& dest )
    {
        MGEngineUtility::toVec3( dest, mMoveDestination );
		if ( mIsIgnoreHeight )
			mMoveDestination.y = 0;
    }

	//-----------------------------------------------------------------------
	//在setMoveToDestination之前调用
	void SceneNodeLineMoveToAction::setIgnoreHeight( Bool isIgnoreHeight )
	{
		mIsIgnoreHeight = isIgnoreHeight;
	}

    //-----------------------------------------------------------------------
    void SceneNodeLineMoveToAction::setStickTerrain( Bool isStickTerrain )
    {
        mIsStickTerrain = isStickTerrain;
    }

	//-----------------------------------------------------------------------
	// 设置是否启用扰动草
	void SceneNodeLineMoveToAction::setPerturbEnable( Bool isPerturb )
	{
		mIsPerturbGrass = isPerturb;  
	}

	//-----------------------------------------------------------------------
	// 设置扰动草半径
	void SceneNodeLineMoveToAction::setPerturbRadiu( Flt radiu )
	{
		mPerturbRadiu = radiu;
	}

	//-----------------------------------------------------------------------
	// 设置扰动草频率
	void SceneNodeLineMoveToAction::setPerturbFrequnce( UInt freq )
	{
		mPerturbFrequnce = freq;
	}

    //-----------------------------------------------------------------------
    void SceneNodeLineMoveToAction::update( Flt delta )
    {
        if ( mIsMoving )
        {
			Vector3 currPos = MGEngineUtility::getPosition( mSceneNode );

			if ( mIsIgnoreHeight )
				currPos. y = 0;

            //Vector3 position = MGEngineUtility::getPosition( mSceneNode );
            Vector3 position =  currPos + mMoveVelocity * delta;

            mCurrMoveLength = ( position - mMoveStartPosition ).length();

            if ( mCurrMoveLength > mMoveLength )
            {
                position = mMoveDestination;
                mIsMoving = false;
            }

            Vec3 moveToPos;
            MGEngineUtility::toVec3( position, moveToPos );
            
            mSceneNode->setPosition( moveToPos );

			//扰动在经过点周围的草
			clock_t t = clock();
			if (mIsPerturbGrass && (t - mLastPerturbTime > CLOCKS_PER_SEC/mPerturbFrequnce))
			{
				ITreeManager* pTreeMgr = mSceneNode->getScene()->getTreeManager();
				pTreeMgr->setGrassPerturbCircle(Vec3(currPos.x,currPos.y,currPos.z),mPerturbRadiu);
				mLastPerturbTime = clock();
			}

            if ( mIsStickTerrain )
            {
                mSceneNode->stickTerrain();
            }
        }
    }

    //-----------------------------------------------------------------------
    Bool SceneNodeLineMoveToAction::isFinished()
    {
        if ( mIsMoving == false )
		{
            return true;
		}

        if ( mCurrMoveLength >= mMoveLength )
		{
            return true;
		}
        
        return false;
    }

    //-----------------------------------------------------------------------
    void SceneNodeLineMoveToAction::onEnter()
    {
        mMoveStartPosition = MGEngineUtility::getPosition( mSceneNode );

		if ( mIsIgnoreHeight )
			mMoveStartPosition.y = 0;

        mMoveLength     = ( mMoveDestination - mMoveStartPosition ).length();
        mMoveVelocity   = ( mMoveDestination - mMoveStartPosition ).normalisedCopy() * mMoveSpeed;
        mCurrMoveLength = 0;

        mIsMoving = true;
    }

    //-----------------------------------------------------------------------
    void SceneNodeLineMoveToAction::onLeave()
    {
        mIsMoving = false;
    }

    /******************************************************************************/
    //SceneNodeYawToAction
    /******************************************************************************/
    Str SceneNodeYawToAction::STATE_NAME = "SceneNodeYawToAction";
    SceneNodeYawToAction::SceneNodeYawToAction( ISceneNode* object )
        :ISceneNodeYawToAction(STATE_NAME)
        ,mSceneNode(object)
        ,mYawRotateSpeed(1)
        ,mIsYawing(false)
		,mIsImmediately(true)
    {
        

    }

    //-----------------------------------------------------------------------
    SceneNodeYawToAction::~SceneNodeYawToAction()
    {
        
    }

    //-----------------------------------------------------------------------
    void SceneNodeYawToAction::setYawSpeed( Flt speed )
    {
        mYawRotateSpeed = speed;
    }

    //-----------------------------------------------------------------------
    void SceneNodeYawToAction::setYawToDirection( const Vec3& dir )
    {
        MGEngineUtility::toVec3( dir, mDstDirection );
    }

    //-----------------------------------------------------------------------
    void SceneNodeYawToAction::setYawToDirection( const Vec3& startPos, const Vec3& endPos )
    {
        Vector3 sPos;
        MGEngineUtility::toVec3( startPos, sPos );
        Vector3 dPos;
        MGEngineUtility::toVec3( endPos, dPos );

        mDstDirection = dPos - sPos;
        mDstDirection.y = 0;
    }

    //-----------------------------------------------------------------------
    void SceneNodeYawToAction::setYawToPosition( const Vec3& pos )
    {
        Vector3 currPos = MGEngineUtility::getPosition( mSceneNode );
        Vector3 desPos;
        MGEngineUtility::toVec3( pos, desPos );
        mDstDirection = desPos - currPos;
		mDstDirection.y = 0;
    }

    //-----------------------------------------------------------------------
    void SceneNodeYawToAction::update( Flt delta )
    {
        if ( mIsYawing )
        {
            Real step = delta * mYawRotateSpeed * mYawDir;
            mSceneNode->yaw( step );

            //判断是否转到相应位置
            Vector3 gmObjVec     = MGEngineUtility::getDirection( mSceneNode );
            Vector2 desVec2D     = Vector2( mDstDirection.x, mDstDirection.z );
            Vector2 gmObjVec2D   = Vector2( gmObjVec.x, gmObjVec.z );

            desVec2D.normalise();
            gmObjVec2D.normalise();
            Real vecCos			 = desVec2D.dotProduct( gmObjVec2D );
            Real crossProduct    = desVec2D.crossProduct( gmObjVec2D );
            Real currYawDir      = 1;
            if ( crossProduct < 0 )
            {
                currYawDir = -1; 
            }
            else
            if ( crossProduct > 0 )
            {
                currYawDir = 1; 
            }

            Real tolerance = 0.001;

            if ( MGEngineUtility::isTwoVectorDirectionEquals(vecCos, tolerance) )
            {
                mIsYawing = false;
            }

            if ( currYawDir != mYawDir )
            {
                mIsYawing = false;
            }

			if ( !mIsYawing )
			{
				mSceneNode->setDirection(Vec3(desVec2D.x,0,desVec2D.y));
			}
        }
    }

    //-----------------------------------------------------------------------
    Bool SceneNodeYawToAction::isFinished()
    {
        if ( mIsYawing == false )
            return true;
        return false;
    }

    //-----------------------------------------------------------------------
    void SceneNodeYawToAction::onEnter()
    {
        Vector3 gmObjVec     = MGEngineUtility::getDirection( mSceneNode );
        Vector2 desVec2D     = Vector2( mDstDirection.x, mDstDirection.z );
        Vector2 gmObjVec2D   = Vector2( gmObjVec.x, gmObjVec.z );
        desVec2D.normalise();
        gmObjVec2D.normalise();
        Real crossProduct = desVec2D.crossProduct( gmObjVec2D );

        if ( crossProduct < 0 )
        {
            mYawDir = - 1; 
        }
        else
        if ( crossProduct > 0 )
        {
            mYawDir = 1; 
        }

        mIsYawing = false;

        //-----------------------------------------------------------------------

        //if ( MGEngineUtility::isTwoVectorCoincide(mDstDirection, Vector3::UNIT_Y) ) 
        //{
        //    mIsYawing = false;
        //}


        if ( (desVec2D.x == 0) && (desVec2D.y == 0) ) 
        {
            return;
        }

        //-----------------------------------------------------------------------

		if ( mIsImmediately )
		{
			mSceneNode->setDirection(Vec3(desVec2D.x,0,desVec2D.y));
		}else
        {
            mIsYawing = true;
        }
    }

    //-----------------------------------------------------------------------
    void SceneNodeYawToAction::onLeave()
    {
        mIsYawing = false;
    }



	//-----------------------------------------------------------------------
   
	/******************************************************************************/
	//SceneNodePitchToAction
	/******************************************************************************/
	Str SceneNodePitchToAction::STATE_NAME = "SceneNodePitchToAction";
	SceneNodePitchToAction::SceneNodePitchToAction( ISceneNode* object )
		:ISceneNodePitchToAction(STATE_NAME)
		,mSceneNode(object)
		,mPitchRotateSpeed(1)
		,mIsPitching(false)
		,mPitchDir(1)
		,mIsImmediately(false)
	{


	}

	//-----------------------------------------------------------------------
	SceneNodePitchToAction::~SceneNodePitchToAction()
	{

	}

	//-----------------------------------------------------------------------
	void SceneNodePitchToAction::setPitchSpeed( Flt speed )
	{
		mPitchRotateSpeed = speed;
	}

	//-----------------------------------------------------------------------
	void SceneNodePitchToAction::setDestAngle( Flt angle)
	{
		mDstPitch = angle;
	}

	//-----------------------------------------------------------------------
	void SceneNodePitchToAction::update( Flt delta )
	{
		if ( mIsPitching )
		{
			Flt cur_pitch = mSceneNode->getPitch();
			Real step = cur_pitch + delta * mPitchRotateSpeed * mPitchDir;

			mSceneNode->setOrientation(Qua(1.0f, 0.0f, 0.0f, 0.0f));
			mSceneNode->pitch( step );

			//判断是否转到相应位置
			Flt cur_dist = mDstPitch - cur_pitch;
			Flt cur_dir = 0.0f;
		
			if ( cur_dist < 0 )
			{
				cur_dir = -1;
			}
			else if ( cur_dist > 0 )
			{
				cur_dir = 1;
			}

			Str8 str1, str2;

			MGStrOp::toString( cur_pitch, str1 );
			MGStrOp::toString( mDstPitch, str2 );

			Str8 final;
			final += str1;
			final += "   ";
			final += str2;
			final += "\n";
			
			OutputDebugString( final.c_str() );

			//if ( fabs (cur_dist)  ) 

			if ( fabs(cur_dist) < 0.001f ||
				cur_dir * mPitchDir <= 0 )
			{
				OutputDebugString("end\n");
				mIsPitching = false;

				mSceneNode->setOrientation(Qua(1.0f, 0.0f, 0.0f, 0.0f));
				mSceneNode->pitch( mDstPitch );
			}
		}
	}

	//-----------------------------------------------------------------------
	Bool SceneNodePitchToAction::isFinished()
	{
		if ( mIsPitching == false )
			return true;
		return false;
	}

	//-----------------------------------------------------------------------
	void SceneNodePitchToAction::onEnter()
	{
		mSrcPitch = mSceneNode->getPitch();

		Flt pitch_dis = mDstPitch - mSrcPitch;

		if ( pitch_dis < 0 )
		{
			mPitchDir = -1; 
		}
		else if ( pitch_dis > 0 )
		{
			mPitchDir = 1; 
		}

		mIsPitching = true;

		if ( mIsImmediately )
		{
			mSceneNode->setOrientation(Qua(1.0f, 0.0f, 0.0f, 0.0f));
			mSceneNode->pitch( mDstPitch);

			OutputDebugString( "enter: false!\n");

			mIsPitching = false;
		}

		Str8 str1, str2;

		MGStrOp::toString( mSrcPitch, str1 );
		MGStrOp::toString( mDstPitch, str2 );

		Str8 final = "ENTER: ";
		final += str1;
		final += "   ";
		final += str2;
		final += "\n";

		OutputDebugString( final.c_str() );
	}

	//-----------------------------------------------------------------------
	void SceneNodePitchToAction::onLeave()
	{
		OutputDebugString("leave\n");
		//mIsPitching = false;
	}



	//-----------------------------------------------------------------------

	/******************************************************************************/
	//SceneNodePitchToAction
	/******************************************************************************/

	Str SceneNodeDirectToAction::STATE_NAME = "SceneNodeDirectToAction";

	SceneNodeDirectToAction::SceneNodeDirectToAction( ISceneNode* node )
		:ISceneNodeDirectToAction(STATE_NAME)
		,mSceneNode(node)
		,mShiftSpeed(0.1f)
		,mIsImmediately(false)
		,mTotalRadianDist(0.0f)
		,mCurrRadianDist(0.0f)
	{
		
	}

	//-----------------------------------------------------------------------
	SceneNodeDirectToAction::~SceneNodeDirectToAction()
	{

	}

	//-----------------------------------------------------------------------
	void SceneNodeDirectToAction::update( Flt delta )
	{
		if ( mCurrRadianDist > 0.0f && mSceneNode )
		{
			//////////////////////////////////////////////////////////////////////////////

			Flt deltaRadian = delta * mShiftSpeed;
			if ( deltaRadian > mCurrRadianDist )
			{
				deltaRadian = mCurrRadianDist;
			}

			mCurrRadianDist -= deltaRadian;

			//////////////////////////////////////////////////////////////////////////////

			Qua deltaOrientation;
			deltaOrientation.FromAngleAxis( (mTotalRadianDist - mCurrRadianDist), mRotateAxis );
			mSceneNode->setDirection(deltaOrientation * mOriginalDirection);

			//////////////////////////////////////////////////////////////////////////////
		}
	}

	//-----------------------------------------------------------------------
	Bool SceneNodeDirectToAction::isFinished()
	{
		if ( mCurrRadianDist <= 0.0f )
			return true;

		return false;
	}

	//-----------------------------------------------------------------------
	void SceneNodeDirectToAction::onEnter()
	{
		if ( mSceneNode )
		{
			if ( mIsImmediately )
			{
				mDestDirection.normalise();
				mSceneNode->setDirection(mDestDirection);

				mCurrRadianDist = 0.0f;
			}
			else
			{
				//////////////////////////////////////////////////////////////////////////////

				mSceneNode->getDirection(mOriginalDirection);
				mOriginalDirection.normalise();

				//////////////////////////////////////////////////////////////////////////////

				Ogre::Vector3 originalDir;
				originalDir.x = mOriginalDirection.x; 
				originalDir.y = mOriginalDirection.y;
				originalDir.z = mOriginalDirection.z;

				Ogre::Vector3 destDir;
				destDir.x	  = mDestDirection.x;
				destDir.y	  = mDestDirection.y;
				destDir.z	  = mDestDirection.z;

				//////////////////////////////////////////////////////////////////////////////

				Ogre::Vector3 rotateAxis;
				Ogre::Radian  totalRadianDist;
				Ogre::Quaternion quaDelta = originalDir.getRotationTo( destDir );
				quaDelta.ToAngleAxis(totalRadianDist, rotateAxis);

				/////////////////////////////////////////////////////////////////////////////

				mTotalRadianDist = totalRadianDist.valueRadians();
				mRotateAxis.x = rotateAxis.x;
				mRotateAxis.y = rotateAxis.y;
				mRotateAxis.z = rotateAxis.z;

				/////////////////////////////////////////////////////////////////////////////

				// 确保距离大于0， 否则反转旋转轴
				if ( mTotalRadianDist < 0.0f )
				{
					mTotalRadianDist = -mTotalRadianDist;
					mRotateAxis = mRotateAxis * (-1);
				}

				mCurrRadianDist = mTotalRadianDist;

				//////////////////////////////////////////////////////////////////////////////
			}
			
		}		
	}

	//-----------------------------------------------------------------------
	void SceneNodeDirectToAction::onLeave()
	{
	}

	//-----------------------------------------------------------------------
	void SceneNodeDirectToAction::setDestDirection( Vec3 dir )
	{
		mDestDirection = dir;
		mDestDirection.normalise();
	}

	//-----------------------------------------------------------------------
}