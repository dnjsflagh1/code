/******************************************************************************/
#include "stdafx.h"
#include "CTroopSoldier.h"
//#include "ClientMain.h"
//#include "CSceneManager.h"
//#include "HeadDes.h"
//#include "HeadDesManage.h"
//#include "CPlayer.h"
//#include "SkillNetPacketProcesser.h"
//#include "BattleBuildingData.h"
/******************************************************************************/
namespace MG
{

    //-----------------------------------------------------------------------
    CTroopSoldier::CTroopSoldier(CTroopObject* owner)
		:GameObject(GOT_SOLDIER,GQT_SOLDIER,NULL,0)
 		,mTroopEntity(owner)
    {
        setGameObjectData( MG_NEW(TroopSoldierData) );
		mCharacterDynamicData = MG_NEW CCharacterSceneEntityDynamicData;
    }

    //-----------------------------------------------------------------------
    CTroopSoldier::~CTroopSoldier()
    {

    }

    //-----------------------------------------------------------------------
    void CTroopSoldier::initialize()
    {
        //CCharacterSceneEntity::initialize();
    }

    //-----------------------------------------------------------------------
    void CTroopSoldier::unInitialize()
    {

    }

    //-----------------------------------------------------------------------
    TroopSoldierData* CTroopSoldier::getBaseData()
    {
        return (TroopSoldierData*)( GameObject::getGameObjectData() );
    }



}