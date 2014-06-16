/******************************************************************************/
#ifndef _TERRAINNODE_H_
#define _TERRAINNODE_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "MGGrid.h"
#include "TerrainTiles.h"

/******************************************************************************/
namespace MG
{


	//��������������������������������������������������������������������������������������������������
	//��������������������������������������������������������������������������������������������������

	//@{
#pragma pack( push )
#pragma pack( 1 )

	/******************************************************************************/
	//һ���ؿ�ڵ�
	/******************************************************************************/
	struct TerrainNodeGrid
	{
		// ��Ⱦ�ؿ���Surface�е���������
		Flt worldCenterPosX, worldCenterPosZ;
		// ��Ⱦ�ؿ���Surface�еİ뾶
		Flt radius;

		// ��Ⱦ�ؿ�Ķ�����Surface�е�����
		Ogre::Rect vertexRectInSurface;

		// ��Ⱦ��
		TerrainNode* node;
	};

#pragma pack (pop)
	//@}


    //��������������������������������������������������������������������������������������������������
    //��������������������������������������������������������������������������������������������������

    /******************************************************************************/
    //�ؿ��еĽڵ�
    /******************************************************************************/
    class TerrainNode : public GridManager<TerrainTile>
    {
        friend class TerrainBatch;
    public:
		TerrainNode( TerrainManager* mgr, TerrainChunk* chunk, TerrainSurface* surface, TerrainNodeGrid* grid, UInt index );
        virtual ~TerrainNode();

    public:

		// ����
		virtual void                    update( Flt delta ) ;
		/// ��Ӧ��Ⱦ����
		virtual void					applyRenderConfig();

        /// �õ����к�
        virtual UInt					getIndex(){ return mIndex; };
        
        /// �õ��������
        virtual TerrainNodeGrid*        getOwner(){ return mOwner; };
        
	public:

		// ����դ��
		virtual void                    createGrids();
		// ����դ��
		virtual void                    createGrids(Int gridsSideNum, Flt gridSize,  Vec2 centerPos);
		// ����դ��
		virtual void                    destroyGrids();

	public:

		// ����
		virtual void                    load();
		// ж��
		virtual void                    unload();
		// �豸����
		virtual void                    reset();

	public:

		// ���¶���λ��
		void                            updateVertex(const Ogre::Rect& vertexRectInSurface);

    public:

        /*########################################
        //     ��Ⱦ���� ���ƶ�����
        #########################################*/
        
        /// ���ε��ƶ�����
        class Movable : public MovableObject
        {

        protected:

            TerrainNode*    mTerrainNode;
            AxisAlignedBox  mAABB; //relative to mLocalCentre
            AxisAlignedBox  mRenderAABB; //relative to mLocalCentre
            Ogre::Rect      mRect;
            Real            mBoundingRadius; //relative to mLocalCentre

        public:

            Movable(TerrainNode* node, AxisAlignedBox& aabb, AxisAlignedBox& worldAAbb);
            virtual ~Movable();

            // necessary overrides
            virtual const String&           getMovableType(void) const;
            virtual const AxisAlignedBox&   getBoundingBox(void) const;
            virtual Real                    getBoundingRadius(void) const;

            virtual void                    findVisibleObject();

            virtual void                    _updateRenderQueue(RenderQueue* queue);
            virtual void                    visitRenderables(Renderable::Visitor* visitor,  bool debugRenderables = false);

            virtual uint32                  getVisibilityFlags(void) const;
            virtual uint32                  getQueryFlags(void) const;
            virtual bool                    getCastShadows(void) const;

            const Ogre::Rect&               getWorldBoundingRect(void){ return mRect; };
        };

        /////////////////////////////////////////////////////////////////////////////////////////////////////

        // ���غ�ж�ؿ��ƶ�����
        void                                loadMovableObject();
        void                                unLoadMovableObject();

        // �õ�movable
        Movable*                            getMovable(){return mMovable;}

        friend class Movable;

	protected:

		TerrainManager*			mTerrainMgr;
		TerrainSurface*			mTerrainSurface;
		TerrainChunk*			mTerrainChunk;
		TerrainNodeGrid*		mOwner;
		UInt					mIndex;

		// Tile һ�� ���� 
		Int             mTileSideNumInNode;
		Flt             mTileSize;

        // �����ڵ���ƶ�����
        Movable*        mMovable;
        MGSceneNode*    mSceneNode; 


    };



}


/******************************************************************************/

#endif