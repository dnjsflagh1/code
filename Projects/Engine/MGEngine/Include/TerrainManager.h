/******************************************************************************/
#ifndef _TERRAINMANAGER_H_
#define _TERRAINMANAGER_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "ITerrain.h"
#include "TerrainRegionManager.h"
#include "TerrainSurfaceManager.h"
#include "TerrainChunk.h"

/******************************************************************************/
namespace MG
{

    #define TERRAIN_MAX_TEXTURE  16
    #define TERRAIN_MAX_DETAIL_TEXTURE_LAYER  8

    /******************************************************************************/
    /**��Ϸ���ι�����
        @remarks
            ������������ͳһ���á�
            ����������еĵ��ο顣

        @remarks:
            ����Movable�ҽӵ����θ��ڵ�SceneNode
            SceneNode����ÿ֡���ʹҽӵ�Movable���Ƿ�����Ҫ��Ⱦ�Ķ�����Ⱦ������RenderQueue�С�
            TerrainManager�������Щ�����¼�������ģ�飬�����ò��ˮ��ֲ���ȶ���
    */
    /******************************************************************************/

    class TerrainManager : public ITerrainManager
    {
    public:
		enum
		{
			TERRAIN_MTL_NORMAL,
			TERRAIN_MTL_REFLECTION,
			TERRAIN_MTL_REFRACTION,

			TERRAIN_MTL_NR,
		};
        TerrainManager(Scene* scene);
        virtual ~TerrainManager();

        /// ���µ�����
        virtual Bool                    update( Flt delta );
        
        /// ���ص�������
        virtual void                    load(Str path);
        /// �����������
        virtual void                    save(Str path);
        /// ��յ�������
        virtual void                    unLoad();
        /// ���豸����
        void                            reset();
		/// �ü���������
		virtual void                    clip(Str path, RectF rect);

		/// �����򲢱��������ͼ������
		virtual void                    _reorderTextureLayer(Str& path);


        /// Ӧ����Ⱦѡ��
        void                            applyRenderConfig();


        ////////////////////////////////////////////////////////////////////////////////////

        /// ���ĸ߶�
        static Flt MaxHeight;
        
        // �õ�����
        Scene*                          getScene(){ return mScene; };

        /// �õ��ڵ����
        virtual ISceneNode*             getSceneNode() { return NULL; };

        /// ���úͻ�ȡ��������λ��
        void                            setCenterPosition(Vec3 pos){ mCenterPos = pos; };
        Vec3                            getCenterPosition(){ return mCenterPos; };

        /// ��������
        virtual void                    setConfig( TerrainDeclare& declare ){ mTerrainDeclare = declare; };
        /// �õ�����
        virtual TerrainDeclare&         getConfig(){ return mTerrainDeclare; };


        /// �õ�����������
        TerrainRegionManager*           getTerrainRegionManager(){ return mRegionMgr; };
        /// �õ��ر�������
        TerrainSurfaceManager*          getTerrainSurfaceManager(){ return mSurfaceMgr; };

        ////////////////////////////////////////////////////////////////////////////////////


        /// �����ؿ�
        virtual TerrainChunk*           createTerrainChunk( I8 x, I8 y, TerrainChunkDeclare& decl );
        /// �õ��ؿ�
        virtual TerrainChunk*           getTerrainChunk( I8 x, I8 y );
        /// ���ٵؿ�
        virtual void                    destroyAllTerrainChunk();
        /// �õ��ؿ���
                U32                     getTerrainChunkUID( I8 x, I8 y );

        /// ���صؿ�
                void                    loadTerrainChunk(Str path);
        /// ����ؿ�
                void                    saveTerrainChunk(Str path);
        /// ж�صؿ�
                void                    unLoadTerrainChunk();
        /// ���µؿ�
                void                    updateTerrainChunk( Flt delta );

        /// �õ��ؿ�����
        virtual UInt                    getTerrainChunkCount();
        /// �õ��ؿ�ͨ������
        virtual TerrainChunk*           getTerrainChunkByIndex(UInt index);
        /// �õ��ؿ�
        virtual TerrainChunk*           getTerrainChunkByWorldPos( Vec2 worldPos ) ;

        /// �õ��ؿ��С
        Flt                             getTerrainChunkSize(){ return mChunkSize; };
        Flt                             getTerrainChunkHalfSize(){ return mChunkHalfSize; };

        ////////////////////////////////////////////////////////////////////////////////////

        /// �õ�������߲�ѯ���
        virtual Bool                    getMouseRayIntersection(Vec3& intersectPos,Bool isPrecise = false);
        /// �õ����߽���
        virtual Bool                    getRayIntersection(Vec3& pos, Vec3& dir, Vec3& intersectPos,Bool isPrecise = false);
        /// �õ��߶�
        virtual Bool                    getStickHeight( Vec2 worldPos , Flt& height );


        ////////////////////////////////////////////////////////////////////////////////////
		Int								getTerrainWidth();
		Int								getTerrainHeight();

		Flt								getTerrainChunkBlockGridSize();

		////////////////////////////////////////////////////////////////////////////////////

    private:

        /// ��������
        Scene* mScene;

        /// ��������λ��
        Vec3 mCenterPos;
        Vec3 mIndexCenterPos;
        /// �ؿ��С
        Flt mChunkSize;
        /// �ؿ�һ���С
        Flt mChunkHalfSize;
        /// ����
        TerrainDeclare mTerrainDeclare;

        ///////////////////////////////////////////////////////////////////////////////

        /// �ر����
        TerrainSurfaceManager* mSurfaceMgr;
        /// �������
        TerrainRegionManager* mRegionMgr;

        ///////////////////////////////////////////////////////////////////////////////

        std::map<U32 ,TerrainChunk*> mTerrainChunks;
        Vec2                         mMaxTerrainChunkRect;

        ///////////////////////////////////////////////////////////////////////////////

		Int							 mTerrainWidth; 
		Int							 mTerrainHeight;

		Flt							 mTerrainChunkBlockGridSize;

		MaterialPtr					 mTerrainMtls[TERRAIN_MTL_NR];
    };

}

/******************************************************************************/

#endif
