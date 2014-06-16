/******************************************************************************/
#ifndef _TERRAINGROUNDBATCH_H_
#define _TERRAINGROUNDBATCH_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "TerrainBatch.h"

/******************************************************************************/
namespace MG
{

    //×××××××××××××××××××××××××××××××××××××××××××××××××
    //×××××××××××××××××××××××××××××××××××××××××××××××××

    /******************************************************************************/
    //地块中的单次渲染管理
    /******************************************************************************/
    class TerrainWaterBatch : public TerrainBatch
    {
    public:
        TerrainWaterBatch( Scene* scene, TerrainTileRender* tileRender, TerrainBatch* parent, 
            const AxisAlignedBox& aabb, Ogre::Rect vertexRectInTile,
            MovableObject* movableObject );
        virtual ~TerrainWaterBatch();

    public:

        // 加载和卸载资源
        virtual void                    load();
        virtual void                    unLoad();

        
        void                            setMaterialGroupID( U32 id );
        U32                             getMaterialGroupID(){return mMaterialGroupID;};


        virtual MaterialPtr&            getOrGenerateMaterialPtr();

    private:

        U32 mMaterialGroupID;
    };



}


/******************************************************************************/

#endif