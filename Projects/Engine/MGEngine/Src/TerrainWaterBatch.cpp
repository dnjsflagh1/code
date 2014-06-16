/******************************************************************************/
#include "stdafx.h"
#include "TerrainWaterBatch.h"
#include "TerrainBatch.h"
#include "TerrainChunk.h"
#include "EngineMain.h"
#include "Scene.h"
#include "TerrainTiles.h"
#include "MGSceneNode.h"
#include "MGEngineUtility.h"
#include "Display.h"
#include "TerrainWaterMaterial.h"
#include "LightingMapMaker.h"

/******************************************************************************/

namespace MG
{

    //------------------------------------------------------------------------
    TerrainWaterBatch::TerrainWaterBatch( Scene* scene, TerrainTileRender* tileRender, TerrainBatch* parent, 
        const AxisAlignedBox& aabb, Ogre::Rect vertexRectInTile, MovableObject* movableObject )
        :TerrainBatch(scene,tileRender,parent,aabb,vertexRectInTile,movableObject)
        ,mMaterialGroupID(0)
    {
        mRenderEnable = false;
    }

    //------------------------------------------------------------------------
    TerrainWaterBatch::~TerrainWaterBatch()
    {
        unLoad();
    }


    //------------------------------------------------------------------------
    void TerrainWaterBatch::load()
    {
        TerrainBatch::load();
    }

    //------------------------------------------------------------------------
    void TerrainWaterBatch::unLoad()
    {
        TerrainBatch::unLoad();
    }

    //------------------------------------------------------------------------
    void TerrainWaterBatch::setMaterialGroupID( U32 id )
    {
        mMaterialGroupID = id;
        //TODO:

    }

    //------------------------------------------------------------------------
    MaterialPtr& TerrainWaterBatch::getOrGenerateMaterialPtr()
    {
        if ( mScene->getShadowManager()->getLightingMapMaker()->isActive() || mScene->getShadowManager()->getLightingMapMaker()->isTest() )
        {
            return mScene->getShadowManager()->getLightingMapMaker()->getTerrainMaterialPtr( TST_WATER );
        }

        return mSurfaceManager->getTerrainWaterMaterial()->getOrGenerateMaterialPtr( mMaterialGroupID, mTerrainChunk );
    }

}