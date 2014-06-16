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
    //��Ϸ�����������
    /******************************************************************************/
    class TerrainRegionManager : public ITerrainRegionManager
    {
    public:
        TerrainRegionManager(TerrainManager* mgr, Scene* scene);
        virtual ~TerrainRegionManager();


        ////////////////////////////////////////////////////////////////////////

        void                            clear();

        ////////////////////////////////////////////////////////////////////////

        // ��������
        TerrainChunkRegions*            createTerrainChunkRegions(TerrainChunk* chunk);
        // ɾ������
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

        /// ˢ��������ʾ
        void                            applyRegionVisible();

    protected:

        // ���ι������
        TerrainManager* mOwner;
        // ��������
        Scene*          mScene;

        // �Ƿ��ϰ�������ʾ
        Bool            mBlockRegionVisible;

        // �Զ������������б�
        std::vector<CustomRegionDeclaration> mTerrainCustomRegionsDecl;
        
        // ���ο������������б�
        std::list<TerrainChunkRegions*> mTerrainChunkRegionsList;
    };

}

/******************************************************************************/

#endif
