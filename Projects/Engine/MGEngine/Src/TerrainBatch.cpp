/******************************************************************************/
#include "stdafx.h"
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

/******************************************************************************/

namespace MG
{

    //------------------------------------------------------------------------
    TerrainBatch::TerrainBatch( Scene* scene, TerrainTileRender* tileRender, TerrainBatch* parent, 
        const AxisAlignedBox& aabb, Ogre::Rect vertexRectInTile, MovableObject* movableObject )
        :mTileRender(tileRender)
        ,mScene(scene)
        ,mParent(parent)
        ,mBoundingBox(aabb)
        ,mVertexRectInTile(vertexRectInTile)
        ,mMovableObject(movableObject)
        ,mRender(NULL)
        ,mGpuVertexData(NULL)
        ,mGpuIndexData(NULL)
        ,mOneVertexSize(0)
        ,mVertexSideNum(0)
        ,mVertexTotalNum(0)
        ,mRenderEnable(false)
        ,mIsLoaded(false)
        ,mIsVisible(false)
    {
        {
            Int nodeCenterX = mTileRender->mTerrainNode->mOwner->worldCenterPosX;
            Int nodeCenterZ = mTileRender->mTerrainNode->mOwner->worldCenterPosZ;

            Vector3 nodeCenterPos = Vector3(nodeCenterX,0,nodeCenterZ);

            mNodeBoundingBox.setMaximum( mBoundingBox.getMaximum() - nodeCenterPos );
            mNodeBoundingBox.setMinimum( mBoundingBox.getMinimum() - nodeCenterPos );
        }

        mTerrainChunk   = mTileRender->getTerrainChunk();
        mTerrainManager = mScene->getTerrainManager();
        mSurfaceManager = mTerrainManager->getTerrainSurfaceManager();

        mOneVertexSize  = mTileRender->getOneVertexSize();
        mVertexSideNum  = vertexRectInTile.width() + 1;
        mVertexTotalNum = mVertexSideNum*mVertexSideNum ; 
    }

    //------------------------------------------------------------------------
    TerrainBatch::~TerrainBatch()
    {
    }

    //------------------------------------------------------------------------
    void TerrainBatch::setRenderEnable( bool enable )
    {
        mRenderEnable = enable;
    }

    //------------------------------------------------------------------------
    void TerrainBatch::load()
    {
        if ( mRenderEnable && !mIsLoaded )
        {
            //////////////////////////////////

            createGpuVertexData();
            createGpuIndexData();

            loadChilds();

            loadRenderableObject();

            updateVertexData( mVertexRectInTile );

            if ( EngineMain::getInstance().getMode() != EM_EDITOR )
            {
                destroyGpuVertexBackupData();
                destroyGpuIndexBackupData();
            }
            
            mIsLoaded = true;
        }
    }

    //------------------------------------------------------------------------
    void TerrainBatch::unLoad()
    {
        if ( mIsLoaded == true )
        {
            unLoadRenderableObject();

            unLoadChilds();

            destroyGpuVertexData();
            destroyGpuIndexData();

            mIsLoaded = false;
        }
    }

    //------------------------------------------------------------------------
    void TerrainBatch::reset()
    {
        checkAndUpdateGpuVertexBackupData();
        checkAndUpdateGpuIndexBackupData();
    }

    //------------------------------------------------------------------------
    void TerrainBatch::loadChilds()
    {
        //TODO:

        
    }

    //------------------------------------------------------------------------
    void TerrainBatch::unLoadChilds()
    {
        //TODO:

        
    }

    //------------------------------------------------------------------------
    Bool TerrainBatch::isValidRenderableDistance(Ogre::Camera* cam)
    {
        return true;
    }

    //------------------------------------------------------------------------
    void TerrainBatch::updateVisible( AxisAlignedBox& visibleAAbb )
    {
        //Ogre::Camera* cam = mScene->getOgreSceneManager()->getCurrentViewport()->getCamera();

        Ogre::Camera* cam = mScene->getActiveCamera()->getOgreCamera();

        if ( isValidRenderableDistance(cam) )
        {
            if ( cam->isVisible(mBoundingBox) )
            {
                mIsVisible = true;
                visibleAAbb.merge( mNodeBoundingBox );
                return;
            }
        }

        mIsVisible = false;
    }

    //------------------------------------------------------------------------
    void TerrainBatch::addRenderable(RenderQueue* queue)
    {
        //TODO:
        if ( mMovableObject && mRender && mRenderEnable && mIsLoaded && mIsVisible )
        {
            //Ogre::Camera* cam = mScene->getOgreSceneManager()->getCurrentViewport()->getCamera();

            //if ( isValidRenderableDistance(cam) )
            //{
            //    if ( cam->isVisible(mBoundingBox) )
            //    {
                    queue->addRenderable( mRender, mMovableObject->getRenderQueueGroup() );	
            //    }
            //}
        }
    }

    //------------------------------------------------------------------------
    void TerrainBatch::visitRenderables(Renderable::Visitor* visitor)
    {
        //TODO:

        if ( mRender && mRenderEnable && mIsLoaded && mIsVisible )
        {
            //Ogre::Camera* cam = mScene->getOgreSceneManager()->getCurrentViewport()->getCamera();

            //if ( isValidRenderableDistance(cam) )
            //{
            //    if ( cam->isVisible(mBoundingBox) )
            //    {
                    visitor->visit(mRender, 0, false);	
            //    }
            //}
        }
    }


    //**********************************************************************************************************************
    //**********************************************************************************************************************



    //------------------------------------------------------------------------
    void TerrainBatch::updateVertexData( const Ogre::Rect& vertexRectInTile )
    {
        
        Vector3 center = mBoundingBox.getCenter();

        Ogre::Rect dirtyRect = mVertexRectInTile.intersect( vertexRectInTile );

        if ( mGpuVertexData && (dirtyRect.isNull() == false) )
        {
            mOneVertexSize  = mTileRender->getOneVertexSize();

            ////////////////////////////////////////////////////////////////////////////////

            Ogre::VertexData* tileVertexData    = mTileRender->getCpuVertexData();
            uint16 srcPosRowSkip                = 0;
            unsigned char * srcRootPosBuf       = 0;
            unsigned char * srcRowPosBuf        = 0;
            HardwareVertexBufferSharedPtr srcPosbuf = tileVertexData->vertexBufferBinding->getBuffer(TerrainTileRender::POSITION_BUFFER);

            long destOffsetX        = dirtyRect.left <= mVertexRectInTile.left ? 0 : (dirtyRect.left - mVertexRectInTile.left) ;
            long destOffsetY        = dirtyRect.top  <= mVertexRectInTile.top ? 0 : (dirtyRect.top - mVertexRectInTile.top) ;
            uint16 destPosRowSkip   = 0;
            size_t destRowPos       = 0;
            HardwareVertexBufferSharedPtr destPosbuf = mGpuVertexData->vertexBufferBinding->getBuffer(TerrainTileRender::POSITION_BUFFER);

            if (!srcPosbuf.isNull() && !destPosbuf.isNull())
            {
                srcPosRowSkip   =  mTileRender->getVertexSideSize() * mOneVertexSize;
                srcRootPosBuf   =  static_cast<unsigned char*>(srcPosbuf->lock(HardwareBuffer::HBL_READ_ONLY));
                // skip src buffer in by left/top
                srcRowPosBuf    =  srcRootPosBuf;
                srcRowPosBuf    += dirtyRect.top * srcPosRowSkip + dirtyRect.left * mOneVertexSize;

                destPosRowSkip  = mVertexSideNum * mOneVertexSize;
                // skip dest pos in by left/top
                destRowPos      = destOffsetY * destPosRowSkip + destOffsetX * mOneVertexSize;


                ///////////////////////////////////////////////////////////////////////////////////////

                {
                    size_t destRowHeadPos   = destRowPos;
                    size_t rowCopyLen = (dirtyRect.width() + 1) * mOneVertexSize;
                    for (uint16 y = dirtyRect.top; y <= dirtyRect.bottom; y ++)
                    {
                        destPosbuf->writeData( destRowHeadPos, rowCopyLen, srcRowPosBuf );
                        srcRowPosBuf    += srcPosRowSkip;
                        destRowHeadPos  += destPosRowSkip;
                    }
                }

                ///////////////////////////////////////////////////////////////////////////////////////

                //{
                //    unsigned char * pRootPosBuf = static_cast<unsigned char*>(destPosbuf->lock(  HardwareBuffer::HBL_NORMAL ));
                //    {
                //        pRootPosBuf += destRowPos;
                //        unsigned char * destRowHeadPos   = pRootPosBuf;
                //        unsigned char * destRowPixelPos  = pRootPosBuf;
                //        for (uint16 y = dirtyRect.top; y <= dirtyRect.bottom; y ++)
                //        {
                //            destRowPixelPos = destRowHeadPos;
                //            for (uint16 x = dirtyRect.left; x <= dirtyRect.right; x ++)
                //            {
                //                float* pPosBuf = static_cast<float*>(static_cast<void*>(destRowPixelPos));
                //                if (pPosBuf)
                //                {
                //                    //position
                //                    *pPosBuf++ = *pPosBuf - center.x;
                //                    *pPosBuf++;
                //                    *pPosBuf++ = *pPosBuf - center.z;
                //                }

                //                destRowPixelPos += mOneVertexSize;
                //            }

                //            destRowHeadPos  += destPosRowSkip;
                //        }
                //    }
                //    destPosbuf->unlock();
                //}

                ///////////////////////////////////////////////////////////////////////////////////////

                srcPosbuf->unlock();
                //destPosbuf->unlock();
            }
        }

    }

    //------------------------------------------------------------------------
    void TerrainBatch::createGpuVertexData()
    {
        if ( !mGpuVertexData )
        {
            DefaultTerrainTilesGpuBufferAllocator& gpuBufferAllocator 
                                                = mSurfaceManager->getDefaultTerrainTilesGpuBufferAllocator();
            mOneVertexSize                      = mTileRender->getOneVertexSize();
            Ogre::VertexData* tileVertexData    = mTileRender->getCpuVertexData();

            /////////////////////////////////////////////////////////////////////////////

            mGpuVertexData  = OGRE_NEW VertexData();


            // copy vertex buffers
            // get new buffers
            HardwareVertexBufferSharedPtr destPosBuf;
            gpuBufferAllocator.allocateVertexBuffers(mOneVertexSize, mVertexTotalNum, destPosBuf);

            // set bindings
            mGpuVertexData->vertexBufferBinding->setBinding( TerrainTileRender::POSITION_BUFFER, destPosBuf);

            // Basic vertex info
            mGpuVertexData->vertexStart = 0;
            mGpuVertexData->vertexCount = mVertexTotalNum;

            // Copy elements
            const VertexDeclaration::VertexElementList elems = 
                tileVertexData->vertexDeclaration->getElements();
            VertexDeclaration::VertexElementList::const_iterator ei, eiend;
            eiend = elems.end();
            for (ei = elems.begin(); ei != eiend; ++ei)
            {
                mGpuVertexData->vertexDeclaration->addElement(
                    ei->getSource(),
                    ei->getOffset(),
                    ei->getType(),
                    ei->getSemantic(),
                    ei->getIndex() );
            }
        }
    }

    //------------------------------------------------------------------------
    void TerrainBatch::destroyGpuVertexData()
    {
        if (mGpuVertexData)
        {
            // Before we delete, free up the vertex buffers for someone else
            DefaultTerrainTilesGpuBufferAllocator& gpuBufferAllocator 
                = mSurfaceManager->getDefaultTerrainTilesGpuBufferAllocator();
            gpuBufferAllocator.freeVertexBuffers( mGpuVertexData->vertexBufferBinding->getBuffer( TerrainTileRender::POSITION_BUFFER) );
            mGpuVertexData->vertexBufferBinding->unsetBinding( TerrainTileRender::POSITION_BUFFER);

            MG_SAFE_DELETE( mGpuVertexData ) ;
        }
    }

    //------------------------------------------------------------------------
    void TerrainBatch::destroyGpuVertexBackupData()
    {
        if (mGpuVertexData)
        {
            HardwareVertexBufferSharedPtr destPosbuf = mGpuVertexData->vertexBufferBinding->getBuffer(TerrainTileRender::POSITION_BUFFER);
            
            if ( destPosbuf.isNull() == false )
            {
                destPosbuf->freeSystemMemoryBuffer();
            }
        }  
    }

    //------------------------------------------------------------------------
    void TerrainBatch::checkAndUpdateGpuVertexBackupData()
    {
        if ( mGpuVertexData )
        {
            HardwareVertexBufferSharedPtr destPosbuf = mGpuVertexData->vertexBufferBinding->getBuffer(TerrainTileRender::POSITION_BUFFER);
            if ( destPosbuf.isNull() == false )
            {
                destPosbuf->createSystemMemoryBuffer();

                {
                    updateVertexData( mVertexRectInTile );
                }

                destPosbuf->freeSystemMemoryBuffer();
            }
        }
    }

    //------------------------------------------------------------------------
    void TerrainBatch::createGpuIndexData()
    {
        destroyGpuIndexData();

        if ( !mGpuIndexData )
        {
            // clone, using default buffer manager ie hardware
            mGpuIndexData = MG_NEW IndexData();
            populateIndexData();
        }
    }

    //------------------------------------------------------------------------
    void TerrainBatch::destroyGpuIndexData()
    {
        MG_SAFE_DELETE( mGpuIndexData );
    }

    //------------------------------------------------------------------------
    void TerrainBatch::destroyGpuIndexBackupData()
    {
        if ( mGpuIndexData )
        {
            mGpuIndexData->indexBuffer->freeSystemMemoryBuffer();
        }
    }

    //------------------------------------------------------------------------
    void TerrainBatch::checkAndUpdateGpuIndexBackupData()
    {
        if ( mGpuIndexData )
        {
            if ( mGpuIndexData->indexBuffer->isOutOfSystemMemoryBuffer() )
            {
                mGpuIndexData->indexBuffer->createSystemMemoryBuffer();

                {
                    DefaultTerrainTilesGpuBufferAllocator& gpuBufferAllocator = mSurfaceManager->getDefaultTerrainTilesGpuBufferAllocator();
                    gpuBufferAllocator.populateIndexBuffer( mGpuIndexData->indexBuffer, mVertexSideNum );
                }
   
                mGpuIndexData->indexBuffer->freeSystemMemoryBuffer();
            }
        }
    }

    //------------------------------------------------------------------------
    void TerrainBatch::populateIndexData()
    {
        DefaultTerrainTilesGpuBufferAllocator& gpuBufferAllocator = mSurfaceManager->getDefaultTerrainTilesGpuBufferAllocator();

        DYNAMIC_ASSERT( mGpuIndexData );

        mGpuIndexData->indexBuffer  = gpuBufferAllocator.getSharedIndexBuffer( mVertexSideNum );
        mGpuIndexData->indexStart   = 0;
        mGpuIndexData->indexCount   = mGpuIndexData->indexBuffer->getNumIndexes();

        // shared index buffer is pre-populated	
    }

    //------------------------------------------------------------------------
    UInt TerrainBatch::getNumIndexesForBatchSize(U16 batchSize)
    {
        size_t mainIndexesPerRow = batchSize * 2 + 1;
        size_t numRows = batchSize - 1;
        size_t mainIndexCount = mainIndexesPerRow * numRows;
        return mainIndexCount;
    }

    //------------------------------------------------------------------------
    void TerrainBatch::populateIndexBuffer(uint32* pI, U16 batchSize)
    {
        /* For even / odd tri strip rows, triangles are this shape:
        6---7---8
        | \ | \ |
        3---4---5
        | / | / |
        0---1---2
        Note how vertex rows count upwards. In order to match up the anti-clockwise
        winding and this upward transitioning list, we need to start from the
        right hand side. So we get (2,5,1,4,0,3) etc on even lines (right-left)
        and (3,6,4,7,5,8) etc on odd lines (left-right). At the turn, we emit the end index 
        twice, this forms a degenerate triangle, which lets us turn without any artefacts. 
        So the full list in this simple case is (2,5,1,4,0,3,3,6,4,7,5,8)

        Skirts are part of the same strip, so after finishing on 8, where sX is
        the skirt vertex corresponding to main vertex X, we go
        anticlockwise around the edge, (s8,7,s7,6,s6) to do the top skirt, 
        then (3,s3,0,s0),(1,s1,2,s2),(5,s5,8,s8) to finish the left, bottom, and
        right skirts respectively.
        */

        // to issue a complete row, it takes issuing the upper and lower row
        // and one extra index, which is the degenerate triangle and also turning
        // around the winding

        size_t rowSize = batchSize;
        size_t numRows = batchSize - 1;

        // Start on the right
        uint32 currentVertex = (batchSize - 1);
        // but, our quad area might not start at 0 in this vertex data
        // offsets are at main terrain resolution, remember
        uint32 columnStart = 0;
        uint32 rowStart = 0;
        currentVertex += rowStart + columnStart;
        bool rightToLeft = true;
        for (uint32 r = 0; r < numRows; ++r)
        {
            for (uint32 c = 0; c < batchSize; ++c)
            {

                *pI++ = currentVertex;
                *pI++ = currentVertex + rowSize;

                // don't increment / decrement at a border, keep this vertex for next
                // row as we 'snake' across the tile
                if (c+1 < batchSize)
                {
                    currentVertex = rightToLeft ? 
                        currentVertex - 1 : currentVertex + 1;
                }				
            }
            rightToLeft = !rightToLeft;
            currentVertex += rowSize;
            // issue one extra index to turn winding around
            *pI++ = currentVertex;
        }
    }

    //**********************************************************************************************************************
    //**********************************************************************************************************************

    //------------------------------------------------------------------------
    void TerrainBatch::loadRenderableObject()
    {
        if ( !mRender )
        {
            mRender = MG_NEW Rend(mTileRender, this, mMovableObject, mBoundingBox.getCenter());
        }
    }

    //------------------------------------------------------------------------
    void TerrainBatch::unLoadRenderableObject()
    {
        MG_SAFE_DELETE( mRender );
    }

    //------------------------------------------------------------------------
    TerrainBatch::Rend::Rend(TerrainTileRender* tileRender, TerrainBatch* batch, MovableObject* movableObject, Vector3 centerPos)
        :mTileRender(tileRender)
        ,mMovableObject(movableObject)
        ,mCenterPos(centerPos)
        ,mBatch(batch)
    {
        mDisplay    = EngineMain::getInstance().display();
    }

    //------------------------------------------------------------------------
    TerrainBatch::Rend::~Rend()
    {
        
    }

    //------------------------------------------------------------------------
    const MaterialPtr&  TerrainBatch::Rend::getMaterial(void) const
    {
        return mBatch->getOrGenerateMaterialPtr();
    }

    //------------------------------------------------------------------------
    Technique* TerrainBatch::Rend::getTechnique(void) const
    {
        MaterialPtr& mat = mBatch->getOrGenerateMaterialPtr();
        DYNAMIC_ASSERT(mat.isNull()==false);
        return mat->getBestTechnique(0, this);
    }

    //------------------------------------------------------------------------
    void TerrainBatch::Rend::getRenderOperation(RenderOperation& op)
    {
        op.indexData        = mBatch->mGpuIndexData;
        op.useIndexes       = true;
        op.operationType    = RenderOperation::OT_TRIANGLE_STRIP;
        op.vertexData       = mBatch->mGpuVertexData;
    }
    
    //------------------------------------------------------------------------
    void TerrainBatch::Rend::getWorldTransforms(Matrix4* xform) const
    {
        *xform = mMovableObject->_getParentNodeFullTransform();
    }

    //------------------------------------------------------------------------
    Real TerrainBatch::Rend::getSquaredViewDepth(const Ogre::Camera* cam) const
    {
        Vector3 diff = mCenterPos - cam->getDerivedPosition();

        // NB use squared length rather than real depth to avoid square root
        return diff.squaredLength();
    }

    //------------------------------------------------------------------------
    const LightList& TerrainBatch::Rend::getLights(void) const
    {
         return mMovableObject->queryLights();
    }

    //------------------------------------------------------------------------
    bool TerrainBatch::Rend::getCastsShadows(void) const
    {
        return true;
    }

    

}