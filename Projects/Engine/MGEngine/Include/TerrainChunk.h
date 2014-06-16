/******************************************************************************/
#ifndef _TERRAINCHUNK_H_
#define _TERRAINCHUNK_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "ITerrain.h"
#include "TerrainGroundSurface.h"
#include "TerrainRegion.h"


/******************************************************************************/
namespace MG
{

	/******************************************************************************/
	//TerrainChunk
	/******************************************************************************/
    class TerrainChunk : public ITerrainChunk
	{
        friend class Scene;
	public:

        TerrainChunk(TerrainManager* mgr, Scene* scene, Vec2 indexPos, Vec2 worldCenterPos, TerrainChunkDeclare& decl);
		virtual ~TerrainChunk();

        ////////////////////////////////////////////////////////////////////////////////////

        /// ���µ���
        void                            update( Flt delta );

        /// ���ص�������
        void                            load(Str path);
        /// �����������
        void                            save(Str path);
        /// ��յ�������
        void                            unLoad();

		/////// �����򲢱�����ͼͼ������
		void                            _reorderTextureLayer(const Str &path);

        // �õ�Chunk����
        const TerrainChunkDeclare&      getTerrainChunkConfig(){ return mChunkDecl;};

        ////////////////////////////////////////////////////////////////////////////////////

        /// �õ�����������
        Vec2&                           getTerrainGroupIndex(){ return mTerrainGroupIndex;};
        /// �õ����ĵ�����
        Vec2&                           getWorldCenterPos(){ return mWorldCenterPos; };
        /// �õ���ײ��
        AxisAlignedBox&                 getBoundingBox(){return mBoundingBox;};
        /// �õ���ײ����
        Ogre::Rect&                     getBoundingRect(){return mBoundingRect;};

        /// ������ײ��
        void                            generateBoundingShape();
        
        /// �õ��ر����
        virtual TerrainSurface*         getTerrainSurface( TerrainSurfaceType type );

        /// �õ��ر������
        virtual TerrainGroundSurface*   getTerrainGroundSurface() { return mTerrainGroundSurface; } ;
        /// �õ�ˮ����
        virtual TerrainWaterSurface*    getTerrainWaterSurface() { return mTerrainWaterSurface; } ;
        /// �õ�����������
        virtual TerrainChunkRegions*    getTerrainRegion(){ return mTerrainRegion; };

		////////////////////////////////////////////////////////////////////////////////////

	public:
        /// �õ�����
        Str&                            getName(){ return mName; };
        /// �õ���ԴĿ¼��
        Str&                            getDirectionName(){ return mDirectionName; };


        ////////////////////////////////////////////////////////////////////////////////////

    private:

        /// �������������.
        TerrainManager* mOwner;
        /// ������������.
        Scene* mScene;
        // ����
        Str mName;
        // �ļ�������
        Str mDirectionName;
        // ��ԴĿ¼
        Str mResourcePath;
        // ��ײ��
        AxisAlignedBox mBoundingBox;
        Ogre::Rect  mBoundingRect;

        ///////////////////////////////////////////////////////////////////////////////

        TerrainChunkDeclare mChunkDecl;
        
        ///////////////////////////////////////////////////////////////////////////////
        
        /// �ر�
        TerrainGroundSurface*   mTerrainGroundSurface;
        /// ˮ��
        TerrainWaterSurface*   mTerrainWaterSurface;
       
        /// ��������
        TerrainChunkRegions* mTerrainRegion;

        ///////////////////////////////////////////////////////////////////////////////
        
        Vec2 mTerrainGroupIndex;
        Vec2 mWorldCenterPos;


		///////////////////////////////////////////////////////////////////////////////
	};

}

/******************************************************************************/

#endif
