/******************************************************************************/
#ifndef _TERRAINTILES_H_
#define _TERRAINTILES_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "MGGrid.h"

/******************************************************************************/
namespace MG
{

    //��������������������������������������������������������������������������������������������������
    //��������������������������������������������������������������������������������������������������

    //@{
#pragma pack( push )
#pragma pack( 1 )
    /******************************************************************************/
    //һ���ؿ�
    /******************************************************************************/
    struct TerrainTile
    {
        // ��Ⱦ�ؿ���Surface�е���������
        Flt worldCenterPosX, worldCenterPosZ;
        // ��Ⱦ�ؿ���Surface�еİ뾶
        Flt radius;

        // ��Ⱦ�ؿ�Ķ�����Surface�е�����
        Ogre::Rect vertexRectInSurface;

        // ��Ⱦ��
        TerrainTileRender* render;
    };

    /******************************************************************************/
    //һ���ؿ�����
    /******************************************************************************/
    struct TerrainBatchGrid
    {
        TerrainBatch* batch;
    };

#pragma pack (pop)
    //@}


    //��������������������������������������������������������������������������������������������������
    //��������������������������������������������������������������������������������������������������

    /******************************************************************************/
    //�ؿ��еĵ�����Ⱦ����
    /******************************************************************************/
    class TerrainTileRender : public GridManager<TerrainBatchGrid>
    {
        friend class TerrainBatch;
    public:

        TerrainTileRender( TerrainManager* mgr, TerrainChunk* chunk, 
            TerrainSurface* surface, TerrainNode* node, TerrainTile* tile, UInt index );

        virtual ~TerrainTileRender();

    public:

        //**********************************************************************************************************************
        //**********************************************************************************************************************

        virtual void                    update( Flt delta ) ;
        
        virtual void                    load( ) ;
        virtual void                    unload( ) ;
        /// �豸����
        virtual void                    reset();

        TerrainSurface*                 getTerrainSurface() { return mTerrainSurface; };
        TerrainChunk*                   getTerrainChunk() { return mTerrainChunk; };
        TerrainManager*                 getTerrainManager() { return mTerrainMgr; };
        

        // ����դ��
        virtual void                    createGrids();
        /// ����դ��
        virtual void                    createGrids(Int gridsSideNum, Flt gridSize,  Vec2 centerPos);
        /// ����դ��
        virtual void                    destroyGrids();

        const Ogre::Rect&               getWorldBoundingRect(void){ return mWorldBoundingRect; };

        //**********************************************************************************************************************
        //**********************************************************************************************************************

    public:

        /*########################################
        //     ���δ������
        #########################################*/

        // ���غ�ж�����δ������
        void                            loadRootBatch();
        void                            resetRootBatch();
        void                            unLoadRootBatch();
        
        // �����������ζ���
        virtual TerrainBatch*           createTerrainBatch( Scene* scene, TerrainTileRender* tileRender, TerrainBatch* parent, 
            const AxisAlignedBox& aabb, Ogre::Rect vertexRectInTile, MovableObject* movableObject) = 0;


        /*########################################
        //      CPU�������ݲ���          
        #########################################*/

    public:

        void                            loadRenderData();
        void                            unLoadRenderData();

    protected:

        // ���������ٶ�������
        void                            createCpuVertexData();
        void                            destroyCpuVertexData();

        // ��ʼ����������
        void                            initializeVertexBuffer();

    public:

        // �õ���������
        UInt                            getOneVertexSize(){ return mOneVertexSize; };
        UInt                            getVertexSideSize(){ return mVertexSideNum; };
        UInt                            getVertexTotalSize(){ return mVertexTotalNum; };

    public:

        // �õ���������
        Ogre::VertexData*               getCpuVertexData(){ return mCpuVertexData; };
        // ���¶���λ��
        void                            updateVertex(const Ogre::Rect& vertexRectInSurface);

       
        /*########################################
        //      ���ʹ���
        #########################################*/

    public:

        /// Ӧ����ʾ�����޸�
        virtual void                    applyRenderConfig(){};

//**********************************************************************************************************************
//**********************************************************************************************************************

    protected:

        ///////////////////////////////////////////////////////////////////////////////
        
        // �������

        TerrainManager* mTerrainMgr;
        TerrainSurface* mTerrainSurface;
        TerrainChunk*   mTerrainChunk;
        TerrainNode*    mTerrainNode;
        TerrainTile*    mOwner;
        UInt            mIndex;

        Ogre::Rect      mWorldBoundingRect;

        ///////////////////////////////////////////////////////////////////////////////

        // ������Ϣ
        Ogre::VertexData* mCpuVertexData;
        UInt    mOneVertexSize;
        UInt    mVertexSideNum;
        UInt    mVertexTotalNum;

    public:

        static unsigned short POSITION_BUFFER;

        ///////////////////////////////////////////////////////////////////////////////
        
    };


    
}

/******************************************************************************/

#endif
