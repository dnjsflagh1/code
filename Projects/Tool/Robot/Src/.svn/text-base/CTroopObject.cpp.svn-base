/******************************************************************************/
#include "stdafx.h"
#include "CTroopObject.h"
#include "CTroopSoldier.h"
#include "CPlayer.h"
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    CTroopObject::CTroopObject()
		: GameObject(GOT_TROOP,GQT_TROOP,NULL,0)
    {
		mCharacterDynaicData = MG_NEW CCharacterSceneEntityDynamicData;
        setGameObjectData( MG_NEW(TroopData) );
    }
    //-----------------------------------------------------------------------
    CTroopObject::~CTroopObject()
    {
        destroySoldierEntitys();
    }
    //-----------------------------------------------------------------------
    void CTroopObject::update(Flt delta)
    {
        updateSoldierEntitys( delta );
    }
    //-----------------------------------------------------------------------
    TroopData* CTroopObject::getBaseData()
    {
        return (TroopData*)(GameObject::getGameObjectData());
    }
	//---------------------------------------------------------------------------------
	CCharacterSceneEntityDynamicData* CTroopObject::getDynamicData()
	{
		return mCharacterDynaicData;
	}
    //-----------------------------------------------------------------------
    CTroopSoldier* CTroopObject::createSoldierEntitys( UInt index , TroopSoldierData* data, CCharacterSceneEntityDynamicData* dynamicData )
    {
        CTroopSoldier* troopSoldierEntity = getSoldierEntitys(index);

        if ( troopSoldierEntity == NULL )
        {
                troopSoldierEntity = MG_NEW CTroopSoldier( this );
                mTroopSoldierEntityList[index] = troopSoldierEntity;

                // copy data
                *(troopSoldierEntity->getBaseData())    = *data;
                *(troopSoldierEntity->getDynamicData()) = *dynamicData;
				troopSoldierEntity->setPos(data->mPos);
        }

        return troopSoldierEntity;
    }
    //-----------------------------------------------------------------------
    CTroopSoldier* CTroopObject::getSoldierEntitys( UInt soldierId )
    {
        std::map<UInt, CTroopSoldier*>::iterator iter =   mTroopSoldierEntityList.find( soldierId );
        if ( iter != mTroopSoldierEntityList.end() )
        {
            return iter->second;
        }
        return NULL;
    }
	//-----------------------------------------------------------------------
	CTroopSoldier* CTroopObject::getSoldierEntitysByIndex( UInt index )
	{
		UInt soldierIndex = 0;
		
		for(std::map<UInt, CTroopSoldier*>::iterator iter = mTroopSoldierEntityList.begin(); iter != mTroopSoldierEntityList.end(); ++iter)
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
        std::map<UInt, CTroopSoldier*>::iterator iter =  mTroopSoldierEntityList.find( soldierId );
        if ( iter != mTroopSoldierEntityList.end() )
        {
            MG_SAFE_DELETE( iter->second );
            mTroopSoldierEntityList.erase( iter );
        }
    }
    //-----------------------------------------------------------------------
    void CTroopObject::destroySoldierEntitys()
    {
        std::map<UInt, CTroopSoldier*>::iterator iter =  mTroopSoldierEntityList.begin( );
        for ( ; iter != mTroopSoldierEntityList.end() ; iter++ )
        {
            MG_SAFE_DELETE( iter->second );
        }
        mTroopSoldierEntityList.clear();
    }
    
    //-----------------------------------------------------------------------
    void CTroopObject::updateSoldierEntitys(Flt delta)
    {
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

		for( std::map<UInt, CTroopSoldier*>::iterator troopSoldierObjectIt = mTroopSoldierEntityList.begin(); troopSoldierObjectIt != mTroopSoldierEntityList.end(); ++troopSoldierObjectIt )
		{
			pos = troopSoldierObjectIt->second->getPos();
			if(troopSoldierObjectIt == mTroopSoldierEntityList.begin())
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
			}

		}

		return Vec3((minX + maxX) / 2, 0, (minZ + maxZ) / 2);
	}
    //-----------------------------------------------------------------------
    void CTroopObject::initialize()
    {   
        
    }

}