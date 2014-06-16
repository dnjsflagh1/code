/******************************************************************************/
#ifndef _TERRAINGROUNDSURFACE_H_
#define _TERRAINGROUNDSURFACE_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "ITerrain.h"
#include "MGGrid.h"
#include "TerrainTiles.h"
#include "TerrainTilesMaterial.h"
#include "TerrainTilesLayerBlendMap.h"
#include "TerrainSurface.h"

/******************************************************************************/
namespace MG
{

    //×××××××××××××××××××××××××××××××××××××××××××××××××
    //×××××××××××××××××××××××××××××××××××××××××××××××××

    
    /******************************************************************************/
    /*
        @remarks:
            每层贴图对应一个TerrainTilesLayerBlendMap对象。
            每四层贴图(以及TerrainTilesLayerBlendMap)通过一张调色板贴图(BlendTexture)混合。
    */
    /******************************************************************************/
    class TerrainGroundSurface : public ITerrainGroundSurface, public TerrainSurface
    {
    public:
        TerrainGroundSurface(TerrainManager* terrainMgr, Scene* scene, TerrainChunk* chunk);
        virtual ~TerrainGroundSurface();

        
        //**********************************************************************************************************************
        //**********************************************************************************************************************

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
        virtual void                refreshColors(const Rect& rect){};

        /*########################################
        //          光影信息
        #########################################*/

        /// 加载光影层数据
        void                        loadLightMapData( Str& path );

        /// 保存光影层数据
        void                        saveLightMapData( Str& path ) ;

        /*########################################
        //          贴图层和混合层操作         
        #########################################*/

		/// 重排序并保存混合层数据
		virtual void                _reorderColorTextureLayerData( const Str& terrPath );

    protected:

        /// 加载混合层数据
        void                        loadColorTextureLayerData( Str path );
        /// 卸载混合层数据
        void                        unLoadColorTextureLayerData();
        /// 保存混合层数据
        void                        saveColorTextureLayerData( Str terrPath );

        ////////////////////////////////////////////////////////////////////////////////

        void                        loadTileTextureIndexMap( Str& path );
        void                        unLoadTileTextureIndexMap();
        void                        saveTileTextureIndexMap( Str& path );

		//重新排序Tile索引(此函数仅用于自动裁剪地图前从新排序贴图索引)
		void                        _reorderTileTextureIndexMap( const Str& path );
		//重新排序BlendMapTex的图层(此函数仅用于自动裁剪地图前从新排序blendMap)
		virtual void                _reorderBlendLayerMap( const Str& path ) = 0;

        ////////////////////////////////////////////////////////////////////////////////

        void                        generateTextureLayerResource();

        ////////////////////////////////////////////////////////////////////////////////

        virtual void                loadBlendLayerMap( Str& path ) = 0;
        virtual void                unLoadBlendLayerMap() = 0;
        virtual void                saveBlendLayerMap( Str& path ) = 0;

        //**********************************************************************************************************************
        //**********************************************************************************************************************


        /*########################################
        //          网格显示数据操作       
        #########################################*/

    private:

        /// 加载网格显示数据
        void                        loadRegionDisplayData( Str& path );
        /// 卸载网格显示数据
        void                        unLoadRegionDisplayData();

    public:

        // 设置是否显示
        void                        setRegionDisplay(Int x, Int y, bool isDisplay,bool isDirty=true);

    protected:

        /// 更新数据
        void                        updateRegionDisplayData();

    public:

        /// 得到网格显示数据
        TexturePtr                  getRegionDisplayTexture() const;
        /// 清空网格显示数据
        void                        clearRegionDisplayData();

        /// 得到网格显示数据
        bool*                       getRegionDisplayData();
        /// 得到网格显示数据    
        void                        setRegionDisplayDirty( Box& dirtyBox );

        //**********************************************************************************************************************
        //**********************************************************************************************************************

    protected:

        typedef std::vector<TexturePtr> TexturePtrList;

    protected:

        //################# 颜色层 ###############

        uint16 mTextureIndexMapSize;
        uint16 mTextureIndexMapSizeActual;

        //################# 混合层 ###############

        uint16  mBlendMapSizeInTile;
        uint16  mLayerBlendMapSize;
        uint16  mLayerBlendMapSizeActual;

        //################# 区域贴图参数 ###############

        TexturePtr  mTerrainRegionDisplayTexture;
        size_t      mTerrainRegionDisplayTextureSideSize;
        uint8       mTerrainRegionChannelOffset; // in pixel format

        bool*       mCpuTerrainRegionDisplayStorage;
        size_t      mCpuTerrainRegionDisplaySideNum;
        size_t      mCpuTerrainRegionDisplaySize;

        Box         mTerrainRegionDirtyBox;
        bool        mTerrainRegionDirty;

    };

}

/******************************************************************************/

#endif
