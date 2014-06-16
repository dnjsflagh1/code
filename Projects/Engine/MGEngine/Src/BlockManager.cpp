/******************************************************************************/
#include "stdafx.h"
#include "Scene.h"
#include "BlockManager.h"
#include "MGEngineUtility.h"
#include "OgreSceneQuery.h"
#include "EngineMain.h"
#include "DynamicBlockObject.h"
/******************************************************************************/

namespace MG
{
    //-----------------------------------------------------------------------

    Real BlockManager::STATIC_BLOCK_GRID_SIZE   = 1;
    Real BlockManager::DYNAMIC_BLOCK_GRID_SIZE  = 0.5;

    //-----------------------------------------------------------------------
    BlockManager::BlockManager( Scene* scene )
        :mScene(scene)
    {

    }

    //-----------------------------------------------------------------------
    BlockManager::~BlockManager()
    {
		unLoad();
    }

	//-----------------------------------------------------------------------
	void BlockManager::loadStaticBlock( Vec2 leftBottomPos, Vec2 rightUpPos )
	{
		TerrainManager* terrainManager = mScene->getTerrainManager();
		if(!terrainManager)
		{
			return;
		}

		TerrainChunk* terrainChunk = NULL;
		TerrainRegionGridData* gridData = NULL;
		TerrainRegion* terrainBlockRegion = NULL;
		Rect terrainChunkRect;
		VecU2 blockPoint;
		Vec2 terrainRegionIndex;

		Flt gridSize = terrainManager->getTerrainChunkBlockGridSize();
		//Int terrainWidth = terrainManager->getTerrainWidth();
		//Int terrainHeight = terrainManager->getTerrainHeight();
		//Int terrainBlockMapWidth = terrainWidth / gridSize;
		//Int terrainBlockMapHeight = terrainHeight / gridSize;

		Int terrainWidth = abs(rightUpPos.x - leftBottomPos.x);
		Int terrainHeight = abs(rightUpPos.y - leftBottomPos.y);
		Int terrainBlockMapWidth = terrainWidth / gridSize;
		Int terrainBlockMapHeight = terrainHeight / gridSize;

        ////////////////////////////////////////////////////////////////////////////////////////////

        // 自动匹配碰撞系统静态格子大小和地形障碍格子大小一致
        STATIC_BLOCK_GRID_SIZE = gridSize;

        ////////////////////////////////////////////////////////////////////////////////////////////

		UInt staticBlockMapWidth = terrainWidth / STATIC_BLOCK_GRID_SIZE;
		if(staticBlockMapWidth * STATIC_BLOCK_GRID_SIZE < terrainWidth)
		{
			staticBlockMapWidth++;
		}

		UInt staticBlockMapHeight = terrainHeight / STATIC_BLOCK_GRID_SIZE;
		if(staticBlockMapHeight * STATIC_BLOCK_GRID_SIZE < terrainHeight)
		{
			staticBlockMapHeight++;
		}

		Vec3 centerPosition = mScene->getTerrainManager()->getCenterPosition();
		mMapStaticBlock.createGrids(staticBlockMapWidth, staticBlockMapHeight, STATIC_BLOCK_GRID_SIZE, leftBottomPos);
		
        ////////////////////////////////////////////////////////////////////////////////////////////
        
        clearAllStaticBlock();

        ////////////////////////////////////////////////////////////////////////////////////////////

        // 加载地形障碍
		for(UInt i = 0; i < terrainManager->getTerrainChunkCount(); ++i)
		{
			terrainChunk = terrainManager->getTerrainChunkByIndex(i);
			terrainChunkRect = terrainChunk->getBoundingRect();
			terrainRegionIndex = terrainChunk->getTerrainGroupIndex();

			terrainBlockRegion = terrainChunk->getTerrainRegion()->getTerrainBlockBaseRegion();

			for(Int z = terrainChunkRect.top; z < terrainChunkRect.bottom; ++z)
			{
				for(Int x = terrainChunkRect.left; x < terrainChunkRect.right; ++x)
				{
					gridData = terrainBlockRegion->getGridByWorldPosition(x, z);
					if(!gridData || gridData->mask == 0)
					{
						continue;
					}
					mMapStaticBlock.convertWorldPositionToGridPoint(Vec2(x,z), blockPoint);
					setStaticBlockByPoint(blockPoint.x, blockPoint.y, BLF_TERRAIN_BLOCK);
				}	
			}
		}
	}

	//-----------------------------------------------------------------------
	void BlockManager::loadDynamicBlock( Vec2 leftBottomPos, Vec2 rightUpPos )
	{
		TerrainManager* terrainManager = mScene->getTerrainManager();
		if(!terrainManager)
		{
			return;
		}

		TerrainChunk* terrainChunk = NULL;
		TerrainRegionGridData* gridData = NULL;
		TerrainRegion* terrainBlockRegion = NULL;
		Rect terrainChunkRect;
		VecU2 blockPoint;
		Vec2 terrainRegionIndex;

		//Vec2 leftBottomPos = Vec2(236.23383, -770.14105);
		//Vec2 rightUpPos = Vec2(820.49918, -125.28143);

		Flt gridSize = terrainManager->getTerrainChunkBlockGridSize();

		Int terrainWidth = abs(rightUpPos.x - leftBottomPos.x);
		Int terrainHeight = abs(rightUpPos.y - leftBottomPos.y);
		Int terrainBlockMapWidth = terrainWidth / gridSize;
		Int terrainBlockMapHeight = terrainHeight / gridSize;


		//Flt gridSize = terrainManager->getTerrainChunkBlockGridSize();
		//Int terrainWidth = terrainManager->getTerrainWidth();
		//Int terrainHeight = terrainManager->getTerrainHeight();
		//Int terrainBlockMapWidth = terrainWidth / gridSize;
		//Int terrainBlockMapHeight = terrainHeight / gridSize;

        UInt dynamicBlockMapWidth = terrainWidth / BlockManager::DYNAMIC_BLOCK_GRID_SIZE;
		if(dynamicBlockMapWidth * BlockManager::DYNAMIC_BLOCK_GRID_SIZE < terrainWidth)
		{
			dynamicBlockMapWidth++;
		}

		UInt dynamicBlockMapHeight = terrainHeight / BlockManager::DYNAMIC_BLOCK_GRID_SIZE;
		if(dynamicBlockMapHeight * BlockManager::DYNAMIC_BLOCK_GRID_SIZE < terrainHeight)
		{
			dynamicBlockMapHeight++;
		}

		Vec3 centerPosition = mScene->getTerrainManager()->getCenterPosition();
		mMapDynamicBlock.createGrids(dynamicBlockMapWidth, dynamicBlockMapHeight, DYNAMIC_BLOCK_GRID_SIZE, leftBottomPos);
		
        
        ////////////////////////////////////////////////////////////////////////////////////////////
        
        clearAllDynamicBlock();

        ////////////////////////////////////////////////////////////////////////////////////////////

        // 加载地形障碍

		for(UInt i = 0; i < terrainManager->getTerrainChunkCount(); ++i)
		{
			terrainChunk = terrainManager->getTerrainChunkByIndex(i);
			terrainChunkRect = terrainChunk->getBoundingRect();
			terrainRegionIndex = terrainChunk->getTerrainGroupIndex();

			terrainBlockRegion = terrainChunk->getTerrainRegion()->getTerrainBlockBaseRegion();

			for(Int z = terrainChunkRect.top; z < terrainChunkRect.bottom; ++z)
			{
				for(Int x = terrainChunkRect.left; x < terrainChunkRect.right; ++x)
				{
					gridData = terrainBlockRegion->getGridByWorldPosition(x, z);
					if(!gridData || gridData->mask == 0)
					{
						continue;
					}

					mMapDynamicBlock.convertWorldPositionToGridPoint(Vec2(x,z), blockPoint);
					setDynamicBlockByPoint(blockPoint.x, blockPoint.y, BLF_TERRAIN_BLOCK);
				}	
			}
		}
	}

    //-----------------------------------------------------------------------
    void BlockManager::unLoad()
    {
		mMapStaticBlock.destroyGrids();
		mMapDynamicBlock.destroyGrids();
    }

    //-----------------------------------------------------------------------
    void BlockManager::update(Flt delta)
    {
        checkEntityBlock();
    }

    //-----------------------------------------------------------------------
    DynamicBlockObject* BlockManager::createDynamicBlockObject(Scene* scene, IEntity* sceneObject, Flt objectRadius)
    {
		DynamicBlockObject* obj = NULL;
		//if ( mMapDynamicBlock.getIsGridCreated() )
		//{
			obj = MG_NEW DynamicBlockObject( scene, sceneObject, objectRadius );
		//}
        return obj;
    }

    //-----------------------------------------------------------------------
    void BlockManager::destroyDynamicBlockObject(DynamicBlockObject* obj)
    {
        MG_SAFE_DELETE( obj );
    }

    //-----------------------------------------------------------------------
    void BlockManager::checkEntityBlock()
    {
        // 遍历实体
        // 查看Entity::getSceneNode()::getPositionDirty

    } 

	//-----------------------------------------------------------------------
	GridPool<Byte>* BlockManager::getStaticBlockList()
	{
		return &mMapStaticBlock;
	}

	//-----------------------------------------------------------------------
	GridPool<Byte>* BlockManager::getDynamicBlockList()
	{
		return &mMapDynamicBlock;
	}

	//-----------------------------------------------------------------------
	void BlockManager::setDynamicBlockByIndex(UInt index, BLOCK_FLAG flag)
	{
		if(!mMapDynamicBlock.getIsGridCreated())
		{
			return;
		}

		UInt dynamicBlockMapWidth = mMapDynamicBlock.getWorldGridWidth();
		UInt dynamicBlockMapHeight = mMapDynamicBlock.getWorldGridHeight();

		if( index < 1 || index >dynamicBlockMapWidth * dynamicBlockMapHeight )
		{
			return;
		}

		Byte* dynamicBlock = mMapDynamicBlock.getGridDataByIndex(index);

        // set block
        (*dynamicBlock) |= flag;
	}

	//-----------------------------------------------------------------------
	void BlockManager::setDynamicBlockByPoint(Int x, Int z, BLOCK_FLAG flag )
	{
		if(!mMapDynamicBlock.getIsGridCreated())
		{
			return;
		}

		UInt index = mMapDynamicBlock.convertGridPointToGridIndex( x,z );
		if(index == 0)
		{
			return;
		}

		setDynamicBlockByIndex(index, flag);
	}

	//-----------------------------------------------------------------------
	void BlockManager::setDynamicBlockByPos( Vec3 pos, BLOCK_FLAG flag, Int diameterSize )
	{
		if(!mMapDynamicBlock.getIsGridCreated())
		{
			return;
		}

		VecI2 minPoint;
		VecI2 maxPoint;
		std::map<UInt, UInt> posGridBlocList;

		getBlockGridListByRect(pos, posGridBlocList, minPoint, maxPoint, diameterSize);

		Byte* dynamicBlock = NULL;
		for(std::map<UInt, UInt>::iterator it = posGridBlocList.begin(); it != posGridBlocList.end(); ++it)
		{
            setDynamicBlockByIndex( it->first, flag );
		}
	}

	//-----------------------------------------------------------------------
	void BlockManager::setBlockByTriangle3DList( std::vector<Triangle3D>& worldTriangle3DList, BLOCK_FLAG flag )
	{
		std::map<UInt, VecU2> gridPointList;
		getBlockGridListByTriangle3DList(gridPointList, worldTriangle3DList, false);

		for(std::map<UInt, VecU2>::iterator it = gridPointList.begin(); it != gridPointList.end(); ++it)
		{
			setDynamicBlockByIndex(it->first, flag);
		}

		getBlockGridListByTriangle3DList(gridPointList, worldTriangle3DList, true);

		for(std::map<UInt, VecU2>::iterator it = gridPointList.begin(); it != gridPointList.end(); ++it)
		{
			setDynamicBlockByIndex(it->first, flag);
		}
	}


	//-----------------------------------------------------------------------
	void BlockManager::setStaticBlockByIndex(UInt index, BLOCK_FLAG flag )
	{
		UInt staticBlockMapWidth = mMapStaticBlock.getWorldGridWidth();
		UInt staticBlockMapHeight = mMapStaticBlock.getWorldGridHeight();

		if( index < 1 || index > staticBlockMapWidth * staticBlockMapHeight )
		{
			return;
		}
		
		Byte* staticBlock = mMapStaticBlock.getGridDataByIndex(index);

        if ( staticBlock )
        {
            (*staticBlock) |= flag;
        }
	}

	//-----------------------------------------------------------------------
	void BlockManager::setStaticBlockByPoint(Int x, Int z, BLOCK_FLAG flag )
	{
		if(!mMapStaticBlock.getIsGridCreated())
		{
			return;
		}

		UInt index = mMapStaticBlock.convertGridPointToGridIndex( x,z );
		if(index == 0)
		{
			return;
		}

		setStaticBlockByIndex(index, flag);
	}

	//-----------------------------------------------------------------------
	void BlockManager::clearDynamicBlock(UInt index, BLOCK_FLAG flag )
	{
		if(!mMapDynamicBlock.getIsGridCreated())
		{
			return;
		}

		UInt dynamicBlockMapWidth = mMapDynamicBlock.getWorldGridWidth();
		UInt dynamicBlockMapHeight = mMapDynamicBlock.getWorldGridHeight();

		if( index < 1 || index > dynamicBlockMapWidth * dynamicBlockMapHeight )
		{
			return;
		}

		Byte* dynamicBlock = mMapDynamicBlock.getGridDataByIndex(index);

        if ( dynamicBlock )
        {
            (*dynamicBlock) = (*dynamicBlock) & ~flag;
        }
	}


	//-----------------------------------------------------------------------
	void BlockManager::clearDynamicBlock(Vec3 pos, BLOCK_FLAG flag, Int diameterSize)
	{
		if(!mMapDynamicBlock.getIsGridCreated())
		{
			return;
		}

		std::map<UInt, UInt> posBlockGridList;
		
		VecI2 minPoint;
		VecI2 maxPoint;

		getBlockGridListByRect(pos, posBlockGridList, minPoint, maxPoint, diameterSize, VERTEX_LEFTDOWN);

		for(std::map<UInt, UInt>::iterator it = posBlockGridList.begin(); it != posBlockGridList.end(); ++it)
		{
            clearDynamicBlock( it->first, flag );
		}
	}

	//-----------------------------------------------------------------------
	void BlockManager::clearStaticBlock(UInt index, BLOCK_FLAG flag)
	{
		UInt staticBlockMapWidth = mMapStaticBlock.getWorldGridWidth();
		UInt staticBlockMapHeight = mMapStaticBlock.getWorldGridHeight();

		if( index < 1 || index > staticBlockMapWidth * staticBlockMapHeight )
		{
			return;
		}

		Byte* staticBlock = mMapStaticBlock.getGridDataByIndex(index);
        if ( staticBlock )
        {
            (*staticBlock) = (*staticBlock) & ~flag;
        }
	}
	
	//-----------------------------------------------------------------------
	void BlockManager::clearAllStaticBlock()
	{
		mMapStaticBlock.clearWorldGrid(BLF_NULL);
	}

	//-----------------------------------------------------------------------
	void BlockManager::clearAllDynamicBlock()
	{
		mMapDynamicBlock.clearWorldGrid(BLF_NULL);
	}

	//-----------------------------------------------------------------------
	void BlockManager::clearMapAllBlock()
	{
		clearAllStaticBlock();
		clearAllDynamicBlock();
	}

	//-----------------------------------------------------------------------
	UInt BlockManager::getStaticBlockIndexByWorldPos( Vec3 pos )
	{
		VecU2 gridPoint;
		mMapStaticBlock.convertWorldPositionToGridPoint(Vec2(pos.x, pos.z), gridPoint);

		return mMapStaticBlock.convertGridPointToGridIndex(gridPoint);
	}

	//-----------------------------------------------------------------------
	UInt BlockManager::getDynamicBlockIndexByWorldPos( Vec3 pos )
	{
		VecU2 gridPoint;
		mMapDynamicBlock.convertWorldPositionToGridPoint(Vec2(pos.x, pos.z), gridPoint);

		return mMapDynamicBlock.convertGridPointToGridIndex(gridPoint);
	}

	//-----------------------------------------------------------------------
	void BlockManager::getDynamicBlockPointByWorldPos( Vec3 pos, Int& x, Int& z )
	{
		VecU2 gridPoint;
		mMapDynamicBlock.convertWorldPositionToGridPoint(Vec2(pos.x, pos.z), gridPoint);
		x = gridPoint.x;
		z = gridPoint.y;
	}

	//-----------------------------------------------------------------------
	Vec3 BlockManager::getDynamicBlockGridCenterPosByIndex( UInt index )
	{
		VecU2 gridPoint;
		mMapDynamicBlock.convertGridIndexToGridPoint(index, gridPoint);
		Vec2 gridPos;
		mMapDynamicBlock.convertGridPointToWorldPosition(gridPoint, gridPos);

		return Vec3(gridPos.x, 0, gridPos.y);
	}

	//-----------------------------------------------------------------------
	UInt BlockManager::getDynamicBlockIndexByPoint( Int x, Int z )
	{
		return mMapDynamicBlock.convertGridPointToGridIndex(x,z);
	}

	//-----------------------------------------------------------------------
	void BlockManager::getStaticBlockPointByWorldPos( Vec3 pos, Int& x, Int& z )
	{
		VecU2 gridPoint;
		mMapStaticBlock.convertWorldPositionToGridPoint(Vec2(pos.x, pos.z), gridPoint);
		x = gridPoint.x;
		z = gridPoint.y;
	}

	//-----------------------------------------------------------------------
	UInt BlockManager::getStaticBlockIndexByPoint( Int x, Int z )
	{
		return mMapStaticBlock.convertGridPointToGridIndex( x,z );
	}

	//-----------------------------------------------------------------------
	Vec3 BlockManager::getStaticBlockGridCenterPosByIndex( UInt index )
	{
		VecU2 gridPoint;
		mMapStaticBlock.convertGridIndexToGridPoint(index, gridPoint);
		Vec2 gridPos;
		mMapStaticBlock.convertGridPointToWorldPosition(gridPoint, gridPos);

		return Vec3(gridPos.x, 0, gridPos.y);
	}

	//-----------------------------------------------------------------------
	Int	BlockManager::getDynamicBlockMapWidth()
	{
		return mMapStaticBlock.getWorldGridWidth();
	}
	
    //-----------------------------------------------------------------------
    Flt BlockManager::getDynamicBlockGridSize()
    {
        return DYNAMIC_BLOCK_GRID_SIZE;
    }

    //-----------------------------------------------------------------------
    Flt BlockManager::getStaticBlockGridSize()
    {
        return STATIC_BLOCK_GRID_SIZE;
    }

    //-----------------------------------------------------------------------
    Bool BlockManager::isStaticBlockByIndex( UInt index )
    {
        if(!mMapStaticBlock.getIsGridCreated())
        {
            return false;
        }

        Byte* staticBlock  = mMapStaticBlock.getGridDataByIndex(index);

        if ( isBlockFlag(staticBlock, LLF_STRUCTURE_OUTSIDE) )
        {
            return true;
        }

        return false;
    }

    //-----------------------------------------------------------------------
    Bool BlockManager::hasStaticBlockFlagByIndex( UInt index, Byte flag )
    {
        if(!mMapStaticBlock.getIsGridCreated())
        {
            return false;
        }

        Byte* staticBlock  = mMapStaticBlock.getGridDataByIndex(index);

        if ( staticBlock )
        {
            return *staticBlock & flag;
        }

        return false;
    }

    //-----------------------------------------------------------------------
    Bool BlockManager::hasDynamicBlockFlagByIndex( UInt index, Byte flag )
    {
        if(!mMapDynamicBlock.getIsGridCreated())
        {
            return false;
        }

        Byte* dynamicBlock  = mMapDynamicBlock.getGridDataByIndex(index);

        if ( dynamicBlock )
        {
            return *dynamicBlock & flag;
        }

        return false;
    }

    //-----------------------------------------------------------------------
    Bool BlockManager::isDynamicBlockByIndex( UInt index )
    {
        if(!mMapDynamicBlock.getIsGridCreated())
        {
            return false;
        }

        Byte* dynamicBlock  = mMapDynamicBlock.getGridDataByIndex(index);

        if ( isBlockFlag(dynamicBlock, LLF_STRUCTURE_OUTSIDE) )
        {
            return true;
        }

        return false;
    }

	//-----------------------------------------------------------------------
	Bool BlockManager::isDynamicBlockByRadius( Vec3 pos, Int diameterSize, VertexPos vertexPos, IDynamicBlockObject* ignoreObj )
	{
		if(!mMapDynamicBlock.getIsGridCreated())
		{
			return false;
		}

		std::map<UInt, UInt> currPosBlockGridList;

		//if(diameterSize % 2 == 0)
		//{
			VecI2 minPoint;
			VecI2 maxPoint;
			getBlockGridListByRect(pos, currPosBlockGridList, minPoint, maxPoint, diameterSize, vertexPos);
		//}

		Byte* dynamicBlock = NULL;
		for(std::map<UInt, UInt>::iterator it = currPosBlockGridList.begin(); it != currPosBlockGridList.end(); ++it)
		{
			dynamicBlock  = mMapDynamicBlock.getGridDataByIndex(it->first);

			if( !dynamicBlock )
			{
				continue;
			}

			if( ignoreObj )
			{
                if ( ignoreObj->isBelongCurrLocationDynamicBlockIndex( it->first ) )
                {
                    continue;
                }
			}

            if ( isBlockFlag(dynamicBlock, LLF_STRUCTURE_OUTSIDE) )
            {
                return true;
            }
		}

		return false;
	}

    //-----------------------------------------------------------------------
    Bool BlockManager::isBlockFlag( Byte* flag, LAYER_FLAG layerFlag )
    {
        if ( flag == NULL )
            return true;

        if ( *flag & BLF_TERRAIN_BLOCK )
            return true;
        if ( *flag & BLF_ENTITY_ALLSIDE_BLOCK )
            return true;

		if(!(*flag & BLF_STRUCTURE_PASSAGE))
		{	
			if ( *flag & BLF_STRUCTURE_ALLSIDE_BLOCK )
				return true;
			if ( (layerFlag == LLF_STRUCTURE_INSIDE) && (*flag & BLF_STRUCTURE_INSIDE_BLOCK) )
				return true;
			if ( (layerFlag == LLF_STRUCTURE_OUTSIDE) && (*flag & BLF_STRUCTURE_OUTSIDE_BLOCK) )
				return true;
		}
		else
		{
			DYNAMIC_ASSERT(0);
		}

        return false;
    }

	//-----------------------------------------------------------------------
	Bool BlockManager::isStaticBlock( Int currX, Int currZ )
	{
		Byte* staticBlock = mMapStaticBlock.getGridDataByPoint(currX, currZ);

        if ( isBlockFlag( staticBlock, LLF_STRUCTURE_OUTSIDE ) )
        {
            return true;
        }

        return false;
	}

	//-----------------------------------------------------------------------
	Bool BlockManager::isStaticBlock( Vec3 currPos )
	{
		Int currX = 0;
		Int currZ = 0;
		getStaticBlockPointByWorldPos(currPos, currX, currZ);

		return isStaticBlock(currX, currZ);
	}

    //-----------------------------------------------------------------------
    Bool BlockManager::isDynamicBlockBetweenTwoPos( IDynamicBlockObject* ignoreObj, Vec3 startPos, Vec3 endPos, UInt& blockIndex, Int findPathObjectCellDiameter,Bool isPrecise)
    {
        // 如果没有动态障碍则退出
        if( !mMapDynamicBlock.getIsGridCreated() )
        {
            return false;
        }

        // 当前监测点
        Vec3 lastCheckPos = startPos;
        Vec3 currCheckPos = startPos;
        // 检测方向
		Vec3 checkDir = endPos - startPos;
        // 检测距离
		Flt checkLen = checkDir.length();
        // 得到检测的步长
        Flt step = BlockManager::DYNAMIC_BLOCK_GRID_SIZE;
        // 得到检测的标量
        checkDir.normalise();
        checkDir = checkDir * step;

        // 循环限制
        UInt loopLimit = 100;
        // 退出标志位
        Bool exit = false;
        // 累计步长
        Flt accuStep = 0;
        // 网格列表
        std::map<UInt, UInt> blockIndexList;
        // 是否有碰撞
        Bool isDynamicBlock = false;

        for ( UInt loopNum=0; loopNum<loopLimit; loopNum++ )
        {
			lastCheckPos = currCheckPos;

            accuStep += step; 
            if ( accuStep >= checkLen )
            {
                currCheckPos = endPos; 
                exit = true;
            }else
            {
                currCheckPos += checkDir; 
            }

            /////////////////////////////////////////////////////////////////////
            
            // 得到检测点一定范围内的网格列表
            //TODO:JJJ
            blockIndexList.clear();

			VecI2 minPoint;
			VecI2 maxPoint;
            if(getNewAddBlockGridListByRect(lastCheckPos, currCheckPos, blockIndexList, minPoint, maxPoint, findPathObjectCellDiameter))
			{
				if(blockIndexList.size() == 0)
				{
					continue;
				}
			}
               
            //TODO:JJJ, 上面getNewAddBlockGridListByRect实现后可以 不要 过滤忽略的网格
            // 过滤忽略的网格
            if ( ignoreObj )
            {

                for(std::map<UInt,UInt>::iterator currIt = blockIndexList.begin(); currIt != blockIndexList.end();)
                {
                    if ( ignoreObj->isBelongCurrLocationDynamicBlockIndex( currIt->first ) )
                    {
                        currIt = blockIndexList.erase(currIt);
                    }else
                    {
                        ++currIt;
                    }
                }
            }

            // 检测是否是障碍
            Byte* gridData = NULL;
			for(std::map<UInt, UInt>::iterator it = blockIndexList.begin(); it != blockIndexList.end(); ++it)
            {
                gridData = mMapDynamicBlock.getGridDataByIndex(it->first);

                if ( isBlockFlag( gridData, LLF_STRUCTURE_OUTSIDE ) )
                {
                    isDynamicBlock = true; 
                }

                /////////////////////////////////////////////////////////////////////

          
                if ( isDynamicBlock )
                {
                    if ( isPrecise )
                    {
                        //TODO:JJJ，不要使用这种碰撞检测，详情询问
                        // 根据移动方向判断是否与网格碰撞
                        //if ( isIntersectionWithDynamicGridByGridIndex( startPos, endPos, it->first ) == false )
                        //{
                        //    isDynamicBlock = false;
                        //}
                    }
                }

                if ( isDynamicBlock )
                {
                    blockIndex = it->first;
                    exit = true;
                    break;
                }
            }

            /////////////////////////////////////////////////////////////////////
            if ( exit )
            {
                break;
            }
        }

        return isDynamicBlock;
    }

	//-----------------------------------------------------------------------
	//Bool BlockManager::getPosNearestAccessiblePosForGridScan( const Vec3 centerPos, Vec3 dir, Flt disLen, Int findPathObjectCellDiameter, Vec3& nearestAccessiblePos )
	//{
	//	
	//}

    //-----------------------------------------------------------------------
    Bool BlockManager::getPosNearestAccessiblePos( const Vec3 centerPos, Int findPathObjectCellDiameter, 
                                                    Vec3& nearestAccessiblePos, IDynamicBlockObject* ignoreObj )
    {
        if(!mMapDynamicBlock.getIsGridCreated())
        {
            nearestAccessiblePos = centerPos;
            return false;
        }

        nearestAccessiblePos = centerPos;

		VecI2 centerGridPoint;

		UInt dirLength[4];
		memset(dirLength, 0, 4*sizeof(UInt));

		std::map<UInt, Bool> isCheckList;
		isCheckList[0] = true;
		isCheckList[1] = true;
		isCheckList[2] = true;
		isCheckList[3] = true;

		Int offsetMinX = 0;
		Int offsetMinY = 0;
		Int offsetMaxX = 0;
		Int offsetMaxY = 0;

		Bool isFinish = false;
		Bool isBlock = false;

		Bool isEven = true;
		if(findPathObjectCellDiameter % 2 == 1)
		{
			isEven = false;
		}

		getDynamicBlockPointByWorldPos(centerPos, centerGridPoint.x, centerGridPoint.y);

		Int minX = centerGridPoint.x;
		Int maxX = centerGridPoint.x;
		Int minY = centerGridPoint.y;
		Int maxY = centerGridPoint.y;

		if(isEven)
		{
			Vec2 vertexPosPos;
			VertexPos vertexPos = getPosNearestVertexPos(centerPos, vertexPosPos);
			if(vertexPos == VERTEX_LEFTUP)
			{
				offsetMinX = 0;
				offsetMaxX -= 1;
				offsetMinY = 0;
				offsetMaxY -= 1;
			}
			else if(vertexPos == VERTEX_LEFTDOWN)
			{
				offsetMinX = 0;
				offsetMaxX -= 1;
				offsetMinY = 0;
				offsetMaxY += 1;
			}
			else if(vertexPos == VERTEX_RIGHTUP)
			{
				offsetMinX += 1;
				offsetMaxX = 0;
				offsetMinY = 0;
				offsetMaxY -= 1;
			}
			else if(vertexPos == VERTEX_RIGHTDOWN)
			{
				offsetMinX += 1;
				offsetMaxX = 0;
				offsetMinY = 0;
				offsetMaxY += 1;
			}
			else
			{
				DYNAMIC_ASSERT(0);
			}
		}

		UInt checkCount = 1;

        //TODO:JJJ
		UInt x = 0;
		UInt y = 0;

		std::map<UInt, Bool>::iterator it;
		std::map<UInt, Bool>::iterator it1;
		std::map<UInt, Bool>::iterator it2;

		while (1)
		{
			//offset = (checkCount * 2 + 1) / 2;
			
			for(UInt i = 0; i < 4; ++i)
			{
				isBlock = false;

				it = isCheckList.find(i);
				if(it == isCheckList.end() || it->second == false)
				{
					continue;
				}

				if( i % 2 == 0)
				{
					UInt y = 0;
					if(i == 0)
					{
						y = centerGridPoint.y - checkCount + offsetMinY;
						//minY = y;
					}
					else
					{
						y = centerGridPoint.y + checkCount + offsetMaxY;
						//maxY = y;
					}

					for(UInt x = centerGridPoint.x - checkCount + offsetMinX; x <= centerGridPoint.x + checkCount + offsetMaxX; ++x)
					{
						UInt index = getDynamicBlockIndexByPoint(x, y);
						if(isDynamicBlockByIndex(index))
						{
							isCheckList.erase(it);
							isBlock = true;
							break;
						}
					}

					if(isBlock)
					{
						break;
					}

					if(i == 0)
					{
						//y = centerGridPoint.y - checkCount + offsetMinY;
						minY = y;
					}
					else
					{
						//y = centerGridPoint.y + checkCount + offsetMaxY;
						maxY = y;
					}
				}
				else if( i % 2 == 1 )
				{
					UInt x = 0;
					if(i == 1)
					{
						x = centerGridPoint.x - checkCount + offsetMinX;
						//minX = x;
					}
					else
					{
						x = centerGridPoint.x + checkCount + offsetMaxX;
						//maxX = x;
					}
					
					for(UInt y = centerGridPoint.y - checkCount + offsetMinY; y <= centerGridPoint.y + checkCount + offsetMaxY; ++y)
					{
						UInt index = getDynamicBlockIndexByPoint(x, y);
						if(isDynamicBlockByIndex(index))
						{
							isCheckList.erase(it);
							isBlock = true;
							break;
						}
					}

					if(isBlock)
					{
						break;
					}

					if(i == 1)
					{
						//x = centerGridPoint.x - checkCount + offsetMinX;
						minX = x;
					}
					else
					{
						//x = centerGridPoint.x + checkCount + offsetMaxX;
						maxX = x;
					}
				}
				else
				{
					continue;
				}
			}

			if(isEven)
			{
				if(maxX - minX + 1>= findPathObjectCellDiameter && maxY - minY + 1 >= findPathObjectCellDiameter)
				{
					isFinish = true;
					break;
				}
			}
			else
			{
				if(maxX - minX >= findPathObjectCellDiameter && maxY - minY >= findPathObjectCellDiameter)
				{
					isFinish = true;
					break;
				}
			}

			if(isCheckList.size() == 0)
			{
				isFinish = false;
				break;
			}

			it1 = isCheckList.find(0);
			it2 = isCheckList.find(2);
			if(it1 == isCheckList.end() && it2 == isCheckList.end())
			{
				isFinish = false;
				break;
			}

			it1 = isCheckList.find(1);
			it2 = isCheckList.find(3);
			if(it1 == isCheckList.end() && it2 == isCheckList.end())
			{
				isFinish = false;
				break;
			}

			checkCount++;
		}

		if(isCheckList.size() == 4)
		{
			nearestAccessiblePos = centerPos;
			return true;
		}

		if(isFinish)
		{
			VecU2 newCenterPos = VecU2((minX + maxX) / 2, (minY + maxY) / 2);
			Vec2 worldPos;	
			mMapDynamicBlock.convertGridPointToWorldPosition(newCenterPos, worldPos);
			nearestAccessiblePos.x = worldPos.x;
			nearestAccessiblePos.y = 0;
			nearestAccessiblePos.z = worldPos.y;
			return true;
		}
		else
		{
			return false;
		}


        // 使用矩形四个方向的扫描线算法， 得到最大的矩形可行走区域


        // 然后判断findPathObjectCellDiameter是否在可行走区域
        // 如果否则返回false
        // 如果是则返回

        //getDynamicBlockPointByWorldPos( Vec3 pos, Int& x, Int& z );
        //getDynamicBlockIndexByPoint( Int x, Int z );
        //isDynamicBlockByIndex( UInt index );
        //isStaticBlockByIndex( UInt index );

        return true;
    }

	//-----------------------------------------------------------------------
	Bool BlockManager::getPosNearestAccessiblePosForDir( const Vec3 centerPos, Vec3 dir, Flt disLen, Int findPathObjectCellDiameter, Vec3& nearestAccessiblePos )
	{
		if(!mMapDynamicBlock.getIsGridCreated())
		{
			nearestAccessiblePos = centerPos;
			return false;
		};

		if(dir.x == 0 && dir.z == 0)
		{
			nearestAccessiblePos = centerPos;
			return false;
		}

		Vec3 currPos = centerPos;
		Flt currDisLen = 0/*DYNAMIC_BLOCK_GRID_SIZE*/;

		while(1)
		{
			currPos = centerPos + (dir * currDisLen);
			if(!isDynamicBlockByRadius(currPos, findPathObjectCellDiameter, VERTEX_LEFTDOWN))
			{
				//if(!isBlockByPointAround(currPos, findPathObjectCellDiameter))
				//{
				nearestAccessiblePos = currPos;
				return true;
				//}
			}

			currDisLen += DYNAMIC_BLOCK_GRID_SIZE;

			if( currDisLen > disLen)
			{
				return false;
			}
		}

		nearestAccessiblePos = centerPos;
		return false;
	}

	//-----------------------------------------------------------------------
	Bool BlockManager::getPosNearestAccessiblePos( const Vec3 centerPos, Vec3 dir, Flt disLen, Int findPathObjectCellDiameter, Vec3& nearestAccessiblePos )
	{
		if(!mMapDynamicBlock.getIsGridCreated())
		{
			nearestAccessiblePos = centerPos;
			return false;
		}

		if(dir.x == 0 && dir.z == 0)
		{
			nearestAccessiblePos = centerPos;
			return false;
		}

		UInt checkDirNum = 16;
		Int currX = 0;
		Int currZ = 0;

		Vec3 currPos = centerPos;
		Vec3 currDir = dir;
		Flt currDisLen = 0/*DYNAMIC_BLOCK_GRID_SIZE*/;
		Flt partDisLen = findPathObjectCellDiameter * DYNAMIC_BLOCK_GRID_SIZE * 2;
		Bool b = false;

		Vec3 tempNearestAccessiblePos;

		while(1)
		{
			for(UInt i = 0; i <= checkDirNum / 2; ++i)
			{
				if(i != 0)
				{
					if(b)
					{
						currDir = MGMath::rotateVector(dir, 360 / checkDirNum * (checkDirNum - i) * (MG_PI / 180));
						b = false;
					}
					else
					{
						currDir = MGMath::rotateVector(dir, 360 / checkDirNum * i * (MG_PI / 180));

						if(i != checkDirNum / 2)
						{
							--i;
						}

						b = true;
					}
				}

				currPos = centerPos + (currDir * currDisLen);

				if(getPosNearestAccessiblePosForDir(currPos, currDir, partDisLen, findPathObjectCellDiameter, tempNearestAccessiblePos))
				{
					nearestAccessiblePos = tempNearestAccessiblePos;
					return true;
				}
				
			}

			currDir = dir;
			currDisLen += partDisLen;

			if( currDisLen > disLen)
			{
				return false;
			}
		}

		nearestAccessiblePos = centerPos;
		return false;
	
		//UInt checkDirNum = 16;
		//Int currX = 0;
		//Int currZ = 0;

		//Vec3 currPos = centerPos;
		//Vec3 currDir = dir;
		//Flt currDisLen = 0/*DYNAMIC_BLOCK_GRID_SIZE*/;
		//Bool b = false;

		//while(1)
		//{
		//	for(UInt i = 0; i <= checkDirNum / 2; ++i)
		//	{
		//		if(i != 0)
		//		{
		//			if(b)
		//			{
		//				currDir = MGMath::rotateVector(dir, 360 / checkDirNum * (checkDirNum - i) * (MG_PI / 180));
		//				b = false;
		//			}
		//			else
		//			{
		//				currDir = MGMath::rotateVector(dir, 360 / checkDirNum * i * (MG_PI / 180));

		//				if(i != checkDirNum / 2)
		//				{
		//					--i;
		//				}

		//				b = true;
		//			}
		//		}

		//		currPos = centerPos + (currDir * currDisLen);
		//		if(!isDynamicBlockByRadius(currPos, findPathObjectCellDiameter, VERTEX_LEFTDOWN))
		//		{
		//			//if(!isBlockByPointAround(currPos, findPathObjectCellDiameter))
		//			//{
		//				nearestAccessiblePos = currPos;
		//				return true;
		//			//}
		//		}
		//	}
		//	
		//	currDir = dir;
		//	currDisLen += DYNAMIC_BLOCK_GRID_SIZE;

		//	if( currDisLen > disLen)
		//	{
		//		return false;
		//	}
		//}

		//nearestAccessiblePos = centerPos;
		//return false;
	}

	//-----------------------------------------------------------------------
	Bool BlockManager::getPosNearestAccessibleDis( const Vec3 centerPos, Vec3 dir, Int findPathObjectRadius, Flt& nearestAccessibleDis )
	{
		if(!mMapDynamicBlock.getIsGridCreated())
		{
			nearestAccessibleDis = 0;
			return false;
		}

		if(dir.x == 0 && dir.z == 0)
		{
			nearestAccessibleDis = 0;
			return false;
		}

		Int currX = 0;
		Int currZ = 0;
		Int lastX = 0;
		Int lastZ = 0;

		Vec3 currPos = centerPos;

		getDynamicBlockPointByWorldPos(centerPos, currX, currZ);

		while(1/*currCell.x != endCell.x || currCell.y != endCell.y*/)
		{
			currPos += (dir * DYNAMIC_BLOCK_GRID_SIZE);

			getDynamicBlockPointByWorldPos(currPos, currX, currZ);

			if(lastX == currX && lastZ == currZ)
			{
				continue;
			}

			if(isDynamicBlockByRadius(currPos, findPathObjectRadius))
			{
				continue;
			}
			else
			{
				nearestAccessibleDis = (centerPos - currPos).length();
				return true;
			}
		}
		
		nearestAccessibleDis = 0;
		return false;
	}

	//-----------------------------------------------------------------------
	Bool BlockManager::getPassBlockGrid( Vec3 startPos, Vec3 endPos, std::map<UInt, VecU2>& passBlockGridList )
	{
		if(!mMapDynamicBlock.getIsGridCreated())
		{
			return false;
		}

		startPos.y = 0;
		endPos.y = 0;

		Vec3 dir = endPos - startPos;
		dir.y = 0;
		Flt dis = dir.length();
		Flt currDis = 0;
		dir.normalise();

		if(dir.x == 0 && dir.z == 0)
		{
			return false;
		}

		Int currX = 0;
		Int currZ = 0;
		Int LastX = 0;
		Int LastZ = 0;
		Int endX = 0;
		Int endZ = 0;
		UInt index = 0;

		Vec3 currPos = startPos;

		PassGridBlock passGridBlock;

		getDynamicBlockPointByWorldPos(startPos, currX, currZ);
		getDynamicBlockPointByWorldPos(endPos, endX, endZ);

		while(1)
		{
			currPos += (dir * DYNAMIC_BLOCK_GRID_SIZE);

			currDis = (currPos - startPos).length();

			if(currDis > dis)
			{
				return true;
			}

			getDynamicBlockPointByWorldPos(currPos, currX, currZ);

			if(LastX == currX && LastZ == currZ)
			{
				continue;
			}

			index = mMapDynamicBlock.convertGridPointToGridIndex(currX, currZ);

			passBlockGridList[index] = VecU2(currX, currZ);

			LastX = currX;
			LastZ = currZ;

			if(currX == endX && currZ == endZ)
			{
				return true;
			}
		}

		return false;
	}

	//-----------------------------------------------------------------------
	Bool BlockManager::getPassBlockGrid( Vec3 startPos, Vec3 endPos, std::vector<PassGridBlock>& passBlockGridList, UInt diameterSize )
	{
		passBlockGridList.clear();
		if(!mMapDynamicBlock.getIsGridCreated())
		{
			return false;
		}

		startPos.y = 0;
		endPos.y = 0;

		Vec3 dir = endPos - startPos;
		dir.y = 0;
		Flt dis = dir.length();
		Flt currDis = 0;
		dir.normalise();

		if(dir.x == 0 && dir.z == 0)
		{
			return false;
		}

		Int currX = 0;
		Int currZ = 0;
		Int LastX = 0;
		Int LastZ = 0;
		Int endX = 0;
		Int endZ = 0;
		UInt index = 0;

		Vec3 currPos = startPos;

		PassGridBlock passGridBlock;

		getDynamicBlockPointByWorldPos(startPos, currX, currZ);
		getDynamicBlockPointByWorldPos(endPos, endX, endZ);

		while(1)
		{
			currPos += (dir * DYNAMIC_BLOCK_GRID_SIZE);

			currDis = (currPos - startPos).length();

			if(currDis > dis)
			{
				return true;
			}

			getDynamicBlockPointByWorldPos(currPos, currX, currZ);

			if(LastX == currX && LastZ == currZ)
			{
				continue;
			}

			index = mMapDynamicBlock.convertGridPointToGridIndex(currX, currZ);

			passGridBlock.passGridBlockIndex = index;
			passGridBlock.passGridBlockPos = currPos;
			passBlockGridList.push_back(passGridBlock);

			LastX = currX;
			LastZ = currZ;

			if(currX == endX && currZ == endZ)
			{
				return true;
			}
		}

		return false;
	}

    //-----------------------------------------------------------------------
    Bool BlockManager::getNewAddBlockGridListByRect( Vec3 oldPos, Vec3 newPos, std::map<UInt, UInt>& blockGridList, VecI2& minPoint, VecI2& maxPoint, Int diameterSize )
    {
        // TODO:JJJ
        //
		if(!mMapDynamicBlock.getIsGridCreated())
		{
			return false;
		}

		blockGridList.clear();

		Vec2 oldPosVertexPosPos;
		getPosNearestVertexPos(oldPos, oldPosVertexPosPos);

		VertexPos vertexPos;
		Vec2 newPosVertexPosPos;

		if(diameterSize % 2 == 0)
		{
			vertexPos = getPosNearestVertexPos(newPos, newPosVertexPosPos);
		}
		else
		{
			vertexPos = VERTEX_MAX;
			VecU2 gridPoint;
			mMapDynamicBlock.convertWorldPositionToGridPoint(Vec2(newPos.x, newPos.z), gridPoint);
			mMapDynamicBlock.convertGridPointToWorldPosition(gridPoint, newPosVertexPosPos);
		}

		if(oldPosVertexPosPos == newPosVertexPosPos)
		{
			return true;
		}


		Flt offsetX = newPosVertexPosPos.x - oldPosVertexPosPos.x;
		Flt offsetZ = newPosVertexPosPos.y - oldPosVertexPosPos.y;
		Int gridOffsetX = offsetX / mMapDynamicBlock.getGridSize();
		Int gridOffsetZ = offsetZ / mMapDynamicBlock.getGridSize();

		Int minGridOffsetX = 0;
		Int minGridOffsetZ = 0;
		Int maxGridOffsetX = 0;
		Int maxGridOffsetZ = 0;

		Int halfDiameterSize = diameterSize / 2;

		if(abs(gridOffsetX) < diameterSize && abs(gridOffsetZ) < diameterSize)
		{
			if(gridOffsetX > 0)
			{
				minGridOffsetX = (diameterSize - abs(gridOffsetX) + 1);
			}
			else if(gridOffsetX < 0)
			{
				maxGridOffsetX = (diameterSize - abs(gridOffsetX) + 1);
			}

			if(gridOffsetZ > 0)
			{
				maxGridOffsetZ = (diameterSize - abs(gridOffsetZ) + 1);
				//minGridOffsetZ = (diameterSize - abs(gridOffsetZ) + 1);
			}
			else if(gridOffsetZ < 0)
			{
				minGridOffsetZ = (diameterSize - abs(gridOffsetZ) + 1);
				//maxGridOffsetZ = (diameterSize - abs(gridOffsetZ) + 1);
			}
		}


		Int currX = 0;
		Int currZ = 0;
		getDynamicBlockPointByWorldPos(newPos, currX, currZ);

		UInt minXOffSet = 0;
		UInt maxXOffSet = 0;
		UInt minZOffSet = 0;
		UInt maxZOffSet = 0;


		if(vertexPos == VERTEX_LEFTUP)
		{
			//minXOffSet = 0;
			//minZOffSet = 0;
			//maxXOffSet = diameterSize - 1;
			//maxZOffSet = diameterSize - 1;

			//minXOffSet = diameterSize - 1;
			//minZOffSet = 0;
			//maxXOffSet = 0;
			//maxZOffSet = diameterSize - 1;

			minXOffSet = diameterSize * 0.5 + 1;
			maxXOffSet = diameterSize * 0.5 - 1;
			minZOffSet = diameterSize * 0.5 + 1;
			maxZOffSet = diameterSize * 0.5 - 1;
		}
		else if(vertexPos == VERTEX_RIGHTUP)
		{
			//minXOffSet = diameterSize - 1;
			//minZOffSet = 0;
			//maxXOffSet = 0;
			//maxZOffSet = diameterSize - 1;

			//minXOffSet = 0;
			//minZOffSet = 0;
			//maxXOffSet = diameterSize - 1;
			//maxZOffSet = diameterSize - 1;

			minXOffSet = diameterSize * 0.5;
			maxXOffSet = diameterSize * 0.5;
			minZOffSet = diameterSize * 0.5 + 1;
			maxZOffSet = diameterSize * 0.5 - 1;
		}
		else if(vertexPos == VERTEX_RIGHTDOWN)
		{
			//minXOffSet = diameterSize - 1;
			//minZOffSet = diameterSize - 1;
			//maxXOffSet = 0;
			//maxZOffSet = 0;

			//minXOffSet = 0;
			//minZOffSet = diameterSize - 1;
			//maxXOffSet = diameterSize - 1;
			//maxZOffSet = 0;

			minXOffSet = diameterSize * 0.5;
			maxXOffSet = diameterSize * 0.5;
			minZOffSet = diameterSize * 0.5;
			maxZOffSet = diameterSize * 0.5;
		}
		else if(vertexPos == VERTEX_LEFTDOWN)
		{
			//minXOffSet = 0;
			//minZOffSet = diameterSize - 1;
			//maxXOffSet = diameterSize - 1;
			//maxZOffSet = 0;

			//minXOffSet = diameterSize - 1;
			//minZOffSet = diameterSize - 1;
			//maxXOffSet = 0;
			//maxZOffSet = 0;

			minXOffSet = diameterSize * 0.5 + 1;
			maxXOffSet = diameterSize * 0.5 - 1;
			minZOffSet = diameterSize * 0.5;
			maxZOffSet = diameterSize * 0.5;
		}
		else
		{
			minXOffSet = diameterSize * 0.5;
			minZOffSet = diameterSize * 0.5;
			maxXOffSet = diameterSize * 0.5;
			maxZOffSet = diameterSize * 0.5;
		}

		minPoint.x = currX - (Int)minXOffSet;
		minPoint.y = currZ - (Int)minZOffSet;
		maxPoint.x = currX + (Int)maxXOffSet;
		maxPoint.y = currZ + (Int)maxZOffSet;

		 //minXOffSet += minGridOffsetX;
		 //maxXOffSet -= maxGridOffsetX;
		 //minZOffSet += minGridOffsetZ;
		 //maxZOffSet -= maxGridOffsetZ;

		 UInt dynamicBlockMapWidth = mMapDynamicBlock.getWorldGridWidth();
		 UInt dynamicBlockMapHeight = mMapDynamicBlock.getWorldGridHeight();

		 UInt index = 0;

		 if(abs(gridOffsetX) < diameterSize && abs(gridOffsetZ) < diameterSize)
		 {
			 //if(gridOffsetX > 0)
			 //{
				//minGridOffsetX = (diameterSize - 1);
			 //}
			 //else if(gridOffsetX < 0)
			 //{
				//maxGridOffsetX = (diameterSize - 1);
			 //}

			 //if(gridOffsetZ > 0)
			 //{
				// minGridOffsetZ = (diameterSize - 1);
			 //}
			 //else if(gridOffsetZ < 0)
			 //{
				// maxGridOffsetZ = (diameterSize - 1);
			 //}

			 if(gridOffsetZ != 0)
			 {
				 for(Int z = currZ - (Int)minZOffSet + minGridOffsetZ; z <= currZ + (Int)maxZOffSet - maxGridOffsetZ; ++z)
				 {
					 if( z < 1 || z > (Int)dynamicBlockMapHeight )
					 {
						 continue;
					 }

					 for(Int x = currX - (Int)minXOffSet; x <= currX + (Int)maxXOffSet; ++x)
					 {
						 if( x < 1 || x > (Int)dynamicBlockMapWidth )
						 {
							 continue;
						 }

						 index = mMapDynamicBlock.convertGridPointToGridIndex(x,z);
						 blockGridList[index] = index;
					 }
				 }
			 }


			if(gridOffsetX != 0)
			{
				for(Int x = currX - (Int)minXOffSet + minGridOffsetX; x <= currX + (Int)maxXOffSet - maxGridOffsetX; ++x)
				{
					if( x < 1 || x > (Int)dynamicBlockMapWidth )
					{
						continue;
					}

					for(Int z = currZ - (Int)minZOffSet; z <= currZ + (Int)maxZOffSet; ++z)
					{
						if( z < 1 || z > (Int)dynamicBlockMapHeight )
						{
							continue;
						}

						index = mMapDynamicBlock.convertGridPointToGridIndex(x,z);
						blockGridList[index] = index;
					}
				}
			}

		 }
		 else
		 {
			 for(Int z = currZ - (Int)minZOffSet; z <= currZ + (Int)maxZOffSet; ++z)
			 {
				 if( z < 1 || z > (Int)dynamicBlockMapHeight )
				 {
					 continue;
				 }

				 for(Int x = currX - (Int)minXOffSet; x <= currX + (Int)maxXOffSet; ++x)
				 {
					 if( x < 1 || x > (Int)dynamicBlockMapWidth )
					 {
						 continue;
					 }

					 index = mMapDynamicBlock.convertGridPointToGridIndex(x,z);
					 blockGridList[index] = index;
				 }
			 }
		 }

		
		return true;

        //return getBlockGridListByRect( newPos, blockGridList, diameterSize/*, vertexPos*/);
    }

	//-----------------------------------------------------------------------
	IBlockManager::VertexPos BlockManager::getPosNearestVertexPos( Vec3 pos, Vec2& vertexPosPos )
	{
		VecU2 gridPoint;
		mMapDynamicBlock.convertWorldPositionToGridPoint(Vec2(pos.x, pos.z), gridPoint);
		Vec2 gridPos;
		mMapDynamicBlock.convertGridPointToWorldPosition(gridPoint, gridPos);

		Vec2 vertexPosList[VERTEX_MAX];
		vertexPosList[VERTEX_LEFTUP] = Vec2(gridPos.x - DYNAMIC_BLOCK_GRID_SIZE * 0.5, gridPos.y - DYNAMIC_BLOCK_GRID_SIZE * 0.5);
		vertexPosList[VERTEX_RIGHTUP] = Vec2(gridPos.x + DYNAMIC_BLOCK_GRID_SIZE * 0.5, gridPos.y - DYNAMIC_BLOCK_GRID_SIZE * 0.5);
		vertexPosList[VERTEX_RIGHTDOWN] = Vec2(gridPos.x + DYNAMIC_BLOCK_GRID_SIZE * 0.5, gridPos.y + DYNAMIC_BLOCK_GRID_SIZE * 0.5);
		vertexPosList[VERTEX_LEFTDOWN] = Vec2(gridPos.x - DYNAMIC_BLOCK_GRID_SIZE * 0.5, gridPos.y + DYNAMIC_BLOCK_GRID_SIZE * 0.5);
		//vertexPosList[VERTEX_LEFTUP] = Vec2(gridPos.x - DYNAMIC_BLOCK_GRID_SIZE * 0.5, gridPos.y - DYNAMIC_BLOCK_GRID_SIZE * 0.5);
		//vertexPosList[VERTEX_RIGHTUP] = Vec2(gridPos.x + DYNAMIC_BLOCK_GRID_SIZE * 0.5, gridPos.y - DYNAMIC_BLOCK_GRID_SIZE * 0.5);
		//vertexPosList[VERTEX_RIGHTDOWN] = Vec2(gridPos.x + DYNAMIC_BLOCK_GRID_SIZE * 0.5, gridPos.y + DYNAMIC_BLOCK_GRID_SIZE * 0.5);
		//vertexPosList[VERTEX_LEFTDOWN] = Vec2(gridPos.x - DYNAMIC_BLOCK_GRID_SIZE * 0.5, gridPos.y + DYNAMIC_BLOCK_GRID_SIZE * 0.5);

		VertexPos vertexPos;
		Vec2 currPos(pos.x, pos.z);
		Flt minDis = 0;
		Flt tempDis = 0;
		for(Int i = 0; i < VERTEX_MAX; ++i)
		{
			tempDis = (currPos - vertexPosList[i]).length();
			if(i == 0 || minDis > tempDis)
			{
				vertexPos = (VertexPos)i;
				minDis = tempDis;
			}
		}
		
		vertexPosPos = vertexPosList[vertexPos];
		return vertexPos;
	}

	//-----------------------------------------------------------------------
	Bool BlockManager::getOldBlockGridListByRect( Vec3 pos, VecI2 minPoint, VecI2 maxPoint, std::map<UInt, UInt>& blockGridList, Int diameterSize , VertexPos vertexPos )
	{
		if(!mMapDynamicBlock.getIsGridCreated())
		{
			return false;
		}

		blockGridList.clear();

		Int currX = 0;
		Int currZ = 0;
		getDynamicBlockPointByWorldPos(pos, currX, currZ);

		UInt dynamicBlockMapWidth = mMapDynamicBlock.getWorldGridWidth();
		UInt dynamicBlockMapHeight = mMapDynamicBlock.getWorldGridHeight();
		UInt minXOffSet = 0;
		UInt maxXOffSet = 0;
		UInt minZOffSet = 0;
		UInt maxZOffSet = 0;

		if(diameterSize % 2 == 0)
		{
			if(vertexPos == VERTEX_MAX)
			{			
				Vec2 vertexPosPos;
				vertexPos = getPosNearestVertexPos(pos, vertexPosPos);
			}

			if(vertexPos == VERTEX_LEFTUP)
			{
				minXOffSet = diameterSize * 0.5 + 1;
				maxXOffSet = diameterSize * 0.5 - 1;
				minZOffSet = diameterSize * 0.5 + 1;
				maxZOffSet = diameterSize * 0.5 - 1;
			}
			else if(vertexPos == VERTEX_RIGHTUP)
			{
				minXOffSet = diameterSize * 0.5;
				maxXOffSet = diameterSize * 0.5;
				minZOffSet = diameterSize * 0.5 + 1;
				maxZOffSet = diameterSize * 0.5 - 1;
			}
			else if(vertexPos == VERTEX_RIGHTDOWN)
			{
				minXOffSet = diameterSize * 0.5;
				maxXOffSet = diameterSize * 0.5;
				minZOffSet = diameterSize * 0.5;
				maxZOffSet = diameterSize * 0.5;
			}
			else if(vertexPos == VERTEX_LEFTDOWN)
			{
				minXOffSet = diameterSize * 0.5 + 1;
				maxXOffSet = diameterSize * 0.5 - 1;
				minZOffSet = diameterSize * 0.5;
				maxZOffSet = diameterSize * 0.5;
			}
		}
		else
		{
			minXOffSet = diameterSize * 0.5;
			minZOffSet = diameterSize * 0.5;
			maxXOffSet = diameterSize * 0.5;
			maxZOffSet = diameterSize * 0.5;
		}

		Int minGridOffsetX = 0;
		Int minGridOffsetZ = 0;
		Int maxGridOffsetX = 0;
		Int maxGridOffsetZ = 0;

		VecI2 currMinPoint;
		VecI2 currMaxPoint;

		currMinPoint.x = currX - (Int)minXOffSet;
		currMinPoint.y = currZ - (Int)minZOffSet;
		currMaxPoint.x = currX + (Int)maxXOffSet;
		currMaxPoint.y = currZ + (Int)maxZOffSet;

		Int offsetX = currMinPoint.x - minPoint.x;
		Int offsetZ = currMinPoint.y - minPoint.y;


		if(offsetX == 0 && offsetZ == 0)
		{
			return true;
		}

		if(abs(offsetX) < diameterSize && abs(offsetZ) < diameterSize)
		{
			if(offsetX > 0)
			{
				maxGridOffsetX = (diameterSize - abs(offsetX) + 1);
			}
			else if(offsetX < 0)
			{
				minGridOffsetX = (diameterSize - abs(offsetX) + 1);
			}

			if(offsetZ > 0)
			{
				maxGridOffsetZ = (diameterSize - abs(offsetZ) + 1);
				//minGridOffsetZ = (diameterSize - abs(offsetZ) + 1);
			}
			else if(offsetZ < 0)
			{
				minGridOffsetZ = (diameterSize - abs(offsetZ) + 1);
				//minGridOffsetZ = (diameterSize - abs(offsetZ) + 1);
			}

			UInt index = 0;

			if(offsetZ != 0)
			{
				for(Int z = minPoint.y + minGridOffsetZ; z <= maxPoint.y - maxGridOffsetZ; ++z)
				{
					if( z < 1 || z > (Int)dynamicBlockMapHeight )
					{
						continue;
					}

					for(Int x = minPoint.x; x <= maxPoint.x; ++x)
					{
						if( x < 1 || x > (Int)dynamicBlockMapWidth )
						{
							continue;
						}

						index = mMapDynamicBlock.convertGridPointToGridIndex(x,z);
						blockGridList[index] = index;
					}
				}
				//for(Int z = currZ - (Int)minZOffSet + minGridOffsetZ; z <= currZ + (Int)maxZOffSet - maxGridOffsetZ; ++z)
				//{
				//	if( z < 1 || z > (Int)dynamicBlockMapHeight )
				//	{
				//		continue;
				//	}

				//	for(Int x = currX - (Int)minXOffSet; x <= currX + (Int)maxXOffSet; ++x)
				//	{
				//		if( x < 1 || x > (Int)dynamicBlockMapWidth )
				//		{
				//			continue;
				//		}

				//		index = mMapDynamicBlock.convertGridPointToGridIndex(x,z);
				//		blockGridList[index] = index;
				//	}
				//}
			}

			if(offsetX != 0)
			{
				for(Int x = minPoint.x + minGridOffsetX; x <= maxPoint.x - maxGridOffsetX; ++x)
				{
					if( x < 1 || x > (Int)dynamicBlockMapWidth )
					{
						continue;
					}

					for(Int z = minPoint.y; z <= maxPoint.y; ++z)
					{
						if( z < 1 || z > (Int)dynamicBlockMapHeight )
						{
							continue;
						}

						index = mMapDynamicBlock.convertGridPointToGridIndex(x,z);
						blockGridList[index] = index;
					}
				}
			}


			//if(offsetX != 0)
			//{
			//	for(Int x = currX - (Int)minXOffSet + minGridOffsetX; x <= currX + (Int)maxXOffSet - maxGridOffsetX; ++x)
			//	{
			//		if( x < 1 || x > (Int)dynamicBlockMapWidth )
			//		{
			//			continue;
			//		}

			//		for(Int z = currZ - (Int)minZOffSet; z <= currZ + (Int)maxZOffSet; ++z)
			//		{
			//			if( z < 1 || z > (Int)dynamicBlockMapHeight )
			//			{
			//				continue;
			//			}

			//			index = mMapDynamicBlock.convertGridPointToGridIndex(x,z);
			//			blockGridList[index] = index;
			//		}
			//	}
			//}
		}
		else
		{
			return false;
		}

		return true;
	}

	//-----------------------------------------------------------------------
	Bool BlockManager::getBlockGridListByRect( Vec3 pos, std::map<UInt, UInt>& blockGridList, VecI2& minPoint, VecI2& maxPoint, Int diameterSize, VertexPos vertexPos )
	{
		if(!mMapDynamicBlock.getIsGridCreated())
		{
			return false;
		}

		blockGridList.clear();

		Int currX = 0;
		Int currZ = 0;
		getDynamicBlockPointByWorldPos(pos, currX, currZ);

		UInt dynamicBlockMapWidth = mMapDynamicBlock.getWorldGridWidth();
		UInt dynamicBlockMapHeight = mMapDynamicBlock.getWorldGridHeight();
		UInt minXOffSet = 0;
		UInt maxXOffSet = 0;
		UInt minZOffSet = 0;
		UInt maxZOffSet = 0;

		if(diameterSize % 2 == 0)
		{
			if(vertexPos == VERTEX_MAX)
			{			
				//VecU2 gridPoint;
				//mMapDynamicBlock.convertWorldPositionToGridPoint(Vec2(pos.x, pos.z), gridPoint);
				//Vec2 gridPos;
				//mMapDynamicBlock.convertGridPointToWorldPosition(gridPoint, gridPos);

				//Vec2 vertexPosList[VERTEX_MAX];
				//vertexPosList[VERTEX_LEFTUP] = Vec2(gridPos.x - DYNAMIC_BLOCK_GRID_SIZE * 0.5, gridPos.y - DYNAMIC_BLOCK_GRID_SIZE * 0.5);
				//vertexPosList[VERTEX_RIGHTUP] = Vec2(gridPos.x + DYNAMIC_BLOCK_GRID_SIZE * 0.5, gridPos.y - DYNAMIC_BLOCK_GRID_SIZE * 0.5);
				//vertexPosList[VERTEX_RIGHTDOWN] = Vec2(gridPos.x + DYNAMIC_BLOCK_GRID_SIZE * 0.5, gridPos.y + DYNAMIC_BLOCK_GRID_SIZE * 0.5);
				//vertexPosList[VERTEX_LEFTDOWN] = Vec2(gridPos.x - DYNAMIC_BLOCK_GRID_SIZE * 0.5, gridPos.y + DYNAMIC_BLOCK_GRID_SIZE * 0.5);
				////vertexPosList[VERTEX_LEFTUP] = Vec2(gridPos.x - DYNAMIC_BLOCK_GRID_SIZE * 0.5, gridPos.y - DYNAMIC_BLOCK_GRID_SIZE * 0.5);
				////vertexPosList[VERTEX_RIGHTUP] = Vec2(gridPos.x + DYNAMIC_BLOCK_GRID_SIZE * 0.5, gridPos.y - DYNAMIC_BLOCK_GRID_SIZE * 0.5);
				////vertexPosList[VERTEX_RIGHTDOWN] = Vec2(gridPos.x + DYNAMIC_BLOCK_GRID_SIZE * 0.5, gridPos.y + DYNAMIC_BLOCK_GRID_SIZE * 0.5);
				////vertexPosList[VERTEX_LEFTDOWN] = Vec2(gridPos.x - DYNAMIC_BLOCK_GRID_SIZE * 0.5, gridPos.y + DYNAMIC_BLOCK_GRID_SIZE * 0.5);

				//Vec2 currPos(pos.x, pos.z);
				//Flt minDis = 0;
				//Flt tempDis = 0;
				//for(Int i = 0; i < VERTEX_MAX; ++i)
				//{
				//	tempDis = (currPos - vertexPosList[i]).length();
				//	if(i == 0 || minDis > tempDis)
				//	{
				//		vertexPos = (VertexPos)i;
				//		minDis = tempDis;
				//	}
				//}
				Vec2 vertexPosPos;
				vertexPos = getPosNearestVertexPos(pos, vertexPosPos);
			}

			if(vertexPos == VERTEX_LEFTUP)
			{
				//minXOffSet = 0;
				//minZOffSet = 0;
				//maxXOffSet = diameterSize - 1;
				//maxZOffSet = diameterSize - 1;

				//minXOffSet = diameterSize - 1;
				//minZOffSet = 0;
				//maxXOffSet = 0;
				//maxZOffSet = diameterSize - 1;

				minXOffSet = diameterSize * 0.5 + 1;
				maxXOffSet = diameterSize * 0.5 - 1;
				minZOffSet = diameterSize * 0.5 + 1;
				maxZOffSet = diameterSize * 0.5 - 1;
			}
			else if(vertexPos == VERTEX_RIGHTUP)
			{
				//minXOffSet = diameterSize - 1;
				//minZOffSet = 0;
				//maxXOffSet = 0;
				//maxZOffSet = diameterSize - 1;

				//minXOffSet = 0;
				//minZOffSet = 0;
				//maxXOffSet = diameterSize - 1;
				//maxZOffSet = diameterSize - 1;

				minXOffSet = diameterSize * 0.5;
				maxXOffSet = diameterSize * 0.5;
				minZOffSet = diameterSize * 0.5 + 1;
				maxZOffSet = diameterSize * 0.5 - 1;
			}
			else if(vertexPos == VERTEX_RIGHTDOWN)
			{
				//minXOffSet = diameterSize - 1;
				//minZOffSet = diameterSize - 1;
				//maxXOffSet = 0;
				//maxZOffSet = 0;

				//minXOffSet = 0;
				//minZOffSet = diameterSize - 1;
				//maxXOffSet = diameterSize - 1;
				//maxZOffSet = 0;

				minXOffSet = diameterSize * 0.5;
				maxXOffSet = diameterSize * 0.5;
				minZOffSet = diameterSize * 0.5;
				maxZOffSet = diameterSize * 0.5;
			}
			else if(vertexPos == VERTEX_LEFTDOWN)
			{
				//minXOffSet = 0;
				//minZOffSet = diameterSize - 1;
				//maxXOffSet = diameterSize - 1;
				//maxZOffSet = 0;

				//minXOffSet = diameterSize - 1;
				//minZOffSet = diameterSize - 1;
				//maxXOffSet = 0;
				//maxZOffSet = 0;

				minXOffSet = diameterSize * 0.5 + 1;
				maxXOffSet = diameterSize * 0.5 - 1;
				minZOffSet = diameterSize * 0.5;
				maxZOffSet = diameterSize * 0.5;
			}
		}
		else
		{
			minXOffSet = diameterSize * 0.5;
			minZOffSet = diameterSize * 0.5;
			maxXOffSet = diameterSize * 0.5;
			maxZOffSet = diameterSize * 0.5;
		}

		minPoint.x = currX - (Int)minXOffSet;
		minPoint.y = currZ - (Int)minZOffSet;
		maxPoint.x = currX - (Int)maxXOffSet;
		maxPoint.y = currZ - (Int)maxZOffSet;

		UInt index = 0;
		for(Int z = currZ - (Int)minZOffSet; z <= currZ + (Int)maxZOffSet; ++z)
		{
			if( z < 1 || z > (Int)dynamicBlockMapHeight )
			{
				continue;
			}

			for(Int x = currX - (Int)minXOffSet; x <= currX + (Int)maxXOffSet; ++x)
			{
				if( x < 1 || x > (Int)dynamicBlockMapWidth )
				{
					continue;
				}
				
				index = mMapDynamicBlock.convertGridPointToGridIndex(x,z);
				blockGridList[index] = index;
			}
		}

		return true;
	}

	//-----------------------------------------------------------------------
	void BlockManager::addDynamicBlockObjectToGridBlock(UInt gridIndex, IDynamicBlockObject* object, Byte flag)
	{
        DynamicBlockObjectList& list = getDynamicBlockObjectList(flag);

		std::map<UInt, IDynamicBlockObject*>::iterator it = list.find(gridIndex);
        if( it == list.end() )
        {
            list[gridIndex] = object;
        }else
        {
            if ( it->second != object )
                DYNAMIC_ASSERT(false);
        }

	}

	//-----------------------------------------------------------------------
	Bool BlockManager::removeDynamicBlockObjectFromGridBlock(UInt gridIndex, IDynamicBlockObject* object, Byte flag)
	{
        DynamicBlockObjectList& list = getDynamicBlockObjectList( flag );

		std::map<UInt, IDynamicBlockObject*>::iterator it = list.find(gridIndex);
		if(it == list.end() || it->second != object)
		{
			//DYNAMIC_ASSERT(false);
			return false;
		}
		list.erase(it);
		return true;
	}

    //-----------------------------------------------------------------------
    IDynamicBlockObject* BlockManager::getDynamicBlockObjectFromGridBlock(UInt gridIndex)
    {
        IDynamicBlockObject* result = NULL;

        result = getDynamicBlockObjectFromGridBlock( gridIndex, BlockManager::BLF_ENTITY_ALLSIDE_BLOCK );
        if ( result )
            return result;

		result = getDynamicBlockObjectFromGridBlock( gridIndex, BlockManager::BLF_STRUCTURE_ALLSIDE_BLOCK );
		if ( result )
			return result;

        result = getDynamicBlockObjectFromGridBlock( gridIndex, BlockManager::BLF_STRUCTURE_INSIDE_BLOCK );
        if ( result )
            return result;

        result = getDynamicBlockObjectFromGridBlock( gridIndex, BlockManager::BLF_STRUCTURE_OUTSIDE_BLOCK );
        if ( result )
            return result;


        return result;
    }

	//-----------------------------------------------------------------------
	IDynamicBlockObject* BlockManager::getDynamicBlockObjectFromGridBlock(UInt gridIndex, Byte flag)
	{
        DynamicBlockObjectList& list = getDynamicBlockObjectList( flag );

		std::map<UInt, IDynamicBlockObject*>::iterator it = list.find(gridIndex);
		if(it == list.end())
		{
			return NULL;
		}

		return it->second;
	}

	//-----------------------------------------------------------------------
	void BlockManager::getBlockGridListByTriangle3DList(  std::map<UInt, VecU2>& gridPointList, std::vector<Triangle3D>&  mWorldTriangle3DList, Bool isStaticBlock )
	{

		GridPool<Byte>*	mapBlock = NULL;
		Int stepSize = 1;
		if(isStaticBlock == true)
		{
			mapBlock = &mMapStaticBlock;
		}
		else
		{
			mapBlock = &mMapDynamicBlock;
			stepSize *= 2;
		}

		if(!mapBlock->getIsGridCreated() || mWorldTriangle3DList.size() == 0)
		{
			return;
		}

		gridPointList.clear();

		Flt minX, minZ, maxX, maxZ = 0;

		Vec2 leftUpGridPoint, rightDownGridPoint, gridWorldPosP, gridWorldPosD;

		Vector2 intersectTempPos, intersectPos[2];

		Vec2 intersectGridPoint1, intersectGridPoint2;

		Int intersectNum = 0;

		for(UInt i = 0; i < mWorldTriangle3DList.size(); ++i)
		{
			Vector3 posList[3];
			posList[0] = mWorldTriangle3DList[i].t0;
			posList[1] = mWorldTriangle3DList[i].t1;
			posList[2] = mWorldTriangle3DList[i].t2;

			for(UInt j = 0; j < 3; ++j)
			{
				if(j == 0)
				{
					minX = posList[j].x;
					maxX = posList[j].x;
					minZ = posList[j].z;
					maxZ = posList[j].z;

					continue;
				}

				if(posList[j].x > maxX)
				{
					maxX = posList[j].x;
				}
				if(posList[j].x < minX)
				{
					minX = posList[j].x;
				}	
				if(posList[j].z > maxZ)
				{
					maxZ = posList[j].z;
				}
				if(posList[j].z < minZ)
				{
					minZ = posList[j].z;
				}
			}

			if(abs(maxX - minX) >= abs(maxZ - minZ))
			{
				getGridByOneWorldBlockTriangleByColScan(mapBlock, posList, Vec2(minX, minZ), Vec2(maxX, maxZ), stepSize, gridPointList);
			}
			else
			{
				getGridByOneWorldBlockTriangleByRowScan(mapBlock, posList, Vec2(minX, minZ), Vec2(maxX, maxZ), stepSize, gridPointList);
			}

		}
	}

	//-----------------------------------------------------------------------
	Bool BlockManager::getLineTriangleIntersectPoint( Vector2 lineP, Vector2 lineD, Vector3* trianglePosList, Vector2* intersectPos )
	{
		UInt vectorPIndex = 0;
		UInt vectorDIndex = 0;
		Int intersectNum = 0;

		for(UInt i = 0; i < 3; ++i)
		{
			if(i != 2)
			{
				vectorPIndex = i;
				vectorDIndex = i + 1;
			}
			else
			{
				vectorPIndex = i;
				vectorDIndex = 0;
			}
			
			Vector2 intersectTempPos;

			if(MGEngineUtility::calculateIntersectPoint(lineP, lineD - lineP, Vector2( trianglePosList[vectorPIndex].x, trianglePosList[vectorPIndex].z ), Vector2( trianglePosList[vectorDIndex].x, trianglePosList[vectorDIndex].z ) - Vector2( trianglePosList[vectorPIndex].x, trianglePosList[vectorPIndex].z ), intersectTempPos) == 1)
			{
				intersectPos[intersectNum] = intersectTempPos;
				intersectNum++;
			}
		}

		if(intersectNum < 2 || intersectNum >= 3)
		{
			return false;
		}

		return true;
	}

	//-----------------------------------------------------------------------
	void BlockManager::getGridByOneWorldBlockTriangleByRowScan( GridPool<Byte>* mapBlock, Vector3* posList, Vec2 minPoint, Vec2 maxPoint, Int stepSize, std::map<UInt, VecU2>& gridPointList )
	{
		VecU2 leftUpGridPoint;
		VecU2 rightDownGridPoint;

		Vec2 gridWorldPosP;
		Vec2 gridWorldPosD;

		Vector2 intersectPos[2];
		VecU2 intersectGridPoint1;
		VecU2 intersectGridPoint2;

		Int intersectGridPointMinX = 0;
		Int intersectGridPointMaxX = 0;

		Flt blockSize = mapBlock->getGridSize();
		Flt blockHalfSize = blockSize * 0.5;

		mapBlock->convertWorldPositionToGridPoint(minPoint, leftUpGridPoint);
		mapBlock->convertWorldPositionToGridPoint(maxPoint, rightDownGridPoint);

		UInt index = 0;
		VecU2 gridPoint;
		Bool isContinue = false;
		
		for(UInt i = 0; i < 3; ++i)
		{
			mapBlock->convertWorldPositionToGridPoint(Vec2(posList[i].x, posList[i].z), gridPoint);
			index = mapBlock->convertGridPointToGridIndex(gridPoint);
			gridPointList[index] = gridPoint;

			UInt endPosIndex = 0;
			if(i != 2)
			{
				endPosIndex = i + 1;
			}

			getPassBlockGrid(Vec3(posList[i].x, 0 , posList[i].z), Vec3(posList[endPosIndex].x, 0 , posList[endPosIndex].z), gridPointList);

			Vector3 dir = posList[endPosIndex] - posList[i];
			dir.y = 0;

			Flt dis = dir.length();

			if(dis > blockSize * 2)
			{
				isContinue = true;
			}
		}

		if(!isContinue)
		{
			return;
		}

		for(UInt z = rightDownGridPoint.y; z <= leftUpGridPoint.y; z += stepSize)
		{
			intersectPos[0] = 0;
			intersectPos[1] = 0;

			if(z == leftUpGridPoint.y)
			{
				gridWorldPosP = Vec2(minPoint.x, minPoint.y + blockHalfSize);
				gridWorldPosD = Vec2(maxPoint.x, minPoint.y + blockHalfSize);
			}
			else if(z == rightDownGridPoint.y)
			{
				gridWorldPosP = Vec2(minPoint.x ,maxPoint.y - blockHalfSize);
				gridWorldPosD = Vec2(maxPoint.x, maxPoint.y - blockHalfSize);
			}
			else
			{
				mapBlock->convertGridPointToWorldPosition(VecU2(leftUpGridPoint.x,z), gridWorldPosP);
				mapBlock->convertGridPointToWorldPosition(VecU2(rightDownGridPoint.x,z), gridWorldPosD);				
			}

			gridWorldPosP.x -= blockHalfSize;
			gridWorldPosD.x += blockHalfSize;

			if(!getLineTriangleIntersectPoint(Vector2(gridWorldPosP.x,gridWorldPosP.y), Vector2(gridWorldPosD.x,gridWorldPosD.y), posList, intersectPos))
			{
				continue;
			}

			mapBlock->convertWorldPositionToGridPoint(Vec2(intersectPos[0].x, intersectPos[0].y), intersectGridPoint1);
			mapBlock->convertWorldPositionToGridPoint(Vec2(intersectPos[1].x, intersectPos[1].y), intersectGridPoint2);

			index = mapBlock->convertGridPointToGridIndex(intersectGridPoint1);
			gridPointList[index] = intersectGridPoint1;
			index = mapBlock->convertGridPointToGridIndex(intersectGridPoint2);
			gridPointList[index] = intersectGridPoint2;

			Flt blockNum = abs( intersectPos[0].x - intersectPos[1].x);
			UInt  xNum = blockNum / blockSize;

			if(intersectGridPoint2.x > intersectGridPoint1.x)
			{
				intersectGridPointMinX = intersectGridPoint1.x;
			}
			else
			{
				intersectGridPointMinX = intersectGridPoint2.x;
			}

			for(UInt x = 0; x <= xNum; ++x)
			{
				for(UInt stepSizeZ = 0; stepSizeZ < (UInt)stepSize; ++stepSizeZ)
				{
					gridPoint = VecU2(intersectGridPointMinX + x, intersectGridPoint1.y + stepSizeZ);
					index = mapBlock->convertGridPointToGridIndex(gridPoint);
					gridPointList[index] = gridPoint;
				}
			}
		}
	}

	//-----------------------------------------------------------------------
	void BlockManager::getGridByOneWorldBlockTriangleByColScan( GridPool<Byte>* mapBlock, Vector3* posList, Vec2 minPoint, Vec2 maxPoint, Int stepSize, std::map<UInt, VecU2>& gridPointList )
	{
		VecU2 leftUpGridPoint;
		VecU2 rightDownGridPoint;

		Vec2 gridWorldPosP;
		Vec2 gridWorldPosD;

		Vector2 intersectPos[2];
		VecU2 intersectGridPoint1;
		VecU2 intersectGridPoint2;

		Int intersectGridPointMinY = 0;
		Int intersectGridPointMaxY = 0;

		Flt blockSize = mapBlock->getGridSize();
		Flt blockHalfSize = blockSize * 0.5;

		mapBlock->convertWorldPositionToGridPoint(minPoint, leftUpGridPoint);
		mapBlock->convertWorldPositionToGridPoint(maxPoint, rightDownGridPoint);

		UInt index = 0;
		VecU2 gridPoint;
		Bool isContinue = false;

		for(UInt i = 0; i < 3; ++i)
		{
			mapBlock->convertWorldPositionToGridPoint(Vec2(posList[i].x, posList[i].z), gridPoint);
			index = mapBlock->convertGridPointToGridIndex(gridPoint);
			gridPointList[index] = gridPoint;

			UInt endPosIndex = 0;
			if(i != 2)
			{
				endPosIndex = i + 1;
			}

			getPassBlockGrid(Vec3(posList[i].x, 0 , posList[i].z), Vec3(posList[endPosIndex].x, 0 , posList[endPosIndex].z), gridPointList);

			Vector3 dir = posList[endPosIndex] - posList[i];
			dir.y = 0;

			Flt dis = dir.length();

			if(dis > blockSize * 2)
			{
				isContinue = true;
			}
		}

		if(!isContinue)
		{
			return;
		}

		for(UInt x = leftUpGridPoint.x; x <= rightDownGridPoint.x; x += stepSize)
		{
			intersectPos[0] = 0;
			intersectPos[1] = 0;

			if(x == leftUpGridPoint.x)
			{
				gridWorldPosP = Vec2(minPoint.x + blockHalfSize, minPoint.y);
				gridWorldPosD = Vec2(minPoint.x + blockHalfSize, maxPoint.y);
			}
			else if(x == rightDownGridPoint.x)
			{
				gridWorldPosP = Vec2(maxPoint.x - blockHalfSize, minPoint.y);
				gridWorldPosD = Vec2(maxPoint.x - blockHalfSize, maxPoint.y);
			}
			else
			{
				mapBlock->convertGridPointToWorldPosition(VecU2(x,rightDownGridPoint.y), gridWorldPosP);
				mapBlock->convertGridPointToWorldPosition(VecU2(x,leftUpGridPoint.y), gridWorldPosD);							
			}

			gridWorldPosP.y += blockHalfSize;
			gridWorldPosD.y -= blockHalfSize;

			if(!getLineTriangleIntersectPoint(Vector2(gridWorldPosP.x,gridWorldPosP.y), Vector2(gridWorldPosD.x,gridWorldPosD.y), posList, intersectPos))
			{
				continue;
			}

			mapBlock->convertWorldPositionToGridPoint(Vec2(intersectPos[0].x, intersectPos[0].y), intersectGridPoint1);
			mapBlock->convertWorldPositionToGridPoint(Vec2(intersectPos[1].x, intersectPos[1].y), intersectGridPoint2);

			index = mapBlock->convertGridPointToGridIndex(intersectGridPoint1);
			gridPointList[index] = intersectGridPoint1;
			index = mapBlock->convertGridPointToGridIndex(intersectGridPoint2);
			gridPointList[index] = intersectGridPoint2;

			Flt blockNum = abs(intersectPos[0].y - intersectPos[1].y);

			UInt zNum = blockNum / blockSize;

			if(intersectGridPoint1.y > intersectGridPoint2.y)
			{
				intersectGridPointMinY = intersectGridPoint2.y;
			}
			else
			{
				intersectGridPointMinY = intersectGridPoint1.y;
			}

			for(UInt z = 0; z <= zNum; ++z)
			{
				for(UInt stepSizeX = 0; stepSizeX < (UInt)stepSize; ++stepSizeX)
				{
					gridPoint = VecU2(intersectGridPoint1.x + stepSizeX, intersectGridPointMinY + z);
					index = mapBlock->convertGridPointToGridIndex(gridPoint);
					gridPointList[index] = gridPoint;
				}
			}
		}
	}

    //-----------------------------------------------------------------------
    Bool BlockManager::isIntersectionWithDynamicGridByGridIndex( Vec3 startPos, Vec3 endPos, UInt index )
    {
        if(!mMapDynamicBlock.getIsGridCreated())
        {
            return false;
        }

        /* /
        +z
        |
        |
        v0----0----v1
        |          |
        3  [Grid]  1
        |          |
        v2----2----v3----+x
        */

        Vec3 centerPos = getDynamicBlockGridCenterPosByIndex( index );
        Flt radius = DYNAMIC_BLOCK_GRID_SIZE * 0.5;

        Vector2 cn  = Vector2(centerPos.x,centerPos.z);
        Vector2 v0  = cn + Vector2( -radius, -radius );
        Vector2 v1  = cn + Vector2( radius, -radius );
        Vector2 v2  = cn + Vector2( -radius, radius );
        Vector2 v3  = cn + Vector2( radius, radius );

        Vector2 sn  = Vector2( startPos.x, startPos.z );
        Vector2 en  = Vector2( endPos.x, endPos.z );
        Vector2 d0 = (en - sn);

        ///////////////////////////////////////////////////////////////////////////////////

        Vector2 inp;

        if ( MGEngineUtility::calculateIntersectPoint(sn, d0, v0, v1-v0, inp) == 1 )
        {
            return true;
        }
        if ( MGEngineUtility::calculateIntersectPoint(sn, d0, v1, v3-v1, inp) == 1 )
        {
            return true;
        }
        if ( MGEngineUtility::calculateIntersectPoint(sn, d0, v3, v2-v3, inp) == 1 )
        {
            return true;
        }
        if ( MGEngineUtility::calculateIntersectPoint(sn, d0, v2, v0-v2, inp) == 1 )
        {
            return true;
        }

        return false;
    }

    //-----------------------------------------------------------------------
    BlockManager::DynamicBlockObjectList& BlockManager::getDynamicBlockObjectList( Byte flag )
    {
        std::map<Byte, DynamicBlockObjectList>::iterator iter = mDynamicBlockObjectListMap.find( flag );
        if ( iter == mDynamicBlockObjectListMap.end() )
        {
            mDynamicBlockObjectListMap[flag] = DynamicBlockObjectList();
        }

        return mDynamicBlockObjectListMap[flag];
    }

	//-----------------------------------------------------------------------
	Bool BlockManager::isBlockByPointAround(Vec3 pos, UInt findPathObjectCellDiameter)
	{
		if(!mMapDynamicBlock.getIsGridCreated())
		{
			return false;
		}

		Vec3 dir(1,0,0);
		Vec3 currDir;
		Vec3 currPos;
		Flt dis = DYNAMIC_BLOCK_GRID_SIZE;

		for(UInt i = 0; i < 16; ++i)
		{
			currDir = MGMath::rotateVector(dir, 360 / 16 * i * (MG_PI / 180));
			currPos = pos + (currDir * dis);
			if(isDynamicBlockByRadius(currPos, findPathObjectCellDiameter, VERTEX_LEFTDOWN))
			{
				return true;
			}
		}

		return false;
	}


}