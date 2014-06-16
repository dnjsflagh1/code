/******************************************************************************/
#ifndef _ITERRAIN_H_
#define _ITERRAIN_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"
#include "ISceneObject.h"
#include "IResourceManager.h"

/******************************************************************************/

namespace MG
{
   
    //����������������������������������������������������������������������������������������������������������������������������
    //����������������������������������������������������������������������������������������������������������������������������

    /********************************************************/
    //��������
    /********************************************************/
    enum TerrainGroundMaterialType
    {
        TMS_BIG = 0,
        TMS_SMALL
    };


    /********************************************************/
    //��������
    /********************************************************/
    struct TerrainChunkDeclare
    {
		Int							gridSideNumInNode;				/// ���νڵ�һ����������
        Int							gridSideNumInTile;              /// ���ηֿ�һ����������
        Int							blendMapSizeInTile;             /// �����ͼӳ���С


        TerrainChunkDeclare()
        {
            reset();
        }

        void reset()
        {
			gridSideNumInNode		= 512;
            gridSideNumInTile       = 512;
            blendMapSizeInTile      = gridSideNumInTile;
        }
    };

	struct TerrainDeclare
	{
		Int							gridSideNumInChunk;             /// ���θ�һ�ߵ�������һ��Chunk����
		Int							gridSideNumInBatch;             /// ��Ⱦ��һ�ߵĸ�������
		Flt							gridSize;                       /// ���θ��С
		Int							lightingMapSize;                /// ��Ӱ��ͼӳ���С			

		Flt							heightScale;
		Flt							minHeight;
		Flt							maxHeight;

		TerrainGroundMaterialType	groundMatType; /// ���α����������

		std::vector<VecI2>			trunkIndexList;		/// thunk�����б�

		TerrainChunkDeclare         chunkDecl;

		TerrainDeclare()
		{
			reset();
		}

		void reset()
		{
			gridSideNumInChunk      = 1024;
			gridSideNumInBatch      = 128;
			gridSize                = 1;
			lightingMapSize         = 1024;

			heightScale             = 20;
			minHeight               = 0;
			maxHeight               = 100;

			groundMatType           = TMS_BIG;

			chunkDecl				= TerrainChunkDeclare();

			trunkIndexList.clear();
			trunkIndexList.push_back(VecI2(1,1));
		}
	};




    //����������������������������������������������������������������������������������������������������������������������������
    //����������������������������������������������������������������������������������������������������������������������������

    enum TerrainSurfaceType
    {
        TST_NULL,
        TST_GROUND,
        TST_WATER
    };

    /********************************************************/
    //��Ϸ�ؿ�������ʾ
    /********************************************************/
    class ITerrainGroundSurface
    {
    };
    class ITerrainWaterSurface
    {
    };


    struct TerrainWaterGroupDeclaration
    {
        UInt        groupID;
        U32         wMatID;
        //MaterialDeclaration* matDecl;
        Vec3        reflectPostion;
        Vec3        reflectDirection;
        TerrainWaterGroupDeclaration()
            :reflectPostion(0,0,0)
            ,reflectDirection(0,-1,0)
        {

        }
    };


    class ITerrainSurfaceManager
    {
    public:
        virtual Int                                 getGlobleTextureLayerMaxCount() = 0;
        virtual TerrainTextureLayerDeclaration*     getGlobleTextureLayer( Int index ) = 0;
        virtual void                                addGlobleTextureLayer(Str name) = 0;
        
        virtual Int                                 getGlobleWaterGroupMaxCount() = 0;
        virtual TerrainWaterGroupDeclaration*       getGlobleWaterGroupByIndex( UInt index ) = 0;
        virtual TerrainWaterGroupDeclaration*       getGlobleWaterGroup( U32 groupID ) = 0;
        virtual TerrainWaterGroupDeclaration*       addGlobleWaterGroup( U32 groupID ) = 0;
    };
    

    /********************************************************/
    //��Ϸ�Զ�������
    /********************************************************/
    struct CustomRegionDeclaration
    {
        Str  name;
        Bool visible;
    };
    class ITerrainChunkRegions
    {
    public:

    };
    class ITerrainRegionManager
    {
    public:

        // �����ϰ�����ɼ���
        virtual void                            setBlockRegionVisible(Bool visible) = 0;
        // �����Զ�������ɼ���
        virtual void                            setCustomRegionVisible( Int index, Bool visible ) = 0;
        // Ӧ������ɼ���
        virtual void                            applyRegionVisible() = 0;

        // ���Ӻ͵õ��Զ�������
        virtual void                            clearCustomRegion() = 0;
        virtual void                            addCustomRegion() = 0;
        virtual void                            removeCustomRegion( Int index ) = 0;
        virtual Int                             getCustomRegionCount() = 0;
        virtual CustomRegionDeclaration*        getCustomRegionDeclaration( UInt index ) = 0;
    };


    //����������������������������������������������������������������������������������������������������������������������������
    //����������������������������������������������������������������������������������������������������������������������������

    /********************************************************/
    //��Ϸ�������ӿ�
    /********************************************************/
    class ITerrainChunk
    {
    public:
        /// �õ��ر���ʾ����
        virtual ITerrainGroundSurface*          getTerrainGroundSurface() = 0;
        /// �õ��ر���ʾ����
        virtual ITerrainChunkRegions*           getTerrainRegion() = 0;

        // �õ�Chunk����
        virtual const TerrainChunkDeclare&      getTerrainChunkConfig() = 0;
    };

   
	/********************************************************/
	//���ι���
	/********************************************************/
	class ITerrainManager //: public ISceneObject
	{
	public:

        /// ��������
        virtual void                            setConfig( TerrainDeclare& declare ) = 0;
        /// �õ�����
        virtual TerrainDeclare&                 getConfig() = 0;

        //////////////////////////////////////////////////////////////////////////////////////////////////

        /// �����ؿ�
        virtual ITerrainChunk*                  createTerrainChunk( I8 x, I8 y, TerrainChunkDeclare& decl ) = 0;
        /// �õ��ؿ�
        virtual ITerrainChunk*                  getTerrainChunk( I8 x, I8 y ) = 0;
        /// ���ٵؿ�
        virtual void                            destroyAllTerrainChunk() = 0;

        /// �õ��ؿ�����
        virtual UInt                            getTerrainChunkCount() = 0;
        /// �õ��ؿ�ͨ������
        virtual ITerrainChunk*                  getTerrainChunkByIndex(UInt index) = 0;
        /// �õ��ؿ�
        virtual ITerrainChunk*                  getTerrainChunkByWorldPos( Vec2 worldPos ) = 0;

        //////////////////////////////////////////////////////////////////////////////////////////////////

        /// ���ص������� 
        virtual void                            load(Str path) = 0;
        /// �����������
        virtual void                            save(Str path) = 0;
        /// ����������� 
        virtual void                            unLoad() = 0;
		/// �ü���������
		virtual void                            clip(Str path, RectF clipRect) = 0;
		/// �����򲢱��������ͼ������
		virtual void							_reorderTextureLayer(Str& path) = 0;

        //////////////////////////////////////////////////////////////////////////////////////////////////

        /// �õ�����������
        virtual ITerrainRegionManager*          getTerrainRegionManager() = 0;
        /// �õ��ر�������
        virtual ITerrainSurfaceManager*         getTerrainSurfaceManager() = 0;

        //////////////////////////////////////////////////////////////////////////////////////////////////

        /// �õ�������߽���
        virtual Bool                            getMouseRayIntersection(Vec3& intersectPos,Bool isPrecise = false) = 0;
        /// �õ����߽���
        virtual Bool                            getRayIntersection(Vec3& pos, Vec3& dir, Vec3& intersectPos,Bool isPrecise = false) = 0;
        /// �õ��߶�
        virtual Bool                            getStickHeight( Vec2 worldPos , Flt& height ) = 0;

		///
		virtual Int								getTerrainWidth() = 0;
		
		///
		virtual Int								getTerrainHeight() = 0;

		/// ���úͻ�ȡ��������λ��
		virtual void							setCenterPosition(Vec3 pos) = 0;
		virtual Vec3							getCenterPosition() = 0;
    };

}

/******************************************************************************/
#endif
