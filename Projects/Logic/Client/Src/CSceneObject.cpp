/******************************************************************************/
#include "stdafx.h"
#include "CSceneObject.h"
#include "CActionManager.h"
#include "CharacterSceneEntityAction.h"
#include "CAIManager.h"
/******************************************************************************/
namespace MG
{
    CSceneObject::CSceneObject(GAMEOBJ_TYPE type,  GAMEOBJ_QUERY_TYPE queryType, SceneObjectData* dynamicData)
        :GameObject(type, queryType, dynamicData)
    {
        //setAIEnable( true );
    }

    //---------------------------------------------------------------------------------
    CSceneObject::~CSceneObject()
    {
        mLinedStateManagerForAction.clear();
        mLinedStateManagerForAI.clear();

        setAIEnable( false );
    }

    //---------------------------------------------------------------------------------
    void CSceneObject::update( Flt delta )
    {
        mLinedStateManagerForAction.update( delta );
    }

    //---------------------------------------------------------------------------------
    void CSceneObject::stopAllAction()
    {
        mLinedStateManagerForAction.clear();
    }

    //---------------------------------------------------------------------------------
    void CSceneObject::stopAllAI()
    {
        mLinedStateManagerForAI.clear();
    }

    //---------------------------------------------------------------------------------
    void CSceneObject::setAIEnable( Bool enable )
    {
        if ( enable )
        {
            CAIManager::getInstance().addUpdateAIMgr( &mLinedStateManagerForAI );
        }else
        {
            CAIManager::getInstance().removeUpdateAIMgr( &mLinedStateManagerForAI );
        }

        getDynamicData()->isAI = enable;
    }
	//---------------------------------------------------------------------------------
	SceneObjectData* CSceneObject::getDynamicData()
	{
		return dynamic_cast<SceneObjectData*>(getGameObjectData());
	}
}