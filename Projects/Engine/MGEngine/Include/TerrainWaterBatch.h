/******************************************************************************/
#ifndef _TERRAINGROUNDBATCH_H_
#define _TERRAINGROUNDBATCH_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "TerrainBatch.h"

/******************************************************************************/
namespace MG
{

    //��������������������������������������������������������������������������������������������������
    //��������������������������������������������������������������������������������������������������

    /******************************************************************************/
    //�ؿ��еĵ�����Ⱦ����
    /******************************************************************************/
    class TerrainWaterBatch : public TerrainBatch
    {
    public:
        TerrainWaterBatch( Scene* scene, TerrainTileRender* tileRender, TerrainBatch* parent, 
            const AxisAlignedBox& aabb, Ogre::Rect vertexRectInTile,
            MovableObject* movableObject );
        virtual ~TerrainWaterBatch();

    public:

        // ���غ�ж����Դ
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