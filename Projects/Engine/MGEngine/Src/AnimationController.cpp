/******************************************************************************/
#include "stdafx.h"
#include "MGEngineUtility.h"
#include "AnimationController.h"
#include "ISceneNode.h"
#include "ResourceManager.h"
/******************************************************************************/

namespace MG
{
    AnimationController::AnimationController()
        :mBlendingTime(0.3)
        ,mBlendingEnable(true)
        ,mAnimSet(NULL)
        ,mSkeleton(NULL)
    {

    }

    //-----------------------------------------------------------------------
    AnimationController::~AnimationController()
    {
        clear();
    }
    //-----------------------------------------------------------------------
    void AnimationController::clear()
    {
        mAnimations.clear();
    }
    //-----------------------------------------------------------------------
    void AnimationController::loadSkeletonAnimation(Ogre::AnimationStateSet* animSet, Ogre::SkeletonInstance* skeleton)
    {
        mSkeleton   = skeleton;
        mAnimSet    = animSet;

        if ( mSkeleton )
        {
			if ( animSet )
			{
				Ogre::AnimationStateIterator it = animSet->getAnimationStateIterator();
				while(it.hasMoreElements())
				{
					Ogre::AnimationState *anim = it.getNext();
					const String& animName = anim->getAnimationName();
					if(animName[0] == '_')
						continue;

					/*
					@   Ogre姿态动画和骨骼动画如果同名的情况下。
					将共享一个AnimationStateSet状态，如果AnimationStateSet状态改变
					将同时影响Ogre姿态动画和骨骼动画
					*/
					mSkeleton->setBlendMode( Ogre::ANIMBLEND_CUMULATIVE );
					if (mSkeleton->hasAnimation( animName ))
					{
                        addAnimation(animName,anim);
					}
				}
			}
        }
    }
    //-----------------------------------------------------------------------
    void AnimationController::loadVertexAnimation(Ogre::Entity* entity)
    {
        if ( entity && entity->hasVertexAnimation() )
        {
            Ogre::AnimationStateSet* animSet = entity->getAllAnimationStates();
            
            if ( animSet )
            {
                Ogre::AnimationStateIterator it = animSet->getAnimationStateIterator();
                while(it.hasMoreElements())
                {
                    Ogre::AnimationState *anim = it.getNext();
                    const String& animName = anim->getAnimationName();
                    if(animName[0] == '_')
                        continue;
                    
                    /*
                    @   Ogre姿态动画和骨骼动画如果同名的情况下。
                    将共享一个AnimationStateSet状态，如果AnimationStateSet状态改变
                    将同时影响Ogre姿态动画和骨骼动画
                    */
                    if (entity->getMesh()->hasAnimation(animName))
                    {
                        addAnimation(animName,anim);
                    }
                }
            }
        }
    }
	//-----------------------------------------------------------------------
	Bool AnimationController::isSeparateSkeletonCompatible(Skeleton::BoneHandleMap boneHandleMap, Skeleton* srcSkeleton, Skeleton* destSkeleton)
	{
		if ( boneHandleMap.size() != srcSkeleton->getNumBones() )
			return false;

		if ( srcSkeleton->getNumBones() != destSkeleton->getNumBones() )
			return false;

		// Check source skeleton structures compatible with ourself (that means
		// identically bones with identical handles, and with same hierarchy, but
		// not necessary to have same number of bones and bone names).
		for (ushort handle = 0; handle < srcSkeleton->getNumBones(); ++handle)
		{
			const Bone* srcBone = srcSkeleton->getBone(handle);
			ushort dstHandle = boneHandleMap[handle];

			// Does it exists in target skeleton?
			if (dstHandle < srcSkeleton->getNumBones())
			{
				Bone* destBone = destSkeleton->getBone(dstHandle);

				// Check both bones have identical parent, or both are root bone.
				const Bone* srcParent = static_cast<Bone*>(srcBone->getParent());
				Bone* destParent = static_cast<Bone*>(destBone->getParent());
				if ((srcParent || destParent) &&
					( !srcParent || !destParent || boneHandleMap[srcParent->getHandle()] != destParent->getHandle()) )
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}

		return true;
	}
    //-----------------------------------------------------------------------
    Bool AnimationController::loadSeparateAnimation(Str animName)
    {
        if ( mSkeleton )
        {
            //Str fileName = animName + ".skeleton";

            SkeletonPtr pSkeletonSeparate;

			Ogre::Animation *anim = NULL;
			if ( mSkeleton->hasAnimation(animName) == true )
			{
				anim = mSkeleton->getAnimation(animName);
			}

			if (anim==NULL)
			{
				// Load skeleton
                pSkeletonSeparate = MG::ResourceManager::getSingletonPtr()->getSkeletonPtr(mParentModelDeclID, animName);

				if (pSkeletonSeparate.isNull()==false)
				{
					Skeleton::BoneHandleMap boneHandleMap;
					pSkeletonSeparate->_buildMapBoneByHandle( pSkeletonSeparate.getPointer(), boneHandleMap );

					if ( isSeparateSkeletonCompatible(boneHandleMap, pSkeletonSeparate.getPointer(), mSkeleton) )
					{
						/*try
						{
							mSkeleton->_mergeSkeletonAnimations( pSkeletonSeparate.getPointer(), boneHandleMap );
						}
						catch (Exception* e)
						{
#ifdef _DEBUG
							char error[64];
							sprintf_s( error, _countof(error), "Animation [%s] not compatible for model which id is [%d]", animName.c_str(), mParentModelDeclID );

							MG_MESSAGE(error);
#endif
						}*/
						
						mSkeleton->_mergeSkeletonAnimations( pSkeletonSeparate.getPointer(), boneHandleMap );
						anim = mSkeleton->getAnimation(animName);
						
					}
					else
					{
						ModelDeclaration* decl = ResourceManager::getSingletonPtr()->getModelDeclaration( mParentModelDeclID, false );

						char error[1024];
						sprintf_s( error, _countof(error), "Animation [%s] not compatible!!\n MODEL ID [%d]\n Resource path [%s]\n Skeleton name [%s]\n", 
							animName.c_str(), mParentModelDeclID, decl->path.c_str(), decl->skeletonFileName.c_str() );

						MG_MESSAGE(error);
					}
				}
			}

			if (anim && mAnimSet)
			{
				Ogre::AnimationState *animState = NULL;
				if ( mAnimSet->hasAnimationState(animName) == false )
				{
					animState = mAnimSet->createAnimationState(animName, 0.0, anim->getLength());

					if ( animState )
					{
						addAnimation(animName,animState);
						return true;
					}
				}
			}

        }

        return false;
    }
	//-----------------------------------------------------------------------
	void AnimationController::applyAnimInfo(Str animName, AnimationInfo* animInfo)
	{
		if ( animInfo != NULL )
		{
			ActionDeclaration* animDecl = MG::ResourceManager::getSingletonPtr()->getActionDeclaration( getParentModelDeclID(), animName );
			if ( animDecl )
			{
				animInfo->isReverse = animDecl->isReverse;
				animInfo->isStopLastFrame = animDecl->isStopLastFrame;
			}
		}
	}
    //-----------------------------------------------------------------------
    void AnimationController::addAnimation(Str animName, Ogre::AnimationState * animState)
    {
        AnimationInfo info;
        info.animationState     = animState;
        info.animationState->setLoop(true);
        info.category           = 0;
        info.priority           = 0;
        info.rate               = 1.0;
        info.isPaused           = false;
        info.isPlaying          = false;
        info.isReverse          = false;
        info.isStopLastFrame    = false;
        info.isBlendingEnable   = mBlendingEnable;
        info.isIdle				= false;
        info.isChangeDirty		= false;
        info.isActive		    = false;
        mAnimations[ animName ] = info;

		applyAnimInfo(animName, &mAnimations[ animName ]);
    }
    //-----------------------------------------------------------------------
    void AnimationController::update( Real delta )
    {
        updateIdle( delta );

        Real newdelta;
        ActiveAnimationMap_iter ai = mActiveAnimations.begin();
        for(;ai != mActiveAnimations.end(); ++ai)
        {
            newdelta = delta * ai->second->rate;
            updateWeight( newdelta, ai->first, ai->second );
            updateTimePosition( newdelta, ai->first, ai->second );
        }

        updateActiveAnimationPool();
    }

    //-----------------------------------------------------------------------
    void AnimationController::setEnabled( CChar* animName, Bool enable )
    {
        AnimationInfo* anim = getAnimationInfo( animName );
        DYNAMIC_ASSERT(anim!=NULL);
        if ( anim )
        {
            anim->animationState->setEnabled( enable );
        }
    }

    //-----------------------------------------------------------------------
    Bool AnimationController::getEnabled( CChar* animName )
    {
        AnimationInfo* anim = getAnimationInfo( animName );
        DYNAMIC_ASSERT(anim!=NULL);
        if ( anim )
        {
            return anim->animationState->getEnabled();
        }
        return false;
    }

    //-----------------------------------------------------------------------
    void AnimationController::play( CChar* animName, Bool isReset )
    {
        if ( isPlaying(animName) == true )
            return;

        if (hasAnimation(animName)==false)
            if ( loadSeparateAnimation(animName) == false )
                return;

        if ( canAnimationPlayable(animName) )
        {
            startAnimation(animName, isReset);
            handleConflictAnimations(animName);
            updateIdle( 0 );
        }
    }

    //-----------------------------------------------------------------------
    void AnimationController::pause( CChar* animName )
    {
        AnimationInfo* anim = getAnimationInfo( animName );
        DYNAMIC_ASSERT(anim!=NULL);
        if ( anim )
        {
            anim->isPaused = true;
        }
    }

    //-----------------------------------------------------------------------
    void AnimationController::resume( CChar* animName )
    {
        AnimationInfo* anim = getAnimationInfo( animName );
        DYNAMIC_ASSERT(anim!=NULL);
        if ( anim )
        {
            anim->isPaused = false;
        }
    }

    //-----------------------------------------------------------------------
    void AnimationController::stop( CChar* animName )
    {
        stopAnimation( animName );
        updateIdle( 0 );
    }

    //-----------------------------------------------------------------------
    void AnimationController::stopAll() 
    {
        ActiveAnimationMap_iter ai = mActiveAnimations.begin();
        for(;ai != mActiveAnimations.end(); ++ai)
        {
            stop( ai->first.c_str() );
        }
    }

    //-----------------------------------------------------------------------
    void AnimationController::getAnimationList( std::vector<Str>& list )
    {
        for(AnimationMap_iter it = mAnimations.begin(); it != mAnimations.end(); ++it)
            list.push_back(it->first);
    }

    //-----------------------------------------------------------------------
    Bool AnimationController::hasAnimation( CChar* animName )
    {
        AnimationMap_iter ai = mAnimations.find(animName);
        return ai != mAnimations.end();
    }

    //-----------------------------------------------------------------------
    Bool AnimationController::isPlaying( CChar* animName )
    {
        AnimationInfo* anim = getAnimationInfo( animName );
       // DYNAMIC_ASSERT(anim!=NULL);
        if ( anim )
        {
            return anim->isPlaying;
        }
        return false;
    }

	//-----------------------------------------------------------------------
	Bool AnimationController::isIdlePlaying()
	{
		AnimationMap_iter ai = mAnimations.begin();
		int count = 0;
		for(;ai != mAnimations.end(); ++ai)
		{
			if( ai->second.isPlaying )
			{
				if ( ai->second.isIdle )
					return true;
			}
		}
		return false;
	}

    //-----------------------------------------------------------------------
    Flt AnimationController::getLength( CChar* animName )
    {
        AnimationInfo* anim = getAnimationInfo( animName );
        //DYNAMIC_ASSERT(anim!=NULL);
        if ( anim )
        {
            return anim->animationState->getLength();
        }
        return 0;
    }

    //-----------------------------------------------------------------------
    void AnimationController::setIsIdle( Bool isIdle, CChar* animName)
    {
        if (hasAnimation(animName)==false)
            if ( loadSeparateAnimation(animName) == false )
                return;

        AnimationInfo* anim = getAnimationInfo( animName );
        DYNAMIC_ASSERT(anim!=NULL);
        if ( anim )
        {
            if ( isIdle ){
                setActive( animName, true );
				// the method updateIdle() will start it
				anim->isPlaying = false;
				anim->animationState->setEnabled(false);
			}else
			{
				if ( anim->isIdle )	{
					if ( anim->isPlaying ){
						// if this animation is playing, enter blending out stage;
						stopAnimation(animName);
					}else
					{
						// if not playing yet, remove it directly
						anim->isActive = false;
						anim->animationState->setEnabled(false);
					}
				}
			}

			anim->isIdle = isIdle;
        }
    }

    //-----------------------------------------------------------------------
    void AnimationController::setBlendingTime(Flt time) 
    {
        mBlendingTime = time;
    }

    //-----------------------------------------------------------------------
    Flt AnimationController::getBlendingTime(void) const 
    {
        return mBlendingTime;
    }

    //-----------------------------------------------------------------------
    void AnimationController::setBlendingEnable(Bool enable) 
    {
        mBlendingEnable = enable;
        AnimationMap_iter ai = mAnimations.begin();
        for(;ai != mAnimations.end(); ++ai)
        {
            setBlendingEnable( ai->first.c_str(), enable );
        }
    }

    //-----------------------------------------------------------------------
    Bool AnimationController::getBlendingEnable(void) const 
    {
        return mBlendingEnable;
    }

    //-----------------------------------------------------------------------
    void AnimationController::setBlendingEnable( CChar* animName, Bool enable) 
    {
        AnimationInfo* anim = getAnimationInfo( animName );
        DYNAMIC_ASSERT(anim!=NULL);
        if ( anim )
        {
            anim->isBlendingEnable = enable;
        }
    }

    //-----------------------------------------------------------------------
    Bool AnimationController::getBlendingEnable( CChar* animName) 
    {
        AnimationInfo* anim = getAnimationInfo( animName );
        DYNAMIC_ASSERT(anim!=NULL);
        if ( anim )
        {
            return anim->isBlendingEnable ;
        }
        return false;
    }

    //-----------------------------------------------------------------------
    void AnimationController::setReverse( CChar* animName, Bool isReverse ) 
    {
        AnimationInfo* anim = getAnimationInfo( animName );
        DYNAMIC_ASSERT(anim!=NULL);
        if ( anim )
        {
            anim->isReverse = isReverse;
        }
    }

    //-----------------------------------------------------------------------
    Bool AnimationController::isReverse( CChar* animName ) 
    {
        AnimationInfo* anim = getAnimationInfo( animName );
        DYNAMIC_ASSERT(anim!=NULL);
        if ( anim )
        {
            return anim->isReverse;
        }
        return false;
    }

    //-----------------------------------------------------------------------
    void AnimationController::setTimePosition( CChar* animName, Flt pos) 
    {
        AnimationInfo* anim = getAnimationInfo( animName );
        DYNAMIC_ASSERT(anim!=NULL);
        if ( anim )
        {
            anim->animationState->setTimePosition( pos );
        }
    }

    //-----------------------------------------------------------------------
    Flt AnimationController::getTimePosition( CChar* animName ) 
    {
        AnimationInfo* anim = getAnimationInfo( animName );
        DYNAMIC_ASSERT(anim!=NULL);
        if ( anim )
        {
            return anim->animationState->getTimePosition();
        }
        return 0;
    }

    //-----------------------------------------------------------------------
    void AnimationController::setWeight( CChar* animName, Flt wight) 
    {
        AnimationInfo* anim = getAnimationInfo( animName );
        DYNAMIC_ASSERT(anim!=NULL);
        if ( anim )
        {
            anim->animationState->setWeight( wight );
        } 
    }

    //-----------------------------------------------------------------------
    Flt AnimationController::getWeight( CChar* animName ) 
    {
        AnimationInfo* anim = getAnimationInfo( animName );
        DYNAMIC_ASSERT(anim!=NULL);
        if ( anim )
        {
            return anim->animationState->getWeight();
        }
        return 0;
    }

    //-----------------------------------------------------------------------
    void AnimationController::setLoop( CChar* animName, Bool isLoop ) 
    {
        AnimationInfo* anim = getAnimationInfo( animName );
        //DYNAMIC_ASSERT(anim!=NULL);
        if ( anim )
        {
            anim->animationState->setLoop(isLoop);
        } 
    }

    //-----------------------------------------------------------------------
    Bool AnimationController::isLoop( CChar* animName ) 
    {
        AnimationInfo* anim = getAnimationInfo( animName );
        DYNAMIC_ASSERT(anim!=NULL);
        if ( anim )
        {
            return anim->animationState->getLoop();
        }
        return 0;
    }

    //-----------------------------------------------------------------------
    void AnimationController::setLastFrameStopEnable( CChar* animName, Bool  enable ) 
    {
        AnimationInfo* anim = getAnimationInfo( animName );
        //DYNAMIC_ASSERT(anim!=NULL);
        if ( anim )
        {
            anim->isStopLastFrame = enable;
        } 
    }

    //-----------------------------------------------------------------------
    Bool AnimationController::getLastFrameStopEnable( CChar* animName ) 
    {
        AnimationInfo* anim = getAnimationInfo( animName );
        DYNAMIC_ASSERT(anim!=NULL);
        if ( anim )
        {
            return anim->isStopLastFrame;
        } 
        return false;
    }

    //-----------------------------------------------------------------------
    void AnimationController::setRate( CChar* animName, Flt rate ) 
    {
        AnimationInfo* anim = getAnimationInfo( animName );
        DYNAMIC_ASSERT(anim!=NULL);
        if ( anim )
        {
            anim->rate = rate;
        } 
    }

    //-----------------------------------------------------------------------
    Flt AnimationController::getRate( CChar* animName ) 
    {
        AnimationInfo* anim = getAnimationInfo( animName );
        DYNAMIC_ASSERT(anim!=NULL);
        if ( anim )
        {
            return anim->rate ;
        } 
        return 0;
    }

    //-----------------------------------------------------------------------
    void AnimationController::setPriority( CChar* animName, Int priority ) 
    {
        AnimationInfo* anim = getAnimationInfo( animName );
        DYNAMIC_ASSERT(anim!=NULL);
        if ( anim )
        {
            anim->priority = priority;
        } 
    }

    //-----------------------------------------------------------------------
    Int AnimationController::getPriority( CChar* animName ) 
    {
        AnimationInfo* anim = getAnimationInfo( animName );
        DYNAMIC_ASSERT(anim!=NULL);
        if ( anim )
        {
            return anim->priority;
        } 
        return 0;
    }

    //-----------------------------------------------------------------------
    void AnimationController::setCategory( CChar* animName, Int category ) 
    {
        AnimationInfo* anim = getAnimationInfo( animName );
        DYNAMIC_ASSERT(anim!=NULL);
        if ( anim )
        {
            anim->category = category;
        } 
    }

    //-----------------------------------------------------------------------
    Int AnimationController::getCategory( CChar* animName ) 
    {
        AnimationInfo* anim = getAnimationInfo( animName );
        DYNAMIC_ASSERT(anim!=NULL);
        if ( anim )
        {
            return anim->category ;
        } 
        return 0;
    }

    //-----------------------------------------------------------------------
    AnimationController::AnimationInfo* AnimationController::getAnimationInfo( const Str& animName )
    {
        AnimationInfo* info = 0;

        AnimationMap::iterator ai = mAnimations.find(animName);
        if (ai != mAnimations.end())
        {
            info = (&ai->second);
        }
            
        return info;
    }

    //-----------------------------------------------------------------------
    void AnimationController::setActive( const Str& animName, Bool active, Bool isIgnoreIdle )
    {
        AnimationInfo* anim = getAnimationInfo( animName );

        if ( anim )
        {
            if (active)
            {
                anim->isActive = true;
                mActiveAnimations[animName] = anim;
            }else
            {
                if ( !anim->isIdle || !isIgnoreIdle )
                    anim->isActive = false;
            }
        }
    }

    //-----------------------------------------------------------------------
    void AnimationController::updateActiveAnimationPool( void )
    {
        ActiveAnimationMap_iter ai = mActiveAnimations.begin();
        for(;ai != mActiveAnimations.end();)
        {
            if ( ai->second->isActive )
            {
                ai++;
            }else
            {
                ai = mActiveAnimations.erase( ai );
            }
        }
    }

    //-----------------------------------------------------------------------
    void AnimationController::handleConflictAnimations( const Str& animName )
    {
        AnimationInfo* info = getAnimationInfo(animName);
        if ( info && info->isActive )
        {
            ActiveAnimationMap_iter ai = mActiveAnimations.begin();
            for(;ai != mActiveAnimations.end(); ++ai)
            {
                if( (ai->second->isPlaying) && (!ai->second->isIdle) ) {
                    if( ai->first != animName ) {
                        if( isAnimationConflict( ai->second, info ) &&
                            ai->second->priority <= info->priority)
                        {
                            stopAnimation( ai->first );
                        }
                    }
                }
            }
        }
    }

    //-----------------------------------------------------------------------
    Bool AnimationController::canAnimationPlayable( const Str& animName )
    {
        AnimationInfo* info = getAnimationInfo(animName);

        ActiveAnimationMap_iter ai = mActiveAnimations.begin();
        for(;ai != mActiveAnimations.end(); ++ai)
        {
            if( ai->second->isPlaying ) {
                if( ai->first != animName ) {
                    if( isAnimationConflict( ai->second, info ) &&
                        ai->second->priority > info->priority)	// 冲突而且优先级低
                    {
                        return false;
                    }
                }
            }
        }

        return true;
    }

    //-----------------------------------------------------------------------
    Bool AnimationController::isAnimationConflict( const AnimationInfo* info1, const AnimationInfo* info2 )
    {
        if( (info1->category == info2->category) || (info1->category & info2->category) ) {
            return true;
        }
        return false;
    }

    //-----------------------------------------------------------------------
    Int AnimationController::getAnimationPlayingCount()
    {
        AnimationMap_iter ai = mAnimations.begin();
        int count = 0;
        for(;ai != mAnimations.end(); ++ai)
        {
            if( ai->second.isPlaying )
                count++;
        }
        return count;
    }

    //-----------------------------------------------------------------------
    void AnimationController::setIdleEnable( Bool enable, Real weight, bool isBlending, Real rate )
    {
        ActiveAnimationMap_iter ai = mActiveAnimations.begin();
        for(;ai != mActiveAnimations.end(); ++ai)
        {
            AnimationInfo* info = ai->second;
            if ( info->isIdle )
            {	
                String animname = ai->first;
                setBlendingEnable(animname.c_str(), isBlending);

                if (enable)
                {	
                    if (weight >= 1.0)
                        rate = 1.0;

                    if ( !info->isPlaying )
                    {
                        startAnimation(animname);
                        setWeight(animname.c_str(), weight);
                        setRate(animname.c_str(), rate);
                    }
                }else
                {
                    if ( info->isPlaying )
                    {
                        stopAnimation(animname);
                        setWeight(animname.c_str(), weight);
                        setRate(animname.c_str(), rate);
                    }
                }

                info->isChangeDirty	= true;
            }
        }
    }

    //-----------------------------------------------------------------------
    void AnimationController::updateIdle( Real delta )
    {
        Bool hasNoIdleAnimPlaying			= false;
        Real idleWeight						= 1.0;
        Bool idleIsblend					= mBlendingEnable;
        Real idleRate						= 1.0;
        ActiveAnimationMap_iter ai = mActiveAnimations.begin();
        for(;ai != mActiveAnimations.end(); ++ai)
        {	
            String animname = ai->first;
            AnimationInfo* info = ai->second;
            if ( ! info->isIdle )
            {
                if ( info->isPlaying )
                {
                    hasNoIdleAnimPlaying = true;
                    idleWeight  = 1.0 - info->animationState->getWeight();
                    idleIsblend = info->isBlendingEnable;
                    idleRate	= info->rate;
                    setIdleEnable( false, idleWeight, idleIsblend, idleRate );
                    break;
                }else
                {
                    if ( info->animationState->getEnabled() )
                    {
                        idleWeight  = 1.0 - info->animationState->getWeight();
                        idleIsblend = info->isBlendingEnable;
                        idleRate	= info->rate;
                    }
                }
            }
        }

        if (!hasNoIdleAnimPlaying)
        {
            setIdleEnable( true, idleWeight, idleIsblend, idleRate );
        }
    }

    //-----------------------------------------------------------------------
    void AnimationController::updateTimePosition( Real delta, const Str& animName, AnimationInfo* anim )
    {
        if ( ! anim->isPaused && anim->isPlaying )
        {
            //判断是否反转动画
            if (anim->isReverse)  
                delta = -delta;  //反转动画时间

            Real position, length, newposition;
            bool isLoop;

            position = anim->animationState->getTimePosition();
            length = anim->animationState->getLength();
            newposition = position + delta;
            isLoop= false;

            //判断是否播放到动画时间长度前或后2端
            if ( ! anim->isReverse ) 
            {
                isLoop = (newposition > length) && (position <= length);
            }
            else
                isLoop = (newposition <= 0) && (position > 0) ;

            if ( isLoop ) 
            {
                fireLoop(animName);
                //不循环时，自动触发停止动画事件
                if ( ! anim->animationState->getLoop() )
                {
                    if ( anim->isStopLastFrame )
                    {
                        if ( ! anim->isReverse ) 
                            newposition = length;
                        else
                            newposition = 0;
                    }else
                    {
                        stopAnimation(animName);
                    }
                }
            }

            //设置最终动画时间进度
            anim->animationState->setTimePosition( newposition ); 
            anim->isChangeDirty	= true;
        }
    }

    //-----------------------------------------------------------------------
    void AnimationController::updateWeight( Real delta, const Str& animName, AnimationInfo* anim )
    {
        if( !anim->isPaused ) {
            if( anim->animationState->getEnabled() ) {
                Real weight    = anim->animationState->getWeight();
                Real maxWeight = 1.0f ;

                if( anim->isPlaying ) {	

                    if ( weight > maxWeight )
                    {
                        weight = maxWeight;
                        anim->animationState->setWeight( weight );
                    }

                    if ( anim->isBlendingEnable )	
                    {	// 淡入..逐步加大动画权重
                        if ( weight < maxWeight )
                        {
                            weight += delta / mBlendingTime;
                            if( weight > maxWeight )
                                weight = maxWeight;	
                            anim->animationState->setWeight( weight );
                        }
                    }

                } else {	
                    if ( anim->isBlendingEnable )
                    {	// 淡出..逐步减小动画权重
                        if (weight > 0.0f)
                        {
                            weight -= delta  / mBlendingTime;
                            if( weight < 0.0f )
                            {
                                weight = 0.0f;
                                anim->animationState->setWeight( weight );
                                closeAnimation(animName);
                            }else
                            {
                                anim->animationState->setWeight( weight );
                            }
                        }
                    }else
                    {
                        closeAnimation(animName);
                    }
                }

                anim->isChangeDirty	= true;
            }
        }
    }

    //-----------------------------------------------------------------------
    void AnimationController::startAnimation( const Str& animName, Bool isReset )
    {
        setActive( animName, true );

        AnimationInfo* info = getAnimationInfo( animName );

        if ( info )
        {
            if ( !info->isPlaying )
            {
                if ( isReset )
                    info->animationState->setTimePosition( 0.0f );
                info->isPlaying = true;

                if ( !info->animationState->getEnabled() )
                {
                    if ( info->isBlendingEnable )
                        info->animationState->setWeight(0.0f);
                    else
                        info->animationState->setWeight(1.0f);
                }
            }
            
            info->isPaused = false;

            if (info->animationState->getEnabled()==false)
                info->animationState->setEnabled(true);

            fireStart(animName);
        }
    }

    //-----------------------------------------------------------------------
    void AnimationController::stopAnimation( const Str& animName )
    {
        AnimationInfo* info = getAnimationInfo( animName );
        if ( info && info->isPlaying && info->isActive )
        {
            info->isPlaying = false;

            if ( info->isBlendingEnable )
            {
                if ( info->animationState->getWeight() == 0.0f )
                    closeAnimation(animName);
            }
            else
            {
                //Notice:
                closeAnimation(animName);
                //info->animationState->setEnabled(false); 
            }

            fireStop(animName);
        }
    }

    //-----------------------------------------------------------------------
    void AnimationController::closeAnimation( const Str& animName )
    {
        AnimationInfo* info = getAnimationInfo( animName );
        if (info && info->isActive)
        {
            info->isPlaying = false;
            info->isPaused  = true;
            if (info->animationState->getEnabled()==true)
                info->animationState->setEnabled(false);
            setActive( animName, false );
        }
    }

    //-----------------------------------------------------------------------
    void AnimationController::addAnimationLisitener( Str name, IAnimationControllerListener* lisitener )
    {
        mLisiteners[name] = lisitener;
    }

    //-----------------------------------------------------------------------
    void AnimationController::removeAnimationLisitener( Str name )
    {
        std::map<Str,IAnimationControllerListener*>::iterator iter = mLisiteners.find( name );
        if ( iter!=mLisiteners.end() )
        {
            mLisiteners.erase( iter );
        }
    }

    //-----------------------------------------------------------------------
    void AnimationController::fireStart( const Str& animName )
    {
        std::map<Str,IAnimationControllerListener*>::iterator iter = mLisiteners.begin();
        for ( ;iter!=mLisiteners.end(); iter++)
        {
            iter->second->onAnimationStart( animName.c_str() );
        }
    }

    //-----------------------------------------------------------------------
    void AnimationController::fireStop( const Str& animName )
    {
        std::map<Str,IAnimationControllerListener*>::iterator iter = mLisiteners.begin();
        for ( ;iter!=mLisiteners.end(); iter++)
        {
            iter->second->onAnimationStop( animName.c_str() );
        }
    }

    //-----------------------------------------------------------------------
    void AnimationController::fireLoop( const Str& animName )
    {
        std::map<Str,IAnimationControllerListener*>::iterator iter = mLisiteners.begin();
        for ( ;iter!=mLisiteners.end(); iter++)
        {
            iter->second->onAnimationLoop( animName.c_str() );
        }
    }

}