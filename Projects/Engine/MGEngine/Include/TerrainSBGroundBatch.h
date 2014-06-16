/******************************************************************************/
#ifndef _TERRAINSBGROUNDBATCH_H_
#define _TERRAINSBGROUNDBATCH_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "TerrainGroundBatch.h"
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
    class TerrainSBGroundBatch : public TerrainGroundBatch
    {
    public:

        TerrainSBGroundBatch( Scene* scene, TerrainTileRender* tileRender, TerrainBatch* parent, 
            const AxisAlignedBox& aabb, Ogre::Rect vertexRectInTile,
            MovableObject* movableObject );
        virtual ~TerrainSBGroundBatch();

    public:

        // �Ƿ����Ⱦ����Ч����
        virtual Bool                    isValidRenderableDistance(Ogre::Camera* cam);

        /// Get the material being used for the terrain
        virtual MaterialPtr&            getOrGenerateMaterialPtr();

    private:

        Vector3 mPosition;

    };



}


/******************************************************************************/

#endif