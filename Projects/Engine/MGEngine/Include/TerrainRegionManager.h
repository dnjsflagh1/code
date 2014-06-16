/******************************************************************************/
#ifndef _TERRAINREGIONMANAGER_H_
#define _TERRAINREGIONMANAGER_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "MGGrid.h"
#include "ITerrain.h"

/******************************************************************************/
namespace MG
{
   

    /******************************************************************************/
    //游戏地形网格管理
    /******************************************************************************/
    class TerrainRegionManager : public ITerrainRegionManager
    {
    public:
        TerrainRegionManager(TerrainManager* mgr, Scene* scene);
        virtual ~TerrainRegionManager();


        ////////////////////////////////////////////////////////////////////////

        void                            clear();

        ////////////////////////////////////////////////////////////////////////

        // 创建区域
        TerrainChunkRegions*            createTerrainChunkRegions(TerrainChunk* chunk);
        // 删除区域
        void                            destroyTerrainChunkRegions(TerrainChunkRegions* regions);
        
        ////////////////////////////////////////////////////////////////////////

        void                            setBlockRegionVisible(Bool visible);
        Bool                            getBlockRegionVisible();

        void                            setCustomRegionVisible( Int index, Bool visible );
        Int                             getVisibledCustomRegionIndex();
        CustomRegionDeclaration*        getVisibledCustomRegion();

        ////////////////////////////////////////////////////////////////////////

        void                            clearCustomRegion();
        void                            addCustomRegion();
        void                            removeCustomRegion( Int index );
        Int                             getCustomRegionCount();
        CustomRegionDeclaration*        getCustomRegionDeclaration( UInt index );

        ////////////////////////////////////////////////////////////////////////

        /// 刷新区域显示
        void                            applyRegionVisible();

    protected:

        // 地形管理对象
        TerrainManager* mOwner;
        // 创建管理
        Scene*          mScene;

        // 是否障碍区域显示
        Bool            mBlockRegionVisible;

        // 自定义区域描述列表
        std::vector<CustomRegionDeclaration> mTerrainCustomRegionsDecl;
        
        // 地形快区域管理对象列表
        std::list<TerrainChunkRegions*> mTerrainChunkRegionsList;
    };

}

/******************************************************************************/

#endif
