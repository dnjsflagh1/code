/******************************************************************************/
#include "stdafx.h"

#include "TerrainGroundBatch.h"
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

/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    TerrainGroundTileRender::TerrainGroundTileRender( TerrainManager* mgr, TerrainChunk* chunk, 
                                                        TerrainNode* node, TerrainTile* tile, UInt index )
        :TerrainTileRender(mgr,chunk,chunk->getTerrainGroundSurface(), node, tile,index)
		, mMaterialType(MTL_NORMAL)
    {
        generateMaterialName();
        generateBlendTextureNameList();
    }

    //-----------------------------------------------------------------------
    TerrainGroundTileRender::~TerrainGroundTileRender()
    {
    }

    //-----------------------------------------------------------------------
    void TerrainGroundTileRender::update( Flt delta )
    {
        TerrainTileRender::update( delta );

        updateTextureBlendLayer();
    }

    //-----------------------------------------------------------------------
    void TerrainGroundTileRender::load( )
    {
        TerrainTileRender::load();

    }

    //-----------------------------------------------------------------------
    void TerrainGroundTileRender::unload( )
    {
        TerrainTileRender::unload();
        unLoadTextureLayerResource();
    }

    //**********************************************************************************************************************
    //**********************************************************************************************************************

    //-----------------------------------------------------------------------
    void TerrainGroundTileRender::clearTextureLayer()
    {
        mColorTextureDeclLayers.clear();
    }

    //-----------------------------------------------------------------------
    Int TerrainGroundTileRender::createOrRetriveTextureLayer( Int globleIndex, Bool isAutoGenerate )
    {
        UInt index = 0;
        Bool isExist = false;

        TextureLayerInstanceList::iterator iter = mColorTextureDeclLayers.begin();
        for ( UInt i=0; iter!=mColorTextureDeclLayers.end(); iter++,i++ )
        {
            if ( (*iter).globleIndex == globleIndex )
            {
                index   = (*iter).layerIndex;
                isExist = true;
                break;
            }
        }

        if ( isExist == false )
        {
            TerrainGroundTileRender::TextureLayerInstance newInstance;

            // 如果贴图层已经超过最大数量,则删除第一个索引,剩下的索引一次向前进一位
            UInt maxLayer = getMaxTextureLayerCount();
            if ( mColorTextureDeclLayers.size() >= maxLayer )
            {
                newInstance = *(mColorTextureDeclLayers.begin());
                mColorTextureDeclLayers.pop_front();
            }else
            {
                newInstance.layerIndex = mColorTextureDeclLayers.size();
            }

            newInstance.globleIndex = globleIndex;

            mColorTextureDeclLayers.push_back( newInstance );

            index = newInstance.layerIndex ;

            if ( isAutoGenerate )
            {
                generateTextureLayerResource( newInstance.layerIndex );
            }
        }

        return index;
    }

    //-----------------------------------------------------------------------
    TerrainGroundTileRender::TextureLayerInstance* TerrainGroundTileRender::getTextureLayer(Int layerIndex)
    {
        TerrainGroundTileRender::TextureLayerInstance* instance = NULL;

        {
            TextureLayerInstanceList::iterator iter = mColorTextureDeclLayers.begin();
            for ( ; iter!=mColorTextureDeclLayers.end(); iter++ )
            {
                if ( (*iter).layerIndex==layerIndex )
                {
                    instance = &(*iter);
                    break;
                }
            }
        }

        return instance;
    }

    //-----------------------------------------------------------------------
    UInt TerrainGroundTileRender::getTextureLayerCount() const
    {
        return mColorTextureDeclLayers.size();
    }

    //-----------------------------------------------------------------------
    void TerrainGroundTileRender::cleanNoUsedTextureLayer()
    {
        //TODO:

        //replaceTextureBlendLayer

    }

   
    //**********************************************************************************************************************
    //**********************************************************************************************************************

    //-----------------------------------------------------------------------
    void TerrainGroundTileRender::generateBlendTextureNameList()
    {
        Str chunkName   = mTerrainChunk->getName();
        UInt nodeIndex  = mTerrainNode->getIndex();

        UInt maxTexNum = 2;

        mBlendTextureNameList.clear();
        for ( UInt i=0; i<maxTexNum; i++ )
        {
            std::ostringstream s;
            s << chunkName << nodeIndex << "_Node_" << mIndex << "_TerrainBlendTextureAtlas_" << i;
            mBlendTextureNameList.push_back( s.str() );
        }

        mBlendTextureNameList.resize( maxTexNum );
    }

    //-----------------------------------------------------------------------
    void TerrainGroundTileRender::generateBlendTextureList()
    {
        PixelFormat blendFormat = TerrainGroundTileRender::getBlendTexturFormat();

        UInt texNum = mBlendTextureNameList.size();
        mBlendTextureList.resize( texNum );
        for ( UInt i=0; i < texNum; i++ )
        {
            String texName = mBlendTextureNameList[i];

            TexturePtr& texPtr = mBlendTextureList[i];

            if ( texPtr.isNull() )
            {
                mLayerBlendMapSize = mTerrainChunk->getTerrainChunkConfig().blendMapSizeInTile;

                // Use TU_STATIC because although we will update this, we won't do it every frame
                // in normal circumstances, so we don't want TU_DYNAMIC. Also we will 
                // read it (if we've cleared local temp areas) so no WRITE_ONLY
                Int mipmap = MGEngineUtility::getMipMapNum( mLayerBlendMapSize );
                texPtr = TextureManager::getSingleton().createManual(
                    texName, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
                    TEX_TYPE_2D, mLayerBlendMapSize, mLayerBlendMapSize, 1, mipmap, blendFormat, TU_STATIC | TU_AUTOMIPMAP);

                mLayerBlendMapSizeActual = texPtr->getWidth();
            }
        }
    }

    //-----------------------------------------------------------------------
    TexturePtr TerrainGroundTileRender::getBlendTexture(Int selfIndex)
    {
        if ( selfIndex > 1 )
            return TexturePtr();

        return mBlendTextureList[selfIndex];
    }

    //-----------------------------------------------------------------------
    void TerrainGroundTileRender::destroyAllBlendTexture()
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

    //-----------------------------------------------------------------------
    PixelFormat TerrainGroundTileRender::getBlendTexturFormat()
    {
        return PF_BYTE_BGRA;
    }

    //-----------------------------------------------------------------------
    const StringVector& TerrainGroundTileRender::getValidBlendTextureNameList()
    {
        mValidBlendTextureNameList.clear();


        UInt num = 0;
        if ( getTextureLayerCount() > 2 )
        {
            num = ((getTextureLayerCount() - 2) / 4) + 1;
        }else
        if ( getTextureLayerCount() > 0 )
        {
            num = 1;
        }

        if ( num != 0 )
        {
            if ( num > mBlendTextureList.size() )
            {
                num = mBlendTextureList.size();
            }

            TexturePtrList::iterator iter =  mBlendTextureList.begin();
            for ( UInt i=0; i<num; i++ )
            {
                if ( mBlendTextureList[i].isNull() == false )
                {
                    mValidBlendTextureNameList.push_back( mBlendTextureList[i]->getName() );
                }else
                {
                    break;
                }
            }
        }

        return mValidBlendTextureNameList;
    }


    //**********************************************************************************************************************
    //**********************************************************************************************************************

    //-----------------------------------------------------------------------
    void TerrainGroundTileRender::generateTextureBlendLayerList()
    {
        destroyAllTextureBlendLayer();

        UInt layerNum = mColorTextureDeclLayers.size();
        if ( layerNum > 1 )
            mBlendMapLayerList.resize( layerNum - 1, NULL );
        else
            mBlendMapLayerList.resize( 1, NULL );
    }   

    //-----------------------------------------------------------------------
    TerrainLayerBlendMap* TerrainGroundTileRender::createOrRetriveTextureBlendLayer(uint8 layerIndex)
    {
        if (layerIndex == 0 || layerIndex > (uint8)getTextureLayerCount())
            OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, 
            "Invalid layer index", "Terrain::getLayerBlendMap");

        uint8 idx = layerIndex - 1;
        if (!mBlendMapLayerList[idx])
        {
            TexturePtr tex = getBlendTexture( idx / 4 );
            mBlendMapLayerList[idx] = OGRE_NEW TerrainLayerBlendMap(this, layerIndex, tex->getBuffer().getPointer());
        }

        return mBlendMapLayerList[idx];
    }

    //-----------------------------------------------------------------------
    void TerrainGroundTileRender::destroyAllTextureBlendLayer()
    {
        for ( UInt i=0; i < mBlendMapLayerList.size(); i++ )
        {
            OGRE_DELETE mBlendMapLayerList[i];
            mBlendMapLayerList[i] = NULL;
        }
        mBlendMapLayerList.clear();
    }

    //-----------------------------------------------------------------------
    uint8 TerrainGroundTileRender::getTextureBlendLayerCount() const 
    {
        return mBlendMapLayerList.size();
    }

    //-----------------------------------------------------------------------
    void TerrainGroundTileRender::replaceTextureBlendLayer( uint8 layerIndex1, uint8 layerIndex2 )
    {
        //TODO:

    }

    //-----------------------------------------------------------------------
    void TerrainGroundTileRender::updateTextureBlendLayer()
    {
        for (size_t i = 0; i < mBlendMapLayerList.size(); ++i)
        {
            TerrainLayerBlendMap* inst = mBlendMapLayerList[i];
            if (inst)
            {
                inst->update();
            }
        }
    }


    //**********************************************************************************************************************
    //**********************************************************************************************************************

    //-----------------------------------------------------------------------
    void TerrainGroundTileRender::generateUVMultipliers()
    {
        Flt worldSize       = mTerrainSurface->getWorldSize();
        Flt layerUVMult     = 1;

        UInt layerCount = getTextureLayerCount();

        mLayerUVMultiplier.resize( layerCount );

        for (size_t i = 0; i < layerCount; ++i)
        {
            TextureLayerInstance* inst = getTextureLayer(i);
            if ( inst )
            {
                layerUVMult = worldSize / inst->worldSize;
            }else
            {
                layerUVMult = worldSize / 100;
            }
            mLayerUVMultiplier[i] = layerUVMult;
        }
    }

    //-----------------------------------------------------------------------
    Real TerrainGroundTileRender::getLayerUVMultiplier(uint8 index) const
    {
        if (index < mLayerUVMultiplier.size())
        {
            return mLayerUVMultiplier[index];
        }
        else if (!mLayerUVMultiplier.empty())
        {
            return mLayerUVMultiplier[0];
        }
        else
        {
            // default to tile 100 times
            return 100;
        }
    }

    //**********************************************************************************************************************
    //**********************************************************************************************************************


    //---------------------------------------------------------------------
    void TerrainGroundTileRender::applyRenderConfig()
    {

        TerrainTileRender::applyRenderConfig();

        /////////////////////////////////////////////////////////

        mMaterialGenerator.mMaterialDirty = true;
        mSimpleMaterialGenerator.mMaterialDirty = true;
    }

	//---------------------------------------------------------------------
	Bool TerrainGroundTileRender::isSimpleMaterial()
	{
		return  mTerrainMgr->getTerrainSurfaceManager()->getTerrainWaterMaterial()->isWaterRendering();
	}

	//---------------------------------------------------------------------
	TerrainGroundTileRender::GroundMaterialGenerator& TerrainGroundTileRender::getGroundMaterialGenerator()
	{
		if (mMaterialType == MTL_REFRACT)
		{
			return mRefractMaterialGenerator;
		}
		else
		{
			if ( isSimpleMaterial() )
			{
				return  mSimpleMaterialGenerator;
			}else
			{
				return	mMaterialGenerator;
			}
		}
	}

    //---------------------------------------------------------------------
    void TerrainGroundTileRender::generateMaterialName()
    {
        Str chunkName = mTerrainChunk->getName();
        UInt nodeIndex = mTerrainNode->getIndex();

		{
			std::ostringstream s;
			s << chunkName << nodeIndex << "Node_" << mIndex << "_TerrainGroundMaterial_Simple";
			mSimpleMaterialGenerator.mMaterialName = s.str();
		}

		{
			std::ostringstream s;
			s << chunkName << nodeIndex << "_Node_" <<  mIndex << "_TerrainGroundMaterial";
			mMaterialGenerator.mMaterialName = s.str();
		}
    }

	//---------------------------------------------------------------------
	MaterialPtr& TerrainGroundTileRender::getMaterialPtr()
	{ 
		return getGroundMaterialGenerator().mMaterial;
	}

	//---------------------------------------------------------------------
	const String& TerrainGroundTileRender::getMaterialName()
	{
		return getGroundMaterialGenerator().mMaterialName;
	}

    //---------------------------------------------------------------------
    MaterialPtr& TerrainGroundTileRender::getOrGenerateMaterialPtr()
    {
		TerrainGroundTileRender::GroundMaterialGenerator& mg = getGroundMaterialGenerator();

        if (mg.mMaterial.isNull() || mg.mMaterialDirty)
        {
            mg.mMaterial = mBaseMaterialGenerator->generate(this);
            mg.mMaterial->load();
            mg.mMaterialGenerationCount++;
            mg.mMaterialDirty = false;
        }

        if (mg.mMaterialParamsDirty)
        {
            mBaseMaterialGenerator->updateParams(mg.mMaterial, this);
            mg.mMaterialParamsDirty = false;
        }

        return mg.mMaterial;
    }

    //---------------------------------------------------------------------
    void TerrainGroundTileRender::freeMaterial()
    {
        if (!mMaterialGenerator.mMaterial.isNull())
        {
            Ogre::MaterialManager::getSingleton().remove(mMaterialGenerator.mMaterial->getHandle());
           mMaterialGenerator. mMaterial.setNull();
        }

		if (!mSimpleMaterialGenerator.mMaterial.isNull())
		{
			Ogre::MaterialManager::getSingleton().remove(mSimpleMaterialGenerator.mMaterial->getHandle());
			mSimpleMaterialGenerator. mMaterial.setNull();
		}
    }
    
}

