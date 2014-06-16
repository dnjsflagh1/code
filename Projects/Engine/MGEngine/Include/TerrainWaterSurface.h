/******************************************************************************/
#ifndef _TERRAINWATERSURFACE_H_
#define _TERRAINWATERSURFACE_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "ITerrain.h"
#include "MGGrid.h"
#include "TerrainTiles.h"
#include "TerrainSurface.h"

/******************************************************************************/
namespace MG
{

    //×××××××××××××××××××××××××××××××××××××××××××××××××
    //×××××××××××××××××××××××××××××××××××××××××××××××××


    /******************************************************************************/
    /*
    */
    /******************************************************************************/
    class TerrainWaterSurface : public ITerrainWaterSurface, public TerrainSurface
    {
    public:
        TerrainWaterSurface(TerrainManager* terrainMgr, Scene* scene, TerrainChunk* chunk);
        virtual ~TerrainWaterSurface();

        /*########################################
        //                  主方法        
        #########################################*/

        virtual TerrainSurfaceType  getType() ;
        virtual SceneObjectTypes    getSceneObjectTypes() ;
        virtual UInt                getSceneVisibleFlags() ;
        // 得到渲染队列
        virtual uint8               getRenderQueueGroup();

        /// 配置选项
        virtual void                configOptions();
        /// 加载数据 
        virtual void                load( Str path );
        /// 设备重置
        virtual void                reset();
        /// 卸载数据
        virtual void                unLoad();
        /// 保存数据
        virtual void                save( Str path );
        /// 更新
        virtual void                update(Flt delta, bool synchronous = false);

        // 创建分块渲染者
        virtual TerrainTileRender*  createTerrainTileRender( TerrainManager* mgr, TerrainChunk* chunk, 
                                        TerrainNode* node, TerrainTile* tile, UInt index );

        /// 更新顶点
        virtual void                updateGeometry( Ogre::Rect rect );


        /// 加载网格数据
        virtual void                loadGridData();
        /// 卸载网格数据
        virtual void                unLoadGridData();

        /*########################################
        //          高度信息
        #########################################*/

        /// 加载高度数据
        virtual void                loadHeightData( Str path );
        /// 保存高度数据
        virtual void                saveHeightData( Str path );

        /*########################################
        //          法线信息
        #########################################*/

        /// 加载法线层数据
        virtual void                loadNormalTangentMapData( Str path );
        /// 保存法线层数据
        virtual void                saveNormalTangentMapData( Str path );


        /*########################################
        //          颜色信息
        #########################################*/

        /// 加载颜色层数据
        virtual void                loadColorMapData( Str path );
        /// 保存颜色层数据
        virtual void                saveColorMapData( Str path );

        /// 刷新颜色数据
        virtual void                refreshColors(const Rect& rect);

        /*########################################
        //          光影信息
        #########################################*/

        /// 加载光影层数据
        void                        loadLightMapData( Str& path );

        /// 保存光影层数据
        void                        saveLightMapData( Str& path ) ;


        /*########################################
        //          材质组数据         
        #########################################*/

    protected:

        void                        loadTileGroundInfoMap( Str& path );
        void                        unLoadTileGroundInfoMap();
        void                        saveTileGroundInfoMap( Str& path );

    private:
        
        

    };

}

/******************************************************************************/

#endif
