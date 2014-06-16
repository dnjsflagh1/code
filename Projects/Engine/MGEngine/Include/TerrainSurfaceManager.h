/******************************************************************************/
#ifndef _TERRAINSURFACEMANAGER_H_
#define _TERRAINSURFACEMANAGER_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "ITerrain.h"
#include "TerrainTilesGpu.h"


/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    /** ������ͼ��
    /******************************************************************************/
    struct GlobleTerrainTextureLayer
    {
        Bool usedDirty;
        TerrainTextureLayerDeclaration* decl;
        GlobleTerrainTextureLayer()
            :usedDirty(true)
            ,decl(NULL)
        {
            
        }
    };

    /******************************************************************************/
    /** ��Ϸ��ò�ؿ���Ⱦ����
    // TerrainSurfaceManager
    /******************************************************************************/
    class TerrainSurfaceManager : public ITerrainSurfaceManager
    {
    public:
        TerrainSurfaceManager(TerrainManager* mgr, Scene* scene);
        virtual ~TerrainSurfaceManager();


        //////////////////////////////////////////////////
        void                                update( Flt delta );
        //////////////////////////////////////////////////
       
        /// ȫ����ͼ����
        void                                clearGlobleTextureLayer();
        void                                addGlobleTextureLayer(Int index, Str name);
        void                                addGlobleTextureLayer(Str name);
        Bool                                hasGlobleTextureLayer(Str name);
        Int                                 getGlobleTextureLayerMaxCount();
        TerrainTextureLayerDeclaration*     getGlobleTextureLayer( Int index );
        void                                clearGlobleTextureLayerUsedDirty();                        
        void                                cleanNoUsedGlobleTextureLayer();  
        
        // �������α���
        TerrainBBGroundSurface*             createTerrainBBGroundSurface(TerrainChunk* chunk);
        // �������α���
        TerrainSBGroundSurface*             createTerrainSBGroundSurface(TerrainChunk* chunk);

        // ɾ�����α���
        void                                destroyTerrainGroundSurface(TerrainGroundSurface* surface);

        // ����ˮ����
        TerrainWaterSurface*                createTerrainWaterSurface(TerrainChunk* chunk);
        // ɾ�����α���
        void                                destroyTerrainWaterSurface(TerrainWaterSurface* surface);


        // �õ�GPU��������
        DefaultTerrainTilesGpuBufferAllocator&
            getDefaultTerrainTilesGpuBufferAllocator(){return mCustomGpuBufferAllocator;};

        ///////////////////////////////////////////////////////////////////////////////////////////////

        Int                                 getGlobleWaterGroupMaxCount();
        TerrainWaterGroupDeclaration*       getGlobleWaterGroupByIndex( UInt index );
        TerrainWaterGroupDeclaration*       getGlobleWaterGroup( U32 groupID );
        TerrainWaterGroupDeclaration*       addGlobleWaterGroup( U32 groupID );
        void                                clearGlobleWaterGroups();  

        // �õ�Water GPU��������
        TerrainWaterMaterial*               getTerrainWaterMaterial(){return mTerrainWaterMaterial;};
        
    private:

        /// �������������.
        TerrainManager* mOwner;
        /// ������������.
        Scene* mScene;

        /// ������ͼ�б�
        std::map<Int, GlobleTerrainTextureLayer> mGlobleTerrainTextureLayerList;

        /// ����ˮ�б�
        std::map<Int, TerrainWaterGroupDeclaration> mGlobleTerrainWaterGroupList;

        ///Gpu�������
        DefaultTerrainTilesGpuBufferAllocator mCustomGpuBufferAllocator;

        TerrainWaterMaterial*    mTerrainWaterMaterial;
    };

}

/******************************************************************************/

#endif
