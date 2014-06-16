/******************************************************************************/
#ifndef _TERRAINTILESGPU_H_
#define _TERRAINTILESGPU_H_
/******************************************************************************/

#include "EnginePreqs.h"

/******************************************************************************/
namespace MG
{
    /** Interface used to by the Terrain instance to allocate GPU buffers.
    @remarks This class exists to make it easier to re-use buffers between
    multiple instances of terrain.
    */
    class GpuBufferAllocator : public GeneralAllocatedObject
    {
    public:
        GpuBufferAllocator() {}
        virtual ~GpuBufferAllocator() {}

        /** Allocate (or reuse) vertex buffers for a terrain LOD. 
        @param numVertices The total number of vertices
        @param destPos Pointer to a vertex buffer for positions, to be bound
        */
        virtual void allocateVertexBuffers(UInt sizeVertex, UInt numVertices, HardwareVertexBufferSharedPtr& destPos) = 0;
        /** Free (or return to the pool) vertex buffers for terrain. 
        */
        virtual void freeVertexBuffers(const HardwareVertexBufferSharedPtr& posbuf) = 0;

        /** Get a shared index buffer for a given number of settings.
        @remarks
        Since all index structures are the same at the same LOD level and
        relative position, we can share index buffers. Therefore the 
        buffer returned from this method does not need to be 'freed' like
        the vertex buffers since it is never owned.
        @param batchSize The batch size along one edge
        */
        virtual HardwareIndexBufferSharedPtr getSharedIndexBuffer(U16 batchSize) = 0;

        /// Free any buffers we're holding
        virtual void freeAllBuffers() = 0;

    };


    /// Standard implementation of a buffer allocator which re-uses buffers
    class DefaultTerrainTilesGpuBufferAllocator : public GpuBufferAllocator
    {
    public:
        DefaultTerrainTilesGpuBufferAllocator();
        ~DefaultTerrainTilesGpuBufferAllocator();

        void allocateVertexBuffers(UInt sizeVertex, UInt numVertices, HardwareVertexBufferSharedPtr& destPos);

        void freeVertexBuffers(const HardwareVertexBufferSharedPtr& posbuf);

        HardwareIndexBufferSharedPtr getSharedIndexBuffer(U16 batchSize);
        void    populateIndexBuffer( HardwareIndexBufferSharedPtr& indexPtr, U16 batchSize );

        void freeAllBuffers();

    protected:

        typedef Ogre::list<HardwareVertexBufferSharedPtr>::type VBufList;
        VBufList mFreePosBufList;
        typedef Ogre::map<UInt, HardwareIndexBufferSharedPtr>::type IBufMap;
        IBufMap mSharedIBufMap;

        UInt hashIndexBuffer(U16 batchSize);
        HardwareVertexBufferSharedPtr getVertexBuffer(VBufList& list, UInt vertexSize, UInt numVertices);

    };

}

/******************************************************************************/

#endif
