/******************************************************************************/
#include "stdafx.h"
#include "COrdinaryBuildingEntity.h"
#include "CSceneManager.h"
#include "OrdinaryBuildingData.h"
#include "CCharacterSceneEntity.h"
/******************************************************************************/
namespace MG
{

    //-----------------------------------------------------------------------
    COrdinaryBuildingEntity::COrdinaryBuildingEntity( IEntity* entity )
        :CNoCharacterSceneEntity(entity,GOT_ORDINARY_BUILDING,GQT_ORDINARY_BUILDING,(MG_NEW OrdinaryBuildingEntityData))
    {
    }

    //-----------------------------------------------------------------------
    COrdinaryBuildingEntity::~COrdinaryBuildingEntity()
    {

    }

    //-----------------------------------------------------------------------
    void COrdinaryBuildingEntity::initialize()
    {
        CNoCharacterSceneEntity::initialize();  
    }

    //-----------------------------------------------------------------------
    void COrdinaryBuildingEntity::unInitialize()
    {
        CNoCharacterSceneEntity::unInitialize();  
    }

    //-----------------------------------------------------------------------
	OrdinaryBuildingEntityData* COrdinaryBuildingEntity::getDynamicData()
	{
		return dynamic_cast<OrdinaryBuildingEntityData*>(getGameObjectData());
	}

}