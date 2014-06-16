/******************************************************************************/
#include "stdafx.h"

#include "TerrainBBGroundTiles.h"
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

#include "TerrainNode.h"

#include "OgreDefaultHardwareBufferManager.h"

/******************************************************************************/

namespace MG
{

    PixelFormat TerrainBBGroundTileRender::mColorPixelFormat = PF_DXT5;
    Int TerrainBBGroundTileRender::mColorTexturMipMapNum    = 5;

    //-----------------------------------------------------------------------
    TerrainBBGroundTileRender::TerrainBBGroundTileRender( TerrainManager* mgr, TerrainChunk* chunk, TerrainNode* node, 
                TerrainTile* tile, UInt index )
        :TerrainGroundTileRender(mgr,chunk, node, tile,index)
    {
        generateTextureAtlasNameList();

        // 材质生成器
        mBaseMaterialGenerator = TerrainTilesGlobalOptions::getInstance().getDefaultMaterialGenerator( TMS_BIG );
    }

    //-----------------------------------------------------------------------
    TerrainBBGroundTileRender::~TerrainBBGroundTileRender()
    {
        unLoadRenderData();
        unLoadTextureLayerResource();
    }

    //-----------------------------------------------------------------------
    UInt TerrainBBGroundTileRender::getMaxTextureLayerCount()
    {
        return 8;
    }

    //-----------------------------------------------------------------------
    TerrainBatch*   TerrainBBGroundTileRender::createTerrainBatch( Scene* scene, TerrainTileRender* tileRender, TerrainBatch* parent, 
        const AxisAlignedBox& aabb, Ogre::Rect vertexRectInTile, MovableObject* movableObject)
    {
        return MG_NEW TerrainGroundBatch( scene, tileRender, parent, aabb, vertexRectInTile, movableObject);
    }

    //**********************************************************************************************************************
    //**********************************************************************************************************************


    //-----------------------------------------------------------------------
    void TerrainBBGroundTileRender::generateTextureLayerResource()
    {
        generateTextureAtlasList();

        generateUVMultipliers();

        generateBlendTextureList();

        generateTextureBlendLayerList();

        applyRenderConfig();
    }

    //-----------------------------------------------------------------------
    void TerrainBBGroundTileRender::generateTextureLayerResource(Int layerIndex)
    {
        TextureLayerInstance* instance = getTextureLayer( layerIndex );

        generateTextureAtlasList( instance );

        generateUVMultipliers();

        generateBlendTextureList();

        generateTextureBlendLayerList();

        applyRenderConfig();
    }

    //-----------------------------------------------------------------------
    void TerrainBBGroundTileRender::unLoadTextureLayerResource()
    {
        freeMaterial();

        destroyAllTextureAtlas();
        destroyAllBlendTexture();
        destroyAllTextureBlendLayer();

        clearTextureLayer();
    }


    //**********************************************************************************************************************
    //**********************************************************************************************************************

    //-----------------------------------------------------------------------
    void TerrainBBGroundTileRender::generateTextureAtlasNameList()
    {
        Str chunkName   = mTerrainChunk->getName();
        UInt nodeIndex  = mTerrainNode->getIndex();

        UInt maxTexNum = 2;

        mDiffuseTextureAtlasNameList.clear();
        mNormalTextureAtlasNameList.clear();
        for ( UInt i=0; i<maxTexNum; i++ )
        {
            {
                std::ostringstream s;
                s << chunkName << nodeIndex << "_Node_" << mIndex << "_TerrainDiffuseTextureAtlas_" << i;
                mDiffuseTextureAtlasNameList.push_back( Str(s.str()) ) ;
            }
            {
                std::ostringstream s;
                s << chunkName << nodeIndex << "_Node_" << mIndex << "_TerrainNormalTextureAtlas_" << i;
                mNormalTextureAtlasNameList.push_back( Str(s.str()) ) ;
            }
        }

        mDiffuseTextureAtlasList.resize( maxTexNum );
        mNormalTextureAtlasList.resize( maxTexNum );
    }

    //-----------------------------------------------------------------------
    void TerrainBBGroundTileRender::generateTextureAtlasList(TextureLayerInstance* instance)
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
                    instance->diffuseSpecularTextureIndex = 
                        addDiffuseSpecularTextureToSet(instance->layerIndex, decl->diffuseSpecularFileName,
                        instance->diffuseSpecularUVPos,instance->diffuseSpecularUVSize);
                }
                if ( instance->hasNormalHeight )
                {
                    instance->normalHeightTextureIndex = 
                        addNormalHeightTextureToSet(instance->layerIndex, decl->normalHeightFileName,
                        instance->normalHeightUVPos,instance->normalHeightUVSize);
                }
            }else
            {
                DYNAMIC_ASSERT( false );
            }
        }
    }

    //-----------------------------------------------------------------------
    void TerrainBBGroundTileRender::generateTextureAtlasList()
    {
        TerrainSurfaceManager* surfaceMgr =  mTerrainMgr->getTerrainSurfaceManager();

        TextureLayerInstanceList::iterator iter = mColorTextureDeclLayers.begin();
        for ( ; iter!=mColorTextureDeclLayers.end(); iter++ )
        {
            TextureLayerInstance& instance = (*iter);

            generateTextureAtlasList( &instance );
        }
    }

    //-----------------------------------------------------------------------
    void TerrainBBGroundTileRender::destroyAllTextureAtlas()
    {
        // remove textures
        TextureManager* tmgr = TextureManager::getSingletonPtr();

        {
            TexturePtrList::iterator iter =  mDiffuseTextureAtlasList.begin();
            for ( ;iter != mDiffuseTextureAtlasList.end(); iter++ )
            {
                if ( (*iter).isNull() == false )
                {
                    tmgr->remove( (*iter)->getHandle() );
                    (*iter).setNull();
                }
            }
        }

        {
            TexturePtrList::iterator iter =  mNormalTextureAtlasList.begin();
            for ( ;iter != mNormalTextureAtlasList.end(); iter++ )
            {
                if ( (*iter).isNull() == false )
                {
                    tmgr->remove( (*iter)->getHandle() );
                    (*iter).setNull();
                }
            }
        }

        //////////////////////////////////////////////////////////////
    }

    //-----------------------------------------------------------------------
    const StringVector& TerrainBBGroundTileRender::getValidDiffuseSpecularTextureAtlasNameList()
    {
        mValidDiffuseTextureAtlasNameList.clear();

        TexturePtrList::iterator iter =  mDiffuseTextureAtlasList.begin();
        for ( ;iter != mDiffuseTextureAtlasList.end(); iter++ )
        {
            if ( (*iter).isNull() == false )
            {
                mValidDiffuseTextureAtlasNameList.push_back( (*iter)->getName() );
            }else
            {
                break;
            }
        }

        return mValidDiffuseTextureAtlasNameList;
    }

    //-----------------------------------------------------------------------
    const StringVector& TerrainBBGroundTileRender::getValidNormalHeightTextureAtlasNameList()
    {
        mValidNormalTextureAtlasNameList.clear();

        TexturePtrList::iterator iter =  mNormalTextureAtlasList.begin();
        for ( ;iter != mNormalTextureAtlasList.end(); iter++ )
        {
            if ( (*iter).isNull() == false )
            {
                mValidNormalTextureAtlasNameList.push_back( (*iter)->getName() );
            }else
            {
                break;
            }
        }

        return mValidNormalTextureAtlasNameList;
    }

    //-----------------------------------------------------------------------
    PixelFormat TerrainBBGroundTileRender::getColorTexturFormat()
    {
        return mColorPixelFormat;
    }

    //-----------------------------------------------------------------------
    Int TerrainBBGroundTileRender::addDiffuseSpecularTextureToSet(Int selfIndex,String textureName,Vec2& texSetPos,Vec2& texSetSize)
    {
        ///////////////////////////////////////////////////////////////////////////////

        // 得到贴图集索引
        size_t texSetIndex = selfIndex / 4;
        if ( texSetIndex >= mDiffuseTextureAtlasList.size() )
            return 0;

        ///////////////////////////////////////////////////////////////////////////////

        // 加载贴图文件
        Ogre::Image img;
        img.load(textureName, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        PixelFormat imgFormat = img.getFormat();

        ///////////////////////////////////////////////////////////////////////////////

        // 创建或得到贴图集
        TexturePtr& texSet = mDiffuseTextureAtlasList[texSetIndex];
        if (texSet.isNull() )
        {
            String  texSetName = mDiffuseTextureAtlasNameList[texSetIndex];
            texSet = createOrRetriveTextureToSet( texSetName, imgFormat, Vec4(0.5,0.5,0.5,1));
        }

        ///////////////////////////////////////////////////////////////////////////////

        // 复制贴图集
        copyTextureToSet(selfIndex,img,texSet,texSetPos,texSetSize,0);

        ///////////////////////////////////////////////////////////////////////////////

        return texSetIndex;
    }

    //-----------------------------------------------------------------------
    Int TerrainBBGroundTileRender::addNormalHeightTextureToSet(Int selfIndex,String textureName,Vec2& texSetPos,Vec2& texSetSize)
    {
        ///////////////////////////////////////////////////////////////////////////////

        // 得到贴图集索引
        size_t texSetIndex = selfIndex / 4;
        if ( texSetIndex >= mNormalTextureAtlasList.size() )
            return 0;

        ///////////////////////////////////////////////////////////////////////////////

        // 加载贴图文件
        Ogre::Image img;
        img.load(textureName, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        PixelFormat imgFormat = img.getFormat();

        ///////////////////////////////////////////////////////////////////////////////

        // 创建或得到贴图集
        TexturePtr& texSet = mNormalTextureAtlasList[texSetIndex];
        if (texSet.isNull() )
        {
            String  texSetName = mNormalTextureAtlasNameList[texSetIndex];
            texSet = createOrRetriveTextureToSet( texSetName, imgFormat, Vec4(0,0,1,0.5));
        }

        ///////////////////////////////////////////////////////////////////////////////

        // 复制贴图集
        copyTextureToSet(selfIndex,img,texSet,texSetPos,texSetSize,1);

        ///////////////////////////////////////////////////////////////////////////////

        return texSetIndex;
    }

    //-----------------------------------------------------------------------
    TexturePtr TerrainBBGroundTileRender::createOrRetriveTextureToSet( String texSetName, PixelFormat format, Vec4 defaultColor )
    {
        TexturePtr texSet;
        TextureManager& texMgr = TextureManager::getSingleton();

        // 创建材质
        texSet = texMgr.getByName(texSetName, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        if (texSet.isNull())
        {
            ////////////////////////////////////////////////////////////////////////
            // 得到或创建贴图集
            // 临时使用固定大小的贴图集

            UInt texSetHeight   = 1024;
            UInt texSetWidth    = 1024;

            Int mipmap = MGEngineUtility::getMipMapNum( texSetHeight );
            texSet = texMgr.createManual(texSetName, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                TEX_TYPE_2D,texSetWidth,texSetHeight, mipmap, format, TU_STATIC | TU_AUTOMIPMAP);

            /////////////////////////////////////////////////////////////////////////

        }
        return texSet;
    }

    //-----------------------------------------------------------------------
    void TerrainBBGroundTileRender::copyTextureToSet(Int selfIndex, Ogre::Image& img, TexturePtr& texSet, Vec2& texSetPos,Vec2& texSetSize,Int type)
    {
        TextureManager& texMgr = TextureManager::getSingleton();

        ///////////////////////////////////////////////////////////////////////////////////////

        // 象限
        UInt quadrantIndex = selfIndex % 4;

        // 宽高
        UInt texSetHeight   = texSet->getHeight();
        UInt texSetWidth    = texSet->getWidth();

        Image::Box desBox;
        // 边大小
        Flt border = 16;
        Flt gap = border / Flt(texSetWidth);
        texSetSize = Vec2(0.5-gap*2,0.5-gap*2);

        if (quadrantIndex==0)
        {
            desBox      = Image::Box(0, 0, texSetWidth/2, texSetHeight/2);
            texSetPos   = Vec2(gap,gap);
        }else
        if (quadrantIndex==1)
        {
            desBox      = Image::Box(texSetWidth/2, 0, texSetWidth, texSetHeight/2);
            texSetPos = Vec2(0.5+gap,gap);
        }else
        if (quadrantIndex==2)
        {
            desBox      = Image::Box(0, texSetHeight/2, texSetWidth/2, texSetHeight);
            texSetPos = Vec2(gap,0.5+gap);
        }else
        if (quadrantIndex==3)
        {
            desBox      = Image::Box(texSetWidth/2, texSetHeight/2, texSetWidth, texSetHeight);
            texSetPos = Vec2(0.5+gap,0.5+gap);
        }

        ///////////////////////////////////////////////////////////////////////////////////////

        PixelFormat imgFormat = img.getFormat();
        if ( imgFormat != texSet->getFormat() )
        {
            DYNAMIC_ASSERT( false );
        }
        // 复制贴图到贴图集
        if (!texSet.isNull())
        {
            texSet->getBuffer()->blitFromMemory(img.getPixelBox(),desBox);
        }

        /////////////////////////////////////////////////////////////////////////////
        //Ogre::Image tempImg;
        //texSet->convertToImage(tempImg,false);

        //TexturePtr savedTexSet = texMgr.getByName("test_TerrainTilesManager_copyTextureToSet");
        //if (savedTexSet.isNull())
        //{
        //    savedTexSet = texMgr.createManual("test_TerrainTilesManager_copyTextureToSet", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        //        TEX_TYPE_2D,1024,1024, MIP_DEFAULT, PF_A8R8G8B8, TU_STATIC | TU_AUTOMIPMAP);
        //}
        //savedTexSet->getBuffer()->blitFromMemory(tempImg.getPixelBox());
        //savedTexSet->convertToImage(tempImg,false);
        //tempImg.save( Str("C:\\") + Str(texSetName) + Str(".png") );  
    }



    //**********************************************************************************************************************
    //**********************************************************************************************************************



    //---------------------------------------------------------------------
    void TerrainBBGroundTileRender::applyRenderConfig()
    {
        TerrainGroundTileRender::applyRenderConfig();

        /////////////////////////////////////////////////////////

        IDisplay* display                   = EngineMain::getInstance().display();

        TexturePtrList::iterator iter =  mDiffuseTextureAtlasList.begin();
        for ( ;iter != mDiffuseTextureAtlasList.end(); iter++ )
        {
            if ( (*iter).isNull() == false )
            {
                (*iter)->setFSAA( display->getFSAA(), "DIFFUSE_TEXTURE_ATLAS_FSAA" );
            }
        }
    }

}

