/******************************************************************************/
#ifndef _TERRAINREGION_H_
#define _TERRAINREGION_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "MGGrid.h"
#include "ITerrain.h"

/******************************************************************************/
namespace MG
{
    
    /******************************************************************************/
    //障碍区域类型
    /******************************************************************************/
    enum TerrainBlockRegionType
    {
        TBR_BLOCK_NULL      = BIT(0),
        TBR_BLOCK_BASE      = BIT(5),
        TBR_BLOCK_STATIC    = BIT(6),
    };

    /******************************************************************************/
    //障碍区域类型
    /******************************************************************************/
    enum TerrainCustomRegionType
    {
        TCR_CUSTOM_NULL     = BIT(0),
        TCR_CUSTOM_1        = BIT(1),
        TCR_CUSTOM_2        = BIT(2),
        TCR_CUSTOM_3        = BIT(3),
        TCR_CUSTOM_4        = BIT(4),
        TCR_CUSTOM_5        = BIT(5),
        TCR_CUSTOM_6        = BIT(6),
    };

    //××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××
    //××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××

    //@{
#pragma pack( push )
#pragma pack( 1 )

    /******************************************************************************/
    //一个区域网格的数据
    /******************************************************************************/
    struct TerrainRegionGridData
    {
        Byte mask;
    };
#pragma pack (pop)
    //@}

    /******************************************************************************/
    //一个区域对象
    /******************************************************************************/
    class TerrainRegion : public GridManager<TerrainRegionGridData>
    {
    public:
        TerrainRegion(){};
        virtual ~TerrainRegion(){};
    };


    //××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××
    //××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××


    /******************************************************************************/
    //游戏Chunk内的区域管理
    /******************************************************************************/
    class TerrainChunkRegions : public ITerrainChunkRegions
    {
    public:
        TerrainChunkRegions(TerrainManager* terrainMgr, Scene* scene, TerrainChunk* chunk);
        virtual ~TerrainChunkRegions();

        ////////////////////////////////////////////////////////////////////////

        void                            load(Str path);
        void                            unLoad();
        void                            save(Str path);

        ////////////////////////////////////////////////////////////////////////

        void                            loadCustomData( Str path );
        void                            unLoadCustomData();
        void                            saveCustomData( Str path );

        void                            loadBlockData( Str path );
        void                            unLoadBlockData();
        void                            saveBlockData( Str path );

        ////////////////////////////////////////////////////////////////////////

        void                            clearCustomRegion();
        void                            addCustomRegion();
        void                            removeCustomRegion( Int index );
        TerrainRegion*                  getCustomRegion( Int index );
        TerrainRegion*                  getVisibledCustomRegion();

        TerrainRegion*                  getTerrainBlockBaseRegion() { return mBlockBaseRegion ;};
        TerrainRegion*                  getTerrainBlockStaticRegion() { return mBlockStaticRegion ;};

        ////////////////////////////////////////////////////////////////////////

        void                            applyRegionVisible();

    private:
        
        ////////////////////////////////////////////////////////////////////////

        TerrainRegionManager*   mOwner;
        TerrainManager*         mTerrainMgr;
        Scene*                  mScene;
        TerrainChunk*           mChunk;

        ////////////////////////////////////////////////////////////////////////

        // 障碍
        TerrainRegion*          mBlockBaseRegion;
        TerrainRegion*          mBlockStaticRegion;

        ////////////////////////////////////////////////////////////////////////

        // 自定义区域列表
        std::vector<TerrainRegion*> mTerrainCustomRegions;
    };

}

/******************************************************************************/

#endif
