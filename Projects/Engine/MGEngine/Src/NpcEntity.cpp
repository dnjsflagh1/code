/******************************************************************************/
#include "stdafx.h"
#include "NpcEntity.h"
#include "EngineMain.h"
#include "MGSceneNode.h"
#include "Scene.h"
#include "ISceneObject.h"
#include "ResourceManager.h"
#include "MeterialEffectSystem.h"
#include "OgreEntityWrapper.h"
/******************************************************************************/

namespace MG
{
    //-----------------------------------------------------------------------
    NpcEntity::NpcEntity(CChar* entityName, ModelDeclaration* modelDeclaration, Scene* scene)
    {
        setName(entityName);
        mOgreEntityWrapper = MG_NEW OgreEntityWrapper(this,entityName,modelDeclaration,scene);

    }
    //-----------------------------------------------------------------------
    NpcEntity::~NpcEntity()
    {
        MG_SAFE_DELETE(mOgreEntityWrapper);
    }
    //-----------------------------------------------------------------------
    SceneObjectTypes NpcEntity::getType()
    {
        return SOT_NPCENTITY;
    }
    //-----------------------------------------------------------------------
    ISceneNode* NpcEntity::getSceneNode()
    {
        return mOgreEntityWrapper->getSceneNode();
    }
    //-----------------------------------------------------------------------
    OgreEntityWrapper* NpcEntity::getModelObject()
    {
        return mOgreEntityWrapper;
    }
    //-----------------------------------------------------------------------
    void NpcEntity::update( Flt delta )
    {
        if ( mOgreEntityWrapper )
        {
            mOgreEntityWrapper->update( delta ); 
        }
    }   
}

