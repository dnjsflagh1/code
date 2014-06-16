/******************************************************************************/
#include "stdafx.h"
#include "NoCharacterSceneEntity.h"
#include "ClientMain.h"
/******************************************************************************/
namespace MG
{
    //--------------------------------------------------------------------------------
    CNoCharacterSceneEntity::CNoCharacterSceneEntity(IEntity* entity, GAMEOBJ_TYPE type, GAMEOBJ_QUERY_TYPE queryType, NoCharacterEntityData* dynamicData)
        :CSceneEntity(entity,type,queryType,dynamicData)
    {

    }
    //--------------------------------------------------------------------------------
    CNoCharacterSceneEntity::~CNoCharacterSceneEntity()
    {

    }
    //--------------------------------------------------------------------------------
    void CNoCharacterSceneEntity::initialize()
    {
        CSceneEntity::initialize();
    }
    //---------------------------------------------------------------------------------------
    void CNoCharacterSceneEntity::unInitialize()
    {
        CSceneEntity::unInitialize();
    }

	//---------------------------------------------------------------------------------------
	void CNoCharacterSceneEntity::setPos(Vec3 pos)
	{
		mEntity->getSceneNode()->setPosition(pos);
	}

	//---------------------------------------------------------------------------------------
	void CNoCharacterSceneEntity::setDir(Vec3 dir)
	{
		mEntity->getSceneNode()->setDirection(dir);
	}

	//---------------------------------------------------------------------------------------
	Vec3 CNoCharacterSceneEntity::getPos(Bool isIgnoreHeight)
	{
		Vec3 pos;
		mEntity->getSceneNode()->getPosition(pos);
		if(isIgnoreHeight)
		{
			pos.y = 0;
		}

		return pos;
	}

	//---------------------------------------------------------------------------------------
	Vec3 CNoCharacterSceneEntity::getDir()
	{
		Vec3 dir;
		mEntity->getSceneNode()->getDirection(dir);

		return dir;
	}
	//---------------------------------------------------------------------------------------
	NoCharacterEntityData* CNoCharacterSceneEntity::getDynamicData()
	{
		return dynamic_cast<NoCharacterEntityData*>(getGameObjectData());
	}
}