/******************************************************************************/
#ifndef _TERRAINBLOCKOPERATION_H_
#define _TERRAINBLOCKOPERATION_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "EditorOperation.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //��Ϸ�����ϰ�����
    /******************************************************************************/
    class TerrainRegionOperation : public EditorOperation
    {
    public:
        TerrainRegionOperation();
        virtual ~TerrainRegionOperation();

        //��Ӧһ�β���
        virtual void    execute( TerrainChunk* chunk, Ogre::Rect& rect );
        //����һ�β���
        virtual void    rollback();

        //Ӱ���ϰ�����
        virtual void    influenceRegionMap(TerrainGroundSurface* tilesMgr, TerrainRegion* blockRegion, Int x, Int y) {};
    };

    /******************************************************************************/
    //��Ϸ�������Ӿ��ϰ�����
    /******************************************************************************/
    class TerrainAddRegionOperation : public TerrainRegionOperation
    {
    public:
        TerrainAddRegionOperation();
        virtual ~TerrainAddRegionOperation();

        //Ӱ���ϰ�����
        virtual void    influenceRegionMap(TerrainGroundSurface* tilesMgr, TerrainRegion* blockRegion, Int x, Int y) ;
    };

    /******************************************************************************/
    //��Ϸ�����Ƴ��ϰ�����
    /******************************************************************************/
    class TerrainRemoveRegionOperation : public TerrainRegionOperation
    {
    public:
        TerrainRemoveRegionOperation();
        virtual ~TerrainRemoveRegionOperation();

        //Ӱ���ϰ�����
        virtual void    influenceRegionMap(TerrainGroundSurface* surface, TerrainRegion* region, Int x, Int y) ;
    };


}

/******************************************************************************/

#endif

