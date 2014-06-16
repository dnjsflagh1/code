/******************************************************************************/
#include "stdafx.h"
#include "CItemEntity.h"
#include "CSceneManager.h"
#include "ItemData.h"
#include "CCharacterSceneEntity.h"
#include "IActionManager.h"
#include "ClientMain.h"
#include "ICollisionSystem.h"
/******************************************************************************/
namespace MG
{

	//-----------------------------------------------------------------------
	CItemEntity::CItemEntity( IEntity* entity )
		:CNoCharacterSceneEntity(entity,GOT_ITEM,GQT_ITEM,(MG_NEW ItemEntityData))
	{
	}

	//-----------------------------------------------------------------------
	CItemEntity::~CItemEntity()
	{

	}

	//-----------------------------------------------------------------------
	void CItemEntity::initialize()
	{
		CNoCharacterSceneEntity::initialize();  
	}

	//-----------------------------------------------------------------------
	void CItemEntity::unInitialize()
	{
		CNoCharacterSceneEntity::unInitialize();  
	}
	//-----------------------------------------------------------------------
	void CItemEntity::parabolaDrop( Vec3 dropStartPos )
	{
		Flt height = 0;
		ClientMain::getInstance().getScene()->getCollisionSystem()->getStickHeight(dropStartPos, height);
		dropStartPos.y = height;

		Vec3 dir(1,0,0);
		Int angle = MGRandom::getInstance().rand_ab_One(0, 360);
		dir = MGMath::rotateVector(dir, angle * (MG_PI / 180));
		Int dis = MGRandom::getInstance().rand_ab_One(1, 3);
		Vec3 dropEndPos = dropStartPos + dir * dis;

		ISceneNode* sceneNode = mEntity->getSceneNode();

		ISceneNodeLineMoveToAction* lineMoveToAction = sceneNode->getScene()->getActionManager()->createSceneNodeParabolaMoveToAction(sceneNode);
		lineMoveToAction->setMoveSpeed(1);
		lineMoveToAction->setIgnoreHeight(false);
		lineMoveToAction->setStickTerrain(false);
		lineMoveToAction->setMoveToDestination(dropEndPos);
		sceneNode->getLinedStateManager()->push(lineMoveToAction);
	}
	//-----------------------------------------------------------------------
	ItemEntityData* CItemEntity::getDynamicData()
	{
		return dynamic_cast<ItemEntityData*>(getGameObjectData());
	}

}