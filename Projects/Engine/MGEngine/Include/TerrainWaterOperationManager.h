/******************************************************************************/
#ifndef _TERRAINWATEROPERATIONMANAGER_H_
#define _TERRAINWATEROPERATIONMANAGER_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "ITerrainWaterOperationManager.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //��Ϸˮ��ʾ
    /******************************************************************************/
    class TerrainWaterShowOperationManager : public ITerrainWaterShowOperationManager
    {
    public:
        SINGLETON_INSTANCE(TerrainWaterShowOperationManager)
        TerrainWaterShowOperationManager();
        virtual ~TerrainWaterShowOperationManager();

        ///�õ�ˮ����
        virtual U32     getWaterGroupID();
        ///����ˮ����
        virtual void    setWaterGroupID(U32 id) ;

        ///����һ������
        virtual IEditorOperation*       createOneOperation();

    protected:

        U32 mGroupID;

    };

    /******************************************************************************/
    //��Ϸˮ����
    /******************************************************************************/
    class TerrainWaterHideOperationManager : public ITerrainWaterHideOperationManager
    {
    public:
        SINGLETON_INSTANCE(TerrainWaterHideOperationManager)
        TerrainWaterHideOperationManager();
        virtual ~TerrainWaterHideOperationManager();

        ///����һ������
        virtual IEditorOperation*       createOneOperation();

    protected:

    };

    
}

/******************************************************************************/

#endif

