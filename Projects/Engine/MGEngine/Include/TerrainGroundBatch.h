/******************************************************************************/
#ifndef _TERRAINGROUNDBATCH_H_
#define _TERRAINGROUNDBATCH_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "TerrainBatch.h"
#include "TerrainTilesLayerBlendMap.h"
#include "TerrainTilesMaterial.h"
#include "TerrainTilesGpu.h"


/******************************************************************************/
namespace MG
{

    //��������������������������������������������������������������������������������������������������
    //��������������������������������������������������������������������������������������������������

    /******************************************************************************/
    //�ؿ��еĵ�����Ⱦ����
    /******************************************************************************/
    class TerrainGroundBatch : public TerrainBatch
    {
    public:
        TerrainGroundBatch( Scene* scene, TerrainTileRender* tileRender, TerrainBatch* parent, 
            const AxisAlignedBox& aabb, Ogre::Rect vertexRectInTile,
            MovableObject* movableObject );
        virtual ~TerrainGroundBatch();

    public:

        // ���غ�ж����Դ
        virtual void                    load();
        virtual void                    unLoad();

        /// Get the material being used for the terrain
        virtual MaterialPtr&            getOrGenerateMaterialPtr();
    };



}


/******************************************************************************/

#endif