/******************************************************************************/
#include "stdafx.h"

#include "TerrainTiles.h"
#include "TerrainChunk.h"
#include "TerrainNode.h"
#include "EngineMain.h"
#include "Scene.h"
#include "MGSceneNode.h"
#include "MGEngineUtility.h"
#include "Display.h"
#include "TerrainBatch.h"
#include "LightingMapMaker.h"

#include "OgreDefaultHardwareBufferManager.h"
/******************************************************************************/

namespace MG
{

    unsigned short TerrainTileRender::POSITION_BUFFER = 0;

    //-----------------------------------------------------------------------
    TerrainTileRender::TerrainTileRender( TerrainManager* mgr, TerrainChunk* chunk, TerrainSurface* surface, 
        TerrainNode* node, TerrainTile* tile, UInt index )
        :mTerrainMgr(mgr)
        ,mTerrainSurface(surface)
        ,mTerrainChunk(chunk)
        ,mTerrainNode(node)
        ,mOwner(tile)
        ,mIndex(index)
        ,mOneVertexSize(0)
        ,mVertexSideNum(0)
        ,mVertexTotalNum(0)
        ,mCpuVertexData(NULL)
    {

        //mWorldBoundingRect
        {
            TerrainDeclare& decl = mTerrainMgr->getConfig();

            Vector3 maximum = Vector3(mOwner->worldCenterPosX + mOwner->radius , decl.maxHeight, mOwner->worldCenterPosZ +  mOwner->radius);
            Vector3 minimum = Vector3(mOwner->worldCenterPosX - mOwner->radius , -decl.maxHeight , mOwner->worldCenterPosZ - mOwner->radius);

            mWorldBoundingRect.left      = minimum.x;
            mWorldBoundingRect.right     = maximum.x;
            mWorldBoundingRect.top       = minimum.z;
            mWorldBoundingRect.bottom    = maximum.z;
        }
    }
    
    //-----------------------------------------------------------------------
    TerrainTileRender::~TerrainTileRender()
    {
    }
    
    //-----------------------------------------------------------------------
    void TerrainTileRender::update( Flt delta )
    {
    }

    //-----------------------------------------------------------------------
    void TerrainTileRender::load( )
    {
        loadRenderData();
    }

    //-----------------------------------------------------------------------
    void TerrainTileRender::unload( )
    {
        unLoadRenderData();
    }

    //-----------------------------------------------------------------------
    void TerrainTileRender::reset()
    {
        createCpuVertexData();
        initializeVertexBuffer();

        resetRootBatch();

        if ( EngineMain::getInstance().getMode() != EM_EDITOR )
        {
            destroyCpuVertexData();
        } 
    }

    //-----------------------------------------------------------------------
    void TerrainTileRender::loadRenderData()
    {
        createCpuVertexData();
        initializeVertexBuffer();
        
        loadRootBatch();

        if ( EngineMain::getInstance().getMode() != EM_EDITOR )
        {
            destroyCpuVertexData();
        }
    }

    //-----------------------------------------------------------------------
    void TerrainTileRender::unLoadRenderData()
    {
        unLoadRootBatch();

        destroyCpuVertexData();
    }


    //**********************************************************************************************************************
    //**********************************************************************************************************************

    void TerrainTileRender::createCpuVertexData()
    {
        destroyCpuVertexData();

        /////////////////////////////////////////////////////////////////////////////

        if ( !mCpuVertexData )
        {
            // create vertex structure, not using GPU for now (these are CPU structures)
            VertexDeclaration* dcl          = MG_NEW VertexDeclaration();
            VertexBufferBinding* bufbind    = MG_NEW VertexBufferBinding();

            mCpuVertexData = MG_NEW VertexData(dcl, bufbind);

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////

            // Vertex declaration
            // TODO: consider vertex compression
            size_t offset = 0;
            // POSITION 
            // float3(x, y, z)
            offset += dcl->addElement(POSITION_BUFFER, offset, VET_FLOAT3, VES_POSITION).getSize();
            // NORMAL 
            // float3(x, y, z)
            offset += dcl->addElement(POSITION_BUFFER, offset, VET_FLOAT3, VES_NORMAL).getSize();
            //// Tangent
            //// float3(x, y, z)
            //offset += dcl->addElement(POSITION_BUFFER, offset, VET_FLOAT3, VES_TANGENT).getSize();

            // DIFFUSE 
            // U8(r, g, b, a) (0-255)
            offset += dcl->addElement(POSITION_BUFFER, offset, VET_COLOUR, VES_DIFFUSE).getSize();
            // UV0
            // float2(u, v)
            // TODO - only include this if needing fixed-function
            offset += dcl->addElement(POSITION_BUFFER, offset, VET_FLOAT2, VES_TEXTURE_COORDINATES, 0).getSize();
            // UV1
            // float2(u, v)
            // TODO - only include this if needing fixed-function
            offset += dcl->addElement(POSITION_BUFFER, offset, VET_FLOAT2, VES_TEXTURE_COORDINATES, 1).getSize();

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////

            // 设置单个顶点缓冲大小
            mOneVertexSize      = dcl->getVertexSize(POSITION_BUFFER);
            // 设置顶点一边数量
            mVertexSideNum      = mTerrainSurface->getVertexSideNumInTile();
            // 设置顶点总数量
            mVertexTotalNum     = (size_t)Math::Sqr( mVertexSideNum );

            // manually create CPU-side buffer
            HardwareVertexBufferSharedPtr posbuf(
                OGRE_NEW DefaultHardwareVertexBuffer(mOneVertexSize, mVertexTotalNum, 
                HardwareBuffer::HBU_STATIC_WRITE_ONLY));

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////

            mCpuVertexData->vertexStart = 0;
            mCpuVertexData->vertexCount = mVertexTotalNum;

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////

            bufbind->setBinding(POSITION_BUFFER, posbuf);
        }
    }

    //-----------------------------------------------------------------------
    void TerrainTileRender::destroyCpuVertexData()
    {
        if ( mCpuVertexData )
        {
            // delete the bindings and declaration manually since not from a buf mgr
            MG_SAFE_DELETE( mCpuVertexData->vertexDeclaration ) ;
            mCpuVertexData->vertexDeclaration = 0;

            MG_SAFE_DELETE( mCpuVertexData->vertexBufferBinding );
            mCpuVertexData->vertexBufferBinding = 0;

            MG_SAFE_DELETE( mCpuVertexData ) ;
            mCpuVertexData = 0;
        }
    }


    //-----------------------------------------------------------------------
    void TerrainTileRender::initializeVertexBuffer()
    {
        // Chunk Surface UV
        Real uv0Scale               = 1.0f / (mTerrainSurface->getVertexSideNum() - 1);
        // Tile UV
        Real uv1Scale               =  1.0f / (mVertexSideNum - 1);

        // chunk 中顶点边数
        UInt vertexSideNumInChunk   = mTerrainSurface->getVertexSideNum();

        Ogre::Rect& vRect           = mOwner->vertexRectInSurface;

        Vector3 center              = Vector3( mTerrainNode->getOwner()->worldCenterPosX, 0 , mTerrainNode->getOwner()->worldCenterPosZ );

        /////////////////////////////////////////////////////////////////////////////////////////////

        //获取高度
        const Flt* pBaseHeight      = mTerrainSurface->getHeightData(vRect.left, vRect.top);

        /////////////////////////////////////////////////////////////////////////////////////////////

        // 获取法线和切线
        const Flt* pBaseNormal      = mTerrainSurface->getNormalDataByIndex(vRect.left, vRect.top);
        //const Flt* pBaseTangent     = mTerrainSurface->getTangentDataByIndex(vRect.left, vRect.top);
        UInt mtOnePixelNum          = mTerrainSurface->getNTOnePixelNum();
     
        /////////////////////////////////////////////////////////////////////////////////////////////

        // 获取颜色
        const U8* pBaseColor        = mTerrainSurface->getColorDataByIndex(vRect.left, vRect.top);
        UInt colorOnePixelNum       = mTerrainSurface->getColorOnePixelNum();

        /////////////////////////////////////////////////////////////////////////////////////////////

        uint16 destPosRowSkip       = 0;
        unsigned char* pRootPosBuf  = 0;
        unsigned char* pRowPosBuf   = 0;

        /////////////////////////////////////////////////////////////////////////////////////////////

        HardwareVertexBufferSharedPtr posbuf = mCpuVertexData->vertexBufferBinding->getBuffer(POSITION_BUFFER);;
        if (!posbuf.isNull())
        {
            destPosRowSkip = mVertexSideNum * mOneVertexSize;
            pRootPosBuf = static_cast<unsigned char*>(posbuf->lock(  HardwareBuffer::HBL_NORMAL ));
            pRowPosBuf  = pRootPosBuf;
        }

        /////////////////////////////////////////////////////////////////////////////////////////////

        {
            Ogre::Vector3 pos;
            Ogre::Vector3 normal;
            Ogre::Vector3 tangent;
            uint16 v    = 0;
            for (uint16 y = mOwner->vertexRectInSurface.top; y <= mOwner->vertexRectInSurface.bottom; y ++, v++)
            {

                const Flt* pHeight  = pBaseHeight;
                const Flt* pNormal  = pBaseNormal;
                //const Flt* pTangent = pBaseTangent;
                const U8*  pColor   = pBaseColor;

                float* pPosBuf = static_cast<float*>(static_cast<void*>(pRowPosBuf));
                uint16 u = 0;
                uint8* pPosBuf8 = NULL;
      
                for (uint16 x = mOwner->vertexRectInSurface.left; x <= mOwner->vertexRectInSurface.right; x ++, u++)
                {
                    if (pPosBuf)
                    {
                        mTerrainSurface->convertVertexPointToWorldPosition(x,y,*pHeight,&pos);
                        pHeight ++;

                        //////////////////////////////////////////////////////////

                        normal.x = *pNormal++;
                        normal.y = *pNormal++;
                        normal.z = *pNormal++;

                        //tangent.x = *pTangent++;
                        //tangent.y = *pTangent++;
                        //tangent.z = *pTangent++;

                        //////////////////////////////////////////////////////////

                        //position
                        *pPosBuf++ = pos.x - center.x;
                        *pPosBuf++ = pos.y;
                        *pPosBuf++ = pos.z - center.z;
  
                        ////normal
                        *pPosBuf++ = normal.x;
                        *pPosBuf++ = normal.y;
                        *pPosBuf++ = normal.z;

                        ////tangent
                        //*pPosBuf++ = tangent.x;
                        //*pPosBuf++ = tangent.y;
                        //*pPosBuf++ = tangent.z;
                        
                        ////diffuse
                        pPosBuf8 = (uint8*)pPosBuf;
                        if ( pColor )
                        {
                            *pPosBuf8++ = *pColor++;
                            *pPosBuf8++ = *pColor++;
                            *pPosBuf8++ = *pColor++;
                            *pPosBuf8++ = *pColor++;
                        }else
                        {
                            *pPosBuf8++ = 0;
                            *pPosBuf8++ = 0;
                            *pPosBuf8++ = 0;
                            *pPosBuf8++ = 127;
                        }
                        pPosBuf = (float*)pPosBuf8;

                        // UVs - base UVs vary from 0 to 1, all other values
                        // will be derived using scalings

                        //uv0
                        *pPosBuf++ = x * uv0Scale;
                        *pPosBuf++ = 1.0f - (y * uv0Scale);

                        //uv1
                        *pPosBuf++ = u * uv1Scale;
                        *pPosBuf++ = 1.0f - (v * uv1Scale);
                    }
                }

                pBaseHeight  += vertexSideNumInChunk;
                pBaseNormal  += vertexSideNumInChunk * mtOnePixelNum;
                //pBaseTangent += vertexSideNumInChunk * mtOnePixelNum;
                if ( pBaseColor )
                    pBaseColor += vertexSideNumInChunk * colorOnePixelNum;

                if (pRowPosBuf)
                    pRowPosBuf += destPosRowSkip;
            }
        }
        
        if (!posbuf.isNull())
            posbuf->unlock();
    }

    //-----------------------------------------------------------------------
    void TerrainTileRender::updateVertex(const Ogre::Rect& vertexRectInSurface)
    {
        
        DYNAMIC_ASSERT( mOwner->vertexRectInSurface.intersect( vertexRectInSurface ).isNull() == false );

        ///////////////////////////////////////////////////////////////////////////////////////

        // Main data
        long destOffsetX            = vertexRectInSurface.left <= mOwner->vertexRectInSurface.left ? 0 : (vertexRectInSurface.left - mOwner->vertexRectInSurface.left) ;
        long destOffsetY            = vertexRectInSurface.top  <= mOwner->vertexRectInSurface.top ? 0 : (vertexRectInSurface.top - mOwner->vertexRectInSurface.top) ;
        UInt vertexSideNumInChunk   = mTerrainSurface->getVertexSideNum();

        // Fill the buffers

        HardwareBuffer::LockOptions lockMode;
        if (destOffsetX || 
            destOffsetY || 
            vertexRectInSurface.width() < Int(mVertexSideNum) || 
            vertexRectInSurface.height() < Int(mVertexSideNum) )
        {
            lockMode = HardwareBuffer::HBL_NORMAL;
        }
        else
        {
            lockMode = HardwareBuffer::HBL_DISCARD;
        }

        Vector3 center              = Vector3( mTerrainNode->getOwner()->worldCenterPosX, 0 , mTerrainNode->getOwner()->worldCenterPosZ );

        //////////////////////////////////////////////////////////////////////////

        //获取高度
        const Flt* pBaseHeight          = mTerrainSurface->getHeightData(vertexRectInSurface.left, vertexRectInSurface.top);


        //////////////////////////////////////////////////////////////////////////

        // 获取法线
        const Flt* pBaseNormal          = mTerrainSurface->getNormalDataByIndex(vertexRectInSurface.left, vertexRectInSurface.top);
       // const Flt* pBaseTangent         = mTerrainSurface->getTangentDataByIndex(vertexRectInSurface.left, vertexRectInSurface.top);

        UInt ntOnePixelNum              = mTerrainSurface->getNTOnePixelNum();

        /////////////////////////////////////////////////////////////////////////////////////////////

        // 获取颜色
        const U8* pBaseColor            = mTerrainSurface->getColorDataByIndex(vertexRectInSurface.left, vertexRectInSurface.top);
        UInt colorOnePixelNum           = mTerrainSurface->getColorOnePixelNum();


        //////////////////////////////////////////////////////////////////////////

        uint16 destPosRowSkip           = 0;
        unsigned char* pRootPosBuf      = 0;
        unsigned char* pRowHeadPosBuf   = 0;
        unsigned char* pRowPosBuf       = 0;
        float* pRowPosFloat             = 0;
        HardwareVertexBufferSharedPtr posbuf = mCpuVertexData->vertexBufferBinding->getBuffer(POSITION_BUFFER);;
        if (!posbuf.isNull())
        {
            destPosRowSkip = mVertexSideNum * mOneVertexSize;
            pRootPosBuf = static_cast<unsigned char*>(posbuf->lock(lockMode));
            pRowHeadPosBuf = pRootPosBuf;
            // skip dest buffer in by left/top
            pRowHeadPosBuf += destOffsetY * destPosRowSkip + destOffsetX * mOneVertexSize;
        }

        {
            Ogre::Vector3 pos;
            Ogre::Vector3 normal;
            Ogre::Vector3 tangent;

            uint8* pPosBuf8 = NULL;

            for (uint16 y = vertexRectInSurface.top; y <= vertexRectInSurface.bottom; y ++)
            {
                const Flt* pHeight  = pBaseHeight;
                const Flt* pNormal  = pBaseNormal;
                //const Flt* pTangent = pBaseTangent;
                const U8*  pColor   = pBaseColor;
                
                pRowPosBuf          = pRowHeadPosBuf;

                for (uint16 x = vertexRectInSurface.left; x <= vertexRectInSurface.right; x ++)
                {
                    //////////////////////////////////////////////////////////////////////////////

                    //pos
                    pRowPosFloat    = static_cast<float*>(static_cast<void*>(pRowPosBuf));
                    pRowPosFloat ++;    //x
                    *pRowPosFloat++ =   *pHeight;//y
                    pRowPosFloat ++;    //z
                    pHeight     ++;

                    //////////////////////////////////////////////////////////////////////////////

                    // normal
                    *pRowPosFloat++ = *pNormal++;
                    *pRowPosFloat++ = *pNormal++;
                    *pRowPosFloat++ = *pNormal++;

                    //// normal
                    //*pRowPosFloat++ = *pTangent++;
                    //*pRowPosFloat++ = *pTangent++;
                    //*pRowPosFloat++ = *pTangent++;
                    
                    //////////////////////////////////////////////////////////////////////////////

                    ////diffuse
                    pPosBuf8 = (uint8*)pRowPosFloat;
                    if ( pColor )
                    {
                        *pPosBuf8++ = *pColor++;
                        *pPosBuf8++ = *pColor++;
                        *pPosBuf8++ = *pColor++;
                        *pPosBuf8++ = *pColor++;
                    }else
                    {
                        *pPosBuf8++ = 0;
                        *pPosBuf8++ = 0;
                        *pPosBuf8++ = 0;
                        *pPosBuf8++ = 127;
                    }
                    pRowPosFloat = (float*)pPosBuf8;

                    //////////////////////////////////////////////////////////////////////////////
            
                    pRowPosBuf  += mOneVertexSize;
                }
                pBaseHeight += vertexSideNumInChunk;
                pBaseNormal += vertexSideNumInChunk * ntOnePixelNum;
               // pBaseTangent += vertexSideNumInChunk * ntOnePixelNum;
                if ( pBaseColor )
                    pBaseColor += vertexSideNumInChunk * colorOnePixelNum;
                if (pRowHeadPosBuf)
                    pRowHeadPosBuf += destPosRowSkip;
            }
        }
       
        if (!posbuf.isNull())
            posbuf->unlock();

        ///////////////////////////////////////////////////////////////////////////////////////

        Ogre::Rect updateRectInTile;
        updateRectInTile.left   = vertexRectInSurface.left - mOwner->vertexRectInSurface.left;
        updateRectInTile.right  = vertexRectInSurface.right - mOwner->vertexRectInSurface.left;
        updateRectInTile.top    = vertexRectInSurface.top   - mOwner->vertexRectInSurface.top;
        updateRectInTile.bottom = vertexRectInSurface.bottom   - mOwner->vertexRectInSurface.top;


        ///////////////////////////////////////////////////////////////////////////////////////

        if ( isHasGrids() )
        {
            TerrainBatchGrid *& grids = getGrids();
            if ( grids )
            {
                UInt num = getGridSideNum() * getGridSideNum();
                for(UInt i =0; i<num; i++)
                {
                    TerrainBatchGrid& batchGrid = grids[i];

                    batchGrid.batch->updateVertexData( updateRectInTile );

 
                }
            }
        }
    }

    //**********************************************************************************************************************
    //**********************************************************************************************************************

    //-----------------------------------------------------------------------
    void TerrainTileRender::createGrids()
    {
        TerrainDeclare& decl    =  mTerrainMgr->getConfig();
        UInt batchGridSideNum   = decl.gridSideNumInBatch;
        UInt batchSideNumInTile = mTerrainChunk->getTerrainChunkConfig().gridSideNumInTile / batchGridSideNum;
        Flt  batchSize          = batchGridSideNum * decl.gridSize;

        Vec2 centerPos;
        centerPos.x             = mOwner->worldCenterPosX;
        centerPos.y             = mOwner->worldCenterPosZ;
   
        createGrids(batchSideNumInTile,batchSize,centerPos);
    }   

    //-----------------------------------------------------------------------
    void TerrainTileRender::createGrids(Int gridsSideNum, Flt gridSize,  Vec2 centerPos)
    {
        /////////////////////////////////////////////////////////////////

        GridManager<TerrainBatchGrid>::createGrids(gridsSideNum,gridSize,centerPos);

        /////////////////////////////////////////////////////////////////

        TerrainDeclare& decl        = mTerrainMgr->getConfig();

        TerrainBatchGrid* gridData  = getGridData();
        Int tileSideNum             = getGridSideNum();

        UInt batchGridSideNum       = decl.gridSideNumInBatch;
        UInt batchSideNumInTile     = gridsSideNum;

        Ogre::Rect  vertexRectInTile;

        Flt radius      = gridSize * 0.5;
        Flt diameter    = batchGridSideNum * decl.gridSize;

        Flt extent = radius;

        Vec3    bacthCenterPos;
        bacthCenterPos.x = mOwner->worldCenterPosX - mOwner->radius + radius;
        bacthCenterPos.z = mOwner->worldCenterPosZ + mOwner->radius - radius;
        bacthCenterPos.y = 0;

        uint16 offsetX   = 0;
        uint16 offsetY   = 0;
        uint16 boundaryX = batchGridSideNum;
        uint16 boundaryY = batchGridSideNum;

        UInt x = 0;
        UInt y = 0;
        UInt index = 0;
        for( ; y < batchSideNumInTile; y++ )
        {
            offsetX     = 0;
            boundaryX   = batchGridSideNum;
            bacthCenterPos.x = mOwner->worldCenterPosX - mOwner->radius + radius;

            for( x = 0; x<batchSideNumInTile; x++ )
            {

                vertexRectInTile.left      = offsetX;
                vertexRectInTile.top       = offsetY;
                vertexRectInTile.right     = boundaryX;
                vertexRectInTile.bottom    = boundaryY;

                AxisAlignedBox boundingBox;

                Vector3 maximum = Vector3(bacthCenterPos.x + extent , decl.maxHeight  , bacthCenterPos.z +  extent);
                Vector3 minimum = Vector3(bacthCenterPos.x - extent , decl.minHeight  , bacthCenterPos.z - extent);
                boundingBox.setMaximum(maximum);
                boundingBox.setMinimum(minimum);


                ///////////////////////////////////////////////////////////////


                if ( gridData->batch == NULL )
                {
                    gridData->batch = createTerrainBatch(
                                        mTerrainMgr->getScene(), 
                                        this, 
                                        NULL, 
                                        boundingBox,
                                        vertexRectInTile, 
                                        mTerrainNode->getMovable() 
                                        ) ; 
                }

                ///////////////////////////////////////////////////////////////

                gridData++;

                offsetX     += batchGridSideNum;
                boundaryX   += batchGridSideNum;
                bacthCenterPos.x += diameter ;

            }
            offsetY     += batchGridSideNum;
            boundaryY   += batchGridSideNum;
            bacthCenterPos.z -= diameter;
        }
    }

    //-----------------------------------------------------------------------
    void TerrainTileRender::destroyGrids()
    {
        if ( isHasGrids() )
        {
            TerrainBatchGrid *& grids = getGrids();
            if ( grids )
            {
                UInt num = getGridSideNum() * getGridSideNum();
                for(UInt i =0; i<num; i++)
                {
                    TerrainBatchGrid& batchGrid = grids[i];

                    MG_SAFE_DELETE( batchGrid.batch );
                }
            }
        }

        //////////////////////////////////////////////////////////////////

        GridManager<TerrainBatchGrid>::destroyGrids();
    }

    //**********************************************************************************************************************
    //**********************************************************************************************************************


    void TerrainTileRender::loadRootBatch()
    {
        unLoadRootBatch();

        ///////////////////////////////////////////////////

        if ( isHasGrids() )
        {
            TerrainBatchGrid *& grids = getGrids();
            if ( grids )
            {
                UInt num = getGridSideNum() * getGridSideNum();
                for(UInt i =0; i<num; i++)
                {
                    TerrainBatchGrid& batchGrid = grids[i];
                    if ( batchGrid.batch )
                        batchGrid.batch->load();
                }
            }
        }
    }

    //-----------------------------------------------------------------------
    void TerrainTileRender::resetRootBatch()
    {
        if ( isHasGrids() )
        {
            TerrainBatchGrid *& grids = getGrids();
            if ( grids )
            {
                UInt num = getGridSideNum() * getGridSideNum();
                for(UInt i =0; i<num; i++)
                {
                    TerrainBatchGrid& batchGrid = grids[i];
                    if ( batchGrid.batch )
                        batchGrid.batch->reset();
                }
            }
        }
    }

    //-----------------------------------------------------------------------
    void TerrainTileRender::unLoadRootBatch()
    {
        if ( isHasGrids() )
        {
            TerrainBatchGrid *& grids = getGrids();
            if ( grids )
            {
                UInt num = getGridSideNum() * getGridSideNum();
                for(UInt i =0; i<num; i++)
                {
                    TerrainBatchGrid& batchGrid = grids[i];
                    if ( batchGrid.batch )
                        batchGrid.batch->unLoad();
                }
            }
        }
    }
    

   
}

