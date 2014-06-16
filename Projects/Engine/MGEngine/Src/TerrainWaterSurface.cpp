/******************************************************************************/
#include "stdafx.h"
#include "TerrainWaterSurface.h"
#include "TerrainChunk.h"
#include "EngineMain.h"
#include "Scene.h"
#include "MGEngineUtility.h"
#include "TerrainWaterTiles.h"
#include "TerrainWaterBatch.h"
#include "TerrainNode.h"

/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    TerrainWaterSurface::TerrainWaterSurface(TerrainManager* terrainMgr, Scene* scene, TerrainChunk* chunk)
        : TerrainSurface(terrainMgr,scene,chunk)
    {
    }   
    //-----------------------------------------------------------------------
    TerrainWaterSurface::~TerrainWaterSurface()
    {
        unLoad();
    }

    //**********************************************************************************************************************
    //**********************************************************************************************************************

    //-----------------------------------------------------------------------
    TerrainSurfaceType TerrainWaterSurface::getType()
    {
        return TST_WATER;
    }

    //-----------------------------------------------------------------------
    SceneObjectTypes TerrainWaterSurface::getSceneObjectTypes()
    {
        return SOT_WATER;
    }

    //-----------------------------------------------------------------------
    UInt TerrainWaterSurface::getSceneVisibleFlags()
    {
        return SOV_WATER;
    }

    //---------------------------------------------------------------------
    uint8 TerrainWaterSurface::getRenderQueueGroup()
    {
        return Ogre::RENDER_QUEUE_WORLD_GEOMETRY_1 + 1; 
    }

    //-----------------------------------------------------------------------
    void TerrainWaterSurface::configOptions()
    {
        TerrainSurface::configOptions();

        TerrainDeclare& decl                    = mTerrainMgr->getConfig();
        const TerrainChunkDeclare& chunkDecl    = mChunk->getTerrainChunkConfig();

    }

    //-----------------------------------------------------------------------
    void TerrainWaterSurface::load( Str path )
    {
        //////////////////////////////////////////////////////////////////////

        TerrainSurface::load( path );

        //////////////////////////////////////////////////////////////////////

        loadTileGroundInfoMap( path );
    }
    //-----------------------------------------------------------------------
    void TerrainWaterSurface::unLoad()
    {
        unLoadTileGroundInfoMap();

        //////////////////////////////////////////////////////////////////////

        TerrainSurface::unLoad();

        //////////////////////////////////////////////////////////////////////

        if ( isHasGrids() == false )
            return ;

    }
    //-----------------------------------------------------------------------
    void TerrainWaterSurface::save( Str path )
    {
        TerrainSurface::save(path);

        saveTileGroundInfoMap(path);
    }    

    //-----------------------------------------------------------------------
    void TerrainWaterSurface::update(Flt delta, bool synchronous)
    {
        TerrainSurface::update(delta,synchronous);
    }

    //-----------------------------------------------------------------------
    TerrainTileRender* TerrainWaterSurface::createTerrainTileRender( TerrainManager* mgr, TerrainChunk* chunk, 
        TerrainNode* node, TerrainTile* tile, UInt index )
    {
        return MG_NEW TerrainWaterTileRender( mgr, chunk, node, tile, index );
    }

    //-----------------------------------------------------------------------
    void TerrainWaterSurface::updateGeometry( Ogre::Rect rect )
    {
        refreshColors(rect);
    }

    //-----------------------------------------------------------------------
    void TerrainWaterSurface::reset()
    {
        //////////////////////////////////////////////////////////////////////

        if ( EngineMain::getInstance().getMode() != EM_EDITOR )
        {
            loadHeightData(mPath);
            loadNormalTangentMapData(mPath);
            loadColorMapData(mPath);

            //////////////////////////////////////////////////////////////////////
    
            TerrainSurface::reset();

            //////////////////////////////////////////////////////////////////////

            unLoadHeightData();
            unLoadNormalTangentMapData();
            unLoadColorMapData();
        }

        //////////////////////////////////////////////////////////////////////
    }


    //-----------------------------------------------------------------------
    void TerrainWaterSurface::loadGridData()
    {
        TerrainSurface::loadGridData();

        //////////////////////////////////////////////////////////////////////

        if ( EngineMain::getInstance().getMode() != EM_EDITOR )
        {
            unLoadHeightData();
            unLoadNormalTangentMapData();
            unLoadColorMapData();
        }

        //////////////////////////////////////////////////////////////////////
    }

    //-----------------------------------------------------------------------
    void TerrainWaterSurface::unLoadGridData()
    {
        TerrainSurface::unLoadGridData();
    }
    //**********************************************************************************************************************
    //**********************************************************************************************************************

    //-----------------------------------------------------------------------
    void TerrainWaterSurface::loadHeightData( Str path )
    {
        TerrainSurface::loadHeightData( path, "WaterHeightMap.png" );
    }

    //-----------------------------------------------------------------------
    void TerrainWaterSurface::saveHeightData( Str path )
    {
        TerrainSurface::saveHeightData( path, "WaterHeightMap.png" );
    }

    //**********************************************************************************************************************
    //**********************************************************************************************************************

    //-----------------------------------------------------------------------
    void TerrainWaterSurface::loadNormalTangentMapData( Str path )
    {
        TerrainSurface::loadNormalTangentMapData( path, "WaterNormalMap.png", "WaterTangentMap.png" );
    }

    //-----------------------------------------------------------------------
    void TerrainWaterSurface::saveNormalTangentMapData( Str path )
    {
        TerrainSurface::saveNormalTangentMapData( path, "WaterNormalMap.png", "WaterTangentMap.png" );
    }

    //**********************************************************************************************************************
    //**********************************************************************************************************************

    //-----------------------------------------------------------------------
    void TerrainWaterSurface::loadLightMapData( Str& path )
    {
        //TerrainSurface::loadLightMapData( path, "WaterLightMap.png" );
    }

    //-----------------------------------------------------------------------
    void TerrainWaterSurface::saveLightMapData( Str& path )
    {
        //TerrainSurface::saveLightMapData( path, "WaterLightMap.png" );
    }

    //**********************************************************************************************************************
    //**********************************************************************************************************************

    //-----------------------------------------------------------------------
    void TerrainWaterSurface::loadColorMapData( Str path )
    {
        TerrainSurface::loadColorMapData( path, "WaterColorMap.png" );
    }

    //-----------------------------------------------------------------------
    void TerrainWaterSurface::saveColorMapData( Str path )
    {
        TerrainSurface::saveColorMapData( path, "WaterColorMap.png" );
    }
    
    //-----------------------------------------------------------------------
    void TerrainWaterSurface::refreshColors(const Rect& rect)
    {
        // 条件判断
        if ( !mColorData )
            return;

        // Widen the rectangle by 1 element in all directions since height
        // changes affect neighbours normals
        Ogre::Rect widenedRect(
            max(0L, rect.left - 1L), 
            max(0L, rect.top - 1L), 
            min((long)mVertexSideNum, rect.right + 1L), 
            min((long)mVertexSideNum, rect.bottom + 1L)
            );

        ///////////////////////////////////////////////////////////////////////////////////////

        Plane plane;
        for (long y = widenedRect.top; y < widenedRect.bottom; ++y)
        {
            for (long x = widenedRect.left; x < widenedRect.right; ++x)
            {
                Vector3 waterPos;
                Vector3 groundPos;

                convertVertexPointToWorldPosition(x, y, &waterPos);
                mChunk->getTerrainGroundSurface()->convertVertexPointToWorldPosition(x,y,&groundPos);

                Flt heightDiff = waterPos.y - groundPos.y;
                Flt maxVisibleDepth = 2;

                if ( heightDiff < 0 )
                    heightDiff = 0;
                if ( heightDiff > maxVisibleDepth )
                    heightDiff = maxVisibleDepth;

                Flt alphaFactor = heightDiff / maxVisibleDepth;
                U8 aplhaPixel   = 0.2 + alphaFactor * 255;
                
                /////////////////////////////////////////////////////////////////////////////////

                U8* pStore = mColorData + ((y * mVertexSideNum) + x) * mColorOnePixelNum;

                *pStore++ ;             //r
                *pStore++ ;             //g 
                *pStore++ ;             //b
                *pStore++ = aplhaPixel; //a
            }
        }

    }

    //**********************************************************************************************************************
    //**********************************************************************************************************************

    //-----------------------------------------------------------------------
    void TerrainWaterSurface::loadTileGroundInfoMap( Str& path )
    {
        Str filename = "WaterGroupInfoMap.png";
        if ( Ogre::ResourceGroupManager::getSingleton().resourceExists(path,filename) )
        {
            TerrainDeclare& decl        =  mTerrainMgr->getConfig();
            UInt tileSideNumInSurface   = this->getGridSideNum();
            UInt batchSideNumInTile     = mChunk->getTerrainChunkConfig().gridSideNumInTile / decl.gridSideNumInBatch;
            UInt batchSideNumInSurface  = decl.gridSideNumInChunk / decl.gridSideNumInBatch;

            ///////////////////////////////////////////////////////////////////////////////////

            Ogre::Image img;
            img.load(filename, path);
            if (img.getWidth() != batchSideNumInSurface || img.getHeight() != batchSideNumInSurface)
                img.resize(batchSideNumInSurface, batchSideNumInSurface,Image::FILTER_NEAREST);

            ///////////////////////////////////////////////////////////////////////////////////

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

                ///////////////////////////////////////////////////////////////////////////////////

                UInt r;
                UInt g;
                UInt b;
                UInt a;

                UInt tileIndexX =0;
                UInt tileIndexY =0;

                UInt batchIndexX =0;
                UInt batchIndexY =0;

                ///////////////////////////////////////////////////////////////////////////////////

                // 遍历像素
                for (size_t y = 0; y < batchSideNumInSurface; ++y)
                {
                    // 图片像素行头移动
                    pRowHeader = pSrcBase + (batchSideNumInSurface-y-1) * rowSpan;

                    tileIndexY  = y / batchSideNumInTile;
                    batchIndexY = y % batchSideNumInTile;

                    for (size_t x = 0; x < batchSideNumInSurface; ++x)
                    {
                        // 图片像素列头移动
                        pPixel = pRowHeader + x * channels;
                        
                        r = *pPixel++;
                        g = *pPixel++;
                        b = *pPixel++;
                        a = *pPixel++;

                        ///////////////////////////////////////////////////////////////////////////////////

                        tileIndexX  = x / batchSideNumInTile;
                        batchIndexX = x % batchSideNumInTile;

                        TerrainTile* tile = this->getTileGridDataByIndex( tileIndexX, tileIndexY );
                        if ( tile == NULL )
                            break;
                        if ( tile->render == NULL )
                            break;

                        TerrainWaterTileRender* render = (TerrainWaterTileRender*)tile->render;
                        if ( render == NULL )
                            break;

                        TerrainBatchGrid* batchGrid = render->getGridDataByIndex( batchIndexX, batchIndexY );
                        if ( batchGrid == NULL )
                            break;
                        if ( batchGrid->batch == NULL )
                            break;

                        TerrainWaterBatch* batch = (TerrainWaterBatch*)batchGrid->batch;
                        if ( batch == NULL )
                            break;

                        ///////////////////////////////////////////////////////////////////////////////////
            
                        if ( a > 0 )
                        {
                            batch->setRenderEnable( true );
                            batch->setMaterialGroupID( r );
                        }else
                        {
                            batch->setRenderEnable( false );
                        }
                    }
                }
            }
        }
    }

    //-----------------------------------------------------------------------
    void TerrainWaterSurface::unLoadTileGroundInfoMap()
    {
        
    }

    //-----------------------------------------------------------------------
    void TerrainWaterSurface::saveTileGroundInfoMap( Str& path )
    {
        TerrainDeclare& decl        =  mTerrainMgr->getConfig();
        UInt tileSideNumInSurface   = this->getGridSideNum();
        UInt batchSideNumInTile     = mChunk->getTerrainChunkConfig().gridSideNumInTile / decl.gridSideNumInBatch;
        UInt batchSideNumInSurface  = decl.gridSideNumInChunk / decl.gridSideNumInBatch;


        PixelFormat imgFormat       = PF_BYTE_BGRA;
        size_t imgFormatSize        = PixelUtil::getNumElemBytes( imgFormat );
        size_t imgSize              = batchSideNumInSurface * batchSideNumInSurface * imgFormatSize; 
        size_t imgRowSize           = batchSideNumInSurface * imgFormatSize;
        void* pixData               = OGRE_MALLOC(imgSize, Ogre::MEMCATEGORY_GENERAL);
        DYNAMIC_ASSERT_LOG( pixData!=NULL, "saveTileGroundInfoMap pixData failed" );

        unsigned char* pImgBase     = (unsigned char*)pixData;

        ////////////////////////////////////////////////////////////////

        unsigned char* pRowHeader   = 0;
        unsigned char* pColHeader   = 0;
        unsigned char* pPixel       = 0;

        ////////////////////////////////////////////////////////////////

        UInt r = 0;
        UInt g = 0;
        UInt b = 0;
        UInt a = 0;

        UInt tileIndexX =0;
        UInt tileIndexY =0;

        UInt batchIndexX =0;
        UInt batchIndexY =0;

        ////////////////////////////////////////////////////////////////

        // 遍历像素
        for (size_t y = 0; y < batchSideNumInSurface; y++)
        {
            // 图片像素行头移动
            pRowHeader = pImgBase + (batchSideNumInSurface-y-1) * imgRowSize;

            tileIndexY  = y / batchSideNumInTile;
            batchIndexY = y % batchSideNumInTile;

            for (size_t x = 0; x < batchSideNumInSurface; x++)
            {
                // 图片像素列头移动
                pColHeader = pRowHeader + x * imgFormatSize;

                ///////////////////////////////////////////////////////////////////////////////////

                tileIndexX  = x / batchSideNumInTile;
                batchIndexX = x % batchSideNumInTile;

                TerrainTile* tile = this->getTileGridDataByIndex( tileIndexX, tileIndexY );
                if ( tile == NULL )
                    break;
                if ( tile->render == NULL )
                    break;

                TerrainWaterTileRender* render = (TerrainWaterTileRender*)tile->render;
                if ( render == NULL )
                    break;

                TerrainBatchGrid* batchGrid = render->getGridDataByIndex( batchIndexX, batchIndexY );
                if ( batchGrid == NULL )
                    break;
                if ( batchGrid->batch == NULL )
                    break;

                TerrainWaterBatch* batch = (TerrainWaterBatch*)batchGrid->batch;
                if ( batch == NULL )
                    break;

                ///////////////////////////////////////////////////////////////////////////////////

                if ( batch->getRenderEnable() == true )
                {
                    a = 250;
                    r = batch->getMaterialGroupID();
                }else
                {
                    a = 0;
                    r = 0;
                }

                
                *pColHeader++ = r;
                *pColHeader++ = g;
                *pColHeader++ = b;
                *pColHeader++ = a;
         
            }
        }

        ////////////////////////////////////////////////////////////////

		if ( EngineMain::getInstance().getMode() == EM_EDITOR )
		{
			//如果目录不存在先创建目录
			if (!FileOp::isExistDirectory(path))
				FileOp::createDirectory(path);

			Str filename = "WaterGroupInfoMap.png";

			// load, and tell Image to delete the memory when it's done.
			Ogre::Image img;
			img.loadDynamicImage((Ogre::uchar*)pixData, batchSideNumInSurface, batchSideNumInSurface, 1, imgFormat, true, 1, 0);
			Str filePath   = FileOp::getFullFilePath( path, filename );
			img.save( filePath );
		}

    }

}

