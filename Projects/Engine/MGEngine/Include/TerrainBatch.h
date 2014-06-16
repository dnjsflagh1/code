/******************************************************************************/
#ifndef _TERRAINBATCH_H_
#define _TERRAINBATCH_H_
/******************************************************************************/

#include "EnginePreqs.h"

/******************************************************************************/
namespace MG
{

    //��������������������������������������������������������������������������������������������������
    //��������������������������������������������������������������������������������������������������

    /******************************************************************************/
    //�ؿ��еĵ�����Ⱦ����
    /******************************************************************************/
    class TerrainBatch
    {
    public:
        TerrainBatch( Scene* scene, TerrainTileRender* tileRender, TerrainBatch* parent, 
            const AxisAlignedBox& aabb, Ogre::Rect vertexRectInTile,
            MovableObject* movableObject );
        virtual ~TerrainBatch();

    public:


        // ���غ�ж����Դ
        virtual void                    load();
        virtual void                    unLoad();
        /// �豸����
        virtual void                    reset();

        void                            setRenderEnable( bool enable );
        Bool                            getRenderEnable(){return mRenderEnable;};
        
        // ������Ⱦ�ɼ�״̬
        void                            updateVisible( AxisAlignedBox& visibleAAbb );

        // ���Ӻͷ�����Ⱦ����
        virtual void                    addRenderable(RenderQueue* queue);
        virtual void                    visitRenderables(Renderable::Visitor* visitor);

        // �Ƿ����Ⱦ����Ч����
        virtual Bool                    isValidRenderableDistance(Ogre::Camera* cam) ;

        /*########################################
        //       Batch ����     
        #########################################*/

    protected:

        // �������������δ��������ζ���
        void                            loadChilds();
        void                            unLoadChilds();


        /*########################################
        //      GPU�������ݲ���          
        #########################################*/

    public:

        // ˢ�¶���
        void                            updateVertexData( const Ogre::Rect& vertexRectInTile );

    protected:

        // ���������ٶ����������Դ
        void                            createGpuVertexData();
        void                            destroyGpuVertexData();
        // ���ٶ����̨�������ݣ����ٺͲ��������������޸��ڴ棬���ǿ�����Ⱦ
        void                            destroyGpuVertexBackupData();
        // ��ⶥ���̨��������
        void                            checkAndUpdateGpuVertexBackupData();

        void                            createGpuIndexData();
        void                            destroyGpuIndexData();
        // ����������̨�������ݣ����ٺͲ��������������޸��ڴ棬���ǿ�����Ⱦ
        void                            destroyGpuIndexBackupData();
        // ���������̨��������
        void                            checkAndUpdateGpuIndexBackupData();

        void                            populateIndexData();


    public:

        static UInt                     getNumIndexesForBatchSize(U16 batchSize);
        /** Utility method to populate a (locked) index buffer.
        @param pIndexes Pointer to an index buffer to populate
        @param batchSize The number of vertices down one side of the batch
        */
        static void                     populateIndexBuffer(uint32* pI, U16 batchSize);


        /*########################################
        //      ��Ⱦʵ��
        #########################################*/

    protected:

        void                            loadRenderableObject();
        void                            unLoadRenderableObject();

    public:

        /// Get the material being used for the terrain
        virtual MaterialPtr&            getOrGenerateMaterialPtr() =0;


    public:

        /// ���ε�������Ⱦʵ��
        class Rend : public Renderable, public GeneralAllocatedObject
        {
        protected:
            TerrainTileRender*  mTileRender;
            MovableObject*      mMovableObject;
            Vector3             mCenterPos;
            TerrainBatch*       mBatch;
            IDisplay*           mDisplay;
        public:
            Rend(TerrainTileRender* tileRender, TerrainBatch* batch, MovableObject* movableObject, Vector3 centerPos);
            virtual ~Rend();

            virtual const MaterialPtr&  getMaterial(void) const;
            virtual Technique*          getTechnique(void) const;
            virtual void                getRenderOperation(RenderOperation& op);
            virtual void                getWorldTransforms(Matrix4* xform) const;
            virtual Real                getSquaredViewDepth(const Ogre::Camera* cam) const;
            virtual const LightList&    getLights(void) const;
            virtual bool                getCastsShadows(void) const;
        };

        friend class Rend;

    protected:

        ///////////////////////////////////////////////////////////////////////////////

        Scene*                  mScene;    
        TerrainManager*         mTerrainManager;
        TerrainSurfaceManager*  mSurfaceManager;
        TerrainChunk*           mTerrainChunk;
        TerrainTileRender*      mTileRender;
        TerrainBatch*           mParent;

        MovableObject*          mMovableObject;
        Rend*                   mRender;

        Bool                    mIsLoaded;
        Bool                    mIsVisible;

        ///////////////////////////////////////////////////////////////////////////////

        AxisAlignedBox          mBoundingBox;
        AxisAlignedBox          mNodeBoundingBox;
        Ogre::Rect              mVertexRectInTile;
         
        //////////////////////////////////////////////////////////////////////

        Ogre::VertexData*       mGpuVertexData;
        Ogre::IndexData*        mGpuIndexData;

        UInt                    mOneVertexSize;         //��������ռ�û����С
        UInt                    mVertexSideNum;
        UInt                    mVertexTotalNum;
                        
        //////////////////////////////////////////////////////////////////////

        Bool                    mRenderEnable;
        

    };



}


/******************************************************************************/

#endif