/******************************************************************************/
#include "stdafx.h"
#include "CEmitterSkillEffect.h"
#include "CSceneManager.h"
#include "CLuaSkillSystem.h"
#include "ICollisionSystem.h"
#include "SkillNetPacketProcesser.h"
#include "ClientMain.h"
#include "CPlayer.h"
#include "ISceneNodeAction.h"
#include "IActionManager.h"
#include "CCharacterSceneEntity.h"
#include "CTroopSoldierEntity.h"
#include "CTroopEntity.h"
#include "IEffectEntity.h"
/******************************************************************************/

namespace MG
{

    //--------------------------------------------------------------------------
    CEmitterSkillEffect::CEmitterSkillEffect( CSkillObject* object )
        :CSkillEffect( object )
        ,mEffectEntity( NULL )
		,mMapId(0)
		,mDis(10)
		,mIsParabola(false)
		,mEmitterInterval(1)
		,mEmitType(ET_PARALLEL)
		,mFlyTrackType(FTT_LINE)
		,mScatterAngle(60)
		,mIsPuncture(false)
		,mMoveSpeed(1)
		,mEmitterNum(1)
		,mState(ESES_NULL)
    {
		mIsCheckCollsion = true;
    }

    //--------------------------------------------------------------------------
    CEmitterSkillEffect::~CEmitterSkillEffect()
    {
        end();
    }

    //--------------------------------------------------------------------------
    void CEmitterSkillEffect::start()
    {
        CSkillEffect::start();

		mMapId = CSceneManager::getInstance().getRegionId();

		CCharacterSceneEntity* characterSceneEntity = CSceneManager::getInstance().getCharacterSceneEntity(mSkillObject->getOwnerType(), mSkillObject->getOwnerID(), mSkillObject->getOwnerIndex());
		if(!characterSceneEntity || characterSceneEntity->getDynamicData()->isDied)
		{
			end();
			return;
		}

		mState = ESES_CREATEEFFECT;
    }

    //--------------------------------------------------------------------------
    void CEmitterSkillEffect::end()
    {
        CSkillEffect::end();

		EffectEntityInfo* effectEnitiyInfo = NULL;
		for(UInt i = 0; i < mEffectEntity.size(); ++i)
		{
			effectEnitiyInfo = mEffectEntity[i];
			if ( effectEnitiyInfo && effectEnitiyInfo->effectEntity)
			{
				// CN_MODIFY
				CSceneManager::getInstance().getEngineScene()->destroyEffectComponent( effectEnitiyInfo->effectEntity->getName().c_str() );
				//CSceneManager::getInstance().getEngineScene()->destroyEffectEntity( effectEnitiyInfo->effectEntity->getName().c_str() );
				effectEnitiyInfo->effectEntity = NULL;
			}

			MG_SAFE_DELETE(effectEnitiyInfo);
		} 

		mEffectEntity.clear();
    }

    //--------------------------------------------------------------------------
    void CEmitterSkillEffect::update( Flt delta )
    {
		//FUNDETECTION(__MG_FUNC__);
        CSkillEffect::update( delta );

		CCharacterSceneEntity* characterSceneEntity = CSceneManager::getInstance().getCharacterSceneEntity(mSkillObject->getOwnerType(), mSkillObject->getOwnerID(), mSkillObject->getTargetObjectIndex());
		if(!characterSceneEntity || characterSceneEntity->getDynamicData()->isDied)
		{
			end();
			return;
		}
	
		switch(mState)
		{
		case ESES_CREATEEFFECT:
			createEffect(characterSceneEntity);
			break;

		case ESES_CHECKCOLLISION:
			checkCollision(characterSceneEntity);
			break;
		}
    }

	//-----------------------------------------------------------------------
	void CEmitterSkillEffect::setStartPos( Vec3 pos )
	{
		mPos = pos;
	}

	//-----------------------------------------------------------------------
	void CEmitterSkillEffect::setStartDir( Vec3 dir )
	{
		mDir = dir;
	}

	//-----------------------------------------------------------------------
	void CEmitterSkillEffect::setDistance( Flt dis )
	{
		mDis = dis;
	}
	//-----------------------------------------------------------------------
	void CEmitterSkillEffect::setPitchAngle( Flt angle )
	{
		mPitchAngle = angle;
	}
	//-----------------------------------------------------------------------
	void CEmitterSkillEffect::setScatterAngle( Flt angle )
	{
		mScatterAngle = angle;
	}
	//-----------------------------------------------------------------------
	void CEmitterSkillEffect::setYawAngle( Flt angle )
	{
		mYawAngle = angle;
	}
	//-----------------------------------------------------------------------
	void CEmitterSkillEffect::setEmitType(EmitType emitType)
	{
		mEmitType = emitType;
	}
	//-----------------------------------------------------------------------
	void CEmitterSkillEffect::setFlyTrackType( FlyTrackType flyTrackType )
	{
		mFlyTrackType = flyTrackType;
	}
	//-----------------------------------------------------------------------
	void CEmitterSkillEffect::setEmitterNum( UInt num )
	{
		mEmitterNum = num;
	}
	//-----------------------------------------------------------------------
	void CEmitterSkillEffect::setIsParabola( Bool IsParabola )
	{
		mIsParabola = IsParabola;
	}
	//-----------------------------------------------------------------------
	void CEmitterSkillEffect::setEmitterInterval(UInt interval)
	{
		mEmitterInterval = interval;
	}
	//-----------------------------------------------------------------------
	void CEmitterSkillEffect::setTargetPos( Vec3 pos )
	{
		mTargetPos = pos;
	}
	//-----------------------------------------------------------------------
	void CEmitterSkillEffect::setIsPuncture( Bool isPuncture )
	{
		mIsPuncture = isPuncture;
	}
	//-----------------------------------------------------------------------
	void CEmitterSkillEffect::setMoveSpeed( Flt speed )
	{
		mMoveSpeed = speed;
	}

	Bool CEmitterSkillEffect::getIsCanHit( CCharacterSceneEntity* hitCharacterSceneEntity )
	{
		if(!hitCharacterSceneEntity)
		{
			return false;
		}

		CCharacterSceneEntity* characterSceneEntity =  CSceneManager::getInstance().getCharacterSceneEntity(mSkillObject->getOwnerType(), mSkillObject->getOwnerID(), mSkillObject->getOwnerIndex());
		if(!characterSceneEntity)
		{
			end();
			return false;
		}

		IdType id = 0;
		UInt index = 0;
		if(characterSceneEntity->getType() == GOT_SOLDIER)
		{
			id = ((CTroopSoldierEntity*)characterSceneEntity)->getTroopEntity()->getID();
			index = characterSceneEntity->getID();
		}
		else
		{
			id = characterSceneEntity->getID();
		}

		IdType hitId = 0;
		UInt hitIndex = 0;
		if(hitCharacterSceneEntity->getType() == GOT_SOLDIER)
		{
			hitId = ((CTroopSoldierEntity*)hitCharacterSceneEntity)->getTroopEntity()->getID();
			hitIndex = hitCharacterSceneEntity->getID();
		}
		else
		{
			hitId = hitCharacterSceneEntity->getID();
		}

		if((id == hitId && index == hitIndex) || characterSceneEntity->getDynamicData()->force == hitCharacterSceneEntity->getDynamicData()->force)
		{
			return true;
		}

		return false;
	}

	//-----------------------------------------------------------------------
	void CEmitterSkillEffect::createEffect( CCharacterSceneEntity* characterSceneEntity )
	{
		Bool isOdd = true;
		if(mEmitterNum % 2 == 0)
		{
			isOdd = false;
		}

		mMapId = CSceneManager::getInstance().getRegionId();

		mPos = characterSceneEntity->getPos(false);

		EffectEntityInfo* effectEntityInfo = NULL;
		GAMEOBJ_TYPE ownerType = mSkillObject->getOwnerType();

		for(UInt i = 0; i < mEmitterNum; ++i)
		{
			effectEntityInfo = new EffectEntityInfo;
			// CN_MODIFY
			effectEntityInfo->effectEntity = CSceneManager::getInstance().getEngineScene()->createEffectComponent(mEffectFileId, false);

			mPos.y += (characterSceneEntity->getEntity()->getModelObject()->getHeight() / 2);

			if ( effectEntityInfo->effectEntity )
			{
				Vec3 des;

				mEffectEntity.push_back(effectEntityInfo);

				switch(mEmitType)
				{
				case ET_PARALLEL:
					{
						Vec3 pos;
						Int interval = 0;
						Int intervalDis = 0;
						Vec3 intervalDir;
						if(isOdd == true)
						{
							interval = (mEmitterNum - 1)/2 * mEmitterInterval;
						}
						else
						{
							interval = mEmitterNum * mEmitterInterval / 2 - mEmitterInterval / 2;
						}

						intervalDir = MGMath::getNormaliseVerticalVector(mDir);
						intervalDis = -interval + i * mEmitterInterval;
						pos = mPos + intervalDir * intervalDis;

						effectEntityInfo->effectEntity->getSceneNode()->setPosition( pos );
						effectEntityInfo->effectEntity->getSceneNode()->setDirection( mDir );			
						des = pos + mDir * mDis;
					}
					break;
				case ET_SCATTER:
					{
						Flt startAngle = mScatterAngle / 2;
						Flt intervalAngle = mScatterAngle / (mEmitterNum - 1);
						Vec3 dir;

						effectEntityInfo->effectEntity->getSceneNode()->setPosition( mPos );
						effectEntityInfo->effectEntity->getSceneNode()->setDirection( mDir);
						Flt angle = startAngle - (i * intervalAngle);
						effectEntityInfo->effectEntity->getSceneNode()->yaw(angle * (MG_PI / 180), ISceneNode::TS_WORLD);
						effectEntityInfo->effectEntity->getSceneNode()->getDirection( dir );
						des = mPos + dir * mDis;
					}
					break;
				}

				effectEntityInfo->effectEntity->getSceneNode()->getPosition( effectEntityInfo->effectEntityLastPos );

				switch(mFlyTrackType)
				{
				case FTT_LINE:
					{
						if(mIsParabola)
						{

						}
						else
						{
							ISceneNodeLineMoveToAction* lineMoveToAction = effectEntityInfo->effectEntity->getSceneNode()->getScene()->getActionManager()->createSceneNodeLineMoveToAction(effectEntityInfo->effectEntity->getSceneNode());
							lineMoveToAction->setMoveSpeed(mMoveSpeed);
							lineMoveToAction->setStickTerrain(false);
							lineMoveToAction->setIgnoreHeight(false);
							lineMoveToAction->setMoveToDestination(des);

							effectEntityInfo->effectEntity->getSceneNode()->getLinedStateManager()->push(lineMoveToAction);
						}

					}
					break;
				case FTT_HELICAL:
					break;
				case FTT_GATHERED:
					break;
				case FTT_DIVERGENT:
					break;
				}

			}
		}

		mState = ESES_CHECKCOLLISION;
	}

	//-----------------------------------------------------------------------
	void CEmitterSkillEffect::checkCollision( CCharacterSceneEntity* characterSceneEntity )
	{
		EffectEntityInfo* effectEnitiyInfo = NULL;

		UInt visibleNum = 0;
		for(UInt i = 0; i < mEffectEntity.size(); ++i)
		{
			effectEnitiyInfo = mEffectEntity[i];
			if ( effectEnitiyInfo && effectEnitiyInfo->effectEntity)
			{
				visibleNum++;
                if( !effectEnitiyInfo->effectEntity->getSceneNode()->getLinedStateManager()->getState("SceneNodeLineMoveToAction", false) &&
                    !effectEnitiyInfo->effectEntity->getSceneNode()->getLinedStateManager()->getState("SceneNodeGridLineMoveToAction", false) )
                {
					// CN_MODIFY
					CSceneManager::getInstance().getEngineScene()->destroyEffectComponent( effectEnitiyInfo->effectEntity->getName().c_str() );
					effectEnitiyInfo->effectEntity = NULL;
					MG_SAFE_DELETE(effectEnitiyInfo);
					mEffectEntity[i] = NULL;
					continue;
				}
				else
				{
					if(!mIsCheckCollsion)
					{
						continue;
					}

					// 检测碰撞
					Vec3 currPos;
					effectEnitiyInfo->effectEntity->getSceneNode()->getPosition( currPos );
					//currPos.y -= 0.5;

					ISceneObjectCollisionCallback callback;
					callback.queryFlagsMask =  GQT_SOLDIER | GQT_PLAYERCHARACTER | GQT_BUILDING | GQT_MONSTER | GQT_TROOP;
					callback.isCheckSingle = false;
					if ( CSceneManager::getInstance().getEngineScene()->getCollisionSystem()->checkLineCollision(currPos,effectEnitiyInfo->effectEntityLastPos,&callback)/*CSceneManager::getInstance().getEngineScene()->getCollisionSystem()->checkLineCollision(currPos,mEffectEntityLastPos,callback)*/ )
					{
						ISceneObject* sceneObject = callback.collisionList[0].second;
						ILogicBinder* logicBinder =  NULL;
						logicBinder =  sceneObject->getLogicBinder();

						// 分派处理鼠标点击事件

						if(!logicBinder)
						{
							continue;
						}

						CCharacterSceneEntity* hitCharacterSceneEntity= (CCharacterSceneEntity*)logicBinder->manager;
						if(!hitCharacterSceneEntity || hitCharacterSceneEntity->getDynamicData()->isDied)
						{
							continue;
						}

						if(getIsCanHit(hitCharacterSceneEntity))
						{
							continue;
						}

						if(!mIsPuncture)
						{
							// CN_MODIFY
							CSceneManager::getInstance().getEngineScene()->destroyEffectComponent( effectEnitiyInfo->effectEntity->getName().c_str() );
							effectEnitiyInfo->effectEntity = NULL;
							MG_SAFE_DELETE(effectEnitiyInfo);
							mEffectEntity[i] = NULL;
						}


						effectCollision(characterSceneEntity, hitCharacterSceneEntity);
					}

					if(effectEnitiyInfo)
					{
						effectEnitiyInfo->effectEntityLastPos = currPos;
					}

				}

			}
		}

		if(visibleNum == 0)
		{
			end();
		}
	}

	//-----------------------------------------------------------------------
	void CEmitterSkillEffect::effectCollision( CCharacterSceneEntity* characterSceneEntity,  CCharacterSceneEntity* hitCharacterSceneEntity )
	{
		CLuaSkillSystem::getInstance().execClientCollisionAffectScript( hitCharacterSceneEntity, 1, mSkillObject, this);

		if(hitCharacterSceneEntity->getType() == GOT_MONSTER)
		{
			CCharacterSceneEntity* characterSceneEntity =  CSceneManager::getInstance().getCharacterSceneEntity(mSkillObject->getOwnerType(), mSkillObject->getOwnerID(), mSkillObject->getOwnerIndex());
			if(!characterSceneEntity)
			{
				end();
				return;
			}

			if(characterSceneEntity->getDynamicData()->belongPlayerID !=  CPlayer::getInstance().getAccountID())
			{
				end();
				return;
			}

			SkillNetPacketProcesser::getInstance().sendSkillCharacterCollisionAffectCharacter( mSkillObject->getOwnerType(), characterSceneEntity, hitCharacterSceneEntity->getType(), hitCharacterSceneEntity, 1,this->getSkillID(), mMapId);
		}
		else if(hitCharacterSceneEntity->getDynamicData()->belongPlayerID == CPlayer::getInstance().getAccountID())
		{
			CCharacterSceneEntity* characterSceneEntity =  CSceneManager::getInstance().getCharacterSceneEntity(mSkillObject->getOwnerType(), mSkillObject->getOwnerID(), mSkillObject->getOwnerIndex());
			if(!characterSceneEntity)
			{
				end();
				return;
			}

			SkillNetPacketProcesser::getInstance().sendSkillCharacterCollisionAffectCharacter( mSkillObject->getOwnerType(), characterSceneEntity, hitCharacterSceneEntity->getType(), hitCharacterSceneEntity, 1,this->getSkillID(), mMapId);
		}
	}

	//-----------------------------------------------------------------------
	void CEmitterSkillEffect::getParllelEmitStartPosAndEndPos( UInt index, UInt emitterNum, UInt emitterInterval, Vec3& startPos, Vec3& endPos )
	{
		Bool isOdd = true;
		if(mEmitterNum % 2 == 0)
		{
			isOdd = false;
		}

		Vec3 pos;
		Int interval = 0;
		Int intervalDis = 0;
		Vec3 intervalDir;
		if(isOdd == true)
		{
			interval = (emitterNum - 1)/2 * emitterInterval;
		}
		else
		{
			interval = emitterNum * emitterInterval / 2 - emitterInterval / 2;
		}

		intervalDir = MGMath::getNormaliseVerticalVector(mDir);
		intervalDis = -interval + index * emitterInterval;
		startPos = mPos + intervalDir * intervalDis;
		
		endPos = startPos + mDir * mDis;
	}

	//-----------------------------------------------------------------------
	Flt CEmitterSkillEffect::getScatterEmitAngle( UInt index, UInt emitterNum, Flt scatterAngle )
	{
		Flt startAngle = scatterAngle / 2;
		Flt intervalAngle = scatterAngle / (emitterNum - 1);

		return startAngle - (index * intervalAngle);
	}
   
}