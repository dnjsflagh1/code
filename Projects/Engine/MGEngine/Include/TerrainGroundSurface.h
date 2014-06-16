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

    //��������������������������������������������������������������������������������������������������
    //��������������������������������������������������������������������������������������������������

    
    /******************************************************************************/
    /*
        @remarks:
            ÿ����ͼ��Ӧһ��TerrainTilesLayerBlendMap����
            ÿ�Ĳ���ͼ(�Լ�TerrainTilesLayerBlendMap)ͨ��һ�ŵ�ɫ����ͼ(BlendTexture)��ϡ�
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
        virtual void                refreshColors(const Rect& rect){};

        /*########################################
        //          ��Ӱ��Ϣ
        #########################################*/

        /// ���ع�Ӱ������
        void                        loadLightMapData( Str& path );

        /// �����Ӱ������
        void                        saveLightMapData( Str& path ) ;

        /*########################################
        //          ��ͼ��ͻ�ϲ����         
        #########################################*/

		/// �����򲢱����ϲ�����
		virtual void                _reorderColorTextureLayerData( const Str& terrPath );

    protected:

        /// ���ػ�ϲ�����
        void                        loadColorTextureLayerData( Str path );
        /// ж�ػ�ϲ�����
        void                        unLoadColorTextureLayerData();
        /// �����ϲ�����
        void                        saveColorTextureLayerData( Str terrPath );

        ////////////////////////////////////////////////////////////////////////////////

        void                        loadTileTextureIndexMap( Str& path );
        void                        unLoadTileTextureIndexMap();
        void                        saveTileTextureIndexMap( Str& path );

		//��������Tile����(�˺����������Զ��ü���ͼǰ����������ͼ����)
		void                        _reorderTileTextureIndexMap( const Str& path );
		//��������BlendMapTex��ͼ��(�˺����������Զ��ü���ͼǰ��������blendMap)
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
        //          ������ʾ���ݲ���       
        #########################################*/

    private:

        /// ����������ʾ����
        void                        loadRegionDisplayData( Str& path );
        /// ж��������ʾ����
        void                        unLoadRegionDisplayData();

    public:

        // �����Ƿ���ʾ
        void                        setRegionDisplay(Int x, Int y, bool isDisplay,bool isDirty=true);

    protected:

        /// ��������
        void                        updateRegionDisplayData();

    public:

        /// �õ�������ʾ����
        TexturePtr                  getRegionDisplayTexture() const;
        /// ���������ʾ����
        void                        clearRegionDisplayData();

        /// �õ�������ʾ����
        bool*                       getRegionDisplayData();
        /// �õ�������ʾ����    
        void                        setRegionDisplayDirty( Box& dirtyBox );

        //**********************************************************************************************************************
        //**********************************************************************************************************************

    protected:

        typedef std::vector<TexturePtr> TexturePtrList;

    protected:

        //################# ��ɫ�� ###############

        uint16 mTextureIndexMapSize;
        uint16 mTextureIndexMapSizeActual;

        //################# ��ϲ� ###############

        uint16  mBlendMapSizeInTile;
        uint16  mLayerBlendMapSize;
        uint16  mLayerBlendMapSizeActual;

        //################# ������ͼ���� ###############

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
