/******************************************************************************/
#include "stdafx.h"
#include "TerrainGroundBatch.h"
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
    TerrainGroundBatch::TerrainGroundBatch( Scene* scene, TerrainTileRender* tileRender, TerrainBatch* parent, 
        const AxisAlignedBox& aabb, Ogre::Rect vertexRectInTile, MovableObject* movableObject )
        :TerrainBatch(scene,tileRender,parent,aabb,vertexRectInTile,movableObject)
    {
        mRenderEnable = true;
    }

    //------------------------------------------------------------------------
    TerrainGroundBatch::~TerrainGroundBatch()
    {
        unLoad();
    }


    //------------------------------------------------------------------------
    void TerrainGroundBatch::load()
    {
        TerrainBatch::load();
    }

    //------------------------------------------------------------------------
    void TerrainGroundBatch::unLoad()
    {
        TerrainBatch::unLoad();
    }

    //------------------------------------------------------------------------
    MaterialPtr& TerrainGroundBatch::getOrGenerateMaterialPtr()
    {
		TerrainGroundTileRender* tileRender = (TerrainGroundTileRender*)mTileRender;
		// ÕÛÉä²ÄÖÊ
		if ( OgreMainInterface::root->getRenderSystem()->_getViewport()->getUsage() == 2 )
		{
			tileRender->setMtlType(TerrainGroundTileRender::MTL_REFRACT);
			return tileRender->getOrGenerateMaterialPtr();
		}

        if ( mScene->getShadowManager()->getLightingMapMaker()->isActive() || mScene->getShadowManager()->getLightingMapMaker()->isTest() )
        {
            return mScene->getShadowManager()->getLightingMapMaker()->getTerrainMaterialPtr( TST_GROUND );
        }

		tileRender->setMtlType(TerrainGroundTileRender::MTL_NORMAL);
        return tileRender->getOrGenerateMaterialPtr();
    }

}