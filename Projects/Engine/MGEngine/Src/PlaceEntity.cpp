/******************************************************************************/
#include "stdafx.h"
#include "PlaceEntity.h"
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
    PlaceEntity::PlaceEntity(CChar* entityName, ModelDeclaration* modelDeclaration, Scene* scene)
    {
        setName(entityName);
        mOgreEntityWrapper = MG_NEW OgreEntityWrapper(this,entityName,modelDeclaration,scene);
    }
    //-----------------------------------------------------------------------
    PlaceEntity::~PlaceEntity()
    {
        MG_SAFE_DELETE(mOgreEntityWrapper);
    }
    //-----------------------------------------------------------------------
    SceneObjectTypes PlaceEntity::getType()
    {
        return SOT_PLACEENTITY;
    }
    //-----------------------------------------------------------------------
    ISceneNode* PlaceEntity::getSceneNode()
    {
        return mOgreEntityWrapper->getSceneNode();
    }
    //-----------------------------------------------------------------------
    OgreEntityWrapper* PlaceEntity::getModelObject()
    {
        return mOgreEntityWrapper;
    }
    //-----------------------------------------------------------------------
    void PlaceEntity::update( Flt delta )
    {
        if ( mOgreEntityWrapper )
        {
            mOgreEntityWrapper->update( delta ); 
        }
    }   
}

