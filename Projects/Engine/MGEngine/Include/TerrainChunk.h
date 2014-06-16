/******************************************************************************/
#ifndef _TERRAINCHUNK_H_
#define _TERRAINCHUNK_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "ITerrain.h"
#include "TerrainGroundSurface.h"
#include "TerrainRegion.h"


/******************************************************************************/
namespace MG
{

	/******************************************************************************/
	//TerrainChunk
	/******************************************************************************/
    class TerrainChunk : public ITerrainChunk
	{
        friend class Scene;
	public:

        TerrainChunk(TerrainManager* mgr, Scene* scene, Vec2 indexPos, Vec2 worldCenterPos, TerrainChunkDeclare& decl);
		virtual ~TerrainChunk();

        ////////////////////////////////////////////////////////////////////////////////////

        /// 更新地形
        void                            update( Flt delta );

        /// 加载地形数据
        void                            load(Str path);
        /// 保存地形数据
        void                            save(Str path);
        /// 清空地形数据
        void                            unLoad();

		/////// 重排序并保存贴图图层数据
		void                            _reorderTextureLayer(const Str &path);

        // 得到Chunk定义
        const TerrainChunkDeclare&      getTerrainChunkConfig(){ return mChunkDecl;};

        ////////////////////////////////////////////////////////////////////////////////////

        /// 得到地形组索引
        Vec2&                           getTerrainGroupIndex(){ return mTerrainGroupIndex;};
        /// 得到中心点坐标
        Vec2&                           getWorldCenterPos(){ return mWorldCenterPos; };
        /// 得到碰撞盒
        AxisAlignedBox&                 getBoundingBox(){return mBoundingBox;};
        /// 得到碰撞区域
        Ogre::Rect&                     getBoundingRect(){return mBoundingRect;};

        /// 生成碰撞盒
        void                            generateBoundingShape();
        
        /// 得到地表对象
        virtual TerrainSurface*         getTerrainSurface( TerrainSurfaceType type );

        /// 得到地表面对象
        virtual TerrainGroundSurface*   getTerrainGroundSurface() { return mTerrainGroundSurface; } ;
        /// 得到水对象
        virtual TerrainWaterSurface*    getTerrainWaterSurface() { return mTerrainWaterSurface; } ;
        /// 得到区域管理对象
        virtual TerrainChunkRegions*    getTerrainRegion(){ return mTerrainRegion; };

		////////////////////////////////////////////////////////////////////////////////////

	public:
        /// 得到名字
        Str&                            getName(){ return mName; };
        /// 得到资源目录名
        Str&                            getDirectionName(){ return mDirectionName; };


        ////////////////////////////////////////////////////////////////////////////////////

    private:

        /// 所属地形组对象.
        TerrainManager* mOwner;
        /// 所属场景对象.
        Scene* mScene;
        // 名字
        Str mName;
        // 文件夹名字
        Str mDirectionName;
        // 资源目录
        Str mResourcePath;
        // 碰撞盒
        AxisAlignedBox mBoundingBox;
        Ogre::Rect  mBoundingRect;

        ///////////////////////////////////////////////////////////////////////////////

        TerrainChunkDeclare mChunkDecl;
        
        ///////////////////////////////////////////////////////////////////////////////
        
        /// 地表
        TerrainGroundSurface*   mTerrainGroundSurface;
        /// 水表
        TerrainWaterSurface*   mTerrainWaterSurface;
       
        /// 地形区域
        TerrainChunkRegions* mTerrainRegion;

        ///////////////////////////////////////////////////////////////////////////////
        
        Vec2 mTerrainGroupIndex;
        Vec2 mWorldCenterPos;


		///////////////////////////////////////////////////////////////////////////////
	};

}

/******************************************************************************/

#endif
