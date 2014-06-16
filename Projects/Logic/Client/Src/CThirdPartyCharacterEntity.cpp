/******************************************************************************/
#include "stdafx.h"
#include "CThirdPartyCharacterEntity.h"
#include "ClientMain.h"
#include "CSceneManager.h"
#include "CPlayer.h"
#include "SkillNetPacketProcesser.h"
#include "BuildingData.h"
/******************************************************************************/
namespace MG
{

    //-----------------------------------------------------------------------
    CThirdPartyCharacterEntity::CThirdPartyCharacterEntity(IEntity* entity)
        :CCharacterSceneEntity(entity,GOT_THIRDPARTYCHARACTER,GQT_THIRDPARTYCHARACTER,(MG_NEW ThirdPartyCharacterEntityData))
    {
    }

    //-----------------------------------------------------------------------
    CThirdPartyCharacterEntity::~CThirdPartyCharacterEntity()
    {
		unInitialize();
    }

    //-----------------------------------------------------------------------
    void CThirdPartyCharacterEntity::initialize()
    {
		CCharacterSceneEntity::initialize();
    }

    //-----------------------------------------------------------------------
    void CThirdPartyCharacterEntity::unInitialize()
    {
		CCharacterSceneEntity::unInitialize();
    }

    //-----------------------------------------------------------------------
	ThirdPartyCharacterEntityData* CThirdPartyCharacterEntity::getDynamicData()
	{
		return dynamic_cast<ThirdPartyCharacterEntityData*>(getGameObjectData());
	}

}