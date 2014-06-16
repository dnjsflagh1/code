/******************************************************************************/
#include "stdafx.h"
#include "TerrainChunk.h"
#include "EngineMain.h"
#include "Scene.h"
#include "TerrainTilesGpu.h"
#include "TerrainBatch.h"
#include "TerrainTiles.h"
/******************************************************************************/

namespace MG
{

    //---------------------------------------------------------------------
    DefaultTerrainTilesGpuBufferAllocator::DefaultTerrainTilesGpuBufferAllocator()
    {

    }
    //---------------------------------------------------------------------
    DefaultTerrainTilesGpuBufferAllocator::~DefaultTerrainTilesGpuBufferAllocator()
    {
        freeAllBuffers();
    }
    //---------------------------------------------------------------------
    void DefaultTerrainTilesGpuBufferAllocator::allocateVertexBuffers(UInt sizeVertex, UInt numVertices, HardwareVertexBufferSharedPtr& destPos)
    {
        destPos = getVertexBuffer(mFreePosBufList, sizeVertex, numVertices);
    }
    //---------------------------------------------------------------------
    HardwareVertexBufferSharedPtr DefaultTerrainTilesGpuBufferAllocator::getVertexBuffer(
        VBufList& list, size_t vertexSize, size_t numVertices)
    {
        //size_t sz = vertexSize * numVertices;
        //for (VBufList::iterator i = list.begin(); i != list.end(); ++i)
        //{
        //    if ((*i)->getSizeInBytes() == sz)
        //    {
        //        HardwareVertexBufferSharedPtr ret = *i;
        //        list.erase(i);

        //        ret->createSystemMemoryBuffer();

        //        return ret;
        //    }
        //}
        // Didn't find one?
        return HardwareBufferManager::getSingleton()
            .createVertexBuffer(vertexSize, numVertices, HardwareBuffer::HBU_STATIC_WRITE_ONLY);
        //return HardwareBufferManager::getSingleton()
        //    .createVertexBuffer(vertexSize, numVertices, HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE);

        
    }
    //---------------------------------------------------------------------
    void DefaultTerrainTilesGpuBufferAllocator::freeVertexBuffers( const HardwareVertexBufferSharedPtr& posbuf )
    {
       // mFreePosBufList.push_back(posbuf);
    }
    //---------------------------------------------------------------------
    HardwareIndexBufferSharedPtr DefaultTerrainTilesGpuBufferAllocator::getSharedIndexBuffer(U16 batchSize)
    {
        UInt hsh = hashIndexBuffer(batchSize);

        IBufMap::iterator i = mSharedIBufMap.find(hsh);
        if (i == mSharedIBufMap.end())
        {
            ////////////////////////////////////////////////////////////////////////////

            // create new
            size_t indexCount = TerrainBatch::getNumIndexesForBatchSize(batchSize);
            
            ////////////////////////////////////////////////////////////////////////////

            HardwareIndexBufferSharedPtr ret = HardwareBufferManager::getSingleton()
                //.createIndexBuffer(HardwareIndexBuffer::IT_16BIT, indexCount, 
                .createIndexBuffer(HardwareIndexBuffer::IT_32BIT, indexCount, 
                HardwareBuffer::HBU_STATIC_WRITE_ONLY);

            ////////////////////////////////////////////////////////////////////////////

            populateIndexBuffer( ret, batchSize );

            ////////////////////////////////////////////////////////////////////////////

            mSharedIBufMap[hsh] = ret;
            return ret;
        }
        else
        {
            //i->second->createSystemMemoryBuffer();
            return i->second;
        }
          
    }

    //---------------------------------------------------------------------
    void DefaultTerrainTilesGpuBufferAllocator::populateIndexBuffer( HardwareIndexBufferSharedPtr& indexPtr, U16 batchSize )
    {
        uint32* pI = static_cast<uint32*>(indexPtr->lock(HardwareBuffer::HBL_DISCARD));
        TerrainBatch::populateIndexBuffer(pI, batchSize);
        indexPtr->unlock();
    }

    //---------------------------------------------------------------------
    void DefaultTerrainTilesGpuBufferAllocator::freeAllBuffers()
    {
        mFreePosBufList.clear();
        mSharedIBufMap.clear();
    }
    //---------------------------------------------------------------------
    UInt DefaultTerrainTilesGpuBufferAllocator::hashIndexBuffer(U16 batchSize)
    {
        UInt ret = 0;
        ret = HashCombine(ret, batchSize);
        return ret;
    }


}

