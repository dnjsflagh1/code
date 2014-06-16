/******************************************************************************/
#include "stdafx.h"
#include "TerrainNode.h"
#include "TerrainBatch.h"
#include "TerrainChunk.h"
#include "EngineMain.h"
#include "Scene.h"
#include "TerrainTiles.h"
#include "TerrainTilesGpu.h"
#include "TerrainTilesLayerBlendMap.h"
#include "TerrainTilesMaterial.h"
#include "TerrainTilesMaterialA.h"
#include "TerrainTilesOptions.h"
#include "MGSceneNode.h"
#include "MGEngineUtility.h"
#include "Display.h"
#include "LightingMapMaker.h"

/******************************************************************************/

namespace MG
{

    //------------------------------------------------------------------------
    TerrainNode::TerrainNode( TerrainManager* mgr, TerrainChunk* chunk, TerrainSurface* surface, TerrainNodeGrid* grid, UInt index )
		:mTerrainMgr(mgr)
		,mTerrainSurface(surface)
		,mTerrainChunk(chunk)
		,mOwner(grid)
		,mIndex(index)
		,mTileSideNumInNode(0)
        ,mSceneNode(NULL)
        ,mMovable(NULL)
    {

    }

    //------------------------------------------------------------------------
    TerrainNode::~TerrainNode()
    {

    }

	//------------------------------------------------------------------------
	void TerrainNode::createGrids()
	{
		TerrainDeclare& decl                    = mTerrainMgr->getConfig();
        const TerrainChunkDeclare& chunkDecl    = mTerrainChunk->getTerrainChunkConfig();

		mTileSideNumInNode			= chunkDecl.gridSideNumInNode / chunkDecl.gridSideNumInTile;
		mTileSize                   = chunkDecl.gridSideNumInTile * decl.gridSize;

		Vec2 centerPos;
		centerPos.x             = mOwner->worldCenterPosX;
		centerPos.y             = mOwner->worldCenterPosZ;

		createGrids(mTileSideNumInNode,mTileSize,centerPos);
	}

	//------------------------------------------------------------------------
	void TerrainNode::createGrids(Int gridsSideNum, Flt gridSize,  Vec2 centerPos)
	{
		GridManager<TerrainTile>::createGrids(gridsSideNum,gridSize,centerPos);

		/////////////////////////////////////////////////////////////////

        loadMovableObject();

        /////////////////////////////////////////////////////////////////

		UInt vertexSideNumInTile = mTerrainSurface->getVertexSideNumInTile();

		TerrainTile* tile		=   getGridData();
		Int tileSideNum         =   getGridSideNum();
		Flt halfGridSize        =   gridSize * 0.5;

		// 加载顶点数据
        
		uint16 offsetX = mOwner->vertexRectInSurface.left;
		uint16 offsetY = mOwner->vertexRectInSurface.top;
		uint16 boundaryX = offsetX + vertexSideNumInTile -1;
		uint16 boundaryY = offsetY + vertexSideNumInTile -1;

		Int x = 0;
		Int y = 0;
		Vec2 gridPoint;
		Vec2 worldPos;
		UInt index = 0;
		for( ; y < tileSideNum; y++ )
		{
			offsetX     = mOwner->vertexRectInSurface.left;;
			boundaryX   = offsetX + vertexSideNumInTile -1;

			for( x = 0; x<tileSideNum; x++ )
			{
				gridPoint.x = x;
				gridPoint.y = y;
				convertGridPointToWorldPosition( gridPoint, worldPos );

				tile->worldCenterPosX               = worldPos.x;
				tile->worldCenterPosZ               = worldPos.y;
				tile->radius                        = halfGridSize;

				tile->vertexRectInSurface.left      = offsetX;
				tile->vertexRectInSurface.top       = offsetY;
				tile->vertexRectInSurface.right     = boundaryX;
				tile->vertexRectInSurface.bottom    = boundaryY;

				///////////////////////////////////////////////////////////////

				if ( tile->render == NULL )
				{
					tile->render = mTerrainSurface->createTerrainTileRender( mTerrainMgr, mTerrainChunk, 
                                                        this, tile, index++ );
					tile->render->createGrids();
				}

				///////////////////////////////////////////////////////////////

				tile++;

				offsetX     += vertexSideNumInTile -1;
				boundaryX   += vertexSideNumInTile -1;

			}
			offsetY += vertexSideNumInTile -1;
			boundaryY += vertexSideNumInTile -1;
		}
	}

	//------------------------------------------------------------------------
	void TerrainNode::destroyGrids()
	{
		if ( isHasGrids() )
		{
			TerrainTile*& grids = getGrids();
			if ( grids )
			{
				UInt num = getGridSideNum() * getGridSideNum();
				for(UInt i =0; i<num; i++)
				{
					TerrainTile& tile = grids[i];
					tile.render->destroyGrids();
					MG_SAFE_DELETE( tile.render );
				}
			}
		}

		//////////////////////////////////////////////////////////////////

        unLoadMovableObject();

        //////////////////////////////////////////////////////////////////

		GridManager<TerrainTile>::destroyGrids();
	}


	//------------------------------------------------------------------------
	void TerrainNode::applyRenderConfig()
	{
		if ( isHasGrids() )
		{
			TerrainTile*& grids = getGrids();
			if ( grids )
			{
				UInt num = getGridSideNum() * getGridSideNum();
				for(UInt i =0; i<num; i++)
				{
					TerrainTile& tile = grids[i];

					if ( tile.render != NULL )
					{
						tile.render->applyRenderConfig();
					}
				}
			}
		}
	}

	//------------------------------------------------------------------------
	void TerrainNode::update( Flt delta )
	{
		if ( isHasGrids() )
		{
			TerrainTile*& grids = getGrids();
			if ( grids )
			{
				UInt num = getGridSideNum() * getGridSideNum();
				for(UInt i =0; i<num; i++)
				{
					TerrainTile& tile = grids[i];

					if ( tile.render  )
					{
						tile.render->update( delta );
					}
				}
			}

            if ( mMovable )
                mMovable->findVisibleObject();
		}
	}


	//------------------------------------------------------------------------
	void TerrainNode::load()
	{
		if ( isHasGrids() )
		{
			TerrainTile*& grids = getGrids();
			if ( grids )
			{
				UInt num = getGridSideNum() * getGridSideNum();
				for(UInt i =0; i<num; i++)
				{
					TerrainTile& tile = grids[i];

					if ( tile.render != NULL )
					{
						tile.render->load();
					}
				}
			}
		}
	}

	//------------------------------------------------------------------------
	void TerrainNode::unload()
	{
		if ( isHasGrids() )
		{
			TerrainTile*& grids = getGrids();
			if ( grids )
			{
				UInt num = getGridSideNum() * getGridSideNum();
				for(UInt i =0; i<num; i++)
				{
					TerrainTile& tile = grids[i];

					if ( tile.render != NULL )
					{
						tile.render->unload();
					}
				}
			}
		}
	}

	//------------------------------------------------------------------------
	void TerrainNode::reset()
	{
		if ( isHasGrids() )
		{
			TerrainTile*& grids = getGrids();
			if ( grids )
			{
				UInt num = getGridSideNum() * getGridSideNum();
				for(UInt i =0; i<num; i++)
				{
					TerrainTile& tile = grids[i];

					if ( tile.render != NULL )
					{
						tile.render->reset();
					}
				}
			}
		}
	}

	//------------------------------------------------------------------------
	void TerrainNode::updateVertex(const Ogre::Rect& vertexRectInSurface)
	{
		if ( isHasGrids() )
		{
			TerrainTile*& grids = getGrids();
			if ( grids )
			{
				UInt num = getGridSideNum() * getGridSideNum();
				for(UInt i =0; i<num; i++)
				{
					TerrainTile& tile = grids[i];

					Ogre::Rect tileRect         = tile.vertexRectInSurface;
					Ogre::Rect dirtyTileRect    = vertexRectInSurface.intersect(tileRect);

					if ( dirtyTileRect.isNull() == false )
					{
						if ( tile.render != NULL )
						{
							tile.render->updateVertex( dirtyTileRect );
						}
					}
				}
			}
		}
	}	

    //**********************************************************************************************************************
    //**********************************************************************************************************************


    void TerrainNode::loadMovableObject()
    {
        TerrainSurface* surface = mTerrainSurface;

        //////////////////////////////////////////////////////////////////////

        TerrainDeclare& decl = mTerrainMgr->getConfig();

        AxisAlignedBox waabb;
        AxisAlignedBox aabb;


        Vector3 wmaximum = Vector3(mOwner->worldCenterPosX + mOwner->radius , decl.maxHeight, mOwner->worldCenterPosZ +  mOwner->radius);
        Vector3 wminimum = Vector3(mOwner->worldCenterPosX - mOwner->radius , -decl.maxHeight , mOwner->worldCenterPosZ - mOwner->radius);
        waabb.setMaximum(wmaximum);
        waabb.setMinimum(wminimum);

        Vector3 maximum = Vector3(mOwner->radius , decl.maxHeight, mOwner->radius);
        Vector3 minimum = Vector3(-mOwner->radius , -decl.maxHeight , -mOwner->radius);
        aabb.setMaximum(maximum);
        aabb.setMinimum(minimum);

        mMovable    =  MG_NEW Movable(this,aabb,waabb);

        //////////////////////////////////////////////////////////////////////

        mMovable->setUserAny( Any((ISceneObject*)mTerrainMgr) );

        mMovable->setQueryFlags(Scene::getQueryMask( surface->getSceneObjectTypes() ));
        mMovable->setVisibilityFlags( surface->getSceneVisibleFlags() );
        mMovable->setRenderQueueGroup( mTerrainSurface->getRenderQueueGroup() );
        mMovable->setVisible( true );

        //////////////////////////////////////////////////////////////////////

        if ( !mSceneNode )
        {
            Ogre::SceneNode* node = mTerrainMgr->getScene()->getOgreSceneManager()->getRootSceneNode();
            mSceneNode = MG_NEW MGSceneNode(node, mTerrainMgr->getScene());
            mSceneNode->getOgreSceneNode()->attachObject(mMovable);

            mSceneNode->setPosition( Vec3(mOwner->worldCenterPosX, 0, mOwner->worldCenterPosZ) );
        }
    }

    //---------------------------------------------------------------------
    void TerrainNode::unLoadMovableObject()
    {
        MG_SAFE_DELETE( mMovable );
        MG_SAFE_DELETE( mSceneNode );
    }



    //------------------------------------------------------------------------
    //**********************************************************************************************************************
    //**********************************************************************************************************************

    //---------------------------------------------------------------------
    //---------------------------------------------------------------------
    TerrainNode::Movable::Movable(TerrainNode* node, AxisAlignedBox& aabb,AxisAlignedBox& worldAAbb)
        : mTerrainNode(node)
        ,mBoundingRadius(1.0)
        ,mAABB(aabb)
    {
        mBoundingRadius = mAABB.getHalfSize().length();

        {
            Vector3 minimum = worldAAbb.getMinimum();
            Vector3 maximum = worldAAbb.getMaximum();
            mRect.left      = minimum.x;
            mRect.right     = maximum.x;
            mRect.top       = minimum.z;
            mRect.bottom    = maximum.z;
        }

        findVisibleObject();
    }
    //---------------------------------------------------------------------
    TerrainNode::Movable::~Movable()
    {

    }
    //---------------------------------------------------------------------
    const String& TerrainNode::Movable::getMovableType(void) const
    {
        static String stype("OgreTerrainNodeMovable");

        return stype;
    }
    //---------------------------------------------------------------------
    const AxisAlignedBox& TerrainNode::Movable::getBoundingBox(void) const
    {
        //return mRenderAABB;
        return mAABB;
    }
    //---------------------------------------------------------------------
    Real TerrainNode::Movable::getBoundingRadius(void) const
    {
        return mBoundingRadius;
    }
    //---------------------------------------------------------------------
    uint32 TerrainNode::Movable::getVisibilityFlags(void) const
    {
        // Combine own vis (in case anyone sets this) and terrain overall
        return mVisibilityFlags;
    }
    //---------------------------------------------------------------------
    uint32 TerrainNode::Movable::getQueryFlags(void) const
    {
        // Combine own vis (in case anyone sets this) and terrain overall
        return mQueryFlags;
    }

    //------------------------------------------------------------------------
    void TerrainNode::Movable::findVisibleObject()
    {
        mRenderAABB.setNull();

        if ( mTerrainNode->isHasGrids() )
        {
            TerrainTile*& tileGrids = mTerrainNode->getGrids();

            UInt num = mTerrainNode->getGridSideNum() * mTerrainNode->getGridSideNum();

            for(UInt i =0; i<num; i++)
            {
                TerrainTile& tile = tileGrids[i];

                if ( tile.render )
                {
                    TerrainBatchGrid *& batchGrids = tile.render->getGrids();

                    if ( batchGrids )
                    {
                        UInt num2 = tile.render->getGridSideNum() * tile.render->getGridSideNum();
                        for(UInt j =0; j<num2; j++)
                        {
                            TerrainBatchGrid& batch = batchGrids[j];

                            batch.batch->updateVisible( mRenderAABB );
                        }
                    }
                }
            }
        }
    }

    //------------------------------------------------------------------------
    void TerrainNode::Movable::_updateRenderQueue(RenderQueue* queue)
    {
        if ( mTerrainNode->isHasGrids() )
        {
            TerrainTile*& tileGrids = mTerrainNode->getGrids();

            UInt num = mTerrainNode->getGridSideNum() * mTerrainNode->getGridSideNum();

            for(UInt i =0; i<num; i++)
            {
                TerrainTile& tile = tileGrids[i];

                if ( tile.render )
                {
                    TerrainBatchGrid *& batchGrids = tile.render->getGrids();

                    if ( batchGrids )
                    {
                        UInt num2 = tile.render->getGridSideNum() * tile.render->getGridSideNum();
                        for(UInt j =0; j<num2; j++)
                        {
                            TerrainBatchGrid& batch = batchGrids[j];

                            batch.batch->addRenderable( queue );
                        }
                    }
                }
            }
        }
    }
    //------------------------------------------------------------------------
    void TerrainNode::Movable::visitRenderables(Renderable::Visitor* visitor,  bool debugRenderables)
    {
        if ( mTerrainNode->isHasGrids() )
        {
            TerrainTile*& tileGrids = mTerrainNode->getGrids();

            UInt num = mTerrainNode->getGridSideNum() * mTerrainNode->getGridSideNum();

            for(UInt i =0; i<num; i++)
            {
                TerrainTile& tile = tileGrids[i];

                if ( tile.render )
                {
                    TerrainBatchGrid *& batchGrids = tile.render->getGrids();

                    if ( batchGrids )
                    {
                        UInt num2 = tile.render->getGridSideNum() * tile.render->getGridSideNum();
                        for(UInt j =0; j<num2; j++)
                        {
                            TerrainBatchGrid& batch = batchGrids[j];

                            batch.batch->visitRenderables( visitor );
                        }
                    }
                }
            }
        }
    }
    //---------------------------------------------------------------------
    bool TerrainNode::Movable::getCastShadows(void) const
    {
        TerrainSurfaceType type = mTerrainNode->mTerrainSurface->getType();
        LightingMapMaker* lmaker = mTerrainNode->mTerrainMgr->getScene()->getShadowManager()->getLightingMapMaker();

        Bool castsShadow = lmaker->getTerrainCastShadows( type );

        return castsShadow;
    }

}