/******************************************************************************/
#include "stdafx.h"
#include "CTroopObject.h"
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
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    CTroopObject::CTroopObject( IEntityGroup* entityGroup )
		:CSceneEntity(NULL, GOT_TROOP, GQT_TROOP, (MG_NEW CCharacterSceneEntityDynamicData))
        ,mEntityGroup(entityGroup)
		,mFlagEntity(NULL)
		,mFightManager(NULL)
		,mFightAIGroup(NULL)
    {
        setGameObjectData( MG_NEW(TroopData) );
    }

    //-----------------------------------------------------------------------
    CTroopObject::~CTroopObject()
    {
    }

    //-----------------------------------------------------------------------
    void CTroopObject::initialize()
    {
        if ( mTroopSoldierEntityList.size() <= 0 )
            return;

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

        CSceneEntity::initialize();

        //////////////////////////////////////////////////////////////////////

        //计算属性。
        if ( CPlayer::getInstance().getAccountID() == getDynamicData()->belongPlayerID )
        {
            const CharacterTempInfo* pInfo =  CharacterTemplate::getInstance().getCharacterTempInfo(getBaseData()->mCharacterTemplateID);
            DYNAMIC_ASSERT(pInfo);
            mCAttributeSystem.calBaseAttr(pInfo);

            mCAttributeSystem.calFinalAttr(pInfo->getCharacterFormulaType());
			mFightAIGroup = FightAIGroupTemplate::getInstance().getFightAIGroup(pInfo->getAIFightGroupId());
        }

		//mFightManager = new FightManager(getType(), getID());

        createFlag(/*40033*/181005);
    }

    //-----------------------------------------------------------------------
    void CTroopObject::unInitialize()
    {
        destroySoldierEntitys();

        if(mEntityGroup)
        {
            ClientMain::getInstance().getScene()->destroyEntityGroup(mEntityGroup->getName().c_str());
            mEntityGroup = NULL;
        }

        destroyFlag();

		MG_SAFE_DELETE(mFightManager);
    }
    
    //-----------------------------------------------------------------------
    void CTroopObject::update(Flt delta)
    {
        CSceneEntity::update(delta);

        updateSoldierEntitys( delta );

		if(mFlagEntity)
		{
			Vec3 centerPos = getTroopCenterPos();
			mFlagEntity->getSceneNode()->setPosition(centerPos);
			mFlagEntity->getSceneNode()->stickTerrain();
		}
    }

    //-----------------------------------------------------------------------
    TroopData* CTroopObject::getBaseData()
    {
        return (TroopData*)(GameObject::getGameObjectData());
    }

	//---------------------------------------------------------------------------------
	CCharacterSceneEntityDynamicData* CTroopObject::getDynamicData()
	{
		return (CCharacterSceneEntityDynamicData*)(CSceneObject::getDynamicData());
	}

	//-----------------------------------------------------------------------
	Bool CTroopObject::getWorldPos( Vec3& worldPos )
	{
		worldPos = getTroopCenterPos();

		return true;
	}

	//-----------------------------------------------------------------------
	Bool CTroopObject::isInScreen()
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
    CTroopSoldierEntity* CTroopObject::createSoldierEntitys( UInt index , TroopSoldierData* data, CCharacterSceneEntityDynamicData* dynamicData )
    {
        CTroopSoldierEntity* troopSoldierEntity = getSoldierEntitys(index);
		IDynamicBlockObject* dynamicBlockObject = NULL;

        if ( troopSoldierEntity == NULL )
        {
            IEntity* entity = mEntityGroup->getEntity( index );
            if ( entity )
            {
                troopSoldierEntity = MG_NEW CTroopSoldierEntity( this, entity );
                mTroopSoldierEntityList[index] = troopSoldierEntity;

                troopSoldierEntity->initialize();

                // copy data
                *(troopSoldierEntity->getBaseData())    = *data;
                *(troopSoldierEntity->getDynamicData()) = *dynamicData;

				troopSoldierEntity->getEntity()->getSceneNode()->setVisible(true);
				troopSoldierEntity->setPos(data->mPos);
				troopSoldierEntity->getEntity()->getSceneNode()->stickTerrain();
                
                dynamicBlockObject = troopSoldierEntity->getEntity()->createOrRetrieveDynamicBlockObject();
				if(dynamicBlockObject)
				{
					dynamicBlockObject->setStructureMode(false);

                    if ( troopSoldierEntity->getDynamicData()->force == FORCE_INIT )
                    {
                        dynamicBlockObject->setEnable( false );
                    }else
                    {
					    dynamicBlockObject->setEnable(true);
                    }
				}

				Color color = CSceneManager::getInstance().getTroopSoldierColor(dynamicData->force, dynamicData->belongPlayerID);
				entity->getModelObject()->setEmissive(color);
            }
        }

        return troopSoldierEntity;
    }

    //-----------------------------------------------------------------------
    CTroopSoldierEntity* CTroopObject::getSoldierEntitys( ISceneObject* sceneObj )
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
    CTroopSoldierEntity* CTroopObject::getSoldierEntitys( UInt soldierId )
    {
        std::map<UInt, CTroopSoldierEntity*>::iterator iter =   mTroopSoldierEntityList.find( soldierId );
        if ( iter != mTroopSoldierEntityList.end() )
        {
            return iter->second;
        }
        return NULL;
    }

	//-----------------------------------------------------------------------
	CTroopSoldierEntity* CTroopObject::getSoldierEntitysByIndex( UInt index )
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
    void CTroopObject::destroySoldierEntitys( UInt soldierId )
    {
        std::map<UInt, CTroopSoldierEntity*>::iterator iter =  mTroopSoldierEntityList.find( soldierId );
        if ( iter != mTroopSoldierEntityList.end() )
        {
            iter->second->unInitialize();
            MG_SAFE_DELETE( iter->second );
            mTroopSoldierEntityList.erase( iter );
        }
    }

    //-----------------------------------------------------------------------
    void CTroopObject::destroySoldierEntitys()
    {
        std::map<UInt, CTroopSoldierEntity*>::iterator iter =  mTroopSoldierEntityList.begin( );
        for ( ; iter != mTroopSoldierEntityList.end() ; iter++ )
        {
            iter->second->unInitialize();
            MG_SAFE_DELETE( iter->second );
        }
        mTroopSoldierEntityList.clear();
    }
    
    //-----------------------------------------------------------------------
    void CTroopObject::updateSoldierEntitys(Flt delta)
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
                iter->second->unInitialize();
				MG_SAFE_DELETE( iter->second );
				iter = mTroopSoldierEntityList.erase(iter);
				continue;
			}

            iter->second->update(delta);
			++iter;
        }
    }

	//-----------------------------------------------------------------------
	UInt CTroopObject::getSoldierEntitysNum()
	{
		return mTroopSoldierEntityList.size();
	}

    //-----------------------------------------------------------------------
	Vec3 CTroopObject::getTroopCenterPos()
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
	void CTroopObject::createFlag(UInt flgModleId)
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
            mFlagEntity->getAnimationController()->setIsIdle(true, "work001");
        }
	}

	//-----------------------------------------------------------------------
	void CTroopObject::destroyFlag()
	{
		if( mFlagEntity )
		{
		    CSceneManager::getInstance().getEngineScene()->destroyEntity(mFlagEntity->getName().c_str());
            mFlagEntity = NULL;
		}
	}

	//-----------------------------------------------------------------------
	FightManager* CTroopObject::getFightManager()
	{
		return mFightManager;
	}

	//-----------------------------------------------------------------------
	CTroopSoldierEntity* CTroopObject::getSoldierEntitysForMinDis( Vec3 pos )
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
	const FightAIGroup*	CTroopObject::getFightAIGroup()
	{
		return mFightAIGroup;
	}

	//-----------------------------------------------------------------------
	void CTroopObject::addFightAITriggerCount( UInt fightAIId )
	{
		mFightAITriggerCountList[fightAIId]++;
	}

	//-----------------------------------------------------------------------
	UInt CTroopObject::getFightAITriggerCount( UInt fightAIId )
	{
		std::map<UInt, UInt>::iterator it = mFightAITriggerCountList.find(fightAIId);
		if(it == mFightAITriggerCountList.end())
		{
			return 0;
		}

		return it->second;
	}

	//-----------------------------------------------------------------------
	void CTroopObject::clearFightAITriggerCount()
	{
		mFightAITriggerCountList.clear();
	}

}