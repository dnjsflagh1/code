/******************************************************************************/
#include "stdafx.h"
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
#include "ILight.h"

#include "OgreStreamSerialiser.h"
#include "OgreMath.h"
#include "OgreImage.h"
#include "OgrePixelFormat.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreException.h"
#include "OgreBitwise.h"
#include "OgreStringConverter.h"
#include "OgreViewport.h"
#include "OgreLogManager.h"
#include "OgreHardwarePixelBuffer.h"
#include "OgreTextureManager.h"
#include "OgreRoot.h"
#include "OgreRenderSystem.h"
#include "OgreRay.h"
#include "OgrePlane.h"
#include "OgreMaterialManager.h"
#include "OgreHardwareBufferManager.h"
#include "Display.h"
/******************************************************************************/

namespace MG
{
    //---------------------------------------------------------------------

    //-----------------------------------------------------------------------
    TerrainSurface::TerrainSurface(TerrainManager* terrainMgr, Scene* scene, TerrainChunk* chunk)
        : mTerrainMgr(terrainMgr)
        , mScene(scene)
        , mChunk(chunk)
        , mHeightData(NULL)
        , mNormalData(NULL)
        ,mTangentData(NULL)
        , mColorData(NULL)
        , mNTOnePixelNum(3)
        , mColorOnePixelNum(4)
        , mVertexSideNum(0)
        , mBaseOffset(0)
        , mVertexOffset(0)
        ,mVertexHalfOffset(0)
        , mHeightDataCreated(false)
        , mPos(Vector3::ZERO)
        , mNormalMapRequired(false)
        , mColorMapRequired(false)
        , mDirtyGeometryRect(0, 0, 0, 0)
        , mDirtyDerivedDataRect(0, 0, 0, 0)
        , mDirtyGeometryRectForNeighbours(0, 0, 0, 0)
        , mModified(false)
        , mHeightDataModified(false)
        , mTileSideNumInChunk(0)
        , mCpuLightmapStorage(0)
        , mLightMapRequired(false)
        , mLightMapShadowsOnly(true)
        ,mLightingMapChangeDirty(false)
    {
    }   
    //-----------------------------------------------------------------------
    TerrainSurface::~TerrainSurface()
    {
    }

    //**********************************************************************************************************************
    //**********************************************************************************************************************

    //-----------------------------------------------------------------------
    void TerrainSurface::configOptions()
    {
        TerrainDeclare& decl                    = mTerrainMgr->getConfig();
        const TerrainChunkDeclare& chunkDecl    = mChunk->getTerrainChunkConfig();

		mNodeSideNumInChunk			= decl.gridSideNumInChunk / chunkDecl.gridSideNumInNode;
		mNodeSize					= chunkDecl.gridSideNumInNode * decl.gridSize;

        mTileSideNumInChunk         = decl.gridSideNumInChunk / chunkDecl.gridSideNumInTile;
        mTileSideNumInNode          = chunkDecl.gridSideNumInNode / chunkDecl.gridSideNumInTile;
        mTileSize                   = chunkDecl.gridSideNumInTile * decl.gridSize;

        mHeightScale                = decl.heightScale;
        mHeightMax                  = decl.maxHeight;
        mHeightMin                  = decl.minHeight;

        ///////////////////////////////////////////////////////////////////////////////////////////////////

		// 计算整个地形顶点数量，沿着一边Node
		mVertexSideNumInNode		= chunkDecl.gridSideNumInNode + 1;
        // 计算整个地形顶点数量，沿着一边Tile
        mVertexSideNumInTile        = chunkDecl.gridSideNumInTile + 1;
        // 计算整个地形顶点数量，沿着一边
        mVertexSideNum              = decl.gridSideNumInChunk + 1;

        Flt worldSize               = decl.gridSideNumInChunk * decl.gridSize;
        // 计算相对于中心点坐标偏移
        mBaseOffset                 = -worldSize * 0.5;
        // 计算顶点间隔
        mVertexOffset               = decl.gridSize;
        mVertexHalfOffset           = mVertexOffset * 0.5;

        ///////////////////////////////////////////////////////////////////////////////////////////////////

        mLightmapSize               = decl.lightingMapSize;
        mLightmapSizeActual         = decl.lightingMapSize; // for now, until we check
    }

    //-----------------------------------------------------------------------
    void TerrainSurface::load( Str path )
    {

        //////////////////////////////////////////////////////////////////////

        mPath = path;

        //////////////////////////////////////////////////////////////////////

        unLoad();

        //////////////////////////////////////////////////////////////////////

        configOptions();
       
        //////////////////////////////////////////////////////////////////////

        createGrids( mNodeSideNumInChunk, mNodeSize, mChunk->getWorldCenterPos() );
        
        //////////////////////////////////////////////////////////////////////

        // 加载高度数据
        loadHeightData( path );

        // 加载法线层数据
        loadNormalTangentMapData( path );

        // 加载颜色层数据
        loadColorMapData( path );

        // 加载光影层数据
        loadLightMapData( path );

        //////////////////////////////////////////////////////////////////////
    }
    //-----------------------------------------------------------------------
    void TerrainSurface::unLoad()
    {
        if ( isHasGrids() == false )
            return ;

        //////////////////////////////////////////////////////////////////////

        unLoadHeightData();
        unLoadNormalTangentMapData();
        unLoadColorMapData();
        unLoadLightMapData();
        
        //////////////////////////////////////////////////////////////////////

        destroyGrids();

        //////////////////////////////////////////////////////////////////////
    }
    //-----------------------------------------------------------------------
    void TerrainSurface::save( Str path )
    {
        //if ( mModified )
        {
            saveHeightData( path );
            saveNormalTangentMapData( path );
            saveColorMapData( path );
            mModified = false;
        }

        //if ( mLightingMapChangeDirty )
            saveLightMapData( path );
    }    
    //-----------------------------------------------------------------------
    void TerrainSurface::createGrids(Int gridsSideNum, Flt gridSize,  Vec2 centerPos)
    {
        GridManager<TerrainNodeGrid>::createGrids(gridsSideNum,gridSize,centerPos);

        /////////////////////////////////////////////////////////////////

        TerrainDeclare& decl    =   mTerrainMgr->getConfig();

        TerrainNodeGrid* node	=   getGridData();
        Int nodeSideNum         =   getGridSideNum();
        Flt halfGridSize        =   gridSize * 0.5;

        // 加载顶点数据
        uint16 offsetX = 0;
        uint16 offsetY = 0;
        uint16 boundaryX = mVertexSideNumInNode -1;
        uint16 boundaryY = mVertexSideNumInNode -1;

        Int x = 0;
        Int y = 0;
        Vec2 gridPoint;
        Vec2 worldPos;
        UInt index = 0;
        for( ; y < nodeSideNum; y++ )
        {
            offsetX = 0;
            boundaryX = mVertexSideNumInNode -1;

            for( x = 0; x<nodeSideNum; x++ )
            {
                gridPoint.x = x;
                gridPoint.y = y;
                convertGridPointToWorldPosition( gridPoint, worldPos );

                node->worldCenterPosX               = worldPos.x;
                node->worldCenterPosZ               = worldPos.y;
                node->radius                        = halfGridSize;

                node->vertexRectInSurface.left      = offsetX;
                node->vertexRectInSurface.top       = offsetY;
                node->vertexRectInSurface.right     = boundaryX;
                node->vertexRectInSurface.bottom    = boundaryY;
              
                ///////////////////////////////////////////////////////////////

                if ( node->node == NULL )
                {
					node->node = createTerrainNode( mTerrainMgr, mChunk, node, index++ );
                    node->node->createGrids();
                }

                ///////////////////////////////////////////////////////////////

                node++;

                offsetX     += mVertexSideNumInNode -1;
                boundaryX   += mVertexSideNumInNode -1;
            }

            offsetY += mVertexSideNumInNode -1;
            boundaryY += mVertexSideNumInNode -1;
        }
    }

    //-----------------------------------------------------------------------
    void TerrainSurface::destroyGrids()
    {
        if ( isHasGrids() )
        {
            TerrainNodeGrid*& grids = getGrids();
            if ( grids )
            {
                UInt num = getGridSideNum() * getGridSideNum();
                for(UInt i =0; i<num; i++)
                {
                    TerrainNodeGrid& node = grids[i];
                    node.node->destroyGrids();
                    MG_SAFE_DELETE( node.node );
                }
            }
        }

        //////////////////////////////////////////////////////////////////

        GridManager<TerrainNodeGrid>::destroyGrids();
    }

    //-----------------------------------------------------------------------
    void TerrainSurface::loadGridData()
    {
        if ( isHasGrids() )
        {
            TerrainNodeGrid*& grids = getGrids();
            if ( grids )
            {
                UInt num = getGridSideNum() * getGridSideNum();
                for(UInt i =0; i<num; i++)
                {
                    TerrainNodeGrid& node = grids[i];

                    if ( node.node != NULL )
                    {
                        node.node->load();
                    }
                }
            }
        }
    }

    //-----------------------------------------------------------------------
    void TerrainSurface::unLoadGridData()
    {
        if ( isHasGrids() )
        {
            TerrainNodeGrid*& grids = getGrids();
            if ( grids )
            {
                UInt num = getGridSideNum() * getGridSideNum();
                for(UInt i =0; i<num; i++)
                {
                    TerrainNodeGrid& node = grids[i];

                    if ( node.node != NULL )
                    {
                        node.node->unload();
                    }
                }
            }
        }
    }

    //-----------------------------------------------------------------------
    void TerrainSurface::updateGridData(Flt delta)
    {
        if ( isHasGrids() )
        {
            TerrainNodeGrid*& grids = getGrids();
            if ( grids )
            {
                UInt num = getGridSideNum() * getGridSideNum();
                for(UInt i =0; i<num; i++)
                {
                    TerrainNodeGrid& node = grids[i];

                    if ( node.node  )
                    {
                        node.node->update( delta );
                    }
                }
            }
        }
    }

    //-----------------------------------------------------------------------
    void TerrainSurface::update(Flt delta, bool synchronous)
    {
        ///////////////////////////////////////////////

        updateGeometry();

        updateGridData( delta );

        ///////////////////////////////////////////////
    }

    //-----------------------------------------------------------------------
    void TerrainSurface::applyRenderConfig()
    {
        if ( isHasGrids() )
        {
            TerrainNodeGrid*& grids = getGrids();
            if ( grids )
            {
                UInt num = getGridSideNum() * getGridSideNum();
                for(UInt i =0; i<num; i++)
                {
                    TerrainNodeGrid& node = grids[i];

                    node.node->applyRenderConfig();
                }
            }
        }
    }
    
    //-----------------------------------------------------------------------
    void TerrainSurface::reset()
    {
        if ( isHasGrids() )
        {
            TerrainNodeGrid*& grids = getGrids();
            if ( grids )
            {
                UInt num = getGridSideNum() * getGridSideNum();
                for(UInt i =0; i<num; i++)
                {
                    TerrainNodeGrid& node = grids[i];

                    node.node->reset();
                }
            }
        }
    }

    //-----------------------------------------------------------------------
    void TerrainSurface::dirtyRect(Int x, Int y)
    {
        Ogre::Rect rect;
        rect.left = x;
        rect.right = x+1;
        rect.top = y;
        rect.bottom = y+1;

        dirtyRect( rect );
    }

    //-----------------------------------------------------------------------
    void TerrainSurface::dirtyRect(const Ogre::Rect& rect)
    {
        //TODO:
        mDirtyGeometryRect.merge(rect);
        mDirtyGeometryRectForNeighbours.merge(rect);
        mDirtyDerivedDataRect.merge(rect);

        mModified = true;
        mHeightDataModified = true;
    }

	//-----------------------------------------------------------------------
	TerrainNode* TerrainSurface::createTerrainNode( TerrainManager* mgr, TerrainChunk* chunk, 
		TerrainNodeGrid* nodeGrid, UInt index )
	{
        return MG_NEW TerrainNode( mgr, chunk, this, nodeGrid, index );
	}

    //-----------------------------------------------------------------------
    TerrainTile* TerrainSurface::getTileGridDataByIndex( UInt x, UInt y )
    {
        TerrainTile* tile = NULL;

        UInt nodeIndexX = x / mTileSideNumInNode;
        UInt nodeIndexY = y / mTileSideNumInNode;

        UInt inNodeX = x % mTileSideNumInNode;
        UInt inNodeY = y % mTileSideNumInNode;

        TerrainNodeGrid* node	=   getGridDataByIndex( nodeIndexX, nodeIndexY );
        
        if ( node && node->node )
        {
            tile = node->node->getGridDataByIndex( inNodeX, inNodeY );
        }

        return tile;
    }

    //**********************************************************************************************************************
    //**********************************************************************************************************************

    
    //---------------------------------------------------------------------
    Real TerrainSurface::getMinHeight() const
    {
        return mHeightMin;
    }

    //---------------------------------------------------------------------
    Real TerrainSurface::getMaxHeight() const
    {
        return mHeightMax;
    }
    //---------------------------------------------------------------------
    Bool TerrainSurface::getRayIntersection(Vec3& pos, Vec3& dir, Vec3& intersectPos, Bool isPrecise)
    {
        //射线声明
        Ogre::Ray ray(Vector3(pos.x,pos.y,pos.z),Vector3(dir.x,dir.y,dir.z));

        if ( isPrecise )
        {
            Plane maxPlane;
            Plane minPlane;

            if ( dir.y != 0 )
            {
                maxPlane = Plane( Vector3(0,1,0), Vector3( 0, getMaxHeight() + mVertexOffset * 2, 0) );
                minPlane = Plane( Vector3(0,1,0), Vector3( 0, getMinHeight() - mVertexOffset * 2, 0) );
            }else
            {
                //TODO:
                //dir.y == 0
                DYNAMIC_ASSERT( false );
            }


            ////////////////////////////////////////////////////////////////////////////

            //射线查询高低2个平面
            Vector3 rayIntersectStartPoint;
            Vector3 rayIntersectEndPoint;


            std::pair< bool, Real > intersect1 = ray.intersects(maxPlane);
            std::pair< bool, Real > intersect2 = ray.intersects(minPlane);

            if ( intersect1.first || intersect2.first )
            {
                if ( intersect1.first && intersect2.first )
                {
                    rayIntersectStartPoint   = ray.getPoint( intersect1.second );	
                    rayIntersectEndPoint   = ray.getPoint( intersect2.second );	
                }else
                if ( intersect1.first && !intersect2.first )
                {
                    rayIntersectStartPoint = Vector3(pos.x,pos.y,pos.z);
                    rayIntersectEndPoint = ray.getPoint( intersect1.second );	
                }else
                if ( !intersect1.first && intersect2.first )
                {
                    rayIntersectStartPoint = Vector3(pos.x,pos.y,pos.z);	
                    rayIntersectEndPoint = ray.getPoint( intersect2.second );
                }
            }else
            {
                return false;
            }


            //////////////////////////////////////////////////////////////////////////////////////////////
           
            // 检测方向
            Vector3 checkDir            = (rayIntersectEndPoint - rayIntersectStartPoint);	
            Vector2 check2DDir          = Vector2(checkDir.x,checkDir.z);	



            // 检测的距离和次数
            Flt     checkLenght         = check2DDir.length();
            UInt    checkCount          = checkLenght  / mVertexOffset * 1.5;


            //////////////////////////////////////////////////////////////////////////////////////////////

            // 检测线段的2端点
            Vector2 checkStartPos       = Vector2(rayIntersectStartPoint.x,rayIntersectStartPoint.z);
            Vector2 checkEndPos         = Vector2(rayIntersectEndPoint.x,rayIntersectEndPoint.z);


            // 有效区域
            Ogre::Rect validRect = mChunk->getBoundingRect();

            // 截断有效区域
            if ( MGEngineUtility::clampLineInRect( checkStartPos, checkEndPos, validRect ) == false )
                return false;

            rayIntersectStartPoint.x = checkStartPos.x;
            rayIntersectStartPoint.z = checkStartPos.y;

            rayIntersectEndPoint.x   = checkEndPos.x;
            rayIntersectEndPoint.z   = checkEndPos.y;

            //////////////////////////////////////////////////////////////////////////////////////////////


            /* // 顶点坐标
            +y
            |
            |
            v0----0----v1
            |          |
            3  [Grid]  1
            |          |
            v2----2----v3----+x
            */


            // 根据方向的象限 , 判断网格需要检测的2线段

            Int checkLineIndex[2];

            if ( (checkDir.x > 0) &&  (checkDir.z < 0) )
            {
                checkLineIndex[0] = 0;
                checkLineIndex[1] = 1;
            }else
            if ( (checkDir.x > 0) &&  (checkDir.z > 0) )
            {
                checkLineIndex[0] = 1;
                checkLineIndex[1] = 2;
            }else
            if ( (checkDir.x < 0) &&  (checkDir.z > 0) )
            {
                checkLineIndex[0] = 2;
                checkLineIndex[1] = 3;
            }else
            if ( (checkDir.x < 0) &&  (checkDir.z < 0) )
            {
                checkLineIndex[0] = 3;
                checkLineIndex[1] = 0;
            }else
            if ( (checkDir.x == 0) &&  (checkDir.z > 0) )
            {
                checkLineIndex[0] = 2;
                checkLineIndex[1] = -1;
            }else
            if ( (checkDir.x == 0) &&  (checkDir.z < 0) )
            {
                checkLineIndex[0] = 0;
                checkLineIndex[1] = -1;
            }else
            if ( (checkDir.x > 0) &&  (checkDir.z == 0) )
            {
                checkLineIndex[0] = 1;
                checkLineIndex[1] = -1;
            }else
            if ( (checkDir.x < 0) &&  (checkDir.z == 0) )
            {
                checkLineIndex[0] = 3;
                checkLineIndex[1] = -1;
            }

            //////////////////////////////////////////////////////////////////////////////////////////////

            Vector3 vertexPointStart;
            this->convertWorldPositionToVertexPoint(rayIntersectStartPoint,&vertexPointStart);
            Vector3 vertexPointEnd;
            this->convertWorldPositionToVertexPoint(rayIntersectEndPoint,&vertexPointEnd);


            // 顶点检测点
            VecI2 vertexCheckPoint;
            vertexCheckPoint.x = vertexPointStart.x;
            vertexCheckPoint.y = vertexPointStart.y;

            //////////////////////////////////////////////////////////////////////////////////////////////


            // 检测网格线段和方向线段的相交
            // 得出下一个检测的网格
            Bool isSegmentsIntersect = false;

            for( UInt i= 0; i<=checkCount; i++)
            {

                //////////////////////////////////////////////////////////////////////////////////////////////

                // 检测射线与网格的相交点
                if (getRayIntersectionTri3DInGridByVertexPoint(ray, vertexCheckPoint.x, vertexCheckPoint.y, intersectPos))
                {
                    return true;
                }

                //////////////////////////////////////////////////////////////////////////////////////////////

                
                long startX = static_cast<long>(vertexCheckPoint.x);
                long startY = static_cast<long>(vertexCheckPoint.y);
                long endX = startX + 1;
                long endY = startY + 1;

                VecI2 v0,v1,v2,v3;

                v0 = VecI2(startX, endY);
                v1 = VecI2(endX, endY);
                v2 = VecI2(startX, startY);
                v3 = VecI2(endX, startY);

                for( UInt j= 0; j<2; j++)
                {
                    Int index = checkLineIndex[j];

                    Vector2 checkPos1,checkPos2;

                    if ( index == 0 )
                    {
                        convertVertexPointToWorldPosition(v0.x, v0.y, &checkPos1);
                        convertVertexPointToWorldPosition(v1.x, v1.y, &checkPos2);

                        vertexCheckPoint = v0;
                    }else
                    if ( index == 1 )
                    {
                        convertVertexPointToWorldPosition(v1.x, v1.y, &checkPos1);
                        convertVertexPointToWorldPosition(v3.x, v3.y, &checkPos2);

                        vertexCheckPoint = v3;
                    }else
                    if ( index == 2 )
                    {
                        convertVertexPointToWorldPosition(v3.x, v3.y, &checkPos1);
                        convertVertexPointToWorldPosition(v2.x, v2.y, &checkPos2);

                        vertexCheckPoint = v2;
                        vertexCheckPoint.y--;

                    }else
                    if ( index == 3 )
                    {
                        convertVertexPointToWorldPosition(v2.x, v2.y, &checkPos1);
                        convertVertexPointToWorldPosition(v0.x, v0.y, &checkPos2);

                        vertexCheckPoint = v2;
                        vertexCheckPoint.x--;
                    }else
                    {
                        break;
                    }

                    Vector2 INP;
                    //if ( MGEngineUtility::isTwoSegmentsIntersect2D(checkPos1,checkPos2,checkStartPos,checkEndPos) )
                    if ( MGEngineUtility::calculateIntersectPoint(checkPos1, checkPos2-checkPos1, checkStartPos, checkEndPos-checkStartPos, INP) )
                    {
                        isSegmentsIntersect = true;
                        break;
                    }else
                    {
                        isSegmentsIntersect = false;
                    }

                }
                
                //////////////////////////////////////////////////////////////////////////////////////////////

                if ( isSegmentsIntersect == false )
                {
                    break;
                }
            }
            //////////////////////////////////////////////////////////////////////////////////////////////
        }else
        {
            //射线查询基础平面
            Plane plane( Vector3(0,1,0), Vector3(0,0,0) );
            std::pair< bool, Real > intersect = ray.intersects(plane);
            if ( intersect.first )
            {
                // convert distance to vector
                Vector3 point   = ray.getPoint( intersect.second );	
                intersectPos    = Vec3(point.x,point.y,point.z);
                return true;
            }
        }

        return false;
    }
    //---------------------------------------------------------------------
    Bool TerrainSurface::getRayIntersection2(Vec3& pos, Vec3& dir, Vec3& intersectPos, Bool isPrecise)
    {
        //射线声明
        Ogre::Ray ray(Vector3(pos.x,pos.y,pos.z),Vector3(dir.x,dir.y,dir.z));

        if ( isPrecise )
        {
            Plane maxPlane;
            Plane minPlane;

            if ( dir.y != 0 )
            {
                maxPlane = Plane( Vector3(0,1,0), Vector3( 0, getMaxHeight(), 0) );
                minPlane = Plane( Vector3(0,1,0), Vector3( 0, getMinHeight(), 0) );
            }else
            {
                //TODO:
                //dir.y == 0
                DYNAMIC_ASSERT( false );
            }


            ////////////////////////////////////////////////////////////////////////////

            //射线查询高低2个平面
            Vector3 rayIntersectMaxPoint;
            Vector3 rayIntersectMinPoint;


            std::pair< bool, Real > intersect1 = ray.intersects(maxPlane);
            std::pair< bool, Real > intersect2 = ray.intersects(minPlane);

            if ( intersect1.first || intersect2.first )
            {
                if ( intersect1.first && intersect2.first )
                {
                    rayIntersectMaxPoint   = ray.getPoint( intersect1.second );	
                    rayIntersectMinPoint   = ray.getPoint( intersect2.second );	
                }else
                if ( intersect1.first && !intersect2.first )
                {
                    rayIntersectMaxPoint = Vector3(pos.x,pos.y,pos.z);
                    rayIntersectMinPoint = ray.getPoint( intersect1.second );	
                }else
                if ( !intersect1.first && intersect2.first )
                {
                    rayIntersectMaxPoint = Vector3(pos.x,pos.y,pos.z);	
                    rayIntersectMinPoint = ray.getPoint( intersect2.second );
                }
            }else
            {
                return false;
            }

           
            //////////////////////////////////////////////////////////////////////////////////////////////

            // 有效区域
            Ogre::Rect validRect = mChunk->getBoundingRect();

            //////////////////////////////////////////////////////////////////////////////////////////////
            
            // TODO:
            // 现在使用射线逼近算法
            // 需要修改为网格逼近算法

            //////////////////////////////////////////////////////////////////////////////////////////////

            // 检测方向
            Vector3 checkDir            = (rayIntersectMinPoint - rayIntersectMaxPoint);	
            Vector3 checkVerticalDir    = MGEngineUtility::getNormaliseVerticalVector( checkDir );
            
            Vector2 check2DDir          = Vector2(checkDir.x,checkDir.z);	
            Vector2 checkNormal2DDir    = check2DDir.normalisedCopy();	
            Vector2 checkUnit2DDir      = checkNormal2DDir * mVertexOffset;	

            Vector2 check2DVDir         = Vector2(checkDir.x,checkDir.z);	
            Vector2 checkNormal2DVDir   = checkNormal2DDir.normalisedCopy();	
            Vector2 checkUnit2DVDir1    = checkNormal2DVDir * mVertexOffset;	
            Vector2 checkUnit2DVDir2    = -checkUnit2DVDir1;	

            Flt     checkLenght         = check2DDir.length();
            Flt     halfcheckLenght     = checkLenght * 0.5;
            UInt    checkCount          = checkLenght  / mVertexOffset + 1;

            Vector2 check2DPoint        = Vector2(rayIntersectMaxPoint.x,rayIntersectMaxPoint.z);
			Vector2 check2DBasePoint	= check2DPoint;
            Vector3 checkWorldPos;

            Vector2 checkWorld2DPos1;
            Vector2 checkWorld2DPos2;
            Vector3 checkWorldPos1;
            Vector3 checkWorldPos2;
            for( UInt i= 0; i<=checkCount; i++)
            {
                check2DPoint = check2DBasePoint + checkUnit2DDir * i;

                checkWorldPos = Vector3( check2DPoint.x, 0, check2DPoint.y );
                if ( checkWorldPos.x >= validRect.left && checkWorldPos.x <= validRect.right )
                {
                    if ( checkWorldPos.z >= validRect.top && checkWorldPos.z <= validRect.bottom )
                    {
                        if (getRayIntersectionTri3DInGridByWorldPosition(ray, checkWorldPos, intersectPos))
                        {
                            return true;
                        }

                        checkWorld2DPos1 = check2DPoint + checkUnit2DVDir1;
                        checkWorldPos1   = Vector3( checkWorld2DPos1.x, 0, checkWorld2DPos1.y );
                        if (getRayIntersectionTri3DInGridByWorldPosition(ray, checkWorldPos1, intersectPos))
                        {
                            return true;
                        }

                        checkWorld2DPos2 = check2DPoint + checkUnit2DVDir2;
                        checkWorldPos2   = Vector3( checkWorld2DPos2.x, 0, checkWorld2DPos2.y );
                        if (getRayIntersectionTri3DInGridByWorldPosition(ray, checkWorldPos2, intersectPos))
                        {
                            return true;
                        }
                    }
                }
            }

            //////////////////////////////////////////////////////////////////////////////////////////////
            
            
            //// 查询区域
            //Ogre::FloatRect rayIntersectRect;
            //rayIntersectRect.left   = min( rayIntersectMaxPoint.x, rayIntersectMinPoint.x );
            //rayIntersectRect.right  = max( rayIntersectMaxPoint.x, rayIntersectMinPoint.x );
            //rayIntersectRect.top    = min( rayIntersectMaxPoint.z, rayIntersectMinPoint.z );
            //rayIntersectRect.bottom = max( rayIntersectMaxPoint.z, rayIntersectMinPoint.z );

            //Flt slope = Flt(rayIntersectMinPoint.x - rayIntersectMaxPoint.x) / Flt(rayIntersectMinPoint.x - rayIntersectMaxPoint.x);
            //Flt xOffset = mVertexOffset;
            //Flt yOffset = xOffset * slope;

            //Flt vy = rayIntersectRect.top;
            //Vector3 checkWorldPos;
            //for ( Flt vx = rayIntersectRect.left; vx<=rayIntersectRect.right;  )
            //{
            //    checkWorldPos = Vector3( vx, 0, vy );

            //    if ( checkWorldPos.x >= validRect.left && checkWorldPos.x <= validRect.right )
            //    {
            //        if ( checkWorldPos.z >= validRect.top && checkWorldPos.z <= validRect.bottom )
            //        {
            //            if (getRayIntersectionTri3D(ray, checkWorldPos, intersectPos))
            //            {
            //                return true;
            //            }
            //        }
            //    }

            //    vx += xOffset;
            //    vy += yOffset;
            //}
            
        }else
        {
            //射线查询基础平面
            Plane plane( Vector3(0,1,0), Vector3(0,0,0) );
            std::pair< bool, Real > intersect = ray.intersects(plane);
            if ( intersect.first )
            {
                // convert distance to vector
                Vector3 point   = ray.getPoint( intersect.second );	
                point.y         = getHeightAtWorldPosition(point.x,point.z);
                intersectPos    = Vec3(point.x,point.y,point.z);
                return true;
            }
        }

        return false;
    }

    //---------------------------------------------------------------------
    Bool TerrainSurface::getRayIntersectionTri3DInGridByVertexPoint( Ogre::Ray& ray, UInt x, UInt y, Vec3& intersectPos )
    {
        std::pair< bool, Real > intersect;

        Triangle3D tri3D1;
        Triangle3D tri3D2;

        if ( getTerrainTri3DByVertexPoint(x,y,tri3D1,tri3D2) == true )
        {
            intersect = ray.intersects( tri3D1.plane );
            if ( intersect.first )
            {
                Vector3 terrainPos = ray.getPoint( intersect.second );	

                if ( Math::pointInTri3D(terrainPos,tri3D1.t0,tri3D1.t1,tri3D1.t2,tri3D1.plane.normal) )
                {
                    intersectPos = Vec3(terrainPos.x,terrainPos.y,terrainPos.z);
                    return true;
                }
            }

            intersect = ray.intersects( tri3D2.plane );
            if ( intersect.first )
            {
                Vector3 terrainPos = ray.getPoint( intersect.second );	

                if ( Math::pointInTri3D(terrainPos,tri3D2.t0,tri3D2.t1,tri3D2.t2,tri3D2.plane.normal) )
                {
                    intersectPos = Vec3(terrainPos.x,terrainPos.y,terrainPos.z);
                    return true;
                }
            }
        }

        return false;
    }

    //---------------------------------------------------------------------
    Bool TerrainSurface::getRayIntersectionTri3DInGridByWorldPosition( Ogre::Ray& ray, Vector3& worldPos, Vec3& intersectPos )
    {
        Vector3 vertexPoint;

        convertWorldPositionToVertexPoint(Vector3(worldPos.x,0,worldPos.z), &vertexPoint);

        return getRayIntersectionTri3DInGridByVertexPoint( ray, vertexPoint.x, vertexPoint.y, intersectPos);
    }
    //---------------------------------------------------------------------
    Flt* TerrainSurface::getHeightData(Int x, Int y) const
    {
        x = Ogre::Math::Clamp( x, (Int)0 , (Int)(mVertexSideNum - 1) );
        y = Ogre::Math::Clamp( y, (Int)0 , (Int)(mVertexSideNum - 1) );

        //DYNAMIC_ASSERT (x >= 0 && x < mVertexSideNum && y >= 0 && y < mVertexSideNum);

        return &mHeightData[y * mVertexSideNum + x];
    }

    //-----------------------------------------------------------------------
    Bool TerrainSurface::hasHeightData() const
    {
        if ( mVertexSideNum == 0 )
            return false;
        return true;
    }

    //-----------------------------------------------------------------------
    Flt TerrainSurface::getHeightAtPoint(Int x, Int y)
    {
        const TerrainSurface* validSurface = this;

        Flt height = 0;

        if (!mHeightData)
            return 0;

        /////////////////////////////////////////////////////////
        Vec2 indexVec2 = mChunk->getTerrainGroupIndex();
        Int newX = x;
        Int newY = y;

        Bool isExceed = false;

        if ( x < 0 )
        {
            indexVec2.x -= 1;
            if ( indexVec2.x == 0 )
                indexVec2.x = -1;
            
            newX = mVertexSideNum - 2;

            isExceed = true;
        }else
        if ( x >= Int(mVertexSideNum) )
        {
            indexVec2.x += 1;
            if ( indexVec2.x == 0 )
                indexVec2.x = 1;

            newX = 1;

            isExceed = true;
        }

        if ( y < 0 )
        {
            indexVec2.y -= 1;
            if ( indexVec2.y == 0 )
                indexVec2.y = -1;

            newY = mVertexSideNum - 2; 

            isExceed = true;
        }else
        if ( y >= Int(mVertexSideNum) )
        {
            indexVec2.y += 1;
            if ( indexVec2.y == 0 )
                indexVec2.y = 1;

            newY = 1;

            isExceed = true;
        }

        /////////////////////////////////////////////////////////

        if ( isExceed )
        {
            TerrainChunk* newChunk = mTerrainMgr->getTerrainChunk( indexVec2.x , indexVec2.y );

            if ( newChunk )
            {
                if ( newChunk != mChunk )
                {
                    validSurface = newChunk->getTerrainSurface( this->getType() );
                    if ( validSurface->hasHeightData() )
                    {
                        /////////////////////////////////////////////////////////////////////
                        //TEST:    

                        //if ( x < 0 )
                        //{
                        //    Flt height1 =  *this->getHeightData(x, y);
                        //    Flt height2 =  *validSurface->getHeightData(mVertexSideNum - 1 , y);

                        //    DYNAMIC_ASSERT( height1 == height2 );
                        //}else
                        //if ( x >= mVertexSideNum )
                        //{
                        //    Flt height1 =  *this->getHeightData(x, y);
                        //    Flt height2 =  *validSurface->getHeightData(0 , y);

                        //    DYNAMIC_ASSERT( height1 == height2 );
                        //}

                        /////////////////////////////////////////////////////////////////////


                        x = newX;
                        y = newY;

                    }else
                    {
                        validSurface = this;
                    }
                }
            }
        }
        
        if ( validSurface )
        {
            /////////////////////////////////////////////////////////
            // clamp
            height = * validSurface->getHeightData(x, y);
        }

        /////////////////////////////////////////////////////////

        return height;
    }
    //-----------------------------------------------------------------------
    void TerrainSurface::setHeightAtPoint(Int x, Int y, Flt h)
    {
        // clamp
        x = Ogre::Math::Clamp(x,(Int)0,(Int)(mVertexSideNum - 1));
        y = Ogre::Math::Clamp(y,(Int)0,(Int)(mVertexSideNum - 1));

        h = Ogre::Math::Clamp(h,(Flt)mHeightMin,(Flt)(mHeightMax));

        *getHeightData(x, y) = h;

        ////////////////////////////////////////////////////////////

        dirtyRect(x,y);
    }
    //-----------------------------------------------------------------------
    void TerrainSurface::getTerrainPlaneByWorldPosition(Flt x, Flt y, 
        Vector3& p0, Vector3& p1, Vector3& p2, Vector3& p3)
    {
        Vector3 terrPoint;
        convertWorldPositionToVertexPoint(Vector3(x,0,y), &terrPoint);

        /*
        0    1
        *----*
        |    |  
        2    3
        *----*
        */
        Vector3 terrPoint0 = terrPoint;
        Vector3 terrPoint1 = terrPoint;
        Vector3 terrPoint2 = terrPoint;
        Vector3 terrPoint3 = terrPoint;

        terrPoint0.y += 1;
        terrPoint1.x += 1;
        terrPoint1.y += 1;
        terrPoint3.x += 1;

        convertVertexPointToWorldPosition(terrPoint0.x,terrPoint0.y,&p0);
        convertVertexPointToWorldPosition(terrPoint1.x,terrPoint1.y,&p1);
        convertVertexPointToWorldPosition(terrPoint2.x,terrPoint2.y,&p2);
        convertVertexPointToWorldPosition(terrPoint3.x,terrPoint3.y,&p3);
    }

    //-----------------------------------------------------------------------
    Bool TerrainSurface::getTerrainTri3DByVertexPoint(UInt x, UInt y, 
        Triangle3D& tri3D1, Triangle3D& tri3D2)
    {
        long startX = static_cast<long>(x);
        long startY = static_cast<long>(y);
        long endX = startX + 1;
        long endY = startY + 1;

        /* For even / odd tri strip rows, triangles are this shape:
        even     odd
        3---2   3---2
        | / |   | \ |
        0---1   0---1
        */


        // Build all 4 positions in terrain space, using point-sampled height
        Vector3 p0,p1,p2,p3;
        Vector3 v0,v1,v2,v3;

        v0 = Vector3(startX, startY, getHeightAtPoint(startX, startY));
        v1 = Vector3(endX, startY,   getHeightAtPoint(endX, startY));
        v2 = Vector3(endX, endY,     getHeightAtPoint(endX, endY));
        v3 = Vector3(startX, endY,   getHeightAtPoint(startX, endY));
        
        /////////////////////////////////////////////////////////////////////////////////
   
        convertVertexPointToWorldPosition(v0,&p0);
        convertVertexPointToWorldPosition(v1,&p1);
        convertVertexPointToWorldPosition(v2,&p2);
        convertVertexPointToWorldPosition(v3,&p3);

        v0 = p0;
        v1 = p1;
        v2 = p2;
        v3 = p3;

        /////////////////////////////////////////////////////////////////////////////////
        
        // define this plane in terrain space


        //TODO:
        // 由于计算精度有问题，现在临时把2个三角面都提交给外部
        // 之后需要查出原因修改

        if (startY % 2)
        {
            // odd row
            //bool secondTri = ((1.0 - yParam) > xParam);
            //if (secondTri)
            //{
            //    tri3D1.t0 = v0;
            //    tri3D1.t1 = v1;
            //    tri3D1.t2 = v3;

            //    tri3D1.plane.redefine(v0, v1, v3);
            //}
            //else
            //{
            //    tri3D1.t0 = v1;
            //    tri3D1.t1 = v2;
            //    tri3D1.t2 = v3;

            //    tri3D1.plane.redefine(v1, v2, v3);
            //}

            tri3D1.t0 = v0;
            tri3D1.t1 = v1;
            tri3D1.t2 = v3;
            tri3D1.plane.redefine(v0, v1, v3);

            tri3D2.t0 = v2;
            tri3D2.t1 = v3;
            tri3D2.t2 = v1;
            tri3D2.plane.redefine(v2, v3, v1);
        }
        else
        {
            // even row
            //bool secondTri = (yParam > xParam);
            //if (secondTri)
            //{
            //    tri3D1.t0 = v0;
            //    tri3D1.t1 = v2;
            //    tri3D1.t2 = v3;

            //    tri3D1.plane.redefine(v0, v2, v3);
            //}else
            //{
            //    tri3D1.t0 = v0;
            //    tri3D1.t1 = v1;
            //    tri3D1.t2 = v2;

            //    tri3D1.plane.redefine(v0, v1, v2);
            //}


            tri3D1.t0 = v0;
            tri3D1.t1 = v2;
            tri3D1.t2 = v3;
            tri3D1.plane.redefine(v0, v2, v3);

            tri3D2.t0 = v1;
            tri3D2.t1 = v2;
            tri3D2.t2 = v0;
            tri3D2.plane.redefine(v1, v2, v0);

        }

        {
            if ( tri3D1.plane.normal.y == 0 )
                return false;
            if ( tri3D2.plane.normal.y == 0 )
                return false;
        }

        return true;
    }

    //-----------------------------------------------------------------------
    Bool TerrainSurface::getTerrainTri3DByTerrainPosition(Flt x, Flt y, 
        Triangle3D& tri3D1, Triangle3D& tri3D2)
    {
        if (!mHeightData)
            return false;

        // get left / bottom points (rounded down)
        Real factor = (Real)mVertexSideNum - 1.0f;
        Real invFactor = 1.0f / factor;

        long startX = static_cast<long>(x * factor);
        long startY = static_cast<long>(y * factor);

        return getTerrainTri3DByVertexPoint(startX,startY,tri3D1,tri3D2);
    }

    //-----------------------------------------------------------------------
    Flt TerrainSurface::getHeightAtWorldPosition(Real x, Real y)
    {
        Triangle3D tri3D1;
        Triangle3D tri3D2;
        Vector3 vertexPoint;

        convertWorldPositionToVertexPoint(Vector3(x,0,y), &vertexPoint);
        if ( getTerrainTri3DByVertexPoint(vertexPoint.x,vertexPoint.y,tri3D1,tri3D2) == false )
            return 0;

        return (-tri3D1.plane.normal.x * x 
            -tri3D1.plane.normal.z * y
            - tri3D1.plane.d) / tri3D1.plane.normal.y;
    }

    //-----------------------------------------------------------------------
    void TerrainSurface::convertVertexPointToWorldPosition(long x, long y,  Vector2* outWSpos)
    {
        Vector3 outW3DSpos;
        convertVertexPointToWorldPosition(x, y, 0, &outW3DSpos);
        outWSpos->x = outW3DSpos.x;
        outWSpos->y = outW3DSpos.z;
    }

    //-----------------------------------------------------------------------
    void TerrainSurface::convertVertexPointToWorldPosition(const Vector3& VSpos, Vector3* outWSpos)
    {
        convertVertexPointToWorldPosition(VSpos.x, VSpos.y, VSpos.z, outWSpos);
    }

    //-----------------------------------------------------------------------
    void TerrainSurface::convertVertexPointToWorldPosition(long x, long y, Vector3* outWSpos)
    {
        Flt height = getHeightAtPoint( x, y );

        convertVertexPointToWorldPosition(x,y,height,outWSpos);
    }
    //-----------------------------------------------------------------------
    void TerrainSurface::convertVertexPointToWorldPosition(long x, long y, float height, Vector3* outWSpos)
    {
        Vec2 leftBottomPos = getLeftBottomPos();

        outWSpos->y = height;
        outWSpos->x =   x * mVertexOffset   + leftBottomPos.x ;
        outWSpos->z = -(y * mVertexOffset ) + leftBottomPos.y ;
    }
    //-----------------------------------------------------------------------
    void TerrainSurface::convertWorldPositionToVertexPoint(const Vector3& WSpos, Vector3* outWSpos)
    {
        Vec2 leftBottomPos = getLeftBottomPos();
        Vector3 wspos_safe = WSpos;
        wspos_safe.x -= leftBottomPos.x;
        wspos_safe.z -= leftBottomPos.y;

        if ( wspos_safe.x < 0 )
            wspos_safe.x = 0;
        if ( wspos_safe.z > 0 )
            wspos_safe.z = 0;

        outWSpos->z = wspos_safe.y;
        outWSpos->x = Int(  ( wspos_safe.x )  / (mVertexOffset)  );
        outWSpos->y = Int(  ( -wspos_safe.z ) / (mVertexOffset)  ); 
    }
    //-----------------------------------------------------------------------
    void TerrainSurface::convertWorldPositionToTerrainPosition(const Vector3& WSpos, Vector3* outTSpos)
    {
        Vec2 leftBottomPos = getLeftBottomPos();
        Vector3 wspos_safe = WSpos;
        wspos_safe.x -= leftBottomPos.x;
        wspos_safe.z -= leftBottomPos.y;

        outTSpos->x = (wspos_safe.x)  / getWorldSize();
        outTSpos->y = (-wspos_safe.z) / getWorldSize();
        outTSpos->z = wspos_safe.y;
    }
    //-----------------------------------------------------------------------
    void TerrainSurface::convertTerrainPositionToWorldPosition(const Vector3& TSpos, Vector3* outWSpos)
    {
        convertTerrainPositionToWorldPosition(TSpos.x,TSpos.y,TSpos.z,outWSpos);
    }
    //-----------------------------------------------------------------------
    void TerrainSurface::convertTerrainPositionToWorldPosition(Real x, Real y, Real z, Vector3* outWSpos)
    {
        Vec2 leftBottomPos = getLeftBottomPos();

        outWSpos->y = z;
        outWSpos->x =    x * getWorldSize()   + leftBottomPos.x ;
        outWSpos->z = -( y * getWorldSize() ) + leftBottomPos.y ;
    }

    //---------------------------------------------------------------------
    Vector3 TerrainSurface::convertPositionSpace(TerrainSurfaceSpace inSpace, const Vector3& inPos, TerrainSurfaceSpace outSpace) const
    {
        Vector3 ret;
        convertPositionSpace(inSpace, inPos, outSpace, ret);
        return ret;
    }
    //---------------------------------------------------------------------
    Vector3 TerrainSurface::convertDirectionSpace(TerrainSurfaceSpace inSpace, const Vector3& inDir, TerrainSurfaceSpace outSpace) const
    {
        Vector3 ret;
        convertDirectionSpace(inSpace, inDir, outSpace, ret);
        return ret;
    }
    //---------------------------------------------------------------------
    void TerrainSurface::convertPositionSpace(TerrainSurfaceSpace inSpace, const Vector3& inPos, TerrainSurfaceSpace outSpace, Vector3& outPos) const
    {
        convertSpace(inSpace, inPos, outSpace, outPos, true);
    }
    //---------------------------------------------------------------------
    void TerrainSurface::convertDirectionSpace(TerrainSurfaceSpace inSpace, const Vector3& inDir, TerrainSurfaceSpace outSpace, Vector3& outDir) const
    {
        convertSpace(inSpace, inDir, outSpace, outDir, false);
    }
    //---------------------------------------------------------------------
    void TerrainSurface::convertSpace(TerrainSurfaceSpace inSpace, const Vector3& inVec, TerrainSurfaceSpace outSpace, Vector3& outVec, bool translation) const
    {
        TerrainSurfaceSpace currSpace = inSpace;
        outVec = inVec;
        while (currSpace != outSpace)
        {
            switch(currSpace)
            {
            case WORLD_SPACE:
                // In all cases, transition to local space
                if (translation)
                    outVec -= mPos;
                currSpace = LOCAL_SPACE;
                break;
            case LOCAL_SPACE:
                switch(outSpace)
                {
                case WORLD_SPACE:
                    if (translation)
                        outVec += mPos;
                    currSpace = WORLD_SPACE;
                    break;
                case POINT_SPACE:
                case TERRAIN_SPACE:
                    // go via terrain space
                    outVec = convertWorldToTerrainAxes(outVec);
                    if (translation)
                    {
                        outVec.x -= mBaseOffset; outVec.y -= mBaseOffset;
                        outVec.x /= (mVertexOffset - 1); outVec.y /= (mVertexOffset - 1);
                    }
                    currSpace = TERRAIN_SPACE;
                    break;
                case LOCAL_SPACE:
                default:
                    break;
                };
                break;
            case TERRAIN_SPACE:
                switch(outSpace)
                {
                case WORLD_SPACE:
                case LOCAL_SPACE:
                    // go via local space
                    if (translation)
                    {
                        outVec.x *= (mVertexOffset - 1); outVec.y *= (mVertexOffset - 1);
                        outVec.x += mBaseOffset; outVec.y += mBaseOffset;
                    }
                    outVec = convertTerrainToWorldAxes(outVec);
                    currSpace = LOCAL_SPACE;
                    break;
                case POINT_SPACE:
                    if (translation)
                    {
                        outVec.x *= (mVertexOffset - 1); outVec.y *= (mVertexOffset - 1); 
                        // rounding up/down
                        // this is why POINT_SPACE is the last on the list, because it loses data
                        outVec.x = static_cast<Real>(static_cast<int>(outVec.x + 0.5));
                        outVec.y = static_cast<Real>(static_cast<int>(outVec.y + 0.5));
                    }
                    currSpace = POINT_SPACE;
                    break;
                case TERRAIN_SPACE:
                default:
                    break;
                };
                break;
            case POINT_SPACE:
                // always go via terrain space
                if (translation)
                    outVec.x /= (mVertexOffset - 1); outVec.y /= (mVertexOffset - 1); 
                currSpace = TERRAIN_SPACE;
                break;

            };
        }

    }
    //---------------------------------------------------------------------
    Vector3 TerrainSurface::convertWorldToTerrainAxes(const Vector3& inVec) const
    {
        Vector3 ret;
        convertWorldToTerrainAxes(inVec, &ret);

        return ret;
    }
    //---------------------------------------------------------------------
    Vector3 TerrainSurface::convertTerrainToWorldAxes(const Vector3& inVec) const
    {
        Vector3 ret;
        convertTerrainToWorldAxes(inVec, &ret);

        return ret;
    }
    //---------------------------------------------------------------------
    void TerrainSurface::convertWorldToTerrainAxes(const Vector3& worldVec, Vector3* terrainVec) 
    {
        //ALIGN_X_Z:
        terrainVec->z = worldVec.y;
        terrainVec->x = worldVec.x;
        terrainVec->y = -worldVec.z;
    }
    //---------------------------------------------------------------------
    void TerrainSurface::convertTerrainToWorldAxes(const Vector3& terrainVec, Vector3* worldVec)
    {
        //ALIGN_X_Z:
        worldVec->x = terrainVec.x;
        worldVec->y = terrainVec.z;
        worldVec->z = -terrainVec.y;
    }



    //---------------------------------------------------------------------
    void TerrainSurface::widenRectByVector(const Vector3& vec, const Rect& inRect, Rect& outRect)
    {
        widenRectByVector(vec, inRect, getMinHeight(), getMaxHeight(), outRect);
    }
    //---------------------------------------------------------------------
    void TerrainSurface::widenRectByVector(const Vector3& vec, const Rect& inRect, 
        Real minHeight, Real maxHeight, Rect& outRect)
    {
        outRect = inRect;

        Plane p;

        p.redefine(Vector3::UNIT_Y, Vector3(0, vec.y < 0.0 ? minHeight : maxHeight, 0));

        float verticalVal = vec.dotProduct(p.normal);

        if (Math::RealEqual(verticalVal, 0.0))
            return;

        Vector3 corners[4];
        Real startHeight = verticalVal < 0.0 ? maxHeight : minHeight;
        convertVertexPointToWorldPosition(inRect.left, inRect.top, startHeight, &corners[0]);
        convertVertexPointToWorldPosition(inRect.right-1, inRect.top, startHeight, &corners[1]);
        convertVertexPointToWorldPosition(inRect.left, inRect.bottom-1, startHeight, &corners[2]);
        convertVertexPointToWorldPosition(inRect.right-1, inRect.bottom-1, startHeight, &corners[3]);

        for (int i = 0; i < 4; ++i)
        {
            Ray ray(corners[i] + mPos, vec);
            std::pair<bool, Real> rayHit = ray.intersects(p);
            if(rayHit.first)
            {
                Vector3 pt = ray.getPoint(rayHit.second);
                // convert back to terrain point
                Vector3 terrainHitPos;
                convertWorldPositionToTerrainPosition(pt, &terrainHitPos);
                // build rectangle which has rounded down & rounded up values
                // remember right & bottom are exclusive
                Rect mergeRect(
                    (long)(terrainHitPos.x * (mVertexSideNum - 1)), 
                    (long)(terrainHitPos.y * (mVertexSideNum - 1)), 
                    (long)(terrainHitPos.x * (float)(mVertexSideNum - 1) + 0.5) + 1, 
                    (long)(terrainHitPos.y * (float)(mVertexSideNum - 1) + 0.5) + 1
                    );
                outRect.merge(mergeRect);
            }
        }

    }

    //**********************************************************************************************************************
    //**********************************************************************************************************************


    //---------------------------------------------------------------------
    void TerrainSurface::loadHeightData( Str path, Str filename )
    {
        unLoadHeightData();

        ////////////////////////////////////////////////////////////////////////

        Int vertexNum   = mVertexSideNum * mVertexSideNum;

        UInt heightDataSize = sizeof(Flt)*(vertexNum + 1);
        mHeightData = (Flt*)RamAlloc::getInstance().get( heightDataSize );
        DYNAMIC_ASSERT_LOG( mHeightData!=NULL, "loadHeightData mHeightData failed" );

        memset(mHeightData, 0, sizeof(mHeightData));
        mHeightDataCreated = true;

        //TODO:
        //加载高度图，高度图数据需要匹配顶点数量
        if ( Ogre::ResourceGroupManager::getSingleton().resourceExists( path.c_str() ,filename) )
        {
            Ogre::Image img;
            img.load(filename, path.c_str());

            if (img.getWidth() != mVertexSideNum || img.getHeight() != mVertexSideNum)
                img.resize(mVertexSideNum, mVertexSideNum);

            // convert image data to floats
            // Do this on a row-by-row basis, because we describe the terrain in
            // a bottom-up fashion (ie ascending world coords), while Image is top-down
            unsigned char* pSrcBase = img.getData();
            size_t depth            = img.getDepth();
            float* pDst             = 0;
            unsigned char* pSrc     = 0;
            size_t rowSpan          = img.getRowSpan();
            PixelFormat imgFormat   = img.getFormat();

            for (size_t i = 0; i < mVertexSideNum; ++i)
            {
                // 图片像素行头移动
                size_t srcy = mVertexSideNum - i - 1;
                pSrc = pSrcBase + srcy * rowSpan;
                // 内存像素行头移动
                pDst = mHeightData + i * mVertexSideNum;
                // 转变图片行像素位数据到内存像素位(根据各自的格式)
                PixelUtil::bulkPixelConversion(pSrc, imgFormat, 
                    pDst, PF_FLOAT32_R, mVertexSideNum);
            }

            if ( !Math::RealEqual( mHeightScale, 1.0 ) )
            {
                float* pAdj = mHeightData;
                for (Int i = 0; i < vertexNum; ++i)
                {
                    *pAdj = (*pAdj * 2 - 1) * mHeightScale;	
                    ++pAdj;
                }
            }
        }
        
    }
    //---------------------------------------------------------------------
    void TerrainSurface::saveHeightData(Str path, Str filename)
    {
        PixelFormat heightFormat    = PF_FLOAT32_R;
        PixelFormat imgFormat       = PF_L16;
        size_t imgFormatSize        = PixelUtil::getNumElemBytes( imgFormat );
        size_t imgSize              = mVertexSideNum * mVertexSideNum * imgFormatSize; 
        size_t imgRowSize           = mVertexSideNum * imgFormatSize;
        void* pixData               = OGRE_MALLOC(imgSize, Ogre::MEMCATEGORY_GENERAL);
        DYNAMIC_ASSERT_LOG( pixData!=NULL, "saveHeightData pixData failed" );

        unsigned char* pImgBase     = (unsigned char*)pixData;

        // 得到一份高度复制数据
        size_t heightElementCount= mVertexSideNum * mVertexSideNum;
        Flt* heightCopyData = (Flt*)RamAlloc::getInstance().get(sizeof(Flt)*(heightElementCount + 1));
        DYNAMIC_ASSERT_LOG( heightCopyData!=NULL, "saveHeightData heightCopyData failed" );

        Flt* pCopy  = heightCopyData;
        Flt* pOri   = mHeightData;
        for (UInt i = 0; i < heightElementCount; ++i)
        {
            *pCopy = ( (*pOri / mHeightScale) + 1 ) / 2;	
            ++pCopy;
            ++pOri;
        }

        // 遍历转换
        float* pHeightPixel         = 0;
        unsigned char* pImgPixel    = 0;
        for (size_t i = 0; i < mVertexSideNum; ++i)
        {
            // 图片像素位移动
            size_t imgY     = mVertexSideNum - i - 1;
            pImgPixel       = pImgBase + imgY * imgRowSize;
            // 内存像素位移动
            pHeightPixel    = heightCopyData + i * mVertexSideNum;

            // 转变图片行像素位数据到内存像素位(根据各自的格式)
            PixelUtil::bulkPixelConversion(pHeightPixel, heightFormat, 
                pImgPixel, imgFormat, mVertexSideNum);
        }

		//如果目录不存在先创建目录
		if ( EngineMain::getInstance().getMode() == EM_EDITOR )
		{
			if (!FileOp::isExistDirectory(path))
				FileOp::createDirectory(path);

			// load, and tell Image to delete the memory when it's done.
			Ogre::Image img;
			img.loadDynamicImage((Ogre::uchar*)pixData, mVertexSideNum, mVertexSideNum, 1, imgFormat, true, 1, 0);
			Str filePath   = FileOp::getFullFilePath( path, filename );
			img.save( filePath );
		}

        // 释放高度复制数据
        RamAlloc::getInstance().release(heightCopyData);
    }
    //---------------------------------------------------------------------
    void TerrainSurface::unLoadHeightData()
    {
        if (mHeightDataCreated)
        {
            RamAlloc::getInstance().release(mHeightData);
            mHeightDataCreated = false;
        }
    }


    //---------------------------------------------------------------------
    void TerrainSurface::updateGeometry()
    {
        if (!mDirtyGeometryRect.isNull())
        {   
            ///////////////////////////////////////////////////////////////////////////////

            refreshNormalTangent( mDirtyGeometryRect );

            ///////////////////////////////////////////////////////////////////////////////

            refreshColors( mDirtyGeometryRect );

            ///////////////////////////////////////////////////////////////////////////////

            //if ( Display::getSingleton().getTerrainLightmapEnabled() )
            //    refreshLightmap( mDirtyGeometryRect );

            ///////////////////////////////////////////////////////////////////////////////

            updateGeometry( mDirtyGeometryRect );

            ///////////////////////////////////////////////////////////////////////////////

			TerrainNodeGrid* node	= getGridData();
			Int nodeSideNum			=   getGridSideNum();
            Int x = 0;
            Int y = 0;
            for( ; x<nodeSideNum; x++ )
            {
                for( y = 0; y<nodeSideNum; y++,node++ )
                {
                    Ogre::Rect tileRect         = node->vertexRectInSurface;
                    Ogre::Rect dirtyTileRect    = mDirtyGeometryRect.intersect(tileRect);

                    if ( dirtyTileRect.isNull() == false )
                    {
                        if ( node->node )
                        {
                            node->node->updateVertex( dirtyTileRect );
                        }
                    }
                }
            }

            ///////////////////////////////////////////////////////////////////////////////

            mDirtyGeometryRect.setNull();
        }
    }


    //**********************************************************************************************************************
    //**********************************************************************************************************************

    //---------------------------------------------------------------------
    void TerrainSurface::loadNormalTangentMapData( Str path, Str normalFilename, Str tangentFileName )
    {
        ////////////////////////////////////////////////////////////////////////

        unLoadNormalTangentMapData();

        ////////////////////////////////////////////////////////////////////////
      
        // 创建内存
        mNTOnePixelNum          = 3;
        Int vertexNum           = mVertexSideNum * mVertexSideNum;
        Int pixelNum            = mNTOnePixelNum * vertexNum;
        mNTPixelNum             = pixelNum;
        mNTDataSize             = sizeof( Flt ) * (pixelNum + 1);

        mNormalData             = (Flt*)RamAlloc::getInstance().get( mNTDataSize );
        DYNAMIC_ASSERT_LOG( mNormalData!=NULL, "loadNormalTangentMapData mNormalData failed" );

        //mTangentData            = (Flt*)RamAlloc::getInstance().get( mNTDataSize );

        memset(mNormalData, 0, mNTDataSize);
        //memset(mTangentData, 0, mNTDataSize);

        ////////////////////////////////////////////////////////////////////////

        Bool isHasNormalFile    = loadNTMapData(path,normalFilename,mNormalData);
        //Bool isHasTangentFile   = loadNTMapData(path,tangentFileName,mTangentData);;

        ////////////////////////////////////////////////////////////////////////
        // 加载文件数据
        if ( !isHasNormalFile )
        {
            Ogre::Rect rect = Ogre::Rect(0,0,mVertexSideNum,mVertexSideNum);
            this->refreshNormalTangent(rect);
            mModified = true;
        }
    }
    
    //---------------------------------------------------------------------
    Bool TerrainSurface::loadNTMapData( Str path, Str filename, Flt*&date )
    {
        ////////////////////////////////////////////////////////////////////////
        // 加载文件数据
        if ( Ogre::ResourceGroupManager::getSingleton().resourceExists( path.c_str() ,filename) )
        {
            ////////////////////////////////////////////////////////////////////////

            Ogre::Image img;
            img.load(filename, path.c_str());
            if (img.getWidth() != mVertexSideNum || img.getHeight() != mVertexSideNum)
                img.resize(mVertexSideNum, mVertexSideNum);

            ////////////////////////////////////////////////////////////////////////

            // 复制文件数据到内存

            // convert image data to floats
            // Do this on a row-by-row basis, because we describe the terrain in
            // a bottom-up fashion (ie ascending world coords), while Image is top-down
            unsigned char* pSrcBase = img.getData();
            size_t depth            = img.getDepth();
            float* pDst             = 0;
            unsigned char* pSrc     = 0;
            size_t rowSpan          = img.getRowSpan();
            PixelFormat imgFormat   = img.getFormat();


            for (size_t i = 0; i < mVertexSideNum; ++i)
            {
                // 图片像素行头移动
                size_t srcy = mVertexSideNum - i - 1;
                pSrc = pSrcBase + srcy * rowSpan;
                // 内存像素行头移动
                pDst = date + i * mVertexSideNum * mNTOnePixelNum;

                // 转变图片行像素位数据到内存像素位(根据各自的格式)
                PixelUtil::bulkPixelConversion(pSrc, imgFormat, 
                    pDst, PF_FLOAT32_RGB, mVertexSideNum);
            }

            // 解压缩
            Flt* pAdj = date;
            for (UInt i = 0; i < mNTPixelNum; ++i)
            {
                *pAdj = (*pAdj) * 2.0f - 1.0f;
                ++pAdj;
            }

            return true;
        }

        return false;
    }

    //---------------------------------------------------------------------
    Bool TerrainSurface::saveNTMapData( Str path, Str filename, Flt*&date )
    {
        if ( !date )
            return false ;

        // 初始化数据
        PixelFormat heightFormat    = PF_FLOAT32_RGB;
        PixelFormat imgFormat       = PF_BYTE_RGB;
        size_t imgFormatSize        = PixelUtil::getNumElemBytes( imgFormat );
        size_t imgSize              = mVertexSideNum * mVertexSideNum * imgFormatSize; 
        size_t imgRowSize           = mVertexSideNum * imgFormatSize;
        void* pixData               = OGRE_MALLOC(imgSize, Ogre::MEMCATEGORY_GENERAL);
        DYNAMIC_ASSERT_LOG( pixData!=NULL, "saveNTMapData pixData failed" );

        unsigned char* pImgBase     = (unsigned char*)pixData;

        //////////////////////////////////////////////////////////////

        // 得到一份内存复制数据
        UInt copyPixelNum           = mNTPixelNum;
        UInt copySize               = mNTDataSize;
        Flt* pBaseCopy              = (Flt*)RamAlloc::getInstance().get( copySize );
        DYNAMIC_ASSERT_LOG( pBaseCopy!=NULL, "saveNTMapData pBaseCopy failed" );

        //////////////////////////////////////////////////////////////

        // 复制和压缩数据
        Flt* pCopy                  = pBaseCopy;
        Flt* pOri                   = date;
        for (UInt i = 0; i < copyPixelNum; ++i)
        {
            *pCopy = ((*pOri) + 1.0f) * 0.5f;
            ++pCopy;
            ++pOri;
        }

        //////////////////////////////////////////////////////////////

        // 复制内存数据到文件数据
        Flt* pCopyPixel             = 0;
        unsigned char* pImgPixel    = 0;
        for (size_t i = 0; i < mVertexSideNum; ++i)
        {
            // 图片像素位移动
            size_t imgY     = mVertexSideNum - i - 1;
            pImgPixel       = pImgBase + imgY * imgRowSize;
            // 内存像素位移动
            pCopyPixel      = pBaseCopy + i * mVertexSideNum * mNTOnePixelNum;

            // 转变图片行像素位数据到内存像素位(根据各自的格式)
            PixelUtil::bulkPixelConversion(pCopyPixel, heightFormat, 
                pImgPixel, imgFormat, mVertexSideNum);
        }

        //////////////////////////////////////////////////////////////
		//如果目录不存在先创建目录
		if ( EngineMain::getInstance().getMode() == EM_EDITOR )
		{
			if (!FileOp::isExistDirectory(path))
				FileOp::createDirectory(path);

			// 保存文件
			// load, and tell Image to delete the memory when it's done.
			Ogre::Image img;
			img.loadDynamicImage((Ogre::uchar*)pixData, mVertexSideNum, mVertexSideNum, 1, imgFormat, true, 1, 0);
			Str filePath   = FileOp::getFullFilePath( path, filename );
			img.save( filePath );
		}

        //////////////////////////////////////////////////////////////

        // 释放高度复制数据
        RamAlloc::getInstance().release(pBaseCopy);

        //////////////////////////////////////////////////////////////

        return true;
    }

    //---------------------------------------------------------------------
    void TerrainSurface::saveNormalTangentMapData( Str path, Str normalFilename, Str tangentFileName )
    {
        saveNTMapData(path,normalFilename,mNormalData);
        //saveNTMapData(path,tangentFileName,mTangentData);
    }

    //---------------------------------------------------------------------
    void TerrainSurface::unLoadNormalTangentMapData()
    {
        if (mNormalData)
        {
            RamAlloc::getInstance().release(mNormalData);
            mNormalData = 0;
        }

        if (mTangentData)
        {
            RamAlloc::getInstance().release(mTangentData);
            mTangentData = 0;
        }

        mNTDataSize = 0;
        mNTPixelNum = 0;
    }
    

    //---------------------------------------------------------------------
    Flt* TerrainSurface::getNormalDataByIndex(Int x, Int y) const
    {
        if ( mNormalData )
        {
            x = Ogre::Math::Clamp( x, (Int)0 , (Int)(mVertexSideNum - 1) );
            y = Ogre::Math::Clamp( y, (Int)0 , (Int)(mVertexSideNum - 1) );

            //DYNAMIC_ASSERT (x >= 0 && x < mVertexSideNum && y >= 0 && y < mVertexSideNum);

            return &mNormalData[(y * mVertexSideNum + x) * mNTOnePixelNum];
        }

        return NULL;
    }

    //---------------------------------------------------------------------
    Flt* TerrainSurface::getTangentDataByIndex(Int x, Int y) const
    {
        if ( mTangentData )
        {
            x = Ogre::Math::Clamp( x, (Int)0 , (Int)(mVertexSideNum - 1) );
            y = Ogre::Math::Clamp( y, (Int)0 , (Int)(mVertexSideNum - 1) );

            //DYNAMIC_ASSERT (x >= 0 && x < mVertexSideNum && y >= 0 && y < mVertexSideNum);

            return &mTangentData[(y * mVertexSideNum + x) * mNTOnePixelNum];
        }

        return NULL;
    }

    //---------------------------------------------------------------------
    void TerrainSurface::refreshNormalTangent(const Rect& rect)
    {
        // 条件判断
        if ( !mNormalData )
            return;

        //if ( !mTangentData )
        //    return;


        // Widen the rectangle by 1 element in all directions since height
        // changes affect neighbours normals
        Ogre::Rect widenedRect(
            max(0L, rect.left - 1L), 
            max(0L, rect.top - 1L), 
            min((long)mVertexSideNum, rect.right + 1L), 
            min((long)mVertexSideNum, rect.bottom + 1L)
            );

        ///////////////////////////////////////////////////////////////////////////////////////

        // Evaluate normal like this
        //  3---2---1
        //  | \ | / |
        //	4---P---0
        //  | / | \ |
        //	5---6---7

        Plane plane;
        for (long y = widenedRect.top; y < widenedRect.bottom; ++y)
        {
            for (long x = widenedRect.left; x < widenedRect.right; ++x)
            {
                Vector3 cumulativeNormal = Vector3::ZERO;
                Vector3 cumulativeTangent = Vector3::ZERO;

                // Build points to sample
                Vector3 centrePoint;
                Vector3 adjacentPoints[8];
                convertVertexPointToWorldPosition(x  , y,   &centrePoint);
                convertVertexPointToWorldPosition(x+1, y,   &adjacentPoints[0]);
                convertVertexPointToWorldPosition(x+1, y+1, &adjacentPoints[1]);
                convertVertexPointToWorldPosition(x,   y+1, &adjacentPoints[2]);
                convertVertexPointToWorldPosition(x-1, y+1, &adjacentPoints[3]);
                convertVertexPointToWorldPosition(x-1, y,   &adjacentPoints[4]);
                convertVertexPointToWorldPosition(x-1, y-1, &adjacentPoints[5]);
                convertVertexPointToWorldPosition(x,   y-1, &adjacentPoints[6]);
                convertVertexPointToWorldPosition(x+1, y-1, &adjacentPoints[7]);

                for (int i = 0; i < 8; ++i)
                {
                    plane.redefine(centrePoint, adjacentPoints[i], adjacentPoints[(i+1)%8]);
                    cumulativeNormal += plane.normal;
                    //cumulativeTangent += plane.projectVector( Vector3(1,0,0) );
                }

                // normalise & store normal
                cumulativeNormal.normalise();
                //cumulativeTangent.normalise();

                // encode as RGB, object space
                // invert the Y to deal with image space
                long storeX = x - widenedRect.left;
                long storeY = widenedRect.bottom - y - 1;

                /////////////////////////////////////////////////////////////////////////////////

                {
                    Flt* pStore = mNormalData + ((y * mVertexSideNum) + x) * mNTOnePixelNum;

                    *pStore++ = cumulativeNormal.x;
                    *pStore++ = cumulativeNormal.y;
                    *pStore++ = cumulativeNormal.z;
                }

                //{
                //    Flt* pStore = mTangentData + ((y * mVertexSideNum) + x) * mNTOnePixelNum;

                //    *pStore++ = cumulativeTangent.x;
                //    *pStore++ = cumulativeTangent.y;
                //    *pStore++ = cumulativeTangent.z;
                //}
                /////////////////////////////////////////////////////////////////////////////////
            }
        }
    }

    //**********************************************************************************************************************
    //**********************************************************************************************************************


    //---------------------------------------------------------------------
    U8* TerrainSurface::getColorDataByIndex(Int x, Int y) const
    {
        if ( mColorData )
        {

            x = Ogre::Math::Clamp( x, (Int)0 , (Int)(mVertexSideNum - 1) );
            y = Ogre::Math::Clamp( y, (Int)0 , (Int)(mVertexSideNum - 1) );

            //DYNAMIC_ASSERT (x >= 0 && x < mVertexSideNum && y >= 0 && y < mVertexSideNum);

            return &mColorData[(y * mVertexSideNum + x) * mColorOnePixelNum];
        }
        
        return NULL;
    }

    //---------------------------------------------------------------------
    void TerrainSurface::loadColorMapData( Str path, Str filename )
    {
        ////////////////////////////////////////////////////////////////////////

        unLoadColorMapData();

        ////////////////////////////////////////////////////////////////////////

        // 创建内存
        mColorOnePixelNum       = 4;
        Int vertexNum           = mVertexSideNum * mVertexSideNum;
        mColorPixelNum          = mColorOnePixelNum * vertexNum;
        mColorDataSize          = sizeof( U8 ) * (mColorPixelNum + 1);
        mColorData              = (U8*)RamAlloc::getInstance().get( mColorDataSize );
        DYNAMIC_ASSERT_LOG( mColorData!=NULL, "loadColorMapData mColorData failed" );

        memset(mColorData, 127, mColorDataSize);

        ////////////////////////////////////////////////////////////////////////

        // 加载文件数据
        if ( Ogre::ResourceGroupManager::getSingleton().resourceExists( path.c_str() ,filename) )
        {
            ////////////////////////////////////////////////////////////////////////

            Ogre::Image img;

            img.load(filename, path.c_str());

            if (img.getWidth() != mVertexSideNum || img.getHeight() != mVertexSideNum)
                img.resize(mVertexSideNum, mVertexSideNum);

            ////////////////////////////////////////////////////////////////////////

            // 复制文件数据到内存

            // convert image data to floats
            // Do this on a row-by-row basis, because we describe the terrain in
            // a bottom-up fashion (ie ascending world coords), while Image is top-down
            unsigned char* pSrcBase = img.getData();
            size_t depth            = img.getDepth();
            U8* pDst                = 0;
            unsigned char* pSrc     = 0;
            size_t rowSpan          = img.getRowSpan();
            PixelFormat imgFormat   = img.getFormat();

            for (size_t i = 0; i < mVertexSideNum; ++i)
            {
                // 图片像素行头移动
                size_t srcy = mVertexSideNum - i - 1;
                pSrc = pSrcBase + srcy * rowSpan;
                // 内存像素行头移动
                pDst = mColorData + i * mVertexSideNum * mColorOnePixelNum;
                // 转变图片行像素位数据到内存像素位(根据各自的格式)
                PixelUtil::bulkPixelConversion(pSrc, imgFormat, 
                    pDst, PF_BYTE_RGBA, mVertexSideNum);
            }
        }else
        {
            Ogre::Rect rect = Ogre::Rect(0,0,mVertexSideNum,mVertexSideNum);
            this->refreshColors(rect);
            mModified = true;
        }
    }

    //---------------------------------------------------------------------
    void TerrainSurface::unLoadColorMapData()
    {
        if (mColorData)
        {
            RamAlloc::getInstance().release(mColorData);
            mColorData = 0;
            mColorDataSize = 0;
            mColorPixelNum = 0;
        }
    }

    //---------------------------------------------------------------------
    void TerrainSurface::saveColorMapData( Str path, Str filename )
    {
        //////////////////////////////////////////////////////////////

        // 条件判断
        if ( !mColorData )
            return;

        //////////////////////////////////////////////////////////////

        // 初始化数据
        PixelFormat heightFormat    = PF_BYTE_RGBA;
        PixelFormat imgFormat       = PF_BYTE_RGBA;
        size_t imgFormatSize        = PixelUtil::getNumElemBytes( imgFormat );
        size_t imgSize              = mVertexSideNum * mVertexSideNum * imgFormatSize; 
        size_t imgRowSize           = mVertexSideNum * imgFormatSize;
        void* pixData               = OGRE_MALLOC(imgSize, Ogre::MEMCATEGORY_GENERAL);
        DYNAMIC_ASSERT_LOG( pixData!=NULL, "saveColorMapData pixData failed" );

        unsigned char* pImgBase     = (unsigned char*)pixData;

        //////////////////////////////////////////////////////////////

        // 得到一份内存复制数据
        U8* pBaseCopy               = mColorData;

        //////////////////////////////////////////////////////////////

        // 复制内存数据到文件数据
        U8* pCopyPixel             = 0;
        unsigned char* pImgPixel    = 0;
        for (size_t i = 0; i < mVertexSideNum; ++i)
        {
            // 图片像素位移动
            size_t imgY     = mVertexSideNum - i - 1;
            pImgPixel       = pImgBase + imgY * imgRowSize;
            // 内存像素位移动
            pCopyPixel      = pBaseCopy + i * mVertexSideNum * mColorOnePixelNum;

            // 转变图片行像素位数据到内存像素位(根据各自的格式)
            PixelUtil::bulkPixelConversion(pCopyPixel, heightFormat, 
                pImgPixel, imgFormat, mVertexSideNum);
        }

        //////////////////////////////////////////////////////////////

		if ( EngineMain::getInstance().getMode() == EM_EDITOR )
		{
			//如果目录不存在先创建目录
			if (!FileOp::isExistDirectory(path))
				FileOp::createDirectory(path);

			// 保存文件
			// load, and tell Image to delete the memory when it's done.
			Ogre::Image img;
			img.loadDynamicImage((Ogre::uchar*)pixData, mVertexSideNum, mVertexSideNum, 1, imgFormat, true, 1, 0);
			Str filePath   = FileOp::getFullFilePath( path, filename );
			img.save( filePath );

		}

        //////////////////////////////////////////////////////////////
    }

    //**********************************************************************************************************************
    //**********************************************************************************************************************



    //---------------------------------------------------------------------
    void TerrainSurface::loadLightMapData( Str path, Str filename )
    {
        //加载光影贴图
        if ( Ogre::ResourceGroupManager::getSingleton().resourceExists(path,filename) )
        {
            Ogre::Image img;
            img.load(filename, path);

            if (img.getWidth() != mLightmapSize || img.getHeight() != mLightmapSize)
                img.resize(mLightmapSize, mLightmapSize);

            PixelFormat fmt     = PF_L8;
            PixelFormat imgFmt  = img.getFormat();
            if ( imgFmt == fmt )
            {
                size_t channels = PixelUtil::getNumElemBytes(fmt);
                size_t dataSz = channels * mLightmapSize * mLightmapSize;
                uint8* pData = (uint8*)OGRE_MALLOC(dataSz, MEMCATEGORY_RESOURCE);
                DYNAMIC_ASSERT_LOG( pData!=NULL, "loadLightMapData pData failed" );

                unsigned char* pSrcBase = img.getData(); 

                memcpy(pData, pSrcBase,dataSz);

                mCpuLightmapStorage = pData;
            }
        }

        mLightMapRequired = true;
        createOrDestroyGPULightmap( path );

        //////////////////////////////////////////////////////////////////

        if  ( mCpuLightmapStorage )
        {
            // release CPU copy, don't need it anymore
            OGRE_FREE(mCpuLightmapStorage, MEMCATEGORY_RESOURCE);
            mCpuLightmapStorage = 0;
        }
    }
    //---------------------------------------------------------------------
    void TerrainSurface::saveLightMapData( Str path, Str filename )
    {
        if ( !mLightmap.isNull())
        {
            Image img;
            PixelFormat fmt = mLightmap->getFormat();
            mLightmap->convertToImage(img);

            Str filePath   = FileOp::getFullFilePath( path, filename );
            img.save( filePath );
        }
    }
    //---------------------------------------------------------------------
    void TerrainSurface::setLightMapDirection(Vec3 dir)
    {
        mLightMapDirection = Vector3(dir.x,dir.y,dir.z);
    }
    //---------------------------------------------------------------------
    void TerrainSurface::unLoadLightMapData()
    {
        TextureManager* tmgr = TextureManager::getSingletonPtr();
        if (tmgr)
        {
            if (!mLightmap.isNull())
            {
                tmgr->remove(mLightmap->getHandle());
                mLightmap.setNull();
            }
        }
    }
    //---------------------------------------------------------------------
    void TerrainSurface::refreshLightmap(const Rect& calRect)
    {
        Ogre::Rect updateRect;
        Ogre::Rect extraRect;

        PixelBox* lightMapBox = calculateLightmap(calRect,extraRect,updateRect);

        if (!mLightmap.isNull())
        {
            // blit the normals into the texture
            if (updateRect.left == 0 && updateRect.top == 0 && updateRect.bottom == mLightmapSizeActual && updateRect.right == mLightmapSizeActual)
            {
                mLightmap->getBuffer()->blitFromMemory(*lightMapBox);
            }
            else
            {
                // content of PixelBox is already inverted in Y, but rect is still 
                // in terrain space for dealing with sub-rect, so invert
                Image::Box dstBox;
                dstBox.left = updateRect.left;
                dstBox.right = updateRect.right;
                dstBox.top = mLightmapSizeActual - updateRect.bottom;
                dstBox.bottom = mLightmapSizeActual - updateRect.top;
                mLightmap->getBuffer()->blitFromMemory(*lightMapBox, dstBox);
            }
        }

        // delete memory
        OGRE_FREE(lightMapBox->data, MEMCATEGORY_GENERAL);
        OGRE_DELETE(lightMapBox);
    }

    //---------------------------------------------------------------------
    void TerrainSurface::createOrDestroyGPULightmap( Str& path )
    {
        TerrainTilesGlobalOptions& opts = TerrainTilesGlobalOptions::getInstance();

        if (mLightMapRequired && mLightmap.isNull())
        {
            // create
            Int mipmap = MGEngineUtility::getMipMapNum( mLightmapSize );
            mLightmap = TextureManager::getSingleton().createManual(
                mChunk->getName() + "/lm", opts.getDefaultResourceGroup(), 
                TEX_TYPE_2D, mLightmapSize, mLightmapSize, mipmap, PF_L8, TU_STATIC | TU_AUTOMIPMAP);

            mLightmapSizeActual = mLightmap->getWidth();

            if (mCpuLightmapStorage)
            {
                // Load cached data
                PixelBox src(mLightmapSize, mLightmapSize, 1, PF_L8, mCpuLightmapStorage);
                mLightmap->getBuffer()->blitFromMemory(src);
            }
            else
            {
                // initialise to full-bright
                Box box(0, 0, mLightmapSizeActual, mLightmapSizeActual);
                HardwarePixelBufferSharedPtr buf = mLightmap->getBuffer();
                uint8* pInit = static_cast<uint8*>(buf->lock(box, HardwarePixelBuffer::HBL_DISCARD).data);
                memset(pInit, 255, mLightmapSizeActual * mLightmapSizeActual);
                buf->unlock();

            }
        }
        else if (!mLightMapRequired && !mLightmap.isNull())
        {
            // destroy
            TextureManager::getSingleton().remove(mLightmap->getHandle());
            mLightmap.setNull();
        }
    }
    //---------------------------------------------------------------------
    PixelBox* TerrainSurface::calculateLightmap(const Rect& rect, const Rect& extraTargetRect, Rect& outFinalRect)
    {
        // as well as calculating the lighting changes for the area that is
        // dirty, we also need to calculate the effect on casting shadow on
        // other areas. To do this, we project the dirt rect by the light direction
        // onto the minimum height

        //暂时使用默认灯光
        Vec3 dir = mScene->getDefaultLight()->getDirection();

        const Vector3& lightVec = Vector3(dir.x,dir.y,dir.z);//mLightMapDirection;
        Ogre::Rect widenedRect;
        widenRectByVector(lightVec, rect, widenedRect);

        // merge in the extra area (e.g. from neighbours)
        widenedRect.merge(extraTargetRect);

        // widenedRect now contains terrain point space version of the area we
        // need to calculate. However, we need to calculate in lightmap image space
        float terrainToLightmapScale = (float)mLightmapSizeActual / (float)mVertexSideNum;
        widenedRect.left = (long)(widenedRect.left * terrainToLightmapScale);
        widenedRect.right = (long)(widenedRect.right * terrainToLightmapScale);
        widenedRect.top = (long)(widenedRect.top * terrainToLightmapScale);
        widenedRect.bottom = (long)(widenedRect.bottom * terrainToLightmapScale);

        // clamp 
        widenedRect.left = max(0L, widenedRect.left);
        widenedRect.top = max(0L, widenedRect.top);
        widenedRect.right = min((long)mLightmapSizeActual, widenedRect.right);
        widenedRect.bottom = min((long)mLightmapSizeActual, widenedRect.bottom);

        outFinalRect = widenedRect;

        ////////////////////////////////////////////////////////////////////////////////////////

        // allocate memory (L8)
        uint8* pData = static_cast<uint8*>(
            OGRE_MALLOC(widenedRect.width() * widenedRect.height(), MEMCATEGORY_GENERAL));
        DYNAMIC_ASSERT_LOG( pData!=NULL, "calculateLightmap pData failed" );

        PixelBox* pixbox = OGRE_NEW PixelBox(widenedRect.width(), widenedRect.height(), 1, PF_L8, pData);

        ////////////////////////////////////////////////////////////////////////////////////////

        Real heightPad = (getMaxHeight() - getMinHeight()) * 1.0e-3f;
        float litValAround[4];
        Vector3 wPosAround[4];

        ////////////////////////////////////////////////////////////////////////////////////////
        for (long y = widenedRect.top; y < widenedRect.bottom; ++y)
        {
            for (long x = widenedRect.left; x < widenedRect.right; ++x)
            {
                // convert to terrain space (not points, allow this to go between points)
                float Tx = (float)x / (float)(mLightmapSizeActual-1);
                float Ty = (float)y / (float)(mLightmapSizeActual-1);


                //////////////////////////////////////////////////////////////////////////


                // get world space point
                // add a little height padding to stop shadowing self
                Vector3 wpos = Vector3::ZERO;

                //////////////////////////////////////////////////////////////////////////

                //convertTerrainPositionToWorldPosition(Tx, Ty, getHeightByTerrainPosition(Tx, Ty) + heightPad, &wpos);

                //////////////////////////////////////////////////////////////////////////

                Triangle3D tri3D1;
                Triangle3D tri3D2;

                if ( getTerrainTri3DByTerrainPosition(Tx, Ty, tri3D1, tri3D2) == false ) 
                    break;
                
                //////////////////////////////////////////////////////////////////////////

                wPosAround[0] = tri3D1.t0;
                wPosAround[1] = tri3D1.t1;
                wPosAround[2] = tri3D1.t2;
                wPosAround[3] = tri3D2.t0;

                //////////////////////////////////////////////////////////////////////////

                for ( UInt i=0; i<4; i++ )
                {
                    litValAround[i] = 1;

                    wpos = wPosAround[i];

                    wpos.y += heightPad;

                    // build ray, cast backwards along light direction
                    //Ray ray(wpos, -lightVec);
                    Vec3 rayPos = Vec3(wpos.x,wpos.y,wpos.z);
                    Vec3 rayDir = Vec3(-lightVec.x,-lightVec.y,-lightVec.z);
                    Vec3 intersectPos;
                    if (getRayIntersection(rayPos,rayDir,intersectPos,true))
                        litValAround[i] = 0.0f;
                }

                //////////////////////////////////////////////////////////////////////////

                float litVal = 0;
                for ( UInt i=0; i<4; i++ )
                {
                    litVal += litValAround[i];
                }

                litVal = litVal / 4;

                //////////////////////////////////////////////////////////////////////////
                
                // encode as L8
                // invert the Y to deal with image space
                long storeX = x - widenedRect.left;
                long storeY = widenedRect.bottom - y - 1;

                uint8* pStore = pData + ((storeY * widenedRect.width()) + storeX);
                *pStore = (unsigned char)(litVal * 255.0);
            }
        }

        return pixbox;
    }


    //**********************************************************************************************************************
    //**********************************************************************************************************************




}

