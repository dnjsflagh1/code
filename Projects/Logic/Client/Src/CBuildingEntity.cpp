/******************************************************************************/
#include "stdafx.h"
#include "CBuildingEntity.h"
#include "ClientMain.h"
#include "CSceneManager.h"
#include "CPlayer.h"
#include "SkillNetPacketProcesser.h"
#include "BuildingData.h"
#include "CharacterList.h"
/******************************************************************************/
namespace MG
{

    //-----------------------------------------------------------------------
	CBuildingEntity::CBuildingEntity(IEntity* entity)
        :CCharacterSceneEntity(entity,GOT_BUILDING,GQT_BUILDING,(MG_NEW BuildingEntityData))
    {
    }

    //-----------------------------------------------------------------------
    CBuildingEntity::~CBuildingEntity()
    {
		unInitialize();
    }

    //-----------------------------------------------------------------------
    void CBuildingEntity::initialize()
    {
        CCharacterSceneEntity::initialize();
    }

    //-----------------------------------------------------------------------
    void CBuildingEntity::unInitialize()
    {
        CCharacterSceneEntity::unInitialize();

    }
	//-----------------------------------------------------------------------
	Bool CBuildingEntity::isWall()
	{
		CHAR_BUILD_TYPE buildType = getCharacterTempInfo()->getBuildType();
		switch(buildType)
		{
		case CHAR_BUILD_TYPE_WALL:
		case CHAR_BUILD_TYPE_CORNER:
		case CHAR_BUILD_TYPE_BAR:
		case CHAR_BUILD_TYPE_TURRET:
			return true;
		}

		return false;
	}
	//-----------------------------------------------------------------------
	BuildingEntityData* CBuildingEntity::getDynamicData()
	{
		return dynamic_cast<BuildingEntityData*>(getGameObjectData());
	}
	//-----------------------------------------------------------------------
	MG::CHAR_BUILD_TYPE CBuildingEntity::getBuildingType()
	{
		return getCharacterTempInfo()->getBuildType();
	}
}