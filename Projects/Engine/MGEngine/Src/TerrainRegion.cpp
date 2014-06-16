/******************************************************************************/
#include "stdafx.h"
#include "TerrainRegion.h"
#include "TerrainChunk.h"
#include "TerrainManager.h"
#include "EngineMain.h"
#include "Scene.h"
#include "TerrainRegionManager.h"
#include "ResourceManager.h"
#include "Display.h"
#include "TerrainGroundSurface.h"
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    TerrainChunkRegions::TerrainChunkRegions(TerrainManager* terrainMgr, Scene* scene, TerrainChunk* chunk)
        :mTerrainMgr(terrainMgr)
        ,mScene(scene)
        ,mChunk(chunk)
        ,mBlockBaseRegion(NULL)
        ,mBlockStaticRegion(NULL)
    {
        mOwner = mTerrainMgr->getTerrainRegionManager();
    }

    //-----------------------------------------------------------------------
    TerrainChunkRegions::~TerrainChunkRegions()
    {
        unLoad();
    }

    //-----------------------------------------------------------------------
    void TerrainChunkRegions::load(Str path)
    {
        loadBlockData(path);
        loadCustomData(path);

        applyRegionVisible();
    }

    //-----------------------------------------------------------------------
    void TerrainChunkRegions::unLoad()
    {
        unLoadBlockData();
        unLoadCustomData();
    }

    //-----------------------------------------------------------------------
    void TerrainChunkRegions::save(Str path)
    {
        saveBlockData( path );
        saveCustomData( path );
    }

    //-----------------------------------------------------------------------
    void TerrainChunkRegions::clearCustomRegion()
    {
       for ( UInt i=0; i<mTerrainCustomRegions.size(); i++ )
       {
           mTerrainCustomRegions[i]->destroyGrids();
           MG_SAFE_DELETE(mTerrainCustomRegions[i]);
       }
       mTerrainCustomRegions.clear();
    }

    //-----------------------------------------------------------------------
    void TerrainChunkRegions::addCustomRegion()
    {
        TerrainDeclare& decl     = mTerrainMgr->getConfig();

        TerrainRegion* regions  = MG_NEW TerrainRegion();
        regions->createGrids( decl.gridSideNumInChunk, decl.gridSize, mChunk->getWorldCenterPos() );

        mTerrainCustomRegions.push_back(regions);
    }

    //-----------------------------------------------------------------------
    void TerrainChunkRegions::removeCustomRegion( Int index )
    {
        std::vector<TerrainRegion*>::iterator iter = mTerrainCustomRegions.begin();
        for ( UInt i=0; iter<mTerrainCustomRegions.end(); iter++,i++ )
        {
           if (i==index)
           {
               MG_SAFE_DELETE( *iter );
               mTerrainCustomRegions.erase( iter );
               break;
           }
        }
    }

    //-----------------------------------------------------------------------
    TerrainRegion* TerrainChunkRegions::getCustomRegion( Int index )
    {
        if ( UInt(index) < mTerrainCustomRegions.size() )
        {
           return mTerrainCustomRegions[index];
        }
        return NULL;
    }

    //-----------------------------------------------------------------------
    TerrainRegion* TerrainChunkRegions::getVisibledCustomRegion()
    {
        Int index = mOwner->getVisibledCustomRegionIndex();
        return getCustomRegion( index );
    }

    //-----------------------------------------------------------------------
    void TerrainChunkRegions::loadBlockData( Str path )
    {
        //////////////////////////////////////////////////////////////////////////

        unLoadBlockData();

        //////////////////////////////////////////////////////////////////////////

        TerrainDeclare& decl     = mTerrainMgr->getConfig();


        TerrainRegionGridData* blockBaseData = NULL;
        if ( ! mBlockBaseRegion )
        {
            mBlockBaseRegion = MG_NEW TerrainRegion();
            mBlockBaseRegion->createGrids( decl.gridSideNumInChunk, decl.gridSize, mChunk->getWorldCenterPos() );
            blockBaseData = mBlockBaseRegion->getGridData();
        }else
        {
            return;
        }

        TerrainRegionGridData* blockStaticData = NULL;
        if ( ! mBlockStaticRegion )
        {
            mBlockStaticRegion = MG_NEW TerrainRegion();
            mBlockStaticRegion->createGrids( decl.gridSideNumInChunk, decl.gridSize, mChunk->getWorldCenterPos() );
            blockStaticData = mBlockStaticRegion->getGridData();
        }else
        {
            return;
        }

        //////////////////////////////////////////////////////////////////////////

        Str filename="Blockmap.png";
        if ( Ogre::ResourceGroupManager::getSingleton().resourceExists(path.c_str(),filename) )
        {
            Ogre::Image img;
            img.load(filename, path.c_str());

            if (img.getWidth() != decl.gridSideNumInChunk || img.getHeight() != decl.gridSideNumInChunk)
                img.resize(decl.gridSideNumInChunk, decl.gridSideNumInChunk);

            PixelFormat fmt     = PF_L8;
            PixelFormat imgFmt  = img.getFormat();
            Int imgRowPitch = img.getRowSpan();
            if ( imgFmt == fmt )
            {
                unsigned char*  pSrcBase = img.getData(); 
                unsigned char*  srcMask = NULL;
                TerrainRegionGridData* gridData = NULL;

                //////////////////////////////////////////////////////////////////////
                // 基础网格
                TerrainRegionGridData* pDesBase     = NULL;
                // 静态网格
                TerrainRegionGridData* pDesStatic   = NULL;

                // 遍历网格高度
                for (Int y =0; y < decl.gridSideNumInChunk; ++y)
                {
                    pDesBase     = blockBaseData     + y * decl.gridSideNumInChunk;
                    pDesStatic   = blockStaticData   + y * decl.gridSideNumInChunk;

                    srcMask      = pSrcBase + (decl.gridSideNumInChunk - y - 1)*imgRowPitch;

                    // 遍历网格宽度
                    for (Int x = 0; x < decl.gridSideNumInChunk; ++x)
                    {
                        /////////////////////////////////////////////

                        if ( (*srcMask) & TBR_BLOCK_BASE )
                        {
                            pDesBase->mask = 1;
                        }else
                        {
                            pDesBase->mask = 0;
                        }

                        /////////////////////////////////////////////

                        if ( (*srcMask) & TBR_BLOCK_STATIC )
                        {
                            pDesStatic->mask = 1;
                        }else
                        {
                            pDesStatic->mask = 0;
                        }

                        /////////////////////////////////////////////

                        pDesBase++;
                        pDesStatic++;
                        srcMask++;
                    }
                }

                //////////////////////////////////////////////////////////////////////
            }
        }
        
    }

    //-----------------------------------------------------------------------
    void TerrainChunkRegions::unLoadBlockData()
    {
        if ( mBlockBaseRegion )
        {
            mBlockBaseRegion->destroyGrids();
            MG_SAFE_DELETE(mBlockBaseRegion);
        }
        if ( mBlockStaticRegion )
        {
            mBlockStaticRegion->destroyGrids();
            MG_SAFE_DELETE(mBlockStaticRegion);
        }
    }

    //-----------------------------------------------------------------------
    void TerrainChunkRegions::saveBlockData( Str path )
    {
        if ( mBlockBaseRegion && mBlockStaticRegion )
        {
            Int gridSideNum         = mBlockBaseRegion->getGridSideNum();

            PixelFormat imgFormat   = PF_L8;
            size_t imgFormatSize    = PixelUtil::getNumElemBytes( imgFormat );
            size_t imgSize          = gridSideNum * gridSideNum * imgFormatSize; 
            void* pixData           = OGRE_MALLOC(imgSize, Ogre::MEMCATEGORY_GENERAL);
            DYNAMIC_ASSERT_LOG( pixData!=NULL, "saveBlockData pixData failed" );

            /////////////////////////////////////////////////////////////////////////

            unsigned char*  pSrcBase                = (unsigned char*)(pixData); 

            TerrainRegionGridData* blockBaseData    = mBlockBaseRegion->getGridData();
            TerrainRegionGridData* blockStaticData  = mBlockStaticRegion->getGridData();

            unsigned char   srcMask                 = NULL;
            TerrainRegionGridData* gridData         = NULL;

            for( Int y = 0; y<gridSideNum ; y++ )
            {
                unsigned char*  pSrcPtr                     = pSrcBase + (gridSideNum - y - 1)*gridSideNum;
                TerrainRegionGridData* blockBaseDataPtr     = blockBaseData     + y*gridSideNum;
                TerrainRegionGridData* blockStaticDataPtr   = blockStaticData   + y*gridSideNum;

                for( Int x = 0; x<gridSideNum ; x++ )
                {
                    srcMask = 0;

                    //@
                    gridData = blockBaseDataPtr + x;
                    if ( gridData->mask )
                    {
                        srcMask |= TBR_BLOCK_BASE;
                    }

                    //@
                    gridData = blockStaticDataPtr + x;
                    if ( gridData->mask )
                    {
                        srcMask |= TBR_BLOCK_STATIC;
                    }

                    //@ 
                    *(pSrcPtr + x) = srcMask;
                }

            }


            /////////////////////////////////////////////////////////////////////////
			//如果目录不存在先创建目录

			if ( EngineMain::getInstance().getMode() == EM_EDITOR )
			{
				if (!FileOp::isExistDirectory(path))
					FileOp::createDirectory(path);

				// load, and tell Image to delete the memory when it's done.
				Ogre::Image img;
				img.loadDynamicImage((Ogre::uchar*)pixData, gridSideNum, gridSideNum, 1, imgFormat, true, 1, 0);
				Str filePath   = FileOp::getFullFilePath( path, Str("BlockMap.png") );
				img.save( filePath );
			}
        }
    }

    //-----------------------------------------------------------------------
    void TerrainChunkRegions::loadCustomData( Str path )
    {

        TerrainDeclare& decl    = mTerrainMgr->getConfig();
        Int gridSideNumInChunk  = decl.gridSideNumInChunk;

        //////////////////////////////////////////////////////////////////////////

        UInt count = mOwner->getCustomRegionCount();
        if ( count != mTerrainCustomRegions.size() )
        {
            clearCustomRegion();
            for ( UInt i=0; i<count; i++ )
            {
                addCustomRegion();
            }
        }
        UInt customRegionCount  = mTerrainCustomRegions.size();

        //////////////////////////////////////////////////////////////////////////

        Str filename="CustomRegionMap.png";
        if ( Ogre::ResourceGroupManager::getSingleton().resourceExists(path.c_str(),filename) )
        {
            Ogre::Image img;
            img.load(filename, path.c_str());

            if (img.getWidth() != gridSideNumInChunk || img.getHeight() != gridSideNumInChunk)
                img.resize(gridSideNumInChunk, gridSideNumInChunk);

            PixelFormat fmt     = PF_L8;
            PixelFormat imgFmt  = img.getFormat();
            Int imgRowPitch = img.getRowSpan();
            if ( imgFmt == fmt )
            {
                unsigned char*  pSrcBase = img.getData(); 
                unsigned char*  srcMask = NULL;
                TerrainRegionGridData* gridData = NULL;

                //////////////////////////////////////////////////////////////////////
                // 基础网格
                std::vector< TerrainRegionGridData* > pDesBases;
                pDesBases.resize( customRegionCount );

                // 遍历网格高度
                for (Int y =0; y < gridSideNumInChunk; ++y)
                {
                    /////////////////////////////////////////////

                    for ( UInt i=0; i<customRegionCount; i++ )
                    {
                        pDesBases[i] = mTerrainCustomRegions[i]->getGrids() + y * gridSideNumInChunk;
                    }

                    /////////////////////////////////////////////

                    srcMask      = pSrcBase + (gridSideNumInChunk - y - 1)*imgRowPitch;

                    // 遍历网格宽度
                    for (Int x = 0; x < gridSideNumInChunk; ++x)
                    {
                        /////////////////////////////////////////////

                        for ( UInt i=0; i<customRegionCount; i++ )
                        {
                            if ( i == 0 )
                            {
                                if ( (*srcMask) & TCR_CUSTOM_1 )
                                {
                                    pDesBases[i]->mask = 1;
                                }else
                                {
                                    pDesBases[i]->mask = 0;
                                }
                            }else
                            if ( i == 1 )
                            {
                                if ( (*srcMask) & TCR_CUSTOM_2 )
                                {
                                    pDesBases[i]->mask = 1;
                                }else
                                {
                                    pDesBases[i]->mask = 0;
                                }
                            }else
                            if ( i == 2 )
                            {
                                if ( (*srcMask) & TCR_CUSTOM_3 )
                                {
                                    pDesBases[i]->mask = 1;
                                }else
                                {
                                    pDesBases[i]->mask = 0;
                                }
                            }else
                            if ( i == 3 )
                            {
                                if ( (*srcMask) & TCR_CUSTOM_4 )
                                {
                                    pDesBases[i]->mask = 1;
                                }else
                                {
                                    pDesBases[i]->mask = 0;
                                }
                            }else
                            if ( i == 4 )
                            {
                                if ( (*srcMask) & TCR_CUSTOM_5 )
                                {
                                    pDesBases[i]->mask = 1;
                                }else
                                {
                                    pDesBases[i]->mask = 0;
                                }
                            }else
                            if ( i == 5 )
                            {
                                if ( (*srcMask) & TCR_CUSTOM_6 )
                                {
                                    pDesBases[i]->mask = 1;
                                }else
                                {
                                    pDesBases[i]->mask = 0;
                                }
                            }
                        }

                        /////////////////////////////////////////////

                        for ( UInt i=0; i<customRegionCount; i++ )
                        {
                            pDesBases[i]++;
                        }

                        /////////////////////////////////////////////

                        srcMask++;
                    }
                }

                //////////////////////////////////////////////////////////////////////
            }
        }
        
    }

    //-----------------------------------------------------------------------
    void TerrainChunkRegions::unLoadCustomData()
    {
        clearCustomRegion();
    }

    //-----------------------------------------------------------------------
    void TerrainChunkRegions::saveCustomData( Str path )
    {
        if ( mTerrainCustomRegions.size() > 0 )
        {
           Int gridSideNum         = mTerrainCustomRegions[0]->getGridSideNum();

           PixelFormat imgFormat   = PF_L8;
           size_t imgFormatSize    = PixelUtil::getNumElemBytes( imgFormat );
           size_t imgSize          = gridSideNum * gridSideNum * imgFormatSize; 
           void* pixData           = OGRE_MALLOC(imgSize, Ogre::MEMCATEGORY_GENERAL);
           DYNAMIC_ASSERT_LOG( pixData!=NULL, "saveCustomData pixData failed" );

           /////////////////////////////////////////////////////////////////////////

           unsigned char*  pSrcBase                = (unsigned char*)(pixData);
           unsigned char   srcMask                 = NULL;
           TerrainRegionGridData* gridData         = NULL;

           /////////////////////////////////////////////////////////////////////////
           std::vector< TerrainRegionGridData* > pGridBases;
           for ( UInt i=0; i<mTerrainCustomRegions.size(); i++ )
           {
               pGridBases.push_back( mTerrainCustomRegions[i]->getGridData() );
           }

           /////////////////////////////////////////////////////////////////////////

           std::vector< TerrainRegionGridData* > pDesBases;
           pDesBases.resize( pGridBases.size() );

           /////////////////////////////////////////////////////////////////////////

           for( Int y = 0; y<gridSideNum ; y++ )
           {
               ////////////////////////////////////////////

               unsigned char*  pSrcPtr  = pSrcBase + (gridSideNum - y - 1)*gridSideNum;

               ////////////////////////////////////////////

               for ( UInt i=0; i<pDesBases.size(); i++ )
               {
                   pDesBases[i] =   pGridBases[i] + y * gridSideNum;
               }

               ////////////////////////////////////////////

               for( Int x = 0; x<gridSideNum ; x++ )
               {
                   srcMask = 0;

                   /////////////////////////////////////////////

                   for ( UInt i=0; i<pDesBases.size(); i++ )
                   {
                       if ( i == 0 )
                       {
                           gridData = pDesBases[i] + x;
                           if ( gridData->mask )
                           {
                               srcMask |= TCR_CUSTOM_1;
                           }
                       }else
                       if ( i == 1 )
                       {
                           gridData = pDesBases[i] + x;
                           if ( gridData->mask )
                           {
                               srcMask |= TCR_CUSTOM_2;
                           }
                       }else
                       if ( i == 2 )
                       {
                           gridData = pDesBases[i] + x;
                           if ( gridData->mask )
                           {
                               srcMask |= TCR_CUSTOM_3;
                           }
                       }else
                       if ( i == 3 )
                       {
                           gridData = pDesBases[i] + x;
                           if ( gridData->mask )
                           {
                               srcMask |= TCR_CUSTOM_4;
                           }
                       }else
                       if ( i == 4 )
                       {
                           gridData = pDesBases[i] + x;
                           if ( gridData->mask )
                           {
                               srcMask |= TCR_CUSTOM_5;
                           }
                       }else
                       if ( i == 5 )
                       {
                           gridData = pDesBases[i] + x;
                           if ( gridData->mask )
                           {
                               srcMask |= TCR_CUSTOM_6;
                           }
                       }                                           
                   }

                   /////////////////////////////////////////////

                   *(pSrcPtr + x) = srcMask;
               }

           }

           /////////////////////////////////////////////////////////////////////////
		   //如果目录不存在先创建目录
		   if ( EngineMain::getInstance().getMode() == EM_EDITOR )
		   {
			   if (!FileOp::isExistDirectory(path))
				   FileOp::createDirectory(path);

			   // load, and tell Image to delete the memory when it's done.
			   Ogre::Image img;
			   img.loadDynamicImage((Ogre::uchar*)pixData, gridSideNum, gridSideNum, 1, imgFormat, true, 1, 0);
			   Str filePath   = FileOp::getFullFilePath( Str(path), Str("CustomRegionMap.png") );
			   img.save( filePath );
		   }
        }
    }

    //-----------------------------------------------------------------------
    void TerrainChunkRegions::applyRegionVisible()
    {
        if ( Display::getSingletonPtr()->getTerrainRegionDisplayEnabled() == false )
           return;

        //////////////////////////////////////////////////////////////////////

        TerrainGroundSurface* tileMgr = mChunk->getTerrainGroundSurface();

        TexturePtr displayTex   = tileMgr->getRegionDisplayTexture();
           
        if ( displayTex.isNull() == false )
        {
           TerrainRegionGridData*  blockBaseData    = mBlockBaseRegion->getGridData();
           TerrainRegionGridData*  blockStaticData  = mBlockStaticRegion->getGridData();
           TerrainRegion*   customRegion            = getCustomRegion( mOwner->getVisibledCustomRegionIndex() );
           TerrainRegionGridData*  customData       = NULL;
           if ( customRegion )
               customData = customRegion->getGridData();
           Bool isBlockRegionVisible                = mOwner->getBlockRegionVisible();

           //格子数量
           UInt gridSideNum = mBlockBaseRegion->getGridSideNum();
           
           // 标志位
           Bool isValid = false;

           // 基础网格
           TerrainRegionGridData* pSrcBase     = NULL;
           // 静态网格
           TerrainRegionGridData* pSrcStatic   = NULL;
           // 自定义网格
           TerrainRegionGridData* pSrcCostom   = NULL;


           // 遍历网格高度
           for (size_t y =0; y < gridSideNum; ++y)
           {

               if (isBlockRegionVisible)
               {
                   // 基础网格
                   pSrcBase     = blockBaseData     + y * gridSideNum;
                   // 静态网格
                   pSrcStatic   = blockStaticData   + y * gridSideNum;
               }else
               if (customData)
               {
                   // 自定义网格
                   pSrcCostom   = customData        + y * gridSideNum;
               }

               // 遍历网格宽度
               for (size_t x = 0; x < gridSideNum; ++x)
               {
                   isValid = false;

                   if (isBlockRegionVisible)
                   {
                       if (pSrcBase->mask)
                           isValid = true;
                       if (pSrcStatic->mask)
                           isValid = true;
                       pSrcBase++;
                       pSrcStatic++;
                   }else
                   if (customData)
                   {
                       if (pSrcCostom->mask)
                           isValid = true;
                       pSrcCostom++;
                   }

                    // 设置目标值
                   if ( isValid )
                   {
                       tileMgr->setRegionDisplay( x, y , 1, false);
                   }
                   else
                   {
                       tileMgr->setRegionDisplay( x, y , 0, false);
                   }
               }
           }
           
           /////////////////////////////////////////////////////////////////////////////////

           // 目标显示区域宽度
           UInt desWidth    = displayTex->getWidth();
           // 目标显示区域高度
           UInt desHeight   = displayTex->getHeight();
           // 锁定需要更新的显示区域
           Box box(0, 0, desWidth, desHeight);
           tileMgr->setRegionDisplayDirty( box );
        }
    }



}