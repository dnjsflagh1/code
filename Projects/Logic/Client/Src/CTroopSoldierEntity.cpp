/******************************************************************************/
#include "stdafx.h"
#include "CTroopSoldierEntity.h"
#include "ClientMain.h"
#include "CSceneManager.h"
#include "CPlayer.h"
#include "SkillNetPacketProcesser.h"
#include "BuildingData.h"
/******************************************************************************/
namespace MG
{

    //-----------------------------------------------------------------------
    CTroopSoldierEntity::CTroopSoldierEntity(CTroopEntity* owner,IEntity* entity)
        :CCharacterSceneEntity(entity,GOT_SOLDIER,GQT_SOLDIER,(MG_NEW TroopSoldierEntityData))
        ,mTroopEntity(owner)
		,mTargetType(GOT_UNKNOWN)
		,mTargetId(0)
		,mTargetIndex(0)
    {
    }

    //-----------------------------------------------------------------------
    CTroopSoldierEntity::~CTroopSoldierEntity()
    {
        unInitialize();
    }

    //-----------------------------------------------------------------------
    void CTroopSoldierEntity::initialize()
    {
        CCharacterSceneEntity::initialize();
    }

    //-----------------------------------------------------------------------
    void CTroopSoldierEntity::unInitialize()
    {
		getActionStateManager().clear();
		getAIStateManager().clear();

        if ( mEntity )
        {
            mEntity->getSceneNode()->setVisible(false);
            mEntity = NULL;
        }

        CCharacterSceneEntity::unInitialize();
    }
	//-----------------------------------------------------------------------
	Bool CTroopSoldierEntity::isBattleState()
	{
		TroopSoldierEntityData* data = getDynamicData();
		if ( data )
			return data->isFightState;

		return false;
	}

	//-----------------------------------------------------------------------
	void CTroopSoldierEntity::setTarget(GAMEOBJ_TYPE gameType, GameObjectIdType id, UInt index)
	{
		mTargetType = gameType;
		mTargetId = id;
		mTargetIndex = index;
	}

	//-----------------------------------------------------------------------
	void CTroopSoldierEntity::getTarget( GAMEOBJ_TYPE& gameType, GameObjectIdType& id, UInt& index )
	{
		gameType = mTargetType;
		id = mTargetId;
		index =mTargetIndex;
	}
	//-----------------------------------------------------------------------
	TroopSoldierEntityData* CTroopSoldierEntity::getDynamicData()
	{
		return dynamic_cast<TroopSoldierEntityData*>(getGameObjectData());
	}
}