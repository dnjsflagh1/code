/******************************************************************************/

#include "stdafx.h"
#include "OperationObjectGroup.h"
#include "GameObject.h"
#include "GameObjectOpCtrl.h"
#include "ClientMain.h"
#include "CPlayerCharacter.h"
#include "PlayCharacterNetPacketProcesser.h"
#include "PlayerNetPacketProcesser.h"
#include "CPlayer.h"
#include "CSceneManager.h"
#include "SkillNetPacketProcesser.h"
#include "PlaceNetPacketProcesser.h"
#include "GameNetPacket.h"
#include "ICollisionSystem.h"
#include "UIJumpRegion.h"
#include "CBuildingEntity.h"
#include "CNpcEntity.h"
#include "CAIManager.h"
#include "CCharacterSceneEntity.h"
#include "CAIManager.h"
#include "CAIEntityGroupPathFindingMoveInAdvance.h"
#include "CPlayerCharacterEntity.h"
#include "CTroopEntity.h"
#include "CTroopSoldierEntity.h"
#include "UISkillOperate.h"
#include "SkillInfoList.h"
#include "TargetPosAreaSkillTemplate.h"
#include "ParabolaAreaSkillTemplate.h"
#include "IDynamicBlockObject.h"
#include "CItemEntity.h"
#include "ItemPacketProcesser.h"
#include "ItemData.h"
#include "CAIController.h"
#include "MessageManager.h"
#include "IBlockManager.h"
#include "UIClanInfo.h"
/******************************************************************************/

namespace MG
{


    //--------------------------------------------------------------------------
    OperationObjectGroup::OperationObjectGroup()
		: mPreparedSkillId(0)
    {
        revert();
    }

    //--------------------------------------------------------------------------
    OperationObjectGroup::~OperationObjectGroup()
    {
        
    }

    //--------------------------------------------------------------------------
    void OperationObjectGroup::update(Flt delta)
    {
        filterOperationObjectList();
        updateSelectDecalEffect();
    }

    //--------------------------------------------------------------------------
    void OperationObjectGroup::setState(GAMEOBJECT_OP_STATE state)
    {
        mState = state;
    }
	
	 //--------------------------------------------------------------------------
	GAMEOBJECT_OP_STATE OperationObjectGroup::getState()
	{
		return mState;
	}

    //--------------------------------------------------------------------------
    void OperationObjectGroup::revert()
    {
		mPreparedSkillId = 0;
        setState( GOS_NORMAL );

		IPointer* pPointer = ClientMain::getInstance().getPointer();
		if(!pPointer)
		{
			return;
		}

		pPointer->setPointer( pointerStatusName[ MGPOINTER_STATUS_NORMAL ] );
    }

    //--------------------------------------------------------------------------
    void OperationObjectGroup::clear()
    {
        mGameObjectList.clear();

        revert();
    }

    //--------------------------------------------------------------------------
    void OperationObjectGroup::requestUseSkill(IdType skillId, GAMEOBJ_TYPE userType, IdType userId, UInt userIndex)
    {
		SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(skillId);
		if(!skillInfo || !skillInfo->skillInfo)
		{
			return;
		}

		CCharacterSceneEntity* characterSceneEntity = CSceneManager::getInstance().getCharacterSceneEntity(userType, userId, userIndex);
		if(!characterSceneEntity)
		{
			return;
		}
		
		CSkillUseManager* skillUseManager = characterSceneEntity->getSkillUseManager();
		if(skillUseManager->checkCD(skillInfo))
		{
			return;
		}

		if(characterSceneEntity->getType() != GOT_TROOP && characterSceneEntity->getType() != GOT_SOLDIER && characterSceneEntity->getDynamicData()->mp <= 0 && skillInfo->skillType != SKT_SHORTRANGEGENERAL
			&& skillInfo->skillType != SKT_LONGRANGEGENERAL && skillInfo->skillType != SKT_GOUPANDDOWN)
		{
			MessageManager::getInstance().addChatMsgForTest(L"MP不足");
			return;
		}

		skillUseManager->addCD(skillInfo, CSkillUseManager::AACSCT_PUBLIC);

		mPreparedSkillId = skillId;
		setState( GOS_SKILL_PREPARE );
		
		if(skillInfo->skillType == SKT_SELFAREA || skillInfo->skillType == SKT_GOUPANDDOWN)
		{
			Vec3 pos = characterSceneEntity->getPos();
			attack(pos);
			revert();
			return;
		}
		else if(skillInfo->skillType == SKT_TARGETPOSAREA)
		{
			TargetPosAreaSkillInfo* targetPosAreaSkillInfo = (TargetPosAreaSkillInfo*)skillInfo->skillInfo;
			GameObjectOpCtrl::getInstance().createPointSkillDecal(targetPosAreaSkillInfo->pointEffectId, targetPosAreaSkillInfo->skillRadius);
		}
		else if(skillInfo->skillType == SKT_PARABOLAAREA)
		{
			ParabolaAreaSkillInfo* parabolaAreaSkillInfo = (ParabolaAreaSkillInfo*)skillInfo->skillInfo;
			GameObjectOpCtrl::getInstance().createPointSkillDecal(parabolaAreaSkillInfo->pointEffectId, parabolaAreaSkillInfo->skillRadius);
		}
		else if(skillInfo->skillType == SKT_SINGLETARGET || skillInfo->skillType == SKT_SINGLEEMITTER)
		{
			IPointer* pPointer = ClientMain::getInstance().getPointer();
			if(!pPointer)
			{
				return;
			}

			pPointer->setPointer( pointerStatusName[ MGPOINTER_STATUS_SKILL2 ] );
		}
    }
  
    //--------------------------------------------------------------------------
    void OperationObjectGroup::selectGameObject( CSceneEntity* entity, Bool isOne )
    {
        if( entity->getDynamicData()->belongPlayerID != CPlayer::getInstance().getAccountID() )
        {
            return;
        }

		// 如果不是下面几种类型，不要加入到可控制对象队列中
		if( entity->getType() == GOT_PLAYERCHARACTER || 
			entity->getType() == GOT_TROOP || 
			entity->getType() == GOT_SOLDIER )
		{	
			CCharacterSceneEntity* characterEntity = dynamic_cast<CCharacterSceneEntity*>(entity);

			if( characterEntity && characterEntity->getDynamicData()->isDied)
			{
				return;
			}
		}else
		{
			return;
		}

		addGameObject( entity, isOne );
    }

    //--------------------------------------------------------------------------
    Bool OperationObjectGroup::hasGameObject( CSceneEntity* entity )
    {
        GAMEOBJ_TYPE objType            = entity->getType();
        IdType id                       = entity->getID();
        OperationObjectList& objList    = mGameObjectList[objType];
        objList.type                    = objType;

        if ( objList.objectList.find( id ) != objList.objectList.end()  )
        {
            return true;
        }

        return false;
    }

    //--------------------------------------------------------------------------
    void OperationObjectGroup::addGameObject( CSceneEntity* entity, Bool isOne )
    {
        /////////////////////////////////////////////////////////////////////////////

        if ( isOne )
            clear();

        /////////////////////////////////////////////////////////////////////////////

        GAMEOBJ_TYPE objType            = entity->getType();
        IdType id                       = entity->getID();
        OperationObjectList& objList    = mGameObjectList[objType];


        /////////////////////////////////////////////////////////////////////////////

        if ( objType == GOT_PLAYERCHARACTER )
        {
			OperationObject& obj  = objList.objectList[entity->getID()];
			obj.entityList[entity->getID()].sceneEntity = entity;
			obj.type = OOT_NULL;

            CPlayerCharacterEntity* charEntity = (CPlayerCharacterEntity*)entity;
            if ( charEntity )
            {
                if(true/* CPlayer::getInstance().getActiveClan()->hasPlayerCharacter( id ) */)
                {
                    obj.type = OOT_MY;
					UISkillOperate::getInstance().addSkillIcon(GOT_PLAYERCHARACTER, charEntity->getID(), 0);
					//UIClanInfo::getInstance().addCharSkillList();
					UISkillOperate::getInstance().addCharItemIcon(GOT_PLAYERCHARACTER, charEntity->getID(), 0);

                }else 
                {
                    //if ( CPlayer::getInstance().getCampaignSystem()->getMyForce() == charEntity->getDynamicData()->force )
                    //{
                    //    obj.type = OOT_FRIEND;
                    //}else
                    //{
                    //    obj.type = OOT_ENEMY;
                    //}
                }
            }
        }else
        if ( objType == GOT_NPC )
        {
            
        }
		else if( objType == GOT_TROOP )
		{
			//CTroopSoldierEntity* troopSoldierEntity = (CTroopSoldierEntity*)entity;
			OperationObject& obj  = objList.objectList[entity->getID()/*troopSoldierEntity->getTroopEntity()->getID()*/];
			obj.entityList[entity->getID()/*troopSoldierEntity->getID()*/].sceneEntity = entity;
			//obj.entityList[troopSoldierEntity->getID()].row = 0;
			obj.type = OOT_NULL;

			CTroopEntity* troopEntity = (CTroopEntity*)entity;
			if ( troopEntity )
			{
				if( CPlayer::getInstance().getAccountID() ==  troopEntity->getDynamicData()->belongPlayerID)
				{
					obj.type = OOT_MY;
					UISkillOperate::getInstance().addSkillIcon(GOT_SOLDIER, troopEntity->getID(), 0/*troopSoldierEntity->getID()*/);
					//UISkillOperate::getInstance().addCharItemIcon(GOT_SOLDIER, troopEntity->getID(), 0/*troopSoldierEntity->getID()*/);
				}else
				{
					//if ( CPlayer::getInstance().getCampaignSystem()->getMyForce() == soldierEntity->getDynamicData()->force )
					//{
					//	obj.type = OOT_FRIEND;
					//}else
					//{
					//	obj.type = OOT_ENEMY;
					//}
				}
			}
		}

        /////////////////////////////////////////////////////////////////////////////
    }

    //--------------------------------------------------------------------------
    Bool OperationObjectGroup::removeGameObject( GAMEOBJ_TYPE objType, IdType id )
    {
        OperationObjectList& objList    = mGameObjectList[objType];

        std::map<IdType, OperationObject>::iterator iter = objList.objectList.find( id );
        if ( iter != objList.objectList.end() )
        {
            objList.objectList.erase( iter );
        }
        return true;
    }

    //--------------------------------------------------------------------------
    Bool OperationObjectGroup::removeGameObject( CSceneEntity* entity )
    {
        removeGameObject( entity->getType(), entity->getID() );
        return true;
    }

    //--------------------------------------------------------------------------
    void OperationObjectGroup::updateSelectDecalEffect()
    {
        GameObjectOpCtrl* ctrl = &GameObjectOpCtrl::getInstance();

        std::map<GAMEOBJ_TYPE,OperationObjectList>::iterator iter = mGameObjectList.begin();
        for ( ; iter != mGameObjectList.end() ; iter++ )
        {
            GAMEOBJ_TYPE objType      = iter->first;
            OperationObjectList& list = iter->second;

            std::map<IdType, OperationObject>::iterator jter = list.objectList.begin();
            for ( ; jter != list.objectList.end() ; jter++ )
            {
                IdType id               = jter->first;
                OperationObject& opObj  = jter->second; 

				std::map<IdType, OperationEntity>::iterator kter = opObj.entityList.begin();
				for( ; kter != opObj.entityList.end() ; kter++ )
				{
					if ( kter->second.sceneEntity )
					{
						IDecalSet*		  decalSet  = NULL;
						UInt*             decalNum  = NULL;

						if ( opObj.type == OOT_FRIEND )
						{
							decalSet = ctrl->mFriendSelectDecalGroup;
							decalNum = &ctrl->mFriendSelectDecalNum;
						}else
						if ( opObj.type == OOT_ENEMY )
						{
							decalSet = ctrl->mEnemySelectDecalGroup;
							decalNum = &ctrl->mEnemySelectDecalNum;
						}else
						//if ( opObj.type == OOT_MY )
						{
							decalSet = ctrl->mMySelectDecalGroup;
							decalNum = &ctrl->mMySelectDecalNum;
						}

						if ( decalSet )
						{
							Vec3 pos;
							if ( kter->second.sceneEntity->getEntity() )
							{
								kter->second.sceneEntity->getEntity()->getSceneNode()->getPosition( pos );

								if( kter->second.sceneEntity->getType() == GOT_TROOP)
								{
									CTroopEntity* troopEntity = (CTroopEntity*)kter->second.sceneEntity;
									CTroopSoldierEntity* troopSoldierEntity = NULL;

									for(UInt i = 0; i < troopEntity->getSoldierEntitysNum(); ++i)
									{
										troopSoldierEntity = troopEntity->getSoldierEntitysByIndex(i);
										if(!troopSoldierEntity || troopSoldierEntity->getDynamicData()->isDied)
										{
											continue;
										}

										IDecal* decal = decalSet->getDecal(*decalNum);
										if (decal)
										{
											Flt radius = troopSoldierEntity->getEntity()->getModelObject()->getPatherRadius();

											decal->setVisible( true );
											decal->setPosition( troopSoldierEntity->getPos(false) );
											//decal->setSize( radius * 0.5 );
											decalSet->setSize( radius * 0.5 );
											(*decalNum)++;
										}

									}

									continue;
								}

								IDecal* decal = decalSet->getDecal(*decalNum);
								if (decal)
								{
                                    Flt radius = kter->second.sceneEntity->getEntity()->getModelObject()->getPatherRadius();

									decal->setVisible( true );
									decal->setPosition( pos );
									decalSet->setSize( radius );
									(*decalNum)++;
								}
							}
						}
					}
				}
            }
        }
    }

    //--------------------------------------------------------------------------
    void OperationObjectGroup::filterOperationObjectList()
    {
        std::map<GAMEOBJ_TYPE,OperationObjectList>::iterator iter = mGameObjectList.begin();
        for ( ; iter != mGameObjectList.end() ; iter++ )
        {
            GAMEOBJ_TYPE objType      = iter->first;
            OperationObjectList& list = iter->second;

            std::map<IdType, OperationObject>::iterator jter = list.objectList.begin();
            for ( ; jter != list.objectList.end() ; jter++ )
            {
                IdType objectId               = jter->first;
                OperationObject& obj    = jter->second; 

				std::map<IdType, OperationEntity>::iterator kter = obj.entityList.begin();
				for( ; kter != obj.entityList.end() ;  )
				{
					IdType entityId = kter->first;
					GAMEOBJ_TYPE entityType = kter->second.sceneEntity->getType();
					kter->second.sceneEntity = NULL;

					CCharacterSceneEntity* entity = CSceneManager::getInstance().getCharacterSceneEntity(entityType, objectId, entityId);
					kter->second.sceneEntity = entity;

					if(!kter->second.sceneEntity || kter->second.sceneEntity->getDynamicData()->belongPlayerID != CPlayer::getInstance().getAccountID())
					{
						kter = obj.entityList.erase(kter);
					}
					else
					{
						kter++;
					}
				}
            }
        }
    }

    //--------------------------------------------------------------------------
    void OperationObjectGroup::onMouseOver( CSceneEntity* entity )
    {
       if(!entity)
       {
		   return;
       }
		
	   IPointer* pPointer = ClientMain::getInstance().getPointer();
	   if(!pPointer)
	   {
		   return;
	   }

	   if ( (entity->getType() == GOT_NPC) ||
		   (entity->getType() == GOT_ORDINARY_BUILDING) )
	   {
		   pPointer->setPointer( pointerStatusName[ MGPOINTER_STATUS_TALK ] );
	   }else if ( (entity->getType() == GOT_TROOP) ||
		   (entity->getType() == GOT_PLAYERCHARACTER) )
	   {
		   if ( entity->getDynamicData()->force != CPlayer::getInstance().getForce() )
		   {
			   const SkillInfo* skillInfo = SkillInfoList::getInstance().getSkillInfo(mPreparedSkillId);
			   if(!skillInfo)
			   {
					return;
			   }

			   if(mState == GOS_SKILL_PREPARE && (skillInfo->skillType == SKT_SINGLETARGET || skillInfo->skillType == SKT_SINGLEEMITTER))
			   {
					pPointer->setPointer( pointerStatusName[ MGPOINTER_STATUS_SKILL1 ] );
			   }
			   else
			   {
					pPointer->setPointer( pointerStatusName[ MGPOINTER_STATUS_ATTACK ] );
			   }
			   
		   }else
		   {

		   }
		}else if ( entity->getType() == GOT_BUILDING )
		{
		   if ( entity->getDynamicData()->force != CPlayer::getInstance().getForce() )
		   {
			   const SkillInfo* skillInfo = SkillInfoList::getInstance().getSkillInfo(mPreparedSkillId);
			   if(!skillInfo)
			   {
				   return;
			   }

			   if(mState == GOS_SKILL_PREPARE && (skillInfo->skillType == SKT_SINGLETARGET || skillInfo->skillType == SKT_SINGLEEMITTER))
			   {
				   pPointer->setPointer( pointerStatusName[ MGPOINTER_STATUS_SKILL1 ] );
			   }
			   else
			   {
				   pPointer->setPointer( pointerStatusName[ MGPOINTER_STATUS_ATTACK ] );
			   }
			   
		   }else
		   {
			   pPointer->setPointer( pointerStatusName[ MGPOINTER_STATUS_TALK ] );
		   }
		}
		else if(entity->getType() == GOT_ITEM)
		{
		   IInput* input = ClientMain::getInstance().getEngine()->input();
		   if ( input && input->isMouseHolded(MB_Left) )
		   {
			   pPointer->setPointer( pointerStatusName[ MGPOINTER_STATUS_RPGPICK2 ] );
		   }
		   else
		   {
			   pPointer->setPointer( pointerStatusName[ MGPOINTER_STATUS_RPGPICK1 ] );
		   }  
		}
		else if(entity->getType() == GOT_MONSTER)
		{
			const SkillInfo* skillInfo = SkillInfoList::getInstance().getSkillInfo(mPreparedSkillId);
			if(!skillInfo)
			{
				return;
			}

			if(mState == GOS_SKILL_PREPARE && (skillInfo->skillType == SKT_SINGLETARGET || skillInfo->skillType == SKT_SINGLEEMITTER))
			{
				pPointer->setPointer( pointerStatusName[ MGPOINTER_STATUS_SKILL1 ] );
			}
			else
			{
				pPointer->setPointer( pointerStatusName[ MGPOINTER_STATUS_ATTACK ] );
			}
		}

    }

    //--------------------------------------------------------------------------
    void OperationObjectGroup::onMouseOver( Vec3 pos )
    {
		IPointer* pPointer = ClientMain::getInstance().getPointer();
		if(!pPointer)
		{
			return;
		}

		if(mState != GOS_SKILL_PREPARE)
		{
			if(ClientMain::getInstance().getScene()->getBlockManager()->isStaticBlock(pos))
			{
				pPointer->setPointer( pointerStatusName[ MGPOINTER_STATUS_DIS ] );
			}
			else
			{
				pPointer->setPointer( pointerStatusName[ MGPOINTER_STATUS_NORMAL ] );
			}
		}
		else
		{
			const SkillInfo* skillInfo = SkillInfoList::getInstance().getSkillInfo(mPreparedSkillId);
			if(!skillInfo)
			{
				return;
			}

			if(skillInfo->skillType == SKT_SINGLETARGET || skillInfo->skillType == SKT_SINGLEEMITTER)
			{
				pPointer->setPointer( pointerStatusName[ MGPOINTER_STATUS_SKILL2 ] );
			}
		}
    }

    //--------------------------------------------------------------------------
    void OperationObjectGroup::onLeftMousePressed( CSceneEntity* entity )
    {
		
		if(mState == GOS_SKILL_PREPARE)
		{
			SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(mPreparedSkillId);
			if(/*skillInfo->skillType != SKT_SINGLEEMITTER 
				&& skillInfo->skillType != SKT_TARGETPOSAREA
				&& */skillInfo->skillType != SKT_SINGLETARGET && skillInfo->skillType != SKT_LONGRANGEAUXILIARY)
			{
				Vec3 targetPos;
				entity->getEntity()->getSceneNode()->getPosition(targetPos);
				if(skillInfo->skillType == SKT_PARABOLAAREA)
				{
					targetPos.y += entity->getEntity()->getModelObject()->getHeight();
				}
				attack(targetPos);
			}
			else
			{
				attack(entity);
			}

			revert();
			GameObjectOpCtrl::getInstance().destroyPointSkillDecal();
			//mState = GOS_SKILL_USE;
		}
    }

    //--------------------------------------------------------------------------
    void OperationObjectGroup::onLeftMouseReleased( CSceneEntity* entity )
    {
		if(!entity || entity->getType() != GOT_ITEM)
		{
			return;
		}

		interact(entity);
		//CItemEntity* itemEntity = (CItemEntity*)entity;
		//pickItem(itemEntity);
    }
    
    //--------------------------------------------------------------------------
    void OperationObjectGroup::onLeftMouseClick( CSceneEntity* entity )
    {
        this->selectGameObject( entity, true );
    }

    //--------------------------------------------------------------------------
    void OperationObjectGroup::onLeftMousePressed( Vec3 pos )
    {
		if(mState == GOS_SKILL_PREPARE)
		{
			SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(mPreparedSkillId);
			if(skillInfo->skillType == SKT_SINGLEEMITTER 
				|| skillInfo->skillType == SKT_TARGETPOSAREA || skillInfo->skillType == SKT_PARABOLAAREA)
			{
				attack(pos);
				revert();
				GameObjectOpCtrl::getInstance().destroyPointSkillDecal();
				/*mState = GOS_SKILL_USE;*/
			}
		}
    }

    //--------------------------------------------------------------------------
    void OperationObjectGroup::onLeftMouseReleased( Vec3 pos )
    {

    }

    //--------------------------------------------------------------------------
    void OperationObjectGroup::onLeftMouseClick( Vec3 pressedPos, Vec3 releasedPos )
    {

    }

    //--------------------------------------------------------------------------
    void OperationObjectGroup::onRightMousePressed( CSceneEntity* entity )
    {

    }

    //--------------------------------------------------------------------------
    void OperationObjectGroup::onRightMouseReleased( CSceneEntity* entity )
    {
		
    }
    
    //--------------------------------------------------------------------------
    void OperationObjectGroup::onRightMouseClick( CSceneEntity* entity )
    {
		GameObjectOpCtrl::getInstance().destroyPointSkillDecal();
		if(entity->getType() == GOT_NPC || entity->getType() == GOT_ORDINARY_BUILDING)
		{
			interact(entity);
		}
		else
		{
			if(mState == GOS_NORMAL)
			{
				attack(entity);
			}
		}
    }

    //--------------------------------------------------------------------------
    void OperationObjectGroup::onRightMousePressed( Vec3 pos )
    {
		GameObjectOpCtrl::getInstance().destroyPointSkillDecal();
        moveTo( pos );
    }

    //--------------------------------------------------------------------------
    void OperationObjectGroup::onRightMouseReleased( Vec3 pos )
    {

    }

    //--------------------------------------------------------------------------
    void OperationObjectGroup::onRightMouseClick( Vec3 pressedPos, Vec3 releasedPos )
    {
        
    }

    //--------------------------------------------------------------------------
    void OperationObjectGroup::interact( CSceneEntity* entity )
    {
		GameObjectOpCtrl* ctrl = &GameObjectOpCtrl::getInstance();

		Vec3 destination;
		entity->getEntity()->getSceneNode()->getPosition(destination);
		
		if ( ctrl && mGameObjectList.size() != 0 )
		{
            ////////////////////////////////////////////////////////////////////////////////////////////

			LinedStateManager& stateMgr = ctrl->getAIGroupManager();
			CAIManager& aiMGr      = CAIManager::getInstance();
			CAIEntityGroupInteractiveInAdvance* ai = aiMGr.createCAIEntityGroupInteractiveInAdvance();
			ai->setTargetSceneEntity(entity);

			////////////////////////////////////////////////////////////////////////////////////////////

			std::map<GAMEOBJ_TYPE,OperationObjectList>::iterator iter = mGameObjectList.begin();
			for ( ; iter != mGameObjectList.end() ; iter++ )
			{
				GAMEOBJ_TYPE objType      = iter->first;
				OperationObjectList& list = iter->second;

				std::map<IdType, OperationObject>::iterator jter = list.objectList.begin();
				for ( ; jter != list.objectList.end() ; jter++ )
				{
					IdType id               = jter->first;
					OperationObject& opObj  = jter->second; 

					std::map<IdType, OperationEntity>::iterator kter = opObj.entityList.begin();
					for( ; kter != opObj.entityList.end() ;  kter++ )
					{
						if ( kter->second.sceneEntity )
						{
							if ( objType == GOT_PLAYERCHARACTER )
							{
								CPlayerCharacterEntity* entity = (CPlayerCharacterEntity*)kter->second.sceneEntity;
								ai->addSceneEntity( entity );
							}
						}
					}

				}
			}

			////////////////////////////////////////////////////////////////////////////////////////////

			stateMgr.push( ai );
		}
    }
    
    //--------------------------------------------------------------------------
    void OperationObjectGroup::attack( CSceneEntity* entity )
    {
		if(mGameObjectList.size() == 0)
		{
			return;
		}

		if(!entity)
		{
			return;
		}

		CCharacterSceneEntity* characterEntity = NULL;

		if( entity->getType() == GOT_PLAYERCHARACTER || 
			entity->getType() == GOT_TROOP || 
			entity->getType() == GOT_SOLDIER || 
			entity->getType() == GOT_MONSTER ||
			entity->getType() == GOT_BUILDING ||	
			entity->getType() == GOT_ORDINARY_BUILDING ||	
			entity->getType() == GOT_THIRDPARTYCHARACTER
			)
		{	
			characterEntity = dynamic_cast<CCharacterSceneEntity*>(entity);

			if( characterEntity && characterEntity->getDynamicData()->isDied)
			{
				return;
			}
		}else
		{
			return;
		}
		
		FORCE force1 = characterEntity->getDynamicData()->force;
		FORCE force2 = CPlayer::getInstance().getForce();

		if(characterEntity->getDynamicData()->isDied)
		{
			return;
		}

		const SkillInfo* skillInfo = SkillInfoList::getInstance().getSkillInfo(mPreparedSkillId);
		if(mPreparedSkillId == 0 || (skillInfo && skillInfo->skillType != SKT_LONGRANGEAUXILIARY))
		{
			if(characterEntity->getDynamicData()->force == CPlayer::getInstance().getForce())
			{
				return;
			}
		}
		else
		{
			if(characterEntity->getDynamicData()->force != CPlayer::getInstance().getForce())
			{
				return;
			}
		}

		GameObjectOpCtrl* ctrl = &GameObjectOpCtrl::getInstance();

		Vec3 destination;
		entity->getEntity()->getSceneNode()->getPosition(destination);

		if ( ctrl )
		{
            ////////////////////////////////////////////////////////////////////////////////////////////

			LinedStateManager& stateMgr = ctrl->getAIGroupManager();
			CAIManager& aiMGr      = CAIManager::getInstance();
			CAIEntityGroupPathFindingPursueAttackInAdvance* ai = aiMGr.createCAIEntityGroupPathFindingPursueAttackInAdvance();
			ai->setUseSkillId(mPreparedSkillId);

			if(entity->getType() == GOT_SOLDIER)
			{
				ai->setTarget(entity->getType(), ((CTroopSoldierEntity*)entity)->getTroopEntity()->getID(), entity->getID());
			}
			else /*if(entity->getType() == GOT_PLAYERCHARACTER)*/
			{
				ai->setTarget(entity->getType(), entity->getID());
			}
			
			////////////////////////////////////////////////////////////////////////////////////////////
			CAIController* aiController = NULL;

			std::map<GAMEOBJ_TYPE,OperationObjectList>::iterator iter = mGameObjectList.begin();
			for ( ; iter != mGameObjectList.end() ; iter++ )
			{
				GAMEOBJ_TYPE objType      = iter->first;
				OperationObjectList& list = iter->second;

				std::map<IdType, OperationObject>::iterator jter = list.objectList.begin();
				for ( ; jter != list.objectList.end() ; jter++ )
				{
					IdType id               = jter->first;
					OperationObject& opObj  = jter->second; 

					std::map<IdType, OperationEntity>::iterator kter = opObj.entityList.begin();
					for( ; kter != opObj.entityList.end() ;  kter++ )
					{				
						if ( kter->second.sceneEntity )
						{
							if(objType == GOT_SOLDIER)
							{
								ai->addSceneEntity( (CCharacterSceneEntity*)kter->second.sceneEntity, id );
							}
							else
							{
								ai->addSceneEntity( (CCharacterSceneEntity*)kter->second.sceneEntity );

								aiController = ((CCharacterSceneEntity*)kter->second.sceneEntity)->getAIController();
								if(aiController)
								{
									aiController->setIsPause(true);
								}
							}
						}
					}
				}
			}

			////////////////////////////////////////////////////////////////////////////////////////////

			stateMgr.push( ai );
		}
    }

    //--------------------------------------------------------------------------
    void OperationObjectGroup::attack( Vec3 pos )
    {
		if(mGameObjectList.size() == 0)
		{
			return;
		}

		FORCE force2 = CPlayer::getInstance().getForce()/* getFirstSceneEntity()->getDynamicData()->force*/;

		GameObjectOpCtrl* ctrl = &GameObjectOpCtrl::getInstance();

		if ( ctrl )
		{
            ////////////////////////////////////////////////////////////////////////////////////////////

			LinedStateManager& stateMgr = ctrl->getAIGroupManager();
			CAIManager& aiMGr      = CAIManager::getInstance();
			CAIEntityGroupPathFindingPursueAttackInAdvance* ai = aiMGr.createCAIEntityGroupPathFindingPursueAttackInAdvance();
			ai->setUseSkillId(mPreparedSkillId);
			ai->setTarget(pos);
	
			////////////////////////////////////////////////////////////////////////////////////////////
			CAIController* aiController = NULL;

			std::map<GAMEOBJ_TYPE,OperationObjectList>::iterator iter = mGameObjectList.begin();
			for ( ; iter != mGameObjectList.end() ; iter++ )
			{
				GAMEOBJ_TYPE objType      = iter->first;
				OperationObjectList& list = iter->second;

				std::map<IdType, OperationObject>::iterator jter = list.objectList.begin();
				for ( ; jter != list.objectList.end() ; jter++ )
				{
					IdType id               = jter->first;
					OperationObject& opObj  = jter->second; 

					std::map<IdType, OperationEntity>::iterator kter = opObj.entityList.begin();
					for( ; kter != opObj.entityList.end() ;  kter++ )
					{
						if ( kter->second.sceneEntity )
						{
							if(objType == GOT_SOLDIER)
							{
								ai->addSceneEntity( (CCharacterSceneEntity*)kter->second.sceneEntity, id );
							}
							else
							{
								ai->addSceneEntity( (CCharacterSceneEntity*)kter->second.sceneEntity );

								aiController = ((CCharacterSceneEntity*)kter->second.sceneEntity)->getAIController();
								if(aiController)
								{
									aiController->setIsPause(true);
								}
							}
						}
					}
				}
			}

			////////////////////////////////////////////////////////////////////////////////////////////

			stateMgr.push( ai );
		} 
    }
    
    //--------------------------------------------------------------------------
    void OperationObjectGroup::moveTo( Vec3 pos )
    {
		revert();

        GameObjectOpCtrl* ctrl = &GameObjectOpCtrl::getInstance();
		CCharacterSceneEntity* characterSceneEntity = NULL;

        if ( ctrl && mGameObjectList.size() != 0 )
        {
            ////////////////////////////////////////////////////////////////////////////////////////////

            LinedStateManager& stateMgr = ctrl->getAIGroupManager();
            CAIManager& aiMGr      = CAIManager::getInstance();
            CAIEntityGroupPathFindingMoveInAdvance* ai = aiMGr.createCAIEntityGroupPathFindingMoveInAdvance();
            ai->setDestination(pos);
	
            ////////////////////////////////////////////////////////////////////////////////////////////

			CAIController* aiController = NULL;

            std::map<GAMEOBJ_TYPE,OperationObjectList>::iterator iter = mGameObjectList.begin();
            for ( ; iter != mGameObjectList.end() ; iter++ )
            {
                GAMEOBJ_TYPE objType      = iter->first;
                OperationObjectList& list = iter->second;

                std::map<IdType, OperationObject>::iterator jter = list.objectList.begin();
                for ( ; jter != list.objectList.end() ; jter++ )
                {
                    IdType id               = jter->first;
                    OperationObject& opObj  = jter->second; 

					std::map<IdType, OperationEntity>::iterator kter = opObj.entityList.begin();
					for( ; kter != opObj.entityList.end() ;  kter++ )
					{ 
						if ( kter->second.sceneEntity )
						{
							characterSceneEntity = (CCharacterSceneEntity*)kter->second.sceneEntity;
							if(!characterSceneEntity->getIsCanMove())
							{
								continue;
							}

							//if(objType == GOT_SOLDIER)
							//{
							//	ai->addSceneEntity( characterSceneEntity, id );
							//}
							//else
							//{
								ai->addSceneEntity( characterSceneEntity );

								aiController = ((CCharacterSceneEntity*)kter->second.sceneEntity)->getAIController();
								if(aiController)
								{
									aiController->setIsPause(true);
								}
							//}
							
						}
					}
                }
            }

            ////////////////////////////////////////////////////////////////////////////////////////////
            

            /// 会移除上次的组AI
            /// TODO: 之后如果加上组聚拢的功能AI在组AI中，则需要保留上次的组AI
            stateMgr.push( ai );
            
        }
    }

	 //--------------------------------------------------------------------------
	void OperationObjectGroup::clearState()
	{
		//if(mState == GOS_SKILL_USE)
		//{
			mState = GOS_NORMAL;
		//}
	}

	//--------------------------------------------------------------------------
	OperationObjectList* OperationObjectGroup::getFirstGameObj()
	{
		return &(mGameObjectList.begin()->second);
	}

    //--------------------------------------------------------------------------
	CSceneEntity* OperationObjectGroup::getFirstSceneEntity()
	{
		OperationObject* tempOperationObject = &(getFirstGameObj()->objectList.begin()->second);
		return tempOperationObject->entityList.begin()->second.sceneEntity;
	}

	 //--------------------------------------------------------------------------
	void OperationObjectGroup::pickItem( CItemEntity* itemEntity )
	{
		std::map<GAMEOBJ_TYPE,OperationObjectList>::iterator iter = mGameObjectList.begin();
		for ( ; iter != mGameObjectList.end() ; iter++ )
		{
			GAMEOBJ_TYPE objType      = iter->first;
			OperationObjectList& list = iter->second;

			std::map<IdType, OperationObject>::iterator jter = list.objectList.begin();
			for ( ; jter != list.objectList.end() ; jter++ )
			{
				IdType id               = jter->first;
				OperationObject& opObj  = jter->second; 

				std::map<IdType, OperationEntity>::iterator kter = opObj.entityList.begin();
				for( ; kter != opObj.entityList.end() ;  kter++ )
				{
					if ( kter->second.sceneEntity && !((CPlayerCharacterEntity*)kter->second.sceneEntity)->getDynamicData()->isDied )
					{
						if ( objType == GOT_PLAYERCHARACTER )
						{
							ItemEntityData* itemData = itemEntity->getDynamicData();
							ItemPacketProcesser::getInstance().sendPickItem(itemData->mId, kter->second.sceneEntity->getID(), itemData->mItemTemplateId,itemData->mItemNum);
							return;
						}
					}
				}
			}
		}

	}
	
    



}