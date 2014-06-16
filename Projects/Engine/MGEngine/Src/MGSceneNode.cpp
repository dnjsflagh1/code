/******************************************************************************/
#include "stdafx.h"
#include "MGSceneNode.h"
#include "EngineMain.h"
#include "SceneNodeAction.h"
#include "Scene.h"
#include "MGEngineUtility.h"
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    MGSceneNode::MGSceneNode(Ogre::SceneNode* parent,Scene* scene)
        :mOgreParentSceneNode(parent)
        ,mScene(scene)
        ,mVisible(true)
        ,mStickTerrainEnable(true)
    {
        DYNAMIC_ASSERT( mOgreParentSceneNode );
        mOgreSceneNode = parent->createChildSceneNode();

		// 注意:如果修改本地参考方向，需要修改所有相关方法，比如setDirection等的默认参数const Vector3& localDirectionVector
        setLocalDirectionVector( Vector3::NEGATIVE_UNIT_Z );
        
        mTerrainRayDir1 = Vec3(0,-1,0);
        mTerrainRayDir2 = Vec3(0,1,0);

		mPositionOffset = Vec3(0,0,0);
		mInitScale = Vec3(1,1,1);

		mAnimations.clear();
    }
    //-----------------------------------------------------------------------
    MGSceneNode::~MGSceneNode()
    {
        mLinedStateManager.clear();

        mOgreSceneNode->removeAllChildren();
		mOgreSceneNode->detachAllObjects();
        mOgreParentSceneNode->removeAndDestroyChild(mOgreSceneNode->getName());

        mOgreSceneNode = NULL;

		clearNodeAnimations();
    }
    //-----------------------------------------------------------------------
    Ogre::SceneNode* MGSceneNode::getOgreSceneNode()
    {
        return mOgreSceneNode;
    }

    //-----------------------------------------------------------------------
    IScene* MGSceneNode::getScene()
    {
        return (MG::IScene *)mScene;
    };
    
    //-----------------------------------------------------------------------
    void MGSceneNode::tempSetVisible(Bool visible)
    {
        mOgreSceneNode->setVisible(visible);
    }

    //-----------------------------------------------------------------------
    void MGSceneNode::revertVisible()
    {
        mOgreSceneNode->setVisible(mVisible);
    }   

    //-----------------------------------------------------------------------
    void MGSceneNode::setVisible(Bool visible)
    {
        mVisible = visible;
        mOgreSceneNode->setVisible(visible);

        notifyVisibleChanged( visible );
    }
    
    //-----------------------------------------------------------------------
    Bool MGSceneNode::getVisible()
    {
        return mVisible;
    }

    //-----------------------------------------------------------------------
    void MGSceneNode::setPosition(Vec3& pos)
	{		
		Vec3 lastPos = MGEngineUtility::toVec3(mOgreSceneNode->getPosition());
        {
            //MovableObject* object = mOgreSceneNode->getAttachedObject(0);
			pos += mPositionOffset;
            mOgreSceneNode->setPosition(pos.x,pos.y,pos.z);
            mPositionDirty = true;
        }
        if( lastPos.x != pos.x || 
            lastPos.y != pos.y || 
            lastPos.z != pos.z 
            )
		{
			notifyPositionChanged(lastPos, pos);
		}
    }
    //-----------------------------------------------------------------------
    void MGSceneNode::getPosition(Vec3& pos)
    {
        const Vector3& ogreVec3 = mOgreSceneNode->getPosition();
        pos.x = ogreVec3.x-mPositionOffset.x;
        pos.y = ogreVec3.y-mPositionOffset.x;
        pos.z = ogreVec3.z-mPositionOffset.x;
    }

	void MGSceneNode::setPositionOffset(const Vec3& offset)
	{		
		mPositionOffset = offset;
	}
	//-----------------------------------------------------------------------
	const Vec3& MGSceneNode::getPositionOffset() const
	{
		return mPositionOffset;
	}

	//-----------------------------------------------------------------------
	void MGSceneNode::getScreenPosition(Vec2& outPos)
	{
		Vec3 worldPos;
		getPosition(worldPos);

		IScene* pScene = getScene();
		ICamera* pCamera = pScene->getActiveCamera();
		pCamera->worldPointToScreenPoint(worldPos, outPos);
	}
	//-----------------------------------------------------------------------
	Bool MGSceneNode::getPositionDirty()
	{
		return mPositionDirty;
	}
    //-----------------------------------------------------------------------
    void MGSceneNode::clearPositionDirty()
    {
        mPositionDirty = false;
    }
    //-----------------------------------------------------------------------
    void MGSceneNode::setScale(Vec3& scale)
    {
        Vec3 lastScale = MGEngineUtility::toVec3(mOgreSceneNode->getScale());
        {
            Vec3 tempScale = scale;
            tempScale *= mInitScale;
            mOgreSceneNode->setScale(tempScale.x,tempScale.y,tempScale.z);
        }
        notifyScaleChanged(lastScale, scale);

		mScaleDirty = true;
    }
    //-----------------------------------------------------------------------
    void MGSceneNode::getScale(Vec3& scale)
    {
        const Vector3& ogreVec3 = mOgreSceneNode->getScale();
		scale.x = ogreVec3.x/mInitScale.x;
		scale.y = ogreVec3.y/mInitScale.y;
		scale.z = ogreVec3.z/mInitScale.z;
    }

	//-----------------------------------------------------------------------
	void MGSceneNode::setInitScale(const Vec3& scale)
	{
		mInitScale = scale;
		setScale(Vec3(1,1,1));
	}
	//-----------------------------------------------------------------------
	const Vec3& MGSceneNode::getInitScale() const
	{
		return mInitScale;
	}

	//----------------------------------------------------------------------
	Bool MGSceneNode::getScaleDirty()
	{
		return mScaleDirty;
	}
    //-----------------------------------------------------------------------
    void MGSceneNode::clearScaleDirty()
    {
        mScaleDirty = false;
    }
    //-----------------------------------------------------------------------
    void MGSceneNode::setOrientation(Qua& quaternion)
    {
        Qua lastQua = MGEngineUtility::toQua(mOgreSceneNode->getOrientation());
        {
            mOgreSceneNode->setOrientation(quaternion.w,quaternion.x,quaternion.y,quaternion.z);
            mOrientationDirty = true;
        }
        notifyOrientationChanged(lastQua, quaternion);
    }
    //-----------------------------------------------------------------------
    void MGSceneNode::getOrientation(Qua& quaternion)
    {
        const Ogre::Quaternion& ogreQua = mOgreSceneNode->getOrientation();
        quaternion.w = ogreQua.w;
        quaternion.x = ogreQua.x;
        quaternion.y = ogreQua.y;
        quaternion.z = ogreQua.z;
    }   
	//-----------------------------------------------------------------------
	Bool MGSceneNode::getOrientationDirty()
	{
		return mOrientationDirty;
	}
    //-----------------------------------------------------------------------
    void MGSceneNode::clearOrientationDirty()
    {
        mOrientationDirty = false;
    }
    //-----------------------------------------------------------------------
    void MGSceneNode::setDirection(Vec3& vec, TransformSpace relativeTo )
    {
        Qua lastQua = MGEngineUtility::toQua(mOgreSceneNode->getOrientation());
        {
            mOgreSceneNode->setDirection(Vector3(vec.x,vec.y,vec.z),(Ogre::Node::TransformSpace)relativeTo);
            mOrientationDirty = true;
        }
        Qua currQua = MGEngineUtility::toQua(mOgreSceneNode->getOrientation());
        notifyOrientationChanged(lastQua, currQua);
    }
    //-----------------------------------------------------------------------
    void MGSceneNode::getDirection(Vec3& vec)
    {
        Vector3 ogreVec3;
        const Ogre::Quaternion& quaternion = mOgreSceneNode->getOrientation();
        ogreVec3 = quaternion * mLocalDirectionVector ;

        vec = Vec3( ogreVec3.x, ogreVec3.y, ogreVec3.z );
    }
    //-----------------------------------------------------------------------
    void MGSceneNode::lookAt(Vec3& targetPoint, TransformSpace relativeTo )
    {
        Qua lastQua = MGEngineUtility::toQua(mOgreSceneNode->getOrientation());
        {
            mOgreSceneNode->lookAt(Vector3(targetPoint.x,targetPoint.y,targetPoint.z),(Ogre::Node::TransformSpace)relativeTo);
            mOrientationDirty = true;
        }
        Qua currQua = MGEngineUtility::toQua(mOgreSceneNode->getOrientation());
        notifyOrientationChanged(lastQua, currQua);
    }
    //-----------------------------------------------------------------------
    void MGSceneNode::translate(Vec3& d, TransformSpace relativeTo )
    {
        Vec3 lastPos = MGEngineUtility::toVec3(mOgreSceneNode->getPosition());
        {
            mOgreSceneNode->translate(d.x,d.y,d.z,(Ogre::Node::TransformSpace)relativeTo);
            mPositionDirty = true;
        }
        Vec3 newPos = MGEngineUtility::toVec3(mOgreSceneNode->getPosition());
        if( lastPos.x != newPos.x || 
            lastPos.y != newPos.y || 
            lastPos.z != newPos.z 
            )
        {
            notifyPositionChanged(lastPos, newPos);
        }
    }
    //-----------------------------------------------------------------------
    void MGSceneNode::roll( Flt angle, TransformSpace relativeTo )
    {
        Qua lastQua = MGEngineUtility::toQua(mOgreSceneNode->getOrientation());
        {
            mOgreSceneNode->roll(Ogre::Radian(angle),(Ogre::Node::TransformSpace)relativeTo);
            mOrientationDirty = true;
        }
        Qua currQua = MGEngineUtility::toQua(mOgreSceneNode->getOrientation());
        notifyOrientationChanged(lastQua, currQua);
    }
    //-----------------------------------------------------------------------
    void MGSceneNode::pitch( Flt angle, TransformSpace relativeTo )
    {
        Qua lastQua = MGEngineUtility::toQua(mOgreSceneNode->getOrientation());
        {
            mOgreSceneNode->pitch(Ogre::Radian(angle),(Ogre::Node::TransformSpace)relativeTo);
            mOrientationDirty = true;
        }
        Qua currQua = MGEngineUtility::toQua(mOgreSceneNode->getOrientation());
        notifyOrientationChanged(lastQua, currQua);
    }
    //-----------------------------------------------------------------------
    void MGSceneNode::yaw( Flt angle, TransformSpace relativeTo )
    {
        Qua lastQua = MGEngineUtility::toQua(mOgreSceneNode->getOrientation());
        {
            mOgreSceneNode->yaw(Ogre::Radian(angle),(Ogre::Node::TransformSpace)relativeTo);
            mOrientationDirty = true;
        }
        Qua currQua = MGEngineUtility::toQua(mOgreSceneNode->getOrientation());
        notifyOrientationChanged(lastQua, currQua);
    }
    //-----------------------------------------------------------------------
    void MGSceneNode::rotate( Vec3& axis, Flt& angle, TransformSpace relativeTo)
    {
        Qua lastQua = MGEngineUtility::toQua(mOgreSceneNode->getOrientation());
        {
            mOgreSceneNode->rotate(Vector3(axis.x,axis.y,axis.z), Ogre::Radian(angle), (Ogre::Node::TransformSpace)relativeTo);
            mOrientationDirty = true;
        }
        Qua currQua = MGEngineUtility::toQua(mOgreSceneNode->getOrientation());
        notifyOrientationChanged(lastQua, currQua);
    }

    //-----------------------------------------------------------------------
    void MGSceneNode::stickTerrain()
    {
        if ( mStickTerrainEnable )
        {
			Flt height = 0;
			if ( getScene()->getCollisionSystem()->getStickHeight(this,height ) )
			{
                Vec3 pos;
                getPosition( pos );

				pos.y = height;
				setPosition(pos);
			}
        }
    }

    //-----------------------------------------------------------------------
    void MGSceneNode::setStickTerrainEnable(Bool enable)
    {
        mStickTerrainEnable = enable;
    }
    
    //-----------------------------------------------------------------------
    void MGSceneNode::setLocalDirectionVector( const Vector3& dir )
    {
        mLocalDirectionVector = dir;
        mWorldDirectionNormalisedVector =  mOgreSceneNode->getOrientation() *( mLocalDirectionVector ).normalisedCopy();
    }

    //-----------------------------------------------------------------------
    const Vector3& MGSceneNode::getLocalDirectionVector()
    {
        return mLocalDirectionVector;
    }

    //-----------------------------------------------------------------------
    const Vector3& MGSceneNode::getWorldDirectionVector()
    {
        return mWorldDirectionNormalisedVector;
    }

    //-----------------------------------------------------------------------
    void MGSceneNode::update( Flt delta )
    {
        mLinedStateManager.update( delta );

		updateNodeAnimations( delta );
    }

	//-----------------------------------------------------------------------
	void MGSceneNode::playNodeAnimation( Str8 name, Bool isLoop /*= false*/, Bool isReverse /*= false */ )
	{
		if ( !mScene )
			return;

		if ( mScene->getOgreSceneManager()->hasAnimation( name ) )
		{
			AnimationState* animationState = NULL;
			
			AnimationMap_iter iter = mAnimations.find( name );
			if ( iter == mAnimations.end() )
			{
				animationState = mScene->getOgreSceneManager()->createAnimationState( name );
				mAnimations[name] = animationState;
			}
			else
			{
				animationState = iter->second;
			}

			animationState->setEnabled( true );
			animationState->setLoop( isLoop );
			animationState->setTimePosition(0.0f);

			Animation* animation = mScene->getOgreSceneManager()->getAnimation(animationState->getAnimationName());
			if ( animation->hasNodeTrack(1) )
				animation->getNodeTrack(1)->setAssociatedNode(mOgreSceneNode);
		}
	}
	//-----------------------------------------------------------------------
	void MGSceneNode::updateNodeAnimations(Flt delta)
	{
		for ( AnimationMap_iter iter = mAnimations.begin(); iter != mAnimations.end(); iter++ )
		{
			AnimationState* animationState = iter->second;
			if ( animationState )
			{
				animationState->addTime(delta);
			}
		}
	}

	//-----------------------------------------------------------------------
	void MGSceneNode::clearNodeAnimations()
	{
		for ( AnimationMap_iter iter = mAnimations.begin(); iter != mAnimations.end(); iter++ )
		{
			AnimationState* animationState = iter->second;
			if ( animationState )
			{
				Animation* animation = mScene->getOgreSceneManager()->getAnimation(animationState->getAnimationName());
				if ( animation->hasNodeTrack(1) )
					animation->getNodeTrack(1)->setAssociatedNode(NULL);
			}
		}

		mAnimations.clear();
	}
}

