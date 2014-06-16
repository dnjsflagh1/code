/******************************************************************************/
#include "stdafx.h"


#include "TerrainGroundTiles.h"
#include "TerrainGroundSurface.h"
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
#include "Display.h"
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    TerrainGroundSurface::TerrainGroundSurface(TerrainManager* terrainMgr, Scene* scene, TerrainChunk* chunk)
        : TerrainSurface(terrainMgr,scene,chunk)
        , mCpuTerrainRegionDisplayStorage(0)
        , mTerrainRegionDirty(false)
    {
    }   
    //-----------------------------------------------------------------------
    TerrainGroundSurface::~TerrainGroundSurface()
    {
    }
    
    //**********************************************************************************************************************
    //**********************************************************************************************************************

    //-----------------------------------------------------------------------
    TerrainSurfaceType TerrainGroundSurface::getType()
    {
        return TST_GROUND;
    }

    //-----------------------------------------------------------------------
    SceneObjectTypes TerrainGroundSurface::getSceneObjectTypes()
    {
        return SOT_GROUND;
    }

    //-----------------------------------------------------------------------
    UInt TerrainGroundSurface::getSceneVisibleFlags()
    {
       return (SOV_GROUND | SOV_STATIC_SHADOW | SOV_DYNAMIC_SHADOW | SOV_REFLECT | SOV_REFRACT);
       // return (SOV_GROUND | SOV_STATIC_SHADOW);
    }

    //---------------------------------------------------------------------
    uint8 TerrainGroundSurface::getRenderQueueGroup()
    {
        return Ogre::RENDER_QUEUE_WORLD_GEOMETRY_1;
    }

    //-----------------------------------------------------------------------
    void TerrainGroundSurface::configOptions()
    {
        TerrainSurface::configOptions();

        TerrainDeclare& decl                    = mTerrainMgr->getConfig();
        const TerrainChunkDeclare& chunkDecl    = mChunk->getTerrainChunkConfig();

        mTextureIndexMapSize        = mTileSideNumInChunk;
        mTextureIndexMapSizeActual  = mTileSideNumInChunk;

        mBlendMapSizeInTile         = chunkDecl.blendMapSizeInTile;
        mLayerBlendMapSize          = mBlendMapSizeInTile * mTextureIndexMapSize;
        mLayerBlendMapSizeActual    = mLayerBlendMapSize; // for now, until we check
    }

    //-----------------------------------------------------------------------
    void TerrainGroundSurface::load( Str path )
    {
        //////////////////////////////////////////////////////////////////////

        TerrainSurface::load( path );

        //////////////////////////////////////////////////////////////////////


        // 加载颜色层和混合层数据
        loadColorTextureLayerData( path );

        //////////////////////////////////////////////////////////////////////

        // 加载区域显示数据
        loadRegionDisplayData( path );

    }

    //-----------------------------------------------------------------------
    void TerrainGroundSurface::reset()
    {
        if ( EngineMain::getInstance().getMode() != EM_EDITOR )
        {
            //////////////////////////////////////////////////////////////////////

            loadNormalTangentMapData(mPath);
            loadColorMapData(mPath);

            //////////////////////////////////////////////////////////////////////

            TerrainSurface::reset();
            
            //////////////////////////////////////////////////////////////////////

            unLoadNormalTangentMapData();
            unLoadColorMapData();
        }
    }

    //-----------------------------------------------------------------------
    void TerrainGroundSurface::loadGridData()
    {
        TerrainSurface::loadGridData();

        //////////////////////////////////////////////////////////////////////

        if ( EngineMain::getInstance().getMode() != EM_EDITOR )
        {
            unLoadNormalTangentMapData();
            unLoadColorMapData();
        }

        //////////////////////////////////////////////////////////////////////
    }

    //-----------------------------------------------------------------------
    void TerrainGroundSurface::unLoadGridData()
    {
        TerrainSurface::unLoadGridData();
    }

    //-----------------------------------------------------------------------
    void TerrainGroundSurface::unLoad()
    {

        TerrainSurface::unLoad();

        //////////////////////////////////////////////////////////////////////

        if ( isHasGrids() == false )
            return ;

        //////////////////////////////////////////////////////////////////////

        unLoadRegionDisplayData();

        //////////////////////////////////////////////////////////////////////

        unLoadColorTextureLayerData();

        //////////////////////////////////////////////////////////////////////
    }
    //-----------------------------------------------------------------------
    void TerrainGroundSurface::save( Str path )
    {
        TerrainSurface::save(path);

        saveColorTextureLayerData( path );
    }    
    
    //-----------------------------------------------------------------------
    void TerrainGroundSurface::update(Flt delta, bool synchronous)
    {
        TerrainSurface::update(delta,synchronous);

        updateRegionDisplayData();
    }

    //-----------------------------------------------------------------------
    void TerrainGroundSurface::updateGeometry( Ogre::Rect rect )
    {
    }

    //**********************************************************************************************************************
    //**********************************************************************************************************************

    //-----------------------------------------------------------------------
    void TerrainGroundSurface::loadHeightData( Str path )
    {
        TerrainSurface::loadHeightData( path, "HeightMap.png" );
    }

    //-----------------------------------------------------------------------
    void TerrainGroundSurface::saveHeightData( Str path )
    {
        TerrainSurface::saveHeightData( path, "HeightMap.png" );
    }

    //-----------------------------------------------------------------------
    void TerrainGroundSurface::loadNormalTangentMapData( Str path )
    {
        TerrainSurface::loadNormalTangentMapData( path, "NormalMap.png", "TangentMap.png" );
    }

    //-----------------------------------------------------------------------
    void TerrainGroundSurface::saveNormalTangentMapData( Str path )
    {
        TerrainSurface::saveNormalTangentMapData( path, "NormalMap.png", "TangentMap.png" );
    }
    
    //**********************************************************************************************************************
    //**********************************************************************************************************************

    //-----------------------------------------------------------------------
    void TerrainGroundSurface::loadColorMapData( Str path )
    {
        //TerrainSurface::loadColorMapData( path, "ColorMap.png" );
    }

    //-----------------------------------------------------------------------
    void TerrainGroundSurface::saveColorMapData( Str path )
    {
        //TerrainSurface::saveColorMapData( path, "ColorMap.png" );
    }

    //**********************************************************************************************************************
    //**********************************************************************************************************************

    //-----------------------------------------------------------------------
    void TerrainGroundSurface::loadLightMapData( Str& path )
    {
        TerrainSurface::loadLightMapData( path, "LightMap.png" );
    }

    //-----------------------------------------------------------------------
    void TerrainGroundSurface::saveLightMapData( Str& path )
    {
        TerrainSurface::saveLightMapData( path, "LightMap.png" );
    }

    //**********************************************************************************************************************
    //**********************************************************************************************************************

    //-----------------------------------------------------------------------
    void TerrainGroundSurface::loadColorTextureLayerData( Str path )
    {
        loadTileTextureIndexMap( path );
        generateTextureLayerResource();
        loadBlendLayerMap( path );
    }
    //-----------------------------------------------------------------------
    void TerrainGroundSurface::unLoadColorTextureLayerData()
    {
        unLoadTileTextureIndexMap();
        unLoadBlendLayerMap();
    }

    //-----------------------------------------------------------------------
    void TerrainGroundSurface::saveColorTextureLayerData(Str path)
    {
        saveTileTextureIndexMap( path );
        saveBlendLayerMap( path );
    }

	//-----------------------------------------------------------------------
	void TerrainGroundSurface::_reorderColorTextureLayerData(const Str& path)
	{
		_reorderTileTextureIndexMap( path );
		_reorderBlendLayerMap( path );
	}

    //-----------------------------------------------------------------------
    void TerrainGroundSurface::generateTextureLayerResource()
    {
        if ( isHasGrids() )
        {
            TerrainGroundTileRender* render = NULL;
            TerrainNodeGrid*& nodeGrids = getGrids();
            if ( nodeGrids )
            {
                UInt num = getGridSideNum() * getGridSideNum();
                for(UInt i =0; i<num; i++)
                {
                    TerrainNodeGrid& node = nodeGrids[i];

                    if ( node.node )
                    {
                        TerrainTile*& tileGrids = node.node->getGrids();

                        UInt num2 = node.node->getGridSideNum() * node.node->getGridSideNum();
                        for(UInt j =0; j<num2; j++)
                        {
                            TerrainTile& tile = tileGrids[j];

                            if ( tile.render )
                            {
                                render = (TerrainGroundTileRender*)tile.render;
                                render->generateTextureLayerResource();
                            }
                        }
                    }
                }
            }
        }    
    }

    //---------------------------------------------------------------------
    void TerrainGroundSurface::loadTileTextureIndexMap( Str& path )
    {
        // load packed CPU data
        UInt numMax = 2;

        for (UInt i = 0; i < numMax; ++i)
        {
            std::ostringstream s;
            s << "TileTextureIndexMap" << i << ".png";
            Str filename = s.str();
            if ( Ogre::ResourceGroupManager::getSingleton().resourceExists(path,filename) )
            {
                Ogre::Image img;
                img.load(filename, path);
                if (img.getWidth() != mTextureIndexMapSize || img.getHeight() != mTextureIndexMapSize)
                    img.resize(mTextureIndexMapSize, mTextureIndexMapSize);

                PixelFormat imgFmt  = img.getFormat();
                //if ( imgFmt == PF_BYTE_RGBA || imgFmt == PF_BYTE_BGRA)
                if ( imgFmt == PF_BYTE_BGRA )
                {
                    unsigned char* pSrcBase     = img.getData();
                    float* pDst                 = 0;
                    unsigned char* pRowHeader   = 0;
                    unsigned char* pPixel       = 0;
                    size_t rowSpan              = img.getRowSpan();
                    size_t channels             = PixelUtil::getNumElemBytes( img.getFormat() );


                    TerrainGroundTileRender* render = NULL;
                    // 遍历像素
                    for (size_t y = 0; y < mTextureIndexMapSize; ++y)
                    {
                        // 图片像素行头移动
                        pRowHeader = pSrcBase + y * rowSpan;

                        for (size_t x = 0; x < mTextureIndexMapSize; ++x)
                        {
                            // 图片像素列头移动
                            pPixel = pRowHeader + x * channels;

                            TerrainTile* tile = this->getTileGridDataByIndex(x,y);
                            if ( tile == NULL )
                                break;
                            if ( tile->render == NULL )
                                break;

                            for (size_t layerIndex = 0; layerIndex < 4; ++layerIndex)
                            {
                                Int globleIndex = *pPixel;
                                if ( globleIndex < 250 )
                                {
                                    render = (TerrainGroundTileRender*)tile->render;
                                    render->createOrRetriveTextureLayer( globleIndex );
                                }
                                pPixel++;
                            }
                        }
                    }
                }
            }
        }
    }

    //---------------------------------------------------------------------
    void TerrainGroundSurface::unLoadTileTextureIndexMap()
    {
        if ( isHasGrids() )
        {
            TerrainGroundTileRender* render = NULL;
            TerrainNodeGrid*& nodeGrids = getGrids();
            if ( nodeGrids )
            {
                UInt num = getGridSideNum() * getGridSideNum();
                for(UInt i =0; i<num; i++)
                {
                    TerrainNodeGrid& node = nodeGrids[i];

                    if ( node.node )
                    {
                        TerrainTile*& tileGrids = node.node->getGrids();

                        UInt num2 = node.node->getGridSideNum() * node.node->getGridSideNum();
                        for(UInt j =0; j<num2; j++)
                        {
                            TerrainTile& tile = tileGrids[j];
                            
                            if ( tile.render )
                            {
                                render = (TerrainGroundTileRender*)tile.render;
                                render->clearTextureLayer();
                            }
                        }
                    }
                }
            }
        }     
    }

    //---------------------------------------------------------------------
    void TerrainGroundSurface::saveTileTextureIndexMap( Str& path )
    {
        UInt numMax = 2;

        for (UInt i = 0; i < numMax; ++i)
        {
            PixelFormat imgFormat       = PF_BYTE_BGRA;
            size_t imgFormatSize        = PixelUtil::getNumElemBytes( imgFormat );
            size_t imgSize              = mTextureIndexMapSize * mTextureIndexMapSize * imgFormatSize; 
            size_t imgRowSize           = mTextureIndexMapSize * imgFormatSize;
            void* pixData               = OGRE_MALLOC(imgSize, Ogre::MEMCATEGORY_GENERAL);
            DYNAMIC_ASSERT_LOG( pixData!=NULL, "saveTileTextureIndexMap pixData failed" );

            unsigned char* pImgBase     = (unsigned char*)pixData;

            ////////////////////////////////////////////////////////////////

            unsigned char* pRowHeader   = 0;
            unsigned char* pColHeader   = 0;
            unsigned char* pPixel       = 0;
            TerrainGroundTileRender::TextureLayerInstance* instance = NULL; 

            TerrainGroundTileRender* render = NULL;

            // 遍历像素
            for (size_t y = 0; y < mTextureIndexMapSize; y++)
            {
                // 图片像素行头移动
                pRowHeader = pImgBase + y * imgRowSize;

                for (size_t x = 0; x < mTextureIndexMapSize; x++)
                {
                    // 图片像素列头移动
                    pColHeader = pRowHeader + x * imgFormatSize;

                    TerrainTile* tile = this->getTileGridDataByIndex(x,y);
                    if ( tile == NULL )
                        break;
                    if ( tile->render == NULL )
                        break;

                    for (size_t layerIndex = 0; layerIndex < 4; layerIndex++)
                    {
                        render = (TerrainGroundTileRender*)tile->render;
                        instance = render->getTextureLayer( layerIndex + i*4 );

                        pPixel = pColHeader + layerIndex;

                        if ( instance )
                        {
                            *pPixel = instance->globleIndex;
                        }else
                        {
                            *pPixel = unsigned char(250);
                        }
                    }
                }
            }

            ////////////////////////////////////////////////////////////////

			if ( EngineMain::getInstance().getMode() == EM_EDITOR )
			{
				if (!FileOp::isExistDirectory(path))
					FileOp::createDirectory(path);
				std::ostringstream s;
				s << "TileTextureIndexMap" << i << ".png";
				Str filename = s.str();

				// load, and tell Image to delete the memory when it's done.
				Ogre::Image img;
				img.loadDynamicImage((Ogre::uchar*)pixData, mTextureIndexMapSize, mTextureIndexMapSize, 1, imgFormat, true, 1, 0);
				Str filePath   = FileOp::getFullFilePath( path, filename );
				img.save( filePath );
			}

			//for test-----------------
			//std::ostringstream bs;
			//bs << "TileTextureIndexMap" << i << ".bmp";
			//Str bfilename = bs.str();
			//Str bfilePath   = FileOp::getFullFilePath( path, bfilename );
			//img.save( bfilePath );
			//--end for test
        }
    }

	//---------------------------------------------------------------------
	void TerrainGroundSurface::_reorderTileTextureIndexMap( const Str& path )
	{
		Str tempPath = path;

		UInt numMax = 2;

		for (UInt i = 0; i < numMax; ++i)
		{
			PixelFormat imgFormat       = PF_BYTE_BGRA;
			size_t imgFormatSize        = PixelUtil::getNumElemBytes( imgFormat );
			size_t imgSize              = mTextureIndexMapSize * mTextureIndexMapSize * imgFormatSize; 
			size_t imgRowSize           = mTextureIndexMapSize * imgFormatSize;
			void* pixData               = OGRE_MALLOC(imgSize, Ogre::MEMCATEGORY_GENERAL);
			DYNAMIC_ASSERT_LOG( pixData!=NULL, "saveTileTextureIndexMap pixData failed" );

			unsigned char* pImgBase     = (unsigned char*)pixData;

			////////////////////////////////////////////////////////////////

			unsigned char* pRowHeader   = 0;
			unsigned char* pColHeader   = 0;
			unsigned char* pPixel       = 0;

			TerrainGroundTileRender::TextureLayerInstance* instance = NULL; 

			TerrainGroundTileRender* render = NULL;

			// 遍历像素
			for (size_t y = 0; y < mTextureIndexMapSize; y++)
			{
				// 图片像素行头移动
				pRowHeader = pImgBase + y * imgRowSize;

				for (size_t x = 0; x < mTextureIndexMapSize; x++)
				{
					// 图片像素列头移动
					pColHeader = pRowHeader + x * imgFormatSize;


					for (size_t layerIndex = 0; layerIndex < 4; layerIndex++)
					{
						pPixel = pColHeader + layerIndex;

						int index = i*4+layerIndex;
						*pPixel = index;
					}
				}
			}

			////////////////////////////////////////////////////////////////

			if ( EngineMain::getInstance().getMode() == EM_EDITOR )
			{
				if (!FileOp::isExistDirectory(tempPath))
					FileOp::createDirectory(tempPath);
				std::ostringstream s;
				s << "TileTextureIndexMap" << i << ".png";
				Str filename = s.str();

				// load, and tell Image to delete the memory when it's done.
				Ogre::Image img;
				img.loadDynamicImage((Ogre::uchar*)pixData, mTextureIndexMapSize, mTextureIndexMapSize, 1, imgFormat, true, 1, 0);
				Str filePath   = FileOp::getFullFilePath( tempPath, filename );
				img.save( filePath );

				//for test----------------------------
				//std::ostringstream bs;
				//bs << "TileTextureIndexMap" << i << ".bmp";
				//Str bfilename = bs.str();
				//Str bfilePath   = FileOp::getFullFilePath( tempPath, bfilename );
				//img.save( bfilePath );
				//-- end for test
			}
		}
	}


    //**********************************************************************************************************************
    //**********************************************************************************************************************

    
    //-----------------------------------------------------------------------
    void TerrainGroundSurface::loadRegionDisplayData( Str& path )
    {
        //////////////////////////////////////////////////////////////////////

        if ( Display::getSingletonPtr()->getTerrainRegionDisplayEnabled() == false )
            return;

        TerrainTilesGlobalOptions& opts = TerrainTilesGlobalOptions::getInstance();

        //////////////////////////////////////////////////////////////////////

        //加载区域显示数据
        if ( mTerrainRegionDisplayTexture.isNull() )
        {
            mTerrainRegionDisplayTextureSideSize = mVertexSideNum - 1;
            mTerrainRegionChannelOffset =  PixelUtil::getNumElemBytes(PF_L8);

            // create
            mTerrainRegionDisplayTexture = TextureManager::getSingleton().createManual(
                mChunk->getName() + "/rm", opts.getDefaultResourceGroup(), 
                TEX_TYPE_2D, mTerrainRegionDisplayTextureSideSize, mTerrainRegionDisplayTextureSideSize, 0, PF_L8, TU_STATIC );
        }

        //////////////////////////////////////////////////////////////////////

        if ( !mCpuTerrainRegionDisplayStorage )
        {
            mCpuTerrainRegionDisplaySideNum         =  mVertexSideNum - 1;
            mCpuTerrainRegionDisplaySize            =  mCpuTerrainRegionDisplaySideNum * mCpuTerrainRegionDisplaySideNum * sizeof(bool);
            mCpuTerrainRegionDisplayStorage         = (bool*)OGRE_MALLOC(mCpuTerrainRegionDisplaySize, MEMCATEGORY_RESOURCE);
            DYNAMIC_ASSERT_LOG( mCpuTerrainRegionDisplayStorage!=NULL, "loadRegionDisplayData mCpuTerrainRegionDisplayStorage failed" );

        }

        //////////////////////////////////////////////////////////////////////

        clearRegionDisplayData();
    }

    //-----------------------------------------------------------------------
    void TerrainGroundSurface::unLoadRegionDisplayData()
    {
        TextureManager* tmgr = TextureManager::getSingletonPtr();
        if (tmgr)
        {
            if (!mTerrainRegionDisplayTexture.isNull())
            {
                tmgr->remove(mTerrainRegionDisplayTexture->getHandle());
                mTerrainRegionDisplayTexture.setNull();
                mTerrainRegionDisplayTextureSideSize = 0;
            }
        }

        if ( mCpuTerrainRegionDisplayStorage )
        {
            OGRE_FREE(mCpuTerrainRegionDisplayStorage, MEMCATEGORY_RESOURCE);
            mCpuTerrainRegionDisplayStorage = 0;
            mCpuTerrainRegionDisplaySize    = 0;
        }
    }

    //-----------------------------------------------------------------------
    void TerrainGroundSurface::clearRegionDisplayData()
    {
        if ( mTerrainRegionDisplayTexture.isNull() == false )
        {
            Box box(0, 0, mTerrainRegionDisplayTextureSideSize, mTerrainRegionDisplayTextureSideSize);
            HardwarePixelBufferSharedPtr buf = mTerrainRegionDisplayTexture->getBuffer();
            const PixelBox& pixelBox = buf->lock(box, HardwarePixelBuffer::HBL_NORMAL);
            {
                UInt rowPitch = pixelBox.rowPitch;
                UInt height = pixelBox.getHeight();
                uint8* pInit = static_cast<uint8*>(pixelBox.data);
                memset(pInit, 0, rowPitch * height);
            }
            buf->unlock();
        }

        if ( mCpuTerrainRegionDisplayStorage )
        {
            memset(mCpuTerrainRegionDisplayStorage, 0, mCpuTerrainRegionDisplaySize);
        }
    }

    //-----------------------------------------------------------------------
    void TerrainGroundSurface::setRegionDisplay(Int x, Int y, bool isDisplay,bool isDirty)
    {
        if ( Display::getSingletonPtr()->getTerrainRegionDisplayEnabled() == false )
            return;

        /////////////////////////////////////////////////////////////////////////////////

        if ( !mCpuTerrainRegionDisplayStorage )
            return;

        /////////////////////////////////////////////////////////////////////////////////

        y = mCpuTerrainRegionDisplaySideNum - y - 1;

        /////////////////////////////////////////////////////////////////////////////////

        // clamp
        x = min(x, (Int)(mCpuTerrainRegionDisplaySideNum));
        x = max(x, (Int)0);
        y = min(y, (Int)(mCpuTerrainRegionDisplaySideNum));
        y = max(y, (Int)0);

        *(mCpuTerrainRegionDisplayStorage + y * mCpuTerrainRegionDisplaySideNum + x) = isDisplay?1:0;

        /////////////////////////////////////////////////////////////////////////////////

        if ( isDirty )
        {
            Int lx = x+1;
            Int ly = y+1;
            lx = min(lx, (Int)(mCpuTerrainRegionDisplaySideNum));
            ly = min(ly, (Int)(mCpuTerrainRegionDisplaySideNum));

            Rect rect(x, y, lx, ly);
            if (mTerrainRegionDirty)
            {
                mTerrainRegionDirtyBox.left     = min(mTerrainRegionDirtyBox.left, (size_t)rect.left);
                mTerrainRegionDirtyBox.top      = min(mTerrainRegionDirtyBox.top, (size_t)rect.top);
                mTerrainRegionDirtyBox.right    = max(mTerrainRegionDirtyBox.right, (size_t)rect.right);
                mTerrainRegionDirtyBox.bottom   = max(mTerrainRegionDirtyBox.bottom, (size_t)rect.bottom);
            }
            else
            {
                mTerrainRegionDirtyBox.left     = rect.left;
                mTerrainRegionDirtyBox.right    = rect.right;
                mTerrainRegionDirtyBox.top      = rect.top;
                mTerrainRegionDirtyBox.bottom   = rect.bottom;
                mTerrainRegionDirty = true;
            }
        }
    }


    //-----------------------------------------------------------------------
    bool* TerrainGroundSurface::getRegionDisplayData()
    {
        return mCpuTerrainRegionDisplayStorage;
    }

    //-----------------------------------------------------------------------
    void TerrainGroundSurface::setRegionDisplayDirty( Box& dirtyBox )
    {
        mTerrainRegionDirtyBox = dirtyBox;
        mTerrainRegionDirty = true;
    }

    //-----------------------------------------------------------------------
    void TerrainGroundSurface::updateRegionDisplayData()
    {
        if ( Display::getSingletonPtr()->getTerrainRegionDisplayEnabled() == false )
            return;

        /////////////////////////////////////////////////////////////////////////////////

        if (mCpuTerrainRegionDisplayStorage && mTerrainRegionDirty && !mTerrainRegionDisplayTexture.isNull())
        {
            // Upload data
            bool* pSrcBase = mCpuTerrainRegionDisplayStorage + mTerrainRegionDirtyBox.top * mCpuTerrainRegionDisplaySideNum + mTerrainRegionDirtyBox.left;

            HardwarePixelBufferSharedPtr buf = mTerrainRegionDisplayTexture->getBuffer();
            const PixelBox& pixelBox = buf->lock(mTerrainRegionDirtyBox, HardwarePixelBuffer::HBL_NORMAL);
            {
                UInt dstRowPitch = pixelBox.rowPitch;
                UInt dstHeight = pixelBox.getHeight();

                uint8* pDstBase = static_cast<uint8*>(pixelBox.data);

                size_t dirtyWidth = mTerrainRegionDirtyBox.getWidth();
                size_t dirtyHeight = mTerrainRegionDirtyBox.getHeight();
                size_t dstInc = PixelUtil::getNumElemBytes(buf->getFormat());

                //pDstBase += mTerrainRegionChannelOffset;

                bool isValid = false;
                // 遍历影响区域高度
                for (size_t y =0; y < dirtyHeight; ++y)
                {
                    bool* pSrc  = pSrcBase + y * mCpuTerrainRegionDisplaySideNum;

                    uint8* pDst = pDstBase + y * dstRowPitch;

                    // 遍历影响区域宽度
                    for (size_t x = 0; x < dirtyWidth; ++x)
                    {
                        isValid = (*pSrc++);
                        // 设置目标值
                        if ( isValid )
                        {
                            *pDst = 255;
                        }
                        else
                        {
                            *pDst = 0;
                        }
                        pDst += dstInc;
                    }
                }
            }
            buf->unlock();

            mTerrainRegionDirty = false;
        }
    }

    //-----------------------------------------------------------------------
    TexturePtr TerrainGroundSurface::getRegionDisplayTexture() const
    {
        return mTerrainRegionDisplayTexture;
    }


}

