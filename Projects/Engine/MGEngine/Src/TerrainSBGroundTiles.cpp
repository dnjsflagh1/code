/******************************************************************************/
#include "stdafx.h"

#include "TerrainSBGroundTiles.h"
#include "TerrainGroundBatch.h"
#include "TerrainSBGroundBatch.h"
#include "TerrainGroundTiles.h"
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
#include "TerrainBatch.h"
#include "TerrainWaterMaterial.h"
#include "OgreDefaultHardwareBufferManager.h"
#include "TerrainNode.h"

/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    TerrainSBGroundTileRender::TerrainSBGroundTileRender( TerrainManager* mgr, TerrainChunk* chunk, 
            TerrainNode* node, TerrainTile* tile, UInt index )
        :TerrainGroundTileRender(mgr,chunk, node, tile,index)
    {
        // ²ÄÖÊÉú³ÉÆ÷
        mBaseMaterialGenerator = TerrainTilesGlobalOptions::getInstance().getDefaultMaterialGenerator( TMS_SMALL );
    }
    
    //-----------------------------------------------------------------------
    TerrainSBGroundTileRender::~TerrainSBGroundTileRender()
    {
        unLoadRenderData();
        unLoadTextureLayerResource();
    }

    //-----------------------------------------------------------------------
    UInt TerrainSBGroundTileRender::getMaxTextureLayerCount()
    {
        return 3;
    }

    //-----------------------------------------------------------------------
    TerrainBatch*   TerrainSBGroundTileRender::createTerrainBatch( Scene* scene, TerrainTileRender* tileRender, TerrainBatch* parent, 
        const AxisAlignedBox& aabb, Ogre::Rect vertexRectInTile, MovableObject* movableObject)
    {
        return MG_NEW TerrainSBGroundBatch( scene, tileRender, parent, aabb, vertexRectInTile, movableObject);
    }

    //**********************************************************************************************************************
    //**********************************************************************************************************************

    //-----------------------------------------------------------------------
    void TerrainSBGroundTileRender::generateTextureLayerResource()
    {
        generateTextureList();

        generateUVMultipliers();

        generateBlendTextureList();

        generateTextureBlendLayerList();

        applyRenderConfig();
    }

    //-----------------------------------------------------------------------
    void TerrainSBGroundTileRender::generateTextureLayerResource(Int layerIndex)
    {
        TextureLayerInstance* instance = getTextureLayer( layerIndex );

        generateTextureList( instance );

        generateUVMultipliers();

        generateBlendTextureList();

        generateTextureBlendLayerList();

        applyRenderConfig();
    }

    //-----------------------------------------------------------------------
    void TerrainSBGroundTileRender::unLoadTextureLayerResource()
    {
        freeMaterial();

        destroyTextureList();
        destroyAllBlendTexture();
        destroyAllTextureBlendLayer();

        clearTextureLayer();
    }

    //**********************************************************************************************************************
    //**********************************************************************************************************************


    //-----------------------------------------------------------------------
    void TerrainSBGroundTileRender::generateTextureList()
    {
        TerrainSurfaceManager* surfaceMgr =  mTerrainMgr->getTerrainSurfaceManager();

        TextureLayerInstanceList::iterator iter = mColorTextureDeclLayers.begin();
        for ( ; iter!=mColorTextureDeclLayers.end(); iter++ )
        {
            TextureLayerInstance& instance = (*iter);

            generateTextureList( &instance );
        }
    }

    //-----------------------------------------------------------------------
    void TerrainSBGroundTileRender::generateTextureList(TextureLayerInstance* instance)
    {
        TerrainSurfaceManager* surfaceMgr =  mTerrainMgr->getTerrainSurfaceManager();

        if ( instance )
        {
            TerrainTextureLayerDeclaration* decl = surfaceMgr->getGlobleTextureLayer( instance->globleIndex );

            if ( decl == false )
            {
                instance->globleIndex = 0;
                decl = surfaceMgr->getGlobleTextureLayer( instance->globleIndex );
            }

            if ( decl )
            {
                instance->worldSize             = decl->worldSize;
                instance->hasDiffuseSpecular    = decl->hasDiffuseSpecular;
                instance->hasNormalHeight       = decl->hasNormalHeight;

                if ( instance->hasDiffuseSpecular )
                {
                    instance->diffuseSpecularTextureIndex = instance->layerIndex;
                    //instance->diffuseSpecularUVPos;
                    //instance->diffuseSpecularUVSize;
                    mDiffuseTextureNameMap[instance->layerIndex] = decl->diffuseSpecularFileName;
                }
                if ( instance->hasNormalHeight )
                {
                    instance->normalHeightTextureIndex = instance->layerIndex;
                    //instance->normalHeightUVPos;
                    //instance->normalHeightUVSize;
                    mNormalTextureNameMap[instance->layerIndex] = decl->normalHeightFileName;
                }
            }else
            {
                DYNAMIC_ASSERT( false );
            }
        }
    }

    //-----------------------------------------------------------------------
    void TerrainSBGroundTileRender::destroyTextureList()
    {
        mDiffuseTextureNameMap.clear();
        mNormalTextureNameMap.clear();

        mDiffuseTextureNameList.clear();
        mNormalTextureNameList.clear();
    }

    //-----------------------------------------------------------------------
    const StringVector& TerrainSBGroundTileRender::getValidDiffuseSpecularTextureNameList()
    {
        mDiffuseTextureNameList.clear();

        std::map<UInt,Str>::iterator iter = mDiffuseTextureNameMap.begin();
        for ( ; iter != mDiffuseTextureNameMap.end(); iter++ )
        {
            mDiffuseTextureNameList.push_back( iter->second );
        }

        return mDiffuseTextureNameList; 
    }

    //-----------------------------------------------------------------------
    const StringVector& TerrainSBGroundTileRender::getValidNormalHeightTextureNameList()
    {
        mNormalTextureNameList.clear();

        std::map<UInt,Str>::iterator iter = mNormalTextureNameMap.begin();
        for ( ; iter != mNormalTextureNameMap.end(); iter++ )
        {
            mNormalTextureNameList.push_back( iter->second );
        }

        return mNormalTextureNameList; 
    }

    //**********************************************************************************************************************
    //**********************************************************************************************************************


    //---------------------------------------------------------------------
    void TerrainSBGroundTileRender::applyRenderConfig()
    {
        TerrainGroundTileRender::applyRenderConfig();

        /////////////////////////////////////////////////////////
    }
}

