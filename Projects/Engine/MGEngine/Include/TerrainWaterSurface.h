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

    //��������������������������������������������������������������������������������������������������
    //��������������������������������������������������������������������������������������������������


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
        //                  ������        
        #########################################*/

        virtual TerrainSurfaceType  getType() ;
        virtual SceneObjectTypes    getSceneObjectTypes() ;
        virtual UInt                getSceneVisibleFlags() ;
        // �õ���Ⱦ����
        virtual uint8               getRenderQueueGroup();

        /// ����ѡ��
        virtual void                configOptions();
        /// �������� 
        virtual void                load( Str path );
        /// �豸����
        virtual void                reset();
        /// ж������
        virtual void                unLoad();
        /// ��������
        virtual void                save( Str path );
        /// ����
        virtual void                update(Flt delta, bool synchronous = false);

        // �����ֿ���Ⱦ��
        virtual TerrainTileRender*  createTerrainTileRender( TerrainManager* mgr, TerrainChunk* chunk, 
                                        TerrainNode* node, TerrainTile* tile, UInt index );

        /// ���¶���
        virtual void                updateGeometry( Ogre::Rect rect );


        /// ������������
        virtual void                loadGridData();
        /// ж����������
        virtual void                unLoadGridData();

        /*########################################
        //          �߶���Ϣ
        #########################################*/

        /// ���ظ߶�����
        virtual void                loadHeightData( Str path );
        /// ����߶�����
        virtual void                saveHeightData( Str path );

        /*########################################
        //          ������Ϣ
        #########################################*/

        /// ���ط��߲�����
        virtual void                loadNormalTangentMapData( Str path );
        /// ���淨�߲�����
        virtual void                saveNormalTangentMapData( Str path );


        /*########################################
        //          ��ɫ��Ϣ
        #########################################*/

        /// ������ɫ������
        virtual void                loadColorMapData( Str path );
        /// ������ɫ������
        virtual void                saveColorMapData( Str path );

        /// ˢ����ɫ����
        virtual void                refreshColors(const Rect& rect);

        /*########################################
        //          ��Ӱ��Ϣ
        #########################################*/

        /// ���ع�Ӱ������
        void                        loadLightMapData( Str& path );

        /// �����Ӱ������
        void                        saveLightMapData( Str& path ) ;


        /*########################################
        //          ����������         
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
