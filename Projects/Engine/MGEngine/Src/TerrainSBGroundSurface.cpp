/******************************************************************************/
#include "stdafx.h"

#include "EngineMain.h"
#include "Scene.h"
#include "MGSceneNode.h"
#include "MGEngineUtility.h"
#include "Display.h"

#include "TerrainGroundSurface.h"
#include "TerrainSBGroundSurface.h"
#include "TerrainGroundTiles.h"
#include "TerrainSBGroundTiles.h"
#include "TerrainChunk.h"
#include "TerrainTiles.h"
#include "TerrainTilesGpu.h"
#include "TerrainTilesLayerBlendMap.h"
#include "TerrainTilesMaterial.h"
#include "TerrainTilesMaterialA.h"
#include "TerrainTilesOptions.h"

#include "OgreStreamSerialiser.h"
#include "OgreMath.h"
#include "OgreImage.h"
#include "OgrePixelFormat.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreException.h"
#include "OgreBitwise.h"
#include "OgreStringConverter.h"
#include "OgreViewport.h"
#include "OgreLogManager.h"
#include "OgreHardwarePixelBuffer.h"
#include "OgreTextureManager.h"
#include "OgreRoot.h"
#include "OgreRenderSystem.h"
#include "OgreRay.h"
#include "OgrePlane.h"
#include "OgreMaterialManager.h"
#include "OgreHardwareBufferManager.h"

/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    TerrainSBGroundSurface::TerrainSBGroundSurface(TerrainManager* terrainMgr, Scene* scene, TerrainChunk* chunk)
        : TerrainGroundSurface(terrainMgr,scene,chunk)
    {
    }   
    //-----------------------------------------------------------------------
    TerrainSBGroundSurface::~TerrainSBGroundSurface()
    {
        unLoad();
    }

    //-----------------------------------------------------------------------
    TerrainTileRender* TerrainSBGroundSurface::createTerrainTileRender( TerrainManager* mgr, TerrainChunk* chunk, 
        TerrainNode* node, TerrainTile* tile, UInt index )
    {
        return MG_NEW TerrainSBGroundTileRender( mgr, chunk, node, tile, index );
    }

    //---------------------------------------------------------------------
    void TerrainSBGroundSurface::loadBlendTextures( Str& path )
    {
        destroyAllBlendTexture();

        /////////////////////////////////////////////////////////////////////

        mLayerBlendMapSizeActual = mLayerBlendMapSize; // for now, until we check

        PixelFormat blendFormat = TerrainGroundTileRender::getBlendTexturFormat();

        /////////////////////////////////////////////////////////////////////

        UInt numMax = 2;

        for (UInt i = 0; i < numMax; ++i)
        {
            std::ostringstream s;
            s << "BlendMap" << i << ".png";
            Str filename = s.str();
            if ( Ogre::ResourceGroupManager::getSingleton().resourceExists(path,filename) )
            {
                Ogre::Image img;
                img.load(filename, path);
                if (img.getWidth() != mLayerBlendMapSizeActual || img.getHeight() != mLayerBlendMapSizeActual)
                    img.resize(mLayerBlendMapSizeActual, mLayerBlendMapSizeActual);

                if ( img.getFormat() == blendFormat )
                {
                    std::ostringstream bs;
                    bs << mChunk->getName() << "/BlendLayerMap" << i;
                    String blendTexName = s.str();

                    TextureManager& texMgr = TextureManager::getSingleton();
                    TexturePtr blendMapTex = texMgr.getByName(blendTexName,ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
                    if (blendMapTex.isNull())
                    {
                        Int mipmap = MGEngineUtility::getMipMapNum( mBlendMapSizeInTile );
                        blendMapTex = texMgr.createManual(blendTexName, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                            TEX_TYPE_2D, mLayerBlendMapSizeActual, mLayerBlendMapSizeActual, mipmap, blendFormat, TU_STATIC | TU_AUTOMIPMAP);
                    }

                    blendMapTex->getBuffer()->blitFromMemory( img.getPixelBox() );

                    ///////////////////////////////////////////////////////////////////

                    mBlendTextureNameList.push_back( blendTexName );
                    mBlendTextureList.push_back( blendMapTex );
                }
            }
        }
    }

    //---------------------------------------------------------------------
    void TerrainSBGroundSurface::destroyAllBlendTexture()
    {
        // remove textures
        TextureManager* tmgr = TextureManager::getSingletonPtr();

        TexturePtrList::iterator iter =  mBlendTextureList.begin();
        for ( ;iter != mBlendTextureList.end(); iter++ )
        {
            if ( (*iter).isNull() == false )
            {
                tmgr->remove( (*iter)->getHandle() );
            }
        }
        mBlendTextureList.clear();
    }

    //---------------------------------------------------------------------
    const StringVector& TerrainSBGroundSurface::getValidBlendTextureNameList()
    {
        return mBlendTextureNameList;
    }
   
    //---------------------------------------------------------------------
    void TerrainSBGroundSurface::loadBlendLayerMap(Str& path)
    {
        loadBlendTextures( path );
    }

    //---------------------------------------------------------------------
    void TerrainSBGroundSurface::unLoadBlendLayerMap()
    {
        destroyAllBlendTexture();
    }               

    //---------------------------------------------------------------------
    void TerrainSBGroundSurface::saveBlendLayerMap( Str& path )
    {
        
    }

	//---------------------------------------------------------------------
	void TerrainSBGroundSurface::_reorderBlendLayerMap( const Str& path )
	{

	}

}

