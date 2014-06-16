/******************************************************************************/
#include "stdafx.h"
#include "TerrainSBGroundBatch.h"
#include "TerrainBatch.h"
#include "TerrainChunk.h"
#include "EngineMain.h"
#include "Scene.h"
#include "TerrainTiles.h"
#include "TerrainTilesGpu.h"
#include "TerrainTilesLayerBlendMap.h"
#include "TerrainTilesMaterial.h"
#include "TerrainTilesMaterialA.h"
#include "TerrainTilesOptions.h"
#include "MGSceneNode.h"
#include "MGEngineUtility.h"
#include "Display.h"
#include "LightingMapMaker.h"
#include "TerrainGroundTiles.h"

/*****************************************************************************/

namespace MG
{

    //------------------------------------------------------------------------
    TerrainSBGroundBatch::TerrainSBGroundBatch( Scene* scene, TerrainTileRender* tileRender, TerrainBatch* parent, 
        const AxisAlignedBox& aabb, Ogre::Rect vertexRectInTile, MovableObject* movableObject )
        :TerrainGroundBatch(scene,tileRender,parent,aabb,vertexRectInTile,movableObject)
    {
        mRenderEnable = true;

        mPosition = mBoundingBox.getCenter();
    }

    //------------------------------------------------------------------------
    TerrainSBGroundBatch::~TerrainSBGroundBatch()
    {
        unLoad();
    }

    //------------------------------------------------------------------------
    MaterialPtr& TerrainSBGroundBatch::getOrGenerateMaterialPtr()
    {
        if ( mScene->getShadowManager()->getLightingMapMaker()->isActive() || mScene->getShadowManager()->getLightingMapMaker()->isTest() )
        {
            return mScene->getShadowManager()->getLightingMapMaker()->getTerrainMaterialPtr( TST_GROUND );
        }

        TerrainGroundTileRender* tileRender = (TerrainGroundTileRender*)mTileRender;
        return tileRender->getOrGenerateMaterialPtr();
    }

    //------------------------------------------------------------------------
    Bool TerrainSBGroundBatch::isValidRenderableDistance(Ogre::Camera* cam)
    {
        const Vector3& camPos = cam->getPosition();
        Flt dis = mPosition.squaredDistance(camPos);

        if ( dis > 10000 )
            return false;

        return true;
    }

}