/******************************************************************************/
#include "stdafx.h"
#include "CTroopEntity.h"
#include "CSceneManager.h"
#include "HeadDesManage.h"
#include "HeadDes.h"
#include "ClientMain.h"
#include "CSkillUseManager.h"
#include "CTroopSoldierEntity.h"
#include "IDynamicBlockObject.h"
#include "CharacterList.h"
#include "CPlayer.h"
#include "FightManager.h"
#include "FightAiGroupTemplate.h"
#include "CharacterArmyList.h"
#include "CAISoldierInTroopMove.h"
#include "CAISoldierInTroopAttack.h"
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    CTroopEntity::CTroopEntity( IEntityGroup* entityGroup )
		:CCharacterSceneEntity(NULL, GOT_TROOP, GQT_TROOP, (MG_NEW TroopEntityData))
        ,mEntityGroup(entityGroup)
		,mFlagEntity(NULL)
		,mFightManager(NULL)
		,mFightAIGroup(NULL)
		,mAISoldierInTroopMove(NULL)
		,mAISoldierInTroopAttack(NULL)
		,mIsWaitMove(false)
    {
    }

    //-----------------------------------------------------------------------
    CTroopEntity::~CTroopEntity()
    {
		MG_SAFE_DELETE(mAISoldierInTroopMove);
		MG_SAFE_DELETE(mAISoldierInTroopAttack);

		getActionStateManager().clear();
		getAIStateManager().clear();
		unInitialize();
    }

    //-----------------------------------------------------------------------
    void CTroopEntity::initialize()
    {
        if ( mTroopSoldierEntityList.size() <= 0 )
            return;

		mAISoldierInTroopMove = MG_NEW CAISoldierInTroopMove(this);
		mAISoldierInTroopAttack = MG_NEW CAISoldierInTroopAttack(this);

        std::map<UInt, CTroopSoldierEntity*>::iterator troopSoldierObjectIt = mTroopSoldierEntityList.begin();
        CTroopSoldierEntity* tempCTroopSoldierEntity = troopSoldierObjectIt->second;

        //////////////////////////////////////////////////////////////////////

        //mHeadDes在CSceneEntity中并没有创建
        //因为CTroopObject并不创建实体。
        //mHeadDes记录的是一个实体集合。
        if ( !mHeadDes )
        mHeadDes = HeadDesManage::getInstance().createHeadDes( this );
        mHeadDes->setHeight( tempCTroopSoldierEntity->getEntity()->getModelObject()->getHeight() );

		//////////////////////////////////////////////////////////////////////

		const CharacterTempInfo* pInfo =  CharacterTemplate::getInstance().getCharacterTempInfo(getDynamicData()->mCharacterTemplateID);
		DYNAMIC_ASSERT(pInfo);

		//计算属性。
		if ( CPlayer::getInstance().getAccountID() == getDynamicData()->belongPlayerID )
		{
			mCAttributeSystem.calBaseAttr(pInfo);

			CharacterData characterData;
			characterData.mLevel = getDynamicData()->mLevel;
			characterData.mLineageNum = getDynamicData()->mLineageNum;
			mCAttributeSystem.calFinalAttr(pInfo->getCharacterFormulaType(), &characterData);

			mFightAIGroup = FightAIGroupTemplate::getInstance().getFightAIGroup(pInfo->getAIFightGroupId());
		}

		IEntity* entity = ClientMain::getInstance().getScene()->createEntity(pInfo->getArmyCollisionMeshId());
		if(!entity)
		{
			DYNAMIC_ASSERT(entity == NULL);
			return;
		}

		mEntity = entity;
		mEntity->getSceneNode()->setVisible(false);
		mEntity->getSceneNode()->setPosition(getDynamicData()->mPos);


        //////////////////////////////////////////////////////////////////////

        CCharacterSceneEntity::initialize();

        //////////////////////////////////////////////////////////////////////


		if(mEntity->getModelObject()->getPatherRadius() > 6)
		{
			DYNAMIC_ASSERT(mEntity->getModelObject()->getPatherRadius() > 6);
		}

        createFlag(181001);

		IDynamicBlockObject* dynamicBlockObject = mEntity->createOrRetrieveDynamicBlockObject();
		if(dynamicBlockObject)
		{
			dynamicBlockObject->setStructureMode(false);
			dynamicBlockObject->setEnable(true);
			//dynamicBlockObject->setShowBlock(true);
		}
    }

    //-----------------------------------------------------------------------
    void CTroopEntity::unInitialize()
    {
        destroySoldierEntitys();

        if(mEntityGroup)
        {
            ClientMain::getInstance().getScene()->destroyEntityGroup(mEntityGroup->getName().c_str());
            mEntityGroup = NULL;
        }

        destroyFlag();

		CCharacterSceneEntity::unInitialize();

		MG_SAFE_DELETE(mFightManager);
    }
    
    //-----------------------------------------------------------------------
    void CTroopEntity::update(Flt delta)
    {
        CCharacterSceneEntity::update(delta);

        updateSoldierEntitys( delta );

		if(mFlagEntity)
		{
			IScene* scene = ClientMain::getInstance().getScene();
			ICamera* camera = scene->getActiveCamera();
			if(camera)
			{
				Vec3 dir;
				camera->getDirection(dir);
				mFlagEntity->getSceneNode()->setDirection(Vec3(dir.x,0,dir.z));
			}

			Vec3 centerPos = getTroopCenterPos();
			mFlagEntity->getSceneNode()->setPosition(centerPos);
			mFlagEntity->getSceneNode()->stickTerrain();
		}

    }

	//---------------------------------------------------------------------------------
	TroopEntityData* CTroopEntity::getDynamicData()
	{
		return dynamic_cast<TroopEntityData*>(CSceneObject::getDynamicData());
	}

	//-----------------------------------------------------------------------
	Bool CTroopEntity::getWorldPos( Vec3& worldPos )
	{
		worldPos = getPos();

		return true;
	}

	//-----------------------------------------------------------------------
	Bool CTroopEntity::isInScreen()
	{
		std::map<UInt, CTroopSoldierEntity*>::iterator iter =   mTroopSoldierEntityList.begin();
		if ( iter != mTroopSoldierEntityList.end() )
		{
			IEntity* entity = iter->second->getEntity();
			if ( !entity )
				return false;

			if ( !entity->isRendering() )
				return false;
		}

		return true;
	}

    //-----------------------------------------------------------------------
    CTroopSoldierEntity* CTroopEntity::createSoldierEntitys( UInt index , TroopSoldierEntityData* data )
    {
        CTroopSoldierEntity* troopSoldierEntity = getSoldierEntitys(index);
		//IDynamicBlockObject* dynamicBlockObject = NULL;

        if ( troopSoldierEntity == NULL )
        {
            IEntity* entity = mEntityGroup->getEntity( index );
            if ( entity )
            {
                troopSoldierEntity = MG_NEW CTroopSoldierEntity( this, entity );
                mTroopSoldierEntityList[index] = troopSoldierEntity;

                // copy data
                *(troopSoldierEntity->getDynamicData()) = *data;
				troopSoldierEntity->setPos(data->mPos);

				troopSoldierEntity->initialize();

				troopSoldierEntity->getEntity()->getSceneNode()->setVisible(true);
                
    //            dynamicBlockObject = troopSoldierEntity->getEntity()->createOrRetrieveDynamicBlockObject();
				//if(dynamicBlockObject)
				//{
				//	dynamicBlockObject->setStructureMode(false);

    //                if ( troopSoldierEntity->getDynamicData()->force == FORCE_INIT )
    //                {
    //                    dynamicBlockObject->setEnable( false );
    //                }else
    //                {
				//	    dynamicBlockObject->setEnable(true);
    //                }
				//}

				Color color = CSceneManager::getInstance().getTroopSoldierColor(data->force, data->belongPlayerID);
				entity->getModelObject()->setEmissive(color);
            }
        }

        return troopSoldierEntity;
    }

    //-----------------------------------------------------------------------
    CTroopSoldierEntity* CTroopEntity::getSoldierEntitys( ISceneObject* sceneObj )
    {
        std::map<UInt, CTroopSoldierEntity*>::iterator iter =   mTroopSoldierEntityList.begin();
        for ( ; iter != mTroopSoldierEntityList.end() ; iter++ )
        {
            IEntity* entity = iter->second->getEntity();
            if ( (ISceneObject*)entity == sceneObj )
                return iter->second;
        }
        return NULL;
    }

    //-----------------------------------------------------------------------
    CTroopSoldierEntity* CTroopEntity::getSoldierEntitys( UInt soldierId )
    {
        std::map<UInt, CTroopSoldierEntity*>::iterator iter =   mTroopSoldierEntityList.find( soldierId );
        if ( iter != mTroopSoldierEntityList.end() )
        {
            return iter->second;
        }
        return NULL;
    }

	//-----------------------------------------------------------------------
	CTroopSoldierEntity* CTroopEntity::getSoldierEntitysByIndex( UInt index )
	{
		UInt soldierIndex = 0;
		
		for(std::map<UInt, CTroopSoldierEntity*>::iterator iter = mTroopSoldierEntityList.begin(); iter != mTroopSoldierEntityList.end(); ++iter)
		{
			if(soldierIndex == index)
			{
				return iter->second;
			}

			soldierIndex++;
		}

		return NULL;
	}

    //-----------------------------------------------------------------------
    void CTroopEntity::destroySoldierEntitys( UInt soldierId )
    {
        std::map<UInt, CTroopSoldierEntity*>::iterator iter =  mTroopSoldierEntityList.find( soldierId );
        if ( iter != mTroopSoldierEntityList.end() )
        {
            MG_SAFE_DELETE( iter->second );
            mTroopSoldierEntityList.erase( iter );
        }
    }

    //-----------------------------------------------------------------------
    void CTroopEntity::destroySoldierEntitys()
    {
        std::map<UInt, CTroopSoldierEntity*>::iterator iter =  mTroopSoldierEntityList.begin( );
        for ( ; iter != mTroopSoldierEntityList.end() ; iter++ )
        {
            MG_SAFE_DELETE( iter->second );
        }
        mTroopSoldierEntityList.clear();
    }
    
    //-----------------------------------------------------------------------
    void CTroopEntity::updateSoldierEntitys(Flt delta)
    {
        std::map<UInt, CTroopSoldierEntity*>::iterator iter =  mTroopSoldierEntityList.begin( );
        for ( ; iter != mTroopSoldierEntityList.end() ; )
        {
			if(!iter->second)
			{
				++iter;
				continue;
			}

			if(iter->second->getDynamicData()->isDestroy)
			{
				MG_SAFE_DELETE( iter->second );
				iter = mTroopSoldierEntityList.erase(iter);
				continue;
			}

            iter->second->update(delta);
			++iter;
        }
    }

	//-----------------------------------------------------------------------
	UInt CTroopEntity::getSoldierEntitysNum()
	{
		return mTroopSoldierEntityList.size();
	}

	//-----------------------------------------------------------------------
	std::map<UInt, CTroopSoldierEntity*>* CTroopEntity::getSoldierEntitysList()
	{
		return &mTroopSoldierEntityList;
	}

    //-----------------------------------------------------------------------
	Vec3 CTroopEntity::getTroopCenterPos()
	{
		Flt minX;
		Flt minZ;
		Flt maxX;
		Flt maxZ;
		Vec3 pos;

		if(mTroopSoldierEntityList.size() == 0)
		{
			return pos;
		}

		for( std::map<UInt, CTroopSoldierEntity*>::iterator troopSoldierObjectIt = mTroopSoldierEntityList.begin(); troopSoldierObjectIt != mTroopSoldierEntityList.end(); ++troopSoldierObjectIt )
		{
			if(!troopSoldierObjectIt->second || troopSoldierObjectIt->second->getDynamicData()->isDied)
			{
				continue;
			}
			pos = troopSoldierObjectIt->second->getPos();
/*			if(troopSoldierObjectIt == mTroopSoldierEntityList.begin())
			{
				minX = pos.x;
				minZ = pos.z;
				maxX = minX;
				maxZ = minZ;
			}
			else if(minX > pos.x)
			{
				minX = pos.x;
			}
			else if(minZ > pos.z)
			{
				minZ = pos.z;
			}
			else if(maxX < pos.x)
			{
				maxX = pos.x;
			}
			else if(maxZ < pos.z)
			{
				maxZ = pos.z;
			}*/

		}

		return pos;/*Vec3((minX + maxX) / 2, 0, (minZ + maxZ) / 2);*/
	}

	//-----------------------------------------------------------------------
	void CTroopEntity::createFlag(UInt flgModleId)
	{
        if ( !mFlagEntity )
        {
            mFlagEntity = CSceneManager::getInstance().getEngineScene()->createEntity(flgModleId);
            if(!mFlagEntity)
            {
                return;
            }

            Color flagColor;
            if(CSceneObject::getDynamicData()->force == FORCE_ATTACK)
            {
                flagColor = Color(1.f, 0, 0, 1.f);
            }
            else
            {
                flagColor = Color(0, 0, 1.f, 1.f);
            }

            mFlagEntity->getModelObject()->setEmissive(flagColor);


			Flt animationTimeLen = mFlagEntity->getAnimationController()->getLength("none_none_stand");
			if(animationTimeLen > 0)
			{
				animationTimeLen *= 1000;
				animationTimeLen = (UInt)MGRandom::getInstance().rand_ab_One(0, (UInt)animationTimeLen);
			}
			else
			{ 
				animationTimeLen;
			}
			
            mFlagEntity->getAnimationController()->setIsIdle(true, "none_none_stand");
			mFlagEntity->getAnimationController()->play("none_none_stand");
			mFlagEntity->getAnimationController()->setTimePosition("none_none_stand", animationTimeLen / 1000);
        }
	}

	//-----------------------------------------------------------------------
	void CTroopEntity::destroyFlag()
	{
		if( mFlagEntity )
		{
		    CSceneManager::getInstance().getEngineScene()->destroyEntity(mFlagEntity->getName().c_str());
            mFlagEntity = NULL;
		}
	}

	//-----------------------------------------------------------------------
	FightManager* CTroopEntity::getFightManager()
	{
		return mFightManager;
	}

	//-----------------------------------------------------------------------
	CTroopSoldierEntity* CTroopEntity::getSoldierEntitysForMinDis( Vec3 pos )
	{
		CTroopSoldierEntity* minDisTroopSoldierEntity = NULL;
		CTroopSoldierEntity* tempTroopSoldierEntity = NULL;
		
		Flt minDis = 0;
		Flt tempDis = 0;
		pos.y = 0;

		for( std::map<UInt, CTroopSoldierEntity*>::iterator it = mTroopSoldierEntityList.begin(); it != mTroopSoldierEntityList.end(); ++it )
		{
			tempTroopSoldierEntity = it->second;
			if(!tempTroopSoldierEntity || tempTroopSoldierEntity->getDynamicData()->isDied)
			{
				continue;
			}

			tempDis = (tempTroopSoldierEntity->getPos() - pos).length();
			if( tempDis < minDis)
			{
				minDis = tempDis;
				minDisTroopSoldierEntity = tempTroopSoldierEntity;
			}
		}

		return minDisTroopSoldierEntity;
	}

	//-----------------------------------------------------------------------
	const FightAIGroup*	CTroopEntity::getFightAIGroup()
	{
		return mFightAIGroup;
	}

	//-----------------------------------------------------------------------
	void CTroopEntity::addFightAITriggerCount( UInt fightAIId )
	{
		mFightAITriggerCountList[fightAIId]++;
	}

	//-----------------------------------------------------------------------
	UInt CTroopEntity::getFightAITriggerCount( UInt fightAIId )
	{
		std::map<UInt, UInt>::iterator it = mFightAITriggerCountList.find(fightAIId);
		if(it == mFightAITriggerCountList.end())
		{
			return 0;
		}

		return it->second;
	}

	//-----------------------------------------------------------------------
	void CTroopEntity::clearFightAITriggerCount()
	{
		mFightAITriggerCountList.clear();
	}

	//---------------------------------------------------------------------------------------
	void CTroopEntity::doMoveToAction(Vec3 destination, Flt startTime, Bool isBlockCheck, ISceneNodeGridLineMoveToAction::MoveToPathFindType moveToPathFindType)
	{
		Vec3 currPos;
		mEntity->getSceneNode()->getPosition( currPos );

		doMoveToAction(currPos,destination,startTime,isBlockCheck,moveToPathFindType);
	}

	//---------------------------------------------------------------------------------------
	void CTroopEntity::doMoveToAction(Vec3 startPos, Vec3 destination, Flt startTime, Bool isBlockCheck, ISceneNodeGridLineMoveToAction::MoveToPathFindType moveToPathFindType)
	{
		if(!mAISoldierInTroopMove)
		{
			return;
		}

		mAISoldierInTroopMove->setDestination(destination);
		mAISoldierInTroopMove->setIsCheckBlock(isBlockCheck);
		mAISoldierInTroopMove->setMoveToPathFindType(moveToPathFindType);
		mAISoldierInTroopMove->onStartMove();
	}

	//---------------------------------------------------------------------------------------
	void CTroopEntity::stopMoveToAction()
	{
		if(mAISoldierInTroopMove)
		{
			mAISoldierInTroopMove->onEndMove();
		}

		CSceneEntity::stopMoveToAction();
	}

	//---------------------------------------------------------------------------------------
	void CTroopEntity::stopAttack()
	{
		CTroopSoldierEntity* troopSoldierEntity = NULL;

		for(std::map<UInt, CTroopSoldierEntity*>::iterator it = mTroopSoldierEntityList.begin(); it != mTroopSoldierEntityList.end(); ++it)
		{
			troopSoldierEntity = it->second;
			if(!troopSoldierEntity)
			{
				continue;
			}

			troopSoldierEntity->getAIStateManager().removeState("CAIEntityPathFindingPursueAttackInAdvance", false);
		}
	}

	////---------------------------------------------------------------------------------------
	//void CTroopEntity::clacTroopSoldierPos( Vec3 pos, std::vector<Vec3>& soldierPosList )
	//{
	//	soldierPosList.clear();

	//	Flt patherRadius = mEntity->getModelObject()->getPatherRadius();
	//	UInt soldierNum = mTroopSoldierEntityList.size();

	//	if(soldierNum == 1)
	//	{
	//		soldierPosList.push_back(pos);
	//		return;
	//	}

	//	Flt angle = 360 / soldierNum;

	//	for(UInt i = 0; i < soldierNum; ++i)
	//	{
	//		Vec3 dir(1,0,0);
	//		
	//		dir = MGMath::rotateVector(dir, angle * i * (MG_PI / 180));
	//		Flt dis = MGRandom::getInstance().rand_ab_One(10, (UInt)patherRadius * 1000);
	//		dis /= 1000;
	//		Vec3 soldierPos = pos + dir * dis;

	//		soldierPosList.push_back(soldierPos);
	//	}
	//}

	////---------------------------------------------------------------------------------------
	//void CTroopEntity::clacTroopSoldierPos( Vec3 pos, Vec3 dir, std::map<UInt, MoveToPosRow>& soldierPosList )
	//{
	//	soldierPosList.clear();

	//	Flt patherRadius = mEntityGroup->getModelObject()->getPatherRadius();
	//	UInt soldierNum = mTroopSoldierEntityList.size();
	//	UInt intervalRow = /*patherRadius * 4*/getCharacterTempInfo()->getArmyArmyX();
	//	UInt intervalCol = getCharacterTempInfo()->getArmyArmyY()/*intervalRow*/;
	//	UInt colNum = getCharacterTempInfo()->getArmyListNum()/*(sqrt((Flt)soldierNum / 2))* 2*/;
	//	UInt rowNum = soldierNum / colNum;
	//	if(colNum * rowNum < soldierNum)
	//	{
	//		rowNum++;
	//	}

	//	/*Vec3 dir(0,0,1);*/

	//	Vec3 colDir = MGMath::rotateVector(dir, (Flt)90 * (MG_PI / 180));

	//	Flt offsetRow = 0;
	//	Flt offsetCol = 0;

	//	if(colNum % 2 == 1)
	//	{
	//		offsetCol = colNum / 2;
	//	}
	//	else
	//	{
	//		offsetCol = (Flt)colNum / 2 - 0.5;
	//	}

	//	if(rowNum % 2 == 1)
	//	{
	//		offsetRow = rowNum / 2;
	//	}
	//	else
	//	{
	//		offsetRow = (Flt)rowNum / 2 - 0.5;
	//	}

	//	Vec3 startPoint = pos + dir * offsetRow * intervalRow + colDir * offsetCol * intervalCol;
	//	startPoint.y = 0;
	//	Vec3 elementPos = startPoint;

	//	Flt col = 0;
	//	Flt colGap = 0;
	//	Flt rowGap = 0;
	//	Vec3 tempPos;

	//	MoveToPosRow moveToPosRow;

	//	Flt row = 1;
	//	soldierPosList[row] = moveToPosRow;

	//	for(UInt i = 0; i < soldierNum; ++i)
	//	{
	//		elementPos = startPoint - colDir * col * intervalCol;
	//		elementPos.y = 0;
	//		soldierPosList[row].moveToPos.push_back(elementPos);

	//		col++;

	//		if(col == colNum)
	//		{
	//			row++;
	//			moveToPosRow.moveToPos.clear();
	//			soldierPosList[row] = moveToPosRow;
	//			startPoint = startPoint - dir * intervalRow;
	//			col = 0;
	//		}
	//	}
	//}

	////---------------------------------------------------------------------------------------
	//void CTroopEntity::clacTroopSoldierMoveToPos( Vec3 pos, Vec3 dir, std::map<UInt, Vec3>& soldierPosList )
	//{
	//	std::map<UInt, MoveToPosRow> tempSoldierPosList;
	//	clacTroopSoldierPos(pos, dir, tempSoldierPosList);

	//	std::vector<UInt> soldierList;
	//	for(UInt i = 0; i < mTroopSoldierEntityList.size(); ++i)
	//	{
	//		soldierList.push_back(i);
	//	}

	//	Flt tempDis;
	//	Vec3 soldierPos;
	//	Flt minDis = 0;

	//	std::vector<Vec3>::iterator minPosIt;
	//	std::vector<UInt>::iterator minSoldierIt;

	//	for(std::map<UInt, MoveToPosRow>::iterator rowPosIt = tempSoldierPosList.begin(); rowPosIt != tempSoldierPosList.end(); ++rowPosIt)
	//	{
	//		while(rowPosIt->second.moveToPos.size() != 0)
	//		{
	//			for(std::vector<Vec3>::iterator posIt = rowPosIt->second.moveToPos.begin(); posIt != rowPosIt->second.moveToPos.end(); ++posIt)
	//			{
	//				for(std::vector<UInt>::iterator soldierIt = soldierList.begin(); soldierIt != soldierList.end(); ++soldierIt)
	//				{
	//					soldierPos = mTroopSoldierEntityList[(*soldierIt)]->getPos();
	//					tempDis = ((*posIt) - soldierPos).length();

	//					if(minDis > tempDis || posIt == rowPosIt->second.moveToPos.begin() && soldierIt == soldierList.begin())
	//					{
	//						minDis = tempDis;
	//						minPosIt = posIt;
	//						minSoldierIt = soldierIt;
	//					}
	//				}
	//			}

	//			soldierPosList[(*minSoldierIt)] = (*minPosIt);
	//			rowPosIt->second.moveToPos.erase(minPosIt);
	//			soldierList.erase(minSoldierIt);
	//		}
	//	}
	//}

	//---------------------------------------------------------------------------------------
	void CTroopEntity::checkTroopMove()
	{

	}

	//---------------------------------------------------------------------------------------
	void CTroopEntity::useSkill( IdType skillId, Byte targetType, IdType targetId, Vec3 taegetPos )
	{
		if(!mAISoldierInTroopAttack)
		{
			return;
		}

		mAISoldierInTroopAttack->setUseSkill(skillId);
		mAISoldierInTroopAttack->setTarget((GAMEOBJ_TYPE)targetType, targetId, taegetPos);
		mAISoldierInTroopAttack->onUseSkill();
		//CTroopSoldierEntity* troopSoldierEntity = NULL;
		//for(std::map<UInt, CTroopSoldierEntity*>::iterator it = mTroopSoldierEntityList.begin(); it != mTroopSoldierEntityList.end(); ++it)
		//{
		//	troopSoldierEntity = it->second;
		//	if(!troopSoldierEntity)
		//	{
		//		continue;
		//	}

		//	CAIEntityPathFindingPursueAttackInAdvance* ai = CAIManager::getInstance().createCAIEntityPathFindingPursueAttackInAdvance(troopSoldierEntity); 
		//	if(targetId != 0)
		//	{
		//		ai->setTarget((GAMEOBJ_TYPE)targetType, targetId, 0);
		//	}
		//	else
		//	{
		//		ai->setTarget(taegetPos);
		//	}

		//	ai->setUseSkillId(skillId);
		//	//ai->setAIEntityGroup(this);
		//	ai->setIsSelectTargetObject(true);

		//	troopSoldierEntity->getAIStateManager().push(ai);
		//}
	}

	//---------------------------------------------------------------------------------------
	void CTroopEntity::clearAIState()
	{
		getAIStateManager().clear();

		CTroopSoldierEntity* troopSoldierEntity = NULL;
		for(std::map<UInt, CTroopSoldierEntity*>::iterator it = mTroopSoldierEntityList.begin(); it != mTroopSoldierEntityList.end(); ++it)
		{
			troopSoldierEntity = it->second;
			if(!troopSoldierEntity)
			{
				continue;
			}

			troopSoldierEntity->getAIStateManager().clear();
		}
	}

	//---------------------------------------------------------------------------------------
	void CTroopEntity::clearActionState()
	{
		getActionStateManager().clear();

		CTroopSoldierEntity* troopSoldierEntity = NULL;
		for(std::map<UInt, CTroopSoldierEntity*>::iterator it = mTroopSoldierEntityList.begin(); it != mTroopSoldierEntityList.end(); ++it)
		{
			troopSoldierEntity = it->second;
			if(!troopSoldierEntity)
			{
				continue;
			}

			troopSoldierEntity->getActionStateManager().clear();
		}
	}

	//---------------------------------------------------------------------------------------
	void CTroopEntity::playAnimation(Str animName, Bool randomTimePlaye, Bool isLoop, Bool isLastFrameStop, Bool isReset)
	{
		CTroopSoldierEntity* troopSoldierEntity = NULL;
		for(std::map<UInt, CTroopSoldierEntity*>::iterator it = mTroopSoldierEntityList.begin(); it != mTroopSoldierEntityList.end(); ++it)
		{
			troopSoldierEntity = it->second;
			if(!troopSoldierEntity)
			{
				continue;
			}

			troopSoldierEntity->playAnimation(animName, randomTimePlaye, isLoop, isLastFrameStop, isReset);
		}
	}

	//---------------------------------------------------------------------------------------
	void CTroopEntity::stopAnimation(Str animName)
	{
		CTroopSoldierEntity* troopSoldierEntity = NULL;
		for(std::map<UInt, CTroopSoldierEntity*>::iterator it = mTroopSoldierEntityList.begin(); it != mTroopSoldierEntityList.end(); ++it)
		{
			troopSoldierEntity = it->second;
			if(!troopSoldierEntity)
			{
				continue;
			}

			troopSoldierEntity->stopAnimation(animName);
		}
	}

	//---------------------------------------------------------------------------------------
	IEntityGroup* CTroopEntity::getEntityGroup()
	{
		return mEntityGroup;
	}

	//---------------------------------------------------------------------------------------
	CAISoldierInTroopMove* CTroopEntity::getCAISoldierInTroopMove()
	{
		return mAISoldierInTroopMove;
	}

	//---------------------------------------------------------------------------------------
	void CTroopEntity::setBattleState(Bool isBattle)
	{
		CCharacterSceneEntity::setBattleState(isBattle);

		CTroopSoldierEntity* troopSoldierEntity = NULL;
		for(std::map<UInt, CTroopSoldierEntity*>::iterator it = mTroopSoldierEntityList.begin(); it != mTroopSoldierEntityList.end(); ++it)
		{
			troopSoldierEntity = it->second;
			if(!troopSoldierEntity)
			{
				continue;
			}

			troopSoldierEntity->setBattleState(isBattle);
		}
	}

	//---------------------------------------------------------------------------------------
	void CTroopEntity::setMoveSpeed(Flt moveSpeed)
	{
		getDynamicData()->moveSpeed = moveSpeed;

		CTroopSoldierEntity* troopSoldierEntity = NULL;
		for(std::map<UInt, CTroopSoldierEntity*>::iterator it = mTroopSoldierEntityList.begin(); it != mTroopSoldierEntityList.end(); ++it)
		{
			troopSoldierEntity = it->second;
			if(!troopSoldierEntity)
			{
				continue;
			}

			troopSoldierEntity->getDynamicData()->moveSpeed = moveSpeed;
		}
	}

}